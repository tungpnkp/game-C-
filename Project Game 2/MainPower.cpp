
#include "stdafx.h"
#include "MainPower.h"

MainPower::MainPower()
{
	number_ = 0;
}

MainPower::~MainPower()
{


}

void MainPower::Addpos(const int& xp)
{
	pos_list_.push_back(xp);
}

void MainPower::Init(SDL_Renderer* screen)
{
	LoadImg("img//player_pw.png", screen);

	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	if (number_ != 0)
	{
		for (int i = 0; i < number_; i++)
		{
			Addpos(40 * i);
		}
	}
}

void MainPower::Show(SDL_Renderer* screen)
{

	for (int i = 0; i < pos_list_.size(); i++)
	{
		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}

void MainPower::DeCrease()
{

	number_--;
	pos_list_.pop_back();
}

void MainPower::InitCrease()
{
	number_++;
	int last_pos = pos_list_.back();
	last_pos += 40;
	pos_list_.push_back(last_pos);

} 
MainMoney::MainMoney()
{
	x_pos_ = 0;
	y_pos_ = 0;

}
MainMoney::~MainMoney()
{


}

void MainMoney::Init(SDL_Renderer* des)
{
	bool ret = LoadImg("img//money_img.png", des);
}
void MainMoney::Show(SDL_Renderer* des)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(des);
}