#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{

    for (int i = 0; i <addressBook->contactCount; i++)
    {
        printf("----------------------------------------------------\n");
        printf("Name: %s\nMobile number: %s\nE-mail: %s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
        }
        
    printf("----------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);  
    exit(EXIT_SUCCESS); 
}


void createContact(AddressBook *addressBook)
{
    int name_flag;
    
    do
    {
        name_flag = 0;
        printf("Enter the name :");
        scanf(" %48[^\n]",addressBook->contacts[addressBook->contactCount].name);

        for (int i = 0; addressBook->contacts[addressBook->contactCount].name[i] != '\0'; i++)
        {
            if ((addressBook->contacts[addressBook->contactCount].name[i] >= 'a' && addressBook->contacts[addressBook->contactCount].name[i] <= 'z') || (addressBook->contacts[addressBook->contactCount].name[i] >= 'A' && addressBook->contacts[addressBook->contactCount].name[i] <= 'Z') || (addressBook->contacts[addressBook->contactCount].name[i] == ' '))
            {
                continue;
            }
            else
            {
                printf("Name should contain only English letters and spaces.\n\n");
                name_flag = 1;
                break;
            }

        }
        
    } while (name_flag);
    
    
// --------------------------------------------------------------------------------------
    
int count_digit;
int ph_flag;
int duplicate_flag;
do
{
    ph_flag = 0;
    duplicate_flag = 0;
    count_digit = 0;
    
    printf("Enter the phone number :");
    scanf("%19s",addressBook->contacts[addressBook->contactCount].phone);
    
    for (int i = 0; addressBook->contacts[addressBook->contactCount].phone[i] != '\0'; i++)
    {
        if (addressBook->contacts[addressBook->contactCount].phone[i] >= '0' && addressBook->contacts[addressBook->contactCount].phone[i] <= '9')
        {
            count_digit++;
        }
        else
        {
            ph_flag = 1;
            break;
        }    
    }
    
    if (ph_flag)
    {
        printf("\nPhone no should not contain any alpphabet\nPlease re enter the number\n\n");
    }
    else
    {
        if (count_digit != 10)
        {
            printf("\nPhone no should contain numerical 10 digits\nPlease re enter the number\n");
            ph_flag = 1;
        }
    }
    
    if (count_digit == 10)
    {
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone,addressBook->contacts[addressBook->contactCount].phone) == 0)
            {
                duplicate_flag = 1;
                break;
            }
        }
    }
    
    if (duplicate_flag)
    {
        printf("Phone number should be unique!!\nRe enter the phone number\n\n");
    }
    
} while (ph_flag || duplicate_flag);

// --------------------------------------------------------------------------------------
int email_flag;
int spl_flag;
int at_flag;
int at_count;
int at_pos;
int dot_flag;
int dot_count;
int email_digit;
int digit_flag;
int email_duplicate_flag;

do
{
    spl_flag = 0;
    email_flag = 0;
    at_flag = 0;
    at_count = 0;
    at_pos = -1;
    dot_flag = 0;
    dot_count = 0;
    email_digit = 0;
    digit_flag = 0;
    email_duplicate_flag = 0;

    printf("Enter the email :");
    getchar();
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);

    for (int i = 0; addressBook->contacts[addressBook->contactCount].email[i] != '\0';i++)
    {
        char ch = addressBook->contacts[addressBook->contactCount].email[i];

        if (ch == ' ')
        {
            email_flag = 1;
            break;
        }

        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '@' || ch == '.'))
        {
            spl_flag = 1;
            break;
        }

        if (ch >= '0' && ch <= '9')
        {
            email_digit++;
        }
        

        if (ch == '@')
        {
            at_count++;

            if (at_count > 1)
            {
                at_flag = 1;
                break;
            }

            at_pos = i;

            if (i == 0 ||
                addressBook->contacts[addressBook->contactCount].email[i + 1] == '\0')
            {
                at_flag = 1;
                break;
            }
        }

        if (ch == '.' && at_pos != -1 && i > at_pos)
        {
            dot_count++;

            if (i - at_pos == 1 ||
                addressBook->contacts[addressBook->contactCount].email[i + 1] == '\0')
            {
                dot_flag = 1;
                break;
            }
        }
    
    }


    if (spl_flag)
    {
        printf("\nEmail should only contain @ and . as a spl char\n");
        continue;
    }

    if (email_digit == 0)
    {
        printf("\nEmail Should atleast contain single integer.\n");
        digit_flag = 1;
        continue;
    }
    if (at_pos == -1)
    {
        at_flag = 1;    
    }
    else if (dot_count == 0)
    {
        dot_flag = 1;   
    }
    
    if (email_flag)
    {
        printf("Invalid email. Please re-enter.\n\n");
    }
    if (dot_flag || at_flag)
    {
        printf("\nEmail should contain @ and .com at valid position\n");
    }

    

    if (!spl_flag && !email_flag && !at_flag && !dot_flag && !digit_flag)
    {
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].email,addressBook->contacts[addressBook->contactCount].email) == 0)
            {
                email_duplicate_flag = 1;
                break;
            }
        }    
    }
    
    if (email_duplicate_flag)
    {
       printf("Email should be unique!!\nRe-enter the email\n\n");
    }
    
    

} while (spl_flag || email_flag || at_flag || dot_flag || digit_flag || email_duplicate_flag);


