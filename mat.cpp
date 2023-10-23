/**
 * TP de matrices en c++,
 * ASD1
 * TP5
 *
 * fait par Emile BONDU, 1/12/2022
 */

#include <stdexcept>
#include <iostream>

struct Matrice
/*
 * Representation en memoire d'une matrice
 *
 * Les coefs sont inversés par rapport aux coordonées habituelles
 */
{
	int nbLignes;
	int nbCollones;
	double** tab;
};

Matrice init_mat_zeros(int n, int m);
//initialisation d'une matrice de n lignes et de m collones
//utilise l'allocation dynamique 
//		-> a desallouer apres utilisation
Matrice identite(int n);

void desalloue_mat(Matrice& m);
void affecte_coeff(Matrice& m, int i, int j, double val);

std::ostream& operator<<(std::ostream& os, Matrice m);

Matrice somme(Matrice a, Matrice b);
Matrice multiplication(Matrice a, Matrice b);

int main()
{
	Matrice m1 = init_mat_zeros(4, 3), i3 = identite(3), m2 = identite(3), resultat, prod1, prod2;
	
	affecte_coeff(m1, 1,2, 3.0);
	
	affecte_coeff(m2, 1,2, 3.0);
	affecte_coeff(m2, 2,1, -2.0);
	
	resultat = somme(i3, m2);
	prod1 = multiplication(i3, m2);
	prod2 = multiplication(m1, m2);
	
	std::cout << m1 << std::endl;
	std::cout << i3 << std::endl;
	std::cout << m2 << std::endl;
	
	std::cout << resultat << std::endl;
	std::cout << prod1 << std::endl;
	std::cout << prod2 << std::endl;
	
	desalloue_mat(m1);
	desalloue_mat(i3);
	desalloue_mat(m2);
	desalloue_mat(resultat);
	desalloue_mat(prod1);
	desalloue_mat(prod2);

	return 0;
}

Matrice init_mat_zeros(int n, int m)
{
	Matrice mat = {n, m, nullptr};
	
	mat.tab = new double*[n];
	if(mat.tab == nullptr)
	{
		throw std::runtime_error("erreur d'allocation");
	}
	
	for(int i = 0; i < n; i++)
	{
		mat.tab[i] = new double[m];
		if(mat.tab[i] == nullptr)
		{
			throw std::runtime_error("erreur d'allocation");
		}
		
		for(int j = 0; j < m; j++)
		{
			mat.tab[i][j] = 0;
		}
	}
	
	return mat;
}

Matrice identite(int n)
{
	Matrice mat = init_mat_zeros(n, n);
	
	for(int i = 0; i < n; i++)
	{
		mat.tab[i][i] = 1;
	}
	
	return mat;
}

void desalloue_mat(Matrice& mat)
{
	for(int i = 0; i < mat.nbCollones; i++)
	{
		delete[] mat.tab[i];
	}
	
	delete[] mat.tab;
	
	mat.tab = nullptr;
}

void affecte_coeff(Matrice& mat, int i, int j, double val)
{
	if( i < 0 || i >= mat.nbCollones || j < 0 || j >= mat.nbLignes)
	{
		throw std::runtime_error("Coordonees invalides");
	}

	mat.tab[i][j] = val;
}

std::ostream& operator<<(std::ostream& os, Matrice mat)
{
	for(int i = 0; i < mat.nbLignes; i++)
	{
		for(int j = 0; j < mat.nbCollones; j++)
		{
			os << mat.tab[i][j] << " ";
		}
		os << std::endl;
	}
	
	return os;
}

Matrice somme(Matrice a, Matrice b)
{
	if(a.nbLignes != b.nbLignes || a.nbCollones != b.nbCollones)
	{
		throw std::runtime_error("Addition impossible : matrices de tailles differentes");
	}

	Matrice resultat = init_mat_zeros(a.nbLignes, a.nbCollones);
	
	for(int i = 0; i < a.nbLignes; i++)
	{
		for(int j = 0; j < a.nbCollones; j++)
		{
			resultat.tab[i][j] = a.tab[i][j] + b.tab[i][j];
		}
	}
	
	return resultat;
}

Matrice multiplication(Matrice a, Matrice b)
{
	if(b.nbLignes != a.nbCollones)
	{
		throw std::runtime_error("Multiplication matricielle impossible : matrices de tailles incompatibles");
	}

	Matrice resultat = init_mat_zeros(a.nbLignes, b.nbCollones);
	double coef;
	
	for(int i = 0; i < b.nbLignes; i++)
	{
		for(int j = 0; j < a.nbCollones; j++)
		{
			coef = 0;
			for(int k = 0; k < b.nbCollones ; k++)
			{
				coef += a.tab[i][k] * b.tab[k][j];
			}
			
			resultat.tab[i][j] = coef;
		}
	}
	
	return resultat;
}
