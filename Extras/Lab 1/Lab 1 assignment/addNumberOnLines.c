#include <stdio.h>
int MAXSIZE = 100;
int stack[100];
int top = -1;

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}

int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek() {
   return stack[top];
}

int pop() {
   int data;

   if(!isempty()) {
      data = stack[top];
      top = top - 1;
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

int push(int data) {

   if(!isfull()) {
      top = top + 1;
      stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}

int printNumber(int num, FILE *p)
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

    fputc(':',p);
    fputc(' ',p);
}

int main()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("addNumberOnLines.c", "r");
    p2 = fopen("addNumberOnLines.txt", "w");
    int lineNumber = 0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {
        printNumber(++lineNumber,p2);
        while((c=fgetc(p1))!=EOF)
        {
            fputc(c,p2);
            if(c=='\n'){
                printNumber(++lineNumber,p2);
            }
        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("addNumberOnLines.txt", "r");
    while((c=fgetc(p2)) != EOF)
        printf("%c", c);
    fclose(p2);


    return 0;
}
