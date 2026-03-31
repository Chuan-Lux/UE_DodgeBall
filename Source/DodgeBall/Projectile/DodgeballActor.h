// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "DodgeballActor.generated.h"

UCLASS()
class DODGEBALL_API ADodgeballActor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADodgeballActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 25.f;

	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* HitParticle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dodgeball", meta = (AllowPrivateAccess="true"))
	class USphereComponent* sphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dodgeball", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalVec, const FHitResult& Hit);
};
