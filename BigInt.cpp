// Brian Nam U08673167
// nam.bbrian@gmail.com
// CSE - 40478 C/C++ Programming IV
// project 1
// BigInt.cpp

#include "BigInt.h"
#include <algorithm>
#include <stdexcept>
using namespace std;

namespace Project1 
{

    BigInt::BigInt() : negative(false) 
    {
        digits.push_back(0);
    }

    BigInt::BigInt(const BigInt &a) : digits(a.digits), negative(a.negative) 
    {

    }

    BigInt::BigInt(long long a) 
    {
        negative = a < 0;
        a = abs(a);
        do 
        {
            digits.push_back(a % 10);
            a /= 10;
        } 
        while (a > 0);
    }

    BigInt::BigInt(const string &a) 
    {
        fromString(a);
    }

    const BigInt 
    &BigInt::operator=(const BigInt &other) 
    {
        if (this != &other) 
        {
            digits = other.digits;
            negative = other.negative;
        }
        return *this;
    }

    const BigInt 
    &BigInt::operator+=(const BigInt &other) 
    {
        if (negative == other.negative) 
        {
            addAbsolute(other);
        }
        else 
        {
            if (compareAbsolute(*this, other) >= 0) 
            {
                subtractAbsolute(other);
            }
            else 
            {
                BigInt temp = other;
                temp.subtractAbsolute(*this);
                *this = temp;
                negative = other.negative;
            }
        }
        return *this;
    }

    const BigInt 
    &BigInt::operator-=(const BigInt &other) 
    {
        BigInt temp = other;
        temp.negative = !other.negative;
        return *this += temp;
    }

    void BigInt::fromString(const string &s) 
    {
        if (s.empty() || s == "-" || s == "+") 
        {
            throw invalid_argument("Invalid string format");
        }

        size_t start = 0;
        negative = false;
        if (s[start] == '-') 
        {
            negative = true;
            ++start;
        }
        else if (s[start] == '+') 
        {
            ++start;
        }

        // Additional check for strings that are not valid numbers
        if (start >= s.length()) 
        {
            throw invalid_argument("Invalid string format");
        }

        // Check for "00"
        if (start >= s.length() || s.find_first_not_of("0", start) == string::npos) 
        {
            // For the case "00" unit test 147
            if (s.length() - start > 1) 
            { // More than one zero
                throw invalid_argument("Invalid string format: multiple leading zeros");
            }
            digits = {0};
            negative = false;
            return;
        }

        digits.clear();
        for (size_t i = s.length(); i-- > start;) 
        {
            if (!isdigit(s[i])) 
            {
                throw invalid_argument("Invalid character in string");
            }
            digits.push_back(s[i] - '0');
        }

        trim();
    }

    void BigInt::trim() 
    {
        while (digits.size() > 1 && digits.back() == 0) 
        {
            digits.pop_back();
        }
        if (digits.size() == 1 && digits[0] == 0) negative = false;
    }

    int BigInt::compareAbsolute(const BigInt &op1, const BigInt &op2) 
    {
        if (op1.digits.size() != op2.digits.size()) 
        {
            return op1.digits.size() > op2.digits.size() ? 1 : -1;
        }
        for (size_t i = op1.digits.size(); i-- > 0;) 
        {
            if (op1.digits[i] != op2.digits[i]) 
            {
                return op1.digits[i] > op2.digits[i] ? 1 : -1;
            }
        }
        return 0;
    }

    void BigInt::addAbsolute(const BigInt &other) 
    {
        int carry = 0;
        size_t n = max(digits.size(), other.digits.size()), i;
        for (i = 0; i < n || carry; ++i) 
        {
            if (i == digits.size()) 
            {
                digits.push_back(0);
            }
            digits[i] += carry + (i < other.digits.size() ? other.digits[i] : 0);
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
    }

    void BigInt::subtractAbsolute(const BigInt &other) 
    {
        int borrow = 0;
        for (size_t i = 0; i < other.digits.size() || borrow; ++i)
        {
            digits[i] -= (i < other.digits.size() ? other.digits[i] : 0) + borrow;
            borrow = digits[i] < 0;
            if (borrow) digits[i] += 10;
        }
        trim();
    }

    const BigInt 
    operator+(const BigInt &op1, const BigInt &op2) 
    {
        BigInt result = op1;
        result += op2;
        return result;
    }

    const BigInt 
    operator-(const BigInt &op1, const BigInt &op2) 
    {
        BigInt result = op1;
        result -= op2;
        return result;
    }

    bool 
    operator==(const BigInt &op1, const BigInt &op2) 
    {
        return op1.negative == op2.negative && op1.digits == op2.digits;
    }

    bool 
    operator!=(const BigInt &op1, const BigInt &op2)
    {
        return !(op1 == op2);
    }

    bool 
    operator<(const BigInt &op1, const BigInt &op2) 
    {
        if (op1.negative != op2.negative)
        {
            return op1.negative;
        }
        if (op1.negative)
        {
            return BigInt::compareAbsolute(op2, op1) < 0;
        }
        return BigInt::compareAbsolute(op1, op2) < 0;
    }

    bool 
    operator<=(const BigInt &op1, const BigInt &op2) 
    {
        return (op1 == op2) || (op1 < op2);
    }

    bool 
    operator>(const BigInt &op1, const BigInt &op2) 
    {
        return !(op1 <= op2);
    }

    bool 
    operator>=(const BigInt &op1, const BigInt &op2) 
    {
        return !(op1 < op2);
    }

    ostream 
    &operator<<(ostream &out, const BigInt &value) 
    {
        if (value.negative) out << '-';
        for (auto it = value.digits.rbegin(); it != value.digits.rend(); ++it) 
        {
            out << *it;
        }
        return out;
    }

    istream 
    &operator>>(istream &in, BigInt &value) 
    {
        string s;
        in >> s;
        value.fromString(s);
        return in;
    }
}
