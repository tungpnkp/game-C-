


#include "stdafx.h"
#include "CommonFunc.h"
#include "ImgTimer.h"
#include "game_map.h"
#include "MainObject.h"
#include "BaseObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "Geometric.h"
#include "MainPower.h"
#include "BossObject.h"


BaseObject g_background;
TTF_Font* font_time;
TTF_Font* font_menu;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Project Game 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)) && imgFlags)
				success = false;
		}

		if (TTF_Init() == -1)
		{
			success = false;

		}
		font_time = TTF_OpenFont("font//dlxfont.ttf", 15);
		if (font_time == NULL)
		{
			success = false;
		}
		font_menu = TTF_OpenFont("font//dlxfont.ttf",50);
		if (font_menu == NULL)
		{
			success = false;
		}
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return false;

	//read file wwav audio
	g_sound_bullet[0] = Mix_LoadWAV("music//Fire1.wav");
	g_sound_bullet[1] = Mix_LoadWAV("music//Fire.wav");
	g_sound_exp[0] = Mix_LoadWAV("music//Explosion+1.wav");
	g_sound_crys[0] = Mix_LoadWAV("music//beep.wav");

	g_sound_win[0] = Mix_LoadWAV("music//wind.wav");



	return success;
}

bool LoadBackGround()
{
	bool ret = g_background.LoadImg("img//BG.png", g_screen);
	if (ret == false)
		return false;
	return true;

}
void close()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit;
	SDL_Quit;
}


std::vector<ThreatsObject*> MakeThreadList(Map& map)
{

	std::vector<ThreatsObject*> list_threats;

	for (int i = 0; i < MAX_MAP_X; i++)
	{
		for (int j = 0; j < MAX_MAP_Y; j++)
		{
			if (map.tile[j][i] == 101)
			{
				ThreatsObject* p_threat = new ThreatsObject();
				if (p_threat != NULL)
				{
					p_threat->LoadImg("img//threat_left.png", g_screen);
					p_threat->set_clips();
					p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
					p_threat->set_x_pos(TILE_SIZE * i);
					p_threat->set_y_pos(TILE_SIZE*j);

					int pos1 = p_threat->get_x_pos() - 128;
					int pos2 = p_threat->get_x_pos() + 128;

					p_threat->setANimationPos(pos1, pos2);
					p_threat->set_input_left(1);

					BulletObject * p_bullet = new BulletObject();
					p_threat->Initbullet(p_bullet, g_screen);
					list_threats.push_back(p_threat);

				

				}
			}
			if (map.tile[j][i] == 102)
			{
				ThreatsObject* p_threat= new ThreatsObject();
				if (p_threat != NULL)
				{

					p_threat->LoadImg("img//threat_level.png", g_screen);
					p_threat->set_clips();
					p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
					p_threat->set_input_left(0);
					p_threat->set_x_pos(i*TILE_SIZE);
					p_threat->set_y_pos(j*TILE_SIZE);



					BulletObject * p_bullet = new BulletObject();
					p_threat->Initbullet(p_bullet, g_screen);
					list_threats.push_back(p_threat);

				
				}
			}
		}
	}

	return list_threats;
}

