#ifndef PERMISSION_H
#define PERMISSION_H


class Permission
{
public:
    Permission() { }

    virtual bool canViewDatabase() = 0;
    virtual bool canModifyDataDirectly() = 0;
    virtual bool canViewModifiedData() = 0;
    virtual bool canManageAccounts() = 0;
};

#endif // PERMISSION_H
