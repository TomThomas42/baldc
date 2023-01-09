#include <stdio.h>
#include <string.h>
#include <ctype.h>

int productionCount, firstIndex = 0;
char productions[10][10], first[10];

void findFirst(char c);
void findFollow(char c);

void findFirst(char c)
{
    if (!isupper(c))
        first[firstIndex++] = c;

    for (int k = 0; k < productionCount; k++)
    {
        if (productions[k][0] == c)
        {
            if (productions[k][2] == '$')
                findFollow(productions[k][0]);
            else if (islower(productions[k][2]))
                first[firstIndex++] = productions[k][2];
            else
                findFirst(productions[k][2]);
        }
    }
}

void findFollow(char c)
{
    if (productions[0][0] == c)
        first[firstIndex++] = '$';
    for (int i = 0; i < productionCount; i++)
    {
        for (int j = 2; j < strlen(productions[i]); j++)
        {
            if (productions[i][j] == c)
            {
                if (productions[i][j + 1] != '\0')
                    findFirst(productions[i][j + 1]);
                if (productions[i][j + 1] == '\0' && c != productions[i][0])
                    findFollow(productions[i][0]);
            }
        }
    }
}

void main()
{
    printf("Enter the no of productions: ");
    scanf("%d", &productionCount);

    printf("Enter the productions :\n");
    for (int i = 0; i < productionCount; i++)
        scanf("%s", productions[i]);

    char ch;
    scanf("%c", &ch);

    firstIndex = 0;
    printf("\nEnter the elemets whose first & follow is to be found: ");
    char c;
    scanf("%c", &c);
    findFirst(c);

    printf("\n First (%c)={", c);
    for (int i = 0; i < firstIndex; i++)
        printf("%c", first[i]);
    printf("}\n");

    strcpy(first, " ");
    firstIndex = 0;

    findFollow(c);
    printf(" Follow (%c)={", c);
    for (int i = 0; i < firstIndex; i++)
        printf("%c", first[i]);
    printf("}\n");
}

/*
1. Start
2. Calculating first, α → t β
3.if α is a terminal, then FIRST(α) = α .
4. if α is a non-terminal and α → ε is a production, then FIRST(α) = ε .
5. if α is a non-terminal and α → γ1 γ2 γ3 . . . γn and any FIRST(γ) contains t then t is in FIRST(α).
6. Calculating follow,
7. if α is a start symbol, then FOLLOW() = $
8. if α is a non-terminal and has a production α → AB, then FIRST(B) is in FOLLOW(A) except ε.
40
9. if α is a non-terminal and has a production α → AB, where B ε, then FOLLOW(A) is in FOLLOW(α).
10. Stop
*/

/*
S=AbCd
A=Cf
A=a
C=gE
E=h
*/