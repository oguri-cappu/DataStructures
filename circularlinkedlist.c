#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;
typedef struct Node{
    DataType data;
    struct Node* next;
} Node;

typedef struct Ouroboros{
    Node* head;
    Node* tail;
}Ouroboros;

void initList(Ouroboros* list)
    {
        list->head = NULL;
        list->tail = NULL;
    }

bool isEmptyList(Ouroboros* list)
    {
        return (list->head == NULL);
    }

void makeEmptyList(Ouroboros* list)
    {
        if(isEmptyList(list)) return;
        Node* curr = list->head;
        if(list->tail != NULL)
            {
                list->tail->next = NULL;
            }
        Node* temp = NULL;
        while(curr != NULL)
            {
                temp = curr->next;
                free(curr);
                curr = temp;
            }
        list->head = NULL;
    }

void printList(Ouroboros* list)
    {
        Node* curr = list->head;
        do{
            if(isEmptyList(list)) break;
            printf("%d -> ", curr->data);
            curr = curr->next;
        }while(curr != list->head);
        printf("NULL\n");
    }

void addToHead(Ouroboros* list, DataType value)
    {
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return;
        new_node->data = value;
        if(isEmptyList(list))
            {
                list->head = new_node;
                list->tail = new_node;
                new_node->next = new_node;
            }
        else
            {
                new_node->next = list->head;
                list->head = new_node;
                list->tail->next = list->head;
            }
    }

void addToTail(Ouroboros* list, DataType value)
    {
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return;
        new_node->data = value;
        if(isEmptyList(list))
            {
                list->head = new_node;
                list->tail = new_node;
                new_node->next = new_node;
            }
        else
            {
                list->tail->next = new_node;
                list->tail = new_node;
                list->tail->next = list->head;
            }
    }

void addToPos(Ouroboros* list, DataType value, int pos)
    {
        if(isEmptyList(list)) return;
        if(pos <= 0) return;
        if(pos == 1)
            {
                addToHead(list, value);
                return;
            }
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return;
        new_node->data = value;
        Node* curr = list->head;
        for(int i = 1; i < pos - 1; i++)
            {
                if(curr == list->tail) return;
                curr = curr->next;
            }
        if(curr == list->tail)
            {
                addToTail(list, value);
                return;
            }
        else
            {
                new_node->next = curr->next;
                curr->next = new_node;
            }
    }

void deleteAtHead(Ouroboros* list)
    {
        if(isEmptyList(list)) return;
        if(list->head->next == list->tail)
            {
                free(list->head->next);
                list->head = NULL;
                list->tail = NULL;
                return;
            }
        Node* temp = list->head;
        list->head = list->head->next;
        list->tail->next = list->head;
        free(temp);
    }

void deleteAtTail(Ouroboros* list)
    {
        if(isEmptyList(list)) return;
        if(list->head->next == list->tail)
            {
                free(list->head->next);
                list->head = NULL;
                list->tail = NULL;
                return;
            }
        Node* curr = list->head;
        while(curr->next != list->tail)
            curr = curr->next;
        Node* temp = list->tail;
        list->tail = curr;
        list->tail->next = list->head;
        free(temp);
    }

void deleteAtPos(Ouroboros* list, int pos)
    {
        if(pos <= 0) return;
        if(pos == 1)
            {
                deleteAtHead(list);
                return;
            }
        Node* curr = list->head;
        for(int i = 1; i < pos - 1; i++)
            {
                if(curr == list->tail) return;
                curr = curr->next;
            }
        if(curr->next == list->tail)
            {
                deleteAtTail(list);
                return;
            }
        Node* temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
    }

void swap(DataType* x, DataType* y)
    {
        DataType temp = *x;
        *x = *y;
        *y = temp;
    }

void sortAscend(Ouroboros* list)
    {
        bool isStarted = 0;
        if(isEmptyList(list) || list->head->next == list->tail) return;
        for(Node* curr1 = list->head; curr1 != list->head || isStarted == 0; curr1 = curr1->next)
            {
                for(Node* curr2 = curr1; curr2 != list->head || isStarted == 0; curr2 = curr2->next)
                    {
                        isStarted = 1;
                        if(curr2->data < curr1->data)
                            {
                                swap(&(curr2->data), &(curr1->data));
                            }
                    }
            }
    }

int main()
    {
        Ouroboros list;
        initList(&list);
        printf("%d\n", isEmptyList(&list));
        addToTail(&list, 2);
        addToTail(&list, 5);
        addToTail(&list, -3);
        addToTail(&list, 0);
        addToTail(&list, 4);
        addToTail(&list, 10);
        addToTail(&list, 1);
        addToTail(&list, 9);
        printList(&list);

        printf("Sorted: ");
        sortAscend(&list);
        printList(&list);

        return 0;
    }