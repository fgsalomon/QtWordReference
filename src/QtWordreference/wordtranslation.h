#ifndef WORDTRANSLATION_H
#define WORDTRANSLATION_H

#include "worddefinition.h"
#include <QList>

class WordTranslation
{
public:
    explicit WordTranslation();
    void setOriginalWord(const WordDefinition &originalWord) {mOriginalWord = originalWord;}
    void setTranslations(const QList<WordDefinition> &translations) {mTranslations = translations;}
    WordDefinition getOriginalWord() const {return mOriginalWord;}
    QList<WordDefinition> getTranslations() const {return mTranslations;}

private:
    WordDefinition mOriginalWord;
    QList<WordDefinition> mTranslations;
    
};

#endif // WORDTRANSLATION_H
