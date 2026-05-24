// Copyright (c) 2025 Pinpoint. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class AudioTracingDebug : ModuleRules
{
    public AudioTracingDebug(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(GetModuleDirectory("Renderer"), "Private"),
                Path.Combine(GetModuleDirectory("Renderer"), "Internal"),
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
                "EditorSubsystem",
                "Projects",
                "RHI",
                "Renderer",
                "RenderCore",
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
