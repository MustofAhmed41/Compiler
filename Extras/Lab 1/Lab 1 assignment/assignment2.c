#include <stdio.h>//hello world
// hello world

/*

12345
23
45
*/
//SUBMIT test.c FILE
int main()
{
    FILE *p1, *p2;

    char c,prev='z';
    p1 = fopen("assignment2.c", "r");
    p2 = fopen("assignment2.txt", "w"); /* abcd */

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!  "); // hello world

    else
    {

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
                fputc(c,p2);
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
                            c = '/';
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
                    }
                }
            }
            prev = c;
        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("assignment2.txt", "r");

    while((c=fgetc(p2))  !=  EOF)printf("%c",  c);

    fclose(p2);

    return   0;
}


