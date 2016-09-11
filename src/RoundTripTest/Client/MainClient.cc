#include <RoundTripClient.h>
#include <Timer.h>

#define ROUND_TIMES 10000

int main()
{
  RoundTripClient rtc = new RoundTripClient();
  rtc.setDstIp("127.0.0.1");
  rtc.setDstPort();

  Timer t = new Timer();

  t.start();

  rtc.roundTrip(ROUND_TIMES);

  t.end();
  t.showInterval();

  return 0;
}
