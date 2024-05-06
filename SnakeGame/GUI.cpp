#include "GUI.h"

GUI::GUI(int WIDTH, int HEIGHT, int x_OFFSET, sf::Texture& TEXTURE)
{
	n = WIDTH; m = HEIGHT; offsetX = x_OFFSET; sBackground = sf::Sprite(TEXTURE);
		spriteSize = TEXTURE.getSize().x;
		width = spriteSize * n;
}

void GUI::Draw(sf::RenderWindow& WINDOW)
{
	int N = offsetX + n;
	for (int i = offsetX; i < N; i++)
	{
		for (int j = 0; j < m; j++)
		{//Background//
			sBackground.setPosition((i) * spriteSize,j * spriteSize);
			WINDOW.draw(sBackground);
		}
	}
	for (auto& w : Widgits)
	{
		w.sprite.setPosition((w.localX + offsetX) * spriteSize, (w.localY + 0) * spriteSize);
		WINDOW.draw(w.sprite);
	}
}

void GUI::AddWidgit(int OFFSETX, int OFFSETY, sf::Texture& TEXTURE)
{
	Widgits.push_back(Widgit(OFFSETX, OFFSETY, TEXTURE));
}
