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
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto i = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    auto w = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    i->SetRenderWindow(w);

    w->SetMultiSamples(0); // no multisampling
    //w->SetPointSmoothing(1); // point antialiasing
    w->SetLineSmoothing(0);

    auto r = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    w->AddRenderer(r);

    auto s = vtkSmartPointer<vtkSphereSource>(vtkSphereSource::New());
    auto m = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    m->SetInputConnection(s->GetOutputPort());

    auto a = vtkSmartPointer<vtkActor>(vtkActor::New());
    a->SetMapper(m);

    auto p = a->GetProperty();
    //p->SetRepresentationToPoints();
    p->SetRepresentationToWireframe();
    //p->SetPointSize(2);
    p->SetLineWidth(2);
    p->SetLighting(0);
    
    r->AddActor(a);

    i->Start();

    return 0;
}