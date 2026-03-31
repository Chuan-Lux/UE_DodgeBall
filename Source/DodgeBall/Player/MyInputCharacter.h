// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HealthInterface.h"
#include "ActorComponent/HealthComponent.h"
#include "MyInputCharacter.generated.h"

class UspringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class DODGEBALL_API AMyInputCharacter : public ACharacter,public IHealthInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

public:
	AMyInputCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//HealthInterface接口函数
	virtual void OnDeath_Implementation() override;

	float HealthUpdate();

	UPROPERTY(EditAnywhere, Category = "Health")
	float Health=100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UPlayerWidget> BP_PlayerWidget;

	//在player controller里面注册
	//UPROPERTY(EditAnywhere, Category = "Input")
	//class UInputMappingContext* IC_Input;
	////ToObjectPtr<UInputMappingContext>IC_Input;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Move; 

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Dodge;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Dash;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Look;

private:
	//CamaraBoom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* CameraBoom;
	//FollowCamera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY()
	class UPlayerWidget* PlayerWidget;

	//UPROPERTY(EditAnywhere,Category = "Health")
	class UHealthComponent* HealthComponent;
};
