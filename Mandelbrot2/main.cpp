/*********************************************************************

This file is part of Mandelbrot Multithreaded (GNU GPL) - https://www.youtube.com/user/Muzkaw.

Mandelbrot Multithreaded is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mandelbrot Multithreaded is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mandelbrot Multithreaded. If not, see <http://www.gnu.org/licenses/>.

Mandelbrot Multithreaded codded by Muzkaw : https://www.youtube.com/user/Muzkaw
You need to link SFML 2.0 or above to run the program

********************************************************************/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "HSVColor.h"
#include "Utility.h"
#include "Param.h"

#define IMAGE_WIDTH 600
#define IMAGE_HEIGHT 600

#define SCROLL_SPEED 1
#define ZOOM_SPEED 1 
#define ITERATION_SPPED 100

#define SCALE 1

using namespace std ;
using namespace sf ;

void update(Param p)
{
	double x ;
	double y ;
	double a=0 ;
	double b=0 ;

	int n(0) ;
	double a_buffer ;
	
	int h0(0), v0(0) ;
	if(p.part == 0) { h0=0; v0=0 ; }
	else if(p.part == 1) { h0=1; v0=0 ; }
	else if(p.part == 2) { h0=0; v0=1 ; }
	else if(p.part == 3) { h0=1; v0=1 ; }

	double sq_m ;
	
	for(int h(h0) ; h < IMAGE_WIDTH ; h+=2)
	{
		x = *p.X0 + ((h - IMAGE_WIDTH/2.f) / (*p.zoom * IMAGE_WIDTH));

		for(int v(v0) ; v < IMAGE_HEIGHT ; v+=2)
		{
			y = *p.Y0 + ((v - IMAGE_HEIGHT/2.f) / (*p.zoom * IMAGE_HEIGHT));
			a=0 ;
			b=0 ;

			n=0 ;
			for(n ; n < *p.maxIteration ; n++)
			{
				a_buffer = a ;

				a=a_buffer*a_buffer-b*b+x ;
				b=2*a_buffer*b+y ;
				sq_m = a*a+b*b ;
				if(sq_m>4)
				{
					break ;
				}
			}

			if(n<*p.maxIteration) p.image->setPixel(h,v,HSVColor::interpolation(*p.colors,(double)0.1*(n+1-log(log(abs(sqrt(sq_m))))/(log(2)* *p.maxIteration)))) ;
			else p.image->setPixel(h,v,Color::Black) ;
		}
	}
}
void control(Param p)
{
	if(Keyboard::isKeyPressed(Keyboard::Z))
		(*p.zoom)+=(ZOOM_SPEED*(*p.zoom))*(*p.dt);
	if(Keyboard::isKeyPressed(Keyboard::S))
		(*p.zoom)-=(ZOOM_SPEED*(*p.zoom))*(*p.dt);
	if(Keyboard::isKeyPressed(Keyboard::Left))
		*p.X0-=(SCROLL_SPEED/(*p.zoom))*(*p.dt);
	if(Keyboard::isKeyPressed(Keyboard::Right))
		*p.X0+=(SCROLL_SPEED/(*p.zoom))*(*p.dt) ;
	if(Keyboard::isKeyPressed(Keyboard::Up))
		*p.Y0-=(SCROLL_SPEED/(*p.zoom))*(*p.dt) ;
	if(Keyboard::isKeyPressed(Keyboard::Down))
		*p.Y0+=(SCROLL_SPEED/(*p.zoom))*(*p.dt) ;
	if(Keyboard::isKeyPressed(Keyboard::Q))
		*p.maxIteration -= ITERATION_SPPED*(*p.dt) ;
	if(Keyboard::isKeyPressed(Keyboard::D))
		*p.maxIteration += ITERATION_SPPED*(*p.dt) ;
}
void render(RenderParam p)
{
	while(p.window->isOpen())
	{
		p.texture->update(*p.image) ;

		p.window->clear(Color::Black) ;
		p.window->draw(*p.sprite) ;
		p.window->display() ;
	}
}

int main()
{
	RenderWindow window(VideoMode(IMAGE_WIDTH*SCALE,IMAGE_HEIGHT*SCALE),"Mandelbrot Set") ;
	window.setFramerateLimit(200);
	window.setActive(false) ;
	Clock deltaTime ; float dt = 0.01 ;

	double zoom = 1 ;

	double X0 = 0 ;
	double Y0 = 0 ;
	double maxIteration = 50 ;
	
	Image image ;
	image.create(IMAGE_WIDTH,IMAGE_HEIGHT,Color::Black) ;
	Texture texture ;
	texture.loadFromImage(image) ;
	Sprite sprite ;
	sprite.setScale(SCALE,SCALE) ;
	sprite.setTexture(texture) ;

	vector<HSVColor> colors ;
	colors.push_back(HSVColor(0,1,0.3,0)) ;
	colors.push_back(HSVColor(38,0.48,0.91,25)) ;
	colors.push_back(HSVColor(190,0.43,0.48,25)) ;
	colors.push_back(HSVColor(114,1,0.23,25)) ;
	colors.push_back(HSVColor(228,0.64,0.54,26)) ;

	Param p0(0,&X0,&Y0,&zoom,&maxIteration,&dt,&image,&colors) ;
	Param p1(1,&X0,&Y0,&zoom,&maxIteration,&dt,&image,&colors) ;
	Param p2(2,&X0,&Y0,&zoom,&maxIteration,&dt,&image,&colors) ;
	Param p3(3,&X0,&Y0,&zoom,&maxIteration,&dt,&image,&colors) ;
	Thread thread0(&update, p0) ;
	Thread thread1(&update, p1) ;
	Thread thread2(&update, p2) ;
	Thread thread3(&update, p3) ;
	Thread controlThread(&control,p0) ;
	RenderParam p4(&image,&texture,&sprite,&window) ;
	Thread renderThread(&render,p4) ;
	renderThread.launch() ;
	
	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		thread0.launch() ;
		thread1.launch() ;
		thread2.launch() ;
		thread3.launch() ;
		controlThread.launch() ;
		
		dt = deltaTime.restart().asSeconds() ;
	}
}

