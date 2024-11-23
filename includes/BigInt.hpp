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

    BigInt (const char& _is_negative, const std::vector<int>& _num)
    {
        is_negative = _is_negative == '-' ? true : false;
        num = _num;
        len = num.size ();
    }

    BigInt (const char& _is_negative, const BigInt& bigint)
    {
        is_negative = _is_negative == '-' ? !bigint.is_negative : bigint.is_negative;
        num = bigint.num;
        len = bigint.len;
    }

    const unsigned char operator | (const BigInt& other);
    const bool operator == (const BigInt& other);
    const std::strong_ordering operator <=> (const BigInt& other);

    BigInt operator + (const BigInt& addend);
    BigInt& operator += (const BigInt& addend);

    BigInt operator - (const BigInt& subtrahend);

    BigInt operator * (const BigInt& multiplier);

    BigInt operator / (const BigInt& divide);

    bool output ()
    {
        if (len == 0)
        {
            std::cout << 0 << std::endl;
            return true;
        }
        if (is_negative) std::cout << '-';
        for (int i = len - 1; i >= 0; i--) std::cout << num[i];
        std::cout << std::endl;
        return true;
    }
};

inline std::istream& operator >> (std::istream& in, BigInt& bigint)
{
    bigint.num.clear ();
    bool in_progress = false; // 是否进入读取数字状态
    char ch;
    while (in.get (ch)) // 一个一个一个向后读，不会停止
    {
        if (!in_progress && std::isspace (ch)) continue; // 未读到数字
        if (!in_progress && ch == '-')
        {
            in_progress = true;
            bigint.is_negative = true;
            continue;
        }
        if (std::isdigit (ch)) // 读数字
        {
            in_progress = true;
            bigint.num.push_back (ch - '0');
        }
        else // 数字结束
        {
            in.unget (); // 将此字符放回缓冲区
            bigint.len = bigint.num.size ();
            std::reverse (bigint.num.begin (), bigint.num.end ()); // 倒转乾坤
            break;
        }
    }
    return in;
}

inline std::ostream& operator << (std::ostream& out, const BigInt& bigint)
{
    if (bigint.len == 0)
    {
        std::cout << 0 << std::endl;
        return out;
    }
    if (bigint.is_negative) std::cout << '-';
    for (int i = bigint.len - 1; i >= 0; i--) std::cout << bigint.num[i];
    return out;
}
