#pragma once

#include <time.h>

struct TIMER
{
	long elapsed_time;
};

TIMER new_timer()
{
	TIMER timer;
	timer.elapsed_time = clock();
	return timer;
}

bool to_continue(TIMER& timer, long time_condition)
{
	if (clock() - timer.elapsed_time > time_condition) {
		timer.elapsed_time = clock();
		return true;
	}
	return false;
}
