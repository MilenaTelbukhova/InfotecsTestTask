#include<chrono>
#include<iostream>
#include "logger.h"

int main()
{
    auto logger = Logger("journal.txt", ImportanceLevel::info);
    return 0;
}