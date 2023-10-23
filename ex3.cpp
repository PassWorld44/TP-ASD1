#include <iostream>
#include <stdexcept>

int main()
{
	int taille;
	int *tab, *tabCarre;
	
	std::cout << "Taille du tableau : ";
	std::cin >> taille;
	//le std::cin c'est pas une source sécurisée mais on va oublier
	
	tab = new int[taille];
	if(tab == nullptr)
		throw std::runtime_error("espace non alloue pour tab");
	
		
	for(int i = 0; i < taille; i++)
	{
		std::cin >> tab[i];
	}
	
	tabCarre = new int[taille];
	if(tabCarre == nullptr)
		throw std::runtime_error("espace non alloue pour tabCarre");
	
	for(int i = 0; i < taille ; i++)
	{
		tabCarre[i] = tab[i] * tab[i];	
	}
	
	delete[] tab;
	
	for(int i = 0; i < taille ; i++)
	{
		std::cout << tabCarre[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
