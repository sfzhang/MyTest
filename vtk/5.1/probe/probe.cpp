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
#include <vtkCamera.h>
#include <vtkPlane.h>
#include <vtkProbeFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkCutter.h>
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

    auto plane = vtkSmartPointer<vtkPlane>(vtkPlane::New());
    plane->SetOrigin(ds->GetCenter());
    plane->SetNormal(-0.287, 0, 0.9579);

    auto cut = vtkSmartPointer<vtkCutter>(vtkCutter::New());
    cut->SetInputData(pl3d_output);
    cut->SetCutFunction(plane);
    cut->GenerateValues(3, 0, 1);

    auto probe = vtkSmartPointer<vtkProbeFilter>(vtkProbeFilter::New());
    probe->SetInputConnection(cut->GetOutputPort());
    probe->SetSourceData(pl3d_output);

    auto cut_mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    cut_mapper->SetInputConnection(probe->GetOutputPort());
    cut_mapper->SetScalarRange(ds->GetPointData()->GetScalars()->GetRange());

    auto cut_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    cut_actor->SetMapper(cut_mapper);

    // Extract plane
    auto comp_plane = vtkSmartPointer<vtkStructuredGridGeometryFilter>(vtkStructuredGridGeometryFilter::New());
    comp_plane->SetInputData(pl3d_output);
    comp_plane->SetExtent(0, 100, 0, 100, 9, 9);

    auto plane_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    plane_mapper->SetInputConnection(comp_plane->GetOutputPort());
    plane_mapper->ScalarVisibilityOff();

    auto plane_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    plane_actor->SetMapper(plane_mapper);
    plane_actor->GetProperty()->SetRepresentationToWireframe();
    plane_actor->GetProperty()->SetColor(0, 0, 0);

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

    renderer->AddActor(cut_actor);
    renderer->AddActor(plane_actor);
    renderer->AddActor(outline_actor);

    renderer->GetActiveCamera()->SetClippingRange(11.1034, 59.5328);
    renderer->GetActiveCamera()->SetFocalPoint(9.71821, 0.458166, 29.3999);
    renderer->GetActiveCamera()->SetPosition(-2.95748, -26.7271, 44.5309);
    renderer->GetActiveCamera()->SetViewUp(0.0184785, 0.479657, 0.877262);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    render_window->Render();
    render_win_inter->Start();

    return 0;
}