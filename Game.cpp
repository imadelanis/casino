/*
 * File:   Game.cpp
 * Author: Imad Anis <imad.anis@neumann.ai>
 *
 */

#include <iostream> //Needed to use inputs / outputs
#include <string> // Needed to use strings
#include <cstdlib> // Needed to use random numbers
#include <ctime> // Needed to define random seed
#include <map> //Needed to store players
#include <limits> //Needed to espace new lines while inputing strings
#include <vector> //Needed to sort players
#include <algorithm> //Needed to sort Players

#include "Const.h" //Include consts header file
#include "Game.h" //Include game header file
#include "Player.h" //Include player header file
#include "Log.h" //Include log header file

Game::Game() {

    LOG(TYPE_LOG::DEBUG) << "GAME Constructed";
    rules();
    init();
};

void Game::rules()
{
    #ifndef DEBUGMODE
        system("cls"); //clear screen if debug mode is disabled 
    #endif
    
    LOG(TYPE_LOG::INFO) << "Print RULES";

    std::cout << "\t\t======CASINO NUMBER GUESSING RULES!======\n";
    std::cout << "\t1. Choose a number between 1 to 10\n";
    std::cout << "\t2. Winner gets " << WON_VALUE << " times of the money bet\n";
    std::cout << "\t3. Wrong bet, and you lose the amount you bet\n\n";
}

void Game::init() {

    LOG(TYPE_LOG::INFO) << "Initialize GAME";

    //Ask for number of players
    std::cout << "\n\nEnter the number of players:";
    std::cin >> playersCount;

    //Initialize players
    for (int i = 0; i < playersCount; ++i)
    {
        Player* player = new Player();
        //Request new name if name already exists
        auto playerExists = players.find(player->getPlayerName());
        while (players.find(player->getPlayerName()) != players.end()) {
            player->requestPlayerName(true);
        }
        //Add player to the list
        players.emplace(player->getPlayerName(), player);
    }

    //Start game
    start();

}

void Game::start()
{

    char coninuePlay; //used as glag to continue play or not
    int bettingAmount; // bett amount entred by player 
    int guess; // the number to gess
    int dice; // stores the random number

    do
    {
        #ifndef DEBUGMODE
            system("cls"); //clear screen if debug mode is disabled 
        #endif

        LOG(TYPE_LOG::INFO) << "Start GAME ROUND";

        //increment round 
        ++round;

        LOG(TYPE_LOG::INFO) << "Round " << round << " Started !!";

        //Show players summary 
        summary();

        //Loop over all players 
        for (auto p : players) {

            //Player 
            Player* player = p.second;

            //Check if have enough balance to play
            if (player->getBalance() > 0) {


                std::cout << "\n\nHey, " << player->getPlayerName() << std::endl;

                //Get player's betting balance
                do
                {
                    std::cout << "Enter amount to bet : $";
                    std::cin >> bettingAmount;
                } while (!player->bet(bettingAmount));

                // Get player's numbers
                std::cout << "Guess any betting number between 1 & 10 :" << std::endl;
                do
                {
                    std::cout << "Enter number :";
                    std::cin >> guess;
                    if (guess <= 0 || guess > 10)
                        std::cout << "Number should be between 1 to 10" << std::endl;
                } while (guess <= 0 || guess > 10);

                //Evaluate number 
                dice = rand() % 10 + 1; //random number
                std::cout << "**********************************************" << std::endl;
                std::cout << "The winning number is : " << dice << std::endl;
                if (dice == guess)
                {
                    player->refreshBalance(GUESS_STATUS::WON);
                }
                else
                {
                    player->refreshBalance(GUESS_STATUS::LOST);
                }
                std::cout << "**********************************************" << std::endl;
                //
                //Pause to show the results
                std::cout << "\nPress ENTER to continue...." << std::endl;
                std::cin.ignore();
                std::cin.get();
                //  
                //Show players summary 
                summary();
            }

        }

        //check if 1 player at least can play. 
        bool canPlayAgain = false;
        for (auto player : players) {
            if (player.second->getBalance() > 0) {
                canPlayAgain = true;
                break;
            }
        }
        if (canPlayAgain) {
            std::cout << "\n\n-->Do you want to play again (y/n)? ";
            std::cin >> coninuePlay;
        }
        else {
            break;
        }

    } while (coninuePlay == 'Y' || coninuePlay == 'y');

    LOG(TYPE_LOG::INFO) << "End GAME";

    std::cout << "\n\n\n";
    std::cout << "\n\nThanks for playing the game.\n\n";

}

void Game::summary()
{
    LOG(TYPE_LOG::INFO) << "Print GAME Summary";

    std::cout << "\nRound " << round << " Summary: " << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // Copy key-value pair from Map
    // to vector of pairs
    std::vector<std::pair<std::string, Player*> > sortedVector;
    for (auto& it : players) {
        sortedVector.emplace_back(it);
    }
    //Sort vector based on players balance / using lambda function and operator override

    std::sort(sortedVector.begin(), sortedVector.end(), [](std::pair<std::string, Player*>& a, std::pair<std::string, Player*>& b) {

        //Sort descending, dereference to compare players
        return *a.second > *b.second;
        });

    for (auto player : players) {
        //Show player info
        // TODO: to understand why the values on the map get sorted also first time only!!
        //std::cout << *player.second;
    }
    // Print the sorted value
    for (auto& player : sortedVector) {
        //Show player info
        std::cout << *player.second;
    }
    std::cout << "------------------------------------" << std::endl;
}

Game::~Game() {
    LOG(TYPE_LOG::DEBUG) << "GAME Destructed";

    for (auto player : players) {
        //destroy players
        delete player.second;
    }
}