#include <RED4ext/Common.hpp>
#include "ScriptDefinitions/ScriptDefinitions.hpp"

namespace ModSettings {

// ScriptBundle, 2.5 layout (a pointer was added at the start)
struct ScriptData {
  void *unk00; // 00 - added in 2.5
  RED4ext::HashMap<uint64_t, uint64_t> unk08; // 08 - definitions by name
  RED4ext::HashMap<uint64_t, uint64_t> unk38; // 38 - functions by name
  RED4ext::HashMap<uint64_t, uint64_t> unk68; // 68 - types by name
  RED4ext::DynArray<void *> files; // 98
  RED4ext::DynArray<void *> functions; // A8
  RED4ext::DynArray<void *> enums; // B8
  RED4ext::DynArray<void *> unkC8; // C8 - bitfields
  RED4ext::DynArray<ScriptClass *> classes; // D8
  RED4ext::DynArray<void *> types; // E8
  RED4ext::DynArray<RED4ext::CString> strings; // F8
};
RED4EXT_ASSERT_OFFSET(ScriptData, classes, 0xD8);

}