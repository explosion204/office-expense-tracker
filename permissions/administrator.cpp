#include "administrator.h"

Administrator::Administrator() { }

bool Administrator::canViewDatabase() { return true; }

bool Administrator::canModifyDataDirectly() { return true; }

bool Administrator::canViewModifiedData() { return true; }

bool Administrator::canManageAccounts() { return true; }
