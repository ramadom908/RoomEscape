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
	Owner = GetOwner(); // private var for this instance to be used in this file
	ActorThatOpens= GetWorld()->GetFirstPlayerController()->GetPawn();
	StartRotation = Owner->K2_GetActorRotation(); // to be used for door close
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (ActorThatOpens) {

		if (PressurePlate) {
			if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
				OpenDoor();
				LastDoorOpenTime = GetWorld()->GetTimeSeconds();
			}
		}
		if (PressurePlate2) {
			if (PressurePlate2->IsOverlappingActor(ActorThatOpens)) {
				OpenDoor();
				LastDoorOpenTime = GetWorld()->GetTimeSeconds();
			}
		}
	}

	// check if is time to close door 
	if (LastDoorOpenTime + DoorCloseDelay < GetWorld()->GetTimeSeconds()) {
		CloseDoor();
	}

}



void UOpenDoor::OpenDoor()
{
	
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	FRotator NewRotation3 = FRotator(0.0f, OpenAngle, 0.0f);

	//ETeleportType tel = ETeleportType::None;

	//Owner->SetActorRotation(NewRotation, ETeleportType::None);
	

	if (Owner) {
		Owner->SetActorRotation(NewRotation);

		if (Owner->GetName() == "SM_Door3") {
			Owner->SetActorRotation(NewRotation3);
		}
	}
}

void UOpenDoor::CloseDoor()
{
	
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	FRotator NewRotation3 = FRotator(0.0f, -94.0f, 0.0f);

	FRotator NewRotation4 = StartRotation;
	//ETeleportType tel = ETeleportType::None;

	//Owner->SetActorRotation(NewRotation, ETeleportType::None);
	Owner->SetActorRotation(StartRotation);


	if (Owner->GetName() == "SM_Door3") {
		Owner->SetActorRotation(StartRotation);
	}

}