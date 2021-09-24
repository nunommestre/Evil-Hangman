#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
STATUS test_nmestre_my_string_comparison1(char* buffer, int length){
	MY_STRING Left_string = my_string_init_c_string("app");
	MY_STRING Right_string = my_string_init_c_string("apple");
	if(my_string_compare(Left_string,Right_string) != -1){
		strncpy(buffer, "test_my_string_comparison1 fails\n"
                        "Did not retrun -1\n", length);
		my_string_destroy((ITEM*)&Left_string);
         	my_string_destroy((ITEM*)&Right_string);
		return FAILURE;
		}
	else{
		strncpy(buffer, "test_my_string_comparison1 works\n", length);
		my_string_destroy((ITEM*)&Left_string);
         	my_string_destroy((ITEM*)&Right_string);
		return SUCCESS;
		}
}
STATUS test_nmestre_my_string_comparison2(char* buffer, int length){
        MY_STRING Left_string = my_string_init_c_string("app");
        MY_STRING Right_string = my_string_init_c_string("app");
        if(my_string_compare(Left_string,Right_string) != 0){
		strncpy(buffer, "test_my_string_comparison2 fails\n"
                        "Did not retrun 0\n", length);
		my_string_destroy((ITEM*)&Left_string);
         	my_string_destroy((ITEM*)&Right_string);
                return FAILURE;
                }
        else{
		strncpy(buffer, "test_my_string_comparison2 works\n", length);
		my_string_destroy((ITEM*)&Left_string);
         	my_string_destroy((ITEM*)&Right_string);
	    	return SUCCESS;
                        }
}
STATUS test_nmestre_my_string_comparison3(char* buffer, int length){
        MY_STRING Left_string = my_string_init_c_string("apple");
        MY_STRING Right_string = my_string_init_c_string("app");
        if(my_string_compare(Left_string,Right_string) != 1){
		strncpy(buffer, "test_my_string_comparison3 fails\n"
                        "Did not retrun 1\n", length);
		my_string_destroy((ITEM*)&Left_string);
         	my_string_destroy((ITEM*)&Right_string);
                return FAILURE;
                }
        else{
		strncpy(buffer, "test_my_string_comparison3 works\n", length);
		my_string_destroy((ITEM*)&Left_string);
         	my_string_destroy((ITEM*)&Right_string);
                return SUCCESS;
                      }
}
STATUS test_nmestre_my_string_comparison4(char* buffer, int length){
        MY_STRING Left_string = my_string_init_c_string("apple");
        MY_STRING Right_string = my_string_init_c_string("");
        if(my_string_compare(Left_string,Right_string) != 1){
		strncpy(buffer, "test_my_string_comparison4 fails\n"
                        "Did not retrun 1\n", length);
		my_string_destroy((ITEM*)&Left_string);
         	my_string_destroy((ITEM*)&Right_string);
                return FAILURE;
                }
        else{
		strncpy(buffer, "test_my_string_comparison4 works\n", length);
		my_string_destroy((ITEM*)&Left_string);
         	my_string_destroy((ITEM*)&Right_string);
                return SUCCESS;
                        }
}
STATUS test_nmestre_init_default_capacity_is7(char* buffer, int length){
	MY_STRING hString = NULL;
	hString = my_string_init_default();

	if(my_string_get_capacity(hString) != 7){
		strncpy(buffer, "test_init_default_capacity_is7 fails\n"
                        "Did not retrun 7\n", length);
		my_string_destroy((ITEM*)&hString);
		return FAILURE;
	}
	else{
		strncpy(buffer, "test_init_default_capacity_is7 works\n", length);
		my_string_destroy((ITEM*)&hString);
		return SUCCESS;
	}
}
STATUS test_nmestre_destroy_works(char* buffer, int length){
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	my_string_destroy((ITEM*)&hString);
	if(hString != NULL){
		strncpy(buffer, "test_destroy_works fails\n"
			"Did not return null\n", length);
		return FAILURE;
	}
	else{
		strncpy(buffer, "test_destroy_works succeeds\n", length);
		return SUCCESS;
		}
}
STATUS test_init_default_returns_nonNULL(char* buffer, int length)
{
 MY_STRING hString = NULL;
 hString = my_string_init_default();
 if(hString == NULL)
 {
 strncpy(buffer, "test_init_default_returns_nonNULL\n"
 "my_string_init_default returns NULL", length);
 return FAILURE;
 }
 else
 {
 my_string_destroy((ITEM*)&hString);
 strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
 return SUCCESS;
 }
}
STATUS test_get_size_on_init_default_returns_0(char* buffer, int length)
{
 	MY_STRING hString = NULL;
 	STATUS status;
 	hString = my_string_init_default();
 	if(my_string_get_size(hString) != 0){
 		status = FAILURE;
 		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
 		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
 		"Did not receive 0 from get_size after init_default\n", length);
 }
	 else
	 {
	 status = SUCCESS;
	 strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
 , length);
 }
 my_string_destroy((ITEM*)&hString);
 return status;
}
STATUS test_nmestre_pop_back(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("apple");
	MY_STRING result = my_string_init_c_string("appl");
	my_string_pop_back(hString);
	if(*my_string_at(hString, my_string_get_size(hString) - 1) != *my_string_at(result, my_string_get_size(result) - 1)){
		strncpy(buffer, "test_pop_back fails\n"
 		"it didn't return one pop back", length);
		my_string_destroy((ITEM*)&hString);
        	my_string_destroy((ITEM*)&result);
 		return FAILURE;
	}
	else{
		strncpy(buffer, "test_pop_back succeeds\n", length);
		my_string_destroy((ITEM*)&hString);
        	my_string_destroy((ITEM*)&result);
                return SUCCESS;
	}
}
STATUS test_nmestre_push_back(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("apple");
	MY_STRING result = my_string_init_c_string("apples");
        my_string_push_back(hString, 's');
         if(*my_string_at(hString, my_string_get_size(hString) - 1) != *my_string_at(result, my_string_get_size(result) - 1)){
                strncpy(buffer, "test_push_back fails\n"
                "it didn't return apples back", length);
		my_string_destroy((ITEM*)&hString);
        	my_string_destroy((ITEM*)&result);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_push_back succeeds\n", length);
		my_string_destroy((ITEM*)&hString);
        	my_string_destroy((ITEM*)&result);
                return SUCCESS;
        }
}
STATUS test_nmestre_concat(char* buffer, int length){
	MY_STRING LeftString = my_string_init_c_string("hello");
	MY_STRING RightString = my_string_init_c_string("goodbye");
	MY_STRING result = my_string_init_c_string("hellogoodbye");
	my_string_concat(LeftString, RightString);
	if(*my_string_at(LeftString, my_string_get_size(LeftString) - 1) != *my_string_at(result, my_string_get_size(result) - 1)){
		 strncpy(buffer, "test_concat fails\n"
                "it didn't return hellogoodbye back", length);
		my_string_destroy((ITEM*)&LeftString);
        	my_string_destroy((ITEM*)&RightString);
        	my_string_destroy((ITEM*)&result);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_concat succeeds\n", length);
		my_string_destroy((ITEM*)&LeftString);
        	my_string_destroy((ITEM*)&RightString);
       		my_string_destroy((ITEM*)&result);
                return SUCCESS;
        }
}
STATUS test_nmestre_concat2(char* buffer, int length){
        MY_STRING LeftString = my_string_init_c_string("hello");
        MY_STRING RightString = my_string_init_c_string("");
        MY_STRING result = my_string_init_c_string("hello");
        my_string_concat(LeftString, RightString);
        if(*my_string_at(LeftString, my_string_get_size(LeftString) - 1) != *my_string_at(result, my_string_get_size(result) - 1)){
                 strncpy(buffer, "test_concat fails\n"
                "it didn't return hellogoodbye back", length);
                my_string_destroy((ITEM*)&LeftString);
                my_string_destroy((ITEM*)&RightString);
                my_string_destroy((ITEM*)&result);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_concat succeeds\n", length);
                my_string_destroy((ITEM*)&LeftString);
                my_string_destroy((ITEM*)&RightString);
                my_string_destroy((ITEM*)&result);
                return SUCCESS;
        }
}

