#include <stdio.h>
#include <stdbool.h>

#define SIZE 24
#define ROWS 8
#define COLUMNS 3

void print_array(int array[], int length);
void print_matrix(int matrix[][COLUMNS], int rows);
bool isValid(const int array[], int length, int index);
void remove_element(int array[], int length, int index);
void insert_element(int array[], int length, int index, int value);
void reshape(const int array[], int length, int rows, int columns, int array_2[rows][columns]);
void trans_matrix(int rows, int columns, const int matrix[rows][columns], int transposed[columns][rows]);
bool found_duplicate(const int array[], int length);

int main() 
{
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) 
    {
        array[i] = (i + 1) * 10;
    }

    int array_2[ROWS][COLUMNS];
    int transposed[COLUMNS][ROWS];

    // Running print_array function
    printf("Running print_array function:\n");
    print_array(array, SIZE);
    printf("\n-------------------\n");

    // Running print_matrix function
    printf("Running print_matrix function:\n");
    print_matrix(array_2, ROWS);
    printf("\n-------------------\n");

    // Running isValid function
    printf("Running isValid function:\n");
    printf("isValid(array, SIZE, 5) -> %d\n", isValid(array, SIZE, 5));
    printf("isValid(array, SIZE, 30) -> %d\n", isValid(array, SIZE, 30));
    printf("\n-------------------\n");

    // Running remove_element function
    printf("Running remove_element function:\n");
    remove_element(array, SIZE, 2);
    print_array(array, SIZE - 1);
    printf("\n-------------------\n");

    // Running insert_element function
    printf("Running insert_element function:\n");
    insert_element(array, SIZE - 1, 2, 80);
    print_array(array, SIZE);
    printf("\n-------------------\n");

    // Running reshape function
    printf("Running reshape function:\n");
    reshape(array, SIZE, ROWS, COLUMNS, array_2);
    print_matrix(array_2, ROWS);
    printf("\n-------------------\n");

    // Running trans_matrix function
    printf("Running trans_matrix function:\n");
    trans_matrix(ROWS, COLUMNS, array_2, transposed);
    for (int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }
    printf("\n-------------------\n");

    // Running found_duplicate function
    printf("Running found_duplicate function:\n");
    printf("found_duplicate(array, SIZE) -> %d\n", found_duplicate(array, SIZE));
    printf("\n-------------------\n");

    return 0;
}


void print_array(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }
}

void print_matrix(int matrix[][COLUMNS], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("matrix[%d][%d] = %d ", i, j, matrix[i][j]);
        }
        printf("\n");
    }
}

bool isValid(const int array[], int length, int index) {
    return index >= 0 && index < length;
}

void remove_element(int array[], int length, int index) {
    if (!isValid(array, length, index)) {
        printf("Invalid index for removal.\n");
        return;
    }
    for (int i = index; i < length - 1; i++) {
        array[i] = array[i + 1];
    }
}

void insert_element(int array[], int length, int index, int value) {
    if (!isValid(array, length, index)) {
        printf("Invalid index for insertion.\n");
        return;
    }
    for (int i = length - 1; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = value;
}

void reshape(const int array[], int length, int rows, int columns, int array_2[rows][columns]) {
    if (length != rows * columns) {
        printf("Error: The length of 1D array does not match the 2D array dimensions.\n");
        return;
    }
    for (int col = 0, k = 0; col < columns; col++) {
        for (int row = 0; row < rows; row++) {
            array_2[row][col] = array[k++];
        }
    }
}

void trans_matrix(int rows, int columns, const int matrix[rows][columns], int transposed[columns][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
}

bool found_duplicate(const int array[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] == array[j]) {
                return true;
            }
        }
    }
    return false;
}
