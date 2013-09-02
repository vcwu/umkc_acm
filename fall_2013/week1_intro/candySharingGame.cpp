//
//  acm_practice_CandySharingGame.cpp
//  acm_practice_CandySharingGame
//
//  Created by Andrew Blackton on 8/31/13.
//

#include <iostream>
using namespace std;

class Problem
{
public:
    Problem(const int nInitStudentCount, int* pInitStudentHas) :
        pStudentHas(pInitStudentHas), nStudentCout(nInitStudentCount), nRounds(0), bIsFinished(false)
    {
        pStudentGives = new int[nStudentCout];
        while (!bIsFinished)
        {
            ++nRounds;
            distribute();
        }
        
        printResults();
    }
    
    ~Problem()
    {
        delete [] pStudentHas;
        delete [] pStudentGives;
    }
    
    void distribute()
    {
        for (int i = 0; i < nStudentCout; ++i)
        {
            int nGive = pStudentHas[i]/2;
            pStudentHas[i] -= nGive;
            pStudentGives[i] = nGive;
        }
        
        bIsFinished = true;
        int nAreAllEqualTo;
        
        for (int i = 0; i < nStudentCout; ++i)
        {
            pStudentHas[i] += pStudentGives[((i+1) % nStudentCout)];
            if (pStudentHas[i]%2 == 1)
            {
                ++pStudentHas[i];
            }
            
            if (i == 0)
                nAreAllEqualTo = pStudentHas[i];
            else if (pStudentHas[i] != nAreAllEqualTo)
                bIsFinished = false;
        }
    }
    
    void printResults()
    {
        cout << nRounds << " " << pStudentHas[0] << endl;
    }
    
private:
    bool bIsFinished;
    int nStudentCout;
    int nRounds;
    int *pStudentHas;
    int *pStudentGives;
};


int main(int argc, const char * argv[])
{
    int nStudentCount = 0;
    int *pStudentHas;
    do
    {
        cin >> nStudentCount;
        if (nStudentCount == 0) break;
        pStudentHas = new int[nStudentCount];
        for (int i = 0; i < nStudentCount; ++i)
        {
            cin >> pStudentHas[i];
        }
        Problem newProblem(nStudentCount, pStudentHas);
    }
    while (true);
    return 0;
}


