#include <iostream>
#include <math.h>
#include <ctime>
#include <random>
#include <string>
#include <array>
#include <chrono>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <list>


using namespace std;
mt19937_64 rng(time(nullptr)); //глобальный рандом
#define MAXSTACK 2048


class Timer
{
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, milli >;

	chrono::time_point<clock_t> m_beg;
	chrono::time_point<clock_t> m_end;

public:
	Timer() {}

	void start()
	{
		m_beg = clock_t::now();
	}
	void finish()
	{
		m_end = clock_t::now();
	}

	double elapsed() const
	{
		//return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
		return chrono::duration_cast<second_t>(m_end - m_beg).count();
	}
}; Timer timer;

class Date
{
private:
	int dd; int mm; int yy;
	int month[12] = { 30,28,31,30,31,30,31,31,30,31,30,31 };
public:
	Date()
	{}
	Date(int d, int m, int y)    
	{
		dd = d; mm = m; yy = y;
	}

	Date ThrowRandomDate()
	{
		/*любой год с 1000 до 2500*/
		int newy = 1000 + rng() % 1500;
		/*любой месяц с 1 до 12*/
		int newm = 1 + rng() % 12;
		int newd = 1 + rng() % month[newm - 1];
		Date newdate(newd, newm, newy);
		return (newdate);
	}
	Date ThrowUnrandomDate(int a)
	{
		int newy = 0;
		if (a == 1)
			/*любой год с 1000 до 1750*/
			newy = 1000 + rng() % 750;
		else
			/*любой год с 1750 до 2500*/
			newy = 1750 + rng() % 750;

		/*любой месяц с 1 до 12*/
		int newm = 1 + rng() % 12;
		int newd = 1 + rng() % month[newm - 1];
		Date newdate(newd, newm, newy);
		return (newdate);
		
	}

	string PrintDate()
	{
		return to_string(dd) + "." + to_string(mm) + "." + to_string(yy);
	}


	friend bool operator > (Date a, Date b);
	friend bool operator >= (Date a, Date b);

};                                      //класс Дата

bool operator > (Date a, Date b)
{
	if (a.yy > b.yy)
		return true;
	if (a.yy < b.yy)
		return false;
	if (a.mm > b.mm)
		return true;
	if (a.mm < b.mm)
		return false;
	if (a.dd > b.dd)
		return true;
	else
		return false;
}
bool operator >= (Date a, Date b)
{
	if (a.yy >= b.yy)
		return true;
	if (a.yy < b.yy)
		return false;
	if (a.mm >= b.mm)
		return true;
	if (a.mm < b.mm)
		return false;
	if (a.dd >= b.dd)
		return true;
	else
		return false;
}


template <class Type>                                     //рандомное заполнение
Type* FillRandomly(Type [], size_t)   //если тип а не рассмотрен ниже
{
	throw domain_error("The unknown type");
}        

template<>
int* FillRandomly(int a [], size_t s)        //short int и int 
{
	a = new int[s];
	//cout << "Short numbers (press 1) or long (2)?" << "  ";
	int type = 2;
	//cin >> type;
	if (type > 2)
	{
		cout << "Error, try again" << endl;
		FillRandomly(a, s);
	}
	if (type == 1)
	{
		for (size_t i = 0; i < s; i++)
			a[i] = rng() % 10;
		return &a[0];
	}
	if (type == 2)
	{
		for (size_t i = 0; i < s; i++)
		{
			//a[i] = rng();
			a[i] = 10000000 + rng()%90000000; //для поразрядной
			if (a[i] < 0)
				a[i] *= (-1);
		}			                 

		return &a[0];
	}		
}

template<>
string* FillRandomly(string a[], size_t s)      //string
{
	a = new string[s];
	int l;
	char letter;
	string word;
	for (size_t i = 0; i < s; i++)
	{
		word.clear();
		//длина строк в массиве рандомная
		//l = 1 + rng() % 8;
		l = 6; //для поразрядной
		for (size_t j = 0; j < l; j++)
		{
			//'97' = a, '122' = z  122-97+1=26
			letter = char(97 + rng() % 26);
			word.push_back(letter);
		}
		a[i] = word;
	}
	return &a[0];
}

