#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {

    FILE *fp = fopen("contacts.txt", "w");
    
    if (fp == NULL)
    {
        printf("Unable to open file\n");
        exit(1);
    }
    
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        
        fprintf(fp,"%s %s %s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    
    fclose(fp);
    
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r");

    if (fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    int ch;

    for (int i = 0; i < MAX_CONTACTS; i++)
    {
        int name_index = 0;
        int phone_index = 0;
        int email_index = 0;

       while ((ch = getc(fp)) != EOF)
        {
            if (ch >= '0' && ch <= '9')
            {
                break;
            }

            if (ch == '\n')
                break;

            addressBook->contacts[i].name[name_index++] = ch;
        }

        while (name_index > 0 &&
            addressBook->contacts[i].name[name_index - 1] == ' ')
        {
            name_index--;
        }

        addressBook->contacts[i].name[name_index] = '\0';

        if (ch == EOF || ch == '\n')
        {
            break;
        }

        addressBook->contacts[i].phone[phone_index++] = ch;

        while (phone_index < 10 && (ch = getc(fp)) != EOF)
        {
            addressBook->contacts[i].phone[phone_index++] = ch;
        }

        addressBook->contacts[i].phone[phone_index] = '\0';

        getc(fp);

        while ((ch = getc(fp)) != EOF && ch != '\n')
        {
            addressBook->contacts[i].email[email_index++] = ch;
        }

        addressBook->contacts[i].email[email_index] = '\0';

        addressBook->contactCount++;
    }

    fclose(fp);
}
