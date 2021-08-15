#pragma once

using namespace std;

struct cheq //��������� �����
{
   int posX;
   int posY;
   int color;
   int queen;
   int exist;
   int justRemoved;
};

struct button //��������� ������
{
   int posX;
   int posY;
   int sizeX;
   int sizeY;
   string str;
   IMAGE *img;
};

constexpr int WINDOWSIZEX = 1024; //������ ����
constexpr int WINDOWSIZEY = 768; //������ ����
constexpr int FIELDSIZE = 8; //���������� ������ �� ����������� � ���������
constexpr int CHEQCOUNT = 24; //���������� ����� �� ����
constexpr int STARTPOSX = 250; //���������� ������ ���� ������ ������ �� x
constexpr int STARTPOSY = 150;//���������� ������ ���� ������ ������ �� y
constexpr int CELLSIZEX= 70;//������ ������ �� �
constexpr int CELLSIZEY= 70;//������ ������ �� �

void drawCheques(); //��������� �����
void drawField(); //��������� ����
void drawimage(int x, int y, IMAGE *m,IMAGE *p); //������� �����������
void drawGame(); //��������� ��������� �������� ����
void drawMainMenu(); //��������� �������� ����
void startGame(); //��������� ��������� ���������� ����
void mouseDetect(); //������������� ��������� ������� ������ ����
void drawButton(button &butt); //��������� ������
void drawAboutProgramm(); //��������� ���� "� ���������"
void drawGameFinished(int type); //��������� ���� ����� ��������� ������
void freeCells(); //�������� ������� �� ���� ������ ����
void markPath(int ID); //����� ��������� ������ ��� ���� ��� �����
void drawHowToPlay();//��������� ���� "��� ������"
void removeDestroyedCheq(); //�������� ���� ���������� ����� � ���� ����� ��������� �������� �����
void freeButton(button &butt); //������������ ������ � ������ (�������� ��������)

int checkCheqsExist(); //�������� �� ����������� ����� ��� �������� ���� ������
int moveCheq(int ID, int x, int y);//����������� ������ �� ���������� 
int isCheqAvailable(int ID); //�������� ����������� ���� � �����
int markAvailCells();//������� ���� ��������� ������ ��� ���� ������
int returnCheq(int x, int y);//����� ����� �� �����������
int isCeilFree(int x, int y);//�������� �� ����������/���������� ����� �� ������
int returnFieldXY(int &x,int &y);//����� ������, �� ������� ����� �����
int isButtonClicked(button &butt);//�������� ������� �� ������ ������

extern int mousePressed ;//������� ������� ������
extern int mouseReleased;//���������� ������� ������
extern int currentMove;//���� �������� ���� 
extern int startedMoving;//����� � �������� ������������� �������� ����� ����������
extern int gameStatus;//��������� ���������
extern int Time;//����� ������ ����

extern int cellType[FIELDSIZE][FIELDSIZE];//��������� ������
extern cheq Cheques[CHEQCOUNT];//������ �������� ������ �����
extern IMAGE *CheqBMP[4];//����������� ����� � �����
extern IMAGE *queenBMP[2];//����������� ����� � �����
extern int chosenCellX;//���������� ��������� ������
extern int chosenCellY;//
extern IMAGE* remCheqBMP[2];//����������� �������� � �����

IMAGE *createmask(IMAGE *p);//�������� �����
IMAGE *resize(IMAGE *p, int w, int h);//��������� ������� �����������

button createButton(int posX, int posY,int sizeX, int sizeY,string str, IMAGE *img);//����������� ������