#include <iostream>
#include "Command.hpp"

int main()
{
    Document doc;

    PasteCommand pCommand(&doc);
    OpenCommand oCommand(&doc);

    Invoker invok(&pCommand, &oCommand);
    
    invok.run();

    return 0;
}
