#include<iostream>

int gcd(int x, int y)
{
    int a = x;
    int b = y;
    int c;
    while(b > 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
}

class Rational{
public:
    int a, b;
    Rational(int x, int y)
    {
        a = x;
        b = y;
    }
    void operator += (Rational r)
    {
        int x = a * r.b + b * r.a;
        int y = b * r.b;
        a = x;
        b = y;
    }
    Rational operator +(Rational r)
    {
        int x = a * r.b + b * r.a;
        int y = b * r.b;
        return Rational(x, y);
    }
    void operator -= (Rational r)
    {
        int x = a * r.b - b * r.a;
        int y = b * r.b;
        a = x;
        b = y;
    }
    Rational operator -(Rational r)
    {
        int x = a * r.b - b * r.a;
        int y = b * r.b;
        return Rational(x, y);
    }
    operator double(){
        return 1.0 * a / b;
    }
    void operator *= (Rational r)
    {
        a *= r.a;
        b *= r.b;
    }
    Rational operator *(Rational r)
    {
        return Rational(a * r.a, b * r.b);
    }
    void operator *=(int n)
    {
        a *= n;
    }
    void operator /= (Rational r)
    {
        a *= r.b;
        b *= r.a;
    }
    Rational operator /(Rational r)
    {
        return Rational(a * r.b, b * r.a);
    }
    void operator /=(int n)
    {
        b *= n;
    }
    Rational(int n)
    {
        a = n;
        b = 1;
    }
    void operator ++()
    {
        a += b;
    }
    void operator --()
    {
        a -= b;
    }
    bool operator <(Rational r)
    {
        return a * r.b < b * r.a;
    }
    bool operator >(Rational r)
    {
        return a * r.b > b * r.a;
    }
    bool operator ==(Rational r)
    {
        return a * r.b == b * r.a;
    }
    Rational operator ++(int)
    {
        Rational old_value(*this);
        ++*this;
        return old_value;
    }
    Rational operator --(int)
    {
        Rational old_value(*this);
        --*this;
        return old_value;
    }
    void print()
    {
        std::cout << a / gcd(a,b) << "/" << b / gcd(a,b) << "\n";
    }
};

void test()
{
    assert((Rational(5,4) * Rational(2, 3)) == (Rational(1,2) + Rational(1,3));
}

int main()
{
    test();
    return 0;
}

