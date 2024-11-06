// Copyright (c) 2024 ElDockerr

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Subsystems/EngineSubsystem.h"
#include "Templates/SharedPointer.h"
#include "ConsumerCallback.h"
#include "ConsumerRecord.h"
#include "UEKafka.h"
#include "ProducerCallback.h"
#include "KafkaProducerConfig.h"
#include "ProducerRecord.h"
#include "KafkaLogLevel.h"
#include "Containers/Map.h"
#include "KafkaAdmin.h"
#include "UEKafkaSubsystem.generated.h"


UCLASS()
class UEKAFKA_API UUEKafkaSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()


public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConsumerError, const FString&, Error);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConsumingStopped);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCommit, const FConsumerCallback&, CommitCallback);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewMessage,const TArray<FConsumerRecord>&, Messages);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Cunsumer", ToolTip = "Create a kafka Consumer. Call it once.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 void CreateConsumerDefault(FString Servers, FString UserName, FString Password, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Cunsumer", ToolTip = "Create a kafka Consumer. Call it once.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 void CreateConsumer(FString Servers, FString UserName, FString Password, TMap<EKafkaConsumerConfig, FString> Configuration, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Cunsumer", ToolTip = "Create a kafka Consumer. Call it once.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 void CreateConsumerStr(FString Servers, FString UserName, FString Password, TMap<FString, FString> Configuration, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Subscribe", ToolTip = "Subscribe to topics", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 void Subscribe(TArray<FString> Topics, int Timeout=1000 );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Unsubscribe", ToolTip ="Unsubscribe from all topics.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 void Unsubscribe(int Timeout=1000);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Commit", ToolTip = "Commit offsets synchronous.warning Blocking.might consume same record multiple times.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 bool Commit();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Commit Async", ToolTip = "", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 void CommitAsync();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Start Consuming", ToolTip = "Start Consuming async.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 int32 StartConsuming();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Stop Consuming", ToolTip = "Stop Consuming async, OnStop callback called.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 void StopConsuming();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pause Consuming", ToolTip = "Pause consuming records until ContinueConsuming is called.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		void PauseConsuming();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Resume Consuming", ToolTip = "Resume consuming records after pause.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		void ResumeConsuming();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Subscription", ToolTip = "Get all subscription topics.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 TArray<FString> GetSubscription();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetGoupId", ToolTip = "Set group Id of this consumer.", Keywords = "UEKafka sample test testing"), Category = "UEKafka|Consumer")
		 void SetGroupId(FString GroupId);
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnConsumerError", ToolTip = "On consumer error callback.", Keywords = ""), Category = "UEKafka|Consumer")
		 FConsumerError OnConsumerError;
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnConsumeStopped", ToolTip = "On Stop consuming callback.", Keywords = ""), Category = "UEKafka|Consumer")
		 FConsumingStopped OnConsumingStopped;
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnCommit", ToolTip = "On Commit async callback.", Keywords = ""), Category = "UEKafka|Consumer")
		 FOnCommit OnCommit;
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnNewMessage", ToolTip = "On new messages consumed callback.", Keywords = ""), Category = "UEKafka|Consumer")
		 FOnNewMessage OnNewMessage;

	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProduce, const FProducerCallback&, ProduceCallback);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Producer", ToolTip = "Create a kafka producer. Call once!", Keywords = ""), Category = "UEKafka|Producer")
		void CreateProducerDefault(FString Servers, FString UserName, FString Password, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Producer", ToolTip = "Create a kafka producer. Call once!", Keywords = ""), Category = "UEKafka|Producer")
		void CreateProducerStr(FString Servers, FString UserName, FString Password, TMap<FString, FString> Configuration, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Producer", ToolTip = "Create a kafka producer. Call once!", Keywords = ""), Category = "UEKafka|Producer")
		void CreateProducer(FString Servers, FString UserName, FString Password, TMap<EKafkaProducerConfig, FString> Configuration, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Produce Record", ToolTip = "Produce Single record", Keywords = ""), Category = "UEKafka|Producer")
		void ProduceRecord(FString Topic, FString Value, int64 Id = -1);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Produce Records", ToolTip = "Produce multiple records.", Keywords = ""), Category = "UEKafka|Producer")
		void ProduceRecords(FString Topic, TMap<FString, int64> ValueIdPair);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Produce Record", ToolTip = "Produce Single record", Keywords = ""), Category = "UEKafka|Producer")
		void ProduceRecordStruct(FProducerRecord Record);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Produce Records", ToolTip = "Produce multiple records.", Keywords = ""), Category = "UEKafka|Producer")
		void ProduceRecordsStruct(TArray<FProducerRecord> Records);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Flush Producer", ToolTip = "Block until the previously sent messages have been delivered. Don't call on game thread.", Keywords = ""), Category = "UEKafka|Producer")
		void FlushProducer();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Purge Messages", ToolTip = "Purge messages currently handled by producer.", Keywords = ""), Category = "UEKafka|Producer")
		void PurgeMessages();
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnMessageProduced", ToolTip = "OnMessage produced callback.(failed/succeded)", Keywords = ""), Category = "UEKafka|Producer")
	FOnProduce OnMessageProduced;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Admin Client", ToolTip = "Create a kafka Admin Client. Call it once.", Keywords = ""), Category = "UEKafka|Admin")
		void CreateAdminDefault(FString Servers, FString UserName, FString Password, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Admin Client", ToolTip = "Create a kafka Admin Client. Call it once.", Keywords = ""), Category = "UEKafka|Admin")
		void CreateAdmin(FString Servers, FString UserName, FString Password, TMap<EKafkaAdminConfig, FString> Configuration, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Admin Client", ToolTip = "Create a kafka Admin Client. Call it once.", Keywords = ""), Category = "UEKafka|Admin")
		void CreateAdminStr(FString Servers, FString UserName, FString Password, TMap<FString, FString> Configuration, EKafkaLogLevel KafkaLogLevel = EKafkaLogLevel::ERR);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Topics", ToolTip = "Create a batch of topics with given configuration.", Keywords = ""), Category = "UEKafka|Admin")
		FAdminRequestResult CreateTopics(const TArray<FString> Topics, int NumPartitions, int  ReplicationFactor, TMap<ETopicConfig, FString> Configuration, int Timeout = 3000);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Delete Topics", ToolTip = "Delete a batch of topics.", Keywords = ""), Category = "UEKafka|Admin")
		FAdminRequestResult DeleteTopics(const TArray<FString> Topics, int Timeout = 3000);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Delete Records", ToolTip = "Delete a batch of records.", Keywords = ""), Category = "UEKafka|Admin")
		FAdminRequestResult DeleteRecords(const TArray<FTopicPartitionOffset> TopicPartitionOffsets, int Timeout = 3000);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "List Topics", ToolTip = "List all the topics.", Keywords = ""), Category = "UEKafka|Admin")
		FListTopicsResult ListTopics(int Timeout = 3000);

	TSharedPtr<FUEKafkaModule> GetUEKafka();
private:
	TSharedPtr<FUEKafkaModule> UEKafka=nullptr;

	void OnConsumingError(const FString& Error);
	void OnNewMessageCallback(const TArray<FConsumerRecord>& Messages);
	void OnCommitCallback(const FConsumerCallback& callback);
	void OnStopConsuming();
	void OnNewMessageProduced(const FProducerCallback& callback);

};
