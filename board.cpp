/* Game15
 *
 * Class: Board
 *
 * Program author
 * Name: Ilari Räisänen
 * Student number: 291645
 * UserID: mcilra
 * E-Mail: ilari.raisanen@tuni.fi
 *
 * Notes:
 * This .cpp file is very long, because every function except main is defined here.
 * There's also plenty of empty rows added for better readability.
 *
 * */

#include "board.hh"
#include <algorithm>
#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;


void Board::play(){

    // Play-loop, keeps running print- and move -functions until game has been won.
    check_won();
    if(check_won()){
        print();
        std::cout << "You won!" << std::endl;
        won = true;
    }
    else{
    print();
    move(grid_);
    }
}

std::vector<int> Board::find(std::vector<std::vector<unsigned int>> grid){

    // Finds coordinates of empty (number 16) from the grid
    int x_coordinate = 0;
    int y_coordinate = 0;
    std::vector<int> coordinates = {};

    for(std::vector<unsigned int> x: grid){
        for(unsigned int y: x){
            if(y == EMPTY){
                coordinates = {x_coordinate, y_coordinate};
                return coordinates;
            }else{
                y_coordinate++;
            }
        }
        x_coordinate++;
        y_coordinate=0;
    }
    std::cout << grid[x_coordinate][y_coordinate] << std::endl;
    return coordinates;
}

bool Board::solvable(){
    const int BOTTOM_ROW = 3;
    int boardnum_index = -1;
    int inversions = 0;

    // x_pos and y_pos are the coordinates of the EMPTY (number 16)
    std::vector<int> empty_pos = find(grid_);
    int x_pos = empty_pos[0];
    int y_pos = empty_pos[1];

    // The number on the bottom row below EMPTY is set to EMPTY, and the that number replaces
    // EMPTY's original position
    unsigned int temp = grid_[BOTTOM_ROW][y_pos];
    grid_[BOTTOM_ROW][y_pos] = EMPTY;
    grid_[x_pos][y_pos] = temp;

    // Flat vector is created from the current grid with the EMPTY in the bottom row
    std::vector<unsigned int> grid_to_vec = {};
    for(std::vector<unsigned int> x : grid_){
        for(unsigned int y : x){
            grid_to_vec.push_back(y);
        }
    }

    // Calculates inversions in the current grid. Each number is checked:
    // each number that is bigger and comes after the checked numbers adds one inversion.
    // If total inversions is divisible by 2, game is solvable.
    for(unsigned int num : grid_to_vec){
        boardnum_index++;
        for(int i=boardnum_index; i < EMPTY; i++){

            if(grid_to_vec[i] < num and num != EMPTY and grid_to_vec[i] != EMPTY){
                inversions++;
            }
        }
    }

    // The grid is returned to its original form.
    grid_[BOTTOM_ROW][y_pos] = temp;
    grid_[x_pos][y_pos] = EMPTY;

    if(inversions % 2 == 0){
        return true;
    }
    else{
        return false;
    }
}


void shuffle(int seed, std::vector<unsigned int> &numbers){

    // Shuffles the numbers 1-16 using seed given by the player after inputing y in the first prompt.
     std::default_random_engine randomEng(seed);
     std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i){

        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
}

std::vector<std::string> split(std::string command){

    std::string temp_string = "";
    std::vector<std::string> words = {};

    // Splits the command only if it's lenght is more than 0 to avoid errors and to
    // allow using one-letter command 'q' (quit).
    if(command.length() > 0 ){

        // Adds characters to temporary string until a separator(space).
        for(char c : command){

            if(c != ' '){
                temp_string += c;

            }else{
                if(temp_string.length()>0){
                    words.push_back(temp_string);
                }

                temp_string = "";
            }
        }
        words.push_back(temp_string);
    }
    else{
        words.push_back(command);
    }
    return words;
}


