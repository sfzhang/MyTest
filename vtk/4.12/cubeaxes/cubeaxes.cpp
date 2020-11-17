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
#include <vtkBYUReader.h>
#include <vtkPolyDataNormals.h>
#include <vtkLODActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkCubeAxesActor2D.h>
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto byu_reader = vtkSmartPointer<vtkBYUReader>(vtkBYUReader::New());
    byu_reader->SetGeometryFileName("../../data/teapot.g");

    auto normals = vtkSmartPointer<vtkPolyDataNormals>(vtkPolyDataNormals::New());
    normals->SetInputConnection(byu_reader->GetOutputPort());

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(normals->GetOutputPort());
    auto teapot_actor = vtkSmartPointer<vtkLODActor>(vtkLODActor::New());
    teapot_actor->SetMapper(mapper);

    auto outline = vtkSmartPointer<vtkOutlineFilter>(vtkOutlineFilter::New());
    outline->SetInputConnection(normals->GetOutputPort());
    auto outline_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    outline_mapper->SetInputConnection(outline->GetOutputPort());
    auto outline_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    outline_actor->SetMapper(outline_mapper);
    outline_actor->GetProperty()->SetColor(0, 1, 0);

    auto camera = vtkSmartPointer<vtkCamera>(vtkCamera::New());
    camera->SetClippingRange(1.60187, 20.0842);
    camera->SetFocalPoint(0.21406, 1.5, 0);
    camera->SetPosition(8.3761, 4.94858, 4.12505);
    camera->SetViewUp(0.180325, 0.549245, -0.815974);

    auto light = vtkSmartPointer<vtkLight>(vtkLight::New());
    light->SetFocalPoint(0.21406, 1.5, 0);
    light->SetPosition(8.3761, 4.94858, 4.12505);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetViewport(0, 0, 0.5, 1.0);
    renderer->SetActiveCamera(camera);
    renderer->AddLight(light);
    renderer->SetBackground(0.1, 0.2, 0.4);

    renderer->AddViewProp(teapot_actor);
    renderer->AddViewProp(outline_actor);

    auto renderer2 = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer2->SetViewport(0.5, 0, 1.0, 1.0);
    renderer2->SetActiveCamera(camera);
    renderer2->AddLight(light);
    renderer2->SetBackground(0.1, 0.2, 0.4);

    renderer2->AddViewProp(teapot_actor);
    renderer2->AddViewProp(outline_actor);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->SetWindowName("VTK - Cube Axes");
    render_window->AddRenderer(renderer);
    render_window->AddRenderer(renderer2);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    auto prop = vtkSmartPointer<vtkTextProperty>(vtkTextProperty::New());
    prop->SetColor(0, 1, 0);
    prop->ShadowOn();

    auto axes = vtkSmartPointer<vtkCubeAxesActor2D>(vtkCubeAxesActor2D::New());
    axes->SetInputConnection(normals->GetOutputPort());
    axes->SetCamera(renderer->GetActiveCamera());
    axes->SetLabelFormat("%6.4g");
    axes->SetFlyModeToOuterEdges();
    axes->SetFontFactor(0.8);
    axes->SetAxisTitleTextProperty(prop);
    axes->SetAxisLabelTextProperty(prop);
    renderer->AddViewProp(axes);

    auto axes2 = vtkSmartPointer<vtkCubeAxesActor2D>(vtkCubeAxesActor2D::New());
    axes2->SetViewProp(teapot_actor);
    axes2->SetCamera(renderer2->GetActiveCamera());
    axes2->SetLabelFormat("%6.4g");
    axes2->SetFlyModeToClosestTriad();
    axes2->SetFontFactor(0.8);
    axes2->ScalingOff();
    axes2->SetAxisTitleTextProperty(prop);
    axes2->SetAxisLabelTextProperty(prop);
    renderer2->AddViewProp(axes2);

    render_window->Render();
    render_win_inter->Start();

    return 0;
}