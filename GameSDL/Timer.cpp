#include "Timer.h"


Timer::Timer()
{
	start_tick_ = 0;
	pause_tick_ = 0;
	is_started_ = false;
	is_paused_ = false;

}

Timer::~Timer()
{

}

void Timer::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}

void Timer::stop()
{
	is_paused_ = false;
	is_started_ = false;
}

void Timer::paused()
{
	if (is_started_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		pause_tick_ = SDL_GetTicks() - start_tick_;

	}
}

void Timer::unpaused()
{
	if (is_paused_ == true)
	{
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - pause_tick_;
		pause_tick_ = 0;
	}
}

int Timer::get_ticks()
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return pause_tick_;
		}
		else
		{
			return SDL_GetTicks() - start_tick_;
		}
	}
	else 
	{
		return 0;
	}
}

bool Timer::get_started()
{
	return is_started_;
}

bool Timer::get_paused()
{
	return is_paused_;
}