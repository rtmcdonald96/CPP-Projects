#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>
using namespace std;

//Prototypes
void quitHandler(int);
void listFilesHandler(int);
void getFileHandler(int, char*);
void putFileHandler(int, char*);

//Constants
const int MAX_CONNECTIONS = 100;
const int BUFFER_SIZE = 256;

int main(int argc, char *argv[]){
  int port;
  int server_socket, client_socket;
  sockaddr_in server_address, client_address;
  socklen_t server_len, client_len;
  char input[BUFFER_SIZE];

  // Check for proper initial arguments
  if(argc != 2){
    cout << "ERROR - use ./runServer <port argument>\n";
    exit(-1);
  }

  port = atoi(argv[1]);

  //Proper port number check
  if(port <= 1024 || port > 65535){
    cout << "Port number must within range\n";
    exit(-1);
  }

  //Create the socket
  if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    cout << "ERROR - could not create socket\n";
    exit(-1);
  }

  //Prepare socket address
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);
  server_len = sizeof(server_address);

  //Bind socket address
  if((bind(server_socket, (sockaddr*)&server_address, server_len)) < 0){
    cout << "ERROR - could not bind socket address\n";
    exit(-1);
  }

  //Listen to the socket, wait for client - possible delete
  if(listen(server_socket, MAX_CONNECTIONS) < 0){
    cout << "ERROR - Listening error\n";
    exit(-1);
  }

  //Main Server Loop
  while(true){

    client_len = sizeof(client_address);

    //Accept connection from client
    if((client_socket = accept(server_socket, (sockaddr*) &client_address, &client_len)) < 0){
        cout << "ERROR - could not accept the connection\n";
	      exit(-1);
      }

    //Reads command from client
    if(read(client_socket, input, BUFFER_SIZE) < 0){
      cout << "ERROR - could not read command from client\n";
      exit(-1);
    }

    //Processes text to only read first word
    string command = strtok(input, " ");

    if(command == "quit")
      quitHandler(client_socket);
    else if(command == "ls")
      listFilesHandler(client_socket);
    else if(command == "get")
      getFileHandler(client_socket, strtok(input+4, " "));
    else if(command == "put")
      putFileHandler(client_socket, strtok(input+4, " "));
    else{
      cout << "ERROR - Command from client not recognized\n";
      close(client_socket);
    }

  }

}
/*
  Quit function:
    Writes "goodbye" to the client to verify the connection is closing,
    then closes the client.
*/
void quitHandler(int client){

  if(write(client, "Goodbye", 7) < 0){
    cout << "ERROR - could not write to client\n";
    exit(-1);
  }
  close(client);
}

/*
  Ls function:
    Reads all files in the parent directory, then outputs those
    filenames onto the client.
*/
void listFilesHandler(int client){

  struct dirent *direntPtr = NULL;
  DIR *dir = NULL;
  char buffer[BUFFER_SIZE];

  //Write to dir
  if((dir = opendir(".")) == NULL){

    cout << "opendir error\n";
    exit(-1);

  }

//Reads all files in directory
  while((direntPtr = readdir(dir)) != NULL){

    //Writes file names to buffer
    if(sprintf(buffer, direntPtr->d_name, BUFFER_SIZE) < 0){

      cout << "SPRINTF error\n";
      exit(-1);

    }

    //Prints buffer with file names onto client
    if(write(client, buffer, BUFFER_SIZE) < 0){

      cout << "write error\n";
      exit(-1);

    }

  }

  closedir(dir);
  close(client);

}

/*
  Get function:
    opens file that client requests, reads the length in bytes, sends file
    in packets, checks to see if the sent file byte size matches the original
    size, and outputs if it was successful or not.
*/
void getFileHandler(int client, char* fileName){
  int fd, total_bytes, send_bytes;
  int sent_bytes = 0;
  char buffer[BUFFER_SIZE];

  if((fd = open(fileName, O_RDONLY)) < 0) {
    cout << "ERROR - could not open file" << endl;
    buffer[0]='N';
    if(write(client, buffer, BUFFER_SIZE) < 0) {
      cout << "ERROR - could not write to file" << endl;
      exit(-1);
    }
    return;
  }

  //Length of file
  total_bytes = lseek(fd,0,SEEK_END);
  lseek(fd,0,SEEK_SET);

  sprintf(buffer, "Y %d\n", total_bytes);
  if(write(client, buffer, BUFFER_SIZE) < 0){
    cout << "ERROR - could not write to client" << endl;
    close(fd);
    exit(-1);
  }

//Send to client
  while((send_bytes = read(fd, buffer, BUFFER_SIZE)) > 0){
    if(write(client, buffer, send_bytes) < 0){
      cout << "ERROR - could not send to client" << endl;
      close(fd);
      exit(-1);
    }
    sent_bytes += send_bytes;
  }

//Checks if sent file size matches original file size
  if(sent_bytes == total_bytes){
    cout << "File sent successfully!" << endl;
  }
  else{
    cout << "ERROR - file sent incomplete" << endl;
  }
  cout << "File Size: " << total_bytes << " Bytes Sent: " << sent_bytes << endl;

  close(fd);
  close(client);
}

/*
  Put function:
    Opens file received from client, receives packets for file content,
    checks to see if expected file size matches the received amount
    and ouputs success or corruption.
*/
void putFileHandler(int client, char* fileName){

  int fd, received_bytes, total_bytes;
  int total_received = 0;
  char buffer[BUFFER_SIZE];
  char temp[BUFFER_SIZE];

  //Opens file if possible
  if((fd = open(fileName, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0){
    cout << "ERROR - could not open file from client" << endl;
    exit(-1);
  }

  //Reads file
  if(read(client, buffer, BUFFER_SIZE) < 0){
    cout << "ERROR - read error" << endl;
    exit(-1);
  }

  //Writes character code at the beginning of buffer to let client know success
  if(buffer[0] != 'Y'){
    close(client);
    cout << "ERROR -  received buffer error" << endl;
    exit(-1);
  }

  //Processes file size recived from client into number format
  int j = 0;
  for(int i = 2; i < sizeof(buffer); i++){
    if(isdigit(buffer[i])){
      temp[j] = buffer[i];
      j++;
    }
    else if(j != 0){
      break;
    }
  }
  total_bytes = atoi(temp);

  //Receives content from file in packets from client
  while((received_bytes = read(client, buffer, BUFFER_SIZE)) > 0){
    if(write(fd, buffer, received_bytes) < 0){
      cout << "ERROR - could not receive from client" << endl;
      close(fd);
      exit(-1);
    }
    total_received += received_bytes;
  }

  // Check the total bytes of received data
  if(total_received == total_bytes) {
      cout << "File received successfully!" << endl;
  }
  else {
      cout << "ERROR - file incomplete" << endl;
  }

  cout << "File Size: " << total_bytes << " Bytes Sent: " << total_received << endl;

  close(fd);
  close(client);

}
