// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Engine/Engine.h"

#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"

#include "FPSProjectile.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	// 将摄像机放置在眼睛上方不远处。
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// 用 pawn 控制摄像机旋转。
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 为拥有玩家创建一个第一人称模型组件
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 拥有玩家无法看到普通（第三人称）身体模型。
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// // 显示调试信息五秒。-1“键”值（首个参数）说明我们无需更新或刷新此消息。
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter"));

}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForward(float value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(dir, value);
}

void AFPSCharacter::MoveRight(float value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(dir, value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (ProjectileClass)
	{
		// 获取摄像机变换。
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// 将 MuzzleOffset 从摄像机空间变换到世界空间。
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;

		// 将准星稍微上抬。
		MuzzleRotation.Pitch += 10.0f;

		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// 在枪口处生成发射物。
			AFPSProjectile* Projectile = world->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// 设置发射物的初始轨道。
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

