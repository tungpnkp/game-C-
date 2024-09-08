#include "stdafx.h"
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	on_ground = false;
	come_back_time = 0;
	frame = 0;
	animation_a_ = 0;
	animation_b_ = 0;
	input_type_.left_ = 0;
	type_move_ = STATIC_THREAT;

}
ThreatsObject:: ~ThreatsObject()
{

}


bool ThreatsObject::LoadImg(std::string path, SDL_Renderer * des)
{

	bool ret = BaseObject::LoadImg(path, des);
	if (ret)
	{
		width_frame_ = rect_.w/THREAT_FRAME_NUM;
		height_frame_ = rect_.h;
	}
	return ret;
}

void ThreatsObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		fame_clip_[0].x = 0;
		fame_clip_[0].y = 0;
		fame_clip_[0].w = width_frame_;
		fame_clip_[0].h = height_frame_;

		fame_clip_[1].x = width_frame_;
		fame_clip_[1].y = 0;
		fame_clip_[1].w = width_frame_;
		fame_clip_[1].h = height_frame_;

		fame_clip_[2].x = 2 * width_frame_;
		fame_clip_[2].y = 0;
		fame_clip_[2].w = width_frame_;
		fame_clip_[2].h = height_frame_;

		fame_clip_[3].x = 3 * width_frame_;
		fame_clip_[3].y = 0;
		fame_clip_[3].w = width_frame_;
		fame_clip_[3].h = height_frame_;

		fame_clip_[4].x = 4 * width_frame_;
		fame_clip_[4].y = 0;
		fame_clip_[4].w = width_frame_;
		fame_clip_[4].h = height_frame_;

		fame_clip_[5].x = 5 * width_frame_;
		fame_clip_[5].y = 0;
		fame_clip_[5].w = width_frame_;
		fame_clip_[5].h = height_frame_;

		fame_clip_[6].x = 6 * width_frame_;
		fame_clip_[6].y = 0;
		fame_clip_[6].w = width_frame_;
		fame_clip_[6].h = height_frame_;

		fame_clip_[7].x = 7 * width_frame_;
		fame_clip_[7].y = 0;
		fame_clip_[7].w = width_frame_;
		fame_clip_[7].h = height_frame_;

	}
}


void ThreatsObject::Show(SDL_Renderer *des)
{
	if (come_back_time == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame++;
		if (frame >= 8)
		{
			frame = 0;
		}


		SDL_Rect* currentClip = &fame_clip_[frame];
		SDL_Rect rendQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
	}
}

void ThreatsObject::DoPlayer(Map &gMap)
{
	if (come_back_time == 0)
	{
		x_val_ = 0;
		y_val_ += THREAT_FRAVITY_SPEED;
		if (y_val_ >= THREAT_MAX_FALL_SPEED);
		{
			y_val_ = THREAT_MAX_FALL_SPEED;
		}
		if (input_type_.left_ == 1)
		{
			x_val_ -= THREAT_SPEED;
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += THREAT_SPEED;
		}

		CheckToMap(gMap);
		
	}
	else if (come_back_time > 0)
	{
		come_back_time--;
		if (come_back_time == 0)
		{
			x_val_ = 0;
			y_val_ = 0;
			if (x_pos_ > 256)
			{
				x_pos_ -= 256;
				animation_a_ -= 256;
				animation_b_ -= 256;
			}
			else
			{
				x_pos_ = 0;
			}
			y_pos_ = 0;
			come_back_time = 0;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
		}
	}


}

void ThreatsObject::CheckToMap(Map& map_data)
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
					input_type_.left_ = 1;
					input_type_.right_ = 0;
				}
				else if (y_val_ > 1)
				{
					on_ground = false;
				}
			


		}
		else if (x_val_<0){
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			
				if ((map_data.tile[y1][x1] != BLANK_TITLE && val1 != Crystal) ||( map_data.tile[y2][x1] != BLANK_TITLE && val2 != Crystal))
				{
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
					on_ground = true; 
					input_type_.left_ = 0;
					input_type_.right_ = 1;

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

			
				if ((val1 != BLANK_TITLE && val1 != Crystal) || (val2 != BLANK_TITLE && val2!= Crystal))
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
			
				if ((val1 != BLANK_TITLE && val1 !=Crystal) || (val2 != BLANK_TITLE&& val2 != Crystal))
				{
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			

		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_){
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}


	if (y_pos_ > map_data.max_y_)
	{

		come_back_time = 60;
	}
}


void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
	if (type_move_ == STATIC_THREAT)
	{
		
	}
	else
	{
		if (on_ground == true)
		{
			if (x_pos_ > animation_b_)
			{
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("img//threat_left.png", screen);
			}
			else if (x_pos_ < animation_a_)
			{
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				LoadImg("img//threat_right.png", screen);

			}
			else
			{
				if (input_type_.left_ == 1)
				{
					LoadImg("img//threat_left.png", screen);
				}
			}
		}
	}
	
}

