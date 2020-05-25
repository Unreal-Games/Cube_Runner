// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CRPawn.generated.h"


UCLASS()
class NEWGAME_API ACRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACRPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Setup")
	UStaticMeshComponent* Cube;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Floats")
		float ForwardPush;

	UPROPERTY(EditAnywhere, Category = "Floats")
		float SidePush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG")
		TSubclassOf<UUserWidget>DefaultHUD;

	UUserWidget* HUD;

	//VARS
	class ACRGameMode* GameMode;
	bool bGameEnded;
	float Mass;
	float DeltaSeconds;
	FTimerHandle EndGametimer;

	// UFUNCTIONS
	UFUNCTION()
		void OnHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//FUNCTIONS
	void GameEnded();
	void MoveRight(float AxisValue);
	void Endgame();
};
