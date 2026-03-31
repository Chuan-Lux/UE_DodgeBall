// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyInputPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class DODGEBALL_API AMyInputPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_RestartWidget;

	void ShowRestartWidget();
	void HidenRestartWidget();
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IC_Input;

	UPROPERTY()
	class URestartWidget* RestartWidget;
};
