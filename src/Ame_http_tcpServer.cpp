#include "Ame_http_tcpServer.h"
#include<iostream>
#include<sstream>
#include<unistd.h>

namespace {
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
		startServer();
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
		return 0;
	}

	void TCPServer::closeServer(){
		close(m_socket);
		close(m_new_socket);
		exit(0);
	}
}
