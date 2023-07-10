#include <iostream>
#include <string>

int get_decimal(const std::string &binary)
{
    int result = 0;
    int length = binary.length() - 1;

    for (int i = 0; i < binary.length(); ++i, --length)
    {
        const char bin = binary.at(i);

        if(('0' != bin) && ('1' != bin))
        {
            result = 0;
            break;
        }
        
        result += (static_cast<int>(bin - '0') << length);
    }

    return result;
}


int main()
{
    std::string binary;

    std::cout << "Input binary number: ";
    std::cin >> binary;

    int dec = get_decimal(binary);

    printf("Decimal: %d\n", dec);
    printf("Hexadecimal: 0x%X\n", dec);
}