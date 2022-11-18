#include "pch.h"
#include "il2cpp-init.h"
#include "dllmain-init.h"
#include "hook.h"
#include "util.h"

VOID InitDllMain(HMODULE *hModule)
{
	util::LoadConfig();
	util::DisableLogReport();
	std::cout << "[init] LogReport disabled." << std::endl;
	while (GetModuleHandle("UserAssembly.dll") == nullptr)
	{
		std::cout << "[init] UserAssembly.dll isn't initialized, waiting for 2 sec." << std::endl;
		Sleep(2000);
	}
	std::cout << "[init] Waiting 15 sec for game initialize." << std::endl;
	Sleep(15000);
	util::DisableVMProtect();
	std::cout << "[init] VMProtect disabled." << std::endl;
	InitIl2Cpp();
	std::cout << "[init] Il2Cpp initialized." << std::endl;
	hook::Install();
	std::cout << "[init] Hook initialized." << std::endl;
	// save config will mess up the comments in config file
	// util::SaveConfig();
}
