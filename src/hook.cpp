#include "pch.h"
#include "hook.h"
#include "hook-manager.h"
#include "il2cpp-init.h"
#include "il2cpp-appdata.h"
#include "util.h"

#define length(array) ((sizeof(array)) / (sizeof(array[0])))

namespace hook {
	VOID Install() {
		HookManager::install(app::MiHoYo__SDK__SDKUtil_RSAEncrypt, hook::MiHoYo__SDK__SDKUtil_RSAEncrypt);
		HookManager::install(app::MoleMole__RSAUtil_GetRSAPublicKey, hook::MoleMole__RSAUtil_GetRSAPublicKey);
		HookManager::install(app::MoleMole__RSAUtil_GetRSAPrivateKey, hook::MoleMole__RSAUtil_GetRSAPrivateKey);
	}

	LPVOID MiHoYo__SDK__SDKUtil_RSAEncrypt(LPVOID publicKey, LPVOID content) {
		std::cout << "[hook] MiHoYo__SDK__SDKUtil_RSAEncrypt reached." << std::endl;
		const char* rsaPublicKey = util::GetRSAPublicKey();
		if (length(rsaPublicKey) != 0) {
			std::cout << "[hook] MiHoYo__SDK__SDKUtil_RSAEncrypt use config.ini value." << std::endl;
			publicKey = il2cpp_string_new(rsaPublicKey);
		}
		return CALL_ORIGIN(MiHoYo__SDK__SDKUtil_RSAEncrypt, publicKey, content);
	}

	LPVOID MoleMole__RSAUtil_GetRSAPublicKey() {
		std::cout << "[hook] MoleMole__RSAUtil_GetRSAPublicKey reached." << std::endl;
		const char* key = util::GetRSAPublicKey();
		if (length(key) == 0) {
			return CALL_ORIGIN(MoleMole__RSAUtil_GetRSAPublicKey);
		}
		std::cout << "[hook] MiHoYo__SDK__SDKUtil_RSAEncrypt use config.ini value." << std::endl;
		auto encoding = app::System__Text__EncodingHelper_GetDefaultEncoding();
		return app::System__Text__Encoding_GetBytes(encoding, il2cpp_string_new(key));
	}

	LPVOID MoleMole__RSAUtil_GetRSAPrivateKey() {
		std::cout << "[hook] MoleMole__RSAUtil_GetRSAPrivateKey reached." << std::endl;
		const char* key = util::GetRSAPrivateKey();
		if (length(key) == 0) {
			return CALL_ORIGIN(MoleMole__RSAUtil_GetRSAPrivateKey);
		}
		std::cout << "[hook] MoleMole__RSAUtil_GetRSAPrivateKey use config.ini value." << std::endl;
		auto encoding = app::System__Text__EncodingHelper_GetDefaultEncoding();
		return app::System__Text__Encoding_GetBytes(encoding, il2cpp_string_new(key));
	}
}
