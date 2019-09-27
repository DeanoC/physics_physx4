cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
get_directory_property(hasParent PARENT_DIRECTORY)
if(NOT hasParent)
	get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
	set_property(GLOBAL PROPERTY GLOBAL_FETCHDEPS_BASE ${PARENT_DIR}/al2o3 )
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out_libs)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out_bin)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out_bin)
	set(LIB_BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/)
	include(FetchContent)
	FetchContent_Declare( al2o3 GIT_REPOSITORY https://github.com/DeanoC/al2o3 GIT_TAG master )
	FetchContent_GetProperties(al2o3)
	if(NOT al2o3_POPULATED)
		FetchContent_Populate(al2o3)
		add_subdirectory(${al2o3_SOURCE_DIR} ${al2o3_BINARY_DIR})
	endif()
endif ()

SET_MIN_VERSIONS()
set(LibName physics_physx4)
project(${LibName})

DECLARE_FETCH(
		nvidiagameworks_physx
		https://github.com/DeanoC/physx.git
		4.1)
FetchContent_GetProperties(nvidiagameworks_physx)
if (NOT nvidiagameworks_physx_POPULATED)
	FetchContent_Populate(nvidiagameworks_physx)
endif ()

set(Interface
		api.h
		)

set(Src
		api.cpp
		)

set(Deps
		al2o3_platform
		al2o3_memory
		)
ADD_LIB(${LibName} "${Interface}" "${Src}" "${Deps}")

set( Tests
		runner.cpp
		test_api
		)
set( TestDeps
		al2o3_catch2

		utils_simple_logmanager)
ADD_LIB_TESTS(${LibName} "${Interface}" "${Tests}" "${TestDeps}")

if(${CMAKE_BUILD_TYPE})
	message( ${CMAKE_BUILD_TYPE} )
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		target_compile_definitions(${LibName} PUBLIC _DEBUG)
	elseif ()
		target_compile_definitions(${LibName} PUBLIC NDEBUG)
	endif ()
elseif()
	message( "No build type so setting NDEBUG")
	target_compile_definitions(${LibName} PUBLIC NDEBUG)
endif()

target_compile_definitions(${LibName} PRIVATE DISABLE_CUDA_PHYSX PX_PHYSX_STATIC_LIB)

set(PHYSX_SOURCE_SIMULATION_CONTROLLER
		simulationcontroller/src/ScTriggerPairs.h
		simulationcontroller/src/ScTriggerInteraction.h
		simulationcontroller/src/ScTriggerInteraction.cpp
		simulationcontroller/src/ScStaticSim.h
		simulationcontroller/src/ScStaticCore.cpp
		simulationcontroller/src/ScSqBoundsManager.h
		simulationcontroller/src/ScSqBoundsManager.cpp
		simulationcontroller/src/ScSimulationController.h
		simulationcontroller/src/ScSimulationController.cpp
		simulationcontroller/src/ScSimStats.h
		simulationcontroller/src/ScSimStats.cpp
		simulationcontroller/src/ScSimStateData.h
		simulationcontroller/src/ScShapeSim.h
		simulationcontroller/src/ScShapeSim.cpp
		simulationcontroller/src/ScShapeInteraction.h
		simulationcontroller/src/ScShapeInteraction.cpp
		simulationcontroller/src/ScShapeCore.cpp
		simulationcontroller/src/ScScene.cpp
		simulationcontroller/src/ScRigidSim.h
		simulationcontroller/src/ScRigidSim.cpp
		simulationcontroller/src/ScRigidCore.cpp
		simulationcontroller/src/ScPhysics.cpp
		simulationcontroller/src/ScObjectIDTracker.h
		simulationcontroller/src/ScNPhaseCore.h
		simulationcontroller/src/ScNPhaseCore.cpp
		simulationcontroller/src/ScMetaData.cpp
		simulationcontroller/src/ScIterators.cpp
		simulationcontroller/src/ScInteractionFlags.h
		simulationcontroller/src/ScInteraction.h
		simulationcontroller/src/ScInteraction.cpp
		simulationcontroller/src/ScElementSimInteraction.h
		simulationcontroller/src/ScElementSim.h
		simulationcontroller/src/ScElementSim.cpp
		simulationcontroller/src/ScElementInteractionMarker.h
		simulationcontroller/src/ScElementInteractionMarker.cpp
		simulationcontroller/src/ScContactStream.h
		simulationcontroller/src/ScContactReportBuffer.h
		simulationcontroller/src/ScConstraintSim.h
		simulationcontroller/src/ScConstraintSim.cpp
		simulationcontroller/src/ScConstraintProjectionTree.h
		simulationcontroller/src/ScConstraintProjectionTree.cpp
		simulationcontroller/src/ScConstraintProjectionManager.h
		simulationcontroller/src/ScConstraintProjectionManager.cpp
		simulationcontroller/src/ScConstraintInteraction.h
		simulationcontroller/src/ScConstraintInteraction.cpp
		simulationcontroller/src/ScConstraintGroupNode.h
		simulationcontroller/src/ScConstraintGroupNode.cpp
		simulationcontroller/src/ScConstraintCore.cpp
		simulationcontroller/src/ScClient.h
		simulationcontroller/src/ScBodySim.h
		simulationcontroller/src/ScBodySim.cpp
		simulationcontroller/src/ScBodyCore.cpp
		simulationcontroller/src/ScArticulationSim.h
		simulationcontroller/src/ScArticulationSim.cpp
		simulationcontroller/src/ScArticulationJointSim.h
		simulationcontroller/src/ScArticulationJointSim.cpp
		simulationcontroller/src/ScArticulationJointCore.cpp
		simulationcontroller/src/ScArticulationCore.cpp
		simulationcontroller/src/ScActorSim.h
		simulationcontroller/src/ScActorSim.cpp
		simulationcontroller/src/ScActorPair.h
		simulationcontroller/src/ScActorCore.cpp
		simulationcontroller/include/ScStaticCore.h
		simulationcontroller/include/ScShapeCore.h
		simulationcontroller/include/ScScene.h
		simulationcontroller/include/ScRigidCore.h
		simulationcontroller/include/ScPhysics.h
		simulationcontroller/include/ScMaterialCore.h
		simulationcontroller/include/ScIterators.h
		simulationcontroller/include/ScConstraintCore.h
		simulationcontroller/include/ScBodyCore.h
		simulationcontroller/include/ScArticulationJointCore.h
		simulationcontroller/include/ScArticulationCore.h
		simulationcontroller/include/ScActorCore.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/simulationcontroller/include)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/simulationcontroller/src)

set(PHYSX_SOURCE_SCENE_QUERY
		scenequery/src/SqTypedef.h
		scenequery/src/SqSceneQueryManager.cpp
		scenequery/src/SqPruningStructure.cpp
		scenequery/src/SqPruningPool.h
		scenequery/src/SqPruningPool.cpp
		scenequery/src/SqMetaData.cpp
		scenequery/src/SqIncrementalAABBTree.h
		scenequery/src/SqIncrementalAABBTree.cpp
		scenequery/src/SqIncrementalAABBPrunerCore.h
		scenequery/src/SqIncrementalAABBPrunerCore.cpp
		scenequery/src/SqIncrementalAABBPruner.h
		scenequery/src/SqIncrementalAABBPruner.cpp
		scenequery/src/SqExtendedBucketPruner.h
		scenequery/src/SqExtendedBucketPruner.cpp
		scenequery/src/SqCompoundPruningPool.h
		scenequery/src/SqCompoundPruningPool.cpp
		scenequery/src/SqCompoundPruner.h
		scenequery/src/SqCompoundPruner.cpp
		scenequery/src/SqBucketPruner.h
		scenequery/src/SqBucketPruner.cpp
		scenequery/src/SqBounds.h
		scenequery/src/SqBounds.cpp
		scenequery/src/SqAABBTreeUpdateMap.h
		scenequery/src/SqAABBTreeUpdateMap.cpp
		scenequery/src/SqAABBTree.h
		scenequery/src/SqAABBTree.cpp
		scenequery/src/SqAABBPruner.h
		scenequery/src/SqAABBPruner.cpp
		scenequery/include/SqSceneQueryManager.h
		scenequery/include/SqPruningStructure.h
		scenequery/include/SqPrunerMergeData.h
		scenequery/include/SqPruner.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/scenequery/include)

