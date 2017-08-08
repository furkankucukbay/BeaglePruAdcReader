bufferSize = 10
bufferByteSize = bufferSize * 4

#print("Hello World\n")
#print(bufferSize)

#file = open("data.txt", "w")
#file.write("G")

#file2 = open("testfile.txt", "r")
#print (file2.read()) 

#file.close()
#file2.close()

#count = 0
#while (count < 10):
#	with open("data.txt", "a") as file:
#		file.write("1")
#	count = count + 1

#with open( "/dev/rpmsg_pru30", buffering = bufferByteSize) as f:
#	for line in f:
#		print line

#count = 0
#while (count < bufferSize):
#	print(count)
#	count = count + 1


with open("/dev/rpmsg_pru31", "w") as file:
	file.write("S")

with open("/dev/rpmsg_pru30", buffering = bufferByteSize) as f:
        for line in f:
		print line


