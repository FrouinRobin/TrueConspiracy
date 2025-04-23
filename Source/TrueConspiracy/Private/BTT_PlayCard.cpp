#include "BTT_PlayCard.h"
#include "TC_AIActions.h"

UBTT_PlayCard::UBTT_PlayCard()
{
	NodeName = "Draw Card";
}

EBTNodeResult::Type UBTT_PlayCard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FAIActions DrawAction(EActionType::PlayCard);

	return EBTNodeResult::Type();
}
