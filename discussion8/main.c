#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1000
#define MAX_LEN 1000

void print_txt(char *str)
{
    int num = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ',')
        {
            printf("%-25e\t", (double)num);
            num = 0;
        }
        else
        {
            num = num * 10 + (str[i] - '0');
        }
    }
    printf("\n");
}

int main()
{
    char csv[MAX_SIZE][MAX_LEN];

    int i;
    for (i = 0; i < MAX_SIZE; i++)
    {
        if (fgets(csv[i], sizeof(csv[i]), stdin) == NULL)
            break;
        else if (strcmp(csv[i], "") == 0)
            break;

        int len = strlen(csv[i]);
        if (len > 0 && csv[i][len - 1] == '\n')
            csv[i][len - 1] = '\0';
    }

    int size = i;
    for (int j = 0; j < size; j++)
    {
        print_txt(csv[j]);
    }

    return 0;
}