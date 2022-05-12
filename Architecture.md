# What A Strange Processor - Architecture

## Constants

### OP 1

| Value (Hex) | Name             |
|:-----------:|:-----------------|
|      0      | No-op            |
|      1      | Add/Subtract     |
|      2      | Logic 1          |
|      3      | Logic 2          |
|      4      | Shift            |
|      5      | Rotate           |
|      6      | Memory Access    |
|      7      | Register Window  |
|      8      | Link Jump        |
|      9      | Conditional Jump |
|      A      | Load Immediate   |
|      B      | Reserved         |
|      C      | Reserved         |
|      D      | Reserved         |
|      E      | Reserved         |
|      F      | Halt             |

### Registers

| Address (Hex) | Mnemonic | Description              |
|:-------------:|:--------:|:-------------------------|
|      00       |  `$g0`   | Global 0                 |
|      01       |  `$g1`   | Global 1                 |
|      02       |  `$g2`   | Global 2                 |
|      03       |  `$g3`   | Global 3                 |
|      04       |  `$g4`   | Global 4                 |
|      05       |  `$g5`   | Global 5                 |
|      06       |  `$g6`   | Global 6                 |
|      07       |  `$g7`   | Global 7                 |
|      08       |  `$i0`   | Input 0                  |
|      09       |  `$i1`   | Input 1                  |
|      0A       |  `$i2`   | Input 2                  |
|      0B       |  `$i3`   | Input 3                  |
|      0C       |  `$i4`   | Input 4                  |
|      0D       |  `$i5`   | Input 5                  |
|      0E       |  `$i6`   | Input 6                  |
|      0F       |  `$i7`   | Input 7                  |
|      10       |  `$l0`   | Local 0                  |
|      11       |  `$l1`   | Local 1                  |
|      12       |  `$l2`   | Local 2                  |
|      13       |  `$l3`   | Local 3                  |
|      14       |  `$l4`   | Local 4                  |
|      15       |  `$l5`   | Local 5                  |
|      16       |  `$l6`   | Local 6                  |
|      17       |  `$l7`   | Local 7                  |
|      18       |  `$o0`   | Output 0                 |
|      19       |  `$o1`   | Output 1                 |
|      1A       |  `$o2`   | Output 2                 |
|      1B       |  `$o3`   | Output 3                 |
|      1C       |  `$o4`   | Output 4                 |
|      1D       |  `$05`   | Output 5                 |
|      1E       |  `$06`   | Output 6                 |
|      1F       |  `$o7`   | Output 7                 |
|      20       |  `$l8`   | Local 8                  |
|      21       |  `$l9`   | Local 9                  |
|      22       |  `$l10`  | Local 10                 |
|      23       |  `$l11`  | Local 11                 |
|      24       |  `$l12`  | Local 12                 |
|      25       |  `$l13`  | Local 13                 |
|      26       |  `$l14`  | Local 14                 |
|      27       |  `$l15`  | Local 15                 |
|      28       |  `$bor`  | Bitwise OR               |
|      29       | `$band`  | Bitwise AND              |
|      2A       | `$bxor`  | Bitwise XOR              |
|      2B       | `$bnot`  | Bitwise NOT              |
|      2C       | `$bnor`  | Bitwise NOR              |
|      2E       | `$bnand` | Bitwise NAND             |
|      2F       |  `$blz`  | Leading zero bits        |
|      30       | `$bpop`  | Population count         |
|      31       |  `$icc`  | Integer condition codes  |
|      32       |          | Reserved                 |
|      33       |          | Reserved                 |
|      34       |          | Reserved                 |
|      35       |          | Reserved                 |
|      36       |          | Reserved                 |
|      37       |          | Reserved                 |
|      38       |          | Reserved                 |
|      39       |          | Reserved                 |
|      3A       |          | Reserved                 |
|      3B       |  `$pc`   | Program counter          |
|      3C       |  `$npc`  | Next program counter     |
|      3D       |  `$psr`  | Processor state register |
|      3E       |  `$c0`   | Constant 0x00000000      |
|      3F       |  `$c1`   | Constant 0xFFFFFFFF      |

## Instructions

All instructions are 32 bytes (4 bytes), and include the opcode in the upper
four bits. The meaning of the remaining bits varies based on the opcode.

### No-op

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 0     | 0                                                     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

### Add/Subtract

Register version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 1     |0|A|C| <unused>    | Reg 1     | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Add (A): If 0, `Rd := R1 - R2`. If 1, `Rd := R1 + R2`.
* Condition (C): If 1, `$icc` will be updated. If 0, `$icc` will not be modified.
* Reg 1: Addend
* Reg 2: Addend
* Reg Dest: Destination

