#include "syati.h"
#include "XanimeResourceTableExt.h"

// A nightmare.
// Read at your own risk. Modifying? Ha.

extern "C" {
    int __kAutoMap_8006E840(int* src, int**, const char*, u32);
    u32 __kAutoMap_8002BD00(const char* pStr);
	void __kAutoMap_8006E4E0(XanimeGroupInfo* pInfo);
}

// TRIPLE TABLE
asm void redirTripleAnimeTable() {
    lis r9, extTripleAnimeTable@ha
    addi r9, r9, extTripleAnimeTable@l
    blr
}

kmCall(0x803DFDB0, redirTripleAnimeTable);




// PARENT TABLE

asm void detectEndOfParentTable() {
    lwzx r3, r17, r31
    add r24, r17, r31

    lwz r0, 8(r24)
    cmpwi r0, 0xFF
    bne origcheck
    b replace

    origcheck:
    lbz r0, 0(r3)
    extsb. r0, r0
    b end

    replace:
    li r31, 0
    lis r17, cNewGroupInfos@ha
    addi r17, r17, cNewGroupInfos@l
    lwzx r3, r17, r31
    add r24, r17, r31
    cmpw r24, r25 // !
    end:
    blr
}
kmWrite32(0x8006EA94, PPC_B(0xC));
kmCall(0x8006EAA0, detectEndOfParentTable);
kmWrite32(0x806D29F8, 0xFF);


void redirGroupInfoHashTable(int* pThis, XanimeGroupInfo* tbl) {
    bool swap = false;
    u32 count;
    asm("lwz %0, 0x4(%1)" : "=r" (count) : "=r" (pThis));
    
    HashSortTable* pTable = 0;
    asm("lwz %0, 0x68(%1)" : "=r" (pTable) : "=r" (pThis));
    
    for (int idx = 0; idx < count; idx++) {
        u32 hash = 0;

        hash = tbl[idx]._40;
        if ((tbl[idx+1]._8) == 0xFF)
            swap = true;

        if (idx >= count-gGroupInfosEnries && swap) {
            XanimeGroupInfo* entry = &cNewGroupInfos[idx-(count-gGroupInfosEnries)];
            hash = entry->_40;
            OSReport("%s [%X]\n", entry->mParent.animationName, hash);
        }

        pTable->add(hash, idx);
    }
}
kmWrite32(0x8006EFB0, PPC_MR(3, 29));
kmWrite32(0x8006EFB4, PPC_LWZ(4, 0x10, 29));
kmCall(0x8006EFB8, redirGroupInfoHashTable);

asm void getGroupInfoReferNewTable() {
    li r6, 0
    li r8, 0
    lwz r4, 0x10(r30)

    loop:
    mulli r0, r8, 0x48
    add r7, r4, r0

    lwz r5, 0x8(r7)
    cmpwi r5, 0xFF
    bne skipreplace

    lis r4, cNewGroupInfos@ha
    addi r4, r4, cNewGroupInfos@l
    li r8, 0
    b loop

    skipreplace:
    cmpw r6, r3
    addi r6, r6, 1
    addi r8, r8, 1
    bne loop 

    exit:
    add r3, r4, r0
    blr
}
kmCall(0x8006E5E4, getGroupInfoReferNewTable);
kmWrite32(0x8006E5E8, PPC_NOP);
kmWrite32(0x8006E5EC, PPC_NOP);


// SINGLE TABLE
asm void redirSingleTable() {
    mflr r6
    b loopstart

    loop:
    lwzx r3, r3, r30
    lhz r0, 0(r3)
    cmpwi r0, 0xFF
    bne skipReplace
    li r30, 0
    lis r26, extSingleAnimeTable@ha
    addi r26, r26, extSingleAnimeTable@l
    lwzx r3, r26, r30

    skipReplace:
    lbz r0, 0(r3)
    extsb. r0, r0
    beq finish
    bl __kAutoMap_8002BD00
    add r7, r26, r30
    stw r3, 8(r7)
    lwz r3, 0x4(r7)
    bl __kAutoMap_8002BD00
    addi r29, r29, 1
    addi r30, r30, 0x10
    stw r3, 0xC(r7)

    loopstart:
    mr r3, r26
    cmpwi r3, 0
    bne loop

    finish:
    mtlr r6
    blr
}
kmCall(0x8006EEA0, redirSingleTable);
kmWrite32(0x8006EEA4, PPC_B(0x50));



static s32 gAnimLoadOff = -1; 
namespace {
    const u32 gZero = 0x00FF0000;
};

kmWritePointer(0x806CC920, &gZero);

int searchSingleAnimTables(int* pTable, int** ppTable, const char* pStr, u32 u) {
    bool search = __kAutoMap_8006E840(pTable, ppTable, pStr, u);;

    if (!search) {
        int* table = (int*)extSingleAnimeTable;
        search = __kAutoMap_8006E840(pTable, &table, pStr, u);

        if (search)
            return 2;
    }
    else {
        return 1;
    }
    
    return 0;
}


kmCall(0x8006EAFC, searchSingleAnimTables);

asm void moveRegs() {
    mr r5, r3
    cmpwi r5, 0
    blr
}
kmCall(0x8006EB00, moveRegs);

void resetCounter(XanimeGroupInfo* pInfo) {
    __kAutoMap_8006E4E0(pInfo);
    gAnimLoadOff = -1;
}
kmCall(0x8006EEFC, resetCounter);

asm void swapTable() {
    cmpwi r5, 2
    bne orig

    lis r4, extSingleAnimeTable@ha
    addi r4, r4, extSingleAnimeTable@l
    lis r5, gAnimLoadOff@ha
    addi r5, r5, gAnimLoadOff@l
    lwz r6, 0(r5)
    addi r6, r6, 1
    stw r6, 0(r5)
    mulli r5, r6, 0x10
    add r4, r4, r5
    stw r4, 0x18(r1);

    b end
    orig:
    lwz r4, 0x18(r1);
    
    end:
    blr
}
kmCall(0x8006EB10, swapTable);