#include "BigInt.hpp"

const unsigned char BigInt::operator | (const BigInt& other) const
{
    if (len == other.len)
    {
        for (int i = len - 1; i >= 0; i--)
        {
            if (num[i] == other.num[i]) continue;
            if (num[i] > other.num[i]) return 1;
            else return 2;
        }
        return 0;
    }
    else if (len > other.len) return 1;
    else return 2;
}

const bool BigInt::operator == (const BigInt& other) const
{
    if (len == other.len)
    {
        for (int i = len - 1; i >= 0; i--) if (num[i] != other.num[i]) return false;
        return true;
    }
    else return false;
}

const std::strong_ordering BigInt::operator <=> (const BigInt& other) const
{
    if (len == other.len)
    {
        for (int i = len - 1; i >= 0; i--)
        {
            if (num[i] == other.num[i]) continue;
            if (num[i] > other.num[i]) return std::strong_ordering::greater;
            else return std::strong_ordering::less;
        }
        return std::strong_ordering::equal;
    }
    else if (len > other.len) return std::strong_ordering::greater;
    else return std::strong_ordering::less;
}