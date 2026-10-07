#include <stdio.h>

#define MAX 100

typedef struct
{
    int weight;
    int id;
} Package;

void display(Package a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d(P%d) ", a[i].weight, a[i].id);

    printf("\n");
}

/* ---------- MERGE SORT ---------- */

void merge(Package a[], int low, int mid, int high)
{
    Package temp[MAX];

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (a[i].weight <= a[j].weight)
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low; i <= high; i++)
        a[i] = temp[i];

    printf("After merge: ");
    display(a, high + 1);
}

void mergeSort(Package a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        merge(a, low, mid, high);
    }
}

/* ---------- QUICK SORT ---------- */

int partition(Package a[], int low, int high)
{
    int pivot = a[high].weight;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j].weight <= pivot)
        {
            i++;

            Package temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    Package temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    printf("Pivot = %d: ", pivot);
    display(a, high + 1);

    return i + 1;
}

void quickSort(Package a[], int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

/* ---------- MAIN ---------- */

int main()
{
    Package packages[MAX];
    Package mergeArray[MAX];
    Package quickArray[MAX];

    int n;

    printf("Enter number of packages: ");
    scanf("%d", &n);

    printf("\nEnter package weights:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Weight of P%d: ", i + 1);
        scanf("%d", &packages[i].weight);

        packages[i].id = i + 1;
    }

    /* Copy original data */
    for (int i = 0; i < n; i++)
    {
        mergeArray[i] = packages[i];
        quickArray[i] = packages[i];
    }

    printf("\nOriginal order:\n");
    display(packages, n);

    /* ---------- MERGE SORT ---------- */

    printf("\n========== MERGE SORT ==========\n");

    mergeSort(mergeArray, 0, n - 1);

    printf("\nFinal Merge Sort:\n");
    display(mergeArray, n);

    /* ---------- QUICK SORT ---------- */

    printf("\n========== QUICK SORT ==========\n");

    quickSort(quickArray, 0, n - 1);

    printf("\nFinal Quick Sort:\n");
    display(quickArray, n);

    return 0;
}