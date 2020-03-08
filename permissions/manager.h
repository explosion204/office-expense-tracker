#ifndef MANAGER_H
#define MANAGER_H

#include <permissions/permission.h>

class Manager : public Permission
{
public:
    Manager();
    bool canViewDatabase() override;
    bool canModifyDataDirectly() override;
    bool canViewModifiedData() override;
    bool canManageAccounts() override;
};

#endif // MANAGER_H
