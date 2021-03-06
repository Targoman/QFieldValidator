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

    VERIFY_VALIDATOR(notEmpty(), "a", "");
    VERIFY_VALIDATOR(notEmpty(), QVariantList({{2},{3}}), QVariantList());
    VERIFY_VALIDATOR(notEmpty(), QVariantMap({{"2","ewe"},{"3","w"}}), QVariantMap());

    VERIFY_VALIDATOR(notNull(), "ace\';'", QVariant());
    VERIFY_VALIDATOR(notNull(), "ace\';'", QString());

    VERIFY_VALIDATOR(minLenght(5), "abcde", "abc");
    VERIFY_VALIDATOR(maxLenght(5), "abc", "abcdefghi");

    VERIFY_VALIDATOR(contains("abc"), "baabc", "aaaa");
    VERIFY_VALIDATOR(startsWith("abc"), "abcdef", "aabcaaa");
    VERIFY_VALIDATOR(endsWith("abc"), "baabc", "aabcaa");

    VERIFY_VALIDATOR(contains("abc"), "baabc", "aaaa");

    VERIFY_VALIDATOR(equals("abc"), "abc", "aaaa");
    VERIFY_VALIDATOR(equals(QVariantMap({{"abc",123}})), QVariantMap({{"abc",123}}), "aaaa");
    VERIFY_VALIDATOR(equals(QVariantMap({{"abc",123}})), QVariantHash({{"abc",123}}), "aaaa");

    VERIFY_VALIDATOR(matches(QRegularExpression("^\\d+$")), "1234", "abcd");
    VERIFY_VALIDATOR(matches(QRegularExpression("^\\d+$")), "1234", "abcd");

    VERIFY_VALIDATOR(real(), 1.2, "abc");
    VERIFY_VALIDATOR(integer(), 1, "a");
    VERIFY_VALIDATOR(boolean(), true, QVariantList());
    VERIFY_VALIDATOR(boolean(), 1, QVariantList({}));
    VERIFY_VALIDATOR(even(), 2, 1);
    VERIFY_VALIDATOR(odd(), 3, 6);
    VERIFY_VALIDATOR(hex(), "abcdef1234567890", "qwedsa");
    VERIFY_VALIDATOR(negative(), "-1234", "1234");
    VERIFY_VALIDATOR(positive(), "1234", "-1234");

    QVERIFY(QFieldValidator().allwaysInvalid().isValid("_trueValue") == false);
    QVERIFY(QFieldValidator().allwaysValid().isValid("_trueValue"));

    VERIFY_VALIDATOR(arrayType(), QVariantList({"abcd"}), "-1234");
    VERIFY_VALIDATOR(arrayType(), QVariantList({"abcd"}), QVariantMap({{"iyu", "1234"}}));

    VERIFY_VALIDATOR(objectType(), QVariantMap({{"abcd", 1234}}), "-1234");
    VERIFY_VALIDATOR(objectType(), QVariantMap({{"abcd", 1234}}), QVariantList({"iyu"}));

    VERIFY_VALIDATOR(date(), "2018-12-01", "1999-13-01");
    VERIFY_VALIDATOR(date(), "1999/12/01", "1999-02-29");
    VERIFY_VALIDATOR(time(), "12:26", "1999/12/01");
    VERIFY_VALIDATOR(time(), "12:26:32", "1999/12/01");
    VERIFY_VALIDATOR(time(), "12:26:32.345", "1999/12/01");
    VERIFY_VALIDATOR(dateTime(), "1999-12-01T12:26:32", "1999/02/29");
    VERIFY_VALIDATOR(dateTime(), "1999/12/01 12:26:32.354", "1999/02/29");
    VERIFY_VALIDATOR(dateTime(), "1999-12-01", "1999/02/29");

    VERIFY_VALIDATOR(url(), "test.com", "1234");
    VERIFY_VALIDATOR(url(), "ftp://test.com", "-1234");
    VERIFY_VALIDATOR(url(), "localhost", "-1234");
    VERIFY_VALIDATOR(url(), "127.0.0.1", "-1234");
    VERIFY_VALIDATOR(url(), "http://127.0.0.1", "-1234");
    VERIFY_VALIDATOR(md5(), "66b89aa15f5f7ea67926d29d02dce7a8", "-1234");
}

