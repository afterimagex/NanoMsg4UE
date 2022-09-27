// Copyright Epic Games, Inc. All Rights Reserved.

#include "NanoMsg4UE.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FNanoMsg4UEModule"

void FNanoMsg4UEModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("NanoMsg4UE")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/NanoMsgLibrary/x64/Release/bin/nanomsg.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/NanoMsgLibrary/Mac/Release/libnanomsg.dylib"));
#elif PLATFORM_LINUX
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/NanoMsgLibrary/Linux/x86_64-unknown-linux-gnu/libnanomsg.so"));
// #elif PLANTFORM_ANDROID
	// LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/NanoMsgLibrary/Android/libs/armeabi-v7a/libnanomsg.so"));
#endif // PLATFORM_WINDOWS

	NanoMsgLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (NanoMsgLibraryHandle)
	{
		UE_LOG(LogTemp, Log, TEXT("NanoMsgLibrary loaded success."));
	}
	// else
	// {
	// 	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load NanoMsgLibrary third party library"));
	// }
}

void FNanoMsg4UEModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (NanoMsgLibraryHandle)
	{
		// Free the dll handle
		FPlatformProcess::FreeDllHandle(NanoMsgLibraryHandle);
		NanoMsgLibraryHandle = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNanoMsg4UEModule, NanoMsg4UE)
