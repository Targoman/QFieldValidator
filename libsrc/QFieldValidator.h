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

#ifndef QFIELDVALIDATOR_H
#define QFIELDVALIDATOR_H

#include <QString>
#include <QException>
#include <QVariant>

class QFieldValidatorPrivate;

class QFieldValidator
{
public:
    class exQFieldValidator : public QException {
    public:
        exQFieldValidator(const QString& _message);
        const char* what() const _GLIBCXX_USE_NOEXCEPT;
        virtual ~exQFieldValidator();
    private:
      QByteArray Message;
    };

    class exRequiredParam : public exQFieldValidator{
        public: exRequiredParam(const QString& _message);
        virtual ~exRequiredParam();
    };
    class exInvalidValue : public exQFieldValidator{
        public: exInvalidValue(const QString& _message);
        virtual ~exInvalidValue();
    };

    struct CreditCards{
        typedef enum {
            Any,
            VISA,
            MasterCard,
            AmericanExpress,
            DinersClub,
            Discover,
            JCB,
            Parsian,
            Mellat
        } Type;
    };

public:
    QFieldValidator();
    QFieldValidator(const QFieldValidator& _other);
    QFieldValidator& operator =(const QFieldValidator& _other);
    ~QFieldValidator();
    /**
     * @brief isValid Validates based on settings
     * @param _value Value to be checked
     * @param _fieldName name of the field to be validated. If ommited it will not be shown in error messages
     * @return true if was correct
     */
    bool isValid(const QVariant& _value, const QString& _fieldName = QString());
    /**
     * @brief validate validates based on settings, Throws if any error with the first error message
     * @param _value Value to be checked
     * @param _fieldName name of the field to be validated. If ommited it will not be shown in error messages
     */
    void validate(const QVariant& _value, const QString& _fieldName = QString());

    /**
     * @brief errorMessage return last error message
     * @return last error message if any
     */
    const QString& errorMessage();

    void reset();

    QFieldValidator& optional(QFieldValidator& _validator);
    QFieldValidator& oneOf(const QList<QFieldValidator>& _validators);
    QFieldValidator& allOf(const QList<QFieldValidator>& _validators);
    QFieldValidator& when(const QFieldValidator& _if, const QFieldValidator& _then, const QFieldValidator& _else);

    /*********************/
    QFieldValidator& asciiAlNum(bool _allowSpace = false, const QString& _extraValidChars = QString());
    QFieldValidator& unicodeAlNum(bool _allowSpace = false, const QString& _extraValidChars = QString());
    QFieldValidator& lowerCase();
    QFieldValidator& upperCase();
    QFieldValidator& notEmpty();
    QFieldValidator& notNull();
    QFieldValidator& minLenght(size_t _len);
    QFieldValidator& maxLenght(size_t _len);
    QFieldValidator& noWhiteSpace(size_t _len);
    QFieldValidator& contains(const QString& _value);
    QFieldValidator& startsWith(const QString& _value);
    QFieldValidator& endsWith(const QString& _value);
    QFieldValidator& equals(const QVariant& _value);
    QFieldValidator& matches(const QRegularExpression& _value);
    /*********************/
    QFieldValidator& real();
    QFieldValidator& integer();
    QFieldValidator& boolean();
    QFieldValidator& even();
    QFieldValidator& odd();
    QFieldValidator& hex();
    QFieldValidator& negative();
    QFieldValidator& positive();
    /*********************/
    QFieldValidator& allwaysInvalid();
    QFieldValidator& allwaysValid();
    QFieldValidator& arrayType();
    QFieldValidator& objectType();
    /*********************/
    QFieldValidator& json();
    QFieldValidator& hasKey(const QString& _key, QFieldValidator& _validator = QFieldValidator().allwaysValid(), bool _mandatory = true);
    QFieldValidator& hasNestedKey(const QString& _key, QFieldValidator& _validator = QFieldValidator().allwaysValid(), bool _mandatory = true);
    /*********************/
    QFieldValidator& date();
    QFieldValidator& time();
    QFieldValidator& dateTime();
    QFieldValidator& url();
    QFieldValidator& md5();
    QFieldValidator& languageCode();
    QFieldValidator& email();
    QFieldValidator& emailNotFake();
    QFieldValidator& emailJustDomains(const QSet<QString>& _validDomains);
    QFieldValidator& emailNotDomains(const QSet<QString>& _validDomains, bool _alsoNotFake = true);
    QFieldValidator& mobile(bool _mandatoryCountryCode = false);
    QFieldValidator& phone(bool _mandatoryProvinceCode = true, bool _mandatoryCountryCode = false);
    QFieldValidator& idCard(const QString& _country = "IR");
    QFieldValidator& postalCode(const QString& _country = "IR");
    QFieldValidator& iban(const QString& _country = "IR");
    QFieldValidator& creditCard(CreditCards::Type _type);
    /*********************/
    QFieldValidator& minValue(double _value);
    QFieldValidator& maxValue(double _value);
    QFieldValidator& betweenValues(double _first, double _second);
    /*********************/

private:
    QSharedDataPointer<QFieldValidatorPrivate> Data;
};

#define QFV QFieldValidator()

#endif // QFIELDVALIDATOR_H



