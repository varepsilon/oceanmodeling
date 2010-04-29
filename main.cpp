#include "object.h"
#include "ocean.hpp"

int main() {
    srand(42);
    // TODO: do all the stuff here
    Ocean & ocean = Ocean::Instance();
    ocean.SetSize(10,10);
    ocean.CreateNewObject(PREY, 3, 3);
    ocean.TicTac();
    ocean.TicTac();
    return 0;
}
