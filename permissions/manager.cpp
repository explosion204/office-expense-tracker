#include "manager.h"

Manager::Manager() { }

bool Manager::canViewDatabase() { return true; }

bool Manager::canModifyDataDirectly() { return false; }

bool Manager::canViewModifiedData() { return false; }

bool Manager::canManageAccounts() { return false; }
