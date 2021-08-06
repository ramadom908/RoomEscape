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
	//ActorThatOpens= GetWorld()->GetFirstPlayerController()->GetPawn();

	StartRotation = Owner->K2_GetActorRotation(); // to be used for door close


	if (PressurePlate) {
		UE_LOG(LogTemp, Warning, TEXT("The actor standing on plate1 is %s"), *PressurePlate->GetName());
	}
	
	if (PressurePlate2) {
		UE_LOG(LogTemp, Warning, TEXT("The actor standing on plate2 is %s"), *PressurePlate2->GetName());
	}

}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	OpenAndCloseDoorByPressurePlate();

}

void UOpenDoor::OpenAndCloseDoorByPressurePlate()
{
	float totalMass = 0.0f;
	float totalMass2 = 0.0f;

	if (PressurePlate) {

		totalMass = GetTotalMassOfActorsOnPlate(PressurePlate);
	}

	if (PressurePlate2) {
		totalMass2 = GetTotalMassOfActorsOnPlate(PressurePlate2);
	}

	if (totalMass > TriggerMass || totalMass2 > TriggerMass) {
		OnOpenRequest97.Broadcast();
	}
	else {
		OnCloseRequest97.Broadcast();
	}
}


float UOpenDoor::GetTotalMassOfActorsOnPlate(ATriggerVolume * PressurePlatePar) {

	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	if (!PressurePlatePar) { return TotalMass;  }
	PressurePlatePar->GetOverlappingActors(OverlappingActors);

	/*for (const auto& actor : OverlappingActors) {

		TotalMass = TotalMass + actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("The actor standing on plate is %s"), *actor->GetName());
	}*/

	for (auto it = OverlappingActors.CreateConstIterator(); it; ++it) {


		TotalMass = TotalMass + (*it)->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}


	//Find all overlapping actors

	//iterate throug them and add their mass


	return TotalMass;
}


//void UOpenDoor::OpenDoor()
//{
//	
//	//FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
//	//FRotator NewRotation3 = FRotator(0.0f, OpenAngle, 0.0f);
//
//	//ETeleportType tel = ETeleportType::None;
//
//	//Owner->SetActorRotation(NewRotation, ETeleportType::None);
//	
//	OnOpenRequest97.Broadcast();
//
//	/*if (Owner) {
//		Owner->SetActorRotation(NewRotation);
//
//		if (Owner->GetName() == "SM_Door3") {
//			Owner->SetActorRotation(NewRotation3);
//		}
//	}*/
//}

//void UOpenDoor::CloseDoor()
//{
//	
//	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
//	FRotator NewRotation3 = FRotator(0.0f, -94.0f, 0.0f);
//
//	FRotator NewRotation4 = StartRotation;
//	//ETeleportType tel = ETeleportType::None;
//
//	//Owner->SetActorRotation(NewRotation, ETeleportType::None);
//	Owner->SetActorRotation(StartRotation);
//
//
//	if (Owner->GetName() == "SM_Door3") {
//		Owner->SetActorRotation(StartRotation);
//	}
//
//}