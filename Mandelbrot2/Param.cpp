//This file is part of Mandelbrot Multithreaded(GNU GPL) - https://www.youtube.com/user/Muzkaw.

#include "Param.h"

Param::Param(int _part,double *_X0,double *_Y0,double *_zoom,double *_maxIteration,float *_dt,Image *_image,vector<HSVColor> *_colors):
part(_part),X0(_X0),Y0(_Y0),zoom(_zoom),maxIteration(_maxIteration),dt(_dt),image(_image),colors(_colors)
{

}
RenderParam::RenderParam(Image *_image,Texture *_texture,Sprite *_sprite,RenderWindow *_window)
{
	image=_image;
	texture=_texture;
	sprite=_sprite;
	window=_window;
}
