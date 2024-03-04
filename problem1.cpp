#include <iostream>
#include <string>
using namespace std;


//the code below works in O(n) time 
// first we check for edge cases and max length

bool validateEmail(string s)
{
    int found = 0;
    //to count the number of @
    bool found_dot=false;
    if (s.empty())
    {
        return false;
    }
    if (s.size() > 256)
    {
        return false;
    }

    else
    {
        if (s[0] == '@' || s[s.size() - 1] == '@')
        {
            return false;
        }
        for (int i = 1; i < s.size() - 1; i++)
        {
            if (found >1){
                return false;
                //returns false for more than 1 @
            }

            if (s[i] == '@')
            {
                found ++;
                
                if (s[i + 1] == '.' || s[i - 1] == '.')
                {
                    return false;
                    //returns false for .@ and @.
                }
            }
            if (found==1)
            {
                if (s[i] == '.')
                {
                    found_dot=true;
                    //checks for dot after @
                }
            }
        
        }
        return (found==1 && found_dot);
    }
}

int main()
{
        cout << validateEmail("john.doe@gmail.com")<<endl;
        cout << validateEmail("john@doe@gmail.com")<<endl;
        cout << validateEmail("john@gmail.c")<<endl;
        //i dont get why this test case should return false 
        cout << validateEmail("john@.com")<<endl;
        

    return 0;
}