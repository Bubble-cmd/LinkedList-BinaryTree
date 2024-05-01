#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "case.h"

// Function to create a new item
Item* createItem(const char name[], int quantity) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy_s(newItem->name, sizeof(newItem->name), name);
    newItem->quantity = quantity;
    newItem->left = NULL;
    newItem->right = NULL;
    return newItem;
}

// Function to create a new warehouse
Warehouse* createWarehouse(const char location[]) {
    Warehouse* newWarehouse = (Warehouse*)malloc(sizeof(Warehouse));
    strcpy_s(newWarehouse->location, sizeof(newWarehouse->location), location);
    newWarehouse->root = NULL;
    newWarehouse->next = NULL;
    return newWarehouse;
}

// Function to insert an item into the BST of a warehouse
// Function to insert an item into the BST of a warehouse
Item* insertItem(Item* root, const char name[], int quantity) {
    // Case 1: If the BST is empty, create a new node and make it the root
    if (root == NULL) {
        return createItem(name, quantity);
    }

    // Compare the item's name with the current node's name
    int compare = strcmp(name, root->name);

    // Case 2: If the item already exists in the BST, update its quantity
    if (compare == 0) {
        root->quantity += quantity;
    }
    // Case 3: If the item's name is less than the current node's name, go left
    else if (compare < 0) {
        root->left = insertItem(root->left, name, quantity);
    }
    // Case 4: If the item's name is greater than the current node's name, go right
    else {
        root->right = insertItem(root->right, name, quantity);
    }

    return root;
}


// Function to insert a warehouse into the linked list
void insertWarehouse(Warehouse** head, const char location[]) {
    Warehouse* newWarehouse = createWarehouse(location);
    newWarehouse->next = *head;
    *head = newWarehouse;
}

// Function to display all items in a warehouse (inorder traversal of BST)
void displayItems(Item* root) {
    if (root != NULL) {
        displayItems(root->left);
        printf("Item Name: %s, Quantity: %d\n", root->name, root->quantity);
        displayItems(root->right);
    }
}

// Function to display all warehouses and their items
void displayWarehouses(Warehouse* head) {
    Warehouse* current = head;
    while (current != NULL) {
        printf("Warehouse Location: %s\n", current->location);
        printf("Items in Warehouse:\n");
        displayItems(current->root); // Display items in the current warehouse
        current = current->next;
    }
}

// Function to search for an item in a warehouse
Item* searchItem(Item* root, const char name[]) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        return searchItem(root->left, name);
    }
    else {
        return searchItem(root->right, name);
    }
}

// Function to delete an item from a warehouse
Item* deleteItem(Item* root, const char name[]) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        root->left = deleteItem(root->left, name);
    }
    else if (strcmp(name, root->name) > 0) {
        root->right = deleteItem(root->right, name);
    }
    else {
        // Case 1: No child or only one child
        if (root->left == NULL) {
            Item* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Item* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children
        Item* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        strcpy_s(root->name, sizeof(root->name), temp->name);
        root->quantity = temp->quantity;
        root->right = deleteItem(root->right, temp->name);
    }

    return root;
}

// Function to delete a warehouse
Warehouse* deleteWarehouse(Warehouse* head, const char location[]) {
    if (head == NULL) {
        return head;
    }

    if (strcmp(head->location, location) == 0) {
        Warehouse* temp = head->next;
        free(head);
        return temp;
    }

    head->next = deleteWarehouse(head->next, location);
    return head;
}
// Function to search for a warehouse by its location
Warehouse* searchWarehouse(Warehouse* head, const char location[]) {
    Warehouse* current = head;
    while (current != NULL) {
        if (strcmp(current->location, location) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Warehouse not found
}


// Test functions and implementation

/*

void testCreateItem() {
    printf(" Item Creat..\n");
    Item* item = createItem("ssd", 100);
    if (item != NULL && strcmp(item->name, "ssd") == 0 && item->quantity == 100) {
        printf("Done");
    } else {
        printf("FAIL");
    }
}

void testInsertItem() {
    printf(" Item Insert...\n");
    Item* root = NULL;
    root = insertItem(root, "dfg", 50);
    root = insertItem(root, "cccvb", 150);
    root = insertItem(root, "fghfh", 100);

    if (searchItem(root, "dfg") != NULL) {
        printf("insert");
    } else {
        printf("FAIL");
    }

    // Clean up
    deleteItem(root, "dfg");
    deleteItem(root, "cccvb");
    deleteItem(root, "fghfh");
}

void testCreateAndInsertWarehouse() {
    printf(" Warehouse Creat and Item Insert\n");
    Warehouse* head = NULL;
    insertWarehouse(&head, "Warehouse A");
    head->root = insertItem(head->root, "dfg", 200);

    Warehouse* foundWarehouse = searchWarehouse(head, "Warehouse A");
    if (foundWarehouse != NULL && searchItem(foundWarehouse->root, "dfg") != NULL) {
        printf("Done");
    } else {
        printf("FAIL");
    }

    // Clean up
}



*/