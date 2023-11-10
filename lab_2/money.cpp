#include "money.h"

unsigned char ToUnsChar(char c) {
    return (unsigned char)(c - '0');
}

char ToChar(unsigned char c) {
    return (char)(c + '0');
}

bool Money::isDecimal (unsigned char c) const {
    return (0 <= c && c <= 9);
}

Money::Money() : _size(0), _array{nullptr} {}

Money::Money(const size_t &n, unsigned char t) {
    _array = new unsigned char[n];
    _size = n;
    for (int i = n - 1; i >= 0; --i) {
        if (isDecimal(t)) _array[i] = t;
        else {
            delete[] _array;
            _array = nullptr;
            throw std::invalid_argument("Init list constructor: symbol is not in correct place");
        }
    }   
}

Money::Money(const std::initializer_list<unsigned char> &t) {
    _array = new unsigned char[t.size()];
    _size = t.size();
    size_t i{t.size() - 1};
    for (auto c : t) {
        if (isDecimal(c)) _array[i--] = c;
        else {
            delete[] _array;
            _array = nullptr;
            throw std::invalid_argument("Init list constructor: symbol is not in correct place");
        }
    }
}

Money::Money(const std::string &str) {
    int ind = 0;
    if (str[0] == '-') {
        _isNegative = true;
        ind += 1; 
    }
    while (str[ind] == '0') ind++;
    
    if (ind == str.size()) ind--;
    
    _size  = str.size() - ind;
    _array = new unsigned char[_size];

    for (int i = _size - 1; i >= 0; i--) {
        if (isDecimal(ToUnsChar(str[ind]))) {
            _array[i] = ToUnsChar(str[ind]);
            ind++;
        } 
        else {
            delete[] _array;
            _array = nullptr;
            throw std::invalid_argument("Init list constructor: symbol is not in correct place");
        }
    }
}


Money::Money(const Money &other) {
    _size  = other._size;
    delete[] _array;
    _array = new unsigned char[_size];
    _isNegative = other._isNegative;

    for(size_t i{0}; i < _size; ++i) _array[i] = other._array[i];
}

Money::Money(Money &&other) noexcept {
    _size = other._size;
    _array = other._array;
    _isNegative = other._isNegative;

    other._size = 0;
    delete[] other._array;
    other._array = nullptr;
}

