/* Game15
 *
 * Class: Board
 * Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author
 * Name: Ilari Räisänen
 * Student number: 291645
 * UserID: mcilra
 * E-Mail: ilari.raisanen@tuni.fi
 *
 * Notes:
 * All of the functions used by the game (except main and shuffle) are declared in here.
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <string>

const int SIZE = 4;


class Board
{
public:

    // If there is an error, value changes to false. Value is used to determine wether
    // to exit with EXIT_SUCCESS or EXIT_FAILURE in main().
    bool exit_success = true;

    // Is set to true if player quits or if there is an error. Is used in multiple
    // while-loops as "while(not quitting)".
    bool quitting = false;

    // Creates the game grid as vector(x-axis) inside another vector(y-axis).
    std::vector<std::vector<unsigned int>> grid_create();

    // Runs check_won- and move-functions, in the beginning and after every command until game ends.
    void play();

    // Calculates if the game is solvable.
    bool solvable();

    // Takes input to make you move the numbers on the board
    int move(std::vector<std::vector<unsigned int>>&grid_);

    // Like quitting, this is used in a while-loop. When it's value is changed to true,
    // game ends.
    bool won=false;

private:

    // Prints the game grid
    void print();

    // Numbers to be used on the board and shuffled if player wishes to use a random
    // board. 16 represents empty.
    std::vector<unsigned int> board_numbers = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

    // grid as vector(x-axis) inside another vector(y-axis).
    std::vector<std::vector<unsigned int>> grid_ = grid_create();

    // Checks if the numbers are in order, is run after every move.
    // Sets bool won -> true when game is won.
    bool check_won();

    // Checks if all 16 numbers exist in the input that is given by the player.
    bool all_exist(std::vector<unsigned int>);

    //
    std::string missing_ = "";
    void check_missing_numbers(std::vector<unsigned int>);
    std::vector<int> find(std::vector<std::vector<unsigned int>>);


};


#endif // BOARD_HH
