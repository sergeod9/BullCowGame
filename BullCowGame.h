#pragma once
#include <string> 
#include <iostream>
#include <map>
#define TMap std::map

//To make syntax UNREAL ENGINE 4 friendly
using FString = std::string;
using int32 = int;

// all variables initialised to Zero
struct FBullCowCount
{
	int32 BullCount = 0;
	int32 CowCount = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};
enum class EResultStatus
{
	Won,
	Lost
};

class FBullCowGame {
public:
	/*
	Currently FBullCowGame() constructor is doing nothing
	I'm just keeping it as a sample of Constructor definition
	This is similar to __init__ function in Python
	*/
	FBullCowGame(); // Constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon(FString) const;
	EGuessStatus CheckGuessValidity(FString) const;
	EResultStatus SummarizeGame(bool) const;

	FString GetHiddenWord();

	void Reset();
	void PrintIntro();
	
	// provide a method for counting bulls and cows and incrementing current try
	FBullCowCount SubmitValidGuess(FString);

	bool HasOnlyDigits(const FString);// Check if a string has only digits
	

private:
	// See constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	TMap <int32, FString> HiddenDictionary;
};
