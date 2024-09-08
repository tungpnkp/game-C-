#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H



#include "BaseObject.h"

#include "CommonFunc.h"

class BulletObject : public BaseObject
{
public:
	BulletObject();
	~BulletObject();
	enum BulletBir{
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
	};
	enum BulletType{

		Bullet_1 = 50,
		Bullet_2 = 51,
		bullet_boss = 52,
	};

	void set_x_val(const int& xVal){ x_val = xVal; }
	void set_y_val(const int& yVal){ y_val = yVal; }
	int get_x_val() const{ return x_val; }
	int get_y_val() const{ return y_val; }
	void set_x_pos(const int& x){ x_pos_ = x; }
	void set_y_pos(const int& y) { y_pos_ = y; }
	int get_x_pos()const{ return x_pos_; }
	int get_y_pos() const{ return y_pos_; }


	void set_is_move(const bool& isMove) { is_move_ = isMove; }
	bool get_is_move() const{ return is_move_; }


	void HandleMove(const int& x_border, const int& y_border);
	void Set_Bullet_dir(const unsigned int& bullet) { bullet_dir_ = bullet; }
	int get_bullet_dir() const { return bullet_dir_; }


	void set_bullet_type(const unsigned int& bullet){ bullet_type_ = bullet; }
	unsigned int get_bullet_type()const { return bullet_type_; }
	bool LoadImgBullet(SDL_Renderer* des);
	bool CheckToMap(Map& map);


private:
	int x_val;
	int y_val;
	bool is_move_;
	unsigned int bullet_dir_;
	unsigned int bullet_type_;
	int x_pos_;
	int y_pos_;
};

#endif