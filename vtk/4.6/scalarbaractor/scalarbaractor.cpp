#include <vtkActor.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkScalarBarActor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    // Create a sphere for some geometry
    auto sphere = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    sphere->SetCenter(0, 0, 0);
    sphere->SetRadius(1);
    sphere->Update();

    // Create scalar data to associate with the vertices of the sphere
    int points_count = sphere->GetOutput()->GetPoints()->GetNumberOfPoints();
    auto scalars = vtkSmartPointer<vtkFloatArray>(vtkFloatArray::New());
    scalars->SetNumberOfValues(points_count);
    for (int i = 0; i < points_count; i++) {
        scalars->SetValue(i, 1.0 * i / points_count);
    }

    auto poly = vtkSmartPointer<vtkPolyData>(vtkPolyData::New());
    poly->DeepCopy(sphere->GetOutput());
    poly->GetPointData()->SetScalars(scalars);

    // mapper
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputData(poly);
    mapper->ScalarVisibilityOn();
    mapper->SetScalarModeToUsePointData();
    mapper->SetColorModeToMapScalars();

    // actor
    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    auto scalar_bar = vtkSmartPointer<vtkScalarBarActor>(vtkScalarBarActor::New());
    scalar_bar->SetLookupTable(mapper->GetLookupTable());
    scalar_bar->SetTitle("Title");
    scalar_bar->SetNumberOfLabels(4);

    // Create a lookup table to share between the mapp[er and the scalar bar
    auto lut = vtkSmartPointer<vtkLookupTable>(vtkLookupTable::New());
    lut->SetTableRange(0, 1);
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