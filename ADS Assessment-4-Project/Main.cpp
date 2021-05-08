#include <iostream>
#include <string>
#include <Windows.h>
#include "textpixels_enums.h"
#include "textpixels.h"
#include "creature.h"
#include "fruit.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Shape.h"
#include "randColor.h"

using namespace std;
using namespace textpixels;

enum Screen // Enum for various screen options
{
    MENU = 1,
    EASY,
    GUIDE,
    MEDIUM,
    HARD,
    PAUSE,
    GAMEOVER,
    QUIT,
    SECRET_COW_LEVEL,
    NO_SCREEN
};

/// Global Variables 
int getScore = 0;                               // Variable to carry player Score
int HighScores = 0;                             // Variable to carry to high scores
vector<Creature> XY_SnakiePostion(2);           // carry 2 sets of snakes positions
vector<Creature> XY_oldSnakiePostion(3);        // carrying 3 inital snake history positions
vector<Fruit> editableFruits(5);                // Variable list of consumeable objects golden apple = 0, rock = 1, water = 2, worm = 3, cow key = 4
vector<Creature> animal(10);                    // Variable list of Creatures snakie = 0, owl = 1, cows = 2+
vector<Shape> obstacle(6);                      // Variable list of Obstacles on the field
vector<randColor> randomColor(31);              // Variable list for generating randome colors
int currentGameMode;                            // Variable to carry the difficulty level

void drawGameInterface() // creates game background showing help, fps and score
{
    fillWindow(FG_BLACK);
    fillRect(1, 1, windowWidth() - 2, windowHeight() - 2, FG_DARK_YELLOW);
    drawString(2, 0, "Move around or (ESCAPE) to exit", layerColours(FG_YELLOW, BG_BLACK));
    drawString(2, windowHeight() - 1, "FPS: " + getFpsString(), layerColours(FG_YELLOW, BG_BLACK));
    drawString(12, windowHeight() - 1, "Score: " + to_string(getScore), layerColours(FG_YELLOW, BG_BLACK));
}

int gameGuideInterface() // Displays the game guide screen identifying the different elements of the game
{
        int choice = NO_SCREEN;
        int screen = MENU;

        do                                                                                                   // Keeps looping, waiting for input from player 
        {
            textpixels::startFrame();                                                                        // starts Frame window to enable drawing
   
            // Draws background and title text for each section
            fillWindow(FG_WHITE);
            fillRect(1, 1, windowWidth() - 2, windowHeight() - 2, FG_BLACK);
            drawString(14, 5, "Welcome to the Game Guide", layerColours(FG_WHITE, BG_BLACK));
            drawString(14, 6, "Press Escape to go back", layerColours(FG_WHITE, BG_BLACK));

            drawString(17, 12, "Use the arrow keys to move ", layerColours(FG_WHITE, BG_BLACK));
            drawString(9, 22, "Types of objects Snakie can eat", layerColours(FG_WHITE, BG_BLACK));
            drawString(9, 36, "Types of Creatures on the field", layerColours(FG_WHITE, BG_BLACK));

            //draws the arrows icon
            drawPixel(9, 13, FG_DARK_YELLOW);
            drawPixel(9, 14, FG_DARK_YELLOW);
            drawPixel(9, 15, FG_WHITE);
            drawPixel(9, 12, FG_DARK_YELLOW);
            drawPixel(9, 11, FG_DARK_YELLOW);
            drawPixel(9, 10, FG_DARK_YELLOW);
            drawPixel(9, 9, FG_WHITE);
            drawPixel(7, 12, FG_DARK_YELLOW);
            drawPixel(8, 12, FG_DARK_YELLOW);
            drawPixel(6, 12, FG_WHITE);
            drawPixel(10, 12, FG_DARK_YELLOW);
            drawPixel(11, 12, FG_DARK_YELLOW);
            drawPixel(12, 12, FG_WHITE);

            //Draws edtible objects
            drawPixel(33, 27, FG_DARK_RED);
            drawPixel(9, 32, FG_GREY);
            drawPixel(22, 32, FG_BLUE);
            drawPixel(40, 32, FG_MAGENTA);

            // Draws text descripton of each object
            drawString(15, 27, "Random", layerColours(FG_WHITE, BG_BLACK));
            drawString(4, 25, "GOLDEN APPLE 1pt", layerColours(FG_YELLOW, BG_BLACK));
            drawString(30, 25, "COW KEY", layerColours(FG_YELLOW, BG_BLACK));
            drawString(4, 30, "ROCK 1pt", layerColours(FG_YELLOW, BG_BLACK));
            drawString(19, 30, "WATER 3pt", layerColours(FG_YELLOW, BG_BLACK));
            drawString(34, 30, "WORM 2pt", layerColours(FG_YELLOW, BG_BLACK));
            drawString(8, 38, "SNAKIE", layerColours(FG_YELLOW, BG_BLACK));
            drawString(23, 38, "OWLY", layerColours(FG_YELLOW, BG_BLACK));
            drawString(37, 38, "COW", layerColours(FG_YELLOW, BG_BLACK));

            //Draws creaure objects
            drawPixel(9, 40, FG_GREEN);
            drawPixel(25, 40, FG_DARK_GREEN);
            drawPixel(40, 40, FG_BLACK);


            //when escape key is pressed exits loops returns to main menu
            if (keyIsDown(VK_ESCAPE))
            {
                choice = QUIT;
            }

            textpixels::endFrame();                                                                          // closes frame ends drawing
        } while (choice == NO_SCREEN);                                                                       // Only stop when playerHasQuit  
        return(0);

}

