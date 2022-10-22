#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "myheader.h"

char intermediate_symbol_table[1000][50];
int intermediate_symbol_table_counter=0;


void take_input_from_console(); // unchanged
void error_remove_comment_and_generate_stream(); //cannot merge
int error_get_number_for_file(int num, FILE *p); //new added
void error_add_number_in_the_file(); //new added
void error_perform_separate(); //can try to merge
int error_detect_identifier(char *word);//changed a bit
int error_detect_keyword(char *word);//changed a bit
int error_detect_separator(char *word);//changed a bit
void error_detect_word(char *word, int length);//changed a bit
void error_tokenizer();//changed
void findError();//new added
void error__read_each_tokens_from_file(FILE *p2); //changed
void error_process_token(char *token); // changed
void find_error(); //new added
void check_if_same(); //new added
void check_if_balanced();//new added
void check_if_else();//new addedz


/* ASSIGNMENT 3 */


void print_file(FILE *p2);
void process_token(char *token);
void _read_each_tokens_from_file(FILE *p2);
void tokenizeSeparator();
int detect_variable_declaration(int i);
void process_intermediate_symbol_table();
void update_scope(char *sc);
void reset_scope();

/* ASSIGNMENT 1 & 2 functions*/

int detect_numeric(char *lex);
void detect_word(char *word, int length);
int detect_keyword(char *word);
int detect_separator(char *word);
int detect_operator(char *word);
int detect_identifier(char *word);
int identifier_detector;
void take_input_from_console();
void remove_comment_and_generate_stream();
void remove_extra_spaces();
void perform_separate();
void tokenizer();
FILE *final_output_tokenized;


/* TODO */
/*


//assigning variables values to another variables
//fix closing condition of scope
*/

//change in the function declaration in symbol table, that if it anything other than main, then make _deleted to true
//when function call deleted, print symbol table, make all those corresponding variables in the table to be true in symbol table
//display them and delete them again. THe function call is in line around 595

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
    int id_type; //var or func
    int data_type; //int/float/double
    char scope[50];
    int int_value;
    double double_value;
    int status; //if item is deleted
} _table[50];

/*   SCOPE/TABLE FUNCTIONS   */

void insert_table_item(struct table item);
const char* get_type(int typ);
void display_table();
void delete_item_from_table(char *name, char *scope);
void search_insert_item_to_table(int _data_type, char *name, char *scope, double value, int is_var);
void search_declare_item_from_table(int _data_type, char *name, char *scope, double value, int is_var);
void update_var_item_in_table(char *name, char *scope, double value);
void remove_id_from_identifiers();

/* GLOBAL VARIABLES */
int table_serial_counter = 1;
int scope_tracker;
char current_scope[50];

FILE *error_final_output_tokenized;
int error_identifier_detector;
int error_tokenize_line_counter = 0;
char error_token_id[1000][50];
char error_token[1000][50];
int error_token_line_number[1000];
int error_token_line_number_tracker = 1;
int error_token_tracker=0;


int main()
{
    //Assignment 1 & 2
    take_input_from_console();
    remove_comment_and_generate_stream();
    remove_extra_spaces();
    perform_separate();
    tokenizer();

    //Assignment 4
    error_remove_comment_and_generate_stream();
    error_remove_extra_spaces();
    error_perform_separate();
    error_tokenizer();
    generate_token_for_error();
    error_add_number_in_the_file();
    find_error();


    // Assignment 3
    tokenizeSeparator();
    process_intermediate_symbol_table();
    modified_token_stream();
    remove_id_from_identifiers();
    display_table_global_main();
    display_table();




    return 0;
}



void find_error()
{
    check_if_same();
    check_if_balanced("(",")");
    check_if_balanced("{","}");
    check_if_else();
}

void check_if_else()
{
    for(int i = error_token_tracker-1 ; i >= 0; i--)
    {
        if(!strcmp(error_token[i],"else") && strcmp(error_token[i+1],"if"))
        {
            int found = 1;
            for(int j = i-1 ; j >= 0; j--)
            {
                if(!strcmp(error_token[j],"else"))
                {
                    if(!strcmp(error_token[j+1],"if")){}
                    else{found++;}

                }
                else if(!strcmp(error_token[j],"if"))
                {
                    if(!strcmp(error_token[j-1],"else")){

                    }else{
                        found--;
                        if(found==0)
                        {
                            break;
                        }
                    }

                }
                else if(!strcmp(error_token_id[j],"kw") && !strcmp(error_token_id[j+1],"id") && !strcmp(error_token[j+2],"(")  )
                {
                    break;
                }
            }
            if(found!=0)
            {
                printf("Misplaced else at line %d\n", error_token_line_number[i] );
            }

        }
    }
}

