#include "MatrixTD.h"

#include <stdio.h>

int main()
{
    printf("%s", "Welcome to MatrixTD\n");

    struct MatrixTD *game = MatrixTD_create();

    while(MatrixTD_isOpen(game))
	;

    return 0;
}
