#pragma once

#include "pch.h"
#include "hook-manager.h"
#include "il2cpp-appdata.h"

#include "config.hpp"
#include "util.hpp"

namespace hook
{
	const char* WarnLuaScript = "[warn] Server is trying to execute a Lua script remotely, which is potentially dangerous if not from a trusted source.";

	std::string uint64_to_hex_string(uint64_t value)
	{
		std::ostringstream os;
		os << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << value;
		return os.str();
	}

	LPVOID MiHoYo__SDK__SDKUtil_RSAEncrypt(LPVOID publicKey, LPVOID content)
	{
		auto command = util::ConvertToString(publicKey);
		if ((command.find("get_rva") != std::string::npos))
		{
			uintptr_t baseAddress = (uintptr_t)GetModuleHandle("UserAssembly.dll");
			auto index = std::stoi(util::ConvertToString(content));
			auto klass = il2cpp__vm__MetadataCache__GetTypeInfoFromTypeDefinitionIndex((uint32_t)index);
			std::string text = il2cpp__vm__Type__GetName(&reinterpret_cast<uintptr_t*>(klass)[config::GetMagicA()], 0);
			if (text.length() == 0)
				text.append("<nil>");
			text.append(";");
			void* iter = 0;
			while (const LPVOID method = il2cpp__vm__Class__GetMethods(klass, (LPVOID)&iter))
			{
				auto method_address = reinterpret_cast<uintptr_t*>(method)[config::GetMagicB()];
				if (method_address)
					method_address = method_address - baseAddress;
				text.append(uint64_to_hex_string(method_address) + ";");
			}
			return il2cpp_string_new(text.c_str());
		}
		else
		{
			const char* key = config::GetRSAEncryptKey();
			if (key != nullptr)
			{
				util::Log("[hook] Reached MiHoYo__SDK__SDKUtil_RSAEncrypt, and using the configured value.");
				publicKey = il2cpp_string_new(key);
			}
		}
		return CALL_ORIGIN(MiHoYo__SDK__SDKUtil_RSAEncrypt, publicKey, content);
	}

	LPVOID MoleMole__MoleMoleSecurity_GetPublicRSAKey()
	{
		const char* key = config::GetPublicRSAKey();
		if (key == nullptr)
		{
			return CALL_ORIGIN(MoleMole__MoleMoleSecurity_GetPublicRSAKey);
		}
		util::Log("[hook] Reached MoleMole__MoleMoleSecurity_GetPublicRSAKey, and using the configured value.");
		auto encoding = app::System__Text__EncodingHelper_GetDefaultEncoding();
		return app::System__Text__Encoding_GetBytes(encoding, il2cpp_string_new(key));
	}

	LPVOID MoleMole__MoleMoleSecurity_GetPrivateRSAKey()
	{
		const char* key = config::GetPrivateRSAKey();
		if (key == nullptr)
		{
			return CALL_ORIGIN(MoleMole__MoleMoleSecurity_GetPrivateRSAKey);
		}
		util::Log("[hook] Reached MoleMole__MoleMoleSecurity_GetPrivateRSAKey, and using the configured value.");
		auto encoding = app::System__Text__EncodingHelper_GetDefaultEncoding();
		return app::System__Text__Encoding_GetBytes(encoding, il2cpp_string_new(key));
	}

	LPVOID MoleMole__RSAUtil_RSAEncrypt(LPVOID key, LPVOID data)
	{
		const char* pub = config::GetPublicRSAKey();
		if (pub == nullptr)
		{
			return CALL_ORIGIN(MoleMole__RSAUtil_RSAEncrypt, key, data);
		}
		util::Log("[hook] Reached MoleMole__RSAUtil_RSAEncrypt, and using the configured value.");
		return CALL_ORIGIN(MoleMole__RSAUtil_RSAEncrypt, il2cpp_string_new(pub), data);
	}

	LPVOID MoleMole__RSAUtil_RSADecrypt(LPVOID key, LPVOID data)
	{
		const char* priv = config::GetPrivateRSAKey();
		if (priv == nullptr)
		{
			return CALL_ORIGIN(MoleMole__RSAUtil_RSADecrypt, key, data);
		}
		util::Log("[hook] Reached MoleMole__RSAUtil_RSADecrypt, and using the configured value.");
		return CALL_ORIGIN(MoleMole__RSAUtil_RSADecrypt, il2cpp_string_new(priv), data);
	}

	LPVOID MoleMole__RSAUtil_RSAVerifyHash(LPVOID key, LPVOID bytes, LPVOID sign)
	{
		const char* pub = config::GetPublicRSAKey();
		if (pub == nullptr)
		{
			return CALL_ORIGIN(MoleMole__RSAUtil_RSAVerifyHash, key, bytes, sign);
		}
		util::Log("[hook] Reached MoleMole__RSAUtil_RSAVerifyHash, and using the configured value.");
		return CALL_ORIGIN(MoleMole__RSAUtil_RSAVerifyHash, il2cpp_string_new(pub), bytes, sign);
	}

	LPVOID MoleMole__RSAUtil_RSAVerifyData(LPVOID key, LPVOID bytes, LPVOID sign)
	{
		const char* priv = config::GetPublicRSAKey();
		if (priv == nullptr)
		{
			return CALL_ORIGIN(MoleMole__RSAUtil_RSAVerifyData, key, bytes, sign);
		}
		util::Log("[hook] Reached MoleMole__RSAUtil_RSAVerifyData, and using the configured value.");
		return CALL_ORIGIN(MoleMole__RSAUtil_RSAVerifyData, il2cpp_string_new(priv), bytes, sign);
	}

