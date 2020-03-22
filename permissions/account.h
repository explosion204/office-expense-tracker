#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <permissions/permission.h>
#include <permissions/administrator.h>
#include <permissions/moderator.h>
#include <permissions/manager.h>
#include <lib/picosha2.h>

enum PermissionType
{
    ADMIN, MODERATOR, MANAGER
};

class Account
{
private:
    QString username;
    QString password_hash;
    Permission *permission;
    PermissionType permission_type;
public:
    Account(QString username, QString password_hash, PermissionType permission_type);
    QString getUsername();
    QString getPasswordHash();
    Permission* getPermission();
    PermissionType getPermissionType();
};

#endif // ACCOUNT_H
