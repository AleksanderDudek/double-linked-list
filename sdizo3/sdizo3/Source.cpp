#include<iostream>
#include<string>
#include<cstring>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<ctime>
#include <cstdlib>
#include <vector>
#include <stack>

using namespace std;

class Wezel
{
public: 
	int klucz;
	char tablica[256];
	Wezel* lewy;
	Wezel* prawy;
	
};



//jest inicjacja drzewa, wstawJeden, wstawWiele, Znajdz, wyswietl in- i preorder, Usun(bez 2 stopnia), usun(2 stopien wezla), losowania charow do tablicy
//ekstra: znajdzPoprzednika


//brakuje: wyswietl postorder 




Wezel* Inicjacja(Wezel* &wezel)
{
	wezel = new Wezel[1]; // alokacja pamieci na jeden wezel
	wezel->lewy = NULL;
	wezel->prawy = NULL;
	//
	//
	return wezel; //tutaj zwraca adres z referencji podanej jako argument funkcji
}




int WstawJeden(Wezel* &korzen, int szukanyKlucz)
{
	//jakie sytuacje?
	//jest wstawiany jako pierwszy (root=NULL), wchodzi pomiedzy inne elementy (nie jest korzeniem, ani lisciem)

	Wezel* nowy = Inicjacja(nowy);
	nowy->klucz = szukanyKlucz;

	//tutaj losowanie tablicy charow

	srand(time(NULL));

	for (int i = 0; i < 255; i++)
	{
		nowy->tablica[i] = rand() % 26 + 1; //66 powinien zmienic wartosc na offset z ascii
	}
	nowy->tablica[255] = '\0'; //wiadomo, znak konca stringa
	//

	Wezel* rodzic = NULL; //bedzie wskazywal rodzica, cos jak 'straznik'
	Wezel* wskaznik = korzen;

	/////////////////////////
	//wyeliminowac Znajdz stad

	while (wskaznik != NULL)
	{
		if (wskaznik->klucz == szukanyKlucz)
		{
			cout << "Juz jest w drzewie" << endl;
			return 0;
		}
		rodzic = wskaznik;
		if (wskaznik->klucz > szukanyKlucz)
		{
			wskaznik = wskaznik->lewy;
		}
		else
		{
			wskaznik = wskaznik->prawy;
		}
	}

	/*if (korzen != NULL && korzen->lewy == NULL && korzen->prawy == NULL)
	{
		rodzic = wskaznik;
	}*/

	if (korzen == NULL)
	{
		korzen = nowy;
	}
	else if (rodzic->klucz > szukanyKlucz)
	{
		rodzic->lewy = nowy;
	}
	else
	{
		rodzic->prawy = nowy;
	}

	
	return 0;
}

Wezel* Znajdz(Wezel* &korzen, int szukanyKlucz)
{

	if (!korzen)
	{
		cout << "Puste drzewo, nic nie znajdziesz" << endl;
		return NULL;
	}
	else
	{
		bool znaleziony = 0;
		Wezel* wskaznik = korzen;

		while (wskaznik != NULL && !znaleziony)
		{
			if (wskaznik->klucz == szukanyKlucz)
			{
				znaleziony = 1;
				cout << "Znalazlem" << endl;
				return wskaznik;
			}
			else if (wskaznik->klucz < szukanyKlucz)
			{
				wskaznik = wskaznik->prawy;
			}
			else
			{
				wskaznik = wskaznik->lewy;
			}
		}
		cout << "Nie znalazlem" << endl;
		return NULL;
	}


}

///////////////////////////////////////////////
void WstawWiele(Wezel* &korzen, int ileNowych)
{
	srand(time(NULL));
	int klucz;
	for (int i = 0; i<ileNowych; i++)
	{
		klucz = (rand() % 10003) + 10; //losowanie
		if (!Znajdz(korzen, klucz)) //gwarancja unikalnosci klucza
		{
			WstawJeden(korzen, klucz); //chodzi o te linijke 
			cout << "Wstawilem: " << klucz << endl;
		}
		else //powtarza losowanie poprzez zmniejszenie iteratora for
		{
			i = i - 1;
		}

	}
}

//albo znajdz rodzica albo w Znajdz przechowywac rodzica



int ZrobPreorder(Wezel* &korzen)
{
	if (!korzen)
	{
		cout << "Puste drzewo, nic nie wypisze" << endl;
		return 0;
	}
	else
	{
		stack<Wezel*> stos;
		Wezel* wskaznik = korzen;

		stos.push(wskaznik);
		while (!stos.empty())
		{
			wskaznik = stos.top();
			stos.pop();
			cout << " Klucz: " << wskaznik->klucz << " ";
			if (wskaznik->prawy)
			{
				stos.push(wskaznik->prawy);
			}
			if (wskaznik->lewy)
			{
				stos.push(wskaznik->lewy);
			}
		}

	}
	return 0;
}


