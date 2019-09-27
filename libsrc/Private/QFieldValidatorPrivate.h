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
#ifndef CLSQFIELDVALIDATORPRIVATE_H
#define CLSQFIELDVALIDATORPRIVATE_H

#include <QString>
#include <QVariant>
#include <QSharedData>
#include "intfValidator.hpp"

class QFieldValidator;
class QFieldValidatorPrivate : public QSharedData
{
public:
    enum enuCriteria{
        CRITERIA_Signle,
        CRITERIA_OneOf,
        CRITERIA_AllOf
    };

    typedef QList<intfValidator*> ValidatorList_t;

public:
    QFieldValidatorPrivate();
    bool isValid(const QVariant& _value, const QString& _fieldName);
    bool isEmpty(const QVariant& _value);
    void reset();

private:
    bool checkAllRules(const QVariant& value, const QString& _fieldName);

public:
    QString FieldName;
    QVariant Value;
    QString ErrorMessage;
    bool IsOptional;
    enuCriteria Criteria;
    ValidatorList_t SingleValidators;

    QList<QFieldValidator*> MultiValidators;
    QFieldValidator* IfValidator;
    QFieldValidator* ElseValidator;
};


#endif // CLSQFIELDVALIDATORPRIVATE_H
