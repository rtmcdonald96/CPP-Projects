#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
using namespace std;

//Prototypes
void quit(sockaddr_in);
void listFiles(sockaddr_in);
void getFile(sockaddr_in, char*);
void putFile(sockaddr_in, char*);

//Constants
const int BUFFER_SIZE = 256;

int main(int argc, char *argv[]){
  int port;
  string input;
  sockaddr_in server_address;
  socklen_t server_len;

  //Check for proper inital arguments
  if(argc != 3) {
    cout << "ERROR - use ./runClient <IP Address> <Server Port>\n";
    exit(-1);
  }

  port = atoi(argv[2]);

//Proper port number check
  if(port <= 1024 || port > 65535) {
    cout << "ERROR - Invalid port number\n";
    exit(-1);
  }

  //Create client socket to connect to server socket
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr(argv[1]);
  server_address.sin_port = htons(port);
  server_len = sizeof(server_address);


//Main Client Loop
  while(1){

    cout << "\nftp> ";
    string command;
    getline(cin, command);

    //Processes input into C string separated by whitespace
    char* buffer = const_cast<char*>(command.c_str());
    string input = strtok(buffer, " ");

    if(input == "quit"){
      quit(server_address);
      exit(0);
    }else if(input == "ls")
      listFiles(server_address);
    else if(input == "get")
      getFile(server_address, buffer);
    else if(input == "put")
      putFile(server_address, buffer);
    else
      cout << "ERROR - command not recognized\n";
  }
}

/**
* Creates the socket, connects to the server, tells the server it is quitting,
* and closes the socket.
*/
void quit(sockaddr_in address){
  int sock;
  char buffer[BUFFER_SIZE];

  //Create socket
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    cout << "ERROR - could not create socket\n";
    exit(-1);
  }

  //Connects to the server
  if(connect(sock, (sockaddr*) &address, sizeof(address)) < 0 ){
    cout << "ERROR - could not connect to socket\n";
    exit(-1);
  }

  //Tells server this client is quitting
  if(write(sock, "quit", BUFFER_SIZE) < 0){
    cout << "ERROR - could not send command to server\n";
    exit(-1);
  }

  //Hears goodbye
  if(read(sock, buffer, BUFFER_SIZE) < 0){
    cout << "ERROR - could not read message from server\n";
    exit(-1);
  }
  cout << string(buffer) << endl;

  //Closes the socket
  close(sock);

}

/*
  Ls function:
    Creates socket connection to server, writes command to request filenames
    from server's parent directory, then reads all files the server provides
*/
void listFiles(sockaddr_in address){

  int sock;
  char buffer[BUFFER_SIZE];

  //Create socket
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){

    cout << "ERROR - could not create socket\n";
    exit(-1);

  }

  //Connects to the server
  if(connect(sock, (sockaddr*) &address, sizeof(address)) < 0 ){

    cout << "ERROR - could not connect to socket\n";
    exit(-1);

  }

  //Asks the server for the file list
  if(write(sock, "ls", BUFFER_SIZE) < 0){

    cout << "ERROR - could not send command to server\n";
    exit(-1);

  }

  //Outputs the listed list
  cout << endl;
  while(read(sock, buffer, BUFFER_SIZE) > 0)
    if(*buffer != '.')
      cout << buffer << endl;

  close(sock);

}

/*
  Get function:
    Creates socket to connect to server, writes request for specific file to
    server, receives file from server if exists, checks to see if bytes recieved
    matches the original size of the file
*/
void getFile(sockaddr_in address, char* fileName){
  int sock,fd, total_bytes, received_bytes;
  int total_received = 0;
  char buffer[BUFFER_SIZE];
  char temp[BUFFER_SIZE];

  //Create Socket
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cout << "ERROR - could not create socket" << endl;
    exit(-1);
  }

  //Connect to Server
  if(connect(sock, (struct sockaddr*)&address, sizeof(address)) < 0) {
    cout << "ERROR - could not connect to server" << endl;
    exit(-1);
  }

  //Write request to server
  if(write(sock, fileName, BUFFER_SIZE) < 0) {
    cout << "ERROR - could not send to client" << endl;
    exit(-1);
  }

  fileName = strtok(fileName+4, " ");

  //Call to check if file exists
  if(read(sock, buffer, BUFFER_SIZE) < 0){
    cout << "ERROR - could not get retrieve" << endl;
    exit(-1);
  }

  //Check if file was opened successfully
  if(buffer[0] != 'Y'){
    close(sock);
    cout << "ERROR - could not open file" << endl;
    return;
  }

  //Text processing byte size from server into number
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

  //Opens file if possible
  if((fd = open(fileName, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0){
    cout << "ERROR - could not open file from server" << endl;
    exit(-1);
  }

  //Receives file content in packets
  while((received_bytes = read(sock, buffer, BUFFER_SIZE)) > 0){
    if(write(fd, buffer, received_bytes) < 0){
      cout << "ERROR - could not receive from server" << endl;
      close(fd);
      exit(-1);
    }
    total_received += received_bytes;
  }

  //Checks if received file matches orignial file size
  if(total_received == total_bytes){
    cout << "File received successfully!" << endl;
  }
  else{
    cout << "ERROR - file incomplete" << endl;
  }
  cout << "File Size: " << total_bytes << " Bytes Received: " << total_received << endl;

  close(fd);
  close(sock);

  return;
}

/*
  Put function:
    Creates socket to connect to server, writes command with file to be sent
    to server, sends original file size to server, sends file content in
    packets, then outputs if the file was sent successfully or not from
    client side.
*/
void putFile(sockaddr_in address, char* fileName){
  int sock, fd, total_bytes, send_bytes;
  int sent_bytes = 0;
  char buffer[BUFFER_SIZE];

  //Create Socket
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    cout << "ERROR - could not create socket" << endl;
    exit(-1);
  }

  //Connect to Server
  if(connect(sock, (struct sockaddr*) &address, sizeof(address)) < 0){
    cout << "ERROR - could not connect to server" << endl;
    exit(-1);
  }

  //Write command to the Socket
  if(write(sock, fileName, BUFFER_SIZE) < 0){
    cout << "ERROR - could not write to server" << endl;
    exit(-1);
  }

  fileName = strtok(fileName+4, " ");

  //Opens file if possible
  if((fd = open(fileName, O_RDONLY)) < 0 ){
    cout << "ERROR - could not open file" << endl;
    buffer[0] = 'N';
    if(write(sock, buffer, BUFFER_SIZE) < 0){
      cout << "ERROR - could not send buffer to server" << endl;
      exit(-1);
    }
    return;
  }

  //Get length of open file
  total_bytes = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  //Writes total size of original file to server
  sprintf(buffer, "Y %d", total_bytes);
  if(write(sock, buffer, BUFFER_SIZE) < 0){
    cout << "ERROR - could not send size to server" << endl;
    close(fd);
    exit(-1);
  }

  //Sends file content in packets
  while((send_bytes = read(fd, buffer, BUFFER_SIZE)) > 0){
    if(write(sock, buffer, send_bytes) < 0){
      cout << "ERROR - could not send file packet" << endl;
      close(fd);
      exit(-1);
    }
    sent_bytes += send_bytes;
  }

  //Check the total sent bytes compared to total bytes
  if(sent_bytes == total_bytes){
    cout << "File sent succesfully" << endl;
  }
  else{
    cout << "ERROR = file incomplete" << endl;
  }

  cout << "File Size: " << total_bytes << " Bytes Sent: " << sent_bytes << endl;

  close(fd);
  close(sock);

}
