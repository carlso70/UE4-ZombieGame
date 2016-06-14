// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEINVASION_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

	/* Reference to our blackboard component*/
	UBlackboardComponent* BlackboardComp;
	
	/* Blackboard keys */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName Target;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName IsAggro;

	/*--------------- BLACKBOARD ---------------*/
	TArray<AActor*> ZombieTargetPoints;

	/* Possess is called when the character we want to control is spawned */
	virtual void Possess(APawn* Pawn) override;

public:

	AZombieAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() const { return ZombieTargetPoints; }

	/* Sets the sensed target in the blackboard */
	void SetSeenTarget(APawn* Pawn);

	/* Sets the target to the shooter an*/
	void SetAggro(bool Aggro, APawn* Pawn);

	/* Reference to our behavior tree component */
	UBehaviorTreeComponent* BehaviorComp;
};
