//This file is part of Mandelbrot Multithreaded(GNU GPL) - https://www.youtube.com/user/Muzkaw.

#include "Utility.h"

using namespace sf ;
using namespace std ;

Color colorGradient(Image &color,float x)
{
	if(x>0.999) x=0.999 ;
	if(x<0.001) x=0.001 ;
	return color.getPixel((int)(x*color.getSize().x),0) ;
}
float lerp(float x1,float x2,float y1,float y2, float x)
{
	return y1+(x-x1)/(x2-x1)*(y2-y1) ;
}