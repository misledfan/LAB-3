#include <stdio.h>

int main() {
    // Initial balance is 1000, list of transations
    int balance = 1000;
        int transactions[] = {-2000, 500, 100};


    int totalTransactions = sizeof(transactions) / sizeof(transactions[0]); // Get the number of transactions
    
    // Array to store transactions that couldn't be processed due to insufficient funds
    int missedTransactions[totalTransactions];
    int missedCount = 0; // Keeps track of how many transactions were missed

    // Loop through each transaction in the list
    for (int i = 0; i < totalTransactions; i++) {
        int currentTransaction = transactions[i];

        if (currentTransaction < 0) { // If it's a withdrawal (negative amount)
            if (-currentTransaction > balance) { // Check if there's enough balance
                printf("Skipped transaction %d AED: Not enough funds.\n", currentTransaction);
                missedTransactions[missedCount++] = currentTransaction; // Add to missed transactions
            } else {
                balance += currentTransaction; // Deduct the withdrawal from the balance
                printf("Processed withdrawal of %d AED. New balance: %d AED.\n", -currentTransaction, balance);
            }
        } else { // If it's a deposit (positive amount)
            balance += currentTransaction; // Add the deposit to the balance
            printf("Processed deposit of %d AED. New balance: %d AED.\n", currentTransaction, balance);
        }

        // If the balance hits zero, stop processing any further transactions
        if (balance == 0) {
            printf("Balance has reached 0. No more transactions will be processed.\n");
            // Store any remaining transactions in missedTransactions since they won't be processed
            for (int j = i + 1; j < totalTransactions; j++) {
                missedTransactions[missedCount++] = transactions[j];
            }
            break; // Exit the loop
        }
    }

    // Print the final balance after all transactions
    printf("\nFinal Balance: %d AED\n", balance);
    // Print the transactions that were skipped due to insufficient funds
    printf("Missed Transactions: ");
    for (int i = 0; i < missedCount; i++) {
        printf("%d ", missedTransactions[i]);
    }
    printf("\n");

    return 0; // End of the program
}
