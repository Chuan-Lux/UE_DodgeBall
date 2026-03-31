// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInputPlayerController.h"
#include "UMG/RestartWidget.h"
#include <EnhancedInputSubsystems.h>

void AMyInputPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//输入子系统注册
	
		UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubSystems = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (EnhancedInputSubSystems != nullptr)
		{
			//注册输入子系统
			EnhancedInputSubSystems->AddMappingContext(IC_Input, 1);
		}
	
}

void AMyInputPlayerController::ShowRestartWidget()
{
	if (BP_RestartWidget!=nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
		RestartWidget->AddToViewport();
	}
}

void AMyInputPlayerController::HidenRestartWidget()
{
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}


