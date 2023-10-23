/*
 * ASD1 - TP4
 * BONDU Emile
 * Fait le 17/11/2022
 *
 * listes chainees
 */

#include <iostream>
#include <stdexcept>

enum JourSemaine { LUNDI = 1, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI, DIMANCHE};

typedef struct t_seance
{
	int numeroSemaine;
	JourSemaine jour;
	int heure; //de 8 à 18
	int minutes; //0 ou 30
	t_seance* seanceSuivante;	

} Seance;

int nbrSeancesPrevues(const t_seance* deb);
//retourne le nombre de seances prevues dans le chainage

t_seance* trouverQueue(t_seance* ptr);
//retourne nullptr si ptr est nullptr
//temps constant si ptr est déja la queue de la chaine

int compare(t_seance *ptr, int numSem, JourSemaine jour, int h, int min);
/*
 * retourne 0 si les seances sont égales, 
 * 1 si ptr est plus grande que celles passée via les multiples paramètres, 
 * -1 sinon
 */
int compare(t_seance *p1, t_seance *p2);
//same comparaison as above

t_seance* trouverPrecedentSeanceNonTrie(t_seance *liste, int numSem, JourSemaine jour, int h, int min);
//retourne le precedent de la 1ere occurence de la seance passée en paramètre
//nullptr si l'element n'est pas trouvé
//retourne le pointeur passé en paramètres si la tête 
//		de la liste est l'élement recherché

std::ostream& operator<<(std::ostream& os, const t_seance* deb);
std::ostream& operator<<(std::ostream& os, const JourSemaine);

void desalloueSeances(t_seance* ptr);

void ajouteSeanceNonTrie(t_seance*& ptr, int numSem, JourSemaine jour, int h, int min);
bool supprimerSeanceNonTrie(t_seance *& ptr, int numSem, JourSemaine jour, int h, int min);
//supprime la 1ere occurence de la seance passée en paramètres
//revoie true si elle a été supprimée, false si elle n'était pas dans la liste.

int nombreSeanceFuturesNonTrie(t_seance *ptr, int numSem, JourSemaine jour, int h, int min);
//retourne le nombre de seances qui suivent

int main()
{
	t_seance* l1 = nullptr;
	
	ajouteSeanceNonTrie(l1, 38, LUNDI, 18, 0);
	ajouteSeanceNonTrie(l1, 40, MARDI, 14, 0);
	ajouteSeanceNonTrie(l1, 39, JEUDI, 8, 0);
	ajouteSeanceNonTrie(l1, 38, VENDREDI, 9, 30);

	std::cout << l1 << std::endl;
	std::cout << nombreSeanceFuturesNonTrie(l1, 38, VENDREDI, 9, 30) << std::endl;
	
	supprimerSeanceNonTrie(l1, 39, JEUDI, 8, 0);
	
	std::cout << l1 << std::endl;


	return 0;
}

int nbrSeancesPrevues(t_seance* deb)
{
	int nbr = 0;
	t_seance *sc = deb;
	
	while(sc != nullptr)
	{
		nbr++;
		sc = sc->seanceSuivante;
	}
	
	return nbr;
}

std::ostream& operator<<(std::ostream& os, const t_seance* deb)
{
	if(deb == nullptr)
	{
		throw std::runtime_error("chaine de seances vide");
	}
	os << "Semaine " << deb->numeroSemaine << " " << deb->jour << " ";
	os << deb->heure << "h" << deb->minutes << std::endl;
	
	if(deb->seanceSuivante!= nullptr) {
		os << deb->seanceSuivante;
	}
	
	return os;
}

std::ostream& operator<<(std::ostream& os, const JourSemaine j)
{
	switch(j)
	{
	case LUNDI:
		os << "lundi";
		break;
	case MARDI:
		os << "mardi";
		break;
	case MERCREDI:
		os << "mercredi";
		break;
	case JEUDI:
		os << "jeudi";
		break;
	case VENDREDI:
		os << "vendredi";
		break;
	case SAMEDI:
		os << "samedi";
		break;
	case DIMANCHE:
		os << "dimanche";
		break;
	}
	
	return os;
}

