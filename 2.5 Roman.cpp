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

