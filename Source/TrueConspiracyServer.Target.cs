// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TrueConspiracyServerTarget : TargetRules
{
    public TrueConspiracyServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
        ExtraModuleNames.Add("TrueConspiracy");

        bUseLoggingInShipping = true;
        bUsesSlate = false;
    }
}