/*
  Games Software Engineering GAD1006-N
  Snake ICA start project 
  
  Project set up to use SFML
  SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>

int main()
{
    // All SFML types and functions are contained in the sf namespace

    // TODO: 
    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text    

    // We can still output to the console window
    std::cout << "SnakeGame: Starting" << std::endl;

    // TODO:
    // Make a main loop that continues until we call window.close()  
    //     
    // {
        // Inside the lopp:
        // Poll for events from the window and handle the closed one  
        // Clear the window to a colour
        // Display the window contents
    // }

    std::cout << "SnakeGame: Finished" << std::endl;

    return 0;
}
