#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <random>
#include <math.h>  
#include <algorithm>
#include <iterator> 
#include <cstdlib>
#include <ctime>
#include <iostream>


using namespace std;

// LAB 5 PAA - THIAGO EMANUEL SILVA ANTUNES LOPES
// CAIXEIRO VIAJANTE COM PROGRAMACAO DINAMICA 
#define MAX 9999
        
int caminhomin(int no, int mask, int n, int** grafo,int maskvisitados, int** memo)
{	
	if(mask==maskvisitados)
    {
		return grafo[no][0];
	}
    if(memo[mask][no]!=-1)
    {
	   return memo[mask][no];
	}
	int customin = MAX;

	for(int i=0; i<n; i++)
    {
		if((mask&(1<<i))==0)
        {
			int c1 = grafo[no][i] + caminhomin(i, mask|(1<<i),n,grafo,maskvisitados,memo);
			customin = min(c1, customin);
		}
	}
	return memo[mask][no]=customin;
} 

//------------------------------------------------------------------------//
// FUNCAO TEMPO //
long double getNow()
{
   struct timeval now;
   long double valor = 1000000;

   gettimeofday(&now,NULL);

   return ((long double)(now.tv_sec*valor)+(long double)(now.tv_usec));
}

void temp()
{
    long double t=0, ti, tf;
    int n = 4;
    
    while(t<60)
    {
        int maskvisitados = (1<<n) -1;
        int **grafo = (int**)malloc(n * sizeof(int*));
        int **memo = (int**)malloc((1<<n) * sizeof(int*));
        
        for(int i=0; i<n; i++) 
        {
            grafo[i] = (int*) malloc(n * sizeof(int));
            for(int j = 0; j < n; j++) 
            {
                if(i==j)
                    grafo[i][j]=0;
                else if(i>j)
                    grafo[i][j]=grafo[j][i];
                else
                    grafo[i][j]=rand()%1000+1;
            }
        }
        for(int i=0; i<(1<<n); i++) 
        {
            memo[i] = (int*) malloc(n * sizeof(int));
            for(int j = 0; j < n; j++) 
            {
                memo[i][j]=-1;
            }
        }
        /*
        for (int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
	            cout<<grafo[i][j];
                cout<<" ";
            }
            cout<<"\n";
        }
        */
        ti = getNow();
        
        caminhomin(0,1,n,grafo,maskvisitados,memo);
      
        tf = getNow();
        t=(tf-ti)/1000000;
	    printf("\n(%d, %Lf)\n", n, t);
        

        for (int i=0; i < n;i++)
        {    
            free(grafo[i]);
        }
        free(grafo);
        
        for (int i=0; i < (1<<n);i++)
        {    
            free(memo[i]);
        }
        free(memo);
        n++;
    }
}

int main()
{
    srand(time(NULL));
	temp();
	return 0;
}
