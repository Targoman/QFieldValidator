################################################################################
#   QBuildSystem
#
#   Copyright(c) 2021 by Targoman Intelligent Processing <http://tip.co.ir>
#
#   Redistribution and use in source and binary forms are allowed under the
#   terms of BSD License 2.0.
################################################################################

# +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-#
DIST_HEADERS += \
    Exceptions.h \
    PhoneNumberUtil.hpp \
    QFieldValidator.h \

PRIVATE_HEADERS += \
    Private/intfValidator.hpp \
    Private/QFieldValidatorPrivate.h \
    Private/GenericValidators.h \
    Private/ObjectValidators.h \
    Private/CountryBasedValidators.h \
    Private/EmailValidators.h \
    Private/BankValidators.h \

# +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-#
SOURCES += \
    Private/QFieldValidatorPrivate.cpp \
    Private/GenericValidators.cpp \
    Private/ObjectValidators.cpp \
    Private/CountryBasedValidators.cpp \
    Private/EmailValidators.cpp \
    Private/BankValidators.cpp \
    Exceptions.cpp \
    QFieldValidator.cpp \

OTHER_FILES += \

LIBS += \
    -lprotobuf \
    -lphonenumber \

################################################################################
include($$QBUILD_PATH/templates/libConfigs.pri)

!exists(/usr/lib64/libphonenumber.so*) {
    error (**** Unable to find linphonenumber.so ****\n\
    zypper ar -f https://download.opensuse.org/repositories/devel:/libraries:/c_c++/openSUSE_Leap_15.2/ devel_libraries\n\
    zypper install libphonenumber8 libphonenumber-devel)
}
