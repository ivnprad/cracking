#include <string>
#include <array>

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