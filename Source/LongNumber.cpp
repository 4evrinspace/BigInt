#include <LongNumber.h>

LongNumber::LongNumber()  : _is_negative(false), _digits({}), _fractional_size(0) {}


// LongNumber store AT LEAST accuracy digits after decimal point
LongNumber::LongNumber(const std::string &string_number, const long long& accuracy) {
    // How many digits we need after decimal point to store this number
    const long long chunk_accuracy = (accuracy + DIGIT_LENGTH - 1) / DIGIT_LENGTH;
    *this = LongNumber();
    // "" - empty number with correct number of fractional digits
    if (string_number == "") {
        for (int i = 0; i < chunk_accuracy + 1; i++) {
            _digits.push_back(0);
        }
        _fractional_size = chunk_accuracy;
        return;
    }
    long long start_pos = 0;
    long long dot_position = string_number.find('.');
    //Checking the sign in the begining
    if (string_number[0] == '-' || string_number[0] == '+') {
        start_pos = 1;
        _is_negative = (string_number[0] == '-');
    }
    long long string_len = string_number.length();
    //If string is integer lets pretend that dot is right before the end ("123" == "123.")
    if (dot_position == std::string::npos) {
        string_len++;
        dot_position = string_len - 1;
    }
    //Size of fractional part is max(digits we need for accuracy digits after point, digits we have after point)
    _fractional_size = std::max(chunk_accuracy, (string_len - dot_position - 1 + DIGIT_LENGTH - 1) / DIGIT_LENGTH);
    //In case we need to store more digits than we have we need right leading zeros
    const long long back_zeros = (_fractional_size * DIGIT_LENGTH - (string_len - dot_position - 1));
    //Correct algorithm only if we divide on chunks from the end of integer part 
    digit_t current_number = 0;
    digit_t current_10_pow = 1;
    long long current_size = 0;
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
    if (current_number != 0 || _digits.size() == 0) {
        _digits.push_back(current_number);
    }
    //Cleaning leading zeros
    while (_digits.size() != 1 && _digits.back() == 0) {
        _digits.pop_back();
    }
    //Correcting order
    std::reverse(_digits.begin(), _digits.end());
    //Filling with fractional digits
    if (_fractional_size != 0) {
        if (dot_position + 1 == string_len) {
            for (long long i = 0; i < _fractional_size; i++) {
                _digits.push_back(0);
            }
            if (this->_is_zero()) {
                _is_negative = false;
            }
            return;
        }
        long long filled = 0;
        current_size = 0;
        current_number = 0;
        for (long long i = dot_position + 1; i < string_len; i++) {
            current_number *= 10;
            current_number += string_number[i] - '0';
            current_size++;
            if (current_size == DIGIT_LENGTH) {
                _digits.push_back(current_number);
                current_size = 0;
                current_number = 0;
            } 
        }
        //Filing the last digit with zeros
        //No overflow : string_len == len_last_digit(DIGIT_LENGTH), back_zeros == -len_last_digit(DIGIT_LENGTH) 
        for (long long i = 0; i < back_zeros % DIGIT_LENGTH; i++) {
            current_number *= 10;
        }
        if (current_number != 0 || back_zeros >= DIGIT_LENGTH){
            _digits.push_back(current_number);
        }
        for (long long i = 0; i < back_zeros / DIGIT_LENGTH; i++) {
            _digits.push_back(0);
        }
    }
    //Beause zero is always positive
    if (this->_is_zero()) {
        _is_negative = false;
    }
}


LongNumber::LongNumber(const char* string_number, const long long& accuracy) {
    std::string casted = string_number;
    (*this) = LongNumber(casted, accuracy);
}


LongNumber::LongNumber(const short& int_number, const long long& accuracy) : LongNumber(std::to_string(int_number), accuracy) {}
LongNumber::LongNumber(const unsigned short& int_number, const long long& accuracy) : LongNumber(std::to_string(int_number), accuracy) {}


LongNumber::LongNumber(const int& int_number, const long long& accuracy) : LongNumber(std::to_string(int_number), accuracy) {}
LongNumber::LongNumber(const unsigned int& int_number, const long long& accuracy) : LongNumber(std::to_string(int_number), accuracy) {}


LongNumber::LongNumber(const long long& int_number, const long long& accuracy) : LongNumber(std::to_string(int_number), accuracy) {}
LongNumber::LongNumber(const unsigned long long& int_number, const long long& accuracy) : LongNumber(std::to_string(int_number), accuracy) {}


