#include <memory>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <queue>
#include <span>
#include <map>
#include <limits>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

// You are given two 32-bit numbers, N and M, and two bit positions i and j.
// Write a method to insert M into N such that M starts at bit j and ends at bit i.
// You can assume that the bits j through i have enough space to fit all of M.
// For example, if M = 10011, you can assume that there are at least 5 bits
// between j and i.

int Insertion(int M, int N, int i, int j)
{
    unsigned int allOnes = ~0u;
    unsigned int left = allOnes << (j + 1);
    unsigned int right = (1u << i) - 1;
    unsigned int mask = left | right;

    unsigned int clearedN = static_cast<unsigned int>(N) & mask;
    unsigned int shiftedM = static_cast<unsigned int>(M) << i;

    return static_cast<int>(clearedN | shiftedM);
}

// Given a real number between 0 and 1 (e.g. 0.72) that is passed in as double
// print the binary representation. If the number cannot be represent accurately in binary
// with at most 32 characters. Print error

void BinaryToString(double realNumber)
{
    if (realNumber >= 1.0 || realNumber <= 0.0)
        throw std::runtime_error("between 0 and 1");

    std::stringstream binaryNumber;
    binaryNumber << ".";

    double bNumber = realNumber;
    for (int i = 0; i < 32; ++i)
    {
        bNumber = bNumber * 2;
        if (bNumber >= 1.0)
        {
            binaryNumber << '1';
            bNumber = bNumber - 1.0;
        }
        else
        {
            binaryNumber << '0';
        }

        if (bNumber == 0.0)
        {
            std::cout << binaryNumber.str();
            return;
        }
    }

    std::cout << "ERROR";
}
