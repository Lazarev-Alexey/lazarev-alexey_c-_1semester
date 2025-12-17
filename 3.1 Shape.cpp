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
    double Perimeter() const override {
        return a + b + c;
    }
    double Area() const override{
        double p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    std::string Name() const override{
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
    double Area() const override{
        return Pi * radius * radius;
    }
    double Perimeter() const override{
        return 2 * Pi * radius;
    }
    std::string Name() const override{
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
    double Area() const override{
        return width * height;
    }
    double Perimeter() const override{
        return 2 * (width + height);
    }
    std::string Name() const override{
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
    std::string Name() const override{
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

void test()
{
    Square s1(7)
    assert(s1.Area() == 49);
    assert(s1.Perimeter() == 28);
    assert(s1.Name() == "Square");
    Rectangle r1(7, 9);
    assert(r1.Area() == 63);
    assert(r1.Perimeter() == 32);
    assert(r1.Name() == "Rectangle");
    Circle c1(6);
    assert(c1.Area() == Pi * 36);
    assert(c1.Perimeter() == 12 * Pi);
    assert(c1.Name() == "Circle");
}

int main()
{
    test();
    return 0;
}

