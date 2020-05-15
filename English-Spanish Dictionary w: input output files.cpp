//----------------------------------------------------
// Author: Weston Myers
// Purpose: Test program for Dictionary Class
// TO COMPILE: 
//    g++ -std=c++11 -Wall hw6.cpp Dictionary.cpp -o hw6.exe
//----------------------------------------------------

#include <iostream>
#include "dictionary.h"
using namespace std; 

//---------------------------------------------------------------------------
// Name: MainMenu
// Parameters: none
// Returns: none
// Purpose: This function prints the main menu 
//---------------------------------------------------------------------------
void MainMenu() {

    cout << endl;
    cout << "Welcome to the English-Spanish Translation Dictionary";
    cout << endl << "Choose one of the following:" << endl;

     cout << "      0 Load dictionary information from a file\n"
          << "      1 Translate a word from English to Spanish\n"
          << "      2 Translate a word from Spanish to English\n"
          << "      3 Add an English-Spanish pair to the dictionary\n"
          << "      4 Remove an English-Spanish pair to the dictionary\n"
          << "      5 Print the contents of the dictionary\n"
          << "      6 Quit the program\n";
    cout << endl;
}


//---------------------------------------------
// Name:  GetChoice
// Purpose:  Collect a number between 0 and 6 from the user
//           Do error checking to reject invalid values
// Parameters:  None
// Returns: int, a valid value entered by the user
//---------------------------------------------
int GetChoice() 
{
    char choice;  
    int intChoice;

   // Prompt character ('0'-'6') initially
    do 
    {
        cout << "Enter choice: ";  
        cin >> choice;
    } while (choice < '0' || choice > '6');

   // Convert character to integer
    intChoice = choice - '0';
    return (intChoice);
}

// UNCOMMENT TO TEST PROGRAM
//----------------------------------------------------
// Purpose: Add English-Spanish pair from dictionary
// Argument: A Dictionary object (pass by reference)
// Returns: none
//----------------------------------------------------
void AddPair(Dictionary &dict)
{
   string englishWord;
   string spanishWord;

   cout << "Enter an English word: ";
   cin >> englishWord;
   cin.ignore();
   cout << "Enter a Spanish translation of the English word above: ";
   getline(cin, spanishWord);
   if (dict.AddPair(englishWord, spanishWord))
      cout << "The English-Spanish pair was added to the dictionary!" << endl;
   else
      cout << "Error. The pair could not be added to the dictionary." << endl;
}

// UNCOMMENT TO TEST PROGRAM
//----------------------------------------------------
// Purpose: Remove English-Spanish pair from dictionary
// Argument: A Dictionary object (pass by reference)
// Returns: none
//----------------------------------------------------
void RemovePair(Dictionary &dict)
{
   int position;

   cout << "Enter the index of the pair to remove: ";
   cin >> position;
   if (dict.RemovePair(position))
      cout << "The English-Spanish pair was removed from the dictionary!" << endl;
   else
      cout << "Error. The information could not be removed from the dictionary." << endl;
}

int main()
{
   Dictionary dict;
   string Filename;
   string Query;
   string English, Spanish;

   //print main menu here
   //While the user does not wish to exit the program
   MainMenu();
   char choice = GetChoice();
   while (choice != 6)
   {
      switch (choice)
      {
         case 0: // LOAD CONTENTS FROM A FILE
         
            cout << "Enter the name of the file to be used: ";
            cin >> Filename;

            if (dict.LoadFile(Filename))
               cout << "The file was successfully loaded." << endl;
            else
               cout << Filename << " failed to load." << endl;
         
            break;
         case 1: // TRANSLATE FROM ENGLISH TO SPANISH
         
            cout << "Enter an English word for translation: ";
            cin >> English;
            Spanish = dict.LookupSpanish(English);
            if (Spanish == "DOES NOT EXIST IN DICTIONARY")
               cout << English << " is not in our dictionary.\n";
            else 
               cout << "The English word " << English << " is " << Spanish <<  " in Spanish.\n";
         
            break;
         case 2: // TRANSLATE FROM SPANISH TO ENGLISH
         
            cout << "Enter an Spanish word for translation: ";
            cin.ignore();
            getline(cin, Spanish);
            English = dict.LookupEnglish(Spanish);
            if (English == "DOES NOT EXIST IN DICTIONARY")
               cout << Spanish << " is not in our dictionary.\n";
            else 
               cout << "The Spanish word " << Spanish << " is " << English <<  " in English.\n";
         
            break;
         case 3: // ADD ENGLISH-SPANISH WORD PAIR TO DICTIONARY
         
            AddPair(dict);
         
            break;
         case 4: // REMOVE ENGLISH-SPANISH WORD PAIR FROM DICTIONARY
         
            RemovePair(dict);
         
            break;
         case 5: // PRINT CONTENTS OF DICTIONARY TO CONSOLE
            dict.Print();
            break;
      } // end switch
   
      // get next choice
      MainMenu();
      choice = GetChoice();
   } 

   // TEST THE COPY CONSTRUCTOR FUNCTIONALITY
   Dictionary dict2 (dict);
   cout << "Copy of the translation dictionary at time of exit:\n";
   dict2.Print();
   return 0;
}