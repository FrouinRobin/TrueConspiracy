#include "TC_GameInstance.h"
#include "Kismet/GameplayStatics.h"

//
// GetInstance
//
// Méthode plus flexible : utilise un UObject (n'importe quel acteur, composant, widget...) 
// pour récupérer le GameInstance. Utilise UGameplayStatics pour extraire le monde.
// À utiliser avec this.
//
UTC_GameInstance* UTC_GameInstance::GetInstance(UObject* InWorldContext)
{
    if (!InWorldContext)
        return nullptr;
    return Cast<UTC_GameInstance>(UGameplayStatics::GetGameInstance(InWorldContext));
}

//
// GetInstanceFromWorld
//
// Utilise un pointeur vers un UWorld pour récupérer l'instance du GameInstance personnalisé.
// Utile dans des classes comme GameMode, GameState, ou toute classe qui possède directement un UWorld.
//
UTC_GameInstance* UTC_GameInstance::GetInstanceFromWorld(UWorld* InWorld)
{
    if (!InWorld) 
        return nullptr;
    return Cast<UTC_GameInstance>(InWorld->GetGameInstance());
}

void UTC_GameInstance::SetSelectedFormat(EGameModeFormat InGameModeFormat)
{
    _SelectedFormat = InGameModeFormat;
}

EGameModeFormat UTC_GameInstance::GetSelectedFormat() const
{
    return _SelectedFormat;
}
