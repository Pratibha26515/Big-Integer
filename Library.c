#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addDigit(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

char* reverseString(const char* str) {
    int length = strlen(str);
    char* reversedStr = (char*)malloc(length + 1);
    reversedStr[length] = '\0';

    for (int i = 0; i < length; i++) {
        reversedStr[i] = str[length - i - 1];
    }

    return reversedStr;
}

void freeNodeList(struct Node* num) {
    while (num) {
        struct Node* temp = num;
        num = num->next;
        free(temp);
    }
}

int compareBigNumbers(struct Node* num1, struct Node* num2) {
    while (num1 && num2) {
        if (num1->data > num2->data) {
            return 1;
        } else if (num1->data < num2->data) {
            return -1;
        }
        num1 = num1->next;
        num2 = num2->next;
    }
    while (num1) {
        if (num1->data > 0) {
            return 1;
        }
        num1 = num1->next;
    }
    while (num2) {
        if (num2->data > 0) {
            return -1;
        }
        num2 = num2->next;
    }
    return 0;
}

char* listToString(struct Node* num) {
    int length = 0;
    struct Node* current = num;

    while (current) {
        length++;
        current = current->next;
    }

    char* resultStr = (char*)malloc(length + 1);
    resultStr[length] = '\0';

    current = num;
    int i = 0;
    while (current) {
        resultStr[length - 1 - i] = current->data + '0';
        i++;
        current = current->next;
    }

    return resultStr;
}

struct Node* add(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    int carry = 0;

    while (num1 || num2 || carry) {
        int sum = carry;

        if (num1) {
            sum += num1->data;
            num1 = num1->next;
        }

        if (num2) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum %= 10;

        addDigit(&result, sum);
    }

    return result;
}

struct Node* subtract(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    int borrow = 0;

    while (num1 || num2 || borrow) {
        int diff = borrow;

        if (num1) {
            diff += num1->data;
            num1 = num1->next;
        }

        if (num2) {
            diff -= num2->data;
            num2 = num2->next;
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        addDigit(&result, diff);
    }

    return result;
}

struct Node* divide(struct Node* num1, struct Node* num2) {
    if (num2 == NULL || compareBigNumbers(num2, createNode(0)) == 0) {
        return NULL;
    }

    struct Node* quotient = NULL;
    struct Node* current = num1;
    struct Node* partialDividend = NULL;
    int isQuotientNonZero = 0;

    while (current) {
        if (!partialDividend) {
            partialDividend = createNode(current->data);
        } else {
            addDigit(&partialDividend, current->data);
        }

        int quotientDigit = 0;

        while (compareBigNumbers(partialDividend, num2) >= 0) {
            isQuotientNonZero = 1;
            partialDividend = subtract(partialDividend, num2);
            quotientDigit++;
        }

        if (isQuotientNonZero || current->next) {
            addDigit(&quotient, quotientDigit);
        }

        current = current->next;
    }

    if (!quotient) {
        quotient = createNode(0);
    }

    return quotient;
}

struct Node* multiply(struct Node* num1, struct Node* num2) {
    struct Node* result = createNode(0);

    struct Node* current2 = num2;
    int position = 0;

    while (current2) {
        int digit = current2->data;
        struct Node* tempResult = createNode(0);
        struct Node* carryList = NULL;
        struct Node* tempNum1 = num1;

        int paddingZeros = position;

        while (tempNum1) {
            int temp = tempNum1->data * digit;

            if (carryList) {
                temp += carryList->data;
                carryList = carryList->next;
            }

            addDigit(&tempResult, temp % 10);

            if (temp >= 10) {
                addDigit(&carryList, temp / 10);
            }

            tempNum1 = tempNum1->next;
        }

        while (carryList) {
            addDigit(&tempResult, carryList->data);
            carryList = carryList->next;
        }

        paddingZeros = position;
        while (paddingZeros > 0) {
            addDigit(&tempResult, 0);
            paddingZeros--;
        }

        result = add(result, tempResult);

        current2 = current2->next;
        position++;
    }

    return result;
}

struct Node* modulus(struct Node* num1, struct Node* num2) {
    if (num2 == NULL || compareBigNumbers(num2, createNode(0)) == 0) {
        return NULL;
    }

    struct Node* current = num1;
    struct Node* partialDividend = NULL;

    while (current) {
        if (!partialDividend) {
            partialDividend = createNode(current->data);
        } else {
            addDigit(&partialDividend, current->data);
        }

        while (compareBigNumbers(partialDividend, num2) >= 0) {
            partialDividend = subtract(partialDividend, num2);
        }

        current = current->next;
    }

    return partialDividend;
}

