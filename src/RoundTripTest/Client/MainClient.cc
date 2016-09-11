#include <RoundTripClient.h>
#include <Timer.h>

#define ROUND_TIMES 10000
#define PACKAGE_SIZE 1 //1 means 1 KB.

int main()
{
  RoundTripClient rtc = new RoundTripClient();
  rtc.setPackageSize(PACKAGE_SIZE);
  rtc.setDstIp("127.0.0.1");
  rtc.setDstPort();

  Timer t = new Timer();

  t.start();

  rtc.roundTrip(ROUND_TIMES);

  t.end();
  t.showInterval();

  return 0;
}
