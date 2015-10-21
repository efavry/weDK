#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int const n=9; 
int const m=9;

int main(int argc, char const *argv[])
{
	srand (time(NULL));


	int tab[n][m]; //on init tout le tab a 0

	/*
	 * rouge = 2
	 * bleu = 1
	 * vert = 0
	 */
	//on place les piece hard de maniere random mais sans quelle soit cote à cote
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
	      //on verifie que on est pas out of bound et que autour ya pas de rouge
	      	if( (i-1)>0 && (i+1)<n && (j-1)>0 && (j+1)<n ){
				if(tab[i-1][j]!= 2 && tab[i][j-1] != 2){ //comme on le remplit dans l'ordre le test de verif pour les rouge se font que pour les i-1 et j-1
		  			if ((rand() % 4 +1) == 1) { //generation de la proba, on considere une proba de 25% 
		    			tab[i][j]=2; // 25% of the time you get 1	
		    		}
		    	}
		    }
		}
	}

	//pour chaque rouhe un voisin bleu et un voisin vert
	for(int i=0; i<n; ++i)
	  for(int j=0; j<m; ++j)
	      if(tab[i][j]!= 2) //si la case est rouge on colore un des voisin en bleu et un en vert
			tab[i][j]=rand() % 2;
	      
	      
	      
	//on part de en haut a gauche pour aller en bas à droite
	//creation du chemin de base => utilisation d'un algo de path style thorup


	      
	//pour chaque node du chemin ajouter ses voisins

	//creer salle détail plus tard
	      
	      
	//creer toute les porte entre les sales
	      
	//supprimer de maniere aléatoire ses portes (15% de chance de del un porte(ptet moins)) avec mini une porte par salle sauf pour les porte du chemin qui doivent avoir deux porte minimum)
	    
	//Affichage de la carte 
	for (int i = 0; i < n; ++i)
	  {
	  	for (int j = 0; j < m; ++j)
	  	{
	  		printf("%d", *(*(tab+i)+j));
	  	}
	  	printf("\n");
	  }  

	return 0;
}
