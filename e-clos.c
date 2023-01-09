#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node
{
    int state;
    char transitions[20];
} node;

void main()
{
    int stateCount;
    printf("Enter the no:of states: ");
    scanf("%d", &stateCount);

    node *NFA = (node *)malloc(sizeof(node) * stateCount);
    node *queue = (node *)malloc(sizeof(node) * stateCount);
    int front = -1, rear = -1;
    int *visited = (int *)malloc(sizeof(int) * stateCount);

    printf("Enter the transitions for:\n");
    for (int i = 0; i < stateCount; ++i)
    {
        printf("State %d : ", i);
        NFA[i].state = i;
        for (int j = 0; j < stateCount; ++j)
            scanf(" %c", &NFA[i].transitions[j]);
    }

    printf("\nEpsilon closure of NFA:\n");
    for (int k = 0; k < stateCount; ++k)
    {
        printf("State %d: { %d", k, k);
        front = rear = 0;
        queue[rear] = NFA[k];

        for (int l = 0; l < stateCount; ++l)
            visited[l] = 0;

        while (front != -1)
        {
            node tmp = queue[front];

            if (front == rear)
                front = rear = -1;
            else
                front++;

            visited[tmp.state] = 1;
            for (int i = 0; i < stateCount; ++i)
            {
                if (tmp.transitions[i] == 'e' && visited[i] != 1)
                {
                    if (front == -1)
                        front = rear = 0;
                    else
                        rear++;
                    queue[rear] = NFA[i];
                    printf(", %d", i);
                    visited[i] = 1;
                }
            }
        }
        printf(" }\n");
    }

    free(NFA);
    free(queue);
    free(visited);
}

/*
1. Read the NFA states and transitions in an adjacency matrix.
2. For each state S in NFA, perform steps 3 to 6.
3. Initialise a queue.
4. Initialise a visited state list.
5. Push S to the queue.
6. While the queue is not empty, perform steps 7 to 9
7. Pop state R from the queue and add R to the visited list.
8. For each epsilon transition t from R to other state A, and A is not in the visited
   list, push A to the queue.
9. Add A to the epsilon closure of S.
10. Exit.

*/

/*
Enter the no: of states: 7
Enter the transitions for:
State 0: - - - - e e -
State 1: - - - - a - -
State 2: - - - a - - -
State 3: - - - - - a -
State 4: - a - - - - -
State 5: - - a - - - e
State 6: - - - - - - -
Epsilon closure of NFA:
State 0: {0, 4, 5, 6}
State 1: {1}
State 2: {2}
State 3: {3}
State 4: {4}
State 5: {5, 6}
State 6: {6 }
*/