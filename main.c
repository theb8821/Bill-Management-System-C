#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateBillHeader(char);
void generateBillBody();
void generataeBillFooter();
void waiter();
void reception();

struct itemsDetail
{
    char itemName[50];
    float itemPrice;
    int itemQuantity;
};

struct orderDetail
{
    int numberOfItems;
    char costumerName[20];
    char date;
    struct itemsDetail items[20]; 
    
};

struct orderDetail order;

int main()
{
    //variable declaration
    int choice;
    char name[20];

    printf("\t---------------Bill Management System---------------");
    printf("\n1. Generate Bill.");
    printf("\n2. Show All Bills.");
    printf("\n3. Search a Bill.");
    printf("\n4. Exit.");

    printf("\nWhat do you want me to do? ");
    scanf("%d", &choice);

    waiter();

    /*switch (choice)
    {
    case 1:
        break;
    
    default:
        break;
    }*/

    return 0;
}

void waiter()
{
    system("clear");
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

void reception()
{
    printf("\nEnter the name of the costumer: ");
    fgets(order.costumerName,20,stdin);  
}

void generateBillHeader(char order.costumerName[], char order.date)
{
    system("clear");
    printf("--------------------Upullo Resturant and Bar--------------------");
    printf("\nCustomer's name: %s", order.costumerName);
    printf("\t\t\t\t\tDate: 2023-02-27\n");
    printf("------------------------------------------------------------")
}