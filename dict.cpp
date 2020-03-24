//============================================================================
// Name        : COLLEGE_HUEMOR.cpp
// Author      : newname
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "dict.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <limits>
#include <string.h>
#include <sstream>


using namespace std;

// a flag for operations that searches for a string
bool string_is_found_do_not_repeat = false;

long int NumberOfRightWords = 0, NumberOfCharacters = 0, NumberOfWrongWords = 0, NumberOfDistinctWords = 0, Iam_the_Most_frequent = 0;
int general_purpose_index = 0, arr_index = 0, Locked_Flag = 0;

//long int Try_Number_OF_Char = 0;
bool Search_For_Pattern_With_Line_Numbers = false;

// To fetch the word from the dictionary
char general_purpose_string[30] = {'/'}, general_purpose_string_stack[30] = {'/'};

// Always make sure you make argv[1] a lower case litters
const char *operationsArray[NoOfOperations] = {
		"wordCount", "distWords", "charCount", "frequentWord",
		"countWord", "starting", "containing", "search"};


// Default constructor for a list
list:: list(const char *FileToOpen)
{

	/* start the list darling */

	cout << "Default constructor for variable " << this << " is called \n";

	// Reset the list
	NumberOfOccurances = 0;
	NumberOfWords = 0;

	// All point to root node (Parent node)
	head = NULL;
	tail = NULL;

	// Define a general root pointer to remove any node at any instance
	general_root_pointer_for_any_Independent_node = NULL;

	/* End of the list darling */


	/* Start of dictionary in loading stage darling*/

	dict_root = NULL;
	ptr_tmp = NULL;

	// Error handling required
	if(!Dictionary_Load(FileToOpen))
	{
		cout << "File not found\n";
	}

	// you should proceed to the commands files
	else
	{

	}

	/* End of dictionary in loading stage darling*/
}

