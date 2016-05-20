#include "RemoteSession.hh"

#include <G4Threading.hh>
#include <G4AutoLock.hh>

namespace { G4Mutex sessionMutex = G4MUTEX_INITIALIZER; }

using namespace std;

RemoteSession::RemoteSession() :
    fLastCommandQueued(-1), fLastCommandExecuted(-1),
    fSleepInterval(10000)
{

}

void RemoteSession::SessionStart(shared_ptr<BaseServer> server)
{
    server->Start(); // TODO: Do we need to keep it?
    G4UImanager* uiManager = G4UImanager::GetUIpointer();

    while (true)
    {
        G4String command;
        if (!PopCommand(command))
        {
            usleep(fSleepInterval);
            continue;
        }
        else
        {
            fCommandStatuses[fLastCommandExecuted + 1] = EXECUTING;
        }
        G4int result = uiManager->ApplyCommand(command);
        fLastCommandExecuted++;
        fCommandStatuses[fLastCommandExecuted] = result;
    }
}

G4int RemoteSession::QueueCommand(G4String command)
{
    G4AutoLock lock(&sessionMutex);
    if (command.empty())
    {
        return -1;
    }
    else
    {
        fCommandQueue.push_back(command);
        fCommandStatuses.push_back(QUEUED);
        fLastCommandQueued++;
    }
    return fLastCommandQueued;  
}

G4int RemoteSession::GetCommandStatus(G4int commandId)
{
    G4AutoLock lock(&sessionMutex);
    if ((fLastCommandQueued < commandId) || (commandId < 0))
    {
        return UNKNOWN;
    }
    else
    {
        return fCommandStatuses[commandId];
    }
}

G4bool RemoteSession::PopCommand(G4String& commandRef)
{
    G4AutoLock lock(&sessionMutex);
    if (fCommandQueue.empty())
    {
        return false;
    }
    else
    {
        commandRef = fCommandQueue.front();
        fCommandQueue.pop_front();
        return true;
    }
}