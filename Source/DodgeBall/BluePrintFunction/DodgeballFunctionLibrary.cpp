// Fill out your copyright notice in the Description page of Project Settings.


#include "BluePrintFunction/DodgeballFunctionLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

bool UDodgeballFunctionLibrary::CanSeeActor(const UWorld* world, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoreActors)
{
	if (TargetActor == nullptr)
	{
		return false;
	}
	//忽视检测对象
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(IgnoreActors);

	//储存射线检测结果
	FHitResult Hit;

	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();
	ECollisionChannel channel = ECollisionChannel::ECC_GameTraceChannel2;

	world->LineTraceSingleByChannel(Hit, Start, End, channel, Params);
	//绘制可视化直线
	DrawDebugLine(world, Start, End, FColor::Red);
	return !Hit.bBlockingHit;
}
