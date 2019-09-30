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
#include "QFieldValidatorPrivate.h"
#include "GenericValidators.h"
#include <QPointer>

QFieldValidatorPrivate::QFieldValidatorPrivate() :
    IsOptional(false),
    Criteria(CRITERIA_Signle)
{;}

QFieldValidatorPrivate::QFieldValidatorPrivate(const QFieldValidatorPrivate &_other) :
    QSharedData(_other),
    ErrorMessage(_other.ErrorMessage),
    IsOptional(_other.IsOptional),
    Criteria(_other.Criteria),
    SingleValidators(_other.SingleValidators),
    MultiValidators(_other.MultiValidators),
    IfValidator(_other.IfValidator.data()),
    ElseValidator(_other.ElseValidator.data())
{;}

bool QFieldValidatorPrivate::isValid(const QVariant& _value, const QString& _fieldName)
{
    switch(this->Criteria){
    case CRITERIA_Signle:
        return this->checkAllRules(_value, _fieldName);
    case CRITERIA_OneOf:
        foreach(auto Validator, this->MultiValidators){
            if(Validator.isValid(_value, _fieldName))
                return true;
        }
        this->ErrorMessage = _fieldName.isEmpty() ? "none of the specified validation rules matched" : QString("%1 is invalid").arg(_fieldName);
        return false;
    case CRITERIA_AllOf:
        foreach(auto Validator, this->MultiValidators){
            if(Validator.isValid(_value, _fieldName) == false){
                this->ErrorMessage = Validator.errorMessage();
                return false;
            }
        }
        return true;
    case CRITERIA_When:
        if(this->IfValidator->isValid(_value, _fieldName)){
            return this->checkAllRules(_value, _fieldName);
        }else{
            if(this->ElseValidator->isValid(_value, _fieldName))
                return true;
            this->ErrorMessage = this->ElseValidator->errorMessage();
            return false;
        }
    }
    return true;
}

bool QFieldValidatorPrivate::isEmpty(const QVariant& _value)
{
    return (_value.isNull()
            || !_value.isValid()
            || (_value.canConvert<QString>() && _value.toString().isEmpty())
            || (_value.canConvert<QVariantList>() && _value.toList().isEmpty())
            || (_value.canConvert<QVariantMap>() && _value.toMap().isEmpty())
            );
}

void QFieldValidatorPrivate::reset()
{
    this->IsOptional = true;
    this->Criteria = CRITERIA_Signle;
    this->IfValidator.reset(nullptr);
    this->ElseValidator.reset(nullptr);
    this->SingleValidators.clear();
    this->MultiValidators.clear();
}

bool QFieldValidatorPrivate::checkAllRules(const QVariant& _value, const QString& _fieldName)
{
    foreach(auto Validation, this->SingleValidators)
        if((this->ErrorMessage = Validation->validate(_value, _fieldName)).size())
            return false;
    return true;
}

/***********************************************/
intfValidator::~intfValidator()
{;}

