#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for an item
typedef struct Item {
    char name[50];
    int quantity;
    struct Item* left;
    struct Item* right;
} Item;

// Structure for a warehouse
typedef struct Warehouse {
    char location[50];
    struct Item* root; // Root of the BST for items in this warehouse
    struct Warehouse* next; // Pointer to the next warehouse in the linked list
} Warehouse;
Item* createItem(const char name[], int quantity);
Warehouse* createWarehouse(const char location[]);
Item* insertItem(Item* root, const char name[], int quantity);
void insertWarehouse(Warehouse** head, const char location[]);
void displayItems(Item* root);
void displayWarehouses(Warehouse* head);
Item* searchItem(Item* root, const char name[]);
Item* deleteItem(Item* root, const char name[]);
Warehouse* deleteWarehouse(Warehouse* head, const char location[]);
Warehouse* searchWarehouse(Warehouse* head, const char location[]);