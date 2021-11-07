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
    libQFieldValidator/Exceptions.h \
    libQFieldValidator/PhoneNumberUtil.hpp \
    libQFieldValidator/QFieldValidator.h

PRIVATE_HEADERS += \
    libQFieldValidator/Private/intfValidator.hpp \
    libQFieldValidator/Private/QFieldValidatorPrivate.h \
    libQFieldValidator/Private/GenericValidators.h \
    libQFieldValidator/Private/ObjectValidators.h \
    libQFieldValidator/Private/CountryBasedValidators.h \
    libQFieldValidator/Private/EmailValidators.h \
    libQFieldValidator/Private/BankValidators.h

# +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-#
SOURCES += \
    libQFieldValidator/Private/QFieldValidatorPrivate.cpp \
    libQFieldValidator/Private/GenericValidators.cpp \
    libQFieldValidator/Private/ObjectValidators.cpp \
    libQFieldValidator/Private/CountryBasedValidators.cpp \
    libQFieldValidator/Private/EmailValidators.cpp \
    libQFieldValidator/Private/BankValidators.cpp \
    libQFieldValidator/Exceptions.cpp \
    libQFieldValidator/QFieldValidator.cpp \
    libID.cpp

OTHER_FILES += \

LIBS += \
    -lprotobuf \
    -lphonenumber

################################################################################
include($$QBUILD_PATH/templates/libConfigs.pri)

!exists(/usr/lib64/libphonenumber.so*) {
    error (**** Unable to find linphonenumber.so ****\n\
    zypper ar -f https://download.opensuse.org/repositories/devel:/libraries:/c_c++/openSUSE_Leap_15.2/ devel_libraries\n\
    zypper install libphonenumber8 libphonenumber-devel)
}
