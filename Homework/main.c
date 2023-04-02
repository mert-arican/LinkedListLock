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

/*
 * Struct: node
 * ____________
 * linked list used to represent chain of the lock.
 */

typedef struct node {
    int number;
    struct node *next;
    struct node *prev;
} node;


/*
 * Enum: direction
 * _______________
 * enum that is used to represent direction of the roll.
 */

enum direction { left, right };


/*
 * Function: swap
 * ______________
 * Swaps the elements of the array at the position 'pos1' and 'pos2'.
 */

void swap(int *array, int pos1, int pos2) {
    int tmp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = tmp;
}


/*
 * Function: contains
 * __________________
 * Checks whether the piece of the given array between given range
 *      contains the copy of the given value specified number of times.
 *
 * array: array to check
 * value: value to search for
 * numberOfTimes: how many copies searched for
 * startIndex: starting index for the search (included)
 * endIndex: end index for the search (excluded)
 *
 * returns: 'true' if 'array' contains 'numberOfTimes' copies of the given 'value'
 *      between 'startIndex' and 'endIndex', 'false' otherwise.
 */

bool contains(int *array, int value, int numberOfTimes, int startIndex, int endIndex) {
    int i = 0, count = 0;
    for (i = startIndex; i < endIndex; i++) {
        if (array[i] == value) { count++; if (count == numberOfTimes) { return true; } }
    }
    return false;
}


/*
 * Function: getRandomIntegerBetweenClosedRange
 * ____________________________________________
 * Returns a random integer between given bounds.
 *
 * lowerBound: lower bound for the random integer (included).
 * upperBound: upper bound for the random integer (included).
 *
 * returns: random integer between bounds.
 */

int getRandomIntegerBetweenClosedRange(int lowerBound, int upperBound) {
    return lowerBound + (rand() % (upperBound-lowerBound+1));
}


/*
 * Function: _printChain
 * ____________________
 * Prints the chain of the lock recursively. When 'count' equals to 'M' recursion ends.
 *
 * node: chain cell.
 * count: current number of recursive calls.
 * M: number of elements in the chain.
 *
 * !!! Do not call this directly. Use 'printChain' function instead. !!!
 */

void _printChain(node *node, int count, int M) {
    (count == M-1) ? printf("%d", node->number) : printf("%d - ", node->number);
    if (count < M-1) { _printChain(node->next, ++count, M); }
    else { printf("\n"); }
}


/*
 * Function: printChain
 * ____________________
 * Prints the chain of the lock.
 *
 * chain: starting node of the chain.
 * M: number of nodes in the chain.
 */

void printChain(node *chain, int M) {
    _printChain(chain, 0, M);
}

// MARK: - Value at the position

/*
 * Function: _getValueAtPosition
 * _____________________________
 * Recursive function that returns the value of the node at the given position.
 *
 * node: chain cell
 * count: current number of recursive calls
 * position: specified position
 *
 * returns: the value of the node at the given position.
 * !!! Do not call this directly. Use 'getValueAtPosition' function instead. !!!
 */
int _getValueAtPosition(node *node, int count, int position) {
    if (count == position) { return node->number; }
    return _getValueAtPosition(node->next, ++count, position);
}


/*
 * Function: getValueAtPosition
 * ____________________________
 * Returns the value at the specified position in the chain.
 *
 * chain: starting node of the chain
 * position: specified position
 *
 * returns: the value at the specified position in the chain.
 */

int getValueAtPosition(node *chain, int position) {
    return _getValueAtPosition(chain, 0, position);
}

// MARK: - Position of the value

/*
 * Function: _getPositionOfTheValue
 * ________________________________
 * Recursive function that searchs and returns the position of the specified value in the chain.
 *
 * node: node of the chain
 * position: current number of recursive calls
 * M: number of cells in chain
 * value: search value
 *
 * returns: the position of the given value if it is in the chain, -1 otherwise.
 * !!! Do not call this directly. Use 'getPositionOfTheValue' function instead. !!!
 */

int _getPositionOfTheValue(node *node, int value, int position, int M) {
    if (position == M) { return -1; }
    if (node ->number == value) { return position; }
    else { return _getPositionOfTheValue(node->next, value, ++position, M); }
}


/*
 * Function: getPositionOfTheValue
 * _______________________________
 * Returns the position of the given value if found in chain, -1 otherwise.
 *
 * node: starting node of the chain
 * value: value to search for
 * M: number of cells in the chain
 *
 * returns: the position of the given value if found in chain, -1 otherwise.
 */

int getPositionOfTheValue(node *node, int value, int M) {
    return _getPositionOfTheValue(node, value, 0, M);
}

int getCommonValue(node *chain1, node *chain2, node *chain3, int M) {
    int i = 0;
    for (i = 0; i < M; i++) {
        int value = getValueAtPosition(chain1, i);
        int pos1 = getPositionOfTheValue(chain2, value, M);
        int pos2 = getPositionOfTheValue(chain3, value, M);
        if (pos1 != -1 && pos2 != -1) { return value; }
    }
    return -1;
}

