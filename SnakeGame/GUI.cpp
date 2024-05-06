#include "GUI.h"

GUI::GUI(int WIDTH, int HEIGHT, int x_OFFSET, sf::Texture& TEXTURE) :spriteSize{16}
{
	n = WIDTH; m = HEIGHT; offsetX = x_OFFSET; sBackground = sf::Sprite(TEXTURE);
		width = spriteSize * n;
}

void GUI::Draw(sf::RenderWindow& WINDOW)
{
	int N = offsetX + n;
	for (int i = offsetX; i < N; i++)
	{
		for (int j = 0; j < m; j++)
		{//Background//
			sBackground.setPosition(i * spriteSize,j * spriteSize);
			WINDOW.draw(sBackground);
		}
	}
	int index{ 0 };
	for (int i = 0; i < 2; i++)
	{
		Widgits[i].sprite.setPosition((Widgits[i].localX + offsetX) * spriteSize, (Widgits[i].localY + 0) * spriteSize);
		WINDOW.draw(Widgits[i].sprite);
		if (Widgits[i].dynamic == true)
		{
			Widgits[i].name.setPosition((Widgits[i].localX + offsetX)* spriteSize,(index*4)*spriteSize);
			WINDOW.draw(Widgits[i].name);
			Widgits[i].breath.setPosition(offsetX * spriteSize, ((index * 6) + 2) * spriteSize);
			WINDOW.draw(Widgits[i].breath);
			Widgits[i].score.setPosition(offsetX * spriteSize, ((index * 6) + 4) * spriteSize);
			WINDOW.draw(Widgits[i].score);

		}
	}
}

void GUI::AddWidgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE)
{
	Widgits.push_back(Widgit(OFFSETX, OFFSETY, TEXTURE));
}
void GUI::AddWidgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE, std::string NAME, sf::Font& FONT)
{
	Widgits.push_back(Widgit(OFFSETX, OFFSETY, TEXTURE, NAME, FONT));
}
