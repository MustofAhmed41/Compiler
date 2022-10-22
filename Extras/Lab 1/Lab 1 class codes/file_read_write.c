
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <math.h>
//reads headers
int main(void)
{

    FILE *fp;
    char inp[5000];
    fp = fopen("read_write_test.txt", "w");
    //fprintf(fp, "This is testing for fprintf...\n");
    //fputs("This is testing for fputs...\n", fp);
    gets(inp);
    fputs( inp,fp);
    fclose(fp);
}

