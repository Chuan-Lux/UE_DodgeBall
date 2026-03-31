// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LookAtActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DODGEBALL_API ULookAtActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULookAtActorComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE const void SetTarget(AActor* NewTarget);
	FORCEINLINE const bool CanseeTarget();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	AActor* TargetActor;
	bool bCanSeeTarget=false;
	bool LookAtActor();
		
};
