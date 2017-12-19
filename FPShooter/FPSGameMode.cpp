// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.h"
#include "GameFramework/Character.h"
#include "GameWidget.h"

void AFPSGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuItem(StartingWidgetClass);

	((UGameWidget*)CurrentWidget)->Load();

	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Restart", IE_Pressed, this, &AFPSGameMode::OnRestart).bExecuteWhenPaused = true;
}

void AFPSGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;
	if (EnemyTimer <= 0.0f)
	{
		float difficultyPercentage = FMath::Min(GameTimer / TIME_TO_MINIMUM_INTERVAL, 1.0f);
		EnemyTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL)*difficultyPercentage;

		UWorld* world = GetWorld();
		if (world)
		{
			float distance = 800.0f;
			float randomAngle = FMath::RandRange(0.0f, 360.0f);

			FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
			FVector EnemyLocation = PlayerLocation;
			EnemyLocation.X += FMath::Cos(randomAngle*180.0f / 3.14f)*distance;
			EnemyLocation.Y += FMath::Sin(randomAngle*180.0f / 3.14f)*distance;
			EnemyLocation.Z = 240.0f;
			AEnemyController* enemy = world->SpawnActor<AEnemyController>(EnemyBluerint, EnemyLocation, FRotator::ZeroRotator);
			enemy->Direction = (PlayerLocation - EnemyLocation).GetSafeNormal();
		}
	}
}

void AFPSGameMode::IncrementScore()
{
	score += 100;
	((UGameWidget*)CurrentWidget)->setScore(score);
	
}

void AFPSGameMode::OnRestart()
{
	UGameplayStatics::OpenLevel(this,FName(*GetWorld()->GetName()), false);
}

void AFPSGameMode::OnGameOver()
{
	((UGameWidget*)CurrentWidget)->OnGameOver(score);
}

void AFPSGameMode::ChangeMenuItem(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if(CurrentWidget!=nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
			CurrentWidget->AddToViewport();
	}

}

