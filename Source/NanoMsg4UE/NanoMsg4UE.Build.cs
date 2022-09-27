// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class NanoMsg4UE : ModuleRules
{

	private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
    }

	public NanoMsg4UE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				Path.Combine(ThirdPartyPath, "NanoMsgLibrary/include"),
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		string NanoMsgLibPath = string.Empty;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			NanoMsgLibPath = Path.Combine(ThirdPartyPath, "NanoMsgLibrary/x64/Release/lib/", "nanomsg.lib");
			PublicAdditionalLibraries.Add(NanoMsgLibPath);
			System.Console.WriteLine("-------------- Android NanoMsg Lib path = " + NanoMsgLibPath);

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("nanomsg.dll");

			// Ensure that the DLL is staged along with the executable
			string NanoMsgDllPath = Path.Combine(ThirdPartyPath, "NanoMsgLibrary/x64/Release/bin/", "nanomsg.dll");
			RuntimeDependencies.Add(NanoMsgDllPath);
			System.Console.WriteLine("-------------- Android NanoMsg DLL path = " + NanoMsgDllPath);
        }
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			// PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			string AplPath = Path.Combine(ThirdPartyPath, "NanoMsgLibrary/Android/NanoMsgLibrary_APL.xml");
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", AplPath);
			System.Console.WriteLine("-------------- Android NanoMsg APL path = " + AplPath);

			{
				NanoMsgLibPath = Path.Combine(ThirdPartyPath, "NanoMsgLibrary/Android/libs/", "armeabi-v7a", "libnanomsg.so");
				PublicAdditionalLibraries.Add(NanoMsgLibPath);
				System.Console.WriteLine("-------------- Android NanoMsg Lib path = " + NanoMsgLibPath);
			}
			{
				NanoMsgLibPath = Path.Combine(ThirdPartyPath, "NanoMsgLibrary/Android/libs/", "arm64-v8a", "libnanomsg.so");
				PublicAdditionalLibraries.Add(NanoMsgLibPath);
				System.Console.WriteLine("-------------- Android NanoMsg Lib path = " + NanoMsgLibPath);
			}
		}
	}
}
