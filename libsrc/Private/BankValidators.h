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

#ifndef BANKVALIDATORS_H
#define BANKVALIDATORS_H

#include "CountryBasedValidators.h"

namespace Validators{
namespace Private {

}

class creditCard : public intfValidator{
public:
    creditCard(QFieldValidator::CreditCards::Type _type) : Type(_type) {;}
    QString validate(const QVariant& _value, const QString& _fieldName);
private:
    QFieldValidator::CreditCards::Type Type;
};

class iban : public intfValidator, private Private::clsBaseCountryCodeValidator{
public:
    iban(const QString& _code) : clsBaseCountryCodeValidator(_code) {;}
    QString validate(const QVariant& _value, const QString& _fieldName);
private:
    QFieldValidator::CreditCards::Type Type;
};

}

#endif // BANKVALIDATORS_H
