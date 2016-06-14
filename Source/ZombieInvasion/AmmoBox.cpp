// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieInvasion.h"
#include "ZombieInvasionCharacter.h"
#include "AmmoBox.h"


// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TB_Ammo = CreateDefaultSubobject<UBoxComponent>(TEXT("TB_Ammo"));
	TB_Ammo->bGenerateOverlapEvents = true;
	TB_Ammo->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::TriggerEnter);
	TB_Ammo->OnComponentEndOverlap.AddDynamic(this, &AAmmoBox::TriggerExit);
	RootComponent = TB_Ammo;

	SM_Ammo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Ammo"));
	SM_Ammo->AttachTo(RootComponent);

	MyText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RotatingText"));
	MyText->SetWorldSize(70.f);
	MyText->SetTextRenderColor(FColor::Red);
	MyText->SetHorizontalAlignment(EHTA_Center);
	MyText->SetText("Ammo Box");
	MyText->AttachTo(SM_Ammo);

}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoBox::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	MakeTextFacePlayer();

	if (MyPlayer)
	{
		if (MyPlayer->bIsPickingUp && bIsWithinRange)
		{
			Pickup();
		}
	}
}

void AAmmoBox::Pickup()
{
	MyPlayer->PickupAmmo(Ammo);
	Destroy();
}

void AAmmoBox::TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	GetPlayer(OtherActor);
	if (MyPlayer)
	{
		bIsWithinRange = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("bIsWithinRange (in)= %i"), bIsWithinRange));
	}
}


void AAmmoBox::TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetPlayer(OtherActor);
	if (MyPlayer)
	{
		bIsWithinRange = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("bIsWithinRange (out)= %i"), bIsWithinRange));
		MyPlayer = nullptr;
	}
}

void AAmmoBox::GetPlayer(AActor* Player)
{
	AZombieInvasionCharacter* Character = Cast<AZombieInvasionCharacter>(Player);
	if (Character)
	{
		MyPlayer = Character;
	}
}


void AAmmoBox::MakeTextFacePlayer()
{
	AZombieInvasionCharacter* Character = Cast<AZombieInvasionCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	FRotator NewRoation = Character->GetActorRotation();
	//add 180 because by default its Yaw is backwards 
	NewRoation.Yaw += 180.f;

	MyText->SetRelativeRotation(NewRoation);
}