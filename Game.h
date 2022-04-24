#pragma once
#include <string> // Needed to use strings
#include <map> //Needed to store players

#include "Player.h" //Include player header file

class Game
{
private:
    int round{ 0 };
    int playersCount{ 1 };
    std::map<std::string, Player*> players;
    int current_guess;
    int currentDice; //stores the random number
    void rules(); //show game rules
    void init(); //init the game
    void start(); //start game

public:
    Game();
    void summary(); //show game summary
    ~Game();
};