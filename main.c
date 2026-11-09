#include <stdio.h>
#include "DataStructures.h"

int main()
    {
        int Stack01[MAXSIZE];
        Stack01[0] = 0;

        int value = 0;

        printf("%d", push(Stack01, 1));
        printf("%d", push(Stack01, 1));
        printf("%d", push(Stack01, 2));
        printf("%d", push(Stack01, 3));
        printf("%d\n", push(Stack01, 4));

        // for(Stack01[0]; Stack01[0] > 0; 0)
        //     {
        //         printf("%d\t%d\n", pop(Stack01, &value), value);
        //     }

        while(Stack01[0] > 0)
            {
                printf("%d\t%d\n", pop(Stack01, &value), value);
                peek(Stack01, &value);
                printf("%d\n", value);
            }

        getchar();
        getchar();

        return 0;
    }