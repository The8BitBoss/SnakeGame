/*
  Games Software Engineering GAD1006-N
  Snake ICA start project 
  
  Project set up to use SFML
  SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>
#include "linkedlist.h"

// todo
// list snake
// die
// border
// 

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
void Tick();
std::vector<SnakeLinkedList> snakes;


int n{ 50 }, m{ 37 };
int spriteSize{ 16 };
int gScreenWidth{ spriteSize * n };
int gScreenHeight{ spriteSize * m };


int dir, lastDir, num = 5;
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

bool checkCollision(std::vector<SnakeLinkedList>& snakes)
{
    std::unordered_set<int> allNodes;// create set to store all nodes
    for (auto& snake : snakes)
    {
        std::unordered_set<int> snakeSet = snake.CreateHash();
        // for every node in every snake
        for (int node : snakeSet)
        {
            if (allNodes.find(node) != allNodes.end())
            {// if it is, then there's a collision between snakes
                bool snakefound = false;
                int index = 0;
                for (auto& snake : snakes)
                {
                    index++;
                    if (node == snake.head->position.x * 100 + snake.head->position.y)
                    {
                        std::cout << "snake " << index <<" has died";
                        snakefound = true;
                    }
                }
                if(!snakefound) {
                std::cout << "Unknown snake has died";
                    }
                return true;
            }
            allNodes.insert(node);
            // if the node is not in the set, add it to the set
        }
    }
    return false;
}

int main()
{
    //////////////////////////////Setup()///////////////////////////////////
    SnakeLinkedList snake1(sf::Vector2f(3, 1));
    snake1.PushBack(sf::Vector2f(2.0f,1.0f) );
    snake1.PushBack(sf::Vector2f(1.0f, 1.0f));
    SnakeLinkedList snake2(sf::Vector2f(3, 5));
    snake2.PushBack(sf::Vector2f(2.0f, 5.0f));
    snake2.PushBack(sf::Vector2f(1.0f, 5.0f));
    snakes.push_back(snake1);
    snakes.push_back(snake2);
    ///////////////   Create Window ///////////////////
    sf::RenderWindow window(sf::VideoMode(gScreenWidth, gScreenHeight), "Snake");

    //////// Load Sprites //////////
    sf::Texture tW,tR,tO,tY,tG,tLB,tB,tP;
    if (!tW.loadFromFile("Assets/white.png")||!tR.loadFromFile("Assets/red.png")||!tO.loadFromFile("Assets/orange.png") || !tY.loadFromFile("Assets/yellow.png") || !tG.loadFromFile("Assets/green.png") || !tLB.loadFromFile("Assets/lBlue.png") || !tB.loadFromFile("Assets/blue.png") || !tP.loadFromFile("Assets/purple.png"))
    {
        std::cout << "Texture Failed to load";
        return 0;
    }
    sf::Sprite tileWhite(tW), tileRed(tR), tileOrange(tO), tileYellow(tY), tileGreen(tG), tileLBlue(tLB), tileBlue(tB), tilePurple(tP);

    ///////////  Timer Setup //////
    sf::Clock clock;
    float timer{ 0 }, delay{ 0.1f };
    ///////////////////////////////////////////////////////////////////////
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
            dir = SnakeLinkedList::EDirection::eLeft;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dir = SnakeLinkedList::EDirection::eRight;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dir = SnakeLinkedList::EDirection::eUp;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dir = SnakeLinkedList::EDirection::eDown;
        

        //////////////   Tick     /////////////////////
        if (timer > delay) { timer = 0; Tick(); }
        ///////////////////  Drawing  /////////////////////
        window.clear(sf::Color(0,0,0,255));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {//Background//
                tileWhite.setPosition(i * spriteSize, j * spriteSize);  window.draw(tileWhite);
            }
        }
        for (int i = 0; i < 5; i++)
        {//fruit//
            if (!fruits[i].dead) {
                switch (fruits[i].value)
                {
                case 1:
                    tileYellow.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window.draw(tileYellow);
                    break;
                case 2:
                    tileLBlue.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window.draw(tileLBlue);
                    break;
                case 3:
                    tileOrange.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window.draw(tileOrange);
                    break;
                case 4:
                    tileRed.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window.draw(tileRed);
                    break;
                case 5:
                    tilePurple.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window.draw(tilePurple);
                    break;
                }
            }

        }
        for (auto& snake : snakes)
        {
            snake.Draw(window);
            //snake
        }

        window.display();
        ////////////////////////////////////
    }
    std::cout << "SnakeGame: Finished" << std::endl;

    return 0;
}

void Tick()
{
    if (dead)
    {
        return;
    }
    for (auto& snake : snakes)
    {
        snake.Move(dir);
       for (int i = 0; i < 5; i++)
       {
           if (!fruits[i].dead && snake.head->position == fruits[i].pos)
           {
               snake.segDebt += fruits[i].value;
               snake.score += fruits[i].value;
               fruits[i].respawnTimer = 50 + rand() % 51;
               fruits[i].dead = true;
               break;
           }
           if (fruits[i].dead)
           {
               if (fruits[i].respawnTimer <= 0)
               {
                   fruits[i].respawnTimer = 50 + rand() % 51;
                   fruits[i].dead = false;
                   fruits[i].pos.x = rand() % n;
                   fruits[i].pos.y = rand() % m;
                   fruits[i].value = 1 + rand() % 5;
               }
               else 
               {
                fruits[i].respawnTimer--;
               }
           }
       }
    }
    if (checkCollision(snakes))
        dead = true;
}