set(PHYSX_SOURCE_PVD
		pvd/src/PxPvdUserRenderTypes.h
		pvd/src/PxPvdUserRenderImpl.h
		pvd/src/PxPvdUserRenderer.cpp
		pvd/src/PxPvdProfileZoneClient.h
		pvd/src/PxPvdProfileZoneClient.cpp
		pvd/src/PxPvdProfileZone.h
		pvd/src/PxPvdObjectRegistrar.h
		pvd/src/PxPvdObjectRegistrar.cpp
		pvd/src/PxPvdObjectModelMetaData.h
		pvd/src/PxPvdObjectModelMetaData.cpp
		pvd/src/PxPvdObjectModelInternalTypes.h
		pvd/src/PxPvdObjectModelInternalTypeDefs.h
		pvd/src/PxPvdMemClient.h
		pvd/src/PxPvdMemClient.cpp
		pvd/src/PxPvdMarshalling.h
		pvd/src/PxPvdInternalByteStreams.h
		pvd/src/PxPvdImpl.h
		pvd/src/PxPvdImpl.cpp
		pvd/src/PxPvdFoundation.h
		pvd/src/PxPvdDefaultSocketTransport.h
		pvd/src/PxPvdDefaultSocketTransport.cpp
		pvd/src/PxPvdDefaultFileTransport.h
		pvd/src/PxPvdDefaultFileTransport.cpp
		pvd/src/PxPvdDataStream.cpp
		pvd/src/PxPvdCommStreamTypes.h
		pvd/src/PxPvdCommStreamEventSink.h
		pvd/src/PxPvdCommStreamEvents.h
		pvd/src/PxPvdByteStreams.h
		pvd/src/PxPvdBits.h
		pvd/src/PxPvd.cpp
		pvd/src/PxProfileZoneManagerImpl.h
		pvd/src/PxProfileZoneManager.h
		pvd/src/PxProfileZoneImpl.h
		pvd/src/PxProfileScopedMutexLock.h
		pvd/src/PxProfileScopedEvent.h
		pvd/src/PxProfileMemoryEvents.h
		pvd/src/PxProfileMemoryEventBuffer.h
		pvd/src/PxProfileMemoryBuffer.h
		pvd/src/PxProfileMemory.h
		pvd/src/PxProfileEventSerialization.h
		pvd/src/PxProfileEventSender.h
		pvd/src/PxProfileEvents.h
		pvd/src/PxProfileEventNames.h
		pvd/src/PxProfileEventMutex.h
		pvd/src/PxProfileEventImpl.cpp
		pvd/src/PxProfileEventId.h
		pvd/src/PxProfileEventBufferClientManager.h
		pvd/src/PxProfileEventBufferClient.h
		pvd/src/PxProfileEventBufferAtomic.h
		pvd/src/PxProfileEventBuffer.h
		pvd/src/PxProfileDataParsing.h
		pvd/src/PxProfileDataBuffer.h
		pvd/src/PxProfileContextProviderImpl.h
		pvd/src/PxProfileContextProvider.h
		pvd/include/PxPvdUserRenderer.h
		pvd/include/PxPvdRenderBuffer.h
		pvd/include/PxPvdObjectModelBaseTypes.h
		pvd/include/PxPvdErrorCodes.h
		pvd/include/PxPvdDataStreamHelpers.h
		pvd/include/PxPvdDataStream.h
		pvd/include/PxPvdClient.h
		pvd/include/PxProfileAllocatorWrapper.h
		pvd/include/PsPvd.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/pvd/include)

#physxvehicle TODO
set(PHYSX_SOURCE_PHYSXVEHICLE
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxvehicle/include)

set(PHYSX_SOURCE_PHYSXMETADATA
		physxmetadata/core/include/PvdMetaDataDefineProperties.h
		physxmetadata/core/include/PvdMetaDataExtensions.h
		physxmetadata/core/include/PvdMetaDataPropertyVisitor.h
		physxmetadata/core/include/PxAutoGeneratedMetaDataObjectNames.h
		physxmetadata/core/include/PxAutoGeneratedMetaDataObjects.h
		physxmetadata/core/include/PxMetaDataCompare.h
		physxmetadata/core/include/PxMetaDataCppPrefix.h
		physxmetadata/core/include/PxMetaDataObjects.h
		physxmetadata/core/include/RepXMetaDataPropertyVisitor.h
		physxmetadata/core/src/PxAutoGeneratedMetaDataObjects.cpp
		physxmetadata/core/src/PxMetaDataObjects.cpp
		physxmetadata/extensions/include/PxExtensionAutoGeneratedMetaDataObjectNames.h
		physxmetadata/extensions/include/PxExtensionAutoGeneratedMetaDataObjects.h
		physxmetadata/extensions/include/PxExtensionMetaDataObjects.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxmetadata/core/include)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxmetadata/extensions/include)

#physxgpu TODO

set(PHYSX_SOURCE_PHYSXEXTENSIONS
		physxextensions/src/ExtTriangleMeshExt.cpp
		physxextensions/src/ExtTaskQueueHelper.h
		physxextensions/src/ExtSphericalJoint.h
		physxextensions/src/ExtSphericalJoint.cpp
		physxextensions/src/ExtSmoothNormals.cpp
		physxextensions/src/ExtSimpleFactory.cpp
		physxextensions/src/ExtSharedQueueEntryPool.h
		physxextensions/src/ExtSerialization.h
		physxextensions/src/ExtSceneQueryExt.cpp
		physxextensions/src/ExtRigidBodyExt.cpp
		physxextensions/src/ExtRigidActorExt.cpp
		physxextensions/src/ExtRevoluteJoint.h
		physxextensions/src/ExtRevoluteJoint.cpp
		physxextensions/src/ExtRaycastCCD.cpp
		physxextensions/src/ExtPxStringTable.cpp
		physxextensions/src/ExtPvd.h
		physxextensions/src/ExtPvd.cpp
		physxextensions/src/ExtPrismaticJoint.h
		physxextensions/src/ExtPrismaticJoint.cpp
		physxextensions/src/ExtPlatform.h
		physxextensions/src/ExtMetaData.cpp
		physxextensions/src/ExtJointMetaDataExtensions.h
		physxextensions/src/ExtJointData.h
		physxextensions/src/ExtJoint.h
		physxextensions/src/ExtJoint.cpp
		physxextensions/src/ExtInertiaTensor.h
		physxextensions/src/ExtFixedJoint.h
		physxextensions/src/ExtFixedJoint.cpp
		physxextensions/src/ExtExtensions.cpp
		physxextensions/src/ExtDistanceJoint.h
		physxextensions/src/ExtDistanceJoint.cpp
		physxextensions/src/ExtDefaultStreams.cpp
		physxextensions/src/ExtDefaultSimulationFilterShader.cpp
		physxextensions/src/ExtDefaultErrorCallback.cpp
		physxextensions/src/ExtDefaultCpuDispatcher.h
		physxextensions/src/ExtDefaultCpuDispatcher.cpp
		physxextensions/src/ExtD6JointCreate.cpp
		physxextensions/src/ExtD6Joint.h
		physxextensions/src/ExtD6Joint.cpp
		physxextensions/src/ExtCpuWorkerThread.h
		physxextensions/src/ExtCpuWorkerThread.cpp
		physxextensions/src/ExtConvexMeshExt.cpp
		physxextensions/src/ExtContactJoint.h
		physxextensions/src/ExtContactJoint.cpp
		physxextensions/src/ExtConstraintHelper.h
		physxextensions/src/ExtCollection.cpp
		physxextensions/src/ExtBroadPhase.cpp

		physxextensions/src/serialization/SnSerialUtils.h
		physxextensions/src/serialization/SnSerialUtils.cpp
		physxextensions/src/serialization/SnSerializationRegistry.h
		physxextensions/src/serialization/SnSerializationRegistry.cpp
		physxextensions/src/serialization/SnSerialization.cpp
		physxextensions/src/serialization/Xml/SnXmlWriter.h
		physxextensions/src/serialization/Xml/SnXmlVisitorWriter.h
		physxextensions/src/serialization/Xml/SnXmlVisitorReader.h
		physxextensions/src/serialization/Xml/SnXmlStringToType.h
		physxextensions/src/serialization/Xml/SnXmlSimpleXmlWriter.h
		physxextensions/src/serialization/Xml/SnXmlSerializer.h
		physxextensions/src/serialization/Xml/SnXmlSerialization.cpp
		physxextensions/src/serialization/Xml/SnXmlReader.h
		physxextensions/src/serialization/Xml/SnXmlMemoryPoolStreams.h
		physxextensions/src/serialization/Xml/SnXmlMemoryPool.h
		physxextensions/src/serialization/Xml/SnXmlMemoryAllocator.h
		physxextensions/src/serialization/Xml/SnXmlImpl.h
		physxextensions/src/serialization/Xml/SnXmlDeserializer.h
		physxextensions/src/serialization/Xml/SnSimpleXmlWriter.h
		physxextensions/src/serialization/Xml/SnRepXUpgrader.h
		physxextensions/src/serialization/Xml/SnRepXUpgrader.cpp
		physxextensions/src/serialization/Xml/SnRepXSerializerImpl.h
		physxextensions/src/serialization/Xml/SnRepXCoreSerializer.h
		physxextensions/src/serialization/Xml/SnRepXCoreSerializer.cpp
		physxextensions/src/serialization/Xml/SnRepXCollection.h
		physxextensions/src/serialization/Xml/SnRepX3_2Defaults.h
		physxextensions/src/serialization/Xml/SnRepX3_1Defaults.h
		physxextensions/src/serialization/Xml/SnRepX1_0Defaults.h
		physxextensions/src/serialization/Xml/SnPxStreamOperators.h
		physxextensions/src/serialization/Xml/SnJointRepXSerializer.h
		physxextensions/src/serialization/Xml/SnJointRepXSerializer.cpp
		physxextensions/src/serialization/File/SnFile.h

		physxextensions/src/serialization/Binary/SnBinaryDeserialization.cpp
		physxextensions/src/serialization/Binary/SnSerializationContext.h
		physxextensions/src/serialization/Binary/SnSerializationContext.cpp
		physxextensions/src/serialization/Binary/SnConvX.h
		physxextensions/src/serialization/Binary/SnConvX.cpp
		physxextensions/src/serialization/Binary/SnConvX_Union.h
		physxextensions/src/serialization/Binary/SnConvX_Union.cpp
		physxextensions/src/serialization/Binary/SnConvX_Output.h
		physxextensions/src/serialization/Binary/SnConvX_Output.cpp
		physxextensions/src/serialization/Binary/SnConvX_MetaData.h
		physxextensions/src/serialization/Binary/SnConvX_MetaData.cpp
		physxextensions/src/serialization/Binary/SnConvX_Error.cpp
		physxextensions/src/serialization/Binary/SnConvX_Convert.cpp
		physxextensions/src/serialization/Binary/SnConvX_Common.h
		physxextensions/src/serialization/Binary/SnConvX_Align.h
		physxextensions/src/serialization/Binary/SnConvX_Align.cpp
		physxextensions/src/serialization/Binary/SnBinarySerialization.cpp
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxextensions/src)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxextensions/src/serialization)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxextensions/src/serialization/Xml)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxextensions/src/serialization/Binary)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxextensions/src/serialization/File)

