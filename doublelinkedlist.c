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

void swap(int* x, int* y)
    {
        int temp = *x;
        *x = *y;
        *y = temp;
    }

void initList(DoubleList* list)
    {
        list->first = NULL;
        list->last = NULL;
    }

bool isEmptyList(DoubleList* list)
    {
        return (list->first == NULL);
    }

void makeEmptyList(DoubleList* list)
    {
        if(isEmptyList(list)) return;
        Node* curr = list->first;
        Node* temp = NULL;
        while(curr != NULL)
            {
                temp = curr->next;
                free(curr);
                curr = temp;
            }
        list->first = NULL;
        list->last = NULL;
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

void deleteAtLast(DoubleList* list)
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
        Node* temp = list->last;
        list->last = list->last->prev;
        list->last->next = NULL;
        free(temp);
    }

void deleteAtPos(DoubleList* list, int pos)
    {
        if(pos <= 0 || isEmptyList(list)) return;
        if(pos == 1)
            {
                deleteAtFirst(list);
                return;
            }
        Node* curr = list->first;
        for(int i = 1; i < pos; i++)
            {
                if(curr == NULL) return;
                curr = curr->next;
            }
        if(curr == NULL) return;
        if(curr == list->last)
            {
                deleteAtLast(list);
                return;
            }
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        free(curr); 
    }

int findNode(DoubleList* list, int value)
    {
        if(isEmptyList(list)) return 0;
        Node* curr = list->first;
        int index = 0;
        while(curr != NULL)
            {
                index++;
                if(curr->data == value)
                    return index;
                curr = curr->next;
            }
        return -1;
    }

void sandwichZ(DoubleList* list, int x, int y, int z)
    {
        if(isEmptyList(list)) return;
        int pos = findNode(list, z);
        if(pos == -1) return;
        addToPos(list, y, pos + 1);
        addToPos(list, x, pos);
        //addToPos(list, y, pos + 1);
    }

void deleteAllX(DoubleList* list, int x)
    {
        if(isEmptyList(list)) return;
        while(findNode(list, x) != -1)
            {
                deleteAtPos(list, findNode(list, x));
            }
    }

void sortAscending(DoubleList* list)
    {
        if(isEmptyList(list)) return;
        for(Node* curr1 = list->first; curr1 != NULL; curr1 = curr1->next)
            {
                for(Node* curr2 = curr1; curr2 != NULL; curr2 = curr2->next)
                    {
                        if(curr2->data < curr1->data)
                            {
                                swap(&(curr2->data), &(curr1->data));
                            }
                    }
            }
    }

void searchHistory(DoubleList* list, int val)
    {
        if(isEmptyList(list)) return;
        deleteAllX(list, val);
        addToFirst(list, val);
    }

void deleteHistory(DoubleList* list)
    {
        makeEmptyList(list);
    }

void revList(DoubleList* list)
    {
        if(isEmptyList(list)) return;
        Node* fast = list->first;
        Node* slow = list->first;
        for(fast, slow; fast != NULL; fast = fast->next->next, slow = slow->next)
            {
                if(fast->next == NULL) break;
            }
        for(Node* curr1 = list->first, *curr2 = list->last; curr1->prev != slow && curr2->next != slow; curr1 = curr1->next, curr2 = curr2->prev)
            {
                swap(&(curr1->data), &(curr2->data));
            }
    }

void deleteRepeatingNode(DoubleList* list)
    {
        if(isEmptyList(list)) return;
        int index1 = 0;
        int index2 = 0;
        bool hasMultipleInstances = false;
        for(Node* curr1 = list->first; curr1 != NULL; curr1 = curr1->next)
            {
                index1++;
                index2 = index1;
                for(Node* curr2 = curr1->next; curr2 != NULL; curr2 = curr2->next)
                    {
                        index2++;
                        if(curr2->data == curr1->data)
                            {
                                deleteAtPos(list, index2);
                                hasMultipleInstances = true;
                                index2--;
                            }
                    }
                if(hasMultipleInstances)
                    {
                        deleteAtPos(list, index1);
                        hasMultipleInstances = false;
                        index1--;
                    }
            }
    }

void putLargesttoFront(DoubleList* list)
    {
        int index = 0;
        Node* largest = list->first;
        for(Node* curr = list->first; curr != NULL; curr = curr->next)
            {
                if(curr->data > largest->data)
                    {
                        largest = curr;
                    }
            }
        for(Node* curr = list->first; curr != NULL; curr = curr->next)
            {
                index++;
                if(curr->data == largest->data)
                    {
                        addToFirst(list, curr->data);
                        deleteAtPos(list, index + 1);
                    }
            }
    }

int main()
    {
        DoubleList list;
        initList(&list);
        
        addToFirst(&list, 1);
        addToFirst(&list, 2);
        addToFirst(&list, 3);
        addToFirst(&list, 10);
        addToFirst(&list, -1);
        addToLast(&list, 10);
        addToLast(&list, 9);
        addToPos(&list, 10, 1);

        printList(&list);

        sandwichZ(&list, -1, -2, 1);
        revList(&list);
        sortAscending(&list);
        searchHistory(&list, 66);
        //makeEmptyList(&list);
        deleteRepeatingNode(&list);
        putLargesttoFront(&list);

        printList(&list);

        revList(&list);
        printList(&list);
        sortAscending(&list);
        printList(&list);

        return 0;
    }

/*-reverse
  -deleteSimilar
  -pushLargesttoFirst*/