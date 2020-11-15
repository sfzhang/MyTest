#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRendererCollection.h>
#include <vtkActorCollection.h>
#include <vtkProperty.h>
#include <vtkCommand.h>
#include <vtkAutoInit.h>
#include <cstring>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

class MyCommand: public vtkCommand {

public:

    static MyCommand *New()
    {
        return new MyCommand;
    }

    virtual void Execute(vtkObject *caller, unsigned long event_id, void *call_data) override
    {
        auto rend_win_inter = vtkRenderWindowInteractor::SafeDownCast(caller);

        switch (event_id) {
        case vtkCommand::LeftButtonPressEvent:
            onMouseLeftButtonPressed();
            break;
        case vtkCommand::LeftButtonReleaseEvent:
            onMouseLeftButtonReleased();
            break;
        case vtkCommand::MiddleButtonPressEvent:
            onMouseMiddleButtonPressed();
            break;
        case vtkCommand::MiddleButtonReleaseEvent:
            onMouseMiddleButtonReleased();
            break;
        case vtkCommand::RightButtonPressEvent:
            onMouseRightButtonPressed();
            break;
        case vtkCommand::RightButtonReleaseEvent:
            onMouseRightButtonReleased();
            break;
        case vtkCommand::MouseMoveEvent:
            onMouseMoved(rend_win_inter);
            break;
        case vtkCommand::KeyPressEvent:
            onKeyPressed(rend_win_inter);
            break;
        default:
            break;
        }
    }

protected:

    MyCommand():
        m_rotating(false),
        m_panning(false),
        m_zoomimg(false)
    {
    }

private:

    void onMouseLeftButtonPressed()
    {
        m_rotating = true;
    }

    void onMouseLeftButtonReleased()
    {
        m_rotating = false;
    }

    void onMouseMiddleButtonPressed()
    {
        m_panning = true;
    }

    void onMouseMiddleButtonReleased()
    {
        m_panning = false;
    }

    void onMouseRightButtonPressed()
    {
        m_zoomimg = true;
    }

    void onMouseRightButtonReleased()
    {
        m_zoomimg = false;
    }

    void onMouseMoved(vtkRenderWindowInteractor *rend_win_inter)
    {
        auto last_xypos = rend_win_inter->GetLastEventPosition();
        auto xypos = rend_win_inter->GetEventPosition();

        auto size = rend_win_inter->GetRenderWindow()->GetSize();

        auto renderers = rend_win_inter->GetRenderWindow()->GetRenderers();
        renderers->InitTraversal();
        auto render = renderers->GetNextItem();
        while (render) {
            if (m_rotating) {
                rotate(render, xypos[0], xypos[1], last_xypos[0], last_xypos[1],
                       size[0] / 2.0, size[1] / 2.0);
            }
            else if (m_panning) {
                pan(render, xypos[0], xypos[1], last_xypos[0], last_xypos[1],
                    size[0] / 2.0, size[1] / 2.0);
            }
            else if (m_zoomimg) {
                dolly(render, xypos[0], xypos[1], last_xypos[0], last_xypos[1],
                      size[0] / 2.0, size[1] / 2.0);
            }

            render = renderers->GetNextItem();
        }
    }

    void rotate(vtkRenderer *renderer, double x, double y, double last_x, double last_y,
                double center_x, double center_y)
    {
        auto camera = renderer->GetActiveCamera();
        camera->Azimuth(last_x - x);
        camera->Elevation(last_y - y);
        camera->OrthogonalizeViewUp();
        renderer->GetRenderWindow()->Render();
    }

    void pan(vtkRenderer *renderer, double x, double y, double last_x, double last_y,
             double center_x, double center_y)
    {
        auto camera = renderer->GetActiveCamera();
        auto focal_point = camera->GetFocalPoint();
        auto position = camera->GetPosition();

        renderer->SetWorldPoint(focal_point[0], focal_point[1], focal_point[2], 1.0);
        renderer->WorldToDisplay();
        auto display_point = renderer->GetDisplayPoint();
        auto focal_depth = display_point[2];

        auto apoint_x = center_x + (x - last_x);
        auto apoint_y = center_y + (y - last_y);

        renderer->SetDisplayPoint(apoint_x, apoint_y, focal_depth);
        renderer->DisplayToWorld();

        auto world_point = renderer->GetWorldPoint();

        if (world_point[3] != 0) {
            world_point[0] /= world_point[3];
            world_point[1] /= world_point[3];
            world_point[2] /= world_point[3];
        }

        camera->SetFocalPoint((focal_point[0] - world_point[0]) / 2.0 + focal_point[0],
                              (focal_point[1] - world_point[1]) / 2.0 + focal_point[1],
                              (focal_point[2] - world_point[2]) / 2.0 + focal_point[2]);
        
        camera->SetPosition((focal_point[0] - world_point[0]) / 2.0 + position[0],
                            (focal_point[1] - world_point[1]) / 2.0 + position[1],
                            (focal_point[2] - world_point[2]) / 2.0 + position[2]);

        renderer->GetRenderWindow()->Render();
    }

