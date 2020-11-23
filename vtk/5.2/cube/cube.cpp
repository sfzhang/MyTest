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
#include <vtkAutoInit.h>
#include <iostream>
#include <array>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto colors = vtkSmartPointer<vtkNamedColors>(vtkNamedColors::New());

    auto pts = array<array<double, 3>, 8>{ {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
        {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
    } };

    auto ordering = array<array<vtkIdType, 4>, 6>{ {
        {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 5, 4},
        {1, 2, 6, 5}, {2, 3, 7, 6}, {3, 0, 4, 7}
    } };

    auto points = vtkSmartPointer<vtkPoints>(vtkPoints::New());
    auto scalars = vtkSmartPointer<vtkFloatArray>(vtkFloatArray::New());

    scalars->SetNumberOfComponents(3);
    for (size_t i = 0; i < pts.size(); i++) {
        points->InsertPoint(i, pts[i].data());

        // throw default LUT
        //scalars->InsertTuple1(i, 1.0 * i / pts.size());

        // use as colors without mapping
        if (i < 4) {
            scalars->InsertTuple3(i, 1, 0, 0);
        }
        else {
            scalars->InsertTuple3(i, 0, 1, 0);
        }
    }

    auto cells = vtkSmartPointer<vtkCellArray>(vtkCellArray::New());
    for (auto &&i: ordering) {
        cells->InsertNextCell(static_cast<vtkIdType>(i.size()), i.data());
    }

    auto cube = vtkSmartPointer<vtkPolyData>(vtkPolyData::New());
    cube->SetPoints(points);
    cube->SetPolys(cells);
    cube->GetPointData()->SetScalars(scalars);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputData(cube);

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

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