#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkProperty.h>
#include <vtkAutoInit.h>
#include <random>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInterActionStyole);

class MyCallback: public vtkCommand {
public:

    static MyCallback* New()
    {
        return new MyCallback;
    }

    virtual void Execute(vtkObject *caller, unsigned long, void *) override
    {
        auto renderer = vtkRenderer::SafeDownCast(caller);
        std::cout << renderer->GetActiveCamera()->GetPosition()[0] << " "
                  << renderer->GetActiveCamera()->GetPosition()[1] << " "
                  << renderer->GetActiveCamera()->GetPosition()[2] << "\n";
    }
};

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
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(90);
    renderer->SetViewport(0, 0, 0.5, 1);

    auto callback = vtkSmartPointer<MyCallback>(MyCallback::New());
    renderer->AddObserver(vtkCommand::StartEvent, callback);

    auto another_renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    another_renderer->AddActor(actor);
    another_renderer->ResetCamera();
    another_renderer->SetViewport(0.5, 0, 1, 1);

    auto rend_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    rend_win->AddRenderer(renderer);
    rend_win->AddRenderer(another_renderer);
    rend_win->SetSize(512, 512);


    for (int i = 0; i < 1000; i++) {
        rend_win->Render();
        renderer->GetActiveCamera()->Azimuth(1);
        another_renderer->GetActiveCamera()->Azimuth(1);

        if (!(i % 10)) {
            actor->GetProperty()->SetColor(r(e), r(e), r(e));
        }

        if (!(i % 100)) {
            renderer->SetBackground(r(e), r(e), r(e));
            another_renderer->SetBackground(r(e), r(e), r(e));
        }
    }

    return 0;
}