void check_if_balanced(char *opening, char *closing)
{

    //checking forward
    for(int i = 0 ; i < error_token_tracker; i++)
    {
        if(!strcmp(error_token[i],opening))
        {
            int found = 1;
            for(int j = i+1 ; j < error_token_tracker; j++)
            {
                if(!strcmp(error_token[j],opening))
                {
                    found++;
                }
                else if(!strcmp(error_token[j],closing))
                {
                    found--;
                    if(found==0)
                    {
                        break;
                    }
                }
                else if(!strcmp(error_token_id[j],"kw") && !strcmp(error_token_id[j+1],"id") && !strcmp(error_token[j+2],"(")  )
                {
                    break;
                }
            }
            if(found!=0)
            {
                printf("Misplaced %s at line %d\n", opening,error_token_line_number[i] );
            }
        }
    }
    //checking backward
    for(int i = error_token_tracker-1 ; i >= 0; i--)
    {
        if(!strcmp(error_token[i],closing))
        {
            int found = 1;
            for(int j = i-1 ; j >= 0; j--)
            {
                if(!strcmp(error_token[j],closing))
                {
                    found++;
                }
                else if(!strcmp(error_token[j],opening))
                {
                    found--;
                    if(found==0)
                    {
                        break;
                    }
                }
                else if(!strcmp(error_token_id[j],"kw") && !strcmp(error_token_id[j+1],"id") && !strcmp(error_token[j+2],"(")  )
                {
                    break;
                }
            }
            if(found!=0)
            {
                printf("Misplaced %s at line %d\n", closing,error_token_line_number[i] );
            }
        }
    }

}

void check_if_same()
{
    for(int i = 0 ; i < error_token_tracker-1 ; i++)
    {
        if(!strcmp(error_token_id[i],error_token_id[i+1]) && strcmp(error_token_id[i],"par")
                && strcmp(error_token_id[i],"brc") && strcmp(error_token[i],"else") )
        {
            if( i>2 && !strcmp(error_token[i-2],"for"))
            {

            }
            else
            {
                printf("Duplicate token at %s line %d\n", error_token[i], error_token_line_number[i]);
            }

        }
    }
}


void generate_token_for_error()
{
    FILE *p1;
    char c;

    p1 = fopen("error_tokenized_file.txt", "r");
    if(!p1)printf("\nTokenized File can't be opened!");
    else
    {
        while((c=fgetc(p1)) != EOF)
        {
            ungetc(c,p1);
            error__read_each_tokens_from_file(p1);
        }
    }
    fclose(p1);
}

void error__read_each_tokens_from_file(FILE *p2)
{
    char c;
    char token[100];
    token[0] = '\0';
    char cToStr[2];
    cToStr[1] = '\0';
    int space_counter = 0;
    while(c=fgetc(p2))
    {
        if(c=='\n')
        {
            error_tokenize_line_counter++;
            break;
        }
        else if(c==' ' && space_counter == 1)
        {
            space_counter=0;
            break;
        }
        else if(c==' ' && space_counter == 0)
        {
            space_counter++;
        }

        cToStr[0] = c;
        strcat(token,cToStr);
    }
    if(strlen(token)!=0)
    {
        printf("%s ", token);
        error_process_token(token);
    }
    else
    {
        error_token_line_number_tracker++;
    }

}

void error_process_token(char *token)
{
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

    strcpy(error_token_id[error_token_tracker],first);
    strcpy(error_token[error_token_tracker],second);
    error_token_line_number[error_token_tracker++] = error_token_line_number_tracker;
}


void error_tokenizer()
{
    char c;
    FILE *p2;
    p2=fopen("error_stream_separator_file.txt", "r");
    error_final_output_tokenized = fopen("error_tokenized_file.txt", "w");
    char reader[100];
    int readerCounter = 0;
    while((c=fgetc(p2)) != EOF)
    {
        if(c=='\n')
        {
            printf("\n");
            fputs("\n", error_final_output_tokenized);
        }
        else if(c==' ')
        {
            error_detect_word(reader,readerCounter);
            readerCounter = 0;
        }
        else
        {
            reader[readerCounter] = c;
            readerCounter++;
        }
        //printf("%c", c);
    }
    fclose(p2);
    fclose(error_final_output_tokenized);

    printf("\n\n");

}

void error_detect_word(char *word, int length)
{

    char str[length];
    for(int i = 0 ; i < length; i++)
    {
        str[i] = word[i];
    }
    int keyword_detector, numeric_detector, separator_detector;
    keyword_detector = error_detect_keyword(str);

    if(keyword_detector==0)
    {
        numeric_detector = error_detect_numeric(str);
    }
    if(numeric_detector==0 && keyword_detector==0)
    {
        error_detect_identifier(str);

        // POSSIBLE ERROR, if identifier is found, it should not check separator detector

        separator_detector = error_detect_separator(str);
        if(error_identifier_detector==0 && separator_detector==0)
        {

            //CHANGES : CHANGED HERE
            printf("unkn ");
            fputs("unkn ", error_final_output_tokenized);

        }
    }


    if(str[0]!='\1') //handling SOH error
    {
        //CHANGES : CHANGED HERE
        printf("%s ", str);
        fputs(str, error_final_output_tokenized);
        fputs(" ", error_final_output_tokenized);
    }
}

