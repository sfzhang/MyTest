#include <vtkAutoInit.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkTextProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkQuadric.h>
#include <vtkExtractVOI.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto quadric = vtkSmartPointer<vtkQuadric>(vtkQuadric::New());
    quadric->SetCoefficients(0.5, 1, 0.2, 0, 0.1, 0, 0, 0.2, 0, 0);

    auto sample = vtkSmartPointer<vtkSampleFunction>(vtkSampleFunction::New());
    sample->SetSampleDimensions(30, 30, 30);
    sample->SetImplicitFunction(quadric);
    sample->ComputeNormalsOff();
    sample->Update();

    auto sample_mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    sample_mapper->SetInputConnection(sample->GetOutputPort());
    auto sample_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    sample_actor->SetMapper(sample_mapper);

    auto extract = vtkSmartPointer<vtkExtractVOI>(vtkExtractVOI::New());
    extract->SetInputConnection(sample->GetOutputPort());
    extract->SetVOI(0, 29, 0, 29, 5, 5);
    extract->SetSampleRate(1, 1, 1);

    auto contours = vtkSmartPointer<vtkContourFilter>(vtkContourFilter::New());
    contours->SetInputConnection(extract->GetOutputPort());
    contours->GenerateValues(13, 0, 1.2);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(contours->GetOutputPort());
    mapper->SetScalarRange(0, 1.2);

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(0.1, 0.2, 0.4);
    renderer->TwoSidedLightingOff();

    sample_actor->AddPosition(3, 3, 0);
    renderer->AddActor(sample_actor);
    renderer->AddActor(actor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.5);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    render_window->Render();
    render_win_inter->Start();

    return 0;
}