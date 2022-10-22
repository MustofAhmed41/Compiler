#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


enum id
{
    _var = 0,
    _func = 1
};

enum data
{
    _int_data = 10,
    _float_data = 11,
    _double_data = 12
};

enum status
{
    _created = 20,
    _deleted = 21,
};

/*   SYMBOL TABLE   */

struct table
{
    int serial_number;
    char name[50];
    int id_type; //var or func
    int data_type; //int/float/double
    char scope[50];
    int int_value;
    double double_value;
    int status; //if item is deleted
} _table[50];


char intermediate_symbol_table[1000][50];
int intermediate_symbol_table_counter=0;

int table_serial_counter = 1;
int scope_tracker;
char current_scope[50];

const char* get_type(int typ) //gets corresponding enum in string format
{
    if(typ==_var)
    {
        char *name = "var";
        return name;
    }
    else if(typ==_func)
    {
        char *name = "func";
        return name;
    }
    else if(typ==_int_data)
    {
        char *name = "int";
        return name;
    }
    else if(typ==_double_data)
    {
        char *name = "double";
        return name;
    }
    else if(typ==_float_data)
    {
        char *name = "float";
        return name;
    }
}



void display_table()
{
    printf("Serial Number \tName \t Id Type \t Data Type \t  Scope \t Value");
    printf("\n\n");

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted) //only display item if they are not deleted
        {
            if(_table[i].data_type == _int_data)
            {
                if(_table[i].int_value != 32765) //32765 implies null value
                {
                    printf("%13d \t%4s \t%8s \t%10s\t %s \t%6d\n", _table[i].serial_number, _table[i].name,
                           get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope, _table[i].int_value);
                }
                else
                {
                    printf("%13d \t%4s \t%8s \t%10s\t %s \t     \n", _table[i].serial_number, _table[i].name,
                           get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope );
                }

            }
            else
            {
                if(_table[i].double_value != 32765)
                {
                    printf("%13d \t%4s \t%8s \t%10s\t %s \t %.3lf\n", _table[i].serial_number, _table[i].name,
                           get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope,_table[i].double_value);
                }
                else
                {
                    printf("%13d \t%4s \t%8s \t%10s\t %s \t     \n", _table[i].serial_number, _table[i].name,
                           get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope);
                }
            }
        }
    }
}





int get_corresponding_enum(char *data_type)
{
    if(!strcmp("float", data_type))
    {
        return _float_data;
    }
    else if(!strcmp("double", data_type))
    {
        return _double_data;
    }
    else if(!strcmp("int", data_type))
    {
        return _int_data;
    }
}

void insert_table_item(struct table item)
{
    _table[table_serial_counter].serial_number = table_serial_counter;
    strcpy(_table[table_serial_counter].name, item.name);
    _table[table_serial_counter].id_type = item.id_type;
    _table[table_serial_counter].data_type = item.data_type;
    strcpy(_table[table_serial_counter].scope, item.scope);
    _table[table_serial_counter].status = _created;

    if(item.data_type == _int_data)
    {
        _table[table_serial_counter].int_value = item.int_value;
    }
    else
    {
        _table[table_serial_counter].double_value = item.double_value;
    }
    table_serial_counter++;
}



void search_insert_item_to_table(int _data_type, char *name, char *scope, double value, int is_var)
{
    printf("\n\nSearching Item - Name : %s  |  Scope : %s\n", name, scope);

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, scope))
        {
            printf("\nERROR : Insertion Failed as variable with same name found\n");
            return;
        }
    }

    struct table tab;
    strcpy(tab.name, name);
    strcpy(tab.scope, scope);
    if(is_var==_var)
    {
        tab.id_type = _var;
    }
    else
    {
        tab.id_type = _func;
    }
    if(_data_type == _int_data)
    {
        tab.int_value = (int)value;
        tab.data_type = _int_data;
    }
    else if(_data_type == _float_data)
    {
        tab.double_value = value;
        tab.data_type = _float_data;
    }
    else
    {
        tab.double_value = value;
        tab.data_type = _double_data;
    }
    insert_table_item(tab);

}




