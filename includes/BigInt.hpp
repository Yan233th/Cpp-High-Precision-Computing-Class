# ifndef BIGINT_HPP
# define BIGINT_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class BigInt {
    public:
        int len;
        bool is_negative;
        std::vector<int> num;

        BigInt ()
        {
            len = 0;
            is_negative = false;
            num.clear ();
        }
        BigInt (int value)
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

        // BigInt (std::string str)
        // {
        //     num.clear ();
        //     len = 0;
        // }

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

        BigInt operator + (const BigInt &addend)
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
                            temp.num.push_back(1);
                            temp.num[now] -= 10;
                        }
                        else break;
                    }
                }
            }
            temp.len = temp.num.size ();
            return temp;
        }

        BigInt &operator += (const BigInt &addend)
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

        BigInt operator - (const BigInt &subtrahend)
        {
            if (is_negative && subtrahend.is_negative) return BigInt {'+', subtrahend.num} - BigInt {'+', num};
            if (!is_negative && subtrahend.is_negative) return *this + subtrahend;
            if (is_negative && !subtrahend.is_negative) return BigInt {'-', BigInt {'+', num} + subtrahend};
            bool equal = true;
            bool is_this_bigger = false;
            if (len == subtrahend.len) for (int i = len - 1; i >= 0; i--)
            {
                if (num[i] == subtrahend.num[i]) continue;
                if (num[i] > subtrahend.num[i]) is_this_bigger = true, equal = false;
                else is_this_bigger = false, equal = false;
                break;
            }
            else if (len > subtrahend.len) is_this_bigger = true, equal = false;
            else is_this_bigger = false, equal = false;
            if (equal) return BigInt {0};
            BigInt temp;
            if (is_this_bigger)
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
                for (int i = temp.len - 1; i >= 0; i--) // 去除头部0
                {
                    if (temp.num[i]) break; // 达到有效数字退出
                    temp.num.pop_back ();
                }
                temp.len = temp.num.size ();
            }
            else
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
                for (int i = temp.len - 1; i >= 0; i--) // 去除头部0
                {
                    if (temp.num[i]) break; // 达到有效数字退出
                    temp.num.pop_back ();
                }
                temp.len = temp.num.size ();
            }
            return temp;
        }

        BigInt operator * (const BigInt &multiplier)
        {
            BigInt temp;
            temp.is_negative = this->is_negative ^ multiplier.is_negative;
            temp.len = this->len + multiplier.len;
            temp.num.resize (temp.len);
            for (int i = 0; i < this->len; i++) for (int j = 0; j < multiplier.len; j++) temp.num[i+j] += this->num[i] * multiplier.num[j];
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

        // BigInt operator * (const BigInt &multiplier)
        // {
        //     BigInt temp = *this;
        //     BigInt finaltemp;
        //     temp.num.resize (temp.len + multiplier.len);
        //     // int arr[temp.len];
        //     vector<int> arr (temp.len);
        //     for (int i = 0; i < multiplier.len; i++)
        //     {
        //         for (int j = 0; j < temp.len; j++)
        //         {
        //             temp.num[j+i] = multiplier.num[i] * num[j];
        //             if (temp.num[j+i] > 9)
        //             {
        //                 temp.num[j+i] = temp.num[j+i] - temp.num[j+i]/10*10;
        //                 temp.num[j+1+i] = temp.num[j+1+i] + (temp.num[j+i]/10);
        //             }
        //             for (int i = 0; i < temp.len; i++)
        //             {
        //                 finaltemp.num[i] = arr[i] + temp.num[i];
        //                 if (finaltemp.num[i] > 9)
        //                 {
        //                     finaltemp.num[i+1] += 1;
        //                     finaltemp.num[i] -= 10;
        //                 }
        //                 temp.num[i] = 0;
        //             }
        //         }
        //     }
        //     for (int i = finaltemp.len - 1; i >= 0; i--) // 去除头部0
        //         {
        //             if (finaltemp.num[i]) break; // 达到有效数字退出
        //             finaltemp.num.pop_back ();
        //         }
        //     return finaltemp;
        // }

        // BigInt operator / (const BigInt &divide)
        // {
        // }

        bool output ()
        {
            if (len == 0)
            {
                std::cout << 0 << std::endl;
                return true;
            }
            if (is_negative) std::cout << '-';
            for (int i = len-1; i >= 0; i--) std::cout << num[i];
            std::cout << std::endl;
            return true;
        }
};

std::istream &operator >> (std::istream &in, BigInt &bigint) // 重载cin>>运算符
{
    bigint.num.clear ();
    bool in_progress = false; // 是否在读取数字的状态
    char ch; // 临时字符变量
    while (in.get (ch))// 一个一个一个向后读，不会停止
    {
        if (!in_progress && std::isspace (ch)) // 未读到数字
        {
            continue;
        }
        if (!in_progress && ch == '-')
        {
            in_progress = true;
            bigint.is_negative = true;
            continue;
        }
        if (std::isdigit (ch)) // 读到数字
        {
            in_progress = true;
            bigint.num.push_back (ch - '0');
        }
        else // 数字结束
        {
            in.unget ();
            bigint.len = bigint.num.size ();
            std::reverse (bigint.num.begin (), bigint.num.end ());//到转乾坤
            break;
        }
    }
    return in;
}

std::ostream &operator << (std::ostream &out, const BigInt &bigint)
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

#endif