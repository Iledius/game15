/* Game15
 *
 * Description:
 * This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author
 * Name: Ilari Räisänen
 * Student number: 291645
 * UserID: mcilra
 * E-Mail: ilari.raisanen@tuni.fi
 *
 * Program almost entirely found in board.cpp. Every function is thoroughly commented and spaced for clarity.
 *
 * */

#include "board.hh"
#include <iostream>


int main()
{
    // Initializes Board -object.
    Board Board;

    // Checks if board is solvable, unless board is missing numbers - if numbers missing, quits with EXIT_SUCCESS.
    if(not Board.quitting){

        if(not Board.solvable()){

            std::cout << "Game is not solvable. What a pity." << std::endl;
            return EXIT_SUCCESS;

        }else{
            std::cout << "Game is solvable: Go ahead!" << std::endl;
        }

        // Play-function runs as long as the game is not won and player hasn't quit.
        while(not Board.won and not Board.quitting){
            Board.play();
        }
    }

    // Value of exit_success is true by default but is changed to false is there
    // is an error while inputting numbers for the board.
    if(Board.exit_success){
        return EXIT_SUCCESS;
    }

    else{
        return EXIT_FAILURE;
    }
}




