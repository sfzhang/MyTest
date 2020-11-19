#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageLuminance.h>
#include <vtkMergeFilter.h>
#include <vtkWarpScalar.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
    auto bmp_reader = vtkSmartPointer<vtkBMPReader>(vtkBMPReader::New());
    bmp_reader->SetFileName("../../data/masonry.bmp");

    auto luminance = vtkSmartPointer<vtkImageLuminance>(vtkImageLuminance::New());
    luminance->SetInputConnection(bmp_reader->GetOutputPort());

    auto geometry = vtkSmartPointer<vtkImageDataGeometryFilter>(vtkImageDataGeometryFilter::New());
    geometry->SetInputConnection(luminance->GetOutputPort());

    auto warp = vtkSmartPointer<vtkWarpScalar>(vtkWarpScalar::New());
    warp->SetInputConnection(geometry->GetOutputPort());
    warp->SetScaleFactor(-0.1);

    auto merge = vtkSmartPointer<vtkMergeFilter>(vtkMergeFilter::New());
    merge->SetGeometryConnection(warp->GetOutputPort());
    merge->SetScalarsConnection(bmp_reader->GetOutputPort());

    auto mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    mapper->SetInputConnection(merge->GetOutputPort());
    mapper->SetScalarRange(0, 255);

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    auto render_win = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_win->AddRenderer(renderer);
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_win);
    render_win->SetSize(512, 512);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(20);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->SetBackground(0.1, 0.2, 0.4);
    renderer->GetActiveCamera()->Zoom(1.4);
    renderer->ResetCameraClippingRange();

    render_win_inter->Initialize();
    render_win_inter->Start();

    return 0;
}