int RekurencyjnyInorder(Wezel* korzen)
{

	while (korzen != NULL)
	{

	}
	if (korzen->lewy && korzen->prawy)
	{
		return NULL;
	}

	return NULL;
}

int ZrobInorder(Wezel* &korzen)
{
	
		stack<Wezel*> stos;
		Wezel* wskaznik = korzen;

		while (wskaznik)
		{
			while (wskaznik)
			{
				if (wskaznik->prawy)
				{
					stos.push(wskaznik->prawy);
				}
				stos.push(wskaznik);
				wskaznik = wskaznik->lewy;
			}
			wskaznik = stos.top();
			stos.pop();

			while (!stos.empty() && wskaznik->prawy == NULL)
			{
				cout << " Klucz: " << wskaznik->klucz <<" ";
				wskaznik = stos.top();
				stos.pop();
			}
			cout << " Klucz: " << wskaznik->klucz << " ";
			if (!stos.empty())
			{
				wskaznik = stos.top();
				stos.pop();
			}
			else
			{
				wskaznik = NULL;
			}
		}

	
	return 0;
}


int counter = 0;

int RekPostorder(Wezel* korzen)
{
	if (korzen != NULL)
	{
		RekPostorder(korzen->lewy);
		RekPostorder(korzen->prawy);
		cout << "Klucz: " << korzen->klucz << " ";
		counter++;
	}

	return 0;
}


int ZrobPostorder(Wezel* korzen)
{
	if (!korzen) return 0;
	stack<Wezel*> s;
	s.push(korzen);
	Wezel *prev = NULL;
	while (!s.empty()) {
		Wezel *curr = s.top();
		if (!prev || prev->lewy == curr || prev->prawy == curr) {
			if (curr->lewy)
				s.push(curr->lewy);
			else if (curr->prawy)
				s.push(curr->prawy);
		}
		else if (curr->lewy == prev) {
			if (curr->prawy)
				s.push(curr->prawy);
		}
		else {
			cout << "Klucz: "<< curr->klucz << " ";
			s.pop();
		}
		prev = curr;
	}

	return 0;
}




//szukamnie Poprzednika dla danego elementu

vector<Wezel*>  ZnajdzPoprzednika(Wezel* kopiaKasowanego, Wezel* kopiaKorzenia)
{
	//z mojego zalozenia wynika, ze element, o ktorym wspominamy pozniej zawsze ma rodzica - korzen jest kasowany manualnie, a nie poprzez zfunkcje usunjeden

	//funkcja przechodzi przez drzewo poszukujac zarowno rodzica danego elementu usuwanego jak i jego poprzednika, normalnie przechodzi przez drzewo przeszukujac, az znajdzie rodzica 
	// potem gdy mamy rodzica rozpatrujemy sytuacje gdy usuwany element ma tylko syna oraz wnuki w prawym poddrzewie syna

	vector<Wezel*> wskazniki(2);

	Wezel* rodzic = NULL;
	Wezel* poprzednik = NULL;

	//asercja z while jest raczej niemozliwa, bo jesli do tego by doszlo, to znaczy, ze wezel o danym kluczu nie istnieje, a zostalo to 
	//wczesniej sprawdzone przez UsunJeden, tutaj po prostu szukamy rodzica kasowanego i jego poprzednika
	
	
	//tutaj znajdujemy rodzica
	while (kopiaKorzenia != NULL)
	{

		if (kopiaKorzenia->lewy != NULL)
		{
			if (kopiaKorzenia->lewy->klucz == kopiaKasowanego->klucz)
			{
				rodzic = kopiaKorzenia;
				kopiaKorzenia = kopiaKorzenia->lewy;
				break;
			}
		}
		
		if (kopiaKorzenia->prawy != NULL)
		{
			if (kopiaKorzenia->prawy->klucz == kopiaKasowanego->klucz)
			{
				rodzic = kopiaKorzenia;
				kopiaKorzenia = kopiaKorzenia->prawy;
				break;
			}
		}
		

		if (kopiaKorzenia->klucz > kopiaKasowanego->klucz)
		{
			kopiaKorzenia = kopiaKorzenia->lewy;
		}
		else
		{
			kopiaKorzenia = kopiaKorzenia->prawy;
		}
	}


	//tutaj znajdujemy poprzednika, kopiaKorzenia jest de facto kopiaElementu


	kopiaKasowanego = kopiaKasowanego->lewy;

	if (kopiaKasowanego->prawy != NULL)
	{
		
		while (kopiaKasowanego->prawy != NULL)
		{
			poprzednik = kopiaKasowanego;
			kopiaKasowanego = kopiaKasowanego->prawy;	
		}

		//jak
	}
	else
	{ //ma tylko lewego kandydata na poprzednika
		poprzednik = kopiaKasowanego;
	}


	//if(wezel->lewy!=NULL )
	//{
	//	Wezel* rodzic = wezel; // to jest czasem falszem, bo albo moze byc korzeniem i chuj bo nie ma rodzica albo ma tylko syna i wtedy gunwo bo rodzicem pozostaje 
	//	Wezel* poprzednik = wezel->lewy; //z definicji zawsze tak jest, jesli ma tylko syna


	//	while (poprzednik->prawy != NULL)
	//	{
	//		rodzic = poprzednik;
	//		poprzednik = poprzednik->prawy;
	//	}

	//





		wskazniki[0] = rodzic;
		wskazniki[1] = poprzednik;

		return wskazniki;
	
	

	
}


