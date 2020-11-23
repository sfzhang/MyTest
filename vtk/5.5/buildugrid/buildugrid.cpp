#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkNamedColors.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkMath.h>
#include <vtkDataSetMapper.h>
#include <vtkVoxel.h>
#include <vtkUnstructuredGrid.h>
#include <vtkTriangleStrip.h>
#include <vtkAutoInit.h>
#include <iostream>
#include <array>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto colors = vtkSmartPointer<vtkNamedColors>(vtkNamedColors::New());

    auto voxel_points = vtkSmartPointer<vtkPoints>(vtkPoints::New());
    voxel_points->SetNumberOfPoints(8);
    voxel_points->InsertPoint(0, 0, 0, 0);
    voxel_points->InsertPoint(1, 1, 0, 0);
    voxel_points->InsertPoint(2, 0, 1, 0);
    voxel_points->InsertPoint(3, 1, 1, 0);
    voxel_points->InsertPoint(4, 0, 0, 1);
    voxel_points->InsertPoint(5, 1, 0, 1);
    voxel_points->InsertPoint(6, 0, 1, 1);
    voxel_points->InsertPoint(7, 1, 1, 1);

    auto voxel = vtkSmartPointer<vtkVoxel>(vtkVoxel::New());
    for (int i = 0; i < 8; i++) {
      voxel->GetPointIds()->SetId(i, i);
    }

    auto voxel_grid = vtkSmartPointer<vtkUnstructuredGrid>(vtkUnstructuredGrid::New());
    voxel_grid->Allocate(1, 1);
    voxel_grid->InsertNextCell(voxel->GetCellType(), voxel->GetPointIds());
    voxel_grid->SetPoints(voxel_points);

    auto voxel_mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    voxel_mapper->SetInputData(voxel_grid);

    auto voxel_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    voxel_actor->SetMapper(voxel_mapper);
    voxel_actor->GetProperty()->SetColor(colors->GetColor3d("red").GetData());

    // triangle strip
    auto tri_strip_points = vtkSmartPointer<vtkPoints>(vtkPoints::New());
    tri_strip_points->SetNumberOfPoints(5);
    tri_strip_points->InsertPoint(0, 0, 1, 0);
    tri_strip_points->InsertPoint(1, 0, 0, 0);
    tri_strip_points->InsertPoint(2, 1, 1, 0);
    tri_strip_points->InsertPoint(3, 1, 0, 0);
    tri_strip_points->InsertPoint(4, 2, 1, 0);

    auto tri_strip_tcoords = vtkSmartPointer<vtkFloatArray>(vtkFloatArray::New());
    tri_strip_tcoords->SetNumberOfComponents(3);
    tri_strip_tcoords->SetNumberOfTuples(3);
    for (int i = 0; i < 5; i++) {
      tri_strip_tcoords->InsertTuple3(i, i + 1, i + 1, i + 1);
    }

    auto tri_strip = vtkSmartPointer<vtkTriangleStrip>(vtkTriangleStrip::New());
    tri_strip->GetPointIds()->SetNumberOfIds(5);
    for (int i = 0; i < 5; i++) {
      tri_strip->GetPointIds()->SetId(i, i);
    }

    auto tri_strip_grid = vtkSmartPointer<vtkUnstructuredGrid>(vtkUnstructuredGrid::New());
    tri_strip_grid->Allocate(1, 1);
    tri_strip_grid->InsertNextCell(tri_strip->GetCellType(), tri_strip->GetPointIds());
    tri_strip_grid->SetPoints(tri_strip_points);
    //tri_strip_grid->GetPointData()->SetTCoords(tri_strip_tcoords);

    auto tri_strip_mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    tri_strip_mapper->SetInputData(tri_strip_grid);

    auto tri_strip_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    tri_strip_actor->SetMapper(tri_strip_mapper);
    tri_strip_actor->AddPosition(8, 0, 2);
    tri_strip_actor->GetProperty()->SetRepresentationToWireframe();
    tri_strip_actor->GetProperty()->SetColor(0, 1, 0);
    tri_strip_actor->GetProperty()->SetDiffuseColor(0.3, 0.7, 1);

    auto i = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    auto w = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    i->SetRenderWindow(w);

    auto r = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    w->AddRenderer(r);
    r->AddActor(voxel_actor);
    r->AddActor(tri_strip_actor);
    r->SetBackground(colors->GetColor3d("Cornsilk").GetData());

    w->SetSize(600, 600);

    w->Render();

    auto camera = r->GetActiveCamera();
    camera->Elevation(60.0);
    camera->Azimuth(30);
    camera->Zoom(1);
    r->ResetCameraClippingRange();

    w->Render();
    i->Start();

    return 0;
}