LongNumber::LongNumber(const double& int_number, const long long& accuracy) : LongNumber(std::to_string(int_number), accuracy) {}


bool operator<(const LongNumber& left_number, const LongNumber& right_number) {
    
    if (left_number._is_zero() && !(right_number._is_zero())) {
        return !(right_number._is_negative);
    }
    if (!(left_number._is_zero()) && right_number._is_zero()) {
        return left_number._is_negative;
    }
    if (left_number._is_zero() && right_number._is_zero()) {
        return false;
    }
    if (left_number._is_negative != left_number._is_negative) {
        return left_number._is_negative;
    }
    //In negative comparing is opposite
    bool comparing_negative = left_number._is_negative;
    long long left_begin = 0;
    long long right_begin = 0;

    for (; left_number._digits[left_begin] == 0; left_begin++);
    for (; right_number._digits[right_begin] == 0; right_begin++);

    //Len of integer parts
    long long left_integer = left_number._digits.size() - left_number._fractional_size - left_begin;
    long long right_integer = right_number._digits.size() - right_number._fractional_size - right_begin;
    if (left_integer != right_integer) {
        return (left_integer < right_integer) ^ comparing_negative;
    }
    for (long long i = 0; left_begin + i < left_number._digits.size() &&
                        right_begin + i < right_number._digits.size(); i++) {
        if (left_number._digits[i + left_begin] != right_number._digits[i + right_begin]) {
            return (left_number._digits[i + left_begin] < right_number._digits[i + right_begin]) ^ comparing_negative;
        }
    }
    //fractional part could containe back-zeros
    long long left_back_zeros = 0;
    long long right_back_zeros = 0;

    for (; left_back_zeros < left_number._fractional_size && 
        left_number._digits[left_number._digits.size() - 1 - left_back_zeros] == 0; left_back_zeros++);
    for (; right_back_zeros < right_number._fractional_size && 
        right_number._digits[right_number._digits.size() - 1 - right_back_zeros] == 0; right_back_zeros++);

    long long left_fractional = left_number._fractional_size - left_back_zeros;
    long long right_fractional = right_number._fractional_size - right_back_zeros;
    
    return (left_fractional < right_fractional) ^ comparing_negative;
}


bool operator==(const LongNumber& left_number, const LongNumber& right_number) {
    //Easy to see that
    return !(left_number < right_number) && !(right_number < left_number);
}


bool operator!=(const LongNumber& left_number, const LongNumber& right_number) {
    return !(left_number == right_number);
}

LongNumber::operator bool() const {
    return !(this->_is_zero());
}


bool operator>(const LongNumber &left_number, const LongNumber &right_number) {
    return !(left_number < right_number) && !(left_number == right_number);
}


bool operator<=(const LongNumber &left_number, const LongNumber &right_number) {
    return (left_number < right_number) || (left_number == right_number);
}


bool operator>=(const LongNumber &left_number, const LongNumber &right_number) {
    return !(left_number < right_number);
}


LongNumber operator+(const LongNumber& left_number, const LongNumber& right_number) {
    //If not the same sign it is subtraction from positive negative
    if (right_number._is_negative != left_number._is_negative) {
        if (abs(right_number) <= abs(left_number)) {
            return _abs_sub(left_number, right_number);
        } else {
            return _abs_sub(right_number, left_number);
        }
    }
    return _abs_add(left_number, right_number);
}


LongNumber operator-(const LongNumber& left_number, const LongNumber& right_number) {
    //If right not the same sign: left_number - right_number == abs(left_number) + abs(right_number) , sign = sign(left_number)
    if (right_number._is_negative != left_number._is_negative) {
        return _abs_add(left_number, right_number);
    }
    // abs(right_number) > abs(left_number) -> return right_number - left_number (with opposite sign)
    if (!(left_number._is_negative) && right_number >= left_number || left_number._is_negative && right_number <= left_number) {
        LongNumber ans = _abs_sub(right_number, left_number);
        ans._is_negative ^= true;
        return ans;
    }
    return _abs_sub(left_number, right_number);
}


LongNumber LongNumber::mul_on_digit(const LongNumber &left_number, const digit_t &right_number) {
    if (right_number == OVER_DIGIT) {
        LongNumber ans = left_number;
        if (ans._fractional_size != 0) {
            ans._fractional_size--;
        } else {
            ans._digits.push_back(0);
        }
        return ans;
    }   
    if (right_number == 0) {
        return LongNumber("0");
    }
    digit_t next = 0;
    LongNumber ans;
    // Like people * 
    for (int i =  left_number._digits.size() - 1; i >= 0; i--) {
        ans._digits.push_back((left_number._digits[i] * right_number + next) % OVER_DIGIT);
        next = (left_number._digits[i] * right_number + next) / OVER_DIGIT;
    }
    while (next != 0) {
        ans._digits.push_back(next % OVER_DIGIT);
        next /= OVER_DIGIT;
    }
    std::reverse(ans._digits.begin(), ans._digits.end());
    ans._fractional_size = left_number._fractional_size;
    return ans;
} 

