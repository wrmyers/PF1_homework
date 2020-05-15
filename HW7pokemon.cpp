//  *~*
//  File: main.cpp
//  Author: Weston Myers
//  Date: April 20, 2020
//  Purpose: PF1 hw7 Storagedex Testing
//  *~*
//  COMPILATION: g++ -std=c+=11 -Wall main.cpp Pokemon.cpp Storagedex.cpp -o hw7
//  TO RUN: ./hw7
//  *~*
#include <iostream>
#include <iomanip>
#include "Pokemon.h"
#include "Storagedex.h"
using namespace std;


void MainMenu() {
    cout << "\nWelcome to Weston Myers's Super Storagedex." << endl;
    cout << " 1 - Print one Pokemon by index" << endl;
    cout << " 2 - Print all Pokemon that are stored" << endl;
    cout << " 3 - Print the Storagedex using a formatted method" << endl;
    cout << " 4 - Add a Pokemon to the Storagedex" << endl;
    cout << " 5 - Release a Pokemon by value from the Storagedex" << endl;
    cout << " 6 - Release a Pokemon by index from the Storagedex" << endl;
    cout << " 7 - Get Pokedex Completion Percentage" << endl;
    cout << " 8 - Get Top X Ranked Pokemon in the Storagedex" << endl;
    cout << " 9 - Get the index of the Weakest Pokemon in the Storagedex" << endl;
    cout << " B - Batch add random Pokemon for testing purposes" << endl;
    cout << " S - Start a new game (Release all Pokemon and option to erase Pokedex)" << endl;
    cout << " Q - QUIT" << endl;
    cout << "\nEnter choice: " << endl;
}

void getPokemonStats(int &id, int &hp, int &atk, int &def, int &lvl) {
    cout << "Enter an integer [0-155] for ID: " << endl;
    cin >> id;
    cout << "Enter an integer [10-500] for Health: " << endl;
    cin >> hp;
    cout << "Enter an integer [1-50] for Attack: " << endl;
    cin >> atk;
    cout << "Enter an integer [1-50] for Defense: " << endl;
    cin >> def;
    cout << "Enter an integer [1-100] for Level: " << endl;
    cin >> lvl;
}


bool AddPokemon4(Storagedex &dex) {
    char charChoice;
    int id, hp, atk, def, lvl;
    cout << "Do you wish to add a random Pokemon or a custom Pokemon? [r] or [c]" << endl;
    cin >> charChoice;
    if (toupper(charChoice) == 'R') {
        Pokemon p;
        p.randomize();
        cout << "You are adding the below Pokemon:" << endl;
        p.print();
        if (dex.addPokemon(p))
            return true;
        return false;
    }
    else if (toupper(charChoice) == 'C') {
        cout << "Let's customize your Pokemon." << endl;
        getPokemonStats(id, hp, atk, def, lvl);
        Pokemon p(id, hp, atk, def, lvl);
        if (dex.addPokemon(p))
            return true;
        return false;
    }
    cout << "Sorry, invalid user input." << endl;
    return false;
}


bool DelPokemon5(Storagedex &dex) {
    cout << "In order to delete by value, we must gather the stats..." << endl;
    int id, hp, atk, def, lvl;
    getPokemonStats(id, hp, atk, def, lvl);
    Pokemon p(id, hp, atk, def, lvl);
    cout << "You are looking for the below Pokemon:" << endl;
    p.print();
    if (dex.deletePokemon(p))
        return true;
    return false;
}


bool getTopXPokemon8(Storagedex &dex) {
    int num;
    cout << "How many Top Ranked Pokemon do you want to find?" << endl;
    cin >> num;
    if (num < 1)
        return false;
    Pokemon best[num];
    dex.getTopRankedPokemon(best, num);
    bool found = false;
    for (int i = 0; i < num; i++) {
        if (best[i].getID() != -1) {
            found = true;
            break;
        }
    }
    if (found) {
        cout << "Your Top " << num << " Ranked Pokemon are:" << endl;
        for (int i = 0; i < num; i++) {
            if (best[i].getID() == -1)
                continue;
            cout << "With a ranked power of " << best[i].getRankedValue() << ":" << endl;
            best[i].print();
        }
        return true;
    }
    return false;
}


