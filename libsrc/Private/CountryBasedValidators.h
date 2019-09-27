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

#ifndef COUNTRYBASEDVALIDATORS_H
#define COUNTRYBASEDVALIDATORS_H

#include "GenericValidators.h"
#include "QFieldValidator.h"

namespace Validators{
namespace Private {
class clsBaseCountryCodeValidator{
protected:
    clsBaseCountryCodeValidator(const QString& _code);
    const QString& Code;
};
}

DEFINE_GENERIC_VALIDATOR(languageCode);

class idCard : public intfValidator, private Private::clsBaseCountryCodeValidator{
public:
    idCard(const QString& _code) : clsBaseCountryCodeValidator(_code) {;}
    QString validate(const QVariant& _value, const QString& _fieldName);
};

class postalCode : public intfValidator, private Private::clsBaseCountryCodeValidator{
public:
    postalCode(const QString& _code) : clsBaseCountryCodeValidator(_code) {;}
    QString validate(const QVariant& _value, const QString& _fieldName);
};


}
#endif // COUNTRYBASEDVALIDATORS_H
