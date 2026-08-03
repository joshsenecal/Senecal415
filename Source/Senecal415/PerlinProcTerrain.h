// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PerlinProcTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class SENECAL415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	UFUNCTION(CallInEditor, Category = "Terrain")
		void GenerateMap();

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int XSize = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int YSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
		float ZMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float NoiseScale = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float Scale = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float UVScale = 0;

	UPROPERTY(EditAnywhere)
		float radius = 100.0f;

	UPROPERTY(EditAnywhere)
		FVector Depth = FVector(0.f, 0.f, 50.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Mat = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void AlterMesh(FVector impactPoint);

private:
	UProceduralMeshComponent* ProcMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;
	TArray<FProcMeshTangent> Tangents;

	int sectionID = 0;

	void ClearMeshData();
	void CreateVertices();
	void CreateTriangles();

};
