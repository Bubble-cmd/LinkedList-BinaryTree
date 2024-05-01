#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "case.h" // Include header file containing warehouse-related functions

int main() {
    Warehouse* warehouseList = NULL;
    int choice;
    char warehouseLocation[50];
    char itemName[50];
    int itemQuantity;
    clock_t start, end;
    double cpu_time_used;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Create Warehouse\n");
        printf("2. Display Warehouses\n");
        printf("3. Insert Item\n");
        printf("4. Delete Item\n");
        printf("5. Delete Warehouse\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);
        start = clock();  // Start timer

        switch (choice) {
        case 1:
            printf("Enter Warehouse Location: ");
            scanf_s("%s", warehouseLocation, sizeof(warehouseLocation));
            insertWarehouse(&warehouseList, warehouseLocation);
            printf("Warehouse created successfully!\n");
            break;
        case 2:
            printf("\n===== WAREHOUSES =====\n");
            displayWarehouses(warehouseList);
            break;
        case 3:
            printf("Enter Warehouse Location: ");
            scanf_s("%s", warehouseLocation, sizeof(warehouseLocation));
            printf("Enter Item Name: ");
            scanf_s("%s", itemName, sizeof(itemName));
            printf("Enter Item Quantity: ");
            scanf_s("%d", &itemQuantity);
            Warehouse* warehouseForInsert = searchWarehouse(warehouseList, warehouseLocation);
            if (warehouseForInsert != NULL) {
                warehouseForInsert->root = insertItem(warehouseForInsert->root, itemName, itemQuantity);
                printf("Item inserted successfully!\n");
            }
            else {
                printf("Warehouse not found!\n");
            }
            break;
        case 4:
            printf("Enter Warehouse Location: ");
            scanf_s("%s", warehouseLocation, sizeof(warehouseLocation));
            printf("Enter Item Name: ");
            scanf_s("%s", itemName, sizeof(itemName));
            Warehouse* warehouseForDelete = searchWarehouse(warehouseList, warehouseLocation);
            if (warehouseForDelete != NULL) {
                warehouseForDelete->root = deleteItem(warehouseForDelete->root, itemName);
                printf("Item deleted successfully!\n");
            }
            else {
                printf("Warehouse not found!\n");
            }
            break;
        case 5:
            printf("Enter Warehouse Location: ");
            scanf_s("%s", warehouseLocation, sizeof(warehouseLocation));
            warehouseList = deleteWarehouse(warehouseList, warehouseLocation);
            printf("Warehouse deleted successfully!\n");
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
        end = clock();  // End timer
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time taken for operation: %f seconds\n", cpu_time_used);

    } while (choice != 6);

    return 0;
}
