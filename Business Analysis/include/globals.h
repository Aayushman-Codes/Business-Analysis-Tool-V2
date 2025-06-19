#ifndef GLOBALS_H
#define GLOBALS_H

#include "product.h"
#include "billing.h"
#include "financial.h"
#include "utils.h"  // This is where MAX_ARRAY_SIZE is defined

// Now these declarations will know about MAX_ARRAY_SIZE
extern Product products[MAX_ARRAY_SIZE];
extern int productCount;

extern Transaction transactions[MAX_ARRAY_SIZE];
extern int transactionCount;

extern FinancialRecord financialRecords[MAX_ARRAY_SIZE];
extern int financialRecordCount;

#endif