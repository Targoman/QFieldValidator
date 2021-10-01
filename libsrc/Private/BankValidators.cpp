/************************************************************************************
#   QFieldValidator: A simple but usefull field validation library
#
#   Copyright 2018-2019 by Targoman Intelligent Processing <http://tip.co.ir>
#
#   QFieldValidator is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   QFieldValidator is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with Targoman. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/
/**
 * @author S.Mehran M.Ziabary <ziabary@targoman.com>
 */
#include "BankValidators.h"
#include <QHash>

namespace Validators{
namespace Private {

static QMap<QFieldValidator::CreditCards::Type, QRegularExpression> rxValidCreditCards = {
    {QFieldValidator::CreditCards::Any, QRegularExpression("^[0-9]+$")},
    {QFieldValidator::CreditCards::AmericanExpress, QRegularExpression("^3[47]\\d{13}$")},
    {QFieldValidator::CreditCards::DinersClub, QRegularExpression("^3(?:0[0-5]|[68]\\d)\\d{11}$")},
    {QFieldValidator::CreditCards::Discover, QRegularExpression("^6(?:011|5\\d{2})\\d{12}$")},
    {QFieldValidator::CreditCards::JCB, QRegularExpression("^(?:2131|1800|35\\d{3})\\d{11}$")},
    {QFieldValidator::CreditCards::MasterCard, QRegularExpression("(5[1-5]|2[2-7])\\d{14}$")},
    {QFieldValidator::CreditCards::VISA, QRegularExpression("^4\\d{12}(?:\\d{3})?$")},
    {QFieldValidator::CreditCards::Parsian, QRegularExpression("^6221\\d{12,12}$")},
    {QFieldValidator::CreditCards::Mellat, QRegularExpression("^6104[0-9]{12,12}$")},
};

}

QString creditCard::validate(const QVariant& _value, const QString& _fieldName) {
    return Private::rxValidCreditCards.value(this->Type).match(_value.toString().replace(Private::rxExtraChars, "")).hasMatch() ? QString() : createErrorString(creditCard, _fieldName);
}

/*
 * The IBAN number consists of a two-letter country code, followed by two check digits, and up to thirty-five alphanumeric
 * characters. These alphanumeric characters are known as the basic bank account number (BBAN). It is up to the banking
 * association of each country to determine which BBAN they will select as the standard for that country's bank accounts.
 * However, only European banks use IBAN, although the practice is becoming popular in other countries.
*/
QString iban::validate(const QVariant& _value, const QString& _fieldName){
//    Q_UNUSED(_value); Q_UNUSED(_fieldName);
//    return "iban validator Not Implememted yet";

    return QRegularExpression("^[a-zA-Z]{2}\\d{2}[0-9a-zA-Z]{1,35}$").match(_value.toString().replace(Private::rxExtraChars, "")).hasMatch()
        ? QString() : createErrorString(creditCard, _fieldName);

    //return Private::rxValidCreditCards.value(this->Type).match(_value.toString().replace(Private::rxExtraChars, "")).hasMatch() ? QString() : createErrorString(creditCard, _fieldName);
}

}
