#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main ()
{

    int numeroElementos;
    int i;
    float *vector;
    float *vector2;
    float *suma;

    char *cadenaV1;
    char *cadenaV2;
    char *cadenaSuma;
    char *cadenaFile;

    FILE *FP;

    // Generamos una semilla para que el random genere siempre valores diferentes:
    srand(time(NULL));

    // Leemos el tamaño de los vectores:
    printf ( "¿Tamaño del vector? " );
    scanf ( "%d", &numeroElementos );

    // Reservamos memoria para los vectores:
    vector  = ( float * ) malloc ( numeroElementos * sizeof ( float ) );
    vector2 = ( float * ) malloc ( numeroElementos * sizeof ( float ) );
    suma =    ( float * ) malloc ( numeroElementos * sizeof ( float ) );

    //Cadenas de texto a almacenar e el file.csv
    cadenaV1   = ( char * ) malloc ( 3000 * sizeof ( char ) );
    cadenaV2   = ( char * ) malloc ( 3000 * sizeof ( char ) );
    cadenaSuma = ( char * ) malloc ( 3000 * sizeof ( char ) );
    cadenaFile = ( char * ) malloc ( 3000 * sizeof ( char ) );


    if ( vector==NULL||vector2==NULL||suma==NULL||cadenaV1==NULL||cadenaV2==NULL||cadenaSuma==NULL||cadenaFile==NULL)
    {      perror ( "Problemas reservando memoria" ); exit ( 1 ); }

    cadenaV1   = strcpy( cadenaV1, "V1: " );
    cadenaV2   = strcpy( cadenaV2, "V2: " );
    cadenaSuma = strcpy( cadenaSuma, "Suma: " );

    #pragma omp parallel shared(vector,vector2,suma,numeroElementos) private(i) num_threads(8)
    {
        #pragma omp for schedule(dynamic,10)
        for(i=0;i<numeroElementos;i++)
        {
            vector[i]  = rand()%1000;
            vector2[i] = rand()%1000;
            suma[i]    = vector2[i] + vector[i];
        }
    }


    for(i=0;i<numeroElementos;i++)
    {
            sprintf(cadenaFile,"%f",vector[i]);
            strcat( cadenaV1, cadenaFile );
            strcat( cadenaV1, "," );

            sprintf(cadenaFile,"%f",vector2[i]);
            strcat( cadenaV2, cadenaFile );
            strcat( cadenaV2, "," );

            sprintf(cadenaFile,"%f",suma[i]);
            strcat( cadenaSuma, cadenaFile );
            strcat( cadenaSuma, "," );
    }

    strcpy( cadenaFile,"");
    strcat( cadenaFile, cadenaV1 );
    strcat( cadenaFile, "\n" );
    strcat( cadenaFile, cadenaV2 );
    strcat( cadenaFile, "\n" );
    strcat( cadenaFile, cadenaSuma );

    free ( vector );
    free ( vector2 );
    free ( suma );
    free ( cadenaV1 );
    free ( cadenaV2 );
    free ( cadenaSuma );

    FP = fopen("d:/gcc/vectores.txt","w");
    if (FP==NULL){printf("Ocurrio un error"); free ( cadenaFile ); exit (1);}
    fputs(cadenaFile,FP);
    fclose(FP);

    free ( cadenaFile );
}
