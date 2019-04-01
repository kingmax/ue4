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

	/** �Ƴ���ǰ�˵��ؼ�����������ܣ���ָ�����д����¿ؼ��� */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	/** ����Ϸ��ʼʱ���ǽ���Ϊ�˵�ʹ�õĿؼ��ࡣ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** ����Ϊ�˵��Ŀؼ�ʵ���� */
	UPROPERTY()
		UUserWidget* CurrentWidget;
	
	
};
