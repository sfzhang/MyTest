#include <vtkActor.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkTextProperty.h>
#include <vtkCamera.h>
#include <vtkQuadric.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkAutoInit.h>
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

    auto contours = vtkSmartPointer<vtkContourFilter>(vtkContourFilter::New());
    contours->SetInputConnection(sample->GetOutputPort());
    //contours->SetValue(0, 0.6);
    contours->GenerateValues(5, 0, 1.2);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(contours->GetOutputPort());
    mapper->SetScalarRange(0, 1.2);

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    auto outline = vtkSmartPointer<vtkOutlineFilter>(vtkOutlineFilter::New());
    outline->SetInputConnection(sample->GetOutputPort());

    auto outline_sample = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    outline_sample->SetInputConnection(outline->GetOutputPort());

    auto outline_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    outline_actor->SetMapper(outline_sample);
    outline_actor->GetProperty()->SetColor(0, 0, 1);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(1, 1, 1);

    renderer->AddActor(actor);
    renderer->AddActor(outline_actor);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    render_win_inter->Initialize();
    render_window->Render();
    render_win_inter->Start();

    return 0;
}