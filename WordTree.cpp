#include "WordTree.hpp"

WordTree::WordTree()
{
    root = std::make_shared<TreeNode>();
}

void WordTree::add(std::string word)
{
    auto currNode = root;

    // Empyt String
    if (word.size() == 0)
    {
        return;
    }

    for (long unsigned int level = 0; level < word.size(); level++)
    {
        // cast to lower case then minus ascii 96 to get 1-26
        int letter = static_cast<int>(tolower(word[level])) - 97;
        // No node
        if (currNode->children[letter] == NULL)
        {
            currNode->children[letter] = std::make_shared<TreeNode>();
        }
        currNode = currNode->children[letter];
    }
    // Ignore if word already added
    if (!currNode->endOfWord == true)
    {
        currNode->endOfWord = true;
        wordCount++;
    }
}

bool WordTree::find(std::string word)
{
    auto currNode = root;
    for (long unsigned int level = 0; level < word.size(); level++)
    {
        // cast to lower case then minus ascii 96 to get 1-26
        int letter = static_cast<int>(tolower(word[level])) - 97;
        // No node
        if (currNode->children[letter] == NULL)
        {
            return false;
        }
        currNode = currNode->children[letter];
    }

    return (currNode != NULL && currNode->endOfWord);
}

bool lastNode(std::shared_ptr<TreeNode> currNode)
{
    for (long unsigned int j = 0; j < currNode->children.size(); j++)
    {
        if (currNode->children[j])
        {
            return false;
        }
    }
    return true;
}

void recPredictHelper(std::string partial,
                      std::vector<std::string>& listOfWords,
                      const long unsigned int listLength,
                      std::shared_ptr<TreeNode> node)
{

    std::string word = partial;
    auto currNode = node;
    // All children are Null
    if (lastNode(currNode))
    {
        return;
    }
    // iterate over children, if words, travel down them
    for (long unsigned int m = 0; m < currNode->children.size(); m++)
    {
        if (listLength <= listOfWords.size())
        {
            break;
        }

        if (currNode->children[m])
        {
            // append character to word
            word.push_back(static_cast<char>(m + 97));
            // add word to list if word
            if (currNode->children[m]->endOfWord == true)
            {
                listOfWords.push_back(word);
            }
            recPredictHelper(word, listOfWords, listLength, currNode->children[m]);
            // add word to list

            word.pop_back();
        }
    }
}

std::vector<std::string> WordTree::predict(std::string partial,
                                           std::uint8_t howMany)
{
    auto currNode = root;
    std::vector<std::string> wordList;

    // Empyt String
    if (partial.size() == 0)
    {
        return wordList;
    }

    // Crawl to end of partial if partial is present
    for (long unsigned int level = 0; level < partial.size(); level++)
    {
        // cast to lower case then minus ascii 96 to get 1-26
        int letter = static_cast<int>(tolower(partial[level])) - 97;

        if (currNode->children[letter] == NULL)
        {
            return wordList;
        }
        currNode = currNode->children[letter];
    }

    if (!lastNode(currNode))
    {
        recPredictHelper(partial, wordList, howMany, currNode);
    }

    return wordList;
}