template<>
Date* FillRandomly(Date a[], size_t s)
{
	a = new Date[s];
	for (size_t i = 0; i < s; i++)
	{
		a[i] = a[i].ThrowRandomDate();
	}
	return &a[0];
}

template <class Type>                                    //нерандомное заполнение
Type* FillUnrandomly(Type[], size_t)  
{
	throw domain_error("The unknown type");
}

template<>
int* FillUnrandomly(int a[], size_t s)        //short int и int 
{
	a = new int[s];
	//cout << "Short numbers (press 1) or long (2)?" << "  ";
	int type = 2;
	//cin >> type;
	if (type > 2)
	{
		cout << "Error, try again" << endl;
		FillRandomly(a, s);
	}
	if (type == 1)
	{
		for (size_t i = 0; i < s/2; i++)
			a[i] = rng() % 5;
		for (size_t i = s/2; i < s; i++)
			a[i] = 5 + rng() % 5;
	}
	if (type == 2)
	{
		for (size_t i = 0; i < s/2; i++)
		{
			a[i] = 10000000 + rng() % 40000000; 
			if (a[i] < 0)
				a[i] *= (-1);
		}
		for (size_t i = s/2; i < s; i++)
		{
			a[i] = 50000000 + rng() % 50000000; 
			if (a[i] < 0)
				a[i] *= (-1);
		}
	}
	for (int i = 1; i < s;i++)     //для одинак элементов
	{
		a[i] = a[0];
	}
	return &a[0];
}

template<>
string* FillUnrandomly(string a[], size_t s)      //string
{
	a = new string[s];
	int l = 6; //длина = 6
	char letter;
	string word;
	for (size_t i = 0; i < s/2; i++)
	{
		word.clear();
		for (size_t j = 0; j < l; j++)
		{
			//'97' = a, '122' = z  122-97+1=26
			if (j==0)
				letter = char(97 + rng() % 13);
			else
				letter = char(97 + rng() % 26);
			word.push_back(letter);
		}
		a[i] = word;
	}
	for (size_t i = s/2; i < s; i++)
	{
		word.clear();
		for (size_t j = 0; j < l; j++)
		{
			//'97' = a, '122' = z  122-97+1=26
			if (j==0)
				letter = char(110 + rng() % 13);
			else
				letter = char(97 + rng() % 26);
			word.push_back(letter);
		}
		a[i] = word;
	}
	for (int i = 1; i < s; i++)     //для одинак элементов
	{
		a[i] = a[0];
	}
	return &a[0];
}

template<>
Date* FillUnrandomly(Date a[], size_t s)
{
	a = new Date[s];
	for (size_t i = 0; i < s/2; i++)
	{
		a[i] = a[i].ThrowUnrandomDate(1);
	}
	for (size_t i = s/2; i < s; i++)
	{
		a[i] = a[i].ThrowUnrandomDate(2);
	}
	for (int i = 1; i < s; i++)     //для одинак элементов
	{
		a[i] = a[0];
	}
	return &a[0];
}

template<class Type>                                        //печать
void RPrint(Type a[], size_t s) {};

template<>
void RPrint(int a[], size_t s)
{
	for (int i = 0; i < s; i++)
		cout << a[i] << " ";
	cout << endl;
}

template<>
void RPrint(string a[], size_t s)
{
	for (int i = 0; i < s; i++)
		cout << a[i] << " ";
	cout << endl;
}

template<>
void RPrint(Date a[], size_t s)
{
	for (int i = 0; i < s; i++)
		//cout << a[i].dd << "." << a[i].mm << "." << a[i].yy << " ";
		cout << a[i].PrintDate() << " ";
	cout << endl;
}

template <class Type, int size>                             //класс Массив
class Array
{
	//Type a[size];
	Type* a;

public:
	Array()
	{
		//выберет нужную функцию, в зависимости от типа а
		//a = FillRandomly(a, size);
		a = FillUnrandomly(a, size);
	}

