#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkTexture.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto bmp_reader = vtkSmartPointer<vtkBMPReader>(vtkBMPReader::New());
    bmp_reader->SetFileName("../../data/masonry.bmp");

    auto texture = vtkSmartPointer<vtkTexture>(vtkTexture::New());
    texture->SetInputConnection(bmp_reader->GetOutputPort());
    texture->InterpolateOn();

    auto plane = vtkSmartPointer<vtkPlaneSource>(vtkPlaneSource::New());
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(plane->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);
    actor->SetTexture(texture);

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