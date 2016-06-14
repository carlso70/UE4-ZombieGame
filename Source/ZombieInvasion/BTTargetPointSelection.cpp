// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieInvasion.h"
#include "BTTargetPointSelection.h"
#include "ZombieTargetPoint.h"
#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AZombieAIController* AICon = Cast<AZombieAIController>(OwnerComp.GetAIOwner());

	/* if the controller is valid
	1) Get the blackboard component and the current point of the bot
	2) Search for the next point which will be different from the current point
	*/
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		AZombieTargetPoint* CurrentPoint = Cast<AZombieTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoints();

		int32 RandomIndex;

		// Next target point
		AZombieTargetPoint* NextTargetPoint = nullptr;
		
		// find the next possible target point
		do
		{
			RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
			// Cast AActor object to Zombie target points
			NextTargetPoint = Cast<AZombieTargetPoint>(AvailableTargetPoints[RandomIndex]);
		} while (CurrentPoint == NextTargetPoint);
		
		// Update the next locaiton in the blackboard so the bot can move to the next blackboard value
		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
	
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}