int error_detect_separator(char *word)
{
    if(strlen(word)==1)
    {
        char c = word[0];
        //CHANGES : changed the print statements a bit
        if(c==',' || c ==';' || c==':' || c=='\'') //detected separator
        {
            printf("sep ");
            fputs("sep ", error_final_output_tokenized);
            return 1;
        }
        if(c=='(' || c==')' || c=='[' || c==']') //detected paranthesis
        {
            printf("par ");
            fputs("par ", error_final_output_tokenized);
            return 1;
        }
        if(c=='{' || c=='}') //detected bracket
        {
            printf("brc ");
            fputs("brc ", error_final_output_tokenized);
            return 1;
        }
        if(c=='+' || c=='-' || c=='*' || c =='/' || c=='=') //detected operator
        {
            printf("op ");
            fputs("op ", error_final_output_tokenized);
            return 1;
        }

        //CHANGES : ADDED THIS
        if(c=='<' || c=='>') //detected operator
        {
            printf("op ");
            fputs("op ", error_final_output_tokenized);
            return 1;
        }

    }
    else if(strlen(word)==2)
    {
        char c = word[0];
        char c2 = word[1];
        if( (c=='+' || c=='-' || c=='/' || c=='*' ||
                c=='=' || c=='<' || c=='>' || c=='!' || c=='%')
                && c2=='=' )
        {
            printf("op ");
            fputs("op ", error_final_output_tokenized);
            return 1;
        }

        //add logical operators code here
    }
    else
    {
        return 0;
    }
}


int error_detect_keyword(char *word)
{
    char keywords[32][15] =
    {
        "auto", "break", "case", "char", "continue", "const", "default",
        "do", "double", "else", "enum", "extern", "if", "float",
        "for", "goto", "int", "long", "return", "register", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    int flag;
    for(int i = 0; i < 32; i++)
    {

        if(strlen(word) != strlen(keywords[i])) // checking if word size matches with keyword size
        {
            continue;
        }
        flag = 1;
        for(int j = 0 ; j < strlen(keywords[i]) ; j++)
        {
            if(word[j]!=keywords[i][j])
            {
                flag = 0;
                break;
            }
        }

        if(flag ==1) //keyword match found
        {
             //CHANGES : changed here only
            printf("kw ");
            fputs("kw ", error_final_output_tokenized);
            return 1;
        }
    }
    return 0;
}


int error_detect_numeric(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;

    l=strlen(lex);

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=1;
            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    }

    if(s==2)
    {
        if(isdigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    }

    if(s==3)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=3;
            else
            {
                s=0;
                break;
            }
        }
    }

    if(s==3 || s==1)
    {
         //CHANGES : changed here only
        s=1;
        printf("num ");
        fputs("num ", error_final_output_tokenized);
    }
    return s;
}

int error_detect_identifier(char *word)
{
    int i, l, s;
    i=0;
    if(isalpha(word[i]) || word[i]=='_')
    {
        s=1;
        i++;
    }
    else
    {
        s=0;
    }

    l=strlen(word);

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(word[i]) || isalpha(word[i]) || word[i]=='_')
                s=1;
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s==1)
    {

        //CHANGES : changed here only
        printf("id ");
        fputs("id ", error_final_output_tokenized);
        error_identifier_detector = 1;
    }
    else
    {
        error_identifier_detector = 0;
    }

    return s;
}



void error_perform_separate()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("error_removed_extra_spaces.txt", "r");
    p2 = fopen("error_stream_separator_file.txt", "w");

    if(!p1)printf("\nFile can't be opened!");
    else
    {
        char prev; // saving previous printed character
        int separator = 0; // this separator checks if the previous character is a separator
        // or not. Or else for consecutive separator, multiple spaces gets printed
        while((c=fgetc(p1))!=EOF)
        {

            //add spaces between separators

            //CHANGES : added this if condition
            if(prev=='\n' && (c=='{' || c=='}')){
                fputc(c, p2);
                fputc(' ', p2);
                separator = 1;
                prev = '\n';
                continue;
            }


            if(c=='(' || c==')' || c==',' || c ==';' || c=='{' || c=='}'
                    || c=='*' || c=='+' || c=='/' || c=='-' || c=='='|| c=='\''
                    || c==':' || c=='[' || c==']' || c=='%' || c=='<' || c=='>')
            {
                if(c=='=')
                {
                    if(prev=='+' || prev=='-' || prev=='/' || prev=='*' ||
                            prev=='=' || prev=='<' || prev=='>' || prev=='!' || prev=='%' )
                    {
                        //checking operator
                        fputc(c, p2);
                        fputc(' ', p2);
                        prev = ' ';
                        separator = 1;
                        continue;
                    }
                }
                if(prev!=' ' && separator == 0) //for operators, put space
                {
                    fputc(' ',p2);
                }
                fputc(c,p2);
                prev = c;
                c=fgetc(p1);
                if(c!=' ' && c!='+' && c!='-' && c!='/' && c!='*' && c!='<' && c!='>' && c!='=')
                {
                    fputc(' ',p2);
                    //prev = ' ';
                }
                ungetc(c,p1);
                separator = 1;
            }
            else
            {
                //for non separator words
                fputc(c,p2);
                prev = c;
                separator = 0;
            }

        }
    }

    fclose(p1);
    fclose(p2);

    printf("\n\n");


}

