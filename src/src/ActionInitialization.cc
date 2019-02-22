#include "ActionInitialization.hh"

// ....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization(DetectorConstruction *detector) : G4VUserActionInitialization(),
                                                                             fDetector(detector)
{
}

// ....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization() = default;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction);
}

// ....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
ActionInitialization::Build() const
{
    auto *primary = new PrimaryGeneratorAction();
    SetUserAction(primary);
    auto *runAction = new RunAction();
    SetUserAction(runAction);
    auto *event = new EventAction();
    SetUserAction(event);

    //    if (Settings::efield_status == Settings::ON)
    //        {
    //    G4bool use_stckg_act_tmp = Settings::USE_STACKING_ACTION; // variable for debug

    Settings::USE_STACKING_ACTION = false;

    if (Settings::USE_STACKING_ACTION)
    {
        G4UserStackingAction *stackingAction = new BaseStackingAction();
        SetUserAction(stackingAction);
    }

    //        }

    //  TrackingAction *trackingAction = new TrackingAction(fDetector);
    //  SetUserAction(trackingAction);
    auto *steppingAction = new SteppingAction(fDetector, event);
    SetUserAction(steppingAction);
}

// ....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
