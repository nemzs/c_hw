#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define ll long long



typedef struct Array{
    char* arr;
    int used,sz;
} Array;

typedef struct people
{
    int id;
    Array name,number;
} people;
people* peoples;
int peopleSize=0;
char buff[255];
int id=1;
int needError=1;
Array pureBuffer;

void initArray(Array *a,int initialSize){
    a->arr = (char*)malloc(initialSize * sizeof(char));
    a->used=0;
    a->sz=initialSize;
}

void pushArray(Array *a, char element){
    if(a->sz==a->used){
        a->sz*=2;
        a->arr = (char*)realloc(a->arr,a->sz*sizeof(char));
        for(int i=a->used;i<a->sz;i++){
            a->arr[i]=0;
        }
    }
    a->arr[a->used++]=element;
}

void freeArray(Array *a){
    free(a->arr);
    a->arr=NULL;
    a->used=a->sz=0;
}

void cpyArray(Array* a, Array* b){
    for(int i=0;i<b->used;i++){
        pushArray(a,b->arr[i]);
    }
}

int cmpStrings(char*a,char * b,int size_a,int size_b,int registryForce){
    if(size_a!=size_b) return(-1);
    for(int i=0;i<size_a;i++){
        if(registryForce){
            if(a[i]!=b[i]){
                return(-1);
            }
        }
         else
        if(tolower(a[i])!=tolower(b[i])){
            return(-1);
        }
    }
    return(0);
}
int strstrStrings(char*a,char * b,int size_a,int size_b){
    int l=0;
    for(int i=0;i<size_a;i++){
        if(l<size_b)
        if(tolower(a[i])==tolower(b[l])){
            l++;
        }
    }
    if(size_b==l)
        return(0);
    else return(-1);
}



int add(Array* name, Array* number)
{
    peopleSize++;
    people* buf= (people*) realloc (peoples, peopleSize * sizeof(people));
    people newPeople;
    newPeople.id=id;
    id++;
    buf[peopleSize-1]=newPeople;
    peoples=buf;
    initArray(&peoples[peopleSize-1].name,1);
    initArray(&peoples[peopleSize-1].number,1);
    for(int i=0;i<name->used;i++){
        pushArray(&peoples[peopleSize-1].name,name->arr[i]);
    }
    for(int i=0;i<number->used;i++){
        pushArray(&peoples[peopleSize-1].number,number->arr[i]);
    }
    return(id-1);
}

void kill_str(char* a)
{
    for(int i=0; i<strlen(a); i++)
    {
        a[i]=0;
    }
}

void del(long id)
{
    for(int i=0; i<peopleSize; i++)
    {
        if(peoples[i].id==id)
        {
            peoples[i].id=-1;
            kill_str(peoples[i].name.arr);
            kill_str(peoples[i].number.arr);
        }
    }
}

void printPeople(people out)
{
    printf("%d ",out.id);
            fflush(stdout);
    for(int j=0; j<out.name.used; j++)
    {
        printf("%c",out.name.arr[j]);
            fflush(stdout);
    }
    printf(" ");
            fflush(stdout);
    for(int j=0; j<out.number.used; j++)
    {
        printf("%c",out.number.arr[j]);
            fflush(stdout);
    }
    printf("\n");
            fflush(stdout);

}

void itoa_C(int a){
    char b[255];
    for(int i=0;i<255;i++) b[i]=buff[i]=0;
    int l=0,r=0;
    while(a>0){
        char c=(a%10)+'0';
        a/=10;
        b[l++]=c;
    }
    for(int i=l-1;i>=0;i--){
        buff[r++]=b[i];
    }
}

void changeNumber(Array* id,Array* number)
{
    for(int i=0; i<peopleSize; i++)
    {
        itoa_C(peoples[i].id);//loads to buff
        if(!cmpStrings(buff,id->arr,strlen(buff),id->used,0))
        {
            kill_str(peoples[i].number.arr);
            initArray(&peoples[i].number,1);
            cpyArray(&peoples[i].number,number);
        }
    }
}

