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
    actor->GetProperty()->SetColor(1, 0, 0);
    actor->GetProperty()->SetDiffuse(0.7);
    actor->GetProperty()->SetSpecular(0.4);
    actor->GetProperty()->SetSpecularPower(20);

    auto property = vtkSmartPointer<vtkProperty>(vtkProperty::New());
    property->SetColor(0, 1, 0);
    property->SetDiffuse(0.7);
    property->SetSpecular(0.4);
    property->SetSpecularPower(20);

    auto actor2 = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor2->SetMapper(mapper);
    actor2->GetProperty()->SetColor(0, 0, 1);
    actor2->SetProperty(property);
    actor2->SetPosition(0, 6, 0);
    actor2->RotateZ(90);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->ResetCamera();
    renderer->AddActor(actor);
    renderer->AddActor(actor2);

    auto rend_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    rend_win->AddRenderer(renderer);
    rend_win->SetSize(512, 512);


    for (int i = 0; i < 1000; i++) {
        rend_win->Render();
        renderer->GetActiveCamera()->Azimuth(1);
    }

    return 0;
}