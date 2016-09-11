#include <RoundTripServer.h>

int main()
{
  RoundTripServer rts = new RoundTripServer();
  rts.setListenerPort(999);
  rts.start();

  return 0;
}
