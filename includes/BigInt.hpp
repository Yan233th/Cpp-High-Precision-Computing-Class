#include <iostream>
#include <vector>

class BigInt
{
    public:

    int len;
    bool is_negative;
    std::vector<int> num;

    BigInt ();
    BigInt (int value);
    BigInt (std::string str);

    const unsigned char operator | (const BigInt& other) const;
    const bool operator == (const BigInt& other) const;
    const std::strong_ordering operator <=> (const BigInt& other) const;

    const BigInt operator + (const BigInt& addend) const;
    BigInt& operator += (const BigInt& addend);

    const BigInt operator - (const BigInt& subtrahend) const;
    BigInt& operator -= (const BigInt& subtrahend);

    const BigInt operator * (const int& multiplier) const;
    const BigInt operator * (const BigInt& multiplier) const;
    BigInt& operator *= (const BigInt& multiplier);

    const BigInt operator / (const BigInt& divisor) const;
    BigInt& operator /= (const BigInt& divisor);

    friend std::istream& operator >> (std::istream& in, BigInt& bigint);
    friend std::ostream& operator << (std::ostream& out, const BigInt& bigint);
    inline void output () const { std::cout << *this << std::endl; }
};


