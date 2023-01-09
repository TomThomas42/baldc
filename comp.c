#include <stdio.h>
#include <string.h>

void main()
{
    char icode[10][30], str[20], opr[10];
    int i = 0;

    printf("\nEnter the set of intermediate code (terminated by exit) :\n");

    do
    {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "exit") != 0);

    printf("\nTarget code generation");
    printf("\n*******************");
    i = 0;
    do
    {
        strcpy(str, icode[i]);
        switch (str[3])
        {
        case '+':
            strcpy(opr, "ADD");
            break;
        case '-':
            strcpy(opr, "SUB");
            break;
        case '*':
            strcpy(opr, "MUL");
            break;
        case '/':
            strcpy(opr, "DIV");
            break;
        }
        printf("\nMOV %c,R%d", str[2], i);
        printf("\n\%s %c,R%d", opr, str[4], i);
        printf("\nMOV R%d,%c", i, str[0]);
    } while (strcmp(icode[++i], "exit") != 0);

    printf("\n");
}

/*
1. Start
2. Open the source file and store the contents as quadruples
3. Check for operators in quadruples, if it is an arithmetic operator generator or if the
   assignment operator generates it, else perform unary minus on register C.
4. Write the generated code to output the definition of the file.
5. Print the output
6. Stop
*/

/*
a=a+3
b=a*5
exit
*/