Immediate version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 1     |1|A|C| Immediate               | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Add (A): If 0, `Rd := Immediate - R2`. If 1, `Rd := Immediate + R2`.
* Condition (C): If 1, `$icc` will be updated. If 0, `$icc` will not be modified.
* Immediate: Addend
* Reg 2: Addend
* Reg Dest: Destination

### Logic 1

Register version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 2     |0| T | <unused>    | Reg 1     | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Type (T): Which logic type (`$bor + T`) to store in the destination
* Reg 1: Input 1
* Reg 2: Input 2
* Reg Dest: Destination

Immediate version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 2     |1| T | Immediate               | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Type (T): Which logic type (`$bor + T`) to store in the destination
* Immediate: Input 1
* Reg 2: Input 2
* Reg Dest: Destination

### Logic 2

Register version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 3     |0| T | <unused>    | Reg 1     | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Type (T): Which logic type (`$bnor + T`) to store in the destination
* Reg 1: Input 1
* Reg 2: Input 2
* Reg Dest: Destination

Immediate version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 3     |1| T | Immediate               | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Type (R): Which logic type (`$bnor + T`) to store in the destination
* Immediate: Input 1
* Reg 2: Input 2
* Reg Dest: Destination

### Shift

Register version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 4     |0|E|R| <unused>    | Reg 1     | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Extend (E): If 0, the new bit will be 0. If 1, the new bit will be a copy of its neighbor.
* Right (R): If 0, perform a left shift. If 1, perform a right shift.
* Reg 1: Value to be shifted
* Reg 2: Number of bits to shift
* Reg Dest: Destination

Immediate version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 4     |1|E|R| Immediate               | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Extend (E): If 0, the new bit will be 0. If 1, the new bit will be a copy of its neighbor.
* Right (R): If 0, perform a left shift. If 1, perform a right shift.
* Immediate: Value to be shifted
* Reg 2: Number of bits to shift
* Reg Dest: Destination

### Rotate

Register version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 5     |0|U|R| <unused>    | Reg 1     | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Unused (U)
* Right (R): If 0, perform a left rotate. If 1, perform a right rotate.
* Reg 1: Value to be rotated
* Reg 2: Bits to rotate
* Reg Dest: Destination

Immediate version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 5     |1|U|R| Immediate               | Reg 2     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

* Unused (U)
* Right (R): If 0, perform a left rotate. If 1, perform a right rotate.
* Immediate: Value to be rotated
* Reg 2: Bits to rotate
* Reg Dest: Destination

### Memory

Read version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 6     |0|0| <unused>                  | Reg Trg   | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Target (Reg Trg): Memory address to read from
* Reg Dest: Destination

Write register version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 6     |0|1| <unused>                  | Reg Val   | Reg Trg   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Value (Reg Val): Value to write
* Target (Reg Trg): Memory address to write to

Write immediate version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 6     |1|1| Immediate                             | Reg Trg   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Immediate: Value to write
* Target (Reg Trg): Memory address to write to

### Register Windows

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 7     |A| <unused>                    | Dest Prev | Dest Cur  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Advance (A): If 0, reduce the register window index by 1. If 1, increase the register window index by 1. Both operations may overflow (seen in `$icc`).
* Dest Prev: Previous register window index will be stored in this register
* Dest Cur: Current register window index will be stored in this register

### Link Jumps

Register version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 8     |0|R| <unused>                  | Reg 1     | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Relative (R): If 0, jump is absolute. If 1, jump is relative to `$npc`.
* Reg 1: Address or offset to jump to
* Reg Dest: Destination; `Dest := $npc + 4`

Immediate version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 8     |1|R| Immediate                             | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Relative (R): If 0, jump is absolute. If 1, jump is relative to `$npc`.
* Immediate: Address or offset to jump to
* Reg Dest: Destination; `Dest := $npc + 4`

### Conditional Jumps

Register version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 8     |0|R|A| <unused>    | Reg 1     | Type      | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Relative (R): If 0, jump is absolute. If 1, jump is relative to `$npc`.
* Annul (A): If 0, the instruction at `$npc` is executed before jumping. If 1, a no-op is performed before jumping instead.
* Reg 1: Address or offset to jump to
* Type: Which bit in `$icc` to compare against
* Reg Dest: Destination; `Dest := $npc + 4`

Immediate version:

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 9     |0|R|A| Immediate               | Type      | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Relative (R): If 0, jump is absolute. If 1, jump is relative to `$npc`.
* Annul (A): If 0, the instruction at `$npc` is executed before jumping. If 1, a no-op is performed before jumping instead.
* Immediate: Address or offset to jump to
* Type: Which bit in `$icc` to compare against
* Reg Dest: Destination; `Dest := $npc + 4`

### Load Immediate

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 10    | Immediate                                 | Reg Dest  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

where:

* Immediate: Value to load
* Reg Dest: Destination

### Halt

```
   3                   2                   1                   0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 15    | <unused>                                              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
