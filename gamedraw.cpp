#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include "varfunc.h" //Глобальные переменные, константы и прототипы функции

void drawGame() //Рисование игры
{
   IMAGE *bufbackground = loadBMP("background.jpg");;
   IMAGE *bufbars = loadBMP("bars.jpg");
   IMAGE *bufcross = loadBMP("cross.bmp");
   IMAGE *buftimeBG = loadBMP("bttn.bmp");
   
   IMAGE *timeBG = resize(buftimeBG,80,40);
   freeimage(buftimeBG);
   IMAGE *bars = resize(bufbars,CELLSIZEX*8+50,CELLSIZEY*8+50);
   freeimage(bufbars);
   IMAGE *background = resize(bufbackground,WINDOWSIZEX,WINDOWSIZEY);
   freeimage(bufbackground);
   IMAGE* cross = resize(bufcross,64,64);
   freeimage(bufcross);
   
   int timePassed;
   string timeStr;
   string currMoveStr = "Текущий ход: ";
   
   button returnButton = createButton(0,0,64,64,"",cross); //Кнопка возврата в главное меню

   int MOVESTATUS = 0;
   int isMoving = 0;
   int ID = -1;

   int p=0; // сначала текущая видимая страница 0
   int t=0; // номер кадра (время)
   while(1)
   {      
      timePassed = time(NULL)-Time;//Время, прошедшее с начала игры
      timeStr = to_string(timePassed/60)+":"+(timePassed%60 < 10?"0"+to_string(timePassed%60):to_string(timePassed%60));
      
      mouseDetect();
      p=1-p;
      setactivepage(p); // активная страница == 1-видимая
      clearviewport(); // закраска текущей страницы цветом фона
      ++t;

      putimage(0,0,background,COPY_PUT);
      putimage(STARTPOSX-25,STARTPOSY-25,bars,COPY_PUT);
      
      putimage(457,10,timeBG,COPY_PUT);
      outtextxy(500,35,timeStr.c_str());
      
      outtextxy(500,90,(currMoveStr+(currentMove == WHITE?"Белые":"Черные")).c_str());
      
      drawButton(returnButton);
      if(isButtonClicked(returnButton))//возвращение в меню
      {
         setvisualpage(p);
         freeimage(background);
         freeimage(bars);
         freeimage(cross);
         freeimage(timeBG);    
         gameStatus = 0;
         return;
      }
      int x,y;
      if(MOVESTATUS == 0)
      {
         MOVESTATUS = 1;
         if(!markAvailCells())//Нету  шашек, доступных для хода
         {
            setvisualpage(p);
            freeimage(background);
            freeimage(bars);
            freeimage(cross);
            freeimage(timeBG);    
            drawGameFinished(2);//Заканчиваем игру
            return;
         }          
      }
      if(returnFieldXY(x,y)) //Была ли нажата какая-либо клетка на поле
      {
         if(MOVESTATUS == 1)//Игрок в стадии поиска шашки для хода
         {
            if(cellType[x][y] == 1)//Игрок выбрал шашку
            {
               ID = returnCheq(x,y);
               chosenCellX = x;
               chosenCellY = y;
               freeCells();
               markPath(ID);
               MOVESTATUS = 2;
            }
         }
         else if(MOVESTATUS == 2)//Игрок выбрал клетку для пермещения шашки
         {
            if(x == chosenCellX && y == chosenCellY && isMoving == 0)//Координаты клетки совпадает с координатой выбранной шашки
            {
               freeCells();
               chosenCellX = -1;
               chosenCellY = -1;
               MOVESTATUS = 0;
               ID = -1;
            }
            else if(cellType[x][y] == 2)
            {
               int k = moveCheq(ID,x,y); 
               chosenCellX = x;
               chosenCellY = y;
               if(Cheques[ID].color == WHITE && Cheques[ID].posY == 0) Cheques[ID].queen = 1;
               if(Cheques[ID].color == BLACK && Cheques[ID].posY == FIELDSIZE-1) Cheques[ID].queen = 1;
               freeCells();
               if(isCheqAvailable(ID) == 2 && k == 1)//Если есть еще доступные шашки для срубания, то продолжаем ход
               {
                  isMoving = 1;
                  markPath(ID);
               }
               else //смена хода
               {
                  chosenCellX = -1;
                  chosenCellY = -1;
                  isMoving = 0;
                  removeDestroyedCheq();
                  MOVESTATUS = 0;
                  ID = -1;
                  currentMove = currentMove==WHITE?BLACK:WHITE;
                  if(!checkCheqsExist()) //Есть шашки у игрока?
                  {
                     setvisualpage(p);
                     freeimage(background);
                     freeimage(bars);
                     freeimage(cross);
                     freeimage(timeBG);    
                     drawGameFinished(1);//Заканчиваем игру
                     return;
                  }
               }
            }
         }
      }
      drawField();
      setvisualpage(p);
   }
}

