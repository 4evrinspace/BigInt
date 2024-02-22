#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

//LongNumber is a number, which have 10^17 base digits instead of 10 base
typedef unsigned long long digit_t;
#define DIGIT_LENGTH 9
#define DEFAULT_PRECISION 13ll
//Over digit = maximum digit + 1
#define OVER_DIGIT (digit_t)1000000000

//TODO https://en.cppreference.com/w/cpp/language/user_literal

class LongNumber {
    public:
    ~LongNumber() = default;
    //0 is positive number
    LongNumber();
    LongNumber& operator= (const LongNumber&) = default;

    //Constructors
    LongNumber(const LongNumber&) = default;
    LongNumber(const std::string &string_number,const long long& accuracy = 0);
    LongNumber(const char* string_number, const long long& accuracy = 0);

    LongNumber(const short& int_number, const long long& accuracy = 0);
    LongNumber(const unsigned short& int_number,const long long& accuracy = 0);

    LongNumber(const int& int_number, const long long& accuracy = 0);
    LongNumber(const unsigned int& int_number, const long long& accuracy = 0);

    LongNumber(const long long& int_number, const long long& accuracy = 0);
    LongNumber(const unsigned long long& int_number, const long long& accuracy = 0);

    LongNumber(const double& number, const long long& accuracy = 0);
    //Operators

    //Logic
    friend bool operator==(const LongNumber &left_number, const LongNumber &right_number);
    friend bool operator!=(const LongNumber &left_number, const LongNumber &right_number);
    explicit operator bool() const;
    friend bool operator<(const LongNumber &left_number, const LongNumber &right_number);
    friend bool operator>(const LongNumber &left_number, const LongNumber &right_number);
    friend bool operator<=(const LongNumber &left_number, const LongNumber &right_number);
    friend bool operator>=(const LongNumber &left_number, const LongNumber &right_number);

    //Arithmetic
    friend LongNumber operator+(const LongNumber &left_number, const LongNumber &right_number);
    friend LongNumber operator-(const LongNumber &left_number, const LongNumber &right_number);
    friend LongNumber operator*(const LongNumber &left_number, const LongNumber &right_number);
    friend LongNumber operator/(const LongNumber &left_number, const LongNumber &right_number);

    LongNumber operator-();
    //In case of something very strange
    LongNumber operator+();

    friend std::ostream& operator<<(std::ostream& os, const LongNumber& num);
    //And a bit of assignment and increment/decrement one's 
    LongNumber& operator +=(const LongNumber& right_number);
    LongNumber& operator -=(const LongNumber& right_number);
    LongNumber& operator *=(const LongNumber& right_number);
    LongNumber& operator /=(const LongNumber& right_number);
    //Prefix
    LongNumber& operator ++();
    LongNumber& operator --();
    //Postfix
    LongNumber operator ++(int);
    LongNumber operator --(int);
    
    friend LongNumber abs(LongNumber);
    std::string to_string() const;
    std::string to_string(const long long& precision) const;
    static LongNumber calculate_pi(size_t precision);

    private:
    std::vector<digit_t> _digits;
    friend LongNumber _abs_add(const LongNumber& left_number, const LongNumber& right_number);
    friend LongNumber _abs_sub(const LongNumber& left_number, const LongNumber& right_number);
    bool _is_negative;
    long long _fractional_size;
    static LongNumber mul_on_digit(const LongNumber& left_number, const digit_t& right_number);
    void _clean_right_zeros();
    static digit_t _find_digit_multip(const LongNumber& result, const LongNumber& multiplier);

    bool _is_zero() const; 
};
LongNumber operator ""_Ln(const char* string_num, const size_t len);
LongNumber operator ""_Ln(const unsigned long long number);
LongNumber operator ""_Ln(long double number);