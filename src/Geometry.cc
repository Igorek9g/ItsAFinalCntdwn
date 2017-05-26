//
// Created by idalov on 10.05.17.
//

#include <Geometry.hh>
#include <G4PVPlacement.hh>
#include <G4AssemblyVolume.hh>
#include <G4Tubs.hh>
#include <G4UImanager.hh>
#include <G4RunManager.hh>
#include <G4GeometryManager.hh>
#include <G4SolidStore.hh>
#include <G4SubtractionSolid.hh>

Geometry::Geometry(){

    nist = G4NistManager::Instance();

    det_Mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");

    i=1;

    i2 = 0;

    detMes = new Mes(this);
}

Geometry::~Geometry(){
    delete world;
    delete world_log;
    delete world_VP;
}

G4VPhysicalVolume* Geometry::Construct() {

    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    G4double size = 50*m;
    world_mat = nist->FindOrBuildMaterial("G4_AIR");
    world = new G4Box("world", size/2., size/2.,size/2.);
    world_log = new G4LogicalVolume(world, world_mat, "world_log");
    world_VP = new G4PVPlacement(0,G4ThreeVector(),world_log,"world_PV",0,false,0);

    box1 = new G4Box("box1", 1 *m, 1 *m, 1 *m);
    tube1 = new G4Tubs("tube1", 0, 2 *m, 4 *m, 0, 180 *deg);
    tube2 = new G4Tubs("tube2", 0, 0.5 *m, 2 *m, 0, 360 *deg);

    box1_log  = new G4LogicalVolume(box1,det_Mat,"log_tubs");
    tube1_log = new G4LogicalVolume(tube1,det_Mat,"log_tubs");
    tube2_log = new G4LogicalVolume(tube2,det_Mat,"log_tubs");

    vic1 = new  G4SubtractionSolid("vic1",box1,tube2,0,G4ThreeVector(0,0,0));
    vic1_log = new G4LogicalVolume(vic1,det_Mat,"log_tubs");

    G4AssemblyVolume* box_ass = new G4AssemblyVolume();



    G4ThreeVector vect1(0,0,0);

    if (i2 == 0){
        box_ass->AddPlacedVolume(box1_log, vect1, 0);
    }
    else{
        box_ass->AddPlacedVolume(vic1_log, vect1, 0);
    }


    G4ThreeVector vect2(4 *m,0,0);
    box_ass->AddPlacedVolume(tube1_log, vect2, 0);

    G4ThreeVector vect3(0,0,0);
    box_ass->AddPlacedVolume(vic1_log, vect3, 0);

for (int counter = 0; counter < i; counter ++ ) {
    G4ThreeVector vect4(counter * 10 *m,0,0);
    box_ass->MakeImprint(world_log, vect4, 0, 0, false);
}


    return world_VP;
}

Mes::Mes(Geometry* geom):detGeom(geom) {
    fDirectory = new G4UIdirectory (" MY_COMMANDS/");
    change_Mat = new G4UIcommand (" MY_COMMANDS/change_Mat", this);
    dirka = new G4UIcmdWithADouble (" MY_COMMANDS/dirka", this);
    dvwt = new G4UIcmdWithADouble (" MY_COMMANDS/dvwt", this);
}

void Mes::SetNewValue(G4UIcommand* cmd, G4String newvalue){
    if (cmd == change_Mat){
        detGeom->SetMat("G4_Fe");
    }

    if (cmd == dirka){
        detGeom->SetDirka(dirka->GetNewDoubleValue(newvalue));
    }

    if (cmd == dvwt){
        detGeom->Setdvwt(dvwt->GetNewDoubleValue(newvalue));
    }
}

void Geometry::Setdvwt(G4double newi){

    i = newi;

    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->ReinitializeGeometry();
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/geometry/set/visibility world_log 0 false");

}

void Geometry::SetDirka(G4double newi2){

    i2 = newi2;

    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->ReinitializeGeometry();
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/geometry/set/visibility world_log 0 false");

}

void Geometry::SetMat (G4String newMat){

    det_Mat = nist->FindOrBuildMaterial(newMat);

    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->ReinitializeGeometry();
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/geometry/set/visibility world_log 0 false");

}

Mes::~Mes(){}