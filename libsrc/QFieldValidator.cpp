/**********************************************************************************
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
 ********************************************************************************/
/**
 * @author S.Mehran M.Ziabary <ziabary@targoman.com>
*/

#include "QFieldValidator.h"
#include <QRegularExpression>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include "Private/QFieldValidatorPrivate.h"
#include "Private/GenericValidators.h"
#include "Private/ObjectValidators.h"
#include "Private/EmailValidators.h"
#include "Private/CountryBasedValidators.h"
#include "Private/BankValidators.h"

QFieldValidator::QFieldValidator() :
    Data(new QFieldValidatorPrivate)
{;}

QFieldValidator::QFieldValidator(const QFieldValidator &_other) : Data(_other.Data)
{;}

QFieldValidator &QFieldValidator::operator =(const QFieldValidator &_other)
{this->Data = _other.Data; return *this;}

QFieldValidator::~QFieldValidator()
{;}

bool QFieldValidator::isValid(const QVariant& _value, const QString& _fieldName)
{
    if(this->Data->isEmpty(_value)){
        if(this->Data->IsOptional == false){
            this->Data->ErrorMessage = _fieldName.isEmpty() ? "required" : QString("%1 is required").arg(_fieldName);
            return false;
        }
        return true;
    }
    return this->Data->isValid(_value, _fieldName);
}

void QFieldValidator::validate(const QVariant& _value, const QString& _fieldName)
{
    if(this->Data->IsOptional == false && this->Data->isEmpty(_value))
        throw exRequiredParam(_fieldName.isEmpty() ? "required" : QString("%1 is required").arg(_fieldName));

    bool IsValid = this->isValid(_value, _fieldName);
    if(!IsValid)
        throw exInvalidValue(this->Data->ErrorMessage);
}

const QString& QFieldValidator::errorMessage()
{
    return this->Data->ErrorMessage;
}

void QFieldValidator::reset()
{
    this->Data->reset();
}

QFieldValidator& QFieldValidator::optional(QFieldValidator& _validator)
{
    this->Data->IsOptional = true;
    this->Data->SingleValidators = _validator.Data->SingleValidators;
    return *this;
}

QFieldValidator& QFieldValidator::oneOf(const QList<QFieldValidator>& _validators)
{
    this->Data->Criteria = QFieldValidatorPrivate::CRITERIA_OneOf;
    this->Data->MultiValidators.clear();
    foreach(auto Validator, _validators)
        this->Data->MultiValidators.push_back(Validator);
    return *this;
}

QFieldValidator& QFieldValidator::allOf(const QList<QFieldValidator> &_validators)
{
    this->Data->Criteria = QFieldValidatorPrivate::CRITERIA_AllOf;
    this->Data->MultiValidators.clear();
    foreach(auto Validator, _validators)
        this->Data->MultiValidators.push_back(Validator);
    return *this;
}

QFieldValidator& QFieldValidator::when(const QFieldValidator& _if, const QFieldValidator& _then, const QFieldValidator& _else)
{
    this->Data->Criteria = QFieldValidatorPrivate::CRITERIA_When;
    this->Data->IfValidator.reset(new QFieldValidator(_if));
    this->Data->ElseValidator.reset(new QFieldValidator(_else));
    this->Data->SingleValidators = _then.Data->SingleValidators;
    return *this;
}


#define ADD_NEW_GENERIC_FIELDVALIDATOR(_name) QFieldValidator& QFieldValidator::_name(){this->Data->SingleValidators.push_back(new Validators::_name);return *this;}

ADD_NEW_GENERIC_FIELDVALIDATOR(lowerCase);
ADD_NEW_GENERIC_FIELDVALIDATOR(upperCase);
ADD_NEW_GENERIC_FIELDVALIDATOR(notEmpty);
ADD_NEW_GENERIC_FIELDVALIDATOR(notNull);

QFieldValidator& QFieldValidator::asciiAlNum(bool _allowSpace, const QString &_extraValidChars){this->Data->SingleValidators.push_back(new Validators::asciiAlNum(_allowSpace, _extraValidChars));return *this;}
QFieldValidator& QFieldValidator::unicodeAlNum(bool _allowSpace, const QString &_extraValidChars){this->Data->SingleValidators.push_back(new Validators::unicodeAlNum(_allowSpace, _extraValidChars));return *this;}
QFieldValidator& QFieldValidator::minLenght(size_t _len){this->Data->SingleValidators.push_back(new Validators::minLenght(_len));return *this;}
QFieldValidator& QFieldValidator::maxLenght(size_t _len){this->Data->SingleValidators.push_back(new Validators::maxLenght(_len));return *this;}
QFieldValidator& QFieldValidator::contains(const QString& _value){this->Data->SingleValidators.push_back(new Validators::contains(_value));return *this;}
QFieldValidator& QFieldValidator::startsWith(const QString& _value){this->Data->SingleValidators.push_back(new Validators::startsWith(_value));return *this;}
QFieldValidator& QFieldValidator::endsWith(const QString& _value){this->Data->SingleValidators.push_back(new Validators::endsWith(_value));return *this;}
QFieldValidator& QFieldValidator::equals(const QVariant& _value){this->Data->SingleValidators.push_back(new Validators::equals(_value));return *this;}
QFieldValidator& QFieldValidator::matches(const QRegularExpression& _value){this->Data->SingleValidators.push_back(new Validators::matches(_value));return *this;}


