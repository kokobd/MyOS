#pragma once

#include <cstdint>

namespace myos::kernel::ipc {

#pragma pack (push, 1)
struct MsgBoxMetaInfo {
    void *memory;
    uint8_t msgSize;
    uint8_t msgMaxCount;
};
#pragma pack (pop)

}
