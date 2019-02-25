WIN_DEFS = -DWIN32 -D_WIN32 -D_DLL -D_X86=1 -D_WIN32_IE=0x0600 -DWINVER=0x0400
CDEBUG_FLAGS = -Zi -Od -DDEBUG
CPPOPT_FLAGS = -Ot
C_FLAGS = -nologo -c -MD -I.

!IFDEF DEBUG
CFLAGS = $(WIN_DEFS) $(CDEBUG_FLAGS) $(C_FLAGS)
!ELSE
CFLAGS = $(WIN_DEFS) $(CPPOPT_FLAGS) $(C_FLAGS)
!ENDIF

LNKFLAGS = /INCREMENTAL:NO /PDB:NONE /NOLOGO /NODEFAULTLIB

!IFDEF DEBUG
LIBFLGS = $(LNKFLAGS) /DEBUG
AAVLIBS = CAdvancedAlignedVectorDbg.lib VectorStdDbg.lib VectorAsm.lib msvcrtd.lib kernel32.lib
AUVLIBS = CAdvancedUnalignedVectorDbg.lib VectorStdDbg.lib VectorAsm.lib msvcrtd.lib kernel32.lib
AVLIBS  = CAlignedVectorDbg.lib VectorStdDbg.lib VectorAsm.lib msvcrtd.lib kernel32.lib
UVLIBS  = CUnalignedVectorDbg.lib VectorStdDbg.lib VectorAsm.lib msvcrtd.lib kernel32.lib
AAVLIB  = CAdvancedAlignedVectorDbg.lib msvcrtd.lib kernel32.lib
AVLIB   = CAlignedVectorDbg.lib msvcrtd.lib kernel32.lib
AUVLIB  = CAdvancedUnalignedVectorDbg.lib msvcrtd.lib kernel32.lib
UVLIB   = CUnalignedVectorDbg.lib msvcrtd.lib kernel32.lib
!ELSE
LIBFLGS = $(LNKFLAGS) /RELEASE
AAVLIBS = CAdvancedAlignedVector.lib VectorStd.lib VectorAsm.lib msvcrt.lib kernel32.lib
AUVLIBS = CAdvancedUnalignedVector.lib VectorStd.lib VectorAsm.lib msvcrt.lib kernel32.lib
AVLIBS  = CAlignedVector.lib VectorStd.lib VectorAsm.lib msvcrt.lib kernel32.lib
UVLIBS  = CUnalignedVector.lib VectorStd.lib VectorAsm.lib msvcrt.lib kernel32.lib
AAVLIB  = CAdvancedAlignedVector.lib msvcrt.lib kernel32.lib
AVLIB   = CAlignedVector.lib msvcrt.lib kernel32.lib
AUVLIB  = CAdvancedUnalignedVector.lib msvcrt.lib kernel32.lib
UVLIB   = CUnalignedVector.lib msvcrt.lib kernel32.lib
!ENDIF

LINK = link
CC   = cl
RC   = rc
MT   = mt

.c.obj:
  @$(CC) $(CFLAGS) $*.c

.cpp.obj:
  @$(CC) $(CFLAGS) $*.cpp

all: 	AdvancedAlignedRegression.exe \
	AdvancedUnalignedRegression.exe \
	AlignedRegression.exe \
	UnalignedRegression.exe \
	CAAVRegression.exe \
	CAVRegression.exe \
	CAUVRegression.exe \
	CUVRegression.exe

AdvancedAlignedRegression.obj   : AdvancedAlignedRegression.cpp
AdvancedUnalignedRegression.obj : AdvancedUnalignedRegression.cpp
AlignedRegression.obj           : AlignedRegression.cpp
UnalignedRegression.obj         : UnalignedRegression.cpp
CAAVRegression.exe              : CAAVRegression.cpp


AdvancedAlignedRegression.exe: AdvancedAlignedRegression.obj
  @$(LINK) $(LIBFLGS) AdvancedAlignedRegression.obj $(AAVLIBS)
  @$(MT) -nologo -manifest $@.manifest -outputresource:$@;1

AdvancedUnalignedRegression.exe: AdvancedUnalignedRegression.obj
  @$(LINK) $(LIBFLGS) AdvancedUnalignedRegression.obj $(AUVLIBS)
  @$(MT) -nologo -manifest $@.manifest -outputresource:$@;1

AlignedRegression.exe: AlignedRegression.obj
  @$(LINK) $(LIBFLGS) AlignedRegression.obj $(AVLIBS)
  @$(MT) -nologo -manifest $@.manifest -outputresource:$@;1

UnalignedRegression.exe: UnalignedRegression.obj
  @$(LINK) $(LIBFLGS) UnalignedRegression.obj $(UVLIBS)
  @$(MT) -nologo -manifest $@.manifest -outputresource:$@;1

CAAVRegression.exe: CAAVRegression.obj
  @$(LINK) $(LIBFLGS) CAAVRegression.obj $(AAVLIB)
  @$(MT) -nologo -manifest $@.manifest -outputresource:$@;1

CAVRegression.exe: CAVRegression.obj
  @$(LINK) $(LIBFLGS) CAVRegression.obj $(AVLIB)
  @$(MT) -nologo -manifest $@.manifest -outputresource:$@;1

CAUVRegression.exe: CAUVRegression.obj
  @$(LINK) $(LIBFLGS) CAUVRegression.obj $(AUVLIB)
  @$(MT) -nologo -manifest $@.manifest -outputresource:$@;1

CUVRegression.exe: CUVRegression.obj
  @$(LINK) $(LIBFLGS) CUVRegression.obj $(UVLIB)
  @$(MT) -nologo -manifest $@.manifest -outputresource:$@;1

clean:
	@if exist *.obj del *.obj
	@if exist *.manifest del *.manifest

cleanall:
	@if exist *.obj del *.obj
	@if exist *.manifest del *.manifest
	@if exist *.exe del *.exe

