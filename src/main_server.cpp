#include "Ame_http_tcpServer.h"
int main(){
	http::TCPServer server("0.0.0.0", 8080);
	server.startListen();
	return 0;
}
