#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_



#include "CommonFunc.h"
#include "ThreatsObject.h"
#include "BulletObject.h"




#define BLANK_TITLE 0
#define MAX_SPEED 10
#define PLAYER_SPEED 7

class MainObject : public BaseObject
{
public:

	MainObject();
	~MainObject();

	enum WalkType
	{
		WalkNone=0,
		WalkRight = 1,
		WalkLeft = 2
	};

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer  *des);
	void HandelInputAction(SDL_Event events, SDL_Renderer *screen, Mix_Chunk* bullet_sound[2]);
	void set_clips();
	void DoPlayer(Map&, Mix_Chunk* bullet_sound[2]);
	void CheckMap(Map& map_data, Mix_Chunk* bullet_sound[2]);
	void SetMapXY(const int map_x, const int map_y){ map_x_ = map_x; map_y_ = map_y; }
	void CenterEntinyOnmap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);

	void set_bullet_list(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list()
		const
	{
		return p_bullet_list_;
	}

	void HandleBullet(SDL_Renderer* des, Map& map);

	void count_money();
	int get_crystal() const { return crystal_count; }

	void RemoveBullet(const int& a);

	SDL_Rect GetRectFrame();
	bool CheckBullet(Map& map);
	void set_comeback_time(const int& n){ come_back = n; }

	void set_num_die(const int & a){ num_die = a; }
	int get_num_die() const{ return num_die; }
	void decrease();
	void increase();
	
	bool get_check_win() const { return Check_Win; }


private:

	std::vector <BulletObject*> p_bullet_list_;


	int crystal_count;


	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect fame_clip_[8];
	Input intput_type_;
	int frame_;
	int status_;

	bool on_ground;

	int map_x_;
	int map_y_;

	int come_back;

	int bullet_type_check;

	int num_die;

	bool Check_Win;
};


#endif