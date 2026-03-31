// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/LookAtActorComponent.h"
#include "BluePrintFunction/DodgeballFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULookAtActorComponent::ULookAtActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool ULookAtActorComponent::LookAtActor()
{
	if (TargetActor == nullptr) return false;
	//if (CanSeeActor(TargetActor))
	const TArray<const AActor*> IgnoreActors = {GetOwner(),TargetActor};
	if (UDodgeballFunctionLibrary::CanSeeActor(GetWorld(),GetComponentLocation(), TargetActor, IgnoreActors))
	{
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(Start, End);
		GetOwner()->SetActorRotation(LookAt);
		return true;
	}
	return false;
}


// Called every frame
void ULookAtActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bCanSeeTarget = LookAtActor();
	// ...
}

//设置Target目标
const void ULookAtActorComponent::SetTarget(AActor* NewTarget)
{
	TargetActor = NewTarget;
}
//输出是否观测到物体
const bool ULookAtActorComponent::CanseeTarget()
{
	return bCanSeeTarget;
}

