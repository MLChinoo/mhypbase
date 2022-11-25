#pragma once

#include "pch.h"

namespace hook {
	VOID Install();
	LPVOID MiHoYo__SDK__SDKUtil_RSAEncrypt(LPVOID publicKey, LPVOID content);
	LPVOID MoleMole__MoleMoleSecurity_GetPublicRSAKey();
	LPVOID MoleMole__MoleMoleSecurity_GetPrivateRSAKey();
}
