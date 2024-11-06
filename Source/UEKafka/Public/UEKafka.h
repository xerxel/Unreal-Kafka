// Copyright (c) 2024 ElDockerr

#pragma once

#include "Modules/ModuleManager.h"
#include "KafkaConsumer.h"
#include "KafkaProducer.h"
#include "KafkaAdmin.h"

class UEKAFKA_API FUEKafkaModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	* Get Kafka Consumer singleton.
	*
	* @return TSharedPtr<FKafkaConsumerModule> singleton
	*/
	FORCEINLINE TSharedPtr<FKafkaConsumerModule> GetConsumer() const{
		return KafkaConsumer;
	}

	/**
	* Get Kafka Producer singleton.
	*
	* @return TSharedPtr<FKafkaProducerModule> singleton
	*/
	FORCEINLINE TSharedPtr<FKafkaProducerModule> GetProducer() const{
		return KafkaProducer;
	}

	/**
	* Get Kafka Admin singleton.
	*
	* @return TSharedPtr<FKafkaAdminModule> singleton
	*/
	FORCEINLINE TSharedPtr<FKafkaAdminModule> GetAdmin() const {
		return KafkaAdmin;
	}

	/**
	* Get Easy kafka singleton.
	*
	* @return FUEKafkaModule ref.
	*/
	static FUEKafkaModule& Get();
private:
	TSharedPtr<FKafkaConsumerModule> KafkaConsumer = nullptr;
	TSharedPtr<FKafkaProducerModule> KafkaProducer = nullptr;
	TSharedPtr<FKafkaAdminModule> KafkaAdmin = nullptr;
	static FUEKafkaModule* UEKafka;
};
