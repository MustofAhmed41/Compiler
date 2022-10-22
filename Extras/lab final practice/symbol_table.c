#include <stdio.h>
#include <string.h>
#include <ctype.h>

int number[100];
char num[100][100];
char id[100][100];
char var[100][100];
int lines = 0;
FILE *p2;

void process(char *inp){

    num[lines][0] = inp[0];
    num[lines][1] = '\0';
    for(int i = 2 ; i < 6; i++){
        if(inp[i]==' '){
            id[lines][i-2] = '\0';
            break;
        }
        id[lines][i-2] = inp[i];
    }
    for(int i = 7 ; i < 10; i++){
        if(inp[i]==' '){
            id[lines][i-7] = '\0';
            break;
        }
        var[lines][i-7] = inp[i];
    }
    lines++;
    puts(inp);
}

void read_file()
{
    FILE *p1;

    char c,prev='z';
    p1 = fopen("symbol.txt", "r");
    char str[100];
    int str_counter = 0;
    int newLine=0;
    if(!p1)printf("\nFile can't be opened!  ");

    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c!='\n'){
                str[str_counter++] = c;
            }
            if(c=='\n'){
                str[str_counter] = '\0';
                process(str);
                str[0] ='\0';
                str_counter = 0;
            }
            //printf("%c", c);
        }
        str[str_counter] = '\0';
        process(str);
    }

    fclose(p1);
}


void process2(char *inp){
    for(int i = 0; i < lines ; i++){
        if(!strcmp(inp,id[i])){
            printf("id %d]", i+1);
            fputs("id ",p2);
            char snum[5];
            itoa(i+1, snum, 10);
            fputs(snum,p2);
            fputs("]",p2);
            break;
        }
    }
}


void read_token(){

    FILE *p1;

    char c,c2, prev='z';
    p1 = fopen("token.txt", "r");
    char str[100];
    int str_counter = 0;

    if(!p1)printf("\nFile can't be opened!  ");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='i'){
                c2=fgetc(p1);
                if(c2=='d'){
                    c = fgetc(p1);//eat space

                    for(int i = 0 ; i < 10 ; i++){
                        str[i] = fgetc(p1);
                        if(str[i]==']'){
                            str[i] = '\0';
                            process2(str);
                            break;
                        }
                    }
                }else{
                    ungetc(c2,p1);
                }
            }
            printf("%c", c);
            fputc(c,p2);
        }
    }

    fclose(p1);

}


int main(){
    read_file();
    p2 = fopen("output.txt", "w");
     for(int i = 0 ; i < lines; i++){
        printf("%s %s %s\n", num[i], id[i], var[i]);
    }
    read_token();
    fclose(p2);
    return 0;
}