void showQuitScreen()
{
    textpixels::startFrame();                                                                   // starts Frame window to enable drawing

    fillWindow(FG_DARK_BLUE);
    drawString(3, 5, "SOME SAY 3 TIMES THE CHARM.", layerColours(FG_WHITE, BG_DARK_BLUE));
    textpixels::endFrame();                                                                     // Needed always at end of game loop.
    Sleep(1500);
}

void snakeieLogo()                                  // Draws snake logo for main menu
{
    // X letter
    fillRect(11, 5, 1, 1, FG_DARK_YELLOW);
    fillRect(12, 6, 1, 1, FG_DARK_YELLOW);
    fillRect(13, 7, 1, 1, FG_DARK_YELLOW);
    fillRect(14, 8, 1, 1, FG_DARK_YELLOW);
    fillRect(15, 9, 1, 1, FG_DARK_YELLOW);
    fillRect(16, 10, 1, 1, FG_DARK_YELLOW);
    fillRect(17, 11, 1, 1, FG_DARK_YELLOW);
    fillRect(18, 12, 1, 1, FG_DARK_YELLOW);

    fillRect(11, 12, 1, 1, FG_DARK_YELLOW);
    fillRect(12, 11, 1, 1, FG_DARK_YELLOW);
    fillRect(13, 10, 1, 1, FG_DARK_YELLOW);
    fillRect(14, 9, 1, 1, FG_DARK_YELLOW);
    fillRect(15, 8, 1, 1, FG_DARK_YELLOW);
    fillRect(16, 7, 1, 1, FG_DARK_YELLOW);
    fillRect(17, 6, 1, 1, FG_DARK_YELLOW);
    fillRect(18, 5, 1, 1, FG_DARK_YELLOW);

    fillRect(34, 5, 1, 1, FG_DARK_YELLOW);
    fillRect(35, 6, 1, 1, FG_DARK_YELLOW);
    fillRect(36, 7, 1, 1, FG_DARK_YELLOW);
    fillRect(37, 8, 1, 1, FG_DARK_YELLOW);
    fillRect(38, 9, 1, 1, FG_DARK_YELLOW);
    fillRect(39, 10, 1, 1, FG_DARK_YELLOW);
    fillRect(40, 11, 1, 1, FG_DARK_YELLOW);
    fillRect(41, 12, 1, 1, FG_DARK_YELLOW);

    fillRect(32, 12, 1, 1, FG_DARK_YELLOW);
    fillRect(33, 11, 1, 1, FG_DARK_YELLOW);
    fillRect(34, 10, 1, 1, FG_DARK_YELLOW);
    fillRect(35, 9, 1, 1, FG_DARK_YELLOW);
    fillRect(36, 8, 1, 1, FG_DARK_YELLOW);
    fillRect(37, 7, 1, 1, FG_DARK_YELLOW);
    fillRect(38, 6, 1, 1, FG_DARK_YELLOW);
    fillRect(39, 5, 1, 1, FG_DARK_YELLOW);

    // O letter
    fillRect(22, 8, 1, 1, FG_DARK_YELLOW);
    fillRect(22, 9, 1, 1, FG_DARK_YELLOW);
    fillRect(23, 7, 1, 1, FG_DARK_YELLOW);
    fillRect(24, 6, 1, 1, FG_DARK_YELLOW);
    fillRect(25, 5, 1, 1, FG_DARK_YELLOW);
    fillRect(26, 5, 1, 1, FG_DARK_YELLOW);
    fillRect(27, 5, 1, 1, FG_DARK_YELLOW);
    fillRect(28, 6, 1, 1, FG_DARK_YELLOW);
    fillRect(29, 7, 1, 1, FG_DARK_YELLOW);
    fillRect(30, 8, 1, 1, FG_DARK_YELLOW);
    fillRect(30, 9, 1, 1, FG_DARK_YELLOW);
    fillRect(29, 10, 1, 1, FG_DARK_YELLOW);
    fillRect(28, 11, 1, 1, FG_DARK_YELLOW);
    fillRect(27, 12, 1, 1, FG_DARK_YELLOW);
    fillRect(26, 12, 1, 1, FG_DARK_YELLOW);
    fillRect(25, 12, 1, 1, FG_DARK_YELLOW);
    fillRect(24, 11, 1, 1, FG_DARK_YELLOW);
    fillRect(23, 10, 1, 1, FG_DARK_YELLOW);

    // underline
    fillRect(0, 15, 1, 1, FG_WHITE);
    fillRect(2, 15, 3, 1, FG_WHITE);
    fillRect(6, 15, 1, 1, FG_WHITE);
    fillRect(8, 15, 4, 1, FG_WHITE);
    fillRect(13, 15, 3, 1, FG_WHITE);
    fillRect(17, 15, 2, 1, FG_WHITE);
    fillRect(20, 15, 1, 1, FG_WHITE);
    fillRect(22, 15, 3, 1, FG_WHITE);
    fillRect(26, 15, 2, 1, FG_WHITE);
    fillRect(29, 15, 1, 1, FG_WHITE);
    fillRect(31, 15, 1, 1, FG_WHITE);
    fillRect(33, 15, 3, 1, FG_WHITE);
    fillRect(36, 15, 3, 1, FG_WHITE);
    fillRect(38, 15, 1, 1, FG_WHITE);
    fillRect(40, 15, 2, 1, FG_WHITE);
    fillRect(43, 15, 1, 1, FG_WHITE);
    fillRect(45, 15, 3, 1, FG_WHITE);
    fillRect(49, 15, 1, 1, FG_WHITE);

    // Draws box around menu selection
    drawWCharacter(2, 37, 0x255A, FG_WHITE);
    drawWCharacter(2, 36, 0x2551, FG_WHITE);
    drawWCharacter(2, 35, 0x2551, FG_WHITE);
    drawWCharacter(2, 34, 0x2551, FG_WHITE);
    drawWCharacter(2, 33, 0x2551, FG_WHITE);
    drawWCharacter(2, 32, 0x2551, FG_WHITE);
    drawWCharacter(2, 31, 0x2551, FG_WHITE);
    drawWCharacter(2, 30, 0x2551, FG_WHITE);
    drawWCharacter(2, 29, 0x2551, FG_WHITE);
    drawWCharacter(2, 28, 0x2551, FG_WHITE);
    drawWCharacter(2, 27, 0x2551, FG_WHITE);
    drawWCharacter(2, 26, 0x2551, FG_WHITE);
    drawWCharacter(2, 25, 0x2554, FG_WHITE);

    // Draws box around menu selection
    drawWCharacter(windowWidth() - 2, 37, 0x255D, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 36, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 35, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 34, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 33, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 32, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 31, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 30, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 29, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 28, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 27, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 26, 0x2551, FG_WHITE);
    drawWCharacter(windowWidth() - 2, 25, 0x2557, FG_WHITE);

    return;
}

