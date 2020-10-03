from math import log2,ceil

class Huffman:

	def __init__(self,filename):
		self.filename=filename

	def encode(self,output_filename):
		self.code=self.__create_code()
		self.__create_encoded_file(self.__get_bit_string_from_txt(),output_filename)

	def decode(self,output_filename):
		self.code=self.__get_code_from_file()
		self.__create_decoded_file(self.__get_bit_string_from_huff(),output_filename)

	def __create_decoded_file(self,enc_seq,output_filename):
		output_file=open(output_filename,'w')
		while True:
			char=self.code[int(enc_seq[0:self.code_length],2)]
			enc_seq=enc_seq[self.code_length:]
			if(char=="end"):
				break
			# elif(char=='\n'):
				# output_file.write('\r')
			output_file.write(char)
		output_file.close()

	def __get_bit_string_from_huff(self):
		file=open(self.filename,'rb')
		file.readline();file.readline();file.readline()
		file_content=file.read()
		file.close()
		seq=''
		for byte in file_content:
			seq=seq+'{0:08b}'.format(byte)
		return seq

	def __get_code_from_file(self):
		code=dict()
		file=open(self.filename,"rb")
		self.code_length=int(file.readline().decode("ascii")[0:-1])
		end_code=int(file.readline().decode("ascii")[0:-1])
		char_list=file.readline().decode("ascii")[0:-1].split(' ')
		for i in range(end_code):
			code[i]=chr(int(char_list[i]))
		code[end_code]="end"
		file.close()
		return code

	def __create_code(self):
		code=dict()
		file=open(self.filename,'r')
		file_content=file.read()
		file.close()
		i=0
		for ch in file_content:
			if ch not in code.keys():
				code[ch]=i
				i+=1
		code["end"]=i
		self.code_length=ceil(log2(len(code.keys())))
		bin_code=dict()
		reqd_format="{0:0%db}"%(self.code_length)
		for ch in code.keys():
			bin_code[ch]=reqd_format.format(code[ch])
		return bin_code

	def __get_bit_string_from_txt(self):
		file=open(self.filename,'r')
		file_content=file.read()
		file.close()
		seq=''
		for ch in file_content:
			seq=seq+self.code[ch]
		seq=seq+self.code["end"]
		return seq

	def __create_encoded_file(self,enc_seq,output_filename):
		header='%d\n%d\n'%(self.code_length,int(self.code["end"],2))
		keys=list(self.code.keys())
		keys.remove('end')
		for ch in keys:
			header=header+"%d "%(ord(ch))
		header=header[0:-1]+'\n'
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