LongNumber operator*(const LongNumber &left_number, const LongNumber &right_number) {
    digit_t next = 0;
    //Setting fractional size because we multiply numbers
    LongNumber ans;
    long long number_of_iteration = 0;
    for (long long i =  right_number._digits.size() - 1; i >= 0; i--, number_of_iteration++) {
        LongNumber tmp = LongNumber:: mul_on_digit(left_number, right_number._digits[i]);
        tmp._fractional_size = 0;
        for (long long j = 0; j < number_of_iteration; j++) {
            tmp._digits.push_back(0);
        }
        ans += tmp;
    }
    ans._fractional_size =  left_number._fractional_size + right_number._fractional_size;
    ans._clean_right_zeros();
    ans._is_negative = left_number._is_negative ^ right_number._is_negative;
    if(ans._is_zero()){
        ans._is_negative = false;
    }

    return ans;
}



digit_t LongNumber::_find_digit_multip(const LongNumber& result, const LongNumber& multiplier) {

    if (result < multiplier) {
        return 0;
    }
    // find closest number, mult, that: temp >= right_number * multp
    digit_t lhs = 0, rhs = OVER_DIGIT + 1;
    while (rhs - lhs > 1) {
        digit_t mid = lhs + (rhs - lhs) / 2;
        if (result < LongNumber::mul_on_digit(multiplier, mid)) {
            rhs = mid;
        } else {
            lhs = mid;
        }
        
    }
    return lhs;
}


LongNumber operator/(const LongNumber &left_number, const LongNumber &right_number) {
    //We don't know about exepction :<
    if (right_number._is_zero()) {
        return LongNumber("-0");
    }
    LongNumber temp(0);
    long long index = 0;
    LongNumber right_unfractional = right_number;
    right_unfractional._fractional_size = 0;
    const long long precision = std::max(DEFAULT_PRECISION, right_number._fractional_size) + right_number._fractional_size;
    const long long integer_part = left_number._digits.size() - left_number._fractional_size;
    LongNumber ans;
    //Immidiatly deleting leading zeros
    bool leading_zero = true;
    //Like people / 
    
    while (index < integer_part) {
        temp = LongNumber::mul_on_digit(temp, OVER_DIGIT);
        temp += LongNumber(left_number._digits[index]);
        //find closest number, mult, that: temp >= right_number * mult
        digit_t mult = LongNumber::_find_digit_multip(temp, right_unfractional);
        ans._digits.push_back(mult);
        if (mult != 0) {
            leading_zero = false;
        } else if (leading_zero && mult == 0) {
            ans._digits.pop_back();
        }
        temp -= LongNumber::mul_on_digit(right_unfractional, mult);
        index++;
    }
    if (ans._digits.empty()) {
        ans._digits.push_back(0);
    }
    
    const long long left_len = left_number._digits.size();
    //Fractional digits
    while (index < left_len) {
        temp = LongNumber::mul_on_digit(temp, OVER_DIGIT);
        temp += left_number._digits[index];
        ans._digits.push_back(LongNumber::_find_digit_multip(temp, right_unfractional));
        temp -= LongNumber::mul_on_digit(right_unfractional, ans._digits.back());
        
        index++;
        ans._fractional_size++;
    }
    //And adding zero to temp until we reach setted precision
    while (ans._fractional_size < precision) {
        temp = LongNumber::mul_on_digit(temp, OVER_DIGIT);
        ans._digits.push_back(LongNumber::_find_digit_multip(temp, right_unfractional));
        temp -= LongNumber::mul_on_digit(right_unfractional, ans._digits.back());
        ans._fractional_size++;
    }
    ans._fractional_size -= right_number._fractional_size;
    ans._clean_right_zeros();
    ans._is_negative = left_number._is_negative ^ right_number._is_negative;
    if(ans._is_zero()){
        ans._is_negative = false;
    }
    return ans;

}


LongNumber LongNumber::operator-() {
    LongNumber tmp = (*this);
    tmp._is_negative ^= true;
    return tmp;
}


