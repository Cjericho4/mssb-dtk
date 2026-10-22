#include "Unknown/File_0x800a64e0.h"
#include "Dolphin/os.h"

typedef struct
{
    OSThread t ATTRIBUTE_ALIGN(16);       // 0x000
    OSSemaphore s[2] ATTRIBUTE_ALIGN(16); // 0x320

    int BytesToRead;          // 0x338
    size_t CachedBytesToRead; // 0x33C
    int volatile ReadOffset;  // 0x340
    u32 bitBuffer;            // 0x344
    u8 * volatile DataWriteBottom;      // 0x348
    u8 *DataReadBottom;       // 0x34C
    u8 *CachedDataReadBottom; // 0x350
    void *DataReadTop;        // 0x354
    u8 * volatile DataWriteTop;         // 0x358
    int _35C;                 // 0x35C

    s8 volatile segmentCount; // 0x360
    u8 BitsInBuffer;          // 0x361
    u8 LookBackSize;          // 0x362
    u8 RepetitionSize;        // 0x363
    u8 error;                 // 0x364
    s8 compressedFlag;        // 0x365
    u8 ShouldWriteDataFlag;   // 0x366
} DataVars;

DataVars gDataDecompressorValues;

#define LZSS_FLAG_SIZE 1
#define LZSS_BYTE_SIZE 8
#define LZSS_MINIMUM_REPETITION_SIZE 2

/*================================================================================*/

#define STRUCT_OFFSET(structName, memberField) \
    (size_t)(&((structName *)NULL)->memberField)

/*================================================================================*/

void SetReadParameters(AssetLoadInstructions *instructions, void *pCompressedData, void *pOutData, BOOL readInSegments)
{
    uint segmentSize;

    gDataDecompressorValues.RepetitionSize = instructions->compressionConstants >> 8;
    gDataDecompressorValues.LookBackSize = instructions->compressionConstants & 0xff;
    gDataDecompressorValues.CachedBytesToRead = gDataDecompressorValues.BytesToRead = instructions->originalDiskSize;

    if (!readInSegments)
    {
        segmentSize = ALIGN_NEXT(instructions->compressedSize, 32);
        gDataDecompressorValues.segmentCount = -1;
    }
    else
    {
        segmentSize = 0x20000;
        gDataDecompressorValues.segmentCount = 0;
    }

    // Set the top of the and bottom of the write to the same output
    gDataDecompressorValues.DataWriteBottom = pOutData;
    gDataDecompressorValues.DataWriteTop =  pOutData;
    gDataDecompressorValues.DataReadBottom = gDataDecompressorValues.CachedDataReadBottom = pCompressedData;

    gDataDecompressorValues.DataReadTop = (u8 *)pCompressedData + segmentSize;
    gDataDecompressorValues.error = 0;
    gDataDecompressorValues.ReadOffset = 0;
    gDataDecompressorValues.BitsInBuffer = 0;
    gDataDecompressorValues.bitBuffer = 0;
    gDataDecompressorValues.compressedFlag = instructions->compressionFlag;
    gDataDecompressorValues.ShouldWriteDataFlag = TRUE;
    OSResumeThread(&gDataDecompressorValues.t);
    return;
}

/*================================================================================*/

extern u8 myStack[2][0x1000];

void StartThreadForReadingFromDisk()
{
    OSCreateThread(&gDataDecompressorValues.t, ReadDataFromDisk, NULL, myStack[1], sizeof(myStack[1]), 0x1f, 1);
    OSResumeThread(&gDataDecompressorValues.t);
}

/*================================================================================*/

void *ReadDataFromDisk(void *)
{
    OSInitSemaphore(gDataDecompressorValues.s, 3);
    while (1)
    {
        gDataDecompressorValues.ShouldWriteDataFlag = FALSE;
        OSSuspendThread(&gDataDecompressorValues.t);

        switch (gDataDecompressorValues.compressedFlag - 1)
        {
        case 0:
            DecompressDiskData();
            break;
        }
    }
}

/*================================================================================*/

