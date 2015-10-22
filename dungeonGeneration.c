#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int const n=5; 
int const m=5;
int const nb_sommets = (n*m) + 1;  

 
int main(int argc, char const *argv[])
{
	srand (time(NULL));


	int tab[n][m]; //on init tout le tab à 0

	/*
	 * rouge = 3  	(pièce difficile)
	 * bleu = 2 	(pièce moyenne)
	 * vert = 1		(pièce facile)
	 */
	//on place les piece hard de maniere random mais sans quelle soit cote à cote
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
	      //on verifie que on est pas out of bound et que autour ya pas de rouge
	      	if( (i-1)>0 && (i+1)<n && (j-1)>0 && (j+1)<n ){
				if(tab[i-1][j]!= 3 && tab[i][j-1] != 3){ //comme on le remplit dans l'ordre le test de verif pour les rouge se font que pour les i-1 et j-1
		  			if ((rand() % 4 +1) == 1) { //generation de la proba, on considere une proba de 25% 
		    			tab[i][j]=3; // 25% of the time you get 1	
		    		}
		    	}
		    }
		}
	}

	//pour chaque rouhe un voisin bleu et un voisin vert
	for(int i=0; i<n; ++i)
	  for(int j=0; j<m; ++j)
	      if(tab[i][j]!= 3) //si la case est rouge on colore un des voisin en bleu et un en vert
			tab[i][j]=rand()%2+1;
	      
	
	//On a besoin d'un graphe 
	int graphe[nb_sommets][nb_sommets];
	for (int i = 0; i < nb_sommets; ++i)
		for (int j = 0; j < nb_sommets; ++j)
			graphe[i][j]=0;

	for (int j = 0; j < m; ++j)
	{
		for (int i = 0; i < n; ++i)
		{
			//pour chaque salle on peut accéder à celle à droite ou en dessous (et inversement)

			//Pour en dessous
			if(j+1 < m){
				graphe[j*n+i][j*n+i+n]=tab[j][i];
				graphe[j*n+i+n][j*n+i]=tab[j][i];
			}

			//pour à droite
			if(i+1 < n){
				graphe[j*n+i][j*n+i+1]=tab[j][i];
				graphe[j*n+i+1][j*n+i]=tab[j][i];
			}

			if (i+1 == n && j+1 == m)
			{
				// printf("Dernière pièce\n");
				graphe[nb_sommets-2][nb_sommets-1]=tab[j][i];
				graphe[nb_sommets-1][nb_sommets-2]=tab[j][i];
			}
		}
	}
	// Affichage de la carte 
	for (int i = 0; i < n; ++i)
	  {
	  	for (int j = 0; j < m; ++j)
	  	{
	  		printf("%d ", *(*(tab+i)+j));
	  	}
	  	printf("\n");
	  }
	//Affichage de la matrice d'adjacence
	for (int i = 0; i < nb_sommets; ++i)
	  {
	  	printf("[ ");
	  	for (int j = 0; j < nb_sommets; ++j)
	  	{
	  		printf("%d ", *(*(graphe+i)+j));
	  	}
	  	printf("] \n");
	  }

	//on part de en haut a gauche pour aller en bas à droite
	//creation du chemin de base => utilisation d'un algo de path style thorup


	      
	//pour chaque node du chemin ajouter ses voisins

	//creer salle détail plus tard
	      
	      
	//creer toute les portes entre les sales
	      
	//supprimer de maniere aléatoire ses portes (15% de chance de del un porte(ptet moins)) avec mini une porte par salle sauf pour les portes du chemin qui doivent avoir deux portes minimum)
	    

	return 0;
}
