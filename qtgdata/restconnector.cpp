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

#ifdef QTGDATA_DEBUG
#include <QDebug>
#endif

#include <sstream>

#include "restconnector.h"
#include "ientity.h"

IEntity* RestConnector::CreateEntity(const IEntity *in)
{
#ifdef QTGDATA_DEBUG
    qDebug() << "\nCreateEntity In: \n" << in->toString() << "\n";
#endif
    switch(in->getId())
    {
    case Id::mockId:
        break;
    default:
        break;
    }
    return ReturnError(QTGDATA_ERROR_INVALID_PARAMETER);
}

IEntity* RestConnector::RetrieveEntity(const IEntity *in)
{
    return ReturnError(QTGDATA_ERROR_INVALID_PARAMETER);
}

IEntity* RestConnector::UpdateEntity(const IEntity *in)
{
    return ReturnError(QTGDATA_ERROR_INVALID_PARAMETER);
}

IEntity* RestConnector::DeleteEntity(const IEntity *in)
{
    return ReturnError(QTGDATA_ERROR_INVALID_PARAMETER);
}


/* Protected Functions */
IEntity* RestConnector::ReturnError(unsigned int reason)
{
    IEntity *res = new IEntity(NamespaceId::NULLID, Id::NULLID);
    char aux[10];
    snprintf(aux, sizeof(aux), "%d", reason);
    res->addValue(aux);
#ifdef QTGDATA_DEBUG
    qDebug() << "\nReturnError:\n" << res->toString() << "\n";
#endif
    return res;
}

IEntity* RestConnector::ReturnError(unsigned int uiReason, QString sReason)
{
    std::ostringstream oss;
    oss << uiReason;
    QString sCode(oss.str().c_str());
    sCode += " - " + sReason;
    IEntity *res = new IEntity(NamespaceId::NULLID, Id::NULLID, sCode);
    return res;
}

/* Private functions */
IEntity* RestConnector::MockFunction(const IEntity *mockEntity)
{

}
