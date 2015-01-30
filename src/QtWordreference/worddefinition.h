#ifndef WORDDEFINITION_H
#define WORDDEFINITION_H
#include <QString>

/*!
 * \brief The WordDefinition class represents a word or expression.
 * A word definition is composed of a term, the sense in which the
 * term is being used and the part of speech to which the term belongs.
 */

class WordDefinition
{
public:
    /*!
     * \brief WordDefinition empty constructor
     */
    explicit WordDefinition();
    /*!
     * \brief WordDefinition constructor
     * \param term Word/expression being defined
     * \param sense Sense in which the word/expression is being used
     * \param POS Part of Speech (noun, verb, etc.)
     */
    WordDefinition(const QString &term, const QString &sense, const QString &POS);
    QString toString() const;
    QString getTerm() const {return mTerm;}
    QString getSense() const {return mSense;}
    QString getPOS() const {return mPOS;}
    void setTerm(const QString &term) {mTerm = term;}
    void setSense(const QString &sense) {mSense = sense;}
    void setPOS(const QString &POS) {mPOS = POS;}

private:
    QString mTerm; /*!< Word/expression being defined */
    QString mSense; /*!< Sense in which the word/expression is being used */
    QString mPOS; /*!< Part of Speech (noun, verb, etc.) */
};

#endif // WORDDEFINITION_H
