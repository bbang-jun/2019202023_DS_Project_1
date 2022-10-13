#include "Manager.h"

int main()
{
    Manager *m = new Manager; // intantiation Manager class
    m->Run("command.txt"); // Run function is main fuction to read command.txt

    delete m; // delete intatnce to memory deallocate

    return 0;
}