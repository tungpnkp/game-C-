#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ThreatsObject.h"

class BossObject: public ThreatsObject
{
public:
	BossObject();
	~BossObject();

	void Set_x_pos(const int & x){ x_pos_ = x; }
	void Set_y_pos(const int & y){ y_pos_ = y; }
	void SetMapXY(const int& a, const int & b){ map_x_ = a, map_y_ = b; }
	void Set_heath_boss(const int & a){ heath_boss = a; }
	
	int Get_x_pos()const { return x_pos_; }
	int Get_y_pos()const { return y_pos_; }
	int Get_heath_boss() { return heath_boss; }

	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }
	void IncreaseHeath(BulletObject* bullet);

	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer * des);
	void Show(SDL_Renderer *des);
	
	void DoBoss(Map& map);
	void CheckMap(Map& map);

	void set_bullet_list(const std::vector<BulletObject*> bull) { bullet_list_boss_ = bull; }
	std::vector<BulletObject*> get_bullet_list() const{ return bullet_list_boss_; }
	void Initbullet(BulletObject * p_bullet, SDL_Renderer *des);
	void RemoveBullet(const int& a);
	void MakeBullet(SDL_Renderer *des, const int& x_limit, const int& y_limit);
private:

	int x_pos_;
	int y_pos_;
	int map_x_;
	int map_y_;
	float y_val_;
	float x_val_;
	bool on_ground;
	int come_back_time;

	int width_frame_;
	int height_frame_;
	int frame;

	int heath_boss;


	SDL_Rect fame_clip_[32];

	std::vector<BulletObject*> bullet_list_boss_;
};


#endif