int  highscore()                                // Functions for updating the players highscore
{
    if (getScore > HighScores)                  // if statement for watching for a get score that is higher than highscore
    {
        HighScores = getScore;                  // if get score is higher. then highscores is updated
    }
    return(HighScores);
}

/*int cowDrop()

/////////////// README - this function was a work in progress (not working at the moment)was trying to implement a secret cow level
that would spawn after reaching 10 points you would be taken to a level with lots of pickups
to boot your points and return you to the main level. but ran out of time to finish. i have commented
out as not to be part of this program but to show progress and working //////////////////////////////////

{
    srand(static_cast<unsigned int>(time(0))); //seed random number generator
    int randomColors = rand(); //generate random number
    int randomColorType = (randomColors % 31) + 1; // get a number between 1 and 4

    //Draws position of cows following a pattern
    animal[2].x = 4;
    animal[2].y = 4;
    animal[2].colour = randomColorType;
    animal[3].x = 5;
    animal[3].y = 5;
    animal[3].colour = randomColorType;
    animal[4].x = 6;
    animal[4].y = 6;
    animal[4].colour = randomColorType;
    animal[5].x = 7;
    animal[5].y = 7;
    animal[5].colour = randomColorType;
    animal[6].x = 8;
    animal[6].y = 8;
    animal[6].colour = randomColorType;
    animal[7].x = 9;
    animal[7].y = 9;
    animal[7].colour = randomColorType;
    animal[8].x = 10;
    animal[8].y = 10;
    animal[8].colour = randomColorType;
    animal[9].x = 11;
    animal[9].y = 11;
    animal[9].colour = randomColorType;
    return(0);
}*/