void changeName(Array* id,Array* name)
{
    for(int i=0; i<peopleSize; i++)
    {
        itoa_C(peoples[i].id);
        if(!cmpStrings(buff,id->arr,strlen(buff),id->used,0))
        {
            kill_str(peoples[i].name.arr);
            initArray(&peoples[i].name,1);
            cpyArray(&peoples[i].name,name);
        }
    }
}

int isNumber(Array* number)
{
    if(number->used==0)
    {
        return(0);
    }
    for(int i=0; i<number->used; i++)
    {
        if(number->arr[i]>='0'&&number->arr[i]<='9')
            continue;
        if(number->arr[i]!='-'&&number->arr[i]!='+'&&number->arr[i]!='('&&number->arr[i]!=')')
        {
            return(0);
        }
    }
    return(1);
}

int isName(Array* name)
{
    if(name->used==0)
    {
        return(0);
    }
    for(int i=0; i<name->used; i++)
    {
        if(!(name->arr[i]>='a'&&name->arr[i]<='z'||name->arr[i]>='A'&&name->arr[i]<='Z'))
        {
            return(0);
        }
    }
    return(1);
}

void PANIC(){
    if(needError){
        needError=0;
        printf("PANIC!!!\n");
        fflush(stdout);
    }
}

void prints(char* out,int sz)
{
    for(int i=0; i<sz; i++)
    {
        printf("%c",out[i]);
            fflush(stdout);
    }
}

int pureNumber(Array* number)
{
    Array pure;
    initArray(&pure,1);
    long l=0;
    freeArray(&pureBuffer);
    initArray(&pureBuffer,1);
    for(int i=0; i<number->used; i++)
    {
        if(number->arr[i]>='0'&&number->arr[i]<='9')
        {
            pushArray(&pure,number->arr[i]);
        }
    }
    cpyArray(&pureBuffer,&pure);
    return(number->used-pure.used);
}

void findByName(Array* name)
{
    for(int i=0; i<peopleSize; i++)
    {
        if(!strstrStrings(peoples[i].name.arr,name->arr,peoples[i].name.used,name->used))
        {
            printPeople(peoples[i]);
        }
    }
}
void findByNumber(Array* number)
{
    for(int i=0; i<peopleSize; i++)
    {
        Array firstNumb,secondNumb;
        initArray(&firstNumb,1);
        initArray(&secondNumb,1);
        pureNumber(&peoples[i].number);//returns to pureBuffer
        cpyArray(&firstNumb,&pureBuffer);
        freeArray(&pureBuffer);
        pureNumber(number);
        cpyArray(&secondNumb,&pureBuffer);
        freeArray(&pureBuffer);
        if(!cmpStrings(firstNumb.arr,secondNumb.arr,firstNumb.used,secondNumb.used,0))
        {
            printPeople(peoples[i]);
        }
        freeArray(&firstNumb);
        freeArray(&secondNumb);
    }
}

void debug_peoples()
{
    for(int i=0; i<peopleSize; i++)
    {
        printf("%d ",peoples[i].id);
            fflush(stdout);
        for(int j=0; j<peoples[i].name.sz; j++)
        {
            printf("%c",peoples[i].name.arr[j]);
            fflush(stdout);
        }
        printf(" ");
        for(int j=0; j<peoples[i].number.sz; j++)
        {
            printf("%c",peoples[i].number.arr[j]);
            fflush(stdout);
        }
        printf("\n");
            fflush(stdout);
    }
}

int validId(Array* stringId)
{
    if(pureNumber(stringId))
    {
        PANIC();
        return(-1);
    }
    char* pEnd;
    long id = strtol(stringId->arr,&pEnd,10);
    return(id);
}

FILE* readString(Array* s,FILE * ptrFile){
    int c, counter = 0;

    if (ptrFile == NULL){ PANIC();
    }
    else
    {
        do
        {
        c = fgetc(ptrFile);
        //printf("%c",c);
        if(c=='\n') needError=1;
        if(c==' '||c=='\n'&&counter>0){
            break;
        }
        if(c!=' '&&c!='\n'){
            pushArray(s,c);
            counter++;
        }
        } while (c != EOF); // пока не конец файла
  }
  return(ptrFile);
}

