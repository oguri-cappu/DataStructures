#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

/*single linked list with single pointer and sentinel node approach*/
//done

typedef int DataType;
typedef struct Node{
    DataType data;
    struct Node* next;
} Node;

Node* initList(Node* list)
    {
        list->next = NULL;
        return list;
    }

bool isEmptyList(Node* list)
    {
        if(list == NULL) return 1;
        return (list->next == NULL);
    }

Node* makeEmptyList(Node* list)
    {
        if(isEmptyList(list)) return NULL;
        Node* curr = list->next;
        Node* temp = NULL;
        while(curr != NULL)
            {
                temp = curr->next;
                free(curr);
                curr = temp;
            }
        list->next = NULL;
        return list;
    }

int searchList(Node* list, DataType value)
    {
        if(isEmptyList(list)) return -1;
        Node* curr = list->next;
        int index = 1;
        while(curr != NULL)
            {
                if(curr->data == value)
                    break;
                curr = curr->next;
                index++;
            }
        if(curr == NULL) return -1;
        else return index;
    }

void printList(Node* list)
    {
        Node* curr = list->next;
        while(curr != NULL)
            {
                printf("%d -> ", curr->data);
                curr = curr->next;
            }
        printf("NULL\n");
    }

Node* insertAtFirst(Node* list, DataType value)
    {
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return list;
        new_node->data = value;
        new_node->next = list->next;
        list->next = new_node;
        return list;
    }

Node* insertAtPos(Node* list, DataType value, int pos)
    {
        if(pos <= 0) return list;
        if(pos == 1)
            {
                insertAtFirst(list, value);
                return list;
            }
        Node* curr = list->next;
        for(int i = 1; i < pos - 1; i++)
            {
                if(curr == NULL) return list;
                curr = curr->next;
            }
        if(curr == NULL) return list;
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return list;
        new_node->data = value;
        new_node->next = curr->next;
        curr->next = new_node;
        return list;
    }

Node* insertAtLast(Node* list, DataType value)
    {
        if(list == NULL || list->next == NULL)
            {
                insertAtFirst(list, value);
                return list;
            }
        Node* curr = list;
        while(curr->next != NULL)
            {
                curr = curr->next;
            }
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) return list;
        new_node->data = value;
        new_node->next = NULL;
        curr->next = new_node;
        return list;
    }

Node* deleteAtFirst(Node* list)
    {
        if(isEmptyList(list)) return list;
        Node* temp = list->next;
        list->next = list->next->next;
        free(temp);
        return list;
    }
    
Node* deleteAtLast(Node* list)
    {
        if(isEmptyList(list)) return list;
        Node* curr = list->next;
        while(curr->next->next != NULL)
            curr = curr->next;
        free(curr->next);
        curr->next = NULL;
        return list;
    }

Node* deleteAtPos(Node* list, int pos)
    {
        if(isEmptyList(list)) return list;
        if(pos == 1)
            {
                deleteAtFirst(list);
                return list;
            }
        Node* curr = list->next;
        for (int i = 1; i < pos - 1; i++)
            {
                if(curr == NULL) return list;
                curr = curr->next;
            }
        if(curr == NULL) return list;
        Node* temp = curr->next->next;
        free(curr->next);
        curr->next = temp;
        return list;
    }

int main()
    {
        Node list;
        initList(&list);
        printf("%d\n", isEmptyList(&list));
        insertAtFirst(&list, 8);
        insertAtFirst(&list, 7);
        insertAtFirst(&list, 6);
        insertAtFirst(&list, 5);

        //insertAtPos(&list, 4, 4);

        //insertAtLast(&list, 3);

        //deleteAtFirst(&list);

        printf("%d\n", isEmptyList(&list));
        printList(&list);
        printf("%d\n", searchList(&list, 8));

        // makeEmptyList(&list);
        // printf("%d\n", isEmptyList(&list));
        // insertAtLast(&list, 5);
        makeEmptyList(&list);
        // deleteAtLast(&list);
        // deleteAtFirst(&list);
        deleteAtPos(&list, 2);
        printList(&list);

        return 0;
    }