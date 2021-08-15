#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include "varfunc.h" //Глобальные переменные, константы и прототипы функции

void drawButton(button &butt)//Рисование кнопки
{
   setfillstyle(SOLID_FILL,COLOR(89, 106, 203));
   if(butt.img == NULL) bar(butt.posX,butt.posY,butt.posX + butt.sizeX,butt.posY+butt.sizeY);
   else putimage(butt.posX,butt.posY,butt.img,COPY_PUT);
   setbkmode(TRANSPARENT);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   outtextxy(butt.posX + butt.sizeX/2,butt.posY+butt.sizeY/2,butt.str.c_str());
}

int isButtonClicked(button &butt)//Проверка нажатия на данную кнопку
{
   if(mouseReleased == 1 && mousex() >= butt.posX && mousex() <= butt.posX + butt.sizeX && mousey() >= butt.posY && mousey() <= butt.posY + butt.sizeY) return 1;
   return 0;
}

button createButton(int posX, int posY,int sizeX, int sizeY, string str, IMAGE *img)//Конструктор кнопки
{
   button buf;
   buf.posX = posX;
   buf.posY = posY;
   buf.sizeX = sizeX;
   buf.sizeY = sizeY;
   buf.str = str;
   buf.img = img;
   return buf;
}

void mouseDetect()//Проверка на отжатия како-либо кнопки мыши
{
   if(mouseReleased != 0)
   {
      mouseReleased = 0;
   }
   if(mousePressed != mousebuttons())
   {
      mouseReleased = mousePressed;
      mousePressed = mousebuttons();
   }
}