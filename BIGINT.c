#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Library.h"


int main() {
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;

    char num1Str[100];
    char num2Str[100];

    printf("Enter the first number: ");
    scanf("%s", num1Str);
    num1 = NULL;
    for (int i = 0; num1Str[i]; i++) {
        addDigit(&num1, num1Str[i] - '0');
    }

    printf("Enter the second number: ");
    scanf("%s", num2Str);
    num2 = NULL;
    for (int i = 0; num2Str[i]; i++) {
        addDigit(&num2, num2Str[i] - '0');
    }

    int choice;
    int x = 1;
    while (x) {
        printf("\nMenu:\n");
        printf("1. Add numbers\n");
        printf("2. Subtract numbers\n");
        printf("3. Divide numbers\n");
        printf("4. Multiply numbers\n");
        printf("5. Modulus of numbers\n");
        printf("6. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (num1 && num2) {
                    struct Node* sum = add(num1, num2);
                    char* resultStr = reverseString(listToString(sum));
                    printf("Sum: %s\n", resultStr);
                    free(resultStr);
                    freeNodeList(sum);
                } else {
                    printf("Please enter both numbers first.\n");
                }
                break;
            case 2:
                if (num1 && num2) {
                    struct Node* difference = subtract(num1, num2);
                    char* resultStr = reverseString(listToString(difference));
                    printf("Difference: %s\n", resultStr);
                    free(resultStr);
                    freeNodeList(difference);
                } else {
                    printf("Please enter both numbers first.\n");
                }
                break;
            case 3:
                if (num1 && num2) {
                    struct Node* remainder;
                    struct Node* quotient = divide(num1, num2);
                    char* quotientStr = listToString(quotient);
                    printf("Quotient: %s\n", quotientStr);
                    free(quotientStr);
                    freeNodeList(quotient);
                } else {
                    printf("Please enter both numbers first.\n");
                }
                break;
            case 4:
                if (num1 && num2) {
                    struct Node* product = multiply(num1, num2);
                    char* resultStr = listToString(product);
                    printf("Product: %s\n", resultStr);
                    free(resultStr);
                    freeNodeList(product);
                } else {
                    printf("Please enter both numbers first.\n");
                }
                break;
            case 5:
                if (num1 && num2) {
                    struct Node* remainder = modulus(num1, num2);
                    char* remainderStr = reverseString(listToString(remainder));
                    printf("Remainder: %s\n", remainderStr);
                    free(remainderStr);
                    freeNodeList(remainder);
                } else {
                    printf("Please enter both numbers first.\n");
                }
                break;
            case 6:
                freeNodeList(num1);
                freeNodeList(num2);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\nTo continue, press 1, and to exit, press 0: ");
        scanf("%d", &x);
    }

    return 0;
}

