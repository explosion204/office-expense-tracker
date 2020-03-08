#include "moderator.h"

Moderator::Moderator() { }

bool Moderator::canViewDatabase() { return true; }

bool Moderator::canModifyDataDirectly() { return true; }

bool Moderator::canViewModifiedData() { return true; }

bool Moderator::canManageAccounts() { return false; }
