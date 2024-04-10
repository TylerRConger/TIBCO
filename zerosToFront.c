#include <stdio.h>
#include <stdlib.h>

// O(N) time complexity

// Take in a list and swap the zeros so the are in the front of the list
// Also known is the length of the list
void zerosToTheFront(int *array, int count)
{
    // Index representing the current swap position
    int curFront = 0;

    for (int i = 0; i < count; i++)
    {
        // Found a zero need to swap it
        if (array[i] == 0)
        {
            // Swap the values w/o a temp because we know one of them is a zero
            array[i] = array[curFront];
            array[curFront] = 0;

            // Increment the new position for added zeros
            curFront++;
        }
    }
}

int main(int argc, char** argv)
{
    printf("\n\n\n\n");

    // Test case 1: No zeros
    int arr1[] = {1, 2, 3, 4, 5};
    int count1 = sizeof(arr1) / sizeof(arr1[0]);
    zerosToTheFront(arr1, count1);
    printf("Result Test case 1: ");
    for (int i = 0; i < count1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // Test case 2: All zeros
    int arr2[] = {0, 0, 0, 0, 0};
    int count2 = sizeof(arr2) / sizeof(arr2[0]);
    zerosToTheFront(arr2, count2);
    printf("Result Test case 2: ");
    for (int i = 0; i < count2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    // Test case 3: Mixed values
    int arr3[] = {1, 0, 3, 0, 5};
    int count3 = sizeof(arr3) / sizeof(arr3[0]);
    zerosToTheFront(arr3, count3);
    printf("Result Test case 3: ");
    for (int i = 0; i < count3; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");

    // Test case 4: Single zero
    int arr4[] = {0};
    int count4 = sizeof(arr4) / sizeof(arr4[0]);
    zerosToTheFront(arr4, count4);
    printf("Result Test case 4: ");
    for (int i = 0; i < count4; i++) {
        printf("%d ", arr4[i]);
    }
    printf("\n");

    // Test case 5: Provided test
    int arr5[] = {1, 3, 6, 0, -1, 2, 3, 0};
    int count5 = sizeof(arr5) / sizeof(arr5[0]);
    zerosToTheFront(arr5, count5);
    printf("Result Test case 5: ");
    for (int i = 0; i < count5; i++) {
        printf("%d ", arr5[i]);
    }
    printf("\n");

    return 0;
}
