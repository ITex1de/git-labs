#include <iostream>
#include <windows.h>
#include <set>
#include <vector>
using namespace std;

template <typename T>
class Matrix {
    int i, j;
    vector<vector<T>> matrix;
    public:
    Matrix(int i, int j) : i(i), j(j), matrix(i, vector<T>(j)) {}

    void set_values() {
        cout << "������ �������: " << i << "x" << j << "\n";
        for (int row = 0; row < i; ++row) {
            cout << "\n���� �������� ������ ��� �������� " << row << "\n";
            for (int cols = 0; cols < j; ++cols) {
                int size;
                cout << "������� ������ �������� ������� �� ������� " << "[" << row << "]" << "[" << cols << "]: ";
                cin >> size;
                while (size <= 0) {
                    cout << "������� �������� ��������.\n������� ������: ";
                    cin >> size;
                }
                cout << "Matrix[" << row << "][" << cols << "]\n";
                for (int k = 0; k < size; ++k) {
                    char ch;
                    cout << "������� �������� �������� " << k + 1 << ": ";
                    cin >> ch;
                    matrix[row][cols].insert(ch);
                }
            }
        }
    }

    void Print() {
        for (int row = 0; row < i; ++row) {
            for (int col = 0; col < j; ++col) {
                cout << "{";
                bool first = true;
                for (const auto &it : matrix[row][col]) {
                    if (!first) cout << ", ";
                    cout << it;
                    first = false;
                }
                cout << "}\t";
            }
            cout << "\n";
        }
    }
    
    friend Matrix<vector<char>> operator+(char x, const Matrix<vector<char>>& other);
    friend Matrix<set<char>> operator+(char x, const Matrix<set<char>>& other);
};

template <>
void Matrix<vector<char>>::set_values() {
    cout << "������ �������: " << i << "x" << j << "\n";
    for (int row = 0; row < i; ++row) {
        cout << "\n���� �������� ������ ��� �������� " << row << "\n";
        for (int cols = 0; cols < j; ++cols) {
            string s;
            cout << "������� ������: \n";
            cin >> s;
            for (auto &it : s) {
                matrix[row][cols].push_back(it);
            }
            cout << "\n";
        }
    }
}

Matrix<vector<char>> operator+(char x, const Matrix<vector<char>>& other) {
    Matrix<vector<char>> buf(other.i, other.j);
        for (int i = 0; i < other.i; ++i) {
            for (int j = 0; j < other.j; ++j) {
                buf.matrix[i][j] = other.matrix[i][j];
                buf.matrix[i][j].insert(buf.matrix[i][j].begin(), x);
            }
        }
    return buf;
}

Matrix<set<char>> operator+(char x, const Matrix<set<char>>& other) {
    Matrix<set<char>> buf(other.i, other.j);
    for (int i = 0; i < other.i; ++i) {
        for (int j = 0; j < other.j; ++j) {
            buf.matrix[i][j] = other.matrix[i][j];
            buf.matrix[i][j].insert(x);
        }
    }
    return buf;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int a, b, type;
    char b_;

    cout << "������������ ������ �4 - ����������������� ������\n";
    cout << "����� �������� �������.\n1 - ���������\n2 - ������ ��������\n";
    cin >> type;
    while (type != 1 && type != 2) {
        cout << "������� �������� ��������.\n������� ������: ";
        cin >> type;
    }
    cout << "������� ������ �������(2 �������� ����� ������): ";
    cin >> a >> b;
    while (a <= 0 || b <= 0) {
        cout << "�������� ��������.\n������� ������: ";
        cin >> a >> b;
    }
    cin.ignore();
    switch (type) {
        case 1: {
            Matrix<set<char>> A(a, b);
            A.set_values();
            cout << "������� A:\n";
            A.Print();
            Matrix<set<char>> C(a, b);
            cout << "������� ������ b ��� ��������� C = b + A.\n���� �������: ";
            cin >> b_;
            C = b_ + A;
            cout << "������� C(��������� ��������� b + A):\n";
            C.Print();
            break;
        }
        case 2: {
            Matrix<vector<char>> A(a, b);
            A.set_values();
            cout << "������� A:\n";
            A.Print();
            Matrix<vector<char>> C(a, b);
            cout << "������� ������ b ��� ��������� C = b + A.\n���� �������: ";
            cin >> b_;
            C = b_ + A;
            cout << "������� C(��������� ��������� b + A):\n";
            C.Print();
            break;
        }
    }
}