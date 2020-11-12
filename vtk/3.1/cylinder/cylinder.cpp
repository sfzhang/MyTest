#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

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
    auto render_win = vtkRenderWindow::New();
    render_win->AddRenderer(renderer);
    auto render_win_inter = vtkRenderWindowInteractor::New();
    render_win_inter->SetRenderWindow(render_win);

    renderer->AddActor(actor);
    renderer->SetBackground(0, 0, 1);
    render_win->SetSize(512, 512);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(0.5);
    render_win->Render();

    render_win_inter->Initialize();
    render_win_inter->Start();

    cylinder->Delete();
    cylinder_mapper->Delete();
    actor->Delete();
    renderer->Delete();
    render_win->Delete();
    render_win_inter->Delete();

    return 0;
}