/**
 * Business Analysis and Management System
 * Enhanced version with modular design and improved functionality
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "product.h"
#include "billing.h"
#include "financial.h"
#include "trend_analysis.h"
#include "utils.h"
#include "globals.h"

void displayMainMenu() {
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m    BUSINESS ANALYSIS AND MANAGEMENT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    printf("Choose an option below:\n");
    printf("1) Business Trend Analysis\n");
    printf("2) Customer Management\n");
    printf("3) Product Management\n");
    printf("4) Billing System\n");
    printf("5) Financial Analysis\n");
    printf("6) Exit\n");
    printf("\033[1;36m========================================\033[0m\n");
    printf("Enter your choice: ");
}

void displayWelcomeScreen() {
    clearScreen();
    printf("\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m    BUSINESS ANALYSIS AND MANAGEMENT\033[0m\n");
    printf("\033[1;32m         ENHANCED EDITION\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    printf("Welcome to the enhanced Business Analysis and Management System.\n");
    printf("This application provides tools for analyzing and managing\n");
    printf("various aspects of your business operations.\n\n");
    
    printf("Key Features:\n");
    printf("- \033[1;33mBusiness Trend Analysis\033[0m: Track and visualize business trends\n");
    printf("- \033[1;33mCustomer Management\033[0m: Organize and search customer data\n");
    printf("- \033[1;33mProduct Management\033[0m: Track products, inventory, and pricing\n");
    printf("- \033[1;33mBilling System\033[0m: Generate bills and track transactions\n");
    printf("- \033[1;33mFinancial Analysis\033[0m: Analyze income, expenses, and profitability\n\n");
    
    printf("Press Enter to continue...");
    getchar(); // Wait for user input
}

int main() {
    int choice;
    
    // Initialize system
    initializeSystem();
    
    // Show welcome screen
    displayWelcomeScreen();
    
    do {
        clearScreen();
        displayMainMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                runTrendAnalysis();
                break;
            case 2:
                runCustomerManagement();
                break;
            case 3:
                runProductManagement();
                break;
            case 4:
                runBillingSystem();
                break;
            case 5:
                runFinancialAnalysis();
                break;
            case 6:
                printf("Exiting the application. Thank you for using Business Analysis and Management System!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                pressEnterToContinue();
        }
    } while (choice != 6);
    
    return 0;
}