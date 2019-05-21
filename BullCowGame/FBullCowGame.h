#pragma once
#include <string>

using FString = std::string;
using int32 = int;

enum class EGuessStatus {
	
	Ok,
	NotIsogram,
	IncorrectWordLength,
	NotSingleWord
};


struct FBullCowCount {

	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public :
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString);
	bool IsSingleWord(FString);
	int32 GetHiddenWordLength() const;
	FBullCowCount SubmitValidGuess(FString);
	void Reset();


private :
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool isIsogram(FString);
	FString GetHiddenWord();
};