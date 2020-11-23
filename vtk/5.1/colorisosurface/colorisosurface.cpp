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
#include <vtkPolyDataNormals.h>
#include <vtkDataSet.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkPlaneSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkProbeFilter.h>
#include <vtkContourFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkLODActor.h>
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
    pl3d->AddFunction(153); // velocity magnitude
    pl3d->Update();

    auto pl3d_output = pl3d->GetOutput()->GetBlock(0);
    auto ds = vtkDataSet::SafeDownCast(pl3d_output);

    auto iso = vtkSmartPointer<vtkContourFilter>(vtkContourFilter::New());
    iso->SetInputData(pl3d_output);
    iso->SetValue(0, 0.24);

    auto normals = vtkSmartPointer<vtkPolyDataNormals>(vtkPolyDataNormals::New());
    normals->SetInputConnection(iso->GetOutputPort());
    normals->SetFeatureAngle(45);

    auto iso_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    iso_mapper->SetInputConnection(normals->GetOutputPort());
    iso_mapper->ScalarVisibilityOn();
    iso_mapper->SetScalarRange(0, 1500);
    iso_mapper->SetScalarModeToUseFieldData();
    iso_mapper->ColorByArrayComponent("VelocityMagnitude", 0); // seems not work!!!

    auto iso_actor = vtkSmartPointer<vtkLODActor>(vtkLODActor::New());
    iso_actor->SetMapper(iso_mapper);
    iso_actor->SetNumberOfCloudPoints(1000);

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

    renderer->AddActor(iso_actor);
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