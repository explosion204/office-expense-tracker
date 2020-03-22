#include "account.h"

Account::Account(QString username, QString password_hash, PermissionType permission_type)
{
    this->username = username;
    this->password_hash = password_hash;
    this->permission_type = permission_type;
    switch (permission_type)
    {
        case ADMIN:
            this->permission = new Administrator();
            break;
        case MODERATOR:
            this->permission = new Moderator();
            break;
        case MANAGER:
            this->permission = new Manager();
            break;
    }
}

QString Account::getUsername() { return username; }

QString Account::getPasswordHash() { return password_hash; }

Permission* Account::getPermission() { return permission; }

PermissionType Account::getPermissionType() { return permission_type; }
