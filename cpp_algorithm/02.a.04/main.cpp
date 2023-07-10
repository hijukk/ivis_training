#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

bool isBinary(const std::string& a, const std::string& b){
    bool check = false;

    auto it = std::find_if(a.begin(), a.end(), [](char c){ return ('0' != c) && ('1' != c); });
    auto it2 = std::find_if(b.begin(), b.end(), [](char c){ return ('0' != c) && ('1' != c); });

    if (it == a.end() && it2 == b.end()) 
    {
        check = true;
    }

    return check;
}


std::string calculate(std::string& a, std::string& b, const std::string& op) {
    std::string str_bin;

    int num1 = std::stoi(a, 0, 2);
    int num2 = std::stoi(b, 0, 2);
    int result = 0;
    int rem = 0;
    int max = std::max({a.length(), b.length(), str_bin.length()});

    if (0 == op.compare("or"))
    {
        result = num1 | num2;
    }
    else if (0 == op.compare("and")) 
    {
        result = num1 & num2;
    }
    else if (0 == op.compare("xor")) 
    {
        result = num1 ^ num2;
    }
    else if (0 == op.compare("nor")) 
    {
        result = std::pow(2, max) + ~(num1 | num2);
    }

    while(0 != result)
    {
        rem = result % 2;
        str_bin.insert(0, std::to_string(rem));
        result /= 2;
    }

    if((a.length() != str_bin.length()) || (b.length() != str_bin.length()))
    {
        str_bin.insert(0, max - str_bin.length(), '0');
    }

    return str_bin;
}

int main() {
    std::string a;
    std::string b;
    std::string op;

    std::cout << "A: ";
    std::cin >> a;

    std::cout << "B: ";
    std::cin >> b;

    std::cout << "OP: ";
    std::cin >> op;

    if(isBinary(a,b))
    {
        std::cout << "Result: " << calculate(a, b, op) << std::endl;
    }
    else
    {
        std::cout << "Invalid argument" << std::endl;
    }

    return 0;
}