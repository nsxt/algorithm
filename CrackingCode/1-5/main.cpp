#include <iostream>
#include <string>
using namespace std;

// ex) the string 'aabcccccaaa' would become 'a2b1c5a3'

// 문자열내에서 문자가 연속으로 반복하는 횟수를 조사하여 압축된 전체 문자열의 길이를 계산
// 전략 : 연속된 문자와 그렇지 않은 문자 모두 2 바이트를 가지게 되므로 (a1, b1 ...) 여기에 착안해서 길이를 계산
// 연속된 문자가 최대 9 개 (한자리수) 이하라고 가정한다.
int count_repeated_char(const char* str, int len)
{
    int compressed_len = 0;
    char prev_char = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != prev_char && str[i] != '\0') {
            compressed_len += 2;
            prev_char = str[i];
        }
    }

    return compressed_len + 1;
}

// 압축된 결과를 저장할 버퍼도 Caller 에서 제공되어야 하며, 본 알고리즘에서는 이와 관려된 예외처리는 하지 않는다.
// 연속된 문자가 최대 9 개 (한자리수) 이하라고 가정한다.
// Caller 에서 buff 메모리를 직접 해제 해 주어야 한다.
void compress(const char* src_str, int src_len, char* buff, int& buff_len)
{
    char prev_char = 0;
    int buff_index = 0;

    for (int i = 0; i < src_len; i++) {

        if (src_str[i] != prev_char && src_str[i] != '\0') {

            buff[buff_index] = src_str[i];
            buff[buff_index + 1] = '1';
            prev_char = src_str[i];

            buff_index += 2;

        } else if (src_str[i] == prev_char) {

            buff[buff_index - 1] += 1;
        }
    }

    buff[buff_index] = '\0';
}

const char* do_compress(const char* str, int len)
{
    int buff_len = count_repeated_char(str, len);

    char* buff;

    if (buff_len >= len) {
        buff = new char[len];
        memcpy(buff, str, sizeof(char) * len);

    } else {
        buff = new char[buff_len];
        compress(str, len, buff, buff_len);
    }

    return buff;
}

int main() {

    string input_str;
    cout << "Input string : ";
    getline(cin, input_str);

    const char* compressed_str = do_compress(input_str.c_str(), input_str.length() + 1);
    cout << "Result : " << compressed_str << endl;

    delete[] compressed_str;

    return 0;
}