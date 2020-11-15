#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto cylinder = vtkCylinderSource::New();
    cylinder->SetResolution(100);
    cylinder->SetRadius(2);
    cylinder->SetHeight(6);

    auto cylinder_mapper = vtkPolyDataMapper::New();
    cylinder_mapper->SetInputConnection(cylinder->GetOutputPort());

    auto actor = vtkActor::New();
    actor->SetMapper(cylinder_mapper);
    actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
    actor->RotateX(45);

    auto renderer = vtkRenderer::New();
    renderer->AddActor(actor);
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(0.5);

    auto render_win = vtkRenderWindow::New();
    render_win->AddRenderer(renderer);
    render_win->SetSize(512, 512);

    auto render_win_inter = vtkRenderWindowInteractor::New();
    render_win_inter->SetRenderWindow(render_win);
    render_win_inter->LightFollowCameraOff();

    auto focal_point = renderer->GetActiveCamera()->GetFocalPoint();

    auto light = vtkSmartPointer<vtkLight>(vtkLight::New());
    light->SetColor(1, 0, 0);
    light->SetFocalPoint(focal_point);
    light->PositionalOn();
    light->SetPosition(focal_point[0], focal_point[1], focal_point[2] + 20);
    light->SetConeAngle(6);
    renderer->AddLight(light);

    light = vtkSmartPointer<vtkLight>(vtkLight::New());
    light->SetColor(0, 1, 0);
    light->SetFocalPoint(focal_point);
    light->SetPosition(focal_point[0] + 20, focal_point[1], focal_point[2]);
    renderer->AddLight(light);

    light = vtkSmartPointer<vtkLight>(vtkLight::New());
    light->SetColor(0, 0, 1);
    light->SetFocalPoint(focal_point);
    light->SetPosition(focal_point[0], focal_point[1] + 20, focal_point[2]);
    light->PositionalOn();
    light->SetConeAngle(5);
    renderer->AddLight(light);

    render_win->Render();

    render_win_inter->Initialize();
    render_win_inter->Start();

    return 0;
}