void read_file()
{
    FILE *p1, *p2;

    char c,prev='z';
    p1 = fopen("abc.txt", "r");
    char str[100];
    char store[5][100];
    int strCounter = 0;
    int rowCounter = 0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {

        while((c=fgetc(p1))!=EOF)
        {
            if(c!=' ' && c!='\n')
            {
                str[strCounter] = c;
                strCounter++;
            }
            else if(c==' ' || c=='\n')
            {
                str[strCounter] = '\0';
                strCounter = 0;
                if(c==' ')
                {
                    while((c=fgetc(p1))==' ') {}
                    ungetc(c,p1);
                }
                strcpy(store[rowCounter++], str);

                if(c=='\n')
                {
                    printf("%s %s %s %s %s\n", store[0], store[1], store[2], store[3], store[4]);
                    //search_insert_item_to_table();
                    rowCounter = 0;
                    if(!strcmp(store[2],"var"))
                    {

                        search_insert_item_to_table(get_corresponding_enum("int"),
                                                    store[1], store[3],
                                                    atoi(store[4]), _var );
                    }
                    else if(!strcmp(store[2],"func"))
                    {
                        search_insert_item_to_table(get_corresponding_enum("int"),
                                                    store[1], store[3],
                                                    32765, _func );
                    }
                    store[0][0] = '\0';
                    store[1][0] = '\0';
                    store[2][0] = '\0';
                    store[3][0] = '\0';
                    store[4][0] = '\0';

                }
            }



        }
    }

    fclose(p1);
}



void update_var_item_in_table(char *name, char *scope, double value)
{

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, scope))
        {
            if(_table[i].data_type == _int_data)
            {
                _table[i].int_value = (int)value;
            }
            else
            {
                _table[i].double_value = value;
            }
            return;
        }

    }

}

void write_file()
{
    FILE *p1;
    p1 = fopen("abcd.txt", "w");

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted) //only display item if they are not deleted
        {
            if(_table[i].data_type == _int_data)
            {
                if(_table[i].int_value != 32765) //32765 implies null value
                {
                    printf("%13d \t%4s \t%8s \t%10s\t %s \t%6d\n", _table[i].serial_number, _table[i].name,
                           get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope, _table[i].int_value);

                    char snum[10];
                    itoa(_table[i].serial_number, snum, 10);
                    fputs(snum, p1);
                    fputs(" ", p1);
                    fputs(_table[i].name, p1);
                    fputs(" ", p1);
                    fputs(get_type(_table[i].id_type), p1);
                    fputs(" ", p1);
                    fputs(_table[i].scope, p1);
                    fputs(" ", p1);
                    itoa(_table[i].int_value, snum, 10);
                    fputs(snum, p1);
                    fputs(" \n", p1);


                }
                else
                {
                    printf("%13d \t%4s \t%8s \t%10s\t %s \t     \n", _table[i].serial_number, _table[i].name,
                           get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope );
                    char snum[10];
                    itoa(_table[i].serial_number, snum, 10);
                    fputs(snum, p1);
                    fputs(" ", p1);
                    fputs(_table[i].name, p1);
                    fputs(" ", p1);
                    fputs(get_type(_table[i].id_type), p1);
                    fputs(" ", p1);
                    fputs(_table[i].scope, p1);
                    fputs(" \n", p1);
                }

            }
            else
            {
                if(_table[i].double_value != 32765)
                {
                    printf("%13d \t%4s \t%8s \t%10s\t %s \t %.3lf\n", _table[i].serial_number, _table[i].name,
                           get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope,_table[i].double_value);
                }
                else
                {
                    printf("%13d \t%4s \t%8s \t%10s\t %s \t     \n", _table[i].serial_number, _table[i].name,
                           get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope);
                }
            }
        }
    }


    fclose(p1);
}



/*
search_insert_item_to_table(get_corresponding_enum(intermediate_symbol_table[i]),
                                            intermediate_symbol_table[i+1], current_scope,
                                            atoi(intermediate_symbol_table[i+3]), _var);


                    char snum[10];
                    itoa(_table[i].serial_number, snum, 10);
                    fputs(snum, p1);
                    fputs(" ", p1);
                    fputs(_table[i].name, p1);
                    fputs(" ", p1);
                    fputs(_table[i].id_type, p1);
                    fputs(" ", p1);
                    fputs(_table[i].scope, p1);
                    fputs(" ", p1);
                    char snum1[10];
                    itoa(_table[i].int_value, snum1, 10);
                    fputs(snum1, p1);
*/

//set 1

int main()
{

    read_file();
    display_table();
    char inp[100];
    char inp2[100];
    gets(inp);
    gets(inp2);
    search_insert_item_to_table(get_corresponding_enum("int"),
                                inp, inp2,
                                32765, _var);
    display_table();
    write_file();

    return 0;
}

/*

//set 2

int main(){
    read_file();
    display_table();
    char inp[100];
    char inp2[100];
    gets(inp);
    gets(inp2);
    double a;
    scanf("%lf",&a);
    update_var_item_in_table(inp, inp2, a);

    display_table();

    return 0;
}

*/