set(PHYSX_SOURCE_PHYSXCOOKING
		physxcooking/src/Adjacencies.cpp
		physxcooking/src/Quantizer.h
		physxcooking/src/Quantizer.cpp
		physxcooking/src/MeshCleaner.h
		physxcooking/src/MeshCleaner.cpp
		physxcooking/src/EdgeList.h
		physxcooking/src/EdgeList.cpp
		physxcooking/src/CookingUtils.h
		physxcooking/src/CookingUtils.cpp
		physxcooking/src/Cooking.h
		physxcooking/src/Cooking.cpp
		physxcooking/src/BVHStructureBuilder.h
		physxcooking/src/BVHStructureBuilder.cpp
		physxcooking/src/Adjacencies.h
		physxcooking/src/mesh/TriangleMeshBuilder.h
		physxcooking/src/mesh/TriangleMeshBuilder.cpp
		physxcooking/src/mesh/RTreeCooking.h
		physxcooking/src/mesh/RTreeCooking.cpp
		physxcooking/src/mesh/QuickSelect.h
		physxcooking/src/mesh/MeshBuilder.h
		physxcooking/src/mesh/MeshBuilder.cpp
		physxcooking/src/mesh/HeightFieldCooking.h
		physxcooking/src/mesh/HeightFieldCooking.cpp
		physxcooking/src/mesh/GrbTriangleMeshCooking.h
		physxcooking/src/mesh/GrbTriangleMeshCooking.cpp
		physxcooking/src/convex/VolumeIntegration.h
		physxcooking/src/convex/VolumeIntegration.cpp
		physxcooking/src/convex/QuickHullConvexHullLib.h
		physxcooking/src/convex/QuickHullConvexHullLib.cpp
		physxcooking/src/convex/ConvexPolygonsBuilder.h
		physxcooking/src/convex/ConvexPolygonsBuilder.cpp
		physxcooking/src/convex/ConvexMeshBuilder.h
		physxcooking/src/convex/ConvexMeshBuilder.cpp
		physxcooking/src/convex/ConvexHullUtils.h
		physxcooking/src/convex/ConvexHullUtils.cpp
		physxcooking/src/convex/ConvexHullLib.h
		physxcooking/src/convex/ConvexHullLib.cpp
		physxcooking/src/convex/ConvexHullBuilder.h
		physxcooking/src/convex/ConvexHullBuilder.cpp
		physxcooking/src/convex/BigConvexDataBuilder.h
		physxcooking/src/convex/BigConvexDataBuilder.cpp
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxcooking/src)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxcooking/src/mesh)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxcooking/src/convex)

set(PHYSX_SOURCE_PHYSXCHARACTERKINIMATRIC
		physxcharacterkinematic/src/CctUtils.h
		physxcharacterkinematic/src/CctSweptVolume.h
		physxcharacterkinematic/src/CctSweptVolume.cpp
		physxcharacterkinematic/src/CctSweptCapsule.h
		physxcharacterkinematic/src/CctSweptCapsule.cpp
		physxcharacterkinematic/src/CctSweptBox.h
		physxcharacterkinematic/src/CctSweptBox.cpp
		physxcharacterkinematic/src/CctObstacleContext.h
		physxcharacterkinematic/src/CctObstacleContext.cpp
		physxcharacterkinematic/src/CctInternalStructs.h
		physxcharacterkinematic/src/CctController.h
		physxcharacterkinematic/src/CctController.cpp
		physxcharacterkinematic/src/CctCharacterControllerManager.h
		physxcharacterkinematic/src/CctCharacterControllerManager.cpp
		physxcharacterkinematic/src/CctCharacterControllerCallbacks.cpp
		physxcharacterkinematic/src/CctCharacterController.h
		physxcharacterkinematic/src/CctCharacterController.cpp
		physxcharacterkinematic/src/CctCapsuleController.h
		physxcharacterkinematic/src/CctCapsuleController.cpp
		physxcharacterkinematic/src/CctBoxController.h
		physxcharacterkinematic/src/CctBoxController.cpp
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physxcharacterkinematic/src)

set(PHYSX_SOURCE_PHYSX
		physx/src/NpActor.cpp
		physx/src/PvdTypeNames.h
		physx/src/PvdPhysicsClient.h
		physx/src/PvdPhysicsClient.cpp
		physx/src/PvdMetaDataPvdBinding.h
		physx/src/PvdMetaDataPvdBinding.cpp
		physx/src/PvdMetaDataBindingData.h
		physx/src/NpWriteCheck.h
		physx/src/NpWriteCheck.cpp
		physx/src/NpShapeManager.h
		physx/src/NpShapeManager.cpp
		physx/src/NpShape.h
		physx/src/NpShape.cpp
		physx/src/NpSerializerAdapter.cpp
		physx/src/NpSceneQueries.h
		physx/src/NpSceneQueries.cpp
		physx/src/NpSceneAccessor.h
		physx/src/NpScene.h
		physx/src/NpScene.cpp
		physx/src/NpRigidStatic.h
		physx/src/NpRigidStatic.cpp
		physx/src/NpRigidDynamic.h
		physx/src/NpRigidDynamic.cpp
		physx/src/NpRigidBodyTemplate.h
		physx/src/NpRigidActorTemplateInternal.h
		physx/src/NpRigidActorTemplate.h
		physx/src/NpReadCheck.h
		physx/src/NpReadCheck.cpp
		physx/src/NpQueryShared.h
		physx/src/NpPvdSceneQueryCollector.h
		physx/src/NpPvdSceneQueryCollector.cpp
		physx/src/NpPtrTableStorageManager.h
		physx/src/NpPhysicsInsertionCallback.h
		physx/src/NpPhysics.h
		physx/src/NpPhysics.cpp
		physx/src/NpMetaData.cpp
		physx/src/NpMaterialManager.h
		physx/src/NpMaterial.h
		physx/src/NpMaterial.cpp
		physx/src/NpFactory.h
		physx/src/NpFactory.cpp
		physx/src/NpConstraint.h
		physx/src/NpConstraint.cpp
		physx/src/NpConnector.h
		physx/src/NpCast.h
		physx/src/NpBatchQuery.h
		physx/src/NpBatchQuery.cpp
		physx/src/NpArticulationTemplate.h
		physx/src/NpArticulationReducedCoordinate.h
		physx/src/NpArticulationReducedCoordinate.cpp
		physx/src/NpArticulationLink.h
		physx/src/NpArticulationLink.cpp
		physx/src/NpArticulationJointReducedCoordinate.h
		physx/src/NpArticulationJointReducedCoordinate.cpp
		physx/src/NpArticulationJoint.h
		physx/src/NpArticulationJoint.cpp
		physx/src/NpArticulation.h
		physx/src/NpArticulation.cpp
		physx/src/NpAggregate.h
		physx/src/NpAggregate.cpp
		physx/src/NpActorTemplate.h
		physx/src/NpActor.h

		physx/src/buffering/ScbActor.cpp
		physx/src/buffering/ScbActor.h
		physx/src/buffering/ScbAggregate.cpp
		physx/src/buffering/ScbAggregate.h
		physx/src/buffering/ScbArticulation.h
		physx/src/buffering/ScbArticulationJoint.h
		physx/src/buffering/ScbBase.cpp
		physx/src/buffering/ScbBase.h
		physx/src/buffering/ScbBody.h
		physx/src/buffering/ScbConstraint.h
		physx/src/buffering/ScbDefs.h
		physx/src/buffering/ScbMetaData.cpp
		physx/src/buffering/ScbNpDeps.h
		physx/src/buffering/ScbRigidObject.h
		physx/src/buffering/ScbRigidStatic.h
		physx/src/buffering/ScbScene.cpp
		physx/src/buffering/ScbScene.h
		physx/src/buffering/ScbSceneBuffer.h
		physx/src/buffering/ScbScenePvdClient.cpp
		physx/src/buffering/ScbScenePvdClient.h
		physx/src/buffering/ScbShape.cpp
		physx/src/buffering/ScbShape.h
		physx/src/buffering/ScbType.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physx/src)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/physx/src/buffering)

