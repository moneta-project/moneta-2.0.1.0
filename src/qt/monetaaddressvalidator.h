// Copyright (c) 2011-2014 The Moneta developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MONETA_QT_MONETAADDRESSVALIDATOR_H
#define MONETA_QT_MONETAADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class MonetaAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MonetaAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Moneta address widget validator, checks for a valid moneta address.
 */
class MonetaAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MonetaAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // MONETA_QT_MONETAADDRESSVALIDATOR_H
