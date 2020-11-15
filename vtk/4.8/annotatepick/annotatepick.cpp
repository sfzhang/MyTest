#include <vtkConeSource.h>
#include <vtkSphereSource.h>
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
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <vtkGlyph3D.h>
#include <vtkTextProperty.h>
#include <vtkCellPicker.h>
#include <vtkLODActor.h>
#include <sstream>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

class MyCallback: public vtkCommand {

public:

    static MyCallback *New()
    {
        return new MyCallback();
    }

    vtkSmartPointer<vtkActor2D> getTextActor() const
    {
        return m_text_actor;
    }

    virtual void Execute(vtkObject *caller, unsigned long, void *)
    {
        auto picker = vtkCellPicker::SafeDownCast(caller);
        std::cout << "pick with ID: " << picker->GetCellId() << std::endl;
        if (picker->GetCellId() < 0) {
            m_text_actor->VisibilityOff();
        }
        else {
            auto pos = picker->GetPickPosition();

            std::stringstream sstrm;
            sstrm << "(" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")";
            m_text_mapper->SetInput(sstrm.str().c_str());
            m_text_actor->SetPosition(picker->GetSelectionPoint());
            m_text_actor->VisibilityOn();
        }
    }

protected:

    MyCallback():
        m_text_mapper(vtkSmartPointer<vtkTextMapper>(vtkTextMapper::New())),
        m_text_actor(vtkSmartPointer<vtkActor2D>(vtkActor2D::New()))
    {
        m_text_mapper->GetTextProperty()->SetFontFamilyToCourier();
        m_text_mapper->GetTextProperty()->SetFontSize(10);
        m_text_mapper->GetTextProperty()->BoldOn();
        m_text_mapper->GetTextProperty()->ShadowOn();
        m_text_mapper->GetTextProperty()->SetColor(0, 1, 0);
        m_text_actor->VisibilityOff();
        m_text_actor->SetMapper(m_text_mapper);
    }

private:

    vtkSmartPointer<vtkTextMapper> m_text_mapper;
    vtkSmartPointer<vtkActor2D> m_text_actor;

};

int main()
{
    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    auto sphere_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    sphere_mapper->SetInputConnection(sphere->GetOutputPort());
    auto sphere_actor = vtkSmartPointer<vtkLODActor>(vtkLODActor::New());
    sphere_actor->SetMapper(sphere_mapper);

    auto cone = vtkSmartPointer<vtkConeSource>(vtkConeSource::New());
    auto glyph = vtkSmartPointer<vtkGlyph3D>(vtkGlyph3D::New());
    glyph->SetInputConnection(sphere->GetOutputPort());
    glyph->SetSourceConnection(cone->GetOutputPort());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);

    auto spike_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    sphere_mapper->SetInputConnection(glyph->GetOutputPort());
    auto spike_actor = vtkSmartPointer<vtkLODActor>(vtkLODActor::New());
    spike_actor->SetMapper(spike_mapper);

    auto callback = vtkSmartPointer<MyCallback>(MyCallback::New());
    auto picker = vtkSmartPointer<vtkCellPicker>(vtkCellPicker::New());
    picker->AddObserver(vtkCommand::EndPickEvent, callback);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor2D(callback->getTextActor());
    renderer->AddActor(sphere_actor);
    renderer->AddActor(spike_actor);

    auto rend_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    rend_win->AddRenderer(renderer);
    rend_win->SetSize(512, 512);

    auto rend_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    rend_win_inter->SetRenderWindow(rend_win);
    rend_win_inter->SetPicker(picker);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.4);

    rend_win_inter->Initialize();
    rend_win_inter->Render();
    picker->Pick(256, 256, 0, renderer);

    rend_win_inter->Start();

    return 0;
}