set(PHYSX_SOURCE_LOWLEVELDYNAMICS
		lowleveldynamics/src/DyThresholdTable.cpp
		lowleveldynamics/src/DyThreadContext.h
		lowleveldynamics/src/DyThreadContext.cpp
		lowleveldynamics/src/DyTGSDynamics.h
		lowleveldynamics/src/DyTGSDynamics.cpp
		lowleveldynamics/src/DyTGSContactPrepBlock.cpp
		lowleveldynamics/src/DyTGSContactPrep.h
		lowleveldynamics/src/DyTGSContactPrep.cpp
		lowleveldynamics/src/DySpatial.h
		lowleveldynamics/src/DySolverPFConstraintsBlock.cpp
		lowleveldynamics/src/DySolverPFConstraints.cpp
		lowleveldynamics/src/DySolverExt.h
		lowleveldynamics/src/DySolverCore.h
		lowleveldynamics/src/DySolverControlPF.h
		lowleveldynamics/src/DySolverControlPF.cpp
		lowleveldynamics/src/DySolverControl.h
		lowleveldynamics/src/DySolverControl.cpp
		lowleveldynamics/src/DySolverContext.h
		lowleveldynamics/src/DySolverContactPF4.h
		lowleveldynamics/src/DySolverContactPF.h
		lowleveldynamics/src/DySolverContact4.h
		lowleveldynamics/src/DySolverContact.h
		lowleveldynamics/src/DySolverConstraintTypes.h
		lowleveldynamics/src/DySolverConstraintsShared.h
		lowleveldynamics/src/DySolverConstraintsBlock.cpp
		lowleveldynamics/src/DySolverConstraints.cpp
		lowleveldynamics/src/DySolverConstraintExtShared.h
		lowleveldynamics/src/DySolverConstraintDesc.h
		lowleveldynamics/src/DySolverConstraint1DStep.h
		lowleveldynamics/src/DySolverConstraint1D4.h
		lowleveldynamics/src/DySolverConstraint1D.h
		lowleveldynamics/src/DySolverBody.h
		lowleveldynamics/src/DyRigidBodyToSolverBody.cpp
		lowleveldynamics/src/DyFrictionPatchStreamPair.h
		lowleveldynamics/src/DyFrictionPatch.h
		lowleveldynamics/src/DyFrictionCorrelation.cpp
		lowleveldynamics/src/DyFeatherstoneInverseDynamic.cpp
		lowleveldynamics/src/DyFeatherstoneForwardDynamic.cpp
		lowleveldynamics/src/DyFeatherstoneArticulationLink.h
		lowleveldynamics/src/DyFeatherstoneArticulation.cpp
		lowleveldynamics/src/DyDynamics.h
		lowleveldynamics/src/DyDynamics.cpp
		lowleveldynamics/src/DyCorrelationBuffer.h
		lowleveldynamics/src/DyContactReduction.h
		lowleveldynamics/src/DyContactPrepShared.h
		lowleveldynamics/src/DyContactPrepPF.cpp
		lowleveldynamics/src/DyContactPrep4PF.cpp
		lowleveldynamics/src/DyContactPrep4.cpp
		lowleveldynamics/src/DyContactPrep.h
		lowleveldynamics/src/DyContactPrep.cpp
		lowleveldynamics/src/DyConstraintSetupBlock.cpp
		lowleveldynamics/src/DyConstraintSetup.cpp
		lowleveldynamics/src/DyConstraintPrep.h
		lowleveldynamics/src/DyConstraintPartition.h
		lowleveldynamics/src/DyConstraintPartition.cpp
		lowleveldynamics/src/DyBodyCoreIntegrator.h
		lowleveldynamics/src/DyArticulationUtils.h
		lowleveldynamics/src/DyArticulationSIMD.cpp
		lowleveldynamics/src/DyArticulationScalar.h
		lowleveldynamics/src/DyArticulationScalar.cpp
		lowleveldynamics/src/DyArticulationReference.h
		lowleveldynamics/src/DyArticulationPImpl.h
		lowleveldynamics/src/DyArticulationHelper.h
		lowleveldynamics/src/DyArticulationHelper.cpp
		lowleveldynamics/src/DyArticulationFnsSimd.h
		lowleveldynamics/src/DyArticulationFnsScalar.h
		lowleveldynamics/src/DyArticulationFnsDebug.h
		lowleveldynamics/src/DyArticulationContactPrepPF.cpp
		lowleveldynamics/src/DyArticulationContactPrep.h
		lowleveldynamics/src/DyArticulationContactPrep.cpp
		lowleveldynamics/src/DyArticulation.cpp
		lowleveldynamics/include/DyVArticulation.h
		lowleveldynamics/include/DyThresholdTable.h
		lowleveldynamics/include/DySleepingConfigulation.h
		lowleveldynamics/include/DyFeatherstoneArticulationUtils.h
		lowleveldynamics/include/DyFeatherstoneArticulationJointData.h
		lowleveldynamics/include/DyFeatherstoneArticulation.h
		lowleveldynamics/include/DyContext.h
		lowleveldynamics/include/DyConstraintWriteBack.h
		lowleveldynamics/include/DyConstraint.h
		lowleveldynamics/include/DyArticulationJointCore.h
		lowleveldynamics/include/DyArticulationCore.h
		lowleveldynamics/include/DyArticulation.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/lowleveldynamics/include)

set(PHYSX_SOURCE_LOWLEVELAABB
		lowlevelaabb/src/BpSAPTasks.h
		lowlevelaabb/src/BpSAPTasks.cpp
		lowlevelaabb/src/BpMBPTasks.h
		lowlevelaabb/src/BpMBPTasks.cpp
		lowlevelaabb/src/BpBroadPhaseShared.h
		lowlevelaabb/src/BpBroadPhaseShared.cpp
		lowlevelaabb/src/BpBroadPhaseSapAux.h
		lowlevelaabb/src/BpBroadPhaseSapAux.cpp
		lowlevelaabb/src/BpBroadPhaseSap.h
		lowlevelaabb/src/BpBroadPhaseSap.cpp
		lowlevelaabb/src/BpBroadPhaseMBPCommon.h
		lowlevelaabb/src/BpBroadPhaseMBP.h
		lowlevelaabb/src/BpBroadPhaseMBP.cpp
		lowlevelaabb/src/BpBroadPhaseABP.h
		lowlevelaabb/src/BpBroadPhaseABP.cpp
		lowlevelaabb/src/BpBroadPhase.cpp
		lowlevelaabb/src/BpAABBManager.cpp
		lowlevelaabb/include/BpBroadPhaseUpdate.h
		lowlevelaabb/include/BpBroadPhase.h
		lowlevelaabb/include/BpAABBManagerTasks.h
		lowlevelaabb/include/BpAABBManager.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/lowlevelaabb/include)