void ThreatsObject::Initbullet(BulletObject * p_bullet, SDL_Renderer * des)
{
	if (p_bullet != NULL)
	{
		p_bullet->set_bullet_type(BulletObject::Bullet_2);
		bool ret = p_bullet->LoadImgBullet(des);
		if (ret)
		{
		p_bullet->set_is_move(true);
		p_bullet->Set_Bullet_dir(BulletObject::DIR_LEFT);
		p_bullet->SetRect(rect_.x+ 20, y_pos_ + 10);
		p_bullet->set_x_val(10);
		bullet_list_.push_back(p_bullet);
		}

	}
}
void ThreatsObject::Initbullet_dynamic(BulletObject* p_bullet, SDL_Renderer * des)
{
	if (p_bullet != NULL)
	{
		p_bullet->set_bullet_type(BulletObject::Bullet_2);
		bool ret = p_bullet->LoadImgBullet(des);
		if (ret)
		{
			p_bullet->set_is_move(true);
			if (input_type_.left_ == 1)
			{
				p_bullet->Set_Bullet_dir(BulletObject::DIR_LEFT);

			}
			else if (input_type_.left_ == 0)
			{
				p_bullet->Set_Bullet_dir(BulletObject::DIR_RIGHT);
			}
			
			p_bullet->SetRect(rect_.x + 20, y_pos_ + 10);
			p_bullet->set_x_val(15);
			bullet_list_.push_back(p_bullet);
		}
	}



}
void ThreatsObject::MakeBullet(SDL_Renderer * des, const int& x_limit, const int& y_limit)
{
	if (type_move_ == STATIC_THREAT)
	{
	for (int i = 0; i < bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move())
			{
				
				int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
				if (bullet_distance < 300 && bullet_distance >0 )
				{

					p_bullet->HandleMove(x_limit, y_limit);
					p_bullet->Render(des);
				}
				else
				{
					p_bullet->set_is_move(false);
				}
			}
			else
			{
				//SDL_Delay(1000);
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x + 20, y_pos_ + 10);
			}
		}
	}
	}
	else if (type_move_ == MOVE_IN_SPACE_THREAT)
	{
		for (int i = 0; i < bullet_list_.size(); i++)
		{
			BulletObject* p_bullet = bullet_list_.at(i);
			if (p_bullet != NULL)
			{
				if (p_bullet->get_is_move())
				{
					if (p_bullet->get_bullet_dir() == p_bullet->DIR_LEFT)
					{
						int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
						if (bullet_distance < 300 && bullet_distance >0)
						{

							p_bullet->HandleMove(x_limit, y_limit);
							p_bullet->Render(des);
						}
						else
						{
							p_bullet->set_is_move(false);
						}
					}
					else
					{
						int bullet_distance = p_bullet->GetRect().x - rect_.x + width_frame_;
						if (bullet_distance < 300)
						{
							p_bullet->HandleMove(x_limit, y_limit);
							p_bullet->Render(des);
						}
						else
						{
							p_bullet->set_is_move(false);
						}
					}

				}
				else
				{
					//SDL_Delay(1000);
					p_bullet->set_is_move(true);
					p_bullet->SetRect(rect_.x + 20, y_pos_ + 10);
					if (input_type_.left_ == 1)
					{
						p_bullet->Set_Bullet_dir(p_bullet->DIR_LEFT);
					}
					else if (input_type_.right_ == 1)
					{
						p_bullet->Set_Bullet_dir(p_bullet->DIR_RIGHT);
					}
				}
			}
		}
	}
	
}
void ThreatsObject::RemoveBullet(const int& idx)
{
	int size = bullet_list_.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list_.at(idx);
		bullet_list_.erase(bullet_list_.begin() + idx);

		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}

}
SDL_Rect ThreatsObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;
	return rect;
}
bool ThreatsObject::CheckBullet(Map& map)
{
	for (int i = 0; i < bullet_list_.size(); i++)
	{
		BulletObject* bullet = bullet_list_.at(i);
		int x = bullet->GetRect().x;
		int y = bullet->GetRect().y;
		if (map.tile[x][y] != BLANK_TITLE && map.tile[x][y] != 6)
		{
			return true;
		}
	}
	return false;
}