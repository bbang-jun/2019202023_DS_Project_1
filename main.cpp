#include "Manager.h"

int main()
{
    Manager *m = new Manager;
    m->Run("command.txt");

    delete m;

    return 0;
}