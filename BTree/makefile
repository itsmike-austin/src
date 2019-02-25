#WIN_DEFS = -DWIN32 -D_WIN32 -D_X86=1 -D_WIN32_IE=0x0600 -DWINVER=0x0400 -D_MT -D_REGRESSION_TESTING
WIN_DEFS = -DWIN32 -D_WIN32 -D_X86=1 -D_WIN32_IE=0x0600 -DWINVER=0x0400 -D_MT

DEBUG_FLAGS = -Zi -Od -DDEBUG

#C_FLAGS = -G6 -O2 -MD -LD -W3 -I.
C_FLAGS = -Zi -W3 -MD -I.

CC = cl

LNKFLAGS = /INCREMENTAL:NO /PDB:NONE /RELEASE /NOLOGO /NODEFAULTLIB /DEBUG
LNKOPT0 =
LNKOPT1 =
LNKOPTS = $(LNKOPT0) $(LNKOPT1)
LNKLIB0 = kernel32.lib  msvcirt.lib msvcrt.lib
LNKLIBS = $(LNKLIB0)

LINK = link

RC = rc

EXE = test

SRCS = $(EXE).cpp

OBJS = $(SRCS:.cpp=.obj)

all: $(EXE).exe $(OBJS)

$(OBJS) : $(SRCS)
  $(CC) $(WIN_DEFS) $(C_FLAGS) $(SRCS) $(LNKLIBS) /link $(LNKFLAGS)
#  $(CC) $(WIN_DEFS) $(C_FLAGS) $*.def $(SRCS) $(LNKLIBS) /link $(LNKFLAGS)
#  $(CC) $(WIN_DEFS) $(C_FLAGS) $(DEBUG_FLAGS) $(SRCS)


$(EXE).exe : $(OBJS)
  $(LINK) $(LNKFLAGS) $(LNKOPTS) $(OBJS) msvcrt.lib msvcirt.lib kernel32.lib

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

