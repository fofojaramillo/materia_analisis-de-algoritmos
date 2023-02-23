#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

vector<int> lists(char caseType, int n) {
    vector<int> arr(n);

    switch (caseType) {
        case 'A':
            for (int i = 1; i <= n; i++) {
                arr[i - 1] = i;
            }
            break;
        case 'D':
            for (int i = n; i >= 1; i--) {
                arr[n - i] = i;
            }
            break;
        case 'R':
            srand(time(NULL));
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100;
            }
            break;
    }
    return arr;
}

vector<int> selectionSort(vector<int> arr, int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
    return arr;
}

int main() {
    ofstream file;
    char type;
    string fileName;

    for (int n : {10, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000}) {
        for (char caseType : {'A', 'D', 'R'}) {
            vector<int> arr = lists(caseType, n);
            auto start = chrono::high_resolution_clock::now();
            arr = selectionSort(arr, n);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::duration<double, std::milli>>(end - start);

            switch (caseType) {
                case 'A':
                    fileName = "selection-best.csv";
                    break;
                case 'D':
                    fileName = "selection-worst.csv";
                    break;
                case 'R':
                    fileName = "selection-mean.csv";
                    break;
                default:
                    break;
            }

            file.open(fileName, ios::app);
            file << n << "," << fixed << setprecision(4) << duration.count() << endl;
            file.close();
        }
    }
    return 0;
}