void UnitTest::ObjectValidators()
{
    VERIFY_VALIDATOR(json(), "{\"1234\":\"abcd\"}", "-1234");
    VERIFY_VALIDATOR(json(), "{}", "{\"1234\"}");
    VERIFY_VALIDATOR(json(), "[\"1234\",1234,\"abcd\"]", "-1234");

    VERIFY_VALIDATOR(hasKey("1234",QFieldValidator().allwaysValid(),true), "{\"1234\":\"abcd\"}", "{\"12345\":{\"1234\":1234}}");
    VERIFY_VALIDATOR(hasKey("1234",QFieldValidator().allwaysValid(),true), QVariantMap({{"1234", "abcd"}}), QVariantMap({{"12345","1234"}}));
    VERIFY_VALIDATOR(hasKey("1234", QFieldValidator().equals("abcd")),
                     QVariantMap({{"1234", "abcd"}}),
                     QVariantMap({{"1234", "1234"}}));
    VERIFY_VALIDATOR(hasKey("1234", QFieldValidator().equals("abcd"), true),
                     QVariantMap({{"1234", "abcd"}}),
                     QVariantMap({{"1234", "1234"}}));

    VERIFY_VALIDATOR(hasNestedKey("ab.cd",QFieldValidator().allwaysValid(), true),
                     QVariantMap({{"ab", QVariantMap({{"cd",1234}})}}),
                     QVariantMap({{"12345","1234"}}));
}

void UnitTest::EmailValidators()
{
    VERIFY_VALIDATOR(email(), "test@4warding.com", "baba/ddexample.com");
    VERIFY_VALIDATOR(emailNotFake(), "test+dfd@gmail.com", "baba@4warding.com");
    VERIFY_VALIDATOR(emailJustDomains({"gmail.com"}), "test@gmail.com", "babadd@hotmail.com");
    VERIFY_VALIDATOR(emailNotDomains({"gmail.com"}), "test@hotmail.com", "babadd@gmail.com");
    VERIFY_VALIDATOR(emailNotDomains({"gmail.com"}, true), "test@hotmail.com", "test@4warding.com");
}

void UnitTest::BankValidators()
{
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::Any), "6221-0610-7157-2589", "6221-0610-7157a2589");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::Any), "6221061071572589", "6221-0610-7157a2589");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::JCB), "3530111333300000", "6221-0610-7157-2589");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::Mellat), "6104337869844439", "6221061071560751");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::Parsian), "6221061071560751", "6104337869844439");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::Discover), "6011 0000 0000 0004", "6104337869844439");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::DinersClub), "3000 0000 0000 04", "6104337869844439");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::MasterCard), "5500 0000 0000 0004", "6104337869844439");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::AmericanExpress), "371449635398431", "6104337869844439");
    VERIFY_VALIDATOR(creditCard(QFieldValidator::CreditCards::VISA), "4012888888881881", "6221-0610-7157-2589");
}

void UnitTest::CountryBasedValidators()
{
    VERIFY_VALIDATOR(postalCode("IR"), "1556913554", "15494");
    VERIFY_VALIDATOR(postalCode("BR"), "02179-000", "02179");
    VERIFY_VALIDATOR(postalCode("BR"), "02179000", "02179.000");
    VERIFY_VALIDATOR(postalCode("CA"), "A1A 2B2", "1A1B2B");
    VERIFY_VALIDATOR(postalCode("GB"), "GIR 0AA", "GIR 00A");
    VERIFY_VALIDATOR(postalCode("GB"), "PR1 9LY", "GIR0AA");
}

void UnitTest::complexValidators()
{
    VERIFY_VALIDATOR(optional(QFieldValidator().md5()), "", "1234");
    VERIFY_VALIDATOR(when(QFieldValidator().email(),
                          QFieldValidator().emailNotFake(),
                          QFieldValidator().phone()
                          ), "mehran@gmail.com", "abbas@emailo.pro");
    VERIFY_VALIDATOR(when(QFieldValidator().email(),
                          QFieldValidator().emailNotFake(),
                          QFieldValidator().mobile()
                          ), "09126184250", "qazwsx");
    VERIFY_VALIDATOR(oneOf({
                               QFieldValidator().email(),
                               QFieldValidator().mobile()
                           }),
                        "09126175251",
                        "bab.com"
                     );
    VERIFY_VALIDATOR(oneOf({
                               {QFieldValidator().email()},
                               {QFieldValidator().mobile()}
                           }),
                        "ali@reza.com",
                        "bab.com"
                     );
    VERIFY_VALIDATOR(allOf({
                               {QFieldValidator().email()},
                               {QFieldValidator().maxLenght(10)}
                           }),
                        "ba@ma.com",
                        "baba@ma.com"
                     );
}

QTEST_MAIN(UnitTest)

