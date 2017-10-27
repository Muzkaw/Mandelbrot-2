//This file is part of Mandelbrot Multithreaded(GNU GPL) - https://www.youtube.com/user/Muzkaw.

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace sf ;
using namespace std ;

Color colorGradient(Image &colors,float x) ;
float lerp(float x1,float x2,float y1,float y2,float x) ;