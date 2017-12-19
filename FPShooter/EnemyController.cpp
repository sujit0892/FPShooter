// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "FPSGameMode.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyController::OnOverlap);
	RootComponent = RootBox;

}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	this->SetLifeSpan(10);
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Direction.X * Speed * DeltaTime;
	NewLocation.Y += Direction.Y * Speed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AEnemyController::OnOverlap(UPrimitiveComponent* OnOverlap, AActor* otherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	if (otherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		((AFPSGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver();
		UGameplayStatics::SetGamePaused(GetWorld(), true);

	}
	else if(otherActor->GetName().Contains("Projectile"))
	{
		this->Destroy();
		otherActor->Destroy();
		((AFPSGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
	}
}