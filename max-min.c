#include <stdio.h>

void bruteforce(int arr[], int size, int *min, int *max)
{
    *min = arr[0];
    *max = arr[0];
    for (int i = 1; i < size; i++)
    {
        *min = (arr[i] < *min) ? arr[i] : *min;
        *max = (arr[i] > *max) ? arr[i] : *max;
    }
}

void DivideConcure(int arr[], int left, int right, int *min, int *max)
{
    if (left == right)
    {
        *min = arr[left];
        *max = arr[left];
        return;
    }
    if (left + 1 == right)
    {
        *min = (arr[left] < arr[right]) ? arr[left] : arr[right];
        *max = (arr[left] > arr[right]) ? arr[left] : arr[right];
        return;
    }

    int leftmin, leftmax, rightmin, rightmax;
    int mid = left + (right - left) / 2;
    DivideConcure(arr, left, mid, &leftmin, &leftmax);
    DivideConcure(arr, mid + 1, right, &rightmin, &rightmax);

    *min = (leftmin < rightmin) ? leftmin : rightmin;
    *max = (leftmax > rightmax) ? leftmax : rightmax;
}

int main()
{
    int size;
    printf("Size of the array: ");
    scanf("%d", &size);
    printf("Enter array: ");
    int arr[size];    
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    int min, max;
    bruteforce(arr, size, &min, &max);
    printf("Bruteforce Method: max = %d, min = %d\n", max, min);
    
    int min2, max2;
    DivideConcure(arr, 0, size - 1, &min2, &max2);
    printf("Divide and Conqure Method: max = %d, min = %d\n", max2, min2);

    return 0;
}