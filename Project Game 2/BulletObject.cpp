#include "stdafx.h"
#include "BulletObject.h"


BulletObject::BulletObject()
{
	x_val = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	y_val = 0;
	is_move_ = false;
	bullet_type_ = Bullet_1;
}

BulletObject:: ~BulletObject()
{

}
bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	bool ret = false;
	if (bullet_type_ == Bullet_1)
	{
		ret = LoadImg("img//bullet_player.png", des);
	}
	else if (bullet_type_ == Bullet_2)
	{
		ret = LoadImg("img//bullet_player02.png", des);
	}
	else if (bullet_type_ == bullet_boss)
	{
		ret = LoadImg("img//boss bullet.png", des);
	}
	return ret;
}
void BulletObject::HandleMove(const int& x_border, const int& y_border)
{

	if (bullet_dir_ == DIR_RIGHT)
	{
		rect_.x += x_val;
		if (rect_.x > x_border)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_LEFT )
	{
		rect_.x -= x_val;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
	}
	x_pos_ = rect_.x;
	y_pos_ = rect_.y;
	
}
bool BulletObject::CheckToMap(Map& map)
{
		/*int x = GetRect().x/TILE_SIZE;
		in t y = GetRect().y/TILE_SIZE;
		if (map.tile[y][x] != 0 && map.tile[y][x] != 6)
		{
			return true;
		}
	
	return false;*/
	return false;
}
