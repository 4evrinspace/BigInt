#include <LongNumber.h>



// TODO: Check code, make it less complicated, add comments 
LongNumber::LongNumber(const std::string &string_number, const size_t& accuracy){
    const size_t chunk_accuracy = (accuracy + DIGIT_LENGTH - 1) / DIGIT_LENGTH;
    *this = LongNumber();
    if (string_number == "") {
        for (int i = 0; i < chunk_accuracy + 1; i++) {
            _digits.push_back(0);
        }
        _fractional_size = chunk_accuracy;
        return;
    }
    long long start_pos = 0;
    size_t dot_position = string_number.find('.');
    if (string_number[0] == '-' || string_number[0] == '+') {
        start_pos = 1;
        _is_negative = (string_number[0] == '-');
    }
    if (dot_position == std::string::npos) {
        dot_position = string_number.length();
    } 
    const size_t string_len = string_number.length();
    _fractional_size = std::max(chunk_accuracy, (string_len - dot_position - 1 + DIGIT_LENGTH - 1) / DIGIT_LENGTH);
    const size_t back_zeros = (dot_position == string_len ? 0 : (_fractional_size * DIGIT_LENGTH - (string_len - dot_position - 1)));
    digit_t current_number = 0;
    digit_t current_10_pow = 1;
    size_t current_size = 0;
    for (long long i = dot_position - 1; i >= start_pos; i--) {
        current_number += current_10_pow * (string_number[i] - '0');
        current_10_pow *= 10;
        current_size++;
        if (current_size == DIGIT_LENGTH) {
            _digits.push_back(current_number);
            current_size = 0;
            current_10_pow = 1;
            current_number = 0;
        } 
    }
    
    if (current_number != 0) {
        _digits.push_back(current_number);
    }
    current_size = 0;
    current_number = 0;
    std::reverse(_digits.begin(), _digits.end());
    for (size_t i = dot_position + 1; i < string_len; i++) {
        current_number *= 10;
        current_number += string_number[i] - '0';
        current_size++;
        if (current_size == DIGIT_LENGTH) {
            _digits.push_back(current_number);
            current_size = 0;
            current_number = 0;
        } 
    }
    for (size_t i = 0; i < back_zeros % DIGIT_LENGTH; i++) {
        current_number *= 10;
    }
    _digits.push_back(current_number);
    for (size_t i = 0; i < back_zeros / DIGIT_LENGTH; i++) {
        _digits.push_back(0);
    } 
    if (this->_is_zero()) {
        _is_negative = false;
    }
}

bool LongNumber::_is_zero() const {
    for (digit_t i : _digits) {
        if (i != 0) {
            return false;
        }
    }
    return true;
}
LongNumber abs(LongNumber num) {
    num._is_negative = false;
    return num;
}

LongNumber operator+(const LongNumber& left_number, const LongNumber& right_number) {
    if (right_number._is_negative != left_number._is_negative) {
        if (right_number._is_negative) {
            return left_number - abs(right_number);
        } else {
            return right_number - abs(left_number);
        }
    }
    size_t next = 0;
    LongNumber ans;
    int left_index = left_number._digits.size() - 1;
    int right_index = right_number._digits.size() - 1;
    if (left_number._fractional_size != right_number._fractional_size) {
        while (left_number._fractional_size - (left_number._digits.size() - left_index - 1) < right_number._fractional_size - (right_number._digits.size() - right_index - 1)) {
            ans._digits.push_back(right_number._digits[right_index]);
            right_index--;
        }
        while (left_number._fractional_size - (left_number._digits.size() - left_index - 1) > right_number._fractional_size - (right_number._digits.size() - right_index - 1)) {
            ans._digits.push_back(left_number._digits[left_index]);
            left_index--;
        }
    }

    while (left_index >= 0 && right_index >= 0) {
        ans._digits.push_back((left_number._digits[left_index] + right_number._digits[right_index] + next) % OVER_DIGIT);
        next = (left_number._digits[left_index] + right_number._digits[right_index] + next) / OVER_DIGIT;
        left_index--;
        right_index--;
    }
    while (left_index >= 0) {
        ans._digits.push_back(left_number._digits[left_index]);
        left_index--;
    }
    while (right_index >= 0) {
        ans._digits.push_back(right_number._digits[right_index]);
        right_index--;
    }
    std::reverse(ans._digits.begin(), ans._digits.end());
    ans._is_negative = left_number._is_negative;
    if (ans._is_zero()) {
        ans._is_negative = false;
    }
    ans._fractional_size = std::max(left_number._fractional_size, right_number._fractional_size);
    return ans;
}

