#pragma once

#include <iostream>
#include <string>
#include <algorithm>

class Money 
{ 

       friend std::ostream& operator<< (std::ostream &os, const Money &obj);

public:

   Money();
   Money(const size_t &n, unsigned char t = 0);
   Money(const std::initializer_list<unsigned char> &t);
   Money(const std::string &t);

   Money(const Money& other);
   Money(Money&& other) noexcept;
   virtual ~Money() noexcept;

   bool operator> (const Money &other) const;
   bool operator== (const Money &other) const;
   bool operator!= (const Money &other) const;
   bool operator>= (const Money &other) const;
   bool operator< (const Money &other) const;
   bool operator<= (const Money &other) const;

   Money operator+ (const Money &other) const;
   Money operator- (const Money &other) const;
   Money operator=(const Money &other);
   Money operator+= (const Money &other);
   Money operator-= (const Money &other);

   size_t getsize() const noexcept;
   unsigned char* getarray() const noexcept;
   bool getisnegative() const noexcept;
   

private:
    size_t _size;
    unsigned char* _array;
    bool _isNegative = false;
    bool isDecimal (unsigned char c) const;
    
};

unsigned char ToUnsChar(char c);
char ToChar(unsigned char c);