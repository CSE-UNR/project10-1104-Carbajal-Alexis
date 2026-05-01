//Author: Alexis Carbajal
//Date: 4/27/26
//Purpose: Wordle!

#include<stdio.h>
#include<stdbool.h>

void getWord(char word[]);
void lowercase(char str[]);
bool validGuess(char guess[]);
void storeGuess(char guesses[][6], char guess[], int attempt);
bool checkWin(char guess[], char word[]);
void printPointers(char guess[], char word[]);
void displayGuesses(char guesses[][6], int attempts, char word[]);

int main(){
	char word[6];
	char guess[6];
	char guesses[6][6];
	int attempts = 0;
	bool won = false;
	
	getWord(word);
	
	while(attempts < 6 && !won){
		if(attempts == 5){
			printf("FINAL GUESS: ");
		} else{
			printf("GUESS %d! Enter your guess! ", attempts +1);
		}
		
		scanf("%s", guess);
		
		if(!validGuess(guess)){
			printf("Your guess must be 5 letters long.\nPlease try again: \n\n");
			continue;
		}
		
		lowercase(guess);
		
		storeGuess(guesses, guess, attempts);
		
		displayGuesses(guesses, attempts + 1, word);
		
		if(checkWin(guess, word)){
			won = true;
		}
		
		attempts++;
	}
	
	if(won){
		printf("You won in %d guesses!\n", attempts);
	} else{
		printf("You lost, better luck next time!\n");
	}
	
	return 0;
}

void getWord(char word[]){
	FILE* file = fopen("mystery.txt", "r");
	
	if(file == NULL){
		printf("Error\n");
		return;
	}
	
	fscanf(file, "%s", word);
	fclose(file);
}
void lowercase(char str[]){
	int i = 0;
	while(str[i] != '\0'){
		if(str[i] >= 'A' && str[i] <= 'Z'){
			str[i] = str[i] + 32;
		}
		i++;
	}
}
bool validGuess(char guess[]){ 
	int i = 0;
	
	while(guess[i] != '\0'){
		i++;
	}
	
	if(i != 5){
		return false;
	}
	
	for(int j = 0; j < 5; j++){
		if(!((guess[j] >= 'a' && guess[j] <= 'z') || (guess[j] >= 'A' && guess[j] <= 'Z'))){
		return false;
		}
	}
	
	return true;
}
void storeGuess(char guesses[][6], char guess[], int attempt){
	for(int i = 0; i < 6; i++){
		guesses[attempt][i] = guess[i];
	}
}
bool checkWin(char guess[], char word[]){
	for(int i = 0; i < 5; i++){
		if(guess[i] != word[i]){
			return false;
		}
	}
	
	return true;
}
void printPointers(char guess[], char word[]){
	for(int i = 0; i < 5; i++){
		if(guess[i] == word[i]){
			printf(" ");
			continue;
		}
		
		bool found = false;
		
		for(int j = 0; j < 5; j++){
			if(guess[i] == word[j]){
				found = true;
			}
		}
		
		if(found){
			printf("^");
		}else{
			printf(" ");
		}
	}
	
	printf("\n");
}
void displayGuesses(char guesses[][6], int attempts, char word[]){

	printf("================================\n");	
	
	for(int i = 0; i < attempts; i++){
		for(int j = 0; j < 5; j++){
			if(guesses[i][j] == word[j]){
				if(guesses[i][j] >= 'a' && guesses[i][j] <= 'z'){
					printf("%c", guesses[i][j] - 32);
				} else{
					printf("%c", guesses[i][j]);
				}
			} else{
				printf("%c", guesses[i][j]);
			}
		}
		
		printf("\n");
		
		printPointers(guesses[i], word);
	}
}		



	
