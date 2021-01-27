#include <string>

const int LETTERS_IN_ALPHABET = 26;

class Trie{

	struct Node {
		Node* children[LETTERS_IN_ALPHABET] = {};
		bool isTerminal;

		Node() : isTerminal(false) {}
	};

	Node* root;
	
	void findNumTerminals(Node* curr, std::string word, std::string suggestions[], int& numSuggestions) const;

public:
	Trie();
	Trie(std::string data[],int sz);
	void addWord(const std::string& newWord);
	bool lookup(const std::string& word) const;
	int suggest(const std::string& partialWord, std::string suggestions[]) const;
	~Trie();	
};
