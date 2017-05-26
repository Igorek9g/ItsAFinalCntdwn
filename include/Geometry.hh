//
// Created by idalov on 10.05.17.
//

#ifndef FINAL_GEOMETRY_HH
#define FINAL_GEOMETRY_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4Box.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4AssemblyVolume.hh>
#include <G4Tubs.hh>
#include <G4SubtractionSolid.hh>
#include <G4PVPlacement.hh>
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"

class Mes;

class Geometry: public G4VUserDetectorConstruction {
private:
    G4Box               *world;
    G4LogicalVolume     *world_log;
    G4VPhysicalVolume   *world_VP;
    G4NistManager*      nist;
    G4Material*         world_mat;
    G4Box*              box1;
    G4Tubs*             tube1;
    G4Tubs*             tube2;
    G4LogicalVolume* box1_log;
    G4LogicalVolume* tube1_log;
    G4LogicalVolume* tube2_log;
    G4LogicalVolume*   vic1_log;
    G4double i;
    G4double i2;
    G4SubtractionSolid* vic1;
    G4PVPlacement* box1_pv;
    G4ThreeVector vic1_v;


    virtual G4VPhysicalVolume *Construct();

public:
    Geometry();

    ~Geometry();

    void SetMat (G4String newMat);
    void SetDirka(G4double newi2);
    void Setdvwt (G4double newi);

    Mes* detMes;
    G4Material* det_Mat;
};

class Mes : public G4UImessenger{
public:
    Mes(Geometry* geom);

    ~Mes();

    void SetNewValue(G4UIcommand* cmd, G4String);

private:
    Geometry* detGeom;
    G4UIdirectory* fDirectory;
    G4UIcommand* change_Mat;
    G4UIcmdWithADouble* dirka;
    G4UIcmdWithADouble* dvwt;

};


#endif //FINAL_GEOMETRY_HH
