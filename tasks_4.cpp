#define STACK

#if defined(STACK)
#include<stack>
#include<iostream>
#include<stdexcept>

class nonumbererror : public std::exception {
private:
    const char* errorMessage;
public:
    nonumbererror(const char* message) : errorMessage(message) {}
};

class toomanynumbererror : public std::exception {
private:
    const char* errorMessage;
public:
    toomanynumbererror(const char* message) : errorMessage(message) {}
};

class nonumberserror : public std::exception{
private:
    const char* errorMessage;
public:
    nonumberserror(const char* message) : errorMessage(message) {}
};

int decode(std::string s)
{
    int n = -1;
    int a, b;
    std::stack<int> st;
    for(int i = 0; i < s.size(); i++)
    {
        if('0' <= s[i] && s[i] <= '9')
        {
            if(n == -1)
            {
                n = 0;
            }
            n = n * 10 + s[i] - '0';
        }
        else
        {
            if(s[i] == ' ')
            {
                if(n != -1)
                {
                    st.push(n);
                }
            }
            else
            {
                switch (s[i])
                {
                case '+':
                    if(st.empty())
                    {
                        throw nonumbererror("first symbols is only one number");
                    }
                    a = st.top();
                    st.pop();
                    if(st.empty())
                    {
                        throw nonumbererror("first symbols is only one number");
                    }
                    b = st.top();
                    st.pop();
                    st.push(a + b);
                    break;
                case '-':
                    if(st.empty())
                    {
                        throw nonumbererror("first symbols is only one number");
                    }
                    a = st.top();
                    st.pop();
                    if(st.empty())
                    {
                        throw nonumbererror("first symbols is only one number");
                    }
                    b = st.top();
                    st.pop();
                    st.push(a - b);
                case '*':
                    if(st.empty())
                    {
                        throw nonumbererror("first symbols is only one number");
                    }
                    a = st.top();
                    st.pop();
                    if(st.empty())
                    {
                        throw nonumbererror("first symbols is only one number");
                    }
                    b = st.top();
                    st.pop();
                    st.push(a * b);
                case '/':
                    if(st.empty())
                    {
                        throw nonumbererror("first symbols is only one number");
                    }
                    a = st.top();
                    st.pop();
                    if(st.empty())
                    {
                        throw nonumbererror("first symbols is only one number");
                    }
                    b = st.top();
                    st.pop();
                    st.push(a / b);
                default:
                    break;
                }
            }
            n = -1;
        }
    }
    if(st.empty())
    {
        throw nonumberserror("must be a number");
    }
    a = st.top();
    st.pop();
    if(!st.empty())
    {
        throw toomanynumbererror("at the end must be only one number");
    }
    return a;
}

int main()
{
    std::string s = "1 3 + 4 * 3 * 3 + 5 /";
    std::cout << decode(s);
    return 0;
}
#endif