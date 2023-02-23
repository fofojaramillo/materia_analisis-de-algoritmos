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

void merge(vector<int> &arr, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        rightArr[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

int main() {
    ofstream file;
    char type;
    string fileName;
    for (int n : {10, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000}) {
        for (char caseType : {'A', 'D', 'R'}) {
            vector<int> arr = lists(caseType, n);
            auto start = chrono::high_resolution_clock::now();
            mergeSort(arr, 0, n - 1);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::duration<double, std::milli>>(end - start);

            switch (caseType) {
                case 'A':
                    fileName = "merge-best.csv";
                    break;
                case 'D':
                    fileName = "merge-worst.csv";
                    break;
                case 'R':
                    fileName = "merge-mean.csv";
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

