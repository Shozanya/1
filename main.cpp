#include <SMLF/Graphics.hpp>
#include <time.h>
using namespace sf;

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
    window.clear(Color::White);
    window.draw(s);
    window.display();
  }
  
  return 0;
}
