#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define OPERAND_SIZE 10

typedef struct Expression
{
    char res[OPERAND_SIZE], op1[OPERAND_SIZE], op2[OPERAND_SIZE], operator;
    int is_const;
} Expression;

void printExpressions(int n, Expression *exprs, int debug)
{
    printf(" Expressions : \n");
    for (int i = 0; i < n; i++)
    {
        printf(" > |%s| = |%s| ", exprs[i].res, exprs[i].op1);
        if (!exprs[i].is_const)
            printf("|%c| |%s|", exprs[i].operator, exprs[i].op2);
        if (debug)
            printf("| %d |", exprs[i].is_const);
        printf("\n");
    }
}

Expression *copyExpression(Expression *expr1, Expression *expr2)
{
    strcpy(expr1->res, expr2->res);
    strcpy(expr1->op1, expr2->op1);
    strcpy(expr1->op2, expr2->op2);
    expr1->operator= expr2->operator;
    expr1->is_const = expr2->is_const;
    return (expr1);
}

int searchExprRes(int n, Expression *exprs, char *s)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!strcmp(exprs[i].res, s))
            return (i);
    }
    return (-1);
}

int searchExprOp1(int n, Expression *exprs, char *s)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!strcmp(exprs[i].op1, s))
            return (i);
    }
    return (-1);
}

int searchExprOp2(int n, Expression *exprs, char *s)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!strcmp(exprs[i].op2, s))
            return (i);
    }
    return (-1);
}

long int getNumber(char *str)
{
    int e;
    long int a;
    a = strtol(str, NULL, 10);
    e = errno;
    // printf(" e = %d", e);
    // check invalid value
    if (errno == 121 || a == 0)
        return (-1);
    return (a);
}

Expression *evaluateExpression(Expression *exprs)
{
    int e;
    long int a, b, res;
    a = getNumber(exprs->op1);
    b = getNumber(exprs->op2);
    // printExpressions(1, exprs, 1);
    if (a != -1 && b != -1)
    {
        int flag = 0;
        switch (exprs->operator)
        {
        case '+':
            res = a + b;
            // printExpressions(1, exprs, 1);
            // printf("%ld + %ld = %ld\n", a, b, res);
            break;

        case '-':
            res = a - b;
            break;

        case '*':
            res = a * b;
            break;

        case '/':
            res = a / b;
            break;

        case '%':
            res = a % b;
            break;
        default:
            printf(" !> Invalid operator in : ");
            printExpressions(1, exprs, 1);
            flag = 1;
            break;
        }
        if (flag != 1)
        {
            sprintf(exprs->op1, "%ld", res);
            strcpy(exprs->op2, "_");
            exprs->operator= 0;
            exprs->is_const = 1;
        }
    }
    return (exprs);
}

Expression *constantPropagate(int n, Expression *exprs, Expression *reduced_expr, int *n2)
{
    reduced_expr = (Expression *)calloc(n, sizeof(Expression));
    int i, j, m = 0, changes;
    for (i = 0; i < n; i++)
        reduced_expr[m++] = *copyExpression(&reduced_expr[m], &exprs[i]);
    do
    {
        changes = 0;
        for (i = 0; i < n; i++)
        {
            // printExpressions(n, reduced_expr, 1);
            if (!reduced_expr[i].is_const)
            {
                int r = searchExprRes(n, reduced_expr, reduced_expr[i].op1);
                if (r != -1)
                {
                    if (reduced_expr[r].is_const)
                    {
                        changes++;
                        strcpy(reduced_expr[i].op1, reduced_expr[r].op1);
                    }
                }
                r = searchExprRes(n, reduced_expr, reduced_expr[i].op2);
                if (r != -1)
                {
                    if (reduced_expr[r].is_const)
                    {
                        changes++;
                        strcpy(reduced_expr[i].op2, reduced_expr[r].op1);
                    }
                }
                reduced_expr[i] = *copyExpression(&reduced_expr[i], evaluateExpression(&reduced_expr[i]));
            }
        }
    } while (changes != 0);
    *n2 = m;
    return (reduced_expr);
}

int main()
{
    int i, n, m;
    printf(" > Enter the number of Expressions: ");
    scanf("%d", &n);
    if (n < 1)
        return (0);
    Expression exprs[n], *r_exprs;
    printf(" > Enter Expressions (res[%d] = op1[%d] operator[1] op2[%d]): \n", OPERAND_SIZE, OPERAND_SIZE, OPERAND_SIZE);
    for (i = 0; i < n; i++)
    {
        printf(" >>> ");
        exprs[i].is_const = 0;
        scanf("%s = %s %c %s", exprs[i].res, exprs[i].op1, &exprs[i].operator, exprs[i].op2);
        if (exprs[i].operator== '_')
            exprs[i].is_const = 1;
    }
    printExpressions(n, exprs, 0);
    r_exprs = constantPropagate(n, exprs, r_exprs, &m);
    printf(" > Expressions after constant propagation: ");
    printExpressions(m, r_exprs, 0);
    if (r_exprs != NULL)
        free(r_exprs);
    return (0);
}

/*
Start
2. Construct a control flow graph (CFG).
3. Associate transfer functions with the edges of the CFG.
4. At every node (program point) we maintain the values of the program’s
variables at that point. We initialize those to L.
5. Iterate until the values of the variables stabilize.
6. Stop
*/

/*
 > Enter the number of Expressions: 3
 > Enter Expressions (res[10] = op1[10] operator[1] op2[10]):
 >>> a = 3 _ _
 >>> b = 10 + a
 >>> c = a + b
 */