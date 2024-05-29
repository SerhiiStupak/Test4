#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <fstream>

using namespace std;

void finputMatrix(int** Matrix, int N, int M, istream& fin) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fin >> Matrix[i][j];
        }
    }
}

void clearMatrix(int** Matrix, int M) {
    for (int i = 0; i < M; ++i) {
        delete[] Matrix[i];
    }
    delete[] Matrix;
}

bool is_emptyf(ifstream& pFile) {
    return pFile.peek() == ifstream::traits_type::eof();
}

void findSaddlePoints(int** Matrix, int N, int M, ostream& fout) {
    for (int i = 0; i < N; ++i) {
        int rowMin = Matrix[i][0];
        int colIndex = 0;
        for (int j = 1; j < M; ++j) {
            if (Matrix[i][j] < rowMin) {
                rowMin = Matrix[i][j];
                colIndex = j;
            }
        }

        bool isSaddlePoint = true;
        for (int k = 0; k < N; ++k) {
            if (Matrix[k][colIndex] > rowMin) {
                isSaddlePoint = false;
                break;
            }
        }

        if (isSaddlePoint) {
            fout << "Сідлова точка знаходиться в [" << i + 1 << ", " << colIndex + 1 << "] зі значенням: " << rowMin << endl;
        }
    }
}

int findMaxRepeated(int** Matrix, int N, int M) { 
    int** frequencies = new int* [N];
    for (int i = 0; i < N; i++) {
        frequencies[i] = new int[M];
    }

    int count = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {

            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < M; ++y) {
                    if (Matrix[i][j] == Matrix[x][y]) {
                        count++;
                    }

                }
            }
            frequencies[i][j] = count;
            count = 0;
        }
    }

    int maxRepeated = Matrix[0][0];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (frequencies[i][j] > 1 && Matrix[i][j] > maxRepeated) {
                maxRepeated = Matrix[i][j];
            }
        }
    }

    clearMatrix(frequencies, N);

    return maxRepeated;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N, M;
    while (true) {
        char inputFileName[101], outputFileName[101];
        cout << "Введіть назву файлу з якого треба взяти дані: ";
        cin >> inputFileName;
        cin.ignore();
        ifstream fin(inputFileName);

        if (!fin.is_open()) {
            cout << "\nНе вдалося відкрити файл під назвою: " << inputFileName << endl;
            system("pause");
            return 0;
        }

        cout << "\nВведіть кількіссть стовпців матриці N: ";
        cin >> N;
        cout << "\nВведіть кількіссть рядків матриці M: ";
        cin >> M;

        int** Matrix = new int* [N];
        for (int i = 0; i < N; i++) {
            Matrix[i] = new int[M];
        }

        cout << "\nВведіть назву файлу в який записати результати: ";
        cin >> outputFileName;

        ofstream fout(outputFileName);
        if (!fout.is_open()) {
            cout << "\nНе вдалося відкрити файл під назвою: " << outputFileName << endl;
            system("pause");
            return 0;
        }
        if (is_emptyf(fin)) {
            cout << "Ви надали пустий файл\n";
            system("pause");
            return 0;
        }

        finputMatrix(Matrix, N, M, fin);

        if (fin.fail()) {
            cout << "Ви ввели некоректні дані, або замало даних\n";
            system("pause");
            return 0;
        }

        findSaddlePoints(Matrix, N, M, fout);

        fout << endl << endl << "Максимальне значення матриці, що повторюється: " << findMaxRepeated(Matrix, N, M);

        clearMatrix(Matrix, N);

        cin.clear();
        cin.get();
        fin.clear();
        fin.get();

        bool restart;
        cout << "Якщо хочете завершити програму натисніть 0, якщо продовщити 1: ";
        cin >> restart;
        if (!restart) {
            return 0;
        }

        cout << endl;
        system("pause");
        system("cls");
    }
}
