WIN_DEFS = -DWIN32 -D_WIN32 -D_DLL -D_X86=1 -D_WIN32_IE=0x0600 -DWINVER=0x0400
CDEBUG_FLAGS = -Zi -Od -DDEBUG
CPPOPT_FLAGS = -Ox
C_FLAGS = -nologo -c -MD -LD -W3 -I.

!IFDEF DEBUG
CFLAGS = $(WIN_DEFS) $(CDEBUG_FLAGS) $(C_FLAGS)
!ELSE
CFLAGS = $(WIN_DEFS) $(CPPOPT_FLAGS) $(C_FLAGS)
!ENDIF

LNKFLAGS = /INCREMENTAL:NO /PDB:NONE /NOLOGO /NODEFAULTLIB
LNKOPT0 = -dll -def:$*.def
LNKOPT1 = -implib:$*.lib  -map:$*.map
LNKOPTS = $(LNKOPT0) $(LNKOPT1)

!IFDEF DEBUG
LIBFLGS = $(LNKFLAGS) /DEBUG $(LNKOPTS)
!ELSE
LIBFLGS = $(LNKFLAGS) /RELEASE $(LNKOPTS)
!ENDIF

LINK = link
CC   = cl
RC   = rc
MT   = mt

DLL = VectorStd

!IFNDEF DEBUG
DLLOUT  = VectorStd
!ELSE
DLLOUT  = VectorStdDbg
!ENDIF

SRCS =  DllMain.c \
	VectorStd.c

OBJS =  DllMain.obj \
	VectorStd.obj

.c.obj:
  @$(CC) $(CFLAGS) $*.c

.cpp.obj:
  @$(CC) $(CFLAGS) $*.cpp

all: $(DLLOUT).dll $(OBJS) $(SRCS)

$(OBJS) : $(SRCS)

$(DLLOUT).dll : $(OBJS)
  @$(LINK) $(LIBFLGS) $(OBJS) msvcrt.lib kernel32.lib
  @$(MT) -nologo -manifest $(DLLOUT).dll.manifest -outputresource:$(DLLOUT).dll;2

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