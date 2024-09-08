
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public: 
	BaseObject();
	~BaseObject();

	void SetRect(const int& x, const int& y){ rect_.x = x; rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() const { return p_object_; }

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Free();
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	int get_num() const{ return map_num; }
	void set_num(const int &a) { map_num = a; }
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;

	int map_num;
};




#endif