#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Company
{
	string name;
	string profit_tax;
	string address;
};

struct HashTable
{
	vector<Company> companyHashTable;

	HashTable() 
	{
		companyHashTable.resize(2000);
	}
};

vector<Company> readCompanyList(string file_name)
{
	vector<Company> companyList;
	ifstream getInfo(file_name);
	string tmpRead;
	getline(getInfo, tmpRead);
	while (getline(getInfo, tmpRead))
	{
		stringstream split(tmpRead);
		Company tmpAdd;
		getline(split, tmpAdd.name, '|');
		getline(split, tmpAdd.profit_tax, '|');
		getline(split, tmpAdd.address);
		companyList.push_back(tmpAdd);
	}
	getInfo.close();
	return companyList;
}

long long hashString(string company_name)
{
	int i = 0, len = (int)company_name.length();
	long long res = 0, pow = 1;
	for (; i < len && i < 20; i++)
	{
		int pos = i;
		if (len >= 20) pos = i + len - 20;
		res += (int)(company_name[pos]) * (pow);
		res %= 2000;
		pow *= 31; pow %= 2000;
	}
	return res % 2000;
}

void insert(HashTable* hash_table, Company company)
{
	long long pos = hashString(company.name);
	while (!hash_table->companyHashTable[pos].name.empty())
	{
		++pos;
		pos %= 2000;
	}
	hash_table->companyHashTable[pos] = company;
}

HashTable* createHashTable(vector<Company> list_company)
{
	HashTable* newHTB = new HashTable;
	for (int i = 0; i < list_company.size(); i++)
	{
		insert(newHTB, list_company[i]);
	}
	return newHTB;
}

Company* search(HashTable* hash_table, string company_name)
{
	long long pos = hashString(company_name);
	while (hash_table->companyHashTable[pos].name != company_name && !hash_table->companyHashTable[pos].name.empty())
	{
		++pos;
		pos %= 2000;
	}
	if (hash_table->companyHashTable[pos].name.empty()) return NULL;
	return &hash_table->companyHashTable[pos];
}

void printCompany(Company cpn, ostream& os)
{
	os << cpn.name << '|' << cpn.profit_tax << '|' << cpn.address << endl;
}

int main(int argc, char* argv[])
{
	ifstream getCpn(argv[2]);
	ofstream printRes(argv[3]);

	vector<Company> cmpList = readCompanyList(argv[1]);
	HashTable* hashTable = createHashTable(cmpList);
	string tmpCompany;
	while (getline(getCpn, tmpCompany))
	{
		Company* findCompany = search(hashTable, tmpCompany);
		if (findCompany)
		{
			printCompany(*findCompany, printRes);
		}
	}

	getCpn.close();
	printRes.close();
}