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

    auto plane = vtkSmartPointer<vtkStructuredGridGeometryFilter>(vtkStructuredGridGeometryFilter::New());
    plane->SetInputData(pl3d_output);
    plane->SetExtent(1, 100, 1, 100, 7, 7);

    auto lut = vtkSmartPointer<vtkLookupTable>(vtkLookupTable::New());
    auto plane_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    plane_mapper->SetLookupTable(lut);
    plane_mapper->SetInputConnection(plane->GetOutputPort());
    plane_mapper->SetScalarRange(ds->GetScalarRange());
    auto plane_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    plane_actor->SetMapper(plane_mapper);

    auto outline = vtkSmartPointer<vtkStructuredGridOutlineFilter>(vtkStructuredGridOutlineFilter::New());
    outline->SetInputData(pl3d_output);
    auto outline_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    outline_mapper->SetInputConnection(outline->GetOutputPort());
    auto outline_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    outline_actor->SetMapper(outline_mapper);

    lut->SetNumberOfColors(256);
    lut->Build();
    for (int i = 0; i < 16; i++) {
        lut->SetTableValue(i * 16, 1, 0, 0, 1);
        lut->SetTableValue(i * 16 + 1, 0, 1, 0, 1);
        lut->SetTableValue(i * 16 + 2, 0, 0, 1, 1);
        lut->SetTableValue(i * 16 + 3, 0, 0, 0, 1);
    }

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