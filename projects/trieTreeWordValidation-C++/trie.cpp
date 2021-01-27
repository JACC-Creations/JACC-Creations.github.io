#include "trie.h"
#include <string>
#include <iostream>

/*
Authors:
Tim Roberts:
- Constructors()
- addWord()
- lookup()
- destructor()

Jared Cotton:
- suggest()
- finNumTerminals()
*/

/*
Author: Tim Roberts
*/
Trie::Trie()
{
	root = new Node();
}

/*
Author: Tim Roberts

Parameters:
data = an array of strings to populate the Trie with
sz = the size of the array 'data'
*/
Trie::Trie(std::string data[], int sz)
{
	root = new Node();

	for (int i = 0; i < sz; ++i)
		addWord(data[i]);
}

/*
Author: Tim Roberts

Description: Adds a new word to the Trie

Parameters:
word = word to be added

Return Value:
none
*/
void Trie::addWord(const std::string &newWord)
{
	Node *curr = root;
	int len = newWord.length();

	for (int i = 0; i < len; i++)
	{
		int index = newWord[i] - 'a';

		Node *node = curr->children[index];

		if (!node)
		{
			node = new Node();
			curr->children[index] = node;
		}
		curr = node;
	}
	curr->isTerminal = true;
}

/*
Author: Tim Roberts

Description: Attempts to find a word in the Trie.

Parameters:
word = word to be found

Return Value:
True if word is found, false if word is not found
*/
bool Trie::lookup(const std::string &word) const
{
	Node *curr = root;
	int len = word.length();

	for (int i = 0; i < len; i++)
	{
		int index = word[i] - 'a';

		Node *node = curr->children[index];

		if (!node)
			return false;

		curr = node;
	}

	return curr->isTerminal;
}

/*
Author: Jared Cotton

Description: This function takes a 'partial word' string, which may in itself be a word too, and finds all possible words
which start with that string in the Trie.

Parameters:
partialWord = the current string that may or may not be an actual word yet from which all possible words are based off
suggestions = a pointer to the array where all possible words found are returned through

Return Value:
The number of possible suggestions found
*/

int Trie::suggest(const std::string &partialWord, std::string suggestions[]) const
{

	Node *curr = root;
	int len = partialWord.length();
	int numSuggestions = 0;

	for (int i = 0; i < len; i++)
	{
		int index = partialWord[i] - 'a';

		Node *node = curr->children[index];

		if (!node)
			return numSuggestions;

		curr = node;
	}

	if (curr->isTerminal)
	{
		suggestions[numSuggestions] = partialWord;
		numSuggestions++;
	}

	findNumTerminals(curr, partialWord, suggestions, numSuggestions);

	return numSuggestions;
}

/*
Author: Jared Cotton

Description: Private recursive function that adds all possible words found to its parameter 'suggestions' 
and returns the number of words found through its parameter 'numSuggestions'

Parameters: 
curr = a pointer to the node to start from
word = the current string that may or may not be an actual word yet
suggestions = a pointer to the array where all possible words are stored
numSuggestions = the number of possible words found 
*/

void Trie::findNumTerminals(Node *curr, std::string word, std::string suggestions[], int &numSuggestions) const
{

	for (int i = 0; i < LETTERS_IN_ALPHABET; i++)
	{

		Node *node = curr->children[i];

		if (node)
		{

			std::string newWord = word;
			newWord += (i + 'a');
			if (node->isTerminal)
			{
				suggestions[numSuggestions] = newWord;
				numSuggestions++;
			}

			findNumTerminals(node, newWord, suggestions, numSuggestions);
		}
	}
}

/*
Author: Tim Roberts
*/
Trie::~Trie()
{
	for (auto &node : root->children)
		if (node)
			delete node;
}