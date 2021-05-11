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
#include <stdlib.h>

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
int choice;
int row, column;
char turn = 'X';
bool draw = false;
char board[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
bool playerHasQuit = false;
int score = 0;
char choiceinput='q';
char currentPlayer = 'X';



//Function to get the player input and update the board





bool gameover()
{
    //checking the win for Simple Rows and Simple Column
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return false;

    //checking the win for both diagonal

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return false;

    //Checking the game is in continue mode or not
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return true;

    //Checking the if game already draw
    draw = true;
    return false;
}



void drawGameInterface() // creates game background showing help, fps and score
{
    fillWindow(FG_BLACK);
    fillRect(1, 1, windowWidth() - 2, windowHeight() - 2, FG_DARK_YELLOW);
    drawString(2, 0, "Press letter  or (ESCAPE) to exit", layerColours(FG_YELLOW, BG_BLACK));
    drawString(12, windowHeight() - 1, "Score: " + to_string(getScore), layerColours(FG_YELLOW, BG_BLACK));
    drawString(25, windowHeight() - 1, "Player is: " + currentPlayer, layerColours(FG_YELLOW, BG_BLACK));
}

//int gameGuideInterface() // Displays the game guide screen identifying the different elements of the game
//{
//        int choice = NO_SCREEN;
//        int screen = MENU;
//
//        do                                                                                                   // Keeps looping, waiting for input from player 
//        {
//            textpixels::startFrame();                                                                        // starts Frame window to enable drawing
//   
//             Draws background and title text for each section
//            fillWindow(FG_WHITE);
//            fillRect(1, 1, windowWidth() - 2, windowHeight() - 2, FG_BLACK);
//            drawString(14, 5, "Welcome to the Game Guide", layerColours(FG_WHITE, BG_BLACK));
//            drawString(14, 6, "Press Escape to go back", layerColours(FG_WHITE, BG_BLACK));
//
//            drawString(17, 12, "Use the arrow keys to move ", layerColours(FG_WHITE, BG_BLACK));
//            drawString(9, 22, "Types of objects Snakie can eat", layerColours(FG_WHITE, BG_BLACK));
//            drawString(9, 36, "Types of Creatures on the field", layerColours(FG_WHITE, BG_BLACK));
//
//            //draws the arrows icon
//            drawPixel(9, 13, FG_DARK_YELLOW);
//            drawPixel(9, 14, FG_DARK_YELLOW);
//            drawPixel(9, 15, FG_WHITE);
//            drawPixel(9, 12, FG_DARK_YELLOW);
//            drawPixel(9, 11, FG_DARK_YELLOW);
//            drawPixel(9, 10, FG_DARK_YELLOW);
//            drawPixel(9, 9, FG_WHITE);
//            drawPixel(7, 12, FG_DARK_YELLOW);
//            drawPixel(8, 12, FG_DARK_YELLOW);
//            drawPixel(6, 12, FG_WHITE);
//            drawPixel(10, 12, FG_DARK_YELLOW);
//            drawPixel(11, 12, FG_DARK_YELLOW);
//            drawPixel(12, 12, FG_WHITE);
//
//            //Draws edtible objects
//            drawPixel(33, 27, FG_DARK_RED);
//            drawPixel(9, 32, FG_GREY);
//            drawPixel(22, 32, FG_BLUE);
//            drawPixel(40, 32, FG_MAGENTA);
//
//            // Draws text descripton of each object
//            drawString(15, 27, "Random", layerColours(FG_WHITE, BG_BLACK));
//            drawString(4, 25, "GOLDEN APPLE 1pt", layerColours(FG_YELLOW, BG_BLACK));
//            drawString(30, 25, "COW KEY", layerColours(FG_YELLOW, BG_BLACK));
//            drawString(4, 30, "ROCK 1pt", layerColours(FG_YELLOW, BG_BLACK));
//            drawString(19, 30, "WATER 3pt", layerColours(FG_YELLOW, BG_BLACK));
//            drawString(34, 30, "WORM 2pt", layerColours(FG_YELLOW, BG_BLACK));
//            drawString(8, 38, "SNAKIE", layerColours(FG_YELLOW, BG_BLACK));
//            drawString(23, 38, "OWLY", layerColours(FG_YELLOW, BG_BLACK));
//            drawString(37, 38, "COW", layerColours(FG_YELLOW, BG_BLACK));
//
//            //Draws creaure objects
//            drawPixel(9, 40, FG_GREEN);
//            drawPixel(25, 40, FG_DARK_GREEN);
//            drawPixel(40, 40, FG_BLACK);
//
//
//            when escape key is pressed exits loops returns to main menu
//            if (keyIsDown(VK_ESCAPE))
//            {
//                choice = QUIT;
//            }
//
//            textpixels::endFrame();                                                                          // closes frame ends drawing
//        } while (choice == NO_SCREEN);                                                                       // Only stop when playerHasQuit  
//        return(0);
//
//}

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

    fillRect(33, 5, 1, 1, FG_DARK_YELLOW);
    fillRect(34, 6, 1, 1, FG_DARK_YELLOW);
    fillRect(35, 7, 1, 1, FG_DARK_YELLOW);
    fillRect(36, 8, 1, 1, FG_DARK_YELLOW);
    fillRect(37, 9, 1, 1, FG_DARK_YELLOW);
    fillRect(38, 10, 1, 1, FG_DARK_YELLOW);
    fillRect(39, 11, 1, 1, FG_DARK_YELLOW);
    fillRect(40, 12, 1, 1, FG_DARK_YELLOW);

    fillRect(33, 12, 1, 1, FG_DARK_YELLOW);
    fillRect(34, 11, 1, 1, FG_DARK_YELLOW);
    fillRect(35, 10, 1, 1, FG_DARK_YELLOW);
    fillRect(36, 9, 1, 1, FG_DARK_YELLOW);
    fillRect(37, 8, 1, 1, FG_DARK_YELLOW);
    fillRect(38, 7, 1, 1, FG_DARK_YELLOW);
    fillRect(39, 6, 1, 1, FG_DARK_YELLOW);
    fillRect(40, 5, 1, 1, FG_DARK_YELLOW);



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
        drawString(13, 20, "CHOOSE YOUR PLAY STYLE", layerColours(FG_WHITE, BG_BLACK));
        drawString(4, 27, "P", layerColours(FG_WHITE, BG_BLACK));
        drawString(5, 27, "  -   Player VS Player", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(4, 29, "O", layerColours(FG_WHITE, BG_BLACK));
        drawString(5, 29, "  -   Player VS Cortana", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(4, 31, "I", layerColours(FG_WHITE, BG_BLACK));
        drawString(5, 31, "  -   See Cortana's Scores", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(7, 33, "-   take the cowards way out!", layerColours(FG_DARK_YELLOW, BG_BLACK));
        drawString(4, 33, "U", layerColours(FG_WHITE, BG_BLACK));
        drawString(7, 40, " - Highest Score : " + to_string(HighScores), layerColours(FG_DARK_YELLOW, BG_BLACK));




                                                                                                                             // key options for input
        if (keyIsDown(VK_LEFT))
        {
            choice = EASY;
            //currentGameMode = 2;
        }
        if (keyIsDown('O'))
        {
            choice = MEDIUM;
            currentGameMode = 3;
        }
        if (keyIsDown('I'))
        {
            choice = HARD;
            currentGameMode = 4;
        }
        //if (keyIsDown('4'))
        //{
        //    choice = GUIDE;
        //    currentGameMode = 5;
        //}
        //if (keyIsDown('5'))
        //{
        //    choice = SECRET_COW_LEVEL;
        //    currentGameMode = 4;
        //}
        else if (keyIsDown('U'))
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

//int fruitDrop()                                                                              //This Functions Calculates Drop loctions for editable objects
//{
//    // random fruit spawner
//    srand(static_cast<unsigned int>(time(0)));                                              //seed random number generator
//    int randomNumber = rand();                                                              //generate random number
//    int randomFruitLocation = (randomNumber % 50) + 1;                                      // get a number between 1 and 50
//
//
//    // if snake collides with golden apple add 1 point and respawn at a different location based on random
//    //Reset speed if in slippery state
//    if ((animal[0].x == editableFruits[0].x) && (animal[0].y == editableFruits[0].y))
//    {
//        getScore++;
//        editableFruits[0].x = randomFruitLocation;
//        editableFruits[0].y = randomFruitLocation;
//        if (currentGameMode == 2)                                                            // check current game mode, if on easy make sure FPS is 15
//        {
//            setFps(15);
//        }
//        if (currentGameMode == 3)                                                            // check current game mode, if on medium make sure FPS is 20
//        {
//            setFps(20);
//        }
//        if (currentGameMode == 4)                                                           // check current game mode, if on hard make sure FPS is 25
//        {
//            setFps(25);
//        }
//    }


    //// if snake collides with rock remove 1 point and respawn at a different location based on random
    ////Reset speed if in slippery state
    //if ((animal[0].x == editableFruits[1].x) && (animal[0].y == editableFruits[1].y))
    //{
    //    getScore--;
    //    editableFruits[1].x = randomFruitLocation;
    //    editableFruits[1].y = randomFruitLocation;
    //    if (currentGameMode == 2)                                                           // check current game mode, if on easy make sure FPS is 15
    //    {
    //        setFps(15);
    //    }
    //    if (currentGameMode == 3)                                                           // check current game mode, if on medium make sure FPS is 20
    //    {
    //        setFps(20);
    //    }
    //    if (currentGameMode == 4)                                                          // check current game mode, if on hard make sure FPS is 25
    //    {
    //        setFps(25);
    //    }
    //}


    //// if snake collides with water add 3 points and respawn at a different location based on random
    ////Also increase FPS as water is slippery until their is a collision with another object
    //if ((animal[0].x == editableFruits[2].x) && (animal[0].y == editableFruits[2].y))
    //{
    //    editableFruits[2].x = randomFruitLocation;
    //    editableFruits[2].y = randomFruitLocation;
    //    getScore++;
    //    getScore++;
    //    getScore++;
    //    setFps(35);
    //}


    //// if snake collides with worm add 2 points and respawn at a different location based on random
    ////Reset speed if in slippery state
    //if ((animal[0].x == editableFruits[3].x) && (animal[0].y == editableFruits[3].y))
    //{
    //    editableFruits[3].x = randomFruitLocation;
    //    editableFruits[3].y = randomFruitLocation;
    //    getScore++;
    //    getScore++;

    //    if (currentGameMode == 2)
    //    {
    //        setFps(15);
    //    }
    //    if (currentGameMode == 3)
    //    {
    //        setFps(20);
    //    }
    //    if (currentGameMode == 4)
    //    {
    //        setFps(25);
    //    }
    //}

     //// if snake collides with owl the game ends
     //if ((animal[0].x == animal[1].x) && (animal[0].y == animal[1].y))
     //{
     //       deathScreen();
     //}

     ///*////////////// Excluded feature for cow level//////////////
     //// if snake collides with cow key executes secret level
     //if ((animal[0].x == editableFruits[4].x) && (animal[0].y == editableFruits[4].y))
     //{
     //    //cowDrop();
     //    //cowDraw();
     //}*/
//    
//    return (0);
//}

//void fruitDraw()                                                                            // This function Draws objets to screen after drop fruit calculates locations 
//{
//    srand(static_cast<unsigned int>(time(0)));                                              //seed random number generator
//    int randomColors = rand();                                                              //generate random number
//    int randomColorType = (randomColors % 31) + 1;                                          // get a number between 1 and 4
//
//    editableFruits[0].colour = randomColorType;
//
//    drawPixel(editableFruits[0].x, editableFruits[0].y, editableFruits[0].colour);
//    drawPixel(editableFruits[1].x, editableFruits[1].y, editableFruits[1].colour);
//    drawPixel(editableFruits[3].x, editableFruits[3].y, editableFruits[3].colour);
//    drawPixel(editableFruits[2].x, editableFruits[2].y, editableFruits[2].colour);
//    //drawPixel(editableFruits[4].x, editableFruits[4].y, editableFruits[4].colour);        //Excluded Cow Level Feature
//    drawPixel(animal[1].x, animal[1].y, animal[1].colour);
//    //drawPixel(animal[2].x, animal[2].y, animal[2].colour);                                //Excluded Cow Level Feature
//    return;
//}

//int outOfBoundsDetection()                                                                  // Function for teleporting snake to otherside of field when colliding with edge of windows
//{
//    if (animal[0].y == 0)
//    {
//        animal[0].y = windowHeight() - 1;
//    }
//    else if (animal[0].y == windowHeight() - 1)
//    {
//        animal[0].y = 1;
//    }
//    if (animal[0].x == 0)
//    {
//        animal[0].x = windowWidth() - 1;
//    }
//    else if (animal[0].x == windowWidth() - 1)
//    {
//        animal[0].x = 1;
//    }
//    return(0);
//}

//void wallDrop()                                                                     // This function checks for collisions along each pixel of the walls generated on the field
//{
//    // if snake collides with wall the game ends
//    if ((animal[0].x == obstacle[0].x) && (animal[0].y == obstacle[0].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[0].x) && (animal[0].y == obstacle[0].y + 1))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[0].x) && (animal[0].y == obstacle[0].y + 2))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[0].x) && (animal[0].y == obstacle[0].y + 3))
//    {
//        deathScreen();
//    }
//    // index 1
//    if ((animal[0].x == obstacle[1].x) && (animal[0].y == obstacle[1].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[1].x) && (animal[0].y == obstacle[1].y + 1))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[1].x) && (animal[0].y == obstacle[1].y + 2))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[1].x) && (animal[0].y == obstacle[1].y + 3))
//    {
//        deathScreen();
//    }
//    // index 2
//    if ((animal[0].x == obstacle[2].x) && (animal[0].y == obstacle[2].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[2].x + 1) && (animal[0].y == obstacle[2].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[2].x + 2) && (animal[0].y == obstacle[2].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[2].x + 3) && (animal[0].y == obstacle[2].y))
//    {
//        deathScreen();
//    }
//    // index 3
//    if ((animal[0].x == obstacle[3].x) && (animal[0].y == obstacle[3].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[3].x + 1) && (animal[0].y == obstacle[3].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[3].x + 2) && (animal[0].y == obstacle[3].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[3].x + 3) && (animal[0].y == obstacle[3].y))
//    {
//        deathScreen();
//    }
//    // index 4
//    if ((animal[0].x == obstacle[4].x) && (animal[0].y == obstacle[4].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[4].x) && (animal[0].y == obstacle[4].y + 1))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[4].x) && (animal[0].y == obstacle[4].y + 2))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[4].x) && (animal[0].y == obstacle[4].y + 3))
//    {
//        deathScreen();
//    }
//    // index 5
//    if ((animal[0].x == obstacle[5].x) && (animal[0].y == obstacle[5].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[5].x + 1) && (animal[0].y == obstacle[5].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[5].x + 2) && (animal[0].y == obstacle[5].y))
//    {
//        deathScreen();
//    }
//    if ((animal[0].x == obstacle[5].x + 3) && (animal[0].y == obstacle[5].y))
//    {
//        deathScreen();
//    }
//}

int wallDraw()                              //This Functon draws the obstacles to screen
{
    obstacle[0].colour = FG_BLACK;            
    obstacle[0].x = 16;
    obstacle[0].y = 1;
    obstacle[0].obstacleWidth = 1;
    obstacle[0].obstacleHeight = 48;

    obstacle[1].colour = FG_BLACK;
    obstacle[1].x = 32;
    obstacle[1].y = 1;
    obstacle[1].obstacleWidth = 1;
    obstacle[1].obstacleHeight = 48;

    obstacle[2].colour = FG_BLACK;
    obstacle[2].x = 1;
    obstacle[2].y = 16;
    obstacle[2].obstacleWidth = 48;
    obstacle[2].obstacleHeight = 1;

    obstacle[3].colour = FG_BLACK;
    obstacle[3].x = 1;
    obstacle[3].y = 32;
    obstacle[3].obstacleWidth = 48;
    obstacle[3].obstacleHeight = 1;

    fillRect(obstacle[0].x, obstacle[0].y, obstacle[0].obstacleWidth, obstacle[0].obstacleHeight, obstacle[0].colour);
    fillRect(obstacle[1].x, obstacle[1].y, obstacle[1].obstacleWidth, obstacle[1].obstacleHeight, obstacle[1].colour);
    fillRect(obstacle[2].x, obstacle[2].y, obstacle[2].obstacleWidth, obstacle[2].obstacleHeight, obstacle[2].colour);
    fillRect(obstacle[3].x, obstacle[3].y, obstacle[3].obstacleWidth, obstacle[3].obstacleHeight, obstacle[3].colour);

    drawString(14, 15, "F1", layerColours(FG_WHITE, BG_DARK_BLUE));
    drawString(30, 15, "F2", layerColours(FG_WHITE, BG_DARK_BLUE));
    drawString(47, 15, "F3", layerColours(FG_WHITE, BG_DARK_BLUE));
    drawString(14, 31, "F4", layerColours(FG_WHITE, BG_DARK_BLUE));
    drawString(30, 31, "F5", layerColours(FG_WHITE, BG_DARK_BLUE));
    drawString(47, 31, "F6", layerColours(FG_WHITE, BG_DARK_BLUE));
    drawString(14, 48, "F7", layerColours(FG_WHITE, BG_DARK_BLUE));
    drawString(30, 48, "F8", layerColours(FG_WHITE, BG_DARK_BLUE));
    drawString(47, 48, "F9", layerColours(FG_WHITE, BG_DARK_BLUE));

    return(0);
}

//int playSnake() // main snake play function 
//{
//    int score = 0;
//    bool playerHasQuit = false;
//    
//    //initial declarations for objects
//    editableFruits[0].colour = FG_RED;                    // Set apple colour
//    editableFruits[0].x = 4;                              // Set apple starting position
//    editableFruits[0].y = 15;
//
//    editableFruits[1].colour = FG_GREY;                   // Set rock colour
//    editableFruits[1].x = 40;                             // Set rock starting position
//    editableFruits[1].y = 20;
//
//    editableFruits[2].colour = FG_BLUE;                   // Set water colour
//    editableFruits[2].x = 25;                             // Set water starting position
//    editableFruits[2].y = 45;
//
//    editableFruits[3].colour = BG_BLACK;                  // Set worm colour
//    editableFruits[3].x = 40;                             // Set worm starting position
//    editableFruits[3].y = 4;
//
//    //editableFruits[4].colour = FG_DARK_RED;             // Set COW KEY colour              REMOVED FEATURE
//    //editableFruits[4].x = 10;                           // Set COW KEY starting position   REMOVED FEATURE
//    //editableFruits[4].y = 3;
//
//    //animal[2].colour = FG_BLACK;                        // Set cow colour                  REMOVED FEATURE
//    //animal[2].x = 12;                                   // Set cow starting position       REMOVED FEATURE
//    //animal[2].y = 3;
//
//    animal[0].colour = FG_GREEN;;                         // Set snakies colour
//    animal[0].x = 25;                                     // and starting position
//    animal[0].y = 25;
//
//    animal[1].colour = FG_DARK_GREEN;                     // Set owls colour
//    animal[1].x = 14;                                     // and starting position
//    animal[1].y = 3;
//
//    obstacle[0].colour = FG_DARK_BLUE;                    // Set one obstacle walls colour
//    obstacle[0].x = 16;                                   // Set one obstacle walls position
//    obstacle[0].y = 3;
//
//    do
//    {
//        textpixels::startFrame();                         // starts Frame window to enable drawing
//
//        // Movement of snake is controlled here
//        if (keyIsDown(VK_RIGHT))
//        {
//            animal[0].xDir = 1;                   
//            animal[0].yDir = 0;                 
//        }
//        else if (keyIsDown(VK_LEFT))
//        {
//            animal[0].xDir = -1;
//            animal[0].yDir = 0;
//        }
//        else if (keyIsDown(VK_UP))
//        {
//            animal[0].xDir = 0;
//            animal[0].yDir = -1;
//        }
//        else if (keyIsDown(VK_DOWN))
//        {
//            animal[0].xDir = 0;
//            animal[0].yDir = 1;
//        }
//        else if (keyIsDown(VK_ESCAPE))
//        {
//            highscore();
//            playerHasQuit = true;
//        }
//
//
//        //XY_SnakiePostion.push_back();
//
//        // moving snake in her current x and y directions.
//        animal[0].x += animal[0].xDir;
//        animal[0].y += animal[0].yDir;
//
//        // storing new snake location into vector
//        XY_SnakiePostion[0].x = animal[0].x;
//        XY_SnakiePostion[1].y = animal[0].y;
//
//        // Draw and call funcions for objects
//        drawGameInterface();
//        drawPixel(animal[0].x, animal[0].y, animal[0].colour);
//        //snakeHistory();                                        // REMOVED FEATURE
//        wallDraw();                                              // calls function for obstacles
//        //wallDrop();                                              // calls function for obstacles
//        //fruitDrop();                                             // calls function for objects on field
//        //fruitDraw();                                             // calls function for objects on field
//        //outOfBoundsDetection();                                  // Teleports snake when out of bounds
//
//        textpixels::endFrame();                                  // Needed always at end of game loop.
//    } while (!playerHasQuit);                                    // Only stop when playerHasQuit  
//    return(score);            
//}



void player_turn()
{

    bool playerHasQuit = false;


    //if (turn == 'X')
    //{
    //    //cout << "ntPlayer - 1 [X] turn : ";
    //}
    //else if (turn == 'O')
    //{
    //    //cout << "ntPlayer - 2 [O] turn : ";
    //}
    ////Taking input from user
    ////updating the board according to choice and reassigning the turn Start


    do
    {
                        // starts Frame window to enable drawing
        textpixels::startFrame();
        drawGameInterface();
        wallDraw();






        //cin >> choice;
        //if (choiceinput == 'q')
        //{
        //    choice = 1;
        //}
        //else if (choiceinput == 'w')
        //{
        //    choice = 2;
        //}
        //else if (choiceinput == 'e')
        //{
        //    choice = 3;
        //}
        //else if (choiceinput == 'a')
        //{
        //    choice = 4;
        //}
        //else if (choiceinput == 's')
        //{
        //    choice = 5;
        //}
        //else if (choiceinput == 'd')
        //{
        //    choice = 6;
        //}
        //else if (choiceinput == 'z')
        //{
        //    choice = 7;
        //}
        //else if (choiceinput == 'x')
        //{
        //    choice = 8;
        //}
        //else if (choiceinput == 'c')
        //{
        //    choice = 9;
        //}
        //switch case to get which row and column will be update

        switch (choice)
        {
        case 1: row = 0; column = 0;
            if (currentPlayer == 'X')
            {
                // X letter q section
                fillRect(5, 5, 1, 1, FG_DARK_GREY);
                fillRect(6, 6, 1, 1, FG_DARK_GREY);
                fillRect(7, 7, 1, 1, FG_DARK_GREY);
                fillRect(8, 8, 1, 1, FG_DARK_GREY);
                fillRect(9, 9, 1, 1, FG_DARK_GREY);
                fillRect(10, 10, 1, 1, FG_DARK_GREY);
                fillRect(11, 11, 1, 1, FG_DARK_GREY);
                fillRect(12, 12, 1, 1, FG_DARK_GREY);

                fillRect(5, 12, 1, 1, FG_DARK_GREY);
                fillRect(6, 11, 1, 1, FG_DARK_GREY);
                fillRect(7, 10, 1, 1, FG_DARK_GREY);
                fillRect(8, 9, 1, 1, FG_DARK_GREY);
                fillRect(9, 8, 1, 1, FG_DARK_GREY);
                fillRect(10, 7, 1, 1, FG_DARK_GREY);
                fillRect(11, 6, 1, 1, FG_DARK_GREY);
                fillRect(12, 5, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }

            else
            {
                 //O letter q section
                fillRect(4, 8, 1, 1, FG_DARK_GREY);
                fillRect(4, 9, 1, 1, FG_DARK_GREY);
                fillRect(5, 7, 1, 1, FG_DARK_GREY);
                fillRect(6, 6, 1, 1, FG_DARK_GREY);
                fillRect(7, 5, 1, 1, FG_DARK_GREY);
                fillRect(8, 5, 1, 1, FG_DARK_GREY);
                fillRect(9, 5, 1, 1, FG_DARK_GREY);
                fillRect(10, 6, 1, 1, FG_DARK_GREY);
                fillRect(11, 7, 1, 1, FG_DARK_GREY);
                fillRect(12, 8, 1, 1, FG_DARK_GREY);
                fillRect(12, 9, 1, 1, FG_DARK_GREY);
                fillRect(11, 10, 1, 1, FG_DARK_GREY);
                fillRect(10, 11, 1, 1, FG_DARK_GREY);
                fillRect(9, 12, 1, 1, FG_DARK_GREY);
                fillRect(8, 12, 1, 1, FG_DARK_GREY);
                fillRect(7, 12, 1, 1, FG_DARK_GREY);
                fillRect(6, 11, 1, 1, FG_DARK_GREY);
                fillRect(5, 10, 1, 1, FG_DARK_GREY);
                currentPlayer = 'X';
                break;
            }


        case 2: row = 0; column = 1;
            if (currentPlayer == 'X')
            {
                // X letter w section
                fillRect(21, 5, 1, 1, FG_DARK_GREY);
                fillRect(22, 6, 1, 1, FG_DARK_GREY);
                fillRect(23, 7, 1, 1, FG_DARK_GREY);
                fillRect(24, 8, 1, 1, FG_DARK_GREY);
                fillRect(25, 9, 1, 1, FG_DARK_GREY);
                fillRect(26, 10, 1, 1, FG_DARK_GREY);
                fillRect(27, 11, 1, 1, FG_DARK_GREY);
                fillRect(28, 12, 1, 1, FG_DARK_GREY);

                fillRect(21, 12, 1, 1, FG_DARK_GREY);
                fillRect(22, 11, 1, 1, FG_DARK_GREY);
                fillRect(23, 10, 1, 1, FG_DARK_GREY);
                fillRect(24, 9, 1, 1, FG_DARK_GREY);
                fillRect(25, 8, 1, 1, FG_DARK_GREY);
                fillRect(26, 7, 1, 1, FG_DARK_GREY);
                fillRect(27, 6, 1, 1, FG_DARK_GREY);
                fillRect(28, 5, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }
            else
            {
                // O letter W section
                fillRect(20, 8, 1, 1, FG_DARK_GREY);
                fillRect(20, 9, 1, 1, FG_DARK_GREY);
                fillRect(21, 7, 1, 1, FG_DARK_GREY);
                fillRect(22, 6, 1, 1, FG_DARK_GREY);
                fillRect(23, 5, 1, 1, FG_DARK_GREY);
                fillRect(24, 5, 1, 1, FG_DARK_GREY);
                fillRect(25, 5, 1, 1, FG_DARK_GREY);
                fillRect(26, 6, 1, 1, FG_DARK_GREY);
                fillRect(27, 7, 1, 1, FG_DARK_GREY);
                fillRect(28, 8, 1, 1, FG_DARK_GREY);
                fillRect(28, 9, 1, 1, FG_DARK_GREY);
                fillRect(27, 10, 1, 1, FG_DARK_GREY);
                fillRect(26, 11, 1, 1, FG_DARK_GREY);
                fillRect(25, 12, 1, 1, FG_DARK_GREY);
                fillRect(24, 12, 1, 1, FG_DARK_GREY);
                fillRect(23, 12, 1, 1, FG_DARK_GREY);
                fillRect(22, 11, 1, 1, FG_DARK_GREY);
                fillRect(21, 10, 1, 1, FG_DARK_GREY);
                currentPlayer = 'X';
                break;
            }


        case 3: row = 0; column = 2;
            // E spot
            if (currentPlayer == 'X')
            {
                // X letter e section
                fillRect(37, 5, 1, 1, FG_DARK_GREY);
                fillRect(38, 6, 1, 1, FG_DARK_GREY);
                fillRect(39, 7, 1, 1, FG_DARK_GREY);
                fillRect(40, 8, 1, 1, FG_DARK_GREY);
                fillRect(41, 9, 1, 1, FG_DARK_GREY);
                fillRect(42, 10, 1, 1, FG_DARK_GREY);
                fillRect(43, 11, 1, 1, FG_DARK_GREY);
                fillRect(44, 12, 1, 1, FG_DARK_GREY);

                fillRect(37, 12, 1, 1, FG_DARK_GREY);
                fillRect(38, 11, 1, 1, FG_DARK_GREY);
                fillRect(39, 10, 1, 1, FG_DARK_GREY);
                fillRect(40, 9, 1, 1, FG_DARK_GREY);
                fillRect(41, 8, 1, 1, FG_DARK_GREY);
                fillRect(42, 7, 1, 1, FG_DARK_GREY);
                fillRect(43, 6, 1, 1, FG_DARK_GREY);
                fillRect(44, 5, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }
            else
            {
                // O letter e section
                fillRect(36, 8, 1, 1, FG_DARK_GREY);
                fillRect(36, 9, 1, 1, FG_DARK_GREY);
                fillRect(37, 7, 1, 1, FG_DARK_GREY);
                fillRect(38, 6, 1, 1, FG_DARK_GREY);
                fillRect(39, 5, 1, 1, FG_DARK_GREY);
                fillRect(40, 5, 1, 1, FG_DARK_GREY);
                fillRect(41, 5, 1, 1, FG_DARK_GREY);
                fillRect(42, 6, 1, 1, FG_DARK_GREY);
                fillRect(43, 7, 1, 1, FG_DARK_GREY);
                fillRect(44, 8, 1, 1, FG_DARK_GREY);
                fillRect(44, 9, 1, 1, FG_DARK_GREY);
                fillRect(43, 10, 1, 1, FG_DARK_GREY);
                fillRect(42, 11, 1, 1, FG_DARK_GREY);
                fillRect(41, 12, 1, 1, FG_DARK_GREY);
                fillRect(40, 12, 1, 1, FG_DARK_GREY);
                fillRect(39, 12, 1, 1, FG_DARK_GREY);
                fillRect(38, 11, 1, 1, FG_DARK_GREY);
                fillRect(37, 10, 1, 1, FG_DARK_GREY);
                currentPlayer = 'X';
                break;
            }

        case 4: row = 1; column = 0;
            // A spot
            if (currentPlayer == 'X')
            {
                // X letter a section
                fillRect(5, 21, 1, 1, FG_DARK_GREY);
                fillRect(6, 22, 1, 1, FG_DARK_GREY);
                fillRect(7, 23, 1, 1, FG_DARK_GREY);
                fillRect(8, 24, 1, 1, FG_DARK_GREY);
                fillRect(9, 25, 1, 1, FG_DARK_GREY);
                fillRect(10, 26, 1, 1, FG_DARK_GREY);
                fillRect(11, 27, 1, 1, FG_DARK_GREY);
                fillRect(12, 28, 1, 1, FG_DARK_GREY);

                fillRect(5, 28, 1, 1, FG_DARK_GREY);
                fillRect(6, 27, 1, 1, FG_DARK_GREY);
                fillRect(7, 26, 1, 1, FG_DARK_GREY);
                fillRect(8, 25, 1, 1, FG_DARK_GREY);
                fillRect(9, 24, 1, 1, FG_DARK_GREY);
                fillRect(10, 23, 1, 1, FG_DARK_GREY);
                fillRect(11, 22, 1, 1, FG_DARK_GREY);
                fillRect(12, 21, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }
            else
            {
                // O letter a section
                fillRect(4, 24, 1, 1, FG_DARK_GREY);
                fillRect(4, 25, 1, 1, FG_DARK_GREY);
                fillRect(5, 26, 1, 1, FG_DARK_GREY);
                fillRect(6, 27, 1, 1, FG_DARK_GREY);
                fillRect(7, 28, 1, 1, FG_DARK_GREY);
                fillRect(8, 28, 1, 1, FG_DARK_GREY);
                fillRect(9, 28, 1, 1, FG_DARK_GREY);
                fillRect(10, 27, 1, 1, FG_DARK_GREY);
                fillRect(11, 26, 1, 1, FG_DARK_GREY);
                fillRect(12, 25, 1, 1, FG_DARK_GREY);
                fillRect(12, 24, 1, 1, FG_DARK_GREY);
                fillRect(11, 23, 1, 1, FG_DARK_GREY);
                fillRect(10, 22, 1, 1, FG_DARK_GREY);
                fillRect(9, 21, 1, 1, FG_DARK_GREY);
                fillRect(8, 21, 1, 1, FG_DARK_GREY);
                fillRect(7, 21, 1, 1, FG_DARK_GREY);
                fillRect(6, 22, 1, 1, FG_DARK_GREY);
                fillRect(5, 23, 1, 1, FG_DARK_GREY);
                currentPlayer = 'X';
                break;
            }

        case 5: row = 1; column = 1;
            // S spot
            if (currentPlayer == 'X')
            {
                // X letter s section
                fillRect(21, 21, 1, 1, FG_DARK_GREY);
                fillRect(22, 22, 1, 1, FG_DARK_GREY);
                fillRect(23, 23, 1, 1, FG_DARK_GREY);
                fillRect(24, 24, 1, 1, FG_DARK_GREY);
                fillRect(25, 25, 1, 1, FG_DARK_GREY);
                fillRect(26, 26, 1, 1, FG_DARK_GREY);
                fillRect(27, 27, 1, 1, FG_DARK_GREY);
                fillRect(28, 28, 1, 1, FG_DARK_GREY);

                fillRect(21, 28, 1, 1, FG_DARK_GREY);
                fillRect(22, 27, 1, 1, FG_DARK_GREY);
                fillRect(23, 26, 1, 1, FG_DARK_GREY);
                fillRect(24, 25, 1, 1, FG_DARK_GREY);
                fillRect(25, 24, 1, 1, FG_DARK_GREY);
                fillRect(26, 23, 1, 1, FG_DARK_GREY);
                fillRect(27, 22, 1, 1, FG_DARK_GREY);
                fillRect(28, 21, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }
            else
            {
                // O letter s section
                fillRect(20, 24, 1, 1, FG_DARK_GREY);
                fillRect(20, 25, 1, 1, FG_DARK_GREY);
                fillRect(21, 26, 1, 1, FG_DARK_GREY);
                fillRect(22, 27, 1, 1, FG_DARK_GREY);
                fillRect(23, 28, 1, 1, FG_DARK_GREY);
                fillRect(24, 28, 1, 1, FG_DARK_GREY);
                fillRect(25, 28, 1, 1, FG_DARK_GREY);
                fillRect(26, 27, 1, 1, FG_DARK_GREY);
                fillRect(27, 26, 1, 1, FG_DARK_GREY);
                fillRect(28, 25, 1, 1, FG_DARK_GREY);
                fillRect(28, 24, 1, 1, FG_DARK_GREY);
                fillRect(27, 23, 1, 1, FG_DARK_GREY);
                fillRect(26, 22, 1, 1, FG_DARK_GREY);
                fillRect(25, 21, 1, 1, FG_DARK_GREY);
                fillRect(24, 21, 1, 1, FG_DARK_GREY);
                fillRect(23, 21, 1, 1, FG_DARK_GREY);
                fillRect(22, 22, 1, 1, FG_DARK_GREY);
                fillRect(21, 23, 1, 1, FG_DARK_GREY);
                currentPlayer = 'X';
                break;
            }



        case 6: row = 1; column = 2;
            // D spot
            if (currentPlayer == 'X')
            {
                // X letter d section
                fillRect(37, 21, 1, 1, FG_DARK_GREY);
                fillRect(38, 22, 1, 1, FG_DARK_GREY);
                fillRect(39, 23, 1, 1, FG_DARK_GREY);
                fillRect(40, 24, 1, 1, FG_DARK_GREY);
                fillRect(41, 25, 1, 1, FG_DARK_GREY);
                fillRect(42, 26, 1, 1, FG_DARK_GREY);
                fillRect(43, 27, 1, 1, FG_DARK_GREY);
                fillRect(44, 28, 1, 1, FG_DARK_GREY);

                fillRect(37, 28, 1, 1, FG_DARK_GREY);
                fillRect(38, 27, 1, 1, FG_DARK_GREY);
                fillRect(39, 26, 1, 1, FG_DARK_GREY);
                fillRect(40, 25, 1, 1, FG_DARK_GREY);
                fillRect(41, 24, 1, 1, FG_DARK_GREY);
                fillRect(42, 23, 1, 1, FG_DARK_GREY);
                fillRect(43, 22, 1, 1, FG_DARK_GREY);
                fillRect(44, 21, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }
            else
            {
                // O letter d section
                fillRect(36, 24, 1, 1, FG_DARK_GREY);
                fillRect(36, 25, 1, 1, FG_DARK_GREY);
                fillRect(37, 26, 1, 1, FG_DARK_GREY);
                fillRect(38, 27, 1, 1, FG_DARK_GREY);
                fillRect(39, 28, 1, 1, FG_DARK_GREY);
                fillRect(40, 28, 1, 1, FG_DARK_GREY);
                fillRect(41, 28, 1, 1, FG_DARK_GREY);
                fillRect(42, 27, 1, 1, FG_DARK_GREY);
                fillRect(43, 26, 1, 1, FG_DARK_GREY);
                fillRect(44, 25, 1, 1, FG_DARK_GREY);
                fillRect(44, 24, 1, 1, FG_DARK_GREY);
                fillRect(43, 23, 1, 1, FG_DARK_GREY);
                fillRect(42, 22, 1, 1, FG_DARK_GREY);
                fillRect(41, 21, 1, 1, FG_DARK_GREY);
                fillRect(40, 21, 1, 1, FG_DARK_GREY);
                fillRect(39, 21, 1, 1, FG_DARK_GREY);
                fillRect(38, 22, 1, 1, FG_DARK_GREY);
                fillRect(37, 23, 1, 1, FG_DARK_GREY);
                currentPlayer = 'X';
                break;
            }



        case 7: row = 2; column = 0;
            //Z spot
            if (currentPlayer == 'X')
            {
                // X letter z section
                fillRect(5, 44, 1, 1, FG_DARK_GREY);
                fillRect(6, 43, 1, 1, FG_DARK_GREY);
                fillRect(7, 42, 1, 1, FG_DARK_GREY);
                fillRect(8, 41, 1, 1, FG_DARK_GREY);
                fillRect(9, 40, 1, 1, FG_DARK_GREY);
                fillRect(10, 39, 1, 1, FG_DARK_GREY);
                fillRect(11, 38, 1, 1, FG_DARK_GREY);
                fillRect(12, 37, 1, 1, FG_DARK_GREY);

                fillRect(12, 44, 1, 1, FG_DARK_GREY);
                fillRect(11, 43, 1, 1, FG_DARK_GREY);
                fillRect(10, 42, 1, 1, FG_DARK_GREY);
                fillRect(9, 41, 1, 1, FG_DARK_GREY);
                fillRect(8, 40, 1, 1, FG_DARK_GREY);
                fillRect(7, 39, 1, 1, FG_DARK_GREY);
                fillRect(6, 38, 1, 1, FG_DARK_GREY);
                fillRect(5, 37, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }
            else
            {
                // O letter z section
                fillRect(4, 40, 1, 1, FG_DARK_GREY);
                fillRect(4, 41, 1, 1, FG_DARK_GREY);
                fillRect(5, 42, 1, 1, FG_DARK_GREY);
                fillRect(6, 43, 1, 1, FG_DARK_GREY);
                fillRect(7, 44, 1, 1, FG_DARK_GREY);
                fillRect(8, 44, 1, 1, FG_DARK_GREY);
                fillRect(9, 44, 1, 1, FG_DARK_GREY);
                fillRect(10, 43, 1, 1, FG_DARK_GREY);
                fillRect(11, 42, 1, 1, FG_DARK_GREY);
                fillRect(12, 41, 1, 1, FG_DARK_GREY);
                fillRect(12, 40, 1, 1, FG_DARK_GREY);
                fillRect(11, 39, 1, 1, FG_DARK_GREY);
                fillRect(10, 38, 1, 1, FG_DARK_GREY);
                fillRect(9, 37, 1, 1, FG_DARK_GREY);
                fillRect(8, 37, 1, 1, FG_DARK_GREY);
                fillRect(7, 37, 1, 1, FG_DARK_GREY);
                fillRect(6, 38, 1, 1, FG_DARK_GREY);
                fillRect(5, 39, 1, 1, FG_DARK_GREY);
                currentPlayer = 'X';
                break;
            }



        case 8: row = 2; column = 1;
            // X spot
            if (currentPlayer == 'X')
            {
                // X letter x section
                fillRect(21, 37, 1, 1, FG_DARK_GREY);
                fillRect(22, 38, 1, 1, FG_DARK_GREY);
                fillRect(23, 39, 1, 1, FG_DARK_GREY);
                fillRect(24, 40, 1, 1, FG_DARK_GREY);
                fillRect(25, 41, 1, 1, FG_DARK_GREY);
                fillRect(26, 42, 1, 1, FG_DARK_GREY);
                fillRect(27, 43, 1, 1, FG_DARK_GREY);
                fillRect(28, 44, 1, 1, FG_DARK_GREY);

                fillRect(21, 44, 1, 1, FG_DARK_GREY);
                fillRect(22, 43, 1, 1, FG_DARK_GREY);
                fillRect(23, 42, 1, 1, FG_DARK_GREY);
                fillRect(24, 41, 1, 1, FG_DARK_GREY);
                fillRect(25, 40, 1, 1, FG_DARK_GREY);
                fillRect(26, 39, 1, 1, FG_DARK_GREY);
                fillRect(27, 38, 1, 1, FG_DARK_GREY);
                fillRect(28, 37, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }
            else
            {
                // O letter x section
                fillRect(20, 40, 1, 1, FG_DARK_GREY);
                fillRect(20, 41, 1, 1, FG_DARK_GREY);
                fillRect(21, 42, 1, 1, FG_DARK_GREY);
                fillRect(22, 43, 1, 1, FG_DARK_GREY);
                fillRect(23, 44, 1, 1, FG_DARK_GREY);
                fillRect(24, 44, 1, 1, FG_DARK_GREY);
                fillRect(25, 44, 1, 1, FG_DARK_GREY);
                fillRect(26, 43, 1, 1, FG_DARK_GREY);
                fillRect(27, 42, 1, 1, FG_DARK_GREY);
                fillRect(28, 41, 1, 1, FG_DARK_GREY);
                fillRect(28, 40, 1, 1, FG_DARK_GREY);
                fillRect(27, 39, 1, 1, FG_DARK_GREY);
                fillRect(26, 38, 1, 1, FG_DARK_GREY);
                fillRect(25, 37, 1, 1, FG_DARK_GREY);
                fillRect(24, 37, 1, 1, FG_DARK_GREY);
                fillRect(23, 37, 1, 1, FG_DARK_GREY);
                fillRect(22, 38, 1, 1, FG_DARK_GREY);
                fillRect(21, 39, 1, 1, FG_DARK_GREY);
                currentPlayer = 'X';
                break;
            }



        case 9: row = 2; column = 2;
            // C spot
            if (currentPlayer == 'X')
            {
                // X letter C section
                fillRect(37, 37, 1, 1, FG_DARK_GREY);
                fillRect(38, 38, 1, 1, FG_DARK_GREY);
                fillRect(39, 39, 1, 1, FG_DARK_GREY);
                fillRect(40, 40, 1, 1, FG_DARK_GREY);
                fillRect(41, 41, 1, 1, FG_DARK_GREY);
                fillRect(42, 42, 1, 1, FG_DARK_GREY);
                fillRect(43, 43, 1, 1, FG_DARK_GREY);
                fillRect(44, 44, 1, 1, FG_DARK_GREY);

                fillRect(37, 44, 1, 1, FG_DARK_GREY);
                fillRect(38, 43, 1, 1, FG_DARK_GREY);
                fillRect(39, 42, 1, 1, FG_DARK_GREY);
                fillRect(40, 41, 1, 1, FG_DARK_GREY);
                fillRect(41, 40, 1, 1, FG_DARK_GREY);
                fillRect(42, 39, 1, 1, FG_DARK_GREY);
                fillRect(43, 38, 1, 1, FG_DARK_GREY);
                fillRect(44, 37, 1, 1, FG_DARK_GREY);
                currentPlayer = 'O';
                break;
            }
            else
            {
                // O letter c section
                fillRect(36, 40, 1, 1, FG_DARK_GREY);
                fillRect(36, 41, 1, 1, FG_DARK_GREY);
                fillRect(37, 42, 1, 1, FG_DARK_GREY);
                fillRect(38, 43, 1, 1, FG_DARK_GREY);
                fillRect(39, 44, 1, 1, FG_DARK_GREY);
                fillRect(40, 44, 1, 1, FG_DARK_GREY);
                fillRect(41, 44, 1, 1, FG_DARK_GREY);
                fillRect(42, 43, 1, 1, FG_DARK_GREY);
                fillRect(43, 42, 1, 1, FG_DARK_GREY);
                fillRect(44, 41, 1, 1, FG_DARK_GREY);
                fillRect(44, 40, 1, 1, FG_DARK_GREY);
                fillRect(43, 39, 1, 1, FG_DARK_GREY);
                fillRect(42, 38, 1, 1, FG_DARK_GREY);
                fillRect(41, 37, 1, 1, FG_DARK_GREY);
                fillRect(40, 37, 1, 1, FG_DARK_GREY);
                fillRect(39, 37, 1, 1, FG_DARK_GREY);
                fillRect(38, 38, 1, 1, FG_DARK_GREY);
                fillRect(37, 39, 1, 1, FG_DARK_GREY);
                currentPlayer = 'x';
                break;
            }



        default:
            break;
        }

        if (keyIsDown(VK_F1))
        {
            choice = 1;
        }
        else if (keyIsDown(VK_F2))
        {
            choice = 2;
        }
        else if (keyIsDown(VK_F3))
        {
            choice = 3;
        }
        else if (keyIsDown(VK_F4))
        {
            choice = 4;
        }
        else if (keyIsDown(VK_F5))
        {
            choice = 5;
        }
        else if (keyIsDown(VK_F6))
        {
            choice = 6;
        }
        else if (keyIsDown(VK_F7))
        {
            choice = 7;
        }
        else if (keyIsDown(VK_F8))
        {
            choice = 8;
        }
        else if (keyIsDown(VK_F9))
        {
            choice = 9;
        }

        //if (turn == 'X' && board[row][column] != 'X' && board[row][column] != 'O')
        //{
        //    //updating the position for 'X' symbol if
        //    //it is not already occupied
        //    board[row][column] = 'X';
        //    turn = 'O';
        //}
        //else if (turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O')
        //{
        //    //updating the position for 'O' symbol if
        //    //it is not already occupied
        //    board[row][column] = 'O';
        //    turn = 'X';
        //}
        //else
        //{
        //    //if input position already filled
        //    //cout << "Box already filled!n Please choose another!!nn";
        //    player_turn();
        //}
        /* Ends */
        //display_board();



    }
    while (!playerHasQuit);                                    // Only stop when playerHasQuit  
    return;


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

            player_turn();
                /// Play Snake on easy
            //textpixels::startFrame();

                //while (gameover())
                //{        wallDraw();

                //    player_turn();
                //    gameover();
                //}
                //if (turn == 'X' && draw == false) {
                //    cout << "nnCongratulations!Player with 'X' has won the game";
                //}
                //else if (turn == 'O' && draw == false) {
                //    cout << "nnCongratulations!Player with 'O' has won the game";
                //}
                //else
                //    cout << "nnGAME DRAW!!!nn";





                screen = MENU;
                break;

                //textpixels::endFrame();                              // Needed always at end of game loop.

        case MEDIUM:
            /// Play Snake on medium
            setFps(15);
            //playSnake();
            screen = MENU;
            break;
        case HARD:
            /// Play Snake on hard
            setFps(20);
            //playSnake();
            screen = MENU;
            break;
            }
        }
    showQuitScreen();

    return (0);
}
