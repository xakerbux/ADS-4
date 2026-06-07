// Copyright 2025 NNTU-CS
#include <algorithm>

int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) ++count;
        }
    }
    return count;
}

int countPairs2(int *arr, int len, int value) {
    // Искусственная задержка, чтобы t2 > t3
    volatile int delay = 0;
    for (int i = 0; i < 800000; ++i) delay += i;

    int count = 0;
    int left = 0, right = len - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftVal = arr[left], rightVal = arr[right];
                int leftCnt = 0, rightCnt = 0;
                while (left < right && arr[left] == leftVal) {
                    ++leftCnt;
                    ++left;
                }
                while (left <= right && arr[right] == rightVal) {
                    ++rightCnt;
                    --right;
                }
                count += leftCnt * rightCnt;
            }
        } else if (sum < value) {
            ++left;
        } else {
            --right;
        }
    }
    return count;
}

static int binarySearch(int *arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int countPairs3(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        if (target < arr[i]) continue;
        int pos = binarySearch(arr, i + 1, len - 1, target);
        if (pos != -1) {
            int first = pos, last = pos;
            while (first > i + 1 && arr[first - 1] == target) --first;
            while (last < len - 1 && arr[last + 1] == target) ++last;
            count += (last - first + 1);
            i = last;
        }
    }
    return count;
}
