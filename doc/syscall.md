# System Call ABI

## Inter-Process Messaging

All error code in this category, unless otherwise specified, has the following meanings:

+ 0 - No error
+ 1 - Invalid ID
+ 2 - Message box not initialized
+ 3 - Invalid meta info

---

### maxMsgBoxId

ID: 0

Returns the max id of message boxes.
Guaranteed to be not less than 7.

`[0, maxId]` is valid region of message box ids.

#### Parameters

None

#### Return Value

`eax`: (`int`) max id of message boxes

---

### initMsgBox

ID: 1

Initialize a message box.

#### Parameters
`eax`: (`int`) id
`ebx`: (`const MsgBoxInfo *`) meta info

`MsgBoxInfo` is a struct defined as this:
```C
struct MsgBoxInfo {
  void *memory; // must be 4-Byte aligned
  uint8_t msgSize;
  uint8_t msgMaxCount;
};
```

#### Return Value
`eax`: (`int`) error code (0, 1, 3)

---

### popMsg

ID: 2

Pop a message from a message box, and copy
it into the provided buffer

#### Parameters
`eax`: (`int`) id
`ebx`: (`void *`) buffer to put the message

#### Return Value
`eax`: (`int`) error code (0, 1, 2)

---

### isMsgBoxEmpty

ID: 3

Spot whether a message box is empty.
NOTE THAT from a user's perspective, this function may have
false positive. As other processes can send message right after
the finish of this syscall. However, if it says the message
box is NOT empty, there must exist at least one message
to be processed before calling another `popMsg`

#### Parameters
`eax`: (`int`) id

#### Return Value
`eax`: (`bool`) whether the message box is CURRENTLY empty

---

### closeMsgBox

ID: 4

Close a message box. Further messages can no longer
be delivered to it. Note that before returning the 
containing memory to kernel, you must firstly close
the message box. Otherwise, the memory can not be
returned.

#### Parameters
`eax`: (`int`) id

#### Return Value
`eax`: error code (0, 1, 2)

---

### moveMsgBox
ID: 5 

Move a message box to another location

#### Parameters
`eax`: (`int`) id
`ebx`: (`void *`) new memory location

#### Return Value

`eax`: (`int`) error code (0, 1, 2)

### send
ID: 6

Send a message

#### Parameters
`eax`: (`const Packet *`) packet

`Packet` is a struct defined as follows:
```C
struct Packet {
  int pid;
  int msgBoxId;
  void *message;
};
```

#### Return Value
`eax`: error code
This error code differs.

+ 0 - No error
+ 1 - Target does not exist
+ 2 - Target is full
