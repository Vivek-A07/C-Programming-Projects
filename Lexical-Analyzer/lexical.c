 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number(char s[])
{
    int i = 0;
    int dot_count = 0;

    while (s[i] != '\0')
    {
        if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
        }
        else if (s[i] == '.')
        {
            dot_count++;
        }
        else
        {
            return 0;
        }

        i++;
    }

    if (dot_count > 1)
    {
        return 0;
    }

    return 1;
}

int operator(char s[])
{
    char *arithmetic[] =
    {
        "+", "-", "*", "/", "%"
    };

    char *relational[] =
    {
        ">", "<", ">=", "<=", "==", "!="
    };

    char *logical[] =
    {
        "&&", "||", "!"
    };

    char *bitwise[] =
    {
        "&", "|", "^", "~", "<<", ">>"
    };

    char *increment_decrement[] =
    {
        "++", "--"
    };

    char *assignment[] =
    {
        "=", "+=", "-=", "*=", "/=", "%="
    };

    for (int i = 0; i < 5; i++)
    {
        if (strcmp(s, arithmetic[i]) == 0)
            return 1;
    }

    for (int i = 0; i < 6; i++)
    {
        if (strcmp(s, relational[i]) == 0)
            return 2;
    }

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(s, logical[i]) == 0)
            return 3;
    }

    for (int i = 0; i < 6; i++)
    {
        if (strcmp(s, bitwise[i]) == 0)
            return 4;
    }

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(s, increment_decrement[i]) == 0)
            return 5;
    }

    for (int i = 0; i < 6; i++)
    {
        if (strcmp(s, assignment[i]) == 0)
            return 6;
    }

    return 0;
}

