// Copyright BitPatterns Cybersys 2021.

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty9988!!!!!!"));

	
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//Get player viewpoint 
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty9988!!!!!!"));

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("The %s position is %s"), *ObjectName, *ObjectPosition);

	UE_LOG(LogTemp, Warning, TEXT("Position is:  %s,  Rotation is: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	//Draw a red trace in the world to visualise
	//FVector LineTraceEnd = VectLocation + FVector(0.f, 0.f, 60.f);

	FColor color = { 255, 0, 0, 0 }; // red


	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, color,false, -1.0f, 0, 5.f);


	//<<<<<<<<<<<<<<<<<De aici este codul ca sa desenez linii facute din mai multe puncte>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//TArray ding99{ LineTraceEnd };

	//TArray<FVector> IntArray{ LineTraceEnd, FVector(0.f, 0.f, 60.f), FVector(0.f, 78.f, 60.f) };

	//TArray<FBatchedLine> lines;

	//FVector start = LineTraceEnd;

	//FVector end = FVector(0.f, 0.f, 60.f);
	//
	//FBatchedLine line = FBatchedLine(start,
	//	end,
	//	FLinearColor(255, 1, 1, 0),
	//	1, // for long period draw
	//	3.3,
	//	4
	//);

	//lines.Add(line);
	//FBatchedLine line2 = FBatchedLine(end,
	//	FVector(0.f, 78.f, 60.f),
	//	color,
	//	1, // for long period draw
	//	1.3f,
	//	1
	//);
	////FBatchedLine line2 = FBatchedLine()

	//lines.Add(line2);
	//FVector anotherP{ 90.f, 78.f, 60.f };

	//	FBatchedLine line3 = FBatchedLine(FVector(0.f, 78.f, 60.f),
	//		anotherP,
	//		color,
	//		1, // for long period draw
	//		1.3f,
	//		1
	//	);
	//lines.Add(line3);

	//GetWorld()->LineBatcher->DrawLines(lines);

	//<<<<<<<<<<<<<<<<<<<<< END drawing lines >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


	//Ray -cast (line trace)  out to reach distance 
	

	//FCollisionObjectQueryParams ()

	//set up query parameters
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	//AActor* actor = Hit.GetActor(); // ->GetName();

	if (Hit.GetActor()) {
		FString actorName = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("I am hitting : %s"), *actorName);
	}

	/*AActor * actor = Hit.GetActor();

	if (actor) {

		UE_LOG(LogTemp, Warning, TEXT("I am hitting : %s"), *actor->GetName());
	}*/


	

	
	

	// see what we hit

	

	/*FVector LineTraceEnd= PlayerViewPointLocation*/

}

