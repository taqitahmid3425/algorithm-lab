#include <stdio.h>
#include <limits.h>

// Helper function to return the maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Recursive Divide and Conquer function
// Parameters 'largest' and 'second_largest' are pointers to store output values
void find_top_two(int arr[], int low, int high, int *largest, int *second_largest)
{
    // Base Case 1: Single element
    if (low == high)
    {
        *largest = arr[low];
        *second_largest = INT_MIN;
        return;
    }

    // Base Case 2: Two elements
    if (high == low + 1)
    {
        if (arr[low] > arr[high])
        {
            *largest = arr[low];
            *second_largest = arr[high];
        }
        else
        {
            *largest = arr[high];
            *second_largest = arr[low];
        }
        return;
    }

    // Divide
    int mid = low + (high - low) / 2;

    int left_max, left_second;
    int right_max, right_second;

    // Conquer
    find_top_two(arr, low, mid, &left_max, &left_second);
    find_top_two(arr, mid + 1, high, &right_max, &right_second);

    // Combine
    if (left_max > right_max)
    {
        *largest = left_max;
        *second_largest = max(left_second, right_max);
    }
    else
    {
        *largest = right_max;
        *second_largest = max(right_second, left_max);
    }
}

int main()
{
    int arr[] = {12, 35, 1, 10, 34, 1, 89, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (n < 2)
    {
        printf("Array must contain at least two elements.\n");
        return 1;
    }

    int largest, second_largest;

    find_top_two(arr, 0, n - 1, &largest, &second_largest);

    printf("Largest element: %d\n", largest);
    if (second_largest == INT_MIN)
    {
        printf("Second-largest element does not exist.\n");
    }
    else
    {
        printf("Second-largest element: %d\n", second_largest);
    }

    return 0;
}