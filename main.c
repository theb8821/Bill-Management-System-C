#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void reciption();
void deleteBill();
void searchBill();
void generateBillHeader();
void generateBillBody();
void generateBillFooter();
void waiter();
void saveBill();

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
    printf("\n\t2. Search a Bill.");
    printf("\n\t3. Delete a Bill Record.");
    printf("\n\t4. Exit.");

    printf("\n\tWhat do you want me to do? ");
    
    selectionError:
    scanf("%d", &choice);
    getc(stdin);
    

    switch (choice)
    {
    case 1:
        reciption();
        break;
    
    case 2:
        printf("Search a bill.\n");
        break;

    case 3:
        printf("Delete a bill record.\n");
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

        printf("\nEnter its quantity: ");
        scanf("%d", &order.items[i].itemQuantity);

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

void saveBill()
{
    FILE *fp;
    /*fp = fopen("bills_records.txt", "a+");
    fprintf(fp, "\n%s", order.costumerName);
    for(int i = 0; i < order.numberOfItems; i++)
    {
        fprintf(fp, "\n%s%i %f", order.items[i].itemName, order.items[i].itemQuantity, order.items[i].itemPrice);
    }
    fclose(fp);
    */
    fp = fopen("bills_records.txt","a+");
    fwrite(&order,sizeof(order),1,fp);

    if(fwrite != 0)
    {
        printf("\n\n\t\t\t\t\tBill have been sucessufully saved!");
    }
    else printf("\n\n\t\t\t\t\tSorry! Something went wrong :(");
    fclose(fp);
}

void generateBillFooter()
{
    char choice;

    printf("\t\t\t\t\t\t\t\t\t\t------------------\n");
    printf("\t\t\t\t\t\t\t\t\t\tSubtotal: %.1f\n", order.subTotal);

    order.discount = order.subTotal * (discountPercentage / 100);
    printf("\t\t\t\t\t\t\t\t\t\tDiscount: %.1f\n", order.discount);

    order.vat = (order.subTotal - order.discount) * 0.13;
    printf("\t\t\t\t\t\t\t\t         Value Added Tax: %.1f\n", order.vat);

    order.grandTotal = order.subTotal - order.discount + order.vat;
    printf("\n\t\t\t\t\t\t\t\t-------------Grand Total: %.1f\n", order.grandTotal);

    printf("\nDo you want to save the bill (y/n)?: ");
    scanf("%c", &choice);

    //saveBill();
}

void reciption()
{
    waiter();
    generateBillHeader();
    generateBillBody();
    generateBillFooter();
}