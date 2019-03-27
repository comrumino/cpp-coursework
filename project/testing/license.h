#pragma once
#include <functional>
#include <string>

class License
{
public:
    int pubint = 6;
    template<typename F> 
    explicit License(F strategy) : strategy(strategy) { }
    void run () {strategy();}
private:
    int prvint = 9;
    std::function<void()> strategy;
};

void jedi();
