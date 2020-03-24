/*
 * app.c
 *
 *  Created on: Mar 7, 2020
 *      Author: newname
 */


#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include "dict.h"

using namespace std;


int main(int argc, char *argv[])
{
	ifstream file;
    // Buffer for a word
    //char word[LENGTH];

	list my_list("m.txt");


	// 1- my_list.Dictionary_size_words();
	// 2- my_list.Dictionary_distinct_words();
	// 3- my_list.Dictionary_size_chars();
	// 4- my_list.Dictionary_Frequent_Word_Initialize("start");

	// 5-
		/*
		my_list.check("1234567890", WORD_COUNT);
		my_list.check("new", WORD_COUNT);
		my_list.check("1234567890", WORD_COUNT);
		*/

	// 6-
		/*
		my_list.starting_with("11");
		my_list.starting_with("11");
		my_list.starting_with("a");
		my_list.starting_with("a");
		 */

	// 7-
		/*
		my_list.Searching_For_Pattern_Initialize("n");
		my_list.Searching_For_Pattern_Initialize("n");
		my_list.Searching_For_Pattern_Initialize("n");
		my_list.Searching_For_Pattern_Initialize("new");
		 */

	// 8-
		/*
		my_list.Searching_For_Pattern_With_lines_Initialize("123456789");
		my_list.Searching_For_Pattern_With_lines_Initialize("new");
		*/


}