int Board::move(std::vector<std::vector<unsigned int>> &grid){
    // This is a VERY long function mostly because of the Switch statement.
    std::string command = "";
    std::cout << "Dir (command, number): ";
    unsigned int num_to_move = 1;

    // Asks for a 2-part command to be splitted into direction and number.
    getline(std::cin, command);
    std::vector<std::string> dir_and_num = split(command);
    if(command.length()!=1){num_to_move = stoi(dir_and_num[1]);}

    //
    std::string dir = dir_and_num[0];
    if(dir == "q"){
        quitting = true;
        return 0;
    }

    if((dir != "w" and dir != "a" and dir != "s" and dir != "d")){
        std::cout << "Unknown command: " << dir << std::endl;
        return 0;
    }

    else if(num_to_move > 15){
        std::cout << "Invalid number: " << num_to_move << std::endl;
        return 0;
    }


    // dir is changed to char so that it can be used with switch statement.
    char direction = dir[0];

    // Finds the num_to_move from the board and operates with is using the switch statement.
    for(int x = 0; x < SIZE; ++x){

        for(int y = 0; y < SIZE; ++y){

            if(grid[x][y]==num_to_move){

                switch (direction){

                    case 'w' :{

                        // Won't move the num_to_move if it's on the edge of the board and would fall off.
                       if(x - 1 >= 0){
                           // Won't move the num_to_move if there's another number in the way.
                            if(grid[x-1][y]==EMPTY){
                                  grid[x - 1][y]=grid[x][y];
                                  grid[x][y] = EMPTY;
                                  break;
                            }
                        }
                        std::cout << "Impossible direction: w" << std::endl;
                        break;
                    }

                    case 'd' :{

                        if(y+1 < SIZE){
                            if(grid[x][y+1]==EMPTY){
                                grid[x][y+1]=grid[x][y];
                                grid[x][y] = EMPTY;
                                break;
                            }
                        }
                        break;
                    }


                    case 's' :{

                        if(x+1 < SIZE){
                            if(grid[x+1][y]==EMPTY){
                                grid[x+1][y]=grid[x][y];
                                grid[x][y] = EMPTY;
                                break;
                            }
                            break;
                        }else
                        break;
                    }

                    case 'a' :{

                        if(y-1 >= 0){
                            if(grid[x][y-1]==EMPTY){
                              grid[x][y-1]=grid[x][y];
                              grid[x][y] = EMPTY;
                              break;
                            }
                        }else
                        std::cout << "Impossible direction: a" << std::endl;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

std::vector<std::vector<unsigned int>> Board::grid_create(){

    // Creates the grid with vector(y-axis) inside vector(x-axis).
    std::vector<std::vector<unsigned int>> grid = {{}};
    std::string random_init = "";
    std::string seed_string = "";
    int seed = 0;
    int indx = 0;

    // With random initialization, 15 numbers (and EMPTY) are shuffled to the grid.
    // Without, player can type the number arrangement.
    std::cout << "Random initialization (y/n): ";
    getline(std::cin, random_init);

    // Asks for a new input if something else than y/n is given.
    while(random_init != "y" and random_init != "n"){

        std::cout << "Unknown choice: " << random_init << std::endl;
        std::cout << "Random initialization (y/n): ";
        getline(std::cin, random_init);
    }

    if(random_init == "y"){

        // board_numbers had to be redefined as a new variable to fix
        // some very strange memory errors.
        std::vector<unsigned int> board_numbers
                = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        std::cout << "Enter a seed value (or an empty line): ";

        getline(std::cin, seed_string);

        // If seed value isn't given, current time is used for the seed.
        if(seed_string.length() == 0){
            seed = time(NULL);
        }
        else{
            seed = stoi(seed_string);
        }

        shuffle(seed, board_numbers);

        // After shuffling the numbers, a grid is created out of them.
        for(unsigned int x = 0; x < SIZE; ++x){
            grid.push_back(std::vector<unsigned int>());

            for(unsigned int y = 0; y < SIZE; ++y){
                grid.at(x).push_back(board_numbers.at(indx));
                indx++;
            }
        }
    }


    else if(random_init == "n"){
        std::string chosen_numbers = {};
        std::vector<unsigned int> needed_numbers
                = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

        std::vector<unsigned int> board_numbers = {};
        std::cout << "Enter the numbers 1-16 in a desired order (16 means empty):"
                  << std::endl;


        getline(std::cin, chosen_numbers);
        std::vector<std::string> chosenNumberList = split(chosen_numbers);

        for(std::string numString : chosenNumberList){
            unsigned int tempnum = (unsigned int)stoi(numString);
            board_numbers.push_back(tempnum);
        }

        check_missing_numbers(board_numbers);

        // Creates a grid of the given numbers, unless there was an error.
        // quitting was changed to true if there was an error with numbers given.
        if(not quitting){
            for(unsigned int x = 0; x < SIZE; ++x){
                grid.push_back(std::vector<unsigned int>());
                for(unsigned int y = 0; y < SIZE; ++y){

                    grid.at(x).push_back(board_numbers.at(indx));
                    indx++;
                }
            }
        }
    }

    return grid;
}


void Board::print(){

    for(unsigned int x = 0; x < SIZE; ++x){
        std::cout <<  std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;

        for(unsigned int y = 0; y < SIZE; ++y) {
             std::cout << "|" <<  std::setw(PRINT_WIDTH - 1);

            if(grid_.at(x).at(y) == 16){
                 std::cout << ".";
            }

            else if(grid_.at(x).at(y) != EMPTY) {
                 std::cout << grid_.at(x).at(y);
            }

            else {
                 std::cout << ".";
            }
        }
         std::cout << "|" <<  std::endl;
    }
     std::cout <<  std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

bool Board::check_won()
{
    unsigned int num1 = grid_[0][0];
    unsigned int num2;

    for(std::vector<unsigned int> x: grid_){
        for(unsigned int y: x){
            num2 = y;
            // Checks if every subsequent number is bigger than the last one.
            // If not, game is unfinished so returns false
            if(num1 > num2){
                return false;

            }
            num1 = y;
        }
    }
    return true;
}

void Board::check_missing_numbers(std::vector<unsigned int> given_numbers){

    std::vector<unsigned int> needed_numbers = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    unsigned long not_found_amount = 0;

    for(unsigned int needed_num: needed_numbers){
        for(unsigned int num: given_numbers){

            // If one of the needed 16 numbers isnt in the given numbers,
            // changes quitting to true which breaks play-loop.
            if(num != needed_num){
                not_found_amount++;
            }
            if(not_found_amount == given_numbers.size()){
                std::cout << "Number " << needed_num << " is missing" << std::endl;
                quitting = true;
                break;
            }
        }
        // exit_success changes to false because there was an error.
        if(quitting){
            exit_success = false;
            break;
        }
        not_found_amount = 0;
    }
}

