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

#include "PhoneValidators.h"
#include <QString>
#include "Exceptions.h"
#include "GenericValidators.h"

#include <string>
using namespace std;

#include "phonenumbers/phonenumberutil.h"
using namespace i18n::phonenumbers;

namespace Validators {
namespace Private {

bool IsValidNumberForString(
    const string &number,
    const string &region_dialing_from)
{
    PhoneNumber number_proto;

    if (PhoneNumberUtil::GetInstance()->Parse(number, region_dialing_from, &number_proto) != PhoneNumberUtil::NO_PARSING_ERROR)
        return false;

    return PhoneNumberUtil::GetInstance()->IsValidNumberForRegion(number_proto, region_dialing_from);
}

bool IsPossibleNumberForType(
    const string &number,
    const string &region_dialing_from,
    PhoneNumberUtil::PhoneNumberType type)
{
    PhoneNumber number_proto;

    if (PhoneNumberUtil::GetInstance()->Parse(number, region_dialing_from, &number_proto) != PhoneNumberUtil::NO_PARSING_ERROR)
        return false;

    return PhoneNumberUtil::GetInstance()->IsPossibleNumberForType(number_proto, type);
}

} //namespace Private

QString mobile::validate(const QVariant& _value, const QString& _fieldName)
{
    ///TODO: make country code paremetric
    return Private::IsPossibleNumberForType(_value.toString().toStdString(), this->Country.toStdString(), PhoneNumberUtil::MOBILE)
        ? QString()
        : createErrorString(mobile, _fieldName);
}

QString phone::validate(const QVariant& _value, const QString& _fieldName)
{
    PhoneNumberUtil* phoneNumberUtil = (PhoneNumberUtil*)PhoneNumberUtil::GetInstance();

    ///TODO: make country code paremetric
    return phoneNumberUtil->IsPossibleNumberForString(_value.toString().toStdString(), this->Country.toStdString())
        ? QString()
        : createErrorString(phone, _fieldName);
}

} //namespace Validators