set(PHYSX_SOURCE_LOWLEVEL
		lowlevel/api/include/PxsMaterialCore.h
		lowlevel/api/include/PxsMaterialManager.h
		lowlevel/api/include/PxvConfig.h
		lowlevel/api/include/PxvDynamics.h
		lowlevel/api/include/PxvGeometry.h
		lowlevel/api/include/PxvGlobals.h
		lowlevel/api/include/PxvManager.h
		lowlevel/api/include/PxvSimStats.h
		lowlevel/api/src/px_globals.cpp
		lowlevel/common/include/collision/PxcContactMethodImpl.h
		lowlevel/common/include/pipeline/PxcConstraintBlockStream.h
		lowlevel/common/include/pipeline/PxcContactCache.h
		lowlevel/common/include/pipeline/PxcMaterialMethodImpl.h
		lowlevel/common/include/pipeline/PxcNpBatch.h
		lowlevel/common/include/pipeline/PxcNpCache.h
		lowlevel/common/include/pipeline/PxcNpCacheStreamPair.h
		lowlevel/common/include/pipeline/PxcNpContactPrepShared.h
		lowlevel/common/include/pipeline/PxcNpMemBlockPool.h
		lowlevel/common/include/pipeline/PxcNpThreadContext.h
		lowlevel/common/include/pipeline/PxcNpWorkUnit.h
		lowlevel/common/include/utils/PxcScratchAllocator.h
		lowlevel/common/include/utils/PxcThreadCoherentCache.h
		lowlevel/common/src/pipeline/PxcContactCache.cpp
		lowlevel/common/src/pipeline/PxcContactMethodImpl.cpp
		lowlevel/common/src/pipeline/PxcMaterialHeightField.cpp
		lowlevel/common/src/pipeline/PxcMaterialMesh.cpp
		lowlevel/common/src/pipeline/PxcMaterialMethodImpl.cpp
		lowlevel/common/src/pipeline/PxcMaterialShape.cpp
		lowlevel/common/src/pipeline/PxcNpBatch.cpp
		lowlevel/common/src/pipeline/PxcNpCacheStreamPair.cpp
		lowlevel/common/src/pipeline/PxcNpContactPrepShared.cpp
		lowlevel/common/src/pipeline/PxcNpMemBlockPool.cpp
		lowlevel/common/src/pipeline/PxcNpThreadContext.cpp

		lowlevel/software/include/PxsBodySim.h
		lowlevel/software/include/PxsCCD.h
		lowlevel/software/include/PxsContactManager.h
		lowlevel/software/include/PxsContactManagerState.h
		lowlevel/software/include/PxsContext.h
		lowlevel/software/include/PxsDefaultMemoryManager.h
		lowlevel/software/include/PxsHeapMemoryAllocator.h
		lowlevel/software/include/PxsIncrementalConstraintPartitioning.h
		lowlevel/software/include/PxsIslandManagerTypes.h
		lowlevel/software/include/PxsIslandNodeIndex.h
		lowlevel/software/include/PxsIslandSim.h
		lowlevel/software/include/PxsKernelWrangler.h
		lowlevel/software/include/PxsMaterialCombiner.h
		lowlevel/software/include/PxsMemoryManager.h
		lowlevel/software/include/PxsNphaseImplementationContext.h
		lowlevel/software/include/PxsRigidBody.h
		lowlevel/software/include/PxsShapeSim.h
		lowlevel/software/include/PxsSimpleIslandManager.h
		lowlevel/software/include/PxsSimulationController.h
		lowlevel/software/include/PxsTransformCache.h
		lowlevel/software/include/PxvNphaseImplementationContext.h
		lowlevel/software/src/PxsCCD.cpp
		lowlevel/software/src/PxsContactManager.cpp
		lowlevel/software/src/PxsContext.cpp
		lowlevel/software/src/PxsDefaultMemoryManager.cpp
		lowlevel/software/src/PxsIslandSim.cpp
		lowlevel/software/src/PxsMaterialCombiner.cpp
		lowlevel/software/src/PxsNphaseImplementationContext.cpp
		lowlevel/software/src/PxsSimpleIslandManager.cpp

		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/lowlevel/api/include)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/lowlevel/common/include)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/lowlevel/common/include/collision)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/lowlevel/common/include/pipeline)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/lowlevel/common/include/utils)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/lowlevel/software/include)

set(PHYSX_SOURCE_IMMEDIATEMODE
		immediatemode/src/NpImmediateMode.cpp
		)

