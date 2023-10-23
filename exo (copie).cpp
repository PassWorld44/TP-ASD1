/*
 * TP3 - ASD1
 * Tableau Dynamiques - implementation
 *
 * Emile Bondu
 * 25/10/2022, L2 Maths Info - CMI OPTIM
*/

#include <iostream>
#include <string>
#include <stdexcept>
 
typedef struct t_RarityClass
{
	std::string name;
	double sellFactor;
} RarityClass;
 
typedef struct t_Artifact
{
	std::string name;
	int magicPower, price, quantity;
	double weight;
	RarityClass* rarity;
} Artifact;
 
typedef struct t_ExtandableBag
{
	Artifact* tab;
	int capa, occu;
} ExtandableBag;
 
ExtandableBag initBag();
//throws an std::runtime_error if there is an allocation failure
 
void increaseBagCapacity(ExtandableBag* b);
//double the bag capacity if it's occupation reached 2/3 of its capacity
//throws an std::runtime_error if there is an allocation failure
 
void decreaseBagCapacity(ExtandableBag* b);
//halfs the bag capacity if it's occupation is less than 1/6 of its capacity
//throws an std::runtime_error if there is an allocation failure
//keep the bag size above 4
 
std::ostream& operator<<(std::ostream& os, Artifact a);
std::ostream& operator<<(std::ostream& os, ExtandableBag b);

int findInsertIndex(ExtandableBag* b, Artifact a);
void addArtifact(ExtandableBag* b, Artifact a);
//add an Articaft into the bag
//keep the bag ordored by magicPower

int max(int a, int b);

int main()
{
	ExtandableBag b = initBag();
	
	std::cout << b;
}
 
ExtandableBag initBag()
{
 	ExtandableBag b = {nullptr, 0, 0};
 	
 	b.tab = new Artifact[4];
 	if(b.tab != nullptr)
 	{
 		b.capa = 4;
 	}
 	else {
 		throw std::runtime_error("allocation failed");
 	}
 	
 	return b;
}
 
void increaseBagCapacity(ExtandableBag* b)
{
  	if(b->occu >= 2.0/3.0 * b->capa) 
  	{
  		Artifact* newTab = nullptr;
  		int newSize = b->capa * 2;
  		
  		newTab = new Artifact[newSize];
  		if(newTab == nullptr) {
  			throw std::runtime_error("allocation failed");
  		}
  		
  		for(int i = 0; i < b->capa; i++)
  		//recopy of the old data in the bag
  		{
  			newTab[i] = b->tab[i];
  		}
  		delete[] b->tab;
  		b->tab = newTab;
  		
  		b->capa = newSize;
  	}
}
  
void decreaseBagCapacity(ExtandableBag* b)
{
  	if(b->occu <= 1.0/6.0 * b->capa && b-> capa > 4) 
  	{
  		Artifact* newTab = nullptr;
  		int newSize = max(b->capa / 2, 4);
  		
  		newTab = new Artifact[newSize];
  		if(newTab == nullptr) {
  			throw std::runtime_error("allocation failed");
  		}
  		
  		for(int i = 0; i < newSize; i++)
  		//recopy of the old data in the bag
  		{
  			newTab[i] = b->tab[i];
  		}
  		delete[] b->tab;
  		b->tab = newTab;
  		
  		b->capa = newSize;
  	}
}
  
std::ostream& operator<<(std::ostream& os, Artifact a)
{
	os << a.name << ", " << a.magicPower << " magie, " << a.weight << " kg, type ";
	os << a.rarity->name << ", " << a.price << " rupee/piece, " << a.quantity << " piece";

	return os;
}

std::ostream& operator<<(std::ostream& os, ExtandableBag b)
{
	for(int i = 0; i < b.occu; i++)
	{
		os << "position " << i+1 << " : " << b.tab[i] << " ;" << std::endl;
	}
	
	if(b.occu < b.capa)
	{
		os << "position " << b.occu+1 << "-" << b.capa << " : empty" << std::endl;
	}
	
	return os;
}

int findInsertIndex(ExtandableBag* b, Artifact a)
{
	//dicotomic research
	int indL = 0, indR = b->occu, mid;
	
	while( b->tab[indL].magicPower == a.magicPower || indR - indL <= 0)
	{
		mid = ( indL + indR )/2;
		
		if( b->tab[mid].pagicPower <= a.magicPower ) {
			indL = mid;
		}
		else {
			indR = mid;
		}
	} 
}

void addArtifact(ExtandableBag* b, Artifact a)
{
	int indInsert = findInsertIndex(b, a);
	
	//there is some room to insert in this dynamic table since we
	//	increase it to keep space : we have at least 1/3 of free space
	//	and this is always true since the minimum capacity is 4
	
	for(int i = b->occu; i > indInsert; i--)
	{
		//b->occu is outside the usual capacity :
		b->tab[i] = b->tab[i-1];
	}
	b->tab[indInsert] = a;
	
	increaseBagCapacity(b);
	//and we don't forget to make space for the next time
}

int max(int a, int b)
{
	if( a < b )
		return b;
	return a;
}
