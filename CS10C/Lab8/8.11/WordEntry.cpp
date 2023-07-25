#include "WordEntry.h"

/* WordEntry contructor
 * input: the string text (word) and the intial score the
 *         word should be assigned to
 *  note that numAppearances should be set to 1 here
 */

WordEntry::WordEntry(const string &text, int score) : word(text), numAppearances(1), totalScore(score) {}

/*Deconstructor*/

WordEntry::~WordEntry() {}

WordEntry::WordEntry(const WordEntry &copy)
{
    word = copy.word;
    numAppearances = copy.numAppearances;
    totalScore = copy.totalScore;
}

WordEntry &WordEntry::operator=(const WordEntry &copy)
{
    if (this == &copy)
    {
        return *this; // Self-assignment, no need to perform anything
    }

    word = copy.word;                     // Copy the word from the source object to the current object
    numAppearances = copy.numAppearances; // Copy the number of appearances from the source object to the current object
    totalScore = copy.totalScore;         // Copy the total score from the source object to the current object

    return *this; // Return a reference to the current object
}

/* addNewAppearance
 * input integer that is a new score for a word that is
 * already in the hash table
 * function should increase total score by s
 * also should increase numAppearances
 */
void WordEntry::addNewAppearance(int s)
{
    totalScore += s;  // Add the given score (s) to the total score of the WordEntry object
    ++numAppearances; // Increment the number of appearances by 1
}

/*getWord
 * this accessor function is needed
 * particularly in the HashTable code to get the word to be
 * used for the hash value
 * simple accessor function
 */
const string &WordEntry::getWord()
{
    return word; // Return a reference to the `word` member variable of the WordEntry object
}

/* getAverage
 *  returns the average score of the word
 *  based on totalScore and numAppearances
 *  note that typecasting -- turning one of the integers
 *  to a double will be necessary to avoid integer division
 */
double WordEntry::getAverage()
{
    return static_cast<double>(totalScore) / numAppearances;
}