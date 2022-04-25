#pragma once
#include <iostream> //Needed to use inputs / outputs
#include <string> // Needed to use strings

enum class GUESS_STATUS {
    WON, LOST
};

class Player
{
private:

    std::string playerName; // stores player's name
    int balance{ 0 }; // stores player's balance
    int bettingAmount; //sotre betting amount 
    int playerIndex; // stores player's index
    void init(); //intitialize private function

public:
    static int playerCount; // stores created players count,
    //inline static int playerCount{0}; // stores created players count, inline added to be able to declare the the static memeber inline c++ 17
    Player(); //constructor
    void requestPlayerName(bool newName);
    void requestPlayerBalance();
    const int refreshBalance(GUESS_STATUS status);
    const int getBalance() const;
    void setBalance(int b);
    bool bet(int amount);
    const int getBettingAmount() const;
    void setBettingAmount(int a);
    const std::string& getPlayerName() const;
    void setPlayerName(std::string& name);
    //Make operator overloading function a friend of the class to be able to access the private memebers of the class.
    friend std::ostream& operator<<(std::ostream& output, Player const& player);
    bool operator< (const Player& otherPlayer);
    bool operator> (const Player& otherPlayer);

    ~Player();

};