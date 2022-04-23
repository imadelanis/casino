#include <iostream> //Needed to use inputs / outputs
#include <string> // Needed to use strings
#include <cstdlib> // Needed to use random numbers
#include <ctime> // Needed to define random seed
#include <map> //Needed to store players
#include <limits> //Needed to espace new lines while inputing strings
#include <vector> //Needed to sort players
#include <algorithm> //Needed to sort Players

#define DEBUG 1; //To be defined by configuration 

#if DEBUG == 1
void* operator new (size_t size) 
{
    void* p = malloc(size);
    std::cout << "-- Memory reserved:" << p << " --" << std::endl;
    return p;
}
void operator delete(void* memory) 
{
    std::cout << "-- Memory deleted:" << memory << " --" << std::endl;
    free(memory);
}


#endif // DEBUG


enum class GUESS_STATUS {
    WON, LOST
};

const int WON_VALUE = 10;

class Player
{
private:
    
    std::string playerName; // stores player's name
    int balance{ 0 }; // stores player's balance
    int bettingAmount; //sotre betting amount 
    int playerIndex; // stores player's index

public:
    static int playerCount; // stores created players count

    Player() : playerName(""), balance(0)
    { 
        playerIndex = ++playerCount;
        
        #if  DEBUG == 1
        std::cout << "\n\nPlayer " << playerIndex << " created!!" << std::endl;
        #endif // DEBUG

        init();
    }

    void init() {
        std::cout << "\n\nEnter Player " << playerIndex << " info!!" << std::endl;
        //Ask for name
        requestPlayerName(false);
        //Ask for balance
        requestPlayerBalance();
    }

    void requestPlayerName(bool newName) {
        //Ask for name
        std::cout << (newName ? "Same name already exists! Enter new Name :" : "Enter the Name :");
        //workarround to be abel to mix getLine and >> for inputs
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, playerName);
    }

    void requestPlayerBalance() {
        //Ask for balance
        std::cout << "Enter the starting balance: $";
        std::cin >> balance;
    }

    const int refreshBalance(GUESS_STATUS status)
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

    const int getBalance() const
    {
        return balance;
    }

    void setBalance(int b) {
        balance = b;
    }

    bool bet(int amount)
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

    const int getBettingAmount() const
    {
        return bettingAmount;
    }

    void setBettingAmount(int a) {
        bettingAmount = a;
    }


    const std::string& getPlayerName() const
    {
        return playerName;
    }

    void setPlayerName(std::string& name) {
        playerName = name;
    }

    //it is important to make operator overloading function a friend of the class because it would be called without creating an object.
    friend std::ostream& operator<<(std::ostream& output, const Player& player)
    {
        return std::cout << "Player" << player.playerIndex << ": " << player.playerName << ", Current Balance : $" << player.balance << std::endl;
    }

    bool operator< (const Player& otherPlayer) {
        return balance < otherPlayer.balance;
    }

    bool operator> (const Player& otherPlayer) {
        return balance > otherPlayer.balance;
    }


    ~Player() {
        
        #if  DEBUG == 1
        std::cout << "Player " << playerIndex << " destroyed !!" << std::endl;
        #endif;
        playerCount--;
    }

};

//required to initialize the player index
int Player::playerCount = 0;

class Game
{
    private:
        int round{ 0 };
        int playersCount{ 1 };
        std::map<std::string, Player*> players;
        int current_guess;
        int currentDice; //stores the random number
        
        void rules()
        {
            system("cls");
            std::cout << "\t\t======CASINO NUMBER GUESSING RULES!======\n";
            std::cout << "\t1. Choose a number between 1 to 10\n";
            std::cout << "\t2. Winner gets " << WON_VALUE << " times of the money bet\n";
            std::cout << "\t3. Wrong bet, and you lose the amount you bet\n\n";
        }

    public:
        Game() {
            rules();
            init();
        };

        void init() {
            //Ask for balance
            std::cout << "\n\nEnter the number of players:";
            std::cin >> playersCount;

            //Initialize players
            for (int i = 0; i < playersCount; ++i)
            {
                Player* player = new Player();
                //Request new name if name already exists
                auto playerExists = players.find(player->getPlayerName());
                while (players.find(player->getPlayerName())!= players.end()) {
                    player->requestPlayerName(true);
                }
                //Add player to the list
                players.emplace(player->getPlayerName(), player);
                
            }

            //Start game
            start();

        }

        void start()
        {
            
            char coninuePlay;
            int bettingAmount;
            int guess;
            int dice; // stores the random number

            do
            {
                system("cls");

                //increment round 
                ++round;

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
            
            std::cout << "\n\n\n";
            std::cout << "\n\nThanks for playing the game.\n\n";
            
        }

        void summary()
        {
            std::cout << "\nRound " << round  << " Summary: " << std::endl;
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

        ~Game() {
            for (auto player : players) {
               //destroy players
               delete player.second;
            }
        }

};


int main()
{
    std::srand(time(0)); //use current time as seed for random generator
    Game game; //Initiate game
    return 0;
}

