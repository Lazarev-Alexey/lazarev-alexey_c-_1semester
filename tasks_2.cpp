#define RECTANGLE
/*
1.RECTANGLE
2.NODE
3.GREYCODE
4. уже сдавал
5.ROMAN
6.COMMIVOYAGER
*/
#if defined(NODE)
struct Node{
    Node* next;
    Node(Node* n)
    {
        next = n;
    }
    Node()
    {
        next = nullptr;
    }
    ~Node()
    {
        delete next;
    }
};

Node* ReverseList(Node* head){
    Node* tail = nullptr;
    Node n;
    while((*head).next != nullptr)
    {
        n = (*head).next -> next;
        (*((*head).next)).next = tail;
        tail = (*head).next;
        (*head).next = &n;
    }
    (*head).next = tail;
    return head;
}

Node* DelNodeAtHead(Node* head)
{
    return head->next;
}

Node* AddNodeAtHead(Node* head, Node* node)
{
    node->next = head;
    return node;
}
#endif
#if defined(COMMIVOYAGER)

#include<iostream>

struct Road {
    int from_num;
    int to_num;
    double distance;
};

const Road kRoads[] = {
    {0, 1, 15.5},
    {1, 2, 10.0},
    {2, 3, 25.6},
    {3, 4, 13.6},
    {4, 5, 20.8},
    {5, 6, 5.8},
    {6, 7, 6.7},
    {7, 8, 9.3},
    {8, 9, 12.9},
    {9, 0, 15.8},
    {4, 7, 5.7},
    {5, 8, 10.6},
    {6, 9, 13.6},
    {7, 0, 7.8},
    {8, 1, 30.0},
    {9, 2, 2.6}
};

int used[10] = {};

double dfs(int v, double s, int n)
{
    if(used[v])
    {
        if(n == 10 && v == 0)
        {
            return s;
        }
        return -1.0;
    }
    double a = -1.0;
    double t;
    for(auto r:kRoads)
    {
        if(r.from_num == v)
        {
            t = dfs(r.to_num, s + r.distance, n + 1);
            if(t != -1.0)
            {
                if(a == -1.0)
                {
                    a = t;
                }
                else
                {
                    a = std::min(a, t);
                }
            }
        }
        if(r.to_num == v)
        {
            t = dfs(r.from_num, s + r.distance, n + 1);
            if(t != -1.0)
            {
                if(a == -1.0)
                {
                    a = t;
                }
                else
                {
                    a = std::min(a, t);
                }
            }
        }
    }
    return a;
}

int main()
{
    double d = dfs(0, 0.0, 0);
    if(d == -1)
    {
        std::cout << "The problem is unsolvable";
    }
    else
    {
        std::cout << d;
    }
    return 0;
}
#endif
#if defined(RECTANGLE)

#include<iostream>

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
    int getx()
    {
        return x;
    }
    int gety()
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
    return point(std::min(A.getx(), B.getx()), std::min(A.gety(), B.gety()));
}

point max_(point A, point B)
{
    return point(std::max(A.getx(), B.getx()), std::max(A.gety(), B.gety()));
}

struct Rectangle
{
private:
    point A, C;
public:
    point geta()
    {
        return A;
    }
    point getc()
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
        return A == r.geta() && C == r.getc();
    }
};

Rectangle union_(Rectangle r1, Rectangle r2)
{
    return Rectangle(max_(r1.geta(), r2.geta()), min_(r1.getc(), r2.getc()));
}

Rectangle boundingbox(Rectangle r1, Rectangle r2)
{
    return Rectangle(min_(r1.geta(), r2.geta()), max_(r1.getc(), r2.getc()));
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

int main(){
    Rectangle r1(point(0, 1), point(4, 5)), r2(point(1, 0), point(5, 4));
    if(!(boundingbox(r2, r1) == Rectangle(point(0, 0), point(5, 5))))
        std::cout << "error";
}
#endif
#if defined(GREYCODE)

#include<iostream>

std::string bitcode_(unsigned int n)
{
    std::string s = "";
    for(int i = 0; i < 5; i++)
    {
        s = static_cast<char>('0' + ((n & (1 << i))/(1 << i))) + s;
    }
    return s;
}

std::string greycode_(unsigned int n)
{
    std::string s = "";
    for(int i = 0; i < 5; i++)
    {
        s = static_cast<char>('0' + (((1 << i) + n) % (2 << i))) + s;
    }
    return s;
}

int decode_(std::string s)
{
    bool b = 0;
    unsigned int n = 0;
    for(int i = 0; i < 5; i++)
    {
        if(s[i] == '1')
        {
            if(b)
            {
                b = 0;
            }
            else
            {
                b = 1;
                n++;
            }
        }
        else
        {
            if(b)
            {
                b = 1;
                n++;
            }
        }
        n *= 2;
    }
    return n;
}

int main()
{
    for(unsigned int i = 0; 1 < 32; i++)
    {
        std::cout << i << " " << bitcode_(i) << " " << greycode_(i) << " " << decode_(bitcode_(i)) << "\n";
    }
    return 0;
}
#endif
#if defined(ROMAN)
#include<iostream>

std::string roman_(int n) {
    if(n >= 5000) {
        return "number is too big";
    }
    if(n < 1)
    {
        return "number is not positive";
    }
    std::string s = "";
    while(n >= 1000)
    {
        s += 'M';
        n -= 1000;
    }
    if(n >= 500)
    {
        s += 'D';
        n -= 500;
    }
    while(n>= 100)
    {
        s += 'C';
        n -= 100;
    }
    if(n >= 50)
    {
        s += 'L';
        n -= 50;
    }
    while(n >= 10)
    {
        s += 'X';
        n -= 10;
    }
    s += 'I' * n;
    return s;
}

int main()
{
    for (int i = 0; i < 1000; i++)
    {
        std::cout << roman_(i + 1) << "\n";
    }
    return 0;
}
#endif
