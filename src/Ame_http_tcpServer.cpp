#include "Ame_http_tcpServer.h"
#include<iostream>
#include<sstream>
#include<unistd.h>

namespace {
	const int BUFFER_SIZE = 30720;
	void log(const std::string &message){
		std::cout << message << std::endl;
	}

	void exitWithError(const std::string &errorMessage){
		log("Error: " + errorMessage);
		exit(1);
	}
}

namespace http{
	TCPServer::TCPServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(), m_incomingM	essage(), m_socketAddress(), m_scoketAddress_len(sizeof(m_socketAddress)), m_serverMessage(buildResponse()) {
		m_socketAddress.sin_family = AF_INET;     // sin_family is a member variable of IPV4 socket address structure in C and C++. Specifies what address family that the socket will use.
		m_socketAddress.sin_port = htons(m_port); // 16 bit integer field inside IPV4 socket address structure. htons() convert bytes to TCP/IP network byte order.
		m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str()); // Converts a IP address string into a binary format understood by OS.

		if(startServer() != 0){
			std::ostringstream ss;
			ss << "Failed to start server with PORT: " << 	ntohs(m_socketAddress.sin_port); // ntohs is network to host short. To convert network byte order to host byte order.
			log(ss.str());
		};
	}
	TCPServer::~TCPServer(){
		closeServer();
	}

	// Defining Start Server and Close Server
	int TCPServer::startServer(){
		m_socket = socket(AF_INET, SOCK_STREAM, 0);   // Creating a socket
		if(m_socket < 0){
			exitWithError("Cannot Create Socket");
			return 1;
		}

		if(bind(m_socket, (sockaddr *) &m_socketAddress, m_socketAddress_len) < 0){    // Bind Socket with the socket address
			exitWithError("Cannot connect Socket with address");
			return 1;
		}
		return 0;
	}

	void TCPServer::closeServer(){
		close(m_socket);
		close(m_new_socket);
		exit(0);
	}

	void TCPServer::startListen(){
		if(listen(m_socket, 20) < 0){ 				// Listen is a syscall for listening to socket Request
			exitWithError("Socket Lenght Exceeded");
		}

		std::ostringstream ss;
		ss << "\n Listening on Address" << inet_ntoa(m_socketAddress.sin_addr) << "Port: " << ntohs(m_socketAddress.sin_port) << " \n\n";
		log(ss.str());

		int bytesReceived;


		while(true){
			log("========= Waiting for a new connection =========\n\n\n");
			acceptConnection(m_new_socket);

			char buffer[BUFFER_SIZE] = {0};
			bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE); // read() is a syscall
			if(bytesReceiver < 0){
				exitWithError("Failed to read bytes from client socket connection");
			}

			std::ostringstream ss;
			ss << "================= Received Request from client =============\n\n";
			log(ss.str());
		}

	}

	void TCPServer::acceptConnection(int &new_socket){
		new_socket = accept(m_socket, (sockaddr *) &m_socketAddress, &m_socketAddress_len);
		if(new_socket < 0){
			std::ostringstream ss;
			ss << "Server Failed to accept incoming connection of Address: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);
			exitWithError(ss.str());
		}
	}

	std::string TCPServer::buildResponse(){
		std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
		std::ostringstream ss;
		ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n";
		return ss.str();
	}


	void TCPServer::sendResponse(){
		long bytesSent;
		bytesSent = write(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size()); // write is a syscall in linux

		if(bytesSent == m_serverMessage.size()){
			log("========== Server Response Sent to Client =============\n\n\n");
		}
		else{
			log("Error Sending response to Client");
		}
	}

}