void markPath(int ID)//Поиск доступных клеток для хода для шашки
{
   if(Cheques[ID].queen == 0)
   {
      if(isCheqAvailable(ID) == 1) //У шашки есть свободная клетка для хода
      {
         if(Cheques[ID].color == WHITE)
         {
            if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY-1) == 1) cellType[Cheques[ID].posX -1][Cheques[ID].posY-1] = 2;
            if(isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY-1) == 1) cellType[Cheques[ID].posX +1][Cheques[ID].posY-1] = 2;
         }
         else
         {
            if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY+1) == 1) cellType[Cheques[ID].posX -1][Cheques[ID].posY+1] = 2;
            if(isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY+1) == 1) cellType[Cheques[ID].posX +1][Cheques[ID].posY+1] = 2;          
         }
      }
      else //У шашки на пути хода есть шашка противника
      {
         if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY-1) == 2 && 
            Cheques[returnCheq(Cheques[ID].posX -1,Cheques[ID].posY-1)].color != Cheques[ID].color  
            && isCeilFree(Cheques[ID].posX-2,Cheques[ID].posY-2) == 1) cellType[Cheques[ID].posX -2][Cheques[ID].posY-2] = 2;
         if(isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY-1) == 2 
            && Cheques[returnCheq(Cheques[ID].posX +1,Cheques[ID].posY-1)].color != Cheques[ID].color 
            && isCeilFree(Cheques[ID].posX+2,Cheques[ID].posY-2) == 1) cellType[Cheques[ID].posX +2][Cheques[ID].posY-2] = 2;
         if(isCeilFree(Cheques[ID].posX +1,Cheques[ID].posY+1) == 2 
            && Cheques[returnCheq(Cheques[ID].posX +1,Cheques[ID].posY+1)].color != Cheques[ID].color 
            && isCeilFree(Cheques[ID].posX+2,Cheques[ID].posY+2) == 1) cellType[Cheques[ID].posX +2][Cheques[ID].posY+2] = 2;     
         if(isCeilFree(Cheques[ID].posX -1,Cheques[ID].posY+1) == 2 
            && Cheques[returnCheq(Cheques[ID].posX -1,Cheques[ID].posY+1)].color != Cheques[ID].color 
            && isCeilFree(Cheques[ID].posX-2,Cheques[ID].posY+2) == 1) cellType[Cheques[ID].posX -2][Cheques[ID].posY+2] = 2; 
      }
   }
   else //Если шашка дамка
   {
      for(int k = 0; k < 4; k++)
      {
         int goX, goY;
         if(k == 0) {goX = 1; goY = 1;}
         if(k == 1) {goX = 1; goY = -1;}
         if(k == 2) {goX = -1; goY = 1;}
         if(k == 3) {goX = -1; goY = -1;}
         int X = Cheques[ID].posX, Y = Cheques[ID].posY;
         if(isCheqAvailable(ID) == 1) //Если у шашки есть свбодные клетки для хода
         {
            do//Отметка всех доступных клеток по диагоналям
            {
               X+=goX;
               Y+=goY;
               if(isCeilFree(X,Y) == 1) cellType[X][Y] = 2;
            }
            while(isCeilFree(X,Y) == 1);
         }
         else //Если хотя бы на одной из диагонали присутствует пешка противника доступная для срубания
         {
            int fl = 0; //есть на диагонали доступная шашка для срубания
            do
            {
               X+=goX;
               Y+=goY;
               if(isCeilFree(X,Y) == 1 && fl == 1) cellType[X][Y] = 2; //Отметка всех клеток доступных по диагонали после шашки противника
               if(fl == 1 && isCeilFree(X,Y) != 1) break;
               if(isCeilFree(X,Y) == 2 && Cheques[returnCheq(X,Y)].color != Cheques[ID].color && isCeilFree(X+goX,Y+goY) == 1 && fl == 0) //Шашка противника найдена
               {
                  cellType[X+goX][Y+goY] = 2;
                  fl = 1;
               }
               if(isCeilFree(X,Y) == 2 && Cheques[returnCheq(X,Y)].color == Cheques[ID].color && fl == 0) break;
               if(isCeilFree(X,Y) == 2 && (isCeilFree(X+goX,Y+goY) == 2 || isCeilFree(X+goX,Y+goY) == 0) && fl == 0) break;
            }
            while(isCeilFree(X,Y) != 0);
         }
      }
   }
}

void freeCells()//Убрать отметку у всех клеток
{
   for(int i = 0; i < FIELDSIZE; i++)
   {
      for(int j = 0; j < FIELDSIZE; j++) cellType[j][i] = 0;
   }
}