void desalloueSeances(t_seance* ptr)
{
	if(ptr != nullptr)
	{
		desalloueSeances(ptr->seanceSuivante);
		delete ptr;
	}
}

t_seance* trouverQueue(t_seance* ptr)
{
	if(ptr == nullptr)
	{
		return ptr;
	}
	while(ptr->seanceSuivante!= nullptr)
	{
		ptr = ptr->seanceSuivante;
	}
	
	return ptr;
}

void ajouteSeanceNonTrie(t_seance *& ptr, int numSem, JourSemaine jour, int h, int min)
{
	t_seance *tmp = ptr;
	ptr = new t_seance { numSem, jour, h, min, nullptr };
	
	ptr->seanceSuivante = tmp;
	
	if(ptr == nullptr)
	{
		throw std::runtime_error("Erreur d'allocation");
	}
}

int compare(t_seance *ptr, int numSem, JourSemaine jour, int h, int min)
/*
 * retourne 0 si les seances sont égales, 
 * 1 si ptr est plus grande que celles passée via les multiples paramètres, 
 * -1 sinon
 */
{
	if(ptr == nullptr)
	{
		throw std::runtime_error("pointeur nul : comparaison impossible");
	}
	
	if(numSem == ptr->numeroSemaine 
		&& jour == ptr->jour && h == ptr->heure 
		&& ptr->minutes == min)
		//on teste les differents champs
	{
		return 0;
	}
	else if(ptr->numeroSemaine > numSem || 
			(numSem == ptr->numeroSemaine && ptr->jour > jour) ||
			(numSem == ptr->numeroSemaine && jour == ptr->jour && ptr->heure > h) ||
			(numSem == ptr->numeroSemaine && jour == ptr->jour && h == ptr->heure && ptr->minutes > min) )
	//oui, on a besoin d'une comparaison de cette taille
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int compare(t_seance *p1, t_seance *p2)
{
	return compare(p1, p2->numeroSemaine, p2->jour, p2->heure, p2->minutes);
}

t_seance* trouverPrecedentSeanceNonTrie(t_seance *liste, int numSem, JourSemaine jour, int h, int min)
//retourne le precedent de la 1ere occurence de la seance passée en paramètre
//nullptr si l'element n'est pas trouvé
//retourne le pointeur passé en paramètres si la tête 
//		de la liste est l'élement recherché
{
	if(liste != nullptr)
	{
		if( compare(liste, numSem, jour, h, min) )
		// cas limite, a gérer en sortie
		{
			return liste;
		}
		
		while(liste->seanceSuivante!= nullptr)
		{
			if(compare(liste->seanceSuivante, numSem, jour, h, min) == 0)
			{
				return liste;
			}
			//sinon on l'a pas trouvé, on continue de chercher
			
			liste = liste->seanceSuivante;
		}
	}
	//l'element n'est pas la liste 
	return nullptr;
}

bool supprimerSeanceNonTrie(t_seance *& ptr, int numSem, JourSemaine jour, int h, int min)
//supprime la 1ere occurence de la seance passée en paramètres
//revoie true si elle a été supprimée, false si elle n'était pas dans la liste.
{
	t_seance *seance = nullptr, *tmp; 
	
	if(compare(ptr, numSem, jour, h, min) == 0)
	//cas limite de la fonction trouverPrecedentSeance
	{
		seance = ptr->seanceSuivante;
		delete(ptr);
		ptr = seance;
		
		return true;
	}
	
	seance = trouverPrecedentSeanceNonTrie(ptr, numSem, jour, h, min);
	
	if(seance != nullptr)
	//on supprime le suivant de seance
	{
		tmp = seance->seanceSuivante->seanceSuivante;
		delete(seance->seanceSuivante);
		seance->seanceSuivante= tmp;
		
		return true;
	}
	else {
		return false;
	}
}

int nombreSeanceFuturesNonTrie(t_seance *ptr, int numSem, JourSemaine jour, int h, int min)
//retourne le nombre de seances qui suivent
{
	int nb = 0;
	
	while(ptr != nullptr)
	{
		if(compare(ptr, numSem, jour, h, min) == 1)
		{
			nb++;
		}
		ptr = ptr->seanceSuivante;
	}
	
	return nb;
}
