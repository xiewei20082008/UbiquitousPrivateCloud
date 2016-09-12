#ifndef ROUND_TRIP_SERVER_H
#define ROUND_TRIP_SERVER_H

#include "../DefaultValue.h"

class RoundTripServer {
public:
	static const int BACKLOG = SERVER_BACKLOG;
	RoundTripServer();
	void setListenerPort(int listener_port);
	void start();
private:
	int sockfd;
};

#endif
