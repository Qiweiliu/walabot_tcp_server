#include "walabot.h"
#include <iostream>
#include "tcp_server.h"
void main() {
	while (true) {
		tcp_server();
		disconnect();
	}
}