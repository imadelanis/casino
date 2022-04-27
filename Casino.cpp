/*
 * File:   Casino.cpp
 * Author: Imad Anis <imad.anis@neumann.ai>
 *
 */

#include <cstdlib> // Needed to use random numbers
#include <ctime> // Needed to define random seed
#include "Game.h" //Include game header file
#include "Log.h"

#ifdef DEBUGMODE
void* operator new (size_t size)
{
    void* p = malloc(size);
    std::cout << "++ Memory reserved:" << p << " ++" << std::endl;
    return p;
}
void operator delete(void* memory)
{
    std::cout << "-- Memory deleted:" << memory << " --" << std::endl;
    free(memory);
}
#endif // DEBUG

 //Init log configuration // had to put the declaration outsie the main function to work 
LOG_CONFIG_DEF LOG_CFG = {};

int main()
{
    //LOG CONFIGURATION
    LOG_CFG.headers = true;
    LOG_CFG.level = TYPE_LOG::NONE; //Change DEBUG LEVEL 

    std::srand(time(0)); //use current time as seed for random generator
    Game game; //Initiate game
   
    return 0;
}

