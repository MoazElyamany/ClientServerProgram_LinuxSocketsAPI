//student_name: write_your_name

/* Client:
   1. define an (IP address + port number) for the server to connect to
   2. create a socket (client socket)
   3. establish a connection to the server
   4. send and receive data to and from the server
   5. close the socket
*/

//include the needed headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>

//define some macros
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)

int main() {

	 //set the following
	 const char* server_hostname = "127.0.0.1";
         const char* server_portnum = "8090";


	 //configure a remote address for connection
	 printf("Configuring remote address...\n");
	 struct addrinfo hints;
	 memset(&hints, 0, sizeof(hints));
	 hints.ai_socktype =SOCK_STREAM;
	 struct addrinfo *peer_address;
	 if (getaddrinfo(server_hostname, server_portnum, &hints, &peer_address)) {
		 fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
		 return 1;
	 }

	 //create clietnt socket
	 printf("Creating socket...\n");
	 SOCKET socket_peer;
	 socket_peer = socket(peer_address->ai_family, peer_address->ai_socktype, peer_address->ai_protocol);
	                               //find the missing function name
	 if (!ISVALIDSOCKET(socket_peer)) {
		 fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
		 return 1;
	 }

	 //Establish a connection to the remote server
	 printf("Connecting...\n");
	 if (connect(socket_peer, peer_address->ai_addr, peer_address->ai_addrlen)) {
	                                                 //find the missing function and parameter names
		 fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
		 return 1;
	 }
	 freeaddrinfo(peer_address);

	 printf("Connected.\n");

	 //send request to server
	 printf("Sending request...\n");
	 char request[1024];
	 printf("Enter your name: ");
	 scanf("%s", request);
	 strcat(request, "\n");
         int bytes_sent = send(socket_peer, request, strlen(request), 0);
	 printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(request));

	 //receive response from server
	 char response[1024];
	 int bytes_received = recv(socket_peer, response, 1024, 0);
	 if (bytes_received < 1)
	 {
		 printf("Connection closed by peer.\n");
         }
	 printf("Received (%d bytes): %.*s", bytes_received, bytes_received, response);

	 //close the client connection
	 printf("Closing socket...\n");
         CLOSESOCKET(socket_peer);

	 printf("Finished.\n");
         return 0;
}













