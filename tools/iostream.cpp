#include "BigInt.hpp"

std::istream& operator >> (std::istream& in, BigInt& bigint)
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

std::ostream& operator << (std::ostream& out, const BigInt& bigint)
{
    if (bigint.len == 0)
    {
        std::cout << 0;
        return out;
    }
    if (bigint.is_negative) std::cout << '-';
    for (int i = bigint.len - 1; i >= 0; i--) std::cout << bigint.num[i];
    return out;
}
