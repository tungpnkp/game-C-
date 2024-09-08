#ifndef IMG_TIMER_H_

#define IMG_TIMER_H_

class  TmpTimer
{
public:
	 TmpTimer();
	~ TmpTimer();

	void start();
	void stop();
	void pasused(); 
	void unpaused();

	int get_ticks();
	bool is_started();
	bool is_paused();
private:
	int start_tick_;
	int paused_tick_;

	bool is_paused_;
	bool is_start_;
};




#endif