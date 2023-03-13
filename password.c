#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <loading.h>
#include <time.h>

struct user
{
    char password[50];
    char reference[50];
    char username[50];

};

void maskpw(char password[])
{
    char ch;
    int i=0;
    while((ch=_getch())!=13)
    {
        printf("*");
        password[i]=ch;
        i++;
    }
    password[i]='\0';
}

void encrypt(char password[], int key)
{
    for(int i=0; i<strlen(password); i++)
    {
        password[i]=password[i]-key;
    }
}

void encryptr(char reference[], int key1)
{
    for(int i=0; i<strlen(reference); i++)
    {
        reference[i]=reference[i]-key1;
    }
}

void decrypt(char password[], int key)
{
    for(int i=0; i<strlen(password); i++)
    {
        password[i]=password[i]+key;
    }
}

void decryptr(char reference[], int key1)
{
    for(int i=0; i<strlen(reference); i++)
    {
        reference[i]=reference[i]+key1;
    }
}

int main()
{
    system("color 0A");
    FILE *fp;
    int opt;
    struct user user;
    char reference2[50],mp[50];
    printf("Enter the Master Password: ");
    maskpw(mp);

    if(!strcmp(mp,"1002"))
    {
        printf("\n\t\t\t\t\tPlease choose your operation");
        printf("\n\t\t\t\t\t1.Store a new password");
        printf("\n\t\t\t\t\t2.Retrieve old password");
        printf("\n\t\t\t\t\t3.Exit");
        printf("\n\n\t\t\t\t\tYour choice:  ");
        scanf("%d",&opt);
        fgetc(stdin);

        switch(opt)
        {
        case 1:
        {
            char password[30], reference[50],rfr[50],ran[50], confpass[50];
            printf("\n\t\t\t\t\tEnter your username:  ");
            scanf("%s", user.username);
            printf("\nDo you want your password to be randomly generated Y/N?  ");
            scanf("%s",&ran);

            if(!strcmp(ran,"Y"))
            {
                char ALPHABETS[30] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                char alphabets[30] = "abcdefghijklmnopqrstuvwxyz";
                char symbols[10] = "!@#$%^&*()";
                char numbers[10] = "0123456789";
                int length;
                printf("\nEnter the length of the password: ");
                scanf("%d", &length);
                int random_number;
                char rpassword[20];
                srand((unsigned int) (time(NULL)));

                for(int i = 0; i < length - 4; i++)
                {
                    rpassword[i] = ALPHABETS[rand() % 26];
                    rpassword[i + 3] = alphabets[rand() % 26];
                    rpassword[i + 1] = symbols[rand() % 10];
                    rpassword[i + 2] = numbers[rand() % 10];
                }

                printf("\nYour generated password is: %s\n", rpassword);
                strcpy(user.password, rpassword);
                printf("\n\t\t\t\t\t Enter your reference:  ");
                scanf("%s", user.reference);
                printf("\t\t\t\t\t Confirm your reference:  ");
                scanf("%s", reference2);
                strcpy(password, user.password);
                encrypt(password,0XAb);
                strcpy(user.password,password);
                strcpy(rfr,user.reference);
                strcpy(reference, user.reference);
                encryptr(reference,0XADb);
                strcpy(user.reference,reference);

                if(!strcmp(rfr,reference2))
                {
                    fp = fopen("Users.txt","a+");
                    fwrite(&user,sizeof(struct user),1,fp);
                    if(fwrite != 0) printf("\n\n\t\t\t\t\tUser registration success, Your reference is %s\n",rfr);
                    else printf("\n\n\t\t\t\t\tSorry! Something went wrong :(");
                    fclose(fp);
                }

                else
                {
                    printf("\n\t\t\t\t\treference does not match\n");
                }
            }

            else
            {
                printf("\n\t\t\t\t\tEnter your password:  ");
                maskpw(password);
                printf("\n\t\t\t\t\tConfirm your password:  ");
                maskpw(confpass);

                if(strcmp(password,confpass))
                {
                    printf("\n\t\t\t\t\tPasswords do not match");

                }
                else
                {
                    strcpy(user.password, password);
                    printf("\n");
                    printf("\n\t\t\t\t\t Enter your reference:  ");
                    scanf("%s", user.reference);
                    printf("\t\t\t\t\t Confirm your reference:  ");
                    scanf("%s", reference2);
                    strcpy(password, user.password);
                    encrypt(password,0XAb);
                    strcpy(user.password,password);
                    strcpy(rfr,user.reference);
                    strcpy(reference, user.reference);
                    encryptr(reference,0XADb);
                    strcpy(user.reference,reference);

                    if(!strcmp(rfr,reference2))
                    {
                        fp = fopen("Users.txt","a+");
                        fwrite(&user,sizeof(struct user),1,fp);
                        if(fwrite != 0) printf("\n\n\t\t\t\t\tUser registration success, Your reference is %s\n",rfr);
                        else printf("\n\n\t\t\t\t\tSorry! Something went wrong :(\n");
                        fclose(fp);
                    }
                    else
                    {
                        printf("\n\t\t\t\t\treference does not match\n");
                    }
                }
            }
            break;
        }

        case 2:
        {
            char username[50],rword[50], reference[50], password[50];
            printf("\n\t\t\t\t\tEnter your reference: ");
            scanf("%s",rword);
            fp = fopen("Users.txt","r");

            while(fread(&user,sizeof(struct user),1,fp))
            {
                strcpy(reference,user.reference);
                decryptr(reference,0XADb);

                if(!strcmp(reference,rword))
                {
                    loading ();
                    system("cls");
                    printf("\n\t\t\t\tYour username is: %s",user.username);
                    strcpy(password,user.password);
                    decrypt(password,0XAb);
                    printf("\n\t\t\t\tYour password is: %s\n",password);
                }

                /*else {
                    loading ();
                    system("cls");
                    printf("\nYour reference is not found!!\n");
                }*/
            }
            break;
        }

        case 3:
            printf("\n\t\t\t\t\tThank you for using PMS:)\n");
            break;

        default:
            printf("\n\t\t\t\t\tInvalid Number!\n");
            break;
            }
    }

    else
    {
        printf("\n");
        printf("\nMaster Password is incorrect! Unable to access.\n");
    }

    getch();

    return 0;



}
