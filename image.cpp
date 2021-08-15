#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include "varfunc.h" //Глобальные переменные, константы и прототипы функции

// функция для создания маски
IMAGE *createmask(IMAGE *p)
{ 
  int w=imagewidth(p);
  int h=imageheight(p);
  IMAGE *m=createimage(w,h);
  int c=imagegetpixel(p,0,0);
  for(int x=0;x<w;++x)
    for(int y=0;y<h;++y)
    { int d=imagegetpixel(p,x,y);
      if(c==d)
      { imageputpixel(m,x,y,WHITE);
        imageputpixel(p,x,y,BLACK);
      }
      else
        imageputpixel(m,x,y,BLACK);
    }
  return m;
}

void drawimage(int x, int y, IMAGE *m,IMAGE *p)
{
  putimage(x,y,m,AND_PUT);
  putimage(x,y,p,OR_PUT);
}

IMAGE *resize(IMAGE *p, int w, int h)//Изменение размера изображения
{
  int wp=imagewidth(p);
  int hp=imageheight(p);
  IMAGE *r=createimage(w,h);
  for(int x=0;x<w; ++x)
    for(int y=0;y<h; ++y)
    {
      imageputpixel(r,x,y,imagegetpixel(p,x*wp/w,y*hp/h));
    }
  return r;
}
