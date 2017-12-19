// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FPSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPSHOOTER_API AFPSGameMode : public AGameMode
{
	GENERATED_BODY()
		float MINIMUM_INTERVAL = 0.5f;
	float MAXIMUM_INTERVAL = 2.0f;
	float TIME_TO_MINIMUM_INTERVAL = 30.0f;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void IncrementScore();
	void OnRestart();
	void OnGameOver();

	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<class AEnemyController> EnemyBluerint;
	
	float EnemyTimer;
	float GameTimer;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuItem(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	int score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;

	
	
};
