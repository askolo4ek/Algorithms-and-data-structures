#include <iostream>
#include <time.h>
#include <ctime>
using namespace std;

long long n_op = 0;
long finaltime;

class Queue
{
public:
	Queue();
	~Queue();
protected:
	// удаление элемента в очереди
	void pop();

	// добавление элемента в очередь
	void push(int data);

	// очистить очередь
	void clear();

	// вывести очередь на экран
	void ShowAll();

	// проверка очереди на пустоту
	bool isEmpty();

	// получить количество елементов в очереди
	int GetSize() { return Size; }

	class Node
	{
	public:
		Node* pNext;
		int data;
															
		Node(int data = int(), Node* pNext = nullptr)
		{
			this->data = data;								
			this->pNext = pNext;							
		}
	};
	int Size;
	Node* head;
};

Queue::Queue()
{
	Size = 0;												
	head = nullptr;											
}

Queue::~Queue()
{
	clear();
}

void Queue::pop()		//4 операции
{
	Node* temp = head;										n_op++;

	head = head->pNext;										n_op += 2;

	delete temp;

	Size--;													n_op++;
}

void Queue::push(int data)   //11 + 4n операций
{															n_op++;
	if (isEmpty())//2 операция											
	{
		head = new Node(data);
															n_op++;
	}
	else
	{
															n_op += 2;
		Node* current = this->head;
															n_op += 2;
		while (current->pNext != nullptr)
		{
			current = current->pNext;						n_op += 4;
		}
		current->pNext = new Node(data);					n_op += 2;
	}
	Size++;													n_op++;
}


void Queue::clear()
{
	while (Size)
	{
		pop();
	}
}

void Queue::ShowAll()
{
	Node* temp = head;

	while (temp)
	{
		cout << temp->data << endl;
		temp = temp->pNext;
	}
	delete[] temp;
}

bool Queue::isEmpty()
{
																	n_op+=2;
	if (head == nullptr)
		return true;
	else
		return false;
}

class Queue_ch : public Queue
{
public:
	int get(int index);
	void set(int value, int index);
	void pop_ch();
	void push_ch(int value);
	void clear_ch();
	int GetSize_ch();
	bool isEmpty_ch();
	void sort();
	void ShowAll_ch();
};

void Queue_ch::clear_ch()
{
	this->clear();
}

int Queue_ch::get(int index) //7 + (22 + 4n)n + (22 + 4n)n = 7 + 44n + 8n^2
{
	int temp;
	int value;
																	n_op += 2;
	for (int i = 0; i < index; i++)                                 
	{
		temp = this->head->data;									n_op += 5;
		
		push_ch(temp); //4n + 11 операций
		pop_ch(); //5 операций
	}
	value = this->head->data;										n_op += 3;
																	n_op += 2;
	for (int i = index; i < GetSize_ch(); i++)						
	{
		temp = this->head->data;									n_op += 5;

		push_ch(temp);//4n + 11 операций
		pop_ch();//5 операций
	}																n_op++;
	return(value);
}

void Queue_ch::set(int value, int index)//7 + (22 + 4n)n + (22 + 4n)n = 7 + 44n + 8n^2
{
	int temp;
																	n_op += 2;
	for (int i = 0; i < index; i++)
	{
		temp = this->head->data;									n_op += 5;
		push_ch(temp);//4n + 11 операций												
		pop_ch();//5 операций
	}
	this->head->data = value;										n_op += 3;
																	n_op += 2;
	for (int i = index; i < GetSize_ch(); i++)
	{
		temp = this->head->data;									n_op += 5;
																	
		push_ch(temp);//4n + 11 операций
		pop_ch();//5 операций
	}
}

void Queue_ch::pop_ch()
{
																	n_op++;
	this->pop();
}

void Queue_ch::push_ch(int value)
{
																	n_op++;
	this->push(value);
}

int Queue_ch::GetSize_ch()
{
													
	return this->GetSize();
}

bool Queue_ch::isEmpty_ch()
{
																	n_op++;
	return this->isEmpty();
}

void Queue_ch::ShowAll_ch()
{
	this->ShowAll();
}

void Queue_ch::sort()		//4 + n(7 + 44n + 8n^2 + 4 + 7 + 44n + 8n^2 + 7 + 44n + 8n^2)
{
	clock_t t = clock();
	int min;
	int min_id;

	if (isEmpty_ch())		//3 операции											
	{
		cout << "Нечего сортировать!" << endl;					n_op++;
	}	
	else
	{
																n_op += 2;
		for (int i = 0; i < GetSize_ch(); i++)
		{
			min = get(i);	/* 7 + 44n + 8n^2*/					n_op++;

			min_id = i;                                         n_op++;
																n_op += 2;
			for (int j = i; j < GetSize_ch(); j++)
			{
				/* 7 + 44n + 8n^2*/								n_op++;
				if (get(j) < min)
				{
					min = get(j);/* 7 + 44n + 8n^2*/            n_op++;

					min_id = j;                                 n_op++;
				}												n_op += 2;
			}
			set(get(i), min_id); //7 + 44n + 8n^2
			set(min, i); //7 + 44n + 8n ^ 2
		}
	}

	finaltime = clock() - t;
}

int main()
{
	setlocale(LC_ALL, "ru");

	Queue_ch* q = new Queue_ch;

	int n=50;



	/*
	cout << "Введите количество членов в очереди: ";
	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		q->push_ch(n - i);
	}
	*/
	
	for (int j = 50; j <= n; j += 50, n += 50)
	{
		for (int i = 0; i < n; i++)
		{
			q->push_ch(rand());
		}
		q->sort();
		cout << "n = " << n << " Время: " << finaltime << endl;
		q->clear_ch();
		n_op = 0;
		if (n == 500) break;
	}
	
	/*
	//cout << "-------------------------" << endl << q->GetSize_ch() << endl;
	q->sort();
	cout << "Прошла сортировка." << endl << "_________________________" << endl;

	q->ShowAll_ch();

	cout << "Время: " << finaltime << " mc." <<endl;

	system("pause");

	q->clear_ch();*/
	return 0;
}