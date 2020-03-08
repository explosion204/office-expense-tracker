#include "user.h"

User::User() { }

bool User::canViewDatabase() { return false; }

bool User::canModifyDataDirectly() { return false; }

bool User::canViewModifiedData() { return false; }

bool User::canManageAccounts() { return false; }
