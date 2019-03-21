// Fill out your copyright notice in the Description page of Project Settings.

#include "CountDown.h"

#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
//#include "CountDown.generated.h"
#include "TimerManager.h"



// Sets default values
ACountDown::ACountDown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.f);
	RootComponent = CountdownText;
	CountdownTime = 3;
}

// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountDown::AdvanceTimer, 1.f, true);
}

// Called every frame
void ACountDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountDown::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ACountDown::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

//void ACountDown::CountdownHasFinished()
void ACountDown::CountdownHasFinished_Implementation()
{
	CountdownText->SetText(TEXT("GO!"));
}

