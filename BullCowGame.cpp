# pragma once
#include "FBullCowGame.h"


using int32 = int;

/*
Currently this is doing nothing
I'm just keeping it as a sample of Constructor definition
This is similar to __init__ function in Python
*/
FBullCowGame::FBullCowGame()//Constructor Initialisation
{
	return;
}

void FBullCowGame::Reset()
{
	/*do
	{
		MyHiddenWord = GetHiddenWord();
	} while (MyHiddenWord == "Wrong Input");*/

	MyCurrentTry = 1; // Reset tries counter
}

void FBullCowGame::PrintIntro()
{
	// Introduce the game
	std::cout << " ======= Welcome to Bulls and Cows ======= \n\n";
	std::cout << "         (        ) \n";
	std::cout << "          \\======/         <====> \n";
	std::cout << "   --____<=(*)(*)=>      <=(0)(0)=>_____-- \n";
	std::cout << "  ||        \\  /            \\  /        || \n";
	std::cout << "  |||-----|| <_>            <_> ||--()-||| \n";
	std::cout << "   ||     ||    BULLS & COWS    ||     || \n";
	std::cout << "   -^     -^     == GAME ==     ^-     ^- \n";
	std::cout << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
	do
	{
		MyHiddenWord = GetHiddenWord();
	} while (MyHiddenWord == "Wrong Input");

	std::cout << " Can you guess the " << GetHiddenWordLength();
	std::cout << " letters isogram?\n";
	std::cout << " You have " << GetMaxTries() << " tries. \n\n";
		
}

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const 
{
	return ((int32)MyHiddenWord.length() * 2 - (int32)floor(MyHiddenWord.length()*0.2));
}

bool FBullCowGame::IsGameWon(FString Guess) const
{
	if (Guess == MyHiddenWord)
	{
		return true;
	}
	else
	{
		return false;
	}
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess is not an isogram //TODO use right condition
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (GetHiddenWordLength() != Guess.length())// if the guess has the wrong length
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowerCase(Guess))// if the guess is not lowercase //TODO use right condition
	{
		return EGuessStatus::Not_Lowercase;
	}
	else // if the guess is 
	{
		return EGuessStatus::OK;
	}
}

EResultStatus FBullCowGame::SummarizeGame(bool won) const
{
	if (won)
	{
		return EResultStatus::Won;
	}
	else
	{
		return EResultStatus::Lost;
	}
}

FString FBullCowGame::GetHiddenWord()
{
	FString MyHiddenWordIndex;
	TMap <int32,FString> HiddenDictionary { { 3,"den" },{ 4,"turn" },{ 5,"orbit" },{ 6,"planet" },{ 7,"jukebox" },{ 8,"matchbox" } };
	std::cout << " Choose word length. \n";
	std::cout << " Enter a number between 3 and 8: ";
	std::getline(std::cin, MyHiddenWordIndex);
	std::cout << std::endl;
	if (!HasOnlyDigits(MyHiddenWordIndex))
	{
		return "Wrong Input";
	}
	else if (std::stoi(MyHiddenWordIndex) >= 3 && std::stoi(MyHiddenWordIndex) <= 8)
	{
		return HiddenDictionary [std::stoi(MyHiddenWordIndex)];
	}
	else
	{
		return "Wrong Input";
	}
}

// receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	// Declare the return variable
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	
	for (int32 i = 0; i < WordLength; i++) //loop through all letters in the guess
	{
		for (int32 j = 0; j< WordLength; j++) //loop through all letters in the hidden word
		{ 		
		//if they match then:
			if (Guess[i] == MyHiddenWord[j])
			{
				//if they are in the same place:
				if (i == j) 
				{
					//increment bulls
					BullCowCount.BullCount++;
				}
				else if (i != j)
				{
					BullCowCount.CowCount++;
				}
				else
				{
					//increment cows
					std::cout << "Something's wrong in SubmitGuessSignature method\n";
				}
			}
				
		}
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//treat single letter guess as isogram
	if (Guess.length() <= 1) { return true; }
	// Set our map
	TMap <char, bool> LetterSeen;
	for (auto Letter : Guess) // auto let's the compiler decide the right type
	{
		Letter = tolower(Letter);
		LetterSeen[Letter] = true;
	}
	if (Guess.length() == LetterSeen.size())
	{
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const //check if the guess is all lower case
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true; 
}

bool FBullCowGame::HasOnlyDigits(const FString s) {
	return s.find_first_not_of("0123456789") == FString::npos;
}



