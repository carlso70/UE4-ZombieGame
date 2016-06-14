// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieInvasion.h"
#include "Zombie.h"
#include "ZombieAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "ZombieInvasionCharacter.h"

// Sets default values
AZombie::AZombie()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Trigger box
	TB_Attack = CreateDefaultSubobject<UBoxComponent>(TEXT("TB_Attack"));
	TB_Attack->bGenerateOverlapEvents = true;
	TB_Attack->OnComponentBeginOverlap.AddDynamic(this, &AZombie::TriggerEnter);
	TB_Attack->OnComponentEndOverlap.AddDynamic(this, &AZombie::TriggerExit);
	TB_Attack->AttachParent = RootComponent;

	bIsAttacking = false;

	//Initialize the pawn sensing component
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComponent->SetPeripheralVisionAngle(90.f);

}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(0);

	//Register function that is going to be called when the character sees a pawn
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AZombie::OnSeePlayer);
	}
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AZombie::OnSeePlayer(APawn* Pawn)
{
	AZombieAIController* AIController = Cast<AZombieAIController>(GetController());

	//Set the seen target on the blackboard
	if (AIController)
	{
		AIController->SetSeenTarget(Pawn);
		if (Player == nullptr)
		{
			AZombieInvasionCharacter* MyChar = Cast<AZombieInvasionCharacter>(Pawn);
			if (MyChar) Player = MyChar;
		}
		if (bIsAggro)
		{
			AIController->SetAggro(bIsAggro, Pawn);
		}
	}
}

void AZombie::TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsAttacking = true;
	Player = Cast<AZombieInvasionCharacter>(OtherActor);
	if (Player)
	{
		AttackTimer = FTimerHandle::FTimerHandle();
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AZombie::Attack, 1.f, true, -1.f);
	}
}

void AZombie::Attack()
{
	if (bIsAttacking && !bIsDying)
	{
		BP_Attack(Player, this);
	}
}


void AZombie::TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsAttacking = false;
}

void AZombie::Damage(float Damage, FVector HitLocation, AZombieInvasionCharacter* Attacker)
{
	// Aggro's AI to the attacker
	bIsAggro = true;
	OnSeePlayer(Attacker);

	if (!bIsDying)
	{
		Health -= Damage;
		BP_SpawnBlood(this, HitLocation);
		if (Health <= 0)
		{
			bIsDying = true;
			Die();
		}
	}
}

void AZombie::Die()
{
	/* do C++ shit before blueprint animation*/
	AZombieAIController* AIController = Cast<AZombieAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{
		FString Reason = "Death";
		AIController->BehaviorComp->StopTree();
	}
	Player->NumberOfEnemies--;
	/* blueprint function to handle animation */
	BP_Die(this);

}