    void dolly(vtkRenderer *renderer, double x, double y, double last_x, double last_y,
               double center_x, double center_y)
    {
        auto camera = renderer->GetActiveCamera();
        auto dolly_factor = pow(1.02, (0.5 * (y - last_y)));

        if (camera->GetParallelProjection()) {
            auto paralle_scale = camera->GetParallelScale() * dolly_factor;
            camera->SetParallelScale(paralle_scale);
        }
        else {
            camera->Dolly(dolly_factor);
            renderer->ResetCameraClippingRange();
        }
        renderer->GetRenderWindow()->Render();
    }


    void onKeyPressed(vtkRenderWindowInteractor *rend_win_inter)
    {
        auto key = rend_win_inter->GetKeySym();
        if (strcmp(key, "e") == 0) {
            cout << "Key Pressed: " << key << endl;
            rend_win_inter->GetRenderWindow()->Finalize();
            rend_win_inter->TerminateApp();
        }
        else if (strcmp(key, "w") == 0) {
            toWireframe(rend_win_inter);
        }
        else if (strcmp(key, "s") == 0) {
            toSurface(rend_win_inter);
        }
    }

    void changeRepresentation(vtkRenderWindowInteractor *rend_win_inter, bool surface)
    {
        auto renderers = rend_win_inter->GetRenderWindow()->GetRenderers();
        renderers->InitTraversal();
        auto render = renderers->GetNextItem();
        while (render) {
            auto actors = render->GetActors();
            actors->InitTraversal();
            auto actor = actors->GetNextActor();
            while (actor) {
                if (surface) {
                    actor->GetProperty()->SetRepresentationToSurface();
                }
                else {
                    actor->GetProperty()->SetRepresentationToWireframe();
                }
                actor = actors->GetNextActor();
            }

            render = renderers->GetNextItem();
        }
        rend_win_inter->Render();
    }

    void toWireframe(vtkRenderWindowInteractor *rend_win_inter)
    {
        changeRepresentation(rend_win_inter, false);
    }

    void toSurface(vtkRenderWindowInteractor *rend_win_inter)
    {
        changeRepresentation(rend_win_inter, true);
    }

private:

    bool m_rotating;
    bool m_panning;
    bool m_zoomimg;

};

int main()
{
    auto cone = vtkSmartPointer<vtkConeSource>(vtkConeSource::New());
    cone->SetHeight(3);
    cone->SetRadius(1);
    cone->SetResolution(10);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(cone->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    auto rend_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    rend_win->AddRenderer(renderer);
    rend_win->SetSize(300, 300);

    auto rend_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    rend_win_inter->SetRenderWindow(rend_win);
    rend_win_inter->SetInteractorStyle(nullptr);

    auto command = vtkSmartPointer<MyCommand>(MyCommand::New());

    rend_win_inter->AddObserver(vtkCommand::LeftButtonPressEvent, command);
    rend_win_inter->AddObserver(vtkCommand::LeftButtonReleaseEvent, command);
    rend_win_inter->AddObserver(vtkCommand::MiddleButtonPressEvent, command);
    rend_win_inter->AddObserver(vtkCommand::MiddleButtonReleaseEvent, command);
    rend_win_inter->AddObserver(vtkCommand::RightButtonPressEvent, command);
    rend_win_inter->AddObserver(vtkCommand::RightButtonReleaseEvent, command);
    rend_win_inter->AddObserver(vtkCommand::MouseMoveEvent, command);
    rend_win_inter->AddObserver(vtkCommand::KeyPressEvent, command);

    rend_win_inter->Initialize();
    rend_win_inter->Start();

    return 0;
}