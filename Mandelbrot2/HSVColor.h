//This file is part of Mandelbrot Multithreaded(GNU GPL) - https://www.youtube.com/user/Muzkaw.

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utility.h"

using namespace std ;
using namespace sf ;

struct HSVColor
{
	HSVColor() ;
	HSVColor(float const& hue,float const& saturation,float const& value, float const& weight);

	Color RGB() ;

	static Color interpolation(vector<HSVColor> const& colors, float const& w) ;

	float h ;
	float s ;
	float v ;
	float w ;
};

