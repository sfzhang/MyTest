#include <iostream>
#include <vtkAutoInit.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkTextProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkImageReader.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkWarpScalar.h>
#include <vtkWindowLevelLookupTable.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto lut = vtkSmartPointer<vtkWindowLevelLookupTable>(vtkWindowLevelLookupTable::New());

    auto reader = vtkSmartPointer<vtkImageReader>(vtkImageReader::New());
    reader->SetDataExtent(0, 63, 0, 63, 40, 40);
    reader->SetFilePrefix("../../data/headsq/quarter");
    reader->SetDataMask(0x7fff);

    auto geometry = vtkSmartPointer<vtkImageDataGeometryFilter>(vtkImageDataGeometryFilter::New());
    geometry->SetInputConnection(reader->GetOutputPort());

    auto image_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    image_mapper->SetInputConnection(geometry->GetOutputPort());
    image_mapper->SetScalarRange(0, 2000);
    image_mapper->SetLookupTable(lut);
    auto image_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    image_actor->SetMapper(image_mapper);
    image_actor->AddPosition(64, 64, 0);

    auto warp = vtkSmartPointer<vtkWarpScalar>(vtkWarpScalar::New());
    warp->SetInputConnection(geometry->GetOutputPort());
    warp->SetScaleFactor(0.005);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(warp->GetOutputPort());
    mapper->SetScalarRange(0, 2000);
    mapper->SetLookupTable(lut);

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(0.1, 0.2, 0.4);
    renderer->TwoSidedLightingOff();

    renderer->AddActor(image_actor);
    renderer->AddActor(actor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.5);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    render_window->Render();
    render_win_inter->Start();

    return 0;
}