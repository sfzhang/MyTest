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
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkDataSet.h>
#include <vtkLineSource.h>
#include <vtkRungeKutta4.h>
#include <vtkRungeKutta4.h>
#include <vtkStreamTracer.h>
#include <vtkRuledSurfaceFilter.h>
#include <vtkCamera.h>
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    // Create a PLOT3D reader and load the data
    auto pl3d = vtkSmartPointer<vtkMultiBlockPLOT3DReader>(vtkMultiBlockPLOT3DReader::New());
    pl3d->SetXYZFileName("../../data/combxyz.bin");
    pl3d->SetQFileName("../../data/combq.bin");
    pl3d->SetScalarFunctionNumber(100); // density
    pl3d->SetVectorFunctionNumber(202); // momentum
    pl3d->Update();

    auto pl3d_output = pl3d->GetOutput()->GetBlock(0);
    auto ds = vtkDataSet::SafeDownCast(pl3d_output);

    auto rake = vtkSmartPointer<vtkLineSource>(vtkLineSource::New());
    rake->SetPoint1(15, -5, 32);
    rake->SetPoint2(15, 5, 32);
    rake->SetResolution(21);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(rake->GetOutputPort());
    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    auto integ = vtkSmartPointer<vtkRungeKutta4>(vtkRungeKutta4::New());
    auto streamer = vtkSmartPointer<vtkStreamTracer>(vtkStreamTracer::New());
    streamer->SetInputData(pl3d_output);
    streamer->SetSourceConnection(rake->GetOutputPort());
    streamer->SetMaximumPropagation(100);
    streamer->SetInitialIntegrationStep(0.1);
    streamer->SetIntegrationDirectionToBackward();
    streamer->SetIntegrator(integ);

    auto surface = vtkSmartPointer<vtkRuledSurfaceFilter>(vtkRuledSurfaceFilter::New());
    surface->SetInputConnection(streamer->GetOutputPort());
    surface->SetOffset(0);
    surface->SetOnRatio(2);
    surface->PassLinesOn();
    surface->SetRuledModeToPointWalk();
    surface->SetDistanceFactor(30);

    auto surface_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    surface_mapper->SetInputConnection(surface->GetOutputPort());
    surface_mapper->SetScalarRange(ds->GetScalarRange());
    auto surface_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    surface_actor->SetMapper(surface_mapper);

    auto outline = vtkSmartPointer<vtkStructuredGridOutlineFilter>(vtkStructuredGridOutlineFilter::New());
    outline->SetInputData(pl3d_output);
    auto outline_map = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    outline_map->SetInputConnection(outline->GetOutputPort());
    auto outline_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    outline_actor->SetMapper(outline_map);
    outline_actor->GetProperty()->SetColor(0, 1, 0);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(0.1, 0.2, 0.4);
    renderer->TwoSidedLightingOff();

    renderer->AddActor(actor);
    renderer->AddActor(surface_actor);
    renderer->AddActor(outline_actor);

    renderer->GetActiveCamera()->SetClippingRange(3.95297, 50);
    renderer->GetActiveCamera()->SetFocalPoint(8.88908, 0.595038, 29.3342);
    renderer->GetActiveCamera()->SetPosition(-12.3332, 31.749, 41.2387);
    renderer->GetActiveCamera()->SetViewUp(0.060772, -0.319905, 0.945498);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    render_window->Render();
    render_win_inter->Start();

    return 0;
}