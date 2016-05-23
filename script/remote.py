import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:%s" % 5555)

socket.send("COMMAND /run/verbose 1".encode("ascii"));
command_id = int(socket.recv())

socket.send("STATUS {0}".format(command_id).encode("ascii"))
response = socket.recv()

print(response)