#include <vtkActor.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkTextProperty.h>
#include <vtkCamera.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataNormals.h>
#include <vtkMaskPoints.h>
#include <vtkConeSource.h>
#include <vtkGlyph3D.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto fran = vtkSmartPointer<vtkPolyDataReader>(vtkPolyDataReader::New());
    fran->SetFileName("../../data/fran_cut.vtk");

    auto normals = vtkSmartPointer<vtkPolyDataNormals>(vtkPolyDataNormals::New());
    normals->SetInputConnection(fran->GetOutputPort());
    normals->FlipNormalsOn();

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(normals->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1.0, 0.49, 0.25);

    auto pt_mask = vtkSmartPointer<vtkMaskPoints>(vtkMaskPoints::New());
    pt_mask->SetInputConnection(normals->GetOutputPort());
    pt_mask->SetOnRatio(10);
    pt_mask->RandomModeOn();

    auto cone = vtkSmartPointer<vtkConeSource>(vtkConeSource::New());
    cone->SetResolution(6);

    auto transform = vtkSmartPointer<vtkTransform>(vtkTransform::New());
    transform->Translate(0.5, 0, 0);
    auto transform_f = vtkSmartPointer<vtkTransformPolyDataFilter>(vtkTransformPolyDataFilter::New());
    transform_f->SetInputConnection(cone->GetOutputPort());
    transform_f->SetTransform(transform);

    auto glyph = vtkSmartPointer<vtkGlyph3D>(vtkGlyph3D::New());
    glyph->SetInputConnection(pt_mask->GetOutputPort());
    glyph->SetSourceConnection(transform_f->GetOutputPort());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.004);

    auto spike_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    spike_mapper->SetInputConnection(glyph->GetOutputPort());
    auto spike_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    spike_actor->SetMapper(spike_mapper);
    spike_actor->GetProperty()->SetColor(0, 0.79, 0.34);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(1, 1, 1);

    renderer->AddActor(actor);
    renderer->AddActor(spike_actor);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    render_win_inter->Initialize();
    render_window->Render();
    render_win_inter->Start();

    return 0;
}