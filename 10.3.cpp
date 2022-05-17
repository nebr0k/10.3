#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;
struct Sluzbuvets
{
	string LastName;
	string Initials;
	string Posada;
	int Year;
	int Fee;
};
Sluzbuvets Parse(string str);
Sluzbuvets* addroutetolis(Sluzbuvets* arr, int& size, Sluzbuvets obj);
void Create();
void AutoCreate();
void StartMenu();
void Print();
void Add();
void Remove();
void Change();
void Find();
void Sort();
void savetofile(Sluzbuvets* arr, int size, string filename);
void main()
{
	StartMenu();
	system("pause");
}
void StartMenu()
{
	int ch;
	do
	{
		{
			cout << "-------Menu------" << endl;
			cout << "1.Create list" << endl;
			cout << "2.Print list" << endl;
			cout << "3.Add" << endl;
			cout << "4.Remove" << endl;
			cout << "5.Change" << endl;
			cout << "6.Sort" << endl;
			cout << "7.Search" << endl;
			cout << "8.Clear screen" << endl;
			cout << "10.Exit" << endl;
			cout << "-------------------" << endl;
		}
		cout << "Enter you choice: "; cin >> ch;
		switch (ch)
		{
		case 1:
		{
			AutoCreate();
			break;
		}
		case 2:
		{
			Print();
			break;
		}
		case 3:
		{
			Add();
			break;
		}
		case 4:
		{
			Remove();
			break;
		}
		case 5:
		{
			Change();
			break;
		}
		case 6:
		{
			Sort();
			break;
		}
		case 7:
		{
			Find();
			break;
		}
		case 8:
		{
			system("cls");
			break;
		}
		default:
			break;
		}
	} while (ch <= 9);
}

void Create()
{
	int size = 0;
	cout << "Enter filename:";
	string filename;
	cin >> filename;
	cout << "Enter count:"; cin >> size;
	ofstream fout(filename);
	for (size_t i = 0; i < size; i++)
	{
		Sluzbuvets sl;
		cout << "Last name: "; cin >> sl.LastName;
		cout << "Initials: "; cin >> sl.Initials;
		cout << "Posada: "; cin >> sl.Posada;
		cout << "Year: "; cin >> sl.Year;
		cout << "Fee: "; cin >> sl.Fee;
		fout << sl.Initials + "^" + sl.LastName + "^" + sl.Posada + "^" + to_string(sl.Fee) + "^" + to_string(sl.Year) << endl;
	}
	fout.close();
}
void AutoCreate()
{
	string InitialVector[] = { "O.I","T.K","L.Y","M.O","J.D","X,Y","O.E","A.I","L.I","K.E","V.V","I.V","A.B","C.D" };
	string LastNames[] = { "Smith","Johnson","Williams","Brown","Jones","Davis","Miller","Wilson","Moore","Taylor","Anderson","Thomas" };
	string posada[] = { "Event-manager","HR ","Brand-manager","PM","Architect","System Admin","TeamLead","Trainee","Junior ","Frontend Dev" };
	int size;
	string filename;
	cout << "Filename:"; cin >> filename;
	cout << "Count:"; cin >> size;
	ofstream fout(filename);
	for (size_t i = 0; i < size; i++)
	{
		Sluzbuvets sl;
		sl.Initials = InitialVector[rand() % 14];
		sl.LastName = LastNames[rand() % 12];
		sl.Fee = (2000 + rand() % 2000); sl.Fee -= (sl.Fee % 100);
		sl.Posada = posada[rand() % 10];
		sl.Year = 2000 + rand() % 15;
		fout << sl.Initials + "^" + sl.LastName + "^" + sl.Posada + "^" + to_string(sl.Fee) + "^" + to_string(sl.Year) << endl;

	}
}
Sluzbuvets Parse(string str)
{
	Sluzbuvets sl;
	sl.Initials = str.substr(0, str.find_first_of("^"));
	str.erase(0, str.find_first_of("^") + 1);
	sl.LastName = str.substr(0, str.find_first_of("^"));
	str.erase(0, str.find_first_of("^") + 1);
	sl.Posada = str.substr(0, str.find_first_of("^"));
	str.erase(0, str.find_first_of("^") + 1);
	string oklad = str.substr(0, str.find_first_of("^"));
	sl.Fee = atoi(oklad.c_str());
	str.erase(0, str.find_first_of("^") + 1);
	sl.Year = atoi(str.c_str());
	return sl;
}
void Print()
{
	cout << "Filename:"; string filename;
	cin >> filename;
	ifstream fin(filename);
	string str;
	int i = 0;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "N\t|Last Name     |Initials|Posada        |Fee\t|Year\t|" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	while (getline(fin, str))
	{
		Sluzbuvets sl = Parse(str);
		cout << i << "\t|";
		cout << sl.LastName << setw(15 - sl.LastName.size()) << "|";
		cout << sl.Initials << "\t|";
		cout << sl.Posada << setw(15 - sl.Posada.size()) << "|";
		cout << sl.Fee << "\t|";
		cout << sl.Year << "\t|";
		cout << endl;
		i++;
	}
	cout << "------------------------------------------------------------------" << endl;
}
void Add()
{
	string filename;
	cout << "Filename: ";
	cin >> filename;
	ofstream fout(filename, ios::app);
	Sluzbuvets sl;
	cout << "Last name: "; cin >> sl.LastName;
	cout << "Initials: "; cin >> sl.Initials;
	cout << "Posada: "; cin >> sl.Posada;
	cout << "Year: "; cin >> sl.Year;
	cout << "Fee: "; cin >> sl.Fee;
	fout << sl.Initials + "^" + sl.LastName + "^" + sl.Posada + "^" + to_string(sl.Fee) + "^" + to_string(sl.Year) << endl;
	fout.close();
}
void Remove()
{
	string filename;
	cout << "Filename:"; cin >> filename;
	ifstream fin;
	fin.open(filename);
	Sluzbuvets* sls = new Sluzbuvets[0];
	int size = 0;
	string str;
	while (getline(fin, str))
	{
		sls = addroutetolis(sls, size, Parse(str));
	}
	Sluzbuvets* nsls = new Sluzbuvets[size];
	cout << "Enter the index of a marchroot which you want to remove: ";
	int index;
	cin >> index;
	bool moved = false;
	for (size_t i = 0; i < size - 1; i++)
	{
		if (i == index)  	moved = true;
		if (moved)	nsls[i] = sls[i + 1];
		else	nsls[i] = sls[i];
	}
	--size;
	savetofile(nsls, size, filename);
}
void savetofile(Sluzbuvets* arr, int size, string filename)
{
	ofstream fout(filename);
	for (size_t i = 0; i < size; i++)
	{
		Sluzbuvets sl = arr[i];
		fout << sl.Initials + "^" + sl.LastName + "^" + sl.Posada + "^" + to_string(sl.Fee) + "^" + to_string(sl.Year) << endl;
	}
	fout.close();
}
void Change()
{
	Sluzbuvets* arr = new Sluzbuvets[0];
	int size = 0;
	string filename;
	cout << "Filename:"; cin >> filename;
	ifstream fin(filename);
	string str;
	while (getline(fin, str))
	{
		arr = addroutetolis(arr, size, Parse(str));
	}
	fin.close();
	cout << "Enter the index of a worker which you want to change: ";
	int index = 0; cin >> index;
	if (index < size)
	{
		cout << "-----------------------------------------------------------------" << endl;
		cout << "N\t|Last Name     |Initials|Posada        |Fee\t|Year\t|" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << index << "\t|";
		cout << arr[index].LastName << setw(15 - arr[index].LastName.size()) << "|";
		cout << arr[index].Initials << "\t|";
		cout << arr[index].Posada << setw(15 - arr[index].Posada.size()) << "|";
		cout << arr[index].Fee << "\t|";
		cout << arr[index].Year << "\t|";
		cout << endl;
		cout << "------------------------------------------------------------------" << endl;
		Sluzbuvets sl;
		cout << "Last name: "; cin >> sl.LastName;
		cout << "Initials: "; cin >> sl.Initials;
		cout << "Posada: "; cin >> sl.Posada;
		cout << "Year: "; cin >> sl.Year;
		cout << "Fee: "; cin >> sl.Fee;
		arr[index] = sl;
	}
	else cout << "There is no worker with the number " << index << endl;
	savetofile(arr, size, filename);
}