	void Print()
	{
		RPrint(a, size);
	}

	Type* GetArray()
	{
		return a;
	}

	int GetSize()
	{
		return size;
	}

	~Array()
	{
		delete[]a;
	}
};

template <class T>                   //простой пузырек
void BubbleSort(T* ar, int n)           
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}
	
	timer.start();

	for (size_t i = 1; i < n; i++)
		for (size_t j = 0; j < n - i; j++)
			if (a[j] > a[j+1])
				swap(a[j], a[j+1]);

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() <<"),time of BubbleSort = " << timer.elapsed() << endl << endl;
}

template <class T>                    //пузырек с проверкой
void BubbleSortCheck(T* ar, int n)           
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();
	bool made = false;
	for (size_t i = 1; i < n && !made; i++)
	{
		made = true;
		for (size_t j = 0; j < n-i; j++)
			if (a[j] > a[j+1])
			{
				swap(a[j], a[j+1]);
				made = false;
			}				
	}

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of BubbleSortCheck = " << timer.elapsed() << endl << endl;
}

template <class T>                    //+выбор
void ChoiceSort(T* ar, int n)           
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();

	for (size_t i = 0; i < n - 1; i++)
		for (size_t j = i + 1; j < n; j++)
			if (a[i] > a[j])
				swap(a[i], a[j]);

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of ChoiceSort = " << timer.elapsed() << endl << endl;
}

template <class T>                    //вставками
void InsertSort(T* ar, int n)       
{
	T *a = new T[n];

	timer.start();

	a[0] = ar[0];
	bool push = false;
	for (size_t i = 1; i < n; i++)
	{
		push = false;
		for (size_t j = 0; j < i && !push; j++)  //перебор уже имеющихся в массиве эл-в
		{
			if (a[j] > ar[i])
			{
				for (size_t k = i; k > j; k--)   //двигаем все вправо
				{
					a[k] = a[k - 1];
				}
				a[j] = ar[i];
				push = true;
			}
		}
		if (!push)
			a[i] = ar[i];   //значит самое большое
	}

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of InsertSort = " << timer.elapsed() << endl << endl;
}

template <class T>                    //расческой
void BrushSort(T* ar, int n)
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();

	int d = n;  //изначальный шаг
	int help = 3;
	size_t k;

	while (help > 1)
	{
		d = d / 1.247;
		if (d < 1)
			d = 1;
		k = 0;
		for (size_t i = 0; i + d < n; i++)
		{
			if (a[i] > a[i + d])
			{
				swap(a[i], a[i + d]);
				k = i;    //запоминаем последний эл-т, который меняли
			}
		}
		if (d == 1)
			help = k + 1;  //если k было 0, то менять больше нечего и цикл не запустится
	}

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of BrushSort = " << timer.elapsed() << endl << endl;
}


