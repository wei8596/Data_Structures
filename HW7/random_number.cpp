#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int main() {
    fstream file;

    file.open("input.txt", ios::out);
    if (file.fail()) {
        throw "open file error!\n";
    }
    const int N = 100;
    file << N;

    int num;
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        num = rand();
        file << endl << num;
    }
    file.close();

    return 0;
}
