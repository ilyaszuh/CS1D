#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int main()
{
    ifstream inFile("browser.txt");
    ofstream oFile("output.txt");
    stack<int> forwardStack;
    stack<int> backwardStack;
    int input = 0;
    int curr = 0;

    while(!inFile.eof())
    {
        inFile >> input;
        switch(input)
        {
            case 9999:
                if(backwardStack.empty())
                {
                    oFile << "9999 - backward stack empty\n";
                }
                else
                {
                    forwardStack.push(curr);
                    curr = backwardStack.top();
                    backwardStack.pop();
                    oFile << "9999 - " << curr << endl;
                }
                break;
            case 9998:
                if(forwardStack.empty())
                {
                    oFile << "9998 - forward stack empty\n";
                }
                else
                {
                    backwardStack.push(curr);
                    curr = forwardStack.top();
                    forwardStack.pop();
                    oFile << "9998 - " << curr << endl;
                }
                break;
            default:
                backwardStack.push(curr);
                curr = input;
                oFile << input << " - " << curr << endl;
        }
    }

    oFile.close();
    inFile.close();
    return 0;
}
