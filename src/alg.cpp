// Copyright 2025 NNTU-CS
#include <cstdint>
#include "alg.h"

bool checkPrime(uint64_t value) {
    if (value < 2) return false;
    if (value == 2) return true;
    if (value % 2 == 0) return false;
    for (uint64_t i = 3; i * i <= value; i += 2) {
        if (value % i == 0) return false;
    }
    return true;
}

uint64_t nPrime(uint64_t n) {
    if (n == 0) return 0;
    uint64_t count = 0;
    uint64_t candidate = 1;
    while (count < n) {
        ++candidate;
        if (checkPrime(candidate)) {
            ++count;
        }
    }
    return candidate;
}

uint64_t nextPrime(uint64_t value) {
    uint64_t candidate = value + 1;
    while (!checkPrime(candidate)) {
        ++candidate;
    }
    return candidate;
}

uint64_t sumPrime(uint64_t hbound) {
    uint64_t sum = 0;
    for (uint64_t i = 2; i < hbound; ++i) {
        if (checkPrime(i)) {
            sum += i;
        }
    }
    return sum;
}

uint64_t twinPrimes(uint64_t lbound, uint64_t hbound) {
    uint64_t count = 0;
    for (uint64_t i = lbound; i + 2 < hbound; ++i) {
        if (checkPrime(i) && checkPrime(i + 2)) {
            ++count;
        }
    }
    return count;
}

uint64_t collatzMaxValue(uint64_t num) {
    uint64_t maxVal = num;
    uint64_t current = num;
    while (current != 1) {
        if (current % 2 == 0) {
            current = current / 2;
        } else {
            current = 3 * current + 1;
        }
        if (current > maxVal) {
            maxVal = current;
        }
    }
    return maxVal;
}

unsigned int collatzLen(uint64_t num) {
    unsigned int length = 1;
    uint64_t current = num;
    while (current != 1) {
        if (current % 2 == 0) {
            current = current / 2;
        } else {
            current = 3 * current + 1;
        }
        ++length;
    }
    return length;
}

unsigned int seqCollatz(unsigned int *maxlen,
                        uint64_t lbound,
                        uint64_t rbound) {
    unsigned int maxLength = 0;
    uint64_t resultNum = lbound;
    for (uint64_t num = lbound; num <= rbound; ++num) {
        unsigned int len = collatzLen(num);
        if (len > maxLength) {
            maxLength = len;
            resultNum = num;
        }
    }
    *maxlen = maxLength;
    return resultNum;
}

int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                ++count;
            }
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
            int leftVal = arr[left];
            int rightVal = arr[right];
            if (leftVal == rightVal) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftCount = 1;
                while (left + leftCount < right && arr[left + leftCount] == leftVal) {
                    ++leftCount;
                }
                int rightCount = 1;
                while (right - rightCount > left && arr[right - rightCount] == rightVal) {
                    ++rightCount;
                }
                count += leftCount * rightCount;
                left += leftCount;
                right -= rightCount;
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
        if (target < arr[i]) continue;
        int left = i + 1;
        int right = len - 1;
        int firstPos = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= target) {
                if (arr[mid] == target) firstPos = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (firstPos == -1) continue;
        left = firstPos;
        right = len - 1;
        int lastPos = firstPos;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                lastPos = mid;
                left = mid + 1;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        count += (lastPos - firstPos + 1);
    }
    return count;
}
