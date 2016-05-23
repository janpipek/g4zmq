#ifndef REMOTE_SESSION_HH
#define REMOTE_SESSION_HH

#include <memory>
#include <vector>
#include <deque>

#include <G4UImanager.hh>

class BaseServer
{
public:
    virtual void Start() = 0;
};

class RemoteSession
{
public:
    RemoteSession();

    virtual void SessionStart(std::shared_ptr<BaseServer> server);

    G4int QueueCommand(G4String command);

    G4int GetCommandStatus(G4int commandId);

    G4bool PopCommand(G4String& commandRef);

    void Exit();

    const G4int QUEUED = -1;
    const G4int EXECUTING = -2;
    const G4int UNKNOWN = -3;

protected:
    std::deque<G4String> fCommandQueue;

    std::vector<G4int> fCommandStatuses;

    G4int fLastCommandQueued;

    G4int fLastCommandExecuted;

    G4float fSleepInterval;    

    std::shared_ptr<BaseServer> fServer;

    G4bool fEnd;
};

#endif