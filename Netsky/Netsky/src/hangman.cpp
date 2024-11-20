#include <iostream>
#include <cstring> 
#include <cstdlib> 
#include <vector>

using namespace std;

int HangMan()
{

    vector<int> FoundLetters;
    int FoundCount = 0;



    const string wordList[4] = { "centimeter",
        "digit", "radius", "percent" };

    string ChosenWord = wordList[rand() % 4]; // choosing a word from the wordlist 
    cout << ChosenWord << endl;

    cout << ChosenWord.size() << endl;
    int lives = 5;



    do
    {

        FoundCount = 0; // reset before searching word



        for (int i = 0; i < ChosenWord.length(); ++i)
        {

            // if the vector contrains this characters index
            if (find(FoundLetters.begin(), FoundLetters.end(), i) != FoundLetters.end())
            {
                // it has been found
                cout << ChosenWord[i] << " "; // so print the char
                FoundCount++;// and add one to the count
            }
            else
            {
                // it hasn't been found
                cout << "_ ";
            }
        }



        cout << "You have " << lives << " lives left" << endl;

        char guess = ' ';
        bool found = false;
        cout << "Guess a letter: " << endl;
        cin >> guess;
        for (int i = 0; i < ChosenWord.length(); i++)
        {
            // if the users choice is valid
            if (guess == ChosenWord[i])
            {
                found = true;
                // log its index in our vector

                FoundLetters.push_back(i);

            }


        }
        if (found != true) {
            lives--;
        }



    } while (FoundCount < (ChosenWord.size() - 1) && lives != 0);
    if (lives != 0)
    {
        cout << "Congrats you found the word!" << endl;
    }
    else {
        cout << "game over" << endl;
        cout << "The correct answer is: " << ChosenWord << endl;
    }








    return 0;

}