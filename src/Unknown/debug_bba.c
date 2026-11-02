#include "mssbTypes.h"
#pragma section code_type ".init"
extern u8 Debug_BBA_803CBE10;
void __set_debug_bba(void) { Debug_BBA_803CBE10=1; }
u8 __get_debug_bba(void) { return Debug_BBA_803CBE10; }
