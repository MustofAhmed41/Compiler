#include <stdio.h>
// hello world
#include <math.h>
void take_input_from_console();
void remove_comment_and_generate_stream();

int main()
{
    take_input_from_console();
    remove_comment_and_generate_stream();
    return   0;
}

void remove_comment_and_generate_stream(){
    FILE *p1, *p2;   // hello world

    char c,prev='z';
    p1 = fopen("main_input_for_assignment_1.txt", "r");
    p2 = fopen("output.txt", "w"); /* abcd */

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!  ");

    else
    {

/*   abcd    */

        while((c=fgetc(p1))!=EOF)
        {
            if(c=='\n')
            {

            }
            else if(c==' ' && prev=='\n')
            {
                while((c=fgetc(p1))==' ')
                {

                }
                ungetc(c,p1);
            }
            else if(c=='/' && prev=='/')
            {
                while((c=fgetc(p1))!='\n')
                {

                }
            }
            else if(prev=='/' && c=='*')
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
                }

            }
            else
            {
                ungetc(c,p1);
                while((c=fgetc(p1))!='\n')
                {
                    if(c=='/')
                    {

                        char c1 = fgetc(p1);
                        if(c1=='/')
                        {
                            while((c=fgetc(p1))!='\n')
                            {

                            }
                            c = '\n';
                            break;
                        }
                        else if(c1=='*')
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
                        if(c==';'){
                            c=fgetc(p1);
                            if(c==' '){
                                while(c==' ')
                                {
                                    c=fgetc(p1);
                                }
                                ungetc(c,p1);
                            }else{
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

    p2=fopen("output.txt", "r");

    while((c=fgetc(p2))  !=  EOF)printf("%c",  c);

    fclose(p2);
}



void take_input_from_console(){
    char ch[100][100];
    char c1;
    char temp[100];
    int i = 0;
    FILE *fp;
    char inp[5000];
    fp = fopen("main_input_for_assignment_1.txt", "w");
    int eof_tracker = 0;
    while(1){
        gets(ch[i]);
        if(ch[i][0]=='\0'){
            eof_tracker++;
            if(eof_tracker==3){
                break;
            }
        }else{
            eof_tracker = 0;
        }
        for(int j = 0 ; j < strlen(ch[i]); j++){
            if(ch[i][j]!='\0'){
                fputc(ch[i][j],fp);
            }
        }
        i++;
        fputc('\n',fp);

    }

    fclose(fp);
}


