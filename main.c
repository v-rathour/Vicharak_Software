#include "codegen.c"
#include<stdio.h>

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        perror("Failed to open file");
        return 1;
    }

    ASTNode *root = parse(file);
    generateAssembly(root);

    fclose(file);
    return 0;
}
