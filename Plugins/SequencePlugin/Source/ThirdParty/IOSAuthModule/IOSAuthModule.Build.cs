// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class IOSAuthModule : ModuleRules
{
	public IOSAuthModule(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libAccessibility.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libAccessibility.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libate.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libate.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libAudioStatistics.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libAudioStatistics.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libAWDSupportFramework.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libAWDSupportFramework.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libAWDSupportFramework.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libAWDSupportFramework.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libAXSpeechManager.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libAXSpeechManager.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libboringssl.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libboringssl.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libdispatch.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libdispatch.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libIOAccessoryManager.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libIOAccessoryManager.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libLinearAlgebra.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libLinearAlgebra.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libmecabra.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libmecabra.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libMobileGestaltExtensionsdylib.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libMobileGestaltExtensionsdylib.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libnetwork.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libnetwork.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libnfshared.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libnfshared.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libobjc.A.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libobjc.A.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libprequelite.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libprequelite.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libswiftCore.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libswiftCore.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libswiftDispatch.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libswiftDispatch.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libswiftFoundation.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libswiftFoundation.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libsysdiagnose.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libsysdiagnose.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libsysmon.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libsysmon.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libsystem_blocks.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libsystem_blocks.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libsystem_trace.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libsystem_trace.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libTelephonyUtilDynamic.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libTelephonyUtilDynamic.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libtzupdate.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libtzupdate.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libusrtcp.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libusrtcp.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libwebrtc.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libwebrtc.dylib");
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "IOS", "Release", "._libxpc.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/IOSAuthModule/libs/._libxpc.dylib");
		}
	}
}