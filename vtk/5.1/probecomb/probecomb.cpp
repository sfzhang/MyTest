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
#include <vtkDataSetMapper.h>
#include <vtkPlaneSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkProbeFilter.h>
#include <vtkContourFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkDataSetMapper.h>
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

    auto pl3d_mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    pl3d_mapper->SetInputData(ds);

    auto pl3d_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    pl3d_actor->SetMapper(pl3d_mapper);

    auto plane = vtkSmartPointer<vtkPlaneSource>(vtkPlaneSource::New());
    plane->SetResolution(50, 50);

    auto t1 = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    t1->Translate(3.7, 0, 28.37);
    t1->Scale(5, 5, 5);
    t1->RotateY(90);
    auto tpd1 = vtkSmartPointer<vtkTransformPolyDataFilter>(vtkTransformPolyDataFilter::New());
    tpd1->SetInputConnection(plane->GetOutputPort());
    tpd1->SetTransform(t1);
    auto ol1 = vtkSmartPointer<vtkOutlineFilter>(vtkOutlineFilter::New());
    ol1->SetInputConnection(tpd1->GetOutputPort());
    auto map1 = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    map1->SetInputConnection(ol1->GetOutputPort());
    auto actor1 = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor1->SetMapper(map1);
    actor1->GetProperty()->SetColor(0, 0, 0);

    auto t2 = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    t2->Translate(9.2, 0, 31.20);
    t2->Scale(5, 5, 5);
    t2->RotateY(90);
    auto tpd2 = vtkSmartPointer<vtkTransformPolyDataFilter>(vtkTransformPolyDataFilter::New());
    tpd2->SetInputConnection(plane->GetOutputPort());
    tpd2->SetTransform(t2);
    auto ol2 = vtkSmartPointer<vtkOutlineFilter>(vtkOutlineFilter::New());
    ol2->SetInputConnection(tpd2->GetOutputPort());
    auto map2 = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    map2->SetInputConnection(ol2->GetOutputPort());
    auto actor2 = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor2->SetMapper(map2);
    actor2->GetProperty()->SetColor(0, 0, 0);

    auto t3 = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    t3->Translate(13.27, 0, 33.30);
    t3->Scale(5, 5, 5);
    t3->RotateY(90);
    auto tpd3 = vtkSmartPointer<vtkTransformPolyDataFilter>(vtkTransformPolyDataFilter::New());
    tpd3->SetInputConnection(plane->GetOutputPort());
    tpd3->SetTransform(t3);
    auto ol3 = vtkSmartPointer<vtkOutlineFilter>(vtkOutlineFilter::New());
    ol3->SetInputConnection(tpd3->GetOutputPort());
    auto map3 = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    map3->SetInputConnection(ol3->GetOutputPort());
    auto actor3 = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor3->SetMapper(map3);
    actor3->GetProperty()->SetColor(0, 0, 0);

    auto append = vtkSmartPointer<vtkAppendPolyData>(vtkAppendPolyData::New());
    append->AddInputConnection(tpd1->GetOutputPort());
    append->AddInputConnection(tpd2->GetOutputPort());
    append->AddInputConnection(tpd3->GetOutputPort());

    auto probe = vtkSmartPointer<vtkProbeFilter>(vtkProbeFilter::New());
    probe->SetInputConnection(append->GetOutputPort());
    probe->SetSourceData(pl3d_output);

    auto contour = vtkSmartPointer<vtkContourFilter>(vtkContourFilter::New());
    contour->SetInputConnection(probe->GetOutputPort());
    contour->GenerateValues(50, ds->GetScalarRange());
    auto contour_map = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    contour_map->SetInputConnection(contour->GetOutputPort());
    contour_map->SetScalarRange(ds->GetScalarRange());
    auto plane_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    plane_actor->SetMapper(contour_map);

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

    //renderer->AddActor(pl3d_actor);
    renderer->AddActor(actor1);
    renderer->AddActor(actor2);
    renderer->AddActor(actor3);
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