int getNumberOfRollsRequired(int value, node *fixedChain, node *chainToRoll, enum direction direction, int M) {
    int count = 0;
    int initialPosition = getPositionOfTheValue(chainToRoll, value, M);
    int destinationPosition = getPositionOfTheValue(fixedChain, value, M);
    while (initialPosition != destinationPosition) {
        if (direction == left) { initialPosition-- ; initialPosition = (initialPosition == 0) ? M : initialPosition; }
        else { initialPosition++ ; initialPosition = (initialPosition == M) ? 0 : initialPosition ;}
        count++;
    }
    return count;
}

// MARK: - Creating the lock

/*
 * Function: getArrayOfRandomIntegersToCreateLock
 * ______________________________________________
 * Creates an array of integers to create lock.
 *
 * M: How many cells are in each chain of lock.
 * N: Maximum value of the cell.
 *
 * returns: an array with 'M*3' elements that is appropriate for creating lock.
 *      Every "M piece" of the array: (if 'M' = 4 then "M piece" means
 *              subarrays between indices 0,1,2,3 - 4,5,6,7 - 8,9,10,11 in the given order)
 *          - contains random values between 1-N.
 *          - contains the randomly generated common value (i.e. password value).
 *          - and contains no duplicate values.
 *
 *      !!! Caller is responsible for freeing the memory used by the array. !!!
 */

int* getArrayOfRandomIntegersToCreateLock(int M, int N) {
    int i = 0, count = 0;
    int numberOfIntegersRequired = M*3;
    int *array = malloc(sizeof(int) * numberOfIntegersRequired);
    
    int randomValue = getRandomIntegerBetweenClosedRange(1, N);
    int commonValue = randomValue;
//    printf("random: %d\n", randomValue);
    for (i=0; i < 3; i++) { array[i*M] = commonValue; }
    
    while (count < numberOfIntegersRequired) {
        randomValue = getRandomIntegerBetweenClosedRange(1, N);
        
        if (count % M == 0) { count++; }
        
        // if it is for the first two chains...
        if (count < (2*M)) {
            if (!contains(array, randomValue, 1, (count >= M ? M : 0), count)) {
                array[count++] = randomValue;
            }
        }
        // if it is for the last chain...
        else {
            if (!contains(array, randomValue, 2, 0, count) && !contains(array, randomValue, 1, 2*M, count)) {
                array[count++] = randomValue;
            }
        }
    }
    // put common value at random positions..
    for (i = 0; i < 3; i++) {
        int randomAppropriatePosition = getRandomIntegerBetweenClosedRange(i*M, ((i+1)*M)-1);
        swap(array, i*M, randomAppropriatePosition);
    }
    return array;
}

void getChains(node *chain1, node *chain2, node *chain3, int N, int M) {
    int i = 0, j = 0;
    int *arrayOfRandomIntegers = getArrayOfRandomIntegersToCreateLock(M, N);
    node *arrayOfChains[3] = { chain1, chain2, chain3 };
    //    printf("NULL: %p\n", NULL);
    for (i = 0; i < 3; i++) {
        node *chain = arrayOfChains[i];
        for (j = 0; j < M; j++) {
            int index = i * M + j;
            chain->number = arrayOfRandomIntegers[index];
            if (j < M-1) {
                node *newNode = malloc(sizeof(node));
                chain->next = newNode;
                newNode -> next = NULL;
                newNode -> prev = chain;
                chain = newNode;
            }
            else {
                chain -> next = arrayOfChains[i];
                arrayOfChains[i] -> prev = chain;
            }
        }
    }
    
    printf("\nList\n");
    printChain(chain1, M);
    //    printChain(chain1, count1, M, false);
    printf("\nList\n");
    
    printChain(chain2, M);
    //    printChain(chain2, count2, M, false);
    printf("\nList\n");
    
    printChain(chain3, M);
    //    printChain(chain3, count3, M, false);
    
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
        
        if (N < ((2*M)-1)-100) {
            printf("N value should be more than or equal to the value of 2*M - 1.\n");
        }
        else if (M < 1) {
            printf("M should be more than or equal to 1.\n");
        }
        else {
            userHasEnteredValidInputs = true;
        }
    }
    
    node *chain1 = malloc(sizeof(node));
    node *chain2 = malloc(sizeof(node));
    node *chain3 = malloc(sizeof(node));
    getChains(chain1, chain2, chain3, N, M);
    
    int commonValue = getCommonValue(chain1, chain2, chain3, M);
    printf("The common value is: %d\n", commonValue);

    printf("pos: %d\n", getPositionOfTheValue(chain1, commonValue, M));
    printf("pos: %d\n", getPositionOfTheValue(chain2, commonValue, M));
    printf("pos: %d\n", getPositionOfTheValue(chain3, commonValue, M));

    printf("num rolls required (left): %d\n", getNumberOfRollsRequired(commonValue, chain1, chain2, left, M));
    printf("num rolls required (right): %d\n", getNumberOfRollsRequired(commonValue, chain1, chain2, right, M));
    return 0;
}
