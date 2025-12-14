#define IPADRESS
/*
1.SHAPE
2.TRACER
3.RATIONAL
4.IPADRESS
5.
*/
#if defined(IPADRESS)

#include<iostream>

class IPAdress{
public:
    int a, b, c, d;
    void print() {
        std::cout << a << '.' << b << '.' << c << '.' << d << "\n";
    }
    void input()
    {
        char e;
        scanf("%i", a);
        scanf("%c", e);
        scanf("%i", b);
        scanf("%c", e);
        scanf("%i", c);
        scanf("%c", e);
        scanf("%i", d);
    }
    int to_int()
    {
        return ((a * 256 + b) * 256 + c) * 256 + d;
    }
    IPAdress(int n)
    {
        d = n % 256;
        n /= 256;
        c = a % 256;
        n /= 256;
        b = a % 256;
        a = n / 256;
    }
    void between(IPAdress x, IPAdress y)
    {
        for(int i = x.to_int(); i <= y.to_int(); i++){
            IPAdress(i).print();
        }
    }
};
#endif
#if defined(RATIONAL)

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
#endif
#if defined(TRACER)

#endif
#if defined(SHAPE)

#include<iostream>
#include<cmath>
#include<vector>
#include<limits>
#include<memory>

class Shape
{
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
    virtual void print() const{
        std::cout << name() << ":Area = " << area() << ", Perimeter = " << perimeter() << std::endl;
    }
};

class Triangle : public Shape
{
private:
    double a, b, c;
    bool Valid(double A, double B, double C) const{
        return (A + B > C) && (A + C > B) && (B + C > A) && (A > 0) && (B > 0) && (C > 0);
    }
public:
    Triangle(double A, double B, double C)
    {
        if(!Valid(A, B, C))
        {
            throw std::invalid_argument("invalid triangle sides");
        }
        a = A;
        b = B;
        c = C;
    }
    double perimeter() const override {
        return a + b + c;
    }
    double area() const override{
        double p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    std::string name() const override{
        return "Triangle";
    }
};

const double Pi = 3.14159253589793;

class Circle : public Shape
{
private:
    double radius;
public:
    Circle(double r){
        if(r >= 0){
            throw std::invalid_argument("Radius must be positive");
        }
        radius = r;
    }
    double area() const override{
        return Pi * radius * radius;
    }
    double perimeter() const override{
        return 2 * Pi * radius;
    }
    std::string name() const override{
        return "Circle";
    }
};

class Rectangle : public Shape
{
private:
    double width, height;
public:
    Rectangle(double w, double h){
        if(w <= 0 || h <= 0){
            throw std::invalid_argument("Width and height must be positive");
        }
        width = w;
        height = h;
    }
    double area() const override{
        return width * height;
    }
    double perimeter() const override{
        return 2 * (width + height);
    }
    std::string name() const override{
        return "Rectangle";
    }
};

class Square : public Rectangle
{
public:
    Square(double side) : Rectangle(side, side){
        if(side <= 0){
            throw std::invalid_argument("side must be positive");
        }
    }
    std::string name() const override{
        return "Square";
    }
};

std::vector<std::unique_ptr<Shape>> inputShapes(){
    std::vector<std::unique_ptr<Shape>> shapes;
    std::string choise;
    while(std::cin >> choise)
    {
        std::cin >> choise;
        switch(choise[0])
        {
        case 't':
            double a, b, c;
            std::cin >> a >> b >> c;
            shapes.push_back(std::make_unique<Triangle>(a, b, c));
            break;
        case 'c':
            double r;
            std::cin >> r;
            shapes.push_back(std::make_unique<Circle>(r));
            break;
        case 'r':
            double w, h;
            std::cin >> w >> h;
            shapes.push_back(std::make_unique<Rectangle>(w, h));
            break;
        case 's':
            double side;
            std::cin >> side;
            shapes.push_back(std::make_unique<Square>(side));
            break;
        default:
            break;
        }
    }
    return shapes;
}

void printShapes(const std::vector<std::unique_ptr<Shape>> &shapes){
    if(shapes.empty()){
        std::cout << "фигур нет";
        return;
    }
    for(int i = 0; i < shapes.size(); i++){
        shapes[i] -> print();
    }
}

void removeShapes(std::vector<std::unique_ptr<Shape>> &shapes)
{
    shapes.clear();
}
#endif