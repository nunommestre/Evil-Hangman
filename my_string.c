#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
struct string{
	int size;
	int capacity;
	char* data;
};
typedef struct string My_String;

MY_STRING my_string_init_default(void){
	My_String* pString;
	pString = (My_String*)malloc(sizeof(My_String));
	if(pString != NULL){
		pString->size  = 0;
		pString->capacity = 7;
		pString->data = (char*)malloc(sizeof(char)*pString->capacity);
		if(pString->data == NULL){
			free(pString);
			return NULL;
		}
	}
	return (MY_STRING) pString;
}
void my_string_destroy(ITEM* pItem){
	//destroy for string not item
	My_String* pString = (My_String*) *pItem;
	free(pString->data);
	free(pString);
	*pItem = NULL;
}
 MY_STRING my_string_init_c_string(const char* c_string){;
 My_String* pString;
 int i=0;
 pString = (My_String*)malloc(sizeof(My_String));
	while(c_string[i] != '\0'){
		i++;
	}
        if(pString != NULL){
                pString->size  = i;
                pString->capacity = pString->size+1;
                pString->data = (char*)malloc(sizeof(char)*pString->capacity);
                if(pString->data == NULL){
                        free(pString);
                        return NULL;
                }
		for(i=0; i < pString->size; i++){
			pString->data[i] = c_string[i];
		}
        }
        return (MY_STRING)pString;
}
int my_string_get_capacity(MY_STRING hMy_string){
	My_String* pString = (My_String*) hMy_string;
	return pString->capacity;
}
int my_string_get_size(MY_STRING hMy_string){
	My_String* pString = (My_String*) hMy_string;
	return pString->size;
}
int my_string_compare(MY_STRING hLeft_string,MY_STRING hRight_string){
	My_String* pString = (My_String*) hLeft_string;
       	My_String* p2String = (My_String*) hRight_string;
	int i = 0;
	if(pString->size == 0 && p2String->size == 0){
		return 0;
	}
	if(pString->size == 0){
		return -1;
	}
	if(p2String->size == 0){
		return 1;
	}

	while(pString->size > i && p2String->size > i && (pString->data[i] == p2String->data[i])){
		i++;
	}
	if(pString->size <= i || p2String->size <= i){
        if(pString->size > p2String->size){
            return 1;
        }
        else if(pString->size < p2String->size){
            return -1;
        }
        else{
            return 0;
        }
    }

    if(pString->data[i] > p2String->data[i]){
        return 1;
    }
    if(pString->data[i] < p2String->data[i]){
        return -1;
    }
    else{
        return 0;
    }
}
STATUS my_string_extraction(MY_STRING hMy_string, FILE* fp){
	My_String* pMy_string = (My_String*) hMy_string;
	char a;
	char *temp;

	if (EOF == (a = fgetc(fp))){
		return FAILURE;
	}
	pMy_string->size = 0;	
	while(a != ' ' && a != EOF && a != '\n'){
		pMy_string->data[pMy_string->size] = a;
		pMy_string->size++;

		if(pMy_string->size >= pMy_string->capacity){
		       pMy_string->capacity *= 4;
	       	       temp = (char*) malloc(sizeof(char) * pMy_string->capacity);

		for(int i=0; i < pMy_string->size; i++){
	 		temp[i]= pMy_string->data[i];
		}
	free(pMy_string->data);
	pMy_string->data = temp;
		}
	a = fgetc(fp);	
	if(a == ' ' || a == '\n' || a == EOF){
	ungetc(a, fp);
	}
	}
return SUCCESS;
}
STATUS my_string_insertion(MY_STRING hMy_string, FILE* fp){
        My_String* pMy_string = (My_String*) hMy_string;
        for(int i=0; i < pMy_string->size; i++){
	fputc(pMy_string->data[i], fp);
	}
	if(fp == NULL){
	return FAILURE;
	}
	return SUCCESS;

}
STATUS my_string_push_back(MY_STRING hMy_string, char item){

	My_String* pMy_string = (My_String*) hMy_string;
	char* temp;
	int i;
	if(pMy_string->size >= pMy_string->capacity){
		temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
		if(temp == NULL){
			return FAILURE;
		}
		for(i = 0; i < pMy_string->size; i++){
			temp[i]= pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data  = temp;
		pMy_string->capacity *= 2;
	}
	pMy_string->data[pMy_string->size] = item;
	pMy_string->size++;
	return SUCCESS;
}
 STATUS my_string_pop_back(MY_STRING hMy_string){
	My_String* pMy_string = (My_String*) hMy_string;
	if(my_string_empty(hMy_string)){
		return FAILURE;
	}
	pMy_string->size--;
	return SUCCESS;
}
Boolean my_string_empty(MY_STRING hMy_string){
	My_String* pMy_string = (My_String*) hMy_string;
	return (Boolean)(pMy_string->size <= 0);
}
char* my_string_at(MY_STRING hMy_string, int index){
	My_String* pMy_string = (My_String*) hMy_string;
	if(index < 0 || index >= pMy_string->size){
		return NULL;
	}
	return &(pMy_string->data[index]);
}
char* my_string_c_str(MY_STRING hMy_string){
	My_String* pMy_string = (My_String*) hMy_string;
	char* temp;
	if(pMy_string->size >= pMy_string->capacity){
	temp = (char*) malloc(sizeof(char) * pMy_string->capacity + 1);
	if(temp == NULL){
		return NULL;
	}
	for(int i = 0; i < pMy_string->size; i++){
		temp[i] = pMy_string->data[i];
	}
	free(pMy_string->data);
	pMy_string->data = temp;
	pMy_string->capacity += 1;
	}
	pMy_string->data[pMy_string->size] = '\0';
	return my_string_at(hMy_string, 0);
}
STATUS my_string_concat(MY_STRING hResult, MY_STRING hAppend){
	My_String* pRstring = (My_String*) hResult;
	My_String* pAstring = (My_String*) hAppend;
	for (int i = 0; i < pAstring->size; i++) {
		if (my_string_push_back(pRstring, *my_string_at(pAstring, i)) == FAILURE) {
			return FAILURE;
		}
	}
	return SUCCESS;
}
STATUS my_string_assignment(ITEM* pLeft, ITEM Right){
	My_String* pRight = (My_String*) Right;
        My_String* ppLeft = (My_String*) *pLeft;
	char* temp;
	if(ppLeft == NULL){
		ppLeft = my_string_init_default();
	}
	if(ppLeft->capacity <= pRight->capacity){
		ppLeft->capacity = pRight->capacity;
		temp = (char*)malloc(sizeof(char) * ppLeft->capacity);
		if(temp == NULL){
			return FAILURE;
		}
		free(ppLeft->data);
		ppLeft->data = temp;
	}
	for(int i = 0; i < pRight->size; i++){
		ppLeft->data[i] = pRight->data[i];
	}
	 ppLeft->size = pRight->size;
        *pLeft = ppLeft;
	if(ppLeft == NULL){
		ppLeft = NULL;
	}
	return SUCCESS;
	}
STATUS get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess){
  int i;
  
  my_string_assignment(&new_key, current_word_family);

  for(i = 0; i< my_string_get_size(word); i++)
  {
    if(*my_string_at(word, i) == guess)
    {
      *my_string_at(new_key, i) = guess;
    }
  }
  
  return SUCCESS;
  }
char guessing(MY_STRING hString){
        char guess;
	scanf(" %c", &guess);
	clear_keyboard_buffer();
	int i;
	My_String* pString = (My_String*) hString;
        for(i = 0; i < my_string_get_size(pString); i++){
                while(*my_string_at(pString, i) == guess){
                        printf("Looks like you already tried that letter! Guess another: ");
              		scanf(" %c", &guess);
			clear_keyboard_buffer();	
		}
	}
	my_string_push_back(pString, guess);
	return guess;
}
void clear_keyboard_buffer(void){
    char c;
    int noc;
    noc = scanf("%c", &c);
    while (noc == 1 && c != '\n' ){
        noc = scanf("%c", &c);
    }
}