void error_remove_extra_spaces()
{
    FILE *p1, *p2;

    char c,prev='z';
    p1 = fopen("error_remove_comment_and_generate_stream.txt", "r");
    p2 = fopen("error_removed_extra_spaces.txt", "w");

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {
        prev = 'a';
        while((c=fgetc(p1))!=EOF)
        {
            if(c==' ')
            {
                if(prev!=' ')
                {
                    fputc(c,p2);
                }
            }
            else
            {
                fputc(c,p2);
            }
            prev = c;
        }
    }

    fclose(p1);
    fclose(p2);

    printf("\n\n");

}


void error_add_number_in_the_file()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("error_tokenized_file.txt", "r");
    p2 = fopen("error_added_number_lines.txt", "w");
    int lineNumber = 0;
    printf("\n\n");
    if(!p1)printf("\nFile can't be opened!");
    else
    {
        error_get_number_for_file(++lineNumber,p2);
        while((c=fgetc(p1))!=EOF)
        {
            fputc(c,p2);
            if(c=='\n')
            {
                error_get_number_for_file(++lineNumber,p2);
            }
        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("error_added_number_lines.txt", "r");
    while((c=fgetc(p2)) != EOF)
        printf("%c", c);
    fclose(p2);

    printf("\n\n");
}


int error_get_number_for_file(int num, FILE *p)
{
    char converter;

    while(num!=0)
    {
        int lastDigit = num%10;
        num /= 10;
        push(lastDigit);
    }

    while(!isempty())
    {
        int data = pop();
        converter = (char) data-208;
        fputc(converter,p);
    }
    fputc(' ',p);
}



void error_remove_comment_and_generate_stream()
{
    FILE *p1, *p2;

    char c,prev='z';
    p1 = fopen("console_input_to_txt_file.txt", "r");
    p2 = fopen("error_remove_comment_and_generate_stream.txt", "w");

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!  ");
    else
    {
        char prev;

        while((c=fgetc(p1))!=EOF)
        {

            if(c=='/')
            {
                char temp=fgetc(p1);
                if(temp=='/')
                {
                    while((c=fgetc(p1))!='\n')
                    {}  // remove // comment
                    fputc('\n',p2);
                }
                else if(temp=='*')
                {
                    char tempChar = c;
                    while(1)
                    {
                        if(tempChar=='*' && c == '/')
                        {
                            break;
                        }
                        tempChar = c;
                        c = fgetc(p1);
                        if(c=='\n')
                            fputc('\n',p2);
                    }
                }
                else
                {
                    ungetc(temp,p1);
                    fputc('/',p2);
                }
            }
            else
            {
                fputc(c,p2);
            }
            prev = c;
        }
    }

    fclose(p1);
    fclose(p2);

    printf("\n\n");

}


void update_scope(char *sc)
{
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
            //variable with same name found in the same scope
            printf("\nERROR : Insertion Failed as variable with %s found in scope %s\n", name, scope);
            get_line_number_for_var_declaration(name,"variable with same name found");
            return;
        }
    }

    //variable with same name NOT found in the same scope, so safe to insert
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

void get_line_number_for_var_declaration(char *name, char *msg){
    char removed_id[30];
    char c;
    int i;
    int count = strlen(name) -3;
    for(i = 0; i < count ; i++)
    {
        removed_id[i] = name[i+3];
    }
    removed_id[i] = '\0';

    for(int j = 0 ; j < error_token_tracker; j++){
        if(!strcmp(error_token_id[j],"id") && !strcmp(error_token[j],removed_id)){
            printf("\nError at line number %d %s ", error_token_line_number[j], msg);
            break;
        }
    }

}

