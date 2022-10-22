#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char intermediate_symbol_table[1000][50];
int intermediate_symbol_table_counter=0;

void print_file(FILE *p2);
void process_token(char *token);
void _read_each_tokens_from_file(FILE *p2);
void tokenizeSeparator();
int detect_variable_declaration(int i);
void process_intermediate_symbol_table();
void detect_function_declaration();

/* TODO */
/*
fix closing condition of scope
*/


/* SYMBOL TABLE */

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
    int id_type;
    int data_type;
    char scope[50];
    int int_value;
    double double_value;
    int status;
} _table[50];

int table_serial_counter = 1;
int scope_tracker;
/*   SCOPE   */

char current_scope[50];

int getSerialCounter()
{
    table_serial_counter++;
    return table_serial_counter;
}

void update_scope(char *sc)
{
    //update_scope("Hello");
    strcpy(current_scope, sc);
}

void reset_scope()
{
    strcpy(current_scope, "global");
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

const char* get_type(int typ)
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
        if(_table[i].status != _deleted)
        {
            if(_table[i].data_type == _int_data)
            {
                if(_table[i].int_value != 32765)
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

void delete_item_from_table(char *name, char *scope)
{
    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, scope) )
        {
            _table[i].status = _deleted;
            return;
        }
    }

}

void search_insert_item_to_table(int _data_type, char *name, char *scope, double value, int is_var)
{
    printf("\n\nSearching Item - Name : %s  |  Scope : %s\n", name, scope);

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, scope))
        {
            //same name found
            printf("Error in inserting\n");
            return;
        }
    }

    //not found, so safe to insert
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

void search_declare_item_from_table(int _data_type, char *name, char *scope, double value, int is_var)
{
    printf("\n\nSearching Item - Name : %s  |  Scope : %s\n", name, scope);

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, scope))
        {
            //same name found
            printf("Couldn't Insert\n");
            return;
        }
    }
    //not found, so safe to insert
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
    else if(_data_type == _double_data)
    {
        tab.double_value = value;
        tab.data_type = _double_data;
    }
    else
    {
        tab.double_value = value;
        tab.data_type = _double_data;
    }
    insert_table_item(tab);
}



void update_var_item_in_table(char *name, char *scope, double value)
{
    //checking in the current scope
    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, scope))
        {
            if(_table[i].data_type == _int_data){
                _table[i].int_value = (int)value;
            }else{
                _table[i].double_value = value;
            }
            return;
        }

    }

    //if not available in the current scope, search in the global scope

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, "global"))
        {
            if(_table[i].data_type == _int_data){
                _table[i].int_value = (int)value;
            }else{
                _table[i].double_value = value;
            }
            return;
        }

    }


}

