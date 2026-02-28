#include <string>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <cstddef>

// there are thre types of edits that can be performed on strings
// inser a character, remove a character or replace a character.
// Given two strings, write a function to check if they are one edit(or zero edits)away
bool OneAway(const std::string& left,const std::string& right)
{
    const auto lhsSize{left.size()};
    const auto rhsSize{right.size()};
    const auto diff = rhsSize>lhsSize?(rhsSize-lhsSize):(lhsSize-rhsSize);
    if (diff>1 ) return false;

    bool edited = false;
    
    std::size_t i{};
    std::size_t j{};

    while (i<lhsSize&&j<rhsSize)
    {
        const unsigned char lhsChar = left[i];
        const unsigned char rhsChar = right[j];
        if (lhsChar==rhsChar)
        {
            ++i,++j;
            continue;
        }
            
        if (edited)
            return false;
        edited=true;
        if (lhsSize==rhsSize)
        {
            ++i,++j; //replace case
        }
        else if(lhsSize>rhsSize)
        {
            ++i; // delete from left / insert into right
        }
        else
        {
            ++j;
        }
    }
    return true;
}


bool IsUnique(const std::string& unique)
{
	if (unique.size() > 256)
		return false;

	std::array<bool,256> seen{};
	for (unsigned char c:unique)
	{
		if (seen[c])
			return false;
		seen[c] = true;
	}
	return true;
}

bool CheckPermutation(const std::string&left, const std::string& right)
{
	if (left.size() != right.size()) return false;

	std::array<int,256> cnt{};
	for (unsigned char c:left)
	{
		cnt[c]++;
	}

	for (unsigned char c:right)
	{
		--cnt[c];
		if (cnt[c]<0)
			return false;
	}
	return true;
}

bool CheckPalindromePermutation(const std::string& permutation)
{
	std::array<int,256> cnt{};
	for (unsigned char c:permutation)
	{
		if (std::isspace(c))
			continue;
		c = std::tolower(c);
		cnt[c]++;
	}

	uint8_t oddCnt = 0;
	for (const auto value:cnt)
	{
		if (value & 0x01) // odd count
		{
			if (++oddCnt > 1)
				return false;
		}
	}

	return true;
}  