/***********************************************************************
*
* Copyright (c) 2012-2015 Barbara Geller
* Copyright (c) 2012-2015 Ansel Sermersheim
* Copyright (c) 2012-2014 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* This file is part of CopperSpice.
*
* CopperSpice is free software: you can redistribute it and/or 
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with CopperSpice.  If not, see 
* <http://www.gnu.org/licenses/>.
*
***********************************************************************/

#ifndef QDBUSBUS_H
#define QDBUSBUS_H

#include <QtCore/qstringlist.h>
#include <QtDBus/qdbusabstractinterface.h>
#include <QtDBus/qdbusreply.h>

#ifndef QT_NO_DBUS


QT_BEGIN_NAMESPACE

class QDBusConnection;
class QString;
class QByteArray;

/*
 * Proxy class for interface org.freedesktop.DBus
 */
class Q_DBUS_EXPORT QDBusConnectionInterface: public QDBusAbstractInterface
{
    CS_OBJECT(QDBusConnectionInterface)
    CS_ENUM(ServiceQueueOptions)
    CS_ENUM(ServiceReplacementOptions)
    CS_ENUM(RegisterServiceReply)
    friend class QDBusConnectionPrivate;
    static inline const char *staticInterfaceName();

    explicit QDBusConnectionInterface(const QDBusConnection &connection, QObject *parent);
    ~QDBusConnectionInterface();

    CS_PROPERTY_READ(registeredServiceNames, registeredServiceNames)

public:
    enum ServiceQueueOptions {
        DontQueueService,
        QueueService,
        ReplaceExistingService
    };
    enum ServiceReplacementOptions {
        DontAllowReplacement,
        AllowReplacement
    };
    enum RegisterServiceReply {
        ServiceNotRegistered = 0,
        ServiceRegistered,
        ServiceQueued
    };

public :
    CS_SLOT_1(Public, QDBusReply<QStringList> registeredServiceNames())
    CS_SLOT_2(registeredServiceNames) 
    CS_SLOT_1(Public, QDBusReply<bool> isServiceRegistered(const QString & serviceName)const)
    CS_SLOT_2(isServiceRegistered) 
    CS_SLOT_1(Public, QDBusReply<QString> serviceOwner(const QString & name)const)
    CS_SLOT_2(serviceOwner) 
    CS_SLOT_1(Public, QDBusReply<bool> unregisterService(const QString & serviceName))
    CS_SLOT_2(unregisterService) 
    CS_SLOT_1(Public, QDBusReply<QDBusConnectionInterface::RegisterServiceReply> registerService(const QString & serviceName,ServiceQueueOptions qoption = DontQueueService,ServiceReplacementOptions roption = DontAllowReplacement))
    CS_SLOT_2(registerService):

    CS_SLOT_1(Public, QDBusReply<uint> servicePid(const QString & serviceName)const)
    CS_SLOT_2(servicePid) 
    CS_SLOT_1(Public, QDBusReply<uint> serviceUid(const QString & serviceName)const)
    CS_SLOT_2(serviceUid) 

    CS_SLOT_1(Public, QDBusReply<void> startService(const QString & name))
    CS_SLOT_2(startService) 

public:
    CS_SIGNAL_1(Public, void serviceRegistered(const QString & service))
    CS_SIGNAL_2(serviceRegistered,service) 
    CS_SIGNAL_1(Public, void serviceUnregistered(const QString & service))
    CS_SIGNAL_2(serviceUnregistered,service) 
    CS_SIGNAL_1(Public, void serviceOwnerChanged(const QString & name,const QString & oldOwner,const QString & newOwner))
    CS_SIGNAL_2(serviceOwnerChanged,name,oldOwner,newOwner) 
    CS_SIGNAL_1(Public, void callWithCallbackFailed(const QDBusError & error,const QDBusMessage & call))
    CS_SIGNAL_2(callWithCallbackFailed,error,call) 

    // internal signals
    // do not use
    CS_SIGNAL_1(Public, void NameAcquired(const QString & un_named_arg1))
    CS_SIGNAL_2(NameAcquired,un_named_arg1) 
    CS_SIGNAL_1(Public, void NameLost(const QString & un_named_arg1))
    CS_SIGNAL_2(NameLost,un_named_arg1) 
    CS_SIGNAL_1(Public, void NameOwnerChanged(const QString & un_named_arg1,const QString & un_named_arg2,const QString & un_named_arg3))
    CS_SIGNAL_2(NameOwnerChanged,un_named_arg1,un_named_arg2,un_named_arg3) 

protected:
    void connectNotify(const char *);
    void disconnectNotify(const char *);

};

QT_END_NAMESPACE

Q_DECLARE_BUILTIN_METATYPE(QDBusConnectionInterface::RegisterServiceReply, UInt)

#endif // QT_NO_DBUS
#endif