STATUS test_nmestre_empty(char* buffer, int length){
	MY_STRING hString =my_string_init_c_string("");
	if(my_string_empty(hString) != 1){
		 strncpy(buffer, "test_empty fails\n"
                "it didn't return that the string is empty", length);
		 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_empty succeeds\n", length);
		my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_empty2(char* buffer, int length){
        MY_STRING hString =my_string_init_c_string("hello");
        if(my_string_empty(hString) != 0){
                 strncpy(buffer, "test_empty2 fails\n"
                "it didn't return that the string isn't empty", length);
                 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_empty2 succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_string_c_str(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("hello"); 
	char first = *my_string_c_str(hString);

	if(*my_string_at(hString, 0) != first){
		 strncpy(buffer, "test_my_string_c_str fails\n"
                "it didn't return first character", length);
		 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_c_str succeeds\n", length);
		my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_string_extraction(char* buffer, int length){
	MY_STRING hString = NULL;
	FILE* fp;
	hString = my_string_init_default();
	fp = fopen("simple.txt", "r");
	my_string_extraction(hString, fp);
	if(fp == NULL){
		strncpy(buffer, "test_my_string_extraction fails\n"
                "it didn't extract", length);
                 my_string_destroy((ITEM*)&hString);
		 fclose(fp);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_c_extraction succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
		fclose(fp);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_string_get_size(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("hello");
	if(my_string_get_size(hString) != 5){
		strncpy(buffer, "test_my_string_get_size fails\n"
                "it didn't return the right size", length);
                 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_get_size succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_string_at(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("hello");
	if(*my_string_at(hString, 0) != 'h'){
		strncpy(buffer, "test_my_string_at fails\n"
                "it didn't return the first value", length);
                 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_at succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_string_at_negative(char* buffer, int length){
	 MY_STRING hString = my_string_init_c_string("hello");
        if(my_string_at(hString, -8) != NULL){
                strncpy(buffer, "test_my_string_at_negative fails\n"
                "it didn't return NULL", length);
                 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_at_negative succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_string_at_out_of_bounds(char* buffer, int length){
	 MY_STRING hString = my_string_init_c_string("hello");
        if(my_string_at(hString, 10) != NULL){
                strncpy(buffer, "test_my_string_at_out_of_bounds fails\n"
                "it didn't return NULL", length);
                 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_at_out_of_bounds succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_string_insertion(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("String insertion printed this!\n");
	if(my_string_insertion(hString, stdout) != 1){
		strncpy(buffer, "test_my_string_insertion fails\n"
                "it didn't insert the string in main", length);
                my_string_destroy((ITEM*)&hString);
                return FAILURE;
	}
        else{
                strncpy(buffer, "test_my_string_insertion succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}	
STATUS test_nmestre_my_string_get_capacity(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("space");
	if(my_string_get_capacity(hString) != 6){
		strncpy(buffer, "test_my_string_get_capacity fails\n"
                "it didn't return a capacity of 6", length);
                my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_get_capacity succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_init_c_string(char* buffer, int length){
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("hello");
	if(hString == NULL){
		strncpy(buffer, "test_init_c_string fails\n"
                "it didn't initialize a value", length);
                my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_init_c_string succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_string_at_NULL(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("");
        if(my_string_at(hString, 8) != NULL){
                strncpy(buffer, "test_my_string_at_NULL fails\n"
                "it didn't return NULL", length);
                 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_at_NULL succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}
STATUS test_nmestre_my_sting_get_size_empty(char* buffer, int length){
	MY_STRING hString = my_string_init_c_string("");
	if(my_string_get_size(hString) != 0){
		strncpy(buffer, "test_my_string_get_size fails\n"
                "it didn't return a size of 0 for NULL", length);
                 my_string_destroy((ITEM*)&hString);
                return FAILURE;
        }
        else{
                strncpy(buffer, "test_my_string_get_size succeeds\n", length);
                my_string_destroy((ITEM*)&hString);
                return SUCCESS;
        }
}

