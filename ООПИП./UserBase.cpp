#include "UserBase.h"

WorkFile UserBase::save;

UserBase::UserBase(const std::string& loginHash) : loginHash(loginHash) {}