
#include "stdafx.h"
#include "Geometric.h"

void Geometric::RenderRectangle(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer * des)
{
	SDL_Rect fill_rect = { geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_ };
	SDL_SetRenderDrawColor(des, color_data.red_, color_data.green_, color_data.blue_,0xFF  );
	SDL_RenderFillRect(des, &fill_rect);


}
void Geometric::RenderOutline(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer * des)
{ 

	SDL_Rect fill_rect = { geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_ };
	SDL_SetRenderDrawColor(des, color_data.red_, color_data.green_, color_data.blue_,0xFF);
	SDL_RenderDrawRect(des, &fill_rect);


}