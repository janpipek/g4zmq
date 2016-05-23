#include "ZmqServer.hh"

#include <iostream>
#include <sstream>

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
    int rc = zmq_bind (responder, "tcp://127.0.0.1:5555");
    if (rc != 0)
    {
        exit(-1);
    }

    char* buffer = (char*)malloc(fBufferSize);

    while (1) {
        int received = zmq_recv (responder, buffer, fBufferSize, 0);
        G4String message(buffer, received);
        G4String response = OnMessage(message);
        zmq_send (responder, response.c_str(), response.size(), 0);
    }

    free(buffer);
}

G4String ZmqServer::OnMessage(const G4String& message)
{
    G4int spacePos = message.find(' ');

    G4String function;
    G4String argument = "";

    function = message.substr(0, spacePos);
    if (spacePos != G4String::npos)
    {
        argument = message.substr(spacePos + 1);
    }

    cout << message << endl;

    ostringstream oss;

    if (function == "COMMAND")
    {
        G4int commandId = fSession->QueueCommand(argument);
        oss << commandId;
    }
    else if (function == "STATUS")
    {
        istringstream iss(argument);
        G4int commandId;
        iss >> commandId;

        G4int status = fSession->GetCommandStatus(commandId);
        oss << status;
    }
    else if (function == "EXIT")
    {
        fSession->Exit();
        oss << "Exit";
    }
    else
    {
        cout << "Unknown command" << endl;
        oss << "Unknown command";
    }
    return oss.str();
}