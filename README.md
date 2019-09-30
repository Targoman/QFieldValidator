
#  QFieldValidator



The  most  awesome  validation  engine  ever  created  for  C++.



###  Table  of  contents

-  [Motivation](#motivation)

-  [Features](#features)

-  [Setup](#setup)

-  [Source  tree](#source-tree)

-  [Credits](#credits)

-  [License](#license)





#  Motivation

[TOC](#table-of-contents)

Qt  is  one  of  the  best  frameworks  for  C++  mostly  used  for  GUI  and  Mobile  application  but  also  usefull  for  developing  high-end  backends.  I  looked  for  a  good  validation  library  to  be  used  in  companion  with  QRestServer  but  I  couldn't  find  any  good  one,  So  I  developed  this  library  based  on  [Respect\Validation](https://github.com/Respect/Validation)  php  library.


#  Features

[TOC](#table-of-contents)

##  Simple  validation
The  Hello  World  validator  is  something  like  this:
``` C++
    QString foo = "bar";
    QFieldValidator().notEmpty().validate(foo);
```
## Chained validation
It is possible to use validators in a chain. Sample below validates a string containing numbers and letters, no whitespace and length between 1 and 15.
``` C++
    QString foo = "bar";
    QFieldValidator().asciiAlNum().minLenght(1).maxLenght(15).validate(foo);
```
## Conditioanl validators
There are three conditional methods that can be used for complex rules:
- `oneOf(const  QList<QFieldValidator>&  _validators)`
    Used when the value can match with any of the specified validation rules
    ```c++
          QFieldValidator().oneOf({
              QFieldValidator().email(),
              QFieldValidator().mobile()
          }).isValid("09136477280");
    ```
- `allOf(const  QList<QFieldValidator>&  _validators)`
    This is an alias for chained rules
    ```c++
          QFieldValidator().allOf({
              QFieldValidator().asciiAlNum(),
              QFieldValidator().minLenght(5)
          }).isValid("09136477280");
    ```
- `when(const  QFieldValidator&  _if,  const  QFieldValidator&  _then,  const  QFieldValidator&  _else)`
    For binary conditions when to validate based on the type of value
    ```c++
          QFieldValidator().when({
              QFieldValidator().email(),
              QFieldValidator().emailNotDomain("gmail.com",true),
              QFieldValidator().mobile()
          }).isValid("09136477280");
    ```

## Validation methods
There are two main methods to validate a value:
- `bool isValid(const  QVariant&  _value,  const  QString&  _fieldName  =  QString()) `
    This method will validate without throwing an excption. returns false on any error and error message can be accessed by `errorMessage()` method
- `void  validate(const  QVariant&  _value,  const  QString&  _fieldName  =  QString());`
    This method will throw an excption on any error with a full description of the error as exception message

## Validating object attributes
Given this simple object:
```c++
const char user[]="{\"name\": \"Mehran\"},{\"mobile\": \"09126174582\"}";
```
It is possible to validate its attributes in a single chain:
```c++
QFieldValidator().hasKey("name")
                 .hasKey("mobile", QFieldValidator().mobile())
                 .validate(user);
```
Or with more complex and nested objects:
Given this simple object:
```c++
QJsonObject user={
    {"name", "Mehran"},
    {"info", QVariantMap({
                             {"mobile", "09126174582"}
                         })
    }
};
```
It is possible to validate its attributes in a single chain:
```c++
QFieldValidator().hasKey("name")
                 .hasNestedKey("info.mobile", QFieldValidator().mobile())
                 .validate(user);
```
## Input optional
All chained rules are mandatory in QfieeldValidator so if you want to treat a value as optional you can use  `QFieldValidator::optional()`  rule:
```c++
QString sampleEmpty;
QString sampleString = "abcd";
QString sampleMobile = "09126578425";

QFieldValidator mobileValidator = QFieldValidator().mobile();

mobileValidator.isValid(sampleEmpty);  //false as mobile number is empty
mobileValidator.isValid(sampleString); //false as it is no mobile
mobileValidator.isValid(sampleMobile); //true

QFiledValidator().optional(mobileValidator).isValid(sampleEmpty)  //true as was optional
QFiledValidator().optional(mobileValidator).isValid(sampleString) //false as it is incorrect
QFiledValidator().optional(mobileValidator).isValid(sampleMobile) //true
```
## Validator reuse
Once created, you can reuse your validator anywhere. Remember `mobileValidator` ?
```c++
mobileValidator.isValid("");  //false as mobile number is empty
mobileValidator.isValid("abcd"); //false as it is no mobile
mobileValidator.isValid("0915154650"); //true
```

## Exception types
### QFieldValidator::exQFieldValidator
This exception is thrown just if there were an error creating a validator. As said at coding time not run time and independednt of the validating value
## QFieldValidator::exRequiredParam
This exception is thrown when a required parameter is passed as empty or null except when specified as optional
## QFieldValidator::exInvalidValue
This exception is thrown when a required parameter is set but invalid according to the chained rules

#  Setup

[TOC](#table-of-contents)

  Installation is described in [INSTALL](./INSTALL) file


#  Credits

[TOC](#table-of-contents)

Main  idea  of  this  library  has  been  derived  from [Respect\Validation](https://github.com/Respect/Validation) PHP library



#  License

[TOC](#table-of-contents)



QFieldValidator  has  been  published  under  the  terms  of  [GNU  LESSER  GENERAL  PUBLIC  LICENSE](./LICENSE)  as  published  by  the  Free  Software  Foundation,  either  version  3  of  the  License,  or  (at  your  option)  any  later  version.
