#include "pch.h"
#include "hook.h"
#include "hook-manager.h"
#include "il2cpp-init.h"
#include "il2cpp-appdata.h"
#include "util.h"

namespace hook {
	VOID Install() {
		HookManager::install(app::MiHoYo__SDK__SDKUtil_RSAEncrypt, hook::MiHoYo__SDK__SDKUtil_RSAEncrypt);
		HookManager::install(app::MoleMole__MoleMoleSecurity_GetPublicRSAKey, hook::MoleMole__MoleMoleSecurity_GetPublicRSAKey);
		HookManager::install(app::MoleMole__MoleMoleSecurity_GetPrivateRSAKey, hook::MoleMole__MoleMoleSecurity_GetPrivateRSAKey);
	}

	LPVOID MiHoYo__SDK__SDKUtil_RSAEncrypt(LPVOID publicKey, LPVOID content) {
		std::cout << "[hook] MiHoYo__SDK__SDKUtil_RSAEncrypt reached." << std::endl;
		const char* key = util::GetPublicRSAKey();
		if (key != nullptr) {
			std::cout << "[hook] MiHoYo__SDK__SDKUtil_RSAEncrypt using the configured value." << std::endl;
			publicKey = il2cpp_string_new(key);
		}
		return CALL_ORIGIN(MiHoYo__SDK__SDKUtil_RSAEncrypt, publicKey, content);
	}

	LPVOID MoleMole__MoleMoleSecurity_GetPublicRSAKey() {
		std::cout << "[hook] MoleMole__MoleMoleSecurity_GetPublicRSAKey reached." << std::endl;
		const char* key = util::GetPublicRSAKey();
		if (key == nullptr) {
			return CALL_ORIGIN(MoleMole__MoleMoleSecurity_GetPublicRSAKey);
		}
		std::cout << "[hook] MoleMole__MoleMoleSecurity_GetPublicRSAKey using the configured value." << std::endl;
		auto encoding = app::System__Text__EncodingHelper_GetDefaultEncoding();
		return app::System__Text__Encoding_GetBytes(encoding, il2cpp_string_new(key));
	}

	LPVOID MoleMole__MoleMoleSecurity_GetPrivateRSAKey() {
		std::cout << "[hook] MoleMole__MoleMoleSecurity_GetPrivateRSAKey reached." << std::endl;
		const char* key = util::GetPrivateRSAKey();
		if (key == nullptr) {
			return CALL_ORIGIN(MoleMole__MoleMoleSecurity_GetPrivateRSAKey);
		}
		std::cout << "[hook] MoleMole__MoleMoleSecurity_GetPrivateRSAKey using the configured value." << std::endl;
		auto encoding = app::System__Text__EncodingHelper_GetDefaultEncoding();
		return app::System__Text__Encoding_GetBytes(encoding, il2cpp_string_new(key));
	}
}
