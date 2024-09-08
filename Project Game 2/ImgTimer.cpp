#include "stdafx.h"
#include "ImgTimer.h"
#include "CommonFunc.h"

TmpTimer::TmpTimer()
{
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_start_ = false;
}

TmpTimer::~TmpTimer()
{
}

void TmpTimer::start()
{
	is_start_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}
void TmpTimer::stop()
{
	is_paused_ = false;
	is_start_ = false;
}
void TmpTimer::pasused()
{
	if (is_start_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks() - start_tick_;
		
	}
}
void TmpTimer::unpaused()
{
	if (is_paused_ == true)
	{
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - paused_tick_;
		paused_tick_ = 0;
	}
}
int TmpTimer::get_ticks()
{
	if (is_start_ == true){
		if (is_paused_ == true)
		{
			return paused_tick_;
		}
		else
		{
			return SDL_GetTicks() - start_tick_;
		}
	}
	return 0;
}

bool TmpTimer::is_started()
{
	return is_start_;
}
bool TmpTimer::is_paused()
{
	return is_paused_;
}