Money::~Money() noexcept {
    if (_size > 0) {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}

bool Money::operator> (const Money &other) const {
    if (this->_isNegative && !other._isNegative) return false;
    else if (!this->_isNegative && other._isNegative) return true;
    else if (!this->_isNegative && !other._isNegative) {
        if (this->_size > other._size) return true;
        else if (this->_size < other._size) return false;
        else {
            for (int i = this->_size - 1; i >= 0; i--) {
                if (this->_array[i] > other._array[i]) return true;
                if (this->_array[i] < other._array[i]) return false;
            }
        }
    } else {
        if (this->_size > other._size) return false;
        else if (this->_size < other._size) return true;
        else {
            for (int i = this->_size - 1; i >= 0; i--) {
                if (this->_array[i] > other._array[i]) return false;
                if (this->_array[i] < other._array[i]) return true;
            }
        }
    }
    return false;
}

bool Money::operator== (const Money &other) const {
    if (this->_isNegative != other._isNegative) return false;
    if (_size == other._size) {
        for (int i = 0; i < _size; i++) {
            if (_array[i] != other._array[i]) return false;
        }
        return true;
    } else {
        return false;
    }
}
bool Money::operator!= (const Money &other) const {
    return (!(*this == other));
}
bool Money::operator>= (const Money &other) const {
    return (*this > other || *this == other);
}

bool Money::operator< (const Money &other) const {
    return(!(*this >= other));
}

bool Money::operator<= (const Money &other) const {
    return (!(*this > other));
}


Money Money::operator+ (const Money &other) const {
    if (!_isNegative && other._isNegative) {
        Money tmp = other;
        tmp._isNegative = false;
        return *this - tmp;
    }
    if (_isNegative && !other._isNegative) {
        Money tmp = *this;
        tmp._isNegative = false;
        return other - tmp;
    }
    if (_isNegative && other._isNegative) {
        Money tmp1 = *this;
        tmp1._isNegative = false;
        Money tmp2 = other;
        tmp2._isNegative = false;
        Money res = tmp1 + tmp2;
        res._isNegative = true;
        return res;
    }
    Money res;
    res._size = (this->_size < other._size) ? other._size : this->_size;
    res._array = new unsigned char[res._size];

    int val = 0, mod = 0;
    for (int i = 0; i < res._size; i++) {
        if (i < _size) val += this->_array[i];
        if (i < other._size) val += other._array[i];
        val += mod;
        mod = val % 10;
        res._array[i] = mod;
        mod = val / 10;
        val = 0;
    }
    if (mod > 0) {
        res._size += 1;
        unsigned char* new_array = new unsigned char[res._size];
        for (int i = 0; i < res._size - 1; i++) {
            new_array[i] = res._array[i];
        }
        new_array[res._size - 1] = mod;
        delete [] res._array;
        res._array = new_array;
    }
    return res;
}

Money Money::operator- (const Money &other) const {
    if (!_isNegative && other._isNegative) {
        Money tmp = other;
        tmp._isNegative = false;
        return *this + tmp;
    }
    if (_isNegative && !other._isNegative) {
        Money tmp = *this;
        tmp._isNegative = false;
        Money res = tmp + other;
        res._isNegative = true;
        return res;
    }
    if (_isNegative && other._isNegative) {
        Money tmp1 = *this;
        tmp1._isNegative = false;
        Money tmp2 = other;
        tmp2._isNegative = false;
        return tmp2 - tmp1;
    }
    if (*this == other) {
        Money res;
        res._size = 1;
        res._array = new unsigned char[res._size];
        res._array[0] = 0;
        return res;
    }
    if (*this >= other) {
        Money res;
        int val;
        res._size = _size;
        res._array = new unsigned char[res._size];
        for (int i = 0; i < _size; ++i) {
            res._array[i] = _array[i];
        }
        for (int i = 0; i < _size; ++i) {
            if (i < other._size) {
                if (res._array[i] >= other._array[i]) {
                    val = res._array[i] - other._array[i];
                } else {
                    val = res._array[i] - other._array[i] + 10;
                    for(int k = i + 1; k < _size; ++k) {
                        if (res._array[k] > 0) {res._array[k] -= 1; break;}
                        else if (res._array[k] == 0) res._array[k] = 9;
                    }
                }
                res._array[i] = val;
            }
        }
        int ind = res._size - 1;
        if (res._array[ind] == 0) {
            while (res._array[ind] == 0) {
                ind--;
            }
            Money ans;
            ans._size = ind + 1;
            ans._array = new unsigned char [ans._size];
            for (int i = ind; i >= 0; i--) {
                ans._array[i] = res._array[i];
            }
            delete [] res._array;
            res._size = 0;
            return ans;
        }

        return res;
    } else {
        Money res = other - *this;
        res._isNegative = true;
        return res;
    }

}

Money Money::operator= (const Money &other) {
    delete [] _array;
    _size = other._size;
    _array = new unsigned char[_size];
    _isNegative = other._isNegative;

    for (int i = 0; i < _size; i++) _array[i] = other._array[i];

    return *this;
}

Money Money::operator+= (const Money &other) {
    *this = *this + other;
    return *this;
}

Money Money::operator-= (const Money &other) {
    *this = *this - other;
    return *this;
}

size_t Money::getsize() const noexcept {
    return _size;
}

unsigned char* Money::getarray() const noexcept {
    return _array;
}

bool Money::getisnegative() const noexcept {
    return _isNegative;
}

std::ostream& operator<< (std::ostream& os, const Money &obj) {
    if (obj._isNegative) os << '-';
    for (int i = obj.getsize() - 1; i >= 0; i--) {
        os << ToChar(obj.getarray()[i]);
    }
    return os;
}