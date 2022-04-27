/*
 * File:   Player.cpp
 * Author: Imad Anis <imad.anis@neumann.ai>
 *
 */

#include <iostream> //Needed to use inputs / outputs
#include <string> // Needed to use strings

#include "Const.h" //Include consts header file
#include "Player.h" //Include player header file
#include "Log.h" //Include log header file

//required to initialize the player index
int Player::playerCount = 0;

//Constructor
Player::Player() : playerName(""), balance(0)
{
    
    playerIndex = ++playerCount;

    LOG(TYPE_LOG::DEBUG) << "PLayer " << playerIndex << " Constructed";
    
    init();
}

void Player::init() {
    std::cout << "\n\nEnter Player " << playerIndex << " info!!" << std::endl;
    //Ask for name
    requestPlayerName(false);
    //Ask for balance
    requestPlayerBalance();
}

void Player::requestPlayerName(bool newName) {
    //Ask for name
    std::cout << (newName ? "Same name already exists! Enter new Name :" : "Enter the Name :");
    //workarround to be abel to mix getLine and >> for inputs
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, playerName);
}

void Player::requestPlayerBalance() {
    //Ask for balance
    std::cout << "Enter the starting balance: $";
    std::cin >> balance;
}

const int Player::refreshBalance(GUESS_STATUS status)
{
    int wonAmount;
    switch (status) {
    case GUESS_STATUS::WON:
        wonAmount = bettingAmount * WON_VALUE;
        std::cout << "You are in luck!! You have won $" << wonAmount << std::endl;
        balance = balance + wonAmount;
        break;
    case GUESS_STATUS::LOST:
        std::cout << "Oops, better luck next time !! You lost $" << bettingAmount << std::endl;
        balance = balance - bettingAmount;
        break;
    }
    // Info user if he can't play again
    if (balance == 0)
    {
        std::cout << "You have no money to play again !!" << std::endl;
    }
    return balance;
}

const int Player::getBalance() const
{
    return balance;
}

void Player::setBalance(int b) {
    balance = b;
}

bool Player::bet(int amount)
{
    //check if bett entered is valid
    if (amount > balance) {
        std::cout << "Betting balance can't be more than current balance!" << std::endl;
        return false;
    }
    else
    {
        bettingAmount = amount;
        return true;
    }
}

const int Player::getBettingAmount() const
{
    return bettingAmount;
}

void Player::setBettingAmount(int a) {
    bettingAmount = a;
}


const std::string& Player::getPlayerName() const
{
    return playerName;
}

void Player::setPlayerName(std::string& name) {
    playerName = name;
}

std::ostream& operator<<(std::ostream& output, Player const& player)
{
    return std::cout << "Player" << player.playerIndex << ": " << player.playerName << ", Current Balance : $" << player.balance << std::endl;
}

bool Player::operator< (const Player& otherPlayer) {
    return balance < otherPlayer.balance;
}

bool Player::operator> (const Player& otherPlayer) {
    return balance > otherPlayer.balance;
}

Player::~Player() {

    LOG(TYPE_LOG::DEBUG) << "PLayer " << playerIndex << " Destructed";

    playerCount--;
}