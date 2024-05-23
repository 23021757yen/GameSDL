#ifndef TIMER_H_
#define TIMER_H_

#pragma once

#include "CommonFunc.h"

// cái này để xử lí thời gian trong game nè

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();

	bool get_started();
	bool get_paused();

private:

	int start_tick_;
	int pause_tick_;

	bool is_paused_;
	bool is_started_;

};


#endif // !TIMER_H_
