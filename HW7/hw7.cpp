/**
*  Author: 范真瑋
*  Date: Dec. 2, 2016
*  Purpose: test the efficiency of the five sorting algorithms.
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;

void A_insertion_sort(int *arr, int len) {
    int i, j, temp;

	for (i = 1; i < len; i++) {

		temp = arr[i];

		j = i - 1;

		for (; j >= 0 && arr[j] > temp; j--)

			arr[j + 1] = arr[j];

		arr[j + 1] = temp;

	}
}

void ms(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1+ j];
    }

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void B_merge_sort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        B_merge_sort(arr, l, m);
        B_merge_sort(arr, m+1, r);

        ms(arr, l, m, r);
    }
}

void C_quick_sort(int *arr, int start, int end) {
    if (start >= end) return;
	int mid = arr[end];
	int left = start, right = end - 1;
	while (left < right) {
		while (arr[left] < mid && left < right) left++;
		while (arr[right] >= mid && left < right) right--;
		swap(arr[left], arr[right]);
	}
	if (arr[left] >= arr[end])
		swap(arr[left], arr[end]);
	else
		left++;
	C_quick_sort(arr, start, left - 1);
	C_quick_sort(arr, left + 1, end);
}

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int main() {
    fstream file;

    file.open("input.txt", ios::in);
    if (file.fail()) {
        throw "open file error!\n";
    }

    int n, i;
    file >> n;
    int a[n];
    int b[n];

    i = 0;
    long double duration;
    clock_t start, stop;
    while (!file.eof()) {
        file >> a[i];
        ++i;
    }
    file.close();

    memcpy(b, a, sizeof(a));
    start = clock();  //  # of clock ticks since the program begins
    A_insertion_sort(b, n);
    stop = clock();
    duration = ((long double) (stop - start) ) / CLOCKS_PER_SEC;
    cout << duration << endl;
    cout << "---\n";

    memcpy(b, a, sizeof(a));
    start = clock();  //  # of clock ticks since the program begins
    B_merge_sort(b, 0, n-1);
    stop = clock();
    duration = ((double) (stop - start) ) / CLOCKS_PER_SEC;
    cout << duration << endl;
    cout << "---\n";

    memcpy(b, a, sizeof(a));
    start = clock();  //  # of clock ticks since the program begins
    C_quick_sort(b, 0, n-1);
    stop = clock();
    duration = ((double) (stop - start) ) / CLOCKS_PER_SEC;
    cout << duration << endl;
    cout << "---\n";

    memcpy(b, a, sizeof(a));
    start = clock();  //  # of clock ticks since the program begins
    qsort (b, n, sizeof(int), compare);
    stop = clock();
    duration = ((double) (stop - start) ) / CLOCKS_PER_SEC;
    cout << duration << endl;
    cout << "---\n";

    memcpy(b, a, sizeof(a));
    start = clock();  //  # of clock ticks since the program begins
    sort(b, b+n);
    stop = clock();
    duration = ((double) (stop - start) ) / CLOCKS_PER_SEC;
    cout << duration << endl;
    cout << "---\n\n";

    return 0;
}
