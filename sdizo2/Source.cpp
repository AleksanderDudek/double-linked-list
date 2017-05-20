#include<iostream>
#include<string>
#include<cstring>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<ctime>
#include <cstdlib>

using namespace std;

// inicjuj, wstawJeden, wstawWiele, znajdz, wyswietl jest super
// wydaje sie, ze usunwszystkie dobrze wyglada

// zostal tylko USUNJEDEN

class Struktura
{
public:
	int klucz;
	double jeden;
	double dwa;
	double trzy;
	Struktura* nastepnik;
	Struktura* poprzednik;

private:
};

Struktura* Inicjacja(Struktura* &elementListy)
{
	elementListy = new Struktura[1]; // alokacja pamieci na jeden wezel
	elementListy->nastepnik = NULL;
	elementListy->poprzednik = NULL;
	//
	//
	return elementListy; //tutaj zwraca adres z referencji podanej jako argument funkcji
}




//tu bedzie inicjuj, w pewnym sensie sortuj, ale chodzi o znalezienie odpowiedniego adresu 
int WstawJeden(Struktura* &czoloListy, int klucz)
{

	//jesli jest pusta lista tylko zainicjalizowana, czolo jest taka pusta lista to:

	Struktura* head = czoloListy;
	//albo wykladowo

	Struktura* nowy = Inicjacja(nowy);
	if (!nowy) return -1;
	nowy->klucz = klucz;
	nowy->jeden = rand();
	nowy->dwa = rand();
	nowy->trzy = rand();

	if (!head) //jesli pusta
	{
		czoloListy = nowy;
		return 0;
	}

	Struktura* pointer = head;
	while (pointer)
	{
		if (pointer->klucz == klucz)
		{
			delete nowy;
			return -2; //
		}

		if (pointer->klucz<klucz) //biezacy element ma mniejszy klucz
		{
			if (pointer == head && pointer->nastepnik == NULL)
			{
				nowy->nastepnik = pointer;
				nowy->poprzednik = pointer;

				pointer->nastepnik = nowy;
				pointer->poprzednik = nowy;
				return 0;
			}
			if (pointer->nastepnik == czoloListy) //dodaje tutaj, sytuacja konca listy
			{
				nowy->nastepnik = czoloListy;
				nowy->poprzednik = pointer;

				pointer->nastepnik = nowy;
				czoloListy->poprzednik = nowy;

				return 0;
			}
			else
			{
				pointer = pointer->nastepnik; //przesuwanie
			}
			
		}
		else //tutaj nalezy wcisnac nowy element 
		{


			if (pointer == head) //jesli pointer wskazuje na czolo i dodajemy to znaczy ze dodany jest nowym czolem (bo nie przesunelismy sie dalej)
			{
				czoloListy = nowy;
			}

			//kiedy mamy do czynienia tylko z 1 elementem i dodajemy 2
			if (pointer == head && pointer->nastepnik == NULL)
			{
				nowy->nastepnik = pointer;
				nowy->poprzednik = pointer;

				pointer->nastepnik = nowy;
				pointer->poprzednik = nowy;
				return 0;
			}
			
			nowy->nastepnik = pointer;
			nowy->poprzednik = pointer->poprzednik;

			pointer->poprzednik->nastepnik = nowy;
			pointer->poprzednik = nowy;
			//tu pojawil sie blad w sytuacji kiedy mamy dodawany nowy element, jesli jest 1 element, to przeciez nowy nie ma poprzednika i nastepnika :) dopiero je ustawia
			

			return 0;
		}


	}


}

Struktura* Znajdz(Struktura* &czoloListy, int szukanyKlucz)
{
	int znaleziony = 0;
	Struktura *wskaznik = czoloListy;

	if (!czoloListy)
	{
		cout << "Pusta lista, wstawilem nowy element" << endl;

		//te linijke moge zakomentowac, jest po to, aby dzialal znajdz w przypadku kiedy listy jeszcze nie ma
		WstawJeden(czoloListy, szukanyKlucz);
		return NULL;
	}


	while (wskaznik != czoloListy->poprzednik)
	{
		if (wskaznik->klucz == szukanyKlucz)
		{
			cout << "Znalazlem " << szukanyKlucz << " w adresie " << wskaznik << endl;
			return wskaznik;
		}
		wskaznik = wskaznik->nastepnik;
	}
	//zoptymalizowac szukanie w momencie kiedy element jest wiekszy od wylosowanego
	cout << "Nie Znalazlem " << szukanyKlucz << endl;
	return NULL;
}

