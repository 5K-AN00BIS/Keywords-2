// Keywords2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Ryan Bachman
// CSC215 C/C++ Programming
// University of Advancing Technology
// Keywords II
// October 27, 2018

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>

using namespace std;

int main()
{
    // Display Title of program to user
	cout << "\t\t\t\t\tWelcome to Keywords II, agent.\n\n";

	// Ask the recruit to login using their name
	cout << "Please enter your name: ";

	// Hold the recruit's name in a var, and address them by it throughout the simulation.
	string agentName = "name";
	cin >> agentName;
	cout << endl;

	// Display an overview of what Keywords II is to the recruit.
	cout << "\t\t\tWelcome " << agentName << " to the new variant of your previous challenge, Keywords.\n";
	cout << "\tThis task will be more difficult than your last, as you will not see the scrambled code ahead of time.\n";
	cout << "\t\tWe will be selecting 3 words at random and scrambling them as codewords, with zero hints.\n\n";

	// Display an directions to the recruit on how to use Keywords
	cout << "\t\t\t\t\tHere's what is expected of you...\n";
	cout << "\t\tLike the game of Hangman, you will be guessing letters for the scrambled word.\n";
	cout << "\t\tOnce the scrambled word is fully built out, you will try and unscramble it.\n";
	cout << "\t   You will be doing this 3 times and can run this simulation as many times as you'd like.\n\n\n\n";

	// Maximum number of incorrect guesses that will be allowed.
	const int MAX_WRONG = 10;

	// Create a collection of 10 words you had wrote down manually. I used spy words from https://www.spymuseum.org/education-programs/news-books-briefings/language-of-espionage/.
	vector<string> words;
	words.push_back("ESPIONAGE");
	words.push_back("BIRDWATCHER");
	words.push_back("BURNED");
	words.push_back("CIPHER");
	words.push_back("HANDLER");
	words.push_back("INFILTRATION");
	words.push_back("PATTERN");
	words.push_back("PLAYBACK");
	words.push_back("SANITIZE");
	words.push_back("SPYMASTER");

	// Create an int var to count the number of simulations being run starting at 1
	int simulations = 1;
	// Defines the playAgain variable so that the simulation can be rerun.
	char playAgain = 'y';

	// While loop begins here so it can be rerun as long as the user says they want to keep going.
	while (playAgain == 'y')
	{
		// Keeps track of how many words the user got correct so that they need to complete 3 words.
		int wordsCorrect = 0;

		// Display the simulation # is starting to the recruit.
		cout << "\t\t\t\tWe are now beginning simulation #" << simulations << ". Good luck." << endl;

		/* While loop that forces the player to have to do 3 words to complete the assignment.
		 * For this, I'm sure there is a better way to set 3 random words total.
		 * My thought is that setting 3 different variables for elements in words, it could get super long and drawn out.
		 * This way compacts the code, but I run into the issue where it's possible to get the same word twice.
		 * This will need further study of course.*/
		while (wordsCorrect < 3)
		{
			// Seeds the random number generator.
			srand(static_cast<unsigned int>(time(nullptr)));
			// Shuffles the words in the vector.
			random_shuffle(words.begin(), words.end());
			// Pick new 3 random words from your collection as the secret code word the recruit has to guess.
			string theWord = words[0];
			// Shuffles the letters in the word that was picked at random.
			random_shuffle(theWord.begin(), theWord.end());
			//cout << theWord << endl; // NO LONGER IN USE. Used to test that the word was being scrambled.

			// Keeps track of the number of incorrect guesses.
			int wrong = 0;
			// Keeps track of how much of the word is guessed so far.
			string soFar(theWord.size(), '-');
			// Keeps track of the letters that were already guessed.
			string used = "";
			// Keeps track of the guess the player is using for unscrambling the word.
			string scrambleGuess = "null";

			// While recruit hasn’t made too many incorrect guesses and hasn’t guessed the secret word
			while ((wrong < MAX_WRONG) && (soFar != theWord))
			{
				// Tell recruit how many incorrect guesses he or she has left
				cout << "\n\nYou have " << (MAX_WRONG - wrong);
				cout << " incorrect guesses left.\n";

				// Show recruit the letters he or she has guessed
				cout << "\nYou've used the following letter:\n" << used << endl;

				// Show player how much of the secret word he or she has guessed
				cout << "\nSo far, the word is:\n" << soFar << endl;

				// Get recruit's next guess
				char guess;
				cout << "\n\nEnter your guess: ";
				cin >> guess;
				// Makes the guess letter uppercase since the secret word is uppercase.
				guess = toupper(guess);

				// While recruit has entered a letter that he or she has already guessed
				while (used.find(guess) != string::npos)
				{
					// Get recruit ’s guess
					cout << "\nYou've already guessed " << guess << endl;
					cout << "Enter your guess: ";
					cin >> guess;
					// Capitalizes the guess so that they don't get it incorrect because it's case sensitive.
					guess = toupper(guess);
				}

				// Add the new guess to the group of used letters
				used += guess;

				// If the guess is in the secret word
				if (theWord.find(guess) != string::npos)
				{
					// Tell the recruit the guess is correct
					cout << "That's correct Special Agent " << agentName << ". " << guess << " is in the word.\n";

					// Update the word guessed so far with the new letter
					for (unsigned int i = 0; i < theWord.length(); ++i)
					{
						if (theWord[i] == guess)
						{
							soFar[i] = guess;
						}
					}
				}
				// Otherwise
				else
				{
					// Tell the recruit the guess is incorrect
					cout << "Sorry, " << guess << " isn't in the word.\n";

					// Increment the number of incorrect guesses the recruit has made
					++wrong;
				}
			}

			// If the recruit has made too many incorrect guesses
			if (wrong == MAX_WRONG)
			{
				// Tell the recruit that he or she has failed the Keywords II course.
				cout << "\nYou've failed this course. Your handler will find you shortly.\n";
				// Sets wordsCorrect to 3 to instantly end the loop but still ask if they want to try again.
				wordsCorrect = 3;
			}
			// Otherwise
			else if (wordsCorrect == 3)
			{
				// Congratulate the recruit on guessing all of the secret words.
				cout << "\nThat is correct. You have solved all of the words. Training successful.\n";
			}
			else
			{
				// Congratulate the recruit on guessing the secret words.
				cout << "\nThe codeword has been built.\n";
				cout << "Please solve the scrambled word " << theWord << "." << endl;

				// Nested while loop so the player can keep guessing the word without it doing the main loop and changes the word.
				while (scrambleGuess != words[0])
				{
					// Asks the agent to guess what the scrambled word is.
					cout << "\nYour guess (Remember to use all capital letters): ";
					cin >> scrambleGuess;

					// If else statement saying whether or not they are correct or incorrect.
					if (scrambleGuess == words[0])
					{
						cout << "Correct.\n";
						++wordsCorrect;
					}
					else
					{
						cout << "Sorry, that's not it.\n";
						cout << "Please solve the scrambled word " << theWord << "." << endl;
					}
				}
				
			}
		}

		// Ask the recruit if they would like to run the simulation again.
		// Special if statement to display a congratulatory message for winning before asking to restart.
		if (wordsCorrect == 3)
		{
			cout << "\n\nCongratulations. You have passed your training.\n";
		}
		cout << "Do you want to train again? (y/n): ";
		cin >> playAgain;
		cout << "\n\n";

		// If the recruit wants to run the simulation again
		if (playAgain == 'y')
		{
			// Increment the number of simulations ran counter
			++simulations;
			// Moves program execution back up to // Display the simulation # is staring to the recruit. 
		}
		// Otherwise
		else
		{
			// Display End of Simulations to the recruit
			cout << "This is the end of the simulation. Pass or fail, you will be picked up by your handler shortly.\n\n";

			// Pause the Simulation with press any key to continue
			return 0;
		}
	}

	// Ends program just in case there is something I missed.
	return 0;
}