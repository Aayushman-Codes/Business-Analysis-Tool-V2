/**
 * Customer Management Implementation File
 * Contains implementations of customer management functions
 */

#include "customer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "globals.h"

// Global array to store customers
Customer customers[MAX_ARRAY_SIZE];
int customerCount = 0;

// Function to run the customer management module
void runCustomerManagement() {
    int choice;
    bool running = true;

    // Load customer data
    loadCustomerData();

    while (running) {
        clearScreen();
        printf("\n\033[1;36m========================================\033[0m\n");
        printf("\033[1;32m        CUSTOMER MANAGEMENT\033[0m\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("1. Add Customer\n");
        printf("2. Search Customer by ID\n");
        printf("3. Search Customers by Name\n");
        printf("4. Display All Customers\n");
        printf("5. Edit Customer\n");
        printf("6. Delete Customer\n");
        printf("7. Back to Main Menu\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addCustomer();
                pressEnterToContinue();
                break;
            case 2: {
                int id;
                printf("Enter customer ID to search: ");
                scanf("%d", &id);
                clearInputBuffer();
                searchCustomerById(id);
                pressEnterToContinue();
                break;
            }
            case 3: {
                char name[MAX_STRING_LENGTH];
                printf("Enter customer name (or part of name) to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                searchCustomersByName(name);
                pressEnterToContinue();
                break;
            }
            case 4:
                displayAllCustomers();
                pressEnterToContinue();
                break;
            case 5: {
                int id;
                printf("Enter customer ID to edit: ");
                scanf("%d", &id);
                clearInputBuffer();
                editCustomer(id);
                pressEnterToContinue();
                break;
            }
            case 6: {
                int id;
                printf("Enter customer ID to delete: ");
                scanf("%d", &id);
                clearInputBuffer();
                deleteCustomer(id);
                pressEnterToContinue();
                break;
            }
            case 7:
                running = false;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pressEnterToContinue();
        }
    }
}

// Function to add a new customer
bool addCustomer() {
    if (customerCount >= MAX_ARRAY_SIZE) {
        displayError("Customer database is full. Cannot add more customers.");
        return false;
    }

    Customer newCustomer;
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           ADD NEW CUSTOMER\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("Enter ID: ");
    scanf("%d", &newCustomer.id);
    clearInputBuffer();
    
    // Check if ID already exists
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == newCustomer.id) {
            displayError("A customer with this ID already exists.");
            return false;
        }
    }
    
    printf("Enter Name: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    newCustomer.name[strcspn(newCustomer.name, "\n")] = 0; // Remove newline character
    
    printf("Enter Phone: ");
    fgets(newCustomer.phone, sizeof(newCustomer.phone), stdin);
    newCustomer.phone[strcspn(newCustomer.phone, "\n")] = 0;
    
    printf("Enter Email: ");
    fgets(newCustomer.email, sizeof(newCustomer.email), stdin);
    newCustomer.email[strcspn(newCustomer.email, "\n")] = 0;
    
    printf("Enter Address: ");
    fgets(newCustomer.address, sizeof(newCustomer.address), stdin);
    newCustomer.address[strcspn(newCustomer.address, "\n")] = 0;
    
    printf("Enter Notes: ");
    fgets(newCustomer.notes, sizeof(newCustomer.notes), stdin);
    newCustomer.notes[strcspn(newCustomer.notes, "\n")] = 0;
    
    // Add the new customer to the array
    customers[customerCount] = newCustomer;
    customerCount++;
    
    // Sort customers by ID
    sortCustomersById();
    
    // Save customer data
    if (saveCustomerData()) {
        displaySuccess("Customer added successfully.");
        return true;
    } else {
        displayError("Failed to save customer data.");
        return false;
    }
}

// Function to search for a customer by ID
bool searchCustomerById(int id) {
    // Binary search since customers are sorted by ID
    int index = findCustomerById(id);
    
    if (index != -1) {
        printf("\n\033[1;36m========================================\033[0m\n");
        printf("\033[1;32m            CUSTOMER FOUND\033[0m\n");
        printf("\033[1;36m========================================\033[0m\n");
        displayCustomerDetails(&customers[index]);
        return true;
    } else {
        displayError("Customer not found.");
        return false;
    }
}

// Function to search for customers by name
void searchCustomersByName(const char *name) {
    bool found = false;
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           SEARCH RESULTS\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    for (int i = 0; i < customerCount; i++) {
        // Case-insensitive search (crude implementation)
        char lowerName[MAX_STRING_LENGTH];
        char lowerCustomerName[MAX_STRING_LENGTH];
        
        // Convert both strings to lowercase
        strcpy(lowerName, name);
        strcpy(lowerCustomerName, customers[i].name);
        
        for (int j = 0; lowerName[j]; j++) {
            lowerName[j] = tolower(lowerName[j]);
        }
        
        for (int j = 0; lowerCustomerName[j]; j++) {
            lowerCustomerName[j] = tolower(lowerCustomerName[j]);
        }
        
        // Check if substring exists
        if (strstr(lowerCustomerName, lowerName) != NULL) {
            displayCustomerDetails(&customers[i]);
            printf("-------------------\n");
            found = true;
        }
    }
    
    if (!found) {
        printf("No customers found matching '%s'.\n", name);
    }
}

// Function to display all customers
void displayAllCustomers() {
    if (customerCount == 0) {
        printf("No customers in the database.\n");
        return;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           ALL CUSTOMERS\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    for (int i = 0; i < customerCount; i++) {
        displayCustomerDetails(&customers[i]);
        printf("-------------------\n");
    }
}

// Function to display details for a specific customer
void displayCustomerDetails(const Customer *customer) {
    printf("ID: %d\n", customer->id);
    printf("Name: %s\n", customer->name);
    printf("Phone: %s\n", customer->phone);
    printf("Email: %s\n", customer->email);
    printf("Address: %s\n", customer->address);
    printf("Notes: %s\n", customer->notes);
}

// Function to edit a customer's information
bool editCustomer(int id) {
    int index = findCustomerById(id);
    
    if (index == -1) {
        displayError("Customer not found.");
        return false;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           EDIT CUSTOMER\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("Editing customer with ID: %d\n", id);
    printf("Current details:\n");
    displayCustomerDetails(&customers[index]);
    
    printf("\nEnter new details (leave blank to keep current):\n");
    
    char buffer[MAX_STRING_LENGTH];
    
    printf("Name [%s]: ", customers[index].name);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(customers[index].name, buffer);
    }
    
    printf("Phone [%s]: ", customers[index].phone);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(customers[index].phone, buffer);
    }
    
    printf("Email [%s]: ", customers[index].email);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(customers[index].email, buffer);
    }
    
    printf("Address [%s]: ", customers[index].address);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(customers[index].address, buffer);
    }
    
    printf("Notes [%s]: ", customers[index].notes);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(customers[index].notes, buffer);
    }
    
    // Save customer data
    if (saveCustomerData()) {
        displaySuccess("Customer updated successfully.");
        return true;
    } else {
        displayError("Failed to save customer data.");
        return false;
    }
}

