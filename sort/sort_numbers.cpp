#include <iostream>
using namespace std;

int main()
{
    while (true)
    {
        int a;
        cin >> a;
        if (cin.eof())
        {
            break;
        }
        cout << a << endl;
    }
}
