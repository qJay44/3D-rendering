#include <algorithm>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "mat.hpp"

#define WIDTH 1200
#define HEIGHT 720

int main() {
  sf::RenderWindow window;
  sf::Font font;

  // Setup main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "3D rendering", sf::Style::Close);
  window.setFramerateLimit(90);

  float distance = 2.5f;
  float boxSize = 50.f;
  float boxSizeHalf = boxSize * 0.5f;
  sf::Vector2f boxPos = {WIDTH * 0.5f - boxSizeHalf, HEIGHT * 0.5f - boxSizeHalf};

  sf::CircleShape points[8];
  for (sf::CircleShape& p : points) {
    constexpr float radius = 3.f;
    p.setRadius(radius);
    p.setOrigin({radius, radius});
  }

  // Placing dots around top-left corner
  mat<3, 1> pointsMat[8] {
    {-boxSizeHalf, -boxSizeHalf, -boxSizeHalf},
    { boxSizeHalf, -boxSizeHalf, -boxSizeHalf},
    { boxSizeHalf,  boxSizeHalf, -boxSizeHalf},
    {-boxSizeHalf,  boxSizeHalf, -boxSizeHalf},
    {-boxSizeHalf, -boxSizeHalf,  boxSizeHalf},
    { boxSizeHalf, -boxSizeHalf,  boxSizeHalf},
    { boxSizeHalf,  boxSizeHalf,  boxSizeHalf},
    {-boxSizeHalf,  boxSizeHalf,  boxSizeHalf}
  };

  double angle = 0.01;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyReleased)
        switch (event.key.code) {
          case sf::Keyboard::Q:
            window.close();
            break;
          default:
            break;
        }

      if (event.type == sf::Event::MouseWheelScrolled)
        distance = std::max((distance + event.mouseWheelScroll.delta * 0.25f), 0.1f);
    }

    window.clear();

    for (int i = 0; i < 8; i++) {
      mat<3, 1> pointMat = pointsMat[i];
      pointMat.rotateX(angle);
      pointMat.rotateY(angle);
      pointMat.rotateZ(angle);
      pointMat.project(distance);
      points[i].setPosition(sf::Vector2f(pointMat.m[0], pointMat.m[1]) + boxPos);
      window.draw(points[i]);
    }

    sf::VertexArray lines{sf::Lines};
    for (int i = 0; i < 4; i++) {
      lines.append(points[i].getPosition());
      lines.append(points[(i + 1) % 4].getPosition());

      lines.append(points[i + 4].getPosition());
      lines.append(points[((i + 1) % 4) + 4].getPosition());

      lines.append(points[i].getPosition());
      lines.append(points[i + 4].getPosition());
    }
    window.draw(lines);

    window.display();

    angle += 0.03;
  }

	return 0;
}

