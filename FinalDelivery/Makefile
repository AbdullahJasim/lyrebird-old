#NAME: 			Abdullah Jasim
#STUDENT NUMBER: 	301093885
#SFU USERNAME: 		ajasim
#LECTURE SECTION: 	D100
#INSTRUCTOR'S NAME: 	Brian G. Booth
#TA'S NAME: 		Scott Kristjanson


all:
	gcc -DMEMWATCH -DMW_STDIO server.c -o lyrebird.server
	gcc -DMEMWATCH -DMW_STDIO client.c -lm -o lyrebird.client

clean:
	rm -rf *o lyrebird.server
	rm -rf *o lyrebird.client
