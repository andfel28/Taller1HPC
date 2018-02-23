#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main ()
{

    int filas;
    int columnas;

    int i;
    int c;
    int k;

    float **A;
    float **B;
    float **producto;
    float suma;
    char *cadenaM1;
    char *cadenaM2;
    char *cadenaProducto;
    char *cadenaFile;

    FILE *FP;

    // Generamos una semilla para que el random genere siempre valores diferentes:
    srand(time(NULL));

    // Leemos el tamaño de los matrizes:
    printf ( "Filas:" );
    scanf ( "%d", &filas);

    printf ( "Columnas:" );
    scanf ( "%d", &columnas);


    // Reservamos memoria para los matrizes:

    A = (float **)malloc(filas*sizeof(float*));
	for (i=0;i<filas;i++)
		A[i] = (float*)malloc(columnas*sizeof(float));

    B = (float **)malloc(columnas*sizeof(float*));
	for (i=0;i<columnas;i++)
		B[i] = (float*)malloc(filas*sizeof(float));

    producto = (float **)malloc(filas*sizeof(float*));
	for (i=0;i<filas;i++)
		producto[i] = (float*)malloc(filas*sizeof(float));

    //Cadenas de texto a almacenar e el file.csv
    cadenaM1       = ( char * ) malloc ( 9000 * sizeof ( char ) );
    cadenaM2       = ( char * ) malloc ( 9000 * sizeof ( char ) );
    cadenaProducto = ( char * ) malloc ( 9000 * sizeof ( char ) );
    cadenaFile     = ( char * ) malloc ( 9000 * sizeof ( char ) );

    if ( A==NULL||B==NULL||producto==NULL||cadenaM1==NULL||cadenaM2==NULL||cadenaProducto==NULL||cadenaFile==NULL)
    {      perror ( "Problemas reservando memoria" ); exit ( 1 ); }

    strcpy( cadenaM1, "M1:\n" );
    strcpy( cadenaM2, "M2:\n" );
    strcpy( cadenaProducto, "Producto:\n" );

    //Iniciliza las matriz A
    for(i=0;i<filas;i++)
    {
       for(c=0;c<columnas;c++)
       {
          A[i][c]  = rand()%1000;
          sprintf(cadenaFile,"%f",A[i][c]);
          strcat( cadenaM1, cadenaFile );
          strcat( cadenaM1, ", " );
       }
       strcat( cadenaM1, "\n" );
    }

    //Iniciliza las matriz B
    for(i=0;i<columnas;i++)
    {
       for(c=0;c<filas;c++)
       {
           B[i][c]  = rand()%1000;
           sprintf(cadenaFile,"%f",B[i][c]);
           strcat( cadenaM2, cadenaFile );
           strcat( cadenaM2, ", " );
       }
       strcat( cadenaM2, "\n" );
    }

   //                        ---------------------------------
    // Procedimiento para realizar el producto de matrices A x B

       for(i=0;i<filas;i++)
       {
           for(c=0;c<filas;c++)
           {
               suma = 0.0;

               for(k=0;k < columnas;k++)
                    suma= A[i][k]*B[k][c] + suma;

               producto[i][c]=suma;

               sprintf(cadenaFile,"%f",producto[i][c]);
               strcat( cadenaProducto, cadenaFile );
               strcat( cadenaProducto, ", " );
          }

           strcat( cadenaProducto, "\n" );
       }

    strcpy( cadenaFile,"");
    strcat( cadenaFile, cadenaM1 );
    strcat( cadenaFile, "\n" );
    strcat( cadenaFile, cadenaM2 );
    strcat( cadenaFile, "\n" );
    strcat( cadenaFile, cadenaProducto );

    free ( A );
    free ( B );
    free ( producto );
    free ( cadenaM1 );
    free ( cadenaM2 );
    free ( cadenaProducto );

    //Almacenamos la informacion en un archivo
    FP = fopen("d:/gcc/matrices.txt","w");
    if (FP==NULL){printf("Ocurrio un error"); free ( cadenaFile ); exit (1);}
    fputs(cadenaFile,FP);
    fclose(FP);

    free ( cadenaFile );

}
