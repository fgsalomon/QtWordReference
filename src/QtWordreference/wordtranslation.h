#ifndef WORDTRANSLATION_H
#define WORDTRANSLATION_H

#include "worddefinition.h"
#include <QList>

/*!
 * \brief The WordTranslation class encapsulates a word/expression translation.
 * A word/expression can have multiple translations. Fox example the word "work"
 * in the sense of "employment" can be translated to French as "travail" or "emploi".
 */

class WordTranslation
{
public:
    /*!
     * \brief WordTranslation empty constructor
     */
    explicit WordTranslation();
    void setOriginalWord(const WordDefinition &originalWord) {mOriginalWord = originalWord;}
    void setTranslations(const QList<WordDefinition> &translations) {mTranslations = translations;}
    WordDefinition getOriginalWord() const {return mOriginalWord;}
    QList<WordDefinition> getTranslations() const {return mTranslations;}

private:
    WordDefinition mOriginalWord; /*!< Native word/expression */
    QList<WordDefinition> mTranslations; /*!< Translation list */
    
};

#endif // WORDTRANSLATION_H
