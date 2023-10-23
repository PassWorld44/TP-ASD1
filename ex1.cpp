/*
gestion de notes automatiques
Ex1 - TP2
ASD2
Emile BONDU
*/

#include <string>
#include <stdexcept>
#include <exception>
#include <iostream>
#include <cstdlib>

enum TestVal { t_BLANK, t_FALSE, t_TRUE, t_INVALID_VALUE };

typedef struct t_testAnswer
/* 
 * made to be use with data
 *
 * some data migt not be initalised;
 */
{
	std::string name;
	int nbQuest;
	TestVal* answers;
	
	bool isNoted;
	int score;
	char note;
} TestAnswer;

typedef struct t_data 
{	
	int nbQuest;
	int nbStud;
	
	TestVal* correction;
	TestAnswer* res;
} DataTest;


TestVal randomVal();
TestVal randomValCorr(TestVal answer);

TestAnswer generateTestRes(std::string name);
void destroyTestAnswer(TestAnswer& a);

DataTest generateData(int nbQuestions, int nbStudents);
void destroyData(DataTest& d);

char evalNote(int note, int nbQuest);
void note(DataTest& d);

std::ostream& operator<<(std::ostream& os, TestVal t);
std::ostream& operator<<(std::ostream& os, TestAnswer t);
std::ostream& operator<<(std::ostream& os, DataTest t);

int main()
{
	srand(time(0));
	DataTest d = generateData(10, 50);
	
	std::cout << "--------- CORRECTION---------------" << std::endl;
	note(d);
	
	std::cout << d << std::endl;
	
	destroyData(d);

	return 0;
}

TestVal randomValCorr()
// 50% of questions aswered by TRUE
{
	switch( rand() % 2 )
	{
	case 0:
		return t_FALSE;
		break;
	case 1:
		return t_TRUE;
		break;
	default: //impossible
		return t_INVALID_VALUE;
		break;
	}
}

TestVal randomVal(TestVal answer)
{	
	if( rand() % 10 > 4) { //sinon les resultats sont trop catastrophiques
		return answer;
	}
	else if( rand() % 10 < 9) 
	//90% of the cases - 90% of questions answered
	{
		return randomValCorr();
	}
	else
	{
		return t_BLANK;// Agrandir le tableau de si son occupation et supérieure à
	}
}

TestAnswer generateTestRes(std::string n, int nbQuest, TestVal *correction)
{
	TestAnswer t;
	t.name = n;
	t.isNoted = false;
	t.nbQuest = nbQuest;
	t.answers = new TestVal[nbQuest];
	if(t.answers == nullptr)
		throw std::runtime_error("Allocation Failed");
	
	for(int i = 0; i < nbQuest; i++)
	{
		t.answers[i] = randomVal(correction[i]);
	}
	
	return t;
}

DataTest generateData(int nbQuest, int nbStud)
{	
	DataTest d;
	d.nbQuest = nbQuest;
	d.nbStud = nbStud;
	
	d.correction = new TestVal[nbQuest];
	if(d.correction == nullptr)
		throw std::runtime_error("Allocation failed");
		
	for(int i = 0; i < d.nbQuest; i++)
	{
		d.correction[i] = randomValCorr();
	}
	
	d.res = new TestAnswer[nbStud];
	if(d.res == nullptr)
		throw std::runtime_error("Allocation failed");
		
	for(int i = 0; i < d.nbStud; i++)
	{	
		d.res[i] = generateTestRes( "ST"+std::to_string(i), nbQuest,
										d.correction);
	}
	
	return d;
}

void destroyTestAnswer(TestAnswer& a)
{
	delete[] a.answers;
	a.answers = nullptr;
}

void destroyData(DataTest& d)
{
	delete[] d.correction;
	d.correction = nullptr;
	
	for(int i = 0; i < d.nbStud; i++)
	{
		destroyTestAnswer(d.res[i]);
	}
}

char evalNote(int note, int nbQuest)
//precondition  : nbQuest !=0 , 0 <= note <= nbQuest
{
	float res = (float)note / nbQuest;
	if(res > 1) {
		throw std::runtime_error("note invalide");
	}
	else if(res >= 0.9) {
		return 'A';
	}
	else if(res >= 0.8) {
		return 'B';
	}
	else if(res >= 0.7) {
		return 'C';
	}
	else if(res >= 0.6) {
		return 'D';
	}
	else if(res >= 0.5) {
		return 'E';
	}
	else {
		return 'F';
	}
}

void note(DataTest& d)
{
	for(int i = 0; i < d.nbStud; i++)
	{
		d.res[i].score = 0;
		for(int j = 0; j < d.nbQuest; j++)
		{
			if(d.res[i].answers[j] != t_BLANK)
			{
				if(d.res[i].answers[j] == d.correction[j])
				{	
					d.res[i].score++;
				}
				else
				{
					d.res[i].score--;
				}
			}
		}
		if(d.nbQuest != 0) {
			d.res[i].note = evalNote(d.res[i].score, d.nbQuest);
			d.res[i].isNoted = true;
		}
	}
}

std::ostream& operator<<(std::ostream& os, TestVal t)
{
	switch(t)
	{
	case(t_BLANK):
		os << ' ';
		break;
	case(t_FALSE):
		os << 'F';
		break;
	case(t_TRUE):
		os << 'T';
		break;
	case(t_INVALID_VALUE):
		throw std::runtime_error("Invalid value");
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, TestAnswer t)
{
	os << t.name << " ";
	for(int i = 0; i < t.nbQuest; i++)
	{
		os << t.answers[i];
	}
	if(t.isNoted) {
		os << ", note : " << t.note << ", score : " << t.score << "/" << t.nbQuest;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, DataTest t)
{
	os << "Bonnes reponses : ";
	for(int i = 0; i < t.nbQuest ; i++)
	{
		os << t.correction[i];
	}
	os << std::endl << std::endl;
	
	for(int i = 0; i < t.nbStud ; i++)
	{
		os << t.res[i] << std::endl;
	}
	return os;
}
