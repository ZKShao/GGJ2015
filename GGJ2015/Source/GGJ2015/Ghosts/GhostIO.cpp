// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ2015.h"
#include "GhostIO.h"
#include <FileManager.h>
#include <Archive.h>

#define MAX_GHOSTS 32

FORCEINLINE FArchive& operator<<(FArchive& Ar, FGhostData_Keyframe& Keyframe)
{
	Ar << Keyframe.TimeStamp;
	Ar << Keyframe.Location.X;
	Ar << Keyframe.Location.Y;
	Ar << Keyframe.Location.Z;
	return Ar;
}

FORCEINLINE FArchive& operator<<(FArchive& Ar, FGhostData_Event& Event)
{
	Ar << Event.TimeStamp;
	Ar << Event.Event;
	return Ar;
}

void GhostIO::WriteGhostData(FString MapName, FGhostData Data)
{
	FString RegisterFile = MapName + "_Count.txt";

	// Read recorded num
	int32 RecordedNum = 0;
	FArchive* FileReader = IFileManager::Get().CreateFileReader(*RegisterFile);
	if (FileReader)
	{
		*FileReader << RecordedNum;
		FileReader->Flush();
		FileReader->Close();
		FileReader = NULL;
	}

	// Write new recorded num
	int32 NewRecordedNum = RecordedNum + 1;
	FArchive* FileWriter = IFileManager::Get().CreateFileWriter(*RegisterFile);
	if (FileWriter)
	{
		*FileWriter << NewRecordedNum;
		FileWriter->Flush();
		FileWriter->Close();
		FileWriter = NULL;
	}

	const int32 Slot = NewRecordedNum % MAX_GHOSTS;
	FString GhostFile = FString::Printf(TEXT("%s_%d.txt"), *MapName, Slot);
	FArchive* GhostFileWriter = IFileManager::Get().CreateFileWriter(*GhostFile);
	if (GhostFileWriter)
	{
		// Write header
		*GhostFileWriter << Data.Name;
		*GhostFileWriter << Data.TimeRemaining;

		// Write key frames
		int32 NumKeyframes = Data.Keyframes.Num();
		*GhostFileWriter << NumKeyframes;
		for (auto Itr = Data.Keyframes.CreateIterator(); Itr; ++Itr)
			*GhostFileWriter << *Itr;

		// Write events
		int32 NumEvents = Data.Events.Num();
		*GhostFileWriter << NumEvents;
		for (auto Itr = Data.Events.CreateIterator(); Itr; ++Itr)
			*GhostFileWriter << *Itr;

		GhostFileWriter->Flush();
		GhostFileWriter->Close();
		GhostFileWriter = NULL;
	}

}

TArray<FGhostData> GhostIO::LoadGhostData(FString MapName)
{
	TArray<FGhostData> GhostDatas;

	for (int32 Slot = 0; Slot < MAX_GHOSTS; ++Slot)
	{
		FString GhostFile = FString::Printf(TEXT("%s_%d.txt"), *MapName, Slot);
		FArchive* GhostFileReader = IFileManager::Get().CreateFileReader(*GhostFile);
		if (GhostFileReader)
		{
			FGhostData NewData;

			// Write header
			*GhostFileReader << NewData.Name;
			*GhostFileReader << NewData.TimeRemaining;

			// Read keyframes
			int32 NumKeyframes;
			*GhostFileReader << NumKeyframes;
			for (int32 i = 0; i < NumKeyframes; ++i)
			{
				FGhostData_Keyframe Keyframe;
				*GhostFileReader << Keyframe;
				NewData.Keyframes.Add(Keyframe);
			}

			// Read events
			int32 NumEvents;
			*GhostFileReader << NumEvents;
			for (int32 i = 0; i < NumEvents; ++i)
			{
				FGhostData_Event Event;
				*GhostFileReader << Event;
				NewData.Events.Add(Event);
			}

			GhostDatas.Add(NewData);

			GhostFileReader->Flush();
			GhostFileReader->Close();
			GhostFileReader = NULL;
		}
	}

	return GhostDatas;
}