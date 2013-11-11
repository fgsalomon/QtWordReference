#ifndef TRANSLATIONENTRY_H
#define TRANSLATIONENTRY_H

#include "wordtranslation.h"
#include <QList>
#include <QTextStream>

class TranslationEntry
{
public:
    explicit TranslationEntry();
    void setPrincipalTranslations(const QList<WordTranslation> &principalTranslations) {mPrincipalTranslations = principalTranslations;}
    void setAdditionalTranslations(const QList<WordTranslation> &additionalTranslations) {mAdditionalTranslations = additionalTranslations;}
    void setCompoundForms(const QList<WordTranslation> &compoundForms) {mCompoundForms = compoundForms;}
    QList<WordTranslation> getPrincipalTranslations() {return mPrincipalTranslations;}
    QList<WordTranslation> getAdditionalTranslations() {return mAdditionalTranslations;}
    QList<WordTranslation> getCompoundForms() {return mCompoundForms;}
    QByteArray getSerialized();

private:
    QList<WordTranslation> mPrincipalTranslations;
    QList<WordTranslation> mAdditionalTranslations;
    QList<WordTranslation> mCompoundForms;
    void printTranslation(const WordTranslation &translation, QTextStream &textStream);
};

#endif // TRANSLATIONENTRY_H
