// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActorComponent/LookAtActorComponent.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DODGEBALL_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle ThrowTimerhandle;
	float ThrowTimerCD=2.f;
	float ThrowDelay=0.5f;
	void ThrowDodgeball();

public:	
	// Sets default values for this character's properties
	AEnemyCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	bool bCansee=false;
	bool BPreviousCansee=false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sight", meta = (AllowPrivateAccess="true"))
	ULookAtActorComponent* LookatActorComponent;
	////朝向目标物体
	//bool LookAtActor(AActor*TargetActor);

	////是否能看到玩家
	//bool CanSeeActor(const AActor* TargetActor) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodgeball")
	TSubclassOf<class ADodgeballActor>Dodgeclass;
};
