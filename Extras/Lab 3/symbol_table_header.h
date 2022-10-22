#include <stdio.h>
#include <string.h>

/*   ENUM   */

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

void create_table_item(struct table item)
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
                printf("%13d \t%4s \t%8s \t%10s\t %s \t%6d\n", _table[i].serial_number, _table[i].name,
                       get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope, _table[i].int_value);
            }
            else
            {
                printf("%13d \t%4s \t%8s \t%10s\t %s \t%.3lf\n", _table[i].serial_number, _table[i].name,
                       get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope,_table[i].double_value);
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

void search_item_from_table(char *name, char *scope)
{
    printf("\n\nSearching Item - Name : %s  |  Scope : %s\n", name, scope);

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, scope))
        {
            if(_table[i].data_type == _int_data)
            {
                printf("Serial Number : %d |  Name : %s | Id Type : %s  | Data Type : %s | Scope : %s | Value : %d\n", _table[i].serial_number, _table[i].name,
                       get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope, _table[i].int_value);
            }
            else
            {
                printf("Serial Number : %d |  Name : %s | Id Type : %s  | Data Type : %s | Scope : %s | Value : %.3lf\n", _table[i].serial_number, _table[i].name,
                       get_type(_table[i].id_type), get_type(_table[i].data_type), _table[i].scope,_table[i].double_value);
            }
            return;
        }
    }

}

void update_item_from_table(struct table item)
{
    for(int i = 1 ; i < table_serial_counter; i++)
    {

        if(_table[i].status != _deleted && !strcmp(_table[i].name, item.name) && !strcmp(_table[i].scope, item.scope))
        {
            _table[i] = item;
            _table[i].serial_number = i;
        }
        return;
    }
}



/*


value=strcmp(str1,str2);
   if(value==0)
   printf("strings are same");


// assign value to name of person1
  strcpy(person1[0].name, "George Orwell");

  // assign values to other person1 variables
  person1[0].citNo = 1984;
  person1[0]. salary = 2500;

  // print struct variables
  printf("Name: %s\n", person1[0].name);
  printf("Citizenship No.: %d\n", person1[0].citNo);
  printf("Salary: %.2f", person1[0].salary);

*/

