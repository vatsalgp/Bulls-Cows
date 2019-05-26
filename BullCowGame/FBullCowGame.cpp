#pragma once
#include "FBullCowGame.h"
#include<iostream>
#include <map>
#include <stdlib.h>
#include <time.h>

#define Tmap std::map


int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry;}

int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	return 2 * MyHiddenWord.length();
}

FBullCowGame::FBullCowGame() {
	// Initialising to 0
	MyCurrentTry = 0;
	bGameIsWon = false;
	MyHiddenWord = "";
	Reset(); // Actual values come from here
}

void FBullCowGame::Reset() {

	MyCurrentTry = 1;
	bGameIsWon = false;
	MyHiddenWord = GetHiddenWord();
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess){

	int32 HiddenWordLength = GetHiddenWordLength();
	int32 GuessLength = Guess.length();

	if (!IsSingleWord(Guess))
		return EGuessStatus::NotSingleWord;

	if (GuessLength != HiddenWordLength)
		return EGuessStatus::IncorrectWordLength;

	if (!isIsogram(Guess))
		return EGuessStatus::NotIsogram;

	return EGuessStatus::Ok;
}

bool FBullCowGame::IsSingleWord(FString Guess) {
	
	int32 GuessLength = Guess.length();

	for (int32 i = 0; i < GuessLength; i++) {
		if (Guess[i] == ' ')
			return false;
	}

	return true;
}


FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {

	MyCurrentTry++;

	FBullCowCount BullCowCount;

	int32 WordLength = GetHiddenWordLength();
	for (int32 i = 0; i < WordLength; i++) {
		for (int32 j = 0; j < WordLength; j++) {
			if (MyHiddenWord[i] == tolower(Guess[j])) {
				if (i == j)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}

	bGameIsWon = BullCowCount.Bulls == WordLength;

	return BullCowCount;
}

bool FBullCowGame::isIsogram(FString Guess) {
	
	// Order of n squared
	/*
	int32 GuessLength = Guess.length();
	for (int32 i = 0; i < GuessLength; i++) {
		for (int32 j = i + 1; j < GuessLength; j++) {
			if (Guess[i] == Guess[j])
				return false;
		}
	}

	return true;

	*/
	
	if (Guess.length() <= 1)
		return true;

	Tmap<char, bool> LetterSeen;
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
			return false;
		else
			LetterSeen[Letter] = true;
	}
	
	return true;
}

void FBullCowGame::PrintGameSummary() {

	if (IsGameWon()) {
		std::cout << "You Win." << std::endl;
	}
	else {
		std::cout << "You Lost. The word was " << MyHiddenWord  << "." << std::endl;
	}
}

FString FBullCowGame::GetHiddenWord() {
	
	int32 NoOfHiddenWords;
	FString HiddenWordList[] = {
		"planet",
		"star",
		"plant",
		"home",
		"house",
		"play",
		"slam",
		"" // Supposed to be empty
	};

	for (NoOfHiddenWords = 0; !HiddenWordList[NoOfHiddenWords].empty(); NoOfHiddenWords++);

	srand(time(NULL));

	return HiddenWordList[rand()%NoOfHiddenWords];
}
