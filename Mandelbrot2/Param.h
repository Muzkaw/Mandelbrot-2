//This file is part of Mandelbrot Multithreaded(GNU GPL) - https://www.youtube.com/user/Muzkaw.

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "HSVColor.h"

using namespace std ;
using namespace sf ;

class Param
{
public:
	Param(int _part,double *_X0, double *_Y0,double *_zoom, double *_maxIteration,float *_dt,Image *_image, vector<HSVColor> *_colors) ;

	int part;
	double *X0;
	double *Y0;
	double *zoom;
	double *maxIteration;
	float *dt ;
	Image *image;
	vector<HSVColor> *colors;
};

class RenderParam
{
public:
	RenderParam(Image *_image,Texture *_texture,Sprite *_sprite,RenderWindow *_window) ;

	Image *image ;
	Texture *texture ;
	Sprite *sprite ;
	RenderWindow *window ;
};
