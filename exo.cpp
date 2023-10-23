/*
 * TP3 - ASD1
 * Tableau Dynamiques - implementation
 *
 * Emile Bondu - Mohamed Larbi TOUATI
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
 
typedef struct t_ExtendableBag
{
	Artifact* tab;
	int capa, occu;
} ExtendableBag;
 
ExtendableBag initBag();
//throws an std::runtime_error if there is an allocation failure
 
void increaseBagCapacity(ExtendableBag* b);
//double the bag capacity if it's occupation reached 2/3 of its capacity
//throws an std::runtime_error if there is an allocation failure
 
void decreaseBagCapacity(ExtendableBag* b);
//halfs the bag capacity if it's occupation is less than 1/6 of its capacity
//throws an std::runtime_error if there is an allocation failure
//keep the bag size above 4
 
std::ostream& operator<<(std::ostream& os, Artifact a);
std::ostream& operator<<(std::ostream& os, ExtendableBag b);

int findInsertIndex(ExtendableBag* b, Artifact a, int start, int end);
int findIndex(ExtendableBag* b, std::string artName);
//returning -1 if the artefact isn't in the bag 

void addArtifact(ExtendableBag* b, Artifact a);
//add an Articaft into the bag
//keep the bag ordored by magicPower

void removeArtifact(ExtendableBag* b, int ind);
//remove an Articaft from the bag 

void deleteArtifact(ExtendableBag* b, std::string artName);
//remove an Articaft from the bag or decrease it's quantity

int max(int a, int b); 
int min(int a, int b);

int sellValue(const Artifact art);

int totalSellValue(const ExtendableBag b);

Artifact maxMagicPower(const ExtendableBag b);
//throws an std::runtime_error if the bag is empty
int main()
{
	ExtendableBag b = initBag();
	RarityClass r1 = {"non spécifié", 0.5}, 
				r2 = {"standard",     1.0}, 
				r3 = {"rare", 		  2.5}; 
	Artifact a1 = {"Orbe magique", 40, 12, 1, 2.0, &r1},
			 a2 = {"Arc chasseur", 25, 83, 1, 2.0, &r3},
			 a3 = {"Flèche",       1,  5, 15, 0.1, &r2};
			 
	std::cout << b;
	
	addArtifact(&b, a2);
	
	std::cout << b; 
		
	addArtifact(&b, a3);
	
	std::cout << b;
	
	addArtifact(&b, a3);
	
	std::cout << b;
	
	addArtifact(&b, a1);
	
	std::cout << b;
	
	deleteArtifact(&b,"Flèche");
	
	std::cout << b;
	
	deleteArtifact(&b,"Arc chasseur");
	
	std::cout << b;
	 
	deleteArtifact(&b,"Orbe magique");
	
	std::cout << b;
}
 
ExtendableBag initBag()
{
 	ExtendableBag b = {nullptr, 0, 0};
 	
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
 
void increaseBagCapacity(ExtendableBag* b)
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
  
void decreaseBagCapacity(ExtendableBag* b)
{
  	if(b->occu <= 1.0/6.0 * b->capa && b-> capa > 4) 
  	{
  		Artifact* newTab = nullptr;
  		int newSize = max(b->capa / 2, 4);
  		
  		newTab = new Artifact[newSize];
  		if(newTab == nullptr) {
  			throw std::runtime_error("allocation failed");
  		}
  		int findDeleteIndex(ExtendableBag* b, std::string artName);
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

std::ostream& operator<<(std::ostream& os, ExtendableBag b)
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


int findInsertIndex(ExtendableBag* b, Artifact a, int start, int end){
	int mid =(start + end)/2 ;
	
	if(end-start == 0){
		return start ;
	}else if(b->tab[mid].magicPower < a.magicPower)
	{
		return findInsertIndex(b, a, start, mid) ;
	}
	else{
		return findInsertIndex(b, a , mid+1, end);
	}
}
	

void addArtifact(ExtendableBag* b, Artifact a)
{
	int indPos = findIndex(b, a.name);
	if(indPos == -1)
	{
		int indInsert = findInsertIndex(b, a,0,b->occu);
		
		//there is some room to insert in this dynamic table since we
		//	increase it to keep space : we have at least 1/3 of free space
		//	and this is always true since the minimum capacity is 4
		findIndex(b, a.name);
		for(int i = b->occu; i > indInsert; i--)
		{
			//b->occu is outside the usual capacity :
			b->tab[i] = b->tab[i-1];
		}
		b->tab[indInsert] = a;
		b->occu++;
		
		increaseBagCapacity(b);
		//and we don't forget to make space for the next time
	}
	else
	{
		b->tab[indPos].quantity += a.quantity;
	}
}

int findIndex(ExtendableBag* b, std::string artName)
{
	for(int i= 0;i< b->occu;i++)
	{
		if(b->tab[i].name == artName){
			return i;
		}
	}
	return -1;
}
void removeArtifact(ExtendableBag* b, int ind){
	for(int i=ind; i < b->occu + 1 ;i++){
		b->tab[i] = b->tab[i+1];
	}
	b->occu--;
	decreaseBagCapacity(b);

}

void deleteArtifact(ExtendableBag* b, std::string artName)
{
	int indPos = findIndex(b, artName );
	if(indPos == -1)
	{
		throw std::runtime_error("Impossible de supprimer un element inexistant");
	}
	else if(b->tab[indPos].quantity == 1)
	{
		 removeArtifact(b, indPos);
	}
	else
	{
		b->tab[indPos].quantity--;
	}
}

int sellValue(const Artifact art)
{
	return int( art.price * art.rarity->sellFactor * art.quantity );
	//rounding down the value
}

int totalSellValue(const ExtendableBag b)
{
	int total=0;
	for(int i = 0;i< b.occu;i++)
	{
		total += sellValue(b.tab[i]);
	}
	return total;

}

int max(int a, int b)
{
	if( a < b )
		return b;
	return a;
}

int min(int a, int b)
{
	if( a > b )
		return b;
	return a;
}

Artifact maxMagicPower(const ExtendableBag b)
{
	if(b.occu ==0)
	{
		throw std::runtime_error("L'inventaire est vide");
	}
	return b.tab[0];
}

