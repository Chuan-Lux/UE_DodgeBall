// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/PlayerWidget.h"
#include "Components/ProgressBar.h"

void UPlayerWidget::UpdateHealth(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}
