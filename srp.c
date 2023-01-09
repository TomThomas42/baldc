#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char inputString[16], ac[20], stack[15], action[10];
void check();

int main()
{
    printf("\n GRAMMAR is E- >E+E \n E- >E*E \n E - >(E) \n E- >id");
    printf("\n enter input string : ");
    scanf("%s", inputString);
    c = strlen(inputString);
    if (c == 0)
        return (0);
    strcpy(action, "SHIFT -> ");
    puts(" stack \t input \t action ");
    for (k = 0, i = 0; j < c; k++, i++, j++)
    {
        if (inputString[j] == 'i' && inputString[j + 1] == 'd')
        {
            stack[i] = inputString[j];
            stack[i + 1] = inputString[j + 1];
            stack[i + 2] = '\0';
            inputString[j] = ' ';
            inputString[j + 1] = ' ';
            printf("\n $ %-10s |     %-10s $ \t %-10s id ", stack, inputString, action);
            check();
        }
        else
        {
            stack[i] = inputString[j];
            stack[i + 1] = '\0';
            inputString[j] = ' ';
            printf("\n $ %-10s |     %-10s $ \t %-10s symbols", stack, inputString, action);
            check();
        }
    }
    printf("\n");
}
void check()
{
    strcpy(ac, "REDUCE TO E ");
    for (z = 0; z < c; z++)
        // [ + ( i d ]
        if (stack[z] == 'i' && stack[z + 1] == 'd')
        {
            stack[z] = 'E';
            stack[z + 1] = '\0';
            printf("\n $ %-10s |     %-10s $ \t %-10s ", stack, inputString, ac);
            j++;
        }
    for (z = 0; z < c; z++)
        if (stack[z] == 'E' && stack[z + 1] == '+' && stack[z + 2] == 'E')
        {
            stack[z] = 'E';
            stack[z + 1] = '\0';
            stack[z + 2] = '\0';
            printf("\n $ %-10s |     %-10s $ \t %-10s ", stack, inputString, ac);
            i = i - 2;
        }
    for (z = 0; z < c; z++)
        if (stack[z] == 'E' && stack[z + 1] == '*' && stack[z + 2] == 'E')
        {
            stack[z] = 'E';
            stack[z + 1] = '\0';
            stack[z + 1] = '\0';
            printf("\n $ %-10s |     %-10s $ \t %-10s ", stack, inputString, ac);
            i = i - 2;
        }
    for (z = 0; z < c; z++)
        if (stack[z] == '(' && stack[z + 1] == 'E' && stack[z + 2] == ')')
        {
            stack[z] = 'E';
            stack[z + 1] = '\0';
            stack[z + 1] = '\0';
            printf("\n $ %-10s |     %-10s $ \t %-10s ", stack, inputString, ac);
            i = i - 2;
        }
}

/*
1. Start
2. Get the input expression and store it in the input buffer.
3. Read the data from the input buffer one at the time
4. Using stack and push & pop operation shift and reduce symbols with respect
   to production rules available.
5. Continue the process till the symbol shift and production rule reduction reach
   the start symbol.
6. Display the Stack Implementation table with corresponding Stack actions
   with input symbols.
7. Stop
*/

/*
id+id*id+id
*/