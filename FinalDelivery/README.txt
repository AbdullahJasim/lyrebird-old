The program takes 2 parameters: a configuration file containing a list of input / output files, and a logging file to store the logs in. It uses server-client connection to support multiple clients.

Files included:
	client.c client.h
	connector.c connector.h
	decrypt.c decrypt.h
	establisher.c establisher.h
	filesReader.c filesFeader.h
	processManager.c processManager.h
	server.c server.h
	utilities.c utilities.h
	
Make commands:
	1. make: create the executable file
	2. make clean: remove the executable file and all .o files
	
How to call the program:
	Sever:	Into the terminal type ./lyrebird.server <parameterOne> <parameterTwo>
					Where parameterOne is the name of the configuration file and parameterTwo is the same of the logging file

	Client: Into the terminal type ./lyrebird.client <IPAddress> <PortNum>
					Where IPAddress is the IP address of the server, and the port number is the one outputted by the server


Sources used:
https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/fast-modular-exponentiation
https://en.wikipedia.org/wiki/Modular_exponentiation
https://www.youtube.com/watch?v=WiaiZmWxcck
https://www.youtube.com/watch?v=aw9wHbFTnAQ
http://web.cs.mun.ca/~michael/c/ascii-table.html
http://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
https://youtu.be/9seb8hddeK4
http://stackoverflow.com/questions/212528/get-the-ip-address-of-the-machine
http://www.linuxhowtos.org/C_C++/socket.htm
