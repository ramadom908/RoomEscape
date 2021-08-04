// Copyright BitPatterns Cybersys 2021.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"



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

	void OpenDoor();

	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate; //=nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate2; //= nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens=nullptr;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;

	float LastDoorOpenTime;

	AActor* Owner; 

	FRotator StartRotation;
		
};
