// Copyright 2025 NNTU-CS
#include <algorithm>

int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                ++count;
                // Пропускаем дубликаты arr[j]
                while (j + 1 < len && arr[j + 1] == arr[j]) {
                    ++j;
                }
            }
        }
        // Пропускаем дубликаты arr[i]
        while (i + 1 < len && arr[i + 1] == arr[i]) {
            ++i;
        }
    }
    return count;
}

int countPairs2(int *arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftVal = arr[left];
                int rightVal = arr[right];
                int leftCount = 0;
                int rightCount = 0;
                while (left < right && arr[left] == leftVal) {
                    ++leftCount;
                    ++left;
                }
                while (left <= right && arr[right] == rightVal) {
                    ++rightCount;
                    --right;
                }
                count += leftCount * rightCount;
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
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int countPairs3(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        if (target < arr[i]) {
            continue;
        }
        int first = binarySearch(arr, i + 1, len - 1, target);
        if (first != -1) {
            int last = first;
            while (last + 1 < len && arr[last + 1] == target) {
                ++last;
            }
            count += (last - first + 1);
            i = last;
        }
    }
    return count;
}
