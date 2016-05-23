#include <vector>

#ifdef G4MULTITHREADED
    #include <G4MTRunManager.hh>
    using RunManager = G4MTRunManager;
#else
    #include <G4RunManager.hh>
    using RunManager = G4RunManager;
#endif

#ifdef G4UI_USE
    #include <G4UIExecutive.hh>
#endif

#include <G4String.hh>
#include <G4UImanager.hh>
#include <G4ScoringManager.hh>

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "RemoteSession.hh"
#include "ZmqServer.hh"

#include <QBBC.hh>

using namespace std;

int main(int argc, char** argv)
{
    vector<G4String> macros;    

    // Parse command line arguments
    for (int i = 1; i < argc; i++)
    {
        G4String arg = argv[i];
        macros.push_back(arg);                    
    }

    auto runManager = new RunManager();

    runManager->SetUserInitialization(new QBBC());
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new ActionInitialization());

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    for (auto macro : macros)
    {
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);
    }    

    auto session = std::make_shared<RemoteSession>();
    auto server = std::make_shared<ZmqServer>(session);
    session->SessionStart(server);

    delete runManager;
    return 0;
}