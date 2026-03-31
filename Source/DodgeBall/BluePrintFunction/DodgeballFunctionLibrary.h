// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DodgeballFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API UDodgeballFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//是否能观测到玩家
	static bool CanSeeActor(const UWorld*world,FVector Location,const AActor*TargetActor,TArray<const AActor*>IgnoreActors=TArray<const AActor*>());
};