void drawCheques()//Рисование шашек
{
   for(int i = 0; i < CHEQCOUNT; i++)
   {
      if(!Cheques[i].exist && !Cheques[i].justRemoved) continue;
      if(Cheques[i].color == WHITE) drawimage(STARTPOSX+Cheques[i].posX*CELLSIZEX+2,STARTPOSY+Cheques[i].posY*CELLSIZEY+2,CheqBMP[1],CheqBMP[0]);
      else drawimage(STARTPOSX+Cheques[i].posX*CELLSIZEX+2,STARTPOSY+Cheques[i].posY*CELLSIZEY+2,CheqBMP[3],CheqBMP[2]);
      if(Cheques[i].queen) drawimage(STARTPOSX+Cheques[i].posX*CELLSIZEX+12,STARTPOSY+Cheques[i].posY*CELLSIZEY+10,queenBMP[1],queenBMP[0]);
      if(Cheques[i].justRemoved) drawimage(STARTPOSX+CELLSIZEX*Cheques[i].posX,STARTPOSY+CELLSIZEY*Cheques[i].posY,remCheqBMP[1],remCheqBMP[0]);
   }
}

void drawField()//Рисование поля
{
   int currentColor = WHITE;
   int DARKRED = COLOR(150,0,0);
   setfillstyle(SOLID_FILL,currentColor);
   for(int i = 0; i < FIELDSIZE; i++)
   {
      for(int j = 0; j < FIELDSIZE; j++)
      {
         if(j == chosenCellX && i == chosenCellY) setfillstyle(SOLID_FILL,COLOR(0,100,0));//Клетка, на которой стоит выбранная шашка игроком
         if(cellType[j][i] == 1) setfillstyle(SOLID_FILL,COLOR(0,100,0));//Клетка, на которой стоит шашка, доступная для хода игроком
         if(cellType[j][i] == 2) setfillstyle(SOLID_FILL,COLOR(0,255,0));//Клетка, доступная для перемещения выбранной шашки
         bar(STARTPOSX + j*CELLSIZEX,STARTPOSY + i*CELLSIZEY,STARTPOSX +( j+1)*CELLSIZEX,STARTPOSY +(i+1)*CELLSIZEY);
         if(j != FIELDSIZE-1)
         {
            if(currentColor == WHITE) currentColor = DARKRED;
            else currentColor = WHITE;
         }
         setfillstyle(SOLID_FILL,currentColor);
      }
   }
   drawCheques();
}

int markAvailCells()//Отметка тех клеток, которые доступны для хода игрок
{
   int n = 0;
   for(int i = 0; i < CHEQCOUNT; i++)
   {
      if(isCheqAvailable(i) == 2 && Cheques[i].color == currentMove)
      {
         n++;
         cellType[Cheques[i].posX][Cheques[i].posY] = 1;
      }
   }
   if(n == 0) 
   {
      for(int i = 0; i < CHEQCOUNT; i++)
      {
         if(isCheqAvailable(i) == 1 && Cheques[i].color == currentMove)
         {
            n++;
            cellType[Cheques[i].posX][Cheques[i].posY] = 1;
         }
      }    
   }
   if(n > 0) return 1; //Хотя бы шашка имеет доступных ход
   return 0;//Нету доступных шашек для хода
}

void drawGameFinished(int type) //Рисование окна после выигрыша одного из игроков
{
   IMAGE *bufbackground = loadBMP("background.jpg");;
   IMAGE *bufbtnImage = loadBMP("bttn.bmp");
   IMAGE *background = resize(bufbackground,WINDOWSIZEX,WINDOWSIZEY);
   freeimage(bufbackground);
   IMAGE* btnImage = resize(bufbtnImage,400,150);
   string stats[5];
   if(currentMove == WHITE) stats[0] = "Игрок 2 победил!";
   else stats[0] = "Игрок 1 победил!";
   if(type == 1) stats[1] = "У противника не осталось шашек на поле.";
   else stats[1] = "У противника не осталось свободных ходов.";
   int N1 = 0, N2 = 0;
   for(int i = 0; i < CHEQCOUNT; i++)
   {
      if(Cheques[i].color == WHITE && Cheques[i].exist == 0) N1++;
      if(Cheques[i].color == BLACK && Cheques[i].exist == 0) N2++;
   }
   int currTime = time(NULL)-Time;
   stats[2] = "Белых шашек срублено: "+to_string(N1)+"/12";
   stats[3] = "Черных шашек срублено: "+to_string(N2)+"/12";
   stats[4] = "Время игры: "+to_string(currTime/60)+":"+(currTime%60 < 10?"0"+to_string(currTime%60):to_string(currTime%60));
   
   button buttonRestart = createButton(350,500, 300,90, "Начать заново",bufbtnImage);
   button buttonReturn = createButton(350, 600, 300, 90, "Главное меню",bufbtnImage);
   
   putimage(0,0,background,COPY_PUT);
   putimage(305,215,btnImage,COPY_PUT);
   drawButton(buttonRestart);
   drawButton(buttonReturn);
   for(int i = 0; i < 5; i++) outtextxy(512,250+20*i,stats[i].c_str());
   while(1)
   {
      mouseDetect();
      if(isButtonClicked(buttonRestart))
      {
         freeimage(background);
         freeimage(btnImage);
         freeimage(bufbtnImage);
         startGame();
         return;
      }
      if(isButtonClicked(buttonReturn))
      {
         freeimage(background);
         freeimage(btnImage);
         freeimage(bufbtnImage);
         gameStatus = 0;
         return;
      }
   }
}