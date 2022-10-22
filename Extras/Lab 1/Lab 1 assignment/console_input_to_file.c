#include <stdio.h>
#include <string.h>

void take_input_from_console();


int main(){
    take_input_from_console();

    return 0;
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
