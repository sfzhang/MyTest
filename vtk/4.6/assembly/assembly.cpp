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
#include <vtkAssembly.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    auto sphere_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    sphere_mapper->SetInputConnection(sphere->GetOutputPort());

    auto sphere_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    sphere_actor->SetMapper(sphere_mapper);
    sphere_actor->SetOrigin(2, 1, 3);
    sphere_actor->RotateY(6);
    sphere_actor->SetPosition(2.25, 0, 0);
    sphere_actor->GetProperty()->SetColor(1, 0, 1);

    auto cube = vtkSmartPointer<vtkCubeSource>(vtkCubeSource::New());
    auto cube_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    cube_mapper->SetInputConnection(cube->GetOutputPort());

    auto cube_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    cube_actor->SetMapper(cube_mapper);
    cube_actor->SetPosition(0, 0.25, 0);
    cube_actor->GetProperty()->SetColor(0, 0, 1);

    auto cone = vtkSmartPointer<vtkConeSource>(vtkConeSource::New());
    auto cone_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    cone_mapper->SetInputConnection(cone->GetOutputPort());

    auto cone_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    cone_actor->SetMapper(cone_mapper);
    cone_actor->SetPosition(0, 0, 0.25);
    cone_actor->GetProperty()->SetColor(0, 1, 0);

    auto cylinder = vtkSmartPointer<vtkCylinderSource>(vtkCylinderSource::New());
    auto cylinder_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    cylinder_mapper->SetInputConnection(cylinder->GetOutputPort());

    auto cylinder_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    cylinder_actor->SetMapper(cylinder_mapper);
    cylinder_actor->GetProperty()->SetColor(1, 0, 0);

    auto assembly = vtkSmartPointer<vtkAssembly>(vtkAssembly::New());
    assembly->AddPart(cylinder_actor);
    assembly->AddPart(sphere_actor);
    assembly->AddPart(cube_actor);
    assembly->AddPart(cone_actor);
    assembly->SetOrigin(5, 10, 15);
    assembly->AddPosition(5, 0, 0);
    assembly->RotateX(15);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor(assembly);
    renderer->AddActor(cone_actor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    auto render_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_win->AddRenderer(renderer);
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_win);
    render_win->SetSize(512, 512);

    auto camera = vtkSmartPointer<vtkCamera>(vtkCamera::New());
    camera->SetClippingRange(21.9464, 30.0179);
    camera->SetFocalPoint(3.49221, 2.28844, -0.970866);
    camera->SetPosition(3.4922, 2.28844, 24.5216);
    camera->SetViewAngle(30);
    camera->SetViewUp(0, 1, 0);
    renderer->SetActiveCamera(camera);

    render_win_inter->Initialize();
    render_win_inter->Start();

    return 0;
}