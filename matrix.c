#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <getopt.h>
#include <stdbool.h>
#include <time.h>

void scalar_multi(char filename[], float multiple, int threads, bool log)        
{
//  ATTEMPT TO OPEN THE FILE FOR READ-ONLY ACCESS
    FILE *input = fopen(filename, "r");

//  CHECK TO SEE IF FILE COULD BE OPENED
    if(input == NULL) {
        printf("cannot open '%s'\n", filename);
        exit(EXIT_FAILURE);
    } else {
        printf("%s opened successfully\n", filename);
    }
    char line[64];
    int  rows,cols;
    
    
    fscanf(input, "%s", &line[0]);
    fscanf(input, "%i", &rows);
    fscanf(input, "%i", &cols);

    int totalelements = rows*cols;
    // printf("totalelements=%i", totalelements);
    
    // // fgets(input, "%f", &mat[0]);
    // printf("\n");
    // printf("no of rows: %i",rows);
    // printf("\n");
    // printf("no of cols: %i\n",cols);
    int i = 0;
    int initmatsize = rows*cols*sizeof(float);
    float* initmat = (float*) malloc(initmatsize);
    // printf("first size=%i", sizeof(initmat));
    while( fscanf(input, "%f ", &initmat[i]) != EOF )
    {
        // printf("entry %i: %f\n", i, initmat[i]);
        i++;
    }
    //  INDICATE THAT THE PROCESS WILL NO LONGER ACCESS FILE
    fclose(input);

    printf("showing mat\n");
    printf("size[%i]\n", initmatsize);
    for(int i=0;i<(initmatsize/sizeof(initmat[0]));i++){
        printf("initmat[%i]=[%f]", i, initmat[i]);
    }

    //count how many non zeros
    int nonzcount = 0;
    for(int i=0;i<(initmatsize/sizeof(initmat[0]));i++){
        if(initmat[i] !=0){
            nonzcount++;
        }
    }
    printf("nonzeros: [%i]\n", nonzcount);
    //allocate accordingly
    int* mrows = (int*) malloc(nonzcount * sizeof(int));
    int* mcols = (int*) malloc(nonzcount * sizeof(int));
    float* mvals = (float*) malloc(nonzcount * sizeof(float));
    int mvalssize = nonzcount * sizeof(float);

    int counter = 0;
    for (int i = 0; i<(initmatsize/sizeof(initmat[0]));i++){
        if(initmat[i] != 0){
            printf("counter %i\n", counter);
            int rowcount = i/cols;
            int colcount = i%cols;
            
            // printf("mrows[counter] = rowcount; mrows[%i]=%i\n", counter, rowcount);
            // printf("rowcount %i\n", rowcount);
            // printf("colcount %i\n", colcount);
            // printf("value %f\n", initmat[i]);
            mrows[counter] = rowcount;
            mcols[counter] = colcount;
            mvals[counter] = initmat[i];
            printf("mrow[%i]: mrow %i\n", counter, mrows[counter]);
            printf("mcol %i\n",  mcols[counter]);
            printf("value %f\n",  mvals[counter]);
            counter++;
        }
    }
    //mrows, mcols, mvals are 3 arrays to express matrix in coordinate form
    //FREE INITMAT HERE, ITS JOB IS DONE

    for(int i =0; i<(mvalssize/sizeof(mvals[0]));i++){
        printf("row %i, col %i, val %f", mrows[i], mcols[i], mvals[i]);
    }printf("\n22");
    
    // scalar multiplication
    for(int i =0; i<(mvalssize/sizeof(mvals[0]));i++){
        mvals[i]=mvals[i]*multiple;
    }

    for(int i =0; i<(mvalssize/sizeof(mvals[0]));i++){
        printf("row %i, col %i, val %f", mrows[i], mcols[i], mvals[i]);
    }printf("\n");

    if(log){
        buff[64];
        char* stid = "21146645";
        //  ATTEMPT TO OPEN THE FILE FOR WRITE ACCESS
    //     char* filename;
    //     FILE *input = fopen(filename, "r");
    // //  CHECK TO SEE IF FILE COULD BE OPENED
    //     if(input == NULL) {
    //         printf("cannot open '%s'\n", filename);
    //         exit(EXIT_FAILURE);
    //     } else {
    //     printf("%s opened successfully\n", filename);
    //     }
    
    setlocale(LC_TIME, "el_GR.utf8"); 
    if (strftime(buff, sizeof buff, "%A %c", &my_time)) {
        puts(buff);
    } else {
        puts("strftime failed");
    }
    }
}


int main(int argc, char **argv){

    // read_using_descriptor( argv[1]);
    int opt, f = 0;
    // int thread = 1, perimeter = -1, breadth = -1, length =-1;
    int thread = 1;
    float scalar;
    char *file1;
    char *file2;
    int operation = 0;
    int log = 0;

    //Specifying the expected options
    //The two options l and b expect numbers as argument
    // static struct option long_options[] = {
    //     {"area",      no_argument,       0,  'a' },
    //     {"perimeter", no_argument,       0,  'p' },
    //     {"length",    required_argument, 0,  'l' },
    //     {"breadth",   required_argument, 0,  'b' },
    //     {0,           0,                 0,  0   }
    // };
    static struct option long_options[] = {
        {"sm",      required_argument,       0,  's' },
        {"tr", no_argument,       0,  'c' },
        {"ad",    required_argument, 0,  'a' },
        {"ts",   required_argument, 0,  'p' },
        {"mm", required_argument, 0 , 'm'},
        {0, 0, 0, 0}
    };


    int long_index =0;
    while ((opt = getopt_long(argc, argv,"s:capmf:t:l", 
                   long_options, &long_index )) != -1) {
        switch (opt) {
            case 'f': 
                // strcat(files,optarg);
                f=1;
                file1 = optarg;
                file2 = argv[optind];
                printf("file: %s\n", optarg);
                printf("file2 %s\n", argv[optind]);
                break;
            case 's':
                printf("--sm\n");
                scalar = atof(optarg);
                printf("Scalar multiple: %f\n", scalar);
                operation = 1;
                break;
            case 'c' :
                printf("--tr\n");
                operation = 2;
                break;
            case 'a' : 
                printf("--ad\n");
                operation = 3; 
                break;
            case 'p' : 
                printf("ts\n");
                operation = 4;
                break;
            case 'm' : 
                printf("--mm\n");
                operation = 5;
            //  breadth = atoi(optarg);
                break;
            case 't' : 
            //  breadth = atoi(optarg);
                break;
            case 'l' : 
            log = 1;
            //  breadth = atoi(optarg);
                break;
            default:printf("nothing found"); 
                 exit(EXIT_FAILURE);
        }
    }
    printf("operation is %i", operation);
    switch (operation){
        case 1://sm
            scalar_multi( file1, scalar, thread, log);
            break;
        case 2://tr
            break;
        case 3://ad
            break;
        case 4://ts
            break;
        case 5://mm
            break;
    }




    return 0;
}