#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include "varfunc.h" //√лобальные переменные, константы и прототипы функции

int returnCheq(int x, int y)//ѕоиск шашки по координатам
{
   for(int i = 0; i < CHEQCOUNT; i++)
   {
      if(Cheques[i].posX == x && Cheques[i].posY == y && Cheques[i].exist == 1) return i;
   }
   return -1;//≈сли не найдено
}

int returnFieldXY(int &x,int &y)//ѕоиск клетки, на которую нажал игрок
{
   if(mouseReleased == 1)
   {
      int xm,ym;
      xm = mousex();
      ym = mousey();
      x = (xm-STARTPOSX)/CELLSIZEX;
      y = (ym-STARTPOSY)/CELLSIZEY;
      if(xm < STARTPOSX || x > FIELDSIZE -1 || ym < STARTPOSY || y > FIELDSIZE - 1) // оординаты за пределами пол€?
      {
         x = -1;
         y = -1;
         return 0;
      }
      return 1; // летка найдена
   }
   return 0;// нопка не была нажата
}

void removeDestroyedCheq() //убирание всех срубленных шашек с пол€ после окончани€ срубани€ шашек
{
   for(int i = 0; i < CHEQCOUNT; i++) Cheques[i].justRemoved = 0;
}

int checkCheqsExist() //ѕроверка на присутствие хот€ бы одной существующей шашки дл€ хода текущего игрока
{
   for(int i = 0; i < CHEQCOUNT; i ++)
   {
      if(Cheques[i].exist == 1 && Cheques[i].color == currentMove) return 1;
   }
   return 0;
}

int moveCheq(int ID, int x, int y)
{
   int n = 0;
   int velX = (x-Cheques[ID].posX)>0?1:-1; // оординаты вектора движени€
   int velY = (y-Cheques[ID].posY)>0?1:-1;//
   int X = Cheques[ID].posX;
   int Y = Cheques[ID].posY;
   
   while(X != x && Y != y) //—рубание шашек противника на пути движени€
   {
      X+=velX;
      Y+=velY;
      if(isCeilFree(X,Y) == 2 && returnCheq(X,Y) != ID)
      {
         n = 1; //—рубил шашку
         Cheques[returnCheq(X,Y)].justRemoved = 1;
         Cheques[returnCheq(X,Y)].exist = 0;
         break;
      }
   }
   
   Cheques[ID].posX = x;
   Cheques[ID].posY = y;
   return n;
}

int isCheqAvailable(int ID)//ѕроверка доступность хода у шашки
{
   if(Cheques[ID].exist == 0 || ID < 0 || ID > CHEQCOUNT) return 0; //Ќет доступных ходов/не существует
   if(Cheques[ID].queen == 0)
   {
      //ѕроверка на то, есть где-то на пути шашка противника
      if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY-1) == 2 && Cheques[returnCheq(Cheques[ID].posX -1,Cheques[ID].posY-1)].color != Cheques[ID].color  && isCeilFree(Cheques[ID].posX-2,Cheques[ID].posY-2) == 1) return 2;
      if(isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY-1) == 2 && Cheques[returnCheq(Cheques[ID].posX +1,Cheques[ID].posY-1)].color != Cheques[ID].color && isCeilFree(Cheques[ID].posX+2,Cheques[ID].posY-2) == 1) return 2;
      if(isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY+1) == 2 && Cheques[returnCheq(Cheques[ID].posX +1,Cheques[ID].posY+1)].color != Cheques[ID].color && isCeilFree(Cheques[ID].posX+2,Cheques[ID].posY+2) == 1) return 2;     
      if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY+1) == 2 && Cheques[returnCheq(Cheques[ID].posX -1,Cheques[ID].posY+1)].color != Cheques[ID].color && isCeilFree(Cheques[ID].posX-2,Cheques[ID].posY+2) == 1) return 2; 
      //
      if(Cheques[ID].color == WHITE) 
      {
         if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY-1) == 1 || isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY-1) == 1) return 1;
      }
      else if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY+1) == 1 || isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY+1) == 1) return 1;
   }
   else
   {
      for(int k = 0; k < 4; k++)//ѕоиск шашек противника по всем диагонал€м
      {
         int goX, goY;
         if(k == 0) {goX = 1; goY = 1;}
         if(k == 1) {goX = 1; goY = -1;}
         if(k == 2) {goX = -1; goY = 1;}
         if(k == 3) {goX = -1; goY = -1;}
         int X = Cheques[ID].posX, Y = Cheques[ID].posY;
         do
         {
            X+=goX;
            Y+=goY;
            if(isCeilFree(X,Y) == 2 && Cheques[returnCheq(X,Y)].color != Cheques[ID].color && isCeilFree(X+goX,Y+goY) == 1) return 2;
            if(isCeilFree(X,Y) == 2 && (isCeilFree(X+goX,Y+goY) == 2 || isCeilFree(X+goX,Y+goY) == 0)) break;
            if(isCeilFree(X,Y) == 2 && Cheques[returnCheq(X,Y)].color == Cheques[ID].color) break;
         }
         while(isCeilFree(X,Y) != 0);
      }     
      //проверка на присутсвтие хот€ бы одной свободной клетки дл€ хода
      if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY-1) == 1) return 1;
      if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY+1) == 1) return 1;
      if(isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY-1) == 1) return 1;
      if(isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY+1) == 1) return 1;
   }
   return 0;//Ќет доступных ходов
}

int isCeilFree(int x, int y) //проверка на присутсвие/отсутствие шашки на клетке
{
   if(x < 0 || y < 0 || x >= FIELDSIZE || y >= FIELDSIZE) return 0;// летки не существует
   if(returnCheq(x,y) != -1) return 2;//Ќа клетке есть шашка
   return 1;// летка свободна€
}

void startGame() //”становка начальных значений перед началом игры
{
   currentMove = WHITE;
   Time = time(NULL);
   chosenCellX = -1;
   chosenCellY = -1;
   startedMoving = 0;
   int x = 1;
   int y = 0;
   int t = 0;
   for(int i = 0; i <  FIELDSIZE; i++)
   {
      for(int j = 0; j < FIELDSIZE; j++) cellType[j][i] = 0;
   }
   for(int i = 0; i < CHEQCOUNT; i++)//”стновка стандартных значений данных у шашек
   {
      if(i < CHEQCOUNT/2) Cheques[i].color = BLACK;
      else Cheques[i].color = WHITE;
      Cheques[i].exist = 1;
      Cheques[i].queen = 0;
      Cheques[i].posX = x;
      Cheques[i].posY = y;
      Cheques[i].justRemoved = 0;
      x+=2;
      if(x >= FIELDSIZE)
      {
         y++;
         if(i >= CHEQCOUNT/2-1)
         {
            y = FIELDSIZE-1-t;
            t++;
         }
      }
      x%=FIELDSIZE;
      if(x == 0) x++;
      else if(x == 1) x--;
   }
}