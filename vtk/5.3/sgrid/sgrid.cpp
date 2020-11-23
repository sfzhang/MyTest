#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkNamedColors.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkMath.h>
#include <vtkHedgeHog.h>
#include <vtkStructuredGrid.h>
#include <vtkAutoInit.h>
#include <iostream>
#include <array>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto colors = vtkSmartPointer<vtkNamedColors>(vtkNamedColors::New());

    float rmin = 0.5, rmax = 1.0;

    auto dims = array<int, 3>{ {13, 11, 11} };

    auto vectors = vtkSmartPointer<vtkFloatArray>(vtkFloatArray::New());
    vectors->SetNumberOfComponents(3);
    vectors->SetNumberOfTuples(dims[0] * dims[1] * dims[2]);

    auto points = vtkSmartPointer<vtkPoints>(vtkPoints::New());
    points->Allocate(dims[0] * dims[1] * dims[2]);

    auto delata_z = 2.0 / (dims[2] - 1);
    auto delta_rad = (rmax - rmin) / (dims[1] - 1);

    float x[3] = {0};
    float v[3] = {0};
    v[2] = 0;

    for (int k = 0; k < dims[2]; k++) {
        x[2] = -1 + k * delata_z;
        int k_offset = k * dims[0] * dims[1];
        for (auto j = 0; j < dims[1]; j++) {
            float r = rmin + j * delta_rad;
            int j_offset = j * dims[0];

            for (auto i = 0; i < dims[0]; i++) {
                float theta = i * vtkMath::RadiansFromDegrees(15.0);
                x[0] = r * cos(theta);
                x[1] = r * sin(theta);
                v[0] = -x[1];
                v[1] = x[0];

                int offset = i + j_offset + k_offset;
                points->InsertPoint(offset, x);
                vectors->InsertTuple(offset, v);
            }
        }
    }

    auto sgrid = vtkSmartPointer<vtkStructuredGrid>(vtkStructuredGrid::New());
    sgrid->SetPoints(points);
    sgrid->GetPointData()->SetVectors(vectors);

    auto hedgehog = vtkSmartPointer<vtkHedgeHog>(vtkHedgeHog::New());
    hedgehog->SetInputData(sgrid);
    hedgehog->SetScaleFactor(0.1);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(hedgehog->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("Indiog").GetData());

    auto i = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    auto w = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    i->SetRenderWindow(w);

    auto r = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    w->AddRenderer(r);
    r->AddActor(actor);
    r->SetBackground(colors->GetColor3d("Cornsilk").GetData());

    w->SetSize(400, 400);

    w->Render();

    auto camera = r->GetActiveCamera();
    camera->Azimuth(60.0);
    camera->Roll(-90);
    camera->Dolly(2);
    r->ResetCameraClippingRange();

    w->Render();
    i->Start();

    return 0;
}