//nalezy rozwazyc takze wskazania dzieci na parenta i w druga strone
int UsunJeden(Wezel* &korzen, int szukanyKlucz)
{
	//trywialne - korzen==NULL i nie ma wezla
	if (!korzen)
	{
		cout << "Puste drzewo, nic nie usuniesz" << endl;
		return 0;
	}
	else
	{

		//nie istnieje
		Wezel* rodzic = NULL;
		Wezel* wskaznik = korzen;


		//przeszukiwanie drzewa
		while (wskaznik != NULL && szukanyKlucz != wskaznik->klucz)
		{
			rodzic = wskaznik;
			if (wskaznik->klucz < szukanyKlucz)
			{
				wskaznik = wskaznik->prawy;
			}
			else
			{
				wskaznik = wskaznik->lewy;
			}
		}

		if (wskaznik == NULL)
		{
			cout << "Nie ma potomkow o takim kluczu. Nie moge usunac" << endl;
			return -1; //to znaczy, ze nie ma potomkow o takim kluczuw ogole i
		}
			

		//tutaj juz jakis zostal znaleziony
		
		//jest lisciem
		//good
		if ((wskaznik->prawy == NULL) && (wskaznik->lewy == NULL))
		{
			//usuwanie: jest korzeniem i lisciem,
			if (wskaznik == korzen)
			{
				delete korzen;
				cout << "Korzen zostal usuniety, drzewo umarlo" << endl;
				return 0;
			}

			
			//usuwam znacznik w rodzicu
			if (rodzic->prawy == wskaznik)
			{
				rodzic->prawy = NULL; //lisc jest prawym potomkiem swojego rodzica
			}
			else
			{
				rodzic->lewy = NULL; //lisc jest lewym potomkiem swojego rodzica
			}

			delete wskaznik; //usuwam liscia
			cout << "Usunieto wezel o kluczu: " << szukanyKlucz << endl;

			return 0;
		}

	

		// ma na bank przynajmniej 1 stopien (jedno poddrzewo), referencja do potomka u rodzica zmienia sie na 'wnuka', syn
		// umiera

		// good
		if (wskaznik->prawy == NULL) //lewe poddrzewo
		{
			//jesli kasowany element jest korzeniem drzewa z lewym poddrzewem
			if (wskaznik == korzen)
			{
				korzen = wskaznik->lewy;
			}
			
			if (rodzic->prawy == wskaznik)
			{
				rodzic->prawy = wskaznik->lewy;
				delete wskaznik; 
			}
			if(rodzic->lewy == wskaznik)
			{
				rodzic->lewy = wskaznik->lewy;
				delete wskaznik;
			}

			
			cout << "Usunieto wezel o kluczu: " << szukanyKlucz << endl;

			return 0;
		}

		//good
		if (wskaznik->lewy == NULL) //prawe poddrzewo
		{
			//jesli kasowany element jest korzeniem drzewa z prawym poddrzewem
			if (wskaznik == korzen)
			{
				korzen = wskaznik->prawy;
				korzen->lewy = wskaznik->prawy->lewy;
				korzen->prawy = wskaznik->prawy->prawy;
			}

			if (rodzic->prawy == wskaznik)
			{
				rodzic->prawy = wskaznik->prawy;
				delete wskaznik;
			}
			if (rodzic->lewy == wskaznik)
			{
				rodzic->lewy = wskaznik->prawy;
				delete wskaznik;
			}
			cout << "Usunieto wezel o kluczu: " << szukanyKlucz << endl;

			return 0;
		}


		//docierajac tutaj zakladamy, ze mamy przynajmniej drzewo, gdzie jakis wezel
		//ma 2 poddrzewa, ponizszy wektor zwraca poprzednika takiego drzewa i rodzica
		//tego poprzednika


		//trzeba sie zastanowic czy nie wprowadzic tu wykladu, bo juz szlag mnie trafia

		Wezel* przedRodzic = wskaznik; //rodzic poprzednika
		Wezel* dziecko = wskaznik->lewy; //de facto poprzednik 
		
		while (dziecko->prawy != NULL) //szukanie poprzednika wsrod (pra)wnuka
		{
			przedRodzic = dziecko;
			dziecko = dziecko->prawy;
		}

		if (dziecko == wskaznik->lewy) //poprzednik jest lewym potomkiem usuwanego wezela =
										// = usuwany element jest rodzicem poprzednika
		{
			if (rodzic->prawy == wskaznik) //rodzic usuwanego elementu adoptuje poprzednika
			{
				rodzic->prawy = dziecko; 
			}
			if (rodzic->lewy == wskaznik)
			{
				rodzic->lewy = dziecko;
			}
			
			dziecko->prawy = wskaznik->prawy;
			//po prostu podciagamy dziecko usuwanego elementu, 

			delete wskaznik;
			cout << "Usunieto wezel o kluczu: " << szukanyKlucz << endl;
			return 0;
		}

		// poprzednik jest pra(pra...)wnukiem


		//ewentualny potomek poprzednika, w razie co jest nullem
		Wezel* wnuk = dziecko->lewy;



		//poza adopcja poprzednika, wskazania poprzednika ulegaja zmianie i wskazania rodzi


		//adopcja ewentualnego dziecka (lewego potomka) poprzednika przez rodzica poprzednika, w razie co nulla
		if (przedRodzic->prawy == dziecko)
		{
			przedRodzic->prawy = wnuk;
		}
		if (przedRodzic->lewy == dziecko)
		{
			przedRodzic->lewy = wnuk;
		}

		//poprzednik adoptuje dzieci usuwanego elementu

		dziecko->lewy = wskaznik->lewy;
		dziecko->prawy = wskaznik->prawy;


		//rodzic usuwanego elementu adoptuje poprzednika
		if (rodzic->prawy == wskaznik)
		{
			rodzic->prawy = dziecko;
		}
		if (rodzic->lewy == wskaznik)
		{
			rodzic->lewy = dziecko;
		}


		delete wskaznik;
		cout << "Usunieto wezel o kluczu: " << szukanyKlucz << endl;
		return 0;

		//

		//vector<Wezel*> poprzPlusRodzic = ZnajdzPoprzednika(wskaznik, korzen); 

		//Wezel* rodzicPoprzednika = poprzPlusRodzic[0];
	 //   Wezel* poprzednik = poprzPlusRodzic[1];

		////poprzednik z definicji nie moze miec 2 stopnia w przypadku BST

		////przepinam wskazania opcjonalnych potomkow poprzednika na rodzica poprzednika
		////czyli rodzicPoprzednika->prawy=poprzednik->lewy albo =NULL (jesli poprzednik jest lisciem)

		//if (poprzednik->lewy != NULL)
		//	//jesli poprzednik jest dzieckiem
		//{
		//	if (poprzednik == wskaznik->lewy) //jesli poprzednik elementu jest dzieckiem tego elementu, to:
		//	{
		//		rodzicPoprzednika->lewy = poprzednik->lewy;
		//	}
		//	else //jesli poprzednik elementu jest (pra...)wnukiem tego elementu, to:
		//	{
		//		rodzicPoprzednika->prawy = poprzednik->lewy;
		//	}
		//	//kasuje wskazania na potomka znalezionego poprzednika (jesli nie jest lisciem)
		//	//poprzednik->lewy=NULL;
		//	poprzednik->lewy = NULL;
		//}
	
		//poprzednik->lewy = wskaznik->lewy;
		//poprzednik->prawy = wskaznik->prawy;

		//if (wskaznik == korzen)
		//{
		//	korzen = poprzednik;
		//}

		//delete wskaznik;
		//cout << "Usunieto wezel o kluczu: " << szukanyKlucz << endl;


		//return 0;

		////wskazania z kasowanego elementu na potomkow przepinam na poprzednika
		////poprzednik->lewy = wskaznik->lewy i to samo dla prawego

		////jesli usuwany element jest rootem no to wypadaloby tez zmienic root=poprzednik;

		////a co w przypadku jesli kasowany element jest rootem 2 stopnia, gdzie ma same liscie?


		////jesli element, ktory chcemy kasowac jest poziomem 1, to:
		//// jesli jego poprzednikiem jest element w 2 poziomie, to: (dziecko)

		////jesli jego poprzednkiem jest element w 3 lub wyzszym poziomie, to (wnuk ++)


		////wtedy poprzednik to lewy lisc, rodzic poprzednika to root, nie ma adopcji tylko jest kill

		////no i kasujemy w chuj ten element 

	}

}
void UsunWszystkie(Wezel* &korzen)
{
	/*stack<Wezel*> stosDoUsuniecia;*/





	int kluczKorzen = korzen->klucz;
	//cale lewe poddrzewo
	while (korzen->lewy!=NULL)
	{
		UsunJeden(korzen, korzen->lewy->klucz);

		cout << endl;
		cout << endl;

		//ZrobPostorder(korzen);

		cout << endl;
		cout << endl;
	}
	cout << "Usunalem lewe poddrzewo!" << endl;
	//cale prawe poddrzewo
	while (korzen->prawy!=NULL)
	{
		UsunJeden(korzen, korzen->prawy->klucz);

		cout << endl;
		cout << endl;

		//ZrobPostorder(korzen);

		cout << endl;
		cout << endl;
	}
	cout << "Usunalem prawe poddrzewo!" << endl;
	//na koniec root'a i chill :)

	delete korzen;
	cout << "Usunalem korzen: " <<kluczKorzen<<" !" << endl;
	cout << "Usunalem wszystko!" << endl;

}


