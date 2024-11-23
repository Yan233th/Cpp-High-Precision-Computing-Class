#include "BigInt.hpp"

BigInt BigInt::operator + (const BigInt& addend)
{
    BigInt temp = *this;
    if (temp.len < addend.len) temp.num.resize (addend.len);
    bool carry = false;
    for (int i = 0; i < addend.len; i++)
    {
        if (carry) temp.num[i] += addend.num[i] + 1;
        else temp.num[i] += addend.num[i];
        if (temp.num[i] > 9)
        {
            carry = true;
            temp.num[i] -= 10;
        }
        else carry = false;
    }
    if (carry)
    {
        if (addend.len >= temp.len) temp.num.push_back (1);
        else
        {
            for (int now = addend.len; now < temp.num.size (); now++)
            {
                temp.num[now] += 1;
                if (temp.num[now] > 9)
                {
                    temp.num.push_back (1);
                    temp.num[now] -= 10;
                }
                else break;
            }
        }
    }
    temp.len = temp.num.size ();
    return temp;
}

BigInt& BigInt::operator += (const BigInt& addend)
{
    if (len < addend.len) num.resize (addend.len);
    bool carry = false;
    for (int i = 0; i < addend.len; i++)
    {
        if (carry) num[i] += addend.num[i] + 1;
        else num[i] += addend.num[i];
        if (num[i] > 9)
        {
            carry = true;
            num[i] -= 10;
        }
        else carry = false;
    }
    if (carry)
    {
        if (addend.len >= len) num.push_back (1);
        else
        {
            for (int now = addend.len; now < num.size (); now++)
            {
                num[now] += 1;
                if (num[now] > 9) num[now] -= 10;
                else break;
            }
            if (carry) num.push_back (1);
        }
    }
    len = num.size ();
    return *this;
}

BigInt BigInt::operator - (const BigInt& subtrahend)
{
    if (is_negative && subtrahend.is_negative) return BigInt {'+', subtrahend.num} - BigInt {'+', num};
    if (!is_negative && subtrahend.is_negative) return *this + subtrahend;
    if (is_negative && !subtrahend.is_negative) return BigInt {'-', BigInt {'+', num} + subtrahend};
    BigInt temp;
    switch (*this | subtrahend)
    {
        case 0:
            break;
        case 1:
        {
            temp = *this;
            temp.is_negative = false;
            bool borrow = false;
            int i = 0;
            while (i < subtrahend.len)
            {
                if (borrow) temp.num[i] -= subtrahend.num[i] + 1;
                else temp.num[i] -= subtrahend.num[i];
                if (temp.num[i] < 0)
                {
                    borrow = true;
                    temp.num[i] += 10;
                }
                else borrow = false;
                i++;
            }
            while (borrow)
            {
                temp.num[i] -= 1;
                if (temp.num[i] < 0)
                {
                    borrow = true;
                    temp.num[i] += 10;
                }
                else borrow = false;
                i++;
            }
            for (int i = temp.len - 1; i >= 0; i--)
            {
                if (temp.num[i]) break;
                temp.num.pop_back ();
            }
            temp.len = temp.num.size ();
            break;
        }
        case 2:
        {
            temp = subtrahend;
            temp.is_negative = true;
            bool borrow = false;
            int i = 0;
            while (i < len)
            {
                if (borrow) temp.num[i] -= num[i] + 1;
                else temp.num[i] -= num[i];
                if (temp.num[i] < 0)
                {
                    borrow = true;
                    temp.num[i] += 10;
                }
                else borrow = false;
                i++;
            }
            while (borrow)
            {
                temp.num[i] -= 1;
                if (temp.num[i] < 0)
                {
                    borrow = true;
                    temp.num[i] += 10;
                }
                else borrow = false;
                i++;
            }
            for (int i = temp.len - 1; i >= 0; i--)
            {
                if (temp.num[i]) break;
                temp.num.pop_back ();
            }
            temp.len = temp.num.size ();
            break;
        }
    }
    return temp;
}

BigInt BigInt::operator * (const BigInt& multiplier)
{
    BigInt temp;
    temp.is_negative = this->is_negative ^ multiplier.is_negative;
    temp.len = this->len + multiplier.len;
    temp.num.resize (temp.len);
    for (int i = 0; i < this->len; i++) for (int j = 0; j < multiplier.len; j++) temp.num[i + j] += this->num[i] * multiplier.num[j];
    for (int i = 0, carry = 0; i < temp.len; i++)
    {
        temp.num[i] += carry;
        carry = temp.num[i] / 10;
        temp.num[i] %= 10;
    }
    for (int i = temp.len - 1; i >= 0; i--)
    {
        if (temp.num[i]) break;
        temp.num.pop_back ();
    }
    temp.len = temp.num.size ();
    return temp;
}

BigInt BigInt::operator / (const BigInt& divide)
{
    // unfinished
    return BigInt {114514};
}
