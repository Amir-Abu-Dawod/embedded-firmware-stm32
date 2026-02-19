# SVC Operation Dispatch (System Call Style)

Goal: use SVC as a system-call mechanism to execute operations in the SVC handler.

## What this experiment does
- User code invokes `SVC #imm` to request an operation (add/sub/mul/div)
- The SVC handler:
  - Decodes the SVC immediate from the calling instruction (using stacked PC)
  - Extracts arguments from the stacked frame (R0/R1)
  - Computes the result based on the SVC number
  - Writes the result back into stacked R0 for return to Thread mode

## ABI / Mechanism
- Arguments: R0 and R1 (AAPCS)
- Result: R0 (written into the stacked frame)
- Dispatch key: SVC immediate value (36–39)

## Notes / assumptions
- Handler uses MSP (`MRS R0, MSP`). If Thread mode uses PSP, EXC_RETURN decoding is required.
- Demo assumes valid inputs (e.g., division by zero is not handled).
- Output uses `printf`, requiring semihosting or `_write()` support.
