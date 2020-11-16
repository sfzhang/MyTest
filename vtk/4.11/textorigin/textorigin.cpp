#include <vtkAxes.h>
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
#include <vtkVectorText.h>
#include <vtkFollower.h>
#include <sstream>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto axes = vtkSmartPointer<vtkAxes>(vtkAxes::New());
    axes->SetOrigin(0, 0, 0);
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(axes->GetOutputPort());
    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    auto vector_text = vtkSmartPointer<vtkVectorText>(vtkVectorText::New());
    vector_text->SetText("Origin");
    auto text_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    text_mapper->SetInputConnection(vector_text->GetOutputPort());
    auto follower = vtkSmartPointer<vtkFollower>(vtkFollower::New());
    follower->GetProperty()->SetColor(1, 0, 0);
    follower->SetMapper(text_mapper);
    follower->SetScale(0.2, 0.2, 0.2);
    follower->AddPosition(0, -0.1, 0);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(0, 0, 1);
    renderer->AddActor(actor);
    renderer->AddActor(follower);

    auto rend_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    rend_win->AddRenderer(renderer);
    rend_win->SetSize(512, 512);

    auto rend_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    rend_win_inter->SetRenderWindow(rend_win);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.4);

    renderer->ResetCameraClippingRange();
    follower->SetCamera(renderer->GetActiveCamera());

    rend_win_inter->Initialize();
    rend_win_inter->Render();
    rend_win_inter->Start();

    return 0;
}