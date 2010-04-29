#include "object.h"
#include "ocean.hpp"

int main() {
    srand(42);
    // TODO: do all the stuff here
    Ocean & ocean = Ocean::Instance();
    ocean.SetSize(10,10);
    //ocean.CreateNewObject(PREY, 3, 3);
    //ocean.CreateNewObject(HUNTER, 8, 8);
    for(int i =0; i < 50; ++i)
      ocean.CreateNewObject(PREY, rand() % 10, rand() % 10);
    for(int i =0; i < 50; ++i)
      ocean.CreateNewObject(HUNTER, rand() % 10, rand() % 10);
    for(int i =0; i < 10; ++i)
      ocean.CreateNewObject(OBSTACLE, rand() % 10, rand() % 10);
    std::cout << "ocean created\n";
    for(int i = 0; i < 30; ++i){
      ocean.TicTac();
      sleep(1);
    }
    //ocean.TicTac();
    return 0;
}