void delete_object(Map& map)
{
	for (int i = 0; i < MAX_MAP_X; i++)
	{
		for (int j = 0; j < MAX_MAP_Y; j++)
		{
			if (map.tile[j][i] == 102 || map.tile[j][i] == 101)
			{
				map.tile[j][i] = 0;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	TmpTimer fps_time;

	BaseObject* map_num = new BaseObject();
	map_num->set_num(1);



	if (InitData() == false)
		return -1;
	if (LoadBackGround() == false)
		return -1;


	bool is_quit = false;

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, font_menu, "Play Game", "Exit", "img//Menu_1.png");
	if (ret_menu == 1)
		is_quit = true;

	int ret_menu2 = SDLCommonFunc::ShowMenu(g_screen, font_menu, "WINTER LAND", "DIESERT", "img//Menu_1.png");
	if (ret_menu2 == 1)
	{
		map_num->set_num(2);
	}

	int dificut = 1;

	int ret_menu3 = SDLCommonFunc::ShowMenu(g_screen, font_menu, "HARD", "EASY", "img//Menu_1.png");
	if (ret_menu3 == 1)
	{
		dificut = 2;
	}
	char str_map[30];
	
	

	GameMap game_map;
	char str_name_map[30];
	sprintf_s(str_name_map, "map%d", map_num->get_num());
	game_map.set_name_map(str_name_map);
	sprintf_s(str_map, "%s//map.dat",game_map.get_name_map());
	game_map.set_name_map(str_name_map);
	game_map.LoadMap(str_map);
	game_map.LoadTiles(g_screen);


	MainObject p_player;
	p_player.LoadImg("img//player_right.png", g_screen);
	p_player.set_clips();
	p_player.set_num_die(4);

	MainPower player_power;
	player_power.Init(g_screen);
	MainMoney Main_money;
	Main_money.Init(g_screen);
	Main_money.SetPos(850, 5);

	BossObject* Boss_=new BossObject();
	for (int i = 0; i < MAX_MAP_X; i++)
	{
		for (int j = 0; j < MAX_MAP_Y; j++)
		{
			if (game_map.getMap().tile[j][i] == 103)
			{
			
			Boss_->LoadImg("img//boss_object.png", g_screen);
			Boss_->set_clips();
			Boss_->set_type_move(ThreatsObject::STATIC_THREAT);
			Boss_->set_input_left(0);
			Boss_->Set_x_pos(i*TILE_SIZE );
			Boss_->Set_y_pos(j*TILE_SIZE);
			if (dificut == 1)
			{
				Boss_->Set_heath_boss(30);
			}
			else if (dificut == 2)
			{
				Boss_->Set_heath_boss(40);
			}
			}
		}
	}
	

	std::vector<ThreatsObject*> threats_list = MakeThreadList(game_map.getMap());

	ExplosionObject exp_threat;
	bool tRet = exp_threat.LoadImg("img//exp3.png", g_screen);
	if (!tRet) return -1;
	exp_threat.set_clip();
	

	//time text
	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);
	TextObject crystal_game;
	crystal_game.SetColor(TextObject::WHITE_TEXT);

	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);
	int mark_val = 0;



	while (!is_quit)
	{
		fps_time.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			p_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
		}
		
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		game_map.DawnMap(g_screen);
		Map ga_map = game_map.getMap();

		delete_object(ga_map);
	
		p_player.HandleBullet(g_screen,ga_map);
		p_player.SetMapXY(ga_map.start_x_, ga_map.start_y_);
		p_player.DoPlayer(ga_map,g_sound_crys);
		p_player.Show(g_screen);

		game_map.SetMap(ga_map);
		game_map.DawnMap(g_screen);

		player_power.SerNum(p_player.get_num_die()-1);
		player_power.Init(g_screen);
		
		GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
		ColorData color_data(0, 80, 150);
		Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

		GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38);
		ColorData color_data2 (255, 0, 0);
		Geometric::RenderRectangle(outLineSize, color_data2, g_screen);

		std::vector<BulletObject*> boss_bullet_arr;
		if (Boss_ != NULL)
		{
		Boss_->SetMapXY(ga_map.start_x_, ga_map.start_y_);
		Boss_->DoBoss(ga_map);
		Boss_->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
		Boss_->Show(g_screen);
		boss_bullet_arr = Boss_->get_bullet_list();
		}
		
		if (p_player.get_check_win())
		{
			if (MessageBox(NULL, _T("You Are WIN"), L"Info", MB_OK || MB_ICONSTOP) == IDOK)
			{
				close();
				SDL_Quit();
				return 0;

			}
		}
	

		player_power.Show(g_screen);
		Main_money.Show(g_screen);
		
		if (p_player.get_num_die() == 0)
		{
			if (MessageBox(NULL, _T("GAME OVER"), L"Info", MB_OK || MB_ICONSTOP) == IDOK)
			{
				close();
				SDL_Quit();
				return 0;

			}
		}

		SDL_Rect rect_player = p_player.GetRectFrame();
		
		for (int bb = 0; bb < boss_bullet_arr.size(); bb++)
		{
			BulletObject* b_bullet = boss_bullet_arr.at(bb);
			if (b_bullet != NULL)
			{
				bool check = b_bullet->CheckToMap(ga_map);
				if (check)
				{
					Boss_->RemoveBullet(bb);
				}
			}
			bool bColBoss = SDLCommonFunc::CheckColision(b_bullet->GetRect(), rect_player);
			if (bColBoss)
			{
				p_player.decrease();
				if (p_player.get_num_die() > 0)
				{
					p_player.SetRect(0, 0);
					p_player.set_comeback_time(60);
					SDL_Delay(1000);
					player_power.DeCrease();
					player_power.Render(g_screen);
					continue;

				} 
				else
				{
					if (MessageBox(NULL, _T("GAME OVER"), L"Info", MB_OK || MB_ICONSTOP) == IDOK)
					{
						close();
						SDL_Quit();
						return 0;

					}
				}

			}
		}
		for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatsObject * p_threat = threats_list.at(i);
			if (p_threat != NULL)
			{
				
				p_threat->setMapXY(ga_map.start_x_, ga_map.start_y_);
				p_threat->ImpMoveType(g_screen);
				p_threat->DoPlayer(ga_map);
				
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				
				std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
				bool bCol1=false;
				
				for (int ff = 0; ff < tBullet_list.size(); ff++)
				{
					BulletObject * t_bullet = tBullet_list.at(ff);
					if (t_bullet != NULL)
					{
						bool bCol3 = t_bullet->CheckToMap(ga_map);
						if (bCol3)
						{
							t_bullet->set_is_move(false);
						}
					}
				}
				if (tBullet_list.size() > 0)
				{
				for (int jj = 0; jj < tBullet_list.size(); ++jj)
				{
				
					BulletObject * t_bullet = tBullet_list.at(jj);
					if (t_bullet != NULL)
					{
					 bCol1 = SDLCommonFunc::CheckColision(t_bullet->GetRect(), rect_player);
					 
						if (bCol1 )
						{
							p_threat->RemoveBullet(jj);
							break;
						}
					}
				}
				}

				SDL_Rect rect_threat = p_threat->GetRectFrame();
				bool bCol2 = SDLCommonFunc::CheckColision(rect_player, rect_threat);
				if (bCol1 || bCol2)
				{
					p_player.decrease();
					if (p_player.get_num_die() > 0)
					{
						p_player.SetRect(0, 0);
						p_player.set_comeback_time(60);
						SDL_Delay(1000);
						player_power.DeCrease();
						player_power.Render(g_screen);
						continue;

					}
					else
					{
					if (MessageBox(NULL, _T("GAME OVER"),L"Info", MB_OK || MB_ICONSTOP) == IDOK)
					{
						p_threat->Free();
						close();
						SDL_Quit();
						return 0;

					}
					}

				}
			}
		}

		
		int frame_exo_width = exp_threat.get_frame_width();
		int frame_exp_height = exp_threat.get_frame_height();
		std::vector<BulletObject*> bubllet_arr = p_player.get_bullet_list();
		for (int r = 0; r < bubllet_arr.size(); r++)
		{
			BulletObject* p_bullet = bubllet_arr.at(r);
			if (p_bullet != NULL)
			{
				bool check = p_bullet->CheckToMap(ga_map);
				if (check)
				{
					p_player.RemoveBullet(r);
				}
			}
		}
		for (int r = 0; r < bubllet_arr.size(); r++)
		{
			BulletObject* p_bullet = bubllet_arr.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < threats_list.size(); t++)
				{
					ThreatsObject* obj_threat = threats_list.at(t);
					if (obj_threat != NULL)
					{
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();
						bool bCol = SDLCommonFunc::CheckColision(bRect, tRect);
						if (bCol)
						{
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
							for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
							{
								int x_pos = p_bullet->GetRect().x - frame_exo_width/2;
								int y_pos = p_bullet->GetRect().y - frame_exp_height/2;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
							}
							if (obj_threat->get_type_move() == ThreatsObject::STATIC_THREAT)
							{
								mark_val += 10;
							}
							else if (obj_threat->get_type_move() == ThreatsObject::MOVE_IN_SPACE_THREAT)
							{
								mark_val += 30;
							}
							p_player.RemoveBullet(r);
							obj_threat->Free();
							threats_list.erase(threats_list.begin() + t);
						}
					}
				}
				if (Boss_!= NULL)
				{
					SDL_Rect tRect;

					tRect.x = Boss_->GetRect().x;
					tRect.y = Boss_->GetRect().y;
					tRect.w = Boss_->get_width_frame();
					tRect.h = Boss_->get_height_frame();
					SDL_Rect bRect = p_bullet->GetRect();
					bool bCol = SDLCommonFunc::CheckColision(bRect, tRect);
					if (bCol)
					{
						Boss_->IncreaseHeath(p_bullet);
						p_player.RemoveBullet(r);
						if (Boss_->Get_heath_boss() <= 0)
						{
							mark_val += 400;
							Boss_ = NULL;
							continue;
						}
					}
				}
				
			}
		}

		//Show game time
		std::string str_time = "time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = 10000 - time_val;
		if (val_time <= 0)
		{
			if (MessageBox(NULL, _T("GAME OVER"), L"Info", MB_OK || MB_ICONSTOP) == IDOK)
			{
				is_quit = true;
				break;

			}
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;

			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
		}
		//show diem game
		
		int total_val = mark_val + p_player.get_crystal() * 50;
		std::string val_str_mark = "Point: ";
		std::string strmark = std::to_string(total_val );

		val_str_mark += strmark;
		mark_game.SetText(val_str_mark);
		mark_game.LoadFromRenderText(font_time, g_screen);
		mark_game.RenderText(g_screen, 500, 15);


		// show so tien
		int crystal_ = p_player.get_crystal();

		std::string str_crystal = std::to_string(crystal_);
		
		crystal_game.SetText(str_crystal);
		crystal_game.LoadFromRenderText(font_time, g_screen);
		crystal_game.RenderText(g_screen, 900, 15);


		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_time.get_ticks();
		int time_one_frame = 1000 / 25;
		if (real_imp_time < time_one_frame)
		{

			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0)
				SDL_Delay(delay_time);
		}

	}


	for (int i = 0; i < threats_list.size(); i++)
	{
		ThreatsObject* p_threat = threats_list.at(i);
		if (p_threat!=NULL)
		{
			p_threat->Free();
			p_threat = NULL;
		}

	}
	threats_list.clear();
	close();
	return 0;
}