set(PHYSX_SOURCE_GEOMUTILS
		geomutils/src/ccd/GuCCDSweepConvexMesh.cpp
		geomutils/src/ccd/GuCCDSweepConvexMesh.h
		geomutils/src/ccd/GuCCDSweepPrimitives.cpp
		geomutils/src/common/GuBarycentricCoordinates.cpp
		geomutils/src/common/GuBarycentricCoordinates.h
		geomutils/src/common/GuBoxConversion.h
		geomutils/src/common/GuEdgeCache.h
		geomutils/src/common/GuEdgeListData.h
		geomutils/src/common/GuSeparatingAxes.cpp
		geomutils/src/common/GuSeparatingAxes.h
		geomutils/src/contact/GuContactBoxBox.cpp
		geomutils/src/contact/GuContactCapsuleBox.cpp
		geomutils/src/contact/GuContactCapsuleCapsule.cpp
		geomutils/src/contact/GuContactCapsuleConvex.cpp
		geomutils/src/contact/GuContactCapsuleMesh.cpp
		geomutils/src/contact/GuContactConvexConvex.cpp
		geomutils/src/contact/GuContactConvexMesh.cpp
		geomutils/src/contact/GuContactMethodImpl.h
		geomutils/src/contact/GuContactPlaneBox.cpp
		geomutils/src/contact/GuContactPlaneCapsule.cpp
		geomutils/src/contact/GuContactPlaneConvex.cpp
		geomutils/src/contact/GuContactPolygonPolygon.cpp
		geomutils/src/contact/GuContactPolygonPolygon.h
		geomutils/src/contact/GuContactSphereBox.cpp
		geomutils/src/contact/GuContactSphereCapsule.cpp
		geomutils/src/contact/GuContactSphereMesh.cpp
		geomutils/src/contact/GuContactSpherePlane.cpp
		geomutils/src/contact/GuContactSphereSphere.cpp
		geomutils/src/contact/GuFeatureCode.cpp
		geomutils/src/contact/GuFeatureCode.h
		geomutils/src/convex/GuBigConvexData.cpp
		geomutils/src/convex/GuBigConvexData.h
		geomutils/src/convex/GuBigConvexData2.h
		geomutils/src/convex/GuConvexEdgeFlags.h
		geomutils/src/convex/GuConvexHelper.cpp
		geomutils/src/convex/GuConvexHelper.h
		geomutils/src/convex/GuConvexMesh.cpp
		geomutils/src/convex/GuConvexMesh.h
		geomutils/src/convex/GuConvexMeshData.h
		geomutils/src/convex/GuConvexSupportTable.cpp
		geomutils/src/convex/GuConvexSupportTable.h
		geomutils/src/convex/GuConvexUtilsInternal.cpp
		geomutils/src/convex/GuConvexUtilsInternal.h
		geomutils/src/convex/GuCubeIndex.h
		geomutils/src/convex/GuHillClimbing.cpp
		geomutils/src/convex/GuHillClimbing.h
		geomutils/src/convex/GuShapeConvex.cpp
		geomutils/src/convex/GuShapeConvex.h
		geomutils/src/distance/GuDistancePointBox.cpp
		geomutils/src/distance/GuDistancePointBox.h
		geomutils/src/distance/GuDistancePointSegment.h
		geomutils/src/distance/GuDistancePointTriangle.cpp
		geomutils/src/distance/GuDistancePointTriangle.h
		geomutils/src/distance/GuDistancePointTriangleSIMD.h
		geomutils/src/distance/GuDistanceSegmentBox.cpp
		geomutils/src/distance/GuDistanceSegmentSegment.cpp
		geomutils/src/distance/GuDistanceSegmentSegmentSIMD.h
		geomutils/src/distance/GuDistanceSegmentTriangle.cpp
		geomutils/src/distance/GuDistanceSegmentTriangle.h
		geomutils/src/distance/GuDistanceSegmentTriangleSIMD.h
		geomutils/src/gjk/GuEPA.cpp
		geomutils/src/gjk/GuEPA.h
		geomutils/src/gjk/GuEPAFacet.h
		geomutils/src/gjk/GuGJK.h
		geomutils/src/gjk/GuGJKPenetration.h
		geomutils/src/gjk/GuGJKRaycast.h
		geomutils/src/gjk/GuGJKSimplex.cpp
		geomutils/src/gjk/GuGJKSimplex.h
		geomutils/src/gjk/GuGJKTest.cpp
		geomutils/src/gjk/GuGJKTest.h
		geomutils/src/gjk/GuGJKType.h
		geomutils/src/gjk/GuGJKUtil.h
		geomutils/src/gjk/GuVecBox.h
		geomutils/src/gjk/GuVecCapsule.h
		geomutils/src/gjk/GuVecConvex.h
		geomutils/src/gjk/GuVecConvexHull.h
		geomutils/src/gjk/GuVecConvexHullNoScale.h
		geomutils/src/gjk/GuVecPlane.h
		geomutils/src/gjk/GuVecSphere.h
		geomutils/src/gjk/GuVecTriangle.h

		geomutils/src/hf/GuEntityReport.h
		geomutils/src/hf/GuHeightField.cpp
		geomutils/src/hf/GuHeightField.h
		geomutils/src/hf/GuHeightFieldData.h
		geomutils/src/hf/GuHeightFieldUtil.cpp
		geomutils/src/hf/GuHeightFieldUtil.h
		geomutils/src/hf/GuOverlapTestsHF.cpp
		geomutils/src/hf/GuSweepsHF.cpp

		geomutils/src/intersection/GuIntersectionBoxBox.cpp
		geomutils/src/intersection/GuIntersectionCapsuleTriangle.cpp
		geomutils/src/intersection/GuIntersectionCapsuleTriangle.h
		geomutils/src/intersection/GuIntersectionEdgeEdge.cpp
		geomutils/src/intersection/GuIntersectionEdgeEdge.h
		geomutils/src/intersection/GuIntersectionRay.h
		geomutils/src/intersection/GuIntersectionRayBox.cpp
		geomutils/src/intersection/GuIntersectionRayBox.h
		geomutils/src/intersection/GuIntersectionRayBoxSIMD.h
		geomutils/src/intersection/GuIntersectionRayCapsule.cpp
		geomutils/src/intersection/GuIntersectionRayCapsule.h
		geomutils/src/intersection/GuIntersectionRayPlane.h
		geomutils/src/intersection/GuIntersectionRaySphere.cpp
		geomutils/src/intersection/GuIntersectionRaySphere.h
		geomutils/src/intersection/GuIntersectionRayTriangle.h
		geomutils/src/intersection/GuIntersectionSphereBox.cpp
		geomutils/src/intersection/GuIntersectionSphereBox.h
		geomutils/src/intersection/GuIntersectionTriangleBox.cpp

		geomutils/src/mesh/GuBV4_AABBAABBSweepTest.h
		geomutils/src/mesh/GuBV4_AABBSweep.cpp
		geomutils/src/mesh/GuBV4_BoxBoxOverlapTest.h
		geomutils/src/mesh/GuBV4_BoxOverlap_Internal.h
		geomutils/src/mesh/GuBV4_BoxOverlap.cpp
		geomutils/src/mesh/GuBV4_BoxSweep_Internal.h
		geomutils/src/mesh/GuBV4_BoxSweep_Params.h
		geomutils/src/mesh/GuBV4_CapsuleSweep_Internal.h
		geomutils/src/mesh/GuBV4_CapsuleSweep.cpp
		geomutils/src/mesh/GuBV4_CapsuleSweepAA.cpp
		geomutils/src/mesh/GuBV4_Common.h
		geomutils/src/mesh/GuBV4_Internal.h
		geomutils/src/mesh/GuBV4_OBBSweep.cpp
		geomutils/src/mesh/GuBV4_ProcessStreamNoOrder_OBBOBB.h
		geomutils/src/mesh/GuBV4_ProcessStreamNoOrder_SegmentAABB_Inflated.h
		geomutils/src/mesh/GuBV4_ProcessStreamNoOrder_SegmentAABB.h
		geomutils/src/mesh/GuBV4_ProcessStreamNoOrder_SphereAABB.h
		geomutils/src/mesh/GuBV4_ProcessStreamOrdered_OBBOBB.h
		geomutils/src/mesh/GuBV4_ProcessStreamOrdered_SegmentAABB_Inflated.h
		geomutils/src/mesh/GuBV4_ProcessStreamOrdered_SegmentAABB.h
		geomutils/src/mesh/GuBV4_Raycast.cpp
		geomutils/src/mesh/GuBV4_Slabs_KajiyaNoOrder.h
		geomutils/src/mesh/GuBV4_Slabs_KajiyaOrdered.h
		geomutils/src/mesh/GuBV4_Slabs_SwizzledNoOrder.h
		geomutils/src/mesh/GuBV4_Slabs_SwizzledOrdered.h
		geomutils/src/mesh/GuBV4_Slabs.h
		geomutils/src/mesh/GuBV4_SphereOverlap.cpp
		geomutils/src/mesh/GuBV4_SphereSweep.cpp
		geomutils/src/mesh/GuBV4.cpp
		geomutils/src/mesh/GuBV4.h
		geomutils/src/mesh/GuBV4Build.cpp
		geomutils/src/mesh/GuBV4Build.h
		geomutils/src/mesh/GuBV4Settings.h
		geomutils/src/mesh/GuBV32.cpp
		geomutils/src/mesh/GuBV32.h
		geomutils/src/mesh/GuBV32Build.cpp
		geomutils/src/mesh/GuBV32Build.h
		geomutils/src/mesh/GuBVConstants.h
		geomutils/src/mesh/GuMeshData.h
		geomutils/src/mesh/GuMeshQuery.cpp
		geomutils/src/mesh/GuMidphaseBV4.cpp
		geomutils/src/mesh/GuMidphaseInterface.h
		geomutils/src/mesh/GuMidphaseRTree.cpp
		geomutils/src/mesh/GuOverlapTestsMesh.cpp
		geomutils/src/mesh/GuRTree.cpp
		geomutils/src/mesh/GuRTree.h
		geomutils/src/mesh/GuRTreeQueries.cpp
		geomutils/src/mesh/GuSweepConvexTri.h
		geomutils/src/mesh/GuSweepMesh.h
		geomutils/src/mesh/GuSweepsMesh.cpp
		geomutils/src/mesh/GuTriangle32.h
		geomutils/src/mesh/GuTriangleCache.h
		geomutils/src/mesh/GuTriangleMesh.cpp
		geomutils/src/mesh/GuTriangleMesh.h
		geomutils/src/mesh/GuTriangleMeshBV4.cpp
		geomutils/src/mesh/GuTriangleMeshBV4.h
		geomutils/src/mesh/GuTriangleMeshRTree.cpp
		geomutils/src/mesh/GuTriangleMeshRTree.h
		geomutils/src/mesh/GuTriangleVertexPointers.h

		geomutils/src/pcm/GuPCMContactBoxBox.cpp
		geomutils/src/pcm/GuPCMContactBoxConvex.cpp
		geomutils/src/pcm/GuPCMContactCapsuleBox.cpp
		geomutils/src/pcm/GuPCMContactCapsuleCapsule.cpp
		geomutils/src/pcm/GuPCMContactCapsuleConvex.cpp
		geomutils/src/pcm/GuPCMContactCapsuleHeightField.cpp
		geomutils/src/pcm/GuPCMContactCapsuleMesh.cpp
		geomutils/src/pcm/GuPCMContactConvexCommon.cpp
		geomutils/src/pcm/GuPCMContactConvexCommon.h
		geomutils/src/pcm/GuPCMContactConvexConvex.cpp
		geomutils/src/pcm/GuPCMContactConvexHeightField.cpp
		geomutils/src/pcm/GuPCMContactConvexMesh.cpp
		geomutils/src/pcm/GuPCMContactGen.h
		geomutils/src/pcm/GuPCMContactGenBoxConvex.cpp
		geomutils/src/pcm/GuPCMContactGenSphereCapsule.cpp
		geomutils/src/pcm/GuPCMContactGenUtil.h
		geomutils/src/pcm/GuPCMContactMeshCallback.h
		geomutils/src/pcm/GuPCMContactPlaneBox.cpp
		geomutils/src/pcm/GuPCMContactPlaneCapsule.cpp
		geomutils/src/pcm/GuPCMContactPlaneConvex.cpp
		geomutils/src/pcm/GuPCMContactSphereBox.cpp
		geomutils/src/pcm/GuPCMContactSphereCapsule.cpp
		geomutils/src/pcm/GuPCMContactSphereConvex.cpp
		geomutils/src/pcm/GuPCMContactSphereHeightField.cpp
		geomutils/src/pcm/GuPCMContactSphereMesh.cpp
		geomutils/src/pcm/GuPCMContactSpherePlane.cpp
		geomutils/src/pcm/GuPCMContactSphereSphere.cpp
		geomutils/src/pcm/GuPCMShapeConvex.cpp
		geomutils/src/pcm/GuPCMShapeConvex.h
		geomutils/src/pcm/GuPCMTriangleContactGen.cpp
		geomutils/src/pcm/GuPCMTriangleContactGen.h
		geomutils/src/pcm/GuPersistentContactManifold.cpp
		geomutils/src/pcm/GuPersistentContactManifold.h

		geomutils/src/sweep/GuSweepBoxBox.cpp
		geomutils/src/sweep/GuSweepBoxBox.h
		geomutils/src/sweep/GuSweepBoxSphere.cpp
		geomutils/src/sweep/GuSweepBoxSphere.h
		geomutils/src/sweep/GuSweepBoxTriangle_FeatureBased.cpp
		geomutils/src/sweep/GuSweepBoxTriangle_FeatureBased.h
		geomutils/src/sweep/GuSweepBoxTriangle_SAT.cpp
		geomutils/src/sweep/GuSweepBoxTriangle_SAT.h
		geomutils/src/sweep/GuSweepCapsuleBox.cpp
		geomutils/src/sweep/GuSweepCapsuleBox.h
		geomutils/src/sweep/GuSweepCapsuleCapsule.cpp
		geomutils/src/sweep/GuSweepCapsuleCapsule.h
		geomutils/src/sweep/GuSweepCapsuleTriangle.cpp
		geomutils/src/sweep/GuSweepCapsuleTriangle.h
		geomutils/src/sweep/GuSweepSphereCapsule.cpp
		geomutils/src/sweep/GuSweepSphereCapsule.h
		geomutils/src/sweep/GuSweepSphereSphere.cpp
		geomutils/src/sweep/GuSweepSphereSphere.h
		geomutils/src/sweep/GuSweepSphereTriangle.cpp
		geomutils/src/sweep/GuSweepSphereTriangle.h
		geomutils/src/sweep/GuSweepTriangleUtils.cpp
		geomutils/src/sweep/GuSweepTriangleUtils.h

		geomutils/src/GuAABBTreeBuild.cpp
		geomutils/src/GuAABBTreeBuild.h
		geomutils/src/GuAABBTreeQuery.h
		geomutils/src/GuBounds.cpp
		geomutils/src/GuBounds.h
		geomutils/src/GuBox.cpp
		geomutils/src/GuBVHStructure.cpp
		geomutils/src/GuBVHStructure.h
		geomutils/src/GuBVHTestsSIMD.h
		geomutils/src/GuCapsule.cpp
		geomutils/src/GuCapsule.h
		geomutils/src/GuCCTSweepTests.cpp
		geomutils/src/GuCenterExtents.h
		geomutils/src/GuGeometryQuery.cpp
		geomutils/src/GuGeometryUnion.cpp
		geomutils/src/GuGeometryUnion.h
		geomutils/src/GuInternal.cpp
		geomutils/src/GuInternal.h
		geomutils/src/GuMeshFactory.cpp
		geomutils/src/GuMeshFactory.h
		geomutils/src/GuMetaData.cpp
		geomutils/src/GuMTD.cpp
		geomutils/src/GuMTD.h
		geomutils/src/GuOverlapTests.cpp
		geomutils/src/GuOverlapTests.h
		geomutils/src/GuRaycastTests.cpp
		geomutils/src/GuSerialize.cpp
		geomutils/src/GuSerialize.h
		geomutils/src/GuSphere.h
		geomutils/src/GuSweepMTD.cpp
		geomutils/src/GuSweepMTD.h
		geomutils/src/GuSweepSharedTests.cpp
		geomutils/src/GuSweepSharedTests.h
		geomutils/src/GuSweepTests.cpp
		geomutils/src/GuSweepTests.h
		geomutils/include/GuSIMDHelpers.h
		geomutils/include/GuSegment.h
		geomutils/include/GuRaycastTests.h
		geomutils/include/GuIntersectionTriangleBoxRef.h
		geomutils/include/GuIntersectionTriangleBox.h
		geomutils/include/GuIntersectionBoxBox.h
		geomutils/include/GuDistanceSegmentSegment.h
		geomutils/include/GuDistanceSegmentBox.h
		geomutils/include/GuBox.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/include)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/ccd)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/common)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/contact)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/convex)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/distance)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/gjk)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/hf)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/intersection)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/mesh)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/pcm)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/geomutils/src/sweep)