/* DecompressDiskData -- LZSS-expand the current disc read segment (Namco-style bit stream).
 *
 * Uses gDataDecompressorValues (0x803C....: set up by SetReadParameters): BitsInBuffer/ReadBits
 * stream, DataWriteBottom (0x348) start of the output buffer, DataWriteTop (0x358) write cursor,
 * BytesToRead (0x338) bytes still to produce, LookBackSize (0x362) / RepetitionSize (0x363) bit
 * widths from the file's compressionConstants, error (0x364).
 * Each token is a 1-bit flag: 1 -> one literal byte (8 bits); 0 -> a back-reference of
 * (ReadBits(LookBackSize) + 1) bytes back, (ReadBits(RepetitionSize) + 2) bytes long, copied byte
 * by byte (overlap allowed).  A reference that would run before the buffer start or past the
 * expected size sets error = 1 and stops.  Returns when BytesToRead reaches 0.
 * Chain position: every character subfile / master descriptor loaded through ARAMTransfer with the
 * 0x40000000 "compressed" bit passes through here before fn_80017814 relocates it; a modded file
 * must be re-packed with this scheme (or stored uncompressed).
 * Match status: NOT matched -- 31 lines: the retail build saves r27..r31 (stmw) with only r27/r31 used, uses a
 * ctr loop for the copy (a for loop gets unrolled here, a do-while compiles to subic./bne) and re-
 * materialises the global address in the error path; semantics identical. */
void DecompressDiskData(void)
{
    u32 lookBack;
    u32 repetition;
    u8 *dst;
    DataVars *v = &gDataDecompressorValues;

    while (TRUE)
    {
        if (ReadBits(LZSS_FLAG_SIZE))
        {
            *v->DataWriteTop++ = ReadBits(LZSS_BYTE_SIZE);
            v->BytesToRead--;
        }
        else
        {
            lookBack = ReadBits(v->LookBackSize) + 1;
            repetition = ReadBits(v->RepetitionSize) + LZSS_MINIMUM_REPETITION_SIZE;
            v->BytesToRead -= repetition;
            if (v->BytesToRead < 0 | &v->DataWriteTop[-lookBack] < v->DataWriteBottom)
            {
                break;
            }
            dst = v->DataWriteTop;
            do
            {
                *dst = dst[-lookBack];
                dst++;
            } while (--repetition != 0);
            v->DataWriteTop = dst;
        }
        if (v->BytesToRead == 0)
        {
            return;
        }
    }
    v->error = 1;
}

/*================================================================================*/

u32 ReadBits(u32 bits)
{
    u32 bitsNeededToRead;
    int interrupts;
    u8 bitsForNextBuffer;
    u32 toReturn;

    if (gDataDecompressorValues.BitsInBuffer >= bits)
    {
        // we have enough bits in the buffer, just cycle them out
        gDataDecompressorValues.BitsInBuffer -= bits;
        // push out the top bits, and then move back to just hold the bottom bits, worse than a mask? maybe faster for cpu
        toReturn = gDataDecompressorValues.bitBuffer << (32 - bits) >> (32 - bits);
        gDataDecompressorValues.bitBuffer >>= bits;
    }
    else
    {
        // not enough bits, figure out how many we need
        bitsNeededToRead = bits - gDataDecompressorValues.BitsInBuffer;
        // the bits left in our buffer will be the top bits of our value
        toReturn = gDataDecompressorValues.bitBuffer << bitsNeededToRead;

        // make sure we have valid data?
        while (!gDataDecompressorValues.ReadOffset && !gDataDecompressorValues.segmentCount)
        {
            // nop
        }

        // read a new u32 into our buffer
        gDataDecompressorValues.bitBuffer = *(u32 *)&gDataDecompressorValues.DataReadBottom[gDataDecompressorValues.ReadOffset];
        // how many bits our next buffer will hold after we remove the rest of the current data
        bitsForNextBuffer = 32 - bitsNeededToRead;
        // push out most of the new bits, and be left with bottom bits of the buffer
        // `or` it into the result
        toReturn |= (gDataDecompressorValues.bitBuffer << bitsForNextBuffer) >> bitsForNextBuffer;

        // update the bit variables
        gDataDecompressorValues.BitsInBuffer = bitsForNextBuffer;
        // cycle out the used bits
        gDataDecompressorValues.bitBuffer >>= bitsNeededToRead;
        // update the read offset
        gDataDecompressorValues.ReadOffset += sizeof(u32);

        // if we've read a full 32Kb
        if (gDataDecompressorValues.ReadOffset == 0x8000)
        {
            // update the read offset by moving the bottom pointer
            gDataDecompressorValues.ReadOffset = 0;
            gDataDecompressorValues.DataReadBottom += 0x8000;
            // If we've read too far, reset the pointer to the bottom of the array
            if (gDataDecompressorValues.DataReadBottom == gDataDecompressorValues.DataReadTop)
            {
                gDataDecompressorValues.DataReadBottom = gDataDecompressorValues.CachedDataReadBottom;
            }
            // signal a thread to update the cache of data to read
            interrupts = OSDisableInterrupts();
            gDataDecompressorValues.segmentCount--;
            OSSignalSemaphore(&gDataDecompressorValues.s);
            OSRestoreInterrupts(interrupts);
        }
    }
    return toReturn;
}

/*================================================================================*/
