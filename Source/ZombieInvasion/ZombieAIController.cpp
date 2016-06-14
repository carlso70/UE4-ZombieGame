// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieInvasion.h"
#include "ZombieAIController.h"
#include "Zombie.h"
#include "ZombieTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AZombieAIController::AZombieAIController()
{
	// Initialize Components
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	Target = "Target";
	LocationToGoKey = "LocationToGo";
	IsAggro = "IsAggro";
}

void AZombieAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	// Get the possessed Character and check if its my own AI Character
	AZombie* AIChar = Cast<AZombie>(Pawn);

	if (AIChar)
	{
		if (AIChar->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
		}

		/* Populate the array of target points */
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZombieTargetPoint::StaticClass(), ZombieTargetPoints);
	
		/* Start the character's behavior tree*/
		BehaviorComp->StartTree(*AIChar->BehaviorTree);
	}
}

void AZombieAIController::SetSeenTarget(APawn* Pawn)
{
	// Registers the pawn that the AI has seen in the blackboard
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(Target, Pawn);
	}
}

void AZombieAIController::SetAggro(bool Aggro, APawn* Pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsAggro, Aggro);
		BlackboardComp->SetValueAsObject(Target, Pawn);
	}
}