#include "MatrixTD.h"

#include <stdio.h>

int main()
{
    printf("Welcome to MatrixTD\n");
    
    struct MatrixTD *game = MatrixTD_create();
    
    if (game == NULL)
    {
	printf(":(((\n");
	return 1;
    }
		
    while(MatrixTD_isOpen(game)) // This is if I get it to work with threading
    {
	SDL_Delay(200);
	printf(".");
	fflush(stdout);
    }
    
    return 0;
}