int main()
{
	//start
	clock_t begin, end;
	double time_spent;

	begin = clock();



	int k1 = 1, k2 = 2, k3 = 3, k4 = 4, X = 10;
	Wezel* lista;
	Wezel* korzen = NULL; //czolo przechowuje adres lista

	/*int* tablica = new int[10];

	tablica[0] = 9;
	tablica[1] = 1;
	tablica[2] = 5;
	tablica[3] = 3;
	tablica[4] = 7;
	tablica[5] = 4;
	tablica[6] = 15;
	tablica[7] = 10;
	tablica[8] = 12;
	tablica[9] = 11;

	for (int i = 0; i < 10; i++)
	{
		WstawJeden(korzen, tablica[i]);
	}

	UsunJeden(korzen, 5);

	ZrobPostorder(korzen); */
	//to moze byc zbedne i wtedy trzeba zmienic we WstawJeden cos
	//lista=Inicjacja(lista);

	//czoloListy gdzies powinno sie zmieniac przy wstawianiu i usuwaniu
	cout << "start" << endl;



	UsunJeden(korzen, k1);

	cout << "Jeden" << endl; 



	WstawWiele(korzen, X);

	cout << "Wstawione" << endl;


	WstawJeden(korzen, k1);

	cout << "Jeden" << endl;


	WstawJeden(korzen, k2);

	cout << "Jeden" << endl;

	WstawJeden(korzen, k3);
	cout << "Jeden" << endl;

	WstawJeden(korzen, k4);
	cout << "Jeden" << endl;

	cout << endl;
	cout << endl;

	cout << "Na stosie: " << endl;
	ZrobPostorder(korzen);
	cout << endl;

	cout << "Rekurencyjnie: " << endl;
	RekPostorder(korzen);
	cout << endl;

	cout << endl;
	cout << endl;

	UsunJeden(korzen, k1);
	cout << "Jeden" << endl;

	Znajdz(korzen, k1);
	cout << "Jeden" << endl;

	cout << endl;
	cout << endl;

	cout << "Na stosie: " << endl;
	ZrobPostorder(korzen);
	cout << endl;


	cout << "Rekurencyjnie: " << endl;
	RekPostorder(korzen);
	cout << endl;

	cout << endl;
	cout << endl;

	UsunJeden(korzen, k2);
	cout << "Jeden" << endl;

	UsunJeden(korzen, k3);
	cout << "Jeden" << endl;

	UsunJeden(korzen, k4);
	cout << "Jeden" << endl;


	//ZrobInorder(korzen);


	//cout << endl;
	//cout << endl;

	//ZrobPreorder(korzen);

	cout << endl;
	cout << endl;

	ZrobPostorder(korzen);

	cout << endl;
	cout << endl;

	UsunWszystkie(korzen);

	cout << "\n stop" << endl;
	//czas stop
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	cout << "Czas: " << time_spent << endl;
	//stop i wypisz czas
	system("pause");

	return 0;
}