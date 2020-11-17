#include <vtkActor.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkCellData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkPoints.h>
#include <vtkAutoInit.h>
#include <vtkCubeSource.h>
#include <vtkGlyph3D.h>
#include <vtkConeSource.h>
#include <vtkAppendPolyData.h>
#include <vtkLODActor.h>
#include <vtkPlane.h>
#include <vtkImplicitPlaneWidget.h>
#include <vtkCommand.h>
#include <vtkClipPolyData.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);


class MyCommand: public vtkCommand {
public:

    static MyCommand *New()
    {
        return new MyCommand();
    }

    void init(vtkSmartPointer<vtkAppendPolyData> append)
    {
        auto clipper = vtkSmartPointer<vtkClipPolyData>(vtkClipPolyData::New());
        clipper->SetInputConnection(append->GetOutputPort());
        clipper->SetClipFunction(m_plane);
        clipper->InsideOutOn();

        auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
        mapper->SetInputConnection(clipper->GetOutputPort());

        m_actor->SetMapper(mapper);
        m_actor->GetProperty()->SetColor(0, 1, 0);
        m_actor->VisibilityOff();
        m_actor->SetScale(1.1, 1.1, 1.1);
    }

    vtkSmartPointer<vtkPlane> getPlane() const
    {
        return m_plane;
    }

    vtkSmartPointer<vtkLODActor> getActor() const
    {
        return m_actor;
    }

    virtual void Execute(vtkObject *object, unsigned long, void *) override
    {
        auto plane_widget = vtkImplicitPlaneWidget::SafeDownCast(object);
        plane_widget->GetPlane(m_plane);
        m_actor->VisibilityOn();
    }

protected:

    MyCommand():
        m_plane(vtkPlane::New()),
        m_actor(vtkLODActor::New())
    {

    }

protected:

    vtkSmartPointer<vtkPlane> m_plane;
    vtkSmartPointer<vtkLODActor> m_actor;

};

using namespace std;

int main()
{
    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    auto cone = vtkSmartPointer<vtkConeSource>(vtkConeSource::New());
    auto glyph = vtkSmartPointer<vtkGlyph3D>(vtkGlyph3D::New());

    glyph->SetInputConnection(sphere->GetOutputPort());
    glyph->SetSourceConnection(cone->GetOutputPort());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);

    auto append = vtkSmartPointer<vtkAppendPolyData>(vtkAppendPolyData::New());
    append->AddInputConnection(glyph->GetOutputPort());
    append->AddInputConnection(sphere->GetOutputPort());

    auto mace_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mace_mapper->SetInputConnection(append->GetOutputPort());

    auto mace_actor = vtkSmartPointer<vtkLODActor>(vtkLODActor::New());
    mace_actor->SetMapper(mace_mapper);
    mace_actor->VisibilityOn();

    // Create a renderer
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(0, 0, 0);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);
    render_window->SetSize(500, 500);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    auto plane_widget = vtkSmartPointer<vtkImplicitPlaneWidget>(vtkImplicitPlaneWidget::New());
    plane_widget->SetInteractor(render_win_inter);
    plane_widget->SetPlaceFactor(1.25);
    plane_widget->SetInputConnection(glyph->GetOutputPort());
    plane_widget->PlaceWidget();

    auto cmd = vtkSmartPointer<MyCommand>(MyCommand::New());
    cmd->init(append);
    plane_widget->AddObserver(vtkCommand::InteractionEvent, cmd);

    renderer->AddActor(mace_actor);
    renderer->AddActor(cmd->getActor());

    render_win_inter->Initialize();
    render_window->Render();
    render_win_inter->Start();

    return 0;
}