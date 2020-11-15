#include <vtkShrinkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSTLReader.h>
#include <vtkLODActor.h>
#include <vtkSmartPointer.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto stl_reader = vtkSmartPointer<vtkSTLReader>(vtkSTLReader::New());
    stl_reader->SetFileName("../../data/42400-IDGH.stl");

    auto shrink = vtkSmartPointer<vtkShrinkPolyData>(vtkShrinkPolyData::New());
    shrink->SetInputConnection(stl_reader->GetOutputPort());
    shrink->SetShrinkFactor(0.9);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(shrink->GetOutputPort());

    auto actor = vtkSmartPointer<vtkLODActor>(vtkLODActor::New());
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
    actor->RotateX(45);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor(actor);
    renderer->SetBackground(0, 0, 1);

    auto render_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_win->AddRenderer(renderer);
    render_win->SetSize(512, 512);

    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_win);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(0.5);
    render_win->Render();

    render_win_inter->Initialize();
    render_win_inter->Start();

    return 0;
}