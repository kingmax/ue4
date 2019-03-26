// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.f, 250.f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Grow -> Scale 基于"Grow"操作来处理增长和收缩
	{
		float currentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			currentScale += DeltaTime;
		}
		else
		{
			currentScale -= (DeltaTime * 0.5f);
		}
		// 确认永不低于起始大小，或增大之前的两倍大小。
		currentScale = FMath::Clamp(currentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(currentScale));
	}

	// 基于"MoveX"和 "MoveY"坐标轴来处理移动
	if (!CurrentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
		SetActorLocation(newLocation);
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &AMyPawn::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::MoveYAxis);
}

void AMyPawn::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}