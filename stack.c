#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "DataStructures.h"

#define MAXSIZE 100

bool push(int Stack[], int value)
    {
        if(Stack[0] == MAXSIZE - 1) return 0;
        Stack[0] += 1;
        Stack[Stack[0]] = value;
        return 1;
    }

bool pop(int Stack[], int* value)
    {
        if(Stack[0] <= 0) return 0;
        *value = Stack[Stack[0]];
        Stack[0] -= 1;
        return 1;
    }

bool peek(int Stack[], int* value)
    {
        *value = -1;
        if(Stack[0] <= 0) return 0;
        *value = Stack[Stack[0]];
        return 1;
    }

bool isEmpty(int Stack[])
    {
        return Stack[0] == 0;
    }

bool isFull(int Stack[])
    {
        return Stack[0] == (MAXSIZE - 1);
    }

void makeEmpty(int Stack[])
    {
        Stack[0] = 0;
    }

void reverseArr(int arr[], int n)
    {
        int stack[MAXSIZE];
        stack[0] = 0;
        for(int i = 0; i < n; i++)
            push(stack, arr[i]);
        for(int i = 0; i < n; i++)
            pop(stack, &arr[i]);
    }

void reverseString(char string[])
    {
        int stack[MAXSIZE];
        stack[0] = 0;
        for(int i = 0; i < strlen(string); i++)
            push(stack, (int)string[i]);
        for(int i = 0; i < strlen(string); i++)
            {
                int temp = 0;
                pop(stack, &temp);
                string[i] = (char)temp;
            }
    }

void toBinary(int number)
    {
        int stack[MAXSIZE];
        stack[0] = 0;
        
    }

int main()
    {
        
        int Stack01[MAXSIZE];
        Stack01[0] = 0;
        
        int arr[] = {1,2,3,4,5,6};

        char c[MAXSIZE] = "agn lil uabys";
        printf("%d\n", strlen(c));
        printf("%s\n", c);
        reverseString(c);
        printf("%s\n", c);

        reverseArr(arr, 6);
        for(int i = 0; i < 6; i++)
            {
                printf("%d\t", arr[i]);
            }
        
        return 0;
    }