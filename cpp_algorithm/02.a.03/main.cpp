#include <iostream>
#include <string>
#include <string.h>

int count_word(const std::string& str_word) {
    int count = 0;
    int pos = 0;

    while (std::string::npos != str_word.find(" ", pos)) 
    {
        int found = str_word.find(" ", pos);
        if(found > pos)
        {
            ++count;
            pos = found + 1;
        }
        else if (found == pos)
        {
            pos += 1;
        }
    }
    
    if(str_word[pos] > ' ')
    {
        ++count;
    }

    return count;
}

int count_word2(char* str){
    int count = 0;
    char* ptr = strtok(str, " ");
    
    while(nullptr != ptr)
    {
        ++count;
        ptr = strtok(nullptr, " ");
    }

    return count;
}


int main() {
    std::string str_word;

    std::cout << "Input string: ";
    std::getline(std::cin, str_word);

    if (str_word.empty()) {
        // nothing
    } else {
        std::cout << "number of words: " << count_word(str_word) << std::endl;

        char str[str_word.length() + 1];
        strcpy(str, str_word.c_str());
        std::cout << "number of words2: " << count_word2(str) << std::endl;
    }

    return 0;
}