#include <random>
#include <iostream>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int n = 0; n < 200; ++n) {
    	std::uniform_real_distribution<> dis(0, 4);
        std::cout << (int)dis(gen) << ',';
    }
    std::cout << '\n'; 
}