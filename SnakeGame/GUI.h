#pragma once
#include <SFML/Graphics.hpp>
class GUI
{
private:
	sf::Texture tBackground;
	sf::Sprite sBackground;
	int n, m, spriteSize;
public:
	int	width{0};
	int offsetX{0};
	GUI() : spriteSize{0} {};
	GUI(int WIDTH, int HEIGHT, int OFFSET, sf::Texture& BACKGROUND);
	void Draw(sf::RenderWindow& WINDOW);

	class Widgit
	{
	private:
		std::string playerName;
		int Breath{ 0 };
		int Score{ 0 };
	public:
		sf::Text name, breath, score;
		bool dynamic{ false };
		int localX, localY;
		sf::Sprite sprite;

		Widgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE) : dynamic{false}, sprite{TEXTURE}, localX{OFFSETX}, localY{OFFSETY}{}
		Widgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE, std::string NAME, sf::Font& FONT)
			:dynamic{true}, sprite{TEXTURE}, localX{OFFSETX}, localY{OFFSETY}, playerName{NAME},
			name{playerName, FONT, 24},
			breath{"Breath", FONT, 12},
			score{"Score: 0", FONT, 24}{}
		//One of these two kept breaking so i initialised everything and it worked for some reason
		bool Update(std::string SCORE)
		{
			if (dynamic == true)
			{
				score.setString("Score:\n" + SCORE);
				return true;
			}
			else
			{
				return false;
			}
		}
		void BreathManager()
		{

		}
	};
	std::vector<Widgit> Widgits;
	void AddWidgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE);
	void AddWidgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE, std::string NAME, sf::Font& FONT);
};

