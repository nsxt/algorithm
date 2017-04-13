#include <iostream>
#include <iomanip>
using namespace std;

// 이미지를 표현하는 N * N 정방 행렬 클래스
// 이미지의 각 픽셀을 4 바이트를 가지며, RGBA 구분하기 않고 4 바이트 정수형을 취한다.
// 배열을 표시하는 방법은 행우선 방식으로 표현한다. ex) 1 2 3 4 / 5 6 7 8 / 9 10 11 12 / ...
class ImageMatrix {
public:
    ImageMatrix(int n) : m_(nullptr), dimension_(-1)
    {
        m_ = new unsigned int [n * n];
        dimension_ = n;

        _init();
    }

    ~ImageMatrix()
    {
        if (m_) {
            delete[] m_;
        }
    }

public:
    // 매트릭스 배열을 90 도 회전
    void rotate_right()
    {

    }

    void print()
    {
        int index = 0;
        for (int i = 0; i < dimension_; i++) {
            for (int j = 0; j < dimension_; j++) {
                cout << setw(4) << m_[j + (i * dimension_)];
            }
            cout << endl;
        }
    }

private:
    void _init()
    {
        for (int i = 0; i < (dimension_ * dimension_); i++) {
            m_[i] = i + 1;
        }
    }

private:
    unsigned int* m_;
    int dimension_;
};


int main() {

    int dim;
    cout << "Input dimension number of the Square Matrix : ";
    cin >> dim;

    ImageMatrix im(dim);

    cout << endl;
    im.print();
    cout << endl;

    return 0;
}