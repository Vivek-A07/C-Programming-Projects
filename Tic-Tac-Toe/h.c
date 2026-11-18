#include <stdio.h>

int main()
{
    int arr[3][3] = {0};

    void display_board(char arr[][3])
{
    printf("\n");
    printf("       ┌───┬───┬───┐\n");

    for (int i = 0; i < 3; i++)
    {
        printf("       │");

        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == '\0')
            {
                printf("   │");
            }
            else
            {
                printf(" %c │", arr[i][j]);
            }
        }

        printf("\n");

        if (i < 2)
        {
            printf("       ├───┼───┼───┤\n");
        }
    }

    printf("       └───┴───┴───┘\n");
    printf("\n");
}
    
    return 0;
}