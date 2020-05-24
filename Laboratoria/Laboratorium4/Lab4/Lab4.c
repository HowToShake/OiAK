#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>

//Links to articles -- "https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C" and "https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Extended-Asm" and "https://en.wikibooks.org/wiki/X86_Assembly/SSE" and "http://students.mimuw.edu.pl/~zbyszek/asm/pl/instrukcje-sse.html"
//Debbugging useful commands --> ggdb i r xmm0 | i r sse | disass | x/f memory | x/sizeOfVectorf memory

//2048 <--> (x0+x1+x2+x3)*512; 4096 <--> 4 * 1024; 8192 <-->  4* 2048


#define sizeOfVector 2048 // sizes -> 512 v 1024 v 2048
#define repeats 10
#define floatValueToRand 10.0f

//time
#define nanoseconds  CLOCKS_PER_SEC * 1000000000.0;
#define microseconds  CLOCKS_PER_SEC * 1000000.0;
#define miliseconds CLOCKS_PER_SEC * 1000.0;


//variables to count avarage.
float divisor =  repeats * sizeOfVector;

clock_t start,end;
double addTime, subTime, mulTime, divTime = 0;
double avgAdd, avgSub, avgMul, avgDiv = 0;



struct vector{
    float x0,x1,x2,x3;
};

struct vector vectorA[sizeOfVector];
struct vector vectorB[sizeOfVector];


void initializeNumbersToTest(float number){
    for(int i=0; i<sizeOfVector; i++){
        vectorA[i].x0 = number;
        vectorA[i].x1 = number;
        vectorA[i].x2 = number;
        vectorA[i].x3 = number;
        vectorB[i].x0 = number;
        vectorB[i].x1 = number;
        vectorB[i].x2 = number;
        vectorB[i].x3 = number;
    }

}


void initializeRandomNumbers(){
    for(int i=0; i<sizeOfVector; i++){
        vectorA[i].x0 = (float)(rand()%1000000)/floatValueToRand;
        vectorA[i].x1 = (float)(rand()%1000000)/floatValueToRand;
        vectorA[i].x2 = (float)(rand()%1000000)/floatValueToRand;
        vectorA[i].x3 = (float)(rand()%1000000)/floatValueToRand;
        vectorB[i].x0 = (float)(rand()%1000000)/floatValueToRand;
        vectorB[i].x1 = (float)(rand()%1000000)/floatValueToRand;
        vectorB[i].x2 = (float)(rand()%1000000)/floatValueToRand;
        vectorB[i].x3 = (float)(rand()%1000000)/floatValueToRand;
    }
}


struct vector sumResultSIMD[sizeOfVector];
struct vector subResultSIMD[sizeOfVector];
struct vector mulResultSIMD[sizeOfVector];
struct vector divResultSIMD[sizeOfVector];


void addSIMD(struct vector firstVector, struct vector secondVector,struct  vector* resultVector){
    __asm__(
        "movaps %1, %%xmm0;"                      //move first argument into xmm0 register
        "movaps %2, %%xmm1;"                   
        "addps %%xmm1, %%xmm0;"                  // add and store vecots in xmm0
        "movaps %%xmm0, %0;"
        : "=m" (*resultVector)                  //output --> letter - m for memory; "=" --> write-only mode
        : "m" (firstVector),"m" (secondVector) //first input --> firstVector, second input --> secondVector
    );
};


void subSIMD(struct vector firstVector, struct vector secondVector,struct  vector* resultVector){
     __asm__(
        "movaps %1, %%xmm0;"                      
        "movaps %2, %%xmm1;"                   
        "subps %%xmm1, %%xmm0;"                  
        "movaps %%xmm0, %0;"
        : "=m" (*resultVector)                  
        : "m" (firstVector),"m" (secondVector) 
    );
}


void mulSIMD(struct vector firstVector, struct vector secondVector,struct  vector* resultVector){
     __asm__(
        "movaps %1, %%xmm0;"                      
        "movaps %2, %%xmm1;"                   
        "mulps %%xmm1, %%xmm0;"                  
        "movaps %%xmm0, %0;"
        : "=m" (*resultVector)                  
        : "m" (firstVector),"m" (secondVector) 
    );
}


void divSIMD(struct vector firstVector, struct vector secondVector,struct  vector* resultVector){
     __asm__(
        "movaps %1, %%xmm0;"                      
        "movaps %2, %%xmm1;"                   
        "divps %%xmm1, %%xmm0;"                  
        "movaps %%xmm0, %0;"
        : "=m" (*resultVector)                  
        : "m" (firstVector),"m" (secondVector) 
    );
}


