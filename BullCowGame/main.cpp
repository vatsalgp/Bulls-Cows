#pragma once
#include <iostream>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCGame;

void PrintIntro();
FText GetGuess();
void PlayGame();
bool AskToPlayAgain();
FText CheckGuessError();
void PrintGameSummary();

int main()
{
	do {
		system("cls");
		PrintIntro();
		PlayGame();
		BCGame.Reset();
	} while (AskToPlayAgain());
	return 0;
}

void PrintIntro() {

	std::cout << "Welcome to Bulls and Cows" << std::endl;

	std::cout << "     /                       \\"                             << std::endl;
	std::cout << "  /X/                       \\X\\"                           << std::endl;
	std::cout << " |XX\\         _____         /XX|"                           << std::endl;
	std::cout << " |XXX\\     _/       \\_     /XXX|___________"               << std::endl;
	std::cout << "  \\XXXXXXX             XXXXXXX/            \\"              << std::endl;
    std::cout << "   \\XXXX    /     \\    XXXXX/               \\___"         << std::endl;
	std::cout << "        |   0     0   |                         \\"          << std::endl;
    std::cout << "         |           |                           \\"         << std::endl;
	std::cout << "          \\         /                            |______//" << std::endl;
	std::cout << "           \\       /                             |"         << std::endl;
	std::cout << "            | O_O | \\                           _|"         << std::endl;
	std::cout << "             \\ _ /   \\______________           /"          << std::endl;
	std::cout << "                      | |  | |      \\         /"            << std::endl;
	std::cout << "                      / |  / |       \\_______/"             << std::endl;
	std::cout << "                      \\ |  \\ |        \\ |  \\ |"          << std::endl;
	std::cout << "                    __| |__| |      __| |__| |"              << std::endl;
	std::cout << "                    |___||___|      |___||___|"              << std::endl;
	std::cout << std::endl;
	std::cout << "An Isogram is a word that does not contain any repeating letters." << std::endl << std::endl;
	std::cout << "Can you successfuly guess a " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram?" << std::endl;
	std::cout << "You will get " << BCGame.GetMaxTries() << " tries." << std::endl << std::endl;

	return;
}

void PlayGame() {

	//std::cout << BCGame.GetCurrentTry() << BCGame.GetMaxTries() << BCGame.IsGameWon() << std::endl;
	while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries() && !BCGame.IsGameWon()) {
		FText Guess = CheckGuessError();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = "<< BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();

	return;
}

FText GetGuess() {
	FText Guess = "";
	std::cout << "Try "<< BCGame.GetCurrentTry() <<" of ";
	std::cout << BCGame.GetMaxTries() << ". Enter Your Guess : ";
	getline(std::cin, Guess);

	return Guess;
}

bool AskToPlayAgain() {

	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	Response[0] = tolower(Response[0]);

	return Response[0] == 'y';
}

FText CheckGuessError() {

	FText Guess = "";
	EGuessStatus Status;
	do {
		Guess = GetGuess();
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::IncorrectWordLength:
			std::cout << "Incorrect Word Length." << std::endl;
			break;
		case EGuessStatus::NotIsogram:
			std::cout << "The Word is Not an Isogram." << std::endl;
			break;
		case EGuessStatus::NotSingleWord:
			std::cout << "You have not entered a single word" << std::endl;
			break;
		case EGuessStatus::Ok:
			return Guess;
		};

		std::cout << std::endl;

	} while (Status != EGuessStatus::Ok);

	return Guess;
}

void PrintGameSummary() {

	if (BCGame.IsGameWon()) {
		std::cout << "You Win." << std::endl;
	}
	else {
		std::cout << "You Lost." << std::endl;
	}
}
