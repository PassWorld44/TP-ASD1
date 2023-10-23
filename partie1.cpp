/*
 * ASD1 - TP4
 * BONDU Emile
 * Fait le 17/11/2022
 *
 * listes chainees
 */

#include <iostream>
#include <stdexcept>
#include <string>

typedef struct t_cellule 
{
	char info;
	t_cellule* suivant;
} Cellule;

t_cellule* enregistrement();
/* role : enregistrement d'un message saisi par l'utilisateur.
 * La fin du message est marquée par un point.
 * la fonction retourne l'adresse du début du chainage.
 */

std::ostream& operator<<(std::ostream& os, const t_cellule *pdeb);
//affiche le message commançant à pdeb.

void desallocation(t_cellule *pdeb);

t_cellule* chainage_string(std::string str);

int main() 
{
	t_cellule *message = enregistrement(), *str = chainage_string("");
		
	std::cout << message << str;
	
	desallocation(message);
	desallocation(str);
	
	return 0;
}

t_cellule* enregistrement()
{
	char lettre;
	t_cellule *pcel  = nullptr,
			  *psuiv = nullptr,
			  *tete  = nullptr;
	
	std::cout << "une message ? (un point pour terminer)" << std::endl;
	std::cin >> lettre;
	
	pcel = new t_cellule;
	if(pcel == nullptr) {
		throw std::runtime_error("erreur d'allocation");
	}
	tete = pcel;
	
	while(lettre != '.')
	{
		pcel->info = lettre;
		psuiv = new t_cellule;
		if(pcel == nullptr) {
			throw std::runtime_error("erreur d'allocation");
		}
		pcel->suivant = psuiv;
		
		std::cin.get(lettre);
		
		pcel = psuiv;
	}
	
	pcel->info = lettre;
	pcel->suivant = nullptr;
	
	return tete;
}

std::ostream& operator<<(std::ostream& os, const t_cellule *pdeb)
{
	char lettre;
	t_cellule const *pcel = pdeb;
	
	while(pcel != nullptr)
	{
		lettre = pcel->info;
		os << lettre;
		pcel = pcel->suivant;
	}
	os << std::endl;
	
	return os;
}

void desallocation(t_cellule *pdeb)
{
	if(pdeb != nullptr)
	{
		desallocation(pdeb->suivant);
		delete pdeb;
	}
}

t_cellule* chainage_string(std::string str)
//implementation tres similaire a enregistrement()
{
	char lettre;
	t_cellule *pcel  = nullptr,
			  *psuiv = nullptr,
			  *tete  = nullptr;
	
	pcel = new t_cellule;
	if(pcel == nullptr) {
		throw std::runtime_error("erreur d'allocation");
	}
	tete = pcel;
	
	lettre = str[0];
	
	for(int i = 1; i < str.size() ; i++)
	{
		pcel->info = lettre;
		psuiv = new t_cellule;
		if(pcel == nullptr) {
			throw std::runtime_error("erreur d'allocation");
		}
		pcel->suivant = psuiv;
		
		lettre = str[i];
		
		pcel = psuiv;
	}
	
	pcel->info = lettre;
	pcel->suivant = nullptr;
	
	return tete;
}
