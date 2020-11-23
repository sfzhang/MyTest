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
#include <vtkDataSetReader.h>
#include <vtkWarpVector.h>
#include <vtkConnectivityFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkGeometryFilter.h>
#include <vtkCastToConcrete.h>
#include <vtkExtractUnstructuredGrid.h>
#include <vtkPolyDataNormals.h>
#include <vtkAutoInit.h>
#include <iostream>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main()
{
    auto reader = vtkSmartPointer<vtkDataSetReader>(vtkDataSetReader::New());
    reader->SetFileName("../../data/blow.vtk");
    reader->SetScalarsName("thickness9");
    reader->SetVectorsName("displacement9");

    auto cast = vtkSmartPointer<vtkCastToConcrete>(vtkCastToConcrete::New());
    cast->SetInputConnection(reader->GetOutputPort());

    auto warp = vtkSmartPointer<vtkWarpVector>(vtkWarpVector::New());
    warp->SetInputConnection(cast->GetOutputPort());

    auto connect = vtkSmartPointer<vtkConnectivityFilter>(vtkConnectivityFilter::New());
    connect->SetInputConnection(warp->GetOutputPort());
    connect->SetExtractionModeToSpecifiedRegions();
    connect->AddSpecifiedRegion(0);
    connect->AddSpecifiedRegion(1);

    auto mold_mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    mold_mapper->SetInputConnection(connect->GetOutputPort());
    mold_mapper->ScalarVisibilityOff();

    auto mold_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    mold_actor->SetMapper(mold_mapper);
    mold_actor->GetProperty()->SetColor(0.2, 0.2, 0.2);
    mold_actor->GetProperty()->SetRepresentationToWireframe();

    auto connect2 = vtkSmartPointer<vtkConnectivityFilter>(vtkConnectivityFilter::New());
    connect2->SetInputConnection(warp->GetOutputPort());
    connect2->SetExtractionModeToSpecifiedRegions();
    connect2->AddSpecifiedRegion(2);

    auto extract = vtkSmartPointer<vtkExtractUnstructuredGrid>(vtkExtractUnstructuredGrid::New());
    extract->SetInputConnection(connect2->GetOutputPort());
    extract->CellClippingOn();
    extract->SetCellMinimum(0);
    extract->SetCellMaximum(23);

    auto parison = vtkSmartPointer<vtkGeometryFilter>(vtkGeometryFilter::New());
    parison->SetInputConnection(extract->GetOutputPort());

    auto normals2 = vtkSmartPointer<vtkPolyDataNormals>(vtkPolyDataNormals::New());
    normals2->SetInputConnection(parison->GetOutputPort());
    normals2->SetFeatureAngle(60);

    auto lut = vtkSmartPointer<vtkLookupTable>(vtkLookupTable::New());
    lut->SetHueRange(0, 2.0 / 3);

    auto parison_mapper = vtkSmartPointer<vtkPolyDataMapper>(vtkPolyDataMapper::New());
    parison_mapper->SetInputConnection(normals2->GetOutputPort());
    parison_mapper->SetLookupTable(lut);
    parison_mapper->SetScalarRange(0.12, 1.0);
    auto parsion_actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    parsion_actor->SetMapper(parison_mapper);

    auto i = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    auto w = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    i->SetRenderWindow(w);

    auto r = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    w->AddRenderer(r);
    r->AddActor(mold_actor);
    r->AddActor(parsion_actor);

    r->SetBackground(0.1, 0.3, 0);
    w->SetSize(400, 400);

    w->Render();

    auto camera = r->GetActiveCamera();
    camera->Azimuth(60.0);
    camera->Roll(-90);
    camera->Dolly(2);
    r->ResetCameraClippingRange();

    w->Render();
    i->Start();

    return 0;
}