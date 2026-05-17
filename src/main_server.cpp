#include "Ame_http_tcpServer.h"
int main(){
	http::TCPServer server = TCPServer("0.0.0.0", 8080);
	return 0;
}