void batchAdd(Storagedex &dex) {
    int num;
    cout << "Only random Pokemon can be batch added. How many do you want to add? [1-30]" << endl;
    cin >> num;
    if (num < -1 || num > 30) {
        cout << "Invalid number received." << endl;
        return;
    }
    for (int i = 0; i < num; i++) {
        Pokemon p;
        p.randomize();
        cout << "Adding... ";
        p.print();
        if (dex.addPokemon(p))
            cout << "Pokemon was added!" << endl;
        else {
            cout << "Failed to add a Pokemon... ending early" << endl;
            return;
        }
    }
}


void startNewGame(Storagedex &dex) {
    char choice;
    cout << "Are you sure you want to release all your Pokemon? [y] or [n]" << endl;
    cin >> choice;
    if (toupper(choice) != 'Y' && toupper(choice) != 'N') {
        cout << "Invalid input." << endl;
        return;
    }
    else if (toupper(choice) == 'N') {
        cout << "Pokemon not released." << endl;
        return;
    }
    cout << "Do you want to erase all your Pokedex progress? [y] or [n]" << endl;
    cin >> choice;
    if (toupper(choice) != 'Y' && toupper(choice) != 'N') {
        cout << "Invalid input." << endl;
        return;
    }
    else if (toupper(choice) == 'N') {
        dex.newGame(false);
        cout << "Pokedex progress not erased. Pokemon released." << endl;
    }
    else {
        dex.newGame(true);
        cout << "\nStoragedex erased! New game!" << endl;
    }
}



int main() {
    srand(time(NULL));
    char keepGoing;
    int index;
    //float completion; //uncomment for case 7
    Storagedex dex;
    do {
        MainMenu();
        cin >> keepGoing;
        switch (keepGoing) {
            case '1':
                cout << "Enter the index you wish to print: int only" << endl;
                cin >> index;
                dex.printOne(index);
                break;
            case '2':

                dex.printAll();

                break;
            case '3':
                dex.printBoxes();
                break;
            case '4':

                if (AddPokemon4(dex))
                    cout << "Pokemon was added!" << endl;
                else
                    cout << "Failed to add a Pokemon" << endl;

                break;
            case '5':

                if (DelPokemon5(dex))
                    cout << "Pokemon was released!" << endl;
                else
                    cout << "That Pokemon wasn't found" << endl;

                break;
            case '6':

                cout << "Enter the index you wish to delete: int only" << endl;
                cin >> index;
                if (dex.deletePokemon(index))
                    cout << "Pokemon was released!" << endl;
                else
                    cout << "That slot didn't have a Pokemon" << endl;

                break;
            case '7':
            /*
                completion = dex.getPokedexCompletion() * 100;
                cout << "You have completed " << setprecision(2) << fixed;
                cout << completion << "% of your Pokedex!" << endl;
            */
                break;
            case '8':

                if (!getTopXPokemon8(dex))
                    cout << "Failed to get top Pokemon" << endl;

                break;
            case '9':

                index = -1;
                dex.getWeakestIndex(index);
                if (index != -1)
                    cout << "The weakest Pokemon is in index " << index << endl;
                else
                    cout << "Error finding weakest Pokemon" << endl;

                break;
            case 'b':
            case 'B':

                batchAdd(dex);

                break;
            case 's':
            case 'S':

                startNewGame(dex);

                break;
            case 'q':
            case 'Q':
                cout << "Good bye." << endl;
                break;
            default:
                cout << "Invalid entry. Try again." << endl;
                break;
        }
    } while (toupper(keepGoing) != 'Q');
    return 0;
}
