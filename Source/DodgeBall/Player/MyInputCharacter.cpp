// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MyInputCharacter.h"
#include "ActorComponent/HealthComponent.h"
#include "MyInputPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFrameWork/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "UMG/PlayerWidget.h"
#include  "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include  <EnhancedInputSubsystems.h>

// Sets default values
AMyInputCharacter::AMyInputCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(45.f, 100.f);

	//是否根据controller旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
    //角色朝向是否对其移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	//设置相机杠
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	//相机杠是否跟随玩家
	CameraBoom->bUsePawnControlRotation = true;

	//设置相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	//相机本身不随鼠标移动
	FollowCamera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AMyInputCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->SetHealth(Health);
	if (BP_PlayerWidget!=nullptr)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(Cast<AMyInputPlayerController>(GetController()), BP_PlayerWidget);
		PlayerWidget->AddToViewport();
	}
}

// Called every frame
void AMyInputCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//持续更新角色血量
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->UpdateHealth(HealthUpdate());
	}
}


// Called to bind functionality to input
void AMyInputCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定子系统注册；
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyInputCharacter::Look);
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyInputCharacter::Move);
	EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
}

void AMyInputCharacter::OnDeath_Implementation()
{
	//UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
	AMyInputPlayerController* PlayerController = Cast<AMyInputPlayerController>(GetController());
	if (PlayerController != nullptr) 
	{
		PlayerController->ShowRestartWidget();
	}
}

//更新角色血量
float AMyInputCharacter::HealthUpdate()
{
	float current = HealthComponent->GetHealth()/Health;
	if (current>1)
	{
		return 1;
	}
	if (current<0)
	{
		return 0;
	}
	return current;
}

void AMyInputCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveInput = Value.Get<FVector2D>();
	if (Controller!=nullptr &&(MoveInput.X!=0.f || MoveInput.Y!=0.f))
	{
		//获取摄像机的航班值
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		if (MoveInput.X!=0.f)
		{
			const FVector RightDirection = UKismetMathLibrary::GetRightVector(YawRotation);
			AddMovementInput(RightDirection, MoveInput.X);
		}
		if (MoveInput.Y != 0.f)
		{
			const FVector ForwardDirection = YawRotation.Vector();
			AddMovementInput(ForwardDirection, MoveInput.Y);
		}
	}
}

void AMyInputCharacter::Look(const FInputActionValue& Value) 
{
	FVector2D LookInput = Value.Get<FVector2D>();
	if (LookInput.X!=0)
	{
		AddControllerYawInput(LookInput.X);
	}
	if (LookInput.Y != 0) 
	{
		AddControllerPitchInput(LookInput.Y);
	}
}


