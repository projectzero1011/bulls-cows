#include <iostream>
#include <vector>
using namespace std;

// Used to check digits of guess and digits of random number generated
bool hasRepeatingDigits(vector<int>);

int main() try {
    while(true) {
        cout << "---Bulls and Cows Guessing Game:---\n\n"
        
              << "- Guess the secret 4-digit number\n"
              << "- The digits of the number are all distinct\n"
              << "- \"Bulls\" are correct digits in the correct position\n"
              << "- \"Cows\" are correct digits in the wrong position\n"
              << "- Keep guessing until you find the number\n\n";

        int bull = 0;
        int cow = 0;
        
        // Storing digits of secret random number
        vector<int> secretDigits(4);
        
        // Storing digits of our guess
        vector<int> guessDigits(4);

        srand(time(NULL));

        // Generate random numbers until no repeat digits
        while(true) {
            for(int i = 0; i < secretDigits.size(); ++i) {
                secretDigits[i] = 0;
            }

            for(int i = 0; i < secretDigits.size(); ++i) {
			    if(i == 0) {
				    secretDigits[i] = rand() % 9 + 1;
			    }
			    else {
				    secretDigits[i] = rand() % 9;
			    }
            }

            if(!hasRepeatingDigits(secretDigits)) {
                break;
            }
        }

        // Main game loop, breaks and you win if you hit 4 bulls
        while(bull < 4) {
            bull = 0;
            cow = 0;

            // Resetting the previous digits guessed
            for(int i = 0; i < 4; ++i) {
                guessDigits[i] = 0;
            }

            // Keep prompting input if guess is invalid
            while(true) {
                int guess = 0;
                cout << "Guess: ";
                cin >> guess;
                cout << "\n";

                // Handling Bad Input
                if(!cin) {
                    throw runtime_error("You must enter a 4-digit number\nPlease try again\n");
                }
                else if(guess > 9999 || guess < 1000) {
                    cout << "You must enter a 4-digit number\nPlease try again\n\n";
                    continue;
                }

                // Separating the digits of our 4 digit guess and storing them
                for(int i = 0, j = 1000; i > 4 || j > 0; ++i, j /= 10) {
                    guessDigits[i] = (guess / j) % 10;
                }
                
                if(hasRepeatingDigits(guessDigits)) {
                    cout << "You cannot have repeating digits in your guess\nPlease try again\n\n";
                    continue;
                }
                else {
                    break;
                }
            }

            // Counting the number of bulls you have in your guess
            for(int i = 0; i < 4; ++i) {
                if(guessDigits[i] == secretDigits[i]) {
                    ++bull;
                }
            }

            // Counting the number of cows you have in your guess
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    if(guessDigits[i] == secretDigits[j] && i != j) {
                        ++cow;
                    }
                }
            }

            // Output correct grammatical sentence based on bull/cow count
            if(bull == 1) {
                cout << bull << " bull" << "\n";
            }
            else {
                cout << bull << " bulls" << "\n";
            }

            if(cow == 1) {
                cout << cow << " cow" << "\n\n";
            }
            else {
                cout << cow << " cows" << "\n\n";
            }
        }

        // Prompting the user if they want to play again
        cout << "You win!\n"
             << "Play Again? (y/n): ";
        
        char answer = ' ';
        cin >> answer;

        if(answer != 'y' && answer != 'Y') {
            break;
        }

        cout << "\n\n";
    }
    return 0;
}
catch(exception& e) {
    cerr << "Runtime Error: " << e.what() << "\n";
    return 1;
}
catch(...) {
    cerr << "Unknown exception!\n";
    return 2; 
}

// Checking for repeat digits using vector of bool values, {0 or 1}
bool hasRepeatingDigits(vector<int> digits) {
    vector<int> digitsSeen(10);

    for(int digit : digits) {
        if(digitsSeen[digit]) {
            return true;
        }
        else {
            digitsSeen[digit] = true;
        }
    }
    return false;
}