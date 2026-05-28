#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <strings.h>
#include "../include/saass.h"
void nurse_menu(char n_id[], char n_name[])
{
    int choice;
    int found = 0;

    while (1)
    {
        printf("\n|======================================================|\n");
        printf("|                 NURSE MENU (%-20s) |\n", n_name);
        printf("|======================================================|\n");
        printf("1. View Full Stock\n");
        printf("2. Find Specific Item\n");
        printf("3. Add/Update Stock\n");
        printf("4. Low Stock Alert\n");
        printf("5. Logout\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[ERROR] Invalid Input.\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }

        if (choice == 1)
        {
            show_stock();
        }
        else if (choice == 2)
        {
            find_item();
        }
        else if (choice == 3)
        {
            add_stock();
        }
        else if (choice == 4)
        {
            low_stock();
        }
        else if (choice == 5)
        {
            printf("\nLogging Out...\n");
            break;
        }
        else
        {
            printf("\n[ERROR] Invalid Choice!\n");
        }
    }
}

void show_stock()
{
    FILE *f = fopen("supplies.txt", "r");
    struct supply s;
    int found = 0;

    if (f == NULL)
    {
        printf("\n[INFO] Supply Closet Is Currently Empty. No Stock Available.\n");
        return;
    }

    printf("\n|======================================================|\n");
    printf("|                  CURRENT INVENTORY                   |\n");
    printf("|======================================================|\n");
    printf("%-20s | %-10s | %-10s\n", "Item Name", "Quantity", "Price (MYR)");
    printf("--------------------------------------------------------\n");

    while (fscanf(f, " %49[^|]|%d|%f\n", s.name, &s.qty, &s.price) == 3)
    {
        printf("%-20s | %-10d | %-10.2f\n", s.name, s.qty, s.price);
        found = 1;
    }

    fclose(f);

    if (!found)
    {
        printf("No Items Found In The Inventory.\n");
    }

    printf("--------------------------------------------------------\n");
}

void find_item()
{
    FILE *f = fopen("data/supplies.txt", "r");
    struct supply s;
    char target[50];
    int found = 0;

    if (f == NULL)
    {
        printf("\n[INFO] Supply Closet Is Currently Empty.\n");
        return;
    }

    printf("\nEnter Item Name To Search (Use_Underscores): ");
    scanf(" %49s", target);

    while (fscanf(f, " %49[^|]|%d|%f\n", s.name, &s.qty, &s.price) == 3)
    {
        if (strcasecmp(target, s.name) == 0)
        {
            printf("\n--- Item Found ---\n");
            printf("Name: %s\nCurrent Stock: %d\nPrice: %.2f MYR\n", s.name, s.qty, s.price);
            found = 1;
            break;
        }
    }

    fclose(f);

    if (!found)
    {
        printf("\n[ERROR] Item '%s' Not Found In Inventory.\n", target);
    }
}

void add_stock()
{
    FILE *f;
    struct supply items[100];
    char name[50];
    int count = 0, q, found = 0;

    f = fopen("data/supplies.txt", "r");

    if (f != NULL)
    {
        while (fscanf(f, " %49[^|]|%d|%f\n", items[count].name, &items[count].qty, &items[count].price) == 3)
        {
            count++;
        }
        fclose(f);
    }

    printf("\nEnter Item Name (Use_Underscores): ");
    scanf(" %49s", name);

    printf("Enter Quantity To Add: ");
    if (scanf("%d", &q) != 1)
    {
        printf("\n[ERROR] Invalid Quantity.\n");
        while (getchar() != '\n')
        {
        }
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (strcasecmp(items[i].name, name) == 0)
        {
            items[i].qty += q;
            found = 1;
            break;
        }
    }

    if (!found)
    {
        strcpy(items[count].name, name);
        items[count].qty = q;
        printf("New Item Detected! Enter Price Per Unit (MYR): ");

        if (scanf("%f", &items[count].price) != 1)
        {
            printf("\n[ERROR] Invalid Price.\n");
            while (getchar() != '\n')
            {
            }
            return;
        }

        count++;
    }

    f = fopen("data/supplies.txt", "w");

    if (f == NULL)
    {
        printf("\n[ERROR] Could Not Save Stock Data.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(f, "%s|%d|%.2f\n", items[i].name, items[i].qty, items[i].price);
    }

    fclose(f);

    printf("\n[SUCCESS] Inventory Updated Successfully!\n");
}

void low_stock()
{
    FILE *f = fopen("data/supplies.txt", "r");
    struct supply s;
    int count = 0;

    if (f == NULL)
    {
        printf("\n[INFO] Supply Closet Is Currently Empty.\n");
        return;
    }

    printf("\n|======================================================|\n");
    printf("|               LOW STOCK ALERT (BELOW 20)             |\n");
    printf("|======================================================|\n");

    while (fscanf(f, " %49[^|]|%d|%f\n", s.name, &s.qty, &s.price) == 3)
    {
        if (s.qty < 20)
        {
            printf("WARNING: %-15s | Only %d Remaining!\n", s.name, s.qty);
            count++;
        }
    }

    fclose(f);

    if (count == 0)
    {
        printf("All Items Are Sufficiently Stocked.\n");
    }

    printf("--------------------------------------------------------\n");
}