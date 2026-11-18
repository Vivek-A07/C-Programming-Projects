#include <stdio.h>
#include <string.h>

struct Student
{
    int id;
    char name[20];
    char add[60];
    char mob[20];
    char gmail[30];
};


void Sort_Array_by_Id(struct Student arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j].id > arr[j + 1].id)
            {
                struct Student temp;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
            }
        }
    }
}

void Add_Student_Info(struct Student arr[], int *size)
{
    int id_flag = 0;

    do
    {
        id_flag = 0;

        printf("\tEnter the Student Id: ");

        int id;
        scanf("%d", &id);

        int i;

        for (i = 0; i < *size; i++)
        {
            if (id == arr[i].id)
            {
                id_flag = 1;
                break;
            }
        }

        if (id_flag == 1)
        {
            printf("\tPlease ReEnter the id\n");
        }
        else
        {
            arr[*size].id = id;
        }

    } while (id_flag);

    getchar();

    printf("\tEnter the Name: ");
    scanf("%[^\n]", arr[*size].name);

    getchar();

    printf("\tEnter the Add: ");
    scanf("%[^\n]", arr[*size].add);

    getchar();

    int mob_flag = 1;

do
{
    mob_flag = 0;

    printf("\tEnter the Mobile Number: ");
    scanf("%[^\n]", arr[*size].mob);

    getchar();  

    int ind = 0;

    while (arr[*size].mob[ind])
    {
        if (arr[*size].mob[ind] < '0' || arr[*size].mob[ind] > '9')
        {
            mob_flag = 1;   
            break;
        }

        ind++;
    }

    if (ind != 10)
    {
        mob_flag = 1;      
    }

    if (mob_flag == 1)
    {
        printf("\tReEnter the Mobile Number\n");
    }

} while (mob_flag);


int gmail_flag = 1;
int username_flag = 1;

do
{
    gmail_flag = 0;
    
    printf("\tEnter Gmail: ");
    scanf("%[^\n]", arr[*size].gmail);

    getchar();
    
    int gmail_size = strlen(arr[*size].gmail); 
    char domain[] = "@gmail.com"; 
    int count_domain = 0;
    int domain_idx = gmail_size - 10; 
    username_flag = 0;

    if (gmail_size < 10 || domain_idx == 0)
    {
        gmail_flag = 1;
    }
    else
    {
        for (int i = 0; i < domain_idx ; i++)
        {
            if (arr[*size].gmail[0] == '.' || arr[*size].gmail[0] == '_')
            {
                username_flag = 1;
                break;
            }

            else if (arr[*size].gmail[domain_idx - 1] == '.' ||
                    arr[*size].gmail[domain_idx - 1] == '_')
            {
                username_flag = 1;
                break;
            }

            if ((arr[*size].gmail[i] == '.' || arr[*size].gmail[i] == '_') &&
                (arr[*size].gmail[i + 1] == '.' || arr[*size].gmail[i + 1] == '_'))
            {
                username_flag = 1;
                break;
            }

            if ((arr[*size].gmail[i] >= 'a' && arr[*size].gmail[i] <= 'z') || arr[*size].gmail[i] == '.' || arr[*size].gmail[i] == '_' || (arr[*size].gmail[i] >= 'A' && arr[*size].gmail[i] <= 'Z') || (arr[*size].gmail[i] >= '0' && arr[*size].gmail[i] <= '9'))
            {
                
                
            }
            else
            {
                username_flag = 1;
                break;
            }
            
        }
        
        while (arr[*size].gmail[domain_idx] )
        {
            if (arr[*size].gmail[domain_idx] != domain[count_domain])
            {
                gmail_flag = 1;
                break;
            }
            count_domain++;
            domain_idx++;
        }
        
        if (count_domain != 10)
        {
            gmail_flag = 1;
        }
    }
    
    if (gmail_flag == 1 || username_flag == 1)
    {
        printf("\tReEnter the Gmail\n");
    }
    
} while (gmail_flag || username_flag);
(*size)++;
}


void Display_Student_Info(struct Student arr[], int s)
{
    if (s == 0)
    {
        printf("\t\t\tNo Student Record:::\n");
        return;
    }

    for (int i = 0; i < s; i++)
    {
        printf("------------------------------------------------------------\n");

        printf("%d %s %s %s %s\n",
               arr[i].id,
               arr[i].name,
               arr[i].add,
               arr[i].mob,
               arr[i].gmail);
    }

    printf("------------------------------------------------------------\n");
}

void Search_Student(struct Student arr[], int s)
{
    int id;

    printf("Enter Your Id: ");
    scanf("%d", &id);

    int flag = 0;
    int i;

    for (i = 0; i < s; i++)
    {
        if (id == arr[i].id)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        printf("\tStudent Data Found\n");

        printf("%d %s %s %s\n",
               arr[i].id,
               arr[i].name,
               arr[i].add,
               arr[i].mob);
    }
    else
    {
        printf("\tStudent Data Not Found\n");
    }
}

