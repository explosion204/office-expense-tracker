#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <permissions/permission.h>
#include <permissions/administrator.h>
#include <permissions/moderator.h>
#include <permissions/manager.h>
#include <permissions/user.h>
#include <lib/picosha2.h>

enum PermissionType
{
    ADMIN, MODERATOR, MANAGER, USER
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
    void setUsername(QString username);
    void setPassword(QString password_hash);
    void setPermissionType(PermissionType permission_type);
};

#endif // ACCOUNT_H
