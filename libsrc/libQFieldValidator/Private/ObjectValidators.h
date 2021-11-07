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

#ifndef OBJECTVALIDATORS_H
#define OBJECTVALIDATORS_H

#include "GenericValidators.h"
#include "QFieldValidator.h"

namespace Validators{
namespace Private {
class clsBaseObjectValidator{
protected:
    clsBaseObjectValidator(const QString& _key, QFieldValidator& _validator, bool _mandatory);

protected:
    const QString& Key;
    QFieldValidator& Validator;
    bool Mandatory;
};
}


DEFINE_GENERIC_VALIDATOR(json);

class hasKey : public intfValidator, private Private::clsBaseObjectValidator{
public:
    hasKey(const QString& _key, QFieldValidator& _validator, bool _mandatory);
    QString validate(const QVariant& _value, const QString& _fieldName);
};

class hasNestedKey : public intfValidator, private Private::clsBaseObjectValidator{
public:
    hasNestedKey(const QString& _key, QFieldValidator& _validator, bool _mandatory);
    QString validate(const QVariant& _value, const QString& _fieldName);
};


}

#endif // OBJECTVALIDATORS_H
