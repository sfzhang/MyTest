#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere->SetThetaResolution(100);
    sphere->SetPhiResolution(100);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(sphere->GetOutputPort());

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    auto render_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_win->AddRenderer(renderer);

    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_win);

    for (int i = 0; i < 8; i++) {
        auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(1, 0, 0);
        actor->GetProperty()->SetAmbient(0.3);
        actor->GetProperty()->SetDiffuse(0.0);
        if (i < 4) {
            actor->GetProperty()->SetSpecular(1.0);
            actor->GetProperty()->SetSpecularPower(5 * pow(2, i));
            actor->AddPosition(1.25 * i, 0, 0);
        }
        else {
            actor->GetProperty()->SetSpecular(0.5);
            actor->GetProperty()->SetSpecularPower(5 * pow(2, i - 4));
            actor->AddPosition(1.25 * (i - 4), 1.25, 0);
        }
        renderer->AddActor(actor);
    }

    renderer->SetBackground(0.1, 0.2, 0.4);
    render_win->SetSize(400, 200);

    // Set up light
    auto light = vtkSmartPointer<vtkLight>(vtkLight::New());
    light->SetFocalPoint(1.875, 0.6125, 0);
    light->SetPosition(0.875, 1.6125, 1);
    renderer->AddLight(light);

    renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    renderer->GetActiveCamera()->SetPosition(0, 0, 1);
    renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
    renderer->GetActiveCamera()->ParallelProjectionOn();
    renderer->ResetCamera();
    renderer->GetActiveCamera()->SetParallelScale(1.5);

    render_win_inter->Initialize();
    render_win_inter->Start();

    return 0;
}