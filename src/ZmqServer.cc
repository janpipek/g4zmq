#include "ZmqServer.hh"

#include <iostream>
#include <zmq.h>

using namespace std;

void runServer(void* arg)
{
    ZmqServer* server = (ZmqServer*)arg;
    server->Run();
}

void ZmqServer::Start()
{
    // Lock
    if (fZmqContext)
    {
        // Error
    }
    cout << "ZmqServer::Start() in main thread." << endl;
    G4THREADCREATE(&fThread, (void* (*)(void*))runServer, this);
}

void ZmqServer::Run()
{
    // Check for main thread => Error
    fZmqContext = zmq_ctx_new();
    cout << "ZmqServer::Run() in child thread." << endl;

    void* responder = zmq_socket(fZmqContext, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    if (rc != 0)
    {
        exit(-1);
    }

    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received Hello\n");
        // sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5, 0);
    }
    // return 0;
}