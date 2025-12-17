class point
{
 private:
    int x,y;
 public:
    point()
    {
        x = 0;
        y = 0;
    }
    point(int a, int b)
    {
        x = a;
        y = b;
    }
    int Getx()
    {
        return x;
    }
    int Gety()
    {
        return y;
    }
    bool operator ==(point p)
    {
        return x == p.getx() && y == p.gety();
    }
};

point min_(point A, point B)
{
    return point(std::min(A.Getx(), B.Getx()), std::min(A.Gety(), B.Gety()));
}

point max_(point A, point B)
{
    return point(std::max(A.Getx(), B.Getx()), std::max(A.Gety(), B.Gety()));
}

struct Rectangle
{
private:
    point A, C;
public:
    point Geta()
    {
        return A;
    }
    point Getc()
    {
        return C;
    }
    Rectangle(point a, point c)
    {
        A = a;
        C = c;
    }
    bool operator ==(Rectangle r)
    {
        return A == r.Geta() && C == r.Getc();
    }
};

Rectangle union_(Rectangle r1, Rectangle r2)
{
    return Rectangle(max_(r1.Geta(), r2.Geta()), min_(r1.Getc(), r2.Getc()));
}

Rectangle boundingbox(Rectangle r1, Rectangle r2)
{
    return Rectangle(min_(r1.Geta(), r2.Geta()), max_(r1.Getc(), r2.Getc()));
}

Rectangle Union(Rectangle* r, int n)
{
    Rectangle R = r[0];
    for (int i = 1; i < n; i++)
    {
        R = union_(R, r[i]);
    }
    return R;
}

Rectangle BoundingBox(Rectangle* r, int n)
{
    Rectangle R = r[0];
    for (int i = 1; i < n; i++)
    {
        R = boundingbox(R, r[i]);
    }
    return R;
}

void test(){
    Rectangle r1(point(0, 1), point(4, 5)), r2(point(1, 0), point(5, 4));
    assert(boundingbox(r2, r1) == Rectangle(point(0, 0), point(5, 5)));
}

int main()
{
    test();
    return 0;
}

