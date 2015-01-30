#ifndef TRANSLATIONENTRY_H
#define TRANSLATIONENTRY_H

#include "wordtranslation.h"
#include <QList>
#include <QTextStream>

/*!
 * \brief The TranslationEntry class encapsulates WordReference translation entry.
 * For a search term WordReference returns the following structure:
 * - Principal translations
 * - Additional translations (optional)
 * - Compound forms (optional)
 * Each of this groups (if exists) is composed by a list of translations (one for
 * each sense).
 */
class TranslationEntry
{
public:
    /*!
     * \brief TranslationEntry empty constructor
     */
    explicit TranslationEntry();
    void setPrincipalTranslations(const QList<WordTranslation> &principalTranslations) {mPrincipalTranslations = principalTranslations;}
    void setAdditionalTranslations(const QList<WordTranslation> &additionalTranslations) {mAdditionalTranslations = additionalTranslations;}
    void setCompoundForms(const QList<WordTranslation> &compoundForms) {mCompoundForms = compoundForms;}
    QList<WordTranslation> getPrincipalTranslations() {return mPrincipalTranslations;}
    QList<WordTranslation> getAdditionalTranslations() {return mAdditionalTranslations;}
    QList<WordTranslation> getCompoundForms() {return mCompoundForms;}
    /*!
     * \brief getSerialized returns a translation entry formatted as HTML
     * \return Serialized HTML
     */
    QByteArray getSerialized();

private:
    QList<WordTranslation> mPrincipalTranslations; /*!< Principal translations list */
    QList<WordTranslation> mAdditionalTranslations; /*!< Additional translations list */
    QList<WordTranslation> mCompoundForms; /*!< Compound forms list */
    /// METHODS ///
    /*!
     * \brief printTranslation prints a translation in HTML format to the output stream textStream
     * \param translation Word/expression translation
     * \param textStream Output stream
     */
    void printTranslation(const WordTranslation &translation, QTextStream &textStream);
};

#endif // TRANSLATIONENTRY_H