// load dictionary in the trie
bool list :: Dictionary_Load(const char *FileToOpen)
{
	// Define the file that contains the dictionary
	ifstream file;

	int iterations = 0, line_Number = 0;

	// Open dictionary
	file.open(FileToOpen, ios::in);

	// Check for file status
	if (!file.is_open())
	{
		cout << "error opening the file \n";
		return false;
	}

	// For number of chars
	file.ignore( std::numeric_limits <std::streamsize>::max());
	std::streamsize length = file.gcount();
	NumberOfCharacters = length;
	file.seekg( 0, std::ios_base::beg );

	// Start the tree
	dict_root = new dict_node;

	// Check for error allocating
	assert(dict_root != NULL);

	if(!dict_root)
	{
		return false;
	}

	// Root is a basic root, don't play with it
	dict_root -> is_word = false;
	dict_root -> parent_name = '.';
	dict_root -> Repeated_times = 0;
	dict_root -> line_Number_is = 0;

	// Initialize all children to NULL; avoid grabage
	for (int j = 0; j < N; j++)
	{
		dict_root -> children[j] = NULL;
	}

    // Buffer for a word in a line
    string word(LENGTH, '/');

    // Buffer for a line fetched from the file
    string line;

    // Insert words into trie
     while (!file.eof())
     {
    	 // Get a whole line
 		getline(file, line);
 		// Save the line number
 		line_Number++;

 		// Initialize ss to read the whole line for further manipulation
 		stringstream ss(line);

 		// Get a word from the buffered line
 		while(std:: getline(ss, word, ' '))
 		{
			// Restart for every new dictionary from the top
			ptr_tmp = dict_root;
			iterations = 0;

			// Iterate over the whole word
			for(int i = 0; word[i] != '\0'; i++)
			{
				// tmp to store the char's index
				int tmp = 0;
				iterations++;

				// Check for upper case
				if(word[i] >= 'A' && word[i] <= 'Z')
				{
					// index from 0 to 25 are for alphabets
					word[i] = word[i] + 32;
					tmp = word[i] - 97;
				}

				// Check for numbers
				else if(word[i] >= '0' && word[i] <= '9')
				{
					// index from 26 to 34 are for numbers
					tmp = word[i] - 48 + 26;
				}

				// Final check for small case
				else if((word[i] >= 'a' && word[i] <= 'z'))
						tmp = word[i] - 97;

				// if any other data, neglect inserting it
				else
					tmp = 55;

				/* Start the party of insertion, Supply the tree */

				// Invalid data has invalid index
				if(tmp == 55)
				{
					// Ignore it but still keep iterating for the word
				}

				// Normal insertion to go
				else
				{
					// first time in the array's index (tmp)
					if(ptr_tmp -> children[tmp] == NULL)
					{
						ptr_tmp -> children[tmp] = new dict_node;
						// Check for error allocating
						assert(ptr_tmp -> children[tmp] != NULL);

						ptr_tmp -> children[tmp] -> is_word = false; // no sure if right or not

						ptr_tmp -> children[tmp] -> parent_name = word[i];

						ptr_tmp -> children[tmp] -> Repeated_times = 0;

						/* Start of Accumulating lines */
						ptr_tmp -> children[tmp] -> line_Number_is = NULL;
						/* End of Accumulating lines */

						if(!(ptr_tmp -> children[tmp]))
						{
							cout << "error allocating new node in dict \n";
							return false;
						}

						// Initialize all indices to Null and is word to false
						for(int k = 0; k < N; k++)
						{
							ptr_tmp -> children[tmp] -> children[k] = NULL;
						}
						ptr_tmp = ptr_tmp -> children[tmp];
					}

					// if an address already existed in this index (tmp)
					else
					{
						// exsist node now assigned to ptr
						ptr_tmp = ptr_tmp -> children[tmp];
					}
				}
			}

			// remember to check if the pointer is still at the root node
			// this means it's just one char and it's a wrong char

			/* remove me if errors happened */
			if(ptr_tmp == dict_root)
			{
				// "wrong word indicated and not inserted" i.e: ., ;, @, !
			}
			else
			{
				ptr_tmp -> is_word = true;

				/* Lines accumulating starts */

				// This means this is the very first line for this word
				if(ptr_tmp -> line_Number_is == NULL)
				{
					ptr_tmp -> line_Number_is = new node;
					// Check for error allocating
					assert(ptr_tmp -> line_Number_is != NULL);

					// Take the line please
					ptr_tmp -> line_Number_is -> line = line_Number;

					// Terminate with NULL for future reference
					ptr_tmp -> line_Number_is -> next = NULL;
				}

				// This means this word already exists in other lines, start accumulating the list
				else
				{
					// Start with setting the pointer to the very beginning of the node list
					general_root_pointer_for_any_Independent_node = ptr_tmp -> line_Number_is;

					// The dictionary is be design an inorder linked list, first come first line XDD
					while(general_root_pointer_for_any_Independent_node -> next != NULL)
					{
						// Loop till you find the null no need for ordering the numbers, the dictionary is self ordered
						general_root_pointer_for_any_Independent_node = general_root_pointer_for_any_Independent_node -> next;
					}

					// Extra check for the same line just in case it exists already
					if(general_root_pointer_for_any_Independent_node -> line == line_Number)
					{
						// Don't repeat lines for the same word
					}

					// Only different lines are added to the list
					else
					{
						// Once you found the tail insert the new line
						node *tmp = new node;
						// Check for error allocating
						assert(tmp != NULL);

						tmp -> line = line_Number;
						tmp -> next = NULL;

						// Append to the list
						general_root_pointer_for_any_Independent_node -> next = tmp;
					}

					// Reset the general root pointer
					general_root_pointer_for_any_Independent_node = NULL;
				}

				/* Lines accumulating is done */

				/* Side operations during insertion including repeated times, number of words and the most frequent */

				/* Repeated time for each word is added while loading*/
				ptr_tmp -> Repeated_times = ptr_tmp -> Repeated_times + 1;

				// Check if repeated so it's not a distinct
				if(ptr_tmp -> Repeated_times == 2)
				{
					NumberOfDistinctWords = NumberOfDistinctWords - 1;
				}

				// It's your first time indeed
				else if(ptr_tmp -> Repeated_times == 1)
					NumberOfDistinctWords++;

				else;

				/* Frequent word is decided here */
				if(Iam_the_Most_frequent <= ptr_tmp -> Repeated_times)
					Iam_the_Most_frequent = ptr_tmp -> Repeated_times;

				NumberOfWords++;

				/* Side operations during insertion*/
			}

			// In general increase the number of characters for the file
			//Try_Number_OF_Char += iterations;

			/* end of remove */
		}
	 }


     cout << "Dictionary is loaded \n";
     file.close();
	return true;
}

