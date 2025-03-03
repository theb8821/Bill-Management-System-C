#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void deleteBills();
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
    int billNo;
    int numberOfItems;
    char costumerName[30];
    char date[15];
    struct itemsDetail items[20];
    float subTotal;
    float grandTotal;
    float discount;
    float vat;
};

struct orderDetail order;
FILE *fp;

float discountPercentage = 10;

int main()
{
    system("clear");

    srand(time(NULL));
    order.billNo = rand() % 1000;

    int choice;
    strcpy(order.date,__DATE__);

    start:

    system("clear");

    printf("\t-------------------------Welcome to Bill Management System-------------------------");
    printf("\n\t1. New Bill.");
    printf("\n\t2. Search a Bill.");
    printf("\n\t3. Delete all bills.");
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
        saveBill();
        goto start;
        break;

    case 2:
        searchBill();
        goto start;
        break;

    case 3:
        deleteBills();
        goto start;
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
    printf("\n\tEnter the name of the costumer: ");
    fgets(order.costumerName,30,stdin);

    printf("\n\tEnter the no. of items ordered: ");
    scanf("%d", &order.numberOfItems);

    for (int i = 0; i < order.numberOfItems; i++)
    {
        getc(stdin);

        printf("\n\tEnter name of item no. %d: ", i + 1);
        fgets(order.items[i].itemName,20, stdin);
        order.items[i].itemName[strcspn(order.items[i].itemName, "\n")] = 0;

        printf("\n\tEnter its quantity: ");
        scanf("%d", &order.items[i].itemQuantity);

        printf("\n\tEnter its price (per unit): ");
        scanf("%f", &order.items[i].itemPrice);
    }
}

void generateBillHeader()
{
    system("clear");

    printf("\t---------------------------Upullo Resturant and Bar--------------------------------------\n");
    printf("\tBill NO: %d\n", order.billNo);
    printf("\n\tDate: %s", order.date);
    printf("\t\t\t\t\tCustomer's name: %s\n", order.costumerName);
    printf("\t-----------------------------------------------------------------------------------------\n");
    printf("\n\tItem Name");
    printf("\t\t\tQuantity");
    printf("\t\tPrice");
    printf("\t\t\tTotal\n\n");
}

void generateBillBody()
{
    for (int i = 0; i < order.numberOfItems; i++)
    {
        printf("\t%s", order.items[i].itemName);
        printf("\t\t\t   %d", order.items[i].itemQuantity);
        printf("\t\t\tRs.%.1f", order.items[i].itemPrice);

        order.items[i].total = order.items[i].itemQuantity * order.items[i].itemPrice;
        printf("\t\t\tRs.%.1f\n", order.items[i].total);

        order.subTotal += order.items[i].total;
    }
}

void saveBill()
{
    fgetc(stdin);
    char choice;

    start:
    printf("\n\tDo you want to save the bill (y/n)?: ");
    scanf("%c", &choice);

    if(choice == 'y')
    {
    fp = fopen("bills_records.txt", "a+");
    fwrite(&order, sizeof(struct orderDetail), 1, fp);

    if(&fwrite != 0)
    {
        printf("\n\tBill has been sucessufully saved :)\n");
    }
    else
    {
        printf("\n\tSorry! Something went wrong :( Bill not saved.\n");
    }

    fclose(fp);

    }
    else if(choice != 'n')
    {
        goto start;
    }

    fgetc(stdin);
    printf("\tPress ENTER KEY to continue: ");
    getc(stdin);

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
    printf("\n\t\t\t\t\t\t\t\t-------------Grand Total: %.1f\n\n", order.grandTotal);
}

void searchBill(){
    int found = 0;
    int billNO;

    fp = fopen("bills_records.txt","r");

    here:
    printf("\tEnter the bill number(zero to exit): ");
    scanf("%d", &billNO);
    fgetc(stdin);


    while(fread(&order, sizeof(struct orderDetail), 1, fp))
    {
            if(!(billNO - order.billNo))
            {
            generateBillHeader();
            generateBillBody();
            generateBillFooter();
            found = 1;
            }
    }
    if(!found){
        if(billNO != 0)
        {
            printf("\tSorry! The bill %d does not exists in our system :(\n", billNO);
            goto here;
        }
    }

    printf("\tPress ENTER KEY to continue: ");
    getc(stdin);

    fclose(fp);
}

void deleteBills()
{
    remove("bills_records.txt");
    fp = fopen("bills_records.txt", "w");
    printf("\n\tBills have been sucessesfully deleted :)\n");

    fclose(fp);

    printf("\tPress ENTER KEY to continue: ");
    getc(stdin);

}
/*
void deleteBill()
{
    int billNO;
    int found = 0;

    printf("Enter the bill number: ");
    scanf("%d", &billNO);
    fgetc(stdin);

    fp = fopen("bills_records.txt","w");

    while(fread(&order, sizeof(struct orderDetail), 1, fp))
    {
            if(!(billNO - order.billNo))
            {
            order.
            found = 1;
            }

    }
    if(!found){
        printf("Sorry! The bill no.%d does not exists in our system :(\n", billNO);
    }
    else{
        printf("Bill has been sucessesfully deleted :)\n");
    }
    fclose(fp);

 }
 */
