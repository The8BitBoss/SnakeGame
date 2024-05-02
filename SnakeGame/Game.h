#pragma once

#include "linkedlist.h"

class Game
{
public:
    sf::Clock clock;
    float timer{ 0 }, delay{ 0.1f };

    int gScreenWidth;
    int gScreenHeight;
    sf::RenderWindow* window;

    std::vector<SnakeLinkedList> snakes;
    SnakeLinkedList player;
    int playerDir;
    int n{ 50 }, m{ 37 };
    int spriteSize{ 16 };


    int num = 5;
    bool dead;
    struct Pos
    {
        enum class Sprite {
            Orange = 1,
            Yellow,
            Green,
            Red,
            Purple,
        };
        sf::Vector2f pos;
        int value{ 0 };
        bool dead = true;
        int respawnTimer = 50 + rand() % 51;;
    } fruits[5];

    sf::Texture tW, tR, tO, tY, tG, tLB, tB, tP;

    Game();
    ~Game();

	void Setup();
	void Tick();

    bool Collisions();

    int Run();

};