template <class T>
void RQuickSort(T* a, int beg, int end)
{
	if (end - beg >= 1)
	{
		/*ищем опорный эл-т*/
		T pivot = a[beg];
		int pivoti = beg;
		bool b = false;
		for (int i = beg + 1; i <= end; i++)
		{
			if (a[i] > pivot)
			{
				pivoti = i;
				pivot = a[i];
				b = true;
				break;
			}
			if (pivot > a[i])
			{
				b = true;
				break;
			}					
		}
		if (!b)
		{
			return;
		}	

		/*раскидываем элементы по отношению к опорному*/
		int l = beg;
		int r = end;
		do
		{
			while (pivot > a[l])
				l++;
			while (a[r] >= pivot)
				r--;
			if (l < r)
				swap(a[l], a[r]);
		} while (l < r);

		//RPrint(a, end - beg + 1);
		RQuickSort(a, beg, l-1);
		RQuickSort(a, l, end);

	}
}
template <class T>                    //быстрая
void QuickSort(T* ar, int n)
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();
	RQuickSort(a, 0, n-1);

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of QuickSort = " << timer.elapsed() << endl << endl;
}
template <class T>
void QuickSortUnR(T* ar, long n)
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}
	timer.start();

	long size = n;
	long i, j;   			// указатели, участвующие в разделении
	long lb, ub;  		// границы сортируемого в цикле фрагмента
	long lbstack[MAXSTACK];
	long ubstack[MAXSTACK]; // стек запросов (каждый запрос = пара значений)					  

	long stackpos = 1;   	// текущая позиция стека
	long ppos;            // середина массива
	T pivot;              // опорный элемент
	T temp;

	lbstack[1] = 0;
	ubstack[1] = size - 1;

	do {
		// Взять границы lb и ub текущего массива из стека.
		lb = lbstack[stackpos];
		ub = ubstack[stackpos];
		stackpos--;
		do {
			// Шаг 1. Разделение по элементу pivot
			ppos = (lb + ub) >> 1;
			i = lb; j = ub; pivot = a[ppos];

			do {
				while (pivot > a[i]) i++;
				while (a[j] > pivot) j--;

				if (i <= j) {
					temp = a[i]; a[i] = a[j]; a[j] = temp;
					i++; j--;
				}
			} while (i <= j);

			// Сейчас указатель i указывает на начало правого подмассива,
			// j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
			// Возможен случай, когда указатель i или j выходит за границу массива

			// Шаги 2, 3. Отправляем большую часть в стек  и двигаем lb,ub

			if (i < ppos) {     // правая часть больше

				if (i < ub) {     //  если в ней больше 1 элемента - нужно 
					stackpos++;       //  сортировать, запрос в стек
					lbstack[stackpos] = i;
					ubstack[stackpos] = ub;
				}
				ub = j;             
									
			}
			else {       	    // левая часть больше
				if (j > lb) {
					stackpos++;
					lbstack[stackpos] = lb;
					ubstack[stackpos] = j;
				}
				lb = i;
			}

		} while (lb < ub);        // пока в меньшей части более 1 элемента

	} while (stackpos != 0);    // пока есть запросы в стеке

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of QuickSortUnR = " << timer.elapsed() << endl << endl;
}

template <class T>
void RMergeSort(T* a, int beg, int end)
{
	//!!!end - индекс реально последнего, а не кол-во эл-тов
	if (beg == end) //1 эл-т
		return;
	int mid = ((beg + end) / 2);
	RMergeSort(a, beg, mid);
	RMergeSort(a, mid + 1, end);

	//cout << beg << "    " << mid << "   " << end << endl;
	int ind1 = beg;
	int ind2 = mid + 1;
	T *help = new T [end-beg+1];  //промежуточ резы здесь будут
	for (size_t k = 0; k <= end - beg; k++)
	{
		if ((ind2 > end) ||((a[ind2] > a[ind1]) && (ind1 <= mid)))
		{
			help[k] = a[ind1];
			ind1++;
		}
		else
		{
			help[k] = a[ind2];
			ind2++;
		}
	}

	for (size_t k = 0; k <= end - beg; k++)
		a[beg + k] = help[k];
	//RPrint(help, end -beg +1);
}
template <class T>                   //слиянием
void MergeSort(T* ar, int n)
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();

	RMergeSort(a, 0, n - 1);

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of MergeSort = " << timer.elapsed() << endl << endl;
}

template <class T>
void HeapPush(T* a, int j, int l)
{
	size_t maxi = j;
	size_t left = j * 2 + 1;
	size_t right = j * 2 + 2;

	if (left <= l)  //если есть потомки вообще
	{
		if (a[left] > a[j])
			maxi = left;
		if ((right <= l) && a[right] > a[maxi])
			maxi = right;
		if (maxi != j)
		{
			swap(a[j], a[maxi]);
			HeapPush(a, maxi, l);
		}		
	}

}
template <class T>
void RHeapSort(T* a, int n)
{
	/*построение дерева*/
	for (int i = (n / 2) - 1; i >= 0; i--)
		HeapPush(a, i, n - 1);
		
	/*max в конец*/
	for (size_t i = n - 1; i > 0; i--)
	{
		swap(a[0], a[i]);
		HeapPush(a, 0, i - 1);
	}
}
template <class T>                   //кучей
void HeapSort(T* ar, int n)
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();

	RHeapSort(a,n);

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of HeapSort = " << timer.elapsed() << endl << endl;
}

