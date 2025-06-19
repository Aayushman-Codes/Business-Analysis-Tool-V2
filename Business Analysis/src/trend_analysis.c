/**
 * Trend Analysis Implementation File
 * Contains implementations of trend analysis functions
 */

#include "trend_analysis.h"
#include "billing.h"
#include "product.h"
#include "financial.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "globals.h"

// Function to run the trend analysis module
void runTrendAnalysis() {
    int choice;
    bool running = true;

    while (running) {
        clearScreen();
        printf("\n\033[1;36m========================================\033[0m\n");
        printf("\033[1;32m          TREND ANALYSIS\033[0m\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("1. Sales Trends\n");
        printf("2. Product Sales Analysis\n");
        printf("3. Category Sales Analysis\n");
        printf("4. Profit Trends\n");
        printf("5. Expense Trends\n");
        printf("6. Sales Forecast\n");
        printf("7. Back to Main Menu\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: {
                char startDate[20], endDate[20], interval[10];
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                printf("Enter interval (daily, weekly, monthly): ");
                fgets(interval, sizeof(interval), stdin);
                interval[strcspn(interval, "\n")] = 0;
                
                if (generateSalesTrend(startDate, endDate, interval)) {
                    char title[100], xLabel[50], yLabel[50];
                    snprintf(title, sizeof(title), "Sales Trend (%s to %s)", startDate, endDate);
                    snprintf(xLabel, sizeof(xLabel), "Date (%s)", interval);
                    sprintf(yLabel, "Sales Amount ($)");
                    
                    printf("Would you like to visualize this trend? (y/n): ");
                    char visualizeChoice;
                    scanf("%c", &visualizeChoice);
                    clearInputBuffer();
                    
                    if (visualizeChoice == 'y' || visualizeChoice == 'Y') {
                        showSalesGraph(SALES_DATA_CSV, title, xLabel, yLabel);
                    }
                } else {
                    displayError("Failed to generate sales trend data.");
                }
                pressEnterToContinue();
                break;
            }
            case 2: {
                int productId;
                char startDate[20], endDate[20], interval[10];
                
                printf("Enter product ID (0 for all products): ");
                scanf("%d", &productId);
                clearInputBuffer();
                
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                printf("Enter interval (daily, weekly, monthly): ");
                fgets(interval, sizeof(interval), stdin);
                interval[strcspn(interval, "\n")] = 0;
                
                if (generateProductSalesTrend(productId, startDate, endDate, interval)) {
                    char title[100], xLabel[50], yLabel[50];
                    
                    if (productId == 0) {
                        snprintf(title, sizeof(title), "Product Sales Comparison (%s to %s)", startDate, endDate);
                    } else {
                        char productName[50] = "Selected Product";
                        // Get product name if available
                        loadProductData();
                        int index = findProductById(productId);
                        if (index != -1) {
                            strcpy(productName, products[index].name);
                        }
                        snprintf(title, sizeof(title), "%s Sales Trend (%s to %s)", productName, startDate, endDate);
                    }
                    
                    snprintf(xLabel, sizeof(xLabel), "Date (%s)", interval);
                    sprintf(yLabel, "Sales Amount ($)");
                    
                    printf("Would you like to visualize this trend? (y/n): ");
                    char visualizeChoice;
                    scanf("%c", &visualizeChoice);
                    clearInputBuffer();
                    
                    if (visualizeChoice == 'y' || visualizeChoice == 'Y') {
                        showSalesGraph(SALES_DATA_CSV, title, xLabel, yLabel);
                    }
                } else {
                    displayError("Failed to generate product sales trend data.");
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                char category[30], startDate[20], endDate[20], interval[10];
                
                printf("Enter category (leave blank for all categories): ");
                fgets(category, sizeof(category), stdin);
                category[strcspn(category, "\n")] = 0;
                
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                printf("Enter interval (daily, weekly, monthly): ");
                fgets(interval, sizeof(interval), stdin);
                interval[strcspn(interval, "\n")] = 0;
                
                if (generateCategorySalesTrend(category, startDate, endDate, interval)) {
                    char title[100], xLabel[50], yLabel[50];
                    
                    if (strlen(category) == 0) {
                        snprintf(title, sizeof(title), "Category Sales Comparison (%s to %s)", startDate, endDate);
                    } else {
                        snprintf(title, sizeof(title), "%s Category Sales Trend (%s to %s)", category, startDate, endDate);
                    }
                    
                    snprintf(xLabel, sizeof(xLabel), "Date (%s)", interval);
                    sprintf(yLabel, "Sales Amount ($)");
                    
                    printf("Would you like to visualize this trend? (y/n): ");
                    char visualizeChoice;
                    scanf("%c", &visualizeChoice);
                    clearInputBuffer();
                    
                    if (visualizeChoice == 'y' || visualizeChoice == 'Y') {
                        showSalesGraph(SALES_DATA_CSV, title, xLabel, yLabel);
                    }
                } else {
                    displayError("Failed to generate category sales trend data.");
                }
                pressEnterToContinue();
                break;
            }
            case 4: {
                char startDate[20], endDate[20], interval[10];
                
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                printf("Enter interval (daily, weekly, monthly): ");
                fgets(interval, sizeof(interval), stdin);
                interval[strcspn(interval, "\n")] = 0;
                
                if (generateProfitTrend(startDate, endDate, interval)) {
                    char title[100], xLabel[50], yLabel[50];
                    snprintf(title, sizeof(title), "Profit Trend (%s to %s)", startDate, endDate);
                    snprintf(xLabel, sizeof(xLabel), "Date (%s)", interval);
                    sprintf(yLabel, "Profit Amount ($)");
                    
                    printf("Would you like to visualize this trend? (y/n): ");
                    char visualizeChoice;
                    scanf("%c", &visualizeChoice);
                    clearInputBuffer();
                    
                    if (visualizeChoice == 'y' || visualizeChoice == 'Y') {
                        showSalesGraph(SALES_DATA_CSV, title, xLabel, yLabel);
                    }
                } else {
                    displayError("Failed to generate profit trend data.");
                }
                pressEnterToContinue();
                break;
            }
            case 5: {
                char category[30], startDate[20], endDate[20], interval[10];
                
                printf("Enter expense category (leave blank for all categories): ");
                fgets(category, sizeof(category), stdin);
                category[strcspn(category, "\n")] = 0;
                
                printf("Enter start date (YYYY-MM-DD): ");
                fgets(startDate, sizeof(startDate), stdin);
                startDate[strcspn(startDate, "\n")] = 0;
                
                printf("Enter end date (YYYY-MM-DD): ");
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = 0;
                
                printf("Enter interval (daily, weekly, monthly): ");
                fgets(interval, sizeof(interval), stdin);
                interval[strcspn(interval, "\n")] = 0;
                
                if (generateExpenseTrend(category, startDate, endDate, interval)) {
                    char title[100], xLabel[50], yLabel[50];
                    
                    if (strlen(category) == 0) {
                        snprintf(title, sizeof(title), "Expense Trend (%s to %s)", startDate, endDate);
                    } else {
                        snprintf(title, sizeof(title), "%s Expense Trend (%s to %s)", category, startDate, endDate);
                    }
                    
                    snprintf(xLabel, sizeof(xLabel), "Date (%s)", interval);
                    sprintf(yLabel, "Expense Amount ($)");
                    
                    printf("Would you like to visualize this trend? (y/n): ");
                    char visualizeChoice;
                    scanf("%c", &visualizeChoice);
                    clearInputBuffer();
                    
                    if (visualizeChoice == 'y' || visualizeChoice == 'Y') {
                        showSalesGraph(SALES_DATA_CSV, title, xLabel, yLabel);
                    }
                } else {
                    displayError("Failed to generate expense trend data.");
                }
                pressEnterToContinue();
                break;
            }
            case 6: {
                int months;
                printf("Enter number of months to forecast: ");
                scanf("%d", &months);
                clearInputBuffer();
                
                if (months > 0) {
                    generateSalesForecastReport(months);
                } else {
                    displayError("Invalid number of months.");
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

// Function to generate sales trend data for visualization
bool generateSalesTrend(const char *startDate, const char *endDate, const char *interval) {
    if (!startDate || !endDate || !interval) {
        return false;
    }
    
    // Load transaction data
    if (!loadTransactionData()) {
        displayError("Failed to load transaction data.");
        return false;
    }
    
    // Create data directory if it doesn't exist
    if (!createDirectory("data")) {
        displayError("Failed to create data directory.");
        return false;
    }
    
    // Open file for writing
    FILE *file = fopen(SALES_DATA_CSV, "w");
    if (!file) {
        displayError("Failed to open sales data file for writing.");
        return false;
    }
    
    // Write header
    fprintf(file, "Date,Sales\n");
    
    // If no transactions, create an empty file and return
    if (transactionCount == 0) {
        fclose(file);
        return true;
    }
    
    // Determine date range and step size
    // For simplicity, we'll just output all transactions with their dates
    // In a real application, you'd need to properly aggregate by the specified interval
    
    for (int i = 0; i < transactionCount; i++) {
        // Filter by date range
        if (strcmp(transactions[i].date, startDate) >= 0 && 
            strcmp(transactions[i].date, endDate) <= 0) {
            fprintf(file, "%s,%.2f\n", transactions[i].date, transactions[i].total);
        }
    }
    
    fclose(file);
    printf("Sales trend data generated and saved to %s\n", SALES_DATA_CSV);
    return true;
}

// Function to generate product sales trend data for visualization
bool generateProductSalesTrend(int productId, const char *startDate, const char *endDate, const char *interval) {
    if (!startDate || !endDate || !interval) {
        return false;
    }
    
    // Load transaction data
    if (!loadTransactionData()) {
        displayError("Failed to load transaction data.");
        return false;
    }
    
    // Create data directory if it doesn't exist
    if (!createDirectory("data")) {
        displayError("Failed to create data directory.");
        return false;
    }
    
    // Open file for writing
    FILE *file = fopen(SALES_DATA_CSV, "w");
    if (!file) {
        displayError("Failed to open sales data file for writing.");
        return false;
    }
    
    // Write header
    if (productId == 0) {
        // For all products, we'll include product ID in output
        fprintf(file, "Date,ProductID,ProductName,Sales\n");
    } else {
        fprintf(file, "Date,Sales\n");
    }
    
    // If no transactions, create an empty file and return
    if (transactionCount == 0) {
        fclose(file);
        return true;
    }
    
    // Process transactions
    for (int i = 0; i < transactionCount; i++) {
        // Filter by date range
        if (strcmp(transactions[i].date, startDate) >= 0 && 
            strcmp(transactions[i].date, endDate) <= 0) {
            
            // Go through items in transaction
            for (int j = 0; j < transactions[i].itemCount; j++) {
                // Filter by product ID if specified
                if (productId == 0 || transactions[i].items[j].productId == productId) {
                    if (productId == 0) {
                        fprintf(file, "%s,%d,%s,%.2f\n", 
                               transactions[i].date,
                               transactions[i].items[j].productId,
                               transactions[i].items[j].name,
                               transactions[i].items[j].subtotal);
                    } else {
                        fprintf(file, "%s,%.2f\n", 
                               transactions[i].date,
                               transactions[i].items[j].subtotal);
                    }
                }
            }
        }
    }
    
    fclose(file);
    printf("Product sales trend data generated and saved to %s\n", SALES_DATA_CSV);
    return true;
}

// Function to generate category sales trend data for visualization
bool generateCategorySalesTrend(const char *category, const char *startDate, const char *endDate, const char *interval) {
    if (!startDate || !endDate || !interval) {
        return false;
    }
    
    // Load transaction data and product data
    if (!loadTransactionData() || !loadProductData()) {
        displayError("Failed to load transaction or product data.");
        return false;
    }
    
    // Create data directory if it doesn't exist
    if (!createDirectory("data")) {
        displayError("Failed to create data directory.");
        return false;
    }
    
    // Open file for writing
    FILE *file = fopen(SALES_DATA_CSV, "w");
    if (!file) {
        displayError("Failed to open sales data file for writing.");
        return false;
    }
    
    // Write header
    if (!category || strlen(category) == 0) {
        // For all categories, we'll include category in output
        fprintf(file, "Date,Category,Sales\n");
    } else {
        fprintf(file, "Date,Sales\n");
    }
    
    // If no transactions or products, create an empty file and return
    if (transactionCount == 0 || productCount == 0) {
        fclose(file);
        return true;
    }
    
    // Process transactions
    for (int i = 0; i < transactionCount; i++) {
        // Filter by date range
        if (strcmp(transactions[i].date, startDate) >= 0 && 
            strcmp(transactions[i].date, endDate) <= 0) {
            
            // Go through items in transaction
            for (int j = 0; j < transactions[i].itemCount; j++) {
                // Find product to get category
                int productIndex = findProductById(transactions[i].items[j].productId);
                
                if (productIndex != -1) {
                    // Filter by category if specified
                    if (!category || strlen(category) == 0 || 
                        strcmp(products[productIndex].category, category) == 0) {
                        
                        if (!category || strlen(category) == 0) {
                            fprintf(file, "%s,%s,%.2f\n", 
                                   transactions[i].date,
                                   products[productIndex].category,
                                   transactions[i].items[j].subtotal);
                        } else {
                            fprintf(file, "%s,%.2f\n", 
                                   transactions[i].date,
                                   transactions[i].items[j].subtotal);
                        }
                    }
                }
            }
        }
    }
    
    fclose(file);
    printf("Category sales trend data generated and saved to %s\n", SALES_DATA_CSV);
    return true;
}

// Function to generate profit trend data for visualization
bool generateProfitTrend(const char *startDate, const char *endDate, const char *interval) {
    if (!startDate || !endDate || !interval) {
        return false;
    }
    
    // Load financial data
    if (!loadFinancialData()) {
        displayError("Failed to load financial data.");
        return false;
    }
    
    // Create data directory if it doesn't exist
    if (!createDirectory("data")) {
        displayError("Failed to create data directory.");
        return false;
    }
    
    // Open file for writing
    FILE *file = fopen(SALES_DATA_CSV, "w");
    if (!file) {
        displayError("Failed to open sales data file for writing.");
        return false;
    }
    
    // Write header
    fprintf(file, "Date,Income,Expenses,Profit\n");
    
    // If no financial records, create an empty file and return
    if (financialRecordCount == 0) {
        fclose(file);
        return true;
    }
    
    // Process financial records by date
    // For this simple implementation, we'll just output the raw data
    // In a real application, you'd need to properly aggregate by the specified interval
    
    char currentDate[20] = "";
    double dayIncome = 0.0;
    double dayExpenses = 0.0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        // Filter by date range
        if (strcmp(financialRecords[i].date, startDate) >= 0 && 
            strcmp(financialRecords[i].date, endDate) <= 0) {
            
            // Check if we're still on the same date
            if (strcmp(currentDate, financialRecords[i].date) != 0) {
                // Output previous date's data if it's not the first entry
                if (strlen(currentDate) > 0) {
                    fprintf(file, "%s,%.2f,%.2f,%.2f\n", 
                           currentDate, dayIncome, dayExpenses, dayIncome - dayExpenses);
                }
                
                // Reset for new date
                strcpy(currentDate, financialRecords[i].date);
                dayIncome = 0.0;
                dayExpenses = 0.0;
            }
            
            // Add to the appropriate counter
            if (strcmp(financialRecords[i].type, "Income") == 0) {
                dayIncome += financialRecords[i].amount;
            } else if (strcmp(financialRecords[i].type, "Expense") == 0) {
                dayExpenses += financialRecords[i].amount;
            }
        }
    }
    
    // Output the last date's data
    if (strlen(currentDate) > 0) {
        fprintf(file, "%s,%.2f,%.2f,%.2f\n", 
               currentDate, dayIncome, dayExpenses, dayIncome - dayExpenses);
    }
    
    fclose(file);
    printf("Profit trend data generated and saved to %s\n", SALES_DATA_CSV);
    return true;
}

// Function to generate expense trend data for visualization
bool generateExpenseTrend(const char *category, const char *startDate, const char *endDate, const char *interval) {
    if (!startDate || !endDate || !interval) {
        return false;
    }
    
    // Load financial data
    if (!loadFinancialData()) {
        displayError("Failed to load financial data.");
        return false;
    }
    
    // Create data directory if it doesn't exist
    if (!createDirectory("data")) {
        displayError("Failed to create data directory.");
        return false;
    }
    
    // Open file for writing
    FILE *file = fopen(SALES_DATA_CSV, "w");
    if (!file) {
        displayError("Failed to open sales data file for writing.");
        return false;
    }
    
    // Write header
    if (!category || strlen(category) == 0) {
        fprintf(file, "Date,Category,Expenses\n");
    } else {
        fprintf(file, "Date,Expenses\n");
    }
    
    // If no financial records, create an empty file and return
    if (financialRecordCount == 0) {
        fclose(file);
        return true;
    }
    
    // Process financial records
    for (int i = 0; i < financialRecordCount; i++) {
        // Filter by date range and record type
        if (strcmp(financialRecords[i].date, startDate) >= 0 && 
            strcmp(financialRecords[i].date, endDate) <= 0 &&
            strcmp(financialRecords[i].type, "Expense") == 0) {
            
            // Filter by category if specified
            if (!category || strlen(category) == 0 || 
                strcmp(financialRecords[i].category, category) == 0) {
                
                if (!category || strlen(category) == 0) {
                    fprintf(file, "%s,%s,%.2f\n", 
                           financialRecords[i].date,
                           financialRecords[i].category,
                           financialRecords[i].amount);
                } else {
                    fprintf(file, "%s,%.2f\n", 
                           financialRecords[i].date,
                           financialRecords[i].amount);
                }
            }
        }
    }
    
    fclose(file);
    printf("Expense trend data generated and saved to %s\n", SALES_DATA_CSV);
    return true;
}

// Function to export trend data to CSV file for visualization
bool exportTrendData(const char *trendType, const char *filename) {
    if (!trendType || !filename) {
        return false;
    }
    
    // For simplicity, just copy the existing sales data file
    FILE *source = fopen(SALES_DATA_CSV, "r");
    if (!source) {
        displayError("No trend data available to export.");
        return false;
    }
    
    FILE *destination = fopen(filename, "w");
    if (!destination) {
        fclose(source);
        displayError("Failed to open destination file for writing.");
        return false;
    }
    
    char buffer[1024];
    size_t bytesRead;
    
    // Copy file contents
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }
    
    fclose(source);
    fclose(destination);
    
    printf("Trend data exported to %s\n", filename);
    return true;
}

// Function to show sales graph using Python script
bool showSalesGraph(const char *dataFile, const char *title, const char *xLabel, const char *yLabel) {
    // Check if CSV file exists
    if (!fileExists(dataFile)) {
        displayError("Sales data file not found.");
        return false;
    }
    
    // Create a temporary Python script to visualize the data
    const char *pythonScriptPath = "show_sales_graph.py";
    
    FILE *pythonScript = fopen(pythonScriptPath, "w");
    if (!pythonScript) {
        displayError("Failed to create Python script file.");
        return false;
    }
    
    // Write Python script content
    fprintf(pythonScript, "import matplotlib.pyplot as plt\n");
    fprintf(pythonScript, "import pandas as pd\n");
    fprintf(pythonScript, "import sys\n\n");
    
    fprintf(pythonScript, "# Load data from CSV\n");
    fprintf(pythonScript, "try:\n");
    fprintf(pythonScript, "    data = pd.read_csv('%s')\n", dataFile);
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    # Create the plot\n");
    fprintf(pythonScript, "    plt.figure(figsize=(10, 6))\n");
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    # If data has more than 2 columns, it's likely a multi-series plot\n");
    fprintf(pythonScript, "    if len(data.columns) > 2:\n");
    fprintf(pythonScript, "        # Get the first column as x-axis (usually date)\n");
    fprintf(pythonScript, "        x_column = data.columns[0]\n");
    fprintf(pythonScript, "        \n");
    fprintf(pythonScript, "        # Plot each numerical column except the first one\n");
    fprintf(pythonScript, "        for column in data.columns[1:]:\n");
    fprintf(pythonScript, "            if pd.api.types.is_numeric_dtype(data[column]):\n");
    fprintf(pythonScript, "                plt.plot(data[x_column], data[column], marker='o', label=column)\n");
    fprintf(pythonScript, "    else:\n");
    fprintf(pythonScript, "        # Simple 2-column plot\n");
    fprintf(pythonScript, "        plt.plot(data.iloc[:, 0], data.iloc[:, 1], marker='o')\n");
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    # Add labels and title\n");
    fprintf(pythonScript, "    plt.xlabel('%s')\n", xLabel);
    fprintf(pythonScript, "    plt.ylabel('%s')\n", yLabel);
    fprintf(pythonScript, "    plt.title('%s')\n", title);
    fprintf(pythonScript, "    plt.grid(True)\n");
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    # Add legend if there are multiple data series\n");
    fprintf(pythonScript, "    if len(data.columns) > 2:\n");
    fprintf(pythonScript, "        plt.legend()\n");
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    # Rotate x-axis labels for better readability\n");
    fprintf(pythonScript, "    plt.xticks(rotation=45)\n");
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    # Adjust layout\n");
    fprintf(pythonScript, "    plt.tight_layout()\n");
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    # Save the plot\n");
    fprintf(pythonScript, "    plt.savefig('sales_graph.png')\n");
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    # Show the plot\n");
    fprintf(pythonScript, "    plt.show()\n");
    fprintf(pythonScript, "    \n");
    fprintf(pythonScript, "    print('Graph generated successfully!')\n");
    fprintf(pythonScript, "    sys.exit(0)\n");
    fprintf(pythonScript, "except Exception as e:\n");
    fprintf(pythonScript, "    print(f'Error generating graph: {e}')\n");
    fprintf(pythonScript, "    sys.exit(1)\n");
    
    fclose(pythonScript);
    
    // Execute the Python script
    printf("\nGenerating graph... (This may open in a new window)\n");
    
    char command[256];
    snprintf(command, sizeof(command), "python %s", pythonScriptPath);
    
    int result = system(command);
    
    if (result != 0) {
        printf("\nFailed to generate graph. Please make sure Python and matplotlib are installed.\n");
        printf("You can install the required packages with: pip install matplotlib pandas\n");
        return false;
    }
    
    return true;
}

// Function to calculate revenue forecast
double calculateRevenueForecast(int months) {
    // Load transaction data
    if (!loadTransactionData()) {
        return 0.0;
    }
    
    // If there are no transactions, we can't make a forecast
    if (transactionCount < 3) {
        return 0.0;
    }
    
    // Simple linear regression-based forecast
    // For simplicity, we're just using the last few months' total revenue
    // In a real application, you would want a more sophisticated model
    
    // Calculate average monthly revenue from the available data
    double totalRevenue = 0.0;
    for (int i = 0; i < transactionCount; i++) {
        totalRevenue += transactions[i].total;
    }
    
    // Assume the data spans approximately 3 months (simplification)
    double monthlyRevenue = totalRevenue / 3.0;
    
    // Apply a simple growth factor (5% per month)
    double growthFactor = 1.05;
    double forecastedRevenue = monthlyRevenue * pow(growthFactor, months);
    
    return forecastedRevenue;
}

// Function to calculate expense forecast
double calculateExpenseForecast(int months) {
    // Load financial data
    if (!loadFinancialData()) {
        return 0.0;
    }
    
    // Calculate total expenses from financial records
    double totalExpenses = 0.0;
    int expenseCount = 0;
    
    for (int i = 0; i < financialRecordCount; i++) {
        if (strcmp(financialRecords[i].type, "Expense") == 0) {
            totalExpenses += financialRecords[i].amount;
            expenseCount++;
        }
    }
    
    // If there are no expense records, we can't make a forecast
    if (expenseCount == 0) {
        return 0.0;
    }
    
    // Calculate average monthly expenses (assume records span 3 months for simplicity)
    double monthlyExpenses = totalExpenses / 3.0;
    
    // Apply a simple growth factor (3% per month)
    double growthFactor = 1.03;
    double forecastedExpenses = monthlyExpenses * pow(growthFactor, months);
    
    return forecastedExpenses;
}

// Function to calculate profit forecast
double calculateProfitForecast(int months) {
    double revenueForecast = calculateRevenueForecast(months);
    double expenseForecast = calculateExpenseForecast(months);
    
    return revenueForecast - expenseForecast;
}

// Function to generate sales forecast report
void generateSalesForecastReport(int months) {
    double revenueForecast = calculateRevenueForecast(months);
    double expenseForecast = calculateExpenseForecast(months);
    double profitForecast = revenueForecast - expenseForecast;
    double profitMargin = revenueForecast > 0 ? (profitForecast / revenueForecast) * 100.0 : 0.0;
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m      %d-MONTH FORECAST REPORT\033[0m\n", months);
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("Forecasted Monthly Figures:\n\n");
    printf("%-20s $%.2f\n", "Revenue:", revenueForecast);
    printf("%-20s $%.2f\n", "Expenses:", expenseForecast);
    printf("%-20s $%.2f\n", "Profit:", profitForecast);
    printf("%-20s %.1f%%\n", "Profit Margin:", profitMargin);
    
    printf("\nNote: This forecast is based on historical data and assumes similar business conditions.\n");
    printf("Actual results may vary based on market conditions, seasonality, and other factors.\n");
    
    // Export option
    printf("\nWould you like to export this forecast to a CSV file? (y/n): ");
    char exportChoice;
    scanf("%c", &exportChoice);
    clearInputBuffer();
    
    if (exportChoice == 'y' || exportChoice == 'Y') {
        char filename[100];
        snprintf(filename, sizeof(filename), "forecast_report_%d_months.csv", months);
        
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "FORECAST REPORT\n");
            fprintf(file, "Forecast Period,%d months\n\n", months);
            
            fprintf(file, "FORECASTED MONTHLY FIGURES\n");
            fprintf(file, "Revenue,$%.2f\n", revenueForecast);
            fprintf(file, "Expenses,$%.2f\n", expenseForecast);
            fprintf(file, "Profit,$%.2f\n", profitForecast);
            fprintf(file, "Profit Margin,%.1f%%\n", profitMargin);
            
            fclose(file);
            printf("Forecast exported to %s\n", filename);
        } else {
            printf("Failed to export forecast.\n");
        }
    }
}