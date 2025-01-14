#pragma once
#include "Renderer.h"

class UWidget : public URenderer
{
public:
	// constrcuter destructer
	UWidget();
	~UWidget();

	// delete Function
	UWidget(const UWidget& _Other) = delete;
	UWidget(UWidget&& _Other) noexcept = delete;
	UWidget& operator=(const UWidget& _Other) = delete;
	UWidget& operator=(UWidget&& _Other) noexcept = delete;

	void AddRelativeLocation(const FVector& _Value)
	{
		Transform.Location += _Value;
		TransformUpdate();
	}

	void SetWorldLocation(const FVector& _Value)
	{
		IsAbsolute = true;
		Transform.Location = _Value;
		TransformUpdate();
	}

	void AddWorldLocation(const FVector& _Value)
	{
		IsAbsolute = true;
		Transform.Location += _Value;
		TransformUpdate();
	}

	void SetRelativeLocation(const FVector& _Value)
	{
		Transform.Location = _Value;
		TransformUpdate();
	}


	void AddWorldRotation(const FVector& _Value)
	{
		IsAbsolute = true;
		Transform.Rotation += _Value;
		TransformUpdate();
	}

	void AddLocalRotation(const FVector& _Value)
	{
		Transform.Rotation += _Value;
		TransformUpdate();
	}

	void SetRotation(const FVector& _Value)
	{
		Transform.Rotation = _Value;
		TransformUpdate();
	}

	void SetScale3D(const FVector& _Value)
	{
		IsAbsolute = true;
		Transform.Scale = _Value;
		TransformUpdate();
	}

	void SetRelativeScale3D(const FVector& _Value)
	{
		Transform.Scale = _Value;
		Transform.Scale.W = 0.0f;
		TransformUpdate();
	}

	FVector GetWorldScale3D()
	{
		return Transform.WorldScale;
	}


	FTransform& GetTransformRef()
	{
		return Transform;
	}

	ENGINEAPI void TransformUpdate();

protected:
	bool IsAbsolute = false;
	FTransform Transform;

private:
	UWidget* Parent = nullptr;
	std::list<std::shared_ptr<UWidget>> Childs;
};

