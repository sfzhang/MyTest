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
#include <vtkTextActor.h>
#include <sstream>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    auto sphere_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    sphere_mapper->SetInputConnection(sphere->GetOutputPort());
    auto sphere_actor = vtkSmartPointer<vtkLODActor>(vtkLODActor::New());
    sphere_actor->SetMapper(sphere_mapper);

    auto text_actor = vtkSmartPointer<vtkTextActor>(vtkTextActor::New());
    text_actor->SetTextScaleModeToProp();
    text_actor->SetDisplayPosition(90, 50);
    text_actor->SetInput("This is a sphere");

    text_actor->GetPosition2Coordinate()->SetCoordinateSystemToNormalizedViewport();
    text_actor->GetPosition2Coordinate()->SetValue(0.6, 0.1);

    auto text_property = text_actor->GetTextProperty();
    text_property->SetFontSize(28);
    text_property->SetFontFamilyToTimes();
    text_property->SetJustificationToCentered();
    text_property->BoldOn();
    text_property->ItalicOn();
    text_property->ShadowOn();
    text_property->SetColor(0, 0, 1);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor2D(text_actor);
    renderer->AddActor(sphere_actor);

    auto rend_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    rend_win->AddRenderer(renderer);
    rend_win->SetSize(512, 512);

    auto rend_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    rend_win_inter->SetRenderWindow(rend_win);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.4);

    rend_win_inter->Initialize();
    rend_win_inter->Render();
    rend_win_inter->Start();

    return 0;
}