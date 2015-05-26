#include<stdio.h>
#include<stdlib.h>
#define FILENAME "testfile"
int line=1;
int startPos=0;
int nowPos=0;
//0 1 2 3 4 
int state=0;
void rollback(){

}
void lexerCh(int ch){

}
void printIF(){
    printf("IF\t(%d,%d)",line,startPos);
    startPos=nowPos;
    state=0;
}
void printID(){
    char *s = "test";
    printf("ID(%s)\t(%d,%d)",s,line,startPos);
    startPos=nowPos;
    state=0;
}
void printINT(){
     
    char *s="test";
    printf("INT(%s)\t(%d,%d)",s,line,startPos);
    startPos=nowPos;
    state=0;
}

void lexer(int ch){
    switch(state){
        case 0:
            if (ch == 'i'){
                state=1;
            }
            else if (ch>='0' && ch <= '9'){
                state=2;
            }
            else if ((ch>='a'&&ch<='Z')||ch=='_'){
                state=3;
            }
            break;
        case 1:
            if (ch == 'f'){
                state=4;
            }
            else if (ch == ' ' || ch == '\n'){
                printID();
            }
            else{
                state=3;
            }
            break;
        case 2:
            if(ch == ' ' || ch == '\n'){
                printINT();
            }
            break;
        case 3:
            if(ch == ' ' || ch =='\n'){
                printID();
            }
            break;
        case 4:
            if (ch == ' ' || ch == '\n'){
                printIF();
            }
            else{
                state=3;
            }
            break;
        default:break;

    }
    nowPos++;

}
void main(int argc,char *argv[]) //命令行参数
{
    int ch;
    FILE *fp;
    char *filename=FILENAME;
    if(argc==2)
    {
       filename=argv[1]; 
    }
    
    if((fp=fopen(filename,"r"))==NULL)
    {
        printf("The file <%s> can not be opened.\n",argv[1]);
        return;
    }
    int state;
    nowPos=startPos=ftell(fp);
    ch=fgetc(fp); 
    while(ch!=EOF) 
    {
        lexer(ch);
        putchar(ch);
        ch=fgetc(fp);
    } 
    lexer(' ');
    fclose(fp); 
}
