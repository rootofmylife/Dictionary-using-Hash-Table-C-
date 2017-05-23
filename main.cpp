#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>

using namespace std;

const int TABLE_SIZE = 128;

class HashNode {
private:
    string value;
    string key;
    HashNode *pNext;
public:
    HashNode(string key, string value) {
        this->key = key;
        this->value = value;
        this->pNext = NULL;
    }

    string getKey() {
        return key;
    }

    string getValue() {
        return value;
    }

    HashNode* getNext(){
        return pNext;
    }

    void setNext(HashNode* p) {
        this->pNext = p;
    }
};

class Hashmap {
private:
    HashNode **table;
public:
    Hashmap() {
        table = new HashNode*[TABLE_SIZE];
        for(int i = 0; i < 128; i++) {
            table[i] = NULL;
        }
    }

    ~Hashmap() {
        for(int i = 0; i < TABLE_SIZE; i++) {
            HashNode* entry = table[i];
            while(entry != NULL) {
                HashNode* p = entry;
                entry = entry->getNext();
                delete p;
            }
        }
        delete[] table;
    }

    int createHash(string key) {
        long sum = 0;
        long len = key.length();
        for(int i = 0; i < len; i++){
            long temp = (int)key[i] * pow(128 * 1.0, len * 1.0);
            sum += temp % TABLE_SIZE;
            len--;
        }
        return sum;
    }

    void Insert(string key, string value) {
        int hash = createHash(key);
        if(table[hash] == NULL) {
            table[hash] = new HashNode(key, value);
        }
        else {
            HashNode* entry = table[hash];
            while(entry->getNext() != NULL) {
                entry = entry->getNext();
            }
            entry->setNext(new HashNode(key, value));
        }
    }

    string Search(string key) {
        int hash = createHash(key);
        if(table[hash] == NULL) {
            return "Not found";
        }
        else {
            HashNode* entry = table[hash];
            while(entry != NULL && entry->getKey() != key) {
                entry = entry->getNext();
            }
            if(entry == NULL) {
                return "Not found";
            }
            return entry->getValue();
        }
    }
};

int main()
{
    Hashmap a;
    ifstream file("test.dat", ios_base::in);
    while(!file.eof()) {
        string str;
        getline(file, str);

        string key = "", val = "";
        int vt = -1;
        for(unsigned int i = 0; i < str.length(); i++) {
            if(str[i] == ':'){
                vt = i + 1;
                break;
            }
            key += str[i];
        }

        for(unsigned int i = vt; i < str.length(); i++){
            val += str[i];
        }
        a.Insert(key, val);
    }

    string sea;
    cout << "Find word(s): ";
    getline(cin, sea);
    cout << a.Search(sea);

    file.close();

    return 0;
}
