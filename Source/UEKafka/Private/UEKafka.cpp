// Copyright (c) 2024 ElDockerr

#include "UEKafka.h"
#include "KafkaConsumer.h"
#include "KafkaProducer.h"
#include "KafkaAdmin.h"


#define LOCTEXT_NAMESPACE "FUEKafkaModule"

FUEKafkaModule* FUEyKafkaModule::UEKafka = nullptr;

void FUEKafkaModule::StartupModule()
{
	if (!UEKafka)
		UEKafka = this;
	else
		return;
	if (!KafkaConsumer) {
		FModuleManager::LoadModuleChecked<FKafkaConsumerModule>("KafkaConsumer");
		KafkaConsumer = MakeShared<FKafkaConsumerModule>(FKafkaConsumerModule::Get());
	}
	if (!KafkaProducer) {
		FModuleManager::LoadModuleChecked<FKafkaProducerModule>("KafkaProducer");
		KafkaProducer = MakeShared <FKafkaProducerModule>(FKafkaProducerModule::Get());
	}
	if (!KafkaAdmin) {
		FModuleManager::LoadModuleChecked<FKafkaAdminModule>("KafkaAdmin");
		KafkaAdmin = MakeShared <FKafkaAdminModule>(FKafkaAdminModule::Get());
	}
}

void FUEKafkaModule::ShutdownModule()
{
		
}


FUEKafkaModule& FUEKafkaModule::Get()
{
	if (UEKafka == nullptr)
	{
		check(IsInGameThread());
		FModuleManager::LoadModuleChecked<FKafkaProducerModule>("FUEKafkaModule");
	}
	check(UEKafka);

	return *UEKafka;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUEKafkaModule, UEKafka)