#include <iostream.h>

class Tama
 {
	private:
	int itsAge;
	int itsWeight;
	int itsFame;
	int itsSete;
	int itsBisognini;
	int itsMalato;
	int itsSporco;
	
	public:
	const int GetAge();
	const int GetWeight();
	const int GetFame();
	const int GetSete();
	const int GetBisognini();
	const int GetMalato();
	const int GetSporco();
	void SetAge(int Age);
	void SetWeight(int Weight);
	void SetFame(int Fame);
	void SetSete(int Sete);
	void SetBisognini(int Bisognini);
	void SetMalato(int Malato);
	void SetSporco(int Sporco);
};

const int Tama::GetAge()
{ return itsAge; }

const int Tama::GetFame()
{ return itsFame; }

const int Tama::GetWeight()
{ return itsWeight; }
 
const int Tama::GetSete()
{ return itsSete; }

const int Tama::GetBisognini()
{ return itsBisognini; }

const int Tama::GetMalato()
{ return itsMalato; }

const int Tama::GetSporco()
{ return itsSporco; }

void Tama::SetAge(int Age)
{ itsAge = Age; }

void Tama::SetWeight(int Weight)
{ itsWeight = Weight; }

void Tama::SetBisognini(int Bisognini)
{ itsBisognini = Bisognini; }

void Tama::SetMalato(int Malato)
{ itsMalato = Malato; }

void Tama::SetFame(int Fame)
{ itsFame = Fame; }

void Tama::SetSete(int Sete)
{ itsSete = Sete; }

void Tama::SetSporco(int Sporco)
{ itsSporco = Sporco; }