	std::string TryPatchConfig(std::string text)
	{
		if (text.find("DispatchConfigs") != std::string::npos)
		{
			const char* text = config::GetConfigChannel();
			if (text != nullptr)
			{
				util::Log("[hook] Reached StreamingAssets\\20527480.blk, and using the configured value.");
				return std::string(text);
			}
		}
		else if (text.find("activity_domain") != std::string::npos)
		{
			const char* config = config::GetConfigBaseUrl();
			if (config != nullptr)
			{
				util::Log("[hook] Reached StreamingAssets\\MiHoYoSDKRes\\PC\\mihoyo_sdk_res, and using the configured value.");
				std::regex pattern("(https?://[a-z0-9\\.\\-:]+)");
				text = std::regex_replace(text, pattern, config);
				return text.c_str();
			}
		}
		return "";
	}

	LPVOID UnityEngine__JsonUtility_FromJson(LPVOID json, LPVOID type, LPVOID method)
	{
		auto text = TryPatchConfig(util::ConvertToString(json));
		if (text != "")
		{
			json = il2cpp_string_new(text.c_str());
		}
		return CALL_ORIGIN(UnityEngine__JsonUtility_FromJson, json, type, method);
	}

	LPVOID MoleMole__ConfigUtil_LoadJSONStrConfig(LPVOID jsonText, LPVOID useJsonUtility, LPVOID method)
	{
		auto text = TryPatchConfig(util::ConvertToString(jsonText));
		if (text != "")
		{
			jsonText = il2cpp_string_new(text.c_str());
		}
		return CALL_ORIGIN(MoleMole__ConfigUtil_LoadJSONStrConfig, jsonText, useJsonUtility, method);
	}

	LPVOID MoleMole__FightModule_OnWindSeedClientNotify(LPVOID __this, LPVOID notify)
	{
		util::Log("[hook] Blocked MoleMole__FightModule_OnWindSeedClientNotify function.");
		util::Log(WarnLuaScript);
		return nullptr;
	}

	LPVOID MoleMole__PlayerModule_OnWindSeedClientNotify(LPVOID __this, LPVOID notify)
	{
		util::Log("[hook] Blocked MoleMole__PlayerModule_OnWindSeedClientNotify function.");
		util::Log(WarnLuaScript);
		return nullptr;
	}

	LPVOID MoleMole__PlayerModule_OnReciveLuaShell(LPVOID __this, LPVOID notify)
	{
		util::Log("[hook] Blocked MoleMole__PlayerModule_OnReciveLuaShell function.");
		util::Log(WarnLuaScript);
		return nullptr;
	}

	void Load()
	{
		HookManager::install(app::MiHoYo__SDK__SDKUtil_RSAEncrypt, MiHoYo__SDK__SDKUtil_RSAEncrypt);
		HookManager::install(app::MoleMole__MoleMoleSecurity_GetPublicRSAKey, MoleMole__MoleMoleSecurity_GetPublicRSAKey);
		HookManager::install(app::MoleMole__MoleMoleSecurity_GetPrivateRSAKey, MoleMole__MoleMoleSecurity_GetPrivateRSAKey);
		HookManager::install(app::MoleMole__RSAUtil_RSAEncrypt, MoleMole__RSAUtil_RSAEncrypt);
		HookManager::install(app::MoleMole__RSAUtil_RSADecrypt, MoleMole__RSAUtil_RSADecrypt);
		HookManager::install(app::MoleMole__RSAUtil_RSAVerifyHash, MoleMole__RSAUtil_RSAVerifyHash);
		HookManager::install(app::MoleMole__RSAUtil_RSAVerifyData, MoleMole__RSAUtil_RSAVerifyData);
		if (config::GetConfigChannel() != nullptr || config::GetConfigBaseUrl() != nullptr)
		{
			HookManager::install(app::UnityEngine__JsonUtility_FromJson, UnityEngine__JsonUtility_FromJson);
			HookManager::install(app::MoleMole__ConfigUtil_LoadJSONStrConfig, MoleMole__ConfigUtil_LoadJSONStrConfig);
		}
		if (config::GetConfigChannel() != nullptr)
		{
			HookManager::install(app::MoleMole__Miscs_GetConfigChannel, app::MoleMole__Miscs_LoadChannelConfigBlk);
		}
		if (config::GetEnableValue("DropRCEPacket", false))
		{
			HookManager::install(app::MoleMole__FightModule_OnWindSeedClientNotify, MoleMole__FightModule_OnWindSeedClientNotify);
			HookManager::install(app::MoleMole__PlayerModule_OnWindSeedClientNotify, MoleMole__PlayerModule_OnWindSeedClientNotify);
			HookManager::install(app::MoleMole__PlayerModule_OnReciveLuaShell, MoleMole__PlayerModule_OnReciveLuaShell);
		}
		auto start = config::GetLongValue("TypeIndexStart", -1);
		if (start > -1 && il2cpp__vm__MetadataCache__GetTypeInfoFromTypeDefinitionIndex != 0 &&
			il2cpp__vm__Type__GetName != 0 && il2cpp__vm__Class__GetMethods != 0 && il2cpp__vm__Method__GetNameWithGenericTypes != 0)
		{
			util::DumpAddress(start, config::GetMagicA(), config::GetMagicB());
		}
	}
}
