#pragma once
#include <SFML/Graphics.hpp>
class GUI
{
private:
	sf::Texture tBackground;
	sf::Sprite sBackground;
	int n, m, spriteSize;
public:
	int	width;
	int offsetX;
	GUI() {};
	GUI(int WIDTH, int HEIGHT, int OFFSET, sf::Texture& BACKGROUND);
	void Draw(sf::RenderWindow& WINDOW);

	class Widgit
	{
	public:
		std::string name;
		sf::Sprite sprite;
		int localX, localY;
		int Breath;
		int Score{0};
		Widgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE)
		{
			localX = OFFSETX; localY = OFFSETY; sprite = sf::Sprite(TEXTURE);
		}
		void ScoreManager()
		{

		}
		void BreathManager()
		{

		}
	};
	std::vector<Widgit> Widgits;
	void AddWidgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE);
};