void testAllSIMD(){

    for(int i=0; i<repeats; i++){


        for(int j=0; j<sizeOfVector; j++){
            start = clock();
            addSIMD(vectorA[i], vectorB[i], &sumResultSIMD[i]);
            end = clock();
            addTime += ((double) (end-start)) / microseconds ;
        }


        for(int j=0; j<sizeOfVector; j++){
            start = clock();
            subSIMD(vectorA[i], vectorB[i], &subResultSIMD[i]);
            end = clock();
            subTime += ((double) (end-start)) / microseconds;
        }


        for(int j=0; j<sizeOfVector; j++){
            start = clock();
            mulSIMD(vectorA[i], vectorB[i], &mulResultSIMD[i]);
            end = clock();
            mulTime += ((double) (end-start)) / microseconds;
        }

        for(int j=0; j<sizeOfVector; j++){
            start = clock();
            divSIMD(vectorA[i], vectorB[i], &divResultSIMD[i]);
            end = clock();
            divTime += ((double) (end-start)) / microseconds;
        }



    }

    avgAdd = addTime/divisor;
    printf("+ ");
    printf("%f\n", avgAdd);

    avgSub = subTime/divisor;
    printf("- ");
    printf("%f\n", avgSub);

    avgMul = mulTime/divisor;
    printf("* ");
    printf("%f\n", avgMul);

    avgDiv = divTime/divisor;
    printf("/ ");
    printf("%f\n", avgDiv);
}


struct vector sumResultSISD[sizeOfVector];
struct vector subResultSISD[sizeOfVector];
struct vector mulResultSISD[sizeOfVector];
struct vector divResultSISD[sizeOfVector];


void addSISD(struct vector firstVector, struct vector secondVector,struct  vector* resultVector ){
    __asm__(
        // adding x0
        "fld %4;"
        "fadd %8;"
        "fstp %0;"

        // adding x1
        "fld %5;"
        "fadd %9;"
        "fstp %1;"

        //adding x2
        "fld %6;"
        "fadd %10;"
        "fstp %2;"

        //adding x3
        "fld %7;"
        "fadd %11;"
        "fstp %3;"

        : 
          "=m"((*resultVector).x0),
          "=m"((*resultVector).x1),
          "=m"((*resultVector).x2),
          "=m"((*resultVector).x3)

        : "m"(firstVector.x0),
          "m"(firstVector.x1),
          "m"(firstVector.x2),
          "m"(firstVector.x3),
          "m"(secondVector.x0),
          "m"(secondVector.x1),
          "m"(secondVector.x2),
          "m"(secondVector.x3)

    );
}


void subSISD(struct vector firstVector, struct vector secondVector,struct  vector* resultVector ){
    __asm__(
        // adding x0
        "fld %4;"
        "fsub %8;"
        "fstp %0;"

        // adding x1
        "fld %5;"
        "fsub %9;"
        "fstp %1;"

        //adding x2
        "fld %6;"
        "fsub %10;"
        "fstp %2;"

        //adding x3
        "fld %7;"
        "fsub %11;"
        "fstp %3;"

        : "=m"((*resultVector).x0),
          "=m"((*resultVector).x1),
          "=m"((*resultVector).x2),
          "=m"((*resultVector).x3)

        : "m"(firstVector.x0),
          "m"(firstVector.x1),
          "m"(firstVector.x2),
          "m"(firstVector.x3),
          "m"(secondVector.x0),
          "m"(secondVector.x1),
          "m"(secondVector.x2),
          "m"(secondVector.x3)

    );
}


void mulSISD(struct vector firstVector, struct vector secondVector,struct  vector* resultVector ){
    __asm__(
        // adding x0
        "fld %4;"
        "fmul %8;"
        "fstp %0;"

        // adding x1
        "fld %5;"
        "fmul %9;"
        "fstp %1;"

        //adding x2
        "fld %6;"
        "fmul %10;"
        "fstp %2;"

        //adding x3
        "fld %7;"
        "fmul %11;"
        "fstp %3;"

        : "=m"((*resultVector).x0),
          "=m"((*resultVector).x1),
          "=m"((*resultVector).x2),
          "=m"((*resultVector).x3)

        : "m"(firstVector.x0),
          "m"(firstVector.x1),
          "m"(firstVector.x2),
          "m"(firstVector.x3),
          "m"(secondVector.x0),
          "m"(secondVector.x1),
          "m"(secondVector.x2),
          "m"(secondVector.x3)

    );
}