void Update_Student_Info(struct Student arr[], int size)
{
    int update_id;
    int update_flag = 0;
    int index = -1;

    printf("Enter the id no to update: ");
    scanf("%d",&update_id);

    for (int i = 0; i < size; i++)
    {
        if (update_id == arr[i].id)
        {
            update_flag = 1;
            index = i;
            break;
        }
    }

    if (update_flag == 0)
    {
        printf("\tStudent ID Not Found\n");
        return;
    }

    int update_opt;

    printf("What do you want to update:\n");
    printf("1. Name\n");
    printf("2. Add\n");
    printf("3. Mob\n");
    printf("4. Gmail\n");
    printf("Enter your option: ");
    scanf("%d", &update_opt);

    getchar();


    switch (update_opt)
    {
        case 1:
            printf("\tEnter the Name: ");
            scanf("%[^\n]", arr[index].name);
            getchar();
            break;

        case 2:
            printf("\tEnter the Add: ");
            scanf("%[^\n]", arr[index].add);
            break;

        case 3:
       
            int mob_flag = 1;

            do
            {
                mob_flag = 0;

                printf("\tEnter the Mobile Number: ");
                scanf("%[^\n]", arr[index].mob);

                getchar();  

                int ind = 0;

                while (arr[index].mob[ind])
                {
                    if (arr[index].mob[ind] < '0' ||
                        arr[index].mob[ind] > '9')
                    {
                        mob_flag = 1;   
                        break;
                    }

                    ind++;
                }

                if (ind != 10)
                {
                    mob_flag = 1;      
                }

                if (mob_flag == 1)
                {
                    printf("\tReEnter the Mobile Number\n");
                }

            } while (mob_flag);
    
        case 4:

            int gmail_flag = 1;
            int username_flag = 1;

            do
            {
                gmail_flag = 0;
                
                printf("\tEnter Gmail: ");
                scanf("%[^\n]", arr[index].gmail);

                getchar();
                
                int gmail_size = strlen(arr[index].gmail); 
                char domain[] = "@gmail.com"; 
                int count_domain = 0;
                int domain_idx = gmail_size - 10; 
                username_flag = 0;

                if (gmail_size < 10 || domain_idx == 0)
                {
                    gmail_flag = 1;
                }
                else
                {
                    for (int i = 0; i < domain_idx ; i++)
                    {
                        if (arr[index].gmail[0] == '.' || arr[index].gmail[0] == '_')
                        {
                            username_flag = 1;
                            break;
                        }

                        else if (arr[index].gmail[domain_idx - 1] == '.' ||
                                arr[index].gmail[domain_idx - 1] == '_')
                        {
                            username_flag = 1;
                            break;
                        }

                        if ((arr[index].gmail[i] == '.' || arr[index].gmail[i] == '_') &&
                            (arr[index].gmail[i + 1] == '.' || arr[index].gmail[i + 1] == '_'))
                        {
                            username_flag = 1;
                            break;
                        }

                        if ((arr[index].gmail[i] >= 'a' && arr[index].gmail[i] <= 'z') || arr[index].gmail[i] == '.' || arr[index].gmail[i] == '_' || (arr[index].gmail[i] >= 'A' && arr[index].gmail[i] <= 'Z') || (arr[index].gmail[i] >= '0' && arr[index].gmail[i] <= '9'))
                        {
                            
                            
                        }
                        else
                        {
                            username_flag = 1;
                            break;
                        }
                        
                    }
                    
                    while (arr[index].gmail[domain_idx] )
                    {
                        if (arr[index].gmail[domain_idx] != domain[count_domain])
                        {
                            gmail_flag = 1;
                            break;
                        }
                        count_domain++;
                        domain_idx++;
                    }
                    
                    if (count_domain != 10)
                    {
                        gmail_flag = 1;
                    }
                }
                
                if (gmail_flag == 1 || username_flag == 1)
                {
                    printf("\tReEnter the Gmail\n");
                }
                
            } while (gmail_flag || username_flag);

                default:
                    printf("\tInvalid Update Option\n");
                    break;
                }
}

void Delete_Student_Info(struct Student arr[], int *size)
{
    int id;

    printf("Enter the id: ");
    scanf("%d",&id);

    int flag = 0, i, newsize = 0;

    for (int i = 0; i < *size; i++)
    {
        if (id != arr[i].id)
        {
            arr[newsize] = arr[i];
            newsize++;
        }
    }
    if (newsize == *size)
    {
        printf("\tStudent not found\n");
    }
    else
    {
        printf("\tStudent Deleted Successfully\n");
        *size = newsize;
    }
    
}


int main()
{
    printf("\t\t\t:::WELCOME TO 26020 STUDENT DATABASE:::\n");

    struct Student arr[30];

    int size = 0;
    int i = 1;

    while (i)
    {
        printf("\n");
        printf("\t1.Add Student Info\n");
        printf("\t2.Search Student Info\n");
        printf("\t3.Display All Student Info\n");
        printf("\t4.Update Student Student Info\n");
        printf("\t5.Exit\n\n");

        int opt;

        printf("\tPlease Select One Option from the above menu: ");
        scanf("%d", &opt);

        switch (opt)
        {
            case 1:
                Add_Student_Info(arr, &size);
                break;

            case 2:
                Search_Student(arr, size);
                break;

            case 3:
                Display_Student_Info(arr, size);
                break;

            case 4:
                Update_Student_Info(arr, size);
                break;

            case 5:
                printf("\t\t\t:::Thank You:::\n");
                return 0;

            default:
                printf("\t\t\t:::Invalid Option:::\n");
        }

        printf("Do You Want to continue(1-Yes/0-No): ");
        scanf("%d", &i);
    }

    return 0;
}   