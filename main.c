#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateBillHeader(char *);
void generateBillBody();
void generataeBillFooter();
void waiter();

struct itemsDetail
{
    char itemName[50];
    float itemPrice;
    int itemQuantity;
};

struct orderDetail
{
    int numberOfItems;
    char costumerName[30];
    char date;
    struct itemsDetail items[20]; 
    
};

struct orderDetail order;

int main()
{
    system("clear");
    int choice;

    printf("\t-------------------------Welcome to Bill Management System-------------------------");
    printf("\n\t1. New Bill.");
    printf("\n\t2. Show Bill Records.");
    printf("\n\t3. Search a Bill.");
    printf("\n\t4. Exit.");

    printf("\n\tWhat do you want me to do? ");
    
    selectionError:
    scanf("%d", &choice);
    getc(stdin);
    

    switch (choice)
    {
    case 1:
        //waiter();
        generateBillHeader(order.costumerName);
        break;
    
    case 2:
        printf("Showing all records.\n");
        break;

    case 3:
        printf("Search a bill.\n");
        break;

    case 4:
        exit(0);
        break;

    default:
        printf("Error! Invalid Option. Try Again: ");
        goto selectionError;
        break;
    }

    return 0;
}

void waiter()
{
    printf("\nEnter the name of the costumer: ");
    fgets(order.costumerName,30,stdin); 

    printf("\nEnter the no. of items ordered: ");
    scanf("%d", &order.numberOfItems);

    for (int i = 0; i < order.numberOfItems; i++)
    {
        fgetc(stdin);
        printf("\nEnter name of item no. %d: ", i + 1);
        fgets(order.items[i].itemName,50, stdin);
        
        printf("\nEnter its quantity: ");
        scanf("%d", &order.items[i].itemQuantity);

        printf("\nEnter its price: ");
        scanf("%f", &order.items[i].itemPrice);
    }  
}

void generateBillHeader(char costumerName[])
{
    system("clear");
    printf("\t-------------------------Upullo Resturant and Bar--------------------------------------\n");
    printf("\n\tDate: 2023-02-27");
    printf("\t\t\t\t\tCustomer's name: %s\n", order.costumerName);
    printf("\t---------------------------------------------------------------------------------------\n");
    printf("\n\tItem Name");
    printf("\t\t\tQuantity");
    printf("\t\tPrice");
    printf("\t\t\tTotal\n");
}