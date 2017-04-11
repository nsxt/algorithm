#include <iostream>
#include <string>
using namespace std;

// 문자열의 모든 공백을 '%20'문자로 변경한다
// 입력문자열은 ASCII Code 이다.
// 입력 : "Mr John Smith    ", 13
// 출력 : "Mr%20John%20Smith"
void replace_space(char* str, int len)
{
    // 전략 : 주어진 문자열을 처음부터 검색하면서 공백문자가 발견되면 이후 문자열들을 뒤로 옮긴다.
    // 문자열의 공간은 대체되는 문자를 포함한 충분한 공간이 있다고 가정한다.
    // 그래서 문자열의 가능한 공간 계산을 위한 검사 처리는 제외한다.
    const char replace_str[3] = {'%', '2', '0'};

    int index = 0;
    while (index < len) {
        // 스페이스문자인가?
        if (str[index] == 32) {
            // 대체할 문자 '%20' 크기만큼 문자열을 뒤로 밀어준다. 이때 널문자도 고려되어야 한다.

            // 공백문자르 고려하여 인덱스 고려
            int stop_index = index + 1;

            // 문자열을 뒤로 밀어서 공간 확보
            int offset = 2;
            for (int i = len - 1; i > stop_index; i--) {
                str[i] = str[i - offset];
            }

            // 확보된 공간에 대체 문자열 대입
            memcpy(str + index, replace_str, sizeof(char) * 3);
        }

        ++index;
    }
}

// 문자열내의 공백문자 갯수 확인
int count_space_char(const char* str, int len)
{
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == 32)
            count++;
    }

    return count;
}

int main() {

    string input_str;
    cout << "Input String : ";
    getline(cin, input_str);

    int str_len;
    cout << "Buffer length : ";
    cin >> str_len;

    // 입력받은 문자열내에 공백 문자가 몇개 있는지 조사 후 확장될 문자만큼 배열을 할당해야됨
    // 문제 내용 중 '문자열 끝에 추가로 필요한 문자들을 더 할 수 있는 충분한 공간이 있다고 가정'
    // string 과 vector 에 이미 모두 있지만... 훈련이니깐...
    int space_count = count_space_char(input_str.c_str(), str_len);
    str_len += (space_count * 2 + 1);

    char array_str[str_len];
    memset(array_str, 0, sizeof(array_str));

    memcpy(array_str, input_str.c_str(), input_str.length());

    replace_space(array_str, str_len);

    cout << endl;
    cout << "Result : " << array_str;

    cout << endl;

    return 0;
}