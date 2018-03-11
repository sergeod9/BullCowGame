#pragma once
#include "FBullCowGame.h"

//To make syntax UNREAL ENGINE 4 friendly
using FText = std::string;
using int32 = int;

void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame;

int main()
{
	
	// Play game
	do
	{
		PlayGame();

	} while (AskToPlayAgain());

	return 0; // Exit the application

}

//Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	BCGame.PrintIntro();
	
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";
	EResultStatus Summary;

	// Loop while The game IS NOT won and the tries haven't expired
	while (!BCGame.IsGameWon(Guess) && BCGame.GetCurrentTry() <= MaxTries)
	{
		Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Your guess is " << Guess << std::endl;
		std::cout << "Bulls: " << BullCowCount.BullCount <<  ".";
		std::cout << "Cows: " << BullCowCount.CowCount << "\n\n";
		
	}

	Summary = BCGame.SummarizeGame(BCGame.IsGameWon(Guess));
	if (Summary == EResultStatus::Won)
	{
		std::cout << "CONGRATULATIONS, YOU WON!\n";
	}
	else
	{
		std::cout << "Better Luck next time\n";
	}
	return;
}


// loops until a valid guess is given
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess;
	do
	{
		// Get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		Guess = "";
		std::cout << " What's your guess: ";
		std::getline(std::cin, Guess);
		std::cout << " Try # "<< CurrentTry << " out of " << BCGame.GetMaxTries();

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "\nPlease enter a " << BCGame.GetHiddenWordLength() << " letters word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "\nPlease pick a word that doesn't have repeated letters (isogram).\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "\nPlease use all lowercase letters.\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get valid input
	
	return Guess;		
}

bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again? (y/n) ";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

