#pragma once

#include "al2o3_platform/platform.h"

typedef struct Physics_Engine *Physics_EngineHandle;

AL2O3_EXTERN_C Physics_EngineHandle Physics_EngineCreate();
AL2O3_EXTERN_C void Physics_EngineDestroy(Physics_EngineHandle handle);
