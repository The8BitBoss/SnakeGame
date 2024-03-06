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
int size{ 16 };
int gScreenWidth{ size * n };
int gScreenHeight{ size * m };

int dir, num = 4;

int main()
{
    // All SFML types and functions are contained in the sf namespace

    // TODO: 
    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text    
    sf::RenderWindow window(sf::VideoMode(gScreenWidth, gScreenHeight), "Snake");

    sf::Texture t1,tS;
    if (!t1.loadFromFile("Assets/white.png")||!tS.loadFromFile("Assets/red.png"))
    {
        std::cout << "Texture Failed to load";
        return 0;
    }
    sf::Sprite sprite1(t1), spriteSnake(tS);
    // We can still output to the console window
    std::cout << "SnakeGame: Starting" << std::endl;

    // TODO:
    // Make a main loop that continues until we call window.close()  
    while (window.isOpen())
    {
        // {
            // Inside the lopp:
            // Poll for events from the window and handle the closed one  
        // Event checker ***************************
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        //******************************************
        window.clear(sf::Color(0,0,0,255));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
            }

        window.display();
            // Clear the window to a colour
            // Display the window contents
        // }
    }
    std::cout << "SnakeGame: Finished" << std::endl;

    return 0;
}