int main()
{
cout << "Enter The Name Of Your Creatur: ";
char Name[16];
cin.get(Name,15);
cout << endl;

Tama Creatur;
Creatur.SetAge(0);
Creatur.SetWeight(5);
Creatur.SetFame(5);
Creatur.SetSete(5);
Creatur.SetBisognini(0);
Creatur.SetMalato(5);
Creatur.SetSporco(0);

char choose;
unsigned short int Turno = 0;

while (1)
{
 Turno++;

 MakeYourChoose:
 if (Turno-1) cout << endl;
 cout << Name << ":" << endl;
 cout << "Eta': " << Creatur.GetAge() << endl;
 cout << "Peso: " << Creatur.GetWeight() << endl;
 cout << "Fame: " << Creatur.GetFame() << endl;
 cout << "Sete: " << Creatur.GetSete() << endl;
 cout << "Bisognini: " << Creatur.GetBisognini() << endl;
 cout << "Sporco: " << Creatur.GetSporco() << endl;
 cout << "Malato: " << Creatur.GetMalato() << endl;
 cout << "Felicita': " << 5 + (5 - Creatur.GetFame()) + (5 - Creatur.GetSete()) + (10 - Creatur.GetSporco()) - Creatur.GetBisognini() - ( 5 - Creatur.GetMalato()) << endl;
	

	cout << "What Are You Going To Do Today: ";
	cin >> choose;
	switch (choose)
	{
	case 'c':
	case 'C': cout << "Ingrassa Porco.\n";
			  Creatur.SetFame(Creatur.GetFame()-2);
			  break;
	case 'b':
	case 'B': cout << "Annega Bastardo.\n";
			  Creatur.SetSete(Creatur.GetSete()-2);
			  Creatur.SetBisognini(Creatur.GetBisognini()+1);
			  break;
	case 'o':
	case 'O': cout << "E curiamolo il pirla.\n";
			  Creatur.SetMalato(Creatur.GetMalato()-2);
			  break;
	case 'p':
	case 'P': cout << "E Puliamolo pure.\n";
			  Creatur.SetSporco(0);
			  break;
	case 'i':
	case 'I': cout << "Ok, Facciamogli fare i bisognini.\n";
			  Creatur.SetBisognini(0);
			  Creatur.SetSporco(Creatur.GetSporco()+4);
	case 'n':
	case 'N': break;
	
	case 'l':
	case 'L': cout << endl << "Lista:" << endl;
			  cout << "B\tDagli Da Bere" << endl;
			  cout << "C\tDagli Da Mangiare" << endl;
			  cout << "I\tFagli Fare I Bisognini" << endl;			  
			  cout << "L\tQuesta Lista" << endl;
			  cout << "N\tNon fare Niente" << endl;
			  cout << "O\tCuralo" << endl;
			  cout << "P\tPuliscilo" << endl;
			  cout << "Q\tEsci" << endl;
			  goto MakeYourChoose;

	case 'q':
	case 'Q': cout << "Sei Sicuro di volerlo lasciare? (S/N) ";
			  Deficente:
			  cin >> choose;
			  if ((choose == 'N') || (choose == 'n')) goto MakeYourChoose;
			  if ((choose == 'S') || (choose == 's')) 
			  {
			  cout << Name << " Sentira' la tua mancanza." << endl;
			  goto InTheEnd;
			  }
			  cout << "Ehhh???(S/N)";
			  goto Deficente;
	default : cout << "Ma a che gioco stai giocando?\n";
			  cout << "Se vuoi 'l' e ti do la lista delle opzioni possibili" << endl;
			  goto MakeYourChoose;
	}

	if (choose != 'c') Creatur.SetFame(Creatur.GetFame()+1);
	if (choose != 'b') Creatur.SetSete(Creatur.GetSete()+1);
	if (choose != 'i') Creatur.SetBisognini(Creatur.GetBisognini()+1);
	
	
	if (Creatur.GetSporco() >= 5) Creatur.SetMalato(Creatur.GetMalato()+1);
	if (Creatur.GetFame() >= 8) Creatur.SetWeight(Creatur.GetWeight()-1);
	if (Creatur.GetFame() <= 2) Creatur.SetWeight(Creatur.GetWeight()+1);
	if (Turno % 10 == 0) Creatur.SetAge(Creatur.GetAge()+1);

	if (Creatur.GetAge() >= 10)
	{
	cout << endl << Name << " E' Morto Di Vecchiaia.\n";
	break;
	}
	if (Creatur.GetWeight() >= 10)
	{
	cout << endl << Name << " E' Esploso.\n";
	break;
	}
	if (Creatur.GetWeight() <= 0)
	{
	cout << endl << Name << " E' Tanto Magro Che Non Lo Vedi Piu'.\n";
	break;
	}
	if (Creatur.GetFame() >= 10)
	{
	cout << endl << Name << " E' Morto Di Fame.\n";
	break;
	}
	if (Creatur.GetFame() <= 0)
	{
	cout << endl << Name << " Ha Fatto Indigestione.\n";
	break;
	}
	if (Creatur.GetSete() >= 10)
	{
	cout << endl << Name << " E' Morto Di Sete.\n";
	break;
	}
	if (Creatur.GetSete() <= 0)
	{
	cout << endl << Name << " E' Annegato.\n";
	break;
	}
	if (Creatur.GetBisognini() >= 10)
	{
	cout << endl << Name << " E' Morto Di Bisognini (?!?!?).\n";
	break;
	}
	if (Creatur.GetSporco() >= 10)
	{
	cout << endl << Name << " E' Morto Di Sporco.\n";
	break;
	}
	if (Creatur.GetMalato() >= 10)
	{
	cout << endl << Name << " E' Morto Di Malattia.\n";
	break;
	}
 }
InTheEnd:
signed short int Punti = (Turno-1) * 100 + (Creatur.GetWeight()-5) * 10 - (Creatur.GetFame()-5) - (Creatur.GetSete()-5) - Creatur.GetSporco() - Creatur.GetMalato() - Creatur.GetBisognini();
if (Punti < 0) Punti = 0;
cout << "Punteggio: " << Punti << endl;
}