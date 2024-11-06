// Copyright (c) 2024 ElDockerr

using System;
using System.IO;
using UnrealBuildTool;

public class KafkaProducer : ModuleRules
{
	public KafkaProducer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;
        PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

        PublicIncludePaths.AddRange(
			new string[] {
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
				"KafkaLib"
			}
			);
		bEnableExceptions = true;
	}
}
