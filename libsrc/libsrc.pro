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
    QFieldValidator.cpp \
    Private/QFieldValidatorPrivate.cpp \
    Private/GenericValidators.cpp \
    Private/ObjectValidators.cpp \
    Private/CountryBasedValidators.cpp \
    Private/EmailValidators.cpp \
    Private/BankValidators.cpp

OTHER_FILES += \

################################################################################
include($$QBUILD_PATH/templates/libConfigs.pri)

