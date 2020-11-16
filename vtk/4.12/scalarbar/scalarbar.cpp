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
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    // Create a sphere for some geometry
    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere->SetCenter(0, 0, 0);
    sphere->SetRadius(1);
    sphere->Update();

    // Create scalar data to associate with the cells of the sphere
    int count = sphere->GetOutput()->GetNumberOfCells();
    auto scalars = vtkSmartPointer<vtkFloatArray>(vtkFloatArray::New());
    scalars->SetNumberOfValues(count);
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        scalars->SetValue(i, i * 1.0 / count);
    }

    auto poly = vtkSmartPointer<vtkPolyData>(vtkPolyData::New());
    poly->DeepCopy(sphere->GetOutput());
    poly->GetCellData()->SetScalars(scalars);

    // mapper
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputData(poly);
    mapper->ScalarVisibilityOn();
    mapper->SetScalarModeToUseCellData();
    mapper->SetColorModeToMapScalars();

    // actor
    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    auto scalar_bar = vtkSmartPointer<vtkScalarBarActor>(vtkScalarBarActor::New());
    scalar_bar->SetOrientationToHorizontal();
    scalar_bar->SetLookupTable(mapper->GetLookupTable());
    scalar_bar->SetTitle("Temperature");
    scalar_bar->SetNumberOfLabels(10);
    scalar_bar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    scalar_bar->GetPositionCoordinate()->SetValue(0.1, 0.01);
    scalar_bar->SetWidth(0.8);
    scalar_bar->SetHeight(0.2);

    // Create a lookup table to share between the mapp[er and the scalar bar
    auto lut = vtkSmartPointer<vtkLookupTable>(vtkLookupTable::New());
    //lut->SetRange(0, 1); only used when IndexedLookup is false
    lut->SetHueRange(0, 1);
    lut->SetSaturationRange(1, 1);
    lut->SetValueRange(1, 1);
    lut->Build();

    mapper->SetLookupTable(lut);
    scalar_bar->SetLookupTable(lut);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->GradientBackgroundOn();
    renderer->SetBackground(1, 1, 1);
    renderer->SetBackground2(0, 0, 0);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    renderer->AddActor(actor);
    renderer->AddActor2D(scalar_bar);

    render_window->Render();
    render_win_inter->Start();

    return 0;
}