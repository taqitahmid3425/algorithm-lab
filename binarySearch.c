#include <stdio.h>

int binarySearch(int arr[], int left, int right, int target)
{
    if (left == right)
    {
        return -1;
    }

    int mid = left + (right - left) / 2;
    if (target == arr[mid])
    {
        return mid;
    }
    else if (target < arr[mid])
    {
        return binarySearch(arr, left, mid, target);
    }
    else
    {
        return binarySearch(arr, mid + 1, right, target);
    }
}

int main()
{
    int arr[] = {34, 67, 31, 46, 68, 74, 48};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("index: %d\n", binarySearch(arr, 0, size - 1, 46));
    return 0;
}