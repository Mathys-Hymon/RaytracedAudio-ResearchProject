// Copyright (c) 2025 Pinpoint. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class AudioTracingEditor : ModuleRules
{
    public AudioTracingEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PrivateIncludePaths.AddRange(
            new string[] {
            }
            );
                
        
        PrivateIncludePaths.AddRange(
            new string[] {
                ModuleDirectory
            }
            );
            
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Engine",
            }
            );
            
        
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "AssetTools",
                "Projects",
                "Blutility",
                "ToolMenus",
                "AudioTracing",
            }
            );
        
        
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
            );
    }
}
