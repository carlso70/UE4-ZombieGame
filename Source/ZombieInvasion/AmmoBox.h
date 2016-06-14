// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class ZOMBIEINVASION_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Ammo the box contains
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 Ammo = 10;

	// Pickup the ammo and puts it in the player's inventory
	UFUNCTION()
	void Pickup();

private: 

	UPROPERTY(EditAnywhere, Category = "Text")
	UTextRenderComponent* MyText;

	void MakeTextFacePlayer();

	class AZombieInvasionCharacter* MyPlayer;
	
	void GetPlayer(AActor* Player);

	bool bIsWithinRange;

	// Trigger box for the ammo
	UPROPERTY(EditAnywhere, Category = "TriggerBox")
	UBoxComponent* TB_Ammo;

	// Static mesh for the ammo
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* SM_Ammo;

	UFUNCTION()
	void TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
