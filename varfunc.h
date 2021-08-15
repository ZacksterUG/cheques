#pragma once

using namespace std;

struct cheq //Струкутра шашки
{
   int posX;
   int posY;
   int color;
   int queen;
   int exist;
   int justRemoved;
};

struct button //Структура кнопки
{
   int posX;
   int posY;
   int sizeX;
   int sizeY;
   string str;
   IMAGE *img;
};

constexpr int WINDOWSIZEX = 1024; //ширина окна
constexpr int WINDOWSIZEY = 768; //высота окна
constexpr int FIELDSIZE = 8; //количество клеток по горизонтали и вертикали
constexpr int CHEQCOUNT = 24; //количество шашек на поле
constexpr int STARTPOSX = 250; //координата левого угла первой клетки по x
constexpr int STARTPOSY = 150;//координата левого угла первой клетки по y
constexpr int CELLSIZEX= 70;//Размер клетки по Х
constexpr int CELLSIZEY= 70;//Размер клетки по У

void drawCheques(); //Рисование шашек
void drawField(); //Рисование поля
void drawimage(int x, int y, IMAGE *m,IMAGE *p); //Вставка изображения
void drawGame(); //Рисование элементов процесса игры
void drawMainMenu(); //Рисование главного меню
void startGame(); //Установка начальных параметров игры
void mouseDetect(); //устанваливает последнюю отжатую кнопку мыши
void drawButton(button &butt); //Рисование кнопки
void drawAboutProgramm(); //Рисование окна "О программе"
void drawGameFinished(int type); //Рисование игры после окончание партии
void freeCells(); //Убирание отметок со всех клеток поля
void markPath(int ID); //Поиск доступных клеток для хода для шашки
void drawHowToPlay();//Рисование окна "Как играть"
void removeDestroyedCheq(); //убирание всех срубленных шашек с поля после окончания срубания шашек
void freeButton(button &butt); //освобождение памяти у кнопки (удаление картинки)

int checkCheqsExist(); //Проверка на присутствие шашки для текущего хода игрока
int moveCheq(int ID, int x, int y);//Переместить клетку на координату 
int isCheqAvailable(int ID); //Проверка доступность хода у шашки
int markAvailCells();//Отметка всех доступных клеток для хода игрока
int returnCheq(int x, int y);//Поиск шашки по координатам
int isCeilFree(int x, int y);//проверка на присутсвие/отсутствие шашки на клетке
int returnFieldXY(int &x,int &y);//Поиск клетки, на которую нажал игрок
int isButtonClicked(button &butt);//Проверка нажатия на данную кнопку

extern int mousePressed ;//текущая нажатая кнопка
extern int mouseReleased;//предыдущая нажатая кнопка
extern int currentMove;//Цвет текущего хода 
extern int startedMoving;//Игрок в процессе многократного срубание шашек противника
extern int gameStatus;//Состояние программы
extern int Time;//Время начала игры

extern int cellType[FIELDSIZE][FIELDSIZE];//Состояние клетки
extern cheq Cheques[CHEQCOUNT];//Массив структур данных шашек
extern IMAGE *CheqBMP[4];//Изображение шашек и маски
extern IMAGE *queenBMP[2];//Изображение дамки и маска
extern int chosenCellX;//Координаты выбранной клетки
extern int chosenCellY;//
extern IMAGE* remCheqBMP[2];//Изображение крестика и маска

IMAGE *createmask(IMAGE *p);//Создание маски
IMAGE *resize(IMAGE *p, int w, int h);//Изменения размера изображения

button createButton(int posX, int posY,int sizeX, int sizeY,string str, IMAGE *img);//Конструктор кнопки