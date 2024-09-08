
#include "stdafx.h"
#include "BossObject.h"

BossObject::BossObject()
{
	x_pos_ = 0;
	y_pos_ = 0;
	map_x_ = 0;
	map_y_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	heath_boss = 0;
	on_ground = false;
	come_back_time = 0;
	frame = 0;

}

BossObject::~BossObject()
{

}


bool BossObject::LoadImg(std::string path, SDL_Renderer * des)
{

	bool ret = BaseObject::LoadImg(path, des);
	if (ret)
	{
		width_frame_ = rect_.w / 32;
		height_frame_ = rect_.h;
	}
	return ret;
}

void BossObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 32; i++)
		{
			fame_clip_[i].x = i*width_frame_  ;
			fame_clip_[i].y = 0;
			fame_clip_[i].w = width_frame_;
			fame_clip_[i].h = height_frame_;
		}

	}
}


void BossObject::Show(SDL_Renderer *des)
{

		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame++;
		if (frame >= 32)
		{
			frame = 0;
		}
		if (frame == 16)
		{
			BulletObject* boss_bullet = new BulletObject();
			Initbullet(boss_bullet, des);

		}


		SDL_Rect* currentClip = &fame_clip_[frame];
		SDL_Rect rendQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
	
}

void BossObject::DoBoss(Map& map)
{
	if (come_back_time == 0)
	{
		x_val_ = 0;
		y_val_ += THREAT_FRAVITY_SPEED;
		if (y_val_ >= THREAT_MAX_FALL_SPEED)
		{
			y_val_ = THREAT_MAX_FALL_SPEED;
		}

	}
	CheckMap(map);
}
void BossObject::CheckMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//check horizontal
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X &&  y1 >= 0 && y2 <= MAX_MAP_Y)
	{
		if (x_val_ > 0) // main di sang ben phai
		{

			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];


			if ((map_data.tile[y1][x2] != BLANK_TITLE && val1 != Crystal) || (val2 != BLANK_TITLE && val2 != Crystal))
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ = x_pos_ - (width_frame_ + 1);
				x_val_ = 0;
				on_ground = true;
			}
			else if (y_val_ > 1)
			{
				on_ground = false;
			}



		}
		else if (x_val_<0){
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];


			if ((map_data.tile[y1][x1] != BLANK_TITLE && val1 != Crystal) || (map_data.tile[y2][x1] != BLANK_TITLE && val2 != Crystal))
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
				on_ground = true;


			}
			else if (y_val_ > 1)
			{
				on_ground = false;
			}


		}
	}

	//check vertical

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min - 1) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X &&  y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];


			if ((val1 != BLANK_TITLE && val1 != Crystal) || (val2 != BLANK_TITLE && val2 != Crystal))
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				on_ground = true;


			}
			else{
				//on_ground = false;
			}





		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if ((val1 != BLANK_TITLE && val1 != Crystal) || (val2 != BLANK_TITLE&& val2 != Crystal))
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}


		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;
}

void BossObject::Initbullet(BulletObject * p_bullet, SDL_Renderer * des)

{
	if (p_bullet != NULL)
	{
		p_bullet->set_bullet_type(BulletObject::bullet_boss);
		bool ret = p_bullet->LoadImgBullet(des);
		if (ret)
		{
			p_bullet->set_is_move(true);
			p_bullet->Set_Bullet_dir(BulletObject::DIR_LEFT);
			{
				p_bullet->SetRect(rect_.x + 20, y_pos_ + height_frame_-30);
				p_bullet->set_x_val(10);
				bullet_list_boss_.push_back(p_bullet);
			}

		}
	}
}
void BossObject::RemoveBullet(const int& idx)
{
	int size = bullet_list_boss_.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list_boss_.at(idx);
		bullet_list_boss_.erase(bullet_list_boss_.begin() + idx);

		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}

}
void BossObject::MakeBullet(SDL_Renderer *des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < bullet_list_boss_.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_boss_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move())
			{

				int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
				if (bullet_distance < 600 && bullet_distance >0)
				{

					p_bullet->HandleMove(x_limit, y_limit);
					p_bullet->Render(des);
				}
				else
				{
					RemoveBullet(i);
				}
			}
		}
	}
}

void BossObject::IncreaseHeath(BulletObject* bullet)
{
	if (bullet->get_bullet_type() == BulletObject::Bullet_1)
	{
		heath_boss -= 1;
	}
	if (bullet->get_bullet_type() == BulletObject::Bullet_2)
	{
		heath_boss -= 2;
	}

}