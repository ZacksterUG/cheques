#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include "varfunc.h" //Глобальные переменные, константы и прототипы функции
using namespace std;

int cellType[FIELDSIZE][FIELDSIZE];//Состояние клетки
cheq Cheques[CHEQCOUNT];//Массив структур данных шашек
IMAGE *CheqBMP[4];//Изображение шашек и маски
IMAGE *queenBMP[2];//Изображение дамки и маска
IMAGE* remCheqBMP[2];//Изображение крестика и маска
int chosenCellX;//Координаты выбранной клетки
int chosenCellY;//

int currentMove = WHITE;//Цвет текущего хода 
int startedMoving = 0;//Игрок в процессе многократного срубание шашек противника
int gameStatus = 0;//Состояние программы
int Time = 0;//Время начала игры
int mousePressed = 0;//текущая нажатая кнопка
int mouseReleased = 0;//предыдущая нажатая кнопка

int main()
{
   initwindow(WINDOWSIZEX,WINDOWSIZEY,"Шашки");
   
   //Загрузка изображений
   CheqBMP[0] = loadBMP("white.bmp");
   CheqBMP[0] = resize(CheqBMP[0],CELLSIZEX-5,CELLSIZEY-5);
   CheqBMP[1] = createmask(CheqBMP[0]);
   CheqBMP[2] = loadBMP("black.bmp");
   CheqBMP[2] = resize(CheqBMP[2],CELLSIZEX-5,CELLSIZEY-5);
   CheqBMP[3] = createmask(CheqBMP[2]);
   queenBMP[0] = loadBMP("queen.bmp");
   queenBMP[0] = resize(queenBMP[0],45,45);
   queenBMP[1] = createmask(queenBMP[0]);
   remCheqBMP[0] = loadBMP("remcheq.bmp");
   remCheqBMP[1] = createmask(remCheqBMP[0]);
   
   while(1)
   {
      switch(gameStatus) //Текущее состояние программы
      {
         case -1: //Программа завершила работу
         {
            //Завершение работы
            closegraph();
            return 0;
         }
         case 0://Программа в состоянии главного меню
         {
            drawMainMenu();
            break;
         }
         case 1://Программа в состоянии игры
         {
            drawGame();
            break;
         }
         case 2://Программа в состоянии "Как играть"
         {
            drawHowToPlay();
            break;
         }
         case 3://Программа в состоянии "О программе"
         {
            drawAboutProgramm();
            break;
         }
      }
   }
   closegraph();
}

void drawHowToPlay()//Рисование окна "Как играть"
{
   IMAGE *bufbtnImage = loadBMP("bttn.bmp");
   IMAGE *bufBackground = loadBMP("background.jpg");;
   IMAGE* imgRules = loadBMP("rules.jpg");
   IMAGE* imgTutorial = loadBMP("guide.jpg");
   IMAGE* btnImage = resize(bufbtnImage,300/1.5,90/1.5);
   freeimage(bufbtnImage);
   int clicked = 0;//Отвечает за то, какая из 2ух кнопок нажата
   button returnButton = createButton(0,0,300/1.5,90/1.5,"Главное меню",btnImage);
   button rulesButton = createButton(350,0,300/1.5,90/1.5,"Правила игры",btnImage);
   button tutorialButton = createButton(560,0,300/1.5,90/1.5,"Обучение",btnImage);
   IMAGE *background = resize(bufBackground,WINDOWSIZEX,WINDOWSIZEY); 
   freeimage(bufBackground);
   putimage(0,0,background,COPY_PUT);
   drawButton(returnButton);
   drawButton(rulesButton);
   drawButton(tutorialButton);
   while(1) 
   {
      mouseDetect();
      if(isButtonClicked(rulesButton)) clicked = 1; //Нажата кнопка правил игры
      if(isButtonClicked(tutorialButton)) clicked = 2;//Нажата кнопка обучения
      if(isButtonClicked(returnButton))
      {
         gameStatus = 0;
         break;
      }
      if(clicked == 1) 
      {
         clicked = 0;
         putimage(0,0,background,COPY_PUT);
         drawButton(returnButton);
         drawButton(rulesButton);
         drawButton(tutorialButton);
         putimage(200,200,imgRules,COPY_PUT);//Выводит правила игры
      }
      if(clicked == 2) 
      {
         clicked = 0;
         putimage(0,0,background,COPY_PUT);
         drawButton(returnButton);
         drawButton(rulesButton);
         drawButton(tutorialButton);
         putimage(200,200,imgTutorial,COPY_PUT);//Выводит обучающее окно
      }
   }
   freeimage(btnImage);
   freeimage(imgRules);
   freeimage(imgTutorial);
   freeimage(background);
}

void drawAboutProgramm()//Рисование окна о программе
{
   IMAGE *bufBackground = loadBMP("background.jpg");;
   IMAGE *aboutimage = loadBMP("about.jpg");
   IMAGE *btnImage = loadBMP("bttn.bmp"); 
   IMAGE *background = resize(bufBackground,WINDOWSIZEX,WINDOWSIZEY);
   freeimage(bufBackground);
   button returnButton = createButton(0,0,300,90,"Главное меню",btnImage);
   setbkmode(TRANSPARENT);
   putimage(0,0,background,COPY_PUT);
   drawButton(returnButton);
   putimage(300,200,aboutimage,COPY_PUT);
   while(1)
   {
      mouseDetect();
      if(isButtonClicked(returnButton))
      {
         gameStatus = 0;
         break;
      }
   }
   freeimage(background);
   freeimage(aboutimage);
   freeimage(btnImage);
}

void drawMainMenu()
{
   IMAGE *bufBackground = loadBMP("bgmain.jpg");
   IMAGE *btnImage = loadBMP("bttn.bmp");
   IMAGE *background = resize(bufBackground,WINDOWSIZEX,WINDOWSIZEY);
   freeimage(bufBackground);
   //Создание кнопок главного меню
   button playButton = createButton(350,275,300,90,"Играть",btnImage);
   button howtpButton = createButton(350,375,300,90,"Как играть",btnImage);
   button aboutButton = createButton(350,475,300,90,"О программе",btnImage);
   button exitButton = createButton(350,575,300,90,"Выход",btnImage);
   
   putimage(0,0,background,COPY_PUT);
   drawButton(playButton);
   drawButton(howtpButton);
   drawButton(aboutButton);
   drawButton(exitButton);
   while(1)
   {
      mouseDetect();
      
      if(isButtonClicked(playButton))//Игрок нажал на кнопку игры
      {
         startGame();
         gameStatus = 1;
         break;
      }
      if(isButtonClicked(howtpButton))//Игрок нажал на копку "Как играть"
      {
         gameStatus = 2;
         break;
      }
      if(isButtonClicked(aboutButton))//Игрок нажал на кнопку "О программе"
      {
         gameStatus = 3;
         break;
      }
      if(isButtonClicked(exitButton))//Игрок нажал на кнопку выхода
      {
         gameStatus = -1;
         break;
      }
   }
   freeimage(background);
   freeimage(btnImage);
}