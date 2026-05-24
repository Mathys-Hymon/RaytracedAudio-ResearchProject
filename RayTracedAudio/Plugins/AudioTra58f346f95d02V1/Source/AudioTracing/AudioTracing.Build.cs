// Copyright (c) 2025 Pinpoint. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class AudioTracing : ModuleRules
{
    public AudioTracing(ReadOnlyTargetRules Target) : base(Target)
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
                "DeveloperSettings",
                "AudioMixer",
                "SignalProcessing",
                "MetasoundEngine"
            }
            );
            
        
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "Projects",
                "RHI",
                "Renderer",
                "RenderCore",
                "Synthesis",
                "AudioExtensions",
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
