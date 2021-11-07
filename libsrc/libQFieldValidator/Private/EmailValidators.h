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

#ifndef EMAILVALIDATORS_H
#define EMAILVALIDATORS_H

#include "GenericValidators.h"
#include "QFieldValidator.h"

namespace Validators{
namespace Private {
class clsDomainBasedValidators{
protected:
    clsDomainBasedValidators(const QSet<QString>& _domain);
    const QSet<QString>& Domains;
};
}

DEFINE_GENERIC_VALIDATOR(email);
DEFINE_GENERIC_VALIDATOR(emailNotFake);

class emailJustDomains : public intfValidator, private Private::clsDomainBasedValidators{
public:
    emailJustDomains(const QSet<QString>& _domains);
    QString validate(const QVariant& _value, const QString& _fieldName);
};

class emailNotDomains : public intfValidator, private Private::clsDomainBasedValidators{
public:
    emailNotDomains(const QSet<QString>& _domains, bool _alsoNotFake);
    QString validate(const QVariant& _value, const QString& _fieldName);

private:
    bool AlsoNotFake;
};


}
#endif // EMAILVALIDATORS_H
