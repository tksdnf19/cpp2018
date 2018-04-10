#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2u size;
public:
	GameObject(const char *filename) {
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		size = texture.getSize();
	}

	void move() {}

	void draw(sf::RenderWindow &window)
	{
		window.draw(sprite);
	}
};

class Player : public GameObject
{
public:
	Player() : GameObject("images/player.png")
	{
	}
	void move()
	{
		auto pos = sprite.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (pos.x>0)
				sprite.move(-1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (pos.x<WINDOW_WIDTH - size.x)
				sprite.move(1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (pos.y>0)
				sprite.move(0, -1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (pos.y<WINDOW_HEIGHT - size.y)
				sprite.move(0, 1);
		}
	}
};

class Bullet : public GameObject {
public:
	Bullet() : GameObject("images/missile.png")
	{
		float x = rand() % WINDOW_WIDTH;
		float y = rand() % WINDOW_HEIGHT;
		sprite.setPosition(x, y);
	}
	void move() {
		auto pos = sprite.getPosition();
		if (pos.x < WINDOW_WIDTH) {
			sprite.move(1, 1);
		}
	}
};

void main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dodge Game");

	GameObject bg("images/background.png");

	Player player;
	Bullet bullets[100];

	int dx = 1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player.move();
		for (auto &b : bullets) {
			b.move();
		}

		window.clear();

		bg.draw(window);
		player.draw(window);
		for (auto &b : bullets) {
			b.draw(window);
		}

		window.display();
	}
}