// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Projectile//DodgeballActor.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookatActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("LookAtActorComponent"));
	//LookatActorComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookatActorComponent->SetTarget(Player);
    bCansee=LookatActorComponent->CanseeTarget();
	if (bCansee!=BPreviousCansee)
	{
		if (bCansee)
		{
			GetWorldTimerManager().SetTimer(ThrowTimerhandle,
				this,
				&AEnemyCharacter::ThrowDodgeball,
				ThrowTimerCD,
				true,
				ThrowDelay);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerhandle);
		}
	}
    BPreviousCansee=bCansee;
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//移动到组件
//朝向玩家
//bool AEnemyCharacter::LookAtActor(AActor* TargetActor)
//{
//	if (TargetActor == nullptr) return false;
//	//if (CanSeeActor(TargetActor))
//	const TArray<const AActor*> IgnoreActors = { this,TargetActor };
//    if (UDodgeballFunctionLibrary::CanSeeActor(GetWorld(),GetActorLocation(),TargetActor,IgnoreActors))
//	{
//		FVector Start = GetActorLocation();
//		FVector End = TargetActor->GetActorLocation();
//		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(Start, End);
//		SetActorRotation(LookAt);
//		return true;
//	}
//	return false;
//}

//移动到函数库
//检测能否看到玩家
//bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor)const 
//{
//	if (TargetActor == nullptr)
//	{
//		return false;
//	}
//	else
//	{
//		//忽视检测对象
//		FCollisionQueryParams Params;
//		Params.AddIgnoredActor(this);
//		Params.AddIgnoredActor(TargetActor);
//
//
//		//储存射线检测结果
//		FHitResult Hit;
//
//		FVector Start = GetActorLocation();
//		FVector End = TargetActor->GetActorLocation();
//		ECollisionChannel channel = ECollisionChannel::ECC_GameTraceChannel2;
//
//		GetWorld()->LineTraceSingleByChannel(Hit,Start,End,channel,Params);
//		//绘制可视化直线
//		DrawDebugLine(GetWorld(), Start, End,FColor::Red);
//		return !Hit.bBlockingHit;
//	}
//}

void AEnemyCharacter::ThrowDodgeball() 
{
	if (Dodgeclass==nullptr)
	{
		return;
	}
	FVector Forward = GetActorForwardVector();
	float Distance = 40.f;
	FVector Position = GetActorLocation() + (Forward * Distance);
	GetWorld()->SpawnActor<ADodgeballActor>(Dodgeclass, Position,GetActorRotation());
}