/*int cowDraw() 

/////////////// README - this function was a work in progress (not working at the moment)was trying to implement a secret cow level
that would spawn after reaching 10 points you would be taken to a level with lots of pickups
to boot your points and return you to the main level. but ran out of time to finish. i have commented
out as not to be part of this program but to show progress and working //////////////////////////////////

{
    bool gotAllCows = false;

    do
    {
        //Draws new background
        textpixels::startFrame();   // starts Frame window to enable drawing
        fillWindow(FG_BLUE);
        fillRect(1, 1, windowWidth() - 2, windowHeight() - 2, FG_DARK_YELLOW);
        drawString(2, 0, "Move around or (X) to exit", layerColours(FG_YELLOW, BG_BLACK));
        drawString(2, windowHeight() - 1, "FPS: " + getFpsString(), layerColours(FG_YELLOW, BG_BLACK));
        drawString(12, windowHeight() - 1, "Score: " + to_string(getScore), layerColours(FG_YELLOW, BG_BLACK));


        //Draws cow pixels 
        drawPixel(animal[2].x, animal[2].y, animal[2].colour);
        drawPixel(animal[3].x, animal[3].y, animal[3].colour);
        drawPixel(animal[4].x, animal[4].y, animal[4].colour);
        drawPixel(animal[5].x, animal[5].y, animal[5].colour);
        drawPixel(animal[6].x, animal[6].y, animal[6].colour);
        drawPixel(animal[7].x, animal[7].y, animal[7].colour);
        drawPixel(animal[8].x, animal[8].y, animal[8].colour);
        drawPixel(animal[9].x, animal[9].y, animal[9].colour);

        if (keyIsDown(VK_ESCAPE))
        {
            showQuitScreen();
            gotAllCows = true;
        }

        //textpixels::endFrame();                           // Needed always at end of game loop.
    } while (!gotAllCows);     // Only stop when playerHasQuit  
   
    return(0);
}*/

/*int snakeHistory()

/////////////// README - this function was a work in progress (not working at the moment)was trying to implement a the snake history
.but ran out of time to finish. i have commented out as not to be part of this program but to show progress and working //////////////////////////////////


{
    Creature oldHead;
    oldHead.x = XY_SnakiePostion[0].x;
    oldHead.y = XY_SnakiePostion[0].y;
    XY_oldSnakiePostion.push_back(oldHead);
    do
    {
        textpixels::startFrame();   // starts Frame window to enable drawing

        //storing old snake location into vector
        XY_oldSnakiePostion[0].x = animal[0].x;
        XY_oldSnakiePostion[0].y = animal[0].y;
        XY_oldSnakiePostion[1].x = animal[0].x;
        XY_oldSnakiePostion[1].y = animal[0].y;
        XY_oldSnakiePostion[2].x = animal[0].x;
        XY_oldSnakiePostion[2].y = animal[0].y;

        for (Creature oldHead : XY_oldSnakiePostion)
        {
            drawPixel(XY_oldSnakiePostion[0].x, XY_oldSnakiePostion[0].y, XY_oldSnakiePostion[0].colour);

        }
        //for (int snakeLoop = 0; snakeLoop < XY_oldSnakiePostion.size(); snakeLoop++)
       // {
           // drawPixel(XY_oldSnakiePostion[0].x, XY_oldSnakiePostion[0].y, XY_oldSnakiePostion[0].colour);
          //  XY_oldSnakiePostion.push_back(oldHead);
    } while (true);

    //
}
return(0);
}*/


