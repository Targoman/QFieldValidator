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

#ifndef PHONENUMBERUTIL_HPP
#define PHONENUMBERUTIL_HPP

#include <QString>
#include "Exceptions.h"

#include <string>
using namespace std;

#include "phonenumbers/phonenumberutil.h"
//using namespace i18n::phonenumbers;

namespace Targoman {

class PhoneNumberUtil : public i18n::phonenumbers::PhoneNumberUtil
{
public:
    bool IsValidNumberForString(
        const string &number,
        const string &region_dialing_from) const
    {
        i18n::phonenumbers::PhoneNumber number_proto;

        if (Parse(number, region_dialing_from, &number_proto) != NO_PARSING_ERROR)
            return false;

        return i18n::phonenumbers::PhoneNumberUtil::IsValidNumberForRegion(number_proto, region_dialing_from);
    }

    bool IsPossibleNumberForType(
        const string &number,
        const string &region_dialing_from,
        PhoneNumberType type) const
    {
        i18n::phonenumbers::PhoneNumber number_proto;

        if (Parse(number, region_dialing_from, &number_proto) != NO_PARSING_ERROR)
            return false;

        return i18n::phonenumbers::PhoneNumberUtil::IsPossibleNumberForType(number_proto, type);
    }

    static QString GetErrorTypeAsString(const ErrorType& _errorType)
    {
        switch (_errorType)
        {
            case ErrorType::INVALID_COUNTRY_CODE_ERROR:
                return "Invalid Country Code";
            case ErrorType::NOT_A_NUMBER:
                return "Not A Number";
            case ErrorType::TOO_SHORT_AFTER_IDD:
                return "Too Short After IDD";
            case ErrorType::TOO_SHORT_NSN:
                return "Too Short NSN";
            case ErrorType::TOO_LONG_NSN:
                return "Too Long NSN";
            default:
                return "Unknown Error";
        }
    }

    static QString NormalizePhoneNumber(QString _number, const QString& _defCountry="IR")
    {
        PhoneNumberUtil* phoneNumberUtil = (PhoneNumberUtil*)PhoneNumberUtil::GetInstance();

        i18n::phonenumbers::PhoneNumber number_proto;
        PhoneNumberUtil::ErrorType ret = phoneNumberUtil->Parse(_number.toStdString(), _defCountry.toStdString(), &number_proto);
        if (ret != NO_PARSING_ERROR)
            throw exQFieldValidator(QString("Error in parsing phone number: %1").arg(GetErrorTypeAsString(ret)));

        string formatted_number;
        phoneNumberUtil->Format(number_proto, i18n::phonenumbers::PhoneNumberUtil::PhoneNumberFormat::E164, &formatted_number);
        return formatted_number.c_str();
    }

};

}

#endif // PHONENUMBERUTIL_HPP