void search_declare_item_from_table(int _data_type, char *name, char *scope, double value, int is_var)
{
    printf("\n\nSearching Item - Name : %s  |  Scope : %s\n", name, scope);

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, scope))
        {
            //variable with same name found in the same scope
            printf("\nERROR : Insertion Failed as variable with %s found in scope %s\n", name, scope);
            get_line_number_for_var_declaration(name,"as variable with same name exits");
            return;
        }
    }
    //variable with same name NOT found in the same scope, so safe to insert
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
        /*
            //POSSIBLE ERROR : THIS SHOULD BE _float_data
        tab.double_value = value;
        tab.data_type = _float_data; //check if it works later..
        //tab.data_type = _double_data; //this was working previously
        */
        tab.double_value = value;
        tab.data_type = _double_data;
    }
    insert_table_item(tab);
}


//assigning values to declared variables
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

    //if variable not available in the current scope, search in the global scope

    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && !strcmp(_table[i].name, name) && !strcmp(_table[i].scope, "global"))
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

    printf("\nERROR : Variable with name %s anywhere\n", name);
    get_line_number_for_var_declaration(name,"variable with this name is not declared");

}

void remove_id_from_identifiers()
{
    //the word 'id ' appears in all the name of identifiers (due to tokens), so removing it
    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted)
        {
            int j;
            for(j = 3; j < strlen(_table[i].name); j++)
            {
                _table[i].name[j-3] = _table[i].name[j];
            }
            _table[i].name[j-3] = '\0';
        }
    }
    //removing id from function names
    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && _table[i].scope[0]=='i' && _table[i].scope[1]=='d' && _table[i].scope[2]==' ')
        {
            int j;
            for(j = 3; j < strlen(_table[i].scope); j++)
            {
                _table[i].scope[j-3] = _table[i].scope[j];
            }
            _table[i].scope[j-3] = '\0';
        }

    }

}