template <class T>                   //поразрядная
void RankSort(T* ar, int n) {};
template <>                   
void RankSort(int* ar, int n)
{
	/*создание копии для сортировки*/
	int* a = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();

	int k = 8;
	if (a[0] < 10)
		k = 1;
	list<int> pocket [10];
	int ostk, delk; //доп коэф
	int num;
	for (size_t i = k; i > 0; i--)
	{
		ostk = pow(10, k - i + 1);
		delk = pow(10, k - i);
		//распихиваем по карманам
		for (size_t j = 0; j < n; j++)
		{
			num = (a[j] % ostk) / delk;
			pocket[num].push_back(a[j]);
		}
		int listi = 0;
		int j = 0;
		//соед карманы
		while(j < n && listi<10)
		{
			while (!pocket[listi].empty())
			{
				//cout << listi << ":  " << pocket[listi].front() << endl;;
				a[j] = pocket[listi].front();
				pocket[listi].pop_front();
				j++;
			}
			listi++;
		}
	}

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(ar[0]).name() << "),time of RankSort = " << timer.elapsed() << endl << endl;
}
template <>                   
void RankSort(string* ar, int n)
{
	/*создание копии для сортировки*/
	string* a = new string[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();

	int k = 6;
	list <string> pocket[26];
	int num;
	for (size_t i = k; i > 0; i--)
	{
		/*распихиваем по карманам*/
		for (size_t j = 0; j < n; j++)
		{
			num = int((a[j])[i-1]) - 97;
			pocket[num].push_back(a[j]);
		}
		int listi = 0;
		int j = 0;
		/*соед карманы*/
		while (j < n && listi < 26)
		{
			while (!pocket[listi].empty())
			{
				//cout << listi << ":  " << pocket[listi].front() << endl;;
				a[j] = pocket[listi].front();
				pocket[listi].pop_front();
				j++;
			}
			listi++;
		}
	}


	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(ar[0]).name() << "),time of RankSort = " << timer.elapsed() << endl << endl;
}
template <>
void RankSort(Date* ar, int n)
{}


template <class T>                   //встроенная
void CSort(T* ar, int n)
{
	/*создание копии для сортировки*/
	T* a = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		a[i] = ar[i];
	}

	timer.start();

	sort(a,a+n);
	//sort(a, a+n, [](const Date& a, const Date& b) { return b > a; });

	timer.finish();
	//RPrint(a, n);
	cout << "(size,type = " << n << typeid(a[0]).name() << "),time of CSort = " << timer.elapsed() << endl << endl;
}

int main()
{	
	Array <int, 500000> my;
	Array <int, 500000> my1;
	Array <int, 500000> my2;
	//my.Print();


	//BubbleSort(my.GetArray(), my.GetSize());
	//BubbleSort(my1.GetArray(), my1.GetSize());
	//BubbleSort(my2.GetArray(), my2.GetSize());
	//cout << endl;
	BubbleSortCheck(my.GetArray(), my.GetSize());
	BubbleSortCheck(my1.GetArray(), my1.GetSize());
	BubbleSortCheck(my2.GetArray(), my2.GetSize());
	cout << endl;
	//ChoiceSort(my.GetArray(), my.GetSize());
	//ChoiceSort(my1.GetArray(), my1.GetSize());
	//ChoiceSort(my2.GetArray(), my2.GetSize());
	//cout << endl;
	//InsertSort(my.GetArray(), my.GetSize());
	//InsertSort(my1.GetArray(), my1.GetSize());
	//InsertSort(my2.GetArray(), my2.GetSize());
	//cout << endl;
	BrushSort(my.GetArray(), my.GetSize());
	BrushSort(my1.GetArray(), my1.GetSize());
	BrushSort(my2.GetArray(), my2.GetSize()); 
}


