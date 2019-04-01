// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "cppHowToUMGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CPPHOWTOUMG_API AcppHowToUMGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	/** 移除当前菜单控件并且如果可能，从指定类中创建新控件。 */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	/** 在游戏开始时我们将作为菜单使用的控件类。 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** 用作为菜单的控件实例。 */
	UPROPERTY()
		UUserWidget* CurrentWidget;
	
	
};
