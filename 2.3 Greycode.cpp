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

