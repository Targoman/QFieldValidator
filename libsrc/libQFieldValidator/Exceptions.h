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

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QException>

/****************************************************************/
class exQFieldValidator : public QException {
public:
    exQFieldValidator(const QString& _message);
    virtual ~exQFieldValidator();

public:
    const char* what() const _GLIBCXX_USE_NOEXCEPT;

private:
    QByteArray Message;
};

/****************************************************************/
class exQFVRequiredParam : public exQFieldValidator {
public:
    exQFVRequiredParam(const QString& _message);
    virtual ~exQFVRequiredParam();
};

/****************************************************************/
class exQFVInvalidValue : public exQFieldValidator {
public:
    exQFVInvalidValue(const QString& _message);
    virtual ~exQFVInvalidValue();
};

/****************************************************************/
#endif // EXCEPTIONS_H
