#include <vtkCylinderSource.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkAppendPolyData.h>
#include <vtkDepthSortPolyData.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto sphere1 = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere1->SetThetaResolution(80);
    sphere1->SetPhiResolution(40);
    sphere1->SetRadius(1);
    sphere1->SetCenter(0, 0, 0);

    auto sphere2 = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere2->SetThetaResolution(80);
    sphere2->SetPhiResolution(40);
    sphere2->SetRadius(0.5);
    sphere2->SetCenter(1, 0, 0);

    auto sphere3 = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere3->SetThetaResolution(80);
    sphere3->SetPhiResolution(40);
    sphere3->SetRadius(0.5);
    sphere3->SetCenter(-1, 0, 0);

    auto sphere4 = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere4->SetThetaResolution(80);
    sphere4->SetPhiResolution(40);
    sphere4->SetRadius(0.5);
    sphere4->SetCenter(0, 1, 0);

    auto sphere5 = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere5->SetThetaResolution(80);
    sphere5->SetPhiResolution(40);
    sphere5->SetRadius(0.5);
    sphere5->SetCenter(0, -1, 0);

    auto append_data = vtkSmartPointer<vtkAppendPolyData>(vtkAppendPolyData::New());
    append_data->AddInputConnection(sphere1->GetOutputPort());
    append_data->AddInputConnection(sphere2->GetOutputPort());
    append_data->AddInputConnection(sphere3->GetOutputPort());
    append_data->AddInputConnection(sphere4->GetOutputPort());
    append_data->AddInputConnection(sphere5->GetOutputPort());

    auto camera = vtkSmartPointer<vtkCamera>(vtkCamera::New());
    auto depth_sort =vtkSmartPointer<vtkDepthSortPolyData>(vtkDepthSortPolyData::New());
    depth_sort->SetInputConnection(append_data->GetOutputPort());
    depth_sort->SetDirectionToBackToFront();
    depth_sort->SetVector(1, 1, 1);
    depth_sort->SetCamera(camera);
    depth_sort->SortScalarsOn();
    depth_sort->Update();

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(depth_sort->GetOutputPort());
    mapper->SetScalarRange(0, depth_sort->GetOutput()->GetNumberOfCells());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);
    actor->GetProperty()->SetOpacity(0.5);
    actor->GetProperty()->SetColor(1, 0, 0);
    actor->RotateX(-72);

    depth_sort->SetProp3D(actor);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    auto render_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_win->AddRenderer(renderer);
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_win);
    render_win->SetSize(512, 512);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(2.2);

    render_win_inter->Initialize();
    render_win_inter->Start();

    return 0;
}