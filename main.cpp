#include <SMLF/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field [M][N] = {0};

struct Point
{int x,y;} a[4], b[4];

int figures[7][4] =
{
  1,3,5,7, // образует фигуру в виде легендандарной палки
  2,4,5,7, // образует фигуру в виде зигзага
  3,5,4,6, // ещё один зигзаг, но в другую сторону
  3,5,4,7, // т-образная фигура
  2,3,5,7, // фигура - уголок в виде буквы L
  3,5,7,6, // фигура - уголок в виде L, но в другую сторону
  2,3,4,5, // фигура в виде квадрата
};

bool check()
{
  for (int i=0; i<4; i++)
    if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
    else if (field[a[i].y][a[i].x]) return 0;
  
  return 1;
};

int main()
{
  srand(time(0));
  
  RenderWindow window(VideoMode(320, 480), "TETRIS");
  
  Texture k;
  k.loadFromFile("textures/kubiki.png");
  
  Sprite s(k);
  s.setTextureReact(IntReact(0,0,18,18)); //размер кубика 18 пискселей
  
  int dx=0;
  bool r=0;
  int colorNum=1;
  float timer=0, delay=0.2;
  
  Clock clock;
    
  while (window.isOpen())
  {
    float time = clock.getElapsedTime().asSeconds(); // переменная меняющее значение по времени, необходимая для падения фигуры
    clock.restart();
    timer+=time;
    
    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();
      
      if (e.type == Event::KeyPressed)
        if (e.key.code==Keyboard::Up) r=true;
        else if e.key.code==Keyboard::Left) dx=-1
        else if e.key.code==Keyboard::Right) dx=1;
    }
    
    for (int i=0; i<4; i++) a[i].x+=dx; //Движение фигуры от нажатия
    
    if (r) //если нажата клавиша поворота фигуры
    {
      Point p = a[1]; // центр поворота фигуры
      for (int i=0; i<4; i++)
      {
        int x = a[i].y-p.y;
        int y = a[i].x-p.x;
        a[i].x = p.x - x;
        a[i].y = p.y + y;
      }
      if (!check()) for (int i=0; i<4; i++) a[i] = b[i];
    }
    
    if (timer>delay) // падение фигуры
    {
      for (int i=0; i<4; i++) { b[i]=a[i]; a[i].y+=1;}
      
      if (!check())
      {
        for (int i=0; i<4; i++) field[b[i].y][b[i].x]=colorNum;
        
        colorNum = 1+rand()%7;
        int n=rand()%7;
        for (int i=0; i<4; i++)
        {
          a[i].x = figures[n][i] % 2;
          a[i].y = figures[n][i] / 2;
        }
      }
      
      timer=0;
    }
    
    dx=0;
    r=0;
    
   
    window.clear(Color::White);
    
    for (int i=0; i<M; i++)
      for (int j=0; j<N; j++)
      {
        if (field[i][j]==0) continue;
        s.setPosition(j*18, i*18);
        winow.draw(s);
      }
    
    for (int i=0; i<4; i++)
    {
      s.setPosition(a[i].x*18,a[i].y*18);
      window.draw(s);
    }                
    window.display();
  }
  
  return 0;
}
