#include <cstdlib> // Needed to use random numbers
#include <ctime> // Needed to define random seed
#include "Game.h" //Include player header file

#define DEBUG 0; //To be defined by configuration 

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

int main()
{
    std::srand(time(0)); //use current time as seed for random generator
    Game game; //Initiate game
    return 0;
}

