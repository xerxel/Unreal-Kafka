// Copyright (c) 2024 ElDockerr

#include "UESubsystem.h"
#include "KafkaConsumer.h"
#include "KafkaAdmin.h"
#include "../../KafkaProducer/Public/KafkaProducer.h"




void UUEKafkaSubsystem::Deinitialize()
{
	if(UEKafka->GetConsumer())
		UEKafka->GetConsumer()->StopConsuming();
}

void UUEKafkaSubsystem::CreateConsumerDefault(FString Servers, FString UserName, FString Password, EKafkaLogLevel KafkaLogLevel)
{
	if(UEKafka->GetConsumer())
	UEKafka->GetConsumer()->CreateConsumer(Servers, UserName, Password, TMap<FString,FString>(), (int)KafkaLogLevel);
}

void UUEKafkaSubsystem::CreateConsumer(FString Servers, FString UserName, FString Password, TMap<EKafkaConsumerConfig, FString> Configuration, EKafkaLogLevel KafkaLogLevel)
{
	if(UEKafka->GetConsumer())
	UEKafka->GetConsumer()->CreateConsumer(Servers, UserName, Password, Configuration, (int)KafkaLogLevel);
}

void UUEKafkaSubsystem::CreateConsumerStr(FString Servers, FString UserName, FString Password, TMap<FString, FString> Configuration, EKafkaLogLevel KafkaLogLevel)
{
	if(UEKafka->GetConsumer())
	UEKafka->GetConsumer()->CreateConsumer(Servers, UserName, Password, Configuration, (int)KafkaLogLevel);
}

void UUEKafkaSubsystem::Subscribe(TArray<FString> Topics, int Timeout)
{
	if(UEKafka->GetConsumer())
	UEKafka->GetConsumer()->Subscribe(Topics, Timeout);
}

void UUEKafkaSubsystem::Unsubscribe(int Timeout)
{
	if(UEKafka->GetConsumer())
	UEKafka->GetConsumer()->Unsubscribe(Timeout);
}

bool UUEKafkaSubsystem::Commit()
{
	if (UEKafka->GetConsumer())
		return UEKafka->GetConsumer()->Commit();
	else
		return false;
}

void UUEKafkaSubsystem::CommitAsync()
{
	if(UEKafka->GetConsumer())
	UEKafka->GetConsumer()->CommitAsync();
}

int32 UUEKafkaSubsystem::StartConsuming()
{
	if (UEKafka->GetConsumer())
		return UEKafka->GetConsumer()->StartConsuming();
	else 
		return -1;
}

void UUEKafkaSubsystem::StopConsuming()
{
	if (UEKafka->GetConsumer())
	UEKafka->GetConsumer()->StopConsuming();
}

void UUEKafkaSubsystem::PauseConsuming()
{
	if (UEKafka->GetConsumer())
		UEKafka->GetConsumer()->PauseConsuming();
}

void UUEKafkaSubsystem::ResumeConsuming()
{
	if (UEKafka->GetConsumer())
		UEKafka->GetConsumer()->ResumeConsuming();
}

TArray<FString> UUEKafkaSubsystem::GetSubscription()
{
	if (UEKafka->GetConsumer())
		return UEKafka->GetConsumer()->GetSubscription();
	else
		return TArray<FString>();
}

void UUEKafkaSubsystem::SetGroupId(FString groupId)
{
	if (UEKafka->GetConsumer())
		UEKafka->GetConsumer()->SetGroupId(groupId);
}

void UUEKafkaSubsystem::Initialize(FSubsystemCollectionBase& Collection) 
{
	FModuleManager::LoadModuleChecked<FUEKafkaModule>("UEKafka");
	UEKafka = MakeShared<FUEKafkaModule>(FUEKafkaModule::Get());

	UEKafka->GetConsumer()->OnNewMessage().AddUObject(this, &UUEKafkaSubsystem::OnNewMessageCallback);
	UEKafka->GetConsumer()->OnError().AddUObject(this, &UUEKafkaSubsystem::OnConsumingError);
	UEKafka->GetConsumer()->OnCommit().AddUObject(this, &UUEKafkaSubsystem::OnCommitCallback);
	UEKafka->GetConsumer()->OnStop().AddUObject(this, &UUEKafkaSubsystem::OnStopConsuming);
	UEKafka->GetProducer()->OnProduce().AddUObject(this, &UUEKafkaSubsystem::OnNewMessageProduced);
}



void UUEKafkaSubsystem::CreateProducerDefault(FString Servers, FString UserName, FString Password, EKafkaLogLevel KafkaLogLevel)
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->CreateProducer(Servers, UserName, Password, TMap<FString, FString>(), true, (int)KafkaLogLevel);
}

void UUEKafkaSubsystem::CreateProducerStr(FString Servers, FString UserName, FString Password, TMap<FString, FString> Configuration, EKafkaLogLevel KafkaLogLevel)
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->CreateProducer(Servers, UserName, Password,Configuration,true, (int)KafkaLogLevel);
}

