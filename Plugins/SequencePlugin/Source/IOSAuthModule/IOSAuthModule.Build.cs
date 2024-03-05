// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class IosAuthModule : ModuleRules
{

	public IosAuthModule(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libsecp256k1.2.0.2.dylib"));
			
			//PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libsecp256k1.2.0.2.dylib"));
			//RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/secp256k1Library/Mac/Release/libsecp256k1.2.0.2.dylib");
		}
	}
    /*public secp256k1Library(ReadOnlyTargetRules Target) : base(Target)
    {
       Type = ModuleType.External;

        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libsecp256k1.2.0.2.dylib"));
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/secp256k1Library/Mac/Release/libsecp256k1.2.0.2.dylib");
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
       {
          string ExampleSoPath = Path.Combine("$(PluginDir)", "Binaries", "ThirdParty", "secp256k1Library", "Linux", "x86_64-unknown-linux-gnu", "libExampleLibrary.so");
          PublicAdditionalLibraries.Add(ExampleSoPath);
          PublicDelayLoadDLLs.Add(ExampleSoPath);
          RuntimeDependencies.Add(ExampleSoPath);
       }
    }*/
}