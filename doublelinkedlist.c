#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct DoubleList{
    Node* first;
    Node* last;
}DoubleList;

void initList(DoubleList* list)
    {
        list->first = NULL;
        list->last = NULL;
    }

bool isEmptyList(DoubleList* list)
    {
        return (list->first == NULL);
    }

void addToFirst(DoubleList* list, int value)
    {
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return;
        new_node->data = value;
        if(isEmptyList(list))
            {
                list->first = new_node;
                list->last = new_node;
                new_node->next = NULL;
                new_node->prev = NULL;
                return;
            }
            list->first->prev = new_node;
            new_node->next = list->first;
            new_node->prev = NULL;
            list->first = new_node;
    }

void addToLast(DoubleList* list, int value)
    {
        if(isEmptyList(list))
            {
                addToFirst(list, value);
                return;
            }
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return;
        new_node->data = value;
        new_node->prev = list->last;
        new_node->next = NULL;
        list->last->next = new_node;
        list->last = new_node;
    }

void addToPos(DoubleList* list, int value, int pos)
    {
        if(pos <= 0) return;
        if(pos == 1)
            {
                addToFirst(list, value);
                return;
            }
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return;
        Node* curr = list->first;
        for(int i = 1; i < pos; i++)
            {
                if(curr == NULL) return;
                curr = curr->next;
            }
        if(curr == NULL)
            {
                addToLast(list, value);
                return;
            }
        new_node->data = value;
        new_node->next = curr;
        new_node->prev = curr->prev;
        curr->prev->next = new_node;
        curr->prev = new_node;
    }

void printList(DoubleList* list)
    {
        Node* curr = list->first;
        while(curr != NULL)
            {
                printf("%d -> ", curr->data);
                curr = curr->next;
            }
        printf("NULL\n");
    }

void deleteAtFirst(DoubleList* list)
    {
        if(isEmptyList(list)) return;
        if(list->first == list->last)
            {
                Node* temp = list->first;
                list->first = NULL;
                list->last = NULL;
                free(temp);
                return;
            }
        Node* temp = list->first;
        list->first = list->first->next;
        list->first->prev = NULL;
        free(temp);
    }

int main()
    {
        DoubleList list;
        initList(&list);
        
        addToFirst(&list, 4);
        addToFirst(&list, 3);
        addToFirst(&list, 2);
        addToFirst(&list, 1);
        addToLast(&list, 5);
        addToLast(&list, 6);
        addToPos(&list, 0, 7);
        deleteAtFirst(&list);

        printList(&list);

        return 0;
    }