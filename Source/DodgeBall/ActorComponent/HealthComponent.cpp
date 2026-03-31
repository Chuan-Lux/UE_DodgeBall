// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/HealthInterface.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetHealth(float AtSet)
{
	Health = AtSet;
}

void UHealthComponent::LoseHealth(float damage)
{
	Health -= damage;
	if (Health<=0.f)
	{
		Health = 0.f;
		if (GetOwner()->Implements<UHealthInterface>()) //Implements 检查对象是否实现这个接口
		{
			IHealthInterface::Execute_OnDeath(GetOwner());
		}
	}
}

float UHealthComponent::GetHealth()
{
	return Health;
}

void UHealthComponent::CureHealth(float cure, float MaxHealth)
{
	Health += cure;
	if (Health>=MaxHealth)
	{
		Health = MaxHealth;
	}
}