int showMenu()                                                                                                     // shows menu for scene selection
{
    int choice = NO_SCREEN;

    do                                                                                                            // Keeps looping, waiting for input
    {
        textpixels::startFrame();                                                                                 // starts Frame window to enable drawing
        fillWindow(BG_DARK_YELLOW);
        fillRect(1, 1, windowWidth() - 2, windowHeight() - 2, BG_DARK_GREY);
        drawString(13, 20, "CHOOSE YOUR DIFFICULTY", layerColours(FG_WHITE, BG_BLACK));
        drawString(4, 27, "1", layerColours(FG_WHITE, BG_BLACK));
        drawString(5, 27, "  -       peasy lemon squeezy", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(10, 27, "Easy", layerColours(FG_WHITE, BG_BLACK));
        drawString(4, 29, "2", layerColours(FG_WHITE, BG_BLACK));
        drawString(5, 29, "  - Do you like your snakes        rare?", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(33, 29, "medium", layerColours(FG_WHITE, BG_BLACK));
        drawString(4, 31, "3", layerColours(FG_WHITE, BG_BLACK));
        drawString(5, 31, "  - Ready to enter the      snake pit?", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(28, 31, "hard", layerColours(FG_WHITE, BG_BLACK));
        drawString(4, 33, "4", layerColours(FG_WHITE, BG_BLACK));
        drawString(5, 33, "  - Game Guide ", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(7, 35, "- if your scared of snake pits", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(4, 35, "Q", layerColours(FG_WHITE, BG_BLACK));
        drawString(7, 45, " - Highest Score : " + to_string(HighScores), layerColours(FG_DARK_YELLOW, BG_BLACK));




                                                                                                                             // key options for input
        if (keyIsDown('1'))
        {
            choice = EASY;
            currentGameMode = 2;
        }
        if (keyIsDown('2'))
        {
            choice = MEDIUM;
            currentGameMode = 3;
        }
        if (keyIsDown('3'))
        {
            choice = HARD;
            currentGameMode = 4;
        }
        if (keyIsDown('4'))
        {
            choice = GUIDE;
            currentGameMode = 5;
        }
        if (keyIsDown('5'))
        {
            choice = SECRET_COW_LEVEL;
            currentGameMode = 4;
        }
        else if (keyIsDown('Q'))
        {
            choice = QUIT;
        }

        snakeieLogo();                                                                                                   //Shows Logo

        textpixels::endFrame();                                                                                          //Ends dawings to screen
    } while (choice == NO_SCREEN);                                                                                       // Only stop when playerHasQuit  
    return(choice);
}

void deathScreen()                                                                                              //death screen shows that the player has died 
{
    bool playerHasQuit = false;

    do                                                                                                          // Do loop to display death screen 
    {
        textpixels::startFrame();                                                                               // starts Frame window to enable drawing
        fillWindow(FG_DARK_RED);
        drawString(15, 25, "YOU HAVE DIED!.", layerColours(FG_WHITE, BG_DARK_RED));
        drawString(8, 29, "Press Escape to return to the menu", layerColours(FG_WHITE, BG_DARK_RED));

        if (keyIsDown(VK_ESCAPE))                                                                               // Escape exits death screen and takes you back to menu
        {
            animal[0].colour = FG_GREEN;;                         // Set snakies colour
            animal[0].x = 25;                                     // and starting position
            animal[0].y = 25;
            highscore();
            showMenu();
            playerHasQuit = true;
        }

        textpixels::endFrame();                                                                                // Needed always at end of game loop.
    } while (!playerHasQuit);                                                                                  // Only stop when playerHasQuit  
    return;
}

int fruitDrop()                                                                              //This Functions Calculates Drop loctions for editable objects
{
    // random fruit spawner
    srand(static_cast<unsigned int>(time(0)));                                              //seed random number generator
    int randomNumber = rand();                                                              //generate random number
    int randomFruitLocation = (randomNumber % 50) + 1;                                      // get a number between 1 and 50


    // if snake collides with golden apple add 1 point and respawn at a different location based on random
    //Reset speed if in slippery state
    if ((animal[0].x == editableFruits[0].x) && (animal[0].y == editableFruits[0].y))
    {
        getScore++;
        editableFruits[0].x = randomFruitLocation;
        editableFruits[0].y = randomFruitLocation;
        if (currentGameMode == 2)                                                            // check current game mode, if on easy make sure FPS is 15
        {
            setFps(15);
        }
        if (currentGameMode == 3)                                                            // check current game mode, if on medium make sure FPS is 20
        {
            setFps(20);
        }
        if (currentGameMode == 4)                                                           // check current game mode, if on hard make sure FPS is 25
        {
            setFps(25);
        }
    }


    // if snake collides with rock remove 1 point and respawn at a different location based on random
    //Reset speed if in slippery state
    if ((animal[0].x == editableFruits[1].x) && (animal[0].y == editableFruits[1].y))
    {
        getScore--;
        editableFruits[1].x = randomFruitLocation;
        editableFruits[1].y = randomFruitLocation;
        if (currentGameMode == 2)                                                           // check current game mode, if on easy make sure FPS is 15
        {
            setFps(15);
        }
        if (currentGameMode == 3)                                                           // check current game mode, if on medium make sure FPS is 20
        {
            setFps(20);
        }
        if (currentGameMode == 4)                                                          // check current game mode, if on hard make sure FPS is 25
        {
            setFps(25);
        }
    }


    // if snake collides with water add 3 points and respawn at a different location based on random
    //Also increase FPS as water is slippery until their is a collision with another object
    if ((animal[0].x == editableFruits[2].x) && (animal[0].y == editableFruits[2].y))
    {
        editableFruits[2].x = randomFruitLocation;
        editableFruits[2].y = randomFruitLocation;
        getScore++;
        getScore++;
        getScore++;
        setFps(35);
    }


    // if snake collides with worm add 2 points and respawn at a different location based on random
    //Reset speed if in slippery state
    if ((animal[0].x == editableFruits[3].x) && (animal[0].y == editableFruits[3].y))
    {
        editableFruits[3].x = randomFruitLocation;
        editableFruits[3].y = randomFruitLocation;
        getScore++;
        getScore++;

        if (currentGameMode == 2)
        {
            setFps(15);
        }
        if (currentGameMode == 3)
        {
            setFps(20);
        }
        if (currentGameMode == 4)
        {
            setFps(25);
        }
    }

     // if snake collides with owl the game ends
     if ((animal[0].x == animal[1].x) && (animal[0].y == animal[1].y))
     {
            deathScreen();
     }

     /*////////////// Excluded feature for cow level//////////////
     // if snake collides with cow key executes secret level
     if ((animal[0].x == editableFruits[4].x) && (animal[0].y == editableFruits[4].y))
     {
         //cowDrop();
         //cowDraw();
     }*/
    
    return (0);
}

void fruitDraw()                                                                            // This function Draws objets to screen after drop fruit calculates locations 
{
    srand(static_cast<unsigned int>(time(0)));                                              //seed random number generator
    int randomColors = rand();                                                              //generate random number
    int randomColorType = (randomColors % 31) + 1;                                          // get a number between 1 and 4

    editableFruits[0].colour = randomColorType;

    drawPixel(editableFruits[0].x, editableFruits[0].y, editableFruits[0].colour);
    drawPixel(editableFruits[1].x, editableFruits[1].y, editableFruits[1].colour);
    drawPixel(editableFruits[3].x, editableFruits[3].y, editableFruits[3].colour);
    drawPixel(editableFruits[2].x, editableFruits[2].y, editableFruits[2].colour);
    //drawPixel(editableFruits[4].x, editableFruits[4].y, editableFruits[4].colour);        //Excluded Cow Level Feature
    drawPixel(animal[1].x, animal[1].y, animal[1].colour);
    //drawPixel(animal[2].x, animal[2].y, animal[2].colour);                                //Excluded Cow Level Feature
    return;
}

int outOfBoundsDetection()                                                                  // Function for teleporting snake to otherside of field when colliding with edge of windows
{
    if (animal[0].y == 0)
    {
        animal[0].y = windowHeight() - 1;
    }
    else if (animal[0].y == windowHeight() - 1)
    {
        animal[0].y = 1;
    }
    if (animal[0].x == 0)
    {
        animal[0].x = windowWidth() - 1;
    }
    else if (animal[0].x == windowWidth() - 1)
    {
        animal[0].x = 1;
    }
    return(0);
}

void wallDrop()                                                                     // This function checks for collisions along each pixel of the walls generated on the field
{
    // if snake collides with wall the game ends
    if ((animal[0].x == obstacle[0].x) && (animal[0].y == obstacle[0].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[0].x) && (animal[0].y == obstacle[0].y + 1))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[0].x) && (animal[0].y == obstacle[0].y + 2))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[0].x) && (animal[0].y == obstacle[0].y + 3))
    {
        deathScreen();
    }
    // index 1
    if ((animal[0].x == obstacle[1].x) && (animal[0].y == obstacle[1].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[1].x) && (animal[0].y == obstacle[1].y + 1))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[1].x) && (animal[0].y == obstacle[1].y + 2))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[1].x) && (animal[0].y == obstacle[1].y + 3))
    {
        deathScreen();
    }
    // index 2
    if ((animal[0].x == obstacle[2].x) && (animal[0].y == obstacle[2].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[2].x + 1) && (animal[0].y == obstacle[2].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[2].x + 2) && (animal[0].y == obstacle[2].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[2].x + 3) && (animal[0].y == obstacle[2].y))
    {
        deathScreen();
    }
    // index 3
    if ((animal[0].x == obstacle[3].x) && (animal[0].y == obstacle[3].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[3].x + 1) && (animal[0].y == obstacle[3].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[3].x + 2) && (animal[0].y == obstacle[3].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[3].x + 3) && (animal[0].y == obstacle[3].y))
    {
        deathScreen();
    }
    // index 4
    if ((animal[0].x == obstacle[4].x) && (animal[0].y == obstacle[4].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[4].x) && (animal[0].y == obstacle[4].y + 1))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[4].x) && (animal[0].y == obstacle[4].y + 2))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[4].x) && (animal[0].y == obstacle[4].y + 3))
    {
        deathScreen();
    }
    // index 5
    if ((animal[0].x == obstacle[5].x) && (animal[0].y == obstacle[5].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[5].x + 1) && (animal[0].y == obstacle[5].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[5].x + 2) && (animal[0].y == obstacle[5].y))
    {
        deathScreen();
    }
    if ((animal[0].x == obstacle[5].x + 3) && (animal[0].y == obstacle[5].y))
    {
        deathScreen();
    }
}