void modified_token_stream()
{

    printf("\n\n");
    reset_scope();
    scope_tracker = -1;
    FILE *p1, *p2;
    char c;
    p2 = fopen("modified_token_stream.txt", "w");
    for(int i = 0 ; i < intermediate_symbol_table_counter; i++)
    {
        //POSSIBLE ERROR, increment i properly
        if(scope_tracker!=-1) //checks if any user defined function has ended or not, and changes scope
        {
            if(i>scope_tracker)
            {
                reset_scope();
                scope_tracker = -1;
            }
        }

        if( (i+1)<intermediate_symbol_table_counter && intermediate_symbol_table[i][0]=='i' && intermediate_symbol_table[i][1]=='d'
                && intermediate_symbol_table[i][2]==' ' && !strcmp(intermediate_symbol_table[i+1],"(")) //finds out what scope the program is in
        {
            update_scope(intermediate_symbol_table[i]);
            for(scope_tracker=i; scope_tracker < intermediate_symbol_table_counter; scope_tracker++)
            {
                if(!strcmp(intermediate_symbol_table[scope_tracker],"}"))
                {
                    break;
                }
            }
        }

        if(intermediate_symbol_table[i][0]=='i' && intermediate_symbol_table[i][1]=='d' && intermediate_symbol_table[i][2]==' ')
        {
            int found = 0;
            for(int j = 1 ; j < table_serial_counter; j++)
            {
                //tries to find variable in the current scope from symbol table
                if(_table[j].status != _deleted && !strcmp(_table[j].name, intermediate_symbol_table[i]) && !strcmp(_table[j].scope, current_scope))
                {
                    found =1;
                    printf("[id %d]", _table[j].serial_number);
                    fputs("[id ", p2);
                    char snum[10];
                    itoa(_table[j].serial_number, snum, 10);
                    fputs(snum, p2);
                    fputs("]", p2);
                    break;
                }
            }
            if(found==0)
            {
                //tries to find variable in the global scope inside the symbol table
                for(int j = 1 ; j < table_serial_counter; j++)
                {

                    if(_table[j].status != _deleted && !strcmp(_table[j].name, intermediate_symbol_table[i]) && !strcmp(_table[j].scope, "global"))
                    {
                        printf("[id %d]", _table[j].serial_number);
                        fputs("[id ", p2);
                        char snum[10];
                        itoa(_table[j].serial_number, snum, 10);
                        fputs(snum, p2);
                        fputs("]", p2);
                        break;
                    }
                }
            }
        }
        else
        {
            printf("[%s]", intermediate_symbol_table[i]);
            fputs("[", p2);
            fputs(intermediate_symbol_table[i], p2);
            fputs("]", p2);
        }
    }
    fclose(p2);

    printf("\n\n");
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

void display_table_global_main()
{
    printf("Serial Number \tName \t Id Type \t Data Type \t  Scope \t Value\n\n");
    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && (!strcmp(_table[i].scope,"global") || !strcmp(_table[i].scope,"id main") || !strcmp(_table[i].scope,"main") ) ) //only display item if they are not deleted
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

void display_symbol_table_with_function(char *function_name)
{
    printf("\nBefore making function call for %s\n", function_name);
    display_table_global_main();
    printf("\n\nSerial Number \tName \t Id Type \t Data Type \t  Scope \t Value\n\n");
    for(int i = 1 ; i < table_serial_counter; i++)
    {
        if(_table[i].status != _deleted && (!strcmp(_table[i].scope,"global") || !strcmp(_table[i].scope,"id main") ||  !strcmp(_table[i].scope,function_name)  ) ) //only display item if they are not deleted
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
    printf("\nAfter making function call for %s\n", function_name);
    display_table_global_main();
}

//all the symbol table works is called from this function
int detect_variable_declaration(int i)
{
    if(scope_tracker!=-1) //checks if any user defined function has ended or not, and changes scope
    {
        if(i>scope_tracker)
        {
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
            //var assignment and declaration of int values
            if(!strcmp(intermediate_symbol_table[i],"int"))
            {
                search_insert_item_to_table(get_corresponding_enum(intermediate_symbol_table[i]),
                                            intermediate_symbol_table[i+1], current_scope,
                                            atoi(intermediate_symbol_table[i+3]), _var );
            }
            else if(!strcmp(intermediate_symbol_table[i],"double") || !strcmp(intermediate_symbol_table[i],"float") )
            {
                //var assignment and declaration of float/double values
                char *ptr;
                double ret;
                ret = strtod(intermediate_symbol_table[i+3], &ptr);
                search_insert_item_to_table(get_corresponding_enum(intermediate_symbol_table[i]),
                                            intermediate_symbol_table[i+1], current_scope, ret, _var );
            }
            i = i+4;
        }
        else if(!strcmp(intermediate_symbol_table[i+2],";"))
        {
            //var declaration only
            search_declare_item_from_table(get_corresponding_enum(intermediate_symbol_table[i]),
                                           intermediate_symbol_table[i+1], current_scope, 32765, _var );
            i = i+2;
        }
        else if(!strcmp(intermediate_symbol_table[i+2],"("))
        {
            //function declaration
            update_scope(intermediate_symbol_table[i+1]); //updating scope to that function
            search_declare_item_from_table(get_corresponding_enum(intermediate_symbol_table[i]),
                                           intermediate_symbol_table[i+1],"global", 32765, _func); //inserting function to symbol table
            i = i + 3;
            if(!strcmp(intermediate_symbol_table[i],")"))
            {
                //if no parameters inside function declaration
                i++;
            }
            else
            {
                int j = i;
                for( ; ; j=j+3)
                {
                    //insert the parameters into the symbol table
                    search_declare_item_from_table(get_corresponding_enum(intermediate_symbol_table[j]),
                                                   intermediate_symbol_table[j+1],current_scope, 32765, _var);
                    if(!strcmp(intermediate_symbol_table[j+2],")"))
                    {
                        i = j+2;
                        break;
                    }
                }
            }

            for(scope_tracker=i; scope_tracker < intermediate_symbol_table_counter; scope_tracker++)
            {
                if(!strcmp(intermediate_symbol_table[scope_tracker],"}"))
                {
                    //finding out when the scope changes
                    break;
                }
            }

        }
    }
    else if(!strcmp(intermediate_symbol_table[i+1],"="))
    {
        if(!strcmp(intermediate_symbol_table[i+3],"("))
        {

            display_symbol_table_with_function(intermediate_symbol_table[i+2]);
            int k ;
            i = i + 3;
            for(k= 0; k < 15; k++ )
            {
                if(!strcmp(intermediate_symbol_table[i],")"))
                {
                    break;
                }
                i++;
            }

        }
        else
        {
            //var assignment
            char *ptr;
            double ret;
            ret = strtod(intermediate_symbol_table[i+2], &ptr);
            update_var_item_in_table(intermediate_symbol_table[i],current_scope, ret);
            i = i+3;
        }

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
        strcpy(intermediate_symbol_table[intermediate_symbol_table_counter++],str); //storing these values to later create symbol table
    }
    else
    {
        //separated the tokens and keeping second part only
        printf("[%s] ", second);
        fputs("[", p1);
        fputs(second, p1);
        fputs("] ", p1);
        strcpy(intermediate_symbol_table[intermediate_symbol_table_counter++],second); //storing these values to later create symbol table
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
    fgetc(p2); //this is shallow copying so pointer gets updated //this removes the spaces between each token
    process_token(token); //a token is fetched excluding the third brackets
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


void remove_extra_spaces()
{
    FILE *p1, *p2;

    char c,prev='z';
    p1 = fopen("remove_comment_and_generate_stream.txt", "r");
    p2 = fopen("removed_extra_spaces.txt", "w");

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {
        prev = 'a';
        while((c=fgetc(p1))!=EOF)
        {
            if(c==' ')
            {
                if(prev!=' ')
                {
                    fputc(c,p2);
                }
            }
            else
            {
                fputc(c,p2);
            }
            prev = c;
        }
    }

    fclose(p1);
    fclose(p2);

    printf("\n\n");
    p2=fopen("removed_extra_spaces.txt", "r");
    while((c=fgetc(p2))  !=  EOF)printf("%c",  c);
    printf("\n\n");
    fclose(p2);
}


void tokenizer()
{
    char c;
    FILE *p2;
    p2=fopen("stream_separator_file.txt", "r");
    final_output_tokenized = fopen("tokenized_file.txt", "w");
    char reader[100];
    int readerCounter = 0;
    while((c=fgetc(p2)) != EOF)
    {
        if(c==' ')
        {
            detect_word(reader,readerCounter);
            readerCounter = 0;
        }
        else
        {
            reader[readerCounter] = c;
            readerCounter++;
        }
        //printf("%c", c);
    }
    fclose(p2);
    fclose(final_output_tokenized);

    printf("\n\n");

}

void perform_separate()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("removed_extra_spaces.txt", "r");
    p2 = fopen("stream_separator_file.txt", "w");

    if(!p1)printf("\nFile can't be opened!");
    else
    {
        char prev; // saving previous printed character
        int separator = 0; // this separator checks if the previous character is a separator
        // or not. Or else for consecutive separator, multiple spaces gets printed
        while((c=fgetc(p1))!=EOF)
        {

            //add spaces between separators
            if(c=='(' || c==')' || c==',' || c ==';' || c=='{' || c=='}'
                    || c=='*' || c=='+' || c=='/' || c=='-' || c=='='|| c=='\''
                    || c==':' || c=='[' || c==']' || c=='%' || c=='<' || c=='>')
            {
                if(c=='=')
                {
                    if(prev=='+' || prev=='-' || prev=='/' || prev=='*' ||
                            prev=='=' || prev=='<' || prev=='>' || prev=='!' || prev=='%' )
                    {
                        //checking operator
                        fputc(c, p2);
                        fputc(' ', p2);
                        prev = ' ';
                        separator = 1;
                        continue;
                    }
                }
                if(prev!=' ' && separator == 0) //for operators, put space
                {
                    fputc(' ',p2);
                }
                fputc(c,p2);
                prev = c;
                c=fgetc(p1);
                if(c!=' ' && c!='+' && c!='-' && c!='/' && c!='*' && c!='<' && c!='>' && c!='=')
                {
                    fputc(' ',p2);
                    //prev = ' ';
                }
                ungetc(c,p1);
                separator = 1;
            }
            else
            {
                //for non separator words
                fputc(c,p2);
                prev = c;
                separator = 0;
            }

        }
    }

    fclose(p1);
    fclose(p2);

    printf("\n\n");
    p2=fopen("stream_separator_file.txt", "r");
    while((c=fgetc(p2))  !=  EOF)printf("%c",  c);
    printf("\n\n");
    fclose(p2);

}

void detect_word(char *word, int length)
{

    char str[length];
    for(int i = 0 ; i < length; i++)
    {
        str[i] = word[i];
    }
    int keyword_detector, numeric_detector, separator_detector;
    keyword_detector = detect_keyword(str);

    if(keyword_detector==0)
    {
        numeric_detector = detect_numeric(str);
    }
    if(numeric_detector==0 && keyword_detector==0)
    {
        detect_identifier(str);
        separator_detector = detect_separator(str);
        if(identifier_detector==0 && separator_detector==0)
        {
            printf("[unkn ");
            fputs("[unkn ", final_output_tokenized);

        }
    }


    if(str[0]!='\1') //handling SOH error
    {
        printf("%s] ", str);
        fputs(str, final_output_tokenized);
        fputs("] ", final_output_tokenized);
    }
}

int detect_separator(char *word)
{
    if(strlen(word)==1)
    {
        char c = word[0];
        if(c==',' || c ==';' || c==':' || c=='\'') //detected separator
        {
            printf("[sep ");
            fputs("[sep ", final_output_tokenized);
            return 1;
        }
        if(c=='(' || c==')' || c=='[' || c==']') //detected paranthesis
        {
            printf("[par ");
            fputs("[par ", final_output_tokenized);
            return 1;
        }
        if(c=='{' || c=='}') //detected bracket
        {
            printf("[brc ");
            fputs("[brc ", final_output_tokenized);
            return 1;
        }
        if(c=='+' || c=='-' || c=='*' || c =='/' || c=='=') //detected operator
        {
            printf("[op ");
            fputs("[op ", final_output_tokenized);
            return 1;
        }
    }
    else if(strlen(word)==2)
    {
        char c = word[0];
        char c2 = word[1];
        if( (c=='+' || c=='-' || c=='/' || c=='*' ||
                c=='=' || c=='<' || c=='>' || c=='!' || c=='%')
                && c2=='=' )
        {
            printf("[op ");
            fputs("[op ", final_output_tokenized);
            return 1;
        }

        //add logical operators code here
    }
    else
    {
        return 0;
    }
}


int detect_keyword(char *word)
{
    char keywords[32][15] =
    {
        "auto", "break", "case", "char", "continue", "const", "default",
        "do", "double", "else", "enum", "extern", "if", "float",
        "for", "goto", "int", "long", "return", "register", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    int flag;
    for(int i = 0; i < 32; i++)
    {

        if(strlen(word) != strlen(keywords[i])) // checking if word size matches with keyword size
        {
            continue;
        }
        flag = 1;
        for(int j = 0 ; j < strlen(keywords[i]) ; j++)
        {
            if(word[j]!=keywords[i][j])
            {
                flag = 0;
                break;
            }
        }

        if(flag ==1) //keyword match found
        {
            printf("[kw ");
            fputs("[kw ", final_output_tokenized);
            return 1;
        }
    }
    return 0;
}


int detect_numeric(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;

    l=strlen(lex);

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=1;
            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    }

    if(s==2)
    {
        if(isdigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    }

    if(s==3)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=3;
            else
            {
                s=0;
                break;
            }
        }
    }

    if(s==3 || s==1)
    {
        s=1;
        printf("[num ");
        fputs("[num ", final_output_tokenized);
    }
    return s;
}

int detect_identifier(char *word)
{
    int i, l, s;
    i=0;
    if(isalpha(word[i]) || word[i]=='_')
    {
        s=1;
        i++;
    }
    else
    {
        s=0;
    }

    l=strlen(word);

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(word[i]) || isalpha(word[i]) || word[i]=='_')
                s=1;
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s==1)
    {
        printf("[id ");
        fputs("[id ", final_output_tokenized);
        identifier_detector = 1;
    }
    else
    {
        identifier_detector = 0;
    }

    return s;
}


