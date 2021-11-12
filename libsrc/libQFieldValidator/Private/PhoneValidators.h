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
 * @author Kambiz Zandi <kambizzandi@gmail.com>
 */

#ifndef PHONEVALIDATORS_H
#define PHONEVALIDATORS_H

#include "intfValidator.hpp"

namespace Validators {

class mobile : public intfValidator
{
public:
    mobile(const QString& _country = "IR", bool _c = false) :
        Country(_country),
        MandatoryCountry(_c)
    {}

    QString validate(const QVariant& _value, const QString& _fieldName);

private:
    QString Country;
    bool MandatoryCountry;
};

class phone : public intfValidator
{
public:
    phone(const QString& _country = "IR", bool _p = true, bool _c = false) :
        Country(_country),
        MandatoryCountry(_c),
        MandatoryProvince(_p)
    {}

    QString validate(const QVariant& _value, const QString& _fieldName);

private:
    QString Country;
    bool MandatoryCountry;
    bool MandatoryProvince;
};

} //namespace Validators

#endif // PHONEVALIDATORS_H
