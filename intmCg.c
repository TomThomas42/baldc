#include <stdio.h>
#include <string.h>

void gen_code_for_operator(char *inp, char operator, char * reg)
{
    int i = 0, j = 0;
    char temp[100];
    while (inp[i] != '\0')
    {
        if (inp[i] == operator)
        {
            printf("%c\t%c\t%c\t%c\n", operator, * reg, inp[i - 1], inp[i + 1]);
            temp[j - 1] = *reg;
            i += 2;
            (*reg)--;
            continue;
        }
        temp[j] = inp[i];
        i++;
        j++;
    }
    temp[++j] = '\0';
    strcpy(inp, temp);
}

void gen_code(char *inp)
{
    char reg = 'Z';
    gen_code_for_operator(inp, '/', &reg);
    gen_code_for_operator(inp, '*', &reg);
    gen_code_for_operator(inp, '+', &reg);
    gen_code_for_operator(inp, '-', &reg);
    gen_code_for_operator(inp, '=', &reg);
}

void main()
{
    char inp[100];
    printf("Enter expression: ");
    scanf("%s", inp);
    printf("Oprtr\tDestn\tOp1\tOp2\n");
    gen_code(inp);
}

/*
1. Start
2. Open the input file in read mode.
3. Open the output file in write mode.
4. In input file scan for operator, argument1,    argument2 and result.
5. If the operator is ‘+’
   Move arg1 to R0
   Add arg2 and R0
   Move R0 to result
6. If the operator is ‘-’
   Move arg1 to R0
   Subtract arg2 and R0
   Move R0 to result
7. If the operator is ‘*’
   Move arg1 to R0
   Multiply arg2 and R0
   Move R0 to result
8. If the operator is ‘/’
   Move arg1 to R0
   Divide arg2 and R0
   Move R0 to result
9. If the operator is ‘=’
   Move arg1 to R0
   Move R0 to result
10.Close both the files.
11.Stop
*/

/*
a+b-c/d*6
 */