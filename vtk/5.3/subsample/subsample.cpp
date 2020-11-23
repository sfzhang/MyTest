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
#include <vtkAppendPolyData.h>
#include <vtkWarpScalar.h>
#include <vtkPolyDataNormals.h>
#include <vtkExtractGrid.h>
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

    auto extract = vtkSmartPointer<vtkExtractGrid>(vtkExtractGrid::New());
    extract->SetInputData(pl3d_output);
    extract->SetVOI(-1000, 1000, -1000, 1000, -1000, 1000);
    extract->SetSampleRate(3, 3, 3);
    extract->IncludeBoundaryOn();

    auto plane = vtkSmartPointer<vtkStructuredGridGeometryFilter>(vtkStructuredGridGeometryFilter::New());
    plane->SetInputConnection(extract->GetOutputPort());
    plane->SetExtent(1, 10, 1, 100, 1, 100);

    auto plane2 = vtkSmartPointer<vtkStructuredGridGeometryFilter>(vtkStructuredGridGeometryFilter::New());
    plane2->SetInputConnection(extract->GetOutputPort());
    plane2->SetExtent(30, 30, 1, 100, 1, 100);

    auto plane3 = vtkSmartPointer<vtkStructuredGridGeometryFilter>(vtkStructuredGridGeometryFilter::New());
    plane3->SetInputConnection(extract->GetOutputPort());
    plane3->SetExtent(45, 45, 1, 100, 1, 100);

    auto append = vtkSmartPointer<vtkAppendPolyData>(vtkAppendPolyData::New());
    append->AddInputConnection(plane->GetOutputPort());
    append->AddInputConnection(plane2->GetOutputPort());
    append->AddInputConnection(plane3->GetOutputPort());

    auto warp = vtkSmartPointer<vtkWarpScalar>(vtkWarpScalar::New());
    warp->SetInputConnection(append->GetOutputPort());
    warp->UseNormalOn();
    warp->SetNormal(1, 0, 0);
    warp->SetScaleFactor(2.5);

    auto normals = vtkSmartPointer<vtkPolyDataNormals>(vtkPolyDataNormals::New());
    normals->SetInputConnection(warp->GetOutputPort());
    normals->SetFeatureAngle(60);

    auto plane_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    plane_mapper->SetInputConnection(normals->GetOutputPort());
    plane_mapper->SetScalarRange(ds->GetScalarRange());
    auto plane_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    plane_actor->SetMapper(plane_mapper);

    auto outline = vtkSmartPointer<vtkStructuredGridOutlineFilter>(vtkStructuredGridOutlineFilter::New());
    outline->SetInputConnection(extract->GetOutputPort());
    auto outline_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    outline_mapper->SetInputConnection(outline->GetOutputPort());
    auto outline_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    outline_actor->SetMapper(outline_mapper);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(0.1, 0.2, 0.4);
    renderer->TwoSidedLightingOff();

    renderer->AddActor(plane_actor);
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