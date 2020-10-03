import socket
import huffman

PORT=9009
IP=''
conn=(IP,PORT)

if __name__ == "__main__":

	s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect(conn)

	filename=input("enter file name: ")
	s.send(filename.encode("utf-8"))
	flag=int(s.recv(1).decode("utf-8"))
	if(not flag):
		print("file was not found in the server")
		quit()

	l=filename.split(".")
	# print(l)
	huff_filename=l[0]+"_recieved.huff"
	file=open(huff_filename,"wb") 
	data=s.recv(1024)
	while data:
		file.write(data)
		data = s.recv(1024)
	file.close()

	huff=huffman.Huffman(huff_filename)
	huff.decode(l[0]+"_recieved.txt")

	s.close()