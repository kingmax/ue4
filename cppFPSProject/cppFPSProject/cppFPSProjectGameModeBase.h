// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "cppFPSProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CPPFPSPROJECT_API AcppFPSProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
	
	
};
