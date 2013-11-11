#include "worddefinition.h"

WordDefinition::WordDefinition()
{
}

QString WordDefinition::toString() const
{
    QString definition = mTerm + " " + mPOS + " " + mSense;
    return definition;
}
