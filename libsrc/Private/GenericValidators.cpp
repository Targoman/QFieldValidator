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

#include "GenericValidators.h"
#include <QVariantList>
#include <QVariantMap>
#include <QUrl>
#include <QDateTime>

namespace Validators{

REGEX_BASED_VALIDATOR_IMPL(asciiAlNum,   QRegularExpression("^[\\w\\d]+$", QRegularExpression::CaseInsensitiveOption));
REGEX_BASED_VALIDATOR_IMPL(unicodeAlNum, QRegularExpression("^[\\w\\d]+$", QRegularExpression::CaseInsensitiveOption | QRegularExpression::UseUnicodePropertiesOption))
REGEX_BASED_VALIDATOR_IMPL(lowerCase,    QRegularExpression("^[a-z0-9]+$"));
REGEX_BASED_VALIDATOR_IMPL(upperCase,    QRegularExpression("^[A-Z0-9]+$"));

REGEX_BASED_VALIDATOR_IMPL(md5,          QRegularExpression("^[a-f0-9]{32}$", QRegularExpression::CaseInsensitiveOption))
REGEX_BASED_VALIDATOR_IMPL(hex,          QRegularExpression("^[a-f0-9]+$", QRegularExpression::CaseInsensitiveOption))

CONDITIONAL_VALIDATOR_IMPL(real,     bool Error;_value.toDouble(&Error);,   Error)
CONDITIONAL_VALIDATOR_IMPL(integer,  bool Error;_value.toLongLong(&Error);, Error)
CONDITIONAL_VALIDATOR_IMPL(boolean, , _value.canConvert<bool>())
CONDITIONAL_VALIDATOR_IMPL(even,     bool Error;qint64 Value = _value.toLongLong(&Error);, (Error || (Value % 2)))
CONDITIONAL_VALIDATOR_IMPL(odd,      bool Error;qint64 Value = _value.toLongLong(&Error);, (Error || (Value % 2) == 0))
CONDITIONAL_VALIDATOR_IMPL(negative, bool Error;qreal Value = _value.toDouble(&Error);,   (Error || Value >= 0) )
CONDITIONAL_VALIDATOR_IMPL(positive, bool Error;qreal Value = _value.toDouble(&Error);,   (Error || Value < 0) )

QString allwaysValid::validate(const QVariant&,  const QString&)  { return QString(); }
QString allwaysInvalid::validate(const QVariant&,  const QString& _fieldName)  { return _fieldName.isEmpty() ? QString("must be alwasy invalid") : QString("'%1' must be allways invalid").arg(_fieldName); }
CONDITIONAL_VALIDATOR_IMPL(arrayType, , _value.canConvert<QVariantList>())
CONDITIONAL_VALIDATOR_IMPL(objectType, , _value.canConvert<QVariantMap>())

CONDITIONAL_VALIDATOR_IMPL(url, , QUrl(_value.toString()).isValid() == false)
CONDITIONAL_VALIDATOR_IMPL(date, , QDate::fromString(_value.toString(), Qt::ISODateWithMs).isValid() == false)
CONDITIONAL_VALIDATOR_IMPL(time, ,  QTime::fromString(_value.toString(), Qt::ISODateWithMs).isValid() == false)
CONDITIONAL_VALIDATOR_IMPL(dateTime, ,  QDateTime::fromString(_value.toString(), Qt::ISODateWithMs).isValid() == false)

QString notEmpty::validate(const QVariant& _value,  const QString& _fieldName)  {
    auto createError = [_fieldName](bool _isEmpty){
        return _isEmpty ?
                    QString() :
                    (_fieldName.isEmpty() ? QString("must be empty") : QString("'%1' must be empty").arg(_fieldName));

    };

    if(_value.canConvert<QVariantMap>()) return createError(_value.toMap().isEmpty());
    if(_value.canConvert<QVariantList>()) return createError(_value.toList().isEmpty());
    return createError(_value.toString().isEmpty());
}

QString null::validate(const QVariant& _value,  const QString& _fieldName)  {
    return _value.isNull() ? QString() : (_fieldName.isEmpty() ? QString("must be null") : QString("'%1' must be null").arg(_fieldName));
}

QString notNull::validate(const QVariant& _value,  const QString& _fieldName)  {
    return _value.isNull() ? (_fieldName.isEmpty() ? QString("must be null") : QString("'%1' must be null").arg(_fieldName)) : QString();
}

QString minLenght::validate(const QVariant& _value, const QString& _fieldName){
    auto createError = [_fieldName, this](bool _condition){
        return _condition ?
                    QString() :
                    (_fieldName.isEmpty() ? QString("size must be at least: %2").arg(this->Len) : QString("'%1' size must be at least: %2").arg(_fieldName).arg(this->Len));

    };

    if(_value.canConvert<QVariantMap>()) return createError(static_cast<size_t>(_value.toMap().size()) >= this->Len);
    if(_value.canConvert<QVariantList>()) return createError(static_cast<size_t>(_value.toList().size()) >= this->Len);
    return createError(static_cast<size_t>(_value.toString().size()) >= this->Len);
}

QString maxLenght::validate(const QVariant& _value, const QString& _fieldName){
    auto createError = [_fieldName, this](bool _condition){
        return _condition ?
                    QString() :
                    (_fieldName.isEmpty() ? QString("size must be at most: %2").arg(this->Len) : QString("'%1' size must be at most: %2").arg(_fieldName).arg(this->Len));

    };

    if(_value.canConvert<QVariantMap>()) return createError(static_cast<size_t>(_value.toMap().size()) <= this->Len);
    if(_value.canConvert<QVariantList>()) return createError(static_cast<size_t>(_value.toList().size()) <= this->Len);
    return createError(static_cast<size_t>(_value.toString().size()) <= this->Len);
}

QString Private::clsStringComparator::createError(const QString& _fieldName, bool _condition, const char _errMessage[]){
    return _condition ?
                QString() :
                (_fieldName.isEmpty() ? QString("%1: %2").arg(_errMessage, this->Key) : QString("'%1' %2: %3").arg(_fieldName, _errMessage, this->Key));

}

#define STRING_COMPARATOR_IMPL(_class, _errMessage) \
QString _class::validate(const QVariant& _value, const QString& _fieldName){return this->createError(_fieldName, _value.toString()._class(this->Key), _errMessage);}

STRING_COMPARATOR_IMPL(contains, "does not contain")
STRING_COMPARATOR_IMPL(startsWith, "does not contain")
STRING_COMPARATOR_IMPL(endsWith, "does not contain")
QString equals::validate(const QVariant& _value, const QString& _fieldName){
    return _value == this->Var ? QString() :
                                 (_fieldName.isEmpty() ? QString("must be equal to: %2").arg(this->Var.toString()) : QString("'%1' must be equal to: %3").arg(_fieldName, this->Var.toString()));
}

QString matches::validate(const QVariant& _value, const QString& _fieldName){
    return this->Regex.match(_value.toString()).hasMatch() ?
                QString() :
                (_fieldName.isEmpty() ? QString("must be match to: %2").arg(this->Regex.pattern()) : QString("'%1' must be equal to: %3").arg(_fieldName, this->Regex.pattern()));
}

QString mobile::validate(const QVariant& _value, const QString& _fieldName)
{
    static QRegularExpression NoCodeRegex("^0[0-9]{10}$");
    static QRegularExpression WithCodeRegex("^[0-9]{2,3}[0-9]{10}$");

    const QRegularExpression& Regex = this->MandatoryCountry ? WithCodeRegex : NoCodeRegex;
    return Regex.match(_value.toString().replace(Private::rxExtraChars, "")).hasMatch() ? QString() :createErrorString(mobile, _fieldName);
}

QString phone::validate(const QVariant& _value, const QString& _fieldName)
{
    static QRegularExpression NoCodeRegex("^[0-9]{10}$");
    static QRegularExpression WithProvinceRegex("^0[0-9]{10}$");
    static QRegularExpression FullCodeRegex("^[0-9]{2,3}[0-9]{10}$");

    const QRegularExpression& Regex = this->MandatoryCountry ? FullCodeRegex : this->MandatoryProvince ? WithProvinceRegex : NoCodeRegex;
    return Regex.match(_value.toString().replace(Private::rxExtraChars, "")).hasMatch() ? QString() :createErrorString(mobile, _fieldName);
}


}
