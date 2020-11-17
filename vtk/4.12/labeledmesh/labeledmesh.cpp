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
#include <vtkIdFilter.h>
#include <vtkSelectVisiblePoints.h>
#include <vtkLabeledDataMapper.h>
#include <vtkCellCenters.h>
#include <vtkTextProperty.h>
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int g_xmin = 200;
int g_xlength = 100;
int g_xmax = g_xmin + g_xlength;
int g_ymin = 200;
int g_ylength = 100;
int g_ymax = g_ymin + g_ylength;

int main()
{
    auto pts = vtkSmartPointer<vtkPoints>(vtkPoints::New());
    pts->InsertPoint(0, g_xmin, g_ymin, 0);
    pts->InsertPoint(1, g_xmax, g_ymin, 0);
    pts->InsertPoint(2, g_xmax, g_ymax, 0);
    pts->InsertPoint(3, g_xmin, g_ymax, 0);

    auto rect = vtkSmartPointer<vtkCellArray>(vtkCellArray::New());
    rect->InsertNextCell(5);
    rect->InsertCellPoint(0);
    rect->InsertCellPoint(1);
    rect->InsertCellPoint(2);
    rect->InsertCellPoint(3);
    rect->InsertCellPoint(0);

    auto select_rect = vtkSmartPointer<vtkPolyData>(vtkPolyData::New());
    select_rect->SetPoints(pts);
    select_rect->SetLines(rect);

    auto rect_mapper = vtkSmartPointer<vtkPolyDataMapper2D>(vtkPolyDataMapper2D::New());
    rect_mapper->SetInputData(select_rect);

    auto rect_actor = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    rect_actor->SetMapper(rect_mapper);

    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    auto sphere_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    sphere_mapper->SetInputConnection(sphere->GetOutputPort());

    auto sphere_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    sphere_actor->SetMapper(sphere_mapper);

    auto ids = vtkSmartPointer<vtkIdFilter>(vtkIdFilter::New());
    ids->SetInputConnection(sphere->GetOutputPort());
    ids->PointIdsOn();
    ids->CellIdsOn();
    ids->FieldDataOn();

    // Create a renderer
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());

    auto vis_pts = vtkSmartPointer<vtkSelectVisiblePoints>(vtkSelectVisiblePoints::New());
    vis_pts->SetInputConnection(ids->GetOutputPort());
    vis_pts->SetRenderer(renderer);
    vis_pts->SelectionWindowOn();
    vis_pts->SetSelection(g_xmin, g_xmin + g_xlength, g_ymin, g_ymin + g_ylength);

    auto ldm = vtkSmartPointer<vtkLabeledDataMapper>(vtkLabeledDataMapper::New());
    ldm->SetInputConnection(vis_pts->GetOutputPort());
    ldm->SetLabelModeToLabelFieldData();

    auto point_labels = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    point_labels->SetMapper(ldm);

    // Create labels for cells
    auto cc = vtkSmartPointer<vtkCellCenters>(vtkCellCenters::New());
    cc->SetInputConnection(ids->GetOutputPort());

    auto vis_cells = vtkSmartPointer<vtkSelectVisiblePoints>(vtkSelectVisiblePoints::New());
    vis_cells->SetInputConnection(cc->GetOutputPort());
    vis_cells->SetRenderer(renderer);
    vis_cells->SelectionWindowOn();
    vis_cells->SetSelection(g_xmin, g_xmin + g_xlength, g_ymin, g_ymin + g_ylength);

    auto cell_mapper = vtkSmartPointer<vtkLabeledDataMapper>(vtkLabeledDataMapper::New());
    cell_mapper->SetInputConnection(vis_cells->GetOutputPort());
    cell_mapper->SetLabelModeToLabelFieldData();
    cell_mapper->GetLabelTextProperty()->SetColor(0, 1, 0);

    auto cell_labels = vtkSmartPointer<vtkActor2D>(vtkActor2D::New());
    cell_labels->SetMapper(cell_mapper);

    renderer->AddActor(sphere_actor);
    renderer->AddActor2D(rect_actor);
    renderer->AddActor2D(point_labels);
    renderer->AddActor2D(cell_labels);
    renderer->SetBackground(1, 1, 1);

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