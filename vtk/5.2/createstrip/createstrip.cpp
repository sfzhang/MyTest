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
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto points = vtkSmartPointer<vtkPoints>(vtkPoints::New());
    points->InsertPoint(0, 0, 0, 0);
    points->InsertPoint(1, 0, 1, 0);
    points->InsertPoint(2, 1, 0, 0);
    points->InsertPoint(3, 1, 1, 0);
    points->InsertPoint(4, 2, 0, 0);
    points->InsertPoint(5, 2, 1, 0);
    points->InsertPoint(6, 3, 0, 0);
    points->InsertPoint(7, 3, 1, 0);

    auto strips = vtkSmartPointer<vtkCellArray>(vtkCellArray::New());
    strips->InsertNextCell(4);
    for (int i = 0; i < 4; i++) {
        strips->InsertCellPoint(i);
    }
    strips->InsertNextCell(4);
    for (int i = 4; i < 8; i++) {
        strips->InsertCellPoint(i);
    }
    
    auto profile = vtkSmartPointer<vtkPolyData>(vtkPolyData::New());
    profile->SetPoints(points);
    profile->SetStrips(strips);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputData(profile);

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.38, 0.7, 0.16);
    actor->GetProperty()->SetRepresentationToWireframe();

    auto i = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    auto w = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    i->SetRenderWindow(w);

    auto r = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    w->AddRenderer(r);
    r->AddActor(actor);

    r->SetBackground(1, 1, 1);
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