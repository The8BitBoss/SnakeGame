#pragma once

#include "linkedlist.h"
#include "GUI.h"

class Game
{
public:
    sf::Clock clock;
    float timer{ 0 }, delay{ 0.1f };

    int gScreenWidth;
    int gScreenHeight;
    int waterlevel{ 1 };
    int ticksTillWaterLower{ 100 };
    sf::RenderWindow* window;

    std::vector<SnakeLinkedList> snakes;
    SnakeLinkedList player;
    GUI scoreUI;
    std::string playerName;
    int playerDir{ 0 };
    int n{ 60 }, m{ 40 };
    int spriteSize;


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

    sf::Texture tW, tGry, tKey, tR, tO, tY, tG, tLB, tB, tP;
    sf::Font font;

    Game();
    ~Game();

	void Setup();
	void Tick(int botdir);

    void CollisionSnakeFruit();

    void LowerWater();

    bool CheckOverlap(int i);

    

    bool Collisions();

    int Run();

    int BalanceFall(int i);

};

