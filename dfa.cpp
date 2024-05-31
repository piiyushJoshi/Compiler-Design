//To implement the following DFA: (a +b)* . a

#include <iostream>
#include <string>

using namespace std;

class DFA{
private:
    enum State { Q0, Q1 };
    State currentState;

public:
    DFA(){
        currentState = Q0;
    }
    void transition(char input){
        switch(currentState){
            case Q0:
                if(input == 'a')
                    currentState = Q1;
                else if(input == 'b')
                    currentState = Q1;
                break;
            case Q1:
                if(input == 'a')
                    currentState = Q1;
                else if(input == 'b')
                    currentState = Q0;
                break;
        }
    }
    bool isAccepted(){
        return currentState == Q1;
    }
};
int main(){
    DFA dfa;
    string input;
    cout << "Enter a string: ";
    cin >> input;
    for(char c : input)
        dfa.transition(c);

    if(dfa.isAccepted())
        cout << "Accepted" << endl;
    else
        cout << "Rejected" << endl;

    return 0;
}
