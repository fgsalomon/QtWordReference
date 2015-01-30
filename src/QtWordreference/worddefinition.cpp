#include "worddefinition.h"

WordDefinition::WordDefinition()
{
}

WordDefinition::WordDefinition(const QString &term, const QString &sense, const QString &POS):
    mTerm(term),
    mSense(sense),
    mPOS(POS)
{

}

QString WordDefinition::toString() const
{
    QString definition = mTerm + " " + mPOS + " " + mSense;
    return definition;
}