void divSISD(struct vector firstVector, struct vector secondVector,struct  vector* resultVector ){
    __asm__(
        // adding x0
        "fld %4;"
        "fdiv %8;"
        "fstp %0;"

        // adding x1
        "fld %5;"
        "fdiv %9;"
        "fstp %1;"

        //adding x2
        "fld %6;"
        "fdiv %10;"
        "fstp %2;"

        //adding x3
        "fld %7;"
        "fdiv %11;"
        "fstp %3;"

        : "=m"((*resultVector).x0),
          "=m"((*resultVector).x1),
          "=m"((*resultVector).x2),
          "=m"((*resultVector).x3)

        : "m"(firstVector.x0),
          "m"(firstVector.x1),
          "m"(firstVector.x2),
          "m"(firstVector.x3),
          "m"(secondVector.x0),
          "m"(secondVector.x1),
          "m"(secondVector.x2),
          "m"(secondVector.x3)

    );
}


void testAllSISD(){

    for(int i=0; i<repeats; i++){


        for(int j=0; j<sizeOfVector; j++){
            start = clock();
            addSIMD(vectorA[i], vectorB[i], &sumResultSISD[i]);
            end = clock();
            addTime += ((double) (end-start)) / microseconds;
        }


        for(int j=0; j<sizeOfVector; j++){
            start = clock();
            subSIMD(vectorA[i], vectorB[i], &subResultSISD[i]);
            end = clock();
            subTime += ((double) (end-start)) / microseconds;
        }



        for(int j=0; j<sizeOfVector; j++){
            start = clock();
            mulSIMD(vectorA[i], vectorB[i], &mulResultSISD[i]);
            end = clock();
            mulTime += ((double) (end-start)) / microseconds;
        }


        for(int j=0; j<sizeOfVector; j++){
            start = clock();
            divSIMD(vectorA[i], vectorB[i], &divResultSISD[i]);
            end = clock();
            divTime += ((double) (end-start)) / microseconds;
        }


    }

    avgAdd = addTime/divisor;
    printf("+ ");
    printf("%f\n", avgAdd);

    avgSub = subTime/divisor;
    printf("- ");
    printf("%f\n", avgSub);

    avgMul = mulTime/divisor;
    printf("* ");
    printf("%f\n", avgMul);

    avgDiv = divTime/divisor;
    printf("/ ");
    printf("%f\n", avgDiv);
}



int main(){

    srand(time(NULL));
    initializeRandomNumbers();
    //initializeNumbersToTest(1.0);

    int input;



    printf("Prosze wybrac opcje: \n");
    printf("1. Test SIMD.\n");
    printf("2. Test SISD.\n");
    scanf("%i", &input);
    printf("\n");


    if(input == 1){

        char type[] = "Typ obliczen: SIMD\n";
        char numbers[] = "Liczba liczb: = ";
        char time[] = "Sredni czas[us]:";

        printf("%s", type);
        printf("%s",numbers);
        printf("%i\n", 4*sizeOfVector);
        printf("%s\n",time);
        
        testAllSIMD();

        FILE* fPtr;

        fPtr = fopen("dataSIMD.txt","w");

        if(fPtr == NULL){
            printf("Nie udalo sie otworzyc pliku. \n");
            exit(EXIT_FAILURE);
        }


        
        fprintf(fPtr, "%s%s%i\n%s\n+ %f\n- %f\n* %f\n/ %f\n",type,numbers,4*sizeOfVector,time, avgAdd, avgSub, avgMul,avgDiv);
        fclose(fPtr);


    }else if(input == 2){
        

        char type[] = "Typ obliczen: SISD\n";
        char numbers[] = "Liczba liczb: = ";
        char time[] = "Sredni czas[us]:";

        printf("%s", type);
        printf("%s",numbers);
        printf("%i\n", 4*sizeOfVector);
        printf("%s\n",time);
        
        testAllSISD();

        FILE* fPtr;

        fPtr = fopen("dataSISD.txt","w");

        if(fPtr == NULL){
            printf("Nie udalo sie otworzyc pliku. \n");
            exit(EXIT_FAILURE);
        }


        
        fprintf(fPtr, "%s%s%i\n%s\n+ %f\n- %f\n* %f\n/ %f\n",type,numbers,4*sizeOfVector,time, avgAdd, avgSub, avgMul,avgDiv);
        fclose(fPtr);
    } 
    
    printf("\nGoodbye!\n");
    
    return 0;
}