void goSave(char* name){
    int validNumbers=0;
    for(int i=0; i<peopleSize; i++)
    {
        if(peoples[i].id!=-1)
        {
            validNumbers++;
        }
    }
    FILE * file;
    file = fopen(name,"w");
    fprintf(file,"%d\n",validNumbers);
            fflush(stdout);
    for(int i=0; i<peopleSize; i++)
    {
        if(peoples[i].id!=-1)
        {
            //printf("%d\n",peoples[i].name.used);
            for(int j=0; j<peoples[i].name.used; j++)
            {
                fprintf(file,"%c",peoples[i].name.arr[j]);
            fflush(stdout);
            }
            fprintf(file," ");
            for(int j=0; j<peoples[i].number.used; j++)
            {
                fprintf(file,"%c",peoples[i].number.arr[j]);
            fflush(stdout);
            }
            fprintf(file,"\n");
            fflush(stdout);
        }
    }
    fclose(file);

}



int main (int argc, char* argv[])
{
    //argv[1] = "test.txt";
    peoples=(people*)malloc(0*sizeof(people));
    FILE * file;
    if(file=fopen(argv[1],"r"))
    {
        int buffSize;
        if(fscanf(file,"%d",&buffSize)>0){
            for(int i=0;i<buffSize;i++){
                Array name,number;
                initArray(&name,1);
                initArray(&number,1);
                file =readString(&name,file);
                file = readString(&number,file);
                add(&name,&number);
            }
        }
    fclose(file);
    }
    Array type;
    initArray(&type,1);
    while(cmpStrings(type.arr,"exit",type.used,4,1))
    {
        freeArray(&type);
        initArray(&type,1);
        int flag=0;
        readString(&type,stdin);
        if(!cmpStrings(type.arr,"create",type.used,6,1))
        {
            flag++;
            Array name,number;
            initArray(&name,1);
            initArray(&number,1);
            readString(&name,stdin);
            readString(&number,stdin);
            if(isName(&name)&&isNumber(&number))
                add(&name,&number);
            else PANIC();
        }
        if(!cmpStrings(type.arr,"delete",type.used,6,1))
        {
            flag++;
            Array stringId;
            initArray(&stringId,1);
            readString(&stringId,stdin);
            int id=validId(&stringId);
            if(id!=-1)
                del(id);
        }
        if(!cmpStrings(type.arr,"change",type.used,6,1))
        {
            flag++;
            Array id,type2,changeTo;
            initArray(&id,1);
            initArray(&type2,1);
            initArray(&changeTo,1);
            readString(&id,stdin);
            readString(&type2,stdin);
            readString(&changeTo,stdin);
//            if(purenumber(id)){
            //              printf("Bad request");
            //        }
            if(!cmpStrings(type2.arr,"number",type2.used,6,1))
            {
                if(isNumber(&id)&&isNumber(&changeTo))
                    changeNumber(&id,&changeTo); else
                    PANIC();
            }
            else if(!cmpStrings(type2.arr,"name",type2.used,4,1))
            {
                if(isNumber(&id)&&isName(&changeTo))
                    changeName(&id,&changeTo); else
                    PANIC();
            }
            else
            {
                PANIC();
            }
        }
        if(!cmpStrings(type.arr,"find",type.used,4,1))
        {
            flag++;
            Array part;
            initArray(&part,1);
            readString(&part,stdin);
            if(isNumber(&part))
            {
                findByNumber(&part);
            }
            else if(isName(&part))
            {
                findByName(&part);
            }
            else
                PANIC();
        }
        if(flag==0&&cmpStrings(type.arr,"exit",type.used,4,1))
        {
            PANIC();
        }
        goSave(argv[1]);
    }
    freeArray(&type);
    return(0);
}
