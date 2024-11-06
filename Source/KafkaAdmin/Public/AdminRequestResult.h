// Copyright (c) 2024 ElDockerr
#pragma once
#include "CoreMinimal.h"
#include "AdminRequestResult.generated.h"

USTRUCT(BlueprintType, meta = (ShortToolTip = "Admin client request result"))
struct FAdminRequestResult
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EasyKafka|Admin", meta = (ShortToolTip = "Error message string"))
		FString ErrorMessage;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EasyKafka|Admin", meta = (ShortToolTip = "is there an error?"))
		bool bError;

	FAdminRequestResult()
	{
		ErrorMessage = "";
		bError = false;
	}

	FAdminRequestResult(FString errorMessage, bool Error)
	{
		ErrorMessage = errorMessage;
		bError = Error;
	}
};