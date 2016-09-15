import zmq
import time

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:%s" % 5555)

print("Post commend to the queue")
socket.send("COMMAND /run/verbose 1".encode("ascii"));
command_id = int(socket.recv())

print("Status of the command (immediately)")
socket.send("STATUS {0}".format(command_id).encode("ascii"))
response = socket.recv()
print(response)
time.sleep(1)


print("Status of the command (after some little delay)")
socket.send("STATUS {0}".format(command_id).encode("ascii"))
response = socket.recv()
print(response)
