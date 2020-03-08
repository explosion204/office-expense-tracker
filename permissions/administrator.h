#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <permissions/permission.h>

class Administrator : public Permission
{
public:
    Administrator();
    bool canViewDatabase() override;
    bool canModifyDataDirectly() override;
    bool canViewModifiedData() override;
    bool canManageAccounts() override;
};

#endif // ADMINISTRATOR_H
