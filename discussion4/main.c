
#include <stdio.h>

int count_func(int rows, int cols, int arr[rows][cols])
{
    int count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (arr[i][j] % 6 == 0 && arr[i][j] % 5 != 0)
                count += 1;
    return count;
}

int count_func2(int rows, int cols, int arr[rows][cols])
{
    int count = 0;
    for (int i = 0; i < rows; i++)
    {
        if (i + 1 % 5 == 0) // just skip row value divisible by 5
            continue;
        else if (i + 1 % 6 == 0)
        {
            count += (cols - cols / 5); // in row value divisible by 6, take all cols except ones' value divisible by 5
            continue;
        }

        for (int j = 0; j < cols; j++)
        {
            if (j + 1 % 5 == 0) // just skip col value divisible by 5
                continue;
            if (arr[i][j] % 6 == 0 && arr[i][j] % 5 != 0)
                count += 1;
        }
    }
    return count;
}

int main(void)
{
    int array[40][50];

    for (int i = 0; i < 40; i++)
        for (int j = 0; j < 50; j++)
            array[i][j] = (i + 1) * (j + 1);

    printf("%d\n", count_func(40, 50, array));
    printf("%d\n", count_func2(40, 50, array));

    return 0;
}
