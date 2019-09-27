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
#include <QSet>
#include "CountryBasedValidators.h"
#include "3rdParty/ISO639/ISO639.h"

namespace Validators{
namespace Private {

clsBaseCountryCodeValidator::clsBaseCountryCodeValidator(const QString& _code) : Code(_code) {;}

static QSet<QString> ValidCurrencyCodes = {
    "AFN", // Afghani
    "EUR", // Euro
    "ALL", // Lek
    "DZD", // Algerian Dinar
    "USD", // US Dollar
    "EUR", // Euro
    "AOA", // Kwanza
    "XCD", // East Caribbean Dollar
    "XCD", // East Caribbean Dollar
    "ARS", // Argentine Peso
    "AMD", // Armenian Dram
    "AWG", // Aruban Florin
    "AUD", // Australian Dollar
    "EUR", // Euro
    "AZN", // Azerbaijan Manat
    "BSD", // Bahamian Dollar
    "BHD", // Bahraini Dinar
    "BDT", // Taka
    "BBD", // Barbados Dollar
    "BYN", // Belarusian Ruble
    "EUR", // Euro
    "BZD", // Belize Dollar
    "XOF", // CFA Franc BCEAO
    "BMD", // Bermudian Dollar
    "INR", // Indian Rupee
    "BTN", // Ngultrum
    "BOB", // Boliviano
    "BOV", // Mvdol
    "USD", // US Dollar
    "BAM", // Convertible Mark
    "BWP", // Pula
    "NOK", // Norwegian Krone
    "BRL", // Brazilian Real
    "USD", // US Dollar
    "BND", // Brunei Dollar
    "BGN", // Bulgarian Lev
    "XOF", // CFA Franc BCEAO
    "BIF", // Burundi Franc
    "CVE", // Cabo Verde Escudo
    "KHR", // Riel
    "XAF", // CFA Franc BEAC
    "CAD", // Canadian Dollar
    "KYD", // Cayman Islands Dollar
    "XAF", // CFA Franc BEAC
    "XAF", // CFA Franc BEAC
    "CLP", // Chilean Peso
    "CLF", // Unidad de Fomento
    "CNY", // Yuan Renminbi
    "AUD", // Australian Dollar
    "AUD", // Australian Dollar
    "COP", // Colombian Peso
    "COU", // Unidad de Valor Real
    "KMF", // Comorian Franc
    "CDF", // Congolese Franc
    "XAF", // CFA Franc BEAC
    "NZD", // New Zealand Dollar
    "CRC", // Costa Rican Colon
    "XOF", // CFA Franc BCEAO
    "HRK", // Kuna
    "CUP", // Cuban Peso
    "CUC", // Peso Convertible
    "ANG", // Netherlands Antillean Guilder
    "EUR", // Euro
    "CZK", // Czech Koruna
    "DKK", // Danish Krone
    "DJF", // Djibouti Franc
    "XCD", // East Caribbean Dollar
    "DOP", // Dominican Peso
    "USD", // US Dollar
    "EGP", // Egyptian Pound
    "SVC", // El Salvador Colon
    "USD", // US Dollar
    "XAF", // CFA Franc BEAC
    "ERN", // Nakfa
    "EUR", // Euro
    "ETB", // Ethiopian Birr
    "EUR", // Euro
    "FKP", // Falkland Islands Pound
    "DKK", // Danish Krone
    "FJD", // Fiji Dollar
    "EUR", // Euro
    "EUR", // Euro
    "EUR", // Euro
    "XPF", // CFP Franc
    "EUR", // Euro
    "XAF", // CFA Franc BEAC
    "GMD", // Dalasi
    "GEL", // Lari
    "EUR", // Euro
    "GHS", // Ghana Cedi
    "GIP", // Gibraltar Pound
    "EUR", // Euro
    "DKK", // Danish Krone
    "XCD", // East Caribbean Dollar
    "EUR", // Euro
    "USD", // US Dollar
    "GTQ", // Quetzal
    "GBP", // Pound Sterling
    "GNF", // Guinean Franc
    "XOF", // CFA Franc BCEAO
    "GYD", // Guyana Dollar
    "HTG", // Gourde
    "USD", // US Dollar
    "AUD", // Australian Dollar
    "EUR", // Euro
    "HNL", // Lempira
    "HKD", // Hong Kong Dollar
    "HUF", // Forint
    "ISK", // Iceland Krona
    "INR", // Indian Rupee
    "IDR", // Rupiah
    "XDR", // SDR (Special Drawing Right)
    "IRR", // Iranian Rial
    "IQD", // Iraqi Dinar
    "EUR", // Euro
    "GBP", // Pound Sterling
    "ILS", // New Israeli Sheqel
    "EUR", // Euro
    "JMD", // Jamaican Dollar
    "JPY", // Yen
    "GBP", // Pound Sterling
    "JOD", // Jordanian Dinar
    "KZT", // Tenge
    "KES", // Kenyan Shilling
    "AUD", // Australian Dollar
    "KPW", // North Korean Won
    "KRW", // Won
    "KWD", // Kuwaiti Dinar
    "KGS", // Som
    "LAK", // Lao Kip
    "EUR", // Euro
    "LBP", // Lebanese Pound
    "LSL", // Loti
    "ZAR", // Rand
    "LRD", // Liberian Dollar
    "LYD", // Libyan Dinar
    "CHF", // Swiss Franc
    "EUR", // Euro
    "EUR", // Euro
    "MOP", // Pataca
    "MKD", // Denar
    "MGA", // Malagasy Ariary
    "MWK", // Malawi Kwacha
    "MYR", // Malaysian Ringgit
    "MVR", // Rufiyaa
    "XOF", // CFA Franc BCEAO
    "EUR", // Euro
    "USD", // US Dollar
    "EUR", // Euro
    "MRU", // Ouguiya
    "MUR", // Mauritius Rupee
    "EUR", // Euro
    "XUA", // ADB Unit of Account
    "MXN", // Mexican Peso
    "MXV", // Mexican Unidad de Inversion (UDI)
    "USD", // US Dollar
    "MDL", // Moldovan Leu
    "EUR", // Euro
    "MNT", // Tugrik
    "EUR", // Euro
    "XCD", // East Caribbean Dollar
    "MAD", // Moroccan Dirham
    "MZN", // Mozambique Metical
    "MMK", // Kyat
    "NAD", // Namibia Dollar
    "ZAR", // Rand
    "AUD", // Australian Dollar
    "NPR", // Nepalese Rupee
    "EUR", // Euro
    "XPF", // CFP Franc
    "NZD", // New Zealand Dollar
    "NIO", // Cordoba Oro
    "XOF", // CFA Franc BCEAO
    "NGN", // Naira
    "NZD", // New Zealand Dollar
    "AUD", // Australian Dollar
    "USD", // US Dollar
    "NOK", // Norwegian Krone
    "OMR", // Rial Omani
    "PKR", // Pakistan Rupee
    "USD", // US Dollar
    "PAB", // Balboa
    "USD", // US Dollar
    "PGK", // Kina
    "PYG", // Guarani
    "PEN", // Sol
    "PHP", // Philippine Peso
    "NZD", // New Zealand Dollar
    "PLN", // Zloty
    "EUR", // Euro
    "USD", // US Dollar
    "QAR", // Qatari Rial
    "EUR", // Euro
    "RON", // Romanian Leu
    "RUB", // Russian Ruble
    "RWF", // Rwanda Franc
    "EUR", // Euro
    "SHP", // Saint Helena Pound
    "XCD", // East Caribbean Dollar
    "XCD", // East Caribbean Dollar
    "EUR", // Euro
    "EUR", // Euro
    "XCD", // East Caribbean Dollar
    "WST", // Tala
    "EUR", // Euro
    "STN", // Dobra
    "SAR", // Saudi Riyal
    "XOF", // CFA Franc BCEAO
    "RSD", // Serbian Dinar
    "SCR", // Seychelles Rupee
    "SLL", // Leone
    "SGD", // Singapore Dollar
    "ANG", // Netherlands Antillean Guilder
    "XSU", // Sucre
    "EUR", // Euro
    "EUR", // Euro
    "SBD", // Solomon Islands Dollar
    "SOS", // Somali Shilling
    "ZAR", // Rand
    "SSP", // South Sudanese Pound
    "EUR", // Euro
    "LKR", // Sri Lanka Rupee
    "SDG", // Sudanese Pound
    "SRD", // Surinam Dollar
    "NOK", // Norwegian Krone
    "SZL", // Lilangeni
    "SEK", // Swedish Krona
    "CHF", // Swiss Franc
    "CHE", // WIR Euro
    "CHW", // WIR Franc
    "SYP", // Syrian Pound
    "TWD", // New Taiwan Dollar
    "TJS", // Somoni
    "TZS", // Tanzanian Shilling
    "THB", // Baht
    "USD", // US Dollar
    "XOF", // CFA Franc BCEAO
    "NZD", // New Zealand Dollar
    "TOP", // Pa’anga
    "TTD", // Trinidad and Tobago Dollar
    "TND", // Tunisian Dinar
    "TRY", // Turkish Lira
    "TMT", // Turkmenistan New Manat
    "USD", // US Dollar
    "AUD", // Australian Dollar
    "UGX", // Uganda Shilling
    "UAH", // Hryvnia
    "AED", // UAE Dirham
    "GBP", // Pound Sterling
    "USD", // US Dollar
    "USD", // US Dollar
    "USN", // US Dollar (Next day)
    "UYU", // Peso Uruguayo
    "UYI", // Uruguay Peso en Unidades Indexadas (UI)
    "UYW", // Unidad Previsional
    "UZS", // Uzbekistan Sum
    "VUV", // Vatu
    "VES", // Bolívar Soberano
    "VND", // Dong
    "USD", // US Dollar
    "USD", // US Dollar
    "XPF", // CFP Franc
    "MAD", // Moroccan Dirham
    "YER", // Yemeni Rial
    "ZMW", // Zambian Kwacha
    "ZWL", // Zimbabwe Dollar
    "XBA", // Bond Markets Unit European Composite Unit (EURCO)
    "XBB", // Bond Markets Unit European Monetary Unit (E.M.U.-6)
    "XBC", // Bond Markets Unit European Unit of Account 9 (E.U.A.-9)
    "XBD", // Bond Markets Unit European Unit of Account 17 (E.U.A.-17)
    "XTS", // Codes specifically reserved for testing purposes
    "XXX", // The codes assigned for transactions where no currency is involved
    "XAU", // Gold
    "XPD", // Palladium
    "XPT", // Platinum
    "XAG", // Silver
};

static QHash<QString, QRegularExpression> PostalCodeValidators = {
    {"AD", QRegularExpression("^(?:AD)*(\\d{3})$")},
    {"AL", QRegularExpression("^(\\d{4})$")},
    {"AM", QRegularExpression("^(\\d{6})$")},
    {"AR", QRegularExpression("^[A-Z]?\\d{4}[A-Z]{0,3}$")},
    {"AS", QRegularExpression("96799")},
    {"AT", QRegularExpression("^(\\d{4})$")},
    {"AU", QRegularExpression("^(\\d{4})$")},
    {"AX", QRegularExpression("^(?:FI)*(\\d{5})$")},
    {"AZ", QRegularExpression("^(?:AZ)*(\\d{4})$")},
    {"BA", QRegularExpression("^(\\d{5})$")},
    {"BB", QRegularExpression("^(?:BB)*(\\d{5})$")},
    {"BD", QRegularExpression("^(\\d{4})$")},
    {"BE", QRegularExpression("^(\\d{4})$")},
    {"BG", QRegularExpression("^(\\d{4})$")},
    {"BH", QRegularExpression("^(\\d{3}\\d?)$")},
    {"BL", QRegularExpression("^(\\d{5})$")},
    {"BM", QRegularExpression("^([A-Z]{2}\\d{2})$")},
    {"BN", QRegularExpression("^([A-Z]{2}\\d{4})$")},
    {"BR", QRegularExpression("^\\d{5}-?\\d{3}$")},
    {"BY", QRegularExpression("^(\\d{6})$")},
    {"CA", QRegularExpression("^([ABCEGHJKLMNPRSTVXY]\\d[ABCEGHJKLMNPRSTVWXYZ]) ?(\\d[ABCEGHJKLMNPRSTVWXYZ]\\d)$")},
    {"CH", QRegularExpression("^(\\d{4})$")},
    {"CL", QRegularExpression("^(\\d{7})$")},
    {"CN", QRegularExpression("^(\\d{6})$")},
    {"CO", QRegularExpression("^(\\d{6})$")},
    {"CR", QRegularExpression("^(\\d{5})$")},
    {"CS", QRegularExpression("^(\\d{5})$")},
    {"CU", QRegularExpression("^(?:CP)*(\\d{5})$")},
    {"CV", QRegularExpression("^(\\d{4})$")},
    {"CX", QRegularExpression("^(\\d{4})$")},
    {"CY", QRegularExpression("^(\\d{4})$")},
    {"CZ", QRegularExpression("^\\d{3}\\s?\\d{2}$")},
    {"DE", QRegularExpression("^(\\d{5})$")},
    {"DK", QRegularExpression("^(\\d{4})$")},
    {"DO", QRegularExpression("^(\\d{5})$")},
    {"DZ", QRegularExpression("^(\\d{5})$")},
    {"EC", QRegularExpression("^([a-zA-Z]\\d{4}[a-zA-Z])$")},
    {"EE", QRegularExpression("^(\\d{5})$")},
    {"EG", QRegularExpression("^(\\d{5})$")},
    {"ES", QRegularExpression("^(\\d{5})$")},
    {"ET", QRegularExpression("^(\\d{4})$")},
    {"FI", QRegularExpression("^(?:FI)*(\\d{5})$")},
    {"FM", QRegularExpression("^(\\d{5})$")},
    {"FO", QRegularExpression("^(?:FO)*(\\d{3})$")},
    {"FR", QRegularExpression("^(\\d{5})$")},
    {"GB", QRegularExpression("^([Gg][Ii][Rr] 0[Aa]{2})|((([A-Za-z][0-9]{1,2})|(([A-Za-z][A-Ha-hJ-Yj-y][0-9]{1,2})|(([A-Za-z][0-9][A-Za-z])|([A-Za-z][A-Ha-hJ-Yj-y][0-9]?[A-Za-z])))) [0-9][A-Za-z]{2})$")},
    {"GE", QRegularExpression("^(\\d{4})$")},
    {"GF", QRegularExpression("^((97|98)3\\d{2})$")},
    {"GG", QRegularExpression("^((?:(?:[A-PR-UWYZ][A-HK-Y]\\d[ABEHMNPRV-Y0-9]|[A-PR-UWYZ]\\d[A-HJKPS-UW0-9])\\s\\d[ABD-HJLNP-UW-Z]{2})|GIR\\s?0AA)$")},
    {"GL", QRegularExpression("^(\\d{4})$")},
    {"GP", QRegularExpression("^((97|98)\\d{3})$")},
    {"GR", QRegularExpression("^(\\d{5})$")},
    {"GT", QRegularExpression("^(\\d{5})$")},
    {"GU", QRegularExpression("^(969\\d{2})$")},
    {"GW", QRegularExpression("^(\\d{4})$")},
    {"HN", QRegularExpression("^([A-Z]{2}\\d{4})$")},
    {"HR", QRegularExpression("^(?:HR)*(\\d{5})$")},
    {"HT", QRegularExpression("^(?:HT)*(\\d{4})$")},
    {"HU", QRegularExpression("^(\\d{4})$")},
    {"ID", QRegularExpression("^(\\d{5})$")},
    {"IE", QRegularExpression("^([AC-FHKNPRTV-Y][0-9]{2}|D6W) ?[0-9AC-FHKNPRTV-Y]{4}$")},
    {"IL", QRegularExpression("^(\\d{5})$")},
    {"IM", QRegularExpression("^((?:(?:[A-PR-UWYZ][A-HK-Y]\\d[ABEHMNPRV-Y0-9]|[A-PR-UWYZ]\\d[A-HJKPS-UW0-9])\\s\\d[ABD-HJLNP-UW-Z]{2})|GIR\\s?0AA)$")},
    {"IN", QRegularExpression("^(\\d{6})$")},
    {"IQ", QRegularExpression("^(\\d{5})$")},
    {"IR", QRegularExpression("^(\\d{10})$")},
    {"IS", QRegularExpression("^(\\d{3})$")},
    {"IT", QRegularExpression("^(\\d{5})$")},
    {"JE", QRegularExpression("^((?:(?:[A-PR-UWYZ][A-HK-Y]\\d[ABEHMNPRV-Y0-9]|[A-PR-UWYZ]\\d[A-HJKPS-UW0-9])\\s\\d[ABD-HJLNP-UW-Z]{2})|GIR\\s?0AA)$")},
    {"JO", QRegularExpression("^(\\d{5})$")},
    {"JP", QRegularExpression("^\\d{3}-\\d{4}$")},
    {"KE", QRegularExpression("^(\\d{5})$")},
    {"KG", QRegularExpression("^(\\d{6})$")},
    {"KH", QRegularExpression("^(\\d{5})$")},
    {"KP", QRegularExpression("^(\\d{6})$")},
    {"KR", QRegularExpression("^(\\d{5})$")},
    {"KW", QRegularExpression("^(\\d{5})$")},
    {"KZ", QRegularExpression("^(\\d{6})$")},
    {"LA", QRegularExpression("^(\\d{5})$")},
    {"LB", QRegularExpression("^(\\d{4}(\\d{4})?)$")},
    {"LI", QRegularExpression("^(\\d{4})$")},
    {"LK", QRegularExpression("^(\\d{5})$")},
    {"LR", QRegularExpression("^(\\d{4})$")},
    {"LS", QRegularExpression("^(\\d{3})$")},
    {"LT", QRegularExpression("^(?:LT)*(\\d{5})$")},
    {"LU", QRegularExpression("^(?:L-)?\\d{4}$")},
    {"LV", QRegularExpression("^(?:LV)*(\\d{4})$")},
    {"MA", QRegularExpression("^(\\d{5})$")},
    {"MC", QRegularExpression("^(\\d{5})$")},
    {"MD", QRegularExpression("^MD-\\d{4}$")},
    {"ME", QRegularExpression("^(\\d{5})$")},
    {"MF", QRegularExpression("^(\\d{5})$")},
    {"MG", QRegularExpression("^(\\d{3})$")},
    {"MH", QRegularExpression("^969\\d{2}(-\\d{4})$")},
    {"MK", QRegularExpression("^(\\d{4})$")},
    {"MM", QRegularExpression("^(\\d{5})$")},
    {"MN", QRegularExpression("^(\\d{6})$")},
    {"MP", QRegularExpression("^9695\\d{1}$")},
    {"MQ", QRegularExpression("^(\\d{5})$")},
    {"MT", QRegularExpression("^[A-Z]{3}\\s?\\d{4}$")},
    {"MV", QRegularExpression("^(\\d{5})$")},
    {"MX", QRegularExpression("^(\\d{5})$")},
    {"MY", QRegularExpression("^(\\d{5})$")},
    {"MZ", QRegularExpression("^(\\d{4})$")},
    {"NC", QRegularExpression("^(\\d{5})$")},
    {"NE", QRegularExpression("^(\\d{4})$")},
    {"NF", QRegularExpression("^(\\d{4})$")},
    {"NG", QRegularExpression("^(\\d{6})$")},
    {"NI", QRegularExpression("^(\\d{7})$")},
    {"NL", QRegularExpression("^(\\d{4} ?[A-Z]{2})$")},
    {"NO", QRegularExpression("^(\\d{4})$")},
    {"NP", QRegularExpression("^(\\d{5})$")},
    {"NZ", QRegularExpression("^(\\d{4})$")},
    {"OM", QRegularExpression("^(\\d{3})$")},
    {"PF", QRegularExpression("^((97|98)7\\d{2})$")},
    {"PG", QRegularExpression("^(\\d{3})$")},
    {"PH", QRegularExpression("^(\\d{4})$")},
    {"PK", QRegularExpression("^(\\d{5})$")},
    {"PL", QRegularExpression("^\\d{2}-\\d{3}$")},
    {"PM", QRegularExpression("^(97500)$")},
    {"PR", QRegularExpression("^00[679]\\d{2}(?:-\\d{4})?$")},
    {"PT", QRegularExpression("^\\d{4}-?\\d{3}$")},
    {"PW", QRegularExpression("^(96940)$")},
    {"PY", QRegularExpression("^(\\d{4})$")},
    {"RE", QRegularExpression("^((97|98)(4|7|8)\\d{2})$")},
    {"RO", QRegularExpression("^(\\d{6})$")},
    {"RS", QRegularExpression("^(\\d{6})$")},
    {"RU", QRegularExpression("^(\\d{6})$")},
    {"SA", QRegularExpression("^(\\d{5})$")},
    {"SD", QRegularExpression("^(\\d{5})$")},
    {"SE", QRegularExpression("^(?:SE)?\\d{3}\\s\\d{2}$")},
    {"SG", QRegularExpression("^(\\d{6})$")},
    {"SH", QRegularExpression("^(STHL1ZZ)$")},
    {"SI", QRegularExpression("^(?:SI)*(\\d{4})$")},
    {"SJ", QRegularExpression("^(\\d{4})$")},
    {"SK", QRegularExpression("^\\d{3}\\s?\\d{2}$")},
    {"SM", QRegularExpression("^(4789\\d)$")},
    {"SN", QRegularExpression("^(\\d{5})$")},
    {"SO", QRegularExpression("^([A-Z]{2}\\d{5})$")},
    {"SV", QRegularExpression("^(?:CP)*(\\d{4})$")},
    {"SZ", QRegularExpression("^([A-Z]\\d{3})$")},
    {"TC", QRegularExpression("^(TKCA 1ZZ)$")},
    {"TH", QRegularExpression("^(\\d{5})$")},
    {"TJ", QRegularExpression("^(\\d{6})$")},
    {"TM", QRegularExpression("^(\\d{6})$")},
    {"TN", QRegularExpression("^(\\d{4})$")},
    {"TR", QRegularExpression("^(\\d{5})$")},
    {"TW", QRegularExpression("^(\\d{5})$")},
    {"UA", QRegularExpression("^(\\d{5})$")},
    {"US", QRegularExpression("^\\d{5}(-\\d{4})?$")},
    {"UY", QRegularExpression("^(\\d{5})$")},
    {"UZ", QRegularExpression("^(\\d{6})$")},
    {"VA", QRegularExpression("^(\\d{5})$")},
    {"VE", QRegularExpression("^(\\d{4})$")},
    {"VI", QRegularExpression("^008\\d{2}(?:-\\d{4})?$")},
    {"VN", QRegularExpression("^(\\d{6})$")},
    {"WF", QRegularExpression("^(986\\d{2})$")},
    {"YT", QRegularExpression("^(\\d{5})$")},
    {"ZA", QRegularExpression("^(\\d{4})$")},
    {"ZM", QRegularExpression("^(\\d{5})$")},
};

}

QString idCard::validate(const QVariant& _value, const QString& _fieldName)
{
    Q_UNUSED(_value); Q_UNUSED(_fieldName);
    return "Not implemented Yet";
}

CONDITIONAL_VALIDATOR_IMPL(postalCode, , Private::PostalCodeValidators.value(this->Code).match(_value.toString()).hasMatch())
CONDITIONAL_VALIDATOR_IMPL(languageCode, , ISO639isValid(_value.toString().toLatin1().constData()))

}

