#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkAutoInit.h>
#include <vtkBoxWidget.h>
#include <vtkTransform.h>
#include <vtkTextMapper.h>
#include <vtkGlyph3D.h>
#include <vtkTextProperty.h>
#include <vtkCellPicker.h>
#include <vtkLODActor.h>
#include <vtkTextActor.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkCoordinate.h>
#include <sstream>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    // single line text property
    auto slt_prop = vtkSmartPointer<vtkTextProperty>(vtkTextProperty::New());
    slt_prop->SetFontSize(14);
    slt_prop->SetFontFamilyToArial();
    slt_prop->BoldOff();
    slt_prop->ItalicOff();
    slt_prop->ShadowOff();

    // multi line text property
    auto mlt_prop = vtkSmartPointer<vtkTextProperty>(vtkTextProperty::New());
    mlt_prop->ShallowCopy(slt_prop);
    mlt_prop->BoldOn();
    mlt_prop->ItalicOn();
    mlt_prop->ShadowOn();
    mlt_prop->SetLineSpacing(0.8);

    // single line text align to bottom
    auto slt_mapper = vtkSmartPointer<vtkTextMapper>(vtkTextMapper::New());
    slt_mapper->SetInput("Single line (bottom)");
    auto text_prop = slt_mapper->GetTextProperty();
    text_prop->ShallowCopy(slt_prop);
    text_prop->SetVerticalJustificationToBottom();
    text_prop->SetColor(1, 0, 0);

    auto slt_actor1 = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    slt_actor1->SetMapper(slt_mapper);
    slt_actor1->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    slt_actor1->GetPositionCoordinate()->SetValue(0.05, 0.85);

    // single line text align to center 
    slt_mapper = vtkSmartPointer<vtkTextMapper>(vtkTextMapper::New());
    slt_mapper->SetInput("Single line (centered)");
    text_prop = slt_mapper->GetTextProperty();
    text_prop->ShallowCopy(slt_prop);
    text_prop->SetVerticalJustificationToCentered();
    text_prop->SetColor(0, 1, 0);

    auto slt_actor2 = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    slt_actor2->SetMapper(slt_mapper);
    slt_actor2->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    slt_actor2->GetPositionCoordinate()->SetValue(0.05, 0.65);

    // single line text align to top
    slt_mapper = vtkSmartPointer<vtkTextMapper>(vtkTextMapper::New());
    slt_mapper->SetInput("Single line (top)");
    text_prop = slt_mapper->GetTextProperty();
    text_prop->ShallowCopy(slt_prop);
    text_prop->SetVerticalJustificationToTop();
    text_prop->SetColor(0, 0, 1);

    auto slt_actor3 = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    slt_actor3->SetMapper(slt_mapper);
    slt_actor3->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    slt_actor3->GetPositionCoordinate()->SetValue(0.05, 0.75);

    // multi line text align to top-left
    auto mlt_mapper = vtkSmartPointer<vtkTextMapper>(vtkTextMapper::New());
    mlt_mapper->SetInput("This is \nmulti-line\ntext output\n(top-left)");
    text_prop = mlt_mapper->GetTextProperty();
    text_prop->ShallowCopy(mlt_prop);
    text_prop->SetJustificationToLeft();
    text_prop->SetVerticalJustificationToTop();
    text_prop->SetColor(1, 0, 0);

    auto mlt_actor1 = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    mlt_actor1->SetMapper(mlt_mapper);
    mlt_actor1->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    mlt_actor1->GetPositionCoordinate()->SetValue(0.05, 0.5);

    // multi line text align to center
    mlt_mapper = vtkSmartPointer<vtkTextMapper>(vtkTextMapper::New());
    mlt_mapper->SetInput("This is \nmulti-line\ntext output\n(center)");
    text_prop = mlt_mapper->GetTextProperty();
    text_prop->ShallowCopy(mlt_prop);
    text_prop->SetJustificationToCentered();
    text_prop->SetVerticalJustificationToCentered();
    text_prop->SetColor(0, 1, 0);

    auto mlt_actor2 = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    mlt_actor2->SetMapper(mlt_mapper);
    mlt_actor2->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    mlt_actor2->GetPositionCoordinate()->SetValue(0.5, 0.5);

    // multi line text align to bottom-right
    mlt_mapper = vtkSmartPointer<vtkTextMapper>(vtkTextMapper::New());
    mlt_mapper->SetInput("This is \nmulti-line\ntext output\n(bottom-right)");
    text_prop = mlt_mapper->GetTextProperty();
    text_prop->ShallowCopy(mlt_prop);
    text_prop->SetJustificationToRight();
    text_prop->SetVerticalJustificationToBottom();
    text_prop->SetColor(0, 0, 1);

    auto mlt_actor3 = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    mlt_actor3->SetMapper(mlt_mapper);
    mlt_actor3->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    mlt_actor3->GetPositionCoordinate()->SetValue(0.95, 0.5);

    // Draw grid
    auto points = vtkSmartPointer<vtkPoints>(vtkPoints::New());
    points->InsertNextPoint(0.05, 0.0, 0.0);
    points->InsertNextPoint(0.05, 1.0, 0.0);
    points->InsertNextPoint(0.5, 0.0, 0.0);
    points->InsertNextPoint(0.5, 1.0, 0.0);
    points->InsertNextPoint(0.95, 0.0, 0.0);
    points->InsertNextPoint(0.95, 1.0, 0.0);
    points->InsertNextPoint(0.0, 0.5, 0.0);
    points->InsertNextPoint(1.0, 0.5, 0.0);
    points->InsertNextPoint(0.0, 0.85, 0.0);
    points->InsertNextPoint(0.5, 0.85, 0.0);
    points->InsertNextPoint(0.0, 0.75, 0.0);
    points->InsertNextPoint(0.5, 0.75, 0.0);
    points->InsertNextPoint(0.0, 0.65, 0.0);
    points->InsertNextPoint(0.5, 0.65, 0.0);

    auto lines = vtkSmartPointer<vtkCellArray>(vtkCellArray::New());
    for (int i = 0; i < 14; ) {
        lines->InsertNextCell(2);
        lines->InsertCellPoint(i++);
        lines->InsertCellPoint(i++);
    }

    auto grid = vtkSmartPointer<vtkPolyData>(vtkPolyData::New());
    grid->SetPoints(points);
    grid->SetLines(lines);

    auto coord = vtkSmartPointer<vtkCoordinate>(vtkCoordinate::New());
    coord->SetCoordinateSystemToNormalizedViewport();

    auto mapper = vtkSmartPointer<vtkPolyDataMapper2D>(vtkPolyDataMapper2D::New());
    mapper->SetInputData(grid);
    mapper->SetTransformCoordinate(coord);

    auto grid_actor = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    grid_actor->SetMapper(mapper);
    grid_actor->GetProperty()->SetColor(0.1, 0.1, 0.1);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(1, 1, 1);
    renderer->AddActor2D(slt_actor1);
    renderer->AddActor2D(slt_actor2);
    renderer->AddActor2D(slt_actor3);
    renderer->AddActor2D(mlt_actor1);
    renderer->AddActor2D(mlt_actor2);
    renderer->AddActor2D(mlt_actor3);
    renderer->AddActor2D(grid_actor);

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