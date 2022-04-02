#include "pch.h"
/* WordList source file
*
*
*	This file will contain the function definitions you will implement.
*	The function signitures may NOT be changed.  You may create your own
*	helper functions and include them in this file.
*
*	In addition to the specific instructions for each function, no function
*	should cause any memory leaks or alias m_list in any way that would result
*	in undefined behavior.
*
*	Topics: Multilevel Pointers, Dynamic Allocation, Classes
*
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif



// Do not include any other libraries

// #include"debugmem.h" 

#include"wordlist.h"
#include<iostream>
#include<cstring>

using std::cout;
using std::endl;

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;



/* Function: Wordlist Constructor
*
*	Constructs an empty Wordlist that is allocated enough space to store
*	max_words many words.  If max_words is less than 1, set m_list to nullptr
*	and the other member variables should be made consistent with this state.
*/
WordList::WordList(const int max_words) {
	m_count = 0;
	m_max = max_words;
	if (m_max < 1)
		m_list = nullptr;
	else
	{
		m_list = new char*[m_max];
		for( unsigned int i = 0; i < m_max; i++) m_list[i] = nullptr;
	}
		

}


/* Function: Wordlist Copy Constructor
*
*	Constructs a Wordlist that is a copy of an existing WordList
*/
WordList::WordList(const WordList &other) {
	
	m_count = other.m_count;
	m_max = other.m_max;
	
	m_list = new char*[m_max];
	
	for (unsigned int i = 0; i < m_count; i++)  m_list[i] = other.m_list[i];
}


/* Function: Wordlist Destructor
*
*	Cleans up WordList's dynamically allocated memory.
*/
WordList::~WordList() {

	for (unsigned int i = 0; i < m_count; i++) delete[] m_list[i];
	delete[] m_list;

}

/* Function: printList
*
*	Prints all the words in WordList in a single line with spaces between each
*	word, then followed by a newline after the last word. Returns the number
*	of words printed.  If m_list is nullptr there is nothing to print, return -1.
*/
int	WordList::print() const {
	unsigned int prt_words = 0;
	if (m_list != nullptr)
	{
		for (unsigned int i = 0; i < m_count; i++)
		{
			std::cout << m_list[i] << " ";
			prt_words += 1;
		}
		std::cout <<std::endl;
		return prt_words;
	}
	return -1;

}



/* Function: at
*
*	Returns the word at the index position in the WordList.
*	return nullptr if the index is out of bounds.
*/
char* WordList::at(const int index) const {

	if ((unsigned int) index < m_count && index > 0)
		return m_list[index];
	return nullptr;

}


/* Function: count
*
*	Returns the number of words currently stored in WordList.
*/
int	WordList::count() const {

	if (m_count > 0)
		return m_count;
	return -1;

}


/* Function: add
*
*	Adds the word into WordList (words have no spaces).  If WordList does not have
*	enough space to add word, addWord will resize with just enough space to allow for
*	the addition of word. If addWord needed to resize then return 1, otherwise if there
*	already enough space to add word without resizing, return 0. If word is empty
*	do nothing return -1. If m_list was nullptr, everything above still holds true except
*	return -2.
*/
int	WordList::add(const char word[]) {

	
	if (word == "")
		return -1;
	if (m_max == m_count)
	{
		m_max += 1;
		char** temp = new char*[m_max];

		for (unsigned int i = 0; i < m_count; i++) {
			temp[i] = m_list[i];
			if (i + 1 == m_count)
			{
				temp[m_count] = new char[strlen(word) + 1];
				for (int j = 0; j < strlen(word) + 1; j++) temp[m_count][j] = word[j];
				
				delete[] m_list;
				
				m_count += 1;
				m_list = new char*[m_max];
				
				for (unsigned int k = 0; k < m_count; k++)
					m_list[k] = temp[k];
				
				delete[] temp;
				
				return 1;
			}
		}
		
	}
	else if(m_max > m_count)
	{
		m_list[m_count] = new char[strlen(word) + 1];
		for(int i = 0; i < strlen(word) + 1 ; i++) m_list[m_count][i] = word[i];
		m_count += 1;
		
		return 0;
	}
	return -2;
}//completed and tested


