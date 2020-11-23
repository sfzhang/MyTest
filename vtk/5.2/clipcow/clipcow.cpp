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
#include <vtkBYUReader.h>
#include <vtkPlane.h>
#include <vtkClipPolyData.h>
#include <vtkCutter.h>
#include <vtkStripper.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkAutoInit.h>
#include <iostream>
#include <array>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto colors = vtkSmartPointer<vtkNamedColors>(vtkNamedColors::New());

    auto cow = vtkSmartPointer<vtkBYUReader>(vtkBYUReader::New());
    cow->SetGeometryFileName("../../data/cow.g");

    auto cow_normals = vtkSmartPointer<vtkPolyDataNormals>(vtkPolyDataNormals::New());
    cow_normals->SetInputConnection(cow->GetOutputPort());

    auto plane = vtkSmartPointer<vtkPlane>(vtkPlane::New());
    plane->SetOrigin(0.25, 0, 0);
    plane->SetNormal(-1, -1, 0);

    auto clipper = vtkSmartPointer<vtkClipPolyData>(vtkClipPolyData::New());
    clipper->SetInputConnection(cow_normals->GetOutputPort());
    clipper->SetClipFunction(plane);
    clipper->GenerateClippedOutputOn();
    clipper->GenerateClipScalarsOn();
    clipper->SetValue(0.5);

    auto clip_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    clip_mapper->SetInputConnection(clipper->GetOutputPort());
    clip_mapper->ScalarVisibilityOff();

    auto back_prop = vtkSmartPointer<vtkProperty>(vtkProperty::New());
    back_prop->SetDiffuseColor(colors->GetColor3d("tomato").GetData());

    auto clip_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    clip_actor->SetMapper(clip_mapper);
    clip_actor->GetProperty()->SetColor(
        colors->GetColor3d("peacock").GetData());
    clip_actor->SetBackfaceProperty(back_prop);

    auto cutter = vtkSmartPointer<vtkCutter>(vtkCutter::New());
    cutter->SetInputConnection(cow_normals->GetOutputPort());
    cutter->SetCutFunction(plane);
    cutter->GenerateCutScalarsOn();
    cutter->SetValue(0, 0.5);

    auto stripper = vtkSmartPointer<vtkStripper>(vtkStripper::New());
    stripper->SetInputConnection(cutter->GetOutputPort());
    stripper->Update();

    auto cut_poly = vtkSmartPointer<vtkPolyData>(vtkPolyData::New());
    cut_poly->SetPoints(stripper->GetOutput()->GetPoints());
    cut_poly->SetPolys(stripper->GetOutput()->GetLines());

    auto triangels = vtkSmartPointer<vtkTriangleFilter>(vtkTriangleFilter::New());
    triangels->SetInputData(cut_poly);

    auto cut_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    cut_mapper->SetInputData(cut_poly);
    cut_mapper->SetInputConnection(triangels->GetOutputPort());

    auto cut_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    cut_actor->SetMapper(cut_mapper);
    cut_actor->GetProperty()->SetColor(colors->GetColor3d("peacock").GetData());

    auto rest_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    rest_mapper->SetInputConnection(clipper->GetClippedOutputPort());
    rest_mapper->ScalarVisibilityOff();
    auto rest_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    rest_actor->SetMapper(rest_mapper);
    rest_actor->GetProperty()->SetRepresentationToWireframe();

    auto i = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    auto w = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    i->SetRenderWindow(w);

    auto r = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    w->AddRenderer(r);
    r->AddActor(clip_actor);
    r->AddActor(cut_actor);
    r->AddActor(rest_actor);
    r->SetBackground(colors->GetColor3d("Cornsilk").GetData());

    w->SetSize(400, 400);

    w->Render();

    auto camera = r->GetActiveCamera();
    camera->Azimuth(30.0);
    camera->Elevation(30);
    camera->Dolly(1.5);
    r->ResetCameraClippingRange();

    w->Render();
    i->Start();

    return 0;
}