LongNumber LongNumber::operator+() {
    LongNumber tmp = (*this);
    std::cout << "\nhttps://www.youtube.com/watch?v=dQw4w9WgXcQ\n";
    return tmp;
}


LongNumber operator ""_Ln(const char* string_num, const size_t len) {
    return LongNumber(string_num);
}


LongNumber operator ""_Ln(const unsigned long long number) {
    return LongNumber(number);
}


LongNumber operator ""_Ln(long double number) {
    return LongNumber(std::to_string(number));
}


std::ostream& operator<<(std::ostream& os, const LongNumber& num) {
    os << num.to_string();
    return os;
}


LongNumber& LongNumber::operator +=(const LongNumber& right_number) {
    (*this) = (*this) + right_number;
    return (*this);
}


LongNumber& LongNumber::operator -=(const LongNumber& right_number) {
    (*this) = (*this) - right_number;
    return (*this);
}


LongNumber& LongNumber::operator++() {
    operator+=(LongNumber("1"));
    return (*this);
}


LongNumber& LongNumber::operator--() {
    operator-=(LongNumber("1"));
    return (*this);
}

LongNumber LongNumber::operator++(int) {
    LongNumber tmp(*this);
    operator+=(LongNumber("1"));
    return tmp;
}


LongNumber LongNumber::operator--(int) {
    LongNumber tmp(*this);
    operator-=(LongNumber("1"));
    return tmp;
}


LongNumber abs(LongNumber num) {
    num._is_negative = false;
    return num;
}

//Presision - number of digits after decimal point
std::string LongNumber::to_string(const long long& precision) const{
    // Number of chunks after point

    const long long full_fraction_digits = precision / DIGIT_LENGTH;
    const long long integer_part_size = _digits.size() - _fractional_size;
    std::string ans;
    if (_is_negative) {
        ans += "-";
    }
    long long index = 0;
    while (index < integer_part_size && _digits[index] == 0) {
        index++;
    }
    if (index == integer_part_size) {
        ans += "0";
    } else {
        ans += std::to_string(_digits[index++]);
        while (index < integer_part_size) {
            std::string tmp = std::to_string(_digits[index]);
            ans += std::string(DIGIT_LENGTH - tmp.length(), '0') + tmp;
            index++;
        }
    }
    
    ans += ".";
    for (long long i = 0; i < std::min(full_fraction_digits, _fractional_size); i++) {
        std::string tmp = std::to_string(_digits[i + integer_part_size]);
        ans += std::string(DIGIT_LENGTH - tmp.length(), '0') + tmp;
    }
    //If we need to write more decimal digits, than we have, we ignore it (i dont want to write zeros)
    //If we need to write less, than we have, we need to write from first unwritten digit precision % DIGIT_LENGTH numbers
    if (precision < _fractional_size * DIGIT_LENGTH) {
        std::string cur_number = std::to_string(_digits[full_fraction_digits + integer_part_size]);
        cur_number = std::string(DIGIT_LENGTH - cur_number.length(), '0') + cur_number;
        ans += cur_number.substr(0, precision % DIGIT_LENGTH);
    }
    //If we somehow have right-leading zeros, write without them
    long long i = ans.length() - 1;
    for (; ans[i] != '.' && ans[i] == '0'; i--) {}
    return ans.substr(0, (ans[i] == '.' ? i : i + 1));
}


std::string LongNumber::to_string() const{
    return this->to_string(_fractional_size * DIGIT_LENGTH);
}


LongNumber LongNumber::calculate_pi(const size_t& precision) {
    LongNumber ans(0, precision);
    for (size_t k = 0; k < precision; k++) {
        LongNumber tmp(1, precision);
        for (size_t j = 0; j < k; j++) {
            tmp = tmp / 16;
        }
        tmp = tmp * (8 / LongNumber(8 * k + 2, precision) + (4) / LongNumber(8 * k + 3, precision) + 
        (4) / LongNumber(8 * k + 4, precision) - (1) / LongNumber(8 * k + 7, precision));
        ans += tmp;
    }
    return LongNumber((ans * 0.5).to_string(precision));

}


bool LongNumber::_is_zero() const {
    for (digit_t i : _digits) {
        if (i != 0) {
            return false;
        }
    }
    return true;
}

