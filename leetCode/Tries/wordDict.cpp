Design Add and Search Word Data Structure
Design a data structure that supports adding new words and searching for existing words.

Implement the WordDictionary class:

void addWord(word) Adds word to the data structure.
bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.
Example 1:

Input:
["WordDictionary", "addWord", "day", "addWord", "bay", "addWord", "may", "search", "say", "search", "day", "search", ".ay", "search", "b.."]

Output:
[null, null, null, null, false, true, true, true]

Explanation:
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("day");
wordDictionary.addWord("bay");
wordDictionary.addWord("may");
wordDictionary.search("say"); // return false
wordDictionary.search("day"); // return true
wordDictionary.search(".ay"); // return true
wordDictionary.search("b.."); // return true
Constraints :

        1 <= word.length <= 20 word in addWord consists of lowercase English letters.word in search consist of '.' or
    lowercase English letters.

    class TrieNode
{
public:
    vector<TrieNode *> children;
    bool word;

    TrieNode() : children(26, nullptr), word(false) {}
};

class WordDictionary
{
private:
    TrieNode *root;

public:
    WordDictionary()
    {
        root = new TrieNode();
    }

    void addWord(string word)
    {
        dfs(word, root);
    }

    void dfs(string word, TrieNode *node)
    {
        if (word == "")
        {
            node->word = true;
            return;
        }

        char first = word[0];
        if (node->children[first - 'a'] == nullptr)
        {
            node->children[first - 'a'] = new TrieNode();
        }
        dfs(word.substr(1), node->children[first - 'a']);
    }

    bool search(string word)
    {
        return dfsSearch(word, root);
    }

    bool dfsSearch(string word, TrieNode *node)
    {
        if (word == "")
        {
            return node->word;
        }

        if (word[0] == '.')
        {
            bool retValue = false;
            for (TrieNode *n : node->children)
            {
                if (n != nullptr)
                {
                    bool value = dfsSearch(word.substr(1), n);
                    retValue = (retValue || value);
                }
            }
            return retValue;
        }
        else
        {
            TrieNode *ptr = node->children[word[0] - 'a'];
            if (ptr == nullptr)
            {
                return false;
            }
            else
            {
                return dfsSearch(word.substr(1), ptr);
            }
        }
    }
};