// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/RestartWidget.h"
#include "MyInputPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void URestartWidget::OnRestartClicked()
{
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
	AMyInputPlayerController* PlayerController = Cast<AMyInputPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HidenRestartWidget();
	}
}

void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (RestartButton!=nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
	}
}
