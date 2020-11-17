#include <vtkActor.h>
#include <vtkFloatArray.h>
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
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolygon.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkActor2D.h>
#include <vtkCellCenters.h>
#include <vtkTextProperty.h>
#include <vtkIdList.h>
#include <vtkUnstructuredGrid.h>
#include <vtkContourFilter.h>
#include <vtkExtractEdges.h>
#include <vtkTubeFilter.h>
#include <vtkAutoInit.h>
#include <vtkCubeSource.h>
#include <vtkShrinkPolyData.h>
#include <vtkVectorText.h>
#include <vtkThresholdPoints.h>
#include <vtkGlyph3D.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

void case12(vtkSmartPointer<vtkFloatArray> &scalars,
            vtkSmartPointer<vtkVectorText> &label,
            int in, int out)
{
    scalars->InsertValue(0, out);
    scalars->InsertValue(1, in);
    scalars->InsertValue(2, out);
    scalars->InsertValue(3, in);
    scalars->InsertValue(4, in);
    scalars->InsertValue(5, in);
    scalars->InsertValue(6, out);
    scalars->InsertValue(7, out);

    if (in) {
        label->SetText("Case 12 - 00111010");
    }
    else {
        label->SetText("Case 12 - 11000101");
    }
}

int main()
{
    auto scalars = vtkSmartPointer<vtkFloatArray>(vtkFloatArray::New());
    scalars->InsertNextValue(1.0);
    scalars->InsertNextValue(0.0);
    scalars->InsertNextValue(1.0);
    scalars->InsertNextValue(0.0);
    scalars->InsertNextValue(0.0);
    scalars->InsertNextValue(0.0);
    scalars->InsertNextValue(0.0);
    scalars->InsertNextValue(0.0);

    auto points = vtkSmartPointer<vtkPoints>(vtkPoints::New());
    points->InsertNextPoint(0, 0, 0);
    points->InsertNextPoint(1, 0, 0);
    points->InsertNextPoint(1, 1, 0);
    points->InsertNextPoint(0, 1, 0);
    points->InsertNextPoint(0, 0, 1);
    points->InsertNextPoint(1, 0, 1);
    points->InsertNextPoint(1, 1, 1);
    points->InsertNextPoint(0, 1, 1);

    auto ids = vtkSmartPointer<vtkIdList>(vtkIdList::New());
    ids->InsertNextId(0);
    ids->InsertNextId(1);
    ids->InsertNextId(2);
    ids->InsertNextId(3);
    ids->InsertNextId(4);
    ids->InsertNextId(5);
    ids->InsertNextId(6);
    ids->InsertNextId(7);

    auto grid = vtkSmartPointer<vtkUnstructuredGrid>(vtkUnstructuredGrid::New());
    grid->Allocate(10, 10);
    grid->InsertNextCell(12, ids); // 12 is VTK_HEXAHEDRON
    grid->SetPoints(points);
    grid->GetPointData()->SetScalars(scalars);

    auto marching = vtkSmartPointer<vtkContourFilter>(vtkContourFilter::New());
    marching->SetInputData(grid);
    marching->SetValue(0, 0.5);
    marching->Update();

    auto triangle_edges = vtkSmartPointer<vtkExtractEdges>(vtkExtractEdges::New());
    triangle_edges->SetInputConnection(marching->GetOutputPort());

    auto triangle_edge_tubes = vtkSmartPointer<vtkTubeFilter>(vtkTubeFilter::New());
    triangle_edge_tubes->SetInputConnection(triangle_edges->GetOutputPort());
    triangle_edge_tubes->SetRadius(0.005);
    triangle_edge_tubes->SetNumberOfSides(6);
    triangle_edge_tubes->UseDefaultNormalOn();
    triangle_edge_tubes->SetDefaultNormal(0.577, 0.577, 0.577);

    auto triangle_edge_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    triangle_edge_mapper->SetInputConnection(triangle_edge_tubes->GetOutputPort());
    triangle_edge_mapper->ScalarVisibilityOff();

    auto triangle_edge_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    triangle_edge_actor->SetMapper(triangle_edge_mapper);
    triangle_edge_actor->GetProperty()->SetDiffuseColor(1, 0, 0);
    triangle_edge_actor->GetProperty()->SetSpecular(0.4);
    triangle_edge_actor->GetProperty()->SetSpecularPower(10);

    auto shrinker = vtkSmartPointer<vtkShrinkPolyData>(vtkShrinkPolyData::New());
    shrinker->SetShrinkFactor(1);
    shrinker->SetInputConnection(marching->GetOutputPort());

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->ScalarVisibilityOff();
    mapper->SetInputConnection(shrinker->GetOutputPort());

    auto triangles = vtkSmartPointer<vtkActor>(vtkActor::New());
    triangles->SetMapper(mapper);
    triangles->GetProperty()->SetColor(0, 0, 1);
    triangles->GetProperty()->SetOpacity(0.6);

    auto cube = vtkSmartPointer<vtkCubeSource>(vtkCubeSource::New());
    cube->SetCenter(0.5, 0.5, 0.5);
    auto edges = vtkSmartPointer<vtkExtractEdges>(vtkExtractEdges::New());
    edges->SetInputConnection(cube->GetOutputPort());

    auto tubes = vtkSmartPointer<vtkTubeFilter>(vtkTubeFilter::New());
    tubes->SetInputConnection(edges->GetOutputPort());
    tubes->SetRadius(0.01);
    tubes->SetNumberOfSides(6);
    tubes->UseDefaultNormalOn();
    tubes->SetDefaultNormal(0.577, 0.577, 0.577);

    auto tube_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    tube_mapper->SetInputConnection(tubes->GetOutputPort());

    auto cube_edges = vtkSmartPointer<vtkActor>(vtkActor::New());
    cube_edges->SetMapper(tube_mapper);
    cube_edges->GetProperty()->SetDiffuseColor(0, 1, 0);
    cube_edges->GetProperty()->SetSpecular(0.4);
    cube_edges->GetProperty()->SetSpecularPower(10);

    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere->SetRadius(0.04);
    sphere->SetPhiResolution(20);
    sphere->SetThetaResolution(20);

    auto threshold_in = vtkSmartPointer<vtkThresholdPoints>(vtkThresholdPoints::New());
    threshold_in->SetInputData(grid);
    threshold_in->ThresholdByUpper(0.5);

    auto vertices = vtkSmartPointer<vtkGlyph3D>(vtkGlyph3D::New());
    vertices->SetInputConnection(threshold_in->GetOutputPort());
    vertices->SetSourceConnection(sphere->GetOutputPort());

    auto sphere_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    sphere_mapper->SetInputConnection(vertices->GetOutputPort());
    sphere_mapper->ScalarVisibilityOff();

    auto cube_vertices = vtkSmartPointer<vtkActor>(vtkActor::New());
    cube_vertices->SetMapper(sphere_mapper);
    cube_vertices->GetProperty()->SetDiffuseColor(0, 0, 1);

    auto label = vtkSmartPointer<vtkVectorText>(vtkVectorText::New());
    label->SetText("Case 1");

    auto xfer = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    xfer->Identity();
    xfer->Translate(-0.2, 0, 1.25);
    xfer->Scale(0.05, 0.05, 0.05);

    auto xfer_filter = vtkSmartPointer<vtkTransformPolyDataFilter>(vtkTransformPolyDataFilter::New());
    xfer_filter->SetTransform(xfer);
    xfer_filter->SetInputConnection(label->GetOutputPort());

    auto label_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    label_mapper->SetInputConnection(xfer_filter->GetOutputPort());

    auto label_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    label_actor->SetMapper(label_mapper);
    label_actor->GetProperty()->SetColor(1, 1, 0);
    label_actor->GetProperty()->ShadingOn();

    auto base = vtkSmartPointer<vtkCubeSource>(vtkCubeSource::New());
    base->SetXLength(1.5);
    base->SetYLength(0.01);
    base->SetZLength(1.5);

    auto base_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    base_mapper->SetInputConnection(base->GetOutputPort());

    auto base_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    base_actor->SetMapper(base_mapper);
    base_actor->SetPosition(0.5, -0.09, 0.5);

    // Create a renderer
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor(triangle_edge_actor);
    renderer->AddActor(cube_edges);
    renderer->AddActor(triangles);
    renderer->AddActor(base_actor);
    renderer->AddActor(cube_vertices);
    renderer->AddActor(label_actor);
    renderer->SetBackground(1, 1, 1);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);
    render_window->SetSize(500, 500);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    case12(scalars, label, 0, 1);

    grid->Modified();

    render_win_inter->Initialize();
    render_window->Render();
    render_win_inter->Start();

    return 0;
}