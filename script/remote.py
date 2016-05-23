import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:%s" % 5555)

for i in range(100):
	socket.send("Hello {0}".format("." * i).encode("ascii"))
	message = socket.recv()
	print("Received reply [", message, "]")

socket.send("COMMAND /run/initialize".encode("ascii"));
response = socket.recv()
print(response)
