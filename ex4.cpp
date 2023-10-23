/*
jeu de TicTacToe de taille n
-> alloc dynamique
29/09/2022
Emile BONDU
ASD1 - fac de Nantes
*/

#include <iostream>
#include <stdexcept>

enum Symbol {EMPTY, P1, P2};
typedef std::runtime_error ErrInput ;

typedef struct s_game
{
	Symbol** grid;
	int size;
	char p1, p2;
} GameGrid;

Symbol** gridInit(int size);

GameGrid initGame(bool byDefault);
void deleteGame(GameGrid& g);
std::ostream& operator<<(std::ostream& s, GameGrid grid);

void playSymbol(GameGrid g, Symbol s, int posX, int posY);
bool hasWon(GameGrid g, Symbol s);

void playTurn(GameGrid g, Symbol s);
void game();

int main()
{
	game();
	
	return 0;
}

// --------------- FONCTIONS -----------------------

Symbol** gridInit(int size)
//retourne une grille de taille size
//peut lançer des std::runetime_error en cas d'erreur d'allocation
{
	Symbol** grid = new Symbol*[size];
	if(grid == nullptr)
		throw std::runtime_error("Erreur d'allocation");
		
	for(int i = 0; i < size; i++)
	{
		grid[i] = new Symbol[size];
		if(grid[i] == nullptr)
			throw std::runtime_error("Erreur d'allocation");
			
		for(int j = 0; j < size; j++)
		{
			grid[i][j] = EMPTY;
		}
	}
	
	return grid;
}

void deleteGame(GameGrid& g)
//libere l'espace mémoire lié a une grille
{
	for(int i = 0; i < g.size; i++)
	{
		delete[] g.grid[i];
	}
	delete[] g.grid;
	
	g.grid = nullptr;
}

GameGrid initGame(bool byDefault = false)
//initialise le jeu en demandant les symboles et la taille de la grille
//option d'initialisation par defaut
{
	GameGrid g;

	if(!byDefault) {
		std::cout << "Taille du jeu de TicTacToe++ : ";
		std::cin >> g.size;
		
		std::cout << std::endl;
		std::cout << "Symbole de la 1ere joueuse : ";
		std::cin >> g.p1;
		std::cout << "Symbole de la 2e joueuse : ";
		std::cin >> g.p2;
	}
	else {
		g.p1 = 'X';
		g.p2 = 'O';
		g.size = 4;
	}
	
	g.grid = gridInit(g.size);
	
	return g;
}

std::ostream& operator<<(std::ostream& s, GameGrid grid)
//affiche une grille de taille size
//affichage correct jusqu'a un tableau de taille 10
{
	s << "    ";
	for(int i = 0; i < grid.size; i++)
	{
		if(i<10)
			s << i << ' ';
		else
			s << i;
	}
	s << std::endl;
	
	for(int i = 0; i < 4 + 2*grid.size; i++)
		s << '_';
	s << std::endl;
	
	for(int i = 0; i < grid.size; i++)
	{
		s << i << " | ";
		for(int j = 0; j < grid.size; j++)
		{
			switch( grid.grid[i][j] )
			{
			case EMPTY:
				s << ".";
				break;
			case P1:
				s << grid.p1;
				break;
			case P2:
				s << grid.p2;
				break;
			default :
				throw std::runtime_error("Erreur de grille : symbole non reconu");
				break;
			}
			s << ' ';
		}
		s << std::endl;
	}
	
	return s;
}

void playSymbol(GameGrid g, Symbol s, int posX, int posY)
//joue le symbole s dans la case de position (x, y)
//throw une ErrInput si les coordonees communiquees 
//			sont invalides/deja prises
{
	if(posX >= g.size || posY >= g.size)
		throw ErrInput("Coordonees invalides");
	
	if(g.grid[posX][posY] != EMPTY)
		throw ErrInput("Case déja prise");
		
	if(s != P1 && s != P2)
		throw ErrInput("Symbole invalide");
		
	g.grid[posX][posY] = s;
}

bool hasWon(GameGrid g, Symbol s)
{
	bool hasWon;
	
	//Colonnes :
	for(int i = 0; i < g.size; i++)
	{
		hasWon = true;
		for(int j = 0; j < g.size; j++) {
			if(g.grid[i][j] != s)
				hasWon = false;
		}
		if(hasWon)
			return true;
	}
	
	//lignes :
	for(int i = 0; i < g.size; i++)
	{
		hasWon = true;
		for(int j = 0; j < g.size; j++) {
			if(g.grid[j][i] != s)
				hasWon = false;
		}
		if(hasWon)
			return true;
	}
	
	//Diagonales :
	hasWon = true;
	for(int i = 0; i < g.size ; i++)
	{
		if(g.grid[i][i] != s)
			hasWon = false;
	}
	if(hasWon)
		return true;
	
	hasWon = true;
	for(int i = 0; i < g.size ; i++)
	{
		if(g.grid[g.size-1-i][i] != s)
			hasWon = false;
	}
	if(hasWon)
		return true;
		
	return false;
}

void playTurn(GameGrid g, Symbol s)
{
	int posX, posY;
	bool isValid = false;

	while(!isValid)
	{	
		try {
			std::cout << g << std::endl;
	
			std::cout << "Tour du symbole ";
			switch(s)
			{
			case P1:
				std::cout << g.p1;
				break;
			case P2:
				std::cout << g.p2;
				break;
			default:
				throw std::runtime_error("Symbole inconnu");
			}
			std::cout << " :" << std::endl;
			std::cout << "Position en x : ";
			std::cin >> posX;
			std::cout << "Position en y : ";
			std::cin >> posY;
			
			playSymbol(g, s, posX, posY);
			isValid = true;
		}
		catch(ErrInput err)
		{
			std::cout << "Erreur : " << err.what() << std::endl;
		}
	}
}


void game()
{
	GameGrid g = initGame(false);
	bool isFinished = false;

	while(!isFinished)
	{
		playTurn(g, P1);
		if(hasWon(g, P1))
		{
			isFinished = true;
			std::cout << "le symbole " << g.p1 << " a gagne !" << std::endl;
			break;
		}

		playTurn(g, P2);
		if(hasWon(g, P2))
		{
			isFinished = true;
			std::cout << "le symbole " << g.p2 << " a gagne !" << std::endl;
			break;
		}
	}
	
	deleteGame(g);
}
