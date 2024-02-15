// Brian Nam U08673167
// nam.bbrian@gmail.com
// CSE - 40478 C/C++ Programming IV
// project 1
// BigInt.h

#ifndef BIGINT_H
#define BIGINT_H

#include <cstdlib>
using std::abs;

#include<iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::istream;
using std::ostream;

#include<string>
using std::string;
#include<vector>
using std::vector;

namespace Project1
{
    class BigInt
    {
        friend const BigInt operator+(const BigInt &op1, const BigInt &op2);
        friend const BigInt operator-(const BigInt &op1, const BigInt &op2);
        friend bool operator==(const BigInt &op1, const BigInt &op2);
        friend bool operator!=(const BigInt &op1, const BigInt &op2);
        friend bool operator<(const BigInt &op1, const BigInt &op2);
        friend bool operator<=(const BigInt &op1, const BigInt &op2);
        friend bool operator>(const BigInt &op1, const BigInt &op2);
        friend bool operator>=(const BigInt &op1, const BigInt &op2);
        friend ostream &operator<<(ostream &out, const BigInt &value);
        friend istream &operator>>(istream &out, BigInt &value);
    public:
        BigInt();
        BigInt(const BigInt &a);
        BigInt(long long a);
        // Throws invalid_argument if string malformed (contains
        // anything other than a legally formatted number)
        BigInt(const string &a);
        const BigInt &operator=(const BigInt &other);
        const BigInt &operator+=(const BigInt &other);
        const BigInt &operator-=(const BigInt &other);
    private:
        vector<int> digits;
        bool negative = false;
        void fromString(const string &s);
        void trim();
        static int compareAbsolute(const BigInt &op1, const BigInt &op2);
        void addAbsolute(const BigInt &other);
        void subtractAbsolute(const BigInt &other);
    };
}

#endif