// WstawJeden iles tam razy
void WstawWiele(Struktura* &czoloListy, int ileNowych)
{
	srand(time(NULL));
	int klucz;
	for (int i = 0; i<ileNowych; i++)
	{
		klucz = (rand() % 100001) + 10; //losowanie
		if (!Znajdz(czoloListy, klucz)) //gwarancja unikalnosci klucza
		{
			WstawJeden(czoloListy, klucz); //chodzi o te linijke 
		}
		else //powtarza losowanie poprzez zmniejszenie iteratora for
		{
			i = i - 1;
		}

	}
}

//zwraca adres elementu o zadanym kluczu, dzieki temu mozna pozniej robic z tym rozne kombosy









int UsunJeden(Struktura* &czoloListy, int szukanyKlucz)
{

	//gdy nic nie ma usuwanie
	if (!czoloListy)
	{
		cout << "Pusta lista, nic nie usuniesz" << endl;
		return 0;
	}

	Struktura* wskaznik = NULL;
	wskaznik = Znajdz(czoloListy, szukanyKlucz); //zwraca adres szukanego elementu


	



	//usuwanie gdy zostal 1, zostaly 2, usuwany jest czolem, jest ogonem, jest pomiedzy
	if (wskaznik)
	{

		if (wskaznik->nastepnik == NULL)  //asercja 1 elementowej listy; warunek wystarczajacy, bo zarowno nast jak i poprz sa wtedy NULLem
		{
			delete wskaznik;

			cout << "Usunieto element o kluczu: " << szukanyKlucz << endl; //komunikat

			return 0;
		}

		if (wskaznik->nastepnik == wskaznik->poprzednik) //asercja 2 elementowej listy
		{
			if (wskaznik == czoloListy) //usuwam czolo
			{
				czoloListy = wskaznik->nastepnik;

				wskaznik->nastepnik->poprzednik = NULL;
				wskaznik->nastepnik->nastepnik = NULL;

				wskaznik->nastepnik = NULL;
				wskaznik->poprzednik = NULL;

				//zostaje sam ogon, ktory zmienil sie w czolo
				delete wskaznik;

				cout << "Usunieto element o kluczu: " << szukanyKlucz << endl; //komunikat

				return 0;

			}
			else //usuwam ogon
			{
				wskaznik->nastepnik->poprzednik = NULL;
				wskaznik->nastepnik->nastepnik = NULL;

				wskaznik->nastepnik = NULL;
				wskaznik->poprzednik = NULL;

				//zostaje samo czolo
				delete wskaznik;

				cout << "Usunieto element o kluczu: " << szukanyKlucz << endl; //komunikat

				return 0;

			}
		}

		// lista nie jest pusta, 1 czy 2 elementowa

		//teraz pozostaje sytuacja wieloelementowej listy cyklicznej, zakladamy ze ma min 3 lub wiecej elementow

		//usuwam czolo, ogon, albo srodek

		Struktura* old = NULL;

		if (wskaznik == czoloListy)
		{
			//nastepnik nowym czolem,
			old = czoloListy; //adres czola ktore usuwamy

			//zmiana czolo
			czoloListy = old->nastepnik;
			//ogon zmienia nastepnika, 
			old->poprzednik->nastepnik = czoloListy;
			czoloListy->poprzednik = old->poprzednik;

			//wygaszenie wskazan starego czola
			old->nastepnik = NULL;
			old->poprzednik = NULL;

			//usuwam stare czolo
			delete old;

		}
		else if (wskaznik==czoloListy->poprzednik) //czy jest ogonem
		{
			old = czoloListy->poprzednik;
			//zmiana ogona
			czoloListy->poprzednik = old->poprzednik;
			//ogon zmienia nastepnika, 
			czoloListy->poprzednik->nastepnik = czoloListy;
			

			//wygaszenie wskazan starego ogona
			old->nastepnik = NULL;
			old->poprzednik = NULL;

			//usuwam stary ogon
			delete old;
		}
		else //jest posrodku
		{
			wskaznik->poprzednik->nastepnik = wskaznik->nastepnik;
			wskaznik->nastepnik->poprzednik = wskaznik->poprzednik;

			wskaznik->nastepnik = NULL;
			wskaznik->poprzednik = NULL;

			delete wskaznik;
		}

		cout << "Usunieto element o kluczu: " << szukanyKlucz << endl; //komunikat
		return 0;
	}
	else
	{

		cout << "Nie ma takiego elementu na liscie!" << endl;
		return 0;
	}
	

}










