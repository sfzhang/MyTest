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
#include <vtkImageSinusoidSource.h>
#include <vtkImageData.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkLookupTable.h>
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto i = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    auto w = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());

    w->SetMultiSamples(0); // no multisampling
    w->SetAlphaBitPlanes(1);
    i->SetRenderWindow(w);

    auto r = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    w->AddRenderer(r);
    r->SetUseDepthPeeling(1);
    r->SetMaximumNumberOfPeels(200);
    r->SetOcclusionRatio(0.1);

    auto s = vtkSmartPointer<vtkImageSinusoidSource>(vtkImageSinusoidSource::New());
    s->SetWholeExtent(0, 9, 0, 9, 9, 9);
    s->SetPeriod(5);
    s->Update();

    auto m = s->GetOutput();

    double range[2] = {0};
    m->GetScalarRange(range);

    auto surface = vtkSmartPointer<vtkDataSetSurfaceFilter>(vtkDataSetSurfaceFilter::New());
    surface->SetInputConnection(s->GetOutputPort());

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(surface->GetOutputPort());

    auto lut = vtkSmartPointer<vtkLookupTable>(vtkLookupTable::New());
    lut->SetTableRange(range);
    lut->SetAlphaRange(0.5, 0.5);
    lut->SetHueRange(0.2, 0.7);
    lut->SetNumberOfTableValues(256);
    lut->Build();

    mapper->SetScalarVisibility(1);
    mapper->SetLookupTable(lut);

    auto a = vtkSmartPointer<vtkActor>(vtkActor::New());
    a->SetMapper(mapper);
    r->AddActor(a);

    r->SetBackground(0.1, 0.3, 0);
    w->SetSize(400, 400);

    w->Render();
    if (r->GetLastRenderingUsedDepthPeeling()) {
        cout << "depth peeling was used!" << endl;
    }
    else {
        cout << "depth peeling was not used (alpha blending instead)" << endl;
    }

    auto camera = r->GetActiveCamera();
    camera->Azimuth(-40.0);
    camera->Elevation(20);
    w->Render();

    i->Start();

    return 0;
}