int identifiers(char s[])
{
    int i = 0;

    while (s[i] != '\0')
    {
        if (i == 0)
        {
            if (s[0] == '_' || (s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))
            {
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
            {
            }
            else
            {
                return 0;
            }
        }

        i++;
    }

    return 1;
}

void print_operator(char s[])
{
    int op = operator(s);
        
        switch (op)
        {
            case 1:
            
            printf("%s\t\t\t\tARITHMETIC OPERATOR\n", s);
            break;
            
            case 2:
            printf("%s\t\t\t\tRELATIONAL OPERATOR\n", s);
            break;
            case 3:
            printf("%s\t\t\t\tLOGICAL OPERATOR\n", s);
            break;
            case 4:
            printf("%s\t\t\t\tBITWISE OPERATOR\n", s);
            break;
            case 5:
            printf("%s\t\t\t\tINCREMENT/DECREMENT OPERATOR\n", s);
            break;
            case 6:
            printf("%s\t\t\t\tASSIGNMENT OPERATOR\n", s);
            break;
        
        default:
            break;
        }
}

int main()
{
    int special_char = 0;
    char spl[10];

    char keywords[][10] =
    {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };

    FILE *fp = fopen("input.c", "r");

    if (fp == NULL)
    {
        printf("File does not exist\n");
        exit(1);
    }

    char store[1000];
    int ch;
    int idx = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }

    printf("\n\n");

    rewind(fp);

    while ((ch = fgetc(fp)) != EOF)
    {
    
        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            if (idx > 0)
            {
                store[idx] = '\0';

                int flag = 0;

                for (int i = 0; i < 32; i++)
                {
                    if (strcmp(store, keywords[i]) == 0)
                    {
                        printf("%s\t\t\t\tKEYWORD\n", store);
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    if (identifiers(store))
                    {
                        printf("%s\t\t\t\tIDENTIFIER\n", store);
                        flag = 1;
                    }
                }

                if (flag == 0)
                {
                    int op = operator(store);

                    if (op != 0)
                    {
                        print_operator(store);
                        flag = 1;
                    }
                }

                if (flag == 0)
                {
                    if (store[0] >= '0' && store[0] <= '9')
                    {
                        if (number(store))
                        {
                            printf("%s\t\t\t\tNUMBER\n", store);
                            flag = 1;
                        }
                    }
                }

                idx = 0;
            }

            continue;
        }

         
        if (ch == '{' || ch == '}' ||
            ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' ||
            ch == ',' || ch == ':' || ch == ';' ||
            ch == '?')
        {
            if (idx > 0)
            {
                store[idx] = '\0';

                int flag = 0;

                for (int i = 0; i < 32; i++)
                {
                    if (strcmp(store, keywords[i]) == 0)
                    {
                        printf("%s\t\t\t\tKEYWORD\n", store);
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0 && identifiers(store))
                {
                    printf("%s\t\t\t\tIDENTIFIER\n", store);
                    flag = 1;
                }

                if (flag == 0)
                {
                    int op = operator(store);

                    if (op != 0)
                    {
                        print_operator(store);
                        flag = 1;
                    }
                }

                if (flag == 0 &&
                    store[0] >= '0' && store[0] <= '9')
                {
                    if (number(store))
                    {
                        printf("%s\t\t\t\tNUMBER\n", store);
                    }
                }

                idx = 0;
            }

            spl[0] = ch;
            spl[1] = '\0';

            printf("%s\t\t\t\tSPECIAL SYMBOL\n", spl);

            continue;
        }

        if (ch == '#')
        {
            char preprocessor[100];
            int i = 0;

            preprocessor[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && ch != '\n')
            {
                preprocessor[i++] = ch;
            }

            preprocessor[i] = '\0';

            printf("%s\t\tPREPROCESSOR DIRECTIVE\n", preprocessor);

            continue;
        }

        if (ch == '"')
        {
            char str[1000];
            int i = 0;

            str[i++] = ch;

            while ((ch = fgetc(fp)) != EOF)
            {
                if (ch == '%')
                {
                    str[i] = '\0';

                    if (i > 0)
                    {
                        printf("%s\t\t\t\tSTRING\n", str);
                    }

                    int next = fgetc(fp);

                    if (next == 'd' ||
                        next == 'f' ||
                        next == 'c' ||
                        next == 's' ||
                        next == 'x' ||
                        next == 'X' ||
                        next == 'o' ||
                        next == 'u' ||
                        next == 'p')
                    {
                        printf("%%%c\t\t\t\tFORMAT SPECIFIER\n", next);
                    }

                    i = 0;
                }

                else if (ch == '\\')
                {
                    str[i] = '\0';

                    if (i > 0)
                    {
                        printf("%s\t\t\t\tSTRING\n", str);
                    }

                    int next = fgetc(fp);

                    if (next == 'n' ||
                        next == 't' ||
                        next == '\\' ||
                        next == '"')
                    {
                        printf("\\%c\t\t\t\tESCAPE SEQUENCE\n", next);
                    }

                    i = 0;
                }

                else if (ch == '"')
                {
                    str[i++] = ch;
                    str[i] = '\0';

                    printf("%s\t\t\t\tSTRING\n", str);

                    break;
                }

                else
                {
                    str[i++] = ch;
                }
            }

            continue;
        }   
        
        
        
        if (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' ||
            ch == '%' || ch == '>' ||
            ch == '<' || ch == '=' ||
            ch == '!' || ch == '&' ||
            ch == '|' || ch == '^' ||
            ch == '~')
        {
            if (idx > 0)
            {
                store[idx] = '\0';

                int flag = 0;

                for (int i = 0; i < 32; i++)
                {
                    if (strcmp(store, keywords[i]) == 0)
                    {
                        printf("%s\t\t\t\tKEYWORD\n", store);
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0 && identifiers(store))
                {
                    printf("%s\t\t\t\tIDENTIFIER\n", store);
                    flag = 1;
                }

                if (flag == 0 &&
                    store[0] >= '0' && store[0] <= '9')
                {
                    if (number(store))
                    {
                        printf("%s\t\t\t\tNUMBER\n", store);
                    }
                }

                idx = 0;
            }


            if (ch == '/')
            {
                int next = fgetc(fp);

                if (next == '/')
                {
                    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
                    {
                    }

                    printf("//\t\t\t\tSINGLE LINE COMMENT\n");
                }
                else if (next == '*')
                {
                    int prev = 0;

                    while ((ch = fgetc(fp)) != EOF)
                    {
                        if (prev == '*' && ch == '/')
                        {
                            break;
                        }

                        prev = ch;
                    }

                    printf("/* */\t\t\t\tMULTI LINE COMMENT\n");
                }
                else
                {
                    ungetc(next, fp);

                    char op[2];
                    op[0] = '/';
                    op[1] = '\0';

                    print_operator(op);
                }

                continue;
            }


            int next = fgetc(fp);

            char op[3];

            op[0] = ch;
            op[1] = '\0';

            if (next != EOF)
            {
                char temp[3];

                temp[0] = ch;
                temp[1] = next;
                temp[2] = '\0';

                if (operator(temp))
                {
                    strcpy(op, temp);
                }
                else
                {
                    ungetc(next, fp);
                }
            }

            print_operator(op);

            continue;
        }

         
        store[idx++] = ch;
    }

    
    if (idx > 0)
    {
        store[idx] = '\0';

        int flag = 0;

        for (int i = 0; i < 32; i++)
        {
            if (strcmp(store, keywords[i]) == 0)
            {
                printf("%s\t\t\t\tKEYWORD\n", store);
                flag = 1;
                break;
            }
        }

        if (flag == 0 && identifiers(store))
        {
            printf("%s\t\t\t\tIDENTIFIER\n", store);
            flag = 1;
        }

        if (flag == 0)
        {
            int op = operator(store);

            if (op != 0)
            {
                print_operator(store);
                flag = 1;
            }
        }

        if (flag == 0 &&
            store[0] >= '0' && store[0] <= '9')
        {
            if (number(store))
            {
                printf("%s\t\t\t\tNUMBER\n", store);
            }
        }
    }

    fclose(fp);

    return 0;
}
