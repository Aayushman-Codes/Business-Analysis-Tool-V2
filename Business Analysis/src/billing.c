/**
 * Billing System Implementation File
 * Contains implementations of billing system functions
 */

#include "billing.h"
#include "product.h"
#include "customer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "globals.h"

// Global array to store transactions
extern Transaction transactions[MAX_ARRAY_SIZE];
extern int transactionCount;

// Current transaction
Transaction currentTransaction;
bool hasCurrentTransaction = false;

// Function to run the billing system module
void runBillingSystem() {
    int choice;
    bool running = true;

    // Load transaction data
    loadTransactionData();

    // Initialize current transaction
    memset(&currentTransaction, 0, sizeof(Transaction));
    hasCurrentTransaction = false;

    while (running) {
        clearScreen();
        printf("\n\033[1;36m========================================\033[0m\n");
        printf("\033[1;32m            BILLING SYSTEM\033[0m\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("1. Create New Bill\n");
        printf("2. View Current Bill\n");
        printf("3. Add Item to Bill\n");
        printf("4. Remove Item from Bill\n");
        printf("5. Complete Transaction\n");
        printf("6. Transaction History\n");
        printf("7. Generate Sales Report\n");
        printf("8. Back to Main Menu\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                createTransaction();
                pressEnterToContinue();
                break;
            case 2:
                if (hasCurrentTransaction) {
                    printf("\n\033[1;36m========================================\033[0m\n");
                    printf("\033[1;32m           CURRENT BILL\033[0m\n");
                    printf("\033[1;36m========================================\033[0m\n");
                    printf("Items:\n");
                    
                    for (int i = 0; i < currentTransaction.itemCount; i++) {
                        printf("%d. %s - %d x $%.2f = $%.2f\n", 
                               i + 1,
                               currentTransaction.items[i].name, 
                               currentTransaction.items[i].quantity,
                               currentTransaction.items[i].price,
                               currentTransaction.items[i].subtotal);
                    }
                    
                    printf("\nTotal: $%.2f\n", calculateTransactionTotal());
                } else {
                    printf("No active transaction. Create a new bill first.\n");
                }
                pressEnterToContinue();
                break;
            case 3:
                if (hasCurrentTransaction) {
                    int productId, quantity;
                    printf("Enter product ID: ");
                    scanf("%d", &productId);
                    clearInputBuffer();
                    
                    printf("Enter quantity: ");
                    scanf("%d", &quantity);
                    clearInputBuffer();
                    
                    if (addItemToTransaction(productId, quantity)) {
                        printf("Item added to transaction.\n");
                    }
                } else {
                    printf("No active transaction. Create a new bill first.\n");
                }
                pressEnterToContinue();
                break;
            case 4:
                if (hasCurrentTransaction && currentTransaction.itemCount > 0) {
                    int index;
                    printf("Enter item number to remove (1-%d): ", currentTransaction.itemCount);
                    scanf("%d", &index);
                    clearInputBuffer();
                    
                    if (removeItemFromTransaction(index - 1)) {
                        printf("Item removed from transaction.\n");
                    } else {
                        printf("Invalid item number.\n");
                    }
                } else {
                    printf("No items in the current transaction.\n");
                }
                pressEnterToContinue();
                break;
            case 5:
                if (hasCurrentTransaction && currentTransaction.itemCount > 0) {
                    char customerId[20];
                    char paymentMethod[20];
                    
                    printf("Enter customer ID (leave blank for anonymous): ");
                    fgets(customerId, sizeof(customerId), stdin);
                    customerId[strcspn(customerId, "\n")] = 0;
                    
                    printf("Enter payment method (Cash, Credit Card, Debit Card, etc.): ");
                    fgets(paymentMethod, sizeof(paymentMethod), stdin);
                    paymentMethod[strcspn(paymentMethod, "\n")] = 0;
                    
                    if (completeTransaction(customerId, paymentMethod)) {
                        char receipt[2000];
                        generateReceipt(&transactions[transactionCount - 1], receipt, sizeof(receipt));
                        
                        printf("\n%s\n", receipt);
                        printf("\nTransaction completed successfully!\n");
                        
                        // Reset current transaction
                        memset(&currentTransaction, 0, sizeof(Transaction));
                        hasCurrentTransaction = false;
                    }
                } else {
                    printf("No items in the current transaction.\n");
                }
                pressEnterToContinue();
                break;
            case 6:
                displayTransactionHistory(NULL, NULL, NULL);
                pressEnterToContinue();
                break;
            case 7: {
                char startDate[20], endDate[20];
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                generateSalesReport(startDate, endDate);
                pressEnterToContinue();
                break;
            }
            case 8:
                running = false;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pressEnterToContinue();
        }
    }
}

// Function to create a new transaction
bool createTransaction() {
    if (hasCurrentTransaction) {
        printf("There is already an active transaction. Complete or clear it first.\n");
        return false;
    }
    
    // Initialize new transaction
    memset(&currentTransaction, 0, sizeof(Transaction));
    
    // Generate unique transaction ID
    generateUniqueId("TXN", currentTransaction.transactionId, sizeof(currentTransaction.transactionId));
    
    // Set current date and time
    getCurrentDateTime(currentTransaction.date, sizeof(currentTransaction.date));
    
    currentTransaction.itemCount = 0;
    currentTransaction.total = 0.0;
    
    hasCurrentTransaction = true;
    
    printf("New transaction created. Transaction ID: %s\n", currentTransaction.transactionId);
    return true;
}

// Function to add an item to the current transaction
bool addItemToTransaction(int productId, int quantity) {
    if (!hasCurrentTransaction) {
        displayError("No active transaction.");
        return false;
    }
    
    if (currentTransaction.itemCount >= MAX_ITEMS_PER_TRANSACTION) {
        displayError("Maximum number of items reached for this transaction.");
        return false;
    }
    
    // Load product data
    if (!loadProductData()) {
        displayError("Failed to load product data.");
        return false;
    }
    
    // Find the product
    int productIndex = findProductById(productId);
    if (productIndex == -1) {
        displayError("Product not found.");
        return false;
    }
    
    // Check if product is in stock
    if (products[productIndex].quantity < quantity) {
        displayError("Insufficient stock available.");
        return false;
    }
    
    // Check if product already exists in transaction
    for (int i = 0; i < currentTransaction.itemCount; i++) {
        if (currentTransaction.items[i].productId == productId) {
            // Update quantity and subtotal
            currentTransaction.items[i].quantity += quantity;
            currentTransaction.items[i].subtotal = currentTransaction.items[i].price * currentTransaction.items[i].quantity;
            
            // Update product inventory
            updateProductInventory(productId, -quantity);
            
            return true;
        }
    }
    
    // Add new item to transaction
    currentTransaction.items[currentTransaction.itemCount].productId = productId;
    strcpy(currentTransaction.items[currentTransaction.itemCount].name, products[productIndex].name);
    currentTransaction.items[currentTransaction.itemCount].price = products[productIndex].price;
    currentTransaction.items[currentTransaction.itemCount].quantity = quantity;
    currentTransaction.items[currentTransaction.itemCount].subtotal = products[productIndex].price * quantity;
    
    currentTransaction.itemCount++;
    
    // Update product inventory
    updateProductInventory(productId, -quantity);
    
    return true;
}

// Function to remove an item from the current transaction
bool removeItemFromTransaction(int index) {
    if (!hasCurrentTransaction) {
        return false;
    }
    
    if (index < 0 || index >= currentTransaction.itemCount) {
        return false;
    }
    
    // Return inventory
    updateProductInventory(currentTransaction.items[index].productId, currentTransaction.items[index].quantity);
    
    // Remove item by shifting all elements down
    for (int i = index; i < currentTransaction.itemCount - 1; i++) {
        currentTransaction.items[i] = currentTransaction.items[i + 1];
    }
    
    currentTransaction.itemCount--;
    
    return true;
}

// Function to calculate the total for the current transaction
double calculateTransactionTotal() {
    if (!hasCurrentTransaction) {
        return 0.0;
    }
    
    double total = 0.0;
    
    for (int i = 0; i < currentTransaction.itemCount; i++) {
        total += currentTransaction.items[i].subtotal;
    }
    
    return total;
}

// Function to complete the current transaction
bool completeTransaction(const char *customerId, const char *paymentMethod) {
    if (!hasCurrentTransaction || currentTransaction.itemCount == 0) {
        displayError("No active transaction or no items in the transaction.");
        return false;
    }
    
    // Set customer ID
    if (customerId && strlen(customerId) > 0) {
        strcpy(currentTransaction.customerId, customerId);
    } else {
        strcpy(currentTransaction.customerId, "Anonymous");
    }
    
    // Set payment method
    if (paymentMethod && strlen(paymentMethod) > 0) {
        strcpy(currentTransaction.paymentMethod, paymentMethod);
    } else {
        strcpy(currentTransaction.paymentMethod, "Cash");
    }
    
    // Calculate total
    currentTransaction.total = calculateTransactionTotal();
    
    // Set status
    strcpy(currentTransaction.status, "Completed");
    
    // Add to transactions array
    if (transactionCount < MAX_ARRAY_SIZE) {
        transactions[transactionCount++] = currentTransaction;
        
        // Save transaction data
        saveTransactionData();
        
        return true;
    } else {
        displayError("Transaction database is full. Cannot add more transactions.");
        return false;
    }
}

// Function to generate a receipt for a transaction
void generateReceipt(const Transaction *transaction, char *receipt, size_t bufferSize) {
    char buffer[bufferSize];
    int offset = 0;
    
    // Add header
    offset += snprintf(buffer + offset, bufferSize - offset,
                      "========================================\n"
                      "           RECEIPT\n"
                      "========================================\n"
                      "Transaction ID: %s\n"
                      "Date: %s\n"
                      "Customer: %s\n"
                      "----------------------------------------\n"
                      "Items:\n",
                      transaction->transactionId,
                      transaction->date,
                      transaction->customerId);
    
    // Add items
    for (int i = 0; i < transaction->itemCount; i++) {
        offset += snprintf(buffer + offset, bufferSize - offset,
                          "%d. %s\n   %d x $%.2f = $%.2f\n",
                          i + 1,
                          transaction->items[i].name,
                          transaction->items[i].quantity,
                          transaction->items[i].price,
                          transaction->items[i].subtotal);
    }
    
    // Add footer
    offset += snprintf(buffer + offset, bufferSize - offset,
                      "----------------------------------------\n"
                      "Total: $%.2f\n"
                      "Payment Method: %s\n"
                      "Status: %s\n"
                      "========================================\n"
                      "          Thank You!\n"
                      "========================================\n",
                      transaction->total,
                      transaction->paymentMethod,
                      transaction->status);
    
    // Copy to output buffer
    strncpy(receipt, buffer, bufferSize);
    receipt[bufferSize - 1] = '\0';
}

// Function to display transaction history
void displayTransactionHistory(const char *startDate, const char *endDate, const char *paymentMethod) {
    if (transactionCount == 0) {
        printf("No transaction history available.\n");
        return;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m        TRANSACTION HISTORY\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("%-20s %-20s %-15s %-10s %s\n", 
           "Transaction ID", "Date", "Customer", "Total", "Status");
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < transactionCount; i++) {
        // Apply filters
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            // Simple string comparison (assumes YYYY-MM-DD format)
            if (strcmp(transactions[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            // Simple string comparison (assumes YYYY-MM-DD format)
            if (strcmp(transactions[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (paymentMethod && strlen(paymentMethod) > 0) {
            if (strcmp(transactions[i].paymentMethod, paymentMethod) != 0) {
                include = false;
            }
        }
        
        if (include) {
            printf("%-20s %-20s %-15s $%-10.2f %s\n", 
                   transactions[i].transactionId,
                   transactions[i].date,
                   transactions[i].customerId,
                   transactions[i].total,
                   transactions[i].status);
        }
    }
    
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    // Display transaction details option
    printf("\nEnter transaction ID to view details (or press Enter to return): ");
    char transactionId[20];
    fgets(transactionId, sizeof(transactionId), stdin);
    transactionId[strcspn(transactionId, "\n")] = 0;
    
    if (strlen(transactionId) > 0) {
        displayTransactionDetails(transactionId);
    }
}

// Function to display transaction details
bool displayTransactionDetails(const char *transactionId) {
    int index = findTransactionById(transactionId);
    
    if (index == -1) {
        printf("Transaction not found.\n");
        return false;
    }
    
    char receipt[2000];
    generateReceipt(&transactions[index], receipt, sizeof(receipt));
    
    printf("\n%s\n", receipt);
    
    return true;
}

// Function to save transaction data to file
bool saveTransactionData() {
    FILE *file = fopen(TRANSACTION_FILE, "wb");
    
    if (!file) {
        return false;
    }
    
    // Write the number of transactions
    fwrite(&transactionCount, sizeof(int), 1, file);
    
    // Write the transaction data
    fwrite(transactions, sizeof(Transaction), transactionCount, file);
    
    fclose(file);
    return true;
}

// Function to load transaction data from file
bool loadTransactionData() {
    FILE *file = fopen(TRANSACTION_FILE, "rb");
    
    if (!file) {
        transactionCount = 0;
        return false;
    }
    
    // Read the number of transactions
    fread(&transactionCount, sizeof(int), 1, file);
    
    // Check if the number of transactions is valid
    if (transactionCount < 0 || transactionCount > MAX_ARRAY_SIZE) {
        transactionCount = 0;
        fclose(file);
        return false;
    }
    
    // Read the transaction data
    fread(transactions, sizeof(Transaction), transactionCount, file);
    
    fclose(file);
    return true;
}

// Function to find a transaction by ID
int findTransactionById(const char *transactionId) {
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].transactionId, transactionId) == 0) {
            return i;
        }
    }
    
    return -1; // Not found
}

// Function to calculate total sales for a given period
double calculateTotalSales(const char *startDate, const char *endDate) {
    double total = 0.0;
    
    for (int i = 0; i < transactionCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            // Simple string comparison (assumes YYYY-MM-DD format)
            if (strcmp(transactions[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            // Simple string comparison (assumes YYYY-MM-DD format)
            if (strcmp(transactions[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include && strcmp(transactions[i].status, "Completed") == 0) {
            total += transactions[i].total;
        }
    }
    
    return total;
}

// Function to generate a sales report for a given period
void generateSalesReport(const char *startDate, const char *endDate) {
    if (transactionCount == 0) {
        printf("No transaction data available for report.\n");
        return;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           SALES REPORT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("Period: %s to %s\n\n", 
           (startDate && strlen(startDate) > 0) ? startDate : "All time",
           (endDate && strlen(endDate) > 0) ? endDate : "Present");
    
    // Calculate total sales
    double totalSales = calculateTotalSales(startDate, endDate);
    
    // Count transactions in period
    int transactionCountInPeriod = 0;
    for (int i = 0; i < transactionCount; i++) {
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            if (strcmp(transactions[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            if (strcmp(transactions[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include && strcmp(transactions[i].status, "Completed") == 0) {
            transactionCountInPeriod++;
        }
    }
    
    // Calculate average sale
    double averageSale = transactionCountInPeriod > 0 ? totalSales / transactionCountInPeriod : 0.0;
    
    printf("Total Sales: $%.2f\n", totalSales);
    printf("Number of Transactions: %d\n", transactionCountInPeriod);
    printf("Average Sale: $%.2f\n\n", averageSale);
    
    // Payment method breakdown
    printf("Payment Method Breakdown:\n");
    printf("------------------------\n");
    
    // Count by payment method
    char paymentMethods[MAX_ARRAY_SIZE][20];
    int paymentCounts[MAX_ARRAY_SIZE] = {0};
    double paymentTotals[MAX_ARRAY_SIZE] = {0.0};
    int methodCount = 0;
    
    for (int i = 0; i < transactionCount; i++) {
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            if (strcmp(transactions[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            if (strcmp(transactions[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include && strcmp(transactions[i].status, "Completed") == 0) {
            // Check if payment method already exists
            bool methodExists = false;
            for (int j = 0; j < methodCount; j++) {
                if (strcmp(paymentMethods[j], transactions[i].paymentMethod) == 0) {
                    paymentCounts[j]++;
                    paymentTotals[j] += transactions[i].total;
                    methodExists = true;
                    break;
                }
            }
            
            if (!methodExists && methodCount < MAX_ARRAY_SIZE) {
                strcpy(paymentMethods[methodCount], transactions[i].paymentMethod);
                paymentCounts[methodCount] = 1;
                paymentTotals[methodCount] = transactions[i].total;
                methodCount++;
            }
        }
    }
    
    for (int i = 0; i < methodCount; i++) {
        double percentage = (paymentTotals[i] / totalSales) * 100;
        printf("%s: %d transactions, $%.2f (%.1f%%)\n", 
               paymentMethods[i], paymentCounts[i], paymentTotals[i], percentage);
    }
    
    printf("\n");
    
    // Export option
    printf("Would you like to export this report to a CSV file? (y/n): ");
    char exportChoice;
    scanf("%c", &exportChoice);
    clearInputBuffer();
    
    if (exportChoice == 'y' || exportChoice == 'Y') {
        char filename[100];
        snprintf(filename, sizeof(filename), "sales_report_%s_%s.csv", 
                 (startDate && strlen(startDate) > 0) ? startDate : "all",
                 (endDate && strlen(endDate) > 0) ? endDate : "present");
        
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "Report Period,%s to %s\n", 
                   (startDate && strlen(startDate) > 0) ? startDate : "All time",
                   (endDate && strlen(endDate) > 0) ? endDate : "Present");
            fprintf(file, "Total Sales,$%.2f\n", totalSales);
            fprintf(file, "Number of Transactions,%d\n", transactionCountInPeriod);
            fprintf(file, "Average Sale,$%.2f\n\n", averageSale);
            
            fprintf(file, "Payment Method,Transactions,Total,Percentage\n");
            for (int i = 0; i < methodCount; i++) {
                double percentage = (paymentTotals[i] / totalSales) * 100;
                fprintf(file, "%s,%d,$%.2f,%.1f%%\n", 
                       paymentMethods[i], paymentCounts[i], paymentTotals[i], percentage);
            }
            
            fprintf(file, "\nTransaction Details\n");
            fprintf(file, "Transaction ID,Date,Customer,Total,Payment Method\n");
            
            for (int i = 0; i < transactionCount; i++) {
                bool include = true;
                
                if (startDate && strlen(startDate) > 0) {
                    if (strcmp(transactions[i].date, startDate) < 0) {
                        include = false;
                    }
                }
                
                if (endDate && strlen(endDate) > 0) {
                    if (strcmp(transactions[i].date, endDate) > 0) {
                        include = false;
                    }
                }
                
                if (include && strcmp(transactions[i].status, "Completed") == 0) {
                    fprintf(file, "%s,%s,%s,%.2f,%s\n",
                           transactions[i].transactionId,
                           transactions[i].date,
                           transactions[i].customerId,
                           transactions[i].total,
                           transactions[i].paymentMethod);
                }
            }
            
            fclose(file);
            printf("Report exported to %s\n", filename);
        } else {
            printf("Failed to export report.\n");
        }
    }
}