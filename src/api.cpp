#include "al2o3_platform/platform.h"
#include "al2o3_memory/memory.h"
#include "physics_physx4/api.h"
#include <new>

#include "foundation/Px.h"
#include "PxPhysicsAPI.h"
#include "PxPhysics.h"
#include "common/PxTolerancesScale.h"

static class Al2o3Allocator : public physx::PxAllocatorCallback {
public:
	void *allocate(size_t size, const char *, const char *, int) {
		return MEMORY_MALLOC(size); // TODO memory tracking
	}

	void deallocate(void *ptr) {
		MEMORY_FREE(ptr);
	}
} gAllocator;

static class Al2o3ErrorCallback : public physx::PxErrorCallback {
public:
	void reportError(physx::PxErrorCode::Enum code, const char *message, const char *file, int line) final {
		switch (code) {
		case physx::PxErrorCode::eMASK_ALL:
		case physx::PxErrorCode::eNO_ERROR:return;

		case physx::PxErrorCode::eDEBUG_INFO: AL2O3_InfoMsg(file, line, "PhysX", message);
			break;
		case physx::PxErrorCode::eDEBUG_WARNING: AL2O3_WarningMsg(file, line, "PhysX", message);
			break;
		case physx::PxErrorCode::eINVALID_PARAMETER: AL2O3_ErrorMsg(file, line, "PhysX Invalid Parameter", message);
			break;
		case physx::PxErrorCode::eINVALID_OPERATION: AL2O3_ErrorMsg(file, line, "PhysX Invalid Operation", message);
			break;
		case physx::PxErrorCode::eOUT_OF_MEMORY:AL2O3_ErrorMsg(file, line, "PhysX Out of Memory", message);
			break;
		case physx::PxErrorCode::eINTERNAL_ERROR:AL2O3_ErrorMsg(file, line, "PhysX Internal Error", message);
			break;
		case physx::PxErrorCode::eABORT:AL2O3_ErrorMsg(file, line, "PhysX ABORT", message);
			break;
		case physx::PxErrorCode::ePERF_WARNING: AL2O3_InfoMsg(file, line, "PhysX Perf Warning", message);
			break;
		}
	}
} gErrorCallback;

struct Physics_Engine {
	physx::PxFoundation *foundation;
	physx::PxPhysics *physics;

	physx::PxDefaultCpuDispatcher *dispatcher;
	physx::PxScene *scene;

};

AL2O3_EXTERN_C Physics_EngineHandle Physics_EngineCreate() {
	using namespace physx;
	auto engine = (Physics_Engine *) MEMORY_CALLOC(1, sizeof(Physics_Engine));
	if (!engine)
		return nullptr;
	engine->foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	engine->physics = PxCreatePhysics(PX_PHYSICS_VERSION, *engine->foundation, PxTolerancesScale(), true, nullptr);

	PxSceneDesc sceneDesc(engine->physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	engine->dispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = engine->dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	engine->scene = engine->physics->createScene(sceneDesc);

	return engine;
}

AL2O3_EXTERN_C void Physics_EngineDestroy(Physics_EngineHandle handle) {
	if (!handle)
		return;

	if (handle->scene) {
		handle->scene->release();
		handle->scene = nullptr;
	}
	if (handle->dispatcher) {
		handle->dispatcher->release();
		handle->dispatcher = nullptr;
	}
	if (handle->physics) {
		handle->physics->release();
		handle->physics = nullptr;
	}
	if (handle->foundation) {
		handle->foundation->release();
		handle->foundation = nullptr;
	}

	MEMORY_FREE(handle);
}
