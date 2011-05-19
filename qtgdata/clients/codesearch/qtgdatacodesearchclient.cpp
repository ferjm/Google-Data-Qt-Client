#include "qtgdatacodesearchclient.h"

QtgdataCodeSearchClient::QtgdataCodeSearchClient(IAuthentication *auth, int version, QObject *parent) :
    QtgdataClient(version,parent)
{
    setAuthenticationData(auth);
}
