#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <stdio.h>

class Timer {
public:
	void start() {
		start_time = clock();
	}
	void end() {
		end_time = clock();
	}
	void showInterval() {
		printf("Time elapsed %lfs.\n", double(end_time - start_time) / CLOCKS_PER_SEC);
	}
private:
	clock_t start_time;
	clock_t end_time;
};

#endif
