#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkAutoInit.h>
#include <random>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInterActionStyole);

int main()
{
    std::uniform_real_distribution<> r;
    std::default_random_engine e;

    auto cone = vtkSmartPointer<vtkConeSource>(vtkConeSource::New());
    cone->SetResolution(50);
    cone->SetRadius(4);
    cone->SetHeight(8);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(cone->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor(actor);

    auto rend_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    rend_win->AddRenderer(renderer);
    rend_win->SetSize(512, 512);


    for (int i = 0; i < 1000; i++) {
        rend_win->Render();
        renderer->GetActiveCamera()->Azimuth(1);
        if (!(i % 10)) {
            actor->GetProperty()->SetColor(r(e), r(e), r(e));
        }

        if (!(i % 100)) {
            renderer->SetBackground(r(e), r(e), r(e));
        }
    }

    return 0;
}