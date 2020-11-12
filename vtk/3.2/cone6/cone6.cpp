#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>
#include <vtkAutoInit.h>
#include <vtkBoxWidget.h>
#include <vtkTransform.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

class MyCallback: public vtkCommand {

public:

    static MyCallback *New()
    {
        return new MyCallback();
    }

    virtual void Execute(vtkObject *caller, unsigned long, void *)
    {
        auto t = vtkSmartPointer<vtkTransform>(vtkTransform::New());
        auto w = vtkBoxWidget::SafeDownCast(caller);
        w->GetTransform(t);
        w->GetProp3D()->SetUserTransform(t);
    }

};

int main()
{
    auto cone = vtkSmartPointer<vtkConeSource>(vtkConeSource::New());
    cone->SetResolution(500);
    cone->SetRadius(4);
    cone->SetHeight(8);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(cone->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1, 140.0 / 255, 0);
    actor->GetProperty()->SetDiffuse(0.7);
    actor->GetProperty()->SetSpecular(0.4);
    actor->GetProperty()->SetSpecularPower(20);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor(actor);
    renderer->SetBackground(0, 139.0 / 255, 139.0 / 255);

    auto rend_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    rend_win->AddRenderer(renderer);
    rend_win->SetSize(512, 512);

    auto rend_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    rend_win_inter->SetRenderWindow(rend_win);

    auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>(vtkInteractorStyleTrackballCamera::New());
    rend_win_inter->SetInteractorStyle(style);

    auto box_widget = vtkSmartPointer<vtkBoxWidget>(vtkBoxWidget::New());
    box_widget->SetInteractor(rend_win_inter);
    box_widget->SetPlaceFactor(2);

    box_widget->SetProp3D(actor);
    box_widget->PlaceWidget();

    auto callback = vtkSmartPointer<MyCallback>(MyCallback::New());
    box_widget->AddObserver(vtkCommand::InteractionEvent, callback);

    box_widget->On();

    rend_win_inter->Initialize();
    rend_win_inter->Start();

    return 0;
}