/* Funtion: remove
*
*	If m_list is nullptr, returns -1.  Otherwise, searches for every
*	occurrence of word[], and removes that word of the list, returns
*	the number of words removed.
*/
int	WordList::remove(const char word[]) {
	int num_words_removed = 0;
	char** temp = new char*[m_max];
	
	if (m_list != nullptr)
	{
		for ( unsigned int i = 0; i < m_count;i++)
		{
			if (m_list[i] == word)
			{
				if (m_list[i + 1] != nullptr) temp[i] = m_list[i + 1];
				else temp[i] = nullptr;
				
				num_words_removed += 1;
				m_count -= 1;
			}
			else
				temp[i] = m_list[i];
		}
		delete[] m_list;
		for (unsigned int i = 0; i < m_count - num_words_removed; i++)
			m_list[i] = temp[i];
		delete[] temp;
		return num_words_removed;
	}
	return -1;
}


/* Funtion: append
*
*
*	Appends the contents of other to the WordList.  If WordList does
*	not have enough space appendList should dynamically allocate enough space
*	to append the contents of other to WordList, returns number of words
*	appended.  If other is nullptr or empty appendList does nothing and
*	returns -1. If this WordList::m_list is nullptr everything above still
*	holds but returns -2.
*
*	Note the pointer parameter type as opposed to reference type.
*/
int	WordList::append(const WordList* other) {

	if (other == nullptr) return -1;
	if (m_list == nullptr) return -2;
	if ((m_max - m_count) < other->m_count)
	{
		m_max += (other->m_count - (m_max - m_count));
		char** temp = new char*[m_max];
		for (unsigned int i = 0; i < m_count; i++)
			temp[i] = m_list[i];
		for (unsigned int i = m_count, j = 0; i < m_max, j < other->m_count; i++, j++)
			temp[i] = other->m_list[j];
		m_count += other->m_count;
		delete[] m_list;
		
		m_list = new char*[m_max];
		for (unsigned int i = 0; i < m_count; i++)
			m_list[i] = temp[i];
		
		delete[] temp;
		return other->m_count;
	}
	else
	{
		for (unsigned int i = m_count, j = 0; i < m_max, j < other->m_count; i++, j++)
		{
			m_list[i] = other->m_list[j];
			m_count += 1;
		}
		return other->m_count;
	}

}//completed and tested


/* Funtion: find
*
*	Finds the first occurrence of the word in the WordList
*	returns the position of that word in the list.  Otherwise,
*	if the word is not in the WordList or if m_list is nullptr
*	return -1.
*/
int WordList::find(const char word[]) const {

	// TODO:
	if (m_list == nullptr) return -1;
	if (m_list != nullptr)
	{
		for ( unsigned int i = 0; i < m_count; i++)
		{
			if (strcmp(m_list[i], word) == 0) {
				return i;
			}
		}
		return -1;
	}
}//completed and tested


/* Funtion: sort
*
*	If m_list is nullptr return -1.  If there is only one word
*	in the list return 1.  Otherwise, sortList sorts the
*	words in WordList in ascending order.  Returns 0 on
*	success.
*/
int	WordList::sort() {

	// TODO:
	char* temp;
	if(m_list == nullptr) return -1;
	if (m_count == 1) return 1;

		for (unsigned int i = 1; i < m_count; i++)
		{
			for (unsigned int j = 1; j < m_count; j++)
			{
				if (strcmp(m_list[j - 1], m_list[j]) > 0)
				{
					temp = m_list[j - 1];
					m_list[j - 1] = m_list[j];
					m_list[j] = temp;
				}
			}
		}
		return 0;
}//completed and tested


/* Funtion: Assignment Operator
*
*	Overload the assignment operator for WordList.  Makes a deep
*	copy from other to this WordList.
*/
WordList& WordList::operator=(const WordList &other) {
	if (this == &other) return *this;
	
	m_count = other.m_count;
	m_max = other.m_max;

	delete[] m_list;
	m_list = new char*[m_max];
	 
	for (unsigned int i = 0; i < m_count; i++)
	{
		if (other.m_list[i] == nullptr) m_list[i] = nullptr;
		else
		{
			for (unsigned int j = 0; j < strlen(other.m_list[i] + 1); j++)
				m_list[i][j] = other.m_list[i][j];
		}
		
	}
		 
	return *this;
}//completed and tested