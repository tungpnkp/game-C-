#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <Windows.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <WinUser.h>
#include "TextObject.h"
#include "BaseObject.h"

using namespace std;

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_screen = NULL;
static SDL_Surface * g_img_menu = NULL;
static SDL_Event g_event;
static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* g_sound_crys[2];
static Mix_Chunk* g_sound_win[2];


const int FRAME_PER_SECOND=25;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
const int COLOR_BPP = 32;
 
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;





#define TILE_SIZE 64
#define MAX_MAP_X 200
#define MAX_MAP_Y 12
#define Crystal 30
#define End_game 31


typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};
typedef struct Map
{
	int start_x_;
	int start_y_;
	
	int max_x_;
	int max_y_;

	int tile [MAX_MAP_Y][MAX_MAP_X];

	char* file_name;



};


namespace SDLCommonFunc
{
	bool CheckColision(const SDL_Rect& object1, const SDL_Rect& object2);
	bool CheckFocus(const int &x, const int & y, const int& a, const int & b);
	int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
		const std::string& menu1,
		const std::string& menu2,
		const std::string& img_name);
}
class CommonFunc
{
public:
	CommonFunc();
	~CommonFunc();

	void set_map_num(const int& a) { map_num = a; }
	int get_map_num() const { return map_num; }
private:
	int map_num;
};
#endif