#include "RoundTripServer.h"
#include "../DefaultValue.h"
#include <stdio.h>

int main()
{
	RoundTripServer rts;
	rts.setListenerPort(SERVER_PORT);
	rts.start();

	return 0;
}