int wallDraw()                              //This Functon draws the obstacles to screen
{
    obstacle[0].colour = FG_RED;            
    obstacle[0].x = 12;
    obstacle[0].y = 30;
    obstacle[0].obstacleWidth = 1;
    obstacle[0].obstacleHeight = 4;

    obstacle[1].colour = FG_BLACK;
    obstacle[1].x = 25;
    obstacle[1].y = 32;
    obstacle[1].obstacleWidth = 1;
    obstacle[1].obstacleHeight = 4;

    obstacle[2].colour = FG_BLACK;
    obstacle[2].x = 13;
    obstacle[2].y = 4;
    obstacle[2].obstacleWidth = 4;
    obstacle[2].obstacleHeight = 1;

    obstacle[3].colour = FG_BLACK;
    obstacle[3].x = 31;
    obstacle[3].y = 35;
    obstacle[3].obstacleWidth = 4;
    obstacle[3].obstacleHeight = 1;

    obstacle[4].colour = FG_BLACK;
    obstacle[4].x = 14;
    obstacle[4].y = 22;
    obstacle[4].obstacleWidth = 1;
    obstacle[4].obstacleHeight = 4;

    obstacle[5].colour = FG_BLACK;
    obstacle[5].x = 9;
    obstacle[5].y = 9;
    obstacle[5].obstacleWidth = 4;
    obstacle[5].obstacleHeight = 1;

    fillRect(obstacle[0].x, obstacle[0].y, obstacle[0].obstacleWidth, obstacle[0].obstacleHeight, obstacle[0].colour);
    fillRect(obstacle[1].x, obstacle[1].y, obstacle[1].obstacleWidth, obstacle[1].obstacleHeight, obstacle[1].colour);
    fillRect(obstacle[2].x, obstacle[2].y, obstacle[2].obstacleWidth, obstacle[2].obstacleHeight, obstacle[2].colour);
    fillRect(obstacle[3].x, obstacle[3].y, obstacle[3].obstacleWidth, obstacle[3].obstacleHeight, obstacle[3].colour);
    fillRect(obstacle[4].x, obstacle[4].y, obstacle[4].obstacleWidth, obstacle[4].obstacleHeight, obstacle[4].colour);
    fillRect(obstacle[5].x, obstacle[5].y, obstacle[5].obstacleWidth, obstacle[5].obstacleHeight, obstacle[5].colour);
    return(0);
}

