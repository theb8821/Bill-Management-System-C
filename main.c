#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void generateBillHeader();
void generateBillBody();
void generateBillFooter();
void waiter();

struct itemsDetail
{
    char itemName[20];
    float itemPrice;
    int itemQuantity;
    float total;
};

struct orderDetail
{
    int numberOfItems;
    char costumerName[30];
    char date;
    struct itemsDetail items[20]; 
    float subTotal;
    float grandTotal;
    float discount;
    float vat;
};

struct orderDetail order;

float discountPercentage = 10;

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
        waiter();
        generateBillHeader();
        generateBillBody();
        generateBillFooter();
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
        fgets(order.items[i].itemName,20, stdin);



        /*
        printf("\nEnter its quantity: ");
        quantityError:
        scanf("%d", &order.items[i].itemQuantity);
        if (!isdigit(order.items[i].itemQuantity))
        {
            printf("Invalid! Try again: ");
            getc(stdin);
            goto quantityError;
        }   
        */
       //this above area need to be fixed!!!!


        printf("\nEnter its price: ");
        scanf("%f", &order.items[i].itemPrice);
        
    }  
}

void generateBillHeader()
{
    system("clear");
    printf("\t-------------------------Upullo Resturant and Bar--------------------------------------\n");
    printf("\n\tDate: 2023-02-27");
    printf("\t\t\t\t\tCustomer's name: %s\n", order.costumerName);
    printf("\t---------------------------------------------------------------------------------------\n");
    printf("\n\tItem Name");
    printf("\t\t\tQuantity");
    printf("\t\tPrice");
    printf("\t\t\tTotal\n\n");
}

void generateBillBody()
{
    getc(stdin);
    for (int i = 0; i < order.numberOfItems; i++)
    {
        printf("\t%s", order.items[i].itemName);
        printf("\t\t\t\t\t   %d", order.items[i].itemQuantity);
        printf("\t\t\tRs.%.1f", order.items[i].itemPrice);

        order.items[i].total = order.items[i].itemQuantity * order.items[i].itemPrice;
        printf("\t\tRs.%.1f\n", order.items[i].total);

        order.subTotal += order.items[i].total;
    } 
}

void generateBillFooter()
{
    printf("\t\t\t\t\t\t\t\t\t\t------------------\n");
    printf("\t\t\t\t\t\t\t\t\t\tSubtotal: %.1f\n", order.subTotal);

    order.discount = order.subTotal * (discountPercentage / 100);
    printf("\t\t\t\t\t\t\t\t\t\tDiscount: %.1f\n", order.discount);

    order.vat = (order.subTotal - order.discount) * 0.13;
    printf("\t\t\t\t\t\t\t\t         Value Added Tax: %.1f\n", order.vat);

    order.grandTotal = order.subTotal - order.discount + order.vat;
    printf("\t\t\t\t\t\t\t\t-------------Grand Total: %.1f\n", order.grandTotal);
}