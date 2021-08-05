// Copyright BitPatterns Cybersys 2021.

#pragma once

#include "Math/Color.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOM1_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//How far can we reach in cm
	float Reach = 140.f;

	UPhysicsHandleComponent * PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	//Ray cast and grab what is in reach
	void Grab();
	
	void Release();

	void FindPhysicsHandleComponent();

	// Setup assumed input comonent
	void SetUpInputComponent();

	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};


