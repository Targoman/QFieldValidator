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

#include "ObjectValidators.h"
#include <QJsonParseError>
#include <QJsonObject>

namespace Validators{

Private::clsBaseObjectValidator::clsBaseObjectValidator(const QString &_key, QFieldValidator &_validator, bool _mandatory) :
    Key(_key),Validator(_validator),Mandatory(_mandatory)
{;}

hasKey::hasKey(const QString& _key, QFieldValidator& _validator, bool _mandatory) :
    clsBaseObjectValidator(_key, _validator, _mandatory)
{;}

hasNestedKey::hasNestedKey(const QString& _key, QFieldValidator& _validator, bool _mandatory) :
    clsBaseObjectValidator(_key, _validator, _mandatory)
{;}

QString validateJson(const QVariant& _value, const QString& _fieldName = QString()){
    QJsonParseError ParseError;
    QJsonDocument Doc = QJsonDocument::fromJson(_value.toByteArray(), &ParseError);
    if(ParseError.error != QJsonParseError::NoError)
        return _fieldName.isEmpty() ?
                    QString("Invalid JSON: %1").arg(ParseError.errorString()) :
                    QString("%1 must be a valid JSON: %2").arg(_fieldName, ParseError.errorString());
    return {};
}

QString json::validate(const QVariant& _value, const QString& _fieldName)  {
    return validateJson(_value, _fieldName);
}

QVariantMap retrieveObject(const QVariant& _value, QString& _error){
    if(_value.canConvert<QVariantMap>())
        return _value.toMap();
    if((_error = validateJson(_value)).isEmpty())
        return QJsonDocument::fromJson(_value.toByteArray()).object().toVariantMap();
    return {};
}

QString hasKey::validate(const QVariant& _value, const QString& _fieldName)  {
    QString Error;
    QVariantMap Object = retrieveObject(_value, Error);
    if(Object.isEmpty()){
        if(this->Mandatory)
            return _fieldName.isEmpty() ?
                        (Error.isEmpty() ? QString("No key found") : Error) :
                        (Error.isEmpty() ? QString("%1 has no key").arg(_fieldName) : QString("%1 is invalid: %2").arg(_fieldName, Error));
        return {};
    }
    if(Object.contains(this->Key) == false){
        if(this->Mandatory)
            return _fieldName.isEmpty() ? QString("Key %1 not found in object").arg(this->Key) : QString("%1 must have %2 key").arg(_fieldName, this->Key);
        return {};
    }

    if(this->Validator.isValid(Object.value(this->Key)) == false)
        return _fieldName.isEmpty() ? QString("Value on %1 is not aceptable: %2").arg(this->Key, this->Validator.errorMessage ()) :
                                      QString("%1 has %2 key with unacceptable value: %3").arg(_fieldName, this->Key, this->Validator.errorMessage());

    return {};
}

QString hasNestedKey::validate(const QVariant& _value, const QString& _fieldName)  {
    QString Error;
    QVariantMap Object = retrieveObject(_value, Error);
    if(Object.isEmpty()){
        if(this->Mandatory)
            return _fieldName.isEmpty() ?
                        (Error.isEmpty() ? QString("No key found") : Error) :
                        (Error.isEmpty() ? QString("%1 has no key").arg(_fieldName) : QString("%1 is invalid: %2").arg(_fieldName, Error));
        return {};
    }

    QStringList Keys = this->Key.split('.');
    quint8 TraversedKeyCount = 0;
    foreach(auto CurrKey, Keys){
        ++TraversedKeyCount;
        if(Object.contains(CurrKey) == false){
            if(this->Mandatory)
                return _fieldName.isEmpty() ? QString("NestedKey %1 not found in object").arg(this->Key) : QString("%1 must have %2").arg(_fieldName, this->Key);
            return {};
        }
        if(TraversedKeyCount < Keys.size())
            Object = Object.value(CurrKey).toMap ();
    }

    if(this->Validator.isValid(Object.first()) == false)
        return _fieldName.isEmpty() ? QString("Value on %1 is not aceptable: %2").arg(this->Key, this->Validator.errorMessage ()) :
                                      QString("%1 has %2 key with unacceptable value: %3").arg(_fieldName, this->Key, this->Validator.errorMessage());

    return {};
}

}
