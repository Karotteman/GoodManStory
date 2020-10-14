#pragma once

#define PRINTFLOAT(a) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Debug : %f"), a));}
#define PRINTSTRING(a) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Debug : "##a));}
#define PRINTINT(a) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Debug : %d"), a));}
#define PRINTBOOL(a) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Debug : %d"), a));}