void Find()
{
	string filename;
	cout << "Filename:"; cin >> filename;
	ifstream fin(filename);
	string str;
	cout << "Last name ofa worker which u want to find: ";
	string ln; cin >> ln;
	int index = -1;
	Sluzbuvets sl;
	int i = -1;
	while (getline(fin, str))
	{
		Sluzbuvets tmp;
		tmp = Parse(str);
		if (tmp.LastName == ln)
		{
			index = i;
			sl = tmp;
			break;
		}
		i++;
	}
	if (index != -1)
	{
		cout << "-----------------------------------------------------------------" << endl;
		cout << "N\t|Last Name     |Initials|Posada        |Fee\t|Year\t|" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << index << "\t|";
		cout << sl.LastName << setw(15 - sl.LastName.size()) << "|";
		cout << sl.Initials << "\t|";
		cout << sl.Posada << setw(15 - sl.Posada.size()) << "|";
		cout << sl.Fee << "\t|";
		cout << sl.Year << "\t|";
		cout << endl;
		cout << "------------------------------------------------------------------" << endl;

	}
	else
	{
		cout << "Sorry but the worker with last name " << ln << "doe not exist in this company." << endl;
	}
}


void Sort()
{
	string filename;
	cout << "Filename:"; cin >> filename;
	ifstream fin;
	fin.open(filename);
	Sluzbuvets* arr = new Sluzbuvets[0];
	int size = 0;
	string str;
	while (getline(fin, str))
	{
		arr = addroutetolis(arr, size, Parse(str));
	}
	fin.close();
	//	size += 1;
	system("cls");
	cout << "---------- Sort -----------" << endl;
	cout << "1.Sort by Last name" << endl;
	cout << "2.Sort by fee" << endl;
	cout << "3.Sort by year" << endl;
	cout << "4.Exit" << endl;
	cout << "---------------------------" << endl;
	cout << "Your choice:"; int choice; cin >> choice;
	switch (choice)
	{
	case 1:
	{
		for (size_t i = 0; i < size - 1; i++)
			for (size_t j = 0; j < size - i - 1; j++)
				if (arr[j].LastName > arr[j + 1].LastName)
					swap(arr[j], arr[j + 1]);
		break;
	}
	case 2:
	{
		for (size_t i = 0; i < size - 1; i++)
			for (size_t j = 0; j < size - i - 1; j++)
				if (arr[j].Fee < arr[j + 1].Fee)
					swap(arr[j], arr[j + 1]);
		break;
	}
	case 3:
	{
		for (size_t i = 0; i < size - 1; i++)
			for (size_t j = 0; j < size - i - 1; j++)
				if (arr[j].Year < arr[j + 1].Year)
					swap(arr[j], arr[j + 1]);
		break;
	}
	default:
		return;
	}
	savetofile(arr, size, filename);
}


Sluzbuvets* addroutetolis(Sluzbuvets* arr, int& size, Sluzbuvets obj)
{
	Sluzbuvets* arr2 = new Sluzbuvets[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		arr2[i] = arr[i];
	}
	arr2[size] = obj;
	size++;
	return arr2;
}
