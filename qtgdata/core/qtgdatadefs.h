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

#ifndef DEFS_H
#define DEFS_H

#include <QString>

#define Ids(...) typedef enum {__VA_ARGS__} tipo;             \
  const QString sAux(#__VA_ARGS__);  

namespace Id
{
    Ids
    (
        NULLID,
        mockId,
        mockId2,
        mockId3,
        mockId4,

        //atom
        feed,
        id,
        category,
        link,
        author,
        name,
        email,
        generator,
        entry,
        updated,
        title,
        subtitle,
        cc,
        uri,
        published,
        summary,
        content,
        total,
        rights,

        //gd
        phoneNumber,
        extendedProperty,
        postalAddress,
        orgName,
        organization,

        //gcs
        file,
        match,
        package
    )
}

namespace AttributeId
{
    Ids
    (
        NULLID,
        mockId,
        mockId1,
        mockId2,
        mockId3,

        //atom
        scheme,
        term,
        title,
        type,
        rel,
        href,
        version,
        uri,
        primary,
        name,

        //openSearch
        totalResults,
        startIndex,
        itemsPerPage,

        //gcs
        lineNumber
    )
}

namespace NamespaceId {
    Ids
    (
        NULLID,
        mockId,
        atom,
        openSearch,
        gContact,
        batch,
        gd,
        thr,
        xmlns,
        gcs
    )
}

/* Error codes */
typedef enum {
    QTGDATA_ERROR_CANCELLED = -1,
    QTGDATA_SUCCESS = 0,
    QTGDATA_ERROR_RESOLUTION,
    QTGDATA_ERROR_CONNECTION,
    QTGDATA_ERROR_SSL,
    QTGDATA_ERROR_IO,
    QTGDATA_ERROR_FAILED,
    QTGDATA_ERROR_INVALID_PARAMETER,
    QTGDATA_ERROR_PARSER,
    QTGDATA_FILE_ERROR,
    QTGDATA_MEMORY_ERROR,
    QTGDATA_SEC_UNAUTHORIZED,

    QTGDATA_ERROR_HTTP_MULTIPLE_CHOICES = 300,
    QTGDATA_ERROR_HTTP_MOVED_PERMANENTLY = 301,
    QTGDATA_ERROR_HTTP_FOUND = 302,
    QTGDATA_ERROR_HTTP_SEE_OTHER = 303,
    QTGDATA_ERROR_HTTP_NOT_MODIFIED = 304,
    QTGDATA_ERROR_HTTP_USE_PROXY = 305,
    QTGDATA_ERROR_HTTP_THREEOHSIX = 306,
    QTGDATA_ERROR_HTTP_TEMPORARY_REDIRECT = 307,
    QTGDATA_ERROR_HTTP_BAD_REQUEST = 400,
    QTGDATA_ERROR_HTTP_UNAUTHORIZED = 401,
    QTGDATA_ERROR_HTTP_FOUROHTWO = 402,
    QTGDATA_ERROR_HTTP_FORBIDDEN = 403,
    QTGDATA_ERROR_HTTP_NOT_FOUND = 404,
    QTGDATA_ERROR_HTTP_METHOD_NOT_ALLOWED = 405,
    QTGDATA_ERROR_HTTP_NOT_ACCEPTABLE = 406,
    QTGDATA_ERROR_HTTP_PROXY_AUTHENTICATION_REQUIRED = 407,
    QTGDATA_ERROR_HTTP_REQUEST_TIMEOUT = 408,
    QTGDATA_ERROR_HTTP_CONFLICT = 409,
    QTGDATA_ERROR_HTTP_GONE = 410,
    QTGDATA_ERROR_HTTP_LENGTH_REQUIRED = 411,
    QTGDATA_ERROR_HTTP_PRECONDITION_FAILED = 412,
    QTGDATA_ERROR_HTTP_REQUEST_ENTITY_TOO_LARGE = 413,
    QTGDATA_ERROR_HTTP_REQUEST_URI_TOO_LONG = 414,
    QTGDATA_ERROR_HTTP_UNSUPPORTED_MEDIA_TYPE = 415,
    QTGDATA_ERROR_HTTP_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
    QTGDATA_ERROR_HTTP_EXPECTATION_FAILED = 417,
    QTGDATA_ERROR_HTTP_INTERNAL_SERVER_ERROR = 500,
    QTGDATA_ERROR_HTTP_NOT_IMPLEMENTED = 501,
    QTGDATA_ERROR_HTTP_BAD_GATEWAY = 502,
    QTGDATA_ERROR_HTTP_SERVICE_UNAVAILABLE = 503,
    QTGDATA_ERROR_HTTP_GATEWAY_TIMEOUT = 504,
    QTGDATA_ERROR_HTTP_HTTP_VERSION_NOT_SUPPORTED = 505,
} QTGDATAReturnCode;

/* OAuth strings */
const QString OAUTH_KEY_CONSUMER("oauth_consumer");
const QString OAUTH_KEY_CONSUMER_KEY("oauth_consumer_key");
const QString OAUTH_KEY_TOKEN("oauth_token");
const QString OAUTH_KEY_TOKEN_SECRET("oauth_token_secret");
const QString OAUTH_KEY_SIGNATURE_METHOD("oauth_signature_method");
const QString OAUTH_KEY_TIMESTAMP("oauth_timestamp");
const QString OAUTH_KEY_NONCE("oauth_nonce");
const QString OAUTH_KEY_SIGNATURE("oauth_signature");
const QString OAUTH_KEY_CALLBACK("oauth_callback");
const QString OAUTH_KEY_VERIFIER("oauth_verifier");
const QString OAUTH_KEY_VERSION("oauth_version");

#endif // DEFS_H
