#include <stdio.h>


int main()
{
    char modified_symbol_table[1000][50];
    strcpy(modified_symbol_table[0], "Hello");
    char modified_symbol_table2[1000][50];
    strcpy(modified_symbol_table2, modified_symbol_table);
    printf("%s", modified_symbol_table2);
    strcpy(modified_symbol_table[0], "Bye");
    printf("%s", modified_symbol_table2[0]);
    printf("%s", modified_symbol_table[0]);
    return 0;
}




