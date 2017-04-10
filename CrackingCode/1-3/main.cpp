#include <iostream>
#include <string>
using namespace std;

// 문자열 두 개를 입력으로 받아
// 그 중 하나가 다른 하나의 순열인지 판별하는 메서드
bool check_permutation(const char* src, const char* other)
{
    if (src == nullptr || other == nullptr) return false;

    // 입력되는 문자열은 null 문자로 종료된다고 가정
    int src_len = 0;
    int other_len = 0;

    while (src[src_len++] != '\0');
    while (other[other_len++] != '\0');

    bool check_result[src_len];
    for (int i = 0; i < src_len; i++) {
        check_result[i] = false;
    }

    for (int i = 0; i < src_len; i++) {
        for (int j = 0; j < other_len; j++) {
            if (src[i] == other[j]) {
                check_result[i] = true;
            }
        }
    }

    for (int i = 0; i < src_len; i++) {
        if (check_result[i] == false)
            return false;
    }

    return true;
}

int main() {

    string str1;
    string str2;

    cout << "Input string 1 : ";
    getline(cin, str1);

    cout << "Input string 2 : ";
    getline(cin, str2);

    cout << endl;

    if (check_permutation(str1.c_str(), str2.c_str())) {
        cout << "String 1 is permutation of String 2.";
    }
    else {
        cout << "String 1 is NOT permutation of String 2";
    }

    cout << endl;

    if (check_permutation(str2.c_str(), str1.c_str())) {
        cout << "String 2 is permutation of String 1.";
    }
    else {
        cout << "String 2 is NOT permutation of String 1.";
    }

    cout << endl;

    return 0;
}