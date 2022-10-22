#include <stdio.h>
#include <ctype.h>
#include <string.h>

int detect_numeric(char *lex);
void detect_word(char *word, int length);
int detect_keyword(char *word);
int detect_separator(char *word);
int detect_operator(char *word);
int detect_identifier(char *word);
int identifier_detector;
void take_input_from_console();
void remove_comment_and_generate_stream();
void perform_separate();
void tokenizer();
FILE *final_output_tokenized;

/*
TODO: REMOVE EXTRA SPACES IN A LINE
DO THIS ON output of separator.
ALGO : say if there are two spaces consecutively, remove them
do it in a function say remove redundant spaces
*/


int main ()
{
    take_input_from_console();
    remove_comment_and_generate_stream();
    perform_separate();
    tokenizer();
    return 0;
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
}

void perform_separate()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("remove_comment_and_generate_stream.txt", "r");
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
                    { //checking operator
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
        if(c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']') //detected paranthesis
        {
            printf("[par ");
            fputs("[par ", final_output_tokenized);
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
            { //remove multiline comment
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

    p2=fopen("remove_comment_and_generate_stream.txt", "r");

    while((c=fgetc(p2))  !=  EOF)printf("%c",  c);
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


