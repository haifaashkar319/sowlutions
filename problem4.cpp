#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isValid(string s) {
        stack<char> st;  //taking stack for keep tracking the order of the brackets..
        for(auto i:s)  
        {
            if(i=='(' or i=='{' or i=='[') st.push(i);  //if current element of the string will be opening bracket then we will just simply push it into the stack
            else  //if current element is a closing bracket, check two conditions  current element matches with top of the stack and the stack must not be empty...
            {
                if(st.empty() or (st.top()=='(' and i!=')') or (st.top()=='{' and i!='}') or (st.top()=='[' and i!=']')) return false;
                st.pop();  //if control reaches to that line, it means we have got the right pair of brackets, so just pop it.
            }
        }
        return st.empty();  }

    int main(){
        string s="{([]}}}";
        cout<<isValid(s);
    }