/*
  Games Software Engineering GAD1006-N
  Snake ICA start project 
  
  Project set up to use SFML
  SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
int n{ 50 }, m{ 37 };
int spriteSize{ 16 };
int gScreenWidth{ spriteSize * n };
int gScreenHeight{ spriteSize * m };

int dir, lastDir, num = 5
;

struct Pos
{   float x, y;   } snakeSegments[100], fruits[5];

enum EDirection
{
    eRight,
    eDown,
    eLeft,
    eUp
};

void Tick()
{
    for (int i = num; i > 0; --i)
    {
        snakeSegments[i].x = snakeSegments[i - 1].x;
        snakeSegments[i].y = snakeSegments[i - 1].y;

    }
    if (dir == (lastDir + 2) % 4)
        dir = lastDir;
        switch (dir)
        {
        case EDirection::eUp:
            snakeSegments[0].y -= 1;
            break;
        case EDirection::eLeft:
            snakeSegments[0].x -= 1;
            break;
        case EDirection::eRight:
            snakeSegments[0].x += 1;
            break;
        case EDirection::eDown:
            snakeSegments[0].y += 1;
            break;
        }
        lastDir = dir;
        for (int i = 0; i < 5; i++)
        {
            if ((snakeSegments[0].x == fruits[i].x) && (snakeSegments[0].y == fruits[i].y))
            {
                num++;
                fruits[i].x = rand() % n;
                fruits[i].y = rand() % m;
            }
        }
}
int main()
{
    ///////////////   Create Window ///////////////////
    sf::RenderWindow window(sf::VideoMode(gScreenWidth, gScreenHeight), "Snake");

    //////// Load Sprites //////////
    sf::Texture t1,tS;
    if (!t1.loadFromFile("Assets/white.png")||!tS.loadFromFile("Assets/red.png"))
    {
        std::cout << "Texture Failed to load";
        return 0;
    }
    sf::Sprite sprite1(t1), spriteSnake(tS);

    ///////////  Timer Setup //////
    sf::Clock clock;
    float timer{ 0 }, delay{ 0.1 };

    for (int i = 0; i < 5; i++)
    {
            fruits[i].x = rand() % n;
            fruits[i].y = rand() % m;
    }

    //////////////  Run Game ///////////////
    while (window.isOpen())
    {
        ///////////////   Timer increment ///////////////
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        ////////////////// Event checker ////////////////
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ////////////   Direction input checker  ///////////////
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            dir = EDirection::eLeft;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dir = EDirection::eRight;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dir = EDirection::eUp;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dir = EDirection::eDown;


        //////////////   Tick     /////////////////////
        if (timer > delay) { timer = 0; Tick(); }
        ///////////////////  Drawing  /////////////////////
        window.clear(sf::Color(0,0,0,255));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                sprite1.setPosition(i * spriteSize, j * spriteSize);  window.draw(sprite1);
            }
        }
        for (int i = 0; i < num; i++)
        {
            spriteSnake.setPosition(snakeSegments[i].x*spriteSize, snakeSegments[i].y*spriteSize);
            window.draw(spriteSnake);
        }

        for (int i = 0; i < 5; i++)
        {
            spriteSnake.setPosition(fruits[i].x * spriteSize, fruits[i].y * spriteSize);
            window.draw(spriteSnake);
        }

        window.display();
        ////////////////////////////////////
    }
    std::cout << "SnakeGame: Finished" << std::endl;

    return 0;
}
