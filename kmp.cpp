#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;


//used struct to save the id and the failure link for that id, could have directly used an array without building a struct
struct flrLink
{
    int id;
    int FL;
};

//Function to build the failure link associated to given id
//used const char because while calling in the main will be directly giving the string won't be taking it from somewhere
int* buildFailureLinks(const char* pat, int n)
{
    flrLink* patFL = new flrLink[n];
    int* failure = new int[n];

    //builds ids for each index
    for(int i = 0; i <= n; i++)
    {
        patFL[i].id = i;
        //cout<<patFL[i].id<<" ";
    }
    // initializing the null value that will be returned to if no match between the prefix and suffix of a string (has to failure link to return to)
    patFL[0].FL = -1;
    // initializing the first character to go to node 0 as the FL because first character has no possible proper suffixes to choose from
    patFL[1].FL = 0;


    int i = 0;
    int j = 1;

    //loops till the variable starting from 1 is equal to the size, breaks of the loop then and doesn't continue in it
    while(j < n)
    {
        /*since we can't take the whole prefix and only can start without the first character at least
          we will be going through with a variable from the start of the prefix and another from the start+1*/

        //if a match occurs, then both i and j will be incremented to check on the rest of the pattern
        //we have already initialized 0 and 1 failure links,0 = -1 and 1 = 0, so this will start from index 2(second letter)
        if(pat[j] == pat[i])
        {
            i++;
            j++;
            //we add the j+1 because we have a null value(-1) in the first index and we want it to refer to the next ones and ignoring it
            //we have the pattern size = n-1 while the array of struct is n, so we need to shift the values in the array of struct
            patFL[j].FL = i;

        }
        //if no match
        else
        {
            if(i != 0)
            {
                //will make the i start at the failure link of the current index and check again if it equals to the letter j
                i = patFL[i].FL;
            }
            else
            {
                /*will enter this case if no match at the start of the prefix and the proper suffix till the current index.
                  failure link will be equal to 0*/
                j++;
                patFL[j].FL = 0;

            }
        }
    }

    // used to copy the failure links from the struct in an array alone to be returned later
    for(int i = 0; i < n; i++)
    {
        failure[i] = patFL[i].FL;
        //cout<<failure[i]<<" ";
    }
    delete [] patFL;
    //delete[] pat;

    return failure;
}

//Function to search for a pattern in a given text
void searchInText(const char* text, const char* pattern, int* failure, int nP, int nT)
{
    int i = 0;
    int j = 0;
    //prints the initial comparison which is the first letter in both the pattern and the text
    cout<< "t(" << i<< ")" << "p(" << j << ")" << endl;
    //loops till it is the end of the text
    //added the = to make sure we get the last failure link(0 index) before we break from the loop
    while(i <= nT)
    {
        //checks if the letters(characters) are equal
        if(text[i] == pattern[j])
        {
            /*increments both as long as it is not the end of the pattern
              we need to make sure that it goes back to the failure link of the index if it is at the end(j=length of the pattern)
              to be used during next iterations along the searching for another occurrence in the text */
            if(j < nP)
            {
                i++;
                j++;
            }
            else
            {
                j = failure[j];
            }
        }
        //if patterns not match
        else
        {
            //as long as j is not equal zero we will keep getting the failure link for it
            if(j != 0)
            {
                j = failure[j];
            }
            //if j=0 then we can't get anymore failure links and we will have to move forward with the pattern
            else
            {
                i++;
            }
        }
        //we don't want it to print t more than the length of the text
        if (i == nT + 1) break;

        //prints the letters that are being compared
        cout<< "t(" << i << ")" << "p(" << j << ")";

        //reports the index at which the match happened(current text index- pattern index)
        if(j == nP)
        {
            cout<< " Rep(" << i-j << ")";
        }
        cout<<endl;
    }
    /*if(i== nT && j>0)
    {
        j=failure[j];
        cout<< "t("<<i<<")"<<"p("<<j<<")";
    }*/
    //delete [] text;
    //delete [] pattern;

}

int main()
{
    //int* failure= buildFailureLinks("AGGAAGA", 8);
    //TEXT = {"AAGAGAGAGGAAGAGGAAGA"}

    //const char because we give it not taking from the user or from an operation
    const char* pattern = {"AGAAGAG"};
    //gets the failure link for the pattern
    int* failure= buildFailureLinks(pattern, 8);
    /*for(int i = 1; i<8; i++) //starts from 1 to ignore printing the null(-1) value
    {
        cout << failure[i] <<" ";
    }
    cout<<endl;*/

    //gives the text
    const char* text = {"AGAGAAGAGGAGAAGAGAAGAGA"};
    /*compares the text and pattern and outputs inside the function which characters are being compared
    and when a full match between the pattern and the text(pattern found in the text)*/
    searchInText(text, pattern, failure, 7, 23);

    delete [] pattern;
    delete [] text;
    delete [] failure;

    return 0;
}
