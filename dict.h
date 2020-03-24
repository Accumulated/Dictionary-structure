/*
 * COLLEGE_HUEMOR.h
 *
 *  Created on: Mar 7, 2020
 *      Author: newname
 */

#ifndef DICT_H_
#define DICT_H_

// Represents number of children for each node in a trie
#define N	36
#define LENGTH	47

#define WORD_COUNT	0

#define Search_For_Pattern	0
#define Distinct_words_process	1

#define NORMAL_OPERATION	1


#define NoOfOperations	8

// Important definitions for String length function to operate correctly
#define ABNORMAL_MODE_FOR_STRING_LENGTH_RETURN		0
#define Normal_MODE_FOR_STRING_LENGTH_COMPARISON	1


typedef int listelementType;

extern long int NumberOfRightWords, NumberOfWrongWords, NumberOfCharacters, NumberOfDistinctWords;
extern long int Iam_the_Most_frequent;
extern long int Try_Number_OF_Char ;

// No direct submission in class variable
class list
{
	private:
		// State variable
		int NumberOfOccurances, NumberOfWords;

		// My structure
		struct node
		{
			listelementType line;
			node *next;
		};

		// Head to start with and tail to insert from
		node *head, *tail, *general_root_pointer_for_any_Independent_node;

		// Represents a node in a trie
		struct dict_node
		{
		    bool is_word;
		    dict_node *children[N];
		    node *line_Number_is;
		    char parent_name;
		    int Repeated_times;
		};

		dict_node *dict_root, *ptr_tmp;

	public:

		// Construct and Destruct

		// Default constructor
		list(const char *FileToOpen);
		~ list();


		// Functions go right here
		bool Dictionary_Load(const char *FileToOpen);
		bool check(const char *word, int mode);
		bool starting_with(const char *word);
		bool starting_with_helper(const char *word);
		bool Searching_For_Pattern(const char *word, int mode);
		bool Searching_For_Pattern_Initialize(const char *word);
		bool Searching_For_Pattern_With_lines_Initialize(const char *word);
		bool Dictionary_Frequent_Word_Initialize(const char *word);
		bool Dictionary_distinct_words(void);
		bool Dictionary_size_chars(void);
		bool Dictionary_size_words(void);
		bool unload(void);
		bool Delete_Whole_List();
		bool Delete_VIP();
		bool List_show_Whole();
		void Reset_all_Generals(void);






};

void MyToLower(char *x);
int My_Compare_string(const char *str1, const char* str2);
int LengthString(const char *str1, const char *str2, int mode);



#endif /* DICT_H_ */

