//
//  acm_practice_quickChange.cpp
//  acm_practice_quickChange
//
//  Created by Andrew Blackton on 8/31/13.
//

#include <iostream>
using namespace std;

class CalculateChange
{
public:
    CalculateChange(int nInitRoundNum, int nInitCents) :
        nRoundNum(nInitRoundNum), nCents(nInitCents), nQuarters(0), nDimes(0), nNickels(0), nPennys(0)
    {
        quickCalculate();
        printResults();
    }
    
    void quickCalculate()
    {
        nQuarters = nCents/25;
        nCents -= nQuarters*25;
        
        nDimes = nCents/10;
        nCents -= nDimes*10;
        
        nNickels = nCents/5;
        nCents -= nNickels*5;
        
        nPennys = nCents;
    }
    
    void printResults() const
    {
        cout << nRoundNum << " " << nQuarters << " QUARTER(S), " << nDimes << " DIME(S), "
            << nNickels << " NICKEL(S), " << nPennys << " PENNY(S)" << endl;
    }
private:
    int nRoundNum;
    int nCents;
    int nQuarters;
    int nDimes;
    int nNickels;
    int nPennys;
    
};

int main(int argc, const char * argv[])
{
    int nDatasets;
    int nChangeGiven;
    cin >> nDatasets;
    
    for (int i = 0; i < nDatasets; ++i)
    {
        cin >> nChangeGiven;
        CalculateChange dataset(i+1, nChangeGiven);
    }
    
    return 0;
}