LongNumber operator-(const LongNumber& left_number, const LongNumber& right_number) {
    if (right_number._is_negative != left_number._is_negative) {
        if (right_number._is_negative) {
            return left_number + abs(right_number);
        } else {
            return right_number + abs(left_number);
        }
    }
    if (abs(right_number) >= abs(left_number)) {
        LongNumber ans = right_number - left_number;
        ans._is_negative ^= true;
        return ans;
    }
    digit_t next = 0;
    LongNumber ans;
    int left_index = left_number._digits.size() - 1;
    int right_index = right_number._digits.size() - 1;
    if (left_number._fractional_size != right_number._fractional_size) {
        while (left_number._fractional_size - (left_number._digits.size() - left_index - 1) < right_number._fractional_size - (right_number._digits.size() - right_index - 1)) {
            ans._digits.push_back(right_number._digits[right_index]);
            right_index--;
        }
        while (left_number._fractional_size - (left_number._digits.size() - left_index - 1) > right_number._fractional_size - (right_number._digits.size() - right_index - 1)) {
            ans._digits.push_back(left_number._digits[left_index]);
            left_index--;
        }
    }

    while (left_index >= 0 && right_index >= 0) {
        if (left_number._digits[left_index] < right_number._digits[right_index] + next) {
            ans._digits.push_back((left_number._digits[left_index]  + OVER_DIGIT - next - right_number._digits[right_index]) % OVER_DIGIT);
            next = 1;
        } else {
            ans._digits.push_back((left_number._digits[left_index]- next - right_number._digits[right_index]) % OVER_DIGIT);
        }
        ans._digits.push_back((left_number._digits[left_index] + right_number._digits[right_index] - next) % OVER_DIGIT);
        left_index--;
        right_index--;
    }
    while (left_index >= 0) {
        if (left_number._digits[left_index] < next) {
            ans._digits.push_back((left_number._digits[left_index]  + OVER_DIGIT - next) % OVER_DIGIT);
            next = 1;
        } else {
            ans._digits.push_back((left_number._digits[left_index] - next) % OVER_DIGIT);
        }
    }
    size_t integer_part = ans._digits.size() - ans._fractional_size;
    while (integer_part != 1 && ans._digits.back() == 0) {
        ans._digits.pop_back();
    }
    std::reverse(ans._digits.begin(), ans._digits.end());
    ans._is_negative = left_number._is_negative;
    ans._fractional_size = std::max(left_number._fractional_size, right_number._fractional_size);
    if (ans._is_zero()) {
        ans._is_negative = false;
    }
    return ans;
}

bool operator<(const LongNumber& left_number, const LongNumber& right_number) {
    if (left_number._is_negative != right_number._is_negative) {
        return left_number._is_negative;
    }
    bool flag = left_number._is_negative;
    size_t left_number_integer = left_number._digits.size() - left_number._fractional_size;
    size_t right_number_integer = right_number._digits.size() - right_number._fractional_size;
    if (left_number_integer != right_number_integer) {
        return (left_number_integer < right_number_integer) ^ flag;  
    }
    for (int i = 0; i < std::min(left_number._digits.size(), right_number._digits.size()) ; i++) {
        if (left_number._digits[i] != right_number._digits[i]) {
            return (left_number._digits[i] < right_number._digits[i]) ^ flag;
        }
    }
    return (left_number._digits.size() < right_number._digits.size()) ^ flag;
}

