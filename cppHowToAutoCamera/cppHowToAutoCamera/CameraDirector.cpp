// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// http://api.unrealengine.com/CHN/Programming/Tutorials/AutoCamera/2/index.html
	// 每隔3秒在两个不同的相机间切换默认玩家的视图
	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTimie = 0.75f;
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if (OurPlayerController->GetViewTarget() != CameraOne && CameraOne != nullptr)
			{
				OurPlayerController->SetViewTarget(CameraOne);
			}
			else if (OurPlayerController->GetViewTarget() != CameraTwo && CameraTwo != nullptr)
			{
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTimie);
			}
		}
	}
}

