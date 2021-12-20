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
  3,5,7,6, // фигура - уголо в виде L, но в другую сторону
  2,3,4,5, // фигура в виде квадрата
};
int main()
{
  RenderWindow window(VideoMode(320, 480), "TETRIS");
  
  Texture k;
  k.loadFromFile("textures/kubiki.png");
  
  Sprite s(k);
  s.setTextureReact(IntReact(0,0,18,18)); //размер кубика 18 пискселей
    
  while (window.isOpen())
  {
    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();
    }
    
    int n=3; // переменная n влияет на то какая фигура будет собрана, данный способ генерации мне пришлось подсмотреть)
    for (int i=0; i<4; i++)
    {
      a[i].x = figures[n][i] % 2;
      a[i].y = figures[n][i] / 2;
    }
    
    
    window.clear(Color::White);
    for (int i=0; i<4; i++)
    {
      s.setPosition(a[i].x*18,a[i].y*18;
      window.draw(s);
    }                
    window.display();
  }
  
  return 0;
}
