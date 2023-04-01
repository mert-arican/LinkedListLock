//
//  main.c
//  Homework
//
//  Created by Mert Arıcan on 1.04.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct list {
    int number;
    struct list *next;
} list;

void swap(int *array, int pos1, int pos2) {
    int tmp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = tmp;
}

bool containsTwoCopyOfTheValue(int *array, int size, int value) {
    int i = 0, count = 0;
    for (i = 0; i < size; i++) {
        if (array[i] == value) { count++; if (count == 2) { return true; } }
    }
    return false;
}

void getArrayOfRandomIntegers(int *resultArray, int numberOfIntegersRequired, int maximumValue) {
    int i = 0, count = 0;
    int randomValue = rand() % (maximumValue+1);
    int commonValue = randomValue;
    //    printf("common val: %d\n", commonValue);
    for (i = 0; i < 3; i++) { resultArray[count++] = commonValue; }
    while (count < numberOfIntegersRequired) {
        randomValue = rand() % (maximumValue+1);
        if (randomValue != commonValue && !containsTwoCopyOfTheValue(resultArray, count, randomValue)) {
            resultArray[count++] = randomValue;
        }
    }
    
    // Put commonValue in random positions...
    int chainLenght = numberOfIntegersRequired / 3;
    for (i = 0; i < 3; i++) {
        int randomAppropriatePosition = (i * chainLenght) + (rand() % chainLenght);
        swap(resultArray, i, randomAppropriatePosition);
    }
    //
    //    int chainLength = numberOfIntegersRequired / 3;
    //    int randomPositionForTheCommonValueInSecondChain = chainLength + (rand() % chainLength);
    //    int randomPositionForTheCommonValueInThirdChain = (2*chainLength) + (rand() % chainLength);
    //    swap(resultArray, 1, randomPositionForTheCommonValueInSecondChain);
    //    swap(resultArray, 2, randomPositionForTheCommonValueInThirdChain);
    
    //    for (int i = 0; i < numberOfIntegersRequired; i++) {
    //        printf("%d - ", resultArray[i]);
    //    }
}

void printlist(list *list, int *count, int max) {
    //    printf("List\n");
    if (*count != max) {
        printf("address: %p number: %d - adress: %p\n", list, list->number, list->next);
        *count = (*count) + 1;
        printlist(list->next, count, max);
    }
}

void getChains(list *chain1, list *chain2, list *chain3, int N, int M) {
    int i = 0, j = 0;
    int *arrayOfRandomIntegers = malloc(sizeof(int) * (M*3));
    getArrayOfRandomIntegers(arrayOfRandomIntegers, M*3, N);
    list *arrayOfChains[3] = { chain1, chain2, chain3 };
    printf("NULL: %p\n", NULL);
    for (i = 0; i < 3; i++) {
        list *chain = arrayOfChains[i];
        for (j = 0; j < M; j++) {
            int index = i * M + j;
            chain->number = arrayOfRandomIntegers[index];
            if (j < M-1) {
                list *newNode = malloc(sizeof(list));
                chain->next = newNode;
                newNode->next = (j == M-1) ? arrayOfChains[i] : NULL;
                newNode -> next = NULL;
                chain = newNode;
            }
            else {
                chain -> next = arrayOfChains[i];
            }
        }
    }
    
    for (int i = 0; i < M*3; i++) {
        printf("%d - ", arrayOfRandomIntegers[i]);
    }
    
    printf("\nList\n");
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    printlist(chain1, &count1, M);
    printf("\nList\n");
    
    printlist(chain2, &count2, M);
    printf("\nList\n");
    
    printlist(chain3, &count3, M);
    
    free(arrayOfRandomIntegers);
}

int main(int argc, const char * argv[]) {
    srand((unsigned int) time(NULL));
    // creating variables for taking input...
    int M = 0, N = 0;
    bool userHasEnteredValidInputs = false;
    
    // take input from user...
    while (!userHasEnteredValidInputs) {
        printf("Enter N:");
        scanf("%d", &N);
        printf("Enter M: ");
        scanf("%d", &M);
        
        if (N < ((2*M)-1)) {
            printf("N value should be more than or equal to the value of 2*M - 1.\n");
        }
        else if (M < 1) {
            printf("M should be more than or equal to 1.\n");
        }
        else {
            userHasEnteredValidInputs = true;
        }
    }
    
    list *chain1 = malloc(sizeof(list));
    list *chain2 = malloc(sizeof(list));
    list *chain3 = malloc(sizeof(list));
    getChains(chain1, chain2, chain3, N, M);
    
    //    int array[] = { 1, 1, 1, 1, 1, 1 };
    //    int ii = containsTwoCopyOfTheValue(array, 6, 1);
    //    printf("%d", ii);
    return 0;
}
