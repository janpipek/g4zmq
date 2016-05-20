#ifndef ZMQ_SERVER_HH
#define ZMQ_SERVER_HH

#include <memory>

#include "RemoteSession.hh"

class ZmqServer : public BaseServer
{
public:
    ZmqServer(std::shared_ptr<RemoteSession> session) :
        fSession(session)
    { }

    void Start() override;

private:
    std::shared_ptr<RemoteSession> fSession;
};

#endif