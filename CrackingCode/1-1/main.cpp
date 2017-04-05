/*
 * 1-1. 문자열에 포함된 문자들이 전부 유일한지를 검사하는 알고리즘
 *
 */

#include <iostream>
#include <string>

using namespace std;

// 전달된 문자열은 ASCII 코드라고 가정 한다.
bool is_unique_string(const char* str, int len)
{
    // 문자열의 길이가 255 (ASCII) 를 초과 하면 중복된 문자가 포함되어 있다
    if (len > 255)
        return false;

    bool check_unique[256];
    for (int i = 0; i < 256; i++) {
        check_unique[i] = false;
    }

    for (int i = 0; i < len; i++) {
        unsigned char ch = str[i];
        if (check_unique[ch]) {
            return false;
        }

        check_unique[ch] = true;
    }

    return true;
}

int main() {

    string mystr;

    cout << "Input ASCII code : ";
    getline(cin, mystr);
    cout << endl;

    bool result = is_unique_string(mystr.c_str(), mystr.length());
    cout << (result ? "All string is unique!!" : "Not unique...");

    cout << endl;

    return 0;
}