void remove_comment_and_generate_stream()
{
    FILE *p1, *p2;

    char c,prev='z';
    p1 = fopen("console_input_to_txt_file.txt", "r");
    p2 = fopen("remove_comment_and_generate_stream.txt", "w");

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!  ");

    else
    {

        while((c=fgetc(p1))!=EOF)
        {
            if(c=='\n')
            {} //do nothing when \n
            else if(c==' ' && prev=='\n')
            {
                while((c=fgetc(p1))==' ')
                {} //remove all spaces at the beginning of line
                ungetc(c,p1);
            }
            else if(c=='/' && prev=='/')
            {
                while((c=fgetc(p1))!='\n')
                {}  // remove // comment
            }
            else if(prev=='/' && c=='*')
            {
                //remove multiline comment
                char tempChar = c;
                while(1)
                {
                    if(tempChar=='*' && c == '/')
                    {
                        break;
                    }
                    tempChar = c;
                    c = fgetc(p1);
                }

            }
            else
            {
                ungetc(c,p1); //start printing line until \n and if there are no more comments
                while((c=fgetc(p1))!='\n')
                {
                    if(c=='/')
                    {

                        char c1 = fgetc(p1);
                        if(c1=='/') //checking single line comment
                        {
                            while((c=fgetc(p1))!='\n')
                            {

                            }
                            c = '\n';
                            break;
                        }
                        else if(c1=='*') //checking multi line comment
                        {

                            char tempChar = c1;
                            while(1)
                            {
                                if(tempChar=='*' && c1 == '/')
                                {
                                    break;
                                }
                                tempChar = c1;
                                c1 =fgetc(p1);
                            }
                            break;
                        }
                        else
                        {
                            fputc('/',p2);
                            ungetc(c1,p1);
                        }

                    }
                    else
                    {
                        fputc(c,p2);
                        if(c==';') //remove white spaces after ';' (if there are any)
                        {
                            c=fgetc(p1);
                            if(c==' ')
                            {
                                while(c==' ')
                                {
                                    c=fgetc(p1);
                                }
                                ungetc(c,p1);
                            }
                            else
                            {
                                ungetc(c,p1);
                            }
                        }
                    }
                }
            }
            prev = c;
        }
    }

    fclose(p1);
    fclose(p2);



}



void take_input_from_console()
{
    char ch[100][200];
    char c1;
    char temp[200];
    int i = 0;
    FILE *fp;
    fp = fopen("console_input_to_txt_file.txt", "w");
    int eof_tracker = 0;
    while(1)
    {
        gets(ch[i]);
        if(ch[i][0]=='\0')
        {
            eof_tracker++;
            if(eof_tracker==3) //user input terminated after 3 carriage return
            {
                break;
            }
        }
        else
        {
            eof_tracker = 0;
        }
        for(int j = 0 ; j < strlen(ch[i]); j++)
        {
            if(ch[i][j]!='\0') //represents end of a line
            {
                fputc(ch[i][j],fp);
            }
        }
        i++;
        fputc('\n',fp);

    }

    fclose(fp);

}


