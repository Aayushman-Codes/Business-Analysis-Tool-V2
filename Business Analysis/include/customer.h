/**
 * Customer Management Header File
 * Contains structures and function declarations for customer management
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdbool.h>

// Customer structure definition
typedef struct {
    int id;              // Unique identifier for the customer
    char name[50];       // Customer's name
    char phone[15];      // Customer's phone number
    char email[50];      // Customer's email address
    char address[100];   // Customer's address
    char notes[200];     // Additional notes about the customer
} Customer;

/**
 * Run the customer management module
 */
void runCustomerManagement();

/**
 * Add a new customer
 * @return true if successful, false otherwise
 */
bool addCustomer();

/**
 * Search for customers
 * Provides multiple search options (by ID, by name, etc.)
 */
void searchCustomers();

/**
 * Search for a customer by ID
 * @param id The ID to search for
 * @return true if found, false otherwise
 */
bool searchCustomerById(int id);

/**
 * Search for customers by name
 * @param name The name (or part of name) to search for
 */
void searchCustomersByName(const char *name);

/**
 * Display all customers
 */
void displayAllCustomers();

/**
 * Display details for a specific customer
 * @param customer Pointer to the customer to display
 */
void displayCustomerDetails(const Customer *customer);

/**
 * Edit a customer's information
 * @param id The ID of the customer to edit
 * @return true if successful, false otherwise
 */
bool editCustomer(int id);

/**
 * Delete a customer
 * @param id The ID of the customer to delete
 * @return true if successful, false otherwise
 */
bool deleteCustomer(int id);

/**
 * Save customer data to file
 * @return true if successful, false otherwise
 */
bool saveCustomerData();

/**
 * Load customer data from file
 * @return true if successful, false otherwise
 */
bool loadCustomerData();

/**
 * Sort customers by ID
 */
void sortCustomersById();

/**
 * Sort customers by name
 */
void sortCustomersByName();

/**
 * Find a customer by ID using binary search (requires sorted array)
 * @param id The ID to search for
 * @return Index of the customer if found, -1 otherwise
 */
int findCustomerById(int id);

#endif /* CUSTOMER_H */