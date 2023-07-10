#include <iostream>

int main()
{   
    int rows;
    
    std::cout << "Input number of rows: ";
    std::cin >> rows;

    for(int r = 1 ; r <= rows; ++r)
    {
        for(int i = rows - 1; i >= r; --i)
        {
            std::cout << " " ;
        }
    
        for(int x = 1; x <= r; ++x)
        {
            std::cout << x ;
        }
        for(int x = (r-1); x >= 1; --x)
        {
            std::cout << x ;
        }
        std::cout << std::endl;
    }

    return 0;
}