set(PHYSX_SOURCE_FOUNDATION
		foundation/src/PsUtilities.cpp
		foundation/src/PsTempAllocator.cpp
		foundation/src/PsString.cpp
		foundation/src/PsMathUtils.cpp
		foundation/src/PsFoundation.cpp
		foundation/src/PsAssert.cpp
		foundation/src/PsAllocator.cpp
		foundation/include/PsVecTransform.h
		foundation/include/PsVecQuat.h
		foundation/include/PsVecMathUtilities.h
		foundation/include/PsVecMathSSE.h
		foundation/include/PsVecMathAoSScalarInline.h
		foundation/include/PsVecMathAoSScalar.h
		foundation/include/PsVecMath.h
		foundation/include/PsUtilities.h
		foundation/include/PsUserAllocated.h
		foundation/include/PsTime.h
		foundation/include/PsThread.h
		foundation/include/PsTempAllocator.h
		foundation/include/PsSync.h
		foundation/include/PsString.h
		foundation/include/PsSortInternals.h
		foundation/include/PsSort.h
		foundation/include/PsSocket.h
		foundation/include/PsSList.h
		foundation/include/PsPool.h
		foundation/include/PsMutex.h
		foundation/include/PsMathUtils.h
		foundation/include/PsIntrinsics.h
		foundation/include/PsInlineArray.h
		foundation/include/PsInlineAoS.h
		foundation/include/PsInlineAllocator.h
		foundation/include/PsHashSet.h
		foundation/include/PsHashMap.h
		foundation/include/PsHashInternals.h
		foundation/include/PsHash.h
		foundation/include/PsFPU.h
		foundation/include/PsFoundation.h
		foundation/include/PsCpu.h
		foundation/include/PsBroadcast.h
		foundation/include/PsBitUtils.h
		foundation/include/PsBasicTemplates.h
		foundation/include/PsAtomic.h
		foundation/include/PsArray.h
		foundation/include/PsAoS.h
		foundation/include/PsAllocator.h
		foundation/include/PsAlloca.h
		foundation/include/PsAlignedMalloc.h
		foundation/include/Ps.h
		)
if (APPLE OR UNIX)
	list(APPEND PHYSX_SOURCE_FOUNDATION
			foundation/src/unix/PsUnixTime.cpp
			foundation/src/unix/PsUnixThread.cpp
			foundation/src/unix/PsUnixSync.cpp
			foundation/src/unix/PsUnixSocket.cpp
			foundation/src/unix/PsUnixSList.cpp
			foundation/src/unix/PsUnixPrintString.cpp
			foundation/src/unix/PsUnixMutex.cpp
			foundation/src/unix/PsUnixFPU.cpp
			foundation/src/unix/PsUnixCpu.cpp
			foundation/src/unix/PsUnixAtomic.cpp
			)
endif ()
if (WIN32)
	list(APPEND PHYSX_SOURCE_FOUNDATION
			foundation/src/windows/PsWindowsAtomic.cpp
			foundation/src/windows/PsWindowsCpu.cpp
			foundation/src/windows/PsWindowsFPU.cpp
			foundation/src/windows/PsWindowsMutex.cpp
			foundation/src/windows/PsWindowsPrintString.cpp
			foundation/src/windows/PsWindowsSList.cpp
			foundation/src/windows/PsWindowsSocket.cpp
			foundation/src/windows/PsWindowsSync.cpp
			foundation/src/windows/PsWindowsThread.cpp
			foundation/src/windows/PsWindowsTime.cpp
			)
endif ()

target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/foundation/include)

set(PHYSX_SOURCE_FILEBUF
		filebuf/include/PsMemoryBuffer.h
		filebuf/include/PsIOStream.inl
		filebuf/include/PsIOStream.h
		filebuf/include/PsFileBuffer.h
		filebuf/include/PsAsciiConversion.inl
		filebuf/include/PsAsciiConversion.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/filebuf/include)

set(PHYSX_SOURCE_FASTXML
		fastxml/src/PsFastXml.cpp
		fastxml/include/PsFastXml.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/fastxml/include)

set(PHYSX_SOURCE_COMMON
		common/src/CmVisualization.h
		common/src/CmVisualization.cpp
		common/src/CmUtils.h
		common/src/CmTransformUtils.h
		common/src/CmTmpMem.h
		common/src/CmTaskPool.h
		common/src/CmTask.h
		common/src/CmSpatialVector.h
		common/src/CmScaling.h
		common/src/CmRenderOutput.h
		common/src/CmRenderOutput.cpp
		common/src/CmRenderBuffer.h
		common/src/CmRefCountable.h
		common/src/CmRadixSortBuffered.h
		common/src/CmRadixSortBuffered.cpp
		common/src/CmRadixSort.h
		common/src/CmRadixSort.cpp
		common/src/CmQueue.h
		common/src/CmPtrTable.h
		common/src/CmPtrTable.cpp
		common/src/CmPriorityQueue.h
		common/src/CmPreallocatingPool.h
		common/src/CmPool.h
		common/src/CmPhysXCommon.h
		common/src/CmMatrix34.h
		common/src/CmMathUtils.cpp
		common/src/CmIO.h
		common/src/CmIDPool.h
		common/src/CmFlushPool.h
		common/src/CmConeLimitHelper.h
		common/src/CmCollection.h
		common/src/CmCollection.cpp
		common/src/CmBlockArray.h
		common/src/CmBitMap.h

		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/common/src)

