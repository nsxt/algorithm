#include <iostream>
#include <string>
using namespace std;

void reverse(char* str) {
    if (str == nullptr) return;

    // 문자열의 길이를 알아낸다.
    int str_len = 0;
    do {
        if (str[str_len++] == '\0') break;
    } while (1);

    if (str_len <= 1) return;

    char* temp_str = new char[str_len];

    // null 문자는 뒤집기 대상에서 제외
    str_len--;
    for (int i = 0, j = str_len - 1; i < str_len; i++, j--) {
        temp_str[i] = str[j];
    }

    memcpy(str, temp_str, str_len);

    // 최종적으로 null 문자 삽입
    str[str_len] = '\0';

    delete[] temp_str;
}

int main() {
    string mystr;
    cout << "Input strings : ";
    getline(cin, mystr);
    cout << endl;

    // 입력받은 문자열을 정적 배열로 복사
    // 문자열의 길이는 ASCII 문자 80 개로 제한 한다.
    char arr_str[80];
    memset(arr_str, 0, sizeof(char) * 80);

    memcpy(arr_str, mystr.c_str(), mystr.length());
    reverse(arr_str);

    cout << "Result : " << arr_str;

    return 0;
}