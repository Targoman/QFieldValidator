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

#ifndef GENERICVALIDATORS_HPP
#define GENERICVALIDATORS_HPP

#include "intfValidator.hpp"
#include <QRegularExpression>

namespace Validators{
namespace Private {
class clsStringComparator{
protected:
    clsStringComparator(const QString& _key) : Key(_key){;}
    QString createError(const QString& _fieldName, bool _condition, const char _errMessage[]);
    QString Key;
};

static QRegularExpression rxExtraChars("[ \\-\\.]");
}

#define DEFINE_GENERIC_VALIDATOR(_name) class _name : public intfValidator{public: QString validate(const QVariant&, const QString&); }
#define DEFINE_GENERIC_STRING_VALIDATOR(_name) \
    class _name : public intfValidator, private Private::clsStringComparator{public: _name(const QString& _key) : clsStringComparator(_key){;} QString validate(const QVariant&, const QString&);};

#define createErrorString(_class, _fieldName) _fieldName.isEmpty() ? QString("Invalid "#_class": '%1'").arg(_value.toString()) : QString("'%1' must be a valid "#_class).arg(_fieldName)

#define REGEX_BASED_VALIDATOR_IMPL(_class, _regex) \
QString _class::validate(const QVariant& _value, const QString& _fieldName){ \
    static QRegularExpression Regex = _regex;\
    return Regex.match(_value.toString()).hasMatch() ? QString() : createErrorString(_class, _fieldName);\
}

#define CONDITIONAL_VALIDATOR_IMPL(_class, _precondition, _falseCondition) \
    QString _class::validate(const QVariant& _value, const QString& _fieldName) { \
        _precondition; return _falseCondition ? createErrorString(_class, _fieldName) : QString(); \
    }

DEFINE_GENERIC_VALIDATOR(asciiAlNum);
DEFINE_GENERIC_VALIDATOR(unicodeAlNum);
DEFINE_GENERIC_VALIDATOR(lowerCase);
DEFINE_GENERIC_VALIDATOR(upperCase);
DEFINE_GENERIC_VALIDATOR(notEmpty);
DEFINE_GENERIC_VALIDATOR(null);
DEFINE_GENERIC_VALIDATOR(notNull);
class minLenght: public intfValidator{public: minLenght(size_t _len) : Len(_len){;} QString validate(const QVariant& _value, const QString& _fieldName); private: size_t Len;};
class maxLenght: public intfValidator{public: maxLenght(size_t _len) : Len(_len){;} QString validate(const QVariant& _value, const QString& _fieldName); private: size_t Len;};
DEFINE_GENERIC_STRING_VALIDATOR(contains)
DEFINE_GENERIC_STRING_VALIDATOR(startsWith)
DEFINE_GENERIC_STRING_VALIDATOR(endsWith)
class equals: public intfValidator{public: equals(const QVariant& _var) : Var(_var){;} QString validate(const QVariant& _value, const QString& _fieldName); private: QVariant Var;};
class matches: public intfValidator{public: matches(const QRegularExpression& _rx) : Regex(_rx){;} QString validate(const QVariant& _value, const QString& _fieldName); private: QRegularExpression Regex;};

DEFINE_GENERIC_VALIDATOR(real);
DEFINE_GENERIC_VALIDATOR(integer);
DEFINE_GENERIC_VALIDATOR(boolean);
DEFINE_GENERIC_VALIDATOR(hex);
DEFINE_GENERIC_VALIDATOR(even);
DEFINE_GENERIC_VALIDATOR(odd);
DEFINE_GENERIC_VALIDATOR(negative);
DEFINE_GENERIC_VALIDATOR(positive);

DEFINE_GENERIC_VALIDATOR(allwaysInvalid);
DEFINE_GENERIC_VALIDATOR(allwaysValid);
DEFINE_GENERIC_VALIDATOR(arrayType);
DEFINE_GENERIC_VALIDATOR(objectType);

DEFINE_GENERIC_VALIDATOR(date);
DEFINE_GENERIC_VALIDATOR(time);
DEFINE_GENERIC_VALIDATOR(dateTime);

DEFINE_GENERIC_VALIDATOR(url);
DEFINE_GENERIC_VALIDATOR(md5);

class mobile: public intfValidator{public: mobile(bool _c) : MandatoryCountry(_c){;} QString validate(const QVariant& _value, const QString& _fieldName); private: bool MandatoryCountry;};
class phone: public intfValidator{public: phone(bool _p, bool _c) : MandatoryCountry(_c), MandatoryProvince(_p){;} QString validate(const QVariant& _value, const QString& _fieldName); private: bool MandatoryCountry, MandatoryProvince;};

}

#endif // GENERICVALIDATORS_HPP
