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
#include <vtkTransform.h>
#include <vtkSphere.h>
#include <vtkImplicitBoolean.h>
#include <vtkExtractGeometry.h>
#include <vtkShrinkFilter.h>
#include <vtkDataSetMapper.h>
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
    sample->SetSampleDimensions(50, 50, 50);
    sample->SetImplicitFunction(quadric);
    sample->ComputeNormalsOff();

    auto t = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    t->Scale(1, 0.5, 0.333);

    auto s = vtkSmartPointer<vtkSphere>(vtkSphere::New());
    s->SetRadius(0.25);
    s->SetTransform(t);

    auto t2 = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    t2->Scale(0.25, 0.5, 1.0);
    auto s2 = vtkSmartPointer<vtkSphere>(vtkSphere::New());
    s2->SetRadius(0.25);
    s2->SetTransform(t2);

    auto u = vtkSmartPointer<vtkImplicitBoolean>(vtkImplicitBoolean::New());
    u->AddFunction(s);
    u->AddFunction(s2);
    u->SetOperationType(0); // union

    auto extract = vtkSmartPointer<vtkExtractGeometry>(vtkExtractGeometry::New());
    extract->SetInputConnection(sample->GetOutputPort());
    extract->SetImplicitFunction(u);

    auto shrink = vtkSmartPointer<vtkShrinkFilter>(vtkShrinkFilter::New());
    shrink->SetInputConnection(extract->GetOutputPort());
    shrink->SetShrinkFactor(0.5);

    auto ds_mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    ds_mapper->SetInputConnection(shrink->GetOutputPort());
    auto d_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    d_actor->SetMapper(ds_mapper);

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

    renderer->AddActor(d_actor);
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