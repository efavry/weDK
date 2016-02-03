#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iostream>
#include <limits.h>
#include <algorithm>



using namespace std;

int const m = 4;
int const n = 4;
int const nbSommets = 	(n*m) + 1;



struct node{
	node* parent;	// Parent du noeud
	int idParent;
	int h; 					// H (distance de l'arrivée)
	int g;					// G (distance du départ)
};
node const defaultNode = {NULL, 0, 1, -1};


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
	      
	
	//On a besoin d'une matrice d'adj 
	int matrice[nbSommets][nbSommets];
	for (int i = 0; i < nbSommets; ++i)
		for (int j = 0; j < nbSommets; ++j)
			matrice[i][j]=0;

	for (int j = 0; j < n; ++j)
	{
		for (int i = 0; i < m; ++i)
		{
			//pour chaque salle on peut accéder à celle à droite ou en dessous (et inversement)

			//Pour en dessous
			if(j+1 < n){
				matrice[j*m+i][j*m+i+m]=tab[j][i];
				matrice[j*m+i+m][j*m+i]=tab[j][i];
			}

			//pour à droite
			if(i+1 < m){
				matrice[j*m+i][j*m+i+1]=tab[j][i];
				matrice[j*m+i+1][j*m+i]=tab[j][i];
			}

			if (i+1 == m && j+1 == n)
			{
				// printf("Dernière pièce\n");
				matrice[nbSommets-2][nbSommets-1]=tab[j][i];
				matrice[nbSommets-1][nbSommets-2]=tab[j][i];
			}
		}
	}

	//Chemin le plus court
	vector<node> nodes(nbSommets, defaultNode);
	nodes[0].g = 0;
	nodes[nbSommets-1].h = 0;
	vector<int> open, closed;
	node* current;
	int index_min, x;
	open.push_back(0);
	while(true){
		index_min = 0;
		for (int i = 0; i < open.size(); ++i)
		{
			//cout << open[i] << ": " << nodes[open[i]].g << "\t";
			//On parcours les nodes dans open pour trouver celui qui a la plus petite valeur
			current = &nodes[open[i]];
			if (((*current).h+(*current).g) < (nodes[open[index_min]].h+nodes[open[index_min]].g))
				index_min = i; //Si on trouve une valeur plus petite on la prend
		}

		current = &nodes[open[index_min]]; //on selectionne le node que l'on va traiter
		x = open[index_min];
		closed.push_back(x);//on le met dans la liste des nodes parcourus
		open.erase(open.begin()+index_min);//on l'enleve de la liste des nodes à parcourir

		if ((*current).h == nodes[nbSommets-1].h){
			// on est à la fin
			cout << "trouvé !!!" << endl;
			break;
		}else{
			for (int i = 0; i < nbSommets; ++i)
			{
				//On va parcourir ses voisins
				if (matrice[i][x] !=0)
				{
					//on trouve un lien vers une autre case (on s'assure qu'il n'est pas dans closed et si il n'est pas dans open ou si le chemin est plus court par ce noeud)
					if (find(closed.begin(), closed.end(), i)==closed.end() && (find(open.begin(), open.end(), i)==open.end() || ((*current).h+(*current).g+matrice[i][x])< (nodes[i].h+nodes[i].g) ))
					{
						nodes[i].g = (*current).g+matrice[i][x];
						nodes[i].parent = current;
						nodes[i].idParent = x;
						// cout << i << " g=" << nodes[i].g << "( "<<(*current).g+matrice[x][i]<<") & idParent=" << nodes[i].idParent <<endl;

						if (find(open.begin(), open.end(), i)==open.end())
						{
							open.push_back(i);
						}
					}
				}
			}
		}
	}

	// On affiche le chemin :
	cout << "Noeuds parcourus (fin vers le début): " << endl;
	current = &nodes[nbSommets-1];
	while((*current).g != 0){
		cout << (*current).idParent <<endl;
		current = (*current).parent;
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


	return 0;
}
