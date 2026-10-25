#pragma once

#include "RED4ext/RTTITypes.hpp"
#include <RED4ext/RED4ext.hpp>

namespace ModSettings {

struct ScriptProperty;

enum class EDefinitionType : char {
  Type = 0x0,
  Class = 0x1,
  Constant = 0x2,
  Enum = 0x3,
  Bitfield = 0x4,
  Function = 0x5,
  Parameter = 0x6,
  LocalVar = 0x7,
  Property = 0x8,
  SourceFile = 0x9,
};

enum class EScriptType : long {
  Simple = 0x0,
  Cls = 0x1,
  Handle = 0x2,
  WeakHandle = 0x3,
  Array = 0x4,
  NativeArray = 0x5
};

enum class EVisibility : char {
  Public = 0x0,
  Protected = 0x1,
  Private = 0x2,
};

struct ScriptClass;

struct ScriptDefinition {
  virtual RED4ext::Memory::IAllocator *dstr() = 0;
  virtual void sub_08() = 0;
  virtual EDefinitionType GetDefinitionType() = 0;
  virtual EVisibility GetVisibility() = 0;
  virtual ScriptClass GetParent() = 0;
  virtual void sub_28() = 0;
  virtual bool IsNative() = 0;

  RED4ext::CName name; // 08
  uint64_t unk10; // 10
  uint8_t unk18[0x28]; // 18 - added in 2.5
};
RED4EXT_ASSERT_SIZE(ScriptDefinition, 0x40);

struct ScriptType : ScriptDefinition {
  RED4ext::CBaseRTTIType *rttiType; // 40
  ScriptClass *innerType; // 48
  uint32_t unk50; // 50 - array size
  EScriptType type; // 54
};
RED4EXT_ASSERT_OFFSET(ScriptType, innerType, 0x48);

struct ScriptClassFlags {
  uint32_t isNative : 1;
  uint32_t isAbstract : 1;
  uint32_t isFinal : 1;
  uint32_t isStruct : 1;
  uint32_t hasFunctions : 1;
  uint32_t hasFields : 1;
  uint32_t isImportOnly : 1;
  uint32_t isTestOnly : 1;
  uint32_t hasOverrides : 1;
  uint32_t unk200 : 1;
  uint32_t unk400 : 1;
};

// 2.5 layout, matches psiberx/cp2077-codeware src/Red/ScriptBundle.hpp
struct ScriptClass : ScriptDefinition {
  RED4ext::CClass *rttiType; // 40
  ScriptClass *parent; // 48
  RED4ext::DynArray<ScriptProperty *> properties; // 50
  RED4ext::DynArray<void *> overrides; // 60
  uint8_t unk70[0x20]; // 70 - added in 2.5
  RED4ext::DynArray<void *> functions; // 90
  RED4ext::HashMap<RED4ext::CName, RED4ext::CString> unkA0; // A0 - attributes
  uint8_t visibility; // D0
  uint8_t flags; // D1
};
RED4EXT_ASSERT_OFFSET(ScriptClass, parent, 0x48);
RED4EXT_ASSERT_OFFSET(ScriptClass, properties, 0x50);
RED4EXT_ASSERT_OFFSET(ScriptClass, functions, 0x90);
RED4EXT_ASSERT_OFFSET(ScriptClass, flags, 0xD1);
// char (*__kaboom)[offsetof(ScriptClass, rttiType)] = 1;

}