//Only for adding two numbers of the same sign
LongNumber _abs_add(const LongNumber& left_number, const LongNumber& right_number) {
    digit_t next = 0;
    //Filling ans in reverse order
    LongNumber ans;
    int left_index = left_number._digits.size() - 1;
    int right_index = right_number._digits.size() - 1;
    //Checking difference between number of ractional digits in both numbers with these vars
    int fractional_digits_left = left_number._fractional_size;
    int fractional_digits_right = right_number._fractional_size;
    //If not the same amount of fractional digits in numbers ans will be first fill with one, that other dont have(sorry, for bad english)
    if (left_number._fractional_size != right_number._fractional_size) {
        //This will work if right number have more fractional digits
        while (fractional_digits_left < fractional_digits_right) {
            ans._digits.push_back(right_number._digits[right_index]);
            right_index--;
            fractional_digits_right--;
        }
        //This will work if left number have more fractional digits
        while (fractional_digits_left > fractional_digits_right) {
            ans._digits.push_back(left_number._digits[left_index]);
            left_index--;
            fractional_digits_left--;
        }
    }
    //Basic + (like people doing)
    while (left_index >= 0 && right_index >= 0) {
        ans._digits.push_back((left_number._digits[left_index] + right_number._digits[right_index] + next) % OVER_DIGIT);
        next = (left_number._digits[left_index] + right_number._digits[right_index] + next) / OVER_DIGIT;
        left_index--;
        right_index--;
    }
    //If leading digits left, fill them 
    while (left_index >= 0) {
        ans._digits.push_back((left_number._digits[left_index] + next) % OVER_DIGIT);
        next = (left_number._digits[left_index] + next) / OVER_DIGIT;
        left_index--;
    }
    while (right_index >= 0) {
        ans._digits.push_back((right_number._digits[right_index] + next) % OVER_DIGIT);
        next = (right_number._digits[right_index] + next) / OVER_DIGIT;
        right_index--;
    }
    std::reverse(ans._digits.begin(), ans._digits.end());
    //Sign of ans is sign of any number
    ans._is_negative = left_number._is_negative;
    ans._fractional_size = std::max(left_number._fractional_size, right_number._fractional_size);
    ans._clean_right_zeros();
    if (ans._is_zero()) {
        ans._is_negative = false;
    }
    return ans;
}

//Only for subtraction from greater abs(number) (same signs)
LongNumber _abs_sub(const LongNumber& left_number, const LongNumber& right_number) {
    digit_t next = 0;
    LongNumber ans;
    //Checking difference between number of ractional digits in both numbers with these vars
    int fractional_digits_left = left_number._fractional_size;
    int fractional_digits_right = right_number._fractional_size;
    int left_index = left_number._digits.size() - 1;
    int right_index = right_number._digits.size() - 1;
    
    if (fractional_digits_left != fractional_digits_right) {
        // Like in normal - we "borrow" from the next digit 
        while (fractional_digits_left < fractional_digits_right) {
            ans._digits.push_back(OVER_DIGIT - next - right_number._digits[right_index]);
            right_index--;
            next = 1;
            fractional_digits_right--;
        }
        //If left has more, we will just copy them
        while (fractional_digits_left < fractional_digits_right) {
            ans._digits.push_back(left_number._digits[left_index]);
            left_index--;
            fractional_digits_left--;
        }
    }
    while (left_index >= 0 && right_index >= 0) {
        //If we subs more than have we borrow from the next digit
        if (left_number._digits[left_index] < right_number._digits[right_index] + next) {
            ans._digits.push_back(OVER_DIGIT - next - right_number._digits[right_index] + left_number._digits[left_index]);
            next = 1;
        } else {
            ans._digits.push_back(left_number._digits[left_index]- next - right_number._digits[right_index]);
            next = 0;
        }
        left_index--;
        right_index--;
    }
    // And copying last digits(keep in mind we still might have 'borrowing')
    while (left_index >= 0) {
        if (left_number._digits[left_index] < next) {
            //Means that current digit is zero
            ans._digits.push_back(OVER_DIGIT - next);
            next = 1;
        } else {
            ans._digits.push_back(left_number._digits[left_index] - next);
            next = 0;
        }
        left_index--;
    }
    //Deleting leading zeros
    long long integer_part = ans._digits.size() - ans._fractional_size;
    while (integer_part != 1 && ans._digits.back() == 0) {
        ans._digits.pop_back();
    }
    std::reverse(ans._digits.begin(), ans._digits.end());
    ans._is_negative = left_number._is_negative;
    ans._fractional_size = std::max(left_number._fractional_size, right_number._fractional_size);
    ans._clean_right_zeros();
    if (ans._is_zero()) {
        ans._is_negative = false;
    }

    return ans;
}

void LongNumber::_clean_right_zeros() {
    
    while (_fractional_size != 0 && _digits.back() == 0) {
        _digits.pop_back();
        _fractional_size--;
    }
}