#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int DataType;
typedef struct Node
    {
        DataType data;
        struct Node* next;
    } Node;

void InitList(Node** root)
    {
        *root = NULL;
    }

bool isEmptyList(Node* root)
    {
        if(root == NULL)
            return 1;
        else return 0;
    }

void InsertAtEnd(Node** root, DataType value)    //double pointer is a pointer to another pointer
    {
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL)
            {
                exit(1);
            }
        new_node->next = NULL;
        new_node->data = value;

        if(*root == NULL)
            {
                *root = new_node;
                return;
            }

        Node* curr = *root; //1st deference returns the address of Node** root
        while(curr->next != NULL)
            {
                curr = curr->next;  
            }
        curr->next = new_node;
    }

void MakeEmptyList(Node** root)
    {
        Node* curr = *root;
        while(curr != NULL)
            {
                Node* temp = curr;
                curr = curr->next;
                free(temp);
            }
        //*root = NULL;
    }

void InsertAtFirst(Node** root, DataType value)
    {
        Node* temp = malloc(sizeof(Node));
        if(temp == NULL) return;
        temp->data = value;
        temp->next = *root;

        *root = temp;
    }

void InsertAtPos(Node** root, DataType value, int pos)
    {
        if(pos <= 0) return;

        if(pos == 1)
            {
                InsertAtFirst(root, value);
                return;
            }

        Node* curr = *root;

        for(int i = 1; i < pos - 1; i++)
            {
                if(curr == NULL || curr->next == NULL) return;
                curr = curr->next;
            }

        if (curr == NULL) return;

        Node* new_node = malloc(sizeof(Node));
        new_node->data = value;
        new_node->next = curr->next;
        curr->next = new_node;
    }

void DeleteAtFirst(Node** root)
    {
        if(!isEmptyList(*root))
            {
                Node* temp = *root;
                *root = temp->next;
                free(temp);
            }
        else return;
    }

void DeleteAtLast(Node** root)
    {
        if(!isEmptyList(*root))
            {
                if((*root)->next == NULL)
                    {
                        free(*root);
                        *root = NULL;
                        return;
                    }
                Node* curr = *root;
                while(curr->next->next != NULL)
                    curr = curr->next;
                free(curr->next);
                curr->next = NULL;
            }
        else return;
    }

void DeleteAtPos(Node** root, int pos)
    {
        if(isEmptyList(*root)) return;
        if(pos == 1)
            {
                DeleteAtFirst(root);
                return;
            }
        Node* curr = *root;
        for(int i = 1; i < pos - 1; i++)
            curr = curr->next;
        
        if(curr == NULL || curr->next == NULL) return;

        Node* toTrash = curr->next;
        curr->next = curr->next->next;
        free(toTrash);
    }

int searchList(Node** root, DataType value)
    {
        Node* curr = *root;
        int index = 1;
        while(curr != NULL)
            {
                if(curr->data == value)
                    {
                        return index;
                    }
                index++;
                curr = curr->next;
            }
        return -1;
    }

void PrintList(Node* root)
    {
        Node* curr = root;
        while(curr != NULL)
            {
                printf("%d -> ", curr->data);
                curr = curr->next;
            }
        printf("NULL\n");
    }

int main()
    {
        Node* root;
        InitList(&root);

        InsertAtEnd(&root, 10);
        InsertAtEnd(&root, 9);
        InsertAtEnd(&root, 11);
        InsertAtEnd(&root, 13);
        InsertAtEnd(&root, 14);

        InsertAtPos(&root, -7, 1);
        DeleteAtPos(&root, 4);

        DeleteAtFirst(&root);
        DeleteAtLast(&root);

        Node* curr = root;
        PrintList(root);

        printf("List empty: %d\n", isEmptyList(root));

        printf("Location: %d\n", searchList(&root, 2));
        
        MakeEmptyList(&root);
        PrintList(root);

        return 0;
    }