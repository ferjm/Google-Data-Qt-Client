/***************************************************************************
 *   Copyright (C) 2010 Fernando Jiménez Moreno <ferjmoreno@gmail.com>     *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef QTGDATACONTACTKIND_H
#define QTGDATACONTACTKIND_H

//POD Classes representing part of gdContactKind
//http://code.google.com/apis/gdata/docs/2.0/elements.html#gdContactKind

class ExtendedProperty {
public:
    QString name;
    QString value;
    QString realm;
};

class Name {
    QString givenName;
    QString additionalName;
    QString familyName;
    QString namePrefix;
    QString nameSuffix;
    QString fullName;
};

class Organization {
    QString label;
    QString orgName;
    QString orgTitle;
    QString where;
    bool primary;
};

class PhoneNumber {
    QString label;
    QString number;
    bool primary;
};

class StructuredPostalAddress {
    QString street;
    QString city;
    QString region;
    QString formattedAddress;
    QString country;
    QString postcode;
};

class QtgdataContactKind
{
public:
    // atom namespace
    QStringList category;
    QString content;
    QStringList link;
    QString title;
    // gd namespace
    QStringList email;
    QList<ExtendedProperty> extendedProperty;
    bool deleted;
    QStringList im;
    Name name;
    QList<Organization> organization;
    QList<PhoneNumber> phoneNumber;
    QList<StructuredPostalAddress> structuredPostalAddress;
    QString where;
};

#endif // QTGDATACONTACTKIND_H
