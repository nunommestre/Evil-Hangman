/* EVIL HANGMAN By: Nuno Mestre
 * April 30, 2021
 * TA: Qilei Chen
 * The game works pretty well, however it does randomly crash on certain words which was one of the errors I wasn't able to figure out. However, if you play a few times it should run well and play as intended, giving you a option to play again at the end. I do have leaks and I'm unsure why. Feel free to give me feedback on those and enjoy. :)
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "AVL_Tree.h"

//function declarations
void play(void);
int check_guess(void);
int check_length(void);
Boolean check_spoil(void);
Boolean rematch(void);

//Lol main is very clean just this one function that plays the game with others inside it
int main(int argc, char* argv[])
{
play();
return 0;
}

void play(void){
	//Intro
	printf("Welcome to Evil Hangman! A totally unrigged game of hangman developed by Nuno Mestre.\n");
	
	//length of word assigned (function ensures good input)
	printf("Enter how long you wish the word to be: ");
	int length = check_length();

	//number of guesses assigned (function ensures good input)
	printf("How many guesses do you want: ");
	int guesses = check_guess();
	
	//type a y to unlock the feature that shows you how rigged the game is
	printf("Let the fun begin!\n");
	printf("Quickly before we start would you like to see hopes of winning disappear?(yes/no): ");
	Boolean isRigged = check_spoil();
	
	//init strings,vectors, and trees
	MY_STRING current_family = my_string_init_default();
	MY_STRING new_state = my_string_init_default();
	MY_STRING letters_guessed = my_string_init_default();
	GENERIC_VECTOR biggest_family_left = NULL;
	Node* potential_families = NULL;
	GENERIC_VECTOR vector = generic_vector_init_default(my_string_assignment, my_string_destroy);
	MY_STRING hString;
	int i;
	FILE* fp;

	fp = fopen("dictionary.txt", "r");
	hString = my_string_init_default();
	
	//pushes the dictionary into the generic vector
	while(my_string_extraction(hString,fp) && !(feof(fp))){
        	if(my_string_get_size(hString) < 30 && my_string_get_size(hString) == length){
			generic_vector_push_back(vector, hString);
        	}
	}
	fclose(fp);
	my_string_destroy(&hString);
	
	//word starts as dashes
	for(i = 0; i < length; i++){
		my_string_push_back(current_family, '-');
	}

	
	while(guesses){
		//outputs the number of words the computer can still switch between
		if(isRigged){
			printf("Lol the computer still has %d words it could change between good luck.\n", generic_vector_get_size(vector));
		}
		printf("You have %d guess(es) remaining.\n", guesses);
		printf("Already guessed:");
		//every letter guessed is pushed onto letters_guessed and the guessing() function reads through each letter in there to make sure future repeat guesses prompt a retry
		for(i = 0; i < my_string_get_size(letters_guessed); i++){
			printf(" %c", *my_string_at(letters_guessed, i));
		}
		printf("\nWord: %s\n", my_string_c_str(current_family));
		printf("What is your guess: ");
		char guess;
		guess = guessing(letters_guessed);
		for(i = 0; i < generic_vector_get_size(vector); i++){
			//part where the guess is taken in and processed
			get_word_key_value(current_family, new_state, generic_vector_at(vector, i), guess);
			potential_families = tree_insert(potential_families, new_state, generic_vector_at(vector, i));
			if(isRigged){
				//every potential word that couldve been selected is shown and displays where the letter would go, or remain dashes if its not in it, list gets smaller as you get closer
				my_string_insertion(generic_vector_at(vector, i),  stdout);
				printf(": ");
				my_string_insertion(new_state, stdout);
				printf("\n");
			}
		}		
		printf("\n");

		//assigns biggest family
		biggest_family_left = find_largest_group(potential_families);
		//resets vector to contain words from this largest group now
		generic_vector_destroy(&vector);
		vector = generic_vector_init_default(my_string_assignment, my_string_destroy);
		
		for(i = 0; i < generic_vector_get_size(biggest_family_left); i++){
			generic_vector_push_back(vector, generic_vector_at(biggest_family_left, i));
		}
		get_word_key_value(current_family, new_state, generic_vector_at(vector, 0), guess);
		
		//guess is wrong + you lose a guess
		if(my_string_compare(current_family, new_state) == 0){
                        printf("HAH nice try there is no %c in this word.\n", guess);
                        guesses--;
                }
		//guess is right
                else{
                        printf("Rats! You got a letter!\n");
                }
		my_string_assignment(&current_family, new_state);
		
		//Losing condition
		if(guesses <= 0){
			printf("HAHA nice try, but didn't I warn you that this wouldn't end well!\n");
			printf("The real word was %s.\n", my_string_c_str(generic_vector_at(vector, 0)));
		}
		//Winning condition, function then sets guesses to 0 to kill the loop
		if(my_string_compare(generic_vector_at(vector, 0), current_family) == 0){
			printf("*GASP* WHAT! YOU DEFEATED ME? Fair play you won, but I will be back!\n");
			guesses = 0;
		}
		generic_vector_destroy(&biggest_family_left);
		my_string_destroy(&new_state);
		tree_destroy(&potential_families);
		new_state = my_string_init_default();
		potential_families = NULL;
	}
	//if true then the user plays again if not then my structures are destroyed
	if(rematch()){
		play();
	}
	generic_vector_destroy(&vector);
	my_string_destroy(&current_family);
	my_string_destroy(&letters_guessed);
	my_string_destroy(&new_state);
	free(vector);
 return;
}
//checks valid input, reprompts bad ones
int check_length(void){
int length;
int check = scanf("%d", &length);
while(!check || length < 2 || length == 26 || length == 27 || length > 29){
	printf("There are no words that are this long try again. Try again: ");
	clear_keyboard_buffer();
	check = scanf("%d", &length);
	}
clear_keyboard_buffer();
return length;
}
//checks valid input, and makes you try til you get it
int check_guess(void){
int guess;
int check = scanf("%d", &guess);
while(!check || guess < 1){
        printf("Yikes I think you might need a few more guesses. Try again: ");
        clear_keyboard_buffer();
        check = scanf("%d", &guess);
        }
clear_keyboard_buffer();
return guess;
}
//checks to see if you want the games cheating system exposed
Boolean check_spoil(void){
	char decision;
	scanf("%c", &decision);
	clear_keyboard_buffer();
	if(decision == 'y'){
		return TRUE;
	}
	return FALSE;
}
//Boolean that if true the loop its in makes it run the game again
Boolean rematch(void){
	char choice;
	printf("Would you like to play again?(yes/no)");
	scanf("%c", &choice);
        clear_keyboard_buffer();
        if(choice == 'y'){
                return TRUE;
        }
        return FALSE;
}


