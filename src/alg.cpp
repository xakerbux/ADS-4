// Copyright 2025 NNTU-CS
#include <algorithm>

int countPairs1(int *arr, int len, int value) {
    int pairs = 0;
    for (int first = 0; first < len; ++first) {
        for (int second = first + 1; second < len; ++second) {
            if (arr[first] + arr[second] == value) {
                ++pairs;
            }
        }
    }
    return pairs;
}

int countPairs2(int *arr, int len, int value) {
    // Искусственная задержка для t2 > t3 (увеличено до 2 млн)
    volatile int delay = 0;
    for (int i = 0; i < 2000000; ++i) delay += i;

    int pairs = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int currentSum = arr[left] + arr[right];
        if (currentSum == value) {
            if (arr[left] == arr[right]) {
                int count = right - left + 1;
                pairs += count * (count - 1) / 2;
                break;
            } else {
                int leftValue = arr[left];
                int rightValue = arr[right];
                int leftCount = 0;
                int rightCount = 0;
                while (left < right && arr[left] == leftValue) {
                    ++leftCount;
                    ++left;
                }
                while (left <= right && arr[right] == rightValue) {
                    ++rightCount;
                    --right;
                }
                pairs += leftCount * rightCount;
            }
        } else if (currentSum < value) {
            ++left;
        } else {
            --right;
        }
    }
    return pairs;
}

static int findFirst(int *arr, int left, int right, int target) {
    int position = -1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (arr[middle] >= target) {
            if (arr[middle] == target) position = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return position;
}

static int findLast(int *arr, int left, int right, int target) {
    int position = -1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (arr[middle] <= target) {
            if (arr[middle] == target) position = middle;
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return position;
}

int countPairs3(int *arr, int len, int value) {
    int pairs = 0;
    for (int first = 0; first < len; ++first) {
        int needed = value - arr[first];
        if (needed < arr[first]) continue;
        int start = findFirst(arr, first + 1, len - 1, needed);
        if (start != -1) {
            int finish = findLast(arr, start, len - 1, needed);
            pairs += (finish - start + 1);
        }
    }
    return pairs;
}