int main()
{
    tokenizeSeparator();
    process_intermediate_symbol_table();
    display_table();
    return 0;
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

int detect_variable_declaration(int i)
{
    if(scope_tracker!=-1){
        if(i>scope_tracker){
            reset_scope();
            scope_tracker = -1;
        }
    }

    if(!strcmp(intermediate_symbol_table[i],"float")
            || !strcmp(intermediate_symbol_table[i],"double")
            || !strcmp(intermediate_symbol_table[i],"int") )
    {
        if(!strcmp(intermediate_symbol_table[i+2],"="))
        {
            //var assignment and declaration
            if(!strcmp(intermediate_symbol_table[i],"int"))
            {
                search_insert_item_to_table(get_corresponding_enum(intermediate_symbol_table[i]), intermediate_symbol_table[i+1],
                                            current_scope, atoi(intermediate_symbol_table[i+3]), _var );
            }
            else if(!strcmp(intermediate_symbol_table[i],"double") || !strcmp(intermediate_symbol_table[i],"float") )
            {
                char *ptr;
                double ret;
                ret = strtod(intermediate_symbol_table[i+3], &ptr);
                search_insert_item_to_table(get_corresponding_enum(intermediate_symbol_table[i]), intermediate_symbol_table[i+1],
                                            current_scope, ret, _var );
            }
            i = i+4;
        }
        else if(!strcmp(intermediate_symbol_table[i+2],";"))
        {
            //var declaration only
            search_declare_item_from_table(get_corresponding_enum(intermediate_symbol_table[i]), intermediate_symbol_table[i+1],
                                           current_scope, 32765, _var );
            i = i+2;
        }
        else if(!strcmp(intermediate_symbol_table[i+2],"("))
        {
            update_scope(intermediate_symbol_table[i+1]);
            search_declare_item_from_table(get_corresponding_enum(intermediate_symbol_table[i]),
                                           intermediate_symbol_table[i+1],current_scope, 32765, _func);
            i = i + 3;
            if(!strcmp(intermediate_symbol_table[i],")"))
            {

            }
            else
            {
                int j = i;
                for( ; ;j=j+3)
                {
                    search_declare_item_from_table(get_corresponding_enum(intermediate_symbol_table[j]),
                                                   intermediate_symbol_table[j+1],current_scope, 32765, _var);
                    if(!strcmp(intermediate_symbol_table[j+2],")"))
                    {
                        i = j+2;
                        break;
                    }
                }
                for(scope_tracker=i;scope_tracker < intermediate_symbol_table_counter; scope_tracker++){
                    if(!strcmp(intermediate_symbol_table[scope_tracker],"}"))
                    {
                        break;
                    }
                }
            }
        }
    }
    else if(!strcmp(intermediate_symbol_table[i+1],"="))
    {
        //var assignment OR Function call which returns a value

        //var assignment
        char *ptr;
        double ret;
        ret = strtod(intermediate_symbol_table[i+2], &ptr);
        update_var_item_in_table(intermediate_symbol_table[i],current_scope, ret);
        i = i+3;
    }
    else
    {
        //nothing to do with symbol table
    }

    return i;
}


void print_file(FILE *p2)
{
    char c;
    while((c=fgetc(p2)) != EOF)printf("%c",  c);
}

void process_token(char *token)
{
    FILE *p1;
    p1 = fopen("identified_tokens.txt", "a");
    char first[20],second[30];
    char c;
    int i;
    for(i = 0; i < strlen(token); i++)
    {
        if(token[i]==' ')
            break;
        first[i] = token[i];
    }
    first[++i] = '\0';
    int j;
    for(j = 0; j < strlen(token); j++, i++)
    {
        second[j] = token[i];
    }
    second[++j] = '\0';
    if(!strcmp(first,"id"))
    {
        printf("[id %s] ", second);
        fputs("[id ",p1);
        fputs(second,p1);
        fputs("] ",p1);
        char str[50] = "id ";
        strcat(str, second);
        strcpy(intermediate_symbol_table[intermediate_symbol_table_counter++],str);
    }
    else
    {
        printf("[%s] ", second);
        fputs("[", p1);
        fputs(second, p1);
        fputs("] ", p1);
        strcpy(intermediate_symbol_table[intermediate_symbol_table_counter++],second);
    }

    fclose(p1);
}

void _read_each_tokens_from_file(FILE *p2)
{

    char c;
    char token[100];
    token[0] = '\0';
    char cToStr[2];
    cToStr[1] = '\0';
    while(c=fgetc(p2))
    {
        if(c=='[')
            continue;
        if(c==']')
            break;
        cToStr[0] = c;
        strcat(token,cToStr);
    }
    fgetc(p2);
    process_token(token);
}

void tokenizeSeparator()
{
    FILE *p1;

    char c;
    p1 = fopen("tokenized_file.txt", "r");

    if(!p1)printf("\nTokenized File can't be opened!");
    else
    {
        while((c=fgetc(p1)) != EOF)
        {
            _read_each_tokens_from_file(p1);
        }
    }

    fclose(p1);
}

void detect_function_declaration()
{

}



void process_intermediate_symbol_table()
{
//    for(int i = 0 ; i < intermediate_symbol_table_counter ; i++){
//        puts(intermediate_symbol_table[i]);
//    }
    reset_scope();
    scope_tracker = -1;
    for(int i = 0 ; i < intermediate_symbol_table_counter ; i++)
    {
        i = detect_variable_declaration(i);
    }
}