// Returns true if word is in dictionary else false
bool list :: check(const char *word, int mode)
{
    // Restart from beginning
    int k = 0;
    ptr_tmp = dict_root;

    // Buffer for word
    while (word[k] != '\0')
    {
        k++;
    }
    char *new_word = new char[k];
	// Check for error allocating
	assert(new_word != NULL);

    // To solve the UPPER_CASE problem
    for (int n = 0; n < k; n++)
    {
        if (word[n] >= 'A' && word[n] <= 'Z')
        {
            if (word[n] + 32 == tolower(word[n]))
            {
                new_word[n] = (char) tolower((word[n]));
            }
            else
            {
                delete [] new_word;
                ptr_tmp = dict_root;
                NumberOfWrongWords++;
                return false;
            }
        }
        else
        {
            new_word[n] = word[n];
        }
    }

    // start traversing trie
    for (int j = 0; j < k; j++)
    {
        int tmp = 0;

        if(new_word[j] >= '0' && new_word[j] <= '9')
		{
			// index from 26 to 34 are for numbers
			tmp = new_word[j] - 48 + 26;
		}
		// DO NOT INSERT ANY OTHER DATA
		else if((new_word[j] >= 'a' && new_word[j] <= 'z'))
			tmp = new_word[j] - 97;
		else
			tmp = 55;

		if(tmp == 55)
		{
			//cout << "wrong character is escaped :: " << new_word[j] << "\n";
		}
		else
		{
			 // checking for index value
			if (ptr_tmp -> children[tmp] == NULL)
			{
				delete [] new_word;
				ptr_tmp = dict_root;
				NumberOfWrongWords++;
				return false;
			}
			else
			{
				ptr_tmp = ptr_tmp -> children[tmp];
			}
		}
    }

    // Checking for is_word field in Dictionary
    if (ptr_tmp -> is_word == true)
    {
        delete [] new_word;

        if(mode == WORD_COUNT)
        {
        	cout << word << " is repeated " << ptr_tmp -> Repeated_times << " times\n";
        }

        ptr_tmp = dict_root;
        return true;
    }

    delete [] new_word;
    ptr_tmp = dict_root;
    cout << "Word not found\n";
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool list :: unload(void)
{
    dict_node *last_before_stack = NULL;
    int i = 0;

    // looping over the root its self
    for (i = 0; i < N ; i++)
    {
        if (ptr_tmp -> children[i] == NULL)
        {

        }
        else
        {
        	/* If error please delete me */
        	if(ptr_tmp -> children[i] -> is_word == true)
        	{
               	general_root_pointer_for_any_Independent_node = ptr_tmp -> children[i] -> line_Number_is;
				Delete_VIP();
        	}

        	/* End of delete */

            last_before_stack = ptr_tmp;
            ptr_tmp = ptr_tmp -> children[i];

            unload();
            ptr_tmp = last_before_stack;
        }
    }

    if (i == N)
    {
        delete(ptr_tmp);
        return true;
    }
    return false;
}

// Delete from here, Do not delete directly from DELETE_WHILE_LIST
bool list :: Delete_VIP()
{
	// remember to set the general root address before calling this function
	/*	CRITICAL WARNING!!! SEGMENTATION FAULT!!!!	*/
	head = general_root_pointer_for_any_Independent_node;
	Delete_Whole_List();

	return true;
}

// Recursive Deletion
bool list :: Delete_Whole_List()
{
	// Buffer to save the previous condition of ptr
	node *last_before_stack = NULL;

	// Checking on the next field
	if(head -> next != NULL)
	{
		last_before_stack = head;
		head = head -> next;
		//cout << head -> line << "exist, then Loop in the stack \n";
		Delete_Whole_List();
		head = last_before_stack;
	}

	//cout << "Current Node item is " << head -> line << " and is deleted\n";
	// free current node and return
	delete(head);
	NumberOfWords = 0;

	return true;
}

// Search words that starts with specific string
bool list :: starting_with(const char *word)
{
	// Always start from the root point
	ptr_tmp = dict_root;
	int i = 0;

    // tmp for index movement
    int tmp = 0, wrong_char = 0;

    // Reset all generals
    for(int i = 0; i < general_purpose_index; i++)
    {
    	general_purpose_string[i] = '\0';
    	general_purpose_string_stack[i] = '\0';
    }

    general_purpose_index = 0;


    // looping over the root its self
    for (i = 0; word[i] != '\0' ; i++)
    {
    	// Check for upper case index
    	if(word[i] >= 'A' && word[i] <= 'Z')
    		tmp = word[i] + 32 - 97;
    	// Check for numbers index
    	else if(word[i] >= '0' && word[i] <= '9')
    		tmp = word[i] - 48 + 26;
    	// Default for alphabets
    	else if(word[i] >= 'a' && word[i] <= 'z')
    		tmp = word[i] - 97;
    	// Wrong chars aren't welcome
    	else
    	{
    		wrong_char = 1;
    		break;
    	}

    	// Check to see if there is data there
    	if(ptr_tmp -> children[tmp] == NULL)
    	{
    		// No data in here and terminate the loop
    		//cout << "this place is empty, terminating .. \n";
        	cout << "Word not found\n";
    		return false;
    	}

    	else
    		ptr_tmp = ptr_tmp -> children[tmp];
    	general_purpose_string[general_purpose_index] = ptr_tmp -> parent_name;
    	general_purpose_index++;

    	//cout << "the value in here is :: " << ptr_tmp -> parent_name << "\n";
    }

    // Check to see if the line is a word
    if(ptr_tmp -> is_word == true)
    	cout << word << "\n";

    // Confirm the pointer position
    // cout << "The pointer after the for loop is at character :: " << ptr_tmp -> parent_name << "\n";

    // Start traversing the words and print them out
    starting_with_helper(word);
    cout << "\n";

    if(string_is_found_do_not_repeat == true)
    {
    	cout << "a7a? \n";
    	string_is_found_do_not_repeat = false;
    }

    else
    {
    	cout << "Word not found\n";
    }

    // Don't search for chars that aren't words or numbers
    if(wrong_char)
    	return false;

    return true;
}

// Help starting with function
bool list :: starting_with_helper(const char *word)
{
	dict_node *last_before_stack = NULL;
	int general_purpose_index_stack = 0;

    for (int i = 0; i < N ; i++)
    {
        if (ptr_tmp -> children[i] == NULL)
        {

        }
        else
        {
        	last_before_stack = ptr_tmp;
            ptr_tmp = ptr_tmp -> children[i];
            general_purpose_string[general_purpose_index] = ptr_tmp -> parent_name;
            general_purpose_index++;

            // Save the current location before looping in the stack again
            general_purpose_index_stack = general_purpose_index;

            // save the current string before looping in the stack again
            // Terminate with a null character before copying
            general_purpose_string[general_purpose_index] = '\0';
            strcpy(general_purpose_string_stack, general_purpose_string);

            starting_with_helper(word);

            // reverse the copying process to keep the old data
            strcpy(general_purpose_string, general_purpose_string_stack);

            // Invalid index coming back from the next frame
            general_purpose_index = general_purpose_index_stack - 1;

            // Invalid character returned from the next frame
            general_purpose_string[general_purpose_index] = 0;

            ptr_tmp = last_before_stack;
        }
    }

    if(ptr_tmp -> is_word == true)
    {
    	// For error handling sake
    	string_is_found_do_not_repeat = true;

    	// 1- Prepare for printing
    	general_purpose_string[general_purpose_index] = '\0';

    	// 2- print the string
    	cout << general_purpose_string << ": " << ptr_tmp -> Repeated_times << "\t";

    	// 3-general purpose index and the string are becoming zero
    	general_purpose_index = 0;
    }
    return true;
}

// Help reset the pointer to the starting address of root
bool list :: Searching_For_Pattern_Initialize(const char *word)
{
	ptr_tmp = dict_root;
	cout << "searching :: \n";
    general_purpose_index = 0;

	Searching_For_Pattern(word, Search_For_Pattern);
	cout << "\n";

    if(string_is_found_do_not_repeat == true)
    {
    	string_is_found_do_not_repeat = false;
    }

    else
    {
    	cout << "Word not found\n";
    }
	return true;
}

// Help reset the pointer to the starting address of root
bool list :: Searching_For_Pattern_With_lines_Initialize(const char *word)
{
	ptr_tmp = dict_root;
	cout << "searching for words and printing their lines:: \n";

	// Prepare for line printing
	Search_For_Pattern_With_Line_Numbers = true;
    general_purpose_index = 0;

	Searching_For_Pattern(word, Search_For_Pattern);

	Search_For_Pattern_With_Line_Numbers = false;

    if(string_is_found_do_not_repeat == true)
    {
    	string_is_found_do_not_repeat = false;
    }

    else
    {
    	cout << "Word not found\n";
    }

	return true;
}


/*
// Searching the whole dictionary for a pattern
bool list :: Searching_For_Pattern(const char *word)
{
	dict_node *last_before_stack = NULL;
	int general_purpose_index_stack = 0, arr_index_stack = 0;

    for (int i = 0; i < N ; i++)
    {
        if (ptr_tmp -> children[i] == NULL)
        {

        }
        else
        {
        	last_before_stack = ptr_tmp;
            ptr_tmp = ptr_tmp -> children[i];
            general_purpose_string[general_purpose_index] = ptr_tmp -> parent_name;
            general_purpose_index++;

            if((ptr_tmp -> parent_name == word[arr_index]) && !Locked_Flag)
            {
            	arr[arr_index] = 1;
            	arr_index++;
            	if(arr_index >= 3)
            	{
            		Locked_Flag = 1;
            	}
            }
            else
            {
            	for(int j = 0; j < 3; j++)
            	{
            		arr[j] = 0;
            	}
            	arr_index = 0;
            }

            // Save the current location before looping in the stack again
            general_purpose_index_stack = general_purpose_index;
           	arr_index_stack = arr_index;

            // save the current string before looping in the stack again
            // Terminate with a null character before copying
            general_purpose_string[general_purpose_index] = '\0';
            arr[arr_index] = '\0';

            strcpy(general_purpose_string_stack, general_purpose_string);
            strcpy(arr_stack, arr);

            Searching_For_Pattern(word);

            // reverse the copying process to keep the old data
            strcpy(general_purpose_string, general_purpose_string_stack);
            strcpy(arr, arr_stack);

            // Invalid index coming back from the next frame
            general_purpose_index = general_purpose_index_stack - 1;
            arr_index = arr_index_stack;

            // Invalid character returned from the next frame
            general_purpose_string[general_purpose_index] = 0;

            ptr_tmp = last_before_stack;
        }
    }

    if(ptr_tmp -> is_word == true)
    {
    	// 1- Check for arr for whole ones
    	for(int k = 0; k < 3; k++)
    	{
    		if(!arr[k])	// Check if correct to inverse the null character
    			return false;
    	}
    	cout << general_purpose_string << "\n";

    }
    return true;
}
*/

bool list :: Searching_For_Pattern(const char *word, int mode)
{
	dict_node *last_before_stack = NULL;
	int general_purpose_index_stack = 0;

    for (int i = 0; i < N ; i++)
    {
        if (ptr_tmp -> children[i] == NULL)
        {

        }
        else
        {
        	last_before_stack = ptr_tmp;
            ptr_tmp = ptr_tmp -> children[i];
            general_purpose_string[general_purpose_index] = ptr_tmp -> parent_name;
            general_purpose_index++;

            // Save the current location before looping in the stack again
            general_purpose_index_stack = general_purpose_index;

            // save the current string before looping in the stack again
            // Terminate with a null character before copying
            general_purpose_string[general_purpose_index] = '\0';

           // strcpy(general_purpose_string_stack, general_purpose_string);
            strncpy(general_purpose_string_stack, general_purpose_string, sizeof(general_purpose_string_stack));

            Searching_For_Pattern(word, mode);

            // reverse the copying process to keep the old data
            strncpy(general_purpose_string, general_purpose_string_stack, sizeof(general_purpose_string));

            // Invalid index coming back from the next frame
            general_purpose_index = general_purpose_index_stack - 1;

            // Invalid character returned from the next frame
            general_purpose_string[general_purpose_index] = '\0';

            ptr_tmp = last_before_stack;
        }
    }

    switch(mode)
    {
    	// Check for pattern
    	case Search_For_Pattern:
    		 if(ptr_tmp -> is_word == true)
			 {
				// 1- Prepare for printing
				general_purpose_string[general_purpose_index] = '\0';

				// 2- general purpose index and the string are becoming zero
				general_purpose_index = 0;

				if(strlen(general_purpose_string) == strlen(word))
				{
					// Direct comparison for strings, returns zero if equal
					if(strcmp(general_purpose_string, word) == 0)
					{
				    	// For error handling sake
				    	string_is_found_do_not_repeat = true;

				    	cout << general_purpose_string << ": " << ptr_tmp -> Repeated_times << "\t";

						//cout << general_purpose_string << "\n";
						// Set the pointer to the very start of the local linked list
						general_root_pointer_for_any_Independent_node = ptr_tmp -> line_Number_is;
						List_show_Whole();
					}
				}

				else if(strlen(general_purpose_string) > strlen(word))
				{
					string s = general_purpose_string;

					// Paten check
					unsigned int x = s.find(word);
					if(x != string::npos)
					{
				    	// For error handling sake
				    	string_is_found_do_not_repeat = true;


						//cout << general_purpose_string << "\n";
						if(Search_For_Pattern_With_Line_Numbers == true)
						{
							cout << general_purpose_string << ": lines ";
							// Set the pointer to the very start of the local linked list
							general_root_pointer_for_any_Independent_node = ptr_tmp -> line_Number_is;
							List_show_Whole();
						}

						// updated
						else
					    	cout << general_purpose_string << ": " << ptr_tmp -> Repeated_times << "\t";

					}
				}

				// wrong word
				else;
			 }

    		break;

    		// Check for distinct word to print
    	case Distinct_words_process:

    		// It's for distinct words function
    		if(ptr_tmp -> is_word == true && ptr_tmp -> Repeated_times == Iam_the_Most_frequent)
    		{
				// 1- Prepare for printing
				general_purpose_string[general_purpose_index] = '\0';

    			cout << general_purpose_string <<" ";

				// 3-general purpose index and the string are becoming zero
				general_purpose_index = 0;
    		}

    		break;

    	default:
    		break;
    }

    return true;
}

// Show the whole list
bool list :: List_show_Whole()
{
	node *ptr = general_root_pointer_for_any_Independent_node;

	// WARNING:: Head is root, can be accessed

	//cout << "iam showing the numbers \n";
	do
	{
		cout << ptr -> line << " ";
		ptr = ptr -> next;
	}
	while(ptr != NULL);

	cout << "\n";

	return true;
}

// Start frequent function from here
bool list :: Dictionary_Frequent_Word_Initialize(const char *word)
{
	int mode = Distinct_words_process;

	ptr_tmp = dict_root;

	cout << "Most frequent word is: ";

	Searching_For_Pattern(word, mode);

	// For demonstration purpose
	cout << "\n";

	return true;

}

// Print the number of chars
bool list :: Dictionary_size_chars()
{
	cout << NumberOfCharacters << " characters\n";
	//cout << Try_Number_OF_Char << " are the number of characters in my typeee\n";

	return true;
}

// Print number of words
bool list :: Dictionary_size_words()
{
	cout << NumberOfWords << " words\n";
	return true;
}

// Print number of distinct words
bool list :: Dictionary_distinct_words()
{
	cout << NumberOfDistinctWords << " distinct words\n";
	return true;
}

// For error handling sake
void list :: Reset_all_Generals()
{
    // Reset all generals
    for(int i = 0; i < general_purpose_index; i++)
    {
    	general_purpose_string[i] = '\0';
    	general_purpose_string_stack[i] = '\0';
    }

    general_purpose_index = 0;
}

// Deconstructor is here for you bitch
list :: ~list()
{
	ptr_tmp = dict_root;
	unload();
	cout << "Deconstructor is called for " << this << " object\n";
}


/* ALL COMING ARE FOR OPERATIONS */

// Check for the required operation and execute it if it's a valid one
int CheckMyOperationAndExecute(char *x, int argc, char **y)
{
	int i = 0;

	// Iterate over each operation to check
	for(i = 0; i < NoOfOperations; i++)
	{
		// Compare strings to find an operation from the list
		if(My_Compare_string(x, operationsArray[i]))
		{
			// Go execute the corresponding function
			break;
		}

		// Operation is found and break the loop
		else;
	}


	// Check for operation required and raise its flag
	switch(i)
	{
		case 0:
			break;

		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;
		case 7:
			break;

		case 8:
			break;

		default:
			cout << "Undefined Command" << "\n";
			return EXIT_FAILURE;
			break;
	}

	return EXIT_SUCCESS;
}


// Compare 2 strings for either matching or not
int My_Compare_string(const char *str1, const char* str2)
{
	int equal = 0;
	equal = LengthString(str1, str2, Normal_MODE_FOR_STRING_LENGTH_COMPARISON);		// 1
	if(equal)
	{
		for(int i = 0; str1[i] != '\0'; i++)
		{
			if(str1[i] != str2[i])
				// False = 0
				return 0;
		}
		// True = 1
		return 1;
	}
	// False = 0
	return 0;
}


// Get string length or compare two strings for the same length
int LengthString(const char *str1, const char *str2, int mode)
{
	int i = 0, k = 0;
	if(mode == ABNORMAL_MODE_FOR_STRING_LENGTH_RETURN)
	{
		while(str1[i] != '\0')
		{
			i++;
		}
		i++;

		return i;
	}
	else
	{
		while(str1[i] != '\0')
		{
			i++;
		}

		while(str2[k] != '\0')
		{
			k++;
		}

		if(k == i)
		{
			// True = 1
			return 1;
		}
		// false = 0
		return 0;
	}

	// false = 0
	return 0;
}