void UUEKafkaSubsystem::CreateProducer(FString Servers, FString UserName, FString Password, TMap<EKafkaProducerConfig, FString> Configuration, EKafkaLogLevel KafkaLogLevel)
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->CreateProducer(Servers, UserName, Password, Configuration, true, (int)KafkaLogLevel);
}

void UUEKafkaSubsystem::ProduceRecord(FString Topic, FString Value, int64 Id)
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->ProduceRecord(Topic, Value, Id);
}

void UUEKafkaSubsystem::ProduceRecords(FString Topic, TMap<FString, int64> ValueIdPair)
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->ProduceRecords(Topic, ValueIdPair);
}

void UUEKafkaSubsystem::ProduceRecordStruct(FProducerRecord Record)
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->ProduceRecord(Record);
}

void UUEKafkaSubsystem::ProduceRecordsStruct(TArray<FProducerRecord> Records)
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->ProduceRecords(Records);
}

void UUEKafkaSubsystem::PurgeMessages()
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->Purge();
}

void UUEKafkaSubsystem::CreateAdminDefault(FString Servers, FString UserName, FString Password, EKafkaLogLevel KafkaLogLevel)
{
	if (UEKafka->GetAdmin())
		UEKafka->GetAdmin()->CreateAdmin(Servers, UserName, Password, TMap<FString, FString>(), (int)KafkaLogLevel);
}

void UUEKafkaSubsystem::CreateAdmin(FString Servers, FString UserName, FString Password, TMap<EKafkaAdminConfig, FString> Configuration, EKafkaLogLevel KafkaLogLevel)
{
	if (UEKafka->GetAdmin())
		UEKafka->GetAdmin()->CreateAdmin(Servers, UserName, Password, Configuration, (int)KafkaLogLevel);
}

void UUEKafkaSubsystem::CreateAdminStr(FString Servers, FString UserName, FString Password, TMap<FString, FString> Configuration, EKafkaLogLevel KafkaLogLevel)
{
	if (UEKafka->GetAdmin())
		UEKafka->GetAdmin()->CreateAdmin(Servers, UserName, Password, Configuration, (int)KafkaLogLevel);
}

FAdminRequestResult UUEKafkaSubsystem::CreateTopics(const TArray<FString> Topics, int NumPartitions, int ReplicationFactor, TMap<ETopicConfig, FString> Configuration, int Timeout)
{
	if (UEKafka->GetAdmin())
		return UEKafka->GetAdmin()->CreateTopics(Topics, NumPartitions, ReplicationFactor, Configuration, Timeout);
	else
		return FAdminRequestResult("Admin client not initialized", true);
}

FAdminRequestResult UUEKafkaSubsystem::DeleteTopics(const TArray<FString> Topics, int Timeout)
{
	if (UEKafka->GetAdmin())
		return UEKafka->GetAdmin()->DeleteTopics(Topics, Timeout);
	else
		return FAdminRequestResult("Admin client not initialized", true);
}

FAdminRequestResult UUEKafkaSubsystem::DeleteRecords(const TArray<FTopicPartitionOffset> TopicPartitionOffsets, int Timeout)
{
	if (UEKafka->GetAdmin())
		return UEKafka->GetAdmin()->DeleteRecords(TopicPartitionOffsets, Timeout);
	else
		return FAdminRequestResult("Admin client not initialized", true);
}

FListTopicsResult UUEKafkaSubsystem::ListTopics(int Timeout)
{
	if (UEKafka->GetAdmin())
		return UEKafka->GetAdmin()->ListTopics(Timeout);
	else
		return FListTopicsResult("Admin client not initialized", true);
}

void UUEKafkaSubsystem::FlushProducer()
{
	if (UEKafka->GetProducer())
		UEKafka->GetProducer()->Flush();
}

TSharedPtr<FUEKafkaModule> UUEKafkaSubsystem::GetUEKafka()
{
	if (!UEKafka)
		UEKafka = MakeShared<FUEKafkaModule>(FUEKafkaModule::Get());

	return UEKafka;
}

void UUEKafkaSubsystem::OnConsumingError(const FString& Error)
{
	OnConsumerError.Broadcast(Error);
}

void UUEKafkaSubsystem::OnNewMessageCallback(const TArray<FConsumerRecord>& Messages)
{
	OnNewMessage.Broadcast(Messages);
}

void UUEKafkaSubsystem::OnCommitCallback(const FConsumerCallback& Callback)
{
	OnCommit.Broadcast(Callback);
}

void UUEKafkaSubsystem::OnStopConsuming()
{
	OnConsumingStopped.Broadcast();
}

void UUEKafkaSubsystem::OnNewMessageProduced(const FProducerCallback& Callback)
{
	OnMessageProduced.Broadcast(Callback);
}





