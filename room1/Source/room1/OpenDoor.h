// Copyright BitPatterns Cybersys 2021.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOM1_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenAndCloseDoorByPressurePlate();

	UPROPERTY(BlueprintAssignable)
	FOnDoorEvent OnOpenRequest97;

	UPROPERTY(BlueprintAssignable)
	FOnDoorEvent OnCloseRequest97;


private:
	/*UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;*/

	UPROPERTY(EditAnywhere)
	float TriggerMass = 50.f;


	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate=nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate2= nullptr;

	/*UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens=nullptr;*/
	
	/*UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;*/

	float LastDoorOpenTime;

	AActor* Owner=nullptr; 

	FRotator StartRotation;

	float GetTotalMassOfActorsOnPlate(ATriggerVolume * PressurePlatePar);
		
};
