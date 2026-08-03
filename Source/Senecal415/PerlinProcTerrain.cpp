// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
	RootComponent = ProcMesh;
	ProcMesh->bUseAsyncCooking = true;

}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();
	GenerateMap();
}

void APerlinProcTerrain::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GenerateMap();
}

void APerlinProcTerrain::GenerateMap()
{
	ClearMeshData();
	CreateVertices();
	CreateTriangles();

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);

	if (Mat)
	{
		ProcMesh->SetMaterial(0, Mat);
	}
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProcTerrain::AlterMesh(FVector impactPoint)
{

	bool bChanged = false;
	for (int i = 0; i < Vertices.Num(); i++) {
		FVector tempVector = impactPoint - this->GetActorLocation();
		float dist = FVector(Vertices[i] - tempVector).Size();
		if (dist < radius) {
			Vertices[i] = Vertices[i] - Depth;
			bChanged = true;
		}
	}

	if (bChanged)
	{
		ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, Tangents);
	}
}



void APerlinProcTerrain::ClearMeshData()
{
	Vertices.Empty();
	Triangles.Empty();
	UV0.Empty();
	Normals.Empty();
	Tangents.Empty();
}

void APerlinProcTerrain::CreateVertices()
{
	for (int X = 0; X <= XSize; X++) {
		for (int Y = 0; Y <= YSize; Y++) {
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
	int Vertex = 0;

	for (int X = 0; X < XSize; X++) {
		for (int Y = 0; Y < YSize; Y++) {
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);
			
			Vertex++;
		}

		Vertex++;
	}
}

