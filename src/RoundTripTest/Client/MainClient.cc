#include "RoundTripClient.h"
#include "Timer.h"
#include "../DefaultValue.h"


int main()
{
	printf("[ Package size: %d ]\n", PACKAGE_SIZE);
	printf("[ Round times: %d ]\n", ROUND_TIMES);
	RoundTripClient rtc;
	rtc.setPackageSize(PACKAGE_SIZE);
	rtc.setDstIp(REMOTE_IP);
	rtc.setDstPort(REMOTE_PORT);

	Timer t;

	t.start();

	rtc.roundTrip(ROUND_TIMES);

	t.end();
	t.showInterval();
	return 0;
}
