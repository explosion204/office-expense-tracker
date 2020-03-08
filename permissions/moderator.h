#ifndef MODERATOR_H
#define MODERATOR_H

#include <permissions/permission.h>

class Moderator : public Permission
{
public:
    Moderator();
    bool canViewDatabase() override;
    bool canModifyDataDirectly() override;
    bool canViewModifiedData() override;
    bool canManageAccounts() override;
};

#endif // MODERATOR_H
