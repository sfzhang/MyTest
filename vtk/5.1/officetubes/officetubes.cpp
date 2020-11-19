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
#include <vtkPolyDataReader.h>
#include <vtkPolyDataNormals.h>
#include <vtkStructuredGridReader.h>
#include <vtkStructuredGrid.h>
#include <vtkRungeKutta4.h>
#include <vtkStreamTracer.h>
#include <vtkTubeFilter.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkPointSource.h>
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto reader = vtkSmartPointer<vtkStructuredGridReader>(vtkStructuredGridReader::New());
    reader->SetFileName("../../data/office.binary.vtk");
    reader->Update();

    auto length = reader->GetOutput()->GetLength();

    auto max_velocity = reader->GetOutput()->GetPointData()->GetVectors()->GetMaxNorm();
    auto max_time = 35 * length / max_velocity;

    auto seeds = vtkSmartPointer<vtkPointSource>(vtkPointSource::New());
    seeds->SetRadius(0.15);
    seeds->SetCenter(0.1, 2.1, 0.5);
    seeds->SetNumberOfPoints(6);

    auto integ = vtkSmartPointer<vtkRungeKutta4>(vtkRungeKutta4::New());
    auto streamer = vtkSmartPointer<vtkStreamTracer>(vtkStreamTracer::New());
    streamer->SetInputConnection(reader->GetOutputPort());
    streamer->SetSourceConnection(seeds->GetOutputPort());
    streamer->SetMaximumPropagation(500);
    streamer->SetInitialIntegrationStep(0.05);
    streamer->SetIntegrationDirectionToBoth();
    streamer->SetIntegrator(integ);

    auto tube = vtkSmartPointer<vtkTubeFilter>(vtkTubeFilter::New());
    tube->SetInputConnection(streamer->GetOutputPort());
    tube->SetInputArrayToProcess(1, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "vectors");
    tube->SetRadius(0.02);
    tube->SetNumberOfSides(12);
    tube->SetVaryRadiusToVaryRadiusByVector();

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(tube->GetOutputPort());
    mapper->SetScalarRange(reader->GetOutput()->GetPointData()->GetScalars()->GetRange());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);
    actor->GetProperty()->BackfaceCullingOn();

    // tables and so on
    auto table1 = vtkSmartPointer<vtkStructuredGridGeometryFilter>(vtkStructuredGridGeometryFilter::New());
    table1->SetInputConnection(reader->GetOutputPort());
    table1->SetExtent(11, 15, 7, 9, 8, 8);
    auto table_map1 = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    table_map1->SetInputConnection(table1->GetOutputPort());
    table_map1->ScalarVisibilityOff();
    auto table_actor1 = vtkSmartPointer<vtkActor>(vtkActor::New());
    table_actor1->SetMapper(table_map1);
    table_actor1->GetProperty()->SetColor(0.59, 0.427, 0.392);

    auto table2 = vtkSmartPointer<vtkStructuredGridGeometryFilter>(vtkStructuredGridGeometryFilter::New());
    table2->SetInputConnection(reader->GetOutputPort());
    table2->SetExtent(11, 15, 10, 12, 8, 8);
    auto table_map2 = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    table_map2->SetInputConnection(table2->GetOutputPort());
    table_map2->ScalarVisibilityOff();
    auto table_actor2 = vtkSmartPointer<vtkActor>(vtkActor::New());
    table_actor2->SetMapper(table_map2);
    table_actor2->GetProperty()->SetColor(0.59, 0.427, 0.392);

    auto outline = vtkSmartPointer<vtkStructuredGridOutlineFilter>(vtkStructuredGridOutlineFilter::New());
    outline->SetInputConnection(reader->GetOutputPort());
    auto outline_map = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    outline_map->SetInputConnection(outline->GetOutputPort());
    auto outline_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    outline_actor->SetMapper(outline_map);
    outline_actor->GetProperty()->SetColor(0, 1, 0);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(1, 1, 1);

    renderer->AddActor(actor);
    renderer->AddActor(table_actor1);
    renderer->AddActor(table_actor2);
    renderer->AddActor(outline_actor);

    auto camera = vtkSmartPointer<vtkCamera>(vtkCamera::New());
    camera->SetClippingRange(0.726079, 36.3039);
    camera->SetFocalPoint(2.43584, 2.15046, 1.11104);
    camera->SetPosition(-4.76183, -10.4426, 3.17203);
    camera->SetViewUp(0.0511273, 0.132773, 0.989827);
    camera->SetViewAngle(18.604);
    camera->Zoom(1.2);

    renderer->SetActiveCamera(camera);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);
    render_window->SetSize(500, 500);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    render_win_inter->Initialize();
    render_window->Render();
    render_win_inter->Start();

    return 0;
}