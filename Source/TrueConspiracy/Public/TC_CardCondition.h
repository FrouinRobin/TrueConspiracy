// Replace the forward declaration of ETC_CardType with the correct enum declaration or include the header file where it is defined.

#pragma once

#include "CoreMinimal.h"
#include "TC_Condition.h"
#include "TC_CardCondition.generated.h"

class ATC_Card;
class ATC_Slot;

UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class TRUECONSPIRACY_API UTC_CardCondition : public UTC_Condition
{
GENERATED_BODY()

public:

   UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Card Condition")
   bool IsValidForCard(ATC_Card* Card, ATC_Slot* Slot);
   virtual bool IsValidForCard_Implementation(ATC_Card* Card, ATC_Slot* Slot);

   UFUNCTION(BlueprintPure, Category = "Checking")
   bool IsSlotEmpty(ATC_Slot* Slot) const;

   UFUNCTION(BlueprintPure, Category = "Checking")
   bool IsCardType(ATC_Card* Card, ETC_CardType Type) const;

   UFUNCTION(BlueprintPure, Category = "Checking")
   bool IsSlotAcceptingCard(ATC_Slot* Slot, ATC_Card* Card) const;
};