ADD_NEW_GENERIC_FIELDVALIDATOR(real);
ADD_NEW_GENERIC_FIELDVALIDATOR(integer);
ADD_NEW_GENERIC_FIELDVALIDATOR(boolean);
ADD_NEW_GENERIC_FIELDVALIDATOR(hex);
ADD_NEW_GENERIC_FIELDVALIDATOR(odd);
ADD_NEW_GENERIC_FIELDVALIDATOR(even);
ADD_NEW_GENERIC_FIELDVALIDATOR(negative);
ADD_NEW_GENERIC_FIELDVALIDATOR(positive);

ADD_NEW_GENERIC_FIELDVALIDATOR(allwaysValid);
ADD_NEW_GENERIC_FIELDVALIDATOR(allwaysInvalid);
ADD_NEW_GENERIC_FIELDVALIDATOR(arrayType);
ADD_NEW_GENERIC_FIELDVALIDATOR(objectType);

ADD_NEW_GENERIC_FIELDVALIDATOR(json)
QFieldValidator& QFieldValidator::hasKey(const QString& _key, QFieldValidator &_validator, bool _mandatory){
    this->Data->SingleValidators.push_back(new Validators::hasKey(_key, _validator, _mandatory));return *this;
}
QFieldValidator& QFieldValidator::hasNestedKey(const QString& _key, QFieldValidator &_validator, bool _mandatory){
    this->Data->SingleValidators.push_back(new Validators::hasNestedKey(_key, _validator, _mandatory));return *this;
}

ADD_NEW_GENERIC_FIELDVALIDATOR(email);
ADD_NEW_GENERIC_FIELDVALIDATOR(md5);
ADD_NEW_GENERIC_FIELDVALIDATOR(url);
ADD_NEW_GENERIC_FIELDVALIDATOR(date);
ADD_NEW_GENERIC_FIELDVALIDATOR(time);
ADD_NEW_GENERIC_FIELDVALIDATOR(dateTime);

ADD_NEW_GENERIC_FIELDVALIDATOR(emailNotFake);
ADD_NEW_GENERIC_FIELDVALIDATOR(languageCode);

QFieldValidator& QFieldValidator::emailJustDomains(const QSet<QString> &_validDomains){
    this->Data->SingleValidators.push_back(new Validators::emailJustDomains(_validDomains));return *this;
}
QFieldValidator& QFieldValidator::emailNotDomains(const QSet<QString> &_validDomains, bool _alsoNotFake){
    this->Data->SingleValidators.push_back(new Validators::emailNotDomains(_validDomains, _alsoNotFake));return *this;
}

QFieldValidator& QFieldValidator::creditCard(QFieldValidator::CreditCards::Type _type){
    this->Data->SingleValidators.push_back(new Validators::creditCard(_type));return *this;
}

QFieldValidator&QFieldValidator::minValue(double _value, bool _inclusive) {
    this->Data->SingleValidators.push_back(new Validators::minValue(_value, _inclusive)); return *this;
}

QFieldValidator&QFieldValidator::maxValue(double _value, bool _inclusive) {
    this->Data->SingleValidators.push_back(new Validators::maxValue(_value, _inclusive)); return *this;
}

QFieldValidator&QFieldValidator::betweenValues(double _first, double _second, bool _inclusive){
    this->Data->SingleValidators.push_back(new Validators::betweenValues(_first, _second, _inclusive)); return *this;
}


QFieldValidator& QFieldValidator::iban(const QString &_country){
    this->Data->SingleValidators.push_back(new Validators::iban(_country));return *this;
}

QFieldValidator& QFieldValidator::postalCode(const QString &_country){
    this->Data->SingleValidators.push_back(new Validators::postalCode(_country));return *this;
}

QFieldValidator& QFieldValidator::idCard(const QString &_country){
    this->Data->SingleValidators.push_back(new Validators::idCard(_country));return *this;
}

QFieldValidator& QFieldValidator::mobile(bool _mandatoryCountryCode){
    this->Data->SingleValidators.push_back(new Validators::mobile(_mandatoryCountryCode));return *this;
}
QFieldValidator& QFieldValidator::phone(bool _mandatoryProvinceCode, bool _mandatoryCountryCode){
    this->Data->SingleValidators.push_back(new Validators::phone(_mandatoryProvinceCode, _mandatoryCountryCode));return *this;
}

/**************************************************************************/
QFieldValidator::exQFieldValidator::exQFieldValidator(const QString& _message):Message(_message.toUtf8()){;}
const char *QFieldValidator::exQFieldValidator::what() const _GLIBCXX_USE_NOEXCEPT{return this->Message.constData();}

QFieldValidator::exQFieldValidator::~exQFieldValidator(){;}
QFieldValidator::exRequiredParam::exRequiredParam(const QString& _message):exQFieldValidator (_message){;}
QFieldValidator::exRequiredParam::~exRequiredParam(){;}

QFieldValidator::exInvalidValue::exInvalidValue(const QString& _message):exQFieldValidator(_message){;}
QFieldValidator::exInvalidValue::~exInvalidValue(){;}