addressBook->contactCount++;

}
// --------------------------------------------------------------------------------------

void searchContact(AddressBook *addressBook) 
{
  
    int found ;
    int no;
    int no_valid;
    int name_flag;
    int digit_count;
    int ph_flag;
    int yes_no;
    do
    { 
        no_valid = 0;
        printf("1.Search by name\n");
        printf("2.Search by ph no\n");
        printf("3.Search by email\n");
        printf("\n");
        
        printf("Enter your choice: ");
        scanf("%d",&no);
        
        if (no < 1 || no > 3)
        {
            no_valid = 1;
            printf("Invalid choice. Please try again.\n");
        }
        
        char search_name[50];
        char search_ph[20];
        char search_email[50];
        found = 0;
        name_flag = 0;
        switch (no)
        {
            case 1:
            printf("Enter the complete name :");
            scanf(" %49[^\n]",search_name);
            
            int match_index[MAX_CONTACTS];
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                //  printf("[%s]\n", addressBook->contacts[i].name);
                if(strcmp(search_name, addressBook->contacts[i].name) == 0)
                {
                    match_index[found] = i;
                    found++;
                    
                    printf("\n%d.\nName: %s\nMobile number: %s\nEmail id: %s\n",found,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            
            int choice;
            if (found == 0)
            {
                printf("Contact not found\n");
                name_flag = 1;
            }
            else
            {
                int selected_index;
                if (found > 1)
                {
                    do
                    {
                        printf("\nthere are several contacts with the name '%s'.",addressBook->contacts->name);
                        printf("\nEnter the index of the contact: ");
                        scanf("%d", &choice);
                        
                    } while (choice > found || choice < 1);
                    
                    selected_index = match_index[choice - 1];
                }
                else
                {
                    selected_index = match_index[0];
                }
                
                if (found != 1)
                {
                    printf("%s %s %s\n",
                        addressBook->contacts[selected_index].name,
                        addressBook->contacts[selected_index].phone,
                        addressBook->contacts[selected_index].email);
                    }
                }
                break;
                
            case 2:
                
                do
                {
                    yes_no = 0;
                    digit_count = 0;
                    ph_flag = 0;
                    int found = 0;

                    printf("Enter the Ph no :");
                    scanf(" %19s",search_ph);
                    
                    for (int i = 0; search_ph[i] != '\0'; i++)
                    {
                        if (search_ph[i] >= '0' && search_ph[i] <= '9')
                        {
                            digit_count++;
                        }
                        else
                        {
                            ph_flag = 1;
                            break;
                        }    
                    }
                    
                    if (ph_flag || digit_count != 10)
                    {
                        printf("Invalid phone number. Please try again.\n");
                        printf("\n");
                        
                        printf("Do you want to re enter the ph number ?:(Y -> 1/N -> 0) :");
                        scanf("%d",&yes_no);
                    }
                    else
                    {

                        if (digit_count == 10)
                        {
                            for (int i = 0; i < addressBook->contactCount; i++)
                            {
                                if(strcmp(search_ph,addressBook->contacts[i].phone) == 0)
                                {
                                    found = 1;
                                    printf("\n%d.\nName: %s\nMobile number: %s\nEmail id: %s\n",found,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                }
                            }
                            
                        }

                        if (!found)
                        {
                            printf("\n");
                            printf("Contact not found\n");
    
                            printf("Do you want to re enter the ph number ?:(Y -> 1/N -> 0) :");
                            scanf("%d",&yes_no);
                        }
                    }

                    
                } while (yes_no);
            
            break;

            case 3:
            do
                {
                    yes_no = 0;
                    int found = 0;

                    printf("Enter the email :");
                    scanf(" %49s",search_email);


                    for (int i = 0; i < addressBook->contactCount; i++)
                    {
                        if(strcmp(search_email,addressBook->contacts[i].email) == 0)
                        {
                            found = 1;
                           printf("\n%d.\nName: %s\nMobile number: %s\nEmail id: %s\n",found,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        }
                    }

                    if (!found)
                    {
                        printf("\n");
                        printf("Email not found\n");

                        printf("Do you want to re enter the email ?:(Y -> 1/N -> 0) :");
                        scanf("%d",&yes_no);
                    }
                    
                } while (yes_no);

        
        default:
            break;
        }
        
    } while (name_flag || no_valid);
    

}
// --------------------------------------------------------------------------------------

void editContact(AddressBook *addressBook)
{
    int selected_index = -1;
    int search_choice;
    int edit_choice;
    int found;
    int yes_no;

    char search_name[50];
    char search_ph[20];
    char search_email[50];

    do
    {
        selected_index = -1;

        printf("\n1. Search by name\n");
        printf("2. Search by ph no\n");
        printf("3. Search by email\n");

        printf("Enter your choice: ");
        scanf("%d", &search_choice);

        switch (search_choice)
        {

            case 1:
            {
                int match_index[MAX_CONTACTS];
                int match_count = 0;
                int choice;

                printf("Enter the complete name: ");
                scanf(" %49[^\n]", search_name);

                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(search_name,
                               addressBook->contacts[i].name) == 0)
                    {
                        match_index[match_count] = i;
                        match_count++;

                        printf("\n%d.\nName: %s\nMobile number: %s\nEmail id: %s\n",
                               match_count,
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                    }
                }

                if (match_count == 0)
                {
                    printf("Contact not found.\n");
                    break;
                }

                if (match_count == 1)
                {
                    selected_index = match_index[0];
                }
                else
                {
                    do
                    {
                        printf("Enter the index of the contact: ");
                        scanf("%d", &choice);

                        if (choice < 1 || choice > match_count)
                        {
                            printf("Invalid index.\n");
                        }

                    } while (choice < 1 || choice > match_count);

                    selected_index = match_index[choice - 1];
                }

                break;
            }

// --------------------------------------------------------------------------------------

            case 2:
            {
                do
                {
                    yes_no = 0;
                    found = 0;

                    int digit_count = 0;
                    int ph_flag = 0;

                    printf("Enter the Ph no: ");
                    scanf(" %19s", search_ph);

                    for (int i = 0; search_ph[i] != '\0'; i++)
                    {
                        if (search_ph[i] >= '0' &&
                            search_ph[i] <= '9')
                        {
                            digit_count++;
                        }
                        else
                        {
                            ph_flag = 1;
                            break;
                        }
                    }

                    if (ph_flag || digit_count != 10)
                    {
                        printf("Invalid phone number.\n");

                        printf("Do you want to re-enter? "
                               "(1-Yes / 0-No): ");
                        scanf("%d", &yes_no);
                    }
                    else
                    {
                        for (int i = 0;
                             i < addressBook->contactCount;
                             i++)
                        {
                            if (strcmp(search_ph,
                                       addressBook->contacts[i].phone) == 0)
                            {
                                found = 1;
                                selected_index = i;

                                printf("\nName: %s\nMobile number: %s\nEmail id: %s\n",
                                       addressBook->contacts[i].name,
                                       addressBook->contacts[i].phone,
                                       addressBook->contacts[i].email);

                                break;
                            }
                        }

                        if (!found)
                        {
                            printf("Contact not found.\n");

                            printf("Do you want to re-enter? "
                                   "(1-Yes / 0-No): ");
                            scanf("%d", &yes_no);
                        }
                    }

                } while (yes_no);

                break;
            }

// --------------------------------------------------------------------------------------

            case 3:
            {
                do
                {
                    yes_no = 0;
                    found = 0;

                    printf("Enter the email: ");
                    scanf(" %49s", search_email);

                    for (int i = 0;i < addressBook->contactCount;i++)
                    {
                        if (strcmp(search_email,addressBook->contacts[i].email) == 0)
                        {
                            found = 1;
                            selected_index = i;

                            // printf("\nName: %s\nMobile number: %s\nEmail id: %s\n",
                            //        addressBook->contacts[i].name,
                            //        addressBook->contacts[i].phone,
                            //        addressBook->contacts[i].email);

                            break;
                        }
                    }

                    if (!found)
                    {
                        printf("Email not found.\n");

                        printf("Do you want to re-enter? "
                               "(1-Yes / 0-No): ");
                        scanf("%d", &yes_no);
                    }

                } while (yes_no);

                break;
            }

            default:
                printf("Invalid search choice.\n");
                break;
        }
// --------------------------------------------------------------------------------------


        if (selected_index != -1)
        {
            printf("\nSelected Contact:\n");
            printf("Name  : %s\n",addressBook->contacts[selected_index].name);
            printf("Phone : %s\n",addressBook->contacts[selected_index].phone);
            printf("Email : %s\n",addressBook->contacts[selected_index].email);

            printf("\nWhat do you want to edit?\n");
            printf("1. Name\n");
            printf("2. Phone\n");
            printf("3. Email\n");

            printf("Enter your choice: ");
            scanf("%d", &edit_choice);

            switch (edit_choice)
            {

                case 1:
                {
                    char new_name[50];
                    int name_flag;

                    do
                    {
                        name_flag = 0;

                        printf("Enter the new name: ");
                        scanf(" %49[^\n]", new_name);

                        for (int i = 0;
                             new_name[i] != '\0';
                             i++)
                        {
                            if (!((new_name[i] >= 'A' &&
                                   new_name[i] <= 'Z') ||
                                  (new_name[i] >= 'a' &&
                                   new_name[i] <= 'z') ||
                                  new_name[i] == ' '))
                            {
                                name_flag = 1;
                                break;
                            }
                        }

                        if (name_flag)
                        {
                            printf("Invalid name. Please try again.\n");
                        }

                    } while (name_flag);

                    strcpy(addressBook->contacts[selected_index].name,
                           new_name);

                    printf("Name updated successfully.\n");

                    break;
                }

// --------------------------------------------------------------------------------------

                case 2:
                {
                    char new_phone[20];
                    int valid;
                    int duplicate;

                    do
                    {
                        valid = 1;
                        duplicate = 0;

                        printf("Enter the new phone number: ");
                        scanf(" %19s", new_phone);

                        int digit_count = 0;

                        for (int i = 0;
                             new_phone[i] != '\0';
                             i++)
                        {
                            if (new_phone[i] >= '0' &&
                                new_phone[i] <= '9')
                            {
                                digit_count++;
                            }
                            else
                            {
                                valid = 0;
                                break;
                            }
                        }

                        if (digit_count != 10)
                        {
                            valid = 0;
                        }

                        if (!valid)
                        {
                            printf("Invalid phone number.\n");
                            continue;
                        }


                        for (int i = 0;
                             i < addressBook->contactCount;
                             i++)
                        {
                            if (i != selected_index &&
                                strcmp(new_phone,
                                       addressBook->contacts[i].phone) == 0)
                            {
                                duplicate = 1;
                                break;
                            }
                        }

                        if (duplicate)
                        {
                            printf("Phone number already exists.\n");
                        }

                    } while (!valid || duplicate);

                    strcpy(addressBook->contacts[selected_index].phone,
                           new_phone);

                    printf("Phone updated successfully.\n");

                    break;
                }
// --------------------------------------------------------------------------------------

                case 3:
                    {
                        char new_email[50];

                        int email_flag;
                        int spl_flag;
                        int at_flag;
                        int at_count;
                        int at_pos;
                        int dot_flag;
                        int dot_count;
                        int email_digit;
                        int digit_flag;
                        int duplicate_flag;

                        do
                        {
                            email_flag = 0;
                            spl_flag = 0;
                            at_flag = 0;
                            at_count = 0;
                            at_pos = -1;
                            dot_flag = 0;
                            dot_count = 0;
                            email_digit = 0;
                            digit_flag = 0;
                            duplicate_flag = 0;

                            printf("Enter the new email: ");
                            scanf(" %49s", new_email);

                            for (int i = 0; new_email[i] != '\0'; i++)
                            {
                                char ch = new_email[i];

                                if (ch == ' ')
                                {
                                    email_flag = 1;
                                    continue;
                                }

                                if (!((ch >= 'a' && ch <= 'z') ||
                                    (ch >= 'A' && ch <= 'Z') ||
                                    (ch >= '0' && ch <= '9') ||
                                    ch == '@' ||
                                    ch == '.'))
                                {
                                    spl_flag = 1;
                                    continue;
                                }

                                if (ch >= '0' && ch <= '9')
                                {
                                    email_digit++;
                                }

                                if (ch == '@')
                                {
                                    at_count++;

                                    if (at_count > 1)
                                    {
                                        at_flag = 1;
                                        continue;
                                    }

                                    at_pos = i;

                                    if (i == 0 || new_email[i + 1] == '\0')
                                    {
                                        at_flag = 1;
                                    }
                                }

                                if (ch == '.' && at_pos != -1 && i > at_pos)
                                {
                                    dot_count++;

                                    if (i - at_pos == 1 ||
                                        new_email[i + 1] == '\0')
                                    {
                                        dot_flag = 1;
                                    }
                                }
                            }

                            if (email_digit == 0)
                            {
                                digit_flag = 1;
                                printf("Email should contain at least one integer.\n");
                            }

                            if (at_pos == -1)
                                at_flag = 1;

                            if (at_pos != -1 && dot_count == 0)
                                dot_flag = 1;

                            if (spl_flag)
                                printf("Email should contain only letters, digits, @ and .\n");

                            if (email_flag)
                                printf("Email should not contain spaces.\n");

                            if (at_flag || dot_flag)
                                printf("Email should contain @ and . at valid position.\n");

                            if (!spl_flag && !email_flag &&
                                !at_flag && !dot_flag && !digit_flag)
                            {
                                for (int i = 0; i < addressBook->contactCount; i++)
                                {
                                    if (i != selected_index &&
                                        strcmp(new_email,
                                            addressBook->contacts[i].email) == 0)
                                    {
                                        duplicate_flag = 1;
                                        break;
                                    }
                                }
                            }

                            if (duplicate_flag)
                            {
                                printf("Email already exists.\n");
                            }

                            if (spl_flag || email_flag ||
                                at_flag || dot_flag ||
                                digit_flag || duplicate_flag)
                            {
                                printf("Do you want to re-enter? (1-Yes / 0-No): ");
                                scanf("%d", &yes_no);
                            }
                            else
                            {
                                yes_no = 0;
                            }

                        } while (yes_no);

                        if (!spl_flag && !email_flag &&
                            !at_flag && !dot_flag &&
                            !digit_flag && !duplicate_flag)
                        {
                            strcpy(addressBook->contacts[selected_index].email,
                                new_email);

                            printf("Email updated successfully.\n");
                        }

                        break;
                    }

                default:
                    printf("Invalid edit choice.\n");
                    break;
            }
        }

    } while (selected_index == -1);
}

void deleteContact(AddressBook *addressBook)
{

    int selected_index = -1;
    int search_choice;
    int found;
    int yes_no;

    char search_name[50];
    char search_ph[20];
    char search_email[50];

    do
    {
        selected_index = -1;

        printf("\n1. Search by name\n");
        printf("2. Search by ph no\n");
        printf("3. Search by email\n");

        printf("Enter your choice: ");
        scanf("%d", &search_choice);

        switch (search_choice)
        {

            case 1:
            {
                int match_index[MAX_CONTACTS];
                int match_count = 0;
                int choice;

                printf("Enter the complete name: ");
                scanf(" %49[^\n]", search_name);

                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(search_name,
                               addressBook->contacts[i].name) == 0)
                    {
                        match_index[match_count] = i;
                        match_count++;

                        printf("\n%d.\nName: %s\nMobile number: %s\nEmail id: %s\n",
                               match_count,
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                    }
                }

                if (match_count == 0)
                {
                    printf("Contact not found.\n");
                    break;
                }

                if (match_count == 1)
                {
                    selected_index = match_index[0];
                }
                else
                {
                    do
                    {
                        printf("Enter the index of the contact: ");
                        scanf("%d", &choice);

                        if (choice < 1 || choice > match_count)
                        {
                            printf("Invalid index.\n");
                        }

                    } while (choice < 1 || choice > match_count);

                    selected_index = match_index[choice - 1];
                }

                break;
            }


            case 2:
            {
                do
                {
                    yes_no = 0;
                    found = 0;

                    int digit_count = 0;
                    int ph_flag = 0;

                    printf("Enter the Ph no: ");
                    scanf(" %19s", search_ph);

                    for (int i = 0; search_ph[i] != '\0'; i++)
                    {
                        if (search_ph[i] >= '0' &&
                            search_ph[i] <= '9')
                        {
                            digit_count++;
                        }
                        else
                        {
                            ph_flag = 1;
                            break;
                        }
                    }

                    if (ph_flag || digit_count != 10)
                    {
                        printf("Invalid phone number.\n");

                        printf("Do you want to re-enter? "
                               "(1-Yes / 0-No): ");
                        scanf("%d", &yes_no);
                    }
                    else
                    {
                        for (int i = 0;
                             i < addressBook->contactCount;
                             i++)
                        {
                            if (strcmp(search_ph,
                                       addressBook->contacts[i].phone) == 0)
                            {
                                found = 1;
                                selected_index = i;

                                printf("\nName: %s\nMobile number: %s\nEmail id: %s\n",
                                       addressBook->contacts[i].name,
                                       addressBook->contacts[i].email,
                                       addressBook->contacts[i].phone);

                                break;
                            }
                        }

                        if (!found)
                        {
                            printf("Contact not found.\n");

                            printf("Do you want to re-enter? "
                                   "(1-Yes / 0-No): ");
                            scanf("%d", &yes_no);
                        }
                    }

                } while (yes_no);

                break;
            }


            case 3:
            {
                do
                {
                    yes_no = 0;
                    found = 0;

                    printf("Enter the email: ");
                    scanf(" %49s", search_email);

                    for (int i = 0;
                         i < addressBook->contactCount;
                         i++)
                    {
                        if (strcmp(search_email,
                                   addressBook->contacts[i].email) == 0)
                        {
                            found = 1;
                            selected_index = i;

                            printf("\nName: %s\nMobile number: %s\nEmail id: %s\n",
                                   addressBook->contacts[i].name,
                                   addressBook->contacts[i].email,
                                   addressBook->contacts[i].phone);

                            break;
                        }
                    }

                    if (!found)
                    {
                        printf("Email not found.\n");

                        printf("Do you want to re-enter? "
                               "(1-Yes / 0-No): ");
                        scanf("%d", &yes_no);
                    }

                } while (yes_no);

                break;
            }

            default:
                printf("Invalid search choice.\n");
                break;
        }


        if (selected_index != -1)
        {
            printf("\nContact selected:\n");

            printf("Name  : %s\n",
                   addressBook->contacts[selected_index].name);

            printf("Phone : %s\n",
                   addressBook->contacts[selected_index].phone);

            printf("Email : %s\n",
                   addressBook->contacts[selected_index].email);

            printf("\nDo you want to delete this contact?\n");
            printf("1. Yes\n");
            printf("0. No\n");

            printf("Enter your choice: ");
            scanf("%d", &yes_no);

            if (yes_no == 1)
            {
                for (int i = selected_index;
                     i < addressBook->contactCount - 1;
                     i++)
                {
                    addressBook->contacts[i] =
                        addressBook->contacts[i + 1];
                }

                addressBook->contactCount--;

                printf("Contact deleted successfully.\n");
            }
            else
            {
                printf("Contact was not deleted.\n");
            }

            break;
        }

    } while (selected_index == -1);
    
   
}
