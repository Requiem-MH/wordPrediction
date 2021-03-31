#pragma once
#include <array>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

class TreeNode
{
  public:
    bool endOfWord = false;
    std::array<std::shared_ptr<TreeNode>, 26> children;
};

class WordTree
{

  public:
    WordTree();
    std::shared_ptr<TreeNode> root;
    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size() { return wordCount; }

  private:
    int wordCount = 0;
};
