#include <string>
#include <iostream>
#include <vector>
using namespace std;

class BarrelCipher
{
public:
	BarrelCipher(vector<int> &cypherKey, string& myMessage)
	{
		pCypher = &cypherKey;
		string sEncyptedMessage = "";
		encrypt(myMessage, sEncyptedMessage);
		decrypt(sEncyptedMessage, sEncyptedMessage);
	};

private:
	vector<int>* pCypher;
	

	void encrypt(const string& sDecrypted, string& sEncrypted)
	{
		sEncrypted = sDecrypted;
		int keySize = pCypher->size();
		int keyPos = 0;
		for (string::iterator it = sEncrypted.begin(); it != sEncrypted.end(); ++it)
		{
			*it = (char) (*it + pCypher->at( (keyPos++ % keySize) ));
		}

		cout << "Encrypted: " << sEncrypted << endl;
	};

	void decrypt(const string& sEncrypted, string& sDecrypted)
	{
		sDecrypted = sEncrypted;
		int keySize = pCypher->size();
		int keyPos = 0;
		for (string::iterator it = sDecrypted.begin(); it != sDecrypted.end(); ++it)
		{
			*it = (char) (*it - pCypher->at( (keyPos++ % keySize) ));
		}

		cout << "Decrypted: " << sDecrypted << endl;
	};
};



int main()
{
	{
	vector<int> myCipher; myCipher.push_back(1); myCipher.push_back(2); myCipher.push_back(3);
	string myMessage = "hello world";
	BarrelCipher myProblem(myCipher, myMessage);
	}

	vector<int> myCipher; myCipher.push_back(8); myCipher.push_back(2); myCipher.push_back(7); myCipher.push_back(3); myCipher.push_back(9);
	string myMessage = "acm programming practice";
	BarrelCipher myProblem(myCipher, myMessage);
}

