#pragma once

#include "pch.h"

namespace hook {
	VOID Install();
	LPVOID MiHoYo__SDK__SDKUtil_RSAEncrypt(LPVOID publicKey, LPVOID content);
	LPVOID MoleMole__RSAUtil_GetRSAPublicKey();
	LPVOID MoleMole__RSAUtil_GetRSAPrivateKey();
}