// Function to delete a customer
bool deleteCustomer(int id) {
    int index = findCustomerById(id);
    
    if (index == -1) {
        displayError("Customer not found.");
        return false;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           DELETE CUSTOMER\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("Are you sure you want to delete the following customer?\n");
    displayCustomerDetails(&customers[index]);
    
    printf("\nConfirm deletion (y/n): ");
    char confirmation;
    scanf("%c", &confirmation);
    clearInputBuffer();
    
    if (confirmation == 'y' || confirmation == 'Y') {
        // Remove customer by shifting all elements down
        for (int i = index; i < customerCount - 1; i++) {
            customers[i] = customers[i + 1];
        }
        
        customerCount--;
        
        // Save customer data
        if (saveCustomerData()) {
            displaySuccess("Customer deleted successfully.");
            return true;
        } else {
            displayError("Failed to save customer data.");
            return false;
        }
    } else {
        printf("Deletion cancelled.\n");
        return false;
    }
}

// Function to save customer data to file
bool saveCustomerData() {
    FILE *file = fopen(CUSTOMER_FILE, "wb");
    
    if (!file) {
        return false;
    }
    
    // Write the number of customers
    fwrite(&customerCount, sizeof(int), 1, file);
    
    // Write the customer data
    fwrite(customers, sizeof(Customer), customerCount, file);
    
    fclose(file);
    return true;
}

// Function to load customer data from file
bool loadCustomerData() {
    FILE *file = fopen(CUSTOMER_FILE, "rb");
    
    if (!file) {
        customerCount = 0;
        return false;
    }
    
    // Read the number of customers
    fread(&customerCount, sizeof(int), 1, file);
    
    // Check if the number of customers is valid
    if (customerCount < 0 || customerCount > MAX_ARRAY_SIZE) {
        customerCount = 0;
        fclose(file);
        return false;
    }
    
    // Read the customer data
    fread(customers, sizeof(Customer), customerCount, file);
    
    fclose(file);
    return true;
}

// Function to sort customers by ID
void sortCustomersById() {
    // Selection sort algorithm
    for (int i = 0; i < customerCount - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < customerCount; j++) {
            if (customers[j].id < customers[minIndex].id) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            Customer temp = customers[i];
            customers[i] = customers[minIndex];
            customers[minIndex] = temp;
        }
    }
}

// Function to sort customers by name
void sortCustomersByName() {
    // Selection sort algorithm
    for (int i = 0; i < customerCount - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < customerCount; j++) {
            if (strcmp(customers[j].name, customers[minIndex].name) < 0) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            Customer temp = customers[i];
            customers[i] = customers[minIndex];
            customers[minIndex] = temp;
        }
    }
}

// Function to find a customer by ID using binary search
int findCustomerById(int id) {
    int low = 0;
    int high = customerCount - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (customers[mid].id == id) {
            return mid;
        } else if (customers[mid].id < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return -1; // Not found
}