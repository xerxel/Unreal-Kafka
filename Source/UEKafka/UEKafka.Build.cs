// Copyright (c) 2024 ElDockerr

using System;
using System.IO;
using UnrealBuildTool;

public class UEKafka : ModuleRules
{
	public UEKafka(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;

		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(PluginDirectory,"Source/KafkaConsumer/Public"),
                Path.Combine(PluginDirectory,"Source/KafkaProducer/Public")
            }
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine",
				"KafkaLib",
				"KafkaConsumer",
				"KafkaProducer",
				"KafkaAdmin"
			}
			);
		bEnableExceptions = true;

		// RTTI will be only available on Windows
		if(Target.Platform != UnrealTargetPlatform.Win64)
			bUseRTTI = true;
    }
}
