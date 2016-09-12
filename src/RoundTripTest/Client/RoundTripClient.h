#ifndef ROUND_TRIP_CLIENT_H
#define ROUND_TRIP_CLIENT_H

#include "../DefaultValue.h"

class RoundTripClient {
public:
	RoundTripClient();
	void setPackageSize(int package_size);
	void setDstIp(char dst_ip[]);
	void setDstPort(int dst_port);
	void roundTrip(int round_times);
private:
	int sockfd;
	int package_size;
	char dst_ip[16];
	int dst_port;
};

#endif
