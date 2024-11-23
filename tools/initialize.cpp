#include "BigInt.hpp"

BigInt::BigInt ()
{
    len = 0;
    is_negative = false;
    num.clear ();
}

BigInt::BigInt (int value)
{
    if (value < 0) is_negative = true, value *= -1;
    else is_negative = false;
    while (value > 0)
    {
        num.push_back (value % 10);
        value /= 10;
    }
    len = num.size ();
}

BigInt::BigInt (std::string str)
{
    num.clear ();
    len = 0;
    // unfinished
}