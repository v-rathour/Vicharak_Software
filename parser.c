#include "lexer.c"  // Include lexer for token handling
#include <stdio.h>

typedef struct ASTNode
{
    Token token;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode *createNode(Token token)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->token = token;
    node->left = node->right = NULL;
    return node;
}

ASTNode *parseExpression(FILE *file)
{
    // Handle a single expression
    Token token;
    getNextToken(file, &token);
    ASTNode *left = createNode(token);

    getNextToken(file, &token);
    if (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS)
    {
        ASTNode *node = createNode(token);
        node->left = left;
        node->right = parseExpression(file);
        return node;
    }

    return left;
}

ASTNode *parseAssignment(FILE *file)
{
    Token token;
    getNextToken(file, &token); // Get the identifier
    ASTNode *node = createNode(token);

    getNextToken(file, &token); // Should be '='
    ASTNode *assignNode = createNode(token);

    assignNode->left = node;
    assignNode->right = parseExpression(file);

    getNextToken(file, &token); // Should be ';'

    return assignNode;
}

ASTNode *parse(FILE *file)
{
    return parseAssignment(file);
}

void printAST(ASTNode *node)
{
    if (node == NULL)
        return;
    printAST(node->left);
    printf("Node: %s\n", node->token.text);
    printAST(node->right);
}


