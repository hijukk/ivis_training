#include <iostream>

long int getFactorial(const int num)
{
    return (num > 1) ? num * getFactorial(num - 1) : 1;
}

int main()
{
    int num;

    std::cout << "input number : ";
    std::cin >> num;

    if ((num >= 0) && (num <= 20))
    {
        printf("Factorial of %d is %ld\n", num, getFactorial(num));
    }
    else
    {
        printf("input number is out of range\n");
    }
    return 0;
}
