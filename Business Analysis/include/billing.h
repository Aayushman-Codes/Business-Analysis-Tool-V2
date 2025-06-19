/**
 * Billing System Header File
 * Contains structures and function declarations for the billing system
 */

#ifndef BILLING_H
#define BILLING_H

#include <stddef.h>  // For size_t

#include <stdbool.h>

// Maximum number of items in a transaction
#define MAX_ITEMS_PER_TRANSACTION 20

// Item structure for billing
typedef struct {
    int productId;       // ID of the product
    char name[50];       // Name of the product
    double price;        // Price of the product
    int quantity;        // Quantity purchased
    double subtotal;     // Subtotal for this item (price * quantity)
} BillingItem;

// Transaction structure
typedef struct {
    char transactionId[20];   // Unique transaction ID
    char date[20];            // Date and time of the transaction
    char customerId[20];      // Customer ID (if applicable)
    BillingItem items[MAX_ITEMS_PER_TRANSACTION];  // Items in the transaction
    int itemCount;            // Number of items in the transaction
    double total;             // Total amount
    char paymentMethod[20];   // Payment method
    char status[20];          // Transaction status (completed, pending, etc.)
} Transaction;

/**
 * Run the billing system module
 */
void runBillingSystem();

/**
 * Create a new transaction
 * @return true if successful, false otherwise
 */
bool createTransaction();

/**
 * Add an item to the current transaction
 * @param productId The ID of the product to add
 * @param quantity The quantity to add
 * @return true if successful, false otherwise
 */
bool addItemToTransaction(int productId, int quantity);

/**
 * Remove an item from the current transaction
 * @param index The index of the item to remove
 * @return true if successful, false otherwise
 */
bool removeItemFromTransaction(int index);

/**
 * Calculate the total for the current transaction
 * @return The total amount
 */
double calculateTransactionTotal();

/**
 * Complete the current transaction
 * @param customerId The customer ID (optional)
 * @param paymentMethod The payment method
 * @return true if successful, false otherwise
 */
bool completeTransaction(const char *customerId, const char *paymentMethod);

/**
 * Generate a receipt for a transaction
 * @param transaction The transaction to generate a receipt for
 * @param receipt Buffer to store the receipt
 * @param bufferSize Size of the receipt buffer
 */
void generateReceipt(const Transaction *transaction, char *receipt, size_t bufferSize);

/**
 * Display transaction history
 * @param startDate Start date for filtering (optional)
 * @param endDate End date for filtering (optional)
 * @param paymentMethod Payment method for filtering (optional)
 */
void displayTransactionHistory(const char *startDate, const char *endDate, const char *paymentMethod);

/**
 * Display transaction details
 * @param transactionId The ID of the transaction to display
 * @return true if found, false otherwise
 */
bool displayTransactionDetails(const char *transactionId);

/**
 * Save transaction data to file
 * @return true if successful, false otherwise
 */
bool saveTransactionData();

/**
 * Load transaction data from file
 * @return true if successful, false otherwise
 */
bool loadTransactionData();

/**
 * Find a transaction by ID
 * @param transactionId The ID to search for
 * @return Index of the transaction if found, -1 otherwise
 */
int findTransactionById(const char *transactionId);

/**
 * Calculate total sales for a given period
 * @param startDate Start date for the period
 * @param endDate End date for the period
 * @return Total sales amount
 */
double calculateTotalSales(const char *startDate, const char *endDate);

/**
 * Generate a sales report for a given period
 * @param startDate Start date for the period
 * @param endDate End date for the period
 */
void generateSalesReport(const char *startDate, const char *endDate);

#endif /* BILLING_H */