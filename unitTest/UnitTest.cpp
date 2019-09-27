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
 * @author S. Mehran M. Ziabary <ziabary@targoman.com>
 */
#include "UnitTest.h"
#include "QFieldValidator.h"

#define VERIFY_VALIDATOR(_validator, _trueValue, _falseValue) \
    QVERIFY(QFieldValidator()._validator.isValid(_trueValue)); \
    QVERIFY(QFieldValidator()._validator.isValid(_falseValue) == false)


void UnitTest::GenericValidators()
{
    VERIFY_VALIDATOR(asciiAlNum(), "abcASD543", "ace\';'");
    VERIFY_VALIDATOR(unicodeAlNum(), "abcینتاASD543", "acییe\';'");
    VERIFY_VALIDATOR(lowerCase(), "abc", "Ace\';'");
    VERIFY_VALIDATOR(lowerCase(), "abc", "Aیی\';'");
    VERIFY_VALIDATOR(upperCase(), "SD543", "ace\';'");
    VERIFY_VALIDATOR(upperCase(), "SD543", "ؤيAA");



    //VERIFY_VALIDATOR(null(), QString(), "ace\';'");
    //VERIFY_VALIDATOR(null(), QVariant(), "ace\';'");

    //VERIFY_VALIDATOR(notNull(), "ace\';'", QString());
    //VERIFY_VALIDATOR(notNull(), "ace\';'", QVariant());

    VERIFY_VALIDATOR(minLenght(5), "abcde", "abc");
    VERIFY_VALIDATOR(maxLenght(5), "abc", "abcdefghi");

    VERIFY_VALIDATOR(contains("abc"), "baabc", "aaaa");
    VERIFY_VALIDATOR(contains("abc"), QVariantList({"abc"}), QVariantList({"baabc"}));
    VERIFY_VALIDATOR(contains("abc"), QVariantMap({{"abc", 1}}), QVariantMap({{"baabc",2}}));

    //VERIFY_VALIDATOR(notEmpty(), "a", "");
    //VERIFY_VALIDATOR(notEmpty(), QVariantList({{2},{3}}), QVariantList());
    //VERIFY_VALIDATOR(notEmpty(), QVariantMap({{"2","ewe"},{"3","w"}}), QVariantMap());

}

void UnitTest::EmailValidators()
{

}

void UnitTest::BankValidators()
{

}

void UnitTest::CountryBasedValidators()
{

}

void UnitTest::complexValidators()
{

}

QTEST_MAIN(UnitTest)

