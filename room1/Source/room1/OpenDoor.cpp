// Copyright BitPatterns Cybersys 2021.

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	

	
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ActorThatOpens= GetWorld()->GetFirstPlayerController()->GetPawn();
	
	
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//Pool the trigger Volume

	//PressurePlate->GetFName();

	//ActorThatOpens->GetName();

	if (ActorThatOpens) {

		if (PressurePlate) {
			if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
				OpenDoor();
			}
		}
		if (PressurePlate2) {
			if (PressurePlate2->IsOverlappingActor(ActorThatOpens)) {
				OpenDoor();
			}
		}


	}

	

	
}



void UOpenDoor::OpenDoor()
{
	AActor * Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, -75.0f, 0.0f);
	FRotator NewRotation3 = FRotator(0.0f, 0.0f, 0.0f);

	//ETeleportType tel = ETeleportType::None;

	//Owner->SetActorRotation(NewRotation, ETeleportType::None);
	Owner->SetActorRotation(NewRotation);

	if (Owner->GetName() == "SM_Door3") {
		Owner->SetActorRotation(NewRotation3);
	}


}