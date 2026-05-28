

#include "saass.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

int id_exists(char *filename, char *searchid)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }

    char id[20], name[50], extra[50];
    int age;

    while (fscanf(file, "%19s %49s %d %49s ", id, name, &age, extra) == 4)
    {
        if (strcmp(id, searchid) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

