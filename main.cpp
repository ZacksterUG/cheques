#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include "varfunc.h" //���������� ����������, ��������� � ��������� �������
using namespace std;

int cellType[FIELDSIZE][FIELDSIZE];//��������� ������
cheq Cheques[CHEQCOUNT];//������ �������� ������ �����
IMAGE *CheqBMP[4];//����������� ����� � �����
IMAGE *queenBMP[2];//����������� ����� � �����
IMAGE* remCheqBMP[2];//����������� �������� � �����
int chosenCellX;//���������� ��������� ������
int chosenCellY;//

int currentMove = WHITE;//���� �������� ���� 
int startedMoving = 0;//����� � �������� ������������� �������� ����� ����������
int gameStatus = 0;//��������� ���������
int Time = 0;//����� ������ ����
int mousePressed = 0;//������� ������� ������
int mouseReleased = 0;//���������� ������� ������

int main()
{
   initwindow(WINDOWSIZEX,WINDOWSIZEY,"�����");
   
   //�������� �����������
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
      switch(gameStatus) //������� ��������� ���������
      {
         case -1: //��������� ��������� ������
         {
            //���������� ������
            closegraph();
            return 0;
         }
         case 0://��������� � ��������� �������� ����
         {
            drawMainMenu();
            break;
         }
         case 1://��������� � ��������� ����
         {
            drawGame();
            break;
         }
         case 2://��������� � ��������� "��� ������"
         {
            drawHowToPlay();
            break;
         }
         case 3://��������� � ��������� "� ���������"
         {
            drawAboutProgramm();
            break;
         }
      }
   }
   closegraph();
}

void drawHowToPlay()//��������� ���� "��� ������"
{
   IMAGE *bufbtnImage = loadBMP("bttn.bmp");
   IMAGE *bufBackground = loadBMP("background.jpg");;
   IMAGE* imgRules = loadBMP("rules.jpg");
   IMAGE* imgTutorial = loadBMP("guide.jpg");
   IMAGE* btnImage = resize(bufbtnImage,300/1.5,90/1.5);
   freeimage(bufbtnImage);
   int clicked = 0;//�������� �� ��, ����� �� 2�� ������ ������
   button returnButton = createButton(0,0,300/1.5,90/1.5,"������� ����",btnImage);
   button rulesButton = createButton(350,0,300/1.5,90/1.5,"������� ����",btnImage);
   button tutorialButton = createButton(560,0,300/1.5,90/1.5,"��������",btnImage);
   IMAGE *background = resize(bufBackground,WINDOWSIZEX,WINDOWSIZEY); 
   freeimage(bufBackground);
   putimage(0,0,background,COPY_PUT);
   drawButton(returnButton);
   drawButton(rulesButton);
   drawButton(tutorialButton);
   while(1) 
   {
      mouseDetect();
      if(isButtonClicked(rulesButton)) clicked = 1; //������ ������ ������ ����
      if(isButtonClicked(tutorialButton)) clicked = 2;//������ ������ ��������
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
         putimage(200,200,imgRules,COPY_PUT);//������� ������� ����
      }
      if(clicked == 2) 
      {
         clicked = 0;
         putimage(0,0,background,COPY_PUT);
         drawButton(returnButton);
         drawButton(rulesButton);
         drawButton(tutorialButton);
         putimage(200,200,imgTutorial,COPY_PUT);//������� ��������� ����
      }
   }
   freeimage(btnImage);
   freeimage(imgRules);
   freeimage(imgTutorial);
   freeimage(background);
}

void drawAboutProgramm()//��������� ���� � ���������
{
   IMAGE *bufBackground = loadBMP("background.jpg");;
   IMAGE *aboutimage = loadBMP("about.jpg");
   IMAGE *btnImage = loadBMP("bttn.bmp"); 
   IMAGE *background = resize(bufBackground,WINDOWSIZEX,WINDOWSIZEY);
   freeimage(bufBackground);
   button returnButton = createButton(0,0,300,90,"������� ����",btnImage);
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
   //�������� ������ �������� ����
   button playButton = createButton(350,275,300,90,"������",btnImage);
   button howtpButton = createButton(350,375,300,90,"��� ������",btnImage);
   button aboutButton = createButton(350,475,300,90,"� ���������",btnImage);
   button exitButton = createButton(350,575,300,90,"�����",btnImage);
   
   putimage(0,0,background,COPY_PUT);
   drawButton(playButton);
   drawButton(howtpButton);
   drawButton(aboutButton);
   drawButton(exitButton);
   while(1)
   {
      mouseDetect();
      
      if(isButtonClicked(playButton))//����� ����� �� ������ ����
      {
         startGame();
         gameStatus = 1;
         break;
      }
      if(isButtonClicked(howtpButton))//����� ����� �� ����� "��� ������"
      {
         gameStatus = 2;
         break;
      }
      if(isButtonClicked(aboutButton))//����� ����� �� ������ "� ���������"
      {
         gameStatus = 3;
         break;
      }
      if(isButtonClicked(exitButton))//����� ����� �� ������ ������
      {
         gameStatus = -1;
         break;
      }
   }
   freeimage(background);
   freeimage(btnImage);
}