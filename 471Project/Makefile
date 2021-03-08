all: server.o client.o
	g++ src/server/server.o -o runServer
	g++ src/client/client.o -o runClient
	rm src/server/server.o src/client/client.o

server.o:
	g++ -c src/server/server.cpp -o src/server/server.o

client.o:
	g++ -c src/client/client.cpp -o src/client/client.o

tar:
	tar cvf project1.tar src/ Makefile README.md ProtocolDesign.docx

clean:
	rm runServer runClient
