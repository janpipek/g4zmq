#ifndef ZMQ_SERVER_HH
#define ZMQ_SERVER_HH

#include <memory>

#include <G4Threading.hh>

#include "RemoteSession.hh"

class ZmqServer : public BaseServer
{
public:
    ZmqServer(std::shared_ptr<RemoteSession> session) :
        fSession(session), fZmqContext(nullptr)
    { }

    // Called in the main thread
    void Start() override;

    // Called in a dedicated thread
    void Run();

private:
    std::shared_ptr<RemoteSession> fSession;

    G4Thread fThread;

    void* fZmqContext;
};

#endif