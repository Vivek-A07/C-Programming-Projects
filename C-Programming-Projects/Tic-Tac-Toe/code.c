#include <stdio.h>
#include <string.h>

void reset(char arr[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            arr[i][j] = '\0';
        }
    }
}

int check_draw(char arr[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == '\0')
            {
                return 0;
            }
            
        }
    }
    return 1;
}



int check_res(char arr[][3])
{
    if ((arr[0][0] != '\0') && (arr[0][0] == arr[0][1]) && (arr[0][1] == arr[0][2]))
    {
        return 1;
    }
    else if ((arr[1][0] != '\0') && (arr[1][0] == arr[1][1]) && (arr[1][1] == arr[1][2]))
    {
        return 1;
    }
    else if ((arr[2][0] != '\0') && (arr[2][0] == arr[2][1]) && (arr[2][1] == arr[2][2]))
    {
        return 1;
    }
    else if ((arr[0][0] != '\0') && (arr[0][0] == arr[1][0]) && (arr[1][0] == arr[2][0]))
    {
        return 1;
    }
    else if ((arr[0][1] != '\0') && (arr[0][1] == arr[1][1]) && (arr[1][1] == arr[2][1]))
    {
        return 1;
    }
    else if ((arr[0][2] != '\0') && (arr[0][2] == arr[1][2]) && (arr[1][2] == arr[2][2]))
    {
        return 1;
    }
    else if ((arr[0][0] != '\0') && (arr[0][0] == arr[1][1]) && (arr[1][1] == arr[2][2]))
    {
        return 1;
    }
    else if ((arr[0][2] != '\0') && (arr[0][2] == arr[1][1]) && (arr[1][1] == arr[2][0]))
    {
        return 1;
    }

    return 0;
}
void display_board(char arr[][3])
{
    printf("\n");

    printf("\033[36m");
    printf("       ┌───┬───┬───┐\n");
    printf("       │");

    for (int j = 0; j < 3; j++)
    {
        if (arr[0][j] == '\0')
            printf("   ");
        else if (arr[0][j] == 'X')
            printf(" \033[31mX\033[36m ");
        else
            printf(" \033[34mO\033[36m ");

        printf("│");
    }

    printf("\n");
    printf("       ├───┼───┼───┤\n");
    printf("       │");

    for (int j = 0; j < 3; j++)
    {
        if (arr[1][j] == '\0')
            printf("   ");
        else if (arr[1][j] == 'X')
            printf(" \033[31mX\033[36m ");
        else
            printf(" \033[34mO\033[36m ");

        printf("│");
    }

    printf("\n");
    printf("       ├───┼───┼───┤\n");
    printf("       │");

    for (int j = 0; j < 3; j++)
    {
        if (arr[2][j] == '\0')
            printf("   ");
        else if (arr[2][j] == 'X')
            printf(" \033[31mX\033[36m ");
        else
            printf(" \033[34mO\033[36m ");

        printf("│");
    }

    printf("\n");
    printf("       └───┴───┴───┘\033[0m\n");

    printf("\n");
}
int main()
{
    char arr[3][3] = {0};
    int row , col;
    
    int flag = 1;

    char name1[20];
    char name2[20];

    printf("Enter The Player 1 Name:");
    scanf("%[^\n]",name1);

    printf("Enter The Player 2 Name:");
    scanf(" %[^\n]",name2);

    int res = 1;
    int input_validation = 1;
    
    char current_name[20];
    
    int player ;

    printf("Who will go first (Player 1 -> %s / Player 2 -> %s):",name1,name2);
    scanf("%d",&player);

    char current_player;

    if (player == 1)
    {
        current_player = 'X';
        strcpy(current_name, name1);
        
    }
    else if(player == 2)
    {
        current_player = 'O';
        strcpy(current_name, name2);
    }
    else
    {
        printf("Please Enter Valid Number\n");      
    }
      
    do
    {
        
        do
        {
            if (flag)
            {
                display_board(arr);
                flag = 0;
            }
            
            
            printf("%s (%c), enter the row and column (e.g. 0 1): ",current_name, current_player);
            scanf("%d %d",&row, &col);
            
            if ((row >= 0 && row <= 2) && (col >= 0 && col <= 2))
            {
                input_validation = 0;
                
                if(arr[row][col] != 0)
                {
                    printf("Please Enter non used place\n");
                    input_validation = 1;
                }
                else
                {
                    arr[row][col] = current_player;
                    input_validation = 0;
                }
            }
            else
            {
                input_validation = 1;
            }
            
            
            
        } while (input_validation);
        
        
            display_board(arr);
            if(check_res(arr))
            {
                printf("\n\033[1;32m*** %s WINS!!! ***\033[0m\n\n", current_name);
                printf("\033[1;32m*** %s WINS!!! ***\033[0m\n\n", current_name);
                printf("\033[1;32m*** %s WINS!!! ***\033[0m\n\n", current_name);


                printf("\n\nDo you want to play again?(Y->1 / N->0):");
                scanf("%d",&res);

                if (res)
                {
                    reset(arr);
                    player = 1;
                    current_player = 'X';
                    strcpy(current_name, name1);
                    flag = 1;
                }
                
            } 
            else if ((check_draw(arr)))
            {
                printf("\033[33mMatch WithDraw!!!!\033[0m\n");
                
                printf("\n\nDo you want to play again?(Y->1 / N->0):");
                scanf("%d",&res);
                
                if (res)
                {
                    reset(arr);
                    player = 1;
                    current_player = 'X';
                    strcpy(current_name, name1);
                    flag = 1;

                }
            }     
            else
            {
                if (input_validation == 0)
                {
                    if (player == 1)
                    {
                        player = 2;
                        current_player = 'O';
                        strcpy(current_name, name2);
                    }
                    else if(player == 2)
                    {
                        player = 1;
                        current_player = 'X';
                        strcpy(current_name, name1);
                    }
                }
            }
            
        
    } while (res);
    
    
    
    return 0;
}