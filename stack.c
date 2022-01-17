//YASH JAYBHAYE
// SYITA146

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_error
{
    char data;
    struct node *next;
} STACK;

STACK *Push(STACK *top, char c);
STACK *Pop(STACK *top);
int isEmpty(STACK *top);
char readTop(STACK *top);
int Precedence(char token);
char *string_rev(char a[20], char rev[]);
int isDigit(char token);
char *infix_to_postfix(char a[], char n[]);
void infix_to_prefix(char a[], char n[]);
int eval_postfix(char postfix[20]);
int eval_prefix(char prefix[20]);

int main(int argc, char const *argv[])
{
    char postfix[20];
    char infix[20];
    char prefix[20];
    int choice;
    do
    {
        printf("\n\n!.infix_to_postfix\n2.infix_to_prefix\n3.postfix evaluation\n4.prefix evaluation\n0.Exit\nEnter your choice");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter infix expression: ");
            scanf("%s", infix);
            printf("%s", infix_to_postfix(infix, postfix));
            break;
        case 2:
            printf("\nEnter infix expression: ");
            scanf("%s", infix);
            infix_to_prefix(infix, prefix);
            break;
        case 3:
            printf("\nEnter postfix expression: ");
            scanf("%s", postfix);
            printf("\nans= %d ", eval_postfix(postfix));
            break;
        case 4:
            printf("\nEnter postfix expression: ");
            scanf("%s", prefix);
            printf("ans= %d ", eval_prefix(prefix));
            break;

        case 0:
            printf("Thankyou!");
            break;

        default:
            break;
        }
    } while (choice != 0);

    return 0;
}

int eval_prefix(char prefix[20])
{
    char prefix_rev[20];
    strcpy(prefix_rev, string_rev(prefix, prefix_rev));
    STACK *top = NULL;
    int i = 0;
    char token, x;
    for (i = 0; prefix_rev[i] != '\0'; i++)
    {
        token = prefix_rev[i];
        if (isDigit(token))
        {
            top = Push(top, token - 48);
        }
        else
        {
            int op1, op2;
            op1 = readTop(top);
            top = Pop(top);
            op2 = readTop(top);
            top = Pop(top);
            switch (token)
            {
            case '+':
                x = op1 + op2;
                break;
            case '-':
                x = op1 - op2;
                break;
            case '*':
                x = op1 * op2;
                break;
            case '/':
                x = op1 / op2;
                break;
            }
            top = Push(top, x);
        }
    }
    x = readTop(top);
    top = Pop(top);
    return x;
}
int eval_postfix(char postfix[20])
{
    STACK *top = NULL;
    int i = 0;
    char token, x;
    for (i = 0; postfix[i] != '\0'; i++)
    {
        token = postfix[i];
        if (isDigit(token))
        {
            top = Push(top, token - 48);
        }
        else
        {
            int op1, op2;
            
            op2 = readTop(top);
            top = Pop(top);
            op1 = readTop(top);
            top = Pop(top);
            switch (token)
            {
            case '+':
                x = op1 + op2;
                break;
            case '-':
                x = op1 - op2;
                break;
            case '*':
                x = op1 * op2;
                break;
            case '/':
                x = op1 / op2;
                break;
            }
            top = Push(top, x);
        }
    }
    x = readTop(top);
    top = Pop(top);
    return x;
}
char *string_rev(char a[20], char rev[])
{
    int l = strlen(a);
    int j = 0;
    for (int i = l - 1; i >= 0; i--)
    {
        rev[j] = a[i];
        j++;
    }
    rev[j] = '\0';
    return rev;
}

void infix_to_prefix(char infix[], char prefix[])
{
    char rev_infix[20];
    int l = strlen(infix);
    int j = 0;
    char rev[20];
    for (int i = l - 1; i >= 0; i--)
    {
        if (infix[i] == '(')
            rev_infix[j] = ')';
        else if (infix[i] == ')')
            rev_infix[j] = '(';
        else
            rev_infix[j] = infix[i];
        j++;
    }
    rev_infix[j] = '\0';
    printf("%s  ", string_rev(prefix, rev));
}
int presedence(char token)
{
    switch (token)
    {
    case '(':
        return 0;
    case ')':
        return 0;
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    }
    return -1;
}

int isDigit(char token)
{
    if (token >= '0' && token <= '9')
        return 1;
    else
        return 0;
}
char *infix_to_postfix(char infix[20], char postfix[20])
{
    int i, j = 0;
    char token;
    STACK *top = NULL;
    for (i = 0; infix[i] != '\0'; i++)
    {
        token = infix[i];
        if (token == '(')
        {
            top = Push(top, token);
        }
        else if (isDigit(token))
        {
            postfix[j] = token;
            j++;
        }
        else if (token == ')')
        {
            while (readTop(top) != '(')
            {
                char x = readTop(top);
                postfix[j] = x;
                j++;
                top = Pop(top);
            }
            top = Pop(top);
        }
        else
        {
            while (!isEmpty(top) && presedence(token) <= presedence(readTop(top)))
            {
                postfix[j] = readTop(top);
                j++;
                top = Pop(top);
            }
            top = Push(top, token);
        }
    }
    while (!isEmpty(top))
    {
        postfix[j] = readTop(top);
        j++;
        top = Pop(top);
    }
    postfix[j] = '\0';
    return postfix;
}
STACK *Push(STACK *top, char c)
{
    STACK *new_node = (STACK *)malloc(sizeof(STACK));
    new_node->data = c;
    new_node->next = NULL;
    if (top == NULL)
        top = new_node;
    else
    {
        new_node->next = top;
        top = new_node;
    }
    return top;
}
void display(STACK *top)
{
    STACK *temp =top;
    while (temp)
    {
        printf("|  %c  |\n", temp->data);
        temp = temp->next;
    }
}
STACK *Pop(STACK *top)
{
    STACK *temp = top;
    top = top->next;
    free(temp);
    return top;
}
int isEmpty(STACK *top)
{
    if (top == NULL)
        return 1;
    else
    {
        return 0;
    }
}
char readTop(STACK *top)
{
    return top->data;
}
