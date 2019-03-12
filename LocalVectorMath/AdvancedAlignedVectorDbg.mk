WIN_DEFS = -DWIN32 -D_WIN32 -D_DLL -D_X86=1 -D_WIN32_IE=0x0600 -DWINVER=0x0400
DEBUG_FLAGS = -Zi -Od -DDEBUG

C_FLAGS = -nologo -c -MT -LD -W3 -I. -D__BUILD_LIBRARY -D__ADVANCED_ALIGNED_LIB
CFLAGS	= $(WIN_DEFS) $(C_FLAGS) $(DEBUG_FLAGS)

ASM_FLAGS = -fwin32 -D__BUILD_ADVANCED_ALIGNED_LIB

LNKFLAGS = /INCREMENTAL:NO /PDB:NONE /RELEASE /NOLOGO /NODEFAULTLIB
LNKOPT0 = -dll -def:$*.def
LNKOPT1 = -implib:$*.lib  -map:$*.map
LNKOPTS = $(LNKOPT0) $(LNKOPT1)

LIBFLGS = $(LNKFLAGS) -dll $(LNKOPT1)

LINK = link
CC   = cl
RC   = rc
ASM  = nasmw
MT   = mt

DLL     = AdvancedAlignedVectorDbg
DLL1    = CAdvancedAlignedVectorDbg

ASRCS = VectorAsm.asm
AOBJS = VectorAsm.obj

SRCS = DllMain.c
OBJS = DllMain.obj

CPPSRCS = CVector.cpp \
	  FlatBuffer.cpp
CPPOBJS = CVector.obj \
	  FlatBuffer.obj

.asm.obj:
  @$(ASM) $(ASM_FLAGS) $*.asm

.c.obj:
  @$(CC) $(CFLAGS) $*.c

.cpp.obj:
  @$(CC) $(CFLAGS) $*.cpp

all: $(DLL).dll $(DLL1).dll $(DLLDBG).dll $(DLL1DBG).dll $(AOBJS) $(OBJS) $(SRCS)

$(AOBJS) : $(ASRCS)

$(OBJS) : $(SRCS)

$(DLL).dll : $(OBJS) $(AOBJS)
  @$(LINK) $(LNKFLAGS) $(LNKOPTS) $(OBJS) $(AOBJS) msvcrt.lib kernel32.lib
  @$(MT) -nologo -manifest $(DLL).dll.manifest -outputresource:$(DLL).dll;2

$(DLL1).dll: $(CPPOBJS) $(OBJS)
  @$(LINK) $(LIBFLGS) -out:$(DLL1).dll $(CPPOBJS) $(OBJS) $(DLL).lib msvcrt.lib kernel32.lib
  @$(MT) -nologo -manifest $(DLL1).dll.manifest -outputresource:$(DLL1).dll;2

clear:
	@if exist *.exp del *.exp
	@if exist *.map del *.map
	@if exist *.obj del *.obj

clean:
  @if exist *.obj del *.obj
  @if exist *.bsc del *.bsc
  @if exist *.dsp del *.dsp
  @if exist *.dsw del *.dsw
  @if exist *.exe del *.exe
  @if exist *.exp del *.exp
  @if exist *.map del *.map
  @if exist *.mdp del *.mdp
  @if exist *.ncb del *.ncb
  @if exist *.opt del *.opt
  @if exist *.pch del *.pch
  @if exist *.pdb del *.pdb
  @if exist *.plg del *.plg
  @if exist *.res del *.res
  @if exist *.res del *.sbr
  @if exist *.vcp del *.vcp
  @if exist *.ilk del *.ilk
  @if exist *~ del *~
  @if exist "#"* del "#"*
  @if exist resource.h del resource.h
  @if exist $(TDIR) rd /q/s $(TDIR)
  @if exist debug rd /q/s debug
  @if exist release rd /q/s release

# Target to clean up all generated files.
cleanall:
  -del *.aps
  -del *.bsc
  -del *.dll
  -del *.dsp
  -del *.dsw
  -del *.exe
  -del *.exp
  -del *.lib
  -del *.mak
  -del *.map
  -del *.mdp
  -del *.ncb
  -del *.obj
  -del *.opt
  -del *.pch
  -del *.pdb
  -del *.plg
  -del *.res
  -del *.sbr
  -del *.vcp
  -del resource.h
  -deltree /y $(TDIR)
  -rmdir /s /q $(TDIR)
  -deltree /y debug
  -rmdir /s /q debug
  -deltree /y release
  -rmdir /s /q release

setup:
  @if exist *.obj del *.obj
