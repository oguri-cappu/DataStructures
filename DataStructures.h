#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#pragma once

#define MAXSIZE 100

// STACK
bool push(int Stack[], int value);
bool pop(int Stack[], int* value);
bool peek(int Stack[], int* value);
bool isEmpty(int Stack[]);
bool isFull(int Stack[]);
void makeEmpty(int Stack[]);
void reverseArr(int arr[], int n);
void reverseString(char string[]);