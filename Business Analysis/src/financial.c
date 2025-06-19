/**
 * Financial Analysis Implementation File
 * Contains implementations of financial analysis functions
 */

#include "financial.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "globals.h"

// Global array to store financial records
extern FinancialRecord financialRecords[MAX_ARRAY_SIZE];
extern int financialRecordCount;

// Function to run the financial analysis module
void runFinancialAnalysis() {
    int choice;
    bool running = true;

    // Load financial data
    loadFinancialData();

    while (running) {
        clearScreen();
        printf("\n\033[1;36m========================================\033[0m\n");
        printf("\033[1;32m       FINANCIAL ANALYSIS\033[0m\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("1. Add Financial Record\n");
        printf("2. View Financial Records\n");
        printf("3. Generate Income Statement\n");
        printf("4. Generate Expense Report\n");
        printf("5. Generate Profit and Loss Report\n");
        printf("6. Export Financial Data\n");
        printf("7. Back to Main Menu\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: {
                char date[20];
                char category[30];
                double amount;
                char type[10];
                char description[200];
                
                printf("\n\033[1;36m========================================\033[0m\n");
                printf("\033[1;32m        ADD FINANCIAL RECORD\033[0m\n");
                printf("\033[1;36m========================================\033[0m\n");
                
                printf("Enter date (YYYY-MM-DD): ");
                fgets(date, sizeof(date), stdin);
                date[strcspn(date, "\n")] = 0;
                
                printf("Enter category: ");
                fgets(category, sizeof(category), stdin);
                category[strcspn(category, "\n")] = 0;
                
                printf("Enter amount: ");
                scanf("%lf", &amount);
                clearInputBuffer();
                
                printf("Enter type (Income or Expense): ");
                fgets(type, sizeof(type), stdin);
                type[strcspn(type, "\n")] = 0;
                
                printf("Enter description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0;
                
                if (addFinancialRecord(date, category, amount, type, description)) {
                    displaySuccess("Financial record added successfully.");
                } else {
                    displayError("Failed to add financial record.");
                }
                pressEnterToContinue();
                break;
            }
            case 2: {
                char startDate[20], endDate[20];
                
                printf("Enter start date (YYYY-MM-DD, leave blank for all): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD, leave blank for all): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                displayFinancialRecords(
                    strlen(startDate) > 0 ? startDate : NULL,
                    strlen(endDate) > 0 ? endDate : NULL
                );
                pressEnterToContinue();
                break;
            }
            case 3: {
                char startDate[20], endDate[20];
                
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                generateIncomeStatement(startDate, endDate);
                pressEnterToContinue();
                break;
            }
            case 4: {
                char startDate[20], endDate[20];
                
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                generateExpenseReport(startDate, endDate);
                pressEnterToContinue();
                break;
            }
            case 5: {
                char startDate[20], endDate[20];
                
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                generateProfitLossReport(startDate, endDate);
                pressEnterToContinue();
                break;
            }
            case 6: {
                char filename[100];
                char startDate[20], endDate[20];
                
                printf("Enter filename to export to: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                
                printf("Enter start date (YYYY-MM-DD, leave blank for all): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD, leave blank for all): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                if (exportFinancialData(
                        filename,
                        strlen(startDate) > 0 ? startDate : NULL,
                        strlen(endDate) > 0 ? endDate : NULL
                    )) {
                    displaySuccess("Financial data exported successfully.");
                } else {
                    displayError("Failed to export financial data.");
                }
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

// Function to add a new financial record
bool addFinancialRecord(const char *date, const char *category, double amount, const char *type, const char *description) {
    if (financialRecordCount >= MAX_ARRAY_SIZE) {
        return false;
    }
    
    // Validate inputs
    if (!date || strlen(date) == 0 || !category || strlen(category) == 0 || 
        !type || strlen(type) == 0 || amount <= 0) {
        return false;
    }
    
    // Create new record
    FinancialRecord record;
    strcpy(record.date, date);
    strcpy(record.category, category);
    record.amount = amount;
    strcpy(record.type, type);
    
    if (description && strlen(description) > 0) {
        strcpy(record.description, description);
    } else {
        strcpy(record.description, "");
    }
    
    // Add record to array
    financialRecords[financialRecordCount++] = record;
    
    // Save data
    return saveFinancialData();
}

// Function to calculate income for a given period
double calculateIncome(const char *startDate, const char *endDate) {
    double total = 0.0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            if (strcmp(financialRecords[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            if (strcmp(financialRecords[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include && strcmp(financialRecords[i].type, "Income") == 0) {
            total += financialRecords[i].amount;
        }
    }
    
    return total;
}

// Function to calculate expenses for a given period
double calculateExpenses(const char *startDate, const char *endDate) {
    double total = 0.0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            if (strcmp(financialRecords[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            if (strcmp(financialRecords[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include && strcmp(financialRecords[i].type, "Expense") == 0) {
            total += financialRecords[i].amount;
        }
    }
    
    return total;
}

// Function to calculate profit for a given period
double calculateProfit(const char *startDate, const char *endDate) {
    double income = calculateIncome(startDate, endDate);
    double expenses = calculateExpenses(startDate, endDate);
    
    return income - expenses;
}

// Function to calculate profit margin for a given period
double calculateProfitMargin(const char *startDate, const char *endDate) {
    double income = calculateIncome(startDate, endDate);
    double profit = calculateProfit(startDate, endDate);
    
    if (income > 0) {
        return (profit / income) * 100.0;
    } else {
        return 0.0;
    }
}

// Function to generate income statement for a given period
void generateIncomeStatement(const char *startDate, const char *endDate) {
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m        INCOME STATEMENT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    printf("Period: %s to %s\n\n", startDate, endDate);
    
    // Calculate totals
    double totalIncome = calculateIncome(startDate, endDate);
    double totalExpenses = calculateExpenses(startDate, endDate);
    double profit = totalIncome - totalExpenses;
    double profitMargin = totalIncome > 0 ? (profit / totalIncome) * 100.0 : 0.0;
    
    // Income breakdown by category
    printf("INCOME\n");
    printf("----------------------------------------------\n");
    
    // Get income categories
    char categories[MAX_ARRAY_SIZE][30];
    double categoryTotals[MAX_ARRAY_SIZE] = {0.0};
    int categoryCount = 0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            if (strcmp(financialRecords[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            if (strcmp(financialRecords[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include && strcmp(financialRecords[i].type, "Income") == 0) {
            // Check if category already exists
            bool categoryExists = false;
            for (int j = 0; j < categoryCount; j++) {
                if (strcmp(categories[j], financialRecords[i].category) == 0) {
                    categoryTotals[j] += financialRecords[i].amount;
                    categoryExists = true;
                    break;
                }
            }
            
            if (!categoryExists && categoryCount < MAX_ARRAY_SIZE) {
                strcpy(categories[categoryCount], financialRecords[i].category);
                categoryTotals[categoryCount] = financialRecords[i].amount;
                categoryCount++;
            }
        }
    }
    
    // Display income categories
    for (int i = 0; i < categoryCount; i++) {
        printf("%-30s $%10.2f\n", categories[i], categoryTotals[i]);
    }
    
    printf("----------------------------------------------\n");
    printf("%-30s $%10.2f\n\n", "Total Income", totalIncome);
    
    // Expense breakdown by category
    printf("EXPENSES\n");
    printf("----------------------------------------------\n");
    
    // Reset for expenses
    memset(categories, 0, sizeof(categories));
    memset(categoryTotals, 0, sizeof(categoryTotals));
    categoryCount = 0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            if (strcmp(financialRecords[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            if (strcmp(financialRecords[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include && strcmp(financialRecords[i].type, "Expense") == 0) {
            // Check if category already exists
            bool categoryExists = false;
            for (int j = 0; j < categoryCount; j++) {
                if (strcmp(categories[j], financialRecords[i].category) == 0) {
                    categoryTotals[j] += financialRecords[i].amount;
                    categoryExists = true;
                    break;
                }
            }
            
            if (!categoryExists && categoryCount < MAX_ARRAY_SIZE) {
                strcpy(categories[categoryCount], financialRecords[i].category);
                categoryTotals[categoryCount] = financialRecords[i].amount;
                categoryCount++;
            }
        }
    }
    
    // Display expense categories
    for (int i = 0; i < categoryCount; i++) {
        printf("%-30s $%10.2f\n", categories[i], categoryTotals[i]);
    }
    
    printf("----------------------------------------------\n");
    printf("%-30s $%10.2f\n\n", "Total Expenses", totalExpenses);
    
    // Net profit
    printf("SUMMARY\n");
    printf("----------------------------------------------\n");
    printf("%-30s $%10.2f\n", "Total Income", totalIncome);
    printf("%-30s $%10.2f\n", "Total Expenses", totalExpenses);
    printf("%-30s $%10.2f\n", "Net Profit/Loss", profit);
    printf("%-30s %10.1f%%\n", "Profit Margin", profitMargin);
    
    // Export option
    printf("\nWould you like to export this statement to a CSV file? (y/n): ");
    char exportChoice;
    scanf("%c", &exportChoice);
    clearInputBuffer();
    
    if (exportChoice == 'y' || exportChoice == 'Y') {
        char filename[100];
        snprintf(filename, sizeof(filename), "income_statement_%s_%s.csv", startDate, endDate);
        
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "INCOME STATEMENT\n");
            fprintf(file, "Period,%s to %s\n\n", startDate, endDate);
            
            fprintf(file, "INCOME\n");
            
            // Reset for CSV export
            memset(categories, 0, sizeof(categories));
            memset(categoryTotals, 0, sizeof(categoryTotals));
            categoryCount = 0;
            
            for (int i = 0; i < financialRecordCount; i++) {
                // Apply date filters
                bool include = true;
                
                if (startDate && strlen(startDate) > 0) {
                    if (strcmp(financialRecords[i].date, startDate) < 0) {
                        include = false;
                    }
                }
                
                if (endDate && strlen(endDate) > 0) {
                    if (strcmp(financialRecords[i].date, endDate) > 0) {
                        include = false;
                    }
                }
                
                if (include && strcmp(financialRecords[i].type, "Income") == 0) {
                    // Check if category already exists
                    bool categoryExists = false;
                    for (int j = 0; j < categoryCount; j++) {
                        if (strcmp(categories[j], financialRecords[i].category) == 0) {
                            categoryTotals[j] += financialRecords[i].amount;
                            categoryExists = true;
                            break;
                        }
                    }
                    
                    if (!categoryExists && categoryCount < MAX_ARRAY_SIZE) {
                        strcpy(categories[categoryCount], financialRecords[i].category);
                        categoryTotals[categoryCount] = financialRecords[i].amount;
                        categoryCount++;
                    }
                }
            }
            
            // Write income categories
            for (int i = 0; i < categoryCount; i++) {
                fprintf(file, "%s,$%.2f\n", categories[i], categoryTotals[i]);
            }
            
            fprintf(file, "Total Income,$%.2f\n\n", totalIncome);
            
            fprintf(file, "EXPENSES\n");
            
            // Reset for expenses CSV export
            memset(categories, 0, sizeof(categories));
            memset(categoryTotals, 0, sizeof(categoryTotals));
            categoryCount = 0;
            
            for (int i = 0; i < financialRecordCount; i++) {
                // Apply date filters
                bool include = true;
                
                if (startDate && strlen(startDate) > 0) {
                    if (strcmp(financialRecords[i].date, startDate) < 0) {
                        include = false;
                    }
                }
                
                if (endDate && strlen(endDate) > 0) {
                    if (strcmp(financialRecords[i].date, endDate) > 0) {
                        include = false;
                    }
                }
                
                if (include && strcmp(financialRecords[i].type, "Expense") == 0) {
                    // Check if category already exists
                    bool categoryExists = false;
                    for (int j = 0; j < categoryCount; j++) {
                        if (strcmp(categories[j], financialRecords[i].category) == 0) {
                            categoryTotals[j] += financialRecords[i].amount;
                            categoryExists = true;
                            break;
                        }
                    }
                    
                    if (!categoryExists && categoryCount < MAX_ARRAY_SIZE) {
                        strcpy(categories[categoryCount], financialRecords[i].category);
                        categoryTotals[categoryCount] = financialRecords[i].amount;
                        categoryCount++;
                    }
                }
            }
            
            // Write expense categories
            for (int i = 0; i < categoryCount; i++) {
                fprintf(file, "%s,$%.2f\n", categories[i], categoryTotals[i]);
            }
            
            fprintf(file, "Total Expenses,$%.2f\n\n", totalExpenses);
            
            fprintf(file, "SUMMARY\n");
            fprintf(file, "Total Income,$%.2f\n", totalIncome);
            fprintf(file, "Total Expenses,$%.2f\n", totalExpenses);
            fprintf(file, "Net Profit/Loss,$%.2f\n", profit);
            fprintf(file, "Profit Margin,%.1f%%\n", profitMargin);
            
            fclose(file);
            printf("Statement exported to %s\n", filename);
        } else {
            printf("Failed to export statement.\n");
        }
    }
}

// Function to generate expense report for a given period
void generateExpenseReport(const char *startDate, const char *endDate) {
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m        EXPENSE REPORT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    printf("Period: %s to %s\n\n", startDate, endDate);
    
    // Calculate total expenses
    double totalExpenses = calculateExpenses(startDate, endDate);
    
    // Expense breakdown by category
    printf("EXPENSE BREAKDOWN\n");
    printf("----------------------------------------------\n");
    
    // Get expense categories
    char categories[MAX_ARRAY_SIZE][30];
    double categoryTotals[MAX_ARRAY_SIZE] = {0.0};
    int categoryCount = 0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            if (strcmp(financialRecords[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            if (strcmp(financialRecords[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include && strcmp(financialRecords[i].type, "Expense") == 0) {
            // Check if category already exists
            bool categoryExists = false;
            for (int j = 0; j < categoryCount; j++) {
                if (strcmp(categories[j], financialRecords[i].category) == 0) {
                    categoryTotals[j] += financialRecords[i].amount;
                    categoryExists = true;
                    break;
                }
            }
            
            if (!categoryExists && categoryCount < MAX_ARRAY_SIZE) {
                strcpy(categories[categoryCount], financialRecords[i].category);
                categoryTotals[categoryCount] = financialRecords[i].amount;
                categoryCount++;
            }
        }
    }
    
    // Display expense categories with percentage
    for (int i = 0; i < categoryCount; i++) {
        double percentage = (categoryTotals[i] / totalExpenses) * 100.0;
        printf("%-30s $%10.2f (%5.1f%%)\n", categories[i], categoryTotals[i], percentage);
    }
    
    printf("----------------------------------------------\n");
    printf("%-30s $%10.2f (100.0%%)\n", "Total Expenses", totalExpenses);
    
    // Export option
    printf("\nWould you like to export this report to a CSV file? (y/n): ");
    char exportChoice;
    scanf("%c", &exportChoice);
    clearInputBuffer();
    
    if (exportChoice == 'y' || exportChoice == 'Y') {
        char filename[100];
        snprintf(filename, sizeof(filename), "expense_report_%s_%s.csv", startDate, endDate);
        
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "EXPENSE REPORT\n");
            fprintf(file, "Period,%s to %s\n\n", startDate, endDate);
            
            fprintf(file, "EXPENSE BREAKDOWN\n");
            fprintf(file, "Category,Amount,Percentage\n");
            
            // Write expense categories
            for (int i = 0; i < categoryCount; i++) {
                double percentage = (categoryTotals[i] / totalExpenses) * 100.0;
                fprintf(file, "%s,$%.2f,%.1f%%\n", categories[i], categoryTotals[i], percentage);
            }
            
            fprintf(file, "Total Expenses,$%.2f,100.0%%\n\n", totalExpenses);
            
            fprintf(file, "EXPENSE DETAILS\n");
            fprintf(file, "Date,Category,Amount,Description\n");
            
            // Write expense details
            for (int i = 0; i < financialRecordCount; i++) {
                // Apply date filters
                bool include = true;
                
                if (startDate && strlen(startDate) > 0) {
                    if (strcmp(financialRecords[i].date, startDate) < 0) {
                        include = false;
                    }
                }
                
                if (endDate && strlen(endDate) > 0) {
                    if (strcmp(financialRecords[i].date, endDate) > 0) {
                        include = false;
                    }
                }
                
                if (include && strcmp(financialRecords[i].type, "Expense") == 0) {
                    fprintf(file, "%s,%s,$%.2f,%s\n", 
                           financialRecords[i].date,
                           financialRecords[i].category,
                           financialRecords[i].amount,
                           financialRecords[i].description);
                }
            }
            
            fclose(file);
            printf("Report exported to %s\n", filename);
        } else {
            printf("Failed to export report.\n");
        }
    }
}

// Function to generate profit and loss report for a given period
void generateProfitLossReport(const char *startDate, const char *endDate) {
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m      PROFIT AND LOSS REPORT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    printf("Period: %s to %s\n\n", startDate, endDate);
    
    // Calculate totals
    double totalIncome = calculateIncome(startDate, endDate);
    double totalExpenses = calculateExpenses(startDate, endDate);
    double profit = totalIncome - totalExpenses;
    double profitMargin = totalIncome > 0 ? (profit / totalIncome) * 100.0 : 0.0;
    
    printf("SUMMARY\n");
    printf("----------------------------------------------\n");
    printf("%-30s $%10.2f\n", "Total Income", totalIncome);
    printf("%-30s $%10.2f\n", "Total Expenses", totalExpenses);
    printf("%-30s $%10.2f\n", "Net Profit/Loss", profit);
    printf("%-30s %10.1f%%\n\n", "Profit Margin", profitMargin);
    
    // Monthly breakdown
    printf("MONTHLY BREAKDOWN\n");
    printf("----------------------------------------------\n");
    printf("%-10s %-12s %-12s %-12s\n", "Month", "Income", "Expenses", "Profit/Loss");
    printf("----------------------------------------------\n");
    
    // Get unique months in the period
    char months[MAX_ARRAY_SIZE][10];
    double monthlyIncome[MAX_ARRAY_SIZE] = {0.0};
    double monthlyExpenses[MAX_ARRAY_SIZE] = {0.0};
    int monthCount = 0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate && strlen(startDate) > 0) {
            if (strcmp(financialRecords[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate && strlen(endDate) > 0) {
            if (strcmp(financialRecords[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include) {
            // Extract month (YYYY-MM)
            char month[10];
            strncpy(month, financialRecords[i].date, 7);
            month[7] = '\0';
            
            // Check if month already exists
            bool monthExists = false;
            for (int j = 0; j < monthCount; j++) {
                if (strcmp(months[j], month) == 0) {
                    if (strcmp(financialRecords[i].type, "Income") == 0) {
                        monthlyIncome[j] += financialRecords[i].amount;
                    } else if (strcmp(financialRecords[i].type, "Expense") == 0) {
                        monthlyExpenses[j] += financialRecords[i].amount;
                    }
                    monthExists = true;
                    break;
                }
            }
            
            if (!monthExists && monthCount < MAX_ARRAY_SIZE) {
                strcpy(months[monthCount], month);
                
                if (strcmp(financialRecords[i].type, "Income") == 0) {
                    monthlyIncome[monthCount] = financialRecords[i].amount;
                } else if (strcmp(financialRecords[i].type, "Expense") == 0) {
                    monthlyExpenses[monthCount] = financialRecords[i].amount;
                }
                
                monthCount++;
            }
        }
    }
    
    // Sort months (simple bubble sort)
    for (int i = 0; i < monthCount - 1; i++) {
        for (int j = 0; j < monthCount - i - 1; j++) {
            if (strcmp(months[j], months[j + 1]) > 0) {
                // Swap months
                char tempMonth[10];
                strcpy(tempMonth, months[j]);
                strcpy(months[j], months[j + 1]);
                strcpy(months[j + 1], tempMonth);
                
                // Swap income
                double tempIncome = monthlyIncome[j];
                monthlyIncome[j] = monthlyIncome[j + 1];
                monthlyIncome[j + 1] = tempIncome;
                
                // Swap expenses
                double tempExpenses = monthlyExpenses[j];
                monthlyExpenses[j] = monthlyExpenses[j + 1];
                monthlyExpenses[j + 1] = tempExpenses;
            }
        }
    }
    
    // Display monthly breakdown
    for (int i = 0; i < monthCount; i++) {
        double monthlyProfit = monthlyIncome[i] - monthlyExpenses[i];
        printf("%-10s $%-11.2f $%-11.2f $%-11.2f\n", 
               months[i], 
               monthlyIncome[i], 
               monthlyExpenses[i], 
               monthlyProfit);
    }
    
    // Export option
    printf("\nWould you like to export this report to a CSV file? (y/n): ");
    char exportChoice;
    scanf("%c", &exportChoice);
    clearInputBuffer();
    
    if (exportChoice == 'y' || exportChoice == 'Y') {
        char filename[100];
        snprintf(filename, sizeof(filename), "profit_loss_report_%s_%s.csv", startDate, endDate);
        
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "PROFIT AND LOSS REPORT\n");
            fprintf(file, "Period,%s to %s\n\n", startDate, endDate);
            
            fprintf(file, "SUMMARY\n");
            fprintf(file, "Total Income,$%.2f\n", totalIncome);
            fprintf(file, "Total Expenses,$%.2f\n", totalExpenses);
            fprintf(file, "Net Profit/Loss,$%.2f\n", profit);
            fprintf(file, "Profit Margin,%.1f%%\n\n", profitMargin);
            
            fprintf(file, "MONTHLY BREAKDOWN\n");
            fprintf(file, "Month,Income,Expenses,Profit/Loss\n");
            
            // Write monthly breakdown
            for (int i = 0; i < monthCount; i++) {
                double monthlyProfit = monthlyIncome[i] - monthlyExpenses[i];
                fprintf(file, "%s,$%.2f,$%.2f,$%.2f\n", 
                       months[i], 
                       monthlyIncome[i], 
                       monthlyExpenses[i], 
                       monthlyProfit);
            }
            
            fclose(file);
            printf("Report exported to %s\n", filename);
        } else {
            printf("Failed to export report.\n");
        }
    }
}

// Function to display financial records for a given period
void displayFinancialRecords(const char *startDate, const char *endDate) {
    if (financialRecordCount == 0) {
        printf("No financial records available.\n");
        return;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m        FINANCIAL RECORDS\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    printf("Period: %s to %s\n\n", 
           startDate ? startDate : "All time",
           endDate ? endDate : "Present");
    
    printf("%-10s %-15s %-10s %-10s %s\n", 
           "Date", "Category", "Amount", "Type", "Description");
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    int recordsDisplayed = 0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate) {
            if (strcmp(financialRecords[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate) {
            if (strcmp(financialRecords[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include) {
            printf("%-10s %-15s $%-9.2f %-10s %s\n", 
                   financialRecords[i].date,
                   financialRecords[i].category,
                   financialRecords[i].amount,
                   financialRecords[i].type,
                   financialRecords[i].description);
            
            recordsDisplayed++;
        }
    }
    
    printf("--------------------------------------------------------------------------------------------------------\n");
    printf("Total records: %d\n", recordsDisplayed);
}

// Function to save financial data to file
bool saveFinancialData() {
    FILE *file = fopen(FINANCIAL_FILE, "wb");
    
    if (!file) {
        return false;
    }
    
    // Write the number of records
    fwrite(&financialRecordCount, sizeof(int), 1, file);
    
    // Write the financial record data
    fwrite(financialRecords, sizeof(FinancialRecord), financialRecordCount, file);
    
    fclose(file);
    return true;
}

// Function to load financial data from file
bool loadFinancialData() {
    FILE *file = fopen(FINANCIAL_FILE, "rb");
    
    if (!file) {
        financialRecordCount = 0;
        return false;
    }
    
    // Read the number of records
    fread(&financialRecordCount, sizeof(int), 1, file);
    
    // Check if the number of records is valid
    if (financialRecordCount < 0 || financialRecordCount > MAX_ARRAY_SIZE) {
        financialRecordCount = 0;
        fclose(file);
        return false;
    }
    
    // Read the financial record data
    fread(financialRecords, sizeof(FinancialRecord), financialRecordCount, file);
    
    fclose(file);
    return true;
}

// Function to export financial data to CSV file
bool exportFinancialData(const char *filename, const char *startDate, const char *endDate) {
    if (!filename || strlen(filename) == 0) {
        return false;
    }
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        return false;
    }
    
    fprintf(file, "Date,Category,Amount,Type,Description\n");
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Apply date filters
        bool include = true;
        
        if (startDate) {
            if (strcmp(financialRecords[i].date, startDate) < 0) {
                include = false;
            }
        }
        
        if (endDate) {
            if (strcmp(financialRecords[i].date, endDate) > 0) {
                include = false;
            }
        }
        
        if (include) {
            fprintf(file, "%s,%s,%.2f,%s,%s\n", 
                   financialRecords[i].date,
                   financialRecords[i].category,
                   financialRecords[i].amount,
                   financialRecords[i].type,
                   financialRecords[i].description);
        }
    }
    
    fclose(file);
    return true;
}