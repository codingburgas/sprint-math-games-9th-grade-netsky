//#include <iostream>
//#include <cstring> 
//#include <cstdlib> 
//#include <vector>
//
//using namespace std;
//
//int hangman()
//{
//
//    vector<int> foundletters;
//    int foundcount = 0;

//
//
//    const string wordlist[4] = { "centimeter",
//        "digit", "radius", "percent" };
//
//    string chosenword = wordlist[rand() % 4]; // choosing a word from the wordlist 
//    cout << chosenword << endl;
//
//    cout << chosenword.size() << endl;
//    int lives = 5;
//
//
//
//    do
//    {
//
//        foundcount = 0; // reset before searching word
//
//
//
//        for (int i = 0; i < chosenword.length(); ++i)
//        {
//
//            // if the vector contrains this characters index
//            if (find(foundletters.begin(), foundletters.end(), i) != foundletters.end())
//            {
//                // it has been found
//                cout << chosenword[i] << " "; // so print the char
//                foundcount++;// and add one to the count
//            }
//            else
//            {
//                // it hasn't been found
//                cout << "_ ";
//            }
//        }
//
//
//
//        cout << "you have " << lives << " lives left" << endl;
//
//        char guess = ' ';
//        bool found = false;
//        cout << "guess a letter: " << endl;
//        cin >> guess;
//        for (int i = 0; i < chosenword.length(); i++)
//        {
//            // if the users choice is valid
//            if (guess == chosenword[i])
//            {
//                found = true;
//                // log its index in our vector
//
//                foundletters.push_back(i);
//
//            }
//
//
//        }
//        if (found != true) {
//            lives--;
//        }
//
//
//
//    } while (foundcount < (chosenword.size() - 1) && lives != 0);
//    if (lives != 0)
//    {
//        cout << "congrats you found the word!" << endl;
//    }
//    else {
//        cout << "game over" << endl;
//        cout << "the correct answer is: " << chosenword << endl;
//    }
//
//
//
//
//
//
//
//
//    return 0;
//
//}
