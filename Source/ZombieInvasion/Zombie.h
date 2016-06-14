// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Zombie.generated.h"

UCLASS()
class ZOMBIEINVASION_API AZombie : public ACharacter
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

public:
	// Sets default values for this character's properties
	AZombie();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/* Character's behavior tree*/
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;
	
	/* Component used for the "seeing" sense of the AI*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UPawnSensingComponent* PawnSensingComponent;
	
	/* Trigger box, if within here zombie will attack and damage */
	UPROPERTY(EditAnywhere, Category = "Attack")
	UBoxComponent* TB_Attack;

	UPROPERTY()
	AZombieInvasionCharacter* Player;

	/*-------------------------- Attacking functions and Variables ------------------------------*/
	// This timer is used in the Attack function
	UPROPERTY()
	FTimerHandle AttackTimer;

	UFUNCTION()
	void TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void BP_Attack(class AZombieInvasionCharacter* PlayerToAttack, AZombie* Zombie);

	UFUNCTION()
	void Attack();

	UPROPERTY(EditAnywhere, Category = "Attack")
	bool bIsAttacking;

	/*------------------- Health and life functions ----------------------------*/
	UPROPERTY(EditAnywhere, Category = "Health")
	float Health = 100;

	// Taking damage from player
	void Damage(float Damage, FVector HitLocation, AZombieInvasionCharacter* Attacker);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SpawnBlood(AZombie* Zombie, FVector HitLocation);

	/* ------------------Death functions and variables -------------------------*/

	void Die();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Die(AZombie* Zombie);

	// Used to prevent animation from glitching and playing twice if shot during death animation
	bool bIsDying = false;
	/*--------------------------------------------------------------------------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	FVector Impulse;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackDamage = 10;

private:
	
	// Set to true if attacked by player
	bool bIsAggro = false;
};
