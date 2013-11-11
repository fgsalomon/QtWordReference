#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(const QStringList &dictionaries, const QStringList &styles, const QString &APIKey,
                             const int defaultDictionaryIndex, const int defaultStyleIndex, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog),
    mDictionaries(dictionaries),
    mStyles(styles),
    mAPIKey(APIKey),
    mDefaultDictionaryIndex(defaultDictionaryIndex),
    mDefaultStyleIndex(defaultStyleIndex)
{
    ui->setupUi(this);
    setWindowTitle(tr("Options"));
    ui->dictionariesComboBox->addItems(mDictionaries);
    ui->stylesComboBox->addItems(mStyles);
    ui->dictionariesComboBox->setCurrentIndex(defaultDictionaryIndex);
    ui->stylesComboBox->setCurrentIndex(defaultStyleIndex);
    ui->APIKeyLineEdit->setText(mAPIKey);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

int OptionsDialog::getDefaultDictionaryIndex()
{
    return ui->dictionariesComboBox->currentIndex();
}

int OptionsDialog::getDefaultStyleIndex()
{
    return ui->stylesComboBox->currentIndex();
}

QString OptionsDialog::getAPIKey()
{
    return ui->APIKeyLineEdit->text();
}

bool OptionsDialog::optionsChanged()
{
    if ((ui->dictionariesComboBox->currentIndex() != mDefaultDictionaryIndex) || (ui->stylesComboBox->currentIndex() != mDefaultStyleIndex)
            || (ui->APIKeyLineEdit->text() != mAPIKey))
        return true;
    else
        return false;

}
