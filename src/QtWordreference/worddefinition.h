#ifndef WORDDEFINITION_H
#define WORDDEFINITION_H
#include <QString>

class WordDefinition
{
public:
    explicit WordDefinition();
    QString toString() const;
    QString getTerm() const {return mTerm;}
    QString getSense() const {return mSense;}
    QString getPOS() const {return mPOS;}
    void setTerm(const QString &term) {mTerm = term;}
    void setSense(const QString &sense) {mSense = sense;}
    void setPOS(const QString &POS) {mPOS = POS;}

private:
    QString mTerm;
    QString mSense;
    QString mPOS; // Part of Speech
};

#endif // WORDDEFINITION_H
