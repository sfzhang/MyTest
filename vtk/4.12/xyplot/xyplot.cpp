#include <vtkActor.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkCellData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkScalarBarActor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkLineSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkProbeFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkTubeFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkProperty.h>
#include <vtkXYPlotActor.h>
#include <vtkProperty2D.h>
#include <vtkTextProperty.h>
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

    // Create three the line source to use for the probe lines
    auto line = vtkSmartPointer<vtkLineSource>(vtkLineSource::New());
    line->SetResolution(30);

    // Move the line into place and create the probe filter.
    auto xferm1 = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    xferm1->Translate(3.7, 0, 28.37);
    xferm1->Scale(5, 5, 5);
    xferm1->RotateY(90);

    auto tf1 = vtkSmartPointer<vtkTransformPolyDataFilter>(vtkTransformPolyDataFilter::New());
    tf1->SetInputConnection(line->GetOutputPort());
    tf1->SetTransform(xferm1);

    auto probe1 = vtkSmartPointer<vtkProbeFilter>(vtkProbeFilter::New());
    probe1->SetInputConnection(tf1->GetOutputPort());
    probe1->SetSourceData(pl3d_output);

    // Move the line into place and create the probe filter.
    auto xferm2 = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    xferm2->Translate(9.2, 0, 31.20);
    xferm2->Scale(5, 5, 5);
    xferm2->RotateY(90);

    auto tf2 = vtkSmartPointer<vtkTransformPolyDataFilter>(vtkTransformPolyDataFilter::New());
    tf2->SetInputConnection(line->GetOutputPort());
    tf2->SetTransform(xferm2);

    auto probe2 = vtkSmartPointer<vtkProbeFilter>(vtkProbeFilter::New());
    probe2->SetInputConnection(tf2->GetOutputPort());
    probe2->SetSourceData(pl3d_output);

    // Move the line into place and create the probe filter.
    auto xferm3 = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    xferm3->Translate(13.27, 0, 33.40);
    xferm3->Scale(4.5, 4.5, 4.5);
    xferm3->RotateY(90);

    auto tf3 = vtkSmartPointer<vtkTransformPolyDataFilter>(vtkTransformPolyDataFilter::New());
    tf3->SetInputConnection(line->GetOutputPort());
    tf3->SetTransform(xferm3);

    auto probe3 = vtkSmartPointer<vtkProbeFilter>(vtkProbeFilter::New());
    probe3->SetInputConnection(tf3->GetOutputPort());
    probe3->SetSourceData(pl3d_output);

    auto append_poly_data = vtkSmartPointer<vtkAppendPolyData>(vtkAppendPolyData::New());
    append_poly_data->AddInputConnection(probe1->GetOutputPort());
    append_poly_data->AddInputConnection(probe2->GetOutputPort());
    append_poly_data->AddInputConnection(probe3->GetOutputPort());

    auto tuber = vtkSmartPointer<vtkTubeFilter>(vtkTubeFilter::New());
    tuber->SetInputConnection(append_poly_data->GetOutputPort());
    tuber->SetRadius(0.1);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(tuber->GetOutputPort());

    auto line_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    line_actor->SetMapper(mapper);

    // Draw an outline of the PLOT3D data set
    auto outline = vtkSmartPointer<vtkStructuredGridOutlineFilter>(vtkStructuredGridOutlineFilter::New());
    outline->SetInputData(pl3d_output);
    auto outline_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    outline_mapper->SetInputConnection(outline->GetOutputPort());

    auto outline_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    outline_actor->SetMapper(outline_mapper);
    outline_actor->GetProperty()->SetColor(1, 0, 0);

    // XYPLOT1
    auto xyplot1 = vtkSmartPointer<vtkXYPlotActor>(vtkXYPlotActor::New());
    xyplot1->AddDataSetInputConnection(probe1->GetOutputPort());
    xyplot1->AddDataSetInputConnection(probe2->GetOutputPort());
    xyplot1->AddDataSetInputConnection(probe3->GetOutputPort());
    xyplot1->GetPositionCoordinate()->SetValue(0, 0.67, 0);
    xyplot1->GetPosition2Coordinate()->SetValue(1.0, 0.33, 0);
    xyplot1->SetXValuesToArcLength();
    xyplot1->SetNumberOfXLabels(6);
    xyplot1->SetTitle("Pressure vs. Arc Length (Zoomed View)");
    xyplot1->SetXTitle("");
    xyplot1->SetYTitle("P");
    xyplot1->SetXRange(0.1, 0.35);
    xyplot1->SetYRange(0.2, 0.4);
    xyplot1->GetProperty()->SetColor(0, 0, 0);
    xyplot1->GetProperty()->SetLineWidth(2);

    auto prop = xyplot1->GetTitleTextProperty();
    prop->SetColor(xyplot1->GetProperty()->GetColor());
    xyplot1->SetAxisTitleTextProperty(prop);
    xyplot1->SetAxisTitleTextProperty(prop);

    // XYPLOT2
    auto xyplot2 = vtkSmartPointer<vtkXYPlotActor>(vtkXYPlotActor::New());
    xyplot2->AddDataSetInputConnection(probe1->GetOutputPort());
    xyplot2->AddDataSetInputConnection(probe2->GetOutputPort());
    xyplot2->AddDataSetInputConnection(probe3->GetOutputPort());
    xyplot2->GetPositionCoordinate()->SetValue(0, 0.33, 0);
    xyplot2->GetPosition2Coordinate()->SetValue(1.0, 0.33, 0);
    xyplot2->SetXValuesToNormalizedArcLength();
    xyplot2->SetNumberOfXLabels(6);
    xyplot2->SetTitle("Pressure vs. Normalized Arc Length");
    xyplot2->SetXTitle("");
    xyplot2->SetYTitle("P");
    xyplot2->PlotPointsOn();
    xyplot2->PlotLinesOff();
    xyplot2->GetProperty()->SetColor(1, 0, 0);
    xyplot2->GetProperty()->SetPointSize(5);

    prop = xyplot2->GetTitleTextProperty();
    prop->SetColor(xyplot2->GetProperty()->GetColor());
    xyplot2->SetAxisTitleTextProperty(prop);
    xyplot2->SetAxisTitleTextProperty(prop);

    // XYPLOT3
    auto xyplot3 = vtkSmartPointer<vtkXYPlotActor>(vtkXYPlotActor::New());
    xyplot3->AddDataSetInputConnection(probe1->GetOutputPort());
    xyplot3->AddDataSetInputConnection(probe2->GetOutputPort());
    xyplot3->AddDataSetInputConnection(probe3->GetOutputPort());
    xyplot3->GetPositionCoordinate()->SetValue(0, 0, 0);
    xyplot3->GetPosition2Coordinate()->SetValue(1.0, 0.33, 0);
    xyplot3->SetXValuesToNormalizedArcLength();
    xyplot3->SetNumberOfXLabels(6);
    xyplot3->SetTitle("Pressure vs. Point Id");
    xyplot3->SetXTitle("Probe Length");
    xyplot3->SetYTitle("P");
    xyplot3->PlotPointsOn();
    xyplot3->GetProperty()->SetColor(0, 0, 1);
    xyplot3->GetProperty()->SetPointSize(3);

    prop = xyplot3->GetTitleTextProperty();
    prop->SetColor(xyplot3->GetProperty()->GetColor());
    xyplot3->SetAxisTitleTextProperty(prop);
    xyplot3->SetAxisTitleTextProperty(prop);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->GradientBackgroundOn();
    renderer->SetBackground(1, 1, 1);
    renderer->SetBackground2(0, 0, 0);
    renderer->SetViewport(0, 0, .5, 1);

    renderer->AddActor(line_actor);
    renderer->AddActor(outline_actor);

    auto renderer1 = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer1->SetViewport(0.5, 0, 1.0, 1.0);
    renderer1->AddActor(xyplot1);
    renderer1->AddActor(xyplot2);
    renderer1->AddActor(xyplot3);
    renderer1->SetBackground(1, 1, 1);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);
    render_window->AddRenderer(renderer1);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    render_window->Render();
    render_win_inter->Start();

    return 0;
}