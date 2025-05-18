#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 2000;
const int P = 31;

struct Company 
{
    string name;
    string profit_tax;
    string address;
};

struct HashTable 
{
    vector<Company> table[TABLE_SIZE];
};

vector<Company> readCompanyList(string file_name) 
{
    vector<Company> result;
    ifstream fin(file_name);
    if (!fin.is_open()) 
    {
        cerr << "Cannot open file: " << file_name << endl;
        return result;
    }

    string line;
    getline(fin, line); 

    while (getline(fin, line)) 
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) continue;

        Company c;
        c.name = line.substr(0, pos1);
        c.profit_tax = line.substr(pos1 + 1, pos2 - pos1 - 1);
        c.address = line.substr(pos2 + 1);

        result.push_back(c);
    }

    fin.close();
    return result;
}

long long hashString(const string& company_name) 
{
    string s = company_name;
    if (s.length() > 20)
        s = s.substr(s.length() - 20);

    long long hash = 0;
    long long p_pow = 1;

    for (int i = 0; i < s.length(); ++i) 
    {
        hash = (hash + (long long)(s[i]) * p_pow) % TABLE_SIZE;
        p_pow = (p_pow * P) % TABLE_SIZE;
    }
    return hash;
}

HashTable* createHashTable(const vector<Company>& list_company) 
{
    HashTable* ht = new HashTable;
    for (const Company& c : list_company) 
    {
        long long index = hashString(c.name);
        ht->table[index].push_back(c);
    }
    return ht;
}

Company* search(HashTable* ht, const string& name)
{
    long long index = hashString(name);
    for (size_t i = 0; i < ht->table[index].size(); ++i)
    {
        if (ht->table[index][i].name == name)
            return &ht->table[index][i];
    }
    return nullptr;
}

int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        cerr << "Usage: ./main MST.txt input.txt output.txt\n";
        return 1;
    }

    string mstFile = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    vector<Company> companies = readCompanyList(mstFile);
    HashTable* ht = createHashTable(companies);

    ifstream fin(inputFile);
    ofstream fout(outputFile);

    if (!fin.is_open()) 
    {
        cerr << "Cannot open input file: " << inputFile << endl;
        return 1;
    }

    if (!fout.is_open()) 
    {
        cerr << "Cannot open output file: " << outputFile << endl;
        return 1;
    }

    string company_name;
    while (getline(fin, company_name)) 
    {
        if (company_name.empty()) continue;

        Company* found = search(ht, company_name);
        if (found != nullptr) 
        {
            fout << found->name << " " << found->profit_tax << " " << found->address << "\n";
        }
    }

    fin.close();
    fout.close();
    delete ht;

    return 0;
}