bool operator==(const LongNumber& left_number, const LongNumber& right_number) {
    if (left_number._is_negative != right_number._is_negative || 
        left_number._digits.size() != right_number._digits.size() ||
        left_number._fractional_size != right_number._fractional_size) {
        return false;
    }
    for (int i = 0; i < left_number._digits.size(); i++) {
        if (left_number._digits[i] != right_number._digits[i]) {
            return false;
        }
    }
    return true;
}

void LongNumber::_clean_right_zeros() {
    while (_fractional_size != 0 && _digits.back() == 0) {
        _digits.pop_back();
        _fractional_size--;
    }
    if (_fractional_size != 0) {
        while (_digits.back() % 10 == 0) {
            _digits.back() /= 10;
        }
    }
}
bool operator>=(const LongNumber &left_number, const LongNumber &right_number) {
    return !(left_number < right_number);
}



LongNumber operator*(const LongNumber &left_number, const digit_t &right_number) {
    if (right_number == 0) {
        return LongNumber('0');
    }
    digit_t next = 0;
    LongNumber ans;
    for (int i =  left_number._digits.size() - 1; i >= 0; i--) {
        ans._digits.push_back((left_number._digits[i] * right_number + next) % OVER_DIGIT);
        next = (left_number._digits[i] * right_number + next) / OVER_DIGIT;
    }
    while (next != 0) {
        ans._digits.push_back(next % OVER_DIGIT);
        next = next / OVER_DIGIT;
    }
    std::reverse(ans._digits.begin(), ans._digits.end());
    return ans;
}

LongNumber operator*(const LongNumber &left_number, const LongNumber &right_number) {
    digit_t next = 0;
    LongNumber ans("", left_number._fractional_size + right_number._fractional_size), power_of_10("1");
    for (int i =  right_number._digits.size() - 1; i >= 0; i--) {
        ans += left_number * right_number._digits[i] * power_of_10;
        power_of_10 *= OVER_DIGIT;
    }
    ans._clean_right_zeros();
    return ans;
}

LongNumber operator/(const LongNumber &left_number, const LongNumber &right_number) {
    if (right_number._is_zero()) {
        return LongNumber("-0");
    }
    LongNumber temp("0");
    int index = 0;
    while (index < left_number._digits.size() && temp * 10 + left_number._digits[index] < right_number) {
        temp *= 10;
        temp += left_number._digits[index];
        index++;
    }
    const size_t precision = std::max(left_number._fractional_size, right_number._fractional_size);
    const size_t integer_part = left_number._digits.size() - left_number._fractional_size;
    LongNumber ans("0");
    while (index < integer_part) {
        temp *= 10;
        temp += left_number._digits[index];
        ans._digits.push_back(_find_digit_multip(temp, right_number));
        temp -= ans._digits.back() * right_number;
        index++;
    }
    const size_t left_len = left_number._digits.size();
    while (index < left_len) {
        temp *= 10;
        temp += left_number._digits[index];
        ans._digits.push_back(_find_digit_multip(temp, right_number));
        temp -= ans._digits.back() * right_number;
        index++;
        ans._fractional_size++;
    }
    while (ans._fractional_size != precision) {
        temp *= 10;
        ans._digits.push_back(_find_digit_multip(temp, right_number));
        temp -= ans._digits.back() * right_number;
        index++;
        ans._fractional_size++;
    }
    ans._clean_right_zeros();
    return ans;
}

digit_t _find_digit_multip(const LongNumber& result, const LongNumber& multiplier) {
    if (result < multiplier) {
        return 0;
    }
    digit_t lhs = 0, rhs = OVER_DIGIT;
    while (rhs - lhs > 1) {
        digit_t mid = lhs + (rhs - lhs) / 2;
        if (result <= mid * multiplier) {
            rhs = mid;
        } else {
            lhs = mid;
        }
    }
    return lhs;
}