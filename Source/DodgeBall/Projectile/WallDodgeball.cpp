// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/WallDodgeball.h"

// Sets default values
AWallDodgeball::AWallDodgeball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;
}

// Called when the game starts or when spawned
void AWallDodgeball::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallDodgeball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

