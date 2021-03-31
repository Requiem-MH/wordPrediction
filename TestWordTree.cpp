#include "WordTree.hpp"

#include "gtest/gtest.h"
#include <algorithm>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(WordTree_Add, CanAddArbitraryValues)
{
    WordTree wordTree;

    wordTree.add("what");
    wordTree.add("apple");
    wordTree.add("hello");

    ASSERT_EQ(wordTree.size(), 3);
    ASSERT_EQ(wordTree.find("what"), true);
    ASSERT_EQ(wordTree.find("apple"), true);
    ASSERT_EQ(wordTree.find("hello"), true);
}

TEST(WordTree_Add, DoesNotAddEmptyStrings)
{
    WordTree wordTree;

    wordTree.add("");

    ASSERT_EQ(wordTree.size(), 0);
}

TEST(WordTree_Add, CanAddDuplicateValues)
{
    WordTree wordTree;

    wordTree.add("apple");
    wordTree.add("apple");

    ASSERT_EQ(wordTree.size(), 1);
    ASSERT_EQ(wordTree.find("apple"), true);
}

TEST(WordTree_Find, CanFindWithNoWordsInTree)
{
    WordTree wordTree;

    ASSERT_FALSE(wordTree.find("hello"));
}

TEST(WordTree_Find, FindEmptyStringIsFalse)
{
    WordTree wordTree;

    ASSERT_FALSE(wordTree.find(""));

    wordTree.add("abc");

    ASSERT_FALSE(wordTree.find(""));
}

TEST(WordTree_Find, CanFindWordWithUniquePrefix)
{
    WordTree wordTree;

    wordTree.add("what");
    wordTree.add("how");
    wordTree.add("nowhere");

    ASSERT_TRUE(wordTree.find("what"));
    ASSERT_TRUE(wordTree.find("how"));
    ASSERT_TRUE(wordTree.find("nowhere"));

    ASSERT_FALSE(wordTree.find("unknown"));
    ASSERT_FALSE(wordTree.find("wh"));
    ASSERT_FALSE(wordTree.find("wha"));
}

TEST(WordTree_Find, CanFindWordWithCommonPrefix)
{
    WordTree wordTree;

    wordTree.add("what");
    wordTree.add("who");
    wordTree.add("when");
    wordTree.add("where");
    wordTree.add("why");

    ASSERT_TRUE(wordTree.find("what"));
    ASSERT_TRUE(wordTree.find("who"));
    ASSERT_TRUE(wordTree.find("when"));
    ASSERT_TRUE(wordTree.find("where"));
    ASSERT_TRUE(wordTree.find("why"));

    ASSERT_FALSE(wordTree.find("wh"));
    ASSERT_FALSE(wordTree.find("w"));
    ASSERT_FALSE(wordTree.find("whosoever"));
}

TEST(WordTree_Predict, CanPredictWithNoWordsInTree)
{
    WordTree wordTree;

    ASSERT_EQ(0, wordTree.predict("hello", 1).size());
}

TEST(WordTree_Predict, CanPredictEmptyString)
{
    WordTree wordTree;

    wordTree.add("hello");

    ASSERT_EQ(0, wordTree.predict("", 1).size());
}

TEST(WordTree_Predict, CanPredictWithSingleLetter)
{
    WordTree wordTree;

    wordTree.add("zoo");
    wordTree.add("acknowledges");
    wordTree.add("acknowledging");
    wordTree.add("acorn");
    wordTree.add("acorns");
    wordTree.add("acoustic");
    wordTree.add("zebras");

    const auto predictions = wordTree.predict("a", 5);

    EXPECT_EQ(5, predictions.size());

    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acknowledges"));
    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acknowledging"));
    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acorn"));
    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acorns"));
    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acoustic"));
}

TEST(WordTree_Predict, CanPredictWithArbitraryPrefix)
{
    WordTree wordTree;

    wordTree.add("zoo");
    wordTree.add("acknowledges");
    wordTree.add("acknowledging");
    wordTree.add("acorn");
    wordTree.add("acorns");
    wordTree.add("acoustic");
    wordTree.add("bounce");
    wordTree.add("bound");
    wordTree.add("boundaries");
    wordTree.add("boundary");
    wordTree.add("zebras");

    const auto predictions = wordTree.predict("aco", 3);

    EXPECT_EQ(3, predictions.size());

    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acorn"));
    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acorns"));
    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acoustic"));
}

TEST(WordTree_Predict, DoesNotIncludePrefixInPrediction)
{
    WordTree wordTree;

    wordTree.add("acknowledging");
    wordTree.add("acorn");
    wordTree.add("acorns");
    wordTree.add("acoustic");

    const auto predictions = wordTree.predict("acorn", 2);

    EXPECT_EQ(1, predictions.size());

    EXPECT_NE(end(predictions),
              std::find(begin(predictions), end(predictions), "acorns"));
}

TEST(WordTree_Predict, DoesLimitPredicitionCount)
{
    WordTree wordTree;

    wordTree.add("acknowledges");
    wordTree.add("acknowledging");
    wordTree.add("acorn");
    wordTree.add("acorns");
    wordTree.add("acoustic");

    ASSERT_EQ(3, wordTree.predict("ac", 3).size());
    ASSERT_EQ(1, wordTree.predict("ac", 1).size());

    ASSERT_EQ(2, wordTree.predict("aco", 2).size());

    ASSERT_EQ(5, wordTree.predict("a", 10).size());
}
