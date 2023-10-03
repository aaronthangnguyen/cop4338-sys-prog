#include <stdio.h>
#include <string.h>
#include<ctype.h>

char *names[] = {"kiwi", "berries", "apple", "orange",
                 "strawberry", "pineapple", "Kiwi", "Berries", "Apple",
                 "Orange", "Strawberry", "Pineapple"};

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void generic_qsort(void *v[], int left, int right,
                   int (*comp)(void *, void *))
{
    int i, last;
    if (left >= right)
        return;                        // base case
    swap(v, left, (left + right) / 2); // pivot
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    generic_qsort(v, left, last - 1, comp);
    generic_qsort(v, last + 1, right, comp);
}

int cmp_desc(void *x_ptr, void *y_ptr)
{
    return -strcmp(x_ptr, y_ptr);
}

int cmp_ignore_case(void *x_ptr, void *y_ptr)
{
    char *x = (char *)x_ptr;
    char *y = (char *)y_ptr;
    while (*x && *y)
    {
        int diff = tolower(*x) - tolower(*y);
        if (diff != 0)
            return diff;
        x++;
        y++;
    }
    return tolower(*x) - tolower(*y);
}

int main(void)
{
    // int (*cmp)(void *, void *) = cmp_desc;
    int (*cmp)(void *, void *) = cmp_ignore_case;
    generic_qsort((void **)names, 0, 11, cmp);
    for (int i = 0; i < 12; i++)
        printf("%s\n", names[i]);
    return 0;
}