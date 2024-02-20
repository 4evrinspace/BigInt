#pragma once


#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
//LongNumber is a number, which have 10^17 base digits instead of 10 base
typedef unsigned long long digit_t;
#define DIGIT_LENGTH 9
//Over digit = maximum digit + 1
#define OVER_DIGIT (digit_t)1000000000
//TODO https://en.cppreference.com/w/cpp/language/user_literal

class LongNumber {
    public:
    ~LongNumber() = default;
    //0 is positive number
    LongNumber() : _is_negative(false), _digits({}), _fractional_size(0) {}
    LongNumber& operator= (const LongNumber&) = default;
    //Constructors
    LongNumber(const LongNumber&) = default;
    LongNumber(const std::string &string_number,const size_t& accuracy = 0);
    LongNumber(const char* string_number, const size_t& accuracy = 0) 
    : LongNumber(std::string(string_number, accuracy)) {}

    LongNumber(const short& int_number, const size_t& accuracy = 0) 
    : LongNumber(static_cast<long long> (int_number, accuracy)) {}
    LongNumber(const unsigned short& int_number,const size_t& accuracy = 0) 
    : LongNumber(static_cast<unsigned long long> (int_number, accuracy)) {}

    LongNumber(const int& int_number, const size_t& accuracy = 0) 
    : LongNumber(static_cast<long long> (int_number, accuracy)) {}
    LongNumber(const unsigned int& int_number, const size_t& accuracy = 0) 
    : LongNumber(static_cast<unsigned long long> (int_number, accuracy)) {}

    LongNumber(const long& int_number, const size_t& accuracy = 0) 
    : LongNumber(static_cast<long long> (int_number, accuracy)) {}
    LongNumber(const unsigned long& int_number, const size_t& accuracy = 0) 
    : LongNumber(static_cast<unsigned long long> (int_number, accuracy)) {}

    LongNumber(const long long& int_number, const size_t& accuracy = 0);
    LongNumber(const unsigned long long& int_number, const size_t& accuracy = 0);

    //Operators

    //Logic
    friend bool operator==(const LongNumber &left_number, const LongNumber &right_number);
    friend bool operator!=(const LongNumber &left_number, const LongNumber &right_number);

    friend bool operator<(const LongNumber &left_number, const LongNumber &right_number);
    friend bool operator>(const LongNumber &left_number, const LongNumber &right_number);
    friend bool operator<=(const LongNumber &left_number, const LongNumber &right_number);
    friend bool operator>=(const LongNumber &left_number, const LongNumber &right_number);

    //Arithmetic
    friend LongNumber operator+(const LongNumber &left_number, const LongNumber &right_number);
    friend LongNumber operator-(const LongNumber &left_number, const LongNumber &right_number);
    friend LongNumber operator*(const LongNumber &left_number, const LongNumber &right_number);
    friend LongNumber operator*(const LongNumber &left_number, const digit_t &right_number);
    friend LongNumber operator/(const LongNumber &left_number, const LongNumber &right_number);
    friend LongNumber operator%(const LongNumber &left_number, const LongNumber &right_number);
    LongNumber operator-();
    //In case of something very strange
    LongNumber operator+();

    //And a bit of assignment and increment/decrement one's 
    LongNumber& operator +=(const LongNumber& right_number);
    LongNumber& operator -=(const LongNumber& right_number);
    //Prefix
    LongNumber& operator ++();
    LongNumber& operator --();
    //Postfix
    LongNumber& operator ++(int);
    LongNumber& operator --(int);
    
    friend LongNumber abs(LongNumber);
    private:
    std::vector<digit_t> _digits;
    bool _is_negative;
    size_t _fractional_size;
    void _shift_point_position(const size_t& new_accuracy) const;
    void _clean_right_zeros();
    static digit_t _find_digit_multip(const LongNumber& result, const LongNumber& multiplier);
    bool _is_zero() const; 
};