void Wyswietl(Struktura* &czoloListy) // od przodu i od tylu
{
	Struktura* wskaznik = czoloListy;
	int iterator = 1;

	if (!wskaznik) {
		cout << "Pusta lista" << endl; //wchodzi i czolo listy jest nullem 0_i
	}

	//przod
	while (wskaznik != czoloListy->poprzednik)
	{
		cout << "Klucz " << iterator << ": " << wskaznik->klucz << " Liczba1: " << wskaznik->jeden << " Liczba2: " << wskaznik->dwa <<
			" Liczba3: " << wskaznik->trzy << endl;
		iterator = iterator + 1;
		wskaznik = wskaznik->nastepnik;
	}
	cout << "Klucz " << iterator << ": " << wskaznik->klucz << " Liczba1: " << wskaznik->jeden << " Liczba2: " << wskaznik->dwa <<
		" Liczba3: " << wskaznik->trzy << endl;

	cout << endl; 

	//tyl
	wskaznik = czoloListy->poprzednik;

	while (wskaznik != czoloListy)
	{
		cout << "Klucz " << iterator << ": " << wskaznik->klucz << " Liczba1: " << wskaznik->jeden << " Liczba2: " << wskaznik->dwa <<
			" Liczba3: " << wskaznik->trzy << endl;
		iterator = iterator - 1;
		wskaznik = wskaznik->poprzednik;
	}
	cout << "Klucz " << iterator << ": " << wskaznik->klucz << " Liczba1: " << wskaznik->jeden << " Liczba2: " << wskaznik->dwa <<
		" Liczba3: " << wskaznik->trzy << endl;
}

// dobrze, jakby zwracala adres, zeby moc operowac na nim przy wstawianiu
// tworzy pojedynczy element i nadaje mu wartosci



//od tylu usuwanie, wydaje sie byc wszystko dobrze
void UsunWszystkie(Struktura* &czoloListy)
{
	Struktura* wskaznik = czoloListy->poprzednik;
	Struktura*  kontener;

	while (wskaznik != czoloListy)
	{
		//usuwamy od konca do przodu, musimy przechowac adres poprzednika przed usunieciem
		kontener = wskaznik->poprzednik; //zeby nie stracic adresu poprzednika po usunieciu
										 //UsunJeden
		UsunJeden(czoloListy, wskaznik->klucz);

		wskaznik = kontener; //zmiana na poprzedni element listy, czyli kolejny do usuniecia
	}
	delete czoloListy; //usuwa ostatni element, jakim jest czolo jesli dorobie to moge zrobic po prostu UsunJeden(czoloListy)

	cout << "Usunalem wszystko!" << endl; 
}

int main()
{
	//start
	clock_t begin, end;
	double time_spent;

	begin = clock();



	int k1 = 1, k2 = 2, k3 = 3, k4 = 4, X = 1000;
	Struktura* lista;
	Struktura* czoloListy = NULL; //czolo przechowuje adres lista


								  //to moze byc zbedne i wtedy trzeba zmienic we WstawJeden cos
								  //lista=Inicjacja(lista);

								  //czoloListy gdzies powinno sie zmieniac przy wstawianiu i usuwaniu
	cout << "start" << endl;

	UsunJeden(czoloListy, k1);
	



	// tutaj jest blad
	WstawWiele(czoloListy, X);
	


	WstawJeden(czoloListy, k2);
	

	UsunJeden(czoloListy, k2);
	// po usunieciu jednego zjebal sie poprzednik czola, notabene dodany element stal sie nowym czolem


	Znajdz(czoloListy, k3);
	
	//do tej pory spoko

	WstawJeden(czoloListy, k4);
	cout << "wstawilem 4" << endl;

	UsunJeden(czoloListy, k4);
	cout << "usunalem 4" << endl;

	//przod i tyl jednoczesnie
	Wyswietl(czoloListy);
	cout << "wypisalem" << endl;

	UsunWszystkie(czoloListy);
	cout << "usunalem calosc" << endl;

	cout << "stop" << endl;
	//czas stop
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	cout << "Czas: " << time_spent << endl;
	//stop i wypisz czas
	system("pause");

	return 0;
}