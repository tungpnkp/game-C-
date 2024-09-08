#ifndef MAIN_POWER_H_
#define MAIN_POWER_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
class MainPower : public BaseObject

{
public:
	MainPower();
	~MainPower();



	void SerNum(const int& num){ number_ = num; }
	void Addpos(const int& xpos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);

	void InitCrease();
	void DeCrease();



private:
	int number_;
	std::vector<int> pos_list_;

};


class MainMoney : public BaseObject
{
public:
	MainMoney();
	~MainMoney();

	void Init(SDL_Renderer* des);
	void Show(SDL_Renderer * des);

	void SetPos(const int& x, const int& y){
		x_pos_ = x;
		y_pos_ = y;
	}
private:
	int x_pos_;
	int y_pos_;
};


#endif