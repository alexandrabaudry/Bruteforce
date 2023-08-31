#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<limits.h>
#include <sys/time.h> // for gettimeofday
//--------------------------------------------------- Déclaration variable ------------------------------------------
#define ERR_MALLOC 1
//#define N 4 
int mc = INT_MAX;
int N;
int *v=NULL;
int **c=NULL;
//int **tremplin=NULL;
int *t=NULL;
void saisie(int *v,int **c);
void INIT(int *t);
void tsp (int k );
//------------------------------------------------------Fonction Saisie-------------------------------------------------
void saisie(int *v,int **c){
 
int i,j,x;
/*demande de saisies des valeurs*/
printf("Remplissage de la matrice \n ");
 
for(i=0;i<N;i++){
              v[i]=i;
             // printf("v[%d]= %d ",i,v[i]);
             // }
              //printf("\n");
              }
for(i=0;i<N;i++){
         for(j=0;j<N;j++) {

		c[i][j]=rand()%9 +1 ;
		//c[j][ii]=c[ii][j];
		c[i][i]=0;

		//c[ii][ii]=rand()%(9);
		     
		//printf("c1[%d][%d]= %d ",ii,j,c[ii][j]);
              }
             // printf("\n");
              }
for(i=0;i<N;i++){
         for(j=0;j<N;j++) {
		if((i!=j)||(c[i][j]!=c[j][i])){
			c[j][i]=c[i][j];
					}
			//printf("c2[%d][%d]= %d ",i,j,c[i][j]);
              }
	}

}
//------------------------------------------------------Fonction INIT-------------------------------------------------
void INIT(int *t){
 
int i;
/*demande de saisies des valeurs*/
//printf("Initialisation de T a 0 \n ");
 
for(i=0;i<N;i++){
              t[i]=0;
             // printf("t[%d]= %d ",i,t[i]);
             // }

              }
printf("\n");

}
//-------------------------------------------------- Fonction TSP---------------------------------------------------------
void tsp (int k )
{
int i,temp,s;

 if(k==1)
 {
  s=0;
  for(i=1;i<=N-2;i++)
  	s=s+c[v[i]][v[i+1]];
  	
  		s=s+c[v[N-1]][v[1]];

  	
  
  if(s<mc){
  	mc=s;
  	
  	for(i=1;i<=N-1;i++)
  		t[i]=v[i];
  	
  	
  }
 }
 else
 {
  tsp(k-1);
   for(i=1;i<k;i++){
    temp=v[i];
    v[i]=v[k];
    v[k]=temp;
    tsp(k-1);
    temp=v[i];
    v[i]=v[k];
    v[k]=temp;
    
    
   }
 }
}
//----------------------------------------------------Fonction MAIN -------------------------------------------------------
int main(int argc, char *argv[])
{
int i,j;
 /*if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }*/
    
    //int num_executions = 5; // Nombre d'exécutions à effectuer
    int num_executions = atoi(argv[1]);
    int size = atoi(argv[1]);
    double total_execution_time = 0.0; // Stockage du temps total d'exécution
    int *execution_times = malloc(num_executions * sizeof(int));
    if (execution_times == NULL) {
        exit(EXIT_FAILURE);
    }
    
    FILE *output_file = fopen("execution_times.txt", "a");
    if (output_file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    
    printf("le problème va tourner sur %d execution\n ", num_executions);
    for (int k = 0; k < num_executions; k++) {
        // Déclaration et initialisation de output_file
        FILE *output_file = fopen("execution_times.txt", "a");

//INIT(execution_times);
//---------------------------------- timing begin----------------------
        struct timeval start, end;

    
    // Start time
        gettimeofday(&start, NULL);// Enregistre le temps au début de l'exécution
    //--------------------------------- taille matrice ----------------------
	/*demande de la taille*/
        printf("Saisir la taille des matrice v et c -> ");
        scanf("%d",&N);
 
//---------------------------------------/*malloc ...*/----------------------------
	v=malloc(((N)*sizeof(int )));
	c=malloc(((N)*sizeof(int *)));
	t=malloc(((N)*sizeof(int )));
	for(i=0;i<N;i++){
	    v[i]=0; 
	    c[i]=malloc((N)*sizeof(int ));
	    t[i]=0;
	    }
	/*on vérifie que le malloc a fonctionné*/
	if(v==NULL||*c==NULL||t==NULL) {
	   fprintf(stderr,"Usage: malloc de matrice non fait");
	   exit(ERR_MALLOC);
	   }  


	//------------------- fonction saisie-------------------------------------------------------
	saisie(v,c);
	INIT(t);
	tsp(N-1);
	printf(" le coût du circuit minimum est %d \n",mc);
	for(i=0;i<N;i++)
		printf("%3d",t[i]);
	printf("%3d",t[0]);
	printf("\n");
	system("pause");
	 // Fin du timing
        gettimeofday(&end, NULL);
        double execution_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 10000000.0;
        total_execution_time += execution_time; // Ajouter le temps d'exécution à la somme totale
        // Enregistrement du temps dans execution_times et dans le fichier
        execution_times[k] = execution_time;
        fprintf(output_file, "%.6f\n", execution_time);
        
        // Fermeture du fichier
        fclose(output_file);
        printf("Temps d'exécution total : %.6f secondes\n", total_execution_time);
	    
           
          

}
output_file = fopen("execution_times.txt", "a");
if (output_file == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    return 1;
}

free(execution_times);
return 0;

}
