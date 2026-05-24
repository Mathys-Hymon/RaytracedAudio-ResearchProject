// Copyright (c) 2025 Pinpoint. All Rights Reserved.


#include "Sound/SoundMaterial.h"

USoundMaterial::USoundMaterial()
    : ScatteringFactor(DefaultScatteringFactor)
    , ReflectionFactor(DefaultReflectionFactor)
    , AbsorptionCoefficient(DefaultAbsorptionCoefficient)
{}

#if WITH_EDITOR
void USoundMaterial::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    UObject::PostEditChangeProperty(PropertyChangedEvent);

    OnSoundMaterialPropertyChanged.Broadcast();
}
#endif
