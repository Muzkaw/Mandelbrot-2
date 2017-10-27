//This file is part of Mandelbrot Multithreaded(GNU GPL) - https://www.youtube.com/user/Muzkaw.

#include "HSVColor.h"

HSVColor::HSVColor()
{
	h = 0 ;
	s = 0 ;
	v = 0 ;
}
HSVColor::HSVColor(float const& hue,float const& saturation,float const& value,float const& weight)
{
	h = hue;
	s = saturation ;
	v = value ;
	w = weight ;
}

Color HSVColor::RGB()
{
	float r,g,b ;
	int hi = (int)(h/60.f) ;
	float f = h/60.f-hi ;
	float l = v*(1-s) ;
	float m = v*(1-f*s) ;
	float n = v*(1-(1-f)*s) ;

	switch(hi)
	{
	case 0: r=v ; g=n ; b=l ; break ;
	case 1: r=m ; g=v ; b=l ; break ;
	case 2: r=l ; g=v ; b=n ; break ;
	case 3: r=l ; g=m ; b=v ; break ;
	case 4: r=n ; g=l ; b=v ; break ;
	case 5: r=v ; g=l ; b=m ; break ;
	}

	return Color(255.f*r,255.f*g,255.f*b) ;
}

Color HSVColor::interpolation(vector<HSVColor> const& colors,float const& w)
{
	float wmax = 0 ;
	float wcur = 0 ;
	int iw = 0 ;
	for(int i(0) ; i < colors.size() ; i++)
	{
		wmax+=colors[i].w ;
		if(wmax < w) iw = i ;
	}
	for(int i(0) ; i <= iw ; i++) wcur+=colors[i].w ;
	
	float h = lerp(0,colors[iw+1].w,colors[iw].h,colors[iw+1].h,w-wcur) ;
	float s = lerp(0,colors[iw+1].w,colors[iw].s,colors[iw+1].s,w-wcur) ;
	float v = lerp(0,colors[iw+1].w,colors[iw].v,colors[iw+1].v,w-wcur) ;
	
	HSVColor result(h,s,v,0);
	return result.RGB() ;
		
}