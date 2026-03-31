// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile/DodgeballActor.h"
#include "Player/MyInputCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "ActorComponent/HealthComponent.h"


// Sets default values
ADodgeballActor::ADodgeballActor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComponent =CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	sphereComponent->SetSphereRadius(35.f);
	sphereComponent->SetCollisionProfileName(FName("Dodgeball"));
	// 启用物理模拟
	sphereComponent->SetSimulatePhysics(true);
	//确保能够调用OnHit()事件
	sphereComponent->SetNotifyRigidBodyCollision(true);
	//将事件绑定到OnComponentHit 确保能够一起调用
	sphereComponent->OnComponentHit.AddDynamic(this, &ADodgeballActor::OnHit);
	RootComponent = sphereComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = 1500.f;
}

// Called when the game starts or when spawned
void ADodgeballActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(5.f);
}

// Called every frame
void ADodgeballActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADodgeballActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//碰撞到character物体上的时候触发
void ADodgeballActor::OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalVec, const FHitResult& Hit)
{
	AMyInputCharacter* Player = Cast<AMyInputCharacter>(OtherActor);
	if (Player !=nullptr)
	{
		UHealthComponent* health = Player->FindComponentByClass<UHealthComponent>();
		if (health!=nullptr)
		{
			health->LoseHealth(Damage);
		}
		if (HitParticle!=nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,GetActorTransform());
		}
		Destroy();
	}
}

