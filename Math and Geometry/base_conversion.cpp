// template for base conversions
/*
2 functions:
1. from integer (base 10) to base N
2. from base N to integer (base 10)

(1) while number > 0, keep adding number % base to answer, and 
divide number by base. Reverse the string at the end.
(2) for each digit, add answer * base + number[i] to answer.

Both time conmplexity is O(len of number)
*/
#include <bits/stdc++.h>
using namespace std;

// representation of integer `num` in base `base`
string intToBase(int num, int base)
{
    string out = "";
    while (num)
    {
        out += to_string(num % base);
        num /= base;
    }

    reverse(out.begin(), out.end());
    return out;
}

// change number (string) of base `base` to integer (base 10)
int baseToInt(string num, int base)
{
    int out = 0;
    for (int i = 0; i < num.length(); i++)
        out = out * base + (num[i] - '0');

    return out;
}

int main(){
    string number; int base;
    cin >> number >> base;
    cout << baseToInt(number, base) << endl;
    // cout << intToBase(number, base) << "\n";

    return 0;
}
