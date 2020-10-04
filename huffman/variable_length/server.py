import socket
import huffman

PORT=9009
IP=''
conn=(IP,PORT)

if __name__ == "__main__":

	s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind(conn)
	s.listen(5)
	c,addr=s.accept()

	filename=c.recv(10).decode("utf-8")
	try:
		file=open(filename,"rb")
	except FileNotFoundError:
		print("file '%s' not found"%filename)
		c.send("0".encode("utf-8"))
		quit()
	c.send("1".encode("utf-8"))
	file.close()

	huff=huffman.Huffman(filename)
	huff.encode("a.huff")

	file=open("a.huff","rb")
	data=file.read(1024)
	while data:
		c.send(data)
		data=file.read(1024)   
	c.send(data)

	file.close()
	c.close()