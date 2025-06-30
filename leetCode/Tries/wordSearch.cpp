My solution for this leetcode problem is giving me this error. find where the error is and show me how to fix it 

run.sh: line 1:     3 Segmentation fault      (core dumped) LD_LIBRARY_PATH=/usr/local/gcc-9.2.0/lib64 ./a.out



Given a 2-D grid of characters board and a list of strings words, return all words that are present in the grid.

For a word to be present it must be possible to form the word with a path in the board with horizontally or vertically neighboring cells. The same cell may not be used more than once in a word.

Example 1:



Input:
board = [
  ["a","b","c","d"],
  ["s","a","a","t"],
  ["a","c","k","e"],
  ["a","c","d","n"]
],
words = ["bat","cat","back","backend","stack"]

Output: ["cat","back","backend"]
Example 2:



Input:
board = [
  ["x","o"],
  ["x","o"]
],
words = ["xoxo"]

Output: []
Constraints:

1 <= board.length, board[i].length <= 10
board[i] consists only of lowercase English letter.
1 <= words.length <= 100
1 <= words[i].length <= 10
words[i] consists only of lowercase English letters.
All strings within words are distinct.

class TrieNode
{
public:
    vector<TrieNode *> children;
    char value;

    TrieNode(char c) : children(4, nullptr), value(c) {}
};

class Solution
{
public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        createBoard(board);
        vector<string> found;
        for (string word : words)
        {
            if (starts.find(word[0]) == starts.end())
                continue;
            for (TrieNode *s : starts[word[0]])
            {
                unordered_set<TrieNode *> seen;
                seen.insert(s);

                bool value = dfs(s, seen, 1, word);
                if (value)
                {
                    found.push_back(word);
                    break;
                }
            }
        }
        return found;
    }

private:
    unordered_map<char, vector<TrieNode *>> starts;

    void createBoard(vector<vector<char>> &board)
    {
        map<pair<int, int>, TrieNode *> rowMap;
        static const int dr[4] = {1, -1, 0, 0};
        static const int dc[4] = {0, 0, 1, -1};

        // create all the nodes and store location in a map;
        for (int j = 0; j < board.size(); j++)
        {
            vector<char> row = board[j];

            for (int i = 0; i < row.size(); i++)
            {
                TrieNode *node = TrieNode(row[i]);
                rowMap[{j, i}] = node;
                starts[row[i]].push_back(node);
            }
        }

        // link all neighbors;
        for (int j = 0; j < board.size(); j++)
        {
            vector<char> row = board[j];
            for (int i = 0; i < row.size(); i++)
            {
                TrieNode *node = rowMap[{j, i}];

                for (int k = 0; k < 4; k++)
                {
                    int r2 = j + dr[k];
                    int c2 = i + dc[k];
                    if (r2 < 0 || r2 >= board.size() ||
                        c2 < 0 || c2 >= board[0].size())
                        continue;
                    node->children.push_back(rowMap[{r2, c2}]);
                }
            }
        }
        return;
    };

    bool dfs(TrieNode *current, unordered_set<TrieNode *> &seen, int n, string &word)
    {
        if (n >= word.length())
        {
            return true;
        }

        for (TrieNode *child : current->children)
        {
            if (child->value == word[n] && seen.find(child) == seen.end())
            {
                seen.insert(child);
                bool value = dfs(child, seen, n + 1, word);
                if (value)
                {
                    return value;
                }
                seen.erase(child);
            }
        }

        return false;
    }
};

Input :

    board = [ [ "a", "b", "c", "d" ], [ "s", "a", "a", "t" ], [ "a", "c", "k", "e" ], [ "a", "c", "d", "n" ] ] words = [ "bat", "cat", "back", "backend", "stack" ] Expected output :

    [ "cat", "back", "backend" ]

    Input :

    board = [ [ "x", "o" ], [ "x", "o" ] ] words = ["xoxo"] Expected output :

    []