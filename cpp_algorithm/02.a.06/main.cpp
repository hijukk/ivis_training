#include <iostream>

#define DIAMETER 16

int main() {
    int radius = static_cast<int> (DIAMETER/2);

    for (int x = -radius; x <= radius; ++x) {
        for (int y = -radius ; y <= radius; ++y) {
            if ((x*x + y*y) <= radius*radius) {
                std::cout << "**";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
