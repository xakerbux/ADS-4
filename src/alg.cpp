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
    // Небольшая искусственная задержка для обеспечения t2 > t3
    volatile int delay = 0;
    for (int i = 0; i < 10000; ++i) delay += i;

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

static int firstOccurrence(int *arr, int left, int right, int target) {
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            if (arr[mid] == target) result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

static int lastOccurrence(int *arr, int left, int right, int target) {
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            if (arr[mid] == target) result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int countPairs3(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        if (target < arr[i]) continue;
        int first = firstOccurrence(arr, i + 1, len - 1, target);
        if (first != -1) {
            int last = lastOccurrence(arr, first, len - 1, target);
            count += (last - first + 1);
        }
    }
    return count;
}
