/*!
 * @brief	プリコンパイル済みヘッダー。
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_
#define BOMBNUM 100
#define APPLENUM 100
#define WALLNUM 200
#define ENEMYNUM 100
#define DEBUFFNUM 100
#define ITEMBOXNUM 100
#define MAXHP 130
#define HEIGHT 2.0f

#include <windows.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "tkEngine/resource/tkSkinModelDataHandle.h"
#include "tkEngine/graphics/tkSkinModelMaterial.h"
#include "tkEngine/Physics/tkPhysics.h"
using namespace tkEngine;
#include "tkEngine/random/tkRandom.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

#endif // _STDAFX_H_