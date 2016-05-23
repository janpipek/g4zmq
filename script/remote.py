import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:%s" % 5555)
for i in range(10000):
	socket.send("Hello".encode("ascii"))
	message = socket.recv()
	print("Received reply [", message, "]")