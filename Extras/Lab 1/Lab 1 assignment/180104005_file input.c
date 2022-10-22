#include <stdio.h>
// hello world

/*

12345
23
45
*/#include <math.h>

int main()
{
    FILE *p1, *p2;   // hello world
    // abc
    char c,prev='z';
    p1 = fopen("180104005.c", "r");
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

    fclose(p2);  int xyz;

    return   0;
}



