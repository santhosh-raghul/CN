class huffman_tree:

	def __init__(self,chars,freq,left=None,right=None):
		self.chars=chars
		self.freq=freq
		self.left=left
		self.right=right

	def __str__(self):
		return "%s %d"%(self.chars,self.freq)

	def getcodes(self):

		codes=dict()

		if(self.left.left==None):
			codes[self.left.chars]="0"
		else:
			left_codes=self.left.getcodes()
			for key in left_codes.keys():
				codes[key]="0"+left_codes[key]

		if(self.right.left==None):
			codes[self.right.chars]="1"
		else:
			right_codes=self.right.getcodes()
			for key in right_codes.keys():
				codes[key]="1"+right_codes[key]

		return codes

def get_key(dictionary,value):
	for key,val in dictionary.items():
		if val==value:
			return key
	return None

def return_min(nodes):
	min=nodes[0]
	for node in nodes:
		if(node.freq<min.freq):
			min=node
	return min
	
def create_huffman_tree(nodes):
	
	if(len(nodes)==1):
		return nodes[0]

	min1=return_min(nodes)
	nodes.remove(min1)
	min2=return_min(nodes)
	nodes.remove(min2)
	new=huffman_tree(min1.chars+min2.chars,min1.freq+min2.freq,min1,min2)
	nodes.append(new)
	return create_huffman_tree(nodes)

class Huffman:
	
	def __init__(self,filename):
		self.filename=filename

	def encode(self,output_filename):
		self.code=self.create_code()
		self.__create_encoded_file(self.__get_bit_string_from_txt(),output_filename)

	def decode(self,output_filename):
		self.code=self.__get_code_from_file()
		self.__create_decoded_file(self.__get_bit_string_from_huff(),output_filename)

	def __create_decoded_file(self,enc_seq,output_filename):
		output_file=open(output_filename,'w')
		curr=""
		while True:
			curr=curr+enc_seq[0]
			enc_seq=enc_seq[1:]
			if(curr in self.code.keys()):
				char=self.code[curr]
				if(char=="{end}"):
					break
				# elif(char=='\n'):
					# output_file.write('\r')
				output_file.write(char)
				curr=""
		output_file.close()

	def __get_code_from_file(self):
		code=dict()
		file=open(self.filename,"rb")
		self.num_codes=int(file.readline().decode("ascii")[0:-1])
		end_code=file.readline().decode("ascii")[0:-1]
		for i in range(self.num_codes-1):
			line=file.readline().decode("ascii")[0:-1].split(' ')
			code[line[0]]=chr(int(line[1]))
		code[end_code]="{end}"
		file.close()
		return code

	def __get_bit_string_from_huff(self):
		file=open(self.filename,'rb')
		n=int(file.readline().decode("ascii")[0:-1])
		for i in range(n):
			file.readline()
		file_content=file.read()
		file.close()
		seq=''
		for byte in file_content:
			seq=seq+'{0:08b}'.format(byte)
		return seq

	def create_code(self):
		file=open(self.filename,'r')
		file_content=file.read()
		file.close()
		freq=dict()
		for ch in file_content:
			if(ch in freq.keys()):
				freq[ch]+=1
			else:
				freq[ch]=1
		freq["{end}"]=1
		nodes=list()
		for key in freq.keys():
			nodes.append(huffman_tree(key,freq[key]))
		root=create_huffman_tree(nodes)
		return root.getcodes()

	def __get_bit_string_from_txt(self):
		file=open(self.filename,'r')
		file_content=file.read()
		file.close()
		seq=''
		for ch in file_content:
			seq=seq+self.code[ch]
		seq=seq+self.code["{end}"]
		return seq

	def __create_encoded_file(self,enc_seq,output_filename):
		header='%d\n'%(len(self.code))
		keys=list(self.code.keys())
		keys.remove("{end}")
		header=header+"%s\n"%self.code["{end}"]
		for ch in keys:
			header=header+"%s %d\n"%(self.code[ch],ord(ch))
		byte_array=[]
		while(len(enc_seq)>=8):
			byte_array.append(int(enc_seq[0:8],2))
			enc_seq=enc_seq[8:]
		if(len(enc_seq)!=0):
			byte_array.append(int(enc_seq+"0"*(8-len(enc_seq)),2))
		file=open(output_filename,"wb")
		file.write(bytes(header,"ascii"))
		file.write(bytearray(byte_array))
		file.close()