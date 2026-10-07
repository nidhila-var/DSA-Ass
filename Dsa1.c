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

/* ---------- STABLE MERGE SORT ---------- */

void merge(Package a[], int low, int mid, int high)
{
    Package temp[MAX];

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        /*
         * If weights are equal, take the element
         * from the left side first.
         * This preserves the original order.
         */
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

/* ---------- STABLE QUICK SORT ---------- */

int compare(Package a, Package b)
{
    if (a.weight < b.weight)
        return -1;

    if (a.weight > b.weight)
        return 1;

    /* Same weight:
       compare Package IDs to preserve original order */
    if (a.id < b.id)
        return -1;

    if (a.id > b.id)
        return 1;

    return 0;
}

int partition(Package a[], int low, int high)
{
    Package pivot = a[high];

    Package temp[MAX];
    int k = low;

    /*
     * Stable partition:
     * copy elements smaller than pivot first,
     * then elements greater than or equal to pivot.
     * Package ID is used when weights are equal.
     */

    for (int i = low; i < high; i++)
    {
        if (compare(a[i], pivot) <= 0)
        {
            temp[k++] = a[i];
        }
    }

    temp[k++] = pivot;

    for (int i = low; i <= high; i++)
        a[i] = temp[i];

    return k - 1;
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

    /* Copy original array */
    for (int i = 0; i < n; i++)
    {
        mergeArray[i] = packages[i];
        quickArray[i] = packages[i];
    }

    printf("\nOriginal order:\n");
    display(packages, n);

    /* ---------- STABLE MERGE SORT ---------- */

    printf("\n========== STABLE MERGE SORT ==========\n");

    mergeSort(mergeArray, 0, n - 1);

    printf("Sorted order:\n");
    display(mergeArray, n);

    /* ---------- STABLE QUICK SORT ---------- */

    printf("\n========== STABLE QUICK SORT ==========\n");

    quickSort(quickArray, 0, n - 1);

    printf("Sorted order:\n");
    display(quickArray, n);

    return 0;
}