#ifndef USER_H
#define USER_H

#include <permissions/permission.h>

class User : public Permission
{
public:
    User();
    bool canViewDatabase() override;
    bool canModifyDataDirectly() override;
    bool canViewModifiedData() override;
    bool canManageAccounts() override;
};

#endif // USER_H
