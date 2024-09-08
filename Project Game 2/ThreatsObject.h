#ifndef THREATS_OBJECT_H
#define THREATS_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "BulletObject.h"

#define THREAT_FRAVITY_SPEED 0.8
#define THREAT_FRAME_NUM 8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3
class ThreatsObject : public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();


	enum TYPEMOVE
	{
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT =1,
	};


	void set_x_val(const float& xval){ x_val_ = xval; }
	void set_y_val(const float& yval){ y_val_ = yval; }


	void set_x_pos(const float& xpos) { x_pos_ = xpos; }
	void set_y_pos(const float& ypos) { y_pos_ = ypos; }
	
	float get_x_pos() const{ return x_pos_;  }
	float get_y_pos() const { return y_pos_; }
	void setMapXY(const int&mp_x, const int& mp_y){ map_x_ = mp_x; map_y_ = mp_y; }

	void set_bullet_list(const std::vector<BulletObject*> bull) { bullet_list_ = bull; }
	std::vector<BulletObject*> get_bullet_list() const{ return bullet_list_; }
	void Initbullet_dynamic(BulletObject* p_bullet,SDL_Renderer * des );
	void Initbullet(BulletObject * p_bullet, SDL_Renderer *des);
	void MakeBullet(SDL_Renderer *des, const int& x_limit, const int& y_limit);


	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer * des);
	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }

	void DoPlayer(Map& gmap);
	void CheckToMap(Map&gmao);

	void Show(SDL_Renderer *des);

	void set_type_move(const int& move){ type_move_ = move; }
	int get_type_move() const { return type_move_; }
	void setANimationPos(const int& pos_a, const int& pos_b) { animation_a_ = pos_a; animation_b_ = pos_b; }
	void set_input_left(const int& isLeft) { input_type_.left_ = isLeft; }
	void ImpMoveType(SDL_Renderer * des);
	void RemoveBullet(const int& a);
	SDL_Rect GetRectFrame();

	bool CheckBullet(Map& map);



private:


	int map_x_;
	int map_y_;
	float y_val_;
	float x_val_;
	float y_pos_;
	float x_pos_;
	bool on_ground;
	int come_back_time;

	int width_frame_;
	int height_frame_;
	int frame;


	int type_move_;
	int animation_a_;
	int animation_b_;
	Input input_type_;

	SDL_Rect fame_clip_[THREAT_FRAME_NUM];

	std::vector<BulletObject*> bullet_list_;


};

#endif