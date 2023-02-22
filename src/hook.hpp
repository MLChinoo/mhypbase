#pragma once

#include "pch.h"
#include "hook-manager.h"
#include "il2cpp-appdata.h"

#include "config.hpp"
#include "util.hpp"

namespace hook
{
	const char* WarnLuaScript = "[warn] Server is trying to execute a Lua script remotely, which is potentially dangerous if not from a trusted source.";

	LPVOID MiHoYo__SDK__SDKUtil_RSAEncrypt(LPVOID publicKey, LPVOID content)
	{
		const char* key = config::GetRSAEncryptKey();
		if (key != nullptr)
		{
			util::Log("[hook] Reached MiHoYo__SDK__SDKUtil_RSAEncrypt, and using the configured value.");
			publicKey = il2cpp_string_new(key);
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
		if (text != "") {
			json = il2cpp_string_new(text.c_str());
		}
		return CALL_ORIGIN(UnityEngine__JsonUtility_FromJson, json, type, method);
	}

	LPVOID MoleMole__ConfigUtil_LoadJSONStrConfig(LPVOID jsonText, LPVOID useJsonUtility, LPVOID method)
	{
		auto text = TryPatchConfig(util::ConvertToString(jsonText));
		if (text != "") {
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
	}
}
