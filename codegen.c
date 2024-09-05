#include "parser.c"

void generateAssembly(ASTNode *node)
{
    if (!node)
        return;

    generateAssembly(node->left);

    if (node->token.type == TOKEN_ASSIGN)
    {
        printf("LOAD %s\n", node->right->token.text);
        printf("STORE %s\n", node->left->token.text);
    }
    else if (node->token.type == TOKEN_PLUS)
    {
        printf("ADD %s\n", node->right->token.text);
    }
    else if (node->token.type == TOKEN_MINUS)
    {
        printf("SUB %s\n", node->right->token.text);
    }
    else
    {
        printf("MOV %s\n", node->token.text);
    }

    generateAssembly(node->right);
}