set(PHYSX_INCLUDE
		vehicle/PxVehicleWheels.h
		vehicle/PxVehicleUtilTelemetry.h
		vehicle/PxVehicleUtilSetup.h
		vehicle/PxVehicleUtilControl.h
		vehicle/PxVehicleUtil.h
		vehicle/PxVehicleUpdate.h
		vehicle/PxVehicleTireFriction.h
		vehicle/PxVehicleShaders.h
		vehicle/PxVehicleSDK.h
		vehicle/PxVehicleNoDrive.h
		vehicle/PxVehicleDriveTank.h
		vehicle/PxVehicleDriveNW.h
		vehicle/PxVehicleDrive4W.h
		vehicle/PxVehicleDrive.h
		vehicle/PxVehicleComponents.h

		task/PxTaskManager.h
		task/PxTaskDefine.h
		task/PxTask.h
		task/PxCpuDispatcher.h
		solver/PxSolverDefs.h
		PxVisualizationParameter.h
		PxSimulationStatistics.h
		PxSimulationEventCallback.h
		PxShape.h
		PxSceneLock.h
		PxSceneDesc.h
		PxScene.h
		PxRigidStatic.h
		PxRigidDynamic.h
		PxRigidBody.h
		PxRigidActor.h
		PxQueryReport.h
		PxQueryFiltering.h
		PxPruningStructure.h
		PxPhysXConfig.h
		PxPhysicsVersion.h
		PxPhysicsSerialization.h
		PxPhysicsAPI.h
		PxPhysics.h
		PxMaterial.h
		PxLockedData.h
		PxImmediateMode.h
		PxFoundation.h
		PxForceMode.h
		PxFiltering.h
		PxDeletionListener.h
		PxContactModifyCallback.h
		PxContact.h
		PxConstraintDesc.h
		PxConstraint.h
		#		PxConfig.h
		PxClient.h
		PxBroadPhase.h
		PxBatchQueryDesc.h
		PxBatchQuery.h
		PxArticulationReducedCoordinate.h
		PxArticulationLink.h
		PxArticulationJointReducedCoordinate.h
		PxArticulationJoint.h
		PxArticulationBase.h
		PxArticulation.h
		PxAggregate.h
		PxActor.h

		pvd/PxPvdTransport.h
		pvd/PxPvdSceneClient.h
		pvd/PxPvd.h

		gpu/PxGpu.h

		geomutils/GuContactPoint.h
		geomutils/GuContactBuffer.h

		geometry/PxTriangleMeshGeometry.h
		geometry/PxTriangleMesh.h
		geometry/PxTriangle.h
		geometry/PxSphereGeometry.h
		geometry/PxSimpleTriangleMesh.h
		geometry/PxPlaneGeometry.h
		geometry/PxMeshScale.h
		geometry/PxMeshQuery.h
		geometry/PxHeightFieldSample.h
		geometry/PxHeightFieldGeometry.h
		geometry/PxHeightFieldFlag.h
		geometry/PxHeightFieldDesc.h
		geometry/PxHeightField.h
		geometry/PxGeometryQuery.h
		geometry/PxGeometryHelpers.h
		geometry/PxGeometry.h
		geometry/PxConvexMeshGeometry.h
		geometry/PxConvexMesh.h
		geometry/PxCapsuleGeometry.h
		geometry/PxBVHStructure.h
		geometry/PxBoxGeometry.h

		foundation/PxMathUtils.h
		foundation/PxFoundationConfig.h
		foundation/PxAssert.h

		filebuf/PxFileBuf.h

		extensions/PxTriangleMeshExt.h
		extensions/PxStringTableExt.h
		extensions/PxSphericalJoint.h
		extensions/PxSmoothNormals.h
		extensions/PxSimpleFactory.h
		extensions/PxShapeExt.h
		extensions/PxSerialization.h
		extensions/PxSceneQueryExt.h
		extensions/PxRigidBodyExt.h
		extensions/PxRigidActorExt.h
		extensions/PxRevoluteJoint.h
		extensions/PxRepXSimpleType.h
		extensions/PxRepXSerializer.h
		extensions/PxRaycastCCD.h
		extensions/PxPrismaticJoint.h
		extensions/PxMassProperties.h
		extensions/PxJointLimit.h
		extensions/PxJoint.h
		extensions/PxFixedJoint.h
		extensions/PxExtensionsAPI.h
		extensions/PxDistanceJoint.h
		extensions/PxDefaultStreams.h
		extensions/PxDefaultSimulationFilterShader.h
		extensions/PxDefaultErrorCallback.h
		extensions/PxDefaultCpuDispatcher.h
		extensions/PxDefaultAllocator.h
		extensions/PxD6JointCreate.h
		extensions/PxD6Joint.h
		extensions/PxConvexMeshExt.h
		extensions/PxContactJoint.h
		extensions/PxConstraintExt.h
		extensions/PxCollectionExt.h
		extensions/PxBroadPhaseExt.h
		extensions/PxBinaryConverter.h

		cudamanager/PxCudaMemoryManager.h
		cudamanager/PxCudaContextManager.h

		cooking/PxTriangleMeshDesc.h
		cooking/PxMidphaseDesc.h
		cooking/PxCooking.h
		cooking/PxConvexMeshDesc.h
		cooking/Pxc.h
		cooking/PxBVHStructureDesc.h
		cooking/PxBVH34MidphaseDesc.h
		cooking/PxBVH33MidphaseDesc.h

		common/PxTypeInfo.h
		common/PxTolerancesScale.h
		common/PxStringTable.h
		common/PxSerializer.h
		common/PxSerialFramework.h
		common/PxRenderBuffer.h
		common/PxProfileZone.h
		common/PxPhysXCommonConfig.h
		common/PxPhysicsInsertionCallback.h
		common/PxMetaDataFlags.h
		common/PxMetaData.h
		common/PxCoreUtilityTypes.h
		common/PxCollection.h
		common/PxBase.h

		collision/PxCollisionDefs.h

		characterkinematic/PxExtended.h
		characterkinematic/PxControllerObstacles.h
		characterkinematic/PxControllerManager.h
		characterkinematic/PxControllerBehavior.h
		characterkinematic/PxController.h
		characterkinematic/PxCapsuleController.h
		characterkinematic/PxBoxController.h
		)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/physx/include)
target_include_directories(${LibName} PRIVATE ${nvidiagameworks_physx_SOURCE_DIR}/pxshared/include)

set(PHYSX_SOURCE
		${_pxsrc}/task/src/TaskManager.cpp
		${_pxsrc}/${PHYSX_SOURCE_SIMULATION_CONTROLLER}
		${_pxsrc}/${PHYSX_SOURCE_SCENE_QUERY}
		${_pxsrc}/${PHYSX_SOURCE_PVD}
		${_pxsrc}/${PHYSX_SOURCE_PHYSXVEHICLE}
		${_pxsrc}/${PHYSX_SOURCE_PHYSXMETADATA}
		${_pxsrc}/${PHYSX_SOURCE_PHYSXGPU}
		${_pxsrc}/${PHYSX_SOURCE_PHYSXEXTENSIONS}
		${_pxsrc}/${PHYSX_SOURCE_PHYSX}
		#		${_pxsrc}/${PHYSX_SOURCE_PHYSXCOOKING}
		${_pxsrc}/${PHYSX_SOURCE_PHYSXCHARACTERKINIMATRIC}
		${_pxsrc}/${PHYSX_SOURCE_LOWLEVELDYNAMICS}
		${_pxsrc}/${PHYSX_SOURCE_LOWLEVELAABB}
		${_pxsrc}/${PHYSX_SOURCE_LOWLEVEL}
		${_pxsrc}/${PHYSX_SOURCE_IMMEDIATEMODE}
		${_pxsrc}/${PHYSX_SOURCE_GEOMUTILS}
		${_pxsrc}/${PHYSX_SOURCE_FOUNDATION}
		${_pxsrc}/${PHYSX_SOURCE_FILEBUF}
		${_pxsrc}/${PHYSX_SOURCE_FASTXML}
		${_pxsrc}/${PHYSX_SOURCE_COMMON}
		)

set(_pxsrcs)
foreach (_pxsrc ${PHYSX_SOURCE})
	list(APPEND _pxsrcs ${nvidiagameworks_physx_SOURCE_DIR}/physx/source/${_pxsrc})
endforeach ()
set(_pxincs)
foreach (_pxinc ${PHYSX_INCLUDE})
	list(APPEND _pxincs ${nvidiagameworks_physx_SOURCE_DIR}/physx/include/${_pxinc})
endforeach ()

target_sources(${LibName} PRIVATE ${_pxsrcs})
target_sources(${LibName} PRIVATE ${_pxincs})
