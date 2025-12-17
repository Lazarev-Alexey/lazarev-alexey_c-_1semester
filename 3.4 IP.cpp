class IPAdress{
public:
    int a, b, c, d;
    void Print() {
        std::cout << a << '.' << b << '.' << c << '.' << d << "\n";
    }
    void Input()
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
    int To_int()
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
    void Between(IPAdress x, IPAdress y)
    {
        for(int i = x.to_int(); i <= y.to_int(); i++){
            IPAdress(i).print();
        }
    }
};

void test()
{
    IPAdress ip1, ip2;
    ip1.Input();
    ip2.Input();
    Between(ip1, ip2);
}

inr main()
{
    test();
}

