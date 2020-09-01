// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class AntacrticSurvivalTarget : TargetRules
{
	public AntacrticSurvivalTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "AntacrticSurvival" } );
	}
}
