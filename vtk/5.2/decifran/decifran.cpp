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
#include <vtkDecimatePro.h>
#include <vtkPNGReader.h>
#include <vtkTexture.h>
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto fran = vtkSmartPointer<vtkPolyDataReader>(vtkPolyDataReader::New());
    fran->SetFileName("../../data/fran_cut.vtk");

    auto texture_reader = vtkSmartPointer<vtkPNGReader>(vtkPNGReader::New());
    texture_reader->SetFileName("../../data/fran_cut.png");

    auto texture = vtkSmartPointer<vtkTexture>(vtkTexture::New());
    texture->InterpolateOn();
    texture->SetInputConnection(texture_reader->GetOutputPort());

    auto deci = vtkSmartPointer<vtkDecimatePro>(vtkDecimatePro::New());
    deci->SetInputConnection(fran->GetOutputPort());
    deci->SetTargetReduction(0.9);
    deci->PreserveTopologyOn();

    auto normals = vtkSmartPointer<vtkPolyDataNormals>(vtkPolyDataNormals::New());
    normals->SetInputConnection(deci->GetOutputPort());
    normals->FlipNormalsOn();
    normals->SetFeatureAngle(60);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    mapper->SetInputConnection(normals->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor->SetMapper(mapper);
    actor->GetProperty()->SetAmbient(0.5);
    actor->GetProperty()->SetDiffuse(0.5);
    actor->SetTexture(texture);

    // Create a renderer and render window
    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer->SetBackground(1, 1, 1);

    renderer->AddActor(actor);

    auto render_window = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    render_window->AddRenderer(renderer);

    // Create an interactor
    auto render_win_inter = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    render_win_inter->SetRenderWindow(render_window);

    renderer->GetActiveCamera()->SetClippingRange(0.0475572, 2.37786);
    renderer->GetActiveCamera()->SetFocalPoint(0.052665, -0.129454, -0.0573973);
    renderer->GetActiveCamera()->SetPosition(0.327637, -0.116299, -0.256418);
    renderer->GetActiveCamera()->SetViewUp(-0.0225386, 0.999137, 0.034901);

    render_win_inter->Initialize();
    render_window->Render();
    render_win_inter->Start();

    return 0;
}