int playSnake() // main snake play function 
{
    int score = 0;
    bool playerHasQuit = false;
    
    //initial declarations for objects
    editableFruits[0].colour = FG_RED;                    // Set apple colour
    editableFruits[0].x = 4;                              // Set apple starting position
    editableFruits[0].y = 15;

    editableFruits[1].colour = FG_GREY;                   // Set rock colour
    editableFruits[1].x = 40;                             // Set rock starting position
    editableFruits[1].y = 20;

    editableFruits[2].colour = FG_BLUE;                   // Set water colour
    editableFruits[2].x = 25;                             // Set water starting position
    editableFruits[2].y = 45;

    editableFruits[3].colour = BG_BLACK;                  // Set worm colour
    editableFruits[3].x = 40;                             // Set worm starting position
    editableFruits[3].y = 4;

    //editableFruits[4].colour = FG_DARK_RED;             // Set COW KEY colour              REMOVED FEATURE
    //editableFruits[4].x = 10;                           // Set COW KEY starting position   REMOVED FEATURE
    //editableFruits[4].y = 3;

    //animal[2].colour = FG_BLACK;                        // Set cow colour                  REMOVED FEATURE
    //animal[2].x = 12;                                   // Set cow starting position       REMOVED FEATURE
    //animal[2].y = 3;

    animal[0].colour = FG_GREEN;;                         // Set snakies colour
    animal[0].x = 25;                                     // and starting position
    animal[0].y = 25;

    animal[1].colour = FG_DARK_GREEN;                     // Set owls colour
    animal[1].x = 14;                                     // and starting position
    animal[1].y = 3;

    obstacle[0].colour = FG_DARK_BLUE;                    // Set one obstacle walls colour
    obstacle[0].x = 16;                                   // Set one obstacle walls position
    obstacle[0].y = 3;

    do
    {
        textpixels::startFrame();                         // starts Frame window to enable drawing

        // Movement of snake is controlled here
        if (keyIsDown(VK_RIGHT))
        {
            animal[0].xDir = 1;                   
            animal[0].yDir = 0;                 
        }
        else if (keyIsDown(VK_LEFT))
        {
            animal[0].xDir = -1;
            animal[0].yDir = 0;
        }
        else if (keyIsDown(VK_UP))
        {
            animal[0].xDir = 0;
            animal[0].yDir = -1;
        }
        else if (keyIsDown(VK_DOWN))
        {
            animal[0].xDir = 0;
            animal[0].yDir = 1;
        }
        else if (keyIsDown(VK_ESCAPE))
        {
            highscore();
            playerHasQuit = true;
        }


        //XY_SnakiePostion.push_back();

        // moving snake in her current x and y directions.
        animal[0].x += animal[0].xDir;
        animal[0].y += animal[0].yDir;

        // storing new snake location into vector
        XY_SnakiePostion[0].x = animal[0].x;
        XY_SnakiePostion[1].y = animal[0].y;

        // Draw and call funcions for objects
        drawGameInterface();
        drawPixel(animal[0].x, animal[0].y, animal[0].colour);
        //snakeHistory();                                        // REMOVED FEATURE
        wallDraw();                                              // calls function for obstacles
        wallDrop();                                              // calls function for obstacles
        fruitDrop();                                             // calls function for objects on field
        fruitDraw();                                             // calls function for objects on field
        outOfBoundsDetection();                                  // Teleports snake when out of bounds

        textpixels::endFrame();                                  // Needed always at end of game loop.
    } while (!playerHasQuit);                                    // Only stop when playerHasQuit  
    return(score);            
}

int main()
{
    //// Set up the console window for drawing text pixels. Default size is 30x30. changed to (50, 50, 10, 10);
    textpixels::setupWindow(50, 50, 10, 10);
    textpixels::setFps(10);
    int screen = MENU;
    //// Main game loop

    while (screen != QUIT)
    {
        switch (screen)
        {
        case MENU:
            screen = showMenu();
            break;
        case EASY:
            /// Play Snake on easy
            setFps(10);
            playSnake();
            screen = MENU;
            break;
        case MEDIUM:
            /// Play Snake on medium
            setFps(15);
            playSnake();
            screen = MENU;
            break;
        case HARD:
            /// Play Snake on hard
            setFps(20);
            playSnake();
            screen = MENU;
            break;
        case GUIDE:
            /// open Guide Screen
            setFps(10);
            gameGuideInterface();
            screen = MENU;
            break;
        /*case SECRET_COW_LEVEL:                      // Removed Feature
            /// Enter Secret Cow Level
            setFps(20);
            //cowDrop();
            //cowDraw();
            screen = MENU;
            break;*/
        }
    }
    showQuitScreen();

    return (0);
}
