BITS 32
CPU  IA64

;;; * ------------- *
;;; * VectorAsm     *
;;; * --------------*-------------------------------------------------------- *
;;; *                                                                         *
;;; *                                                                         *
;;; *                                                                         *
;;; *                                                                         *
;;; *                                                                         *
;;; *                                                                         *
;;; *                                                                         *
;;; *                                                                         *
;;; *                                                                         *
;;; *                                                                         *
;;; * ----------------------------------------------------------------------- *
;;; *                                                                         *
;;; * ----------------------------------------------------------------------- *

;;; Setup the default defines
;;;

%ifdef __BUILD_ADVANCED_ALIGNED_LIB
  %define __BUILD_ADVANCED_ALIGNED_LIB   1
  %define __BUILD_ADVANCED_UNALIGNED_LIB 0
  %define __BUILD_ALIGNED_LIB            0
  %define __BUILD_UNALIGNED_LIB          0
  %define __BUILD_ALL                    0
%elifdef __BUILD_ADVANCED_UNALIGNED_LIB
  %define __BUILD_ADVANCED_ALIGNED_LIB   0
  %define __BUILD_ADVANCED_UNALIGNED_LIB 1
  %define __BUILD_ALIGNED_LIB            0
  %define __BUILD_UNALIGNED_LIB          0
  %define __BUILD_ALL                    0
%elifdef __BUILD_ALIGNED_LIB
  %define __BUILD_ADVANCED_ALIGNED_LIB   0
  %define __BUILD_ADVANCED_UNALIGNED_LIB 0
  %define __BUILD_ALIGNED_LIB            1
  %define __BUILD_UNALIGNED_LIB          0
  %define __BUILD_ALL                    0
%elifdef __BUILD_UNALIGNED_LIB
  %define __BUILD_ADVANCED_ALIGNED_LIB   0
  %define __BUILD_ADVANCED_UNALIGNED_LIB 0
  %define __BUILD_ALIGNED_LIB            0
  %define __BUILD_UNALIGNED_LIB          1
  %define __BUILD_ALL                    0
%elifdef __BUILD_ALL
  %define __BUILD_ADVANCED_ALIGNED_LIB   0
  %define __BUILD_ADVANCED_UNALIGNED_LIB 0
  %define __BUILD_ALIGNED_LIB            0
  %define __BUILD_UNALIGNED_LIB          0
  %define __BUILD_ALL                    1
%else
  %define __BUILD_ADVANCED_ALIGNED_LIB   0
  %define __BUILD_ADVANCED_UNALIGNED_LIB 0
  %define __BUILD_ALIGNED_LIB            0
  %define __BUILD_UNALIGNED_LIB          0
  %define __BUILD_ALL                    1
  %error No Build Specified
  %error Defaulting to __BUILD_ALL
%endif
		
;;; Define a few operational macros (porting aids) ...
;;;
;;; ... yes, of course these should be defined as non-intel specifics, but
;;;     the original was intel specific, so I'm not going to bother
;;;     with mods. I can use bison for fsm porting definition if I need
;;;     to later. ... m (8/10/99)
;;; 

%define SHUFFLE(r0, r1, r2, r3) (((r3) << 6) | ((r2) << 4) | ((r1) << 2) | (r0))
%define PtrSize     4

%define STACK_SAVE1 esp-4
%define STACK_SAVE2 esp-8
%define STACK_SAVE3 esp-12
%define STACK_SAVE4 esp-16
%define STACK_SAVE5 esp-20
%define STACK_SAVE6 esp-24
%define STACK_SAVE7 esp-28
%define STACK_SAVE8 esp-32
%define STACK_SAVE9 esp-36

%define SAVE_OFFSET_1  4
%define SAVE_OFFSET_2  8
%define SAVE_OFFSET_3 12
%define SAVE_OFFSET_4 16
%define SAVE_OFFSET_5 20
%define SAVE_OFFSET_6 24
%define SAVE_OFFSET_7 28

%define STACK_PTR1 esp+4
%define STACK_PTR2 esp+8
%define STACK_PTR3 esp+12
%define STACK_PTR4 esp+16
%define STACK_PTR5 esp+20
%define STACK_PTR6 esp+24
%define STACK_PTR7 esp+28
%define STACK_PTR8 esp+32

;;; Warning:	Use of Srcp/Dstp may require additional work
;;;		to assure correct pointers (es:di,ds:si)
;;;             Should not be an issue for linux ... not an issue
;;;             for Windows as long as you stay away from WFW and
;;;             old segmented models
;;; 
	
%define AReg eax
%define BReg ebx
%define CReg ecx
%define DReg edx
%define BPtr ebp
%define SPtr esp
%define Srcp esi
%define Dstp edi

%define FloatSize 4
%define Vec2Size  8 		; 2*sizeof(float)
%define Vec3Size 16		; 4*sizeof(float)
%define Vec4Size 16		; 4*sizeof(float)
%define Mat2Size 16		; 4*sizeof(float)
%define Mat3Size 36		; 3*sizeof(Vec3)
%define Mat4Size 48		; 4*sizeof(Vec4)

section .data data align=32

	negVec		dd	-1.0e0
			dd	-1.0e0
			dd	-1.0e0
			dd	-1.0e0

	oneVec		dd	1.0e0
			dd	1.0e0
			dd	1.0e0
			dd	1.0e0

	zeroVec		dd	0.0e0
			dd	0.0e0
			dd	0.0e0
			dd	0.0e0

	negateW		dd	1.0e0
			dd	1.0e0
			dd	1.0e0
			dd	-1.0e0

	quatInverse	dd	-1.0e0
			dd	-1.0e0
			dd	-1.0e0
			dd	1.0e0

	mat2Identity	dd	1.0e0
			dd	0.0e0
			dd	0.0e0
			dd	1.0e0

	mat3Identity	dd	1.0e0
			dd	0.0e0
			dd	0.0e0
			dd	0.0e0

			dd	0.0e0
			dd	1.0e0
			dd	0.0e0
			dd	0.0e0

			dd	0.0e0
			dd	0.0e0
			dd	1.0e0
			dd	0.0e0

	mat4Identity	dd	1.0e0
			dd	0.0e0
			dd	0.0e0
			dd	0.0e0

			dd	0.0e0
			dd	1.0e0
			dd	0.0e0
			dd	0.0e0

			dd	0.0e0
			dd	0.0e0
			dd	1.0e0
			dd	0.0e0

			dd	0.0e0
			dd	0.0e0
			dd	0.0e0
			dd	1.0e0

	twoVec		dd	2.0e0
			dd	2.0e0
			dd	2.0e0
			dd	2.0e0

	mirrorVec0	dd	1.0e0
			dd	0.0e0
			dd	0.0e0
			dd	0.0e0

	mirrorVec1	dd	0.0e0
			dd	1.0e0
			dd	0.0e0
			dd	0.0e0

	mirrorVec2	dd	0.0e0
			dd	0.0e0
			dd	1.0e0
			dd	0.0e0

	mirrorVec3	dd	0.0e0
			dd	0.0e0
			dd	0.0e0
			dd	1.0e0

	face0		dd	 0.0e0
			dd	 0.0e0
			dd	-1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0

	face1		dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	-1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0

	face2		dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	-1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0

	face3		dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	-1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0

	face4		dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0

	face5		dd	-1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	-1.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 0.0e0
			dd	 1.0e0

	halfVec		dd	0.5e0
			dd	0.5e0
			dd	0.5e0
			dd	0.5e0

	qFlip1		dd	-1.0e0
			dd	1.0e0
			dd	1.0e0
			dd	0.0e0

	qFlip2		dd	1.0e0
			dd	-1.0e0
			dd	1.0e0
			dd	0.0e0

	qFlip3		dd	1.0e0
			dd	1.0e0
			dd	-1.0e0
			dd	0.0e0

	qPos1		dd	1.0e0
			dd	0.0e0
			dd	0.0e0
			dd	0.0e0

	qPos2		dd	0.0e0
			dd	1.0e0
			dd	0.0e0
			dd	0.0e0

	qPos3		dd	0.0e0
			dd	0.0e0
			dd	1.0e0
			dd	0.0e0

	q4375	dq	0.4375e0,
	q5625	dq	0.5625e0,
	qHalf	dq	0.5e0,
	qTwo	dq	2.0e0,
	qZero	dq	0.0e0,
	qOne	dq	1.0e0

	qPi	dq	3.14159265358979323846e0
	pio2_hi	dq	1.5707963267948966192313216916397514420986e0
	pio2_lo	dq	4.3359050650618905123985220130216759843812E-35

	rS0	dq	 5.619049346208901520945464704848780243887E0
	rS1	dq	-4.460504162777731472539175700169871920352E1
	rS2	dq	 1.317669505315409261479577040530751477488E2
	rS3	dq	-1.626532582423661989632442410808596009227E2
	rS4	dq	 3.144806644195158614904369445440583873264E1
	rS5	dq	 9.806674443470740708765165604769099559553E1
	rS6	dq	-5.708468492052010816555762842394927806920E1
	rS7	dq	-1.396540499232262112248553357962639431922E1
	rS8	dq	 1.126243289311910363001762058295832610344E1
	rS9	dq	 4.956179821329901954211277873774472383512E-1
	rS10	dq	-3.313227657082367169241333738391762525780E-1

	sS0	dq	-4.645814742084009935700221277307007679325E0
	sS1	dq	 3.879074822457694323970438316317961918430E1
	sS2	dq	-1.221986588013474694623973554726201001066E2
	sS3	dq	 1.658821150347718105012079876756201905822E2
	sS4	dq	-4.804379630977558197953176474426239748977E1
	sS5	dq	-1.004296417397316948114344573811562952793E2
	sS6	dq	 7.530281592861320234941101403870010111138E1
	sS7	dq	 1.270735595411673647119592092304357226607E1
	sS8	dq	-1.815144839646376500705105967064792930282E1
	sS9	dq	-7.821597334910963922204235247786840828217E-2

	acosr5625	dq	9.7338991014954640492751132535550279812151E-1
	pimacosr5625	dq	2.1682027434402468335351320579240000860757E0

	P0	dq	 2.177690192235413635229046633751390484892E0
	P1	dq	-2.848698225706605746657192566166142909573E1
	P2	dq	 1.040076477655245590871244795403659880304E2
	P3	dq	-1.400087608918906358323551402881238180553E2
	P4	dq	 2.221047917671449176051896400503615543757E1
	P5	dq	 9.643714856395587663736110523917499638702E1
	P6	dq	-5.158406639829833829027457284942389079196E1
	P7	dq	-1.578651828337585944715290382181219741813E1
	P8	dq	 1.093632715903802870546857764647931045906E1
	P9	dq	 5.448925479898460003048760932274085300103E-1
	P10	dq	-3.315886001095605268470690485170092986337E-1
	Q0	dq	-1.958219113487162405143608843774587557016E0
	Q1	dq	 2.614577866876185080678907676023269360520E1
	Q2	dq	-9.990858606464150981009763389881793660938E1
	Q3	dq	 1.443958741356995763628660823395334281596E2
	Q4	dq	-3.206441012484232867657763518369723873129E1
	Q5	dq	-1.048560885341833443564920145642588991492E2
	Q6	dq	 6.745883931909770880159915641984874746358E1
	Q7	dq	 1.806809656342804436118449982647641392951E1
	Q8	dq	-1.770150690652438294290020775359580915464E1
	Q9	dq	-5.659156469628629327045433069052560211164E-1

	acosr4375	dq	1.1179797320499710475919903296900511518755E0
	pimacosr4375	dq	2.0236129215398221908706530535894517323217E0

	pS0	dq	-8.358099012470680544198472400254596543711E2
	pS1	dq	 3.674973957689619490312782828051860366493E3
	pS2	dq	-6.730729094812979665807581609853656623219E3
	pS3	dq	 6.643843795209060298375552684423454077633E3
	pS4	dq	-3.817341990928606692235481812252049415993E3
	pS5	dq	 1.284635388402653715636722822195716476156E3
	pS6	dq	-2.410736125231549204856567737329112037867E2
	pS7	dq	 2.219191969382402856557594215833622156220E1
	pS8	dq	-7.249056260830627156600112195061001036533E-1
	pS9	dq	 1.055923570937755300061509030361395604448E-3
	qS0	dq	-5.014859407482408326519083440151745519205E3
	qS1	dq	 2.430653047950480068881028451580393430537E4
	qS2	dq	-4.997904737193653607449250593976069726962E4
	qS3	dq	 5.675712336110456923807959930107347511086E4
	qS4	dq	-3.881523118339661268482937768522572588022E4
	qS5	dq	 1.634202194895541569749717032234510811216E4
	qS6	dq	-4.151452662440709301601820849901296953752E3
	qS7	dq	 5.956050864057192019085175976175695342168E2
	qS8	dq	-4.175375777334867025769346564600396877176E1

	p754abs	dd	0xffffffff
		dd	0x7fffffff
		dd	0xffffffff
		dd	0x7fffffff
 
	dnan	dd	0x00000000
		dd	0xfff80000

	floatTwo	dd	2.0e0
	floatHalf	dd	0.5e0
	nearZero	dd	1.0e-6

section .code code align=16

;;; ---------------------------------------------
;;; Status and global operations
;;; ---------------------------------------------
;;;

	global _GetFpuStatusAsm
	global _ClearFpuStatusAsm

;;; ---------------------------------------------
;;; Basic floating point methods
;;; ---------------------------------------------
;;; 

	global _FloatLerpAsm
	global _FloatLerpPtrAsm
	global _FloatSqrAsm
	global _FloatSqrPtrAsm

	global _fCosAsm
	global _CosAsm
	global _AfCosAsm
	global _ACosAsm
	global _fSinAsm
	global _SinAsm
	global _AfSinAsm
	global _ASinAsm
	global _fTanAsm
	global _TanAsm
	global _AfTanAsm
	global _ATanAsm

;;; ---------------------------------------------
;;; Common Vector2 Methods
;;; ---------------------------------------------
;;; 

	global _Vec2CopyAsm
	global _Vec2CopyBlockAsm
	global _BuildVec2PackedArrayAsm

;;; ---------------------------------------------
;;; Common Vector2 Scalar Methods
;;; ---------------------------------------------
;;; 


%if (__BUILD_ADVANCED_ALIGNED_LIB == 1   || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2AddFloatAsm
	global _Vec2SubtractFloatAsm
	global _Vec2MultiplyFloatAsm
	global _Vec2FloatMultiplyAsm
	global _Vec2DivideFloatAsm
%endif

;;; ---------------------------------------------
;;; Common Vector2 Scalar Methods
;;; (Floating point unit execution)
;;; ---------------------------------------------
;;; 

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2AddFloatFPU_Asm
	global _Vec2SubtractFloatFPU_Asm
	global _Vec2MultiplyFloatFPU_Asm
	global _Vec2FloatMultiplyFPU_Asm
	global _Vec2DivideFloatFPU_Asm
%endif

;;; ---------------------------------------------
;;; Block (array) floating point Vector 2 methods
;;; ---------------------------------------------
;;;

;;; ---------------------------------------------
;;; Vector2 + float
;;; ---------------------------------------------
;;; 

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2AddFloatToBlockAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 ||__BUILD_ALL == 1)
	global _Vec2uAddFloatToBlockAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2AddFloatToBlockFPU_Asm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1   || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2AddFloatToBlockSizeAsm
	global _Vec2BufAddFloatToBlockAsm
	global _Vec2BufAddFloatToBufAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2AddFloatToBlockSizeFPU_Asm
	global _Vec2BufAddFloatToBlockFPU_Asm
	global _Vec2BufAddFloatToBufFPU_Asm
%endif

;;; ---------------------------------------------
;;; Vector2 - float
;;; ---------------------------------------------
;;; 

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2SubtractFloatFromBlockAsm
%endif
	
%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uSubtractFloatFromBlockAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2SubtractFloatFromBlockFPU_Asm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2SubFloatFromBlockSizeAsm
	global _Vec2BufSubFloatFromBlkSizeAsm
	global _Vec2BufSubFloatFromBufAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2SubFloatFromBlockSizeFPU_Asm
	global _Vec2BufSubFloatFromBlkSizeFPU_Asm
	global _Vec2BufSubFloatFromBufFPU_Asm
%endif

;;; ---------------------------------------------
;;; Vector2 * float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2MultiplyBlockByFloatAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uMultiplyBlockByFloatAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2MultiplyBlockByFloatFPU_Asm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2MultiplyBlkByFloatSizeAsm
	global _Vec2BufMulBlockByFloatSizeAsm
	global _Vec2BufMulBlockByFloatBufAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2MultiplyBlkByFloatSizeFPU_Asm
	global _Vec2BufMulBlockByFloatSizeFPU_Asm
	global _Vec2BufMulBlockByFloatBufFPU_Asm
%endif

;;; ---------------------------------------------
;;; Vector2 / float
;;; ---------------------------------------------
;;; 

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2DivideBlockByFloatAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uDivideBlockByFloatAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2DivideBlockByFloatFPU_Asm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2DivideBlockByFloatSizeAsm
	global _Vec2BufDivBlockByFloatSizeAsm
	global _Vec2BufDivBufByFloatAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2DivideBlockByFloatSizeFPU_Asm
	global _Vec2BufDivBlockByFloatSizeFPU_Asm
	global _Vec2BufDivBufByFloatFPU_Asm
%endif

	global _Vec2NegateAsm
	global _Vec2AddAsm
	global _Vec2SubtractAsm
	global _Vec2MultiplyAsm
	global _Vec2DivideAsm
	global _Vec2AngleAsm

;;; ---------------------------------------------
;;;  Vector2 boolean operations
;;; ---------------------------------------------
;;; 

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2EqualsAsm
	global _Vec2NotEqualsAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uEqualsAsm
	global _Vec2uNotEqualsAsm
%endif

;;; ---------------------------------------------
;;; Vector2 Unary Operations
;;; ---------------------------------------------
;;; 

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2NegateBlockAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uNegateBlockAsm
%endif

	global _Vec2NegateBlockBySizeAsm
	global _Vec2BufNegateBlockBySizeAsm
	global _Vec2BufNegateBufBySizeAsm

;;; ---------------------------------------------
;;; Vector2 <> Vector2 Array Operations
;;; ---------------------------------------------
;;; 

;;; ---------------------------------------------
;;; Vector2<array> + Vector2
;;; ---------------------------------------------
;;; 

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2AddVec2ToBlockAsm
	global _Vec2AddBlockToBlockAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uAddVec2ToBlockAsm
	global _Vec2uAddBlockToBlockAsm
%endif

	global _Vec2BufAddVec2ToBlockBySizeAsm
	global _Vec2BufAddBlockBySizeAsm
	global _Vec2BufAddBufBySizeAsm

;;; ---------------------------------------------
;;; Vector2<array> - Vector2
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2SubtractVec2FromBlockAsm
	global _Vec2SubtractBlockFromBlockAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uSubtractVec2FromBlockAsm
	global _Vec2uSubtractBlockFromBlockAsm
%endif

	global _Vec2BufSubVec2FromBlkBySizeAsm
	global _Vec2BufSubBlockBySizeAsm
	global _Vec2BufSubBufBySizeAsm

;;; ---------------------------------------------
;;; Vector2<array> * Vector2
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2MultiplyBlockByVec2Asm
	global _Vec2MultiplyBlockByBlockAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uMultiplyBlockByVec2Asm
	global _Vec2uMultiplyBlockByBlockAsm
%endif

	global _Vec2BufMulVec2ByBlockSizeAsm
	global _Vec2BufMulBlockBySizeAsm
	global _Vec2BufMulBufBySizeAsm

;;; ---------------------------------------------
;;; Vector2<array> / Vector2
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2DivideBlockByVec2Asm
	global _Vec2DivideBlockByBlockAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uDivideBlockByVec2Asm
	global _Vec2uDivideBlockByBlockAsm
%endif

	global _Vec2BufDivVec2ByBlockSizeAsm
	global _Vec2BufDivBlockBySizeAsm
	global _Vec2BufDivBufBySizeAsm

;;; ---------------------------------------------
;;; Vector2 Linear Basic Support Methods
;;; ---------------------------------------------
;;;


%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2LerpBlockAsm
	global _Vec2SqrBlockAsm
	global _Vec2SqrtBlockAsm
	global _Vec2NormalizeBlockAsm
	global _Vec2DotBlockAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec2uLerpBlockAsm
	global _Vec2uSqrBlockAsm
	global _Vec2uSqrtBlockAsm
	global _Vec2uNormalizeBlockAsm
	global _Vec2uDotBlockAsm
%endif

	global _Vec2LerpAsm
	global _Vec2BufLerpBufAsm
	global _Vec2SqrAsm
	global _Vec2BufSqrBufAsm
	global _Vec2SqrtAsm
	global _Vec2BufSqrtBufAsm
	global _Vec2NormalizeAsm
	global _Vec2BufNormalizeBufAsm
	global _Vec2DotAsm
	global _Vec2BufDotBufAsm
	global _Vec2LengthAsm
	global _Vec2LengthBlockAsm
	global _Vec2BufLengthBufAsm

;;; ---------------------------------------------
;;; Vector3 Common Operations
;;; ---------------------------------------------
;;;

	global _Vec3CopyAsm
	global _Vec3CopyBlockAsm
	global _BuildVec3PackedArrayAsm

;;; ---------------------------------------------
;;; Vector3(<array>)  + float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3AddFloatAsm
	global _Vec3AddFloatToBlockAsm
	global _Vec3AddFloatToBlockBySizeAsm
	global _Vec3BufAddFloatToBlockAsm
	global _Vec3BufAddFloatToBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uAddFloatAsm
	global _Vec3uAddFloatToBlockAsm
	global _Vec3uAddFloatToBlockBySizeAsm
	global _Vec3uBufAddFloatToBlockAsm
	global _Vec3uBufAddFloatToBufAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>)  - float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3SubtractFloatAsm
	global _Vec3SubtractFloatFromBlockAsm
	global _Vec3SubFloatFromBlockBySizeAsm
	global _Vec3BufSubFloatFromBlockAsm
	global _Vec3BufSubFloatFromBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uSubtractFloatAsm
	global _Vec3uSubtractFloatFromBlockAsm
	global _Vec3uSubFloatFromBlockBySizeAsm
	global _Vec3uBufSubFloatFromBlockAsm
	global _Vec3uBufSubFloatFromBufAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) * float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3MultiplyFloatAsm
	global _Vec3MultiplyFloatToBlockAsm
	global _Vec3MulFloatToBlockBySizeAsm
	global _Vec3BufMulFloatToBlockAsm
	global _Vec3BufMulFloatToBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uMultiplyFloatAsm
	global _Vec3uMultiplyFloatToBlockAsm
	global _Vec3uMulFloatToBlockBySizeAsm
	global _Vec3uBufMulFloatToBlockAsm
	global _Vec3uBufMulFloatToBufAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) / float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3DivideFloatAsm
	global _Vec3DivideBlockByFloatAsm
	global _Vec3DivBlockByFloatBySizeAsm
	global _Vec3BufDivBlockByFloatAsm
	global _Vec3BufDivBufByFloatAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uDivideFloatAsm
	global _Vec3uDivideBlockByFloatAsm
	global _Vec3uDivBlockByFloatBySizeAsm
	global _Vec3uBufDivBlockByFloatAsm
	global _Vec3uBufDivBufByFloatAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) Boolean
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3EqualsAsm
	global _Vec3NotEqualsAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uEqualsAsm
	global _Vec3uNotEqualsAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) Unary
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3NegateAsm
	global _Vec3NegateBlockAsm
	global _Vec3NegateBlockBySizeAsm
	global _Vec3BufNegateBlockAsm
	global _Vec3BufNegateBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uNegateAsm
	global _Vec3uNegateBlockAsm
	global _Vec3uNegateBlockBySizeAsm
	global _Vec3uBufNegateBlockAsm
	global _Vec3uBufNegateBufAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) + Vector3
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3AddAsm
	global _Vec3AddVecToBlockAsm
	global _Vec3AddVecToBlockBySizeAsm
	global _Vec3BufAddVecToBlockAsm
	global _Vec3BufAddVecToBufAsm
	global _Vec3AddBlockToBlockAsm
	global _Vec3AddBlockToBlockBySizeAsm
	global _Vec3BufAddBlockToBufAsm
	global _Vec3BufAddBufToBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uAddAsm
	global _Vec3uAddVecToBlockAsm
	global _Vec3uAddVecToBlockBySizeAsm
	global _Vec3uBufAddVecToBlockAsm
	global _Vec3uBufAddVecToBufAsm
	global _Vec3uAddBlockToBlockAsm
	global _Vec3uAddBlockToBlockBySizeAsm
	global _Vec3uBufAddBlockToBufAsm
	global _Vec3uBufAddBufToBufAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) - Vector3
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3SubtractAsm
	global _Vec3SubVecFromBlockAsm
	global _Vec3SubVecFromBlockBySizeAsm
	global _Vec3BufSubVecFromBlockAsm
	global _Vec3BufSubVecFromBufAsm
	global _Vec3SubBlockFromBlockAsm
	global _Vec3SubBlockFromBlockBySizeAsm
	global _Vec3BufSubBlockFromBufAsm
	global _Vec3BufSubBufFromBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uSubtractAsm
	global _Vec3uSubVecFromBlockAsm
	global _Vec3uSubVecFromBlockBySizeAsm
	global _Vec3uBufSubVecFromBlockAsm
	global _Vec3uBufSubVecFromBufAsm
	global _Vec3uSubBlockFromBlockAsm
	global _Vec3uSubBlockFromBlockBySizeAsm
	global _Vec3uBufSubBlockFromBufAsm
	global _Vec3uBufSubBufFromBufAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) * Vector3
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3MultiplyAsm
	global _Vec3MulBlockByVecAsm
	global _Vec3MulBlockByVecUseSizeAsm
	global _Vec3BufMulBufByVecAsm
	global _Vec3BufMulBufByVecUseSizeAsm
	global _Vec3MulBlockByBlockAsm
	global _Vec3MulBlockByBlockUseSizeAsm
	global _Vec3BufMulBufByBlockAsm
	global _Vec3BufMulBufByBufAsm	
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uMultiplyAsm
	global _Vec3uMulBlockByVecAsm
	global _Vec3uMulBlockByVecUseSizeAsm
	global _Vec3uBufMulBufByVecAsm
	global _Vec3uBufMulBufByVecUseSizeAsm
	global _Vec3uMulBlockByBlockAsm
	global _Vec3uMulBlockByBlockUseSizeAsm
	global _Vec3uBufMulBufByBlockAsm
	global _Vec3uBufMulBufByBufAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) / Vector3
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3DivideAsm
	global _Vec3DivBlockByVecAsm
	global _Vec3DivBlockByVecUseSizeAsm
	global _Vec3BufDivBufByVecAsm
	global _Vec3BufDivBufByVecUseSizeAsm
	global _Vec3DivBlockByBlockAsm
	global _Vec3DivBlockByBlockUseSizeAsm
	global _Vec3BufDivBufByBlockAsm
	global _Vec3BufDivBufByBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uDivideAsm
	global _Vec3uDivBlockByVecAsm
	global _Vec3uDivBlockByVecUseSizeAsm
	global _Vec3uBufDivBufByVecAsm
	global _Vec3uBufDivBufByVecUseSizeAsm
	global _Vec3uDivBlockByBlockAsm
	global _Vec3uDivBlockByBlockUseSizeAsm
	global _Vec3uBufDivBufByBlockAsm
	global _Vec3uBufDivBufByBufAsm
%endif

;;; ---------------------------------------------
;;; Vector3(<array>) Linear Interpolation
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3LerpAsm
	global _Vec3LerpBlockAsm
	global _Vec3LerpBlockUseSizeAsm
	global _Vec3BufLerpBlockAsm
	global _Vec3BufLerpBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uLerpAsm
	global _Vec3uLerpBlockAsm
	global _Vec3uLerpBlockUseSizeAsm
	global _Vec3uBufLerpBlockAsm
	global _Vec3uBufLerpBufAsm
%endif

;;; ---------------------------------------------
;;; dot(Vector3(<array>)
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3DotAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uDotAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3DotFlatAsm
%endif
	
%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uDotFlatAsm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3DotBlockAsm
	global _Vec3DotBlockUseSizeAsm
	global _Vec3BufDotBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uDotBlockAsm
	global _Vec3uDotBlockUseSizeAsm
	global _Vec3uBufDotBufAsm
%endif

%if (__BUILD_ALL == 1)
	global _Vec3DotFPU_Asm
%endif

;;; ---------------------------------------------
;;; sqr(Vector3(<array>))
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3SqrAsm
	global _Vec3SqrBlockAsm
	global _Vec3SqrBlockUseSizeAsm
	global _Vec3BufSqrBufAsm

	global _Vec3SqrtAsm
	global _Vec3SqrtBlockAsm
	global _Vec3SqrtBlockUseSizeAsm
	global _Vec3BufSqrtBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uSqrAsm
	global _Vec3uSqrBlockAsm
	global _Vec3uSqrBlockUseSizeAsm
	global _Vec3uBufSqrBufAsm

	global _Vec3uSqrtAsm
	global _Vec3uSqrtBlockAsm
	global _Vec3uSqrtBlockUseSizeAsm
	global _Vec3uBufSqrtBufAsm
%endif

;;; ---------------------------------------------
;;; norm(Vector3(<array>))
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3NormalizeAsm
	global _Vec3NormalizeBlockAsm
	global _Vec3NormalizeBlockUseSizeAsm
	global _Vec3BufNormalizeBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uNormalizeAsm
	global _Vec3uNormalizeBlockAsm
	global _Vec3uNormalizeBlockUseSizeAsm
	global _Vec3uBufNormalizeBufAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3NormalizeFlatAsm
	global _Vec3NormalizeBlockFlatAsm
	global _Vec3NormalizeBlockFlatUseSizeAsm
	global _Vec3BufNormalizeBufFlatAsm
%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uNormalizeFlatAsm
	global _Vec3uNormalizeBlockFlatAsm
	global _Vec3uNormalizeBlockFlatUseSizeAsm
	global _Vec3uBufNormalizeBufFlatAsm
%endif

%if (__BUILD_ALL == 1)
	global _Vec3NormalizeFPU_Asm
%endif

;;; ---------------------------------------------
;;; length(Vector3(<array>))
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3LengthAsm
	global _Vec3LengthBlockAsm
	global _Vec3LengthBlockUseSizeAsm
	global _Vec3BufLengthBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uLengthAsm
	global _Vec3uLengthBlockAsm
	global _Vec3uLengthBlockUseSizeAsm
	global _Vec3uBufLengthBufAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3LengthFlatAsm
	global _Vec3LengthBlockFlatAsm
	global _Vec3LengthBlockFlatUseSizeAsm
	global _Vec3BufLengthBufFlatAsm
%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uLengthFlatAsm
	global _Vec3uLengthBlockFlatAsm
	global _Vec3uLengthBlockFlatUseSizeAsm
	global _Vec3uBufLengthBufFlatAsm
%endif

%if (__BUILD_ALL == 1)
	global _Vec3LengthFPU_Asm
%endif

;;; ---------------------------------------------
;;; cross(Vector3(<array>))
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3CrossAsm
	global _Vec3CrossBlockAsm
	global _Vec3CrossBlockUseSizeAsm
	global _Vec3BufCrossBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uCrossAsm
	global _Vec3uCrossBlockAsm
	global _Vec3uCrossBlockUseSizeAsm
	global _Vec3uBufCrossBufAsm
%endif

;;; ---------------------------------------------
;;; reflect(Vector3(<array>))
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3ReflectAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec3uReflectAsm
%endif

;;; ---------------------------------------------
;;; Common Vector4 Methods
;;; ---------------------------------------------
;;;

	global _Vec4CopyAsm
	global _Vec4CopyBlockAsm
	global _BuildVec4PackedArrayAsm

;;; ---------------------------------------------
;;; Vector4 + float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4AddFloatAsm
	global _Vec4AddFloatToBlockAsm
	global _Vec4AddFloatToBlockBySizeAsm
	global _Vec4BufAddFloatToBlockAsm
	global _Vec4BufAddFloatToBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uAddFloatAsm
	global _Vec4uAddFloatToBlockAsm
	global _Vec4uAddFloatToBlockBySizeAsm
	global _Vec4uBufAddFloatToBlockAsm
	global _Vec4uBufAddFloatToBufAsm
%endif

;;; ---------------------------------------------
;;; Vector4 - float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4SubtractFloatAsm
	global _Vec4SubtractFloatFromBlockAsm
	global _Vec4SubFloatFromBlockBySizeAsm
	global _Vec4BufSubFloatFromBlockAsm
	global _Vec4BufSubFloatFromBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uSubtractFloatAsm
	global _Vec4uSubtractFloatFromBlockAsm
	global _Vec4uSubFloatFromBlockBySizeAsm
	global _Vec4uBufSubFloatFromBlockAsm
	global _Vec4uBufSubFloatFromBufAsm
%endif

;;; ---------------------------------------------
;;; Vector4 * float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4MultiplyFloatAsm
	global _Vec4MultiplyFloatToBlockAsm
	global _Vec4MulFloatToBlockBySizeAsm
	global _Vec4BufMulFloatToBlockAsm
	global _Vec4BufMulFloatToBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uMultiplyFloatAsm
	global _Vec4uMultiplyFloatToBlockAsm
	global _Vec4uMulFloatToBlockBySizeAsm
	global _Vec4uBufMulFloatToBlockAsm
	global _Vec4uBufMulFloatToBufAsm
%endif

;;; ---------------------------------------------
;;; Vector4 / float
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4DivideFloatAsm
	global _Vec4DivideBlockByFloatAsm
	global _Vec4DivBlockByFloatBySizeAsm
	global _Vec4BufDivBlockByFloatAsm
	global _Vec4BufDivBufByFloatAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uDivideFloatAsm
	global _Vec4uDivideBlockByFloatAsm
	global _Vec4uDivBlockByFloatBySizeAsm
	global _Vec4uBufDivBlockByFloatAsm
	global _Vec4uBufDivBufByFloatAsm
%endif

;;; ---------------------------------------------
;;; Vector4 Boolean Methods
;;; ---------------------------------------------
;;;

	global _Vec4EqualsAsm
	global _Vec4NotEqualsAsm

;;; ---------------------------------------------
;;; -Vector4 
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4NegateAsm
	global _Vec4NegateBlockAsm
	global _Vec4NegateBlockBySizeAsm
	global _Vec4BufNegateBlockAsm
	global _Vec4BufNegateBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uNegateAsm
	global _Vec4uNegateBlockAsm
	global _Vec4uNegateBlockBySizeAsm
	global _Vec4uBufNegateBlockAsm
	global _Vec4uBufNegateBufAsm
%endif

;;; ---------------------------------------------
;;; Vector4(<array>) + Vector4(<array>)
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4AddAsm
	global _Vec4AddVecToBlockAsm
	global _Vec4AddVecToBlockBySizeAsm
	global _Vec4BufAddVecToBlockAsm
	global _Vec4BufAddVecToBufAsm
	global _Vec4AddBlockToBlockAsm
	global _Vec4AddBlockToBlockBySizeAsm
	global _Vec4BufAddBlockToBufAsm
	global _Vec4BufAddBufToBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uAddAsm
	global _Vec4uAddVecToBlockAsm
	global _Vec4uAddVecToBlockBySizeAsm
	global _Vec4uBufAddVecToBlockAsm
	global _Vec4uBufAddVecToBufAsm
	global _Vec4uAddBlockToBlockAsm
	global _Vec4uAddBlockToBlockBySizeAsm
	global _Vec4uBufAddBlockToBufAsm
	global _Vec4uBufAddBufToBufAsm
%endif

;;; ---------------------------------------------
;;; Vector4(<array>) - Vector4(<array>)
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4SubtractAsm
	global _Vec4SubVecFromBlockAsm
	global _Vec4SubVecFromBlockBySizeAsm
	global _Vec4BufSubVecFromBlockAsm
	global _Vec4BufSubVecFromBufAsm
	global _Vec4SubBlockFromBlockAsm
	global _Vec4SubBlockFromBlockBySizeAsm
	global _Vec4BufSubBlockFromBufAsm
	global _Vec4BufSubBufFromBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uSubtractAsm
	global _Vec4uSubVecFromBlockAsm
	global _Vec4uSubVecFromBlockBySizeAsm
	global _Vec4uBufSubVecFromBlockAsm
	global _Vec4uBufSubVecFromBufAsm
	global _Vec4uSubBlockFromBlockAsm
	global _Vec4uSubBlockFromBlockBySizeAsm
	global _Vec4uBufSubBlockFromBufAsm
	global _Vec4uBufSubBufFromBufAsm
%endif

;;; ---------------------------------------------
;;; Vector4(<array>) * Vector4(<array>)
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4MultiplyAsm
	global _Vec4MulBlockByVecAsm
	global _Vec4MulBlockByVecUseSizeAsm
	global _Vec4BufMulBufByVecAsm
	global _Vec4BufMulBufByVecUseSizeAsm
	global _Vec4MulBlockByBlockAsm
	global _Vec4MulBlockByBlockUseSizeAsm
	global _Vec4BufMulBufByBlockAsm
	global _Vec4BufMulBufByBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uMultiplyAsm
	global _Vec4uMulBlockByVecAsm
	global _Vec4uMulBlockByVecUseSizeAsm
	global _Vec4uBufMulBufByVecAsm
	global _Vec4uBufMulBufByVecUseSizeAsm
	global _Vec4uMulBlockByBlockAsm
	global _Vec4uMulBlockByBlockUseSizeAsm
	global _Vec4uBufMulBufByBlockAsm
	global _Vec4uBufMulBufByBufAsm
%endif

;;; ---------------------------------------------
;;; Vector4(<array>) / Vector4(<array>)
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4DivideAsm
	global _Vec4DivBlockByVecAsm
	global _Vec4DivBlockByVecUseSizeAsm
	global _Vec4BufDivBufByVecAsm
	global _Vec4BufDivBufByVecUseSizeAsm
	global _Vec4DivBlockByBlockAsm
	global _Vec4DivBlockByBlockUseSizeAsm
	global _Vec4BufDivBufByBlockAsm
	global _Vec4BufDivBufByBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uDivideAsm
	global _Vec4uDivBlockByVecAsm
	global _Vec4uDivBlockByVecUseSizeAsm
	global _Vec4uBufDivBufByVecAsm
	global _Vec4uBufDivBufByVecUseSizeAsm
	global _Vec4uDivBlockByBlockAsm
	global _Vec4uDivBlockByBlockUseSizeAsm
	global _Vec4uBufDivBufByBlockAsm
	global _Vec4uBufDivBufByBufAsm
%endif

;;; ---------------------------------------------
;;; lerp(Vector4(<array>)) : Linear Interp
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4LerpAsm
	global _Vec4LerpBlockAsm
	global _Vec4LerpBlockUseSizeAsm
	global _Vec4BufLerpBlockAsm
	global _Vec4BufLerpBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uLerpAsm
	global _Vec4uLerpBlockAsm
	global _Vec4uLerpBlockUseSizeAsm
	global _Vec4uBufLerpBlockAsm
	global _Vec4uBufLerpBufAsm
%endif

;;; ---------------------------------------------
;;; dot(Vector4(<array>))
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4DotAsm
	global _Vec4DotBlockAsm
	global _Vec4DotBlockUseSizeAsm
	global _Vec4BufDotBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uDotAsm
	global _Vec4uDotBlockAsm
	global _Vec4uDotBlockUseSizeAsm
	global _Vec4uBufDotBufAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4DotFlatAsm
	global _Vec4DotBlockFlatAsm
	global _Vec4DotBlockFlatUseSizeAsm
	global _Vec4BufDotBufFlatAsm
%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uDotFlatAsm
	global _Vec4uDotBlockFlatAsm
	global _Vec4uDotBlockFlatUseSizeAsm
	global _Vec4uBufDotBufFlatAsm
%endif

%if (__BUILD_ALL == 1)
	global _Vec4DotFPU_Asm
%endif

;;; ---------------------------------------------
;;; sqr(Vector4(<array>)
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4SqrAsm
	global _Vec4SqrBlockAsm
	global _Vec4SqrBlockUseSizeAsm
	global _Vec4BufSqrBufAsm

	global _Vec4SqrtAsm
	global _Vec4SqrtBlockAsm
	global _Vec4SqrtBlockUseSizeAsm
	global _Vec4BufSqrtBufAsm

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uSqrAsm
	global _Vec4uSqrBlockAsm
	global _Vec4uSqrBlockUseSizeAsm
	global _Vec4uBufSqrBufAsm

	global _Vec4uSqrtAsm
	global _Vec4uSqrtBlockAsm
	global _Vec4uSqrtBlockUseSizeAsm
	global _Vec4uBufSqrtBufAsm
%endif

;;; ---------------------------------------------
;;; normalize(Vector4(<array>))
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4NormalizeAsm
	global _Vec4NormalizeBlockAsm
	global _Vec4NormalizeBlockUseSizeAsm
	global _Vec4BufNormalizeBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uNormalizeAsm
	global _Vec4uNormalizeBlockAsm
	global _Vec4uNormalizeBlockUseSizeAsm
	global _Vec4uBufNormalizeBufAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4NormalizeFlatAsm
	global _Vec4NormalizeBlockFlatAsm
	global _Vec4NormalizeBlockFlatUseSizeAsm
	global _Vec4BufNormalizeBufFlatAsm
%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uNormalizeFlatAsm
	global _Vec4uNormalizeBlockFlatAsm
	global _Vec4uNormalizeBlockFlatUseSizeAsm
	global _Vec4uBufNormalizeBufFlatAsm
%endif

%if (__BUILD_ALL == 1)
	global _Vec4NormalizeFPU_Asm
%endif

;;; ---------------------------------------------
;;; length(Vector4(<array>)
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4LengthAsm
	global _Vec4LengthBlockAsm
	global _Vec4LengthBlockUseSizeAsm
	global _Vec4BufLengthBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uLengthAsm
	global _Vec4uLengthBlockAsm
	global _Vec4uLengthBlockUseSizeAsm
	global _Vec4uBufLengthBufAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4LengthFlatAsm
	global _Vec4LengthBlockFlatAsm
	global _Vec4LengthBlockFlatUseSizeAsm
	global _Vec4BufLengthBufFlatAsm
%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uLengthFlatAsm
	global _Vec4uLengthBlockFlatAsm
	global _Vec4uLengthBlockFlatUseSizeAsm
	global _Vec4uBufLengthBufFlatAsm
%endif

%if (__BUILD_ALL == 1)
	global _Vec4LengthFPU_Asm
%endif

;;; ---------------------------------------------
;;; cross(Vector4(<array>))
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4CrossAsm
	global _Vec4CrossBlockAsm
	global _Vec4CrossBlockUseSizeAsm
	global _Vec4BufCrossBufAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Vec4uCrossAsm
	global _Vec4uCrossBlockAsm
	global _Vec4uCrossBlockUseSizeAsm
	global _Vec4uBufCrossBufAsm
%endif

;;; ---------------------------------------------
;;; Mat2 Operations
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat2NegateAsm
	global _Mat2AddAsm
	global _Mat2AddFloatAsm
	global _Mat2SubtractAsm
	global _Mat2SubtractFloatAsm
	global _Mat2MultiplyAsm
	global _Mat2MultiplyVecAsm
	global _Mat2MultiplyFloatAsm
	global _Mat2IdentityAsm
	global _Mat2TransposeAsm
	global _Mat2MultiplyVecBlockAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat2uNegateAsm
	global _Mat2uAddAsm
	global _Mat2uAddFloatAsm
	global _Mat2uSubtractAsm
	global _Mat2uSubtractFloatAsm
	global _Mat2uMultiplyAsm
	global _Mat2uMultiplyVecAsm
	global _Mat2uMultiplyFloatAsm
	global _Mat2uIdentityAsm
	global _Mat2uTransposeAsm
	global _Mat2uMultiplyVecBlockAsm
%endif
	global _Mat2RotateLHAsm
	global _Mat2RotateRHAsm
	global _Mat2RotateAsm
	global _Mat2ScaleAsm

;;; ---------------------------------------------
;;; Mat3 Operations
;;; ---------------------------------------------
;;;

	global _Mat3CopyAsm
	global _Mat3IdentityAsm

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat3NegateAsm
	global _Mat3AddAsm
	global _Mat3AddFloatAsm
	global _Mat3SubtractAsm
	global _Mat3SubtractFloatAsm
	global _Mat3MultiplyAsm
	global _Mat3MultiplyIdentityByBlocksAsm
	global _Mat3MultiplyVecAsm
	global _Mat3MultiplyVecBlockAsm
	global _Mat3MulVecBlockBySizeAsm
	global _Mat3MulVec3BufByBufAsm
	global _Mat3MultiplyFloatAsm
	global _Mat3InverseAsm
	global _Mat3TransposeAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat3uNegateAsm
	global _Mat3uAddAsm
	global _Mat3uAddFloatAsm
	global _Mat3uSubtractAsm
	global _Mat3uSubtractFloatAsm
	global _Mat3uMultiplyAsm
	global _Mat3uMultiplyIdentityByBlocksAsm
	global _Mat3uMultiplyVecAsm
	global _Mat3uMultiplyVecBlockAsm
	global _Mat3uMulVecBlockBySizeAsm
	global _Mat3uMulVec3BufByBufAsm
	global _Mat3uMultiplyFloatAsm
	global _Mat3uInverseAsm
	global _Mat3uTransposeAsm
%endif

%if (__BUILD_ALL == 1)
	global _Mat3MultiplyFPU_Asm
	global _Mat3MultiplyIdentityByBlockFPU_Asm
%endif

	global _Mat3RotateRHX_Asm
	global _Mat3RotateLHX_Asm
	global _Mat3RotateRHY_Asm
	global _Mat3RotateLHY_Asm
	global _Mat3RotateRHZ_Asm
	global _Mat3RotateLHZ_Asm

	global _Mat3RotateRHXY_Asm
	global _Mat3RotateLHXY_Asm
	global _Mat3RotateRHXZ_Asm
	global _Mat3RotateLHXZ_Asm
	global _Mat3RotateRHYZ_Asm
	global _Mat3RotateLHYZ_Asm
	
	global _Mat3RotateRHXYZ_Asm
	global _Mat3RotateLHXYZ_Asm

	;; 
	;; XXX:	Direct multiply methods are eventually required
	;;

	global _Mat3ScaleAsm
	global _Mat3ScaleByVec3Asm

;;; ---------------------------------------------
;;; Mat4 Operations
;;; ---------------------------------------------
;;;

	global _Mat4CopyAsm

	;; XXX:	
	;; These are embedded object methods and require additional work
	;; XXX: Additional review is still required.
	;; 
%if 0
	global _Mat4TranslateRHAsm
	global _Mat4TranslateRH_FPU_Asm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat4NegateAsm
	global _Mat4NegateMatrixAsm
	global _Mat4AddAsm
	global _Mat4AddFloatAsm
	global _Mat4AddMatrixAsm
	global _Mat4SubtractAsm
	global _Mat4SubtractFloatAsm
	global _Mat4SubtractMatrixAsm
	global _Mat4MultiplyMatrixAsm
	global _Mat4MultiplyAsm
	global _Mat4MultiplyVecAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat4uNegateAsm
	global _Mat4uNegateMatrixAsm
	global _Mat4uAddAsm
	global _Mat4uAddFloatAsm
	global _Mat4uAddMatrixAsm
	global _Mat4uSubtractAsm
	global _Mat4uSubtractFloatAsm
	global _Mat4uSubtractMatrixAsm
	global _Mat4uMultiplyMatrixAsm
	global _Mat4uMultiplyAsm
	global _Mat4uMultiplyVecAsm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat4LookAtAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat4uLookAtAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat4saLookAtAsm
%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat4suLookAtAsm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat4MultiplyFloatAsm
	global _Mat4TransposeAsm
	global _Mat4ShadowMatrixAsm
	global _Mat4MirrorMatrixAsm
	global _Mat4GlToD3DProjMatAsm
	global _Mat4LookAtLHAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _Mat4uMultiplyFloatAsm
	global _Mat4uTransposeAsm
	global _Mat4uShadowMatrixAsm
	global _Mat4uMirrorMatrixAsm
	global _Mat4uGlToD3DProjMatAsm
	global _Mat4uLookAtLHAsm
%endif

%if (__BUILD_ALL == 1)
	global _Mat4uMultiplyFPU_Asm
%endif

	;; Mat4Methods
	;; 

	global _Mat4IdentityAsm
	global _Mat4ScaleAsm
	global _Mat4RotateRHX_Asm
	global _Mat4RotateLHX_Asm
	global _Mat4RotateRHY_Asm
	global _Mat4RotateLHY_Asm
	global _Mat4RotateRHZ_Asm
	global _Mat4RotateLHZ_Asm

	global _Mat4RotateRHXY_Asm
	global _Mat4RotateLHXY_Asm
	global _Mat4RotateRHXZ_Asm
	global _Mat4RotateLHXZ_Asm
	global _Mat4RotateRHYZ_Asm
	global _Mat4RotateLHYZ_Asm
	
	global _Mat4RotateRHXYZ_Asm
	global _Mat4RotateLHXYZ_Asm
	global _Mat4TranslateRH_Asm
	global _Mat4TranslateLH_Asm
	global _Mat4TranslateRH_Vec3Asm
	global _Mat4TranslateLH_Vec3Asm
	global _Mat4TranslateRH_Vec4Asm
	global _Mat4TranslateLH_Vec4Asm
	global _Mat4OrthoMatrixAsm
	global _Mat4OrthoStructAsm
	global _Mat4PerspectiveAsm
	global _Mat4PerspectiveXAsm
	global _Mat4CubemapMatrixAsm
	global _Mat4CubemapProjectionMatAsm
	global _Mat4LookAtHorizAsm

%if 0
	global _MatMultiply3x3Asm
	global _MatMultiplyVec4x4Asm
%endif

	;; These are the basic methods ... block and specialized
	;; interpolation should be left for later
	;; 

	global _Mat3RotationFromMat4Asm
	global _Mat4FromMat3Asm


;;; ---------------------------------------------
;;; Quaternion Operations
;;; ---------------------------------------------
;;;

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _QuaternionAddAsm
	global _QuaternionMultiplyAsm
	global _QuaternionInverseAsm
	global _QuaternionToMat3Asm
	global _QuaternionToMat4Asm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _uQuaternionAddAsm
	global _uQuaternionMultiplyAsm
	global _uQuaternionInverseAsm
	global _uQuaternionToMat3Asm
	global _uQuaternionToMat4Asm
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _QuaternionNormalizeAsm
	global _QuaternionDotAsm
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _uQuaternionNormalizeAsm
	global _uQuaternionDotAsm
%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _QuaternionNormalizeFlatAsm
	global _QuaternionDotFPU_Asm
%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	global _uQuaternionNormalizeFlatAsm
	global _uQuaternionDotFlatAsm
%endif

%if (__BUILD_ALL == 1)
	global _QuaternionDotFlatAsm
%endif

	global _QuaternionFromAxisAsm
	global _QuaternionFromMat3Asm
	global _QuaternionFromMat4Asm
	global _QuaternionFromMat3Asm
	global _QuaternionFromMat4Asm
	global _QuaternionSlerpAsm
	global _QuaternionCosAsm
	global _QuaternionSinAsm

;;;
;;; GetFpuStatusAsm
;;;
;;; Call Stack
;;;
;;; [1] WORD *wStack : UNSIGNED SHORT* wStack
;;;
;;; extern "C" void GetFpuStatusAsm(unsigned short* wStack)
;;;

_GetFpuStatusAsm:

	mov	[STACK_SAVE1],AReg
	mov	AReg,[STACK_PTR1]
	
	fnstsw	[AReg]

	mov	AReg,[STACK_SAVE1]
	ret

;;;
;;; ClearFpuStatus
;;;
;;; Call Stack
;;;
;;; [1] unsigned short* wStack
;;;
;;; extern "C" void ClearFpuStatusAsm(unsigned short* wStack)
;;;

_ClearFpuStatusAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg

	mov	BReg,[STACK_PTR1]

	fnstsw	ax
	
	cmp	ax,0
	jz	ClearFpuStatusOk

	fnclex

ClearFpuStatusOk:

	mov	[BReg],ax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]

	ret

;;;
;;; FloatLerpAsm
;;;
;;; Call Stack
;;;
;;; [3] x
;;; [2] v
;;; [1] u
;;; [0] ret
;;;
;;; Calculation:	 u * (1-x) + x * v
;;;
;;; extern "C" float FloatLerpAsm(const float x,const float v,const float u)
;;;

_FloatLerpAsm:
	fld1
	fld	dword [STACK_PTR3]	; step (x)
	fsubp	st1,st0			; 1-x
	fmul	dword [STACK_PTR1]	; u*(1-x)
	fld	dword [STACK_PTR3]	; x
	fmul	dword [STACK_PTR2]	; x*v
	faddp	st1,st0			; u*(1-x)+x*v

	ret

;;;
;;; FloatLerpPtrAsm
;;;
;;; Call Stack
;;;
;;; [4] float Step
;;; [3] float End Point
;;; [2] float Start Point
;;; [1] ret
;;;
;;; Calculation:	(*u) * (1 - (*x)) + (*x) * (*v)
;;;
;;; extern "C" void FloatLerpPtrAsm(float* ret,
;;;                                 const float* u,
;;;                                 const float* v,
;;;                                 const float* x)
;;; 

_FloatLerpPtrAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	CReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	AReg,[STACK_PTR4]	; *x

	fld1				; [0] 1.0
	fld	dword [AReg]		; [0] x [1] 1.0
	fsubp	st1,st0			; [0] 1.0 - x
	fmul	dword [CReg]		; [0] u*(1-x)

	fld	dword [AReg]		; [0] x [1] u*(1-x)
	fmul	dword [BReg]		; [0] v*x [1] u*(1-x)
	faddp	st1,st0			; [0] u*(1-x) + x*v

	fstp	dword [DReg]		; *r = u*(1-x) + x*v
	
	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	
	ret

;;;
;;; FloatSqrAsm
;;; 
;;; float = float * float
;;;
;;; Call Stack
;;; [1] x
;;; [0] ret
;;;
;;; Calculation:	x * x
;;; 
;;; extern "C" float FloatSqrAsm(float x)
;;; 

_FloatSqrAsm:
	fld	dword [STACK_PTR1]	; x
	fmul	dword [STACK_PTR1]
	ret

;;;
;;; FloatSqrPtrAsm
;;;
;;; float = (*float) * (*float)
;;;
;;; CallStack
;;; [1] *x
;;; [0] ret
;;;
;;; Calculation:	(*x) * (*x)
;;;
;;; extern "C" float FloatSqrPtrAsm(float* x)
;;;

_FloatSqrPtrAsm:
	mov	[STACK_SAVE1],AReg
	mov	AReg,[STACK_PTR1]
	fld	dword [AReg]
	fmul	dword [AReg]
	mov	AReg,[STACK_SAVE1]
	ret

;;;
;;; fCosAsm
;;;
;;; Call Stack
;;;
;;; [1] float angle
;;;
;;; extern "C" float fCosAsm(float angle)
;;;

_fCosAsm:
	fld	dword [STACK_PTR1]
	fcos
	ret

;;;
;;; CosAsm
;;;
;;; Call Stack
;;;
;;; [1] double angle
;;;
;;; extern "C" double CosAsm(float angle)
;;;

_CosAsm:
	fld	qword [STACK_PTR1]
	fcos
	ret

;;;
;;; AfCosAsm
;;;
;;; Call Stack
;;;
;;; [1] float cos(angle)
;;;
;;; extern "C" float AfCosAsm(float cosa)
;;;

_AfCosAsm:
	fld1
	fld	dword [STACK_PTR1]	; [0] cosa [1] 1.0
	fmul	st0,st0			; [0] sqr(cosa) [1] 1.0
	fsubp	st1,st0			; sqr(sin) = 1 - sqr(cosa)
	fsqrt				; [0] sin = sqrt(1-sqr(cosa))
	fld	dword [STACK_PTR1]	; [0] cosa [1] sina
	fpatan				; [0] angle

	ret

;;;
;;; ACosAsm
;;;
;;; Call Stack
;;;
;;; [1] double cos
;;;
;;; extern "C" double ACosAsm(double cosa)
;;;

_ACosAsm:
	fld1
	fld	qword [STACK_PTR1]	; [0] cosa [1] 1.0
	fmul	st0,st0			; [0] sqr(cosa) [1] 1.0
	fsubp	st1,st0			; sqr(sin) = 1 - sqr(cosa)
	fsqrt				; [0] sin = sqrt(1-sqr(cosa))
	fld	qword [STACK_PTR1]	; [0] cosa [1] sina
	fpatan				; [0] angle

	ret

;;;
;;; fSinAsm
;;;
;;; Call Stack
;;;
;;; [1] float angle
;;;
;;; extern "C" float fSinAsm(float angle)
;;;

_fSinAsm:
	fld	dword [STACK_PTR1]
	fsin
	ret

;;;
;;; SinAsm
;;;
;;; Call Stack
;;;
;;; [1] double angle
;;;
;;; extern "C" double SinAsm(double angle)
;;;

_SinAsm:
	fld	qword [STACK_PTR1]
	fsin
	ret

;;;
;;; AfSinAsm
;;;
;;; Call Stack
;;;
;;; [1] float sin(angle)
;;;
;;; extern "C" float ASinAsm(float sina) 
;;;

_AfSinAsm:
	fld	dword [STACK_PTR1]	; [0] sina
	fld1				; [0] 1.0 [1] sina
	fld	st1			; [0] sina [1] 1.0 [2] sina
	fmul	st0,st0			; [0] sqr(sina) [1] 1.0 [2] sina
	fsubp	st1,st0			; [0] sqr(cosa) = 1.0 - sqr(sina) [1] sina
	fsqrt				; [0] cosa [1] sina
	fpatan				; [0] angle

	ret

;;;
;;; ASinAsm
;;;
;;; Call Stack
;;;
;;; [1] double sin(angle)
;;;
;;; extern "C" double ASinAsm(double sina) 
;;;

_ASinAsm:
	fld	qword [STACK_PTR1]	; [0] sina
	fld1				; [0] 1.0 [1] sina
	fld	st1			; [0] sina [1] 1.0 [2] sina
	fmul	st0,st0			; [0] sqr(sina) [1] 1.0 [2] sina
	fsubp	st1,st0			; [0] sqr(cosa) = 1.0 - sqr(sina) [1] sina
	fsqrt				; [0] cosa [1] sina
	fpatan				; [0] angle

	ret

;;;
;;; fTanAsm
;;;
;;; Call Stack
;;;
;;; [1] float angle
;;;
;;; extern "C" float fTanAsm(float angle)
;;;

_fTanAsm:
	fld	dword [STACK_PTR1]
	fsincos
	fdivp	st1,st0
	ret

;;;
;;; TanAsm
;;;
;;; Call Stack
;;;
;;; [1] double angle
;;;
;;; extern "C" double TanAsm(double angle)
;;;

_TanAsm:
	fld	qword [STACK_PTR1]
	fsincos
	fdivp	st1,st0
	ret

;;;
;;; AfTanAsm
;;;
;;; Call Stack
;;;
;;; [1] float tan(angle)
;;;
;;; extern "C" float ATanAsm(float tana) 
;;;

_AfTanAsm:
	fld	dword [STACK_PTR1]	; [0] tana
	fld1				; [0] 1.0 [1] tana
	fpatan				; [0] angle

	ret

;;;
;;; ATanAsm
;;;
;;; Call Stack
;;;
;;; [1] double tan(angle)
;;;
;;; extern "C" double ATanAsm(double tana) 
;;;

_ATanAsm:
	fld	qword [STACK_PTR1]	; [0] tana
	fld1				; [0] 1.0 [1] tana
	fpatan				; [0] angle

	ret

;;;
;;; Vec2CopyAsm
;;;
;;; Call Stack
;;;
;;; [2] vec2 Source * (through reference)
;;; [1] vec2 Dest   * (through reference)
;;; [0] ret
;;;
;;; extern "C" void Vec2CopyAsm(vec2& r,const vec2& v)
;;; 

_Vec2CopyAsm:
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]
	mov	ecx,[DReg]
	mov	[AReg],ecx
	mov	ecx,[DReg+4]
	mov	[AReg+4],ecx
	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2CopyBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount  
;;; [2] vec2    Source *
;;; [1] vec2    Dest   *
;;; [0] ret
;;;
;;; extern "C" void Vec2CopyBlockAsm(vec2* r,vec2* v,int32_t iCount)
;;;

_Vec2CopyBlockAsm:
	mov	[STACK_SAVE1],Srcp
	mov	[STACK_SAVE2],Dstp
	mov	[STACK_SAVE3],CReg

	mov	Srcp,[STACK_PTR2]
	mov	Dstp,[STACK_PTR1]
	mov	ecx,[STACK_PTR3]
	shl	ecx,1

	cld
	rep	movsd

	mov	Srcp,[STACK_SAVE1]
	mov	Dstp,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	ret

;;;
;;; BuildVec2PackedArrayAsm
;;;
;;; [3] int32_t iCount
;;; [2] vec2**	ppList
;;; [1] vec2*   r
;;; [0] ret
;;;
;;; extern "C" void BuildVec2PackedArrayAsm(vec2* r,const vec2** ppList,const int32_t iCount)
;;;

_BuildVec2PackedArrayAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	BReg,[STACK_PTR2]	; ppList
	mov	ecx, [STACK_PTR3]	; iCount
	mov	DReg,[STACK_PTR1]	; *r

BuildVec2PackedArrayLoop:

	mov	AReg,[BReg]		; *ppList

	mov	Srcp,[AReg]		; x
	mov	[DReg],Srcp
	mov	Srcp,[AReg+4]		; y
	mov	[DReg+4],Srcp

	add	BReg,PtrSize
	add	DReg,Vec2Size

	dec	ecx
	jnz	BuildVec2PackedArrayLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1   || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	
;;;
;;; Vec2AddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float
;;; [2] vec2*
;;; [1] Save ptr
;;; [0] ret
;;;
;;; vec2 += float
;;; vec2 = vec2 + float
;;;
;;;  extern "C" void Vec2AddFloatAsm(vec2& r,const vec2& u,const float s)
;;; 

_Vec2AddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; u
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	addps	xmm0,xmm1		; (*u) + s
	movhps	[DReg],xmm0		; *r = *u + s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2SubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float
;;; [2] vec2* u
;;; [1] vec2* r
;;; [0] ret
;;;
;;; extern "C" void Vec2SubtractFloatAsm(vec2& r,const vec2& u,const float s)
;;; 

_Vec2SubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; (*u)
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	subps	xmm0,xmm1		; (*u) - s
	movhps	[DReg],xmm0		; *r = *u - s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2MultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float
;;; [2] vec2*
;;; [1] Save ptr
;;; [0] ret
;;;
;;; extern "C" void Vec2MultiplyFloatAsm(vec2& r,const vec2& u,const float s)
;;; 

_Vec2MultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; u
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	mulps	xmm0,xmm1		; u * s
	movhps	[DReg],xmm0		; r = u * s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2FloatMultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2* u
;;; [2] float s
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 = float * vec2
;;;
;;; extern "C" void Vec2FloatMultiplyAsm(vec2& r,const float s,const vec2& v)
;;; 

_Vec2FloatMultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; u
	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0
	mulps	xmm0,xmm1		; u * s
	movhps	[DReg],xmm0		; r = u * s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2DivideFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float
;;; [2] vec2*
;;; [1] Save ptr
;;; [0] ret
;;;
;;; extern "C" void Vec2DivideFloatAsm(vec2& r,const vec2& u,const float s)
;;; 

_Vec2DivideFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR3]	; s
	ucomiss	xmm1,[zeroVec]

	jz	Vec2DivideFloatBy0

	movhps	xmm0,[AReg]		; u
	shufps	xmm1,xmm1,0		; s
	divps	xmm0,xmm1		; u / s

	movhps	[DReg],xmm0		; r = u / s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec2DivideFloatBy0:

	mov	eax,[zeroVec]		; zero out return vec
	mov	[DReg],eax
	mov	[DReg+4],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2AddFloat_FPUAsm
;;;
;;; Call Stack
;;;
;;; [3] float
;;; [2] vec2*
;;; [1] Save ptr
;;; [0] ret
;;;
;;; vec2 += float
;;; vec2 = vec2 + float
;;;
;;;  extern "C" void Vec2AddFloat_FPUAsm(vec2& r,const vec2& u,const float s)
;;; 

_Vec2AddFloatFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR1]

	fld	dword [AReg+4]		; u.y
	fld	dword [STACK_PTR3]	; s
	fadd	st1,st0			; u.y + s
	fadd	dword [AReg]		; s + u.x

	fstp	dword [DReg]		; *r.x
	fstp	dword [DReg+4]		; *r.y

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2SubtractFloat_FPUAsm
;;;
;;; Call Stack
;;;
;;; [3] float
;;; [2] vec2* u
;;; [1] vec2* r
;;; [0] ret
;;;
;;; extern "C" void Vec2SubtractFloat_FPUAsm(vec2& r,const vec2& u,const float s)
;;; 

_Vec2SubtractFloatFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [AReg+4]		; u.y
	fld	dword [STACK_PTR3]	; s
	fsub	st1,st0			; u.y - s
	fsubr	dword [AReg]		; s - u.x
	
	fstp	dword [DReg]		; *r.x = s + u.x
	fstp	dword [DReg+4]		; *r.y = u.y + s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2MultiplyFloat_FPUAsm
;;;
;;; Call Stack
;;;
;;; [3] float
;;; [2] vec2*
;;; [1] Save ptr
;;; [0] ret
;;;
;;; extern "C" void Vec2MultiplyFloat_FPUAsm(vec2& r,const vec2& u,const float s)
;;; 

_Vec2MultiplyFloatFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [AReg+4]		; u.y
	fld	dword [STACK_PTR3]	; s
	fmul	st1,st0			; u.y * s
	fmul	dword [AReg]		; s * u.x

	fstp	dword [DReg]		; r.x = s * u.x
	fstp	dword [DReg+4]		; r.y = s * u.y

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2FloatMultiply_FPUAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2* u
;;; [2] float s
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 = float * vec2
;;;
;;; extern "C" void Vec2FloatMultiply_FPUAsm(vec2& r,const float s,const vec2& v)
;;; 

_Vec2FloatMultiplyFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [AReg+4]		; u.y
	fld	dword [STACK_PTR2]	; s
	fmul	st1,st0			; u.y * s
	fmul	dword [AReg]		; s * u.x

	fstp	dword [DReg]		; r.x = s * u.x
	fstp	dword [DReg+4]		; r.y = u.y * s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2DivideFloat_FPUAsm
;;;
;;; Call Stack
;;;
;;; [3] float
;;; [2] vec2*
;;; [1] Save ptr
;;; [0] ret
;;;
;;; extern "C" void Vec2DivideFloat_FPUAsm(vec2& r,const vec2& u,const float s)
;;; 

_Vec2DivideFloatFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR3]	; s
	fldz
	fcomip	st0,st1

	jz	Vec2DivideFloatFPUBy0

	fld	dword [AReg+4]		; [0] u.y [1] s
	fdiv	st0,st1			; [0] u.y / s [1] s
	fld	dword [AReg]		; [0] u.x [1] u.y/s [2] s
	fdivrp  st2,st0			; [0] u.y/s [1] u.x / s

	fstp	dword [DReg+4]		; r.x = u.x / s
	fstp	dword [DReg]		; r.y = u.y / s

	;; 	ffree	st0			; pitch s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec2DivideFloatFPUBy0:

	ffree	st0

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2AddFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2AddFloatToBlockAsm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2AddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *rv

	mov	ecx,[STACK_PTR3]	; iCount
	mov	eax,ecx

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	cmp	ecx,2
	jl	Vec2AddFloatToBlockExtra

	shr	ecx,1

Vec2AddFloatToBlockLoop:

	movaps	xmm0,[DReg]		; v
	addps	xmm0,xmm1		; v + s
	movaps	[DReg],xmm0		; r = v + s

	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2AddFloatToBlockLoop

Vec2AddFloatToBlockExtra:

	test	eax,1
	jz	Vec2AddFloatToBlockEnd

	movhps	xmm0,[DReg]		; v
	addps	xmm0,xmm1		; v + s
	movhps	[DReg],xmm0		; r = v + s

Vec2AddFloatToBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 ||__BUILD_ALL == 1)

;;;
;;; Vec2uAddFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2uAddFloatToBlockAsm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2uAddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *rv

	mov	ecx,[STACK_PTR3]	; iCount
	mov	eax,ecx

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	cmp	ecx,2
	jl	Vec2uAddFloatToBlockExtra

	shr	ecx,1

Vec2uAddFloatToBlockLoop:

	movups	xmm0,[DReg]		; v
	addps	xmm0,xmm1		; v + s
	movups	[DReg],xmm0		; r = v + s

	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2uAddFloatToBlockLoop

Vec2uAddFloatToBlockExtra:

	test	eax,1
	jz	Vec2uAddFloatToBlockEnd

	movhps	xmm0,[DReg]		; v
	addps	xmm0,xmm1		; v + s
	movhps	[DReg],xmm0		; r = v + s

Vec2uAddFloatToBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2AddFloatToBlockFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2AddFloatToBlockFPU_Asm(vec2* rv,const float s,const int32_t iCount)
;;;
	
_Vec2AddFloatToBlockFPU_Asm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *pv

	mov	ecx,[STACK_PTR3]	; iCount

	fld	dword [STACK_PTR2]	; s

Vec2AddFloatToBlockFPULoop:

	fld	dword [DReg+4]		; v.y
	fadd	st0,st1			; v.y * s
	fld	dword [DReg]		; v.x
	fadd	st0,st2			; v.x * s
	fstp	dword [DReg]		; r.x = v.x * s
	fstp	dword [DReg+4]		; r.y = v.y * s

	add	DReg,Vec2Size

	dec	ecx
	jnz	Vec2AddFloatToBlockFPULoop

	ffree	st0

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1   || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2AddFloatToBlockSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; extern "C" void Vec2AddFloatToBlockSizeAsm(vec2*       rv,
;;;                                            const float s,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec2AddFloatToBlockSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	eax, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	DReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec2AddStepLoop:

	movhps	xmm0,[DReg]		; v
	addps	xmm0,xmm1		; v + s
	movhps	[DReg],xmm0		; r = v + s

	add	DReg,eax

	dec	ecx
	jnz	Vec2AddStepLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufAddFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float
;;; [2] vec2*   pSource
;;; [1] vec2*   pDest
;;; [0] ret
;;;
;;; extern "C" void Vec2BufAddFloatToBlockAsm(void*       r,
;;;                                           const void* v,
;;;                                           const float s,
;;;                                           const int32_t iSize
;;;                                           const int32_t iCount);
;;;

_Vec2BufAddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	eax, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]
	shufps	xmm0,xmm0,0

Vec2BufAddBlockFloatLoop:

	movhps	xmm1,[BReg]		; v
	addps	xmm1,xmm0		; v + s
	movhps	[DReg],xmm1		; r = v + s

	add	BReg,eax		; *v += iSize
	add	DReg,eax		; *r += iSize

	dec	ecx
	jnz	Vec2BufAddBlockFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2BufAddFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iSrcSize
;;; [3] vec2*   pSource
;;; [2] int32_t iDestSize
;;; [1] vec2*   pDest
;;; [0] ret
;;;
;;; extern "C" void Vec2BufAddFloatToBufAsm(void*         r
;;;                                         const int32_t iRSize,
;;;                                         const void*   v,
;;;                                         const int32_t iVSize,
;;;                                         const float   s,
;;;                                         const int32_t iCount);
;;;

_Vec2BufAddFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	ebx,[STACK_PTR2]	; iDestSize
	mov	ebp,[STACK_PTR4]	; iSrcSize
	mov	ecx,[STACK_PTR6]	; iCount

	mov	AReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec2BufAddFloatToBufLoop:

	movhps	xmm0,[AReg]		; v
	addps	xmm0,xmm1		; v + s
	movhps	[DReg],xmm0		; r = v + s

	add	AReg,ebp		; *v += iSrcSize
	add	DReg,ebx		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufAddFloatToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2AddFloatToBlockSizeFPU_Asm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; extern "C" void Vec2AddFloatToBlockSizeFPU_Asm(vec2*       rv,
;;;                                                const float s,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec2AddFloatToBlockSizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	eax,[STACK_PTR3]	; iSize
	mov	ecx,[STACK_PTR4]	; iCount

	mov	DReg,[STACK_PTR1]	; *rv

	fld	dword [STACK_PTR2]	; s

Vec2AddStepFPULoop:

	fld	dword [DReg+4]		; v.y
	fadd	st0,st1			; v.y + s
	fld	dword [DReg]		; v.x
	fadd	st0,st2			; v.x + s
	fstp	dword [DReg]		; r.x = v.x + s
	fstp	dword [DReg+4]		; r.y = v.y + s

	add	DReg,eax		; *rv += offset

	dec	ecx
	jnz	Vec2AddStepFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufAddFloatToBlockFPU_Asm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float
;;; [2] vec2*   pSource
;;; [1] vec2*   pDest
;;; [0] ret
;;;
;;; extern "C" void Vec2BufAddFloatToBlockFPU_Asm(void*       r,
;;;                                               const void* v,
;;;                                               const float s,
;;;                                               const int32_t iSize
;;;                                               const int32_t iCount);
;;;

_Vec2BufAddFloatToBlockFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	eax,[STACK_PTR4]	; iSize
	mov	ecx,[STACK_PTR5]	; iCount

	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR3]	; s

Vec2BufAddBlockFloatFPULoop:

	fld	dword [BReg+4]		; v.y
	fadd	st0,st1			; v.y + s
	fld	dword [BReg]		; v.x
	fadd	st0,st2			; v.x + s

	fstp	dword [DReg]		; r.x = v.x + s
	fstp	dword [DReg+4]		; r.y = v.y + s

	add	BReg,eax		; *v += offset
	add	DReg,eax		; *r += offset

	dec	ecx
	jnz	Vec2BufAddBlockFloatFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2BufAddFloatToBufFPU_Asm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float
;;; [4] int32_t iSrcSize
;;; [3] vec2*   pSource
;;; [2] int32_t iDestSize
;;; [1] vec2*   pDest
;;; [0] ret
;;;
;;; extern "C" void Vec2BufAddFloatToBufFPU_Asm(void*         r
;;;                                             const int32_t iRSize,
;;;                                             const void*   v,
;;;                                             const int32_t iVSize,
;;;                                             const float   s,
;;;                                             const int32_t iCount);
;;;

_Vec2BufAddFloatToBufFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	eax,[STACK_PTR2]	; iDstSize
	mov	ebx,[STACK_PTR4]	; iSrcSize
	mov	ecx,[STACK_PTR6]	; iCount

	mov	Srcp,[STACK_PTR3]	; *v
	mov	Dstp,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR5]	; s

Vec2BufAddFloatToBufFPULoop:

	fld	dword [Srcp+4]		; v.x
	fadd	st0,st1			; v.x + s
	fld	dword [Srcp]		; v.y
	fadd	st0,st2			; v.y + s

	fstp	dword [Dstp]		; r.x = v.x + s
	fstp	dword [Dstp+4]		; r.y = v.y + s

	add	Srcp,ebx		; *v += iSrcSize
	add	Dstp,eax		; *r += iDstSize

	dec	ecx

	jnz	Vec2BufAddFloatToBufFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2SubtractFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2SubtractFloatFromBlockAsm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2SubtractFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	eax, ecx
	mov	DReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	cmp	ecx,2
	jl	Vec2SubFloatFromBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2SubFloatFromBlockLoop:

	movaps	xmm0,[DReg]		; v v
	subps	xmm0,xmm1		; v-s v-s
	movaps	[DReg],xmm0		; r=v-s r=v-s

	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2SubFloatFromBlockLoop

Vec2SubFloatFromBlockExtra:

	test	eax,1
	jz	Vec2SubFloatFromBlockEnd

	movhps	xmm0,[DReg]			; v
	subps	xmm0,xmm1			; v + s
	movhps	[DReg],xmm0			; r = v + s

Vec2SubFloatFromBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uSubtractFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2uSubtractFloatFromBlockAsm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2uSubtractFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	eax, ecx
	mov	DReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	cmp	ecx,2
	jl	Vec2uSubFloatFromBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2uSubFloatFromBlockLoop:

	movups	xmm0,[DReg]		; v v
	subps	xmm0,xmm1		; v-s v-s
	movups	[DReg],xmm0		; r=v-s r=v-s

	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2uSubFloatFromBlockLoop

Vec2uSubFloatFromBlockExtra:

	test	eax,1
	jz	Vec2uSubFloatFromBlockEnd

	movhps	xmm0,[DReg]			; v
	subps	xmm0,xmm1			; v + s
	movhps	[DReg],xmm0			; r = v + s

Vec2uSubFloatFromBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2SubtractFloatFromBlockFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2uSubtractFloatFromBlockFPU_Asm(vec2* rv,const float s,const int32_t iCount)
;;;
	
_Vec2SubtractFloatFromBlockFPU_Asm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	DReg,[STACK_PTR1]	; *rv

	fld	dword [STACK_PTR2]	; s

Vec2SubFloatBlockFPULoop:

	fld	dword [DReg+4]		; v.y
	fsub	st0,st1			; v.y + s
	fld	dword [DReg]		; v.x
	fsub	st0,st2			; v.x + s
	fstp	dword [DReg]		; r.x = v.x + s
	fstp	dword [DReg+4]		; r.y = v.y + s

	add	DReg,Vec2Size		; *rv += offset

	dec	ecx
	jnz	Vec2SubFloatBlockFPULoop

	ffree	st0			; dump s

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2SubFloatFromBlockSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2SubFloatFromBlockSizeAsm(vec2*       rv,
;;;                                              const float s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec2SubFloatFromBlockSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	eax, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	ebx, ecx
	mov	DReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec2SubBlockSizeLoop:

	movhps	xmm0,[DReg]		; v
	subps	xmm0,xmm1		; v - s
	movhps	[DReg],xmm0		; r = v - s

	add	DReg,eax		; *rv += offset

	dec	ecx
	jnz	Vec2SubBlockSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufSubFloatFromBlkSizeAsm
;;;
;;; Call Stack
;;; 
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   v
;;; [1] void*	r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufSubFloatFromBlkSizeAsm(void*       r,
;;;                                               const void* v,
;;;                                               const float s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec2BufSubFloatFromBlkSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	eax, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

Vec2BufSubBlockLoop:

	movhps	xmm1,[BReg]		; v
	subps	xmm1,xmm0		; v - s
	movhps	[DReg],xmm1		; r = v - s

	add	BReg,eax		; *v += iSize
	add	DReg,eax		; *r += iSize

	dec	ecx
	jnz	Vec2BufSubBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2BufSubFloatFromBufAsm
;;;
;;; Call Stack
;;; 
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iSrcSize
;;; [3] void*   v
;;; [2] int32_t iDstSize
;;; [1] void*	r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufSubFloatFromBufAsm(void*         pDest,
;;;                                           const int32_t iDstSize,
;;;                                           const void*   pSource,
;;;                                           const int32_t iSrcSize,
;;;                                           const float s,
;;;                                           const int32_t iCount);
;;;

_Vec2BufSubFloatFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	eax, [STACK_PTR2]	; iDstSize
	mov	ebx, [STACK_PTR4]	; iSrcSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	Srcp,[STACK_PTR3]	; *v
	mov	Dstp,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec2BufSubFloatFromBufLoop:

	movhps	xmm0,[Srcp]		; v
	subps	xmm0,xmm1		; v - s
	movhps	[Dstp],xmm0		; r = v - s

	add	Srcp,ebx		; *v += iSrcSize
	add	Dstp,eax		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufSubFloatFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2SubFloatFromBlockSizeFPU_Asm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2SubFloatFromBlockSizeFPU_Asm(vec2*       rv,
;;;                                                 const float s,
;;;                                                 const int32_t iSize,
;;;                                                 const int32_t iCount);
;;;

_Vec2SubFloatFromBlockSizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *rv
	mov	eax, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	fld	dword [STACK_PTR2]	; s

Vec2SubBlockSizeFPULoop:

	fld	dword [DReg+4]		; v.y
	fsub	st0,st1			; v.y - s
	fld	dword [DReg]		; v.x
	fsub	st0,st2			; v.x - s

	fstp	dword [DReg]		; r.x = v.x - s
	fstp	dword [DReg+4]		; r.y = v.y - s

	add	DReg,eax		; *rv += offset

	dec	ecx
	jnz	Vec2SubBlockSizeFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufSubFloatFromBlkSizeFPU_Asm
;;;
;;; Call Stack
;;; 
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   v
;;; [1] void*	r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufSubFloatFromBlkSizeFPU_Asm(void*       r,
;;;                                                   const void* v,
;;;                                                   const float s,
;;;                                                   const int32_t iSize,
;;;                                                   const int32_t iCount);
;;;

_Vec2BufSubFloatFromBlkSizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	eax, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR3]	; s

Vec2BufSubBlockFPULoop:

	fld	dword [BReg+4]		; v.y
	fsub	st0,st1			; v.y - s
	fld	dword [BReg]		; v.x
	fsub	st0,st2			; v.x - s

	fstp	dword [DReg]		; r = v.x - s
	fstp	dword [DReg+4]		; r = v.y - s

	add	BReg,eax		; *v += iSize
	add	DReg,eax		; *r += iSize

	dec	ecx
	jnz	Vec2BufSubBlockFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret
	
;;;
;;; Vec2BufSubFloatFromBufFPU_Asm
;;;
;;; Call Stack
;;; 
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iSrcSize
;;; [3] void*   v
;;; [2] int32_t iDstSize
;;; [1] void*	r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufSubFloatFromBufFPU_Asm(void*         pDest,
;;;                                               const int32_t iDstSize,
;;;                                               const void*   pSource,
;;;                                               const int32_t iSrcSize,
;;;                                               const float s,
;;;                                               const int32_t iCount);
;;;

_Vec2BufSubFloatFromBufFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	eax, [STACK_PTR2]	; iDstSize
	mov	ebx, [STACK_PTR4]	; iSrcSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	Srcp,[STACK_PTR3]	; *v
	mov	Dstp,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR5]	; s

Vec2BufSubFloatFromBufFPULoop:

	fld	dword [Srcp+4]		; v.y
	fsub	st0,st1			; v.y - s
	fld	dword [Srcp]		; v.x
	fsub	st0,st2			; v.y - s
	fstp	dword [Dstp]		; r.x = v.x - s
	fstp	dword [Dstp+4]		; r.y = v.y - s

	add	Srcp,ebx		; *v += iSrcSize
	add	Dstp,eax		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufSubFloatFromBufFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2MultiplyBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2MultiplyBlockByFloatAsm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2MultiplyBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	eax, ecx
	mov	DReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	cmp	ecx,2
	jl	Vec2MulBlockByFloatExtra

	shr	ecx,1			; iCount /= 2

Vec2MulBlockByFloatLoop:

	movaps	xmm0,[DReg]		; v v
	mulps	xmm0,xmm1		; v*s v*s
	movaps	[DReg],xmm0		; r=v*s r=v*s

	add	DReg,2*Vec2Size		; *rv += offset

	dec	ecx
	jnz	Vec2MulBlockByFloatLoop

Vec2MulBlockByFloatExtra:

	test	eax,1
	jz	Vec2MulBlockByFloatEnd

	movhps	xmm0,[DReg]		; v
	mulps	xmm0,xmm1		; v * s
	movhps	[DReg],xmm0		; r = v * s

Vec2MulBlockByFloatEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uMultiplyBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2uMultiplyBlockByFloatAsm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2uMultiplyBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	eax, ecx
	mov	DReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	cmp	ecx,2
	jl	Vec2uMulBlockByFloatExtra

	shr	ecx,1			; iCount /= 2

Vec2uMulBlockByFloatLoop:

	movups	xmm0,[DReg]		; v v
	mulps	xmm0,xmm1		; v*s v*s
	movups	[DReg],xmm0		; r=v*s r=v*s

	add	DReg,2*Vec2Size		; *rv += offset

	dec	ecx
	jnz	Vec2uMulBlockByFloatLoop

Vec2uMulBlockByFloatExtra:

	test	eax,1
	jz	Vec2uMulBlockByFloatEnd

	movhps	xmm0,[DReg]		; v
	mulps	xmm0,xmm1		; v * s
	movhps	[DReg],xmm0		; r = v * s

Vec2uMulBlockByFloatEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2MultiplyBlockByFloatFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2MultiplyBlockByFloatFPU_Asm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2MultiplyBlockByFloatFPU_Asm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	DReg,[STACK_PTR1]	; *rv

	fld	dword [STACK_PTR2]	; s

Vec2MulBlockFPULoop:

	fld	dword [DReg+4]		; v.y
	fmul	st0,st1			; v.y * s
	fld	dword [DReg]		; v.x
	fmul	st0,st2			; v.x * s
	fstp	dword [DReg]		; r.x = v.x * s
	fstp	dword [DReg+4]		; r.y = v.y * s

	add	DReg,Vec2Size

	dec	ecx
	jnz	Vec2MulBlockFPULoop

	ffree	st0			; dump s

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2MultiplyBlockByFloatSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] vec2*   *rv
;;; [0] ret
;;;
;;; extern "C" void Vec2MultiplyBlkByFloatSizeAsm(void*       rv,
;;;                                               const float s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec2MultiplyBlkByFloatSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	eax, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	DReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec2MultiplyBlockSizeLoop:

	movhps	xmm0,[DReg]		; v
	mulps	xmm0,xmm1		; v * s
	movhps	[DReg],xmm0		; r = v * s

	add	DReg,eax		; *rv += iSize

	dec	ecx
	jnz	Vec2MultiplyBlockSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufMulBlockByFloatSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   pDest
;;; [1] void*   pSource
;;; [0] ret
;;;
;;; extern "C" void Vec2BufMulBlockByFloatSizeAsm(void*       r,
;;;                                               const void* v
;;;                                               const float s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec2BufMulBlockByFloatSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	eax, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

Vec2BufMulBlockByFloatLoop:

	movhps	xmm1,[BReg]		; v
	mulps	xmm1,xmm0		; v * s
	movhps	[DReg],xmm1		; r = v * s

	add	BReg,eax		; *v += iSize
	add	DReg,eax		; *r += iSize

	dec	ecx
	jnz	Vec2BufMulBlockByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2BufMulBlockByFloatBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iSrcSize
;;; [3] void*   v
;;; [2] int32_t iDstSize
;;; [1] void*   r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufMulBlockByFloatBufAsm(void*         r,
;;;                                              const int32_t iDstSize
;;;                                              const void*   v,
;;;                                              const int32_t iSrcSize,
;;;                                              const float s,
;;;                                              const int32_t iCount);
;;;

_Vec2BufMulBlockByFloatBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	eax, [STACK_PTR2]	; iDstSize
	mov	ebx, [STACK_PTR4]	; iSrcSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	Srcp,[STACK_PTR3]	; *v
	mov	Dstp,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec2BufMulBlockByFloatBufLoop:

	movhps	xmm0,[Srcp]		; v
	mulps	xmm0,xmm1		; v * s
	movhps	[Dstp],xmm0		; r = v * s

	add	Srcp,ebx		; *v += iSrcSize
	add	Dstp,eax		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufMulBlockByFloatBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2MultiplyBlockByFloatSizeFPU_Asm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] vec2*   *rv
;;; [0] ret
;;;
;;; extern "C" void Vec2MultiplyBlkByFloatSizeFPU_Asm(void*       rv,
;;;                                                   const float s,
;;;                                                   const int32_t iSize,
;;;                                                   const int32_t iCount);
;;;

_Vec2MultiplyBlkByFloatSizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	eax, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	DReg,[STACK_PTR1]	; *rv

	fld	dword [STACK_PTR2]	; s

Vec2MulBlockSizeFPULoop:

	fld	dword [DReg+4]		; v.y
	fmul	st0,st1			; v.y * s
	fld	dword [DReg]		; v.x
	fmul	st0,st2			; v.x * s
	fstp	dword [DReg]		; r.x = v.x * s
	fstp	dword [DReg+4]		; r.y = v.y * s

	add	DReg,eax		; *rv += iSize

	dec	ecx
	jnz	Vec2MulBlockSizeFPULoop

	ffree	st0

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret
	
;;;
;;; Vec2BufMulBlockByFloatSizeFPU_Asm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   pDest
;;; [1] void*   pSource
;;; [0] ret
;;;
;;; extern "C" void Vec2BufMulBlockByFloatSizeFPU_Asm(void*       r,
;;;                                                   const void* v
;;;                                                   const float s,
;;;                                                   const int32_t iSize,
;;;                                                   const int32_t iCount);
;;;

_Vec2BufMulBlockByFloatSizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	eax, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR3]	; s

Vec2BufMulBlockByFloatFPULoop:

	fld	dword [BReg+4]		; v.x
	fmul	st0,st1			; v.x * s
	fld	dword [BReg]		; v.y
	fmul	st0,st2			; v.y * s

	fstp	dword [DReg]		; r.x = v.x * s
	fstp	dword [DReg+4]		; r.y = v.y ( s

	add	BReg,eax		; *v += iSize
	add	DReg,eax		; *r += iSize

	dec	ecx
	jnz	Vec2BufMulBlockByFloatFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2BufMulBlockByFloatBufFPU_Asm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iSrcSize
;;; [3] void*   v
;;; [2] int32_t iDstSize
;;; [1] void*   r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufMulBlockByFloatBufFPU_Asm(void*         r,
;;;                                                  const int32_t iDstSize
;;;                                                  const void*   v,
;;;                                                  const int32_t iSrcSize,
;;;                                                  const float s,
;;;                                                  const int32_t iCount);
;;;

_Vec2BufMulBlockByFloatBufFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	eax, [STACK_PTR2]	; iDstSize
	mov	ebx, [STACK_PTR4]	; iSrcSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	Srcp,[STACK_PTR3]	; *v
	mov	Dstp,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR5]	; s

Vec2BufMulBlockByFloatBufFPULoop:

	fld	dword [Srcp+4]		; v.y
	fmul	st0,st1			; v.y * s
	fld	dword [Srcp]		; v.x
	fmul	st0,st2			; v.x * s

	fstp	dword [Dstp]		; r.x = v.x * s
	fstp	dword [Dstp+4]		; r.y = v.y * s

	add	Srcp,ebx		; *v += iSrcSize
	add	Dstp,eax		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufMulBlockByFloatBufFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2DivideBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2DivideBlockByFloatAsm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2DivideBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	movss	xmm1,[STACK_PTR2]	; s
	ucomiss	xmm1,[zeroVec]

	jz	Vec2DivBlockByFloatError

	mov	ecx, [STACK_PTR3]	; iCount
	mov	eax, ecx
	mov	DReg,[STACK_PTR1]	; *rv

	shufps	xmm1,xmm1,0

	cmp	ecx,2
	jl	Vec2DivBlockByFloatExtra

	shr	ecx,1			; iCount /= 2

Vec2DivBlockByFloatLoop:

	movaps	xmm0,[DReg]		; v v
	divps	xmm0,xmm1		; v/s v/s
	movaps	[DReg],xmm0		; r=v/s r=v/s

	add	DReg,2*Vec2Size		; *rv += iSize

	dec	ecx
	jnz	Vec2DivBlockByFloatLoop

Vec2DivBlockByFloatExtra:

	test	eax,1
	jz	Vec2DivBlockByFloatError

	movhps	xmm0,[DReg]		; v
	divps	xmm0,xmm1		; v / s
	movhps	[DReg],xmm0		; r = v / s

Vec2DivBlockByFloatError:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uDivideBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2uDivideBlockByFloatAsm(vec2* rv,const float s,const int32_t iCount)
;;;

_Vec2uDivideBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	movss	xmm1,[STACK_PTR2]	; s
	ucomiss	xmm1,[zeroVec]

	jz	Vec2uDivBlockByFloatError

	mov	ecx, [STACK_PTR3]	; iCount
	mov	eax, ecx
	mov	DReg,[STACK_PTR1]	; *rv

	shufps	xmm1,xmm1,0

	cmp	ecx,2
	jl	Vec2uDivBlockByFloatExtra

	shr	ecx,1			; iCount /= 2

Vec2uDivBlockByFloatLoop:

	movups	xmm0,[DReg]		; v v
	divps	xmm0,xmm1		; v/s v/s
	movups	[DReg],xmm0		; r=v/s r=v/s

	add	DReg,2*Vec2Size		; *rv += iSize

	dec	ecx
	jnz	Vec2uDivBlockByFloatLoop

Vec2uDivBlockByFloatExtra:

	test	eax,1
	jz	Vec2uDivBlockByFloatError

	movhps	xmm0,[DReg]		; v
	divps	xmm0,xmm1		; v / s
	movhps	[DReg],xmm0		; r = v / s

Vec2uDivBlockByFloatError:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2DivideBlockByFloatFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2DivideBlockByFloatFPU_Asm(vec2* rv,const float s,const int32_t iCount)
;;;
	
_Vec2DivideBlockByFloatFPU_Asm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],DReg

	fld	dword [STACK_PTR2]	; s
	fldz
	fcomip	st0,st1

	jz	Vec2DivBlockFPU_DivBy0

	mov	ecx, [STACK_PTR3]	; iCount
	mov	DReg,[STACK_PTR1]	; *rv

Vec2DivBlockFloatFPULoop:

	fld	dword [DReg+4]		; v.y
	fdiv	st0,st1			; v.y * s
	fld	dword [DReg]		; v.x
	fdiv	st0,st2			; v.x * s
	fstp	dword [DReg]		; r.x = v.x * s
	fstp	dword [DReg+4]		; v.y = v.y * s

	add	DReg,Vec2Size		; *rv += offset

	dec	ecx
	jnz	Vec2DivBlockFloatFPULoop

Vec2DivBlockFPU_DivBy0:

	ffree	st0			; dump s

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2DivideBlockByFloatSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2DivideBlockByFloatSizeAsm(vec2*         rv,
;;;                                               const float   s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec2DivideBlockByFloatSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	movss	xmm1,[STACK_PTR2]	; s
	ucomiss	xmm1,[zeroVec]

	jz	Vec2DivBlockFloatSize_DivBy0

	mov	eax, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	DReg,[STACK_PTR1]	; *rv

	shufps	xmm1,xmm1,0

Vec2DivBlockFloatSizeLoop:

	movhps	xmm0,[DReg]		; v
	divps	xmm0,xmm1		; v * s
	movhps	[DReg],xmm0		; r = v * s

	add	DReg,eax		; *rv += iSize

	dec	ecx
	jnz	Vec2DivBlockFloatSizeLoop

Vec2DivBlockFloatSize_DivBy0:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufDivBlockByFloatSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] vec2*   v
;;; [1] vec2*   r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufDivBlockByFloatSizeAsm(void*         r,
;;;                                               const void*   v
;;;                                               const float   s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec2BufDivBlockByFloatSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ecx, [STACK_PTR5]	; iCount
	mov	eax, [STACK_PTR4]	; iSize
	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR3]	; s
	ucomiss	xmm1,[zeroVec]
	jz	Vec2BufDivBlockByFloatSizeDB0

	shufps	xmm1,xmm1,0

Vec2BufDivBlockByFloatSizeLoop:

	movhps	xmm0,[BReg]		; v
	divps	xmm0,xmm1		; v / s
	movhps	[DReg],xmm0		; r = v / s

	add	BReg,eax		; *v += iSize
	add	DReg,eax		; *r += iSize

	dec	ecx
	jnz	Vec2BufDivBlockByFloatSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

Vec2BufDivBlockByFloatSizeDB0:

	mov	ebx,[zeroVec]

Vec2BufDivBlockByFloatSizeDB0Loop:

	mov	[DReg],ebx
	add	DReg,eax
	loopnz	Vec2BufDivBlockByFloatSizeDB0Loop

	mov	AReg,[STACK_SAVE1]	
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2BufDivBlockByFloatBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iSrcSize
;;; [3] vec2*   v
;;; [2] int32_t iDstSize
;;; [1] vec2*   r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufDivBufByFloatAsm(void*         r,
;;;                                         const int32_t iDstSize,
;;;                                         const void*   v,
;;;                                         const int32_t iSrcSize,
;;;                                         const float   s,
;;;                                         const int32_t iCount);
;;;

_Vec2BufDivBufByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	edi, [STACK_PTR2]	; iDstSize
	mov	esi, [STACK_PTR4]	; iSrcSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	AReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	ucomiss	xmm1,[zeroVec]

	jz	Vec2BufDivBufByFloatDB0

	shufps	xmm1,xmm1,0

Vec2BufDivBufByFloatLoop:

	movhps	xmm0,[AReg]		; v
	divps	xmm0,xmm1		; v / s
	movhps	[DReg],xmm0		; r = v / s

	add	AReg,esi		; *v += iSrcSize
	add	DReg,edi		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufDivBufByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

Vec2BufDivBufByFloatDB0:

	mov	ebx,[zeroVec]

Vec2BufDivBufByFloatDB0Loop:

	mov	[DReg],ebx		;  r  = 0.0f
	add	DReg,edi		; *r += iDstSize

	loopnz	Vec2BufDivBufByFloatDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2DivideBlockByFloatSizeFPU_Asm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2DivideBlockByFloatSizeFPU_Asm(vec2*         rv,
;;;                                                   const float   s,
;;;                                                   const int32_t iSize,
;;;                                                   const int32_t iCount);
;;;

_Vec2DivideBlockByFloatSizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	fld	dword [STACK_PTR2]	; s
	fldz
	fcomip	st0,st1

	jz	Vec2DivBlockFloatSizeFPU_DivBy0

	mov	eax, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	DReg,[STACK_PTR1]	; *rv

Vec2DivBlockByFloatSzFPULoop:

	fld	dword [DReg+4]		; v.y
	fdiv	st0,st1			; v.y * s
	fld	dword [DReg]		; v.x
	fdiv	st0,st2			; v.x * s

	fstp	dword [DReg]		; r.x = v.x * s
	fstp	dword [DReg+4]		; r.y = v.y * s

	add	DReg,eax		; *rv += iSize

	dec	ecx
	jnz	Vec2DivBlockByFloatSzFPULoop

Vec2DivBlockFloatSizeFPU_DivBy0:

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufDivBlockByFloatSizeFPU_Asm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] vec2*   v
;;; [1] vec2*   r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufDivBlockByFloatSizeFPU_Asm(void*         r,
;;;                                                   const void*   v
;;;                                                   const float   s,
;;;                                                   const int32_t iSize,
;;;                                                   const int32_t iCount);
;;;

_Vec2BufDivBlockByFloatSizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ecx, [STACK_PTR5]	; iCount
	mov	eax, [STACK_PTR4]	; iSize
	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR3]	; s
	fldz
	fcomip	st0,st1

	jz	Vec2BufDivBlockByFloatSizeFPUDB0

Vec2BufDivByFloatSizeFPULoop:

	fld	dword [BReg+4]		; v.y
	fdiv	st0,st1			; v.y / s
	fld	dword [BReg]		; v.x
	fdiv	st0,st2			; v.y / s

	fstp	dword [DReg]		; v.x
	fstp	dword [DReg+4]		; v.y

	add	BReg,eax		; *v += iSize
	add	DReg,eax		; *r += iSize

	dec	ecx
	jnz	Vec2BufDivByFloatSizeFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

Vec2BufDivBlockByFloatSizeFPUDB0:

	mov	ebx,[zeroVec]

Vec2BufDivBlkByFltSizeFPULoop:

	mov	[DReg],ebx
	add	DReg,eax		; *r += iSize

	loopnz	Vec2BufDivBlkByFltSizeFPULoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2BufDivBlockByFloatBufFPU_Asm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iSrcSize
;;; [3] vec2*   v
;;; [2] int32_t iDstSize
;;; [1] vec2*   r
;;; [0] ret
;;;
;;; extern "C" void Vec2BufDivBufByFloatFPU_Asm(void*         r,
;;;                                             const int32_t iDstSize,
;;;                                             const void*   v,
;;;                                             const int32_t iSrcSize,
;;;                                             const float   s,
;;;                                             const int32_t iCount);
;;;

_Vec2BufDivBufByFloatFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	edi, [STACK_PTR2]	; iDstSize
	mov	esi, [STACK_PTR4]	; iSrcSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	AReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR5]	; s
	fldz
	fcomip	st0,st1

	jz	Vec2BufDivBufByFloatDB0FPU

Vec2BufDivBufByFloatFPULoop:

	fld	dword [AReg+4]		; v.y
	fdiv	st0,st1			; v.y * s
	fld	dword [AReg]		; v.x
	fdiv	st0,st2			; v.x * s

	fstp	dword [DReg]		; r.x = v.x * s
	fstp	dword [DReg+4]		; r.y = v.y * s

	add	AReg,esi		; *v += iSrcSize
	add	DReg,edi		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufDivBufByFloatFPULoop

	ffree	st0			; dump s

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

Vec2BufDivBufByFloatDB0FPU:

	ffree	st0			; dump s
	mov	ebx,[zeroVec]

Vec2BufDivBufByFloatDB0FPULoop:

	mov	[DReg],ebx		;  r  = 0.0f
	add	DReg,edi		; *r += iDstSize

	loopnz	Vec2BufDivBufByFloatDB0FPULoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

;;;
;;; Vec2NegateAsm
;;;
;;; Call Stack
;;; [2] vec2* value
;;; [1] vec2* return
;;; [0] ret
;;;
;;;  -vec2
;;;  vec2 = -vec2
;;;
;;;  extern "C" void Vec2NegateAsm(vec2& r,const vec2& u)
;;; 

_Vec2NegateAsm:
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; u
	mulps	xmm0,[negVec]		; u * -1
	movhps	[DReg],xmm0		; r = -u

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2AddAsm
;;; 
;;; Call Stack
;;;
;;; [3] vec2 *v (through reference)
;;; [2] vec2 *u (through reference)
;;; [1] vec2 *r (through reference)
;;; [0] ret
;;;
;;;  vec2 += vec2
;;;  vec2 = vec2 + vec2
;;;
;;;  extern "C" void Vec2AddAsm(vec2& r,const vec2& u,const vec2& v)
;;; 

_Vec2AddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u - v
	movhps	[DReg],xmm0		; r = u - v

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2SubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2* v 
;;; [2] vec2* u 
;;; [1] vec2* r 
;;; [0] ret
;;;
;;; vec2 -= vec2
;;; vec2 = vec2 - vec2
;;;
;;; extern "C" void Vec2SubtractAsm(vec2& r,const vec2& u,const vec2& v)
;;; 

_Vec2SubtractAsm:
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u - v
	movhps	[DReg],xmm0		; r = u - v

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2MultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2* v
;;; [2] vec2* u
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 *= vec2
;;; vec2 = vec2 * vec2
;;;
;;; extern "C" void Vec2MultiplyAsm(vec2& r,const vec2& u,const vec2& v)
;;; 

_Vec2MultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u * v
	movhps	[DReg],xmm0		; r = u * v

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2DivideAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2* v
;;; [2] vec2* u
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 /=
;;; vec2 = vec2 / vec2
;;;
;;; extern "C" void Vec2DivideAsm(vec2& r,const vec2& u,const vec2& v)
;;; 

_Vec2DivideAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v

	mov	ecx,0
	movlps	xmm0,[zeroVec]
	movlps	xmm1,[oneVec]

	ucomiss	xmm0,[BReg]
	jne	Vec2DivideAdjArg1

	or	ecx,1
	movss	[BReg],xmm1

Vec2DivideAdjArg1:

	ucomiss	xmm0,[BReg+4]
	jne	Vec2DivideArgs

	or	ecx,2
	movss	[BReg+4],xmm1

Vec2DivideArgs:

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v

	divps	xmm0,xmm1

	movhps	[DReg],xmm0

	cmp 	ecx,0
	je 	Vec2DivideEnd

	test	ecx,1
	jz	Vec2DivideChkArg2

	movss	[BReg],xmm0
	movss	[DReg],xmm0

Vec2DivideChkArg2:

	test	ecx,2
	jz 	Vec2DivideEnd

	movss	[BReg+4],xmm0
	movss	[DReg+4],xmm0

Vec2DivideEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2AngleAsm
;;;
;;; CallStack
;;;
;;; [2] vec2*  u
;;; [1] float* r
;;;
;;; extern "C" void Vec2AngleAsm(float* r,const vec2* u)
;;; XXX:
%if 0
_Vec2AngleAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u

	fld	dword [DReg]		; [0] u.x
	fld	st0			; [0] u.x [1] u.x
	fmul	st0,st0			; [0] sqr(u.x) [1] u.x
	fld	dword [DReg+4]		; [0] u.y [1] sqr(u.x) [2] u.x
	fmul	st0,st0			; [0] sqr(u.y) [1] sqr(u.x) [2] u.x
	faddp	st1,st0			; [0] sum(sqr(u)) [1] u.x
	fsqrt	st0			; [0] length(u) [1] u.x
	fdivp	st1,st0			; [0] u.x / length(u)
	facos	st0			; [0] angle
	fstp	dword [DReg]

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2EqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2*    v
;;; [2] vec2*    u
;;; [1] int32_t* flag
;;;
;;; extern "C" void Vec2EqualsAsm(int32_t* iFlag,const vec2* u,const vec2* v);
;;;

_Vec2EqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFlag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movhps	xmm0,[BReg]		; u
	movhps	xmm1,[DReg]		; v

	subps	xmm0,xmm1		; u-v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,3,3,3)
	ucomiss	xmm0,[zeroVec]
	jnz	Vec2EqualsFalse

	shufps	xmm1,xmm2,SHUFFLE(2,2,2,2)
	ucomiss	xmm0,[zeroVec]
	jnz	Vec2EqualsFalse

	mov	ebx,1
	mov	[AReg],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec2EqualsFalse:

	mov	ebx,0
	mov	[AReg],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2NotEqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*    v
;;; [2] vec3*    u
;;; [1] int32_t* flag
;;;
;;; extern "C" void Vec2NotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);
;;;

_Vec2NotEqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFlag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movhps	xmm0,[BReg]		; u
	movhps	xmm1,[DReg]		; v
	subps	xmm0,xmm1		; u-v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,3,3,3)
	ucomiss	xmm0,[zeroVec]
	jnz	Vec2NotEqualsTrue

	shufps	xmm1,xmm1,SHUFFLE(2,2,2,2)
	ucomiss	xmm1,[zeroVec]
	jnz	Vec2NotEqualsTrue

	mov	ebx,0
	mov	[AReg],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec2NotEqualsTrue:

	mov	ebx,1
	mov	[AReg],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uEqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2*    v
;;; [2] vec2*    u
;;; [1] int32_t* flag
;;;
;;; extern "C" void Vec2uEqualsAsm(int32_t* iFlag,const vec2* u,const vec2* v);
;;;

_Vec2uEqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFlag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movhps	xmm0,[BReg]		; u
	movhps	xmm1,[DReg]		; v

	subps	xmm0,xmm1		; u-v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,3,3,3)
	ucomiss	xmm0,[zeroVec]
	jnz	Vec2uEqualsFalse

	shufps	xmm1,xmm1,SHUFFLE(2,2,2,2)
	ucomiss	xmm1,[zeroVec]
	jnz	Vec2uEqualsFalse

	mov	ebx,1
	mov	[AReg],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec2uEqualsFalse:

	mov	ebx,0
	mov	[AReg],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2uNotEqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*    v
;;; [2] vec3*    u
;;; [1] int32_t* flag
;;;
;;; extern "C" void Vec2uNotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);
;;;

_Vec2uNotEqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFlag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movhps	xmm0,[BReg]		; u
	movhps	xmm1,[DReg]		; v
	subps	xmm0,xmm1		; u-v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,3,3,3)
	ucomiss	xmm0,[zeroVec]
	jnz	Vec2uNotEqualsTrue

	shufps	xmm1,xmm1,SHUFFLE(2,2,2,2)
	ucomiss	xmm1,[zeroVec]
	jnz	Vec2uNotEqualsTrue

	mov	ebx,0
	mov	[AReg],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec2uNotEqualsTrue:

	mov	ebx,1
	mov	[AReg],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	
;;;
;;; Vec2NegateBlock
;;;
;;; Call Stack
;;;
;;; [2] int32_t nCount
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2NegateBlockAsm(vec2* pSource_Dest,int32_t nCount)
;;;

_Vec2NegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]
	mov	ecx, [STACK_PTR2]
	mov	edx, ecx

	movaps	xmm1,[negVec]		; Load -1

	cmp	ecx,2
	jl	Vec2NegateBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2NegateBlockLoop:

	movaps	xmm0,[AReg]		; v v
	mulps	xmm0,xmm1		; -v -v
	movaps	[AReg],xmm0		; r=-v r=-v

	add	AReg,2*Vec2Size		; *rv += iSize

	dec	ecx
	jnz	Vec2NegateBlockLoop

Vec2NegateBlockExtra:

	test	edx,1
	jz	Vec2NegateBlockEnd

	movhps	xmm0,[AReg]
	mulps	xmm0,xmm1
	movhps	[AReg],xmm0

Vec2NegateBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uNegateBlock
;;;
;;; Call Stack
;;;
;;; [2] int32_t nCount
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2uNegateBlockAsm(vec2* pSource_Dest,int32_t nCount)
;;;

_Vec2uNegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]
	mov	ecx, [STACK_PTR2]
	mov	edx, ecx

	movaps	xmm1,[negVec]		; Load -1

	cmp	ecx,2
	jl	Vec2uNegateBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2uNegateBlockLoop:

	movups	xmm0,[AReg]		; v v
	mulps	xmm0,xmm1		; -v -v
	movups	[AReg],xmm0		; r=-v r=-v

	add	AReg,2*Vec2Size		; *rv += iSize

	dec	ecx
	jnz	Vec2uNegateBlockLoop

Vec2uNegateBlockExtra:

	test	edx,1
	jz	Vec2uNegateBlockEnd

	movhps	xmm0,[AReg]
	mulps	xmm0,xmm1
	movhps	[AReg],xmm0

Vec2uNegateBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

;;;
;;; Vec2NegateBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec2*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec2NegateBlockBySize(vec2*         rv,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;; 

_Vec2NegateBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[negVec]

Vec2NegateBlockSizeLoop:

	movhps	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v = -1 * v
	movhps	[AReg],xmm0		; r = -v

	add	AReg,ebx		; *rv += iSize

	loopnz	Vec2NegateBlockSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufNegateBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] vec2*   v
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufNegateBlockBySizeAsm(vec2*         r,
;;;                                             const vec2*   v,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec2BufNegateBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm1,[negVec]		; -1

Vec2BufNegBlockSizeLoop:

	movhps	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; v * -1
	movhps	[DReg],xmm0		; r = -v

	add	AReg,ebx		; *v += iSize
	add	DReg,ebx		; *r += iSize

	loopnz	Vec2BufNegBlockSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2BufNegateBufBySizeAsm:
;;;
;;; Call Stack
;;;
;;; [5] int32_t nCount
;;; [4] int32_t iSrcSize
;;; [3] vec2*   v
;;; [2] int32_t iDstSize
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufNegateBufBySizeAsm(vec2*         r,
;;;                                           const int32_t iDstSize,
;;;                                           const vec2*   v,
;;;                                           const int32_t iSrcSize,
;;;                                           const int32_t iCount);
;;;

_Vec2BufNegateBufBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp
	
	mov	AReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR5]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iSrcSize
	mov	edi, [STACK_PTR2]	; iDstSize

	movaps	xmm1,[negVec]

Vec2BufNegBufSizeLoop:

	movhps	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; v * -1
	movhps	[DReg],xmm0		; r = -v

	add	AReg,esi		; *v += iSrcSize
	add	DReg,edi		; *v += iDstSize

	loopnz	Vec2BufNegBufSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2AddVec2ToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec2*   pSource (constant vector)
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2AddVec2ToBlock(vec2* ru,const vec2* v,const int32_t iCount)
;;;

_Vec2AddVec2ToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movhps	xmm1,[AReg]		; v

	cmp	ecx,2			; < 2 entries
	jl	Vec2AddVec2ToBlkExtra

	shr	ecx,1			; iCount /= 2

	movlps	xmm1,[AReg]		; v

Vec2AddVec2ToBlockLoop:

	movaps	xmm0,[DReg]		; u u
	addps	xmm0,xmm1		; u+v u+v
	movaps	[DReg],xmm0		; r=u+v r=u+v

	add	DReg,2*Vec2Size		; *ru += 2*iSize

	dec	ecx
	jnz	Vec2AddVec2ToBlockLoop

Vec2AddVec2ToBlkExtra:

	test	ebx,1
	jz	Vec2AddVec2ToBlockEnd

	movhps	xmm0,[DReg]		; u
	addps	xmm0,xmm1		; u + v
	movhps	[DReg],xmm0		; r = u + v

Vec2AddVec2ToBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2AddBlockToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pDest += AlignedBuffer<vec2> pSource
;;;
;;; extern "C" void Vec2AddBlockToBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount)
;;;

_Vec2AddBlockToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	cmp	ecx,2			; < 2
	jl	Vec2AddBlockToBlockExtra

	shr	ecx,1			; divide by 2

Vec2AddBlockToBlockLoop:

	movaps	xmm0,[DReg]		; u
	addps   xmm0,[AReg]		; u + v
	movaps	[DReg],xmm0		; r = u + v

	add	AReg,2*Vec2Size		; *v  += iSize
	add	DReg,2*Vec2Size		; *ru += iSize

	loopnz	Vec2AddBlockToBlockLoop

Vec2AddBlockToBlockExtra:

	test	ebx,1
	jz	Vec2AddBlockToBlockEnd

	movhps	xmm0,[DReg]		; u
	movhps	xmm1,[AReg]		; v
	addps	xmm0,xmm1		; u + v
	movhps	[DReg],xmm0		; r = u + v

Vec2AddBlockToBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uAddVec2ToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec2*   pSource (constant vector)
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2uAddVec2ToBlock(vec2* ru,const vec2* v,const int32_t iCount)
;;;

_Vec2uAddVec2ToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movhps	xmm1,[AReg]		; v

	cmp	ecx,2			; < 2 entries
	jl	Vec2uAddVec2ToBlkExtra

	shr	ecx,1			; iCount /= 2

	movlps	xmm1,[AReg]		; v

Vec2uAddVec2ToBlockLoop:

	movups	xmm0,[DReg]		; u u
	addps	xmm0,xmm1		; u+v u+v
	movups	[DReg],xmm0		; r=u+v r=u+v

	add	DReg,2*Vec2Size		; *ru += 2*iSize

	dec	ecx
	jnz	Vec2uAddVec2ToBlockLoop

Vec2uAddVec2ToBlkExtra:

	test	ebx,1
	jz	Vec2uAddVec2ToBlockEnd

	movhps	xmm0,[DReg]		; u
	addps	xmm0,xmm1		; u + v
	movhps	[DReg],xmm0		; r = u + v

Vec2uAddVec2ToBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2uAddBlockToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pDest += AlignedBuffer<vec2> pSource
;;;
;;; extern "C" void Vec2uAddBlockToBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount)
;;;

_Vec2uAddBlockToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	cmp	ecx,2			; < 2
	jl	Vec2uAddBlockToBlockExtra

	shr	ecx,1			; divide by 2

Vec2uAddBlockToBlockLoop:

	movups	xmm0,[DReg]		; u
	movups	xmm1,[AReg]		; v
	addps   xmm0,xmm1		; u + v
	movups	[DReg],xmm0		; r = u + v

	add	AReg,2*Vec2Size		; *v  += iSize
	add	DReg,2*Vec2Size		; *ru += iSize

	loopnz	Vec2uAddBlockToBlockLoop

Vec2uAddBlockToBlockExtra:

	test	ebx,1
	jz	Vec2uAddBlockToBlockEnd

	movhps	xmm0,[DReg]		; u
	movhps	xmm1,[AReg]		; v
	addps	xmm0,xmm1		; u + v
	movhps	[DReg],xmm0		; r = u + v

Vec2uAddBlockToBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

;;;
;;; Vec2BufAddVec2ToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufAddVec2ToBlockBySizeAsm(vec2*         r,
;;;                                                const vec2*   u,
;;;                                                const vec2*   v,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec2BufAddVec2ToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm1,[BReg]		; v

Vec2BufAddVec2ToBlkSzLoop:

	movhps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movhps	[DReg],xmm0		; r = u + v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec2BufAddVec2ToBlkSzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2BufAddBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufAddBlockBySizeAsm(vec2*         r,
;;;                                          const vec2*   u,
;;;                                          const vec2*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec2BufAddBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

Vec2BufAddBlockBySizeLoop:

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u + v
	movhps	[DReg],xmm0		; r = u + v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec2BufAddBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2BufAddBufBySizeAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iSrc1Size
;;; [5] vec2*   v
;;; [4] int32_t iSrc0Size
;;; [3] vec2*   u
;;; [2] int32_t iDstSize
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufAddBufBySize(vec2*         r,
;;;                                     const int32_t iSaveSize,
;;;                                     const vec2*   u,
;;;                                     const int32_t iSrcSize0,
;;;                                     const vec2*   v,
;;;                                     const int32_t iSrcSize1
;;;                                     const int32_t iCount);
;;;

_Vec2BufAddBufBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR6]	; iSrcSize0
	mov	edi, [STACK_PTR4]	; iSrcSize1
	mov	ebp, [STACK_PTR2]	; iDstSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r

Vec2BufAddBufBySizeLoop:

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u + v
	movhps	[DReg],xmm0		; r = u + v

	add	AReg,esi		; *u += iSrcSize0
	add	BReg,edi		; *v += iSrcSize1
	add	DReg,ebp		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufAddBufBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2SubtractVec2FromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource (constant vector)
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2SubtractVec2FromBlockAsm(vec2* pDest,vec2* pVector,int32_t nCount)
 ;;;

_Vec2SubtractVec2FromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movhps	xmm1,[AReg]		; v

	cmp	ecx,2			; < 2 entries
	jl	Vec2SubVec2FromBlockExtra

	shr	ecx,1			; iCount /= 2

	movlps	xmm1,[AReg]		; v

Vec2SubtractVec2FromBlockLoop:

	movaps	xmm0,[DReg]		; u u
	subps	xmm0,xmm1		; u-v u-v
	movaps	[DReg],xmm0		; r=u-v r=u-v

	add	DReg,2*Vec2Size		; *rc += 2*iSize

	loopnz	Vec2SubtractVec2FromBlockLoop

Vec2SubVec2FromBlockExtra:

	test	ebx,1
	jz	Vec2SubVec2FromBlkEnd

	movhps	xmm0,[DReg]		; u
	subps	xmm0,xmm1		; u-v
	movhps	[DReg],xmm0		; r = u-v

Vec2SubVec2FromBlkEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2SubtractBlockFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pDest += AlignedBuffer<vec2> pSource
;;;
;;; extern "C" void Vec2SubtractBlockFromBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount)
;;;

_Vec2SubtractBlockFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	cmp	ecx,2			; < 2 entries
	jl	Vec2SubBlkFromBlkExtra

	shr	ecx,1			; iCount /= 2

Vec2SubBlockFromBlockLoop:

	movaps	xmm0,[DReg]		; u u
	subps   xmm0,[AReg]		; u-v u-v
	movaps	[DReg],xmm0		; r=u-v r=u-v

	add	AReg,2*Vec2Size		; *v  += 2*iSize
	add	DReg,2*Vec2Size		; *ru += 2*iSize

	loopnz	Vec2SubBlockFromBlockLoop

Vec2SubBlkFromBlkExtra:

	test	ebx,1
	jz	Vec2SubBlockFromBlockEnd

	movhps	xmm0,[DReg]		; u
	movhps	xmm1,[AReg]		; v
	subps	xmm0,xmm1		; u-v
	movhps	[DReg],xmm0		; r = u-v

Vec2SubBlockFromBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uSubtractVec2FromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource (constant vector)
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2uSubtractVec2FromBlockAsm(vec2* pDest,vec2* pVector,int32_t nCount)
;;;

_Vec2uSubtractVec2FromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movhps	xmm1,[AReg]		; v

	cmp	ecx,2			; < 2 entries
	jl	Vec2uSubVec2FromBlockExtra

	shr	ecx,1			; iCount /= 2

	movlps	xmm1,[AReg]		; v

Vec2uSubtractVec2FromBlockLoop:

	movups	xmm0,[DReg]		; u u
	subps	xmm0,xmm1		; u-v u-v
	movups	[DReg],xmm0		; r=u-v r=u-v

	add	DReg,2*Vec2Size		; *rc += 2*iSize

	loopnz	Vec2uSubtractVec2FromBlockLoop

Vec2uSubVec2FromBlockExtra:

	test	ebx,1
	jz	Vec2uSubVec2FromBlkEnd

	movhps	xmm0,[DReg]		; u
	subps	xmm0,xmm1		; u-v
	movhps	[DReg],xmm0		; r = u-v

Vec2uSubVec2FromBlkEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2uSubtractBlockFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pDest += AlignedBuffer<vec2> pSource
;;;
;;; extern "C" void Vec2uSubtractBlockFromBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount)
;;;

_Vec2uSubtractBlockFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	cmp	ecx,2			; < 2 entries
	jl	Vec2uSubBlkFromBlkExtra

	shr	ecx,1			; iCount /= 2

Vec2uSubBlockFromBlockLoop:

	movups	xmm0,[DReg]		; u u
	movups	xmm1,[AReg]		; v v
	subps	xmm0,xmm1		; u-v u-v
	movups	[DReg],xmm0		; r=u-v r=u-v

	add	AReg,2*Vec2Size		; *v  += 2*iSize
	add	DReg,2*Vec2Size		; *ru += 2*iSize

	loopnz	Vec2uSubBlockFromBlockLoop

Vec2uSubBlkFromBlkExtra:

	test	ebx,1
	jz	Vec2uSubBlockFromBlockEnd

	movhps	xmm0,[DReg]		; u
	movhps	xmm1,[AReg]		; v
	subps	xmm0,xmm1		; u-v
	movhps	[DReg],xmm0		; r = u-v

Vec2uSubBlockFromBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

%endif

;;;
;;; Vec2BufSubVec2FromBlkBySizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufSubVec2FromBlkBySizeAsm(vec2*         r,
;;;                                                const vec2*   u,
;;;                                                const vec2*   v,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec2BufSubVec2FromBlkBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm1,[BReg]		; v

Vec2BufSubV2FromBlkSzLoop:

	movhps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movhps	[DReg],xmm0		; r = u - v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec2BufSubV2FromBlkSzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2BufSubBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufSubBlockBySizeAsm(vec2* r,
;;;                                          const vec2* u,
;;;                                          const vec2* v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec2BufSubBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

Vec2BufSubBlkBySizeLoop:

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u - v
	movhps	[DReg],xmm0		; r = u - v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec2BufSubBlkBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2BufSubBufBySizeAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iSrcSize1
;;; [5] vec2*   v
;;; [4] int32_t iSrcSize0
;;; [3] vec2*   u
;;; [2] int32_t iDstSize
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufSubBufBySizeAsm(vec2*         r,
;;;                                        const int32_t iSaveSize,
;;;                                        const vec2* u,
;;;                                        const int32_t iSrcSize0,
;;;                                        const vec2* v,
;;;                                        const int32_t iSrcSize1,
;;;                                        const int32_t iCount);
;;; 

_Vec2BufSubBufBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR6]	; iSrcSize0
	mov	edi, [STACK_PTR4]	; iSrcSize1
	mov	ebp, [STACK_PTR2]	; iDstSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r

Vec2BufSubBufBySizeLoop:

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u - v
	movhps	[DReg],xmm0		; r = u - v

	add	AReg,esi		; *u += iSrcSize0
	add	BReg,edi		; *v += iSrcSize1
	add	DReg,ebp		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufSubBufBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2MultiplyBlockByVec2Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource (constant vector)
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2MultiplyBlockByVec2Asm(vec2* pDest,vec2* pVector,int32_t nCount)
;;;

_Vec2MultiplyBlockByVec2Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movhps	xmm1,[AReg]		; v

	cmp	ecx,2
	jl	Vec2MulBlockByVec2Extra

	shr	ecx,1			; iCount /= 2

	movlps	xmm1,[AReg]		; v

Vec2MultiplyBlockByVec2Loop:

	movaps	xmm0,[DReg]		; u u
	mulps	xmm0,xmm1		; u*v u*v
	movaps	[DReg],xmm0		; r=u*v r=u*v

	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2MultiplyBlockByVec2Loop

Vec2MulBlockByVec2Extra:

	test	ebx,1
	jz	Vec2MulBlockByVec2End

	movhps	xmm0,[DReg]		; u
	mulps	xmm0,xmm1		; u*v
	movhps	[DReg],xmm0		; r = u*v

Vec2MulBlockByVec2End:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2MultiplyBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pDest += AlignedBuffer<vec2> pSource
;;;
;;; extern "C" void Vec2MultiplyBlockByBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount)
;;;

_Vec2MultiplyBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	cmp	ecx,2
	jl	Vec2MulBlockByBlockStraggler

	shr	ecx,1			; iCount /= 2

Vec2MulBlockByBlockLoop:

	movaps	xmm0,[DReg]		; u
	mulps   xmm0,[AReg]		; u * v
	movaps	[DReg],xmm0		; r = u * v

	add	AReg,2*Vec2Size		; *v  += iSize
	add	DReg,2*Vec2Size		; *ru += iSize

	dec	ecx
	jnz	Vec2MulBlockByBlockLoop

Vec2MulBlockByBlockStraggler:

	test	ebx,1
	jz	Vec2MulBlockByBlockEnd

	movhps	xmm0,[DReg]		; u
	movhps	xmm1,[AReg]		; v
	mulps	xmm0,xmm1		; u*v
	movhps	[DReg],xmm0		; r = u*v

Vec2MulBlockByBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uMultiplyBlockByVec2Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource (constant vector)
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2uMultiplyBlockByVec2Asm(vec2* pDest,vec2* pVector,int32_t nCount)
;;;

_Vec2uMultiplyBlockByVec2Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movhps	xmm1,[AReg]		; v

	cmp	ecx,2
	jl	Vec2uMulBlockByVec2Extra

	shr	ecx,1			; iCount /= 2

	movlps	xmm1,[AReg]		; v

Vec2uMultiplyBlockByVec2Loop:

	movups	xmm0,[DReg]		; u u
	mulps	xmm0,xmm1		; u*v u*v
	movups	[DReg],xmm0		; r=u*v r=u*v

	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2uMultiplyBlockByVec2Loop

Vec2uMulBlockByVec2Extra:

	test	ebx,1
	jz	Vec2uMulBlockByVec2End

	movhps	xmm0,[DReg]		; u
	mulps	xmm0,xmm1		; u*v
	movhps	[DReg],xmm0		; r = u*v

Vec2uMulBlockByVec2End:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret
	
;;;
;;; Vec2uMultiplyBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pDest += AlignedBuffer<vec2> pSource
;;;
;;; extern "C" void Vec2uMultiplyBlockByBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount)
;;;

_Vec2uMultiplyBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	cmp	ecx,2
	jl	Vec2uMulBlockByBlockStraggler

	shr	ecx,1			; iCount /= 2

Vec2uMulBlockByBlockLoop:

	movups	xmm0,[DReg]		; u
	movups	xmm1,[AReg]		; v
	mulps	xmm0,xmm1		; u * v
	movups	[DReg],xmm0		; r = u * v

	add	AReg,2*Vec2Size		; *v  += iSize
	add	DReg,2*Vec2Size		; *ru += iSize

	dec	ecx
	jnz	Vec2uMulBlockByBlockLoop

Vec2uMulBlockByBlockStraggler:

	test	ebx,1
	jz	Vec2uMulBlockByBlockEnd

	movhps	xmm0,[DReg]		; u
	movhps	xmm1,[AReg]		; v
	mulps	xmm0,xmm1		; u*v
	movhps	[DReg],xmm0		; r = u*v

Vec2uMulBlockByBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

%endif

;;;
;;; Vec2BufMulVec2ByBlockSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufMulVec2ByBlockSizeAsm(vec2*         r,
;;;                                              const vec2*   u,
;;;                                              const vec2*   v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec2BufMulVec2ByBlockSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm1,[BReg]		; v

Vec2BufMulBlkByVec2SzLoop:

	movhps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u * v
	movhps	[DReg],xmm0		; r = u * v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec2BufMulBlkByVec2SzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2BufMulBlockBySizeAsm
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufMulBlockBySizeAsm(vec2*         r,
;;;                                          const vec2*   u,
;;;                                          const vec2*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec2BufMulBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

Vec2BufMulBlockBySizeLoop:

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u * v
	movhps	[DReg],xmm0		; r = u * v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec2BufMulBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2BufMulBufBySizeAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iSrcSize1
;;; [5] vec2*   v
;;; [4] int32_t iSrcSize0
;;; [3] vec2*   u
;;; [2] int32_t iDstSize
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufMulBufBySizeAsm(vec2*         r,
;;;                                        const int32_t iDstSize,
;;;                                        const vec2*   u,
;;;                                        const int32_t iSrcSize0,
;;;                                        const vec2*   v,
;;;                                        const int32_t iSrcSize1,
;;;                                        const int32_t iCount);
;;; 

_Vec2BufMulBufBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR6]	; iSrcSize1
	mov	edi, [STACK_PTR4]	; iSrcSize0
	mov	ebp, [STACK_PTR2]	; iDstSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r

Vec2BufMulBufBySizeLoop:

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u * v
	movhps	[DReg],xmm0		; r = u * v

	add	AReg,esi		; *u += iSrcSize0
	add	BReg,edi		; *v += iSrcSize1
	add	DReg,ebp		; *r += iDstSize

	dec	ecx
	jnz	Vec2BufMulBufBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2DivideBlockByVec2Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource (constant vector)
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2DivideBlockByVec2Asm(vec2* pDest,vec2* pVector,int32_t nCount)
;;;

_Vec2DivideBlockByVec2Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	esi, 0			; iFlags

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movss	xmm2,[zeroVec]		; Compare/substitute value
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[AReg]		; v.x == 0.0f
	jne	Vec2DivBlockByVec2Not0_1

	or	esi,1			; First entry = 0
	movss	[AReg],xmm3

Vec2DivBlockByVec2Not0_1:

	ucomiss	xmm2,[AReg+4]
	jne	Vec2DivBlockByVec2Not0_2

	or	esi,2
	movss	[AReg+4],xmm3

Vec2DivBlockByVec2Not0_2:

	movhps	xmm1,[AReg]		; v

	cmp	ecx,2			; single entry?
	jl	Vec2DivBlockByVec2Extra

	shr	ecx,1			; iCount /= 2

	movlps	xmm1,[AReg]		; v

Vec2DivBlockByVec2Loop:

	movaps	xmm0,[DReg]		; u u
	divps	xmm0,xmm1		; u/v u/v
	movaps	[DReg],xmm0		; r=u/v r=u/v

	cmp	esi,0
	je	Vec2DivBlkByVec2AdjPtrs

	test	esi,1			; fp[0] = 0.0f
	jz	Vec2DivBlkByVec2Test2

	movss	[DReg],xmm2
	movss	[DReg+8],xmm2

Vec2DivBlkByVec2Test2:

	test	esi,2			; fp[1] = 0.0f
	jz	Vec2DivBlkByVec2AdjPtrs

	movss	[DReg+4],xmm2
	movss	[DReg+12],xmm2

Vec2DivBlkByVec2AdjPtrs:

	add	DReg,2*Vec2Size		; *r += iSize

	dec	ecx
	jnz	Vec2DivBlockByVec2Loop

Vec2DivBlockByVec2Extra:

	test	ebx,1
	jz	Vec2DivBlkByVec2End

	movhps	xmm0,[DReg]
	divps	xmm0,xmm1
	movhps	[DReg],xmm0

	cmp	esi,0
	je	Vec2DivBlkByVec2End

	test	esi,1
	jz	Vec2DivBlkByVec2Test3

	movss	[DReg],xmm2

Vec2DivBlkByVec2Test3:

	test	esi,2
	jz	Vec2DivBlkByVec2End

	movss	[DReg+4],xmm2

Vec2DivBlkByVec2End:

	cmp	esi,0
	je	Vec2DivBlkByVec2Done

	test	esi,1
	jz	Vec2DivBlkByVec2Fix2

	movss	[AReg],xmm2

Vec2DivBlkByVec2Fix2:

	test	esi,2
	jz	Vec2DivBlkByVec2Done

	movss	[AReg+4],xmm2

Vec2DivBlkByVec2Done:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2DivideBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pDest += AlignedBuffer<vec2> pSource
;;;
;;; extern "C" void Vec2DivideBlockByBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount)
;;;

_Vec2DivideBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movss	xmm2,[zeroVec]		; Compare/substitute value
	movss	xmm3,[oneVec]

	cmp	ecx,2
	jge	Vec2DivBlkByBlkPreLoop
	jmp	Vec2DivBlkByBlkDivExtra

Vec2DivBlkByBlkPreLoop:

	shr	ecx,1			; iCount /= 2

Vec2DivBlkByBlkLoop:

	mov	esi,0			; Clear iFlags

	ucomiss	xmm2,[AReg]		; v0.x == 0.0f
	jne	Vec2DivBlkByBlkChkArg1

	or	esi,1
	movss	[AReg],xmm3

Vec2DivBlkByBlkChkArg1:

	ucomiss	xmm2,[AReg+4]		; v0.y == 0.0
	jne	Vec2DivBlkByBlkChkArg2

	or	esi,2
	movss	[AReg+4],xmm3

Vec2DivBlkByBlkChkArg2:

	ucomiss	xmm2,[AReg+8]		; v1.x == 0.0f
	jne	Vec2DivBlkByBlkChkArg3

	or	esi,4
	movss	[AReg+8],xmm3

Vec2DivBlkByBlkChkArg3:

	ucomiss	xmm2,[AReg+12]		; v1.y == 0.0f
	jne	Vec2DivBlkByBlkDivArgs

	or	esi,8
	movss	[AReg+12],xmm3

Vec2DivBlkByBlkDivArgs:

	movaps	xmm0,[DReg]		; u u
	divps	xmm0,[AReg]		; u/v u/v
	movaps	[DReg],xmm0		; r = u/v r = u/v

	cmp	esi,0
	jz	Vec2DivBlkByBlkAdjPtrs

	test	esi,1			; Check arg0
	jz	Vec2DivBlkByBlkAdjArg1

	movss	[AReg],xmm2
	movss	[DReg],xmm2

Vec2DivBlkByBlkAdjArg1:

	test	esi,2
	jz	Vec2DivBlkByBlkAdjArg2

	movss	[AReg+4],xmm2
	movss	[DReg+4],xmm2

Vec2DivBlkByBlkAdjArg2:

	test	esi,4
	jz	Vec2DivBlkByBlkAdjArg3

	movss	[AReg+8],xmm2
	movss	[DReg+8],xmm2

Vec2DivBlkByBlkAdjArg3:

	test	esi,8
	jz	Vec2DivBlkByBlkAdjPtrs

	movss	[AReg+12],xmm2
	movss	[DReg+12],xmm2

Vec2DivBlkByBlkAdjPtrs:

	add	AReg,2*Vec2Size
	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2DivBlkByBlkLoop

Vec2DivBlkByBlkDivExtra:

	test	ebx,1
	jz	Vec2DivBlkByBlkDivEnd

	mov	esi,0

	ucomiss	xmm2,[AReg]		; v.x == 0.0f
	jne	Vec2DivBlkByBlkDivEx1

	or	esi,1
	movss	[AReg],xmm3

Vec2DivBlkByBlkDivEx1:

	ucomiss	xmm2,[AReg+4]		; v.y == 0.0f
	jne	Vec2DivBlkByBlkDivLast

	or	esi,2
	movss	[AReg+4],xmm3

Vec2DivBlkByBlkDivLast:

	movhps	xmm0,[DReg]
	movhps	xmm1,[AReg]
	divps	xmm0,xmm1
	movhps	[DReg],xmm0

	cmp	esi,0
	jz	Vec2DivBlkByBlkDivEnd

	test	esi,1
	jz	Vec2DivBlkByBlkEndAdj1

	movss	[AReg],xmm2
	movss	[DReg],xmm2

Vec2DivBlkByBlkEndAdj1:

	test	esi,2
	jz	Vec2DivBlkByBlkDivEnd

	movss	[AReg+4],xmm2
	movss	[DReg+4],xmm2

Vec2DivBlkByBlkDivEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uDivideBlockByVec2Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource (constant vector)
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pSource_Dest += pSource
;;;
;;; extern "C" void Vec2uDivideBlockByVec2Asm(vec2* pDest,vec2* pVector,int32_t nCount)
;;;

_Vec2uDivideBlockByVec2Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx
	mov	esi, 0			; iFlags

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movss	xmm2,[zeroVec]		; Compare/substitute value
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[AReg]		; v.x == 0.0f
	jne	Vec2uDivBlockByVec2Not0_1

	or	esi,1			; First entry = 0
	movss	[AReg],xmm3

Vec2uDivBlockByVec2Not0_1:

	ucomiss	xmm2,[AReg+4]
	jne	Vec2uDivBlockByVec2Not0_2

	or	esi,2
	movss	[AReg+4],xmm3

Vec2uDivBlockByVec2Not0_2:

	movhps	xmm1,[AReg]		; v

	cmp	ecx,2			; single entry?
	jl	Vec2uDivBlockByVec2Extra

	shr	ecx,1			; iCount /= 2

	movlps	xmm1,[AReg]		; v

Vec2uDivBlockByVec2Loop:

	movups	xmm0,[DReg]		; u u
	divps	xmm0,xmm1		; u/v u/v
	movups	[DReg],xmm0		; r=u/v r=u/v

	cmp	esi,0
	je	Vec2uDivBlkByVec2AdjPtrs

	test	esi,1			; fp[0] = 0.0f
	jz	Vec2uDivBlkByVec2Test2

	movss	[DReg],xmm2
	movss	[DReg+8],xmm2

Vec2uDivBlkByVec2Test2:

	test	esi,2			; fp[1] = 0.0f
	jz	Vec2uDivBlkByVec2AdjPtrs

	movss	[DReg+4],xmm2
	movss	[DReg+12],xmm2

Vec2uDivBlkByVec2AdjPtrs:

	add	DReg,2*Vec2Size		; *r += iSize

	dec	ecx
	jnz	Vec2uDivBlockByVec2Loop

Vec2uDivBlockByVec2Extra:

	test	ebx,1
	jz	Vec2uDivBlkByVec2End

	movhps	xmm0,[DReg]
	divps	xmm0,xmm1
	movhps	[DReg],xmm0

	cmp	esi,0
	je	Vec2uDivBlkByVec2End

	test	esi,1
	jz	Vec2uDivBlkByVec2Test3

	movss	[DReg],xmm2

Vec2uDivBlkByVec2Test3:

	test	esi,2
	jz	Vec2uDivBlkByVec2End

	movss	[DReg+4],xmm2

Vec2uDivBlkByVec2End:

	cmp	esi,0
	je	Vec2uDivBlkByVec2Done

	test	esi,1
	jz	Vec2uDivBlkByVec2Fix2

	movss	[AReg],xmm2

Vec2uDivBlkByVec2Fix2:

	test	esi,2
	jz	Vec2uDivBlkByVec2Done

	movss	[AReg+4],xmm2

Vec2uDivBlkByVec2Done:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2uDivideBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] vec2*   pSource
;;; [1] vec2*   pSource_Dest
;;; [0] ret
;;;
;;; AlignedBuffer<vec2> pDest += AlignedBuffer<vec2> pSource
;;;
;;; extern "C" void Vec2uDivideBlockByBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount)
;;;

_Vec2uDivideBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ebx, [STACK_PTR3]	; iCount
	mov	ecx, ebx

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *ru

	movss	xmm2,[zeroVec]		; Compare/substitute value
	movss	xmm3,[oneVec]

	cmp	ecx,2
	jge	Vec2uDivBlkByBlkPreLoop
	jmp	Vec2uDivBlkByBlkDivExtra

Vec2uDivBlkByBlkPreLoop:

	shr	ecx,1			; iCount /= 2

Vec2uDivBlkByBlkLoop:

	mov	esi,0			; Clear iFlags

	ucomiss	xmm2,[AReg]		; v0.x == 0.0f
	jne	Vec2uDivBlkByBlkChkArg1

	or	esi,1
	movss	[AReg],xmm3

Vec2uDivBlkByBlkChkArg1:

	ucomiss	xmm2,[AReg+4]		; v0.y == 0.0
	jne	Vec2uDivBlkByBlkChkArg2

	or	esi,2
	movss	[AReg+4],xmm3

Vec2uDivBlkByBlkChkArg2:

	ucomiss	xmm2,[AReg+8]		; v1.x == 0.0f
	jne	Vec2uDivBlkByBlkChkArg3

	or	esi,4
	movss	[AReg+8],xmm3

Vec2uDivBlkByBlkChkArg3:

	ucomiss	xmm2,[AReg+12]		; v1.y == 0.0f
	jne	Vec2uDivBlkByBlkDivArgs

	or	esi,8
	movss	[AReg+12],xmm3

Vec2uDivBlkByBlkDivArgs:

	movups	xmm0,[DReg]		; u u
	movups	xmm1,[AReg]		; v v
	divps	xmm0,xmm1		; u/v u/v
	movups	[DReg],xmm0		; r = u/v r = u/v

	cmp	esi,0
	jz	Vec2uDivBlkByBlkAdjPtrs

	test	esi,1			; Check arg0
	jz	Vec2uDivBlkByBlkAdjArg1

	movss	[AReg],xmm2
	movss	[DReg],xmm2

Vec2uDivBlkByBlkAdjArg1:

	test	esi,2
	jz	Vec2uDivBlkByBlkAdjArg2

	movss	[AReg+4],xmm2
	movss	[DReg+4],xmm2

Vec2uDivBlkByBlkAdjArg2:

	test	esi,4
	jz	Vec2uDivBlkByBlkAdjArg3

	movss	[AReg+8],xmm2
	movss	[DReg+8],xmm2

Vec2uDivBlkByBlkAdjArg3:

	test	esi,8
	jz	Vec2uDivBlkByBlkAdjPtrs

	movss	[AReg+12],xmm2
	movss	[DReg+12],xmm2

Vec2uDivBlkByBlkAdjPtrs:

	add	AReg,2*Vec2Size
	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2uDivBlkByBlkLoop

Vec2uDivBlkByBlkDivExtra:

	test	ebx,1
	jz	Vec2uDivBlkByBlkDivEnd

	mov	esi,0

	ucomiss	xmm2,[AReg]		; v.x == 0.0f
	jne	Vec2uDivBlkByBlkDivEx1

	or	esi,1
	movss	[AReg],xmm3

Vec2uDivBlkByBlkDivEx1:

	ucomiss	xmm2,[AReg+4]		; v.y == 0.0f
	jne	Vec2uDivBlkByBlkDivLast

	or	esi,2
	movss	[AReg+4],xmm3

Vec2uDivBlkByBlkDivLast:

	movhps	xmm0,[DReg]
	movhps	xmm1,[AReg]
	divps	xmm0,xmm1
	movhps	[DReg],xmm0

	cmp	esi,0
	jz	Vec2uDivBlkByBlkDivEnd

	test	esi,1
	jz	Vec2uDivBlkByBlkEndAdj1

	movss	[AReg],xmm2
	movss	[DReg],xmm2

Vec2uDivBlkByBlkEndAdj1:

	test	esi,2
	jz	Vec2uDivBlkByBlkDivEnd

	movss	[AReg+4],xmm2
	movss	[DReg+4],xmm2

Vec2uDivBlkByBlkDivEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

%endif

;;;
;;; Vec2BufDivVec2ByBlockSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufDivVec2ByBlockSizeAsm(vec2*         r,
;;;                                              const vec2*   u,
;;;                                              const vec2*   v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;; 

_Vec2BufDivVec2ByBlockSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize
	mov	AReg,[STACK_PTR3]	; *v
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	;; Change the vector as required to avoid divide by 0
	;;

	mov	edi,0			; iFlags = 0
	ucomiss	xmm2,[AReg]		; v.x == 0.0f
	jne	Vec2BufDivV2ByBlkSzChkArg1

	or	edi,1
	movss	[AReg],xmm3

Vec2BufDivV2ByBlkSzChkArg1:

	ucomiss	xmm2,[AReg+4]		; v.y == 0.0f
	jne	Vec2BufDivVec2ByBlkSizePreLoop

	or	edi,2
	movss	[AReg+4],xmm3

Vec2BufDivVec2ByBlkSizePreLoop:

	movhps	xmm1,[AReg]		; v

Vec2BufDivVec2ByBlkSizeLoop:

	movhps	xmm0,[BReg]		; u
	divps	xmm0,xmm1		; u / v
	movhps	[DReg],xmm0		; r = u / v

	cmp	edi,0
	je	Vec2BufDivV2ByBlkSzAdjPtrs

	test	edi,1
	jz	Vec2BufDivV2ByBlkSzAdjArg1

	movss	[DReg],xmm2

Vec2BufDivV2ByBlkSzAdjArg1:

	test	edi,2
	jz	Vec2BufDivV2ByBlkSzAdjPtrs

	movss	[DReg+4],xmm2

Vec2BufDivV2ByBlkSzAdjPtrs:

	add	BReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec2BufDivVec2ByBlkSizeLoop

	cmp	edi,0
	je	Vec2BufDivV2ByBlkSizeEnd

	test	edi,1
	jz	Vec2BufDivV2ByBlkSzAdjArg1

	movss	[AReg],xmm2

Vec2BufDivV2ByBlkSizeAdjArg1:

	test	edi,2
	jz	Vec2BufDivV2ByBlkSizeEnd

	movss	[AReg+4],xmm2

Vec2BufDivV2ByBlkSizeEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec2BufDivBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufDivBlockBySizeAsm(vec2*         r,
;;;                                          const vec2*   u,
;;;                                          const vec2*   v,
;;;                                          const int32_t iSize
;;;                                          const int32_t iCount);
;;; 

_Vec2BufDivBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	mov	AReg,[STACK_PTR3]	; *v
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec2BufDivBlkSizeLoop:

	mov	edi,0			; iFlags = 0

	ucomiss	xmm2,[AReg]		; v.x == 0.0f
	jne	Vec2BufDivBlkSizeChkArg1

	or	edi,1
	movss	[AReg],xmm3

Vec2BufDivBlkSizeChkArg1:

	ucomiss	xmm2,[AReg+4]		; v.y == 0.0f
	jne	Vec2BufDivBlkSizeExec

	or	edi,2
	movss	[AReg+4],xmm3

Vec2BufDivBlkSizeExec:

	movhps	xmm0,[BReg]
	movhps	xmm1,[AReg]
	divps	xmm0,xmm1
	movhps	[DReg],xmm0

	cmp	edi,0
	je	Vec2BufDivBlkSizeAdjPtrs

	test	edi,1
	jz	Vec2BufDivBlkSizeAdjArg1

	movss	[AReg],xmm2
	movss	[DReg],xmm2

Vec2BufDivBlkSizeAdjArg1:

	test	edi,2
	jz	Vec2BufDivBlkSizeAdjPtrs

	movss	[AReg+4],xmm2
	movss	[DReg+4],xmm2

Vec2BufDivBlkSizeAdjPtrs:

	add	AReg,esi		; *v += iSize
	add	BReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec2BufDivBlkSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec2BufDivBufBySizeAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iSrcSize1
;;; [5] vec2*   v
;;; [4] int32_t iSrcSize0
;;; [3] vec2*   u
;;; [2] int32_t iDstSize
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2BufDivBufBySizeAsm(vec2*         r,
;;;                                        const int32_t iDstSize,
;;;                                        const vec2*   u,
;;;                                        const int32_t iSrcSize0,
;;;                                        const vec2*   v,
;;;                                        const int32_t iSrcSize1,
;;;                                        const int32_t iCount);
;;;

_Vec2BufDivBufBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	ecx, [STACK_PTR7]	; iCount
	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iDstSize
	mov	edi, [STACK_PTR4]	; iSrcSize0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec2BufDivByBufLoop:

	mov	ebp,0

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec2BufDivByBufChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec2BufDivByBufChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec2BufDivByBufExec

	or	ebp,2
	movss	[BReg+4],xmm3

Vec2BufDivByBufExec:

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movhps	[DReg],xmm0		; r = u / v

	cmp	ebp,0
	je	Vec2BufDivByBufAdjPtrs

	test	ebp,1
	jz	Vec2BufDivByBufAdjArg1

	movss	[BReg],xmm2		; v.x = 0.0
	movss	[DReg],xmm2		; r.x = 0.0

Vec2BufDivByBufAdjArg1:

	test	ebp,2
	jz	Vec2BufDivByBufAdjPtrs

	movss	[BReg+4],xmm2		; v.y = 0.0
	movss	[DReg+4],xmm2		; r.y = 0.0

Vec2BufDivByBufAdjPtrs:

	add	AReg,edi		; *u += iSrcSize0
	add	DReg,esi		; *r += iDstSize0
	add	BReg,[STACK_PTR6]	; *v += iSrcSize1

	dec	ecx
	jnz	Vec2BufDivByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2LerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] float   fStep
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2LerpBlockAsm(vec2*         r,
;;;                                  const vec2*   u,
;;;                                  const vec2*   v,
;;;                                  const float   step,
;;;                                  const int32_t iCount);
;;;

_Vec2LerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, ecx
	mov	AReg,[STACK_PTR3]	; *v
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm2,[STACK_PTR4]	; step
	shufps	xmm2,xmm2,0

	cmp	ecx,2
	jl	Vec2LerpBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2LerpBlockLoop:

	movaps	xmm0,[AReg]		; v v
	movaps	xmm1,[BReg]		; u u
	movaps	xmm3,[oneVec]

	subps	xmm3,xmm2		; 1 - x
	mulps	xmm1,xmm3		; u * (1 - x)
	mulps	xmm0,xmm2		; v * x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movaps	[DReg],xmm0

	add	AReg,2*Vec2Size
	add	BReg,2*Vec2Size
	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2LerpBlockLoop

Vec2LerpBlockExtra:

	test	esi,1
	jz	Vec2LerpBlockEnd

	movhps	xmm0,[AReg]		; v
	movhps	xmm1,[BReg]		; u
	movhps	xmm3,[oneVec]

	subps	xmm3,xmm2		; 1-x
	mulps	xmm1,xmm3		; u*(1-x)
	mulps	xmm0,xmm2		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movhps	[DReg],xmm0

Vec2LerpBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2SqrBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec2*   u
;;; [1] vec2*   v
;;;
;;; extern "C" void Vec2SqrBlockAsm(vec2* r,const vec2* u,const int32_t iCount);
;;;

_Vec2SqrBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	ebx, ecx
	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *v

	cmp	ecx,2
	jl	Vec2SqrBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2SqrBlockLoop:

	movaps	xmm0,[AReg]		; u u
	mulps	xmm0,xmm0		; u*u u*u
	movaps	[DReg],xmm0		; r=sqr(u) r=sqr(u)

	add	AReg,2*Vec2Size		; *u += iSize
	add	DReg,2*Vec2Size		; *r += iSize

	dec	ecx
	jnz	Vec2SqrBlockLoop

Vec2SqrBlockExtra:

	test	ebx,1
	jz	Vec2SqrBlockEnd

	movhps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movhps	[DReg],xmm0		; r=sqr(u)

Vec2SqrBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2SqrtBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec2*   u
;;; [1] vec2*   v
;;;
;;; extern "C" void Vec2SqrtBlockAsm(vec2* r,const vec2* u,const int32_t iCount);
;;;

_Vec2SqrtBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	ebx, ecx
	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *v

	cmp	ecx,2
	jl	Vec2SqrtBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2SqrtBlockLoop:

	movaps	xmm0,[AReg]		; u u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movaps	[DReg],xmm0		; r=sqr(u) r=sqr(u)

	add	AReg,2*Vec2Size		; *u += iSize
	add	DReg,2*Vec2Size		; *r += iSize

	dec	ecx
	jnz	Vec2SqrtBlockLoop

Vec2SqrtBlockExtra:

	test	ebx,1
	jz	Vec2SqrtBlockEnd

	movhps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movhps	[DReg],xmm0		; r=sqr(u)

Vec2SqrtBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2NormalizeBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2NormalizeBlockAsm(vec2* r,const vec2* u,const int32_t iCount);
;;;

_Vec2NormalizeBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR3]	; iCount
	mov	ebx, ecx
	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	cmp	ecx,2
	jge	Vec2NormalizePreLoop
	jmp	Vec2NormalizeBlockExtra

Vec2NormalizePreLoop:

	shr	ecx,1

	movaps	xmm2,[oneVec]
	movss	xmm3,[zeroVec]

Vec2NormalizeBlockLoop:

	mov	esi,0

	movaps	xmm0,[AReg]		; v v
	movaps	xmm4,xmm0		; result
	mulps	xmm0,xmm0		; sqr(v) sqr(v)
	movaps	xmm1,xmm0

	shufps	xmm0,xmm2,SHUFFLE(1,3,0,0)	; sqr(v0.x) sqr(v1.x) 1.0 1.0
	shufps	xmm1,xmm2,SHUFFLE(0,2,0,0)	; sqr(v0.y) sqr(v1.y) 1.0 1.0
	addps	xmm0,xmm1			; sqr(v0.x)+sqr(v0.y) sqr(v1.x)+sqr(v1.y)
	sqrtps	xmm0,xmm0			; sqrt(sqr(v0.x)+sqr(v0.y))
						; sqrt(sqr(v1.x)+sqr(v1.y))
						; 1.0 1.0
	shufps	xmm0,xmm0,SHUFFLE(0,0,1,1)

	movaps	[DReg],xmm0

	ucomiss	xmm3,[DReg]
	jne	Vec2NormalizeBlockChkArg1

	or	esi,1
	movss	[DReg],xmm2
	movss	[DReg+4],xmm2

Vec2NormalizeBlockChkArg1:

	ucomiss	xmm3,[DReg+8]
	jne	Vec2NormalizeBlockExec

	or	esi,2
	movss	[DReg+8],xmm2
	movss	[DReg+12],xmm2

Vec2NormalizeBlockExec:

	divps	xmm4,[DReg]			; v / sqrt(sum(sqr(v))) v/sqrt(sum(sqr(v)))

	movaps	[DReg],xmm4

	cmp	esi,0
	je	Vec2NormalizeBlockAdjPtrs

	test	esi,1
	jz	Vec2NormalizeBlockAdjArg1

	movss	[DReg],xmm3
	movss	[DReg+4],xmm3

Vec2NormalizeBlockAdjArg1:

	test	esi,2
	jz	Vec2NormalizeBlockAdjPtrs

	movss	[DReg+8],xmm3
	movss	[DReg+12],xmm3

Vec2NormalizeBlockAdjPtrs:

	add	AReg,2*Vec2Size
	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2NormalizeBlockLoop

Vec2NormalizeBlockExtra:

	test	ebx,1
	jz	Vec2NormalizeBlockEnd

	movhps	xmm0,[AReg]		; v
	movaps	xmm4,xmm0
	mulps	xmm0,xmm0		; v*v
	movaps	xmm1,xmm0
	shufps	xmm0,xmm0,SHUFFLE(3,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(2,0,0,0)
	addss	xmm0,xmm1		; sum(sqr(v))
	sqrtss	xmm0,xmm0

	ucomiss	xmm0,xmm3		; 0.0f == sum(sqr(v))
	jne	Vec2NormalizeBlockCalc

	movss	[DReg],xmm3
	movss	[DReg+4],xmm3

	jmp	Vec2NormalizeBlockEnd

Vec2NormalizeBlockCalc:

	shufps	xmm2,xmm0,0		; sum(sqr(v)) sum(sqr(v)) 1.0f 1.0f
	divps	xmm4,xmm2		; v / sum(sqr(v))
	movhps	[DReg],xmm4

Vec2NormalizeBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2DotBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec2DotBlockAsm(float*        r,
;;;                                 const vec2*   u,
;;;                                 const vec2*   v,
;;;                                 const int32_t iCount);
;;; 

_Vec2DotBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR4]	; iCount
	mov	esi, ecx
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	cmp	ecx,2
	jl	Vec2DotBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2DotBlockLoop:

	movaps	xmm0,[AReg]		; u u
	mulps	xmm0,[BReg]		; u*v u*v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,2,0,0)	; u0.x*v0.x u1.x*v1.x xxx xxx
	shufps	xmm1,xmm1,SHUFFLE(1,3,0,0)	; u0.y*v0.y u1.y*v1.y xxx xxx

	addps	xmm0,xmm1

	movlps	[DReg],xmm0

	add	AReg,2*Vec2Size
	add	BReg,2*Vec2Size
	add	DReg,Vec2Size

	dec	ecx
	jnz	Vec2DotBlockLoop

Vec2DotBlockExtra:

	test	esi,1
	jz	Vec2DotBlockEnd

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1		; (u.x*v.x)+(u.y*v.y)

	movss	[DReg],xmm0

Vec2DotBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec2uLerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] float   fStep
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2uLerpBlockAsm(vec2*         r,
;;;                                   const vec2*   u,
;;;                                   const vec2*   v,
;;;                                   const float   step,
;;;                                   const int32_t iCount);
;;;

_Vec2uLerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, ecx
	mov	AReg,[STACK_PTR3]	; *v
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm2,[STACK_PTR4]	; step
	shufps	xmm2,xmm2,0

	cmp	ecx,2
	jl	Vec2uLerpBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2uLerpBlockLoop:

	movups	xmm0,[AReg]		; v v
	movups	xmm1,[BReg]		; u u
	movaps	xmm3,[oneVec]

	subps	xmm3,xmm2		; 1 - x
	mulps	xmm1,xmm3		; u * (1 - x)
	mulps	xmm0,xmm2		; v * x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movups	[DReg],xmm0

	add	AReg,2*Vec2Size
	add	BReg,2*Vec2Size
	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2uLerpBlockLoop

Vec2uLerpBlockExtra:

	test	esi,1
	jz	Vec2uLerpBlockEnd

	movhps	xmm0,[AReg]		; v
	movhps	xmm1,[BReg]		; u
	movhps	xmm3,[oneVec]

	subps	xmm3,xmm2		; 1-x
	mulps	xmm1,xmm3		; u*(1-x)
	mulps	xmm0,xmm2		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movhps	[DReg],xmm0

Vec2uLerpBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2uSqrBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec2*   u
;;; [1] vec2*   v
;;;
;;; extern "C" void Vec2uSqrBlockAsm(vec2* r,const vec2* u,const int32_t iCount);
;;;

_Vec2uSqrBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	ebx, ecx
	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *v

	cmp	ecx,2
	jl	Vec2uSqrBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2uSqrBlockLoop:

	movups	xmm0,[AReg]		; u u
	mulps	xmm0,xmm0		; u*u u*u
	movups	[DReg],xmm0		; r=sqr(u) r=sqr(u)

	add	AReg,2*Vec2Size		; *u += iSize
	add	DReg,2*Vec2Size		; *r += iSize

	dec	ecx
	jnz	Vec2uSqrBlockLoop

Vec2uSqrBlockExtra:

	test	ebx,1
	jz	Vec2uSqrBlockEnd

	movhps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movhps	[DReg],xmm0		; r=sqr(u)

Vec2uSqrBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2uSqrtBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec2*   u
;;; [1] vec2*   v
;;;
;;; extern "C" void Vec2uSqrtBlockAsm(vec2* r,const vec2* u,const int32_t iCount);
;;;

_Vec2uSqrtBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	ebx, ecx
	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *v

	cmp	ecx,2
	jl	Vec2uSqrtBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2uSqrtBlockLoop:

	movups	xmm0,[AReg]		; u u
	mulps	xmm0,xmm0		; u*u u*u
	movups	[DReg],xmm0		; r=sqr(u) r=sqr(u)

	add	AReg,2*Vec2Size		; *u += iSize
	add	DReg,2*Vec2Size		; *r += iSize

	dec	ecx
	jnz	Vec2uSqrtBlockLoop

Vec2uSqrtBlockExtra:

	test	ebx,1
	jz	Vec2uSqrtBlockEnd

	movhps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movhps	[DReg],xmm0		; r=sqr(u)

Vec2uSqrtBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec2uNormalizeBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec2*   u
;;; [1] vec2*   r
;;;
;;; extern "C" void Vec2uNormalizeBlockAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iCount);
;;;

_Vec2uNormalizeBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR3]	; iCount
	mov	ebx, ecx
	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	cmp	ecx,2
	jge	Vec2uNormalizePreLoop
	jmp	Vec2uNormalizeBlockExtra

Vec2uNormalizePreLoop:

	shr	ecx,1

	movaps	xmm2,[oneVec]
	movss	xmm3,[zeroVec]

Vec2uNormalizeBlockLoop:

	mov	esi,0

	movups	xmm0,[AReg]		; v v
	movaps	xmm4,xmm0		; result
	mulps	xmm0,xmm0		; sqr(v) sqr(v)
	movaps	xmm1,xmm0

	shufps	xmm0,xmm2,SHUFFLE(1,3,0,0)	; sqr(v0.x) sqr(v1.x) 1.0 1.0
	shufps	xmm1,xmm2,SHUFFLE(0,2,0,0)	; sqr(v0.y) sqr(v1.y) 1.0 1.0
	addps	xmm0,xmm1			; sqr(v0.x)+sqr(v0.y) sqr(v1.x)+sqr(v1.y)
	sqrtps	xmm0,xmm0			; sqrt(sqr(v0.x)+sqr(v0.y))
						; sqrt(sqr(v1.x)+sqr(v1.y))
						; 1.0 1.0
	shufps	xmm0,xmm0,SHUFFLE(0,0,1,1)

	movups	[DReg],xmm0

	ucomiss	xmm3,[DReg]
	jne	Vec2uNormalizeBlockChkArg1

	or	esi,1
	movss	[DReg],xmm2
	movss	[DReg+4],xmm2

Vec2uNormalizeBlockChkArg1:

	ucomiss	xmm3,[DReg+8]
	jne	Vec2uNormalizeBlockExec

	or	esi,2
	movss	[DReg+8],xmm2
	movss	[DReg+12],xmm2

Vec2uNormalizeBlockExec:

	movups	xmm5,[DReg]
	divps	xmm4,xmm5			; v / sqrt(sum(sqr(v))) v/sqrt(sum(sqr(v)))

	movups	[DReg],xmm4

	cmp	esi,0
	je	Vec2uNormalizeBlockAdjPtrs

	test	esi,1
	jz	Vec2uNormalizeBlockAdjArg1

	movss	[DReg],xmm3
	movss	[DReg+4],xmm3

Vec2uNormalizeBlockAdjArg1:

	test	esi,2
	jz	Vec2uNormalizeBlockAdjPtrs

	movss	[DReg+8],xmm3
	movss	[DReg+12],xmm3

Vec2uNormalizeBlockAdjPtrs:

	add	AReg,2*Vec2Size
	add	DReg,2*Vec2Size

	dec	ecx
	jnz	Vec2uNormalizeBlockLoop

Vec2uNormalizeBlockExtra:

	test	ebx,1
	jz	Vec2uNormalizeBlockEnd

	movhps	xmm0,[AReg]		; v
	movaps	xmm4,xmm0
	mulps	xmm0,xmm0		; v*v
	movaps	xmm1,xmm0
	shufps	xmm0,xmm0,SHUFFLE(3,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(2,0,0,0)
	addss	xmm0,xmm1		; sum(sqr(v))
	sqrtss	xmm0,xmm0

	ucomiss	xmm0,xmm3		; 0.0f == sum(sqr(v))
	jne	Vec2uNormalizeBlockCalc

	movss	[DReg],xmm3
	movss	[DReg+4],xmm3

	jmp	Vec2uNormalizeBlockEnd

Vec2uNormalizeBlockCalc:

	shufps	xmm2,xmm0,0		; sum(sqr(v)) sum(sqr(v)) 1.0f 1.0f
	divps	xmm4,xmm2		; v / sum(sqr(v))
	movhps	[DReg],xmm4

Vec2uNormalizeBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2uDotBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] vec2*   v
;;; [2] vec2*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec2uDotBlockAsm(float*        r,
;;;                                  const vec2*   u,
;;;                                  const vec2*   v,
;;;                                  const int32_t iCount);
;;; 

_Vec2uDotBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	ecx, [STACK_PTR4]	; iCount
	mov	esi, ecx
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	cmp	ecx,2
	jl	Vec2uDotBlockExtra

	shr	ecx,1			; iCount /= 2

Vec2uDotBlockLoop:

	movups	xmm0,[AReg]		; u u
	movups	xmm1,[BReg]		; v v
	mulps	xmm0,xmm1		; u*v u*v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,2,0,0)	; u0.x*v0.x u1.x*v1.x xxx xxx
	shufps	xmm1,xmm1,SHUFFLE(1,3,0,0)	; u0.y*v0.y u1.y*v1.y xxx xxx

	addps	xmm0,xmm1

	movlps	[DReg],xmm0

	add	AReg,2*Vec2Size
	add	BReg,2*Vec2Size
	add	DReg,Vec2Size

	dec	ecx
	jnz	Vec2uDotBlockLoop

Vec2uDotBlockExtra:

	test	esi,1
	jz	Vec2uDotBlockEnd

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1		; (u.x*v.x)+(u.y*v.y)

	movss	[DReg],xmm0

Vec2uDotBlockEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

%endif

;;;
;;; Vec2LerpAsm
;;;
;;; Call Stack
;;;
;;; [4] step
;;; [3] vec2* v
;;; [2] vec2* u
;;; [1] vec2* r
;;; [0] ret
;;;
;;; float lerp = (vec2& u,vec2& v,float step)
;;;
;;; return u * (1 - x) + v * x
;;;
;;; extern "C" void Vec2LerpAsm(vec2& r,const vec2& u,const vec2& v,const float step)
;;; 

_Vec2LerpAsm:
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[BReg]		; v
	movhps	xmm1,[AReg]		; u
	movss	xmm2,[STACK_PTR4]	; s
	movaps	xmm3,[oneVec]		; 1.0f

	shufps	xmm2,xmm2,0
	subps	xmm3,xmm2		; 1 - x
	mulps	xmm1,xmm3		; u*(1-x)
	mulps	xmm0,xmm2		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movhps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufLerpBufAsm
;;;
;;; Call Stack
;;;
;;; [8] int32_t iCount
;;; [7] float   s
;;; [6] int32_t iVLength
;;; [5] void*   v
;;; [4] int32_t iULength
;;; [3] void*   u
;;; [2] int32_t iRLength
;;; [1] void*   r
;;;
;;; extern "C" void Vec2BufLerpBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u
;;;                                   const int32_t iUSize,
;;;                                   const void*   v,
;;;                                   const int32_t iVSize,
;;;                                   const float   s,
;;;                                   const int32_t iCount)
;;;

_Vec2BufLerpBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iRSize
	mov	BReg,[STACK_PTR3]	; *u
	mov	edi, [STACK_PTR4]	; iUSize
	mov	AReg,[STACK_PTR5]	; *v
	mov	ebp, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR8]	; iCount

	movss	xmm3,[STACK_PTR7]	; s
	shufps	xmm3,xmm3,0
	movaps	xmm4,[oneVec]
	subps	xmm4,xmm3		; (1-x)

	movlps	xmm0,[zeroVec]
	movlps	xmm1,[zeroVec]

Vec2BufLerpBufLoop:

	movhps	xmm0,[BReg]		; u
	movhps	xmm1,[AReg]		; v

	mulps	xmm0,xmm4		; u*(1-x)
	mulps	xmm1,xmm3		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movhps	[DReg],xmm0

	add	BReg,edi		; *u += iUSize
	add	AReg,ebp		; *v += IVSize
	add	DReg,esi		; *r += iRSize

	dec	ecx
	jnz	Vec2BufLerpBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec2SqrAsm
;;;
;;; Call Stack
;;;
;;; [2] vec2* u
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 = sqr(vec2)
;;;
;;; extern "C" void Vec2SqrAsm(const vec2& r,const vec2& u)
;;; 

_Vec2SqrAsm:
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]
	mulps	xmm0,xmm0		; u*u
	movhps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2BufSqrBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec2BufSqrBufAsm(void*         r,
;;;                                  const int32_t iRSize,
;;;                                  const void*   u,
;;;                                  const int32_t iUSize,
;;;                                  const int32_t iCount);
;;;

_Vec2BufSqrBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movlps	xmm0,[zeroVec]

Vec2BufSqrBufLoop:

	movhps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movhps	[DReg],xmm0		; r=u*u

	add	AReg,esi		; *u += iUSize
	add	DReg,ebx		; *r += iRSize

	dec	ecx
	jnz	Vec2BufSqrBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2SqrtAsm
;;;
;;; Call Stack
;;;
;;; [2] vec2* u
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 = sqrt(vec2)
;;;
;;; extern "C" void Vec2SqrtAsm(const vec2& r,const vec2& u)
;;; 

_Vec2SqrtAsm:
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]
	sqrtps	xmm0,xmm0		; sqrt(u)
	movhps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2BufSqrtBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec2BufSqrtBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const int32_t iCount);
;;;

_Vec2BufSqrtBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movlps	xmm0,[zeroVec]

Vec2BufSqrtBufLoop:

	movhps	xmm0,[AReg]		; u
	sqrtps  xmm0,xmm0		; sqrt(u)
	movhps	[DReg],xmm0		; r=sqrt(u)

	add	AReg,esi		; *u += iUSize
	add	DReg,ebx		; *r += iRSize

	dec	ecx
	jnz	Vec2BufSqrtBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2NormalizeAsm
;;;
;;; Call Stack
;;;
;;; [2] vec2* u
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 = normalize(vec2)
;;;
;;; return v / sqrtf(sqr(v.x)+sqr(v.y))
;;;
;;; extern "C" void Vec2NormalizeAsm(vec2& r,const vec2& v)
;;; 

_Vec2NormalizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; v
	movlps	xmm0,[zeroVec]
	movaps	xmm2,xmm0		; save v
	mulps	xmm0,xmm0		; v*v
	movaps	xmm1,xmm0		; save v*v
	
	shufps	xmm0,xmm0,SHUFFLE(3,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1		; sqr(v.x) + sqr(v.y)
	ucomiss	xmm0,[zeroVec]
	je	Vec2NormalizeDivBy0

	sqrtss	xmm0,xmm0		; sqrt(sqr(v.x)+sqr(v.y))
	shufps	xmm0,xmm0,0
	divps	xmm2,xmm0		; v / sqrt(sum(sqr(v)))

	movhps	[DReg],xmm2

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec2NormalizeDivBy0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2BufNormalizeBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUCount
;;; [3] void*   u
;;; [2] int32_t iRCount
;;; [1] void*   r
;;;
;;; extern "C" void Vec2BufNormalizeBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const int32_t iCount)
;;;

_Vec2BufNormalizeBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]
	mov	ebx, [STACK_PTR2]
	mov	AReg,[STACK_PTR3]
	mov	esi, [STACK_PTR4]
	mov	ecx, [STACK_PTR5]

	movhps	xmm0,[zeroVec]
	movaps	xmm3,[zeroVec]

Vec2BufNormalizeBufLoop:

	movlps	xmm0,[AReg]			; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1			; u*u
	movaps	xmm2,xmm1
	shufps	xmm2,xmm2,SHUFFLE(1,1,1,1)
	addss	xmm1,xmm2

	sqrtss	xmm1,xmm1			; sqrt(sum(sqr(u)))

	ucomiss	xmm1,xmm3			; 0 == sqrt(sum(sqr(u)))
	je	Vec2BufNormalizeDB0Error

	shufps	xmm1,xmm1,0

	divps	xmm0,xmm1			; r = u / (sqrt(sum(sqr(u))))

Vec2BufNormalizeDB0Error:

	movlps	[DReg],xmm0

	add	AReg,esi			; *u += iUSize
	add	DReg,ebx			; *r += iRSize

	dec	ecx
	jnz	Vec2BufNormalizeBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec2DotAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2*  v
;;; [2] vec2*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; return u.x * v.x + u.y * v.y;
;;; 
;;; float Vec2Dot(const vec2& u,const vec2& v)
;;;
;;; extern "C" float Vec2DotAsm(float* f,const vec2& u,const vec2& v)
;;;

_Vec2DotAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; u
	movhps	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u.x*v.x u.y*v.y xxx xxx

	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,0,0,0)	; u.x*v.x xxx xxx xxx
	shufps	xmm1,xmm1,SHUFFLE(2,0,0,0)	; u.y*v.y xxx xxx xxx
	addss	xmm0,xmm1			;

	movss	[DReg],xmm0		; r = A (.) B

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufDotBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec2BufDotBufAsm(void*         r,
;;;                                  const int32_t iRSize,
;;;                                  const void*   u,
;;;                                  const int32_t iUSize,
;;;                                  const void*   v,
;;;                                  const int32_t iVSize,
;;;                                  const int32_t iCount)
;;;

_Vec2BufDotBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec2BufDotBufLoop:

	movlps	xmm0,[AReg]		; u
	movlps	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)

	addss	xmm0,xmm1		; u.x*v.x + u.y*v.y

	movss	[DReg],xmm0		; r = (u.x*v.x + u.y*v.y)

	add	AReg,esi		; *u += iUSize
	add	BReg,ebp		; *v += iVSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec2BufDotBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret
	
;;; 
;;; Vec2LengthAsm
;;;
;;; Call Stack
;;;
;;; [2] vec2* v
;;; [1] float* r
;;; [0] ret
;;;
;;; float = length(vec2&)
;;;
;;; return sqrtf(v.x * v.x + v.y * v.y);
;;;
;;; extern "C" void Vec2LengthAsm(float* r,const vec2& v)
;;;

_Vec2LengthAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movhps	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v*v
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1		; (v.x*v.x) + (v.y*v.y)
	sqrtss	xmm0,xmm0		; sqrtf((v.x*v.x)+(v.y*v.y))
	movss	[DReg],xmm0		; r = sqrtf(sum(v))

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec2LengthBlockAsm
;;;
;;; Call Stack
;;; 
;;; [3] int32_t nCount
;;; [2] vec2*   v_array
;;; [1] float*  r
;;; [0] ret
;;;
;;; extern "C" void Vec2LengthBlockAsm(float* pr,const vec2* v,const int32_t nCount)
;;;

_Vec2LengthBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	ecx, [STACK_PTR3]	; iCount
	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

Vec2LengthBlockLoop:

	movhps	xmm0,[AReg]
	mulps	xmm0,xmm0
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(3,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(2,0,0,0)

	addps	xmm0,xmm1
	sqrtss	xmm0,xmm0

	movss	[DReg],xmm0

	add	AReg,Vec2Size
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec2LengthBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec2BufLengthBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec2BufLengthBufAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const int32_t iCount)
;;;

_Vec2BufLengthBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movhps	xmm0,[zeroVec]
	movaps	xmm3,[zeroVec]

Vec2BufLengthBufLoop:

	movlps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	xmm1,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)
	addss	xmm0,xmm1
	sqrtss	xmm0,xmm0		; sqrt(sum(sqr(u)))

	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,esi		; *r += iRSize

	dec	ecx
	jnz	Vec2BufLengthBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3CopyAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* pSource
;;; [1] vec3* pDest
;;;
;;; extern "C" void Vec3CopyAsm(vec3* pDest,const vec3* pSource);
;;;

_Vec3CopyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *x

	mov	ebx,[AReg]		; v.x
	mov	[DReg],ebx

	mov	ebx,[AReg+4]		; v.y
	mov	[DReg+4],ebx

	mov	ebx,[AReg+8]		; v.z
	mov	[DReg+8],ebx

	mov	ebx,[AReg+12]		; v.n
	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3CopyBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   pSource
;;; [1] vec3*   pDest
;;;
;;; extern "C" void Vec3CopyBlockAsm(vec3* pDest,const vec3* pSource,const int32_t iCount);
;;;

_Vec3CopyBlockAsm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],Srcp
	mov	[STACK_SAVE3],Dstp

	mov	Dstp,[STACK_PTR1]	; *dest
	mov	Srcp,[STACK_PTR2]	; *src
	mov	CReg,0
	mov	ecx, [STACK_PTR3]	; iCount

	cld
	rep	movsd			; Copy

	mov	CReg,[STACK_SAVE1]
	mov	Srcp,[STACK_SAVE2]
	mov	Dstp,[STACK_SAVE3]

	ret

;;;
;;; BuildVec3PackedArrayAsm
;;;
;;; [3] int32_t iCount
;;; [2] vec3**  ppList
;;; [1] vec3*   r
;;;
;;; extern "C" void BuildVec3PackedArrayAsm(vec3* r,const vec3** pSrc,const int32_t iCount);
;;;

_BuildVec3PackedArrayAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; **pSrc
	mov	ecx, [STACK_PTR3]	; iCount

BuildVec3PackedArrayLoop:

	mov	AReg,[BReg]		; *pSrc

	mov	esi,[AReg]		; x
	mov	[DReg],esi

	mov	esi,[AReg+4]		; y
	mov	[DReg+4],esi

	mov	esi,[AReg+8]		; z
	mov	[DReg+8],esi

	mov	esi,[AReg+12]		; xxx
	mov	[DReg+12],esi

	add	BReg,PtrSize
	add	DReg,Vec3Size

	dec	ecx
	jnz	BuildVec3PackedArrayLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3AddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float     s
;;; [2] vec(3/4)* v
;;; [1] vec(3/4)* r
;;; [0] ret
;;;
;;; extern "C" void Vec3AddFloatAsm(vec3* r,const vec3* v,const float s)
;;;

_Vec3AddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ebx, [AReg+12]		; u.w

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	addps	xmm0,[AReg]		; u+s
	movaps	[DReg],xmm0		; r=u+s

	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3AddFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec3*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec3AddFloatToBlockAsm(vec3* rv,const float s,const int32_t iCount);
;;;

_Vec3AddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	mov	ecx, [STACK_PTR3]	; iCount

Vec3AddFloatToBlockLoop:

	mov	ebx, [AReg+12]		; u.w
	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + s
	movaps	[AReg],xmm0
	mov	[AReg+12],ebx

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3AddFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3AddFloatToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;; 
;;; extern "C" void Vec3AddFloatToBlockBySizeAsm(void*         rv,
;;;                                              const float   s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3AddFloatToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3AddFloatToBlkSzLoop:

	mov	ebx,[AReg+12]		; u.w
	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movaps	[AReg],xmm0		; r=u+s
	mov	[AReg+12],ebx

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3AddFloatToBlkSzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufAddFloatToBlockAsm
;;;
;;; Call Stack
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;; 
;;; extern "C" void Vec3BufAddFloatToBlockAsm(void*       r,
;;;                                           const void* u,
;;;                                           const float s,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;; 

_Vec3BufAddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebp, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec3BufAddFloatToBlkLoop:

	mov	ebx,[AReg+12]		; u.w
	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + s
	movaps	[DReg],xmm0		; r = u + s
	mov	[DReg+12],ebx		; r.w

	add	AReg,ebp		; *u += iSize
	add	DReg,ebp		; *v += iSize

	dec	ecx
	jnz	Vec3BufAddFloatToBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufAddFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufAddFloatToBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const float   s,
;;;                                         const int32_t iCount);
;;; 

_Vec3BufAddFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR6]	; iCount

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec3BufAddFloatToBufLoop:

	mov	ebx,[AReg+12]		; u.w
	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movaps	[DReg],xmm0		; r=u+s
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec3BufAddFloatToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uAddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float     s
;;; [2] vec(3/4)* v
;;; [1] vec(3/4)* r
;;; [0] ret
;;;
;;; extern "C" void Vec3uAddFloatAsm(vec3* r,const vec3* v,const float s)
;;;

_Vec3uAddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ebx, [AReg+12]		; u.w

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movups	xmm1,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movups	[DReg],xmm0		; r=u+s

	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uAddFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec3*   rv
;;; [0] ret
;;;
;;; extern "C" void Vec3uAddFloatToBlockAsm(vec3* rv,const float s,const int32_t iCount);
;;;

_Vec3uAddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	mov	ecx, [STACK_PTR3]	; iCount

Vec3uAddFloatToBlockLoop:

	mov	ebx, [AReg+12]		; u.w
	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + s
	movups	[AReg],xmm0
	mov	[AReg+12],ebx

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3uAddFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uAddFloatToBlockSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;; 
;;; extern "C" void Vec3uAddFloatToBlockBySizeAsm(void*         rv,
;;;                                               const float   s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec3uAddFloatToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3uAddFloatToBlkSzLoop:

	mov	ebx,[AReg+12]		; u.w
	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movups	[AReg],xmm0		; r=u+s
	mov	[AReg+12],ebx

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3uAddFloatToBlkSzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufAddFloatToBlockAsm
;;;
;;; Call Stack
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;; 
;;; extern "C" void Vec3uBufAddFloatToBlockAsm(void*       r,
;;;                                            const void* u,
;;;                                            const float s,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;; 

_Vec3uBufAddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	DReg,[STACK_PTR1]	; *rv
	mov	AReg,[STACK_PTR2]	; *U
	mov	ebp, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec3uBufAddFloatToBlkLoop:

	mov	ebx,[AReg+12]		; u.w
	movups	xmm0,[AReg]		; *u
	addps	xmm0,xmm1		; u+s
	movups	[DReg],xmm0		; r=u+s
	mov	[DReg+12],ebx		; r.w

	add	AReg,ebp		; *u += iSize
	add	DReg,ebp		; *r += iSize

	dec	ecx
	jnz	Vec3uBufAddFloatToBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufAddFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufAddFloatToBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const float   s,
;;;                                          const int32_t iCount);
;;; 

_Vec3uBufAddFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR6]	; iCount

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec3uBufAddFloatToBufLoop:

	mov	ebx,[AReg+12]		; u.w
	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movups	[DReg],xmm0		; r=u+s
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec3uBufAddFloatToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3SubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3SubtractFloatAsm(vec3& r,const vec3& u,const float s);
;;;

_Vec3SubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ebx, [AReg+12]

	movaps	xmm0,[AReg]		; u
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	subps	xmm0,xmm1		; u-s
	movaps	[DReg],xmm0		; r=u-s

	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret
;;;
;;; Vec3SubtractFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec3*   rv
;;;
;;; extern "C" void Vec3SubtractFloatFromBlockAsm(vec3* rv,const float s,const int32_t iCount);
;;;

_Vec3SubtractFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3SubtractFloatFromBlockLoop:

	mov	ebx,[AReg+12]		; u.w
	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u+s
	movaps	[AReg],xmm0		; r=u+s
	mov	[AReg+12],ebx

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3SubtractFloatFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3SubFloatFromBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec3SubFloatFromBlockBySizeAsm(void*       rv,
;;;                                                const float s,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;; 

_Vec3SubFloatFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3SubFloatFromBlockBySizeLoop:

	mov	ebx,[AReg+12]		; u.w
	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u+s
	movaps	[AReg],xmm0		; r=u+s
	mov	[AReg+12],ebx

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3SubFloatFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufSubFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufSubFloatFromBlockAsm(void*         r,
;;;                                             const void*   u,
;;;                                             const float   s,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec3BufSubFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec3BufSubFloatFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-s
	movaps	[DReg],xmm0		; r=u-s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *u += iSize

	dec	ecx
	jnz	Vec3BufSubFloatFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufSubFloatFromBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufSubFloatFromBufAsm(void*         r,
;;;                                           const int32_t iRSize,
;;;                                           const void*   u,
;;;                                           const int32_t iUSize,
;;;                                           const float   s,
;;;                                           const int32_t iCount);
;;; 

_Vec3BufSubFloatFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	esi, [STACK_PTR2]	; iRetSize
	mov	edi, [STACK_PTR4]	; iVecSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec3BufSubFloatFromBufLoop:

	mov	ebx,[AReg+12]		; u.w

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-s
	movaps	[DReg],xmm0		; r=u-s

	mov	[DReg+12],ebx

	add	AReg,edi		; *u += iVecSize
	add	DReg,esi		; *r += iRetSize

	dec	ecx
	jnz	Vec3BufSubFloatFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uSubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3uSubtractFloatAsm(vec3& r,const vec3& u,const float s);
;;;

_Vec3uSubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ebx, [AReg+12]		; u.w
	movups	xmm0,[AReg]		; u
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	subps	xmm0,xmm1		; u-s
	movups	[DReg],xmm0		; r=u-s

	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uSubtractFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec3*   rv
;;;
;;; extern "C" void Vec3uSubtractFloatFromBlockAsm(vec3* rv,const float s,const int32_t iCount);
;;;

_Vec3uSubtractFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3uSubtractFloatFromBlockLoop:

	mov	ebx,[AReg+12]		; u.w
	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u+s
	movups	[AReg],xmm0		; r=u+s
	mov	[AReg+12],ebx

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3uSubtractFloatFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uSubFloatFromBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec3uSubFloatFromBlockBySizeAsm(void*       rv,
;;;                                                 const float s,
;;;                                                 const int32_t iSize,
;;;                                                 const int32_t iCount);
;;; 

_Vec3uSubFloatFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3uSubFloatFromBlockBySizeLoop:

	mov	ebx,[AReg+12]		; u.w
	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u+s
	movups	[AReg],xmm0		; r=u+s
	mov	[AReg+12],ebx

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3uSubFloatFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufSubFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufSubFloatFromBlockAsm(void*         r,
;;;                                              const void*   u,
;;;                                              const float   s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3uBufSubFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec3uBufSubFloatFromBlockLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-s
	movups	[DReg],xmm0		; r=u-s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *u += iSize

	dec	ecx
	jnz	Vec3uBufSubFloatFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufSubFloatFromBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufSubFloatFromBufAsm(void*         r,
;;;                                            const int32_t iRSize,
;;;                                            const void*   u,
;;;                                            const int32_t iUSize,
;;;                                            const float   s,
;;;                                            const int32_t iCount);
;;; 

_Vec3uBufSubFloatFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	esi, [STACK_PTR2]	; iRetSize
	mov	edi, [STACK_PTR4]	; iVecSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec3uBufSubFloatFromBufLoop:

	mov	ebx,[AReg+12]

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-s
	movups	[DReg],xmm0		; r=u-s

	mov	[DReg+12],ebx

	add	AReg,edi		; *u += iVecSize
	add	DReg,esi		; *r += iRetSize

	dec	ecx
	jnz	Vec3uBufSubFloatFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3MultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3MultiplyFloatAsm(vec3*  r,const vec3* u,const float s);
;;;

_Vec3MultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	mov	ebx,[AReg+12]		; u.w

	mulps	xmm0,[AReg]
	movaps	[DReg],xmm0

	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3MultiplyFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec3*   rv
;;;
;;; extern "C" void Vec3MultiplyFloatToBlockAsm(vec3*         rv,
;;;                                             const float   s,
;;;                                             const int32_t iCount);
;;;

_Vec3MultiplyFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3MultiplyFloatToBlockLoop:

	mov	ebx,[AReg+12]		; u.x
	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movaps	[AReg],xmm0		; r=u*s
	mov	[AReg+12],ebx

	add	AReg,Vec3Size		; *rv += iSize

	dec	ecx
	jnz	Vec3MultiplyFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3MulFloatToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec3MulFloatToBlockBySizeAsm(void*         rv,
;;;                                              const float   s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3MulFloatToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3MulFloatToBlockBySizeLoop:

	mov	ebx,[AReg+12]		; u.w
	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movaps	[AReg],xmm0		; r=u*s
	mov	[AReg+12],ebx		; u.w

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3MulFloatToBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufMulFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufMulFloatToBlockAsm(void*  r,
;;;                                           const void* u,
;;;                                           const float s,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Vec3BufMulFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec3BufMulFloatToBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movaps	[DReg],xmm0		; r=u*s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufMulFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufMulFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufMulFloatToBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const float   s,
;;;                                         const int32_t iCount);
;;; 

_Vec3BufMulFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec3BufMulBufToBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movaps	[DReg],xmm0		; r=u*s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec3BufMulBufToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uMultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3uMultiplyFloatAsm(vec3*  r,const vec3* u,const float s);
;;;

_Vec3uMultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	mov	ebx,[AReg+12]		; u.w

	movups	xmm1,[AReg]
	mulps	xmm0,xmm1
	movups	[DReg],xmm0

	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uMultiplyFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec3*   rv
;;;
;;; extern "C" void Vec3uMultiplyFloatToBlockAsm(vec3*         rv,
;;;                                              const float   s,
;;;                                              const int32_t iCount);
;;;

_Vec3uMultiplyFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3uMultiplyFloatToBlockLoop:

	mov	ebx,[AReg+12]		; u.x
	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movups	[AReg],xmm0		; r=u*s
	mov	[AReg+12],ebx

	add	AReg,Vec3Size		; *rv += iSize

	dec	ecx
	jnz	Vec3uMultiplyFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uMulFloatToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec3uMulFloatToBlockBySizeAsm(void*         rv,
;;;                                               const float   s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec3uMulFloatToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec3uMulFloatToBlockBySizeLoop:

	mov	ebx,[AReg+12]		; u.w
	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movups	[AReg],xmm0		; r=u*s
	mov	[AReg+12],ebx		; u.w

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3uMulFloatToBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufMulFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufMulFloatToBlockAsm(void*  r,
;;;                                            const void* u,
;;;                                            const float s,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec3uBufMulFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec3uBufMulFloatToBlockLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movups	[DReg],xmm0		; r=u*s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3uBufMulFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufMulFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufMulFloatToBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const float   s,
;;;                                          const int32_t iCount);
;;; 

_Vec3uBufMulFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec3uBufMulBufToBufLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movups	[DReg],xmm0		; r=u*s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec3uBufMulBufToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3DivideFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3DivideFloatAsm(vec3* r,const vec3* u,const float s);
;;;

_Vec3DivideFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR3]	; s
	ucomiss	xmm1,[zeroVec]		; s == 0.0f
	je	Vec3DivideFloatByZero

	shufps	xmm1,xmm1,0
	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[DReg],xmm0		; r=u/s

	mov	ebx,[AReg+12]
	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec3DivideFloatByZero:

	mov	ebx,[zeroVec]
	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	ebx,[AReg+12]
	mov	[DReg+12],ebx

	mov	AReg,[STACK_PTR1]
	mov	BReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR3]

	ret

;;;
;;; Vec3DivideBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec3*   rv
;;;
;;; extern "C" void Vec3DivideBlockByFloatAsm(vec3* rv,const float s,const int32_t iCount);
;;;

_Vec3DivideBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s

	ucomiss	xmm1,[zeroVec]		; 0.0f == s
	je	Vec3DivideBlockByFloatDB0

	shufps	xmm1,xmm1,0

Vec3DivideBlockByFloatLoop:

	mov	ebx, [AReg+12]		; u.w
	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[AReg],xmm0		; r=u/s
	mov	[AReg+12],ebx

	add	AReg,Vec3Size		; *u += iSize

	dec	ecx
	jnz	Vec3DivideBlockByFloatLoop

Vec3DivideBlockByFloatDB0:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;; 
;;; Vec3DivBlockByFloatBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec3DivBlockByFloatBySizeAsm(void*         rv,
;;;                                              const float   s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3DivBlockByFloatBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	movss	xmm2,[oneVec]
	ucomiss	xmm1,[zeroVec]
	je	Vec3DivBlockByFloatBySzDB0

	shufps	xmm1,xmm1,0

Vec3DivBlockByFloatBySzLoop:

	mov	ebx,[AReg+12]		; u.w
	movss	[AReg+12],xmm2
	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[AReg],xmm0		; r=u/s
	mov	[AReg+12],ebx

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3DivBlockByFloatBySzLoop

Vec3DivBlockByFloatBySzDB0:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufDivBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufDivBlockByFloatAsm(void*         r,
;;;                                           const void*   u,
;;;                                           const float   s,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Vec3BufDivBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm1,[STACK_PTR3]	; s

	ucomiss	xmm1,[zeroVec]		; 0.0f == s
	je	Vec3BufDivBlkByFloatDB0

	shufps	xmm1,xmm1,0

Vec3BufDivBlockByFloatLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[DReg],xmm0		; r=u/s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufDivBlockByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

Vec3BufDivBlkByFloatDB0:

	mov	ebx,[zeroVec]

Vec3BufDivBlkByFloatDB0Loop:

	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	[DReg+12],ebx

	add	DReg,edx

	dec	ecx
	jnz	Vec3BufDivBlkByFloatDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufDivBufByFloatAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufDivBufByFloatAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const float   s,
;;;                                         const int32_t iCount);
;;; 

_Vec3BufDivBufByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	ucomiss	xmm1,[zeroVec]
	je	Vec3BufDivBufByFltDB0

	shufps	xmm1,xmm1,0

Vec3BufDivBufByFloatLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[DReg],xmm0		; r=u/s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec3BufDivBufByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

Vec3BufDivBufByFltDB0:

	mov	ebx,[zeroVec]

Vec3BufDivBufByFltDB0Loop:

	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	[DReg+12],ebx

	dec	ecx
	jnz	Vec3BufDivBufByFltDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uDivideFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3uDivideFloatAsm(vec3* r,const vec3* u,const float s);
;;;

_Vec3uDivideFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR3]	; s
	ucomiss	xmm1,[zeroVec]		; s == 0.0f
	je	Vec3uDivideFloatByZero

	shufps	xmm1,xmm1,0
	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[DReg],xmm0		; r=u/s

	mov	ebx,[AReg+12]
	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec3uDivideFloatByZero:

	mov	ebx,[zeroVec]
	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	ebx,[AReg+12]
	mov	[DReg+12],ebx

	mov	AReg,[STACK_PTR1]
	mov	BReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR3]

	ret

;;;
;;; Vec3uDivideBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec3*   rv
;;;
;;; extern "C" void Vec3uDivideBlockByFloatAsm(vec3* rv,const float s,const int32_t iCount);
;;;

_Vec3uDivideBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s

	ucomiss	xmm1,[zeroVec]		; 0.0f == s
	je	Vec3uDivideBlockByFloatDB0

	shufps	xmm1,xmm1,0

Vec3uDivideBlockByFloatLoop:

	mov	ebx, [AReg+12]		; u.w
	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[AReg],xmm0		; r=u/s
	mov	[AReg+12],ebx

	add	AReg,Vec3Size		; *u += iSize

	dec	ecx
	jnz	Vec3uDivideBlockByFloatLoop

Vec3uDivideBlockByFloatDB0:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;; 
;;; Vec3uDivBlockByFloatBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec3uDivBlockByFloatBySizeAsm(void*         rv,
;;;                                               const float   s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec3uDivBlockByFloatBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	movss	xmm2,[oneVec]
	ucomiss	xmm1,[zeroVec]
	je	Vec3uDivBlockByFloatBySzDB0

	shufps	xmm1,xmm1,0

Vec3uDivBlockByFloatBySzLoop:

	mov	ebx,[AReg+12]		; u.w
	movss	[AReg+12],xmm2
	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[AReg],xmm0		; r=u/s
	mov	[AReg+12],ebx

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3uDivBlockByFloatBySzLoop

Vec3uDivBlockByFloatBySzDB0:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufDivBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufDivBlockByFloatAsm(void*         r,
;;;                                            const void*   u,
;;;                                            const float   s,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec3uBufDivBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm1,[STACK_PTR3]	; s

	ucomiss	xmm1,[zeroVec]		; 0.0f == s
	je	Vec3uBufDivBlkByFloatDB0

	shufps	xmm1,xmm1,0

Vec3uBufDivBlockByFloatLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[DReg],xmm0		; r=u/s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3uBufDivBlockByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

Vec3uBufDivBlkByFloatDB0:

	mov	ebx,[zeroVec]

Vec3uBufDivBlkByFloatDB0Loop:

	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	[DReg+12],ebx

	add	DReg,edx

	dec	ecx
	jnz	Vec3uBufDivBlkByFloatDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufDivBufByFloatAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufDivBufByFloatAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const float   s,
;;;                                          const int32_t iCount);
;;; 

_Vec3uBufDivBufByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	ucomiss	xmm1,[zeroVec]
	je	Vec3uBufDivBufByFltDB0

	shufps	xmm1,xmm1,0

Vec3uBufDivBufByFloatLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[DReg],xmm0		; r=u/s

	mov	ebx,[AReg+12]		; u.w
	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec3uBufDivBufByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

Vec3uBufDivBufByFltDB0:

	mov	ebx,[zeroVec]

Vec3uBufDivBufByFltDB0Loop:

	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	[DReg+12],ebx

	dec	ecx
	jnz	Vec3uBufDivBufByFltDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3EqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*    v
;;; [2] vec3*    u
;;; [1] int32_t* iFlag
;;;
;;; extern "C" void Vec3EqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);
;;;

_Vec3EqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFlag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movaps	xmm0,[BReg]		; u
	movaps	xmm2,[DReg]		; v

	movss	xmm0,[BReg]		; u.x
	movss	xmm1,[DReg]		; u.x
	ucomiss	xmm0,xmm1
	je	Vec3EqualsChk2
	jmp	Vec3EqualsFalse

Vec3EqualsChk2:

	movss	xmm0,[BReg+4]
	movss	xmm1,[DReg+4]
	ucomiss	xmm0,xmm1
	je	Vec3EqualsChk3
	jmp	Vec3EqualsFalse

Vec3EqualsChk3:

	movss	xmm0,[BReg+8]
	movss	xmm1,[DReg+8]
	ucomiss	xmm0,xmm1
	jne	Vec3EqualsFalse

	mov	edx,1
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec3EqualsFalse:

	mov	edx,0
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3NotEqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*    v
;;; [2] vec3*    u
;;; [1] int32_t* iFlag
;;;
;;; extern "C" void Vec3NotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);
;;;

_Vec3NotEqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFLag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movss	xmm0,[BReg]		; u.x
	movss	xmm1,[DReg]		; v.x
	ucomiss	xmm0,xmm1
	je	Vec3NotEqualsChk2
	jmp	Vec3NotEquals

Vec3NotEqualsChk2:

	movss	xmm0,[BReg+4]		; u.y
	movss	xmm1,[DReg+4]		; v.y
	ucomiss	xmm0,xmm1
	je	Vec3NotEqualsChk3
	jmp	Vec3NotEquals

Vec3NotEqualsChk3:

	movss	xmm0,[BReg+8]		; u.z
	movss	xmm1,[DReg+8]		; v.z
	ucomiss	xmm0,xmm1
	jne	Vec3NotEquals

	mov	edx,0
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec3NotEquals:

	mov	edx,1
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret
	
%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uEqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*    v
;;; [2] vec3*    u
;;; [1] int32_t* iFlag
;;;
;;; extern "C" void Vec3uEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);
;;;

_Vec3uEqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFlag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movups	xmm0,[BReg]		; u
	movups	xmm2,[DReg]		; v

	movss	xmm0,[BReg]		; u.x
	movss	xmm1,[DReg]		; u.x
	ucomiss	xmm0,xmm1
	je	Vec3uEqualsChk2
	jmp	Vec3uEqualsFalse

Vec3uEqualsChk2:

	movss	xmm0,[BReg+4]
	movss	xmm1,[DReg+4]
	ucomiss	xmm0,xmm1
	je	Vec3uEqualsChk3
	jmp	Vec3uEqualsFalse

Vec3uEqualsChk3:

	movss	xmm0,[BReg+8]
	movss	xmm1,[DReg+8]
	ucomiss	xmm0,xmm1
	jne	Vec3uEqualsFalse

	mov	edx,1
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec3uEqualsFalse:

	mov	edx,0
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uNotEqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*    v
;;; [2] vec3*    u
;;; [1] int32_t* iFlag
;;;
;;; extern "C" void Vec3uNotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);
;;;

_Vec3uNotEqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFLag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movss	xmm0,[BReg]		; u.x
	movss	xmm1,[DReg]		; v.x
	ucomiss	xmm0,xmm1
	je	Vec3uNotEqualsChk2
	jmp	Vec3uNotEquals

Vec3uNotEqualsChk2:

	movss	xmm0,[BReg+4]		; u.y
	movss	xmm1,[DReg+4]		; v.y
	ucomiss	xmm0,xmm1
	je	Vec3uNotEqualsChk3
	jmp	Vec3uNotEquals

Vec3uNotEqualsChk3:

	movss	xmm0,[BReg+8]		; u.z
	movss	xmm1,[DReg+8]		; v.z
	ucomiss	xmm0,xmm1
	jne	Vec3uNotEquals

	mov	edx,0
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec3uNotEquals:

	mov	edx,1
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3NegateAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3NegateAsm(vec3& r,const vec3& v)
;;;

_Vec3NegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ebx,[AReg+12]		; v.w
	
	movaps	xmm0,[AReg]		; v
	mulps	xmm0,[negVec]		; (-1.0f) * v
	movaps	[DReg],xmm0

	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3NegateBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   rv
;;;
;;; extern "C" void Vec3NegateBlockAsm(vec3* rv,int32_t iCount);
;;;

_Vec3NegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR2]	;  nCount

	movaps	xmm1,[negVec]

Vec3NegateBlockLoop:

	mov	ebx,[AReg+12]		; u.w

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v
	movaps	[AReg],xmm0

	mov	[AReg+12],ebx

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3NegateBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3NegateBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   u
;;;
;;; extern "C" void Vec3NegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
;;;

_Vec3NegateBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec3NegateBlockBySizeLoop:

	mov	edx,[AReg+12]		; v.w

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v
	movaps	[AReg],xmm0		; r=-v

	mov	[AReg+12],edx

	add	AReg,ebx		; *rv += iSize

	dec	ecx
	jnz	Vec3NegateBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret
;;;
;;; Vec3BufNegateBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufNegateBlockAsm(void*  r,
;;;                                       const void* u,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;;

_Vec3BufNegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm1,[negVec]		; -1

Vec3BufNegateBlockLoop:

	mov	ebp,[AReg+12]		; u+w

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; -u
	movaps	[DReg],xmm0		; r=-u

	mov	[DReg+12],ebp

	add	AReg,ebx		; *v += iSize
	add	DReg,ebx		; *r += iSize

	dec	ecx
	jnz	Vec3BufNegateBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufNegateBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufNegateBufAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const int32_t iCount);
;;; 

_Vec3BufNegateBufAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp
	mov	[STACK_SAVE6],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRetSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec3BufNegateBufLoop:

	mov	ebp,[AReg+12]		; u.w

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; -u
	movaps	[DReg],xmm0		; r=-u

	mov	[DReg+12],ebp

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec3BufNegateBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]
	mov	BPtr,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uNegateAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3uNegateAsm(vec3& r,const vec3& v)
;;;

_Vec3uNegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ebx,[AReg+12]

	movups	xmm0,[AReg]		; v
	mulps	xmm0,[negVec]		; (-1.0f) * v
	movups	[DReg],xmm0

	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uNegateBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   rv
;;;
;;; extern "C" void Vec3uNegateBlockAsm(vec3* rv,int32_t iCount);
;;;

_Vec3uNegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR2]	;  nCount

	movaps	xmm1,[negVec]

Vec3uNegateBlockLoop:

	mov	ebx,[AReg+12]		; v.w

	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v
	movups	[AReg],xmm0

	mov	[AReg+12],ebx

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3uNegateBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret
;;;
;;; Vec3uNegateBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   u
;;;
;;; extern "C" void Vec3uNegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
;;;

_Vec3uNegateBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec3uNegateBlockBySizeLoop:

	mov	edx,[AReg+12]		; v.w

	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v
	movups	[AReg],xmm0		; r=-v

	mov	[AReg+12],edx

	add	AReg,ebx		; *rv += iSize

	dec	ecx
	jnz	Vec3uNegateBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufNegateBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufNegateBlockAsm(void*  r,
;;;                                        const void* u,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec3uBufNegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm1,[negVec]		; -1

Vec3uBufNegateBlockLoop:

	mov	ebp,[AReg+12]		; u.v

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; -u
	movups	[DReg],xmm0		; r=-u

	mov	[DReg+12],ebp

	add	AReg,ebx		; *v += iSize
	add	DReg,ebx		; *r += iSize

	dec	ecx
	jnz	Vec3uBufNegateBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufNegateBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufNegateBufAsm(void*         r,
;;;                                      const int32_t iRSize,
;;;                                      const void*   u,
;;;                                      const int32_t iUSize,
;;;                                      const int32_t iCount);
;;; 

_Vec3uBufNegateBufAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp
	mov	[STACK_SAVE6],BReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRetSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec3uBufNegateBufLoop:

	mov	ebx,[AReg+12]		; u.w

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; -u
	movups	[DReg],xmm0		; r=-u

	mov	[DReg+12],ebx

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec3uBufNegateBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]
	mov	BReg,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;; 
;;; Vec3AddAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3AddAsm(vec3* r,const vec3* u,const vec3* v)
;;;

_Vec3AddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u+v
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3AddVecToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;; [0] ret
;;; 
;;; extern "C" void Vec3AddVecToBlockAsm(vec3*         ru,
;;;                                      const vec3*   v,
;;;                                      const int32_t iCount);
;;; 

_Vec3AddVecToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[BReg]		; v

Vec3AddVecToBlockLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movaps	[AReg],xmm0

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3AddVecToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3AddBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3AddVecToBlockBySizeAsm(void*         ru,
;;;                                            const void*   v,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec3AddVecToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movaps	xmm1,[BReg]		; v

Vec3AddVecToBlockBySizeLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+v
	movaps	[AReg],xmm0		; r=u+v

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3AddVecToBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufAddVecToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufAddVecToBlockAsm(void*         r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec3BufAddVecToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR5]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iSize

	movaps	xmm1,[BReg]		; v

Vec3BufAddVecToBlockLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movaps	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufAddVecToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufAddVecToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] void*   v
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;; 
;;; extern "C" void Vec3BufAddVecToBufAsm(void*         r,
;;;                                       const int32_t iRSize,
;;;                                       const void*   u,
;;;                                       const int32_t iUSize,
;;;                                       const void*   v,
;;;                                       const int32_t iCount);
;;;

_Vec3BufAddVecToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	BReg,[STACK_PTR5]	; *v
	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize

	movaps	xmm1,[BReg]

Vec3BufAddVecToBufLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+v
	movaps	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *v += iRetSize

	dec	ecx
	jnz	Vec3BufAddVecToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec3AddBlockToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v         ; Vec3Array
;;; [1] vec3*   ru        ; Vec3Array
;;;
;;; extern "C" void Vec3AddBlockToBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3AddBlockToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]

Vec3AddBlockToBlockLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u+v
	movaps	[AReg],xmm0		; r=u+v

	add	AReg,Vec3Size		; *ru += iSize
	add	BReg,Vec3Size		; *v  += iSize

	dec	ecx
	jnz	Vec3AddBlockToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3AddBlockToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3AddBlockToBlockBySizeAsm(void* ru,
;;;                                              const void* v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3AddBlockToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec3AddBlkToBlkBySzLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3AddBlkToBlkBySzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufAddBlockToBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufAddBlockToBufAsm(void*         r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec3BufAddBlockToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

Vec3BufAddBlockToBufLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u+v
	movaps	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufAddBlockToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufAddBufToBufAsm
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufAddBufToBufAsm(void*         r,
;;;                                       const int32_t iRSize,
;;;                                       const void*   u,
;;;                                       const int32_t iUSize,
;;;                                       const void*   v,
;;;                                       const int32_t iVSize,
;;;                                       const int32_t iCount);
;;; 

_Vec3BufAddBufToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ebp, [STACK_PTR2]	; iRSize

Vec3BufAddBufToBufLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u+v
	movaps	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3BufAddBufToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;; 
;;; Vec3uAddAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3uAddAsm(vec3* r,const vec3* u,const vec3* v)
;;;

_Vec3uAddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u+v
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uAddVecToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;; [0] ret
;;; 
;;; extern "C" void Vec3uAddVec3ToBlockAsm(vec3*         ru,
;;;                                        const vec3*   v,
;;;                                        const int32_t iCount);
;;; 

_Vec3uAddVecToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movups	xmm1,[BReg]		; v

Vec3uAddVecToBlockLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movups	[AReg],xmm0

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3uAddVecToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uAddBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uAddVecToBlockBySizeAsm(void*         ru,
;;;                                             const void*   v,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec3uAddVecToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movups	xmm1,[BReg]		; v

Vec3uAddVecToBlockBySizeLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+v
	movups	[AReg],xmm0		; r=u+v

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec3uAddVecToBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufAddVecToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufAddVecToBlockAsm(void*         r,
;;;                                          const void*   u,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec3uBufAddVecToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR5]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iSize

	movups	xmm1,[BReg]		; v

Vec3uBufAddVecToBlockLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movups	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3uBufAddVecToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufAddVecToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] void*   v
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;; 
;;; extern "C" void Vec3uBufAddVecToBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const void*   v,
;;;                                        const int32_t iCount);
;;;

_Vec3uBufAddVecToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	BReg,[STACK_PTR5]	; *v
	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize

	movups	xmm1,[BReg]

Vec3uBufAddVecToBufLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+v
	movups	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *v += iRetSize

	dec	ecx
	jnz	Vec3uBufAddVecToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec3uAddBlockToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v         ; Vec3Array
;;; [1] vec3*   ru        ; Vec3Array
;;;
;;; extern "C" void Vec3uAddBlockToBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3uAddBlockToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]

Vec3uAddBlockToBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1  		; u+v
	movups	[AReg],xmm0		; r=u+v

	add	AReg,Vec3Size		; *ru += iSize
	add	BReg,Vec3Size		; *v  += iSize

	dec	ecx
	jnz	Vec3uAddBlockToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uAddBlockToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uAddBlockToBlockBySizeAsm(void* ru,
;;;                                               const void* v,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec3uAddBlockToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec3uAddBlkToBlkBySzLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3uAddBlkToBlkBySzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufAddBlockToBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufAddBlockToBufAsm(void*         r,
;;;                                          const void*   u,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec3uBufAddBlockToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

Vec3uBufAddBlockToBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u+v
	movups	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3uBufAddBlockToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufAddBufToBufAsm
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufAddBufToBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const void*   v,
;;;                                        const int32_t iVSize,
;;;                                        const int32_t iCount);
;;; 

_Vec3uBufAddBufToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ebp, [STACK_PTR2]	; iRSize

Vec3uBufAddBufToBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u+v
	movups	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufAddBufToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3SubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3SubtractAsm(vec3* r,const vec3* u,const vec3* v);
;;;

_Vec3SubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u - v
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3SubVecFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3SubVecFromBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3SubVecFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[BReg]		; v

Vec3SubVecFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-v
	movaps	[AReg],xmm0		; r=u-v

	add	AReg,Vec3Size		; *r += iSize

	dec	ecx
	jnz	Vec3SubVecFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3SubVecFromBlockBySizeAsm
;;; 
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3SubVecFromBlockBySizeAsm(void*         ru,
;;;                                              const void*   v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3SubVecFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movaps	xmm1,[BReg]		; v

Vec3SubVecFromBlockBySizeLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movaps	[AReg],xmm0		; r=u-v

	add	AReg,edx		; *ru += iSize

	dec	ecx
	jnz	Vec3SubVecFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufSubVecFromBlockAsm
;;; 
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufSubVecFromBlockAsm(void*         r,
;;;                                           const void*   u,
;;;                                           const void*   v,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;; 

_Vec3BufSubVecFromBlockAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movaps	xmm1,[BReg]		; v

Vec3BufSubVecFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-v
	movaps	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufSubVecFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufSubVecFromBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufSubBufFromBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const vec3*   v,
;;;                                         const int32_t iCount);
;;; 

_Vec3BufSubVecFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; iRSize

	movaps	xmm1,[BReg]		; v

Vec3BufSubVecFromBufLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movaps	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += UiSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufSubVecFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec3SubBlockFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3SubBlockFromBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3SubBlockFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec3SubBlockFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u-v
	movaps	[AReg],xmm0		; r=u-v

	add	AReg,Vec3Size		; *ru += iSize
	add	BReg,Vec3Size		; *v  += iSize

	dec	ecx
	jnz	Vec3SubBlockFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3SubBlockFromBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3SubBlockFromBlockBySizeAsm(void* ru,
;;;                                                const void* v,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec3SubBlockFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec3SubBlockFromBlockBySizeLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u-v
	movaps	[AReg],xmm0		; r=u-v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3SubBlockFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufSubBlockFromBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufSubBlockFromBufAsm(void*         r,
;;;                                           const void*   u,
;;;                                           const void*   v,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Vec3BufSubBlockFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

Vec3BufSubBlockFromBufLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u-v
	movaps	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufSubBlockFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufSubBufFromBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufSubBufFromBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const void*   v,
;;;                                         const int32_t iVSize,
;;;                                         const int32_t iCount);
;;;

_Vec3BufSubBufFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ebp, [STACK_PTR2]	; iRSize

Vec3BufSubBufFromBufLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u-v

	movaps	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3BufSubBufFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uSubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3uSubtractAsm(vec3* r,const vec3* u,const vec3* v);
;;;

_Vec3uSubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u - v
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uSubVecFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uSubVecFromBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3uSubVecFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movups	xmm1,[BReg]		; v

Vec3uSubVecFromBlockLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-v
	movups	[AReg],xmm0		; r=u-v

	add	AReg,Vec3Size		; *r += iSize

	dec	ecx
	jnz	Vec3uSubVecFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uSubVecFromBlockBySizeAsm
;;; 
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uSubVecFromBlockBySizeAsm(void*         ru,
;;;                                               const void*   v,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec3uSubVecFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movups	xmm1,[BReg]		; v

Vec3uSubVecFromBlockBySizeLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movups	[AReg],xmm0		; r=u-v

	add	AReg,edx		; *ru += iSize

	dec	ecx
	jnz	Vec3uSubVecFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufSubVecFromBlockAsm
;;; 
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufSubVecFromBlockAsm(void*         r,
;;;                                            const void*   u,
;;;                                            const void*   v,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;; 

_Vec3uBufSubVecFromBlockAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movups	xmm1,[BReg]		; v

Vec3uBufSubVecFromBlockLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-v
	movups	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3uBufSubVecFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufSubVecFromBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufSubBufFromBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const vec3*   v,
;;;                                          const int32_t iCount);
;;; 

_Vec3uBufSubVecFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; iRSize

	movups	xmm1,[BReg]		; v

Vec3uBufSubVecFromBufLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movups	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += UiSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufSubVecFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec3uSubBlockFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uSubBlockFromBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3uSubBlockFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec3uSubBlockFromBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u-v
	movups	[AReg],xmm0		; r=u-v

	add	AReg,Vec3Size		; *ru += iSize
	add	BReg,Vec3Size		; *v  += iSize

	dec	ecx
	jnz	Vec3uSubBlockFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uSubBlockFromBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uSubBlockFromBlockBySizeAsm(void* ru,
;;;                                                 const void* v,
;;;                                                 const int32_t iSize,
;;;                                                 const int32_t iCount);
;;;

_Vec3uSubBlockFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec3uSubBlockFromBlockBySizeLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u-v
	movups	[AReg],xmm0		; r=u-v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3uSubBlockFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufSubBlockFromBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufSubBlockFromBufAsm(void*         r,
;;;                                            const void*   u,
;;;                                            const void*   v,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec3uBufSubBlockFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

Vec3uBufSubBlockFromBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u-v
	movups	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3uBufSubBlockFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufSubBufFromBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufSubBufFromBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const void*   v,
;;;                                          const int32_t iVSize,
;;;                                          const int32_t iCount);
;;;

_Vec3uBufSubBufFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ebp, [STACK_PTR2]	; iRSize

Vec3uBufSubBufFromBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u-v

	movups	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufSubBufFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3MultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3MultiplyAsm(vec3* r,const vec3* u,const vec3* v);
;;;

_Vec3MultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u * v
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3MulBlockByVecAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3MulBlockByVecAsm(vec3* ru,const vec3* v,const int32_t nCount);
;;;

_Vec3MulBlockByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[BReg]		; v

Vec3MulBlockByVecLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3MulBlockByVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3BufMulBufByVecAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufMulBufByVecAsm(void*         r,
;;;                                       const void*   u,
;;;                                       const void*   v,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;;

_Vec3BufMulBufByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	movaps	xmm1,[BReg]		; v
	mov	ebx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3BufMulBufByVecLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movaps	[DReg],xmm0		; r=u*v

	add	AReg,ebx		; *u += iSize
	add	DReg,ebx		; *r += iSize

	dec	ecx
	jnz	Vec3BufMulBufByVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3MulBlockByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3MulBlockByVecUseSizeAsm(void*         ru,
;;;                                             const void*   v,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec3MulBlockByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movaps	xmm1,[BReg]

Vec3MulBlockByVecUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize

	dec	ecx
	jnz	Vec3MulBlockByVecUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufMulBufByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufMulBufByVecUseSizeAsm(void*         r,
;;;                                              const int32_t iRSize,
;;;                                              const void*   u,
;;;                                              const int32_t iUSize,
;;;                                              const vec3*   v,
;;;                                              const int32_t iCount);
;;; 

_Vec3BufMulBufByVecUseSizeAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	BReg,[STACK_PTR5]	; *v
	movaps	xmm1,[BReg]		; v

	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ebx, [STACK_PTR2]	; iRSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize

Vec3BufMulBufByVecUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movaps	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *r += iUSize
	add	DReg,ebx		; *u += iRSize

	dec	ecx
	jnz	Vec3BufMulBufByVecUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3MulBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3MulBlockByBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3MulBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec3MulBlockByBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,Vec3Size
	add	BReg,Vec3Size

	dec	ecx
	jnz	Vec3MulBlockByBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3MulBlockByBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3MulBlockByBlockUseSizeAsm(void*         ru,
;;;                                               const void*   v,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec3MulBlockByBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec3MulBlockByBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3MulBlockByBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufMulBufByBlockAsm
;;; 
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufMulBufByBlockAsm(void*         r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec3BufMulBufByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

Vec3BufMulBufByBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufMulBufByBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufMulBufByBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufMulBufByBufAsm(void*  r,
;;;                                       const int32_t iRSize,
;;;                                       const void* u,
;;;                                       const int32_t iUSize,
;;;                                       const vec3* v,
;;;                                       const int32_t iVSize,
;;;                                       const int32_t iCount);
;;; 

_Vec3BufMulBufByBufAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr
	
	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; IRSize
	mov	ebp, [STACK_PTR6]	; iVSize

Vec3BufMulBufByBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *u += iUSize
	add	BReg,ebp		; *v += iVSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufMulBufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uMultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3uMultiplyAsm(vec3* r,const vec3* u,const vec3* v);
;;;

_Vec3uMultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u * v
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uMulBlockByVecAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uMulBlockByVecAsm(vec3* ru,const vec3* v,const int32_t nCount);
;;;

_Vec3uMulBlockByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movups	xmm1,[BReg]		; v

Vec3uMulBlockByVecLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3uMulBlockByVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uMulBlockByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uMulBlockByVecUseSizeAsm(void*         ru,
;;;                                              const void*   v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3uMulBlockByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movups	xmm1,[BReg]

Vec3uMulBlockByVecUseSizeLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize

	dec	ecx
	jnz	Vec3uMulBlockByVecUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufMulBufByVecAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufMulBufByVecAsm(void*         r,
;;;                                        const void*   u,
;;;                                        const void*   v,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec3uBufMulBufByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm1,[BReg]		; v
	mov	ebx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3uBufMulBufByVecLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movups	[DReg],xmm0		; r=u*v

	add	AReg,ebx		; *u += iSize
	add	DReg,ebx		; *r += iSize

	dec	ecx
	jnz	Vec3uBufMulBufByVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufMulBufByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufMulBufByVecUseSizeAsm(void*         r,
;;;                                               const int32_t iRSize,
;;;                                               const void*   u,
;;;                                               const int32_t iUSize,
;;;                                               const vec3*   v,
;;;                                               const int32_t iCount);
;;; 

_Vec3uBufMulBufByVecUseSizeAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	BReg,[STACK_PTR5]	; *v
	movups	xmm1,[BReg]		; v

	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ebx, [STACK_PTR2]	; iRSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize

Vec3uBufMulBufByVecUseSizeLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movups	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *r += iUSize
	add	DReg,ebx		; *u += iRSize

	dec	ecx
	jnz	Vec3uBufMulBufByVecUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uMulBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uMulBlockByBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3uMulBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec3uMulBlockByBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,Vec3Size
	add	BReg,Vec3Size

	dec	ecx
	jnz	Vec3uMulBlockByBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uMulBlockByBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uMulBlockByBlockUseSizeAsm(void*         ru,
;;;                                                const void*   v,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec3uMulBlockByBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec3uMulBlockByBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3uMulBlockByBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufMulBufByBlockAsm
;;; 
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufMulBufByBlockAsm(void*         r,
;;;                                          const void*   u,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec3uBufMulBufByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

Vec3uBufMulBufByBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movups	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3uBufMulBufByBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufMulBufByBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufMulBufByBufAsm(void*  r,
;;;                                        const int32_t iRSize,
;;;                                        const void* u,
;;;                                        const int32_t iUSize,
;;;                                        const vec3* v,
;;;                                        const int32_t iVSize,
;;;                                        const int32_t iCount);
;;; 

_Vec3uBufMulBufByBufAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr
	
	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; IRSize
	mov	ebp, [STACK_PTR6]	; iVSize

Vec3uBufMulBufByBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movups	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *u += iUSize
	add	BReg,ebp		; *v += iVSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufMulBufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3DivideAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3DivideAsm(vec3& r,const vec3& u,const vec3& v);
;;;

_Vec3DivideAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v

	mov	ecx,0
	movss	xmm2,[oneVec]

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm2

	movss	xmm1,[zeroVec]
	ucomiss	xmm1,[BReg]		; 0.0f == v.x
	jne	Vec3DivideChkArg1

	or	ecx,1
	movss	[BReg],xmm2

Vec3DivideChkArg1:

	ucomiss	xmm1,[BReg+4]		; 0.0f == v.y
	jne	Vec3DivideChkArg2

	or	ecx,2
	movss	[BReg+4],xmm2

Vec3DivideChkArg2:

	ucomiss	xmm1,[BReg+8]		; 0.0f == v.z
	jne	Vec3DivideExec

	or	ecx,4
	movss	[BReg+8],xmm2

Vec3DivideExec:

	movaps	xmm0,[AReg]
	divps	xmm0,[BReg]
	movaps	[DReg],xmm0

	cmp	ecx,0
	je	Vec3DivideEnd

	test	ecx,1
	jz	Vec3DivideAdjArg1

	movss	[BReg],xmm1
	movss	[DReg],xmm1

Vec3DivideAdjArg1:

	test	ecx,2
	jz	Vec3DivideAdjArg2

	movss	[BReg+4],xmm1
	movss	[DReg+4],xmm1

Vec3DivideAdjArg2:

	test	ecx,4
	jz	Vec3DivideEnd

	movss	[BReg+8],xmm1
	movss	[DReg+8],xmm1

Vec3DivideEnd:

	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;; 
;;; Vec3DivBlockByVecAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3DivBlockByVecAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3DivBlockByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v

	mov	ecx, [STACK_PTR3]	; iCount
	mov	edx, 0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0
	jne	Vec3DivBlockByVecChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec3DivBlockByVecChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3DivBlockByVecChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec3DivBlockByVecChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3DivBlockByVecExec

	or	edx,4
	movss	[BReg+8],xmm3

Vec3DivBlockByVecExec:

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movaps	xmm1,[BReg]

Vec3DivBlockByVecLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movaps	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec3DivBlockByVecAdjPtrs

	test	edx,1			; v.x == 0.0
	jz	Vec3DivBlockByVecAdjArg1

	movss	[AReg],xmm2

Vec3DivBlockByVecAdjArg1:

	test	edx,2
	jz	Vec3DivBlockByVecAdjArg2

	movss	[AReg+4],xmm2

Vec3DivBlockByVecAdjArg2:

	test	edx,4
	jz	Vec3DivBlockByVecAdjPtrs

	movss	[AReg+8],xmm2

Vec3DivBlockByVecAdjPtrs:

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3DivBlockByVecLoop

	cmp	edx,0
	je	Vec3DivBlockByVecEnd

	test	edx,1
	jz	Vec3DivBlockByVecAdjV1

	movss	[BReg],xmm2

Vec3DivBlockByVecAdjV1:

	test	edx,2
	jz	Vec3DivBlockByVecAdjV2

	movss	[BReg+4],xmm2

Vec3DivBlockByVecAdjV2:

	test	edx,4
	jz	Vec3DivBlockByVecEnd

	movss	[BReg+8],xmm2

Vec3DivBlockByVecEnd:

	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;; 
;;; Vec3DivBlockByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] vec3*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3DivBlockByVecUseSizeAsm(void* ru,
;;;                                             const vec3* v,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec3DivBlockByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec3DivBlkByVecSzChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec3DivBlkByVecSzChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3DivBlkByVecSzChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec3DivBlkByVecSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3DivBlkByVecSzExec

	or	edx,4
	movss	[BReg+8],xmm3

Vec3DivBlkByVecSzExec:

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movaps	xmm1,[BReg]

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR4]	; iCount
	mov	ebx, [STACK_PTR3]	; iSize

Vec3DivBlkByVecSzLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movaps	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec3DivBlkByVecSzAdjPtrs

	test	edx,1
	jz	Vec3DivBlkByVecSzAdjArg1

	movss	[AReg],xmm2

Vec3DivBlkByVecSzAdjArg1:

	test	edx,2
	jz	Vec3DivBlkByVecSzAdjArg2

	movss	[AReg+4],xmm2

Vec3DivBlkByVecSzAdjArg2:

	test	edx,4
	jz	Vec3DivBlkByVecSzAdjPtrs

	movss	[AReg+8],xmm2

Vec3DivBlkByVecSzAdjPtrs:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3DivBlkByVecSzLoop

	mov	BReg,[STACK_PTR2]	; *v

	cmp	edx,0
	je	Vec3DivBlkByVecSzEnd

	test	edx,1
	jz	Vec3DivBlkByVecSzAdjVec1

	movss	[BReg],xmm2

Vec3DivBlkByVecSzAdjVec1:

	test	edx,2
	jz	Vec3DivBlkByVecSzAdjVec2

	movss	[BReg+4],xmm2

Vec3DivBlkByVecSzAdjVec2:

	test	edx,4
	jz	Vec3DivBlkByVecSzEnd

	movss	[BReg+8],xmm2

Vec3DivBlkByVecSzEnd:

	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufDivBufByVecAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec3*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufDivBufByVecAsm(void*	        r,
;;;                                       const void*   u,
;;;                                       const vec3*   v,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;;

_Vec3BufDivBufByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	BReg,[STACK_PTR3]	; *v
	mov	edi,0
	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec3BufDivBufByVecChkArg1

	or	edi,1
	movss	[BReg],xmm3

Vec3BufDivBufByVecChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec3BufDivBufByVecChkArg2

	or	edi,2
	movss	[BReg+4],xmm3

Vec3BufDivBufByVecChkArg2:

	ucomiss	xmm2,[BReg+8]		; v.z == 0.0f
	jne	Vec3BufDivBufByVecExec

	or	edi,4
	movss	[BReg+8],xmm3

Vec3BufDivBufByVecExec:

	movaps	xmm1,[BReg]		; v

	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR5]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iSize

Vec3BufDivBufByVecLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movaps	[DReg],xmm0		; r=u/v

	cmp	edi,0
	je	Vec3BufDivBufByVecAdjPtrs

	test	edi,1
	jz	Vec3BufDivBufByVecAdjArg1

	movss	[DReg],xmm2

Vec3BufDivBufByVecAdjArg1:

	test	edi,2
	jz	Vec3BufDivBufByVecAdjArg2

	movss	[DReg+4],xmm2

Vec3BufDivBufByVecAdjArg2:

	test	edi,4
	jz	Vec3BufDivBufByVecAdjPtrs

	movss	[DReg+8],xmm2

Vec3BufDivBufByVecAdjPtrs:

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufDivBufByVecLoop

	cmp	edi,0
	je	Vec3BufDivBufByVecEnd

	test	edi,1
	jz	Vec3BufDivBufByVecAdjV1

	movss	[BReg],xmm2

Vec3BufDivBufByVecAdjV1:

	test	edi,2
	jz	Vec3BufDivBufByVecAdjV2

	movss	[BReg+4],xmm2

Vec3BufDivBufByVecAdjV2:

	test	edi,4
	jz	Vec3BufDivBufByVecEnd

	movss	[BReg+8],xmm2

Vec3BufDivBufByVecEnd:

	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec3BufDivBufByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufDivBufByVecUseSizeAsm(void*         r,
;;;                                              const int32_t iRSize,
;;;                                              const void*   u,
;;;                                              const int32_t iUSize,
;;;                                              const vec3*   v,
;;;                                              const int32_t iCount);
;;;

_Vec3BufDivBufByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	BReg,[STACK_PTR5]	; *v
	
	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	mov	ebp,[BReg+12]
	mov	[STACK_SAVE8],BPtr
	movss	[BReg+12],xmm3

	mov	ebp, 0

	ucomiss	xmm2,[BReg]
	jne	Vec3BufDivByVecSzChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec3BufDivByVecSzChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3BufDivByVecSzChkArg2

	or	ebp,2
	movss	[BReg+4],xmm3

Vec3BufDivByVecSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3BufDivByVecSzExec

	or	ebp,4
	movss	[BReg+8],xmm3

Vec3BufDivByVecSzExec:

	movaps	xmm1,[BReg]		; v

	mov	AReg,[STACK_PTR3]	; *u
	mov	ecx, [STACK_PTR6]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; iRSize

Vec3BufDivByVecSzLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movaps	[DReg],xmm0		; r=u/v

	cmp	ebp,0
	je	Vec3BufDivByVecSzAdjPtrs

	test	ebp,1
	jz	Vec3BufDivByVecSzAdjArg1

	movss	[DReg],xmm2

Vec3BufDivByVecSzAdjArg1:

	test	ebp,2
	jz	Vec3BufDivByVecSzAdjArg2

	movss	[DReg+4],xmm2

Vec3BufDivByVecSzAdjArg2:

	test	ebp,4
	jz	Vec3BufDivByVecSzAdjPtrs

	movss	[DReg+8],xmm2

Vec3BufDivByVecSzAdjPtrs:

	add	AReg,esi		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufDivByVecSzLoop

	cmp	ebp,0
	je	Vec3BufDivByVecSzEnd

	test	ebp,1
	jz	Vec3BufDivByVecSzAdjV1

	movss	[BReg],xmm2

Vec3BufDivByVecSzAdjV1:

	test	ebp,2
	jz	Vec3BufDivByVecSzAdjV2

	movss	[BReg+4],xmm2

Vec3BufDivByVecSzAdjV2:

	test	ebp,4
	jz	Vec3BufDivByVecSzEnd

	movss	[BReg+8],xmm2

Vec3BufDivByVecSzEnd:

	mov	BPtr,[STACK_SAVE8]
	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec3DivBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3DivBlockByBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3DivBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec3DivBlkByBlkLoop:

	mov	edx, 0			; iFlags

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec3DivBlkByBlkChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec3DivBlkByBlkChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec3DivBlkByBlkChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec3DivBlkByBlkChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3DivBlkByBlkExec

	or	edx,4
	movss	[BReg+8],xmm3

Vec3DivBlkByBlkExec:

	mov	ebp,[BReg+12]		; u.w
	movss	[BReg+12],xmm3

	movaps	xmm0,[AReg]		; u
	divps	xmm0,[BReg]		; u/v
	movaps	[AReg],xmm0		; r=u/v

	mov	[BReg+12],ebp

	cmp	edx,0
	je	Vec3DivBlkByBlkAdjPtrs

	test	edx,1
	jz	Vec3DivBlkByBlkAdjArg1

	movss	[AReg],xmm2
	movss	[BReg],xmm2

Vec3DivBlkByBlkAdjArg1:

	test	edx,2
	jz	Vec3DivBlkByBlkAdjArg2

	movss	[AReg+4],xmm2
	movss	[BReg+4],xmm2

Vec3DivBlkByBlkAdjArg2:

	test	edx,4
	jz	Vec3DivBlkByBlkAdjPtrs

	movss	[AReg+8],xmm2
	movss	[BReg+8],xmm2

Vec3DivBlkByBlkAdjPtrs:

	add	AReg,Vec3Size		; *u += iSize
	add	BReg,Vec3Size		; *v += iSize
	add	DReg,Vec3Size		; *r += iSize

	dec	ecx
	jnz	Vec3DivBlkByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;;
;;; Vec3DivBlockByBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSie
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3DivBlockByBlockUseSizeAsm(void*         ru,
;;;                                               const void*   v,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec3DivBlockByBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],BPtr

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	esi, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec3DivBlkByBlkUseSizeLoop:

	mov	edx,0

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	ucomiss	xmm2,[BReg]		; v.x == 0 ?
	jne	Vec3BufDivBlkByBlkSzChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec3BufDivBlkByBlkSzChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec3BufDivBlkByBlkSzChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec3BufDivBlkByBlkSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3BufDivBlkByBlkSzExec

	or	edx,4
	movss	[BReg+8],xmm3

Vec3BufDivBlkByBlkSzExec:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,[BReg]		; u/v
	movaps	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec3BufDivBlkByBlkSzAdjPtrs

	test	edx,1
	jz	Vec3BufDivBlkByBlkSzAdjV1

	movss	[AReg],xmm2
	movss	[BReg],xmm2

Vec3BufDivBlkByBlkSzAdjV1:

	test	edx,2
	jz	Vec3BufDivBlkByBlkSzAdjV2

	movss	[AReg+4],xmm2
	movss	[BReg+4],xmm2

Vec3BufDivBlkByBlkSzAdjV2:

	test	edx,4
	jz	Vec3BufDivBlkByBlkSzAdjPtrs

	movss	[AReg+8],xmm2
	movss	[BReg+8],xmm2

Vec3BufDivBlkByBlkSzAdjPtrs:

	mov	[BReg+12],ebp

	add	AReg,esi		; *ru += iSize
	add	BReg,esi		; *v  += iSize

	dec	ecx
	jnz	Vec3DivBlkByBlkUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	BPtr,[STACK_SAVE6]

	ret

;;; 
;;; Vec3BufDivBufByBlkAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufDivBufByBlockAsm(void*         r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec3BufDivBufByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec3BufDivBufByBlkLoop:

	mov	edi,0

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec3BufDivBufByBlkChkArg1

	or	edi,1
	movss	[BReg],xmm3

Vec3BufDivBufByBlkChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3BufDivBufByBlkChkArg2

	or	edi,2
	movss	[BReg+4],xmm3

Vec3BufDivBufByBlkChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3BufDivBufByBlkExec

	or	edi,4
	movss	[BReg+8],xmm3

Vec3BufDivBufByBlkExec:

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movaps	xmm0,[AReg]		; u
	divps	xmm0,[BReg]		; u/v
	movaps	[DReg],xmm0		; r=u/v

	mov	[BReg+12],ebp

	cmp	edi,0
	je	Vec3BufDivBufByBlkAdjPtrs

	test	edi,1
	jz	Vec3BufDivBufByBlkAdjV1

	movss	[BReg],xmm2
	movss	[DReg],xmm2

Vec3BufDivBufByBlkAdjV1:

	test	edi,2
	jz	Vec3BufDivBufByBlkAdjV2

	movss	[BReg+4],xmm2
	movss	[DReg+4],xmm2

Vec3BufDivBufByBlkAdjV2:

	test	edi,4
	jz	Vec3BufDivBufByBlkAdjPtrs

	movss	[BReg+8],xmm2
	movss	[DReg+8],xmm2

Vec3BufDivBufByBlkAdjPtrs:

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3BufDivBufByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec3BufDivBufByBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufDivBufByBufAsm(void*         r,
;;;                                       const int32_t iRSize,
;;;                                       const void*   u,
;;;                                       const int32_t iUSize,
;;;                                       const void*   v,
;;;                                       const int32_t iVSize,
;;;                                       const int32_t iCount);
;;; 

_Vec3BufDivBufByBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	edi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ecx, [STACK_PTR7]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec3BufDivBufByBufLoop:

	mov	ebp,0			; iFlags

	ucomiss	xmm2,[BReg]		; v.z == 0.0f
	jne	Vec3BufDivBufByBufChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec3BufDivBufByBufChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3BufDivBufByBufChkArg2

	or	ebp,2
	movss	[BReg+4],xmm3

Vec3BufDivBufByBufChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3BufDivBufByBufExec

	or	ebp,4
	movss	[BReg+8],xmm3

Vec3BufDivBufByBufExec:

	mov	[STACK_SAVE8],ebp
	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movaps	xmm0,[AReg]		; u
	divps	xmm0,[BReg]		; u/v
	movaps	[DReg],xmm0		; r=u/v

	mov	[BReg+12],ebp
	mov	ebp,[STACK_SAVE8]

	cmp	ebp,0
	je	Vec3BufDivBufByBufAdjPtrs

	test	ebp,1
	jz	Vec3BufDivBufByBufAdjV1

	movss	[BReg],xmm2
	movss	[DReg],xmm2

Vec3BufDivBufByBufAdjV1:

	test	ebp,2
	jz	Vec3BufDivBufByBufAdjV2

	movss	[BReg+4],xmm2
	movss	[DReg+4],xmm2

Vec3BufDivBufByBufAdjV2:

	test	ebp,4
	jz	Vec3BufDivBufByBufAdjPtrs

	movss	[BReg+8],xmm2
	movss	[DReg+8],xmm2

Vec3BufDivBufByBufAdjPtrs:

	add	AReg,edi
	add	BReg,[STACK_PTR6]
	add	DReg,esi

	dec	ecx
	jnz	Vec3BufDivBufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uDivideAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3uDivideAsm(vec3& r,const vec3& u,const vec3& v);
;;;

_Vec3uDivideAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ecx,0
	movss	xmm2,[oneVec]

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm2

	movss	xmm1,[zeroVec]
	ucomiss	xmm1,[BReg]		; 0.0f == v.x
	jne	Vec3uDivideChkArg1

	or	ecx,1
	movss	[BReg],xmm2

Vec3uDivideChkArg1:

	ucomiss	xmm1,[BReg+4]		; 0.0f == v.y
	jne	Vec3uDivideChkArg2

	or	ecx,2
	movss	[BReg+4],xmm2

Vec3uDivideChkArg2:

	ucomiss	xmm1,[BReg+8]		; 0.0f == v.z
	jne	Vec3uDivideExec

	or	ecx,4
	movss	[BReg+8],xmm2

Vec3uDivideExec:

	movups	xmm0,[AReg]
	movups	xmm1,[BReg]
	divps	xmm0,xmm1
	movups	[DReg],xmm0

	cmp	ecx,0
	je	Vec3uDivideEnd

	test	ecx,1
	jz	Vec3uDivideAdjArg1

	movss	[BReg],xmm1
	movss	[DReg],xmm1

Vec3uDivideAdjArg1:

	test	ecx,2
	jz	Vec3uDivideAdjArg2

	movss	[BReg+4],xmm1
	movss	[DReg+4],xmm1

Vec3uDivideAdjArg2:

	test	ecx,4
	jz	Vec3uDivideEnd

	movss	[BReg+8],xmm1
	movss	[DReg+8],xmm1

Vec3uDivideEnd:

	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;; 
;;; Vec3uDivBlockByVecAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uDivBlockByVecAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3uDivBlockByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v

	mov	ecx, [STACK_PTR3]	; iCount
	mov	edx, 0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0
	jne	Vec3uDivBlockByVecChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec3uDivBlockByVecChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3uDivBlockByVecChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec3uDivBlockByVecChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3uDivBlockByVecExec

	or	edx,4
	movss	[BReg+8],xmm3

Vec3uDivBlockByVecExec:

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movups	xmm1,[BReg]

Vec3uDivBlockByVecLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movups	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec3uDivBlockByVecAdjPtrs

	test	edx,1			; v.x == 0.0
	jz	Vec3uDivBlockByVecAdjArg1

	movss	[AReg],xmm2

Vec3uDivBlockByVecAdjArg1:

	test	edx,2
	jz	Vec3uDivBlockByVecAdjArg2

	movss	[AReg+4],xmm2

Vec3uDivBlockByVecAdjArg2:

	test	edx,4
	jz	Vec3uDivBlockByVecAdjPtrs

	movss	[AReg+8],xmm2

Vec3uDivBlockByVecAdjPtrs:

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3uDivBlockByVecLoop

	cmp	edx,0
	je	Vec3uDivBlockByVecEnd

	test	edx,1
	jz	Vec3uDivBlockByVecAdjV1

	movss	[BReg],xmm2

Vec3uDivBlockByVecAdjV1:

	test	edx,2
	jz	Vec3uDivBlockByVecAdjV2

	movss	[BReg+4],xmm2

Vec3uDivBlockByVecAdjV2:

	test	edx,4
	jz	Vec3uDivBlockByVecEnd

	movss	[BReg+8],xmm2

Vec3uDivBlockByVecEnd:

	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;; 
;;; Vec3uDivBlockByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] vec3*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uDivBlockByVecUseSizeAsm(void* ru,
;;;                                              const vec3* v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3uDivBlockByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec3uDivBlkByVecSzChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec3uDivBlkByVecSzChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3uDivBlkByVecSzChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec3uDivBlkByVecSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3uDivBlkByVecSzExec

	or	edx,4
	movss	[BReg+8],xmm3

Vec3uDivBlkByVecSzExec:

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movups	xmm1,[BReg]

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR4]	; iCount
	mov	ebx, [STACK_PTR3]	; iSize

Vec3uDivBlkByVecSzLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movups	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec3uDivBlkByVecSzAdjPtrs

	test	edx,1
	jz	Vec3uDivBlkByVecSzAdjArg1

	movss	[AReg],xmm2

Vec3uDivBlkByVecSzAdjArg1:

	test	edx,2
	jz	Vec3uDivBlkByVecSzAdjArg2

	movss	[AReg+4],xmm2

Vec3uDivBlkByVecSzAdjArg2:

	test	edx,4
	jz	Vec3uDivBlkByVecSzAdjPtrs

	movss	[AReg+8],xmm2

Vec3uDivBlkByVecSzAdjPtrs:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3uDivBlkByVecSzLoop

	mov	BReg,[STACK_PTR2]	; *v

	cmp	edx,0
	je	Vec3uDivBlkByVecSzEnd

	test	edx,1
	jz	Vec3uDivBlkByVecSzAdjVec1

	movss	[BReg],xmm2

Vec3uDivBlkByVecSzAdjVec1:

	test	edx,2
	jz	Vec3uDivBlkByVecSzAdjVec2

	movss	[BReg+4],xmm2

Vec3uDivBlkByVecSzAdjVec2:

	test	edx,4
	jz	Vec3uDivBlkByVecSzEnd

	movss	[BReg+8],xmm2

Vec3uDivBlkByVecSzEnd:

	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufDivBufByVecAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec3*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufDivBufByVecAsm(void*         r,
;;;                                        const void*   u,
;;;                                        const vec3*   v,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec3uBufDivBufByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	BReg,[STACK_PTR3]	; *v
	mov	edi,0
	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec3uBufDivBufByVecChkArg1

	or	edi,1
	movss	[BReg],xmm3

Vec3uBufDivBufByVecChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec3uBufDivBufByVecChkArg2

	or	edi,2
	movss	[BReg+4],xmm3

Vec3uBufDivBufByVecChkArg2:

	ucomiss	xmm2,[BReg+8]		; v.z == 0.0f
	jne	Vec3uBufDivBufByVecExec

	or	edi,4
	movss	[BReg+8],xmm3

Vec3uBufDivBufByVecExec:

	movups	xmm1,[BReg]		; v

	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR5]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iSize

Vec3uBufDivBufByVecLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movups	[DReg],xmm0		; r=u/v

	cmp	edi,0
	je	Vec3uBufDivBufByVecAdjPtrs

	test	edi,1
	jz	Vec3uBufDivBufByVecAdjArg1

	movss	[DReg],xmm2

Vec3uBufDivBufByVecAdjArg1:

	test	edi,2
	jz	Vec3uBufDivBufByVecAdjArg2

	movss	[DReg+4],xmm2

Vec3uBufDivBufByVecAdjArg2:

	test	edi,4
	jz	Vec3uBufDivBufByVecAdjPtrs

	movss	[DReg+8],xmm2

Vec3uBufDivBufByVecAdjPtrs:

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *v += iSize

	dec	ecx
	jnz	Vec3uBufDivBufByVecLoop

	cmp	edi,0
	je	Vec3uBufDivBufByVecEnd

	test	edi,1
	jz	Vec3uBufDivBufByVecAdjV1

	movss	[BReg],xmm2

Vec3uBufDivBufByVecAdjV1:

	test	edi,2
	jz	Vec3uBufDivBufByVecAdjV2

	movss	[BReg+4],xmm2

Vec3uBufDivBufByVecAdjV2:

	test	edi,4
	jz	Vec3uBufDivBufByVecEnd

	movss	[BReg+8],xmm2

Vec3uBufDivBufByVecEnd:

	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec3uBufDivBufByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufDivBufByVecUseSizeAsm(void*         r,
;;;                                               const int32_t iRSize,
;;;                                               const void*   u,
;;;                                               const int32_t iUSize,
;;;                                               const vec3*   v,
;;;                                               const int32_t iCount);
;;;

_Vec3uBufDivBufByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	BReg,[STACK_PTR5]	; *v

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	mov	ebp,[BReg+12]
	mov	[STACK_SAVE8],BPtr
	movss	[BReg+12],xmm3
	
	mov	ebp, 0

	ucomiss	xmm2,[BReg]
	jne	Vec3uBufDivByVecSzChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec3uBufDivByVecSzChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3uBufDivByVecSzChkArg2

	or	ebp,2
	movss	[BReg+4],xmm3

Vec3uBufDivByVecSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3uBufDivByVecSzExec

	or	ebp,4
	movss	[BReg+8],xmm3

Vec3uBufDivByVecSzExec:

	movups	xmm1,[BReg]		; v

	mov	AReg,[STACK_PTR3]	; *u
	mov	ecx, [STACK_PTR6]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; iRSize

Vec3uBufDivByVecSzLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movups	[DReg],xmm0		; r=u/v

	cmp	ebp,0
	je	Vec3uBufDivByVecSzAdjPtrs

	test	ebp,1
	jz	Vec3uBufDivByVecSzAdjArg1

	movss	[DReg],xmm2

Vec3uBufDivByVecSzAdjArg1:

	test	ebp,2
	jz	Vec3uBufDivByVecSzAdjArg2

	movss	[DReg+4],xmm2

Vec3uBufDivByVecSzAdjArg2:

	test	ebp,4
	jz	Vec3uBufDivByVecSzAdjPtrs

	movss	[DReg+8],xmm2

Vec3uBufDivByVecSzAdjPtrs:

	add	AReg,esi		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufDivByVecSzLoop

	cmp	ebp,0
	je	Vec3uBufDivByVecSzEnd

	test	ebp,1
	jz	Vec3uBufDivByVecSzAdjV1

	movss	[BReg],xmm2

Vec3uBufDivByVecSzAdjV1:

	test	ebp,2
	jz	Vec3uBufDivByVecSzAdjV2

	movss	[BReg+4],xmm2

Vec3uBufDivByVecSzAdjV2:

	test	ebp,4
	jz	Vec3uBufDivByVecSzEnd

	movss	[BReg+8],xmm2

Vec3uBufDivByVecSzEnd:

	mov	BPtr,[STACK_SAVE8]
	mov	[BReg+12],ebp

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec3uDivBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uDivBlockByBlockAsm(vec3* ru,const vec3* v,const int32_t iCount);
;;;

_Vec3uDivBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec3uDivBlkByBlkLoop:

	mov	edx, 0			; iFlags

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec3uDivBlkByBlkChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec3uDivBlkByBlkChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec3uDivBlkByBlkChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec3uDivBlkByBlkChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3uDivBlkByBlkExec

	or	edx,4
	movss	[BReg+8],xmm3

Vec3uDivBlkByBlkExec:

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movups	[AReg],xmm0		; r=u/v

	mov	[BReg+12],ebp

	cmp	edx,0
	je	Vec3uDivBlkByBlkAdjPtrs

	test	edx,1
	jz	Vec3uDivBlkByBlkAdjArg1

	movss	[AReg],xmm2
	movss	[BReg],xmm2

Vec3uDivBlkByBlkAdjArg1:

	test	edx,2
	jz	Vec3uDivBlkByBlkAdjArg2

	movss	[AReg+4],xmm2
	movss	[BReg+4],xmm2

Vec3uDivBlkByBlkAdjArg2:

	test	edx,4
	jz	Vec3uDivBlkByBlkAdjPtrs

	movss	[AReg+8],xmm2
	movss	[BReg+8],xmm2

Vec3uDivBlkByBlkAdjPtrs:

	add	AReg,Vec3Size		; *u += iSize
	add	BReg,Vec3Size		; *v += iSize
	add	DReg,Vec3Size		; *r += iSize

	dec	ecx
	jnz	Vec3uDivBlkByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	BPtr,[STACK_SAVE5]

	ret

;;;
;;; Vec3uDivBlockByBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSie
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uDivBlockByBlockUseSizeAsm(void*         ru,
;;;                                                const void*   v,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec3uDivBlockByBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],BPtr

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	esi, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec3uDivBlkByBlkUseSizeLoop:

	mov	edx,0

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	ucomiss	xmm2,[BReg]		; v.x == 0 ?
	jne	Vec3uBufDivBlkByBlkSzChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec3uBufDivBlkByBlkSzChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec3uBufDivBlkByBlkSzChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec3uBufDivBlkByBlkSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3uBufDivBlkByBlkSzExec

	or	edx,4
	movss	[BReg+8],xmm3

Vec3uBufDivBlkByBlkSzExec:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movups	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec3uBufDivBlkByBlkSzAdjPtrs

	test	edx,1
	jz	Vec3uBufDivBlkByBlkSzAdjV1

	movss	[AReg],xmm2
	movss	[BReg],xmm2

Vec3uBufDivBlkByBlkSzAdjV1:

	test	edx,2
	jz	Vec3uBufDivBlkByBlkSzAdjV2

	movss	[AReg+4],xmm2
	movss	[BReg+4],xmm2

Vec3uBufDivBlkByBlkSzAdjV2:

	test	edx,4
	jz	Vec3uBufDivBlkByBlkSzAdjPtrs

	movss	[AReg+8],xmm2
	movss	[BReg+8],xmm2

Vec3uBufDivBlkByBlkSzAdjPtrs:

	mov	[BReg+12],ebp

	add	AReg,esi		; *ru += iSize
	add	BReg,esi		; *v  += iSize

	dec	ecx
	jnz	Vec3uDivBlkByBlkUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	BPtr,[STACK_SAVE6]

	ret

;;; 
;;; Vec3uBufDivBufByBlkAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufDivBufByBlockAsm(void*         r,
;;;                                          const void*   u,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec3uBufDivBufByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec3uBufDivBufByBlkLoop:

	mov	edi,0

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec3uBufDivBufByBlkChkArg1

	or	edi,1
	movss	[BReg],xmm3

Vec3uBufDivBufByBlkChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3uBufDivBufByBlkChkArg2

	or	edi,2
	movss	[BReg+4],xmm3

Vec3uBufDivBufByBlkChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3uBufDivBufByBlkExec

	or	edi,4
	movss	[BReg+8],xmm3

Vec3uBufDivBufByBlkExec:

	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movups	[DReg],xmm0		; r=u/v

	mov	[BReg+12],ebp

	cmp	edi,0
	je	Vec3uBufDivBufByBlkAdjPtrs

	test	edi,1
	jz	Vec3uBufDivBufByBlkAdjV1

	movss	[BReg],xmm2
	movss	[DReg],xmm2

Vec3uBufDivBufByBlkAdjV1:

	test	edi,2
	jz	Vec3uBufDivBufByBlkAdjV2

	movss	[BReg+4],xmm2
	movss	[DReg+4],xmm2

Vec3uBufDivBufByBlkAdjV2:

	test	edi,4
	jz	Vec3uBufDivBufByBlkAdjPtrs

	movss	[BReg+8],xmm2
	movss	[DReg+8],xmm2

Vec3uBufDivBufByBlkAdjPtrs:

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec3uBufDivBufByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec3uBufDivBufByBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufDivBufByBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const void*   v,
;;;                                        const int32_t iVSize,
;;;                                        const int32_t iCount);
;;; 

_Vec3uBufDivBufByBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	edi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ecx, [STACK_PTR7]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec3uBufDivBufByBufLoop:

	mov	ebp,0			; iFlags

	ucomiss	xmm2,[BReg]		; v.z == 0.0f
	jne	Vec3uBufDivBufByBufChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec3uBufDivBufByBufChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec3uBufDivBufByBufChkArg2

	or	ebp,2
	movss	[BReg+4],xmm3

Vec3uBufDivBufByBufChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec3uBufDivBufByBufExec

	or	ebp,4
	movss	[BReg+8],xmm3

Vec3uBufDivBufByBufExec:

	mov	[STACK_SAVE8],ebp
	mov	ebp,[BReg+12]
	movss	[BReg+12],xmm3

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movups	[DReg],xmm0		; r=u/v

	mov	[BReg+12],ebp
	mov	ebp,[STACK_SAVE8]

	cmp	ebp,0
	je	Vec3uBufDivBufByBufAdjPtrs

	test	ebp,1
	jz	Vec3uBufDivBufByBufAdjV1

	movss	[BReg],xmm2
	movss	[DReg],xmm2

Vec3uBufDivBufByBufAdjV1:

	test	ebp,2
	jz	Vec3uBufDivBufByBufAdjV2

	movss	[BReg+4],xmm2
	movss	[DReg+4],xmm2

Vec3uBufDivBufByBufAdjV2:

	test	ebp,4
	jz	Vec3uBufDivBufByBufAdjPtrs

	movss	[BReg+8],xmm2
	movss	[DReg+8],xmm2

Vec3uBufDivBufByBufAdjPtrs:

	add	AReg,edi
	add	BReg,[STACK_PTR6]
	add	DReg,esi

	dec	ecx
	jnz	Vec3uBufDivBufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3LerpAsm
;;;
;;; Call Stack
;;; 
;;; [4]       s
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; vec3 = lerp(vec3,vec3,float)
;;;
;;; return u * (1 - x) + v * x;
;;;
;;; extern "C" void Vec3LerpAsm(vec3& r,const vec3& u,const vec3& v,const float s)
;;;

_Vec3LerpAsm:			; return u * (1 - x) + v * x

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[oneVec]
	movss	xmm1,[STACK_PTR4]	; s
	shufps	xmm1,xmm1,0

	subps	xmm0,xmm1		; (1-x)
	mulps	xmm0,[AReg]		; u*(1-x)
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movaps	[DReg],xmm0

	mov	eax,[zeroVec]
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3LerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] float   s
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3LerpBlockAsm(vec3* ru,vec3* v,const float s,const int32_t iCount)
;;;

_Vec3LerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	movss	xmm4,[STACK_PTR3]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec3LerpBlockLoop:

	movaps	xmm0,xmm5		; 1-x
	mulps	xmm0,[AReg]		; u*(1-x)
	movaps	xmm1,xmm4		; x
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movaps	[AReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,Vec3Size
	add	BReg,Vec3Size

	dec	ecx
	jnz	Vec3LerpBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3LerpBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3LerpBlockUseSize(void*         ru,
;;;                                      const void*   v,
;;;                                      const float   s,
;;;                                      const int32_t iSize,
;;;                                      const int32_t iCount);
;;; 

_Vec3LerpBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm3,[STACK_PTR3]	; s
	shufps	xmm3,xmm3,0

	movaps	xmm2,[oneVec]
	subps	xmm2,xmm3		; 1-s

Vec3LerpBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,[BReg]		; v

	mulps	xmm0,xmm2		; u*(1-s)
	mulps	xmm1,xmm3		; v*s
	addps	xmm0,xmm1		; u*(1-s)+v*s

	movaps	[AReg],xmm0		; r = u*(1-x)+(v*s)

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3LerpBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Vec3BufLerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] float   s
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] vec3*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufLerpBlockAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const vec3*   v,
;;;                                     const float   s,
;;;                                     const int32_t iCount);
;;; 

_Vec3BufLerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ecx, [STACK_PTR7]	; iCount

	movss	xmm4,[STACK_PTR6]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]		; 1.0f
	subps	xmm5,xmm4		; 1-s

Vec3BufLerpBlockLoop:

	movaps	xmm0,xmm5		; 1-x
	movaps	xmm1,xmm4		; v
	mulps	xmm0,[AReg]		; u*(1-x)
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movaps	[DReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,esi		; *u += iUSize
	add	BReg,Vec3Size		; *v += iSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufLerpBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec3BufLerpBufAsm
;;;
;;; Call Stack
;;;
;;; [8] int32_t iCount
;;; [7] float   s
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufLerpBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const void*   v,
;;;                                   const int32_t iVSize,
;;;                                   const float   s,
;;;                                   const int32_t iCount);
;;;

_Vec3BufLerpBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR8]	; iCount

	movss	xmm4,[STACK_PTR7]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]		; 1.0
	subps	xmm5,xmm4		; 1-x

Vec3BufLerpBufLoop:

	movaps	xmm0,xmm5		; 1-x
	movaps	xmm1,xmm4		; x
	mulps	xmm0,[AReg]		; u*(1-x)
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movaps	[DReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3BufLerpBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uLerpAsm
;;;
;;; Call Stack
;;; 
;;; [4]       s
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; vec3 = lerp(vec3,vec3,float)
;;;
;;; return u * (1 - x) + v * x;
;;;
;;; extern "C" void Vec3uLerpAsm(vec3& r,const vec3& u,const vec3& v,const float s)
;;;

_Vec3uLerpAsm:			; return u * (1 - x) + v * x

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[oneVec]
	movss	xmm1,[STACK_PTR4]	; s
	shufps	xmm1,xmm1,0

	subps	xmm0,xmm1		; (1-x)
	movups	xmm3,[AReg]		; u
	movups	xmm4,[BReg]		; v
	mulps	xmm0,xmm3		; u*(1-x)
	mulps	xmm1,xmm4		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movups	[DReg],xmm0

	mov	eax,[zeroVec]
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uLerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] float   s
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uLerpBlockAsm(vec3* ru,vec3* v,const float s,const int32_t iCount)
;;;

_Vec3uLerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	movss	xmm4,[STACK_PTR3]	; x
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec3uLerpBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm5		; u*(1-x)
	mulps	xmm1,xmm4		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movups	[AReg],xmm0		; r = u*(1-x)+(v*x)

	add	AReg,Vec3Size
	add	BReg,Vec3Size

	dec	ecx
	jnz	Vec3uLerpBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uLerpBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uLerpBlockUseSize(void*         ru,
;;;                                       const void*   v,
;;;                                       const float   s,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;; 

_Vec3uLerpBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm3,[STACK_PTR3]	; s
	shufps	xmm3,xmm3,0

	movaps	xmm2,[oneVec]
	subps	xmm2,xmm3		; 1-x

Vec3uLerpBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v

	mulps	xmm0,xmm2		; u*(1-x)
	mulps	xmm1,xmm3		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movups	[AReg],xmm0

	add	AReg,edx
	add	BReg,edx

	dec	ecx
	jnz	Vec3uLerpBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Vec3uBufLerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] float   s
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] vec3*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufLerpBlockAsm(void*         r,
;;;                                      const int32_t iRSize,
;;;                                      const void*   u,
;;;                                      const int32_t iUSize,
;;;                                      const vec3*   v,
;;;                                      const float   s,
;;;                                      const int32_t iCount);
;;; 

_Vec3uBufLerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ecx, [STACK_PTR7]	; iCount

	movss	xmm4,[STACK_PTR6]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec3uBufLerpBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm5		; u*(1-x)
	mulps	xmm1,xmm4		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movups	[DReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,esi		; *u += iUSize
	add	BReg,Vec3Size		; *v += iSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufLerpBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec3uBufLerpBufAsm
;;;
;;; Call Stack
;;;
;;; [8] int32_t iCount
;;; [7] float   s
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufLerpBufAsm(void*         r,
;;;                                    const int32_t iRSize,
;;;                                    const void*   u,
;;;                                    const int32_t iUSize,
;;;                                    const void*   v,
;;;                                    const int32_t iVSize,
;;;                                    const float   s,
;;;                                    const int32_t iCount);
;;;

_Vec3uBufLerpBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR8]	; iCount

	movss	xmm4,[STACK_PTR7]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec3uBufLerpBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm5		; u*(1-x)
	mulps	xmm1,xmm4		; v*x
	addps	xmm0,xmm1		; u*(1-x)*(v*x)
	movups	[DReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufLerpBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3DotAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*  v
;;; [2] vec3*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec3,vec3)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec3DotAsm(float* r,const vec3& u,const vec3& v)
;;; 

_Vec3DotAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,[zeroVec]

	mulps	xmm0,[BReg]		; u * v

	haddps	xmm0,xmm1		; (u.x*v.x)+(u.y*v.y),(u.z*v.z)+(u.w*v.w), 0, 0
	haddps	xmm0,xmm1		; (u.x*v.x)+(u.y*v.y)+(u.z*v.z)+(u.w*v.w),0,0,0

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uDotAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*  v
;;; [2] vec3*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec3,vec3)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec3uDotAsm(float* r,const vec3& u,const vec3& v)
;;; 

_Vec3uDotAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,[zeroVec]

	haddps	xmm0,xmm1		; (u.x*v.x)+(u.y*v.y),(u.z*v.z)+(u.w*v.w), 0, 0
	haddps	xmm0,xmm1		; (u.x*v.x)+(u.y*v.y)+(u.z*v.z)+(u.w*v.w),0,0,0

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3DotFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*  v
;;; [2] vec3*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec3,vec3)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec3DotFlatAsm(float* r,const vec3& u,const vec3& v)
;;; 

_Vec3DotFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u * v

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uDotFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3*  v
;;; [2] vec3*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec3,vec3)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec3uDotFlatAsm(float* r,const vec3& u,const vec3& v)
;;; 

_Vec3uDotFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3DotBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] vec3*   v
;;; [2] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3DotBlockAsm(float*        r,
;;;                                 const vec3*   u,
;;;                                 const vec3*   v,
;;;                                 const int32_t iCount);
;;; 

_Vec3DotBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR4]	; iCount

Vec3DotBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; u.x*v.x
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)	; u.y*v.y
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)	; u.z*v.z

	addss	xmm0,xmm1		; u.x*v.x + u.y*v.y
	addss	xmm0,xmm2		; u.x*v.x + u.y*v.y + u.z*v.z

	movss	[DReg],xmm0		; r = sum(u*v)

	add	AReg,Vec3Size		; *u += iSize
	add	BReg,Vec3Size		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec3DotBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3DotBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3DotBlockUseSizeAsm(float*        r,
;;;                                        const void*   u,
;;;                                        const void*   v,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec3DotBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3DotBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2

	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec3DotBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3BufDotBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufDotBufAsm(void*         r,
;;;                                  const int32_t iRSize,
;;;                                  const void*   u,
;;;                                  const int32_t iUSize,
;;;                                  const void*   v,
;;;                                  const int32_t iVSize,
;;;                                  const int32_t iCount);
;;;

_Vec3BufDotBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec3BufDotBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	addss	xmm0,xmm1
	addss	xmm0,xmm2
	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3BufDotBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uDotBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] vec3*   v
;;; [2] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3uDotBlockAsm(float*        r,
;;;                                  const vec3*   u,
;;;                                  const vec3*   v,
;;;                                  const int32_t iCount);
;;; 

_Vec3uDotBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR4]	; iCount

Vec3uDotBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; u.x*v.x
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)	; u.y*v.y
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)	; u.z*v.z

	addss	xmm0,xmm1		; u.x*v.x + u.y*v.y
	addss	xmm0,xmm2		; u.x*v.x + u.y*v.y + u.z*v.z

	movss	[DReg],xmm0		; r = sum(u*v)

	add	AReg,Vec3Size		; *u += iSize
	add	BReg,Vec3Size		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec3uDotBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uDotBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3uDotBlockUseSizeAsm(float*        r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec3uDotBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3uDotBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2

	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec3uDotBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec3uBufDotBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufDotBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const void*   v,
;;;                                   const int32_t iVSize,
;;;                                   const int32_t iCount);
;;;

_Vec3uBufDotBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec3uBufDotBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	addss	xmm0,xmm1
	addss	xmm0,xmm2
	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufDotBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; Vec3DotFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] vec3*  v
;;; [2] vec3*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec3,vec3)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec3DotFPU_Asm(float* r,const vec3& u,const vec3& v)
;;; 

_Vec3DotFPU_Asm:

	fld	dword [STACK_PTR2]
	fmul	dword [STACK_PTR3]

	fld	dword [STACK_PTR2+4]
	fmul	dword [STACK_PTR3+4]

	fld	dword [STACK_PTR2+8]
	fmul	dword [STACK_PTR3+8]

	faddp	st1,st0
	faddp	st1,st0

	fstp	dword [STACK_PTR1]

	fwait

	ret
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3SqrAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;;
;;;
;;; extern "C" void Vec3SqrAsm(vec3& r,const vec3& v);
;;;

_Vec3SqrAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3SqrBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3SqrBlockAsm(vec3* ru,const int32_t iCount);
;;;

_Vec3SqrBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	ecx, [STACK_PTR2]	; iCount

Vec3SqrBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	[AReg],xmm0		; r=u*u

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3SqrBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3SqrBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3SqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
;;;

_Vec3SqrBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

Vec3SqrBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	[AReg],xmm0		; r=u*u

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3SqrBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3BufSqrBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufSqrBufAsm(void*         r,
;;;                                  const int32_t iRSize,
;;;                                  const void*   u,
;;;                                  const int32_t iUSize,
;;;                                  const int32_t iCount);
;;; 

_Vec3BufSqrBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3BufSqrBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	[DReg],xmm0		; r=u*u

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufSqrBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uSqrAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;;
;;;
;;; extern "C" void Vec3uSqrAsm(vec3& r,const vec3& v);
;;;

_Vec3uSqrAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uSqrBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uSqrBlockAsm(vec3* ru,const int32_t iCount);
;;;

_Vec3uSqrBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	ecx, [STACK_PTR2]	; iCount

Vec3uSqrBlockLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movups	[AReg],xmm0		; r=u*u

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3uSqrBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uSqrBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uSqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
;;;

_Vec3uSqrBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

Vec3uSqrBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movups	[AReg],xmm0		; r=u*u

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3uSqrBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uBufSqrBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufSqrBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const int32_t iCount);
;;; 

_Vec3uBufSqrBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3uBufSqrBufLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movups	[DReg],xmm0		; r=u*u

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufSqrBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3SqrtAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3SqrtAsm(vec3* r,const vec3* v)
;;;

_Vec3SqrtAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *v

	movaps	xmm0,[AReg]		; v
	sqrtps	xmm0,xmm0		; sqrt(v)
	movaps	[DReg],xmm0		; r = sqrt(v)

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3SqrtBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3SqrtBlockAsm(vec3* ru,const int32_t iCount)
;;;

_Vec3SqrtBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

Vec3SqrtBlockLoop:

	movaps	xmm0,[AReg]
	sqrtps	xmm0,xmm0
	movaps	[AReg],xmm0

	add	AReg,Vec3Size

	dec	ecx
	jnz	Vec3SqrtBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3SqrtBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3SqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount)
;;;

_Vec3SqrtBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

Vec3SqrtBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movaps	[AReg],xmm0		; r = sqrt(u)

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3SqrtBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3BufSqrtBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufSqrtBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const int32_t iCount)
;;;

_Vec3BufSqrtBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3BufSqrtBufLoop:

	movaps	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movaps	[DReg],xmm0		; r = sqrt(u)

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufSqrtBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uSqrtAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;;
;;;
;;; extern "C" void Vec3uSqrtAsm(vec3& r,const vec3& v);
;;;

_Vec3uSqrtAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	sqrtps	xmm0,xmm0		; sqrt(v)
	movups	[DReg],xmm0		; r = sqrt(v)

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uSqrtBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uSqrtBlockAsm(vec3* ru,const int32_t iCount);
;;;

_Vec3uSqrtBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	ecx, [STACK_PTR2]	; iCount

Vec3uSqrtBlockLoop:

	movups	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movups	[AReg],xmm0		; r = sqrt(u)

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3uSqrtBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uSqrtBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uSqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
;;;

_Vec3uSqrtBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

Vec3uSqrtBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movups	[AReg],xmm0		; r = sqrt(u)

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3uSqrtBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uBufSqrtBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufSqrtBufAsm(void*         r,
;;;                                    const int32_t iRSize,
;;;                                    const void*   u,
;;;                                    const int32_t iUSize,
;;;                                    const int32_t iCount);
;;; 

_Vec3uBufSqrtBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3uBufSqrtBufLoop:

	movups	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movups	[DReg],xmm0		; r = sqrt(u)

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufSqrtBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3NormalizeAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3NormalizeAsm(vec3* r,const vec3* r)
;;;

_Vec3NormalizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; v * v
	movaps	xmm2,[zeroVec]

	haddps	xmm1,xmm2
	haddps	xmm1,xmm2

	ucomiss	xmm1,xmm2
	je	Vec3NormalizeDB0

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0

	divps	xmm0,xmm1

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec3NormalizeDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3NormalizeBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3NormalizeBlockAsm(vec3*         ru,
;;;                                       const int32_t iCount);
;;;

_Vec3NormalizeBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

	movaps	xmm4,[zeroVec]

Vec3NormalizeBlockLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	haddps	xmm1,xmm4
	haddps	xmm1,xmm4

	ucomiss	xmm1,xmm4
	jne	Vec3NormalizeBlockExec

	movaps	[AReg],xmm4
	jmp	Vec3NormalizeBlockAdjPtrs

Vec3NormalizeBlockExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sum(sqr(u))
	movaps	[AReg],xmm0		; r=u/sum(sqr(u))

Vec3NormalizeBlockAdjPtrs:

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3NormalizeBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3NormalizeBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3NormalizeBlockUseSizeAsm(vec3*         ru,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec3NormalizeBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm4,[zeroVec]

Vec3NormalizeBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	haddps	xmm1,xmm4
	haddps	xmm1,xmm4

	ucomiss	xmm1,xmm4
	jne	Vec3NormalizeBlockUseSzExec

	movaps	[AReg],xmm4
	jmp	Vec3NormalizeBlockUseSzAdjPtrs

Vec3NormalizeBlockUseSzExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movaps	[AReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec3NormalizeBlockUseSzAdjPtrs:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3NormalizeBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3BufNormalizeBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufNormalizeBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const int32_t iCount);
;;;

_Vec3BufNormalizeBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm4,[zeroVec]

Vec3BufNormalizeBufLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1

	haddps	xmm1,xmm4
	haddps	xmm1,xmm4

	ucomiss	xmm1,xmm4		; 0.0 == sqrt(sum(sqr(u)))
	jne	Vec3BufNormalizeBufExec

	movaps	[DReg],xmm4
	jmp	Vec3BufNormalizeAdjPtrs

Vec3BufNormalizeBufExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movaps	[DReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec3BufNormalizeAdjPtrs:

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufNormalizeBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uNormalizeAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3uNormalizeAsm(vec3* r,const vec3* r)
;;;

_Vec3uNormalizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm4,[zeroVec]
	movups	xmm0,[AReg]		; v
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; v * v

	haddps	xmm1,xmm4
	haddps	xmm1,xmm4

	ucomiss	xmm1,xmm4
	je	Vec3uNormalizeDB0

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec3uNormalizeDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uNormalizeBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uNormalizeBlockAsm(vec3*         ru,
;;;                                        const int32_t iCount);
;;;

_Vec3uNormalizeBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

	movaps	xmm4,[zeroVec]

Vec3uNormalizeBlockLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	haddps	xmm1,xmm4
	haddps	xmm1,xmm4

	ucomiss	xmm1,xmm4		; sum(sqr(u)) == 0.0
	jne	Vec3uNormalizeBlockExec

	movups	[AReg],xmm4
	jmp	Vec3uNormalizeBlockAdjPtrs

Vec3uNormalizeBlockExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sum(sqr(u))
	movups	[AReg],xmm0		; r=u/sum(sqr(u))

Vec3uNormalizeBlockAdjPtrs:

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3uNormalizeBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uNormalizeBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uNormalizeBlockUseSizeAsm(vec3*         ru,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec3uNormalizeBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm4,[zeroVec]

Vec3uNormalizeBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	haddps	xmm1,xmm4
	haddps	xmm1,xmm4

	ucomiss	xmm1,xmm4
	jne	Vec3uNormalizeBlockUseSzExec

	movups	[AReg],xmm4
	jmp	Vec3uNormalizeBlockUseSzAdjPtrs

Vec3uNormalizeBlockUseSzExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movups	[AReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec3uNormalizeBlockUseSzAdjPtrs:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3uNormalizeBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uBufNormalizeBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufNormalizeBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const int32_t iCount);
;;;

_Vec3uBufNormalizeBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm4,[zeroVec]

Vec3uBufNormalizeBufLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1

	haddps	xmm1,xmm4
	haddps	xmm1,xmm4

	ucomiss	xmm1,xmm4		; 0.0 == sqrt(sum(sqr(u)))
	jne	Vec3uBufNormalizeBufExec

	movups	[DReg],xmm4
	jmp	Vec3uBufNormalizeAdjPtrs

Vec3uBufNormalizeBufExec:

	sqrtss	xmm1,xmm1		; sqrt(sum(sqr(u)))
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movups	[DReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec3uBufNormalizeAdjPtrs:

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufNormalizeBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	
;;;
;;; Vec3NormalizeFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3NormalizeFlatAsm(vec3* r,const vec3* r)
;;;

_Vec3NormalizeFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; v * v

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1

	shufps	xmm1,xmm1,0
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	sqrtss	xmm1,xmm1

	ucomiss	xmm1,[zeroVec]
	je	Vec3NormalizeFDB0

	shufps	xmm1,xmm1,0

	divps	xmm0,xmm1

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec3NormalizeFDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3NormalizeBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3NormalizeBlockFlatAsm(vec3*         ru,
;;;                                           const int32_t iCount);
;;;

_Vec3NormalizeBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

	movaps	xmm4,[zeroVec]

Vec3NormalizeBlockLoopF:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1

	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3

	sqrtss	xmm1,xmm1

	ucomiss	xmm1,xmm4		; sum(sqr(u)) == 0.0
	jne	Vec3NormalizeBlockExecF

	movaps	[AReg],xmm4
	jmp	Vec3NormalizeBlockAdjPtrsF

Vec3NormalizeBlockExecF:

	shufps	xmm1,xmm1,0

	divps	xmm0,xmm1		; u / sum(sqr(u))

	movaps	[AReg],xmm0		; r=u/sum(sqr(u))

Vec3NormalizeBlockAdjPtrsF:

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3NormalizeBlockLoopF

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3NormalizeBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3NormalizeBlockFlatUseSizeAsm(vec3*         ru,
;;;                                                  const int32_t iSize,
;;;                                                  const int32_t iCount);
;;;

_Vec3NormalizeBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm4,[zeroVec]

Vec3NormalizeBlockUseSizeLoopF:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)

	addps	xmm1,xmm2
	addps	xmm1,xmm3

	sqrtss	xmm1,xmm1

	ucomiss	xmm1,xmm4
	jne	Vec3NormalizeBlockUseSzExecF

	movaps	[AReg],xmm4
	jmp	Vec3NormalizeBlockUseSzAdjPtrsF

Vec3NormalizeBlockUseSzExecF:

	shufps	xmm1,xmm1,0

	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movaps	[AReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec3NormalizeBlockUseSzAdjPtrsF:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3NormalizeBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3BufNormalizeBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufNormalizeBufFlatAsm(void*         r,
;;;                                            const int32_t iRSize,
;;;                                            const void*   u,
;;;                                            const int32_t iUSize,
;;;                                            const int32_t iCount);
;;;

_Vec3BufNormalizeBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm4,[zeroVec]

Vec3BufNormalizeBufLoopF:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1

	movaps	xmm2,xmm1
	movaps	xmm3,xmm2

	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3

	ucomiss	xmm1,xmm4		; 0.0 == sqrt(sum(sqr(u)))
	jne	Vec3BufNormalizeBufExecF

	movaps	[DReg],xmm4
	jmp	Vec3BufNormalizeAdjPtrsF

Vec3BufNormalizeBufExecF:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movaps	[DReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec3BufNormalizeAdjPtrsF:

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufNormalizeBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret
	
%endif
	
%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uNormalizeFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3uNormalizeFlatAsm(vec3* r,const vec3* r)
;;;

_Vec3uNormalizeFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; v * v

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1

	shufps	xmm1,xmm1,0
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3

	ucomiss	xmm1,[zeroVec]
	je	Vec3uNormalizeFDB0

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec3uNormalizeFDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uNormalizeBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uNormalizeBlockFlatAsm(vec3*         ru,
;;;                                            const int32_t iCount);
;;;

_Vec3uNormalizeBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

	movaps	xmm4,[zeroVec]

Vec3uNormalizeBlockLoopF:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1

	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3

	ucomiss	xmm1,xmm4		; sum(sqr(u)) == 0.0
	jne	Vec3uNormalizeBlockExecF

	movups	[AReg],xmm4
	jmp	Vec3uNormalizeBlockAdjPtrsF

Vec3uNormalizeBlockExecF:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sum(sqr(u))
	movups	[AReg],xmm0		; r=u/sum(sqr(u))

Vec3uNormalizeBlockAdjPtrsF:

	add	AReg,Vec3Size		; *ru += iSize

	dec	ecx
	jnz	Vec3uNormalizeBlockLoopF

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uNormalizeBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uNormalizeBlockFlatUseSizeAsm(vec3*         ru,
;;;                                                   const int32_t iSize,
;;;                                                   const int32_t iCount);
;;;

_Vec3uNormalizeBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm4,[zeroVec]

Vec3uNormalizeBlockUseSizeLoopF:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)

	addps	xmm1,xmm2
	addps	xmm1,xmm3

	ucomiss	xmm1,xmm4
	jne	Vec3uNormalizeBlockUseSzExecF

	movups	[AReg],xmm4
	jmp	Vec3uNormalizeBlockUseSzAdjPtrsF

Vec3uNormalizeBlockUseSzExecF:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movups	[AReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec3uNormalizeBlockUseSzAdjPtrsF:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec3uNormalizeBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uBufNormalizeBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufNormalizeBufFlatAsm(void*         r,
;;;                                             const int32_t iRSize,
;;;                                             const void*   u,
;;;                                             const int32_t iUSize,
;;;                                             const int32_t iCount);
;;;

_Vec3uBufNormalizeBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm4,[zeroVec]

Vec3uBufNormalizeBufLoopF:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	addps	xmm1,xmm2
	addps	xmm1,xmm3

	ucomiss	xmm1,xmm4		; 0.0 == sqrt(sum(sqr(u)))
	jne	Vec3uBufNormalizeBufExecF

	movups	[DReg],xmm4
	jmp	Vec3uBufNormalizeAdjPtrsF

Vec3uBufNormalizeBufExecF:

	sqrtss	xmm1,xmm1		; sqrt(sum(sqr(u)))
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movups	[DReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec3uBufNormalizeAdjPtrsF:

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufNormalizeBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; Vec3NormalizeFPU_Asm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Vec3NormalizeFPU_Asm(vec3* r,const vec3* r)
;;;

_Vec3NormalizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *v

	fld	dword [AReg]		; v.x
	fld	st0
	fmulp	st1,st0			; v.x*v.x

	fld	dword [AReg+4]		; v.y
	fld	st0
	fmulp	st1,st0			; v.y*v.y
	faddp	st1,st0			; sqr(v.x)+sqr(v.y)

	fld	dword [AReg+8]		; v.z
	fld	st0
	fmulp	st1,st0			; v.z*v.z
	faddp	st1,st0			; sum(sqr(v))

	fsqrt				; sqrtf(sum(sqr(v)))

	fldz				; 
	fcomip	st0,st1
	je	Vec3NormalizeFPUDB0

	fld	st0
	fld	st0

	fdivr	dword [AReg]		; v.x / sqrtf(sum(sqr(v)))
	fstp	dword [DReg]

	fdivr	dword [AReg+4]		; v.y / sqrtf(sum(sqr(v)))
	fstp	dword [DReg+4]

	fdivr	dword [AReg+8]		; v.z / sqrtf(sum(sqr(v)))
	fstp	dword [DReg+8]

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec3NormalizeFPUDB0:

	ffree	st0

	fldz
	fst	dword [DReg]
	fst	dword [DReg+4]
	fstp	dword [DReg+8]

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3LengthAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec3LengthAsm(float* r,const vec3& v);
;;;

_Vec3LengthAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm1,[zeroVec]
	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v*v

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3LengthBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3LengthBlockAsm(float* r,const vec3* u,const int32_t iCount);
;;; 

_Vec3LengthBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR3]	; iCount

Vec3LengthBlockLoop:

	movaps	xmm1,[zeroVec]
	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr))

	add	AReg,Vec3Size		; *u += iSize
	add	DReg,FloatSize		; *r += iSize

	dec	ecx
	jnz	Vec3LengthBlockLoop

	mov	AReg,[STACK_PTR1]
	mov	CReg,[STACK_PTR2]

	ret

;;;
;;; Vec3LengthBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3LengthBlockUseSize(float*        r,
;;;                                        const vec3*   u,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec3LengthBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec3LengthBlockUseSizeLoop:

	movaps	xmm1,[zeroVec]
	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0

	movss	[DReg],xmm0		; r=sqrt(sum(sqr(u)))

	add	AReg,ebx		; *u += iSize
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec3LengthBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufLengthBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufLengthBufAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const int32_t iCount);
;;;

_Vec3BufLengthBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3BufLengthBufLoop:

	movaps	xmm1,[zeroVec]
	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufLengthBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uLengthAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec3uLengthAsm(float* r,const vec3& v);
;;;

_Vec3uLengthAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm1,[zeroVec]
	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v*v

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uLengthBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3uLengthBlockAsm(float* r,const vec3* u,const int32_t iCount);
;;; 

_Vec3uLengthBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR3]	; iCount

Vec3uLengthBlockLoop:

	movaps	xmm1,[zeroVec]
	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr))

	add	AReg,Vec3Size		; *u += iSize
	add	DReg,FloatSize		; *r += iSize

	dec	ecx
	jnz	Vec3uLengthBlockLoop

	mov	AReg,[STACK_PTR1]
	mov	CReg,[STACK_PTR2]

	ret

;;;
;;; Vec3uLengthBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3uLengthBlockUseSize(float*        r,
;;;                                         const vec3*   u,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec3uLengthBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec3uLengthBlockUseSizeLoop:

	movaps	xmm1,[zeroVec]
	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0

	movss	[DReg],xmm0		; r=sqrt(sum(sqr(u)))

	add	AReg,ebx		; *u += iSize
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec3uLengthBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufLengthBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufLengthBufAsm(void*         r,
;;;                                      const int32_t iRSize,
;;;                                      const void*   u,
;;;                                      const int32_t iUSize,
;;;                                      const int32_t iCount);
;;;

_Vec3uBufLengthBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3uBufLengthBufLoop:

	movaps	xmm1,[zeroVec]
	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufLengthBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3LengthFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec3LengthFlatAsm(float* r,const vec3& v);
;;;

_Vec3LengthFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2		; sum(sqr(v))
	sqrtss	xmm0,xmm0		; sqrtf(sum(sqr(v)))

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3LengthBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3LengthBlockFlatAsm(float* r,const vec3* u,const int32_t iCount);
;;; 

_Vec3LengthBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR3]	; iCount

Vec3LengthBlockLoopF:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr))

	add	AReg,Vec3Size		; *u += iSize
	add	DReg,FloatSize		; *r += iSize

	dec	ecx
	jnz	Vec3LengthBlockLoopF

	mov	AReg,[STACK_PTR1]
	mov	CReg,[STACK_PTR2]

	ret

;;;
;;; Vec3LengthBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3LengthBlockFlatUseSize(float*        r,
;;;                                            const vec3*   u,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec3LengthBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec3LengthBlockUseSizeLoopF:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	addps	xmm0,xmm1
	addps	xmm0,xmm2
	sqrtss	xmm0,xmm0

	movss	[DReg],xmm0		; r=sqrt(sum(sqr(u)))

	add	AReg,ebx		; *u += iSize
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec3LengthBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufLengthBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufLengthBufFlatAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const int32_t iCount);
;;;

_Vec3BufLengthBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3BufLengthBufLoopF:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	addss	xmm0,xmm1
	addss	xmm0,xmm2
	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3BufLengthBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uLengthFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] vec3*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec3uLengthFlatAsm(float* r,const vec3& v);
;;;

_Vec3uLengthFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2		; sum(sqr(v))
	sqrtss	xmm0,xmm0		; sqrtf(sum(sqr(v)))

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec3uLengthBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3uLengthBlockFlatAsm(float* r,const vec3* u,const int32_t iCount);
;;; 

_Vec3uLengthBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR3]	; iCount

Vec3uLengthBlockLoopF:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr))

	add	AReg,Vec3Size		; *u += iSize
	add	DReg,FloatSize		; *r += iSize

	dec	ecx
	jnz	Vec3uLengthBlockLoopF

	mov	AReg,[STACK_PTR1]
	mov	CReg,[STACK_PTR2]

	ret

;;;
;;; Vec3uLengthBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec3*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec3uLengthBlockFlatUseSize(float*        r,
;;;                                             const vec3*   u,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec3uLengthBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec3uLengthBlockUseSizeLoopF:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	addps	xmm0,xmm1
	addps	xmm0,xmm2
	sqrtss	xmm0,xmm0

	movss	[DReg],xmm0		; r=sqrt(sum(sqr(u)))

	add	AReg,ebx		; *u += iSize
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec3uLengthBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufLengthBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufLengthBufFlatAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const int32_t iCount);
;;;

_Vec3uBufLengthBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec3uBufLengthBufLoopF:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	addss	xmm0,xmm1
	addss	xmm0,xmm2
	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufLengthBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; Vec3LengthFPU_Asm
;;;
;;; Call Stack
;;;
;;; [2] vec3*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec3LengthFPU_Asm(float* r,const vec3& v);
;;;

_Vec3LengthFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *v

	fld	dword [AReg]		; v.x
	fld	st0
	fmulp	st1,st0			; v.x*v.x

	fld	dword [AReg+4]		; v.y
	fld	st0
	fmulp	st1,st0			; v.y*v.y
	faddp	st1,st0			; v.x*v.x+v.y*v.y

	fld	dword [AReg+8]		; v.z
	fld	st0
	fmulp	st1,st0			; v.z*v.z
	faddp	st1,st0			; v.x*v.x+v.y*v.y+v.z*v.z

	fsqrt				; sqrtf(sum(sqr(v)))

	fstp	dword [DReg]

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3CrossAsm
;;;
;;; Call Stack
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; vec3 = cross(const vec3& u,const vec3& v)
;;;
;;; return vec3(u.y * v.z - v.y * u.z, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x)
;;;
;;; extern "C" void Vec3CrossAsm(vec3* r,const vec3* u,const vec3* v)
;;; 

_Vec3CrossAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *u
	mov	BReg,[STACK_PTR3]		; *v
	mov	DReg,[STACK_PTR1]		; *r

	movaps	xmm0,[AReg]			; u
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]			; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)	; u_zxy
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)	; u_yzx
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; v_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; v_zxy

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movaps	[DReg],xmm1

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3CrossBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3CrossBlockAsm(vec3* ru,const vec3* v,const int32_iCount)
;;;

_Vec3CrossBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec3CrossBlockLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movaps	[AReg],xmm1

	add	AReg,Vec3Size
	add	BReg,Vec3Size

	dec	ecx
	jnz	Vec3CrossBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3CrossBlockUseSizeAsm
;;;
;;; Call Stack
;;; 
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3CrossBlockUseSizeAsm(void*         ru,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec3CrossBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec3CrossBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movaps	[AReg],xmm1

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3CrossBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3BufCrossBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufCrossBufAsm(void*         r,
;;;                                    const int32_t iRSize,
;;;                                    const void*   u,
;;;                                    const int32_t iUSize,
;;;                                    const void*   v,
;;;                                    const int32_t iVSize,
;;;                                    const int32_t iCount);
;;;

_Vec3BufCrossBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec3BufCrossBufLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movaps	[DReg],xmm1

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3BufCrossBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3uCrossAsm
;;;
;;; Call Stack
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; vec3 = cross(const vec3& u,const vec3& v)
;;;
;;; return vec3(u.y * v.z - v.y * u.z, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x)
;;;
;;; extern "C" void Vec3uCrossAsm(vec3* r,const vec3* u,const vec3* v)
;;; 

_Vec3uCrossAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *u
	mov	BReg,[STACK_PTR3]		; *v
	mov	DReg,[STACK_PTR1]		; *r

	movups	xmm0,[AReg]			; u
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]			; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)	; u_zxy
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)	; u_yzx
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; v_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; v_zxy

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movups	[DReg],xmm1

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uCrossBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec3*   v
;;; [1] vec3*   ru
;;;
;;; extern "C" void Vec3uCrossBlockAsm(vec3* ru,const vec3* v,const int32_iCount)
;;;

_Vec3uCrossBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec3uCrossBlockLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movups	[AReg],xmm1

	add	AReg,Vec3Size
	add	BReg,Vec3Size

	dec	ecx
	jnz	Vec3uCrossBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec3uCrossBlockUseSizeAsm
;;;
;;; Call Stack
;;; 
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec3uCrossBlockUseSizeAsm(void*         ru,
;;;                                           const void*   v,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Vec3uCrossBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec3uCrossBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movups	[AReg],xmm1

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec3uCrossBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec3uBufCrossBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3uBufCrossBufAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const void*   v,
;;;                                     const int32_t iVSize,
;;;                                     const int32_t iCount);
;;;

_Vec3uBufCrossBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec3uBufCrossBufLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movups	[DReg],xmm1

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec3uBufCrossBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec3ReflectAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3ReflectAsm(vec3* r,const vec3* u,const Vec3* v);
;;;
;;; XXX: This needs a little more work

_Vec3ReflectAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,[BReg]		; v

	;; normalize(u)

	movss	xmm6,[zeroVec]

	movaps	xmm2,xmm0
	mulps	xmm2,xmm2
	movaps	xmm3,xmm2
	movaps	xmm4,xmm2
	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)
	addss	xmm2,xmm3
	addss	xmm2,xmm4
	sqrtss	xmm2,xmm2

	ucomiss	xmm2,xmm6
	je	Vec3ReflectNoNorm0

Vec3ReflectCont0:

	shufps	xmm2,xmm2,0
	divps	xmm0,xmm2

Vec3ReflectNoNorm0:

	;; normalize(v)

	movaps	xmm2,xmm1
	mulps	xmm2,xmm2
	movaps	xmm3,xmm2
	movaps	xmm4,xmm2

	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)
	addss	xmm2,xmm3
	addss	xmm2,xmm4
	sqrtss	xmm2,xmm2

	ucomiss	xmm2,xmm6
	je	Vec3ReflectNoNorm1

	shufps	xmm2,xmm2,0
	divps	xmm1,xmm2

Vec3ReflectNoNorm1:

	;; 2*dot(u,v)

	movaps	xmm2,xmm0
	mulps	xmm2,xmm1
	movaps	xmm3,xmm2
	movaps	xmm4,xmm2
	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)
	addss	xmm2,xmm3
	addss	xmm2,xmm4		; dot(u,v)
	mulss	xmm2,[twoVec]		; 2*dot(u,v)
	shufps	xmm2,xmm2,0

	mulps	xmm1,[negVec]		; -v

	mulps	xmm0,xmm2		; u*dot(u,v)
	addps	xmm0,xmm1		; u*dot(u,v) + v

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)
	
;;;
;;; Vec3uReflectAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] vec3* u
;;; [1] vec3* r
;;;
;;; extern "C" void Vec3uReflectAsm(vec3* r,const vec3* u,const Vec3* v);
;;;
;;; XXX: This needs a little more work

_Vec3uReflectAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v

	;; normalize(u)

	movss	xmm6,[zeroVec]

	movaps	xmm2,xmm0
	mulps	xmm2,xmm2
	movaps	xmm3,xmm2
	movaps	xmm4,xmm2
	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)
	addss	xmm2,xmm3
	addss	xmm2,xmm4
	sqrtss	xmm2,xmm2

	ucomiss	xmm2,xmm6
	je	Vec3uReflectNoNorm0

Vec3uReflectCont0:

	shufps	xmm2,xmm2,0
	divps	xmm0,xmm2

Vec3uReflectNoNorm0:

	;; normalize(v)

	movaps	xmm2,xmm1
	mulps	xmm2,xmm2
	movaps	xmm3,xmm2
	movaps	xmm4,xmm2

	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)
	addss	xmm2,xmm3
	addss	xmm2,xmm4
	sqrtss	xmm2,xmm2

	ucomiss	xmm2,xmm6
	je	Vec3uReflectNoNorm1

	shufps	xmm2,xmm2,0
	divps	xmm1,xmm2

Vec3uReflectNoNorm1:

	;; 2*dot(u,v)

	movaps	xmm2,xmm0
	mulps	xmm2,xmm1
	movaps	xmm3,xmm2
	movaps	xmm4,xmm2
	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)
	addss	xmm2,xmm3
	addss	xmm2,xmm4		; dot(u,v)
	mulss	xmm2,[twoVec]		; 2*dot(u,v)
	shufps	xmm2,xmm2,0

	mulps	xmm1,[negVec]		; -v

	mulps	xmm0,xmm2		; u*dot(u,v)
	addps	xmm0,xmm1		; u*dot(u,v) + v

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

;;;
;;; Vec4CopyAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* pSource
;;; [1] vec4* pDest
;;;
;;; extern "C" void Vec4CopyAsm(vec4* pDest,const vec4* pSource);
;;;

_Vec4CopyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *v

	mov	ebx,[AReg]		; v.x
	mov	[DReg],ebx

	mov	ebx,[AReg+4]		; v.y
	mov	[DReg+4],ebx

	mov	ebx,[AReg+8]		; v.z
	mov	[DReg+8],ebx

	mov	ebx,[AReg+12]		; v.w
	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4CopyBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   pSource
;;; [1] vec4*   pDest
;;;
;;; extern "C" void Vec4CopyBlockAsm(vec4* pDest,const vec4* pSource,const int32_t iCount);
;;;

_Vec4CopyBlockAsm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],Srcp
	mov	[STACK_SAVE3],Dstp

	mov	Dstp,[STACK_PTR1]	; *dest
	mov	Srcp,[STACK_PTR2]	; *src
	mov	CReg,0
	mov	ecx, [STACK_PTR3]	; iCount XXX:	shl ecx,2 (ecx*4 for sizeof(vec4)?)
	shl	ecx,2

	cld
	rep	movsd			; Copy

	mov	CReg,[STACK_SAVE1]
	mov	Srcp,[STACK_SAVE2]
	mov	Dstp,[STACK_SAVE3]

	ret

;;;
;;; BuildVec4PackedArrayAsm
;;;
;;; [3] int32_t iCount
;;; [2] vec4**  ppList
;;; [1] vec4*   r
;;;
;;; extern "C" void BuildVec4PackedArrayAsm(vec4* r,const vec4** pSrc,const int32_t iCount);
;;;

_BuildVec4PackedArrayAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; **pSrc
	mov	ecx, [STACK_PTR3]	; iCount

BuildVec4PackedArrayLoop:

	mov	AReg,[BReg]		; *pSrc

	mov	esi,[AReg]		; x
	mov	[DReg],esi

	mov	esi,[AReg+4]		; y
	mov	[DReg+4],esi

	mov	esi,[AReg+8]		; z
	mov	[DReg+8],esi

	mov	esi,[AReg+12]		; w
	mov	[DReg+12],esi

	add	BReg,PtrSize
	add	DReg,Vec4Size

	dec	ecx
	jnz	BuildVec4PackedArrayLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4AddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec4* v
;;; [1] vec4* r
;;;
;;; extern "C" void Vec4AddFloatAsm(vec4* r,const vec4* v,const float s)
;;;

_Vec4AddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	addps	xmm0,[AReg]		; u+s
	movaps	[DReg],xmm0		; r=u+s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4AddFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4AddFloatToBlockAsm(vec4* rv,const float s,const int32_t iCount);
;;;

_Vec4AddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	mov	ecx, [STACK_PTR3]	; iCount

Vec4AddFloatToBlockLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + s
	movaps	[AReg],xmm0

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4AddFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4AddFloatToBlockSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;; 
;;; extern "C" void Vec4AddFloatToBlockBySizeAsm(void*         rv,
;;;                                              const float   s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4AddFloatToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4AddFloatToBlkSzLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movaps	[AReg],xmm0		; r=u+s

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4AddFloatToBlkSzLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufAddFloatToBlockAsm
;;;
;;; Call Stack
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;; 
;;; extern "C" void Vec4BufAddFloatToBlockAsm(void*       r,
;;;                                           const void* u,
;;;                                           const float s,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;; 

_Vec4BufAddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec4BufAddFloatToBlkLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movaps	[DReg],xmm0		; r=u+s

	add	AReg,ebx		; *u += iSize
	add	DReg,ebx		; *v += iSize

	dec	ecx
	jnz	Vec4BufAddFloatToBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufAddFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufAddFloatToBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const float   s,
;;;                                         const int32_t iCount);
;;; 

_Vec4BufAddFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR6]	; iCount

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec4BufAddFloatToBufLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movaps	[DReg],xmm0		; r=u+s

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec4BufAddFloatToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uAddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec4* v
;;; [1] vec4* r
;;;
;;; extern "C" void Vec4uAddFloatAsm(vec4* r,const vec4* v,const float s)
;;;

_Vec4uAddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movups	xmm1,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movups	[DReg],xmm0		; r=u+s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uAddFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4uAddFloatToBlockAsm(vec4* rv,const float s,const int32_t iCount);
;;;

_Vec4uAddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

	mov	ecx, [STACK_PTR3]	; iCount

Vec4uAddFloatToBlockLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + s
	movups	[AReg],xmm0

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4uAddFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uAddFloatToBlockSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;; 
;;; extern "C" void Vec4uAddFloatToBlockBySizeAsm(void*         rv,
;;;                                               const float   s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec4uAddFloatToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4uAddFloatToBlkSzLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movups	[AReg],xmm0		; r=u+s

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4uAddFloatToBlkSzLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufAddFloatToBlockAsm
;;;
;;; Call Stack
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;; 
;;; extern "C" void Vec4uBufAddFloatToBlockAsm(void*       r,
;;;                                            const void* u,
;;;                                            const float s,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;; 

_Vec4uBufAddFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec4uBufAddFloatToBlkLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movups	[DReg],xmm0		; r=u+s

	add	AReg,ebx		; *u += iSize
	add	DReg,ebx		; *v += iSize

	dec	ecx
	jnz	Vec4uBufAddFloatToBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufAddFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufAddFloatToBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const float   s,
;;;                                          const int32_t iCount);
;;; 

_Vec4uBufAddFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR6]	; iCount

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec4uBufAddFloatToBufLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+s
	movups	[DReg],xmm0		; r=u+s

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec4uBufAddFloatToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4SubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4SubtractFloatAsm(vec4* r,const vec4* u,const float s);
;;;

_Vec4SubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	subps	xmm0,xmm1		; u-s
	movaps	[DReg],xmm0		; r=u-s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4SubtractFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4SubtractFloatFromBlockAsm(vec4* rv,const float s,const int32_t iCount);
;;;

_Vec4SubtractFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4SubtractFloatFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u+s
	movaps	[AReg],xmm0		; r=u+s

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4SubtractFloatFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4SubFloatFromBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec4SubFloatFromBlockBySizeAsm(void*       rv,
;;;                                                const float s,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;; 

_Vec4SubFloatFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4SubFloatFromBlockBySizeLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u+s
	movaps	[AReg],xmm0		; r=u+s

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4SubFloatFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufSubFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufSubFloatFromBlockAsm(void*         r,
;;;                                             const void*   u,
;;;                                             const float   s,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec4BufSubFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec4BufSubFloatFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-s
	movaps	[DReg],xmm0		; r=u-s

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *u += iSize

	dec	ecx
	jnz	Vec4BufSubFloatFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufSubFloatFromBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufSubFloatFromBufAsm(void*         r,
;;;                                           const int32_t iRSize,
;;;                                           const void*   u,
;;;                                           const int32_t iUSize,
;;;                                           const float   s,
;;;                                           const int32_t iCount);
;;; 

_Vec4BufSubFloatFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	esi, [STACK_PTR2]	; iRetSize
	mov	edi, [STACK_PTR4]	; iVecSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec4BufSubFloatFromBufLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-s
	movaps	[DReg],xmm0		; r=u-s

	add	AReg,edi		; *u += iVecSize
	add	DReg,esi		; *r += iRetSize

	dec	ecx
	jnz	Vec4BufSubFloatFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uSubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4uSubtractFloatAsm(vec4* r,const vec4* u,const float s);
;;;

_Vec4uSubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	subps	xmm0,xmm1		; u-s
	movups	[DReg],xmm0		; r=u-s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uSubtractFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4uSubtractFloatFromBlockAsm(vec4* rv,const float s,const int32_t iCount);
;;;

_Vec4uSubtractFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4uSubtractFloatFromBlockLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u+s
	movups	[AReg],xmm0		; r=u+s

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4uSubtractFloatFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uSubFloatFromBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec4uSubFloatFromBlockBySizeAsm(void*       rv,
;;;                                                 const float s,
;;;                                                 const int32_t iSize,
;;;                                                 const int32_t iCount);
;;; 

_Vec4uSubFloatFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4uSubFloatFromBlockBySizeLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u+s
	movups	[AReg],xmm0		; r=u+s

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4uSubFloatFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufSubFloatFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufSubFloatFromBlockAsm(void*         r,
;;;                                              const void*   u,
;;;                                              const float   s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4uBufSubFloatFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec4uBufSubFloatFromBlockLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-s
	movups	[DReg],xmm0		; r=u-s

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *u += iSize

	dec	ecx
	jnz	Vec4uBufSubFloatFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufSubFloatFromBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufSubFloatFromBufAsm(void*         r,
;;;                                            const int32_t iRSize,
;;;                                            const void*   u,
;;;                                            const int32_t iUSize,
;;;                                            const float   s,
;;;                                            const int32_t iCount);
;;; 

_Vec4uBufSubFloatFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	esi, [STACK_PTR2]	; iRetSize
	mov	edi, [STACK_PTR4]	; iVecSize
	mov	ecx, [STACK_PTR6]	; iCount
	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec4uBufSubFloatFromBufLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-s
	movups	[DReg],xmm0		; r=u-s

	add	AReg,edi		; *u += iVecSize
	add	DReg,esi		; *r += iRetSize

	dec	ecx
	jnz	Vec4uBufSubFloatFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4MultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; extern "C" void Vec4MultiplyFloatAsm(vec4*  r,const vec4* u,const float s);
;;;

_Vec4MultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	mulps	xmm0,[AReg]
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4MultiplyFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4MultiplyFloatToBlockAsm(vec4*         rv,
;;;                                             const float   s,
;;;                                             const int32_t iCount);
;;;

_Vec4MultiplyFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4MultiplyFloatToBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movaps	[AReg],xmm0		; r=u*s

	add	AReg,Vec4Size		; *rv += iSize

	dec	ecx
	jnz	Vec4MultiplyFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4MulFloatToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec4MulFloatToBlockBySizeAsm(void*         rv,
;;;                                              const float   s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4MulFloatToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4MulFloatToBlockBySizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movaps	[AReg],xmm0		; r=u*s

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4MulFloatToBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufMulFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufMulFloatToBlockAsm(void*  r,
;;;                                           const void* u,
;;;                                           const float s,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Vec4BufMulFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec4BufMulFloatToBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movaps	[DReg],xmm0		; r=u*s

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4BufMulFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufMulFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufMulFloatToBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const float   s,
;;;                                         const int32_t iCount);
;;; 

_Vec4BufMulFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec4BufMulBufToBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movaps	[DReg],xmm0		; r=u*s

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec4BufMulBufToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uMultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; extern "C" void Vec4uMultiplyFloatAsm(vec4*  r,const vec4* u,const float s);
;;;

_Vec4uMultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movups	xmm1,[AReg]
	mulps	xmm0,xmm1
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uMultiplyFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4uMultiplyFloatToBlockAsm(vec4*         rv,
;;;                                              const float   s,
;;;                                              const int32_t iCount);
;;;

_Vec4uMultiplyFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4uMultiplyFloatToBlockLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movups	[AReg],xmm0		; r=u*s

	add	AReg,Vec4Size		; *rv += iSize

	dec	ecx
	jnz	Vec4uMultiplyFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uMulFloatToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec4uMulFloatToBlockBySizeAsm(void*         rv,
;;;                                               const float   s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec4uMulFloatToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	shufps	xmm1,xmm1,0

Vec4uMulFloatToBlockBySizeLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movups	[AReg],xmm0		; r=u*s

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4uMulFloatToBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufMulFloatToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufMulFloatToBlockAsm(void*  r,
;;;                                            const void* u,
;;;                                            const float s,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec4uBufMulFloatToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0

Vec4uBufMulFloatToBlockLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movups	[DReg],xmm0		; r=u*s

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4uBufMulFloatToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufMulFloatToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufMulFloatToBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const float   s,
;;;                                          const int32_t iCount);
;;; 

_Vec4uBufMulFloatToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize

	movss	xmm1,[STACK_PTR5]	; s
	shufps	xmm1,xmm1,0

Vec4uBufMulBufToBufLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*s
	movups	[DReg],xmm0		; r=u*s

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec4uBufMulBufToBufLoop
 
	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4DivideFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; extern "C" void Vec4DivideFloatAsm(vec4* r,const vec4* u,const float s);
;;;

_Vec4DivideFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR3]	; s
	ucomiss	xmm1,[zeroVec]		; s == 0.0f
	je	Vec4DivideFloatByZero

	shufps	xmm1,xmm1,0
	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[DReg],xmm0		; r=u/s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec4DivideFloatByZero:

	mov	BReg,[STACK_SAVE3]

	mov	ebx,[zeroVec]
	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	ebx,[AReg+12]
	mov	[DReg+12],ebx

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	ret

;;;
;;; Vec4DivideBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4DivideBlockByFloatAsm(vec4* rv,const float s,const int32_t iCount);
;;;

_Vec4DivideBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s

	ucomiss	xmm1,[zeroVec]		; 0.0f == s
	je	Vec4DivideBlockByFloatDB0

	shufps	xmm1,xmm1,0

Vec4DivideBlockByFloatLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[AReg],xmm0		; r=u/s

	add	AReg,Vec4Size		; *u += iSize

	dec	ecx
	jnz	Vec4DivideBlockByFloatLoop

Vec4DivideBlockByFloatDB0:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;; 
;;; Vec4DivBlockByFloatBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec4DivBlockByFloatBySizeAsm(void*         rv,
;;;                                              const float   s,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4DivBlockByFloatBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	ucomiss	xmm1,[zeroVec]
	je	Vec4DivBlockByFloatBySzDB0

	shufps	xmm1,xmm1,0

Vec4DivBlockByFloatBySzLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[AReg],xmm0		; r=u/s

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4DivBlockByFloatBySzLoop

Vec4DivBlockByFloatBySzDB0:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufDivBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufDivBlockByFloatAsm(void*         r,
;;;                                           const void*   u,
;;;                                           const float   s,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Vec4BufDivBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm1,[STACK_PTR3]	; s

	ucomiss	xmm1,[zeroVec]		; 0.0f == s
	je	Vec4BufDivBlkByFloatDB0

	shufps	xmm1,xmm1,0

Vec4BufDivBlockByFloatLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[DReg],xmm0		; r=u/s

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4BufDivBlockByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]

	ret

Vec4BufDivBlkByFloatDB0:

	mov	ebx,[zeroVec]

Vec4BufDivBlkByFloatDB0Loop:

	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	[DReg+12],ebx

	add	DReg,edx

	dec	ecx
	jnz	Vec4BufDivBlkByFloatDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufDivBufByFloatAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufDivBufByFloatAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const float   s,
;;;                                         const int32_t iCount);
;;; 

_Vec4BufDivBufByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	ucomiss	xmm1,[zeroVec]
	je	Vec4BufDivBufByFltDB0

	shufps	xmm1,xmm1,0

Vec4BufDivBufByFloatLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movaps	[DReg],xmm0		; r=u/s

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec4BufDivBufByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

Vec4BufDivBufByFltDB0:

	mov	esi,[zeroVec]

Vec4BufDivBufByFltDB0Loop:

	mov	[DReg],esi
	mov	[DReg+4],esi
	mov	[DReg+8],esi
	mov	[DReg+12],esi

	dec	ecx
	jnz	Vec4BufDivBufByFltDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uDivideFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; extern "C" void Vec4uDivideFloatAsm(vec4* r,const vec4* u,const float s);
;;;

_Vec4uDivideFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR3]	; s
	ucomiss	xmm1,[zeroVec]		; s == 0.0f
	je	Vec4uDivideFloatByZero

	shufps	xmm1,xmm1,0
	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[DReg],xmm0		; r=u/s

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec4uDivideFloatByZero:

	mov	BReg,[STACK_SAVE3]

	mov	ebx,[zeroVec]
	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	ebx,[AReg+12]
	mov	[DReg+12],ebx

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	ret

;;;
;;; Vec4uDivideBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] float   s
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4uDivideBlockByFloatAsm(vec4* rv,const float s,const int32_t iCount);
;;;

_Vec4uDivideBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm1,[STACK_PTR2]	; s

	ucomiss	xmm1,[zeroVec]		; 0.0f == s
	je	Vec4uDivideBlockByFloatDB0

	shufps	xmm1,xmm1,0

Vec4uDivideBlockByFloatLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[AReg],xmm0		; r=u/s

	add	AReg,Vec4Size		; *u += iSize

	dec	ecx
	jnz	Vec4uDivideBlockByFloatLoop

Vec4uDivideBlockByFloatDB0:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;; 
;;; Vec4uDivBlockByFloatBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] float   s
;;; [1] void*   rv
;;;
;;; extern "C" void Vec4uDivBlockByFloatBySizeAsm(void*         rv,
;;;                                               const float   s,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec4uDivBlockByFloatBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movss	xmm1,[STACK_PTR2]	; s
	ucomiss	xmm1,[zeroVec]
	je	Vec4uDivBlockByFloatBySzDB0

	shufps	xmm1,xmm1,0

Vec4uDivBlockByFloatBySzLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[AReg],xmm0		; r=u/s

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4uDivBlockByFloatBySzLoop

Vec4uDivBlockByFloatBySzDB0:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufDivBlockByFloatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufDivBlockByFloatAsm(void*         r,
;;;                                            const void*   u,
;;;                                            const float   s,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec4uBufDivBlockByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm1,[STACK_PTR3]	; s

	ucomiss	xmm1,[zeroVec]		; 0.0f == s
	je	Vec4uBufDivBlkByFloatDB0

	shufps	xmm1,xmm1,0

Vec4uBufDivBlockByFloatLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[DReg],xmm0		; r=u/s

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4uBufDivBlockByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]

	ret

Vec4uBufDivBlkByFloatDB0:

	mov	ebx,[zeroVec]

Vec4uBufDivBlkByFloatDB0Loop:

	mov	[DReg],ebx
	mov	[DReg+4],ebx
	mov	[DReg+8],ebx
	mov	[DReg+12],ebx

	add	DReg,edx

	dec	ecx
	jnz	Vec4uBufDivBlkByFloatDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufDivBufByFloatAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] float   s
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufDivBufByFloatAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const float   s,
;;;                                          const int32_t iCount);
;;; 

_Vec4uBufDivBufByFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	edi, [STACK_PTR2]	; iRetSize
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm1,[STACK_PTR5]	; s
	ucomiss	xmm1,[zeroVec]
	je	Vec4uBufDivBufByFltDB0

	shufps	xmm1,xmm1,0

Vec4uBufDivBufByFloatLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/s
	movups	[DReg],xmm0		; r=u/s

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec4uBufDivBufByFloatLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

Vec4uBufDivBufByFltDB0:

	mov	esi,[zeroVec]

Vec4uBufDivBufByFltDB0Loop:

	mov	[DReg],esi
	mov	[DReg+4],esi
	mov	[DReg+8],esi
	mov	[DReg+12],esi

	dec	ecx
	jnz	Vec4uBufDivBufByFltDB0Loop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

;;;
;;; Vec4EqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4*    v
;;; [2] vec4*    u
;;; [1] int32_t* iFlag
;;;
;;; extern "C" void Vec4EqualsAsm(int32_t* iFlag,const vec4* u,const vec4* v);
;;;

_Vec4EqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFlag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movss	xmm0,[BReg]		; u.x
	movss	xmm1,[DReg]		; v.x
	ucomiss	xmm0,xmm1
	je	Vec4EqualsChk2
	jmp	Vec4NotEquals

Vec4EqualsChk2:

	movss	xmm0,[BReg+4]		; u.y
	movss	xmm1,[DReg+4]		; v.y
	ucomiss	xmm0,xmm1
	je	Vec4EqualsChk3
	jmp	Vec4NotEquals

Vec4EqualsChk3:

	movss	xmm0,[BReg+8]		; u.z
	movss	xmm1,[DReg+8]		; v.z
	ucomiss	xmm0,xmm1
	je	Vec4EqualsChk4
	jmp	Vec4NotEquals

Vec4EqualsChk4:

	movss	xmm0,[BReg+12]		; u.w
	movss	xmm1,[DReg+12]		; v.w
	ucomiss	xmm0,xmm1
	jne	Vec4NotEquals

	mov	edx,1
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec4NotEquals:

	mov	edx,0
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4NotEqualsAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4*    v
;;; [2] vec4*    u
;;; [1] int32_t* iFlag
;;;
;;; extern "C" void Vec4NotEqualsAsm(int32_t* iFlag,const vec4* u,const vec4* v);
;;;

_Vec4NotEqualsAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *iFlag
	mov	BReg,[STACK_PTR2]	; *u
	mov	DReg,[STACK_PTR3]	; *v

	movss	xmm0,[BReg]		; u.x
	movss	xmm1,[DReg]		; v.x
	ucomiss	xmm0,xmm1
	jne	Vec4NotEqualsChk2
	jmp	Vec4Equals

Vec4NotEqualsChk2:

	movss	xmm0,[BReg+4]		; u.y
	movss	xmm1,[DReg+4]		; v.y
	ucomiss	xmm0,xmm1
	jne	Vec4NotEqualsChk3
	jmp	Vec4Equals

Vec4NotEqualsChk3:

	movss	xmm0,[BReg+8]		; u.z
	movss	xmm1,[DReg+8]		; v.z
	ucomiss	xmm0,xmm1
	jne	Vec4NotEqualsChk4
	jmp	Vec4Equals

Vec4NotEqualsChk4:

	movss	xmm0,[BReg+12]		; u.w
	movss	xmm1,[DReg+12]		; v.w
	ucomiss	xmm0,xmm1
	je	Vec4Equals

	mov	edx,1
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Vec4Equals:

	mov	edx,0
	mov	[AReg],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4NegateAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4NegateAsm(vec4* r,const vec4* v)
;;;

_Vec4NegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,[negVec]		; (-1.0f) * v
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4NegateBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4NegateBlockAsm(vec4* rv,int32_t iCount);
;;;

_Vec4NegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR2]	;  nCount

	movaps	xmm1,[negVec]

Vec4NegateBlockLoop:

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v
	movaps	[AReg],xmm0

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4NegateBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4NegateBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   u
;;;
;;; extern "C" void Vec4NegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
;;;

_Vec4NegateBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec4NegateBlockBySizeLoop:

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v
	movaps	[AReg],xmm0		; r=-v

	add	AReg,ebx		; *rv += iSize

	dec	ecx
	jnz	Vec4NegateBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufNegateBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufNegateBlockAsm(void*         r,
;;;                                       const void*   u,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;;

_Vec4BufNegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec4BufNegateBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; -u
	movaps	[DReg],xmm0		; r=-u

	add	AReg,ebx		; *v += iSize
	add	DReg,ebx		; *r += iSize

	dec	ecx
	jnz	Vec4BufNegateBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufNegateBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufNegateBufAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const int32_t iCount);
;;; 

_Vec4BufNegateBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRetSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec4BufNegateBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; -u
	movaps	[DReg],xmm0		; r=-u

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec4BufNegateBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uNegateAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4uNegateAsm(vec4* r,const vec4* v)
;;;

_Vec4uNegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	mulps	xmm0,[negVec]		; (-1.0f) * v
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uNegateBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   rv
;;;
;;; extern "C" void Vec4uNegateBlockAsm(vec4* rv,int32_t iCount);
;;;

_Vec4uNegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ecx, [STACK_PTR2]	;  nCount

	movaps	xmm1,[negVec]

Vec4uNegateBlockLoop:

	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v
	movups	[AReg],xmm0

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4uNegateBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uNegateBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   u
;;;
;;; extern "C" void Vec4uNegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
;;;

_Vec4uNegateBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *rv
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec4uNegateBlockBySizeLoop:

	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm1		; -v
	movups	[AReg],xmm0		; r=-v

	add	AReg,ebx		; *rv += iSize

	dec	ecx
	jnz	Vec4uNegateBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufNegateBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufNegateBlockAsm(void*         r,
;;;                                        const void*   u,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec4uBufNegateBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec4uBufNegateBlockLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; -u
	movups	[DReg],xmm0		; r=-u

	add	AReg,ebx		; *v += iSize
	add	DReg,ebx		; *r += iSize

	dec	ecx
	jnz	Vec4uBufNegateBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufNegateBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iVecSize
;;; [3] void*   u
;;; [2] int32_t iRetSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufNegateBufAsm(void*         r,
;;;                                      const int32_t iRSize,
;;;                                      const void*   u,
;;;                                      const int32_t iUSize,
;;;                                      const int32_t iCount);
;;; 

_Vec4uBufNegateBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRetSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iVecSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm1,[negVec]		; -1

Vec4uBufNegateBufLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; -u
	movups	[DReg],xmm0		; r=-u

	add	AReg,esi		; *u += iVecSize
	add	DReg,edi		; *r += iRetSize

	dec	ecx
	jnz	Vec4uBufNegateBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;; 
;;; Vec4AddAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec3AddAsm(vec4* r,const vec4* u,const vec4* v)
;;;

_Vec4AddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u+v
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4AddVecToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;; [0] ret
;;; 
;;; extern "C" void Vec4AddVecToBlockAsm(vec4*         ru,
;;;                                      const vec4*   v,
;;;                                      const int32_t iCount);
;;; 

_Vec4AddVecToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[BReg]		; v

Vec4AddVecToBlockLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movaps	[AReg],xmm0

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4AddVecToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4AddVecToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4AddVecToBlockBySizeAsm(void*         ru,
;;;                                            const void*   v,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec4AddVecToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movaps	xmm1,[BReg]		; v

Vec4AddVecToBlockBySizeLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+v
	movaps	[AReg],xmm0		; r=u+v

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4AddVecToBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufAddVecToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufAddVecToBlockAsm(void*         r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec4BufAddVecToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm1,[BReg]		; v

Vec4BufAddVecToBlockLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movaps	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4BufAddVecToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4BufAddVecToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufAddVecToBufAsm(void* r,
;;;                                       const int32_t iRSize,
;;;                                       const void*   u,
;;;                                       const int32_t iUSize,
;;;                                       const void*   v,
;;;                                       const int32_t iCount
;;; 

_Vec4BufAddVecToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	Dstp,[STACK_PTR1]	; *r
	mov	ebx, [STACK_PTR2]	; iRSize
	mov	Srcp,[STACK_PTR3]	; *u
	mov	edx, [STACK_PTR4]	; iUSize
	mov	AReg,[STACK_PTR5]	; *v
	mov	CReg,[STACK_PTR6]	; iCount

	movaps	xmm1,[AReg]		; v

Vec4BufAddVecToBufLoop:

	movaps	xmm0,[Srcp]		; u
	addps	xmm0,xmm1		; u+v
	movaps	[Dstp],xmm0		; r = u + v

	add	Srcp,edx 		; *u += iUSize
	add	Dstp,ebx  		; *r += iRSize

	dec	CReg
	jnz	Vec4BufAddVecToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec4AddBlockToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v         ; Vec3Array
;;; [1] vec4*   ru        ; Vec3Array
;;;
;;; extern "C" void Vec4AddBlockToBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4AddBlockToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]

Vec4AddBlockToBlockLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u+v
	movaps	[AReg],xmm0		; r=u+v

	add	AReg,Vec4Size		; *ru += iSize
	add	BReg,Vec4Size		; *v  += iSize

	dec	ecx
	jnz	Vec4AddBlockToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4AddBlockToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4AddBlockToBlockBySizeAsm(void* ru,
;;;                                              const void* v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4AddBlockToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec4AddBlkToBlkBySzLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4AddBlkToBlkBySzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufAddBlockToBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufAddBlockToBufAsm(void*         r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec4BufAddBlockToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4BufAddBlockToBufLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u+v
	movaps	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4BufAddBlockToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4BufAddBufToBufAsm
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufAddBufToBufAsm(void*         r,
;;;                                       const int32_t iRSize,
;;;                                       const void*   u,
;;;                                       const int32_t iUSize,
;;;                                       const void*   v,
;;;                                       const int32_t iVSize,
;;;                                       const int32_t iCount);
;;; 

_Vec4BufAddBufToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec4BufAddBufToBufLoop:

	movaps	xmm0,[AReg]		; u
	addps	xmm0,[BReg]		; u+v
	movaps	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4BufAddBufToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;; 
;;; Vec4uAddAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4uAddAsm(vec4* r,const vec4* u,const vec4* v)
;;;

_Vec4uAddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u+v
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uAddVecToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;; [0] ret
;;; 
;;; extern "C" void Vec4uAddVecToBlockAsm(vec4*         ru,
;;;                                       const vec4*   v,
;;;                                       const int32_t iCount);
;;; 

_Vec4uAddVecToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movups	xmm1,[BReg]		; v

Vec4uAddVecToBlockLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movups	[AReg],xmm0

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4uAddVecToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uAddVecToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uAddVecToBlockBySizeAsm(void*         ru,
;;;                                             const void*   v,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec4uAddVecToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movups	xmm1,[BReg]		; v

Vec4uAddVecToBlockBySizeLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u+v
	movups	[AReg],xmm0		; r=u+v

	add	AReg,edx		; *rv += iSize

	dec	ecx
	jnz	Vec4uAddVecToBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufAddVecToBlockAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufAddVecToBlockAsm(void*         r,
;;;                                          const void*   u,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec4uBufAddVecToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movups	xmm1,[BReg]		; v

Vec4uBufAddVecToBlockLoop:

	movups	xmm0,[AReg]		; u
	addps	xmm0,xmm1		; u + v
	movups	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4uBufAddVecToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4uBufAddVecToBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufAddVecToBufAsm(void* r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const void*   v,
;;;                                        const int32_t iCount);
;;; 

_Vec4uBufAddVecToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	Dstp,[STACK_PTR1]	; *r
	mov	ebx, [STACK_PTR2]	; iRSize
	mov	Srcp,[STACK_PTR3]	; *u
	mov	edx, [STACK_PTR4]	; iUSize
	mov	AReg,[STACK_PTR5]	; *v
	mov	CReg,[STACK_PTR6]	; iCount

	movups	xmm1,[AReg]		; v

Vec4uBufAddVecToBufLoop:

	movups	xmm0,[Srcp]		; u
	addps	xmm0,xmm1		; u+v
	movups	[Dstp],xmm0		; r = u + v

	add	Srcp,edx		; *u += iUSize
	add	Dstp,ebx		; *r += iRSize

	dec	CReg
	jnz	Vec4uBufAddVecToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec4uAddBlockToBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v         ; Vec3Array
;;; [1] vec4*   ru        ; Vec3Array
;;;
;;; extern "C" void Vec4uAddBlockToBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4uAddBlockToBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]

Vec4uAddBlockToBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u+v
	movups	[AReg],xmm0		; r=u+v

	add	AReg,Vec4Size		; *ru += iSize
	add	BReg,Vec4Size		; *v  += iSize

	dec	ecx
	jnz	Vec4uAddBlockToBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uAddBlockToBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uAddBlockToBlockBySizeAsm(void* ru,
;;;                                               const void* v,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec4uAddBlockToBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec4uAddBlkToBlkBySzLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4uAddBlkToBlkBySzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufAddBlockToBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufAddBlockToBufAsm(void*         r,
;;;                                          const void*   u,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec4uBufAddBlockToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uBufAddBlockToBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u+v
	movups	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4uBufAddBlockToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4uBufAddBufToBufAsm
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufAddBufToBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const void*   v,
;;;                                        const int32_t iVSize,
;;;                                        const int32_t iCount);
;;; 

_Vec4uBufAddBufToBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec4uBufAddBufToBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	addps	xmm0,xmm1		; u+v
	movups	[DReg],xmm0		; r=u+v

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufAddBufToBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif


%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4SubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; extern "C" void Vec4SubtractAsm(vec4* r,const vec4* u,const vec4* v);
;;;

_Vec4SubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u - v
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4SubVecFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4SubVecFromBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4SubVecFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[BReg]		; v

Vec4SubVecFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-v
	movaps	[AReg],xmm0		; r=u-v

	add	AReg,Vec4Size		; *r += iSize

	dec	ecx
	jnz	Vec4SubVecFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4SubVecFromBlockBySizeAsm
;;; 
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4SubVecFromBlockBySizeAsm(void*         ru,
;;;                                              const void*   v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4SubVecFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movaps	xmm1,[BReg]		; v

Vec4SubVecFromBlockBySizeLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movaps	[AReg],xmm0		; r=u-v

	add	AReg,edx		; *ru += iSize

	dec	ecx
	jnz	Vec4SubVecFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufSubVecFromBlockAsm
;;; 
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufSubVecFromBlockAsm(void*         r,
;;;                                           const void*   u,
;;;                                           const void*   v,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;; 

_Vec4BufSubVecFromBlockAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movaps	xmm1,[BReg]		; v

Vec4BufSubVecFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-v
	movaps	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4BufSubVecFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4BufSubVecFromBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufSubBufFromBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const vec3*   v,
;;;                                         const int32_t iCount);
;;; 

_Vec4BufSubVecFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; iRSize

	movaps	xmm1,[BReg]		; v

Vec4BufSubVecFromBufLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movaps	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += UiSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufSubVecFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec4SubBlockFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4SubBlockFromBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4SubBlockFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec4SubBlockFromBlockLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u-v
	movaps	[AReg],xmm0		; r=u-v

	add	AReg,Vec4Size		; *ru += iSize
	add	BReg,Vec4Size		; *v  += iSize

	dec	ecx
	jnz	Vec4SubBlockFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4SubBlockFromBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4SubBlockFromBlockBySizeAsm(void* ru,
;;;                                                const void* v,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec4SubBlockFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec4SubBlockFromBlockBySizeLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u-v
	movaps	[AReg],xmm0		; r=u-v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4SubBlockFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufSubBlockFromBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufSubBlockFromBufAsm(void*         r,
;;;                                           const void*   u,
;;;                                           const void*   v,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Vec4BufSubBlockFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

Vec4BufSubBlockFromBufLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u-v
	movaps	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4BufSubBlockFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4BufSubBufFromBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufSubBufFromBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const void*   v,
;;;                                         const int32_t iVSize,
;;;                                         const int32_t iCount);
;;;

_Vec4BufSubBufFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ebp, [STACK_PTR2]	; iRSize

Vec4BufSubBufFromBufLoop:

	movaps	xmm0,[AReg]		; u
	subps	xmm0,[BReg]		; u-v

	movaps	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4BufSubBufFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uSubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; extern "C" void Vec4uSubtractAsm(vec4* r,const vec4* u,const vec4* v);
;;;

_Vec4uSubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u - v
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uSubVecFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uSubVecFromBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4uSubVecFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movups	xmm1,[BReg]		; v

Vec4uSubVecFromBlockLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-v
	movups	[AReg],xmm0		; r=u-v

	add	AReg,Vec4Size		; *r += iSize

	dec	ecx
	jnz	Vec4uSubVecFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uSubVecFromBlockBySizeAsm
;;; 
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uSubVecFromBlockBySizeAsm(void*         ru,
;;;                                               const void*   v,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec4uSubVecFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movups	xmm1,[BReg]		; v

Vec4uSubVecFromBlockBySizeLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movups	[AReg],xmm0		; r=u-v

	add	AReg,edx		; *ru += iSize

	dec	ecx
	jnz	Vec4uSubVecFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufSubVecFromBlockAsm
;;; 
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufSubVecFromBlockAsm(void*         r,
;;;                                            const void*   u,
;;;                                            const void*   v,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;; 

_Vec4uBufSubVecFromBlockAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

	movups	xmm1,[BReg]		; v

Vec4uBufSubVecFromBlockLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u-v
	movups	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4uBufSubVecFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4uBufSubVecFromBufAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufSubVecFromBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const vec3*   v,
;;;                                          const int32_t iCount);
;;; 

_Vec4uBufSubVecFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR6]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; iRSize

	movups	xmm1,[BReg]		; v

Vec4uBufSubVecFromBufLoop:

	movups	xmm0,[AReg]		; u
	subps	xmm0,xmm1		; u - v
	movups	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += UiSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufSubVecFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec4uSubBlockFromBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uSubBlockFromBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4uSubBlockFromBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec4uSubBlockFromBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u-v
	movups	[AReg],xmm0		; r=u-v

	add	AReg,Vec4Size		; *ru += iSize
	add	BReg,Vec4Size		; *v  += iSize

	dec	ecx
	jnz	Vec4uSubBlockFromBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uSubBlockFromBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uSubBlockFromBlockBySizeAsm(void* ru,
;;;                                                 const void* v,
;;;                                                 const int32_t iSize,
;;;                                                 const int32_t iCount);
;;;

_Vec4uSubBlockFromBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

Vec4uSubBlockFromBlockBySizeLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u-v
	movups	[AReg],xmm0		; r=u-v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4uSubBlockFromBlockBySizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufSubBlockFromBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufSubBlockFromBufAsm(void*         r,
;;;                                            const void*   u,
;;;                                            const void*   v,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec4uBufSubBlockFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR5]	; iCount
	mov	esi, [STACK_PTR4]	; iSize

Vec4uBufSubBlockFromBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u-v
	movups	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4uBufSubBlockFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4uBufSubBufFromBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufSubBufFromBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const void*   v,
;;;                                          const int32_t iVSize,
;;;                                          const int32_t iCount);
;;;

_Vec4uBufSubBufFromBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	AReg,[STACK_PTR3]	; *u
	mov	BReg,[STACK_PTR5]	; *v
	mov	DReg,[STACK_PTR1]	; *r
	mov	ecx, [STACK_PTR7]	; iCount
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ebp, [STACK_PTR2]	; iRSize

Vec4uBufSubBufFromBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	subps	xmm0,xmm1		; u-v

	movups	[DReg],xmm0		; r=u-v

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufSubBufFromBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4MultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4MultiplyAsm(vec4* r,const vec4* u,const vec4* v);
;;;

_Vec4MultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u * v
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4MulBlockByVecAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4MulBlockByVecAsm(vec4* ru,const vec4* v,const int32_t nCount);
;;;

_Vec4MulBlockByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm1,[BReg]		; v

Vec4MulBlockByVecLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4MulBlockByVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4MulBlockByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4MulBlockByVecUseSizeAsm(void*         ru,
;;;                                             const void*   v,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec4MulBlockByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movaps	xmm1,[BReg]

Vec4MulBlockByVecUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize

	dec	ecx
	jnz	Vec4MulBlockByVecUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufMulBufByVecAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufMulBufByVecAsm(void*         r,
;;;                                       const void*   u,
;;;                                       const void*   v,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;;

_Vec4BufMulBufByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	movaps	xmm1,[BReg]		; v
	mov	ebx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4BufMulBufByVecLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movaps	[DReg],xmm0		; r=u*v

	add	AReg,ebx		; *u += iSize
	add	DReg,ebx		; *r += iSize

	dec	ecx
	jnz	Vec4BufMulBufByVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufMulBufByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufMulBufByVecUseSizeAsm(void*         r,
;;;                                              const int32_t iRSize,
;;;                                              const void*   u,
;;;                                              const int32_t iUSize,
;;;                                              const vec3*   v,
;;;                                              const int32_t iCount);
;;; 

_Vec4BufMulBufByVecUseSizeAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	BReg,[STACK_PTR5]	; *v
	movaps	xmm1,[BReg]		; v

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebx, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR6]	; iCount

Vec4BufMulBufByVecUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movaps	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *r += iUSize
	add	DReg,ebx		; *u += iRSize

	dec	ecx
	jnz	Vec4BufMulBufByVecUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4MulBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4MulBlockByBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4MulBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec4MulBlockByBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,Vec4Size
	add	BReg,Vec4Size

	dec	ecx
	jnz	Vec4MulBlockByBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4MulBlockByBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4MulBlockByBlockUseSizeAsm(void*         ru,
;;;                                               const void*   v,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec4MulBlockByBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec4MulBlockByBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4MulBlockByBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufMulBufByBlockAsm
;;; 
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufMulBufByBlockAsm(void*         r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec4BufMulBufByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4BufMulBufByBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4BufMulBufByBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4BufMulBufByBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufMulBufByBufAsm(void*  r,
;;;                                       const int32_t iRSize,
;;;                                       const void* u,
;;;                                       const int32_t iUSize,
;;;                                       const vec3* v,
;;;                                       const int32_t iVSize,
;;;                                       const int32_t iCount);
;;; 

_Vec4BufMulBufByBufAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr
	
	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; IRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec4BufMulBufByBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *u += iUSize
	add	BReg,ebp		; *v += iVSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufMulBufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uMultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4uMultiplyAsm(vec4* r,const vec4* u,const vec4* v);
;;;

_Vec4uMultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u * v
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uMulBlockByVecAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uMulBlockByVecAsm(vec4* ru,const vec4* v,const int32_t nCount);
;;;

_Vec4uMulBlockByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movups	xmm1,[BReg]		; v

Vec4uMulBlockByVecLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4uMulBlockByVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uMulBlockByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uMulBlockByVecUseSizeAsm(void*         ru,
;;;                                              const void*   v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4uMulBlockByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	mov	edx, [STACK_PTR3]	; iSize

	movups	xmm1,[BReg]

Vec4uMulBlockByVecUseSizeLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize

	dec	ecx
	jnz	Vec4uMulBlockByVecUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufMulBufByVecAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufMulBufByVecAsm(void*         r,
;;;                                        const void*   u,
;;;                                        const void*   v,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec4uBufMulBufByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	movups	xmm1,[BReg]		; v
	mov	ebx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uBufMulBufByVecLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movups	[DReg],xmm0		; r=u*v

	add	AReg,ebx		; *u += iSize
	add	DReg,ebx		; *r += iSize

	dec	ecx
	jnz	Vec4uBufMulBufByVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufMulBufByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufMulBufByVecUseSizeAsm(void*         r,
;;;                                               const int32_t iRSize,
;;;                                               const void*   u,
;;;                                               const int32_t iUSize,
;;;                                               const vec3*   v,
;;;                                               const int32_t iCount);
;;; 

_Vec4uBufMulBufByVecUseSizeAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	BReg,[STACK_PTR5]	; *v
	movups	xmm1,[BReg]		; v

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebx, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR6]	; iCount

Vec4uBufMulBufByVecUseSizeLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm1		; u*v
	movups	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *r += iUSize
	add	DReg,ebx		; *u += iRSize

	dec	ecx
	jnz	Vec4uBufMulBufByVecUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4uMulBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uMulBlockByBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4uMulBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec4uMulBlockByBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,Vec4Size
	add	BReg,Vec4Size

	dec	ecx
	jnz	Vec4uMulBlockByBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uMulBlockByBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uMulBlockByBlockUseSizeAsm(void*         ru,
;;;                                                const void*   v,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec4uMulBlockByBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec4uMulBlockByBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movups	[AReg],xmm0		; r=u*v

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4uMulBlockByBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufMulBufByBlockAsm
;;; 
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufMulBufByBlockAsm(void*         r,
;;;                                          const void*   u,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec4uBufMulBufByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uBufMulBufByBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movups	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4uBufMulBufByBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4uBufMulBufByBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufMulBufByBufAsm(void*  r,
;;;                                        const int32_t iRSize,
;;;                                        const void* u,
;;;                                        const int32_t iUSize,
;;;                                        const vec3* v,
;;;                                        const int32_t iVSize,
;;;                                        const int32_t iCount);
;;; 

_Vec4uBufMulBufByBufAsm:	
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr
	
	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; IRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec4uBufMulBufByBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movups	[DReg],xmm0		; r=u*v

	add	AReg,esi		; *u += iUSize
	add	BReg,ebp		; *v += iVSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufMulBufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4DivideAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4DivideAsm(vec4* r,const vec4* u,const vec4* v);
;;;

_Vec4DivideAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ecx,0
	movss	xmm2,[oneVec]

	movss	xmm1,[zeroVec]
	ucomiss	xmm1,[BReg]		; 0.0f == v.x
	jne	Vec4DivideChkArg1

	or	ecx,1
	movss	[BReg],xmm2

Vec4DivideChkArg1:

	ucomiss	xmm1,[BReg+4]		; 0.0f == v.y
	jne	Vec4DivideChkArg2

	or	ecx,2
	movss	[BReg+4],xmm2

Vec4DivideChkArg2:

	ucomiss	xmm1,[BReg+8]		; 0.0f == v.z
	jne	Vec4DivideChkArg3

	or	ecx,4
	movss	[BReg+8],xmm2

Vec4DivideChkArg3:

	ucomiss	xmm1,[BReg+12]
	jne	Vec4DivideExec

	or	ecx,8
	movss	[BReg+12],xmm2

Vec4DivideExec:

	movaps	xmm0,[AReg]
	divps	xmm0,[BReg]
	movaps	[DReg],xmm0

	cmp	ecx,0
	je	Vec4DivideEnd

	test	ecx,1
	jz	Vec4DivideAdjArg1

	movss	[BReg],xmm1
	movss	[DReg],xmm1

Vec4DivideAdjArg1:

	test	ecx,2
	jz	Vec4DivideAdjArg2

	movss	[BReg+4],xmm1
	movss	[DReg+4],xmm1

Vec4DivideAdjArg2:

	test	ecx,4
	jz	Vec4DivideAdjArg3

	movss	[BReg+8],xmm1
	movss	[DReg+8],xmm1

Vec4DivideAdjArg3:

	test	ecx,8
	jz	Vec4DivideEnd

	movss	[BReg+12],xmm1
	movss	[DReg+12],xmm1

Vec4DivideEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Vec4DivBlockByVecAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4DivBlockByVecAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4DivBlockByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount
	mov	edx, 0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0
	jne	Vec4DivBlockByVecChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec4DivBlockByVecChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4DivBlockByVecChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec4DivBlockByVecChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4DivBlockByVecChkArg3

	or	edx,4
	movss	[BReg+8],xmm3

Vec4DivBlockByVecChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4DivBlockByVecExec

	or	edx,8
	movss	[BReg+12],xmm3

Vec4DivBlockByVecExec:

	movaps	xmm1,[BReg]

Vec4DivBlockByVecLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movaps	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec4DivBlockByVecAdjPtrs

	test	edx,1			; v.x == 0.0
	jz	Vec4DivBlockByVecAdjArg1

	movss	[AReg],xmm2

Vec4DivBlockByVecAdjArg1:

	test	edx,2
	jz	Vec4DivBlockByVecAdjArg2

	movss	[AReg+4],xmm2

Vec4DivBlockByVecAdjArg2:

	test	edx,4
	jz	Vec4DivBlockByVecAdjArg3

	movss	[AReg+8],xmm2

Vec4DivBlockByVecAdjArg3:

	test	edx,8
	jz	Vec4DivBlockByVecAdjPtrs

	movss	[AReg+12],xmm2

Vec4DivBlockByVecAdjPtrs:

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4DivBlockByVecLoop

	cmp	edx,0
	je	Vec4DivBlockByVecEnd

	test	edx,1
	jz	Vec4DivBlockByVecAdjV1

	movss	[BReg],xmm2

Vec4DivBlockByVecAdjV1:

	test	edx,2
	jz	Vec4DivBlockByVecAdjV2

	movss	[BReg+4],xmm2

Vec4DivBlockByVecAdjV2:

	test	edx,4
	jz	Vec4DivBlockByVecAdjV3

	movss	[BReg+8],xmm2

Vec4DivBlockByVecAdjV3:

	test	edx,8
	jz	Vec4DivBlockByVecEnd

	movss	[BReg+12],xmm2

Vec4DivBlockByVecEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Vec4DivBlockByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] vec3*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4DivBlockByVecUseSizeAsm(void* ru,
;;;                                             const vec3* v,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec4DivBlockByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec4DivBlkByVecSzChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec4DivBlkByVecSzChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4DivBlkByVecSzChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec4DivBlkByVecSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4DivBlkByVecSzChkArg3

	or	edx,4
	movss	[BReg+8],xmm3

Vec4DivBlkByVecSzChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4DivBlkByVecSzExec

	or	edx,8
	movss	[BReg+12],xmm3

Vec4DivBlkByVecSzExec:

	movaps	xmm1,[BReg]

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR4]	; iCount
	mov	ebx, [STACK_PTR3]	; iSize

Vec4DivBlkByVecSzLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movaps	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec4DivBlkByVecSzAdjPtrs

	test	edx,1
	jz	Vec4DivBlkByVecSzAdjArg1

	movss	[AReg],xmm2

Vec4DivBlkByVecSzAdjArg1:

	test	edx,2
	jz	Vec4DivBlkByVecSzAdjArg2

	movss	[AReg+4],xmm2

Vec4DivBlkByVecSzAdjArg2:

	test	edx,4
	jz	Vec4DivBlkByVecSzAdjArg3

	movss	[AReg+8],xmm2

Vec4DivBlkByVecSzAdjArg3:

	test	edx,8
	jz	Vec4DivBlkByVecSzAdjPtrs

	movss	[AReg+12],xmm2

Vec4DivBlkByVecSzAdjPtrs:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4DivBlkByVecSzLoop

	cmp	edx,0
	je	Vec4DivBlkByVecSzEnd

	mov	BReg,[STACK_PTR2]	; *v

	test	edx,1
	jz	Vec4DivBlkByVecSzAdjVec1

	movss	[BReg],xmm2

Vec4DivBlkByVecSzAdjVec1:

	test	edx,2
	jz	Vec4DivBlkByVecSzAdjVec2

	movss	[BReg+4],xmm2

Vec4DivBlkByVecSzAdjVec2:

	test	edx,4
	jz	Vec4DivBlkByVecSzAdjVec3

	movss	[BReg+8],xmm2

Vec4DivBlkByVecSzAdjVec3:

	test	edx,8
	jz	Vec4DivBlkByVecSzEnd

	movss	[BReg+12],xmm2

Vec4DivBlkByVecSzEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufDivBufByVecAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec3*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufDivBufByVecAsm(void*	        r,
;;;                                       const void*   u,
;;;                                       const vec4*   v,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;;

_Vec4BufDivBufByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	BReg,[STACK_PTR3]	; *v
	mov	edi,0
	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec4BufDivBufByVecChkArg1

	or	edi,1
	movss	[BReg],xmm3

Vec4BufDivBufByVecChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec4BufDivBufByVecChkArg2

	or	edi,2
	movss	[BReg+4],xmm3

Vec4BufDivBufByVecChkArg2:

	ucomiss	xmm2,[BReg+8]		; v.z == 0.0f
	jne	Vec4BufDivBufByVecChkArg3

	or	edi,4
	movss	[BReg+8],xmm3

Vec4BufDivBufByVecChkArg3:

	ucomiss	xmm2,[BReg+12]		; v.w == 0.0f
	jne	Vec4BufDivBufByVecExec

	or	edi,8
	movss	[BReg+12],xmm3

Vec4BufDivBufByVecExec:

	movaps	xmm1,[BReg]		; v

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4BufDivBufByVecLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movaps	[DReg],xmm0		; r=u/v

	cmp	edi,0
	je	Vec4BufDivBufByVecAdjPtrs

	test	edi,1
	jz	Vec4BufDivBufByVecAdjArg1

	movss	[DReg],xmm2

Vec4BufDivBufByVecAdjArg1:

	test	edi,2
	jz	Vec4BufDivBufByVecAdjArg2

	movss	[DReg+4],xmm2

Vec4BufDivBufByVecAdjArg2:

	test	edi,4
	jz	Vec4BufDivBufByVecAdjArg3

	movss	[DReg+8],xmm2

Vec4BufDivBufByVecAdjArg3:

	test	edi,8
	jz	Vec4BufDivBufByVecAdjPtrs

	movss	[DReg+12],xmm2

Vec4BufDivBufByVecAdjPtrs:

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *v += iSize

	dec	ecx
	jnz	Vec4BufDivBufByVecLoop

	cmp	edi,0
	je	Vec4BufDivBufByVecEnd

	test	edi,1
	jz	Vec4BufDivBufByVecAdjV1

	movss	[BReg],xmm2

Vec4BufDivBufByVecAdjV1:

	test	edi,2
	jz	Vec4BufDivBufByVecAdjV2

	movss	[BReg+4],xmm2

Vec4BufDivBufByVecAdjV2:

	test	edi,4
	jz	Vec4BufDivBufByVecAdjV3

	movss	[BReg+8],xmm2

Vec4BufDivBufByVecAdjV3:

	test	edi,8
	jz	Vec4BufDivBufByVecEnd

	movss	[BReg+12],xmm2

Vec4BufDivBufByVecEnd:

	mov	AReg,[STACK_PTR1]
	mov	BReg,[STACK_PTR2]
	mov	CReg,[STACK_PTR3]
	mov	DReg,[STACK_PTR4]
	mov	Srcp,[STACK_PTR5]
	mov	Dstp,[STACK_PTR6]

	ret

;;;
;;; Vec4BufDivBufByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufDivBufByVecUseSizeAsm(void*         r,
;;;                                              const int32_t iRSize,
;;;                                              const void*   u,
;;;                                              const int32_t iUSize,
;;;                                              const vec3*   v,
;;;                                              const int32_t iCount);
;;;

_Vec4BufDivBufByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, 0
	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]
	jne	Vec4BufDivByVecSzChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec4BufDivByVecSzChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4BufDivByVecSzChkArg2

	or	ebp,2
	movss	[BReg+4],xmm3

Vec4BufDivByVecSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4BufDivByVecSzChkArg3

	or	ebp,4
	movss	[BReg+8],xmm3

Vec4BufDivByVecSzChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4BufDivByVecSzExec

	or	ebp,8
	movss	[BReg+12],xmm3

Vec4BufDivByVecSzExec:

	movaps	xmm1,[BReg]		; v

	mov	AReg,[STACK_PTR3]	; *u
	mov	ecx, [STACK_PTR6]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; iRSize

Vec4BufDivByVecSzLoop:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movaps	[DReg],xmm0		; r=u/v

	cmp	ebp,0
	je	Vec4BufDivByVecSzAdjPtrs

	test	ebp,1
	jz	Vec4BufDivByVecSzAdjArg1

	movss	[DReg],xmm2

Vec4BufDivByVecSzAdjArg1:

	test	ebp,2
	jz	Vec4BufDivByVecSzAdjArg2

	movss	[DReg+4],xmm2

Vec4BufDivByVecSzAdjArg2:

	test	ebp,4
	jz	Vec4BufDivByVecSzAdjArg3

	movss	[DReg+8],xmm2

Vec4BufDivByVecSzAdjArg3:

	test	ebp,8
	jz	Vec4BufDivByVecSzAdjPtrs

	movss	[DReg+12],xmm2
	

Vec4BufDivByVecSzAdjPtrs:

	add	AReg,esi		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufDivByVecSzLoop

	cmp	ebp,0
	je	Vec4BufDivByVecSzEnd

	test	ebp,1
	jz	Vec4BufDivByVecSzAdjV1

	movss	[BReg],xmm2

Vec4BufDivByVecSzAdjV1:

	test	ebp,2
	jz	Vec4BufDivByVecSzAdjV2

	movss	[BReg+4],xmm2

Vec4BufDivByVecSzAdjV2:

	test	ebp,4
	jz	Vec4BufDivByVecSzAdjV3

	movss	[BReg+8],xmm2

Vec4BufDivByVecSzAdjV3:

	test	ebp,8
	jz	Vec4BufDivByVecSzEnd

	movss	[BReg+12],xmm2

Vec4BufDivByVecSzEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec4DivBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4DivBlockByBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4DivBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec4DivBlkByBlkLoop:

	mov	edx, 0			; iFlags

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec4DivBlkByBlkChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec4DivBlkByBlkChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec4DivBlkByBlkChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec4DivBlkByBlkChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4DivBlkByBlkChkArg3

	or	edx,4
	movss	[BReg+8],xmm3

Vec4DivBlkByBlkChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4DivBlkByBlkExec

	or	edx,8
	movss	[BReg+12],xmm3

Vec4DivBlkByBlkExec:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,[BReg]		; u/v
	movaps	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec4DivBlkByBlkAdjPtrs

	test	edx,1
	jz	Vec4DivBlkByBlkAdjArg1

	movss	[AReg],xmm2
	movss	[BReg],xmm2

Vec4DivBlkByBlkAdjArg1:

	test	edx,2
	jz	Vec4DivBlkByBlkAdjArg2

	movss	[AReg+4],xmm2
	movss	[BReg+4],xmm2

Vec4DivBlkByBlkAdjArg2:

	test	edx,4
	jz	Vec4DivBlkByBlkAdjArg3

	movss	[AReg+8],xmm2
	movss	[BReg+8],xmm2

Vec4DivBlkByBlkAdjArg3:

	test	edx,8
	jz	Vec4DivBlkByBlkAdjPtrs

	movss	[AReg+12],xmm2
	movss	[BReg+12],xmm2

Vec4DivBlkByBlkAdjPtrs:

	add	AReg,Vec4Size		; *u += iSize
	add	BReg,Vec4Size		; *v += iSize
	add	DReg,Vec4Size		; *r += iSize

	dec	ecx
	jnz	Vec4DivBlkByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4DivBlockByBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4DivBlockByBlockUseSizeAsm(void*         ru,
;;;                                               const void*   v,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec4DivBlockByBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	esi, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec4DivBlkByBlkUseSizeLoop:

	mov	edx,0

	ucomiss	xmm2,[BReg]		; v.x == 0 ?
	jne	Vec4BufDivBlkByBlkSzChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec4BufDivBlkByBlkSzChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec4BufDivBlkByBlkSzChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec4BufDivBlkByBlkSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4BufDivBlkByBlkSzChkArg3

	or	edx,4
	movss	[BReg+8],xmm3

Vec4BufDivBlkByBlkSzChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4BufDivBlkByBlkSzExec

	or	edx,8
	movss	[BReg+12],xmm3

Vec4BufDivBlkByBlkSzExec:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,[BReg]		; u/v
	movaps	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec4BufDivBlkByBlkSzAdjPtrs

	test	edx,1
	jz	Vec4BufDivBlkByBlkSzAdjV1

	movss	[AReg],xmm2
	movss	[BReg],xmm2

Vec4BufDivBlkByBlkSzAdjV1:

	test	edx,2
	jz	Vec4BufDivBlkByBlkSzAdjV2

	movss	[AReg+4],xmm2
	movss	[BReg+4],xmm2

Vec4BufDivBlkByBlkSzAdjV2:

	test	edx,4
	jz	Vec4BufDivBlkByBlkSzAdjV3

	movss	[AReg+8],xmm2
	movss	[BReg+8],xmm2

Vec4BufDivBlkByBlkSzAdjV3:

	test	edx,8
	jz	Vec4BufDivBlkByBlkSzAdjPtrs

	movss	[AReg+12],xmm2
	movss	[BReg+12],xmm2

Vec4BufDivBlkByBlkSzAdjPtrs:

	add	AReg,esi		; *ru += iSize
	add	BReg,esi		; *v  += iSize

	dec	ecx
	jnz	Vec4DivBlkByBlkUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;; 
;;; Vec4BufDivBufByBlkAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufDivBufByBlockAsm(void*         r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec4BufDivBufByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec4BufDivBufByBlkLoop:

	mov	edi,0

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec4BufDivBufByBlkChkArg1

	or	edi,1
	movss	[BReg],xmm3

Vec4BufDivBufByBlkChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4BufDivBufByBlkChkArg2

	or	edi,2
	movss	[BReg+4],xmm3

Vec4BufDivBufByBlkChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4BufDivBufByBlkChkArg3

	or	edi,4
	movss	[BReg+8],xmm3

Vec4BufDivBufByBlkChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4BufDivBufByBlkExec

	or	edi,8
	movss	[BReg+12],xmm3

Vec4BufDivBufByBlkExec:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,[BReg]		; u/v
	movaps	[DReg],xmm0		; r=u/v

	cmp	edi,0
	je	Vec4BufDivBufByBlkAdjPtrs

	test	edi,1
	jz	Vec4BufDivBufByBlkAdjV1

	movss	[BReg],xmm2
	movss	[DReg],xmm2

Vec4BufDivBufByBlkAdjV1:

	test	edi,2
	jz	Vec4BufDivBufByBlkAdjV2

	movss	[BReg+4],xmm2
	movss	[DReg+4],xmm2

Vec4BufDivBufByBlkAdjV2:

	test	edi,4
	jz	Vec4BufDivBufByBlkAdjV3

	movss	[BReg+8],xmm2
	movss	[DReg+8],xmm2

Vec4BufDivBufByBlkAdjV3:

	test	edi,8
	jz	Vec4BufDivBufByBlkAdjPtrs

	movss	[BReg+12],xmm2
	movss	[DReg+12],xmm2

Vec4BufDivBufByBlkAdjPtrs:

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4BufDivBufByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec4BufDivBufByBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufDivBufByBufAsm(void*         r,
;;;                                       const int32_t iRSize,
;;;                                       const void*   u,
;;;                                       const int32_t iUSize,
;;;                                       const void*   v,
;;;                                       const int32_t iVSize,
;;;                                       const int32_t iCount);
;;; 

_Vec4BufDivBufByBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	edi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ecx, [STACK_PTR7]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec4BufDivBufByBufLoop:

	mov	ebp,0			; iFlags

	ucomiss	xmm2,[BReg]		; v.z == 0.0f
	jne	Vec4BufDivBufByBufChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec4BufDivBufByBufChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4BufDivBufByBufChkArg2

	or	ebp,2
	movss	[BReg+4],xmm3

Vec4BufDivBufByBufChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4BufDivBufByBufChkArg3

	or	ebp,4
	movss	[BReg+8],xmm3

Vec4BufDivBufByBufChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4BufDivBufByBufExec

	or	ebp,8
	movss	[BReg+12],xmm3

Vec4BufDivBufByBufExec:

	movaps	xmm0,[AReg]		; u
	divps	xmm0,[BReg]		; u/v
	movaps	[DReg],xmm0		; r=u/v

	cmp	ebp,0
	je	Vec4BufDivBufByBufAdjPtrs

	test	ebp,1
	jz	Vec4BufDivBufByBufAdjV1

	movss	[BReg],xmm2
	movss	[DReg],xmm2

Vec4BufDivBufByBufAdjV1:

	test	ebp,2
	jz	Vec4BufDivBufByBufAdjV2

	movss	[BReg+4],xmm2
	movss	[DReg+4],xmm2

Vec4BufDivBufByBufAdjV2:

	test	ebp,4
	jz	Vec4BufDivBufByBufAdjV3

	movss	[BReg+8],xmm2
	movss	[DReg+8],xmm2

Vec4BufDivBufByBufAdjV3:

	test	ebp,8
	jz	Vec4BufDivBufByBufAdjPtrs

	movss	[BReg+12],xmm2
	movss	[DReg+12],xmm2

Vec4BufDivBufByBufAdjPtrs:

	add	AReg,edi
	add	BReg,[STACK_PTR6]
	add	DReg,esi

	dec	ecx
	jnz	Vec4BufDivBufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uDivideAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4uDivideAsm(vec4* r,const vec4* u,const vec4* v);
;;;

_Vec4uDivideAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ecx,0
	movss	xmm2,[oneVec]

	movss	xmm1,[zeroVec]
	ucomiss	xmm1,[BReg]		; 0.0f == v.x
	jne	Vec4uDivideChkArg1

	or	ecx,1
	movss	[BReg],xmm2

Vec4uDivideChkArg1:

	ucomiss	xmm1,[BReg+4]		; 0.0f == v.y
	jne	Vec4uDivideChkArg2

	or	ecx,2
	movss	[BReg+4],xmm2

Vec4uDivideChkArg2:

	ucomiss	xmm1,[BReg+8]		; 0.0f == v.z
	jne	Vec4uDivideChkArg3

	or	ecx,4
	movss	[BReg+8],xmm2

Vec4uDivideChkArg3:

	ucomiss	xmm1,[BReg+12]
	jne	Vec4uDivideExec

	or	ecx,8
	movss	[BReg+12],xmm2

Vec4uDivideExec:

	movups	xmm0,[AReg]
	movups	xmm1,[BReg]
	divps	xmm0,xmm1
	movups	[DReg],xmm0

	cmp	ecx,0
	je	Vec4uDivideEnd

	test	ecx,1
	jz	Vec4uDivideAdjArg1

	movss	[BReg],xmm1
	movss	[DReg],xmm1

Vec4uDivideAdjArg1:

	test	ecx,2
	jz	Vec4uDivideAdjArg2

	movss	[BReg+4],xmm1
	movss	[DReg+4],xmm1

Vec4uDivideAdjArg2:

	test	ecx,4
	jz	Vec4uDivideAdjArg3

	movss	[BReg+8],xmm1
	movss	[DReg+8],xmm1

Vec4uDivideAdjArg3:

	test	ecx,8
	jz	Vec4uDivideEnd

	movss	[BReg+12],xmm1
	movss	[DReg+12],xmm1

Vec4uDivideEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Vec4uDivBlockByVecAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uDivBlockByVecAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4uDivBlockByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount
	mov	edx, 0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0
	jne	Vec4uDivBlockByVecChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec4uDivBlockByVecChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4uDivBlockByVecChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec4uDivBlockByVecChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4uDivBlockByVecChkArg3

	or	edx,4
	movss	[BReg+8],xmm3

Vec4uDivBlockByVecChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4uDivBlockByVecExec

	or	edx,8
	movss	[BReg+12],xmm3

Vec4uDivBlockByVecExec:

	movups	xmm1,[BReg]

Vec4uDivBlockByVecLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movups	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec4uDivBlockByVecAdjPtrs

	test	edx,1			; v.x == 0.0
	jz	Vec4uDivBlockByVecAdjArg1

	movss	[AReg],xmm2

Vec4uDivBlockByVecAdjArg1:

	test	edx,2
	jz	Vec4uDivBlockByVecAdjArg2

	movss	[AReg+4],xmm2

Vec4uDivBlockByVecAdjArg2:

	test	edx,4
	jz	Vec4uDivBlockByVecAdjArg3

	movss	[AReg+8],xmm2

Vec4uDivBlockByVecAdjArg3:

	test	edx,8
	jz	Vec4uDivBlockByVecAdjPtrs

	movss	[AReg+12],xmm2

Vec4uDivBlockByVecAdjPtrs:

	add	AReg,Vec4Size

	dec	ecx
	jnz	Vec4uDivBlockByVecLoop

	cmp	edx,0
	je	Vec4uDivBlockByVecEnd

	test	edx,1
	jz	Vec4uDivBlockByVecAdjV1

	movss	[BReg],xmm2

Vec4uDivBlockByVecAdjV1:

	test	edx,2
	jz	Vec4uDivBlockByVecAdjV2

	movss	[BReg+4],xmm2

Vec4uDivBlockByVecAdjV2:

	test	edx,4
	jz	Vec4uDivBlockByVecAdjV3

	movss	[BReg+8],xmm2

Vec4uDivBlockByVecAdjV3:

	test	edx,8
	jz	Vec4uDivBlockByVecEnd

	movss	[BReg+12],xmm2

Vec4uDivBlockByVecEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Vec4uDivBlockByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] vec3*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uDivBlockByVecUseSizeAsm(void* ru,
;;;                                              const vec3* v,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4uDivBlockByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	BReg,[STACK_PTR2]	; *v
	mov	DReg,0

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec4uDivBlkByVecSzChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec4uDivBlkByVecSzChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4uDivBlkByVecSzChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec4uDivBlkByVecSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4uDivBlkByVecSzChkArg3

	or	edx,4
	movss	[BReg+8],xmm3

Vec4uDivBlkByVecSzChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4uDivBlkByVecSzExec

	or	edx,8
	movss	[BReg+12],xmm3

Vec4uDivBlkByVecSzExec:

	movups	xmm1,[BReg]

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR4]	; iCount
	mov	ebx, [STACK_PTR3]	; iSize

Vec4uDivBlkByVecSzLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movups	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec4uDivBlkByVecSzAdjPtrs

	test	edx,1
	jz	Vec4uDivBlkByVecSzAdjArg1

	movss	[AReg],xmm2

Vec4uDivBlkByVecSzAdjArg1:

	test	edx,2
	jz	Vec4uDivBlkByVecSzAdjArg2

	movss	[AReg+4],xmm2

Vec4uDivBlkByVecSzAdjArg2:

	test	edx,4
	jz	Vec4uDivBlkByVecSzAdjArg3

	movss	[AReg+8],xmm2

Vec4uDivBlkByVecSzAdjArg3:

	test	edx,8
	jz	Vec4uDivBlkByVecSzAdjPtrs

	movss	[AReg+12],xmm2

Vec4uDivBlkByVecSzAdjPtrs:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4uDivBlkByVecSzLoop

	cmp	edx,0
	je	Vec4uDivBlkByVecSzEnd

	mov	BReg,[STACK_PTR2]	; *v

	test	edx,1
	jz	Vec4uDivBlkByVecSzAdjVec1

	movss	[BReg],xmm2

Vec4uDivBlkByVecSzAdjVec1:

	test	edx,2
	jz	Vec4uDivBlkByVecSzAdjVec2

	movss	[BReg+4],xmm2

Vec4uDivBlkByVecSzAdjVec2:

	test	edx,4
	jz	Vec4uDivBlkByVecSzAdjVec3

	movss	[BReg+8],xmm2

Vec4uDivBlkByVecSzAdjVec3:

	test	edx,8
	jz	Vec4uDivBlkByVecSzEnd

	movss	[BReg+12],xmm2

Vec4uDivBlkByVecSzEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufDivBufByVecAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] vec3*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufDivBufByVecAsm(void*         r,
;;;                                        const void*   u,
;;;                                        const vec4*   v,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec4uBufDivBufByVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	BReg,[STACK_PTR3]	; *v
	mov	edi,0
	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec4uBufDivBufByVecChkArg1

	or	edi,1
	movss	[BReg],xmm3

Vec4uBufDivBufByVecChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec4uBufDivBufByVecChkArg2

	or	edi,2
	movss	[BReg+4],xmm3

Vec4uBufDivBufByVecChkArg2:

	ucomiss	xmm2,[BReg+8]		; v.z == 0.0f
	jne	Vec4uBufDivBufByVecChkArg3

	or	edi,4
	movss	[BReg+8],xmm3

Vec4uBufDivBufByVecChkArg3:

	ucomiss	xmm2,[BReg+12]		; v.w == 0.0f
	jne	Vec4uBufDivBufByVecExec

	or	edi,8
	movss	[BReg+12],xmm3

Vec4uBufDivBufByVecExec:

	movups	xmm1,[BReg]		; v

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uBufDivBufByVecLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movups	[DReg],xmm0		; r=u/v

	cmp	edi,0
	je	Vec4uBufDivBufByVecAdjPtrs

	test	edi,1
	jz	Vec4uBufDivBufByVecAdjArg1

	movss	[DReg],xmm2

Vec4uBufDivBufByVecAdjArg1:

	test	edi,2
	jz	Vec4uBufDivBufByVecAdjArg2

	movss	[DReg+4],xmm2

Vec4uBufDivBufByVecAdjArg2:

	test	edi,4
	jz	Vec4uBufDivBufByVecAdjArg3

	movss	[DReg+8],xmm2

Vec4uBufDivBufByVecAdjArg3:

	test	edi,8
	jz	Vec4uBufDivBufByVecAdjPtrs

	movss	[DReg+12],xmm2

Vec4uBufDivBufByVecAdjPtrs:

	add	AReg,esi		; *u += iSize
	add	DReg,esi		; *v += iSize

	dec	ecx
	jnz	Vec4uBufDivBufByVecLoop

	cmp	edi,0
	je	Vec4uBufDivBufByVecEnd

	test	edi,1
	jz	Vec4uBufDivBufByVecAdjV1

	movss	[BReg],xmm2

Vec4uBufDivBufByVecAdjV1:

	test	edi,2
	jz	Vec4uBufDivBufByVecAdjV2

	movss	[BReg+4],xmm2

Vec4uBufDivBufByVecAdjV2:

	test	edi,4
	jz	Vec4uBufDivBufByVecAdjV3

	movss	[BReg+8],xmm2

Vec4uBufDivBufByVecAdjV3:

	test	edi,8
	jz	Vec4uBufDivBufByVecEnd

	movss	[BReg+12],xmm2

Vec4uBufDivBufByVecEnd:

	mov	AReg,[STACK_PTR1]
	mov	BReg,[STACK_PTR2]
	mov	CReg,[STACK_PTR3]
	mov	DReg,[STACK_PTR4]
	mov	Srcp,[STACK_PTR5]
	mov	Dstp,[STACK_PTR6]

	ret

;;;
;;; Vec4uBufDivBufByVecUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [6] int32_t iCount
;;; [5] vec3*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufDivBufByVecUseSizeAsm(void*         r,
;;;                                               const int32_t iRSize,
;;;                                               const void*   u,
;;;                                               const int32_t iUSize,
;;;                                               const vec3*   v,
;;;                                               const int32_t iCount);
;;;

_Vec4uBufDivBufByVecUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, 0
	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

	ucomiss	xmm2,[BReg]
	jne	Vec4uBufDivByVecSzChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec4uBufDivByVecSzChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4uBufDivByVecSzChkArg2

	or	ebp,2
	movss	[BReg+4],xmm3

Vec4uBufDivByVecSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4uBufDivByVecSzChkArg3

	or	ebp,4
	movss	[BReg+8],xmm3

Vec4uBufDivByVecSzChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4uBufDivByVecSzExec

	or	ebp,8
	movss	[BReg+12],xmm3

Vec4uBufDivByVecSzExec:

	movups	xmm1,[BReg]		; v

	mov	AReg,[STACK_PTR3]	; *u
	mov	ecx, [STACK_PTR6]	; iCount
	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR4]	; iUSize
	mov	edi, [STACK_PTR2]	; iRSize

Vec4uBufDivByVecSzLoop:

	movups	xmm0,[AReg]		; u
	divps	xmm0,xmm1		; u/v
	movups	[DReg],xmm0		; r=u/v

	cmp	ebp,0
	je	Vec4uBufDivByVecSzAdjPtrs

	test	ebp,1
	jz	Vec4uBufDivByVecSzAdjArg1

	movss	[DReg],xmm2

Vec4uBufDivByVecSzAdjArg1:

	test	ebp,2
	jz	Vec4uBufDivByVecSzAdjArg2

	movss	[DReg+4],xmm2

Vec4uBufDivByVecSzAdjArg2:

	test	ebp,4
	jz	Vec4uBufDivByVecSzAdjArg3

	movss	[DReg+8],xmm2

Vec4uBufDivByVecSzAdjArg3:

	test	ebp,8
	jz	Vec4uBufDivByVecSzAdjPtrs

	movss	[DReg+12],xmm2

Vec4uBufDivByVecSzAdjPtrs:

	add	AReg,esi		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufDivByVecSzLoop

	cmp	ebp,0
	je	Vec4uBufDivByVecSzEnd

	test	ebp,1
	jz	Vec4uBufDivByVecSzAdjV1

	movss	[BReg],xmm2

Vec4uBufDivByVecSzAdjV1:

	test	ebp,2
	jz	Vec4uBufDivByVecSzAdjV2

	movss	[BReg+4],xmm2

Vec4uBufDivByVecSzAdjV2:

	test	ebp,4
	jz	Vec4uBufDivByVecSzAdjV3

	movss	[BReg+8],xmm2

Vec4uBufDivByVecSzAdjV3:

	test	ebp,8
	jz	Vec4uBufDivByVecSzEnd

	movss	[BReg+12],xmm2

Vec4uBufDivByVecSzEnd:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

;;;
;;; Vec4uDivBlockByBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uDivBlockByBlockAsm(vec4* ru,const vec4* v,const int32_t iCount);
;;;

_Vec4uDivBlockByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec4uDivBlkByBlkLoop:

	mov	edx, 0			; iFlags

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec4uDivBlkByBlkChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec4uDivBlkByBlkChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec4uDivBlkByBlkChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec4uDivBlkByBlkChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4uDivBlkByBlkChkArg3

	or	edx,4
	movss	[BReg+8],xmm3

Vec4uDivBlkByBlkChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4uDivBlkByBlkExec

	or	edx,8
	movss	[BReg+12],xmm3

Vec4uDivBlkByBlkExec:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movups	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec4uDivBlkByBlkAdjPtrs

	test	edx,1
	jz	Vec4uDivBlkByBlkAdjArg1

	movss	[AReg],xmm2
	movss	[BReg],xmm2

Vec4uDivBlkByBlkAdjArg1:

	test	edx,2
	jz	Vec4uDivBlkByBlkAdjArg2

	movss	[AReg+4],xmm2
	movss	[BReg+4],xmm2

Vec4uDivBlkByBlkAdjArg2:

	test	edx,4
	jz	Vec4uDivBlkByBlkAdjArg3

	movss	[AReg+8],xmm2
	movss	[BReg+8],xmm2

Vec4uDivBlkByBlkAdjArg3:

	test	edx,8
	jz	Vec4uDivBlkByBlkAdjPtrs

	movss	[AReg+12],xmm2
	movss	[BReg+12],xmm2

Vec4uDivBlkByBlkAdjPtrs:

	add	AReg,Vec4Size		; *u += iSize
	add	BReg,Vec4Size		; *v += iSize
	add	DReg,Vec4Size		; *r += iSize

	dec	ecx
	jnz	Vec4uDivBlkByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uDivBlockByBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uDivBlockByBlockUseSizeAsm(void*         ru,
;;;                                                const void*   v,
;;;                                                const int32_t iSize,
;;;                                                const int32_t iCount);
;;;

_Vec4uDivBlockByBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	esi, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec4uDivBlkByBlkUseSizeLoop:

	mov	edx,0

	ucomiss	xmm2,[BReg]		; v.x == 0 ?
	jne	Vec4uBufDivBlkByBlkSzChkArg1

	or	edx,1
	movss	[BReg],xmm3

Vec4uBufDivBlkByBlkSzChkArg1:

	ucomiss	xmm2,[BReg+4]		; v.y == 0.0f
	jne	Vec4uBufDivBlkByBlkSzChkArg2

	or	edx,2
	movss	[BReg+4],xmm3

Vec4uBufDivBlkByBlkSzChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4uBufDivBlkByBlkSzChkArg3

	or	edx,4
	movss	[BReg+8],xmm3

Vec4uBufDivBlkByBlkSzChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4uBufDivBlkByBlkSzExec

	or	edx,8
	movss	[BReg+12],xmm3

Vec4uBufDivBlkByBlkSzExec:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movups	[AReg],xmm0		; r=u/v

	cmp	edx,0
	je	Vec4uBufDivBlkByBlkSzAdjPtrs

	test	edx,1
	jz	Vec4uBufDivBlkByBlkSzAdjV1

	movss	[AReg],xmm2
	movss	[BReg],xmm2

Vec4uBufDivBlkByBlkSzAdjV1:

	test	edx,2
	jz	Vec4uBufDivBlkByBlkSzAdjV2

	movss	[AReg+4],xmm2
	movss	[BReg+4],xmm2

Vec4uBufDivBlkByBlkSzAdjV2:

	test	edx,4
	jz	Vec4uBufDivBlkByBlkSzAdjV3

	movss	[AReg+8],xmm2
	movss	[BReg+8],xmm2

Vec4uBufDivBlkByBlkSzAdjV3:

	test	edx,8
	jz	Vec4uBufDivBlkByBlkSzAdjPtrs

	movss	[AReg+12],xmm2
	movss	[BReg+12],xmm2

Vec4uBufDivBlkByBlkSzAdjPtrs:

	add	AReg,esi		; *ru += iSize
	add	BReg,esi		; *v  += iSize

	dec	ecx
	jnz	Vec4uDivBlkByBlkUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;; 
;;; Vec4uBufDivBufByBlkAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufDivBufByBlockAsm(void*         r,
;;;                                          const void*   u,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec4uBufDivBufByBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec4uBufDivBufByBlkLoop:

	mov	edi,0

	ucomiss	xmm2,[BReg]		; v.x == 0.0f
	jne	Vec4uBufDivBufByBlkChkArg1

	or	edi,1
	movss	[BReg],xmm3

Vec4uBufDivBufByBlkChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4uBufDivBufByBlkChkArg2

	or	edi,2
	movss	[BReg+4],xmm3

Vec4uBufDivBufByBlkChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4uBufDivBufByBlkChkArg3

	or	edi,4
	movss	[BReg+8],xmm3

Vec4uBufDivBufByBlkChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4uBufDivBufByBlkExec

	or	edi,8
	movss	[BReg+12],xmm3

Vec4uBufDivBufByBlkExec:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movups	[DReg],xmm0		; r=u/v

	cmp	edi,0
	je	Vec4uBufDivBufByBlkAdjPtrs

	test	edi,1
	jz	Vec4uBufDivBufByBlkAdjV1

	movss	[BReg],xmm2
	movss	[DReg],xmm2

Vec4uBufDivBufByBlkAdjV1:

	test	edi,2
	jz	Vec4uBufDivBufByBlkAdjV2

	movss	[BReg+4],xmm2
	movss	[DReg+4],xmm2

Vec4uBufDivBufByBlkAdjV2:

	test	edi,4
	jz	Vec4uBufDivBufByBlkAdjV3

	movss	[BReg+8],xmm2
	movss	[DReg+8],xmm2

Vec4uBufDivBufByBlkAdjV3:

	test	edi,8
	jz	Vec4uBufDivBufByBlkAdjPtrs

	movss	[BReg+12],xmm2
	movss	[DReg+12],xmm2

Vec4uBufDivBufByBlkAdjPtrs:

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,esi		; *r += iSize

	dec	ecx
	jnz	Vec4uBufDivBufByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec4uBufDivBufByBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufDivBufByBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const void*   v,
;;;                                        const int32_t iVSize,
;;;                                        const int32_t iCount);
;;; 

_Vec4uBufDivBufByBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	esi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	edi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ecx, [STACK_PTR7]	; iCount

	movss	xmm2,[zeroVec]
	movss	xmm3,[oneVec]

Vec4uBufDivBufByBufLoop:

	mov	ebp,0			; iFlags

	ucomiss	xmm2,[BReg]		; v.z == 0.0f
	jne	Vec4uBufDivBufByBufChkArg1

	or	ebp,1
	movss	[BReg],xmm3

Vec4uBufDivBufByBufChkArg1:

	ucomiss	xmm2,[BReg+4]
	jne	Vec4uBufDivBufByBufChkArg2

	or	ebp,2
	movss	[BReg+4],xmm3

Vec4uBufDivBufByBufChkArg2:

	ucomiss	xmm2,[BReg+8]
	jne	Vec4uBufDivBufByBufChkArg3

	or	ebp,4
	movss	[BReg+8],xmm3

Vec4uBufDivBufByBufChkArg3:

	ucomiss	xmm2,[BReg+12]
	jne	Vec4uBufDivBufByBufExec

	or	ebp,8
	movss	[BReg+12],xmm3

Vec4uBufDivBufByBufExec:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	divps	xmm0,xmm1		; u/v
	movups	[DReg],xmm0		; r=u/v

	cmp	ebp,0
	je	Vec4uBufDivBufByBufAdjPtrs

	test	ebp,1
	jz	Vec4uBufDivBufByBufAdjV1

	movss	[BReg],xmm2
	movss	[DReg],xmm2

Vec4uBufDivBufByBufAdjV1:

	test	ebp,2
	jz	Vec4uBufDivBufByBufAdjV2

	movss	[BReg+4],xmm2
	movss	[DReg+4],xmm2

Vec4uBufDivBufByBufAdjV2:

	test	ebp,4
	jz	Vec4uBufDivBufByBufAdjV3

	movss	[BReg+8],xmm2
	movss	[DReg+8],xmm2

Vec4uBufDivBufByBufAdjV3:

	test	ebp,8
	jz	Vec4uBufDivBufByBufAdjPtrs

	movss	[BReg+12],xmm2
	movss	[DReg+12],xmm2

Vec4uBufDivBufByBufAdjPtrs:

	add	AReg,edi
	add	BReg,[STACK_PTR6]
	add	DReg,esi

	dec	ecx
	jnz	Vec4uBufDivBufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4LerpAsm
;;;
;;; Call Stack
;;; 
;;; [4]       s
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; vec4 = lerp(vec4,vec4,float)
;;;
;;; return u * (1 - x) + v * x;
;;;
;;; extern "C" void Vec4LerpAsm(vec4* r,const vec4* u,const vec4* v,const float s)
;;; 
	
_Vec4LerpAsm:			; return u * (1 - x) + v * x

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[oneVec]
	movss	xmm1,[STACK_PTR4]	; s
	shufps	xmm1,xmm1,0

	subps	xmm0,xmm1		; (1-x)
	mulps	xmm0,[AReg]		; u*(1-x)
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4LerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] float   s
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4LerpBlockAsm(vec4* ru,vec4* v,const float s,const int32_t iCount)
;;;

_Vec4LerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	movss	xmm4,[STACK_PTR3]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec4LerpBlockLoop:

	movaps	xmm0,xmm5		; 1-x
	mulps	xmm0,[AReg]		; u*(1-x)
	movaps	xmm1,xmm4		; x
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movaps	[AReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,Vec4Size
	add	BReg,Vec4Size

	dec	ecx
	jnz	Vec4LerpBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4LerpBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4LerpBlockUseSize(void*         ru,
;;;                                      const void*   v,
;;;                                      const float   s,
;;;                                      const int32_t iSize,
;;;                                      const int32_t iCount);
;;; 

_Vec4LerpBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	movss	xmm4,[STACK_PTR3]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec4LerpBlockUseSizeLoop:

	movaps	xmm0,xmm5		; 1-x
	mulps	xmm0,[AReg]		; u*(1-x)
	movaps	xmm1,xmm4		; x
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movaps	[AReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4LerpBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Vec4BufLerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] float   s
;;; [5] vec4*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec3BufLerpBlockAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const vec3*   v,
;;;                                     const float   s,
;;;                                     const int32_t iCount);
;;; 

_Vec4BufLerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ecx, [STACK_PTR7]	; iCount

	movss	xmm4,[STACK_PTR6]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]		; 1.0f
	subps	xmm5,xmm4		; 1-s

Vec4BufLerpBlockLoop:

	movaps	xmm0,xmm5		; 1-x
	movaps	xmm1,xmm4		; v
	mulps	xmm0,[AReg]		; u*(1-x)
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movaps	[DReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,esi		; *u += iUSize
	add	BReg,Vec4Size		; *v += iSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufLerpBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec4BufLerpBufAsm
;;;
;;; Call Stack
;;;
;;; [8] int32_t iCount
;;; [7] float   s
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufLerpBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const void*   v,
;;;                                   const int32_t iVSize,
;;;                                   const float   s,
;;;                                   const int32_t iCount);
;;;

_Vec4BufLerpBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR8]	; iCount

	movss	xmm4,[STACK_PTR7]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]		; 1.0
	subps	xmm5,xmm4		; 1-x

Vec4BufLerpBufLoop:

	movaps	xmm0,xmm5		; 1-x
	movaps	xmm1,xmm4		; x
	mulps	xmm0,[AReg]		; u*(1-x)
	mulps	xmm1,[BReg]		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movaps	[DReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4BufLerpBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uLerpAsm
;;;
;;; Call Stack
;;; 
;;; [4]       s
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; vec4 = lerp(vec4,vec4,float)
;;;
;;; return u * (1 - x) + v * x;
;;;
;;; extern "C" void Vec4uLerpAsm(vec4* r,const vec4* u,const vec4* v,const float s)
;;; 
	
_Vec4uLerpAsm:			; return u * (1 - x) + v * x

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[oneVec]
	movss	xmm1,[STACK_PTR4]	; s
	shufps	xmm1,xmm1,0

	subps	xmm0,xmm1		; (1-x)
	movups	xmm3,[AReg]		; u
	movups	xmm4,[BReg]		; v
	mulps	xmm0,xmm3		; u*(1-x)
	mulps	xmm1,xmm4		; v*x
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uLerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] float   s
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uLerpBlockAsm(vec4* ru,vec4* v,const float s,const int32_t iCount)
;;;

_Vec4uLerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR4]	; iCount
	movss	xmm4,[STACK_PTR3]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec4uLerpBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm5		; u*(1-x)
	mulps	xmm1,xmm4		; u*v
	addps	xmm0,xmm1		; u*(1-x)+(v*x)

	movups	[AReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,Vec4Size
	add	BReg,Vec4Size

	dec	ecx
	jnz	Vec4uLerpBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uLerpBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] float   s
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uLerpBlockUseSize(void*         ru,
;;;                                       const void*   v,
;;;                                       const float   s,
;;;                                       const int32_t iSize,
;;;                                       const int32_t iCount);
;;; 

_Vec4uLerpBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount
	movss	xmm4,[STACK_PTR3]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec4uLerpBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm5		; u*(1-x)
	mulps	xmm1,xmm4		; u*v
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movups	[AReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4uLerpBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Vec4uBufLerpBlockAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] float   s
;;; [5] vec4*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufLerpBlockAsm(void*         r,
;;;                                      const int32_t iRSize,
;;;                                      const void*   u,
;;;                                      const int32_t iUSize,
;;;                                      const vec3*   v,
;;;                                      const float   s,
;;;                                      const int32_t iCount);
;;; 

_Vec4uBufLerpBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ecx, [STACK_PTR7]	; iCount

	movss	xmm4,[STACK_PTR6]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec4uBufLerpBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm5		; u*(1-x)
	mulps	xmm1,xmm4		; u*v
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movups	[DReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,esi		; *u += iUSize
	add	BReg,Vec4Size		; *v += iSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufLerpBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Vec4uBufLerpBufAsm
;;;
;;; Call Stack
;;;
;;; [8] int32_t iCount
;;; [7] float   s
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufLerpBufAsm(void*         r,
;;;                                    const int32_t iRSize,
;;;                                    const void*   u,
;;;                                    const int32_t iUSize,
;;;                                    const void*   v,
;;;                                    const int32_t iVSize,
;;;                                    const float   s,
;;;                                    const int32_t iCount);
;;;

_Vec4uBufLerpBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR8]	; iCount

	movss	xmm4,[STACK_PTR7]	; s
	shufps	xmm4,xmm4,0
	movaps	xmm5,[oneVec]
	subps	xmm5,xmm4		; 1-x

Vec4uBufLerpBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm5		; u*(1-x)
	mulps	xmm1,xmm4		; u*v
	addps	xmm0,xmm1		; u*(1-x)+(v*x)
	movups	[DReg],xmm0		; r=u*(1-x)+(v*x)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufLerpBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4DotAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4*  v
;;; [2] vec4*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec4,vec4)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec4DotAsm(float* r,const vec4* u,const vec4* v)
;;; 

_Vec4DotAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,[zeroVec]

	mulps	xmm0,[BReg]		; u * v

	haddps	xmm0,xmm1		; (u.x*v.x)+(u.y*v.y),(u.z*v.z)+(u.w*v.w), 0, 0
	haddps	xmm0,xmm1		; (u.x*v.x)+(u.y*v.y)+(u.z*v.z)+(u.w*v.w),0,0,0

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4DotBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] vec4*   v
;;; [2] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4DotBlockAsm(float*        r,
;;;                                 const vec4*   u,
;;;                                 const vec4*   v,
;;;                                 const int32_t iCount);
;;; 

_Vec4DotBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR4]	; iCount

	movaps	xmm2,[zeroVec]

Vec4DotBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v

	haddps	xmm0,xmm2
	haddps	xmm0,xmm2		; u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w

	movss	[DReg],xmm0		; r = sum(u*v)

	add	AReg,Vec4Size		; *u += iSize
	add	BReg,Vec4Size		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec4DotBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4DotBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4DotBlockUseSizeAsm(float*        r,
;;;                                        const void*   u,
;;;                                        const void*   v,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec4DotBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm2,[zeroVec]

Vec4DotBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v

	haddps	xmm0,xmm2
	haddps	xmm0,xmm2

	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec4DotBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4BufDotBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufDotBufAsm(void*         r,
;;;                                  const int32_t iRSize,
;;;                                  const void*   u,
;;;                                  const int32_t iUSize,
;;;                                  const void*   v,
;;;                                  const int32_t iVSize,
;;;                                  const int32_t iCount);
;;;

_Vec4BufDotBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

	movaps	xmm2,[zeroVec]

Vec4BufDotBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v

	haddps	xmm0,xmm2
	haddps	xmm0,xmm2

	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4BufDotBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uDotAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4*  v
;;; [2] vec4*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec4,vec4)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec4uDotAsm(float* r,const vec4* u,const vec4* v)
;;; 

_Vec4uDotAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	movaps	xmm2,[zeroVec]

	mulps	xmm0,xmm1		; u*v

	haddps	xmm0,xmm2		; (u.x*v.x)+(u.y*v.y),(u.z*v.z)+(u.w*v.w), 0, 0
	haddps	xmm0,xmm2		; (u.x*v.x)+(u.y*v.y)+(u.z*v.z)+(u.w*v.w),0,0,0

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uDotBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] vec4*   v
;;; [2] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4uDotBlockAsm(float*        r,
;;;                                  const vec4*   u,
;;;                                  const vec4*   v,
;;;                                  const int32_t iCount);
;;; 

_Vec4uDotBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR4]	; iCount

	movaps	xmm2,[zeroVec]

Vec4uDotBlockLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v

	haddps	xmm0,xmm2
	haddps	xmm0,xmm2		; u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w

	movss	[DReg],xmm0		; r = sum(u*v)

	add	AReg,Vec4Size		; *u += iSize
	add	BReg,Vec4Size		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec4uDotBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uDotBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4uDotBlockUseSizeAsm(float*        r,
;;;                                         const void*   u,
;;;                                         const void*   v,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec4uDotBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm2,[zeroVec]

Vec4uDotBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v

	haddps	xmm0,xmm2
	haddps	xmm0,xmm2

	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec4uDotBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4uBufDotBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufDotBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const void*   v,
;;;                                   const int32_t iVSize,
;;;                                   const int32_t iCount);
;;;

_Vec4uBufDotBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

	movaps	xmm2,[zeroVec]

Vec4uBufDotBufLoop:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v

	haddps	xmm0,xmm2
	haddps	xmm0,xmm2

	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufDotBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4DotFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4*  v
;;; [2] vec4*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec4,vec4)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec4DotFlatAsm(float* r,const vec4* u,const vec4* v)
;;; 

_Vec4DotFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u * v

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4DotBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] vec4*   v
;;; [2] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4DotBlockFlatAsm(float*        r,
;;;                                     const vec4*   u,
;;;                                     const vec4*   v,
;;;                                     const int32_t iCount);
;;; 

_Vec4DotBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR4]	; iCount

Vec4DotBlockLoopF:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)	; u.y*v.y
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)	; u.z*v.z
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)	; u.w*v.w

	addss	xmm0,xmm1		; u.x*v.x + u.y*v.y
	addss	xmm0,xmm2		; u.x*v.x + u.y*v.y + u.z*v.z
	addss	xmm0,xmm3		; u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w

	movss	[DReg],xmm0		; r = sum(u*v)

	add	AReg,Vec4Size		; *u += iSize
	add	BReg,Vec4Size		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec4DotBlockLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4DotBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4DotBlockFlatUseSizeAsm(float*        r,
;;;                                            const void*   u,
;;;                                            const void*   v,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec4DotBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4DotBlockUseSizeLoopF:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec4DotBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4BufDotBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufDotBufFlatAsm(void*         r,
;;;                                      const int32_t iRSize,
;;;                                      const void*   u,
;;;                                      const int32_t iUSize,
;;;                                      const void*   v,
;;;                                      const int32_t iVSize,
;;;                                      const int32_t iCount);
;;;

_Vec4BufDotBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec4BufDotBufLoopF:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,[BReg]		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)
	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3
	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4BufDotBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uDotFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4*  v
;;; [2] vec4*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec4,vec4)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vecu4DotFlatAsm(float* r,const vec4* u,const vec4* v)
;;; 

_Vec4uDotFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u * v

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uDotBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t iCount
;;; [3] vec4*   v
;;; [2] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4uDotBlockFlatAsm(float*        r,
;;;                                      const vec4*   u,
;;;                                      const vec4*   v,
;;;                                      const int32_t iCount);
;;; 

_Vec4uDotBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	ecx, [STACK_PTR4]	; iCount

Vec4uDotBlockLoopF:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)	; u.y*v.y
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)	; u.z*v.z
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)	; u.w*v.w

	addss	xmm0,xmm1		; u.x*v.x + u.y*v.y
	addss	xmm0,xmm2		; u.x*v.x + u.y*v.y + u.z*v.z
	addss	xmm2,xmm3		; u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w

	movss	[DReg],xmm0		; r = sum(u*v)

	add	AReg,Vec4Size		; *u += iSize
	add	BReg,Vec4Size		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec4uDotBlockLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uDotBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] void*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4uDotBlockFlatUseSizeAsm(float*        r,
;;;                                             const void*   u,
;;;                                             const void*   v,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec4uDotBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v
	mov	esi, [STACK_PTR4]	; iSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uDotBlockUseSizeLoopF:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iSize
	add	BReg,esi		; *v += iSize
	add	DReg,FloatSize		; *r += fSize

	dec	ecx
	jnz	Vec4uDotBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Vec4uBufDotBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufDotBufFlatAsm(void*         r,
;;;                                       const int32_t iRSize,
;;;                                       const void*   u,
;;;                                       const int32_t iUSize,
;;;                                       const void*   v,
;;;                                       const int32_t iVSize,
;;;                                       const int32_t iCount);
;;;

_Vec4uBufDotBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	ebp, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	edi, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec4uBufDotBufLoopF:

	movups	xmm0,[AReg]		; u
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; u*v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)
	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3
	movss	[DReg],xmm0		; r=sum(u*v)

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufDotBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; Vec4uDotFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] vec4*  v
;;; [2] vec4*  u
;;; [1] float* r
;;; [0] ret
;;;
;;; float = dot(vec4,vec4)
;;;
;;; u.x * v.x + u.y * v.y + u.z * v.z
;;;
;;; extern "C" void Vec4uDotFPU_Asm(float* r,const vec4* u,const vec4* v)
;;; 

_Vec4DotFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	BReg,[STACK_PTR3]	; *v

	fld	dword [AReg]		; u.x
	fmul	dword [BReg]		; u.x*v.x

	fld	dword [AReg+4]		; u.y
	fmul	dword [BReg+4]		; u.y*v.y
	faddp	st1,st0			; u.x*v.x + u.y*v.y

	fld	dword [AReg+8]		; u.z
	fmul	dword [BReg+8]		; u.z*v.z
	faddp	st1,st0			; u.x*v.x + u.y*v.y + u.z*v.z

	fld	dword [AReg+12]		; u.w
	fmul	dword [BReg+12]		; u.x*v.w
	faddp	st1,st0			; u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w

	fstp	dword [DReg]		; r = sum(u*v)

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4SqrAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;;
;;;
;;; extern "C" void Vec4SqrAsm(vec4* r,const vec4* v);
;;;

_Vec4SqrAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4SqrBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4SqrBlockAsm(vec4* ru,const int32_t iCount);
;;;

_Vec4SqrBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	ecx, [STACK_PTR2]	; iCount

Vec4SqrBlockLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	[AReg],xmm0		; r=u*u

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4SqrBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4SqrBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4SqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
;;;

_Vec4SqrBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

Vec4SqrBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	[AReg],xmm0		; r=u*u

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4SqrBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufSqrBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufSqrBufAsm(void*         r,
;;;                                  const int32_t iRSize,
;;;                                  const void*   u,
;;;                                  const int32_t iUSize,
;;;                                  const int32_t iCount);
;;; 

_Vec4BufSqrBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4BufSqrBufLoop:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movaps	[DReg],xmm0		; r=u*u

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufSqrBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uSqrAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;;
;;;
;;; extern "C" void Vec4uSqrAsm(vec4* r,const vec4* v);
;;;

_Vec4uSqrAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uSqrBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uSqrBlockAsm(vec4* ru,const int32_t iCount);
;;;

_Vec4uSqrBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	ecx, [STACK_PTR2]	; iCount

Vec4uSqrBlockLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movups	[AReg],xmm0		; r=u*u

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4uSqrBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uSqrBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uSqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
;;;

_Vec4uSqrBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

Vec4uSqrBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movups	[AReg],xmm0		; r=u*u

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4uSqrBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufSqrBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufSqrBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const int32_t iCount);
;;; 

_Vec4uBufSqrBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uBufSqrBufLoop:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u
	movups	[DReg],xmm0		; r=u*u

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufSqrBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4SqrtAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;;
;;;
;;; extern "C" void Vec4SqrtAsm(vec4* r,const vec4* v);
;;;

_Vec4SqrtAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	sqrtps	xmm0,xmm0		; sqrt(v)
	movaps	[DReg],xmm0		; r = sqrt(v)

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4SqrtBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4SqrtBlockAsm(vec4* ru,const int32_t iCount);
;;;

_Vec4SqrtBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	ecx, [STACK_PTR2]	; iCount

Vec4SqrtBlockLoop:

	movaps	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movaps	[AReg],xmm0		; r = sqrt(u)

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4SqrtBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4SqrtBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4SqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
;;;

_Vec4SqrtBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

Vec4SqrtBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movaps	[AReg],xmm0		; r = sqrt(u)

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4SqrtBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufSqrtBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufSqrtBufAsm(void*         r,
;;;                                   const int32_t iRSize,
;;;                                   const void*   u,
;;;                                   const int32_t iUSize,
;;;                                   const int32_t iCount);
;;; 

_Vec4BufSqrtBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4BufSqrtBufLoop:

	movaps	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movaps	[DReg],xmm0		; r = sqrt(u)

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufSqrtBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uSqrtAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;;
;;;
;;; extern "C" void Vec4uSqrtAsm(vec4* r,const vec4* v);
;;;

_Vec4uSqrtAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	sqrtps	xmm0,xmm0		; sqrt(v)
	movups	[DReg],xmm0		; r = sqrt(v)

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uSqrtBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uSqrtBlockAsm(vec4* ru,const int32_t iCount);
;;;

_Vec4uSqrtBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *u
	mov	ecx, [STACK_PTR2]	; iCount

Vec4uSqrtBlockLoop:

	movups	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movups	[AReg],xmm0		; r = sqrt(u)

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4uSqrtBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uSqrtBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uSqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
;;;

_Vec4uSqrtBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

Vec4uSqrtBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movups	[AReg],xmm0		; r = sqrt(u)

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4uSqrtBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufSqrtBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufSqrtBufAsm(void*         r,
;;;                                    const int32_t iRSize,
;;;                                    const void*   u,
;;;                                    const int32_t iUSize,
;;;                                    const int32_t iCount);
;;; 

_Vec4uBufSqrtBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uBufSqrtBufLoop:

	movups	xmm0,[AReg]		; u
	sqrtps	xmm0,xmm0		; sqrt(u)
	movups	[DReg],xmm0		; r = sqrt(u)

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufSqrtBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif
	
%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4NormalizeAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4NormalizeAsm(vec3* r,const vec3* r)
;;;

_Vec4NormalizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm2,[zeroVec]
	movaps	xmm0,[AReg]		; v
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; v * v

	haddps	xmm1,xmm2
	haddps	xmm1,xmm2

	ucomiss	xmm1,xmm2
	je	Vec4NormalizeDB0

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec4NormalizeDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4NormalizeBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4NormalizeBlockAsm(vec4*         ru,
;;;                                       const int32_t iCount);
;;;

_Vec4NormalizeBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

	movaps	xmm5,[zeroVec]

Vec4NormalizeBlockLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	haddps	xmm1,xmm5
	haddps	xmm1,xmm5

	ucomiss	xmm1,xmm5		; sum(sqr(u)) == 0.0
	jne	Vec4NormalizeBlockExec

	movaps	[AReg],xmm5
	jmp	Vec4NormalizeBlockAdjPtrs

Vec4NormalizeBlockExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sum(sqr(u))
	movaps	[AReg],xmm0		; r=u/sum(sqr(u))

Vec4NormalizeBlockAdjPtrs:

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4NormalizeBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4NormalizeBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4NormalizeBlockUseSizeAsm(vec4*         ru,
;;;                                              const int32_t iSize,
;;;                                              const int32_t iCount);
;;;

_Vec4NormalizeBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm5,[zeroVec]

Vec4NormalizeBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	haddps	xmm1,xmm5
	haddps	xmm1,xmm5

	ucomiss	xmm1,xmm5
	jne	Vec4NormalizeBlockUseSzExec

	movaps	[AReg],xmm5
	jmp	Vec4NormalizeBlockUseSzAdjPtrs

Vec4NormalizeBlockUseSzExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movaps	[AReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec4NormalizeBlockUseSzAdjPtrs:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4NormalizeBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufNormalizeBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufNormalizeBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const void*   u,
;;;                                        const int32_t iUSize,
;;;                                        const int32_t iCount);
;;;

_Vec4BufNormalizeBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm5,[zeroVec]

Vec4BufNormalizeBufLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1

	haddps	xmm1,xmm5
	haddps	xmm1,xmm5

	ucomiss	xmm1,xmm5		; 0.0 == sqrt(sum(sqr(u)))
	jne	Vec4BufNormalizeBufExec

	movaps	[DReg],xmm5
	jmp	Vec4BufNormalizeAdjPtrs

Vec4BufNormalizeBufExec:

	sqrtss	xmm1,xmm1		; sqrt(sum(sqr(u)))
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movaps	[DReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec4BufNormalizeAdjPtrs:

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufNormalizeBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uNormalizeAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4uNormalizeAsm(vec3* r,const vec3* r)
;;;

_Vec4uNormalizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm2,[zeroVec]
	movups	xmm0,[AReg]		; v
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; v * v

	haddps	xmm1,xmm2
	haddps	xmm1,xmm2

	ucomiss	xmm1,xmm2
	je	Vec4uNormalizeDB0

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec4uNormalizeDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uNormalizeBlockAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uNormalizeBlockAsm(vec4*         ru,
;;;                                        const int32_t iCount);
;;;

_Vec4uNormalizeBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

	movaps	xmm5,[zeroVec]

Vec4uNormalizeBlockLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	haddps	xmm1,xmm5
	haddps	xmm1,xmm5

	ucomiss	xmm1,xmm5		; sum(sqr(u)) == 0.0
	jne	Vec4uNormalizeBlockExec

	movups	[AReg],xmm5
	jmp	Vec4uNormalizeBlockAdjPtrs

Vec4uNormalizeBlockExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sum(sqr(u))
	movups	[AReg],xmm0		; r=u/sum(sqr(u))

Vec4uNormalizeBlockAdjPtrs:

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4uNormalizeBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uNormalizeBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uNormalizeBlockUseSizeAsm(vec4*         ru,
;;;                                               const int32_t iSize,
;;;                                               const int32_t iCount);
;;;

_Vec4uNormalizeBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movups	xmm5,[zeroVec]

Vec4uNormalizeBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	haddps	xmm1,xmm5
	haddps	xmm1,xmm5

	ucomiss	xmm1,xmm5
	jne	Vec4uNormalizeBlockUseSzExec

	movups	[AReg],xmm5
	jmp	Vec4uNormalizeBlockUseSzAdjPtrs

Vec4uNormalizeBlockUseSzExec:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movups	[AReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec4uNormalizeBlockUseSzAdjPtrs:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4uNormalizeBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufNormalizeBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufNormalizeBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const int32_t iCount);
;;;

_Vec4uBufNormalizeBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm5,[zeroVec]

Vec4uBufNormalizeBufLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1

	haddps	xmm1,xmm5
	haddps	xmm1,xmm5

	ucomiss	xmm1,xmm5		; 0.0 == sqrt(sum(sqr(u)))
	jne	Vec4uBufNormalizeBufExec

	movups	[DReg],xmm5
	jmp	Vec4uBufNormalizeAdjPtrs

Vec4uBufNormalizeBufExec:

	sqrtss	xmm1,xmm1		; sqrt(sum(sqr(u)))
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movups	[DReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec4uBufNormalizeAdjPtrs:

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufNormalizeBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4NormalizeFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4NormalizeFlatAsm(vec3* r,const vec3* r)
;;;

_Vec4NormalizeFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; v * v

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1

	shufps	xmm1,xmm1,0
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(3,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	addss	xmm1,xmm4
	sqrtss	xmm1,xmm1

	ucomiss	xmm1,[zeroVec]
	je	Vec4NormalizeDB0F

	shufps	xmm1,xmm1,0

	divps	xmm0,xmm1

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec4NormalizeDB0F:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4NormalizeBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4NormalizeBlockFlatAsm(vec4*         ru,
;;;                                           const int32_t iCount);
;;;

_Vec4NormalizeBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

	movaps	xmm5,[zeroVec]

Vec4NormalizeBlockLoopF:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1

	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(3,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	addss	xmm1,xmm4

	sqrtss	xmm1,xmm1

	ucomiss	xmm1,xmm5		; sum(sqr(u)) == 0.0
	jne	Vec4NormalizeBlockExecF

	movaps	[AReg],xmm5
	jmp	Vec4NormalizeBlockAdjPtrsF

Vec4NormalizeBlockExecF:

	shufps	xmm1,xmm1,0

	divps	xmm0,xmm1		; u / sum(sqr(u))

	movaps	[AReg],xmm0		; r=u/sum(sqr(u))

Vec4NormalizeBlockAdjPtrsF:

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4NormalizeBlockLoopF

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4NormalizeBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4NormalizeBlockFlatUseSizeAsm(vec4*         ru,
;;;                                                  const int32_t iSize,
;;;                                                  const int32_t iCount);
;;;

_Vec4NormalizeBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm5,[zeroVec]

Vec4NormalizeBlockUseSizeLoopF:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(3,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	addss	xmm1,xmm4

	ucomiss	xmm1,xmm5
	jne	Vec4NormalizeBlockUseSzExecF

	movaps	[AReg],xmm5
	jmp	Vec4NormalizeBlockUseSzAdjPtrsF

Vec4NormalizeBlockUseSzExecF:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movaps	[AReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec4NormalizeBlockUseSzAdjPtrsF:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4NormalizeBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4BufNormalizeBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufNormalizeBufFlatAsm(void*         r,
;;;                                            const int32_t iRSize,
;;;                                            const void*   u,
;;;                                            const int32_t iUSize,
;;;                                            const int32_t iCount);
;;;

_Vec4BufNormalizeBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm5,[zeroVec]

Vec4BufNormalizeBufLoopF:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(3,0,0,0)
	addss	xmm1,xmm2
	addss	xmm1,xmm3
	addss	xmm1,xmm4

	ucomiss	xmm1,xmm5		; 0.0 == sqrt(sum(sqr(u)))
	jne	Vec4BufNormalizeBufExecF

	movaps	[DReg],xmm5
	jmp	Vec4BufNormalizeAdjPtrsF

Vec4BufNormalizeBufExecF:

	sqrtss	xmm1,xmm1		; sqrt(sum(sqr(u)))
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movaps	[DReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec4BufNormalizeAdjPtrsF:

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufNormalizeBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uNormalizeFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4uNormalizeFlatAsm(vec3* r,const vec3* r)
;;;

_Vec4uNormalizeFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; v * v

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1

	shufps	xmm1,xmm1,0
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(3,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	addss	xmm1,xmm4
	sqrtss	xmm1,xmm1

	ucomiss	xmm1,[zeroVec]
	je	Vec4uNormalizeDB0F

	shufps	xmm1,xmm1,0

	divps	xmm0,xmm1

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec4uNormalizeDB0F:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uNormalizeBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] int32_t iCount
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uNormalizeBlockFlatAsm(vec4*         ru,
;;;                                            const int32_t iCount);
;;;

_Vec4uNormalizeBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ecx, [STACK_PTR2]	; iCount

	movaps	xmm5,[zeroVec]

Vec4uNormalizeBlockLoopF:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1

	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(3,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	addss	xmm1,xmm4

	ucomiss	xmm1,xmm5		; sum(sqr(u)) == 0.0
	jne	Vec4uNormalizeBlockExecF

	movups	[AReg],xmm5
	jmp	Vec4uNormalizeBlockAdjPtrsF

Vec4uNormalizeBlockExecF:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sum(sqr(u))
	movups	[AReg],xmm0		; r=u/sum(sqr(u))

Vec4uNormalizeBlockAdjPtrsF:

	add	AReg,Vec4Size		; *ru += iSize

	dec	ecx
	jnz	Vec4uNormalizeBlockLoopF

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uNormalizeBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uNormalizeBlockFlatUseSizeAsm(vec4*         ru,
;;;                                                   const int32_t iSize,
;;;                                                   const int32_t iCount);
;;;

_Vec4uNormalizeBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	ebx, [STACK_PTR2]	; iSize
	mov	ecx, [STACK_PTR3]	; iCount

	movaps	xmm5,[zeroVec]

Vec4uNormalizeBlockUseSizeLoopF:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; u*u

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(3,0,0,0)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	addss	xmm1,xmm4

	ucomiss	xmm1,xmm5
	jne	Vec4uNormalizeBlockUseSzExecF

	movups	[AReg],xmm5
	jmp	Vec4uNormalizeBlockUseSzAdjPtrsF

Vec4uNormalizeBlockUseSzExecF:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movups	[AReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec4uNormalizeBlockUseSzAdjPtrsF:

	add	AReg,ebx		; *ru += iSize

	dec	ecx
	jnz	Vec4uNormalizeBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uBufNormalizeBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufNormalizeBufFlatAsm(void*         r,
;;;                                             const int32_t iRSize,
;;;                                             const void*   u,
;;;                                             const int32_t iUSize,
;;;                                             const int32_t iCount);
;;;

_Vec4uBufNormalizeBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

	movaps	xmm5,[zeroVec]

Vec4uBufNormalizeBufLoopF:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1
	shufps	xmm2,xmm2,SHUFFLE(1,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(2,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(3,0,0,0)
	addss	xmm1,xmm2
	addss	xmm1,xmm3
	addss	xmm1,xmm4

	ucomiss	xmm1,xmm5		; 0.0 == sqrt(sum(sqr(u)))
	jne	Vec4uBufNormalizeBufExecF

	movups	[DReg],xmm5
	jmp	Vec4uBufNormalizeAdjPtrsF

Vec4uBufNormalizeBufExecF:

	sqrtss	xmm1,xmm1		; sqrt(sum(sqr(u)))
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; u / sqrt(sum(sqr(u)))
	movups	[DReg],xmm0		; r=u/sqrt(sum(sqr(u)))

Vec4uBufNormalizeAdjPtrsF:

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufNormalizeBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; Vec4NormalizeFPU_Asm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Vec4uNormalizeFPU_Asm(vec3* r,const vec3* r)
;;;

_Vec4NormalizeFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *v

	fld	dword [AReg]		; v.x
	fld	st0
	fmulp	st1,st0			; v.x*v.x

	fld	dword [AReg+4]		; v.y
	fld	st0
	fmulp	st1,st0			; v.y*v.y
	faddp	st1,st0			; sqr(v.x)+sqr(v.y)

	fld	dword [AReg+8]		; v.z
	fld	st0
	fmulp	st1,st0			; v.z*v.z
	faddp	st1,st0			; sum(sqr(v))

	fld	dword [AReg+12]		; v.w
	fld	st0
	fmulp	st1,st0
	faddp	st1,st0			; sum(sqr(v))

	fsqrt				; sqrtf(sum(sqr(v)))

	fldz
	fcomip	st0,st1
	je	Vec4NormalizeFPUDB0

	fld	st0
	fld	st0
	fld	st0

	fdivr	dword [AReg]		; v.x / sqrtf(sum(sqr(v)))
	fstp	dword [DReg]

	fdivr	dword [AReg+4]		; v.y / sqrtf(sum(sqr(v)))
	fstp	dword [DReg+4]

	fdivr	dword [AReg+8]		; v.z / sqrtf(sum(sqr(v)))
	fstp	dword [DReg+8]

	fdivr	dword [AReg+12]		; v.w / sqrtf(sum(sqr(v)))
	fstp	dword [DReg+12]

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Vec4NormalizeFPUDB0:

	ffree	st0

	fldz
	fst	dword [DReg]
	fst	dword [DReg+4]
	fst 	dword [DReg+8]
	fstp	dword [DReg+12]

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4LengthAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec4LengthAsm(float* r,const vec4* v);
;;;

_Vec4LengthAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm1,[zeroVec]
	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1
	
	sqrtss	xmm0,xmm0		; sqrtf(sum(sqr(v)))

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4LengthBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4LengthBlockAsm(float* r,const vec4* u,const int32_t iCount);
;;; 

_Vec4LengthBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR3]	; iCount

Vec4LengthBlockLoop:

	movaps	xmm1,[zeroVec]
	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr))

	add	AReg,Vec4Size		; *u += iSize
	add	DReg,FloatSize		; *r += iSize

	dec	ecx
	jnz	Vec4LengthBlockLoop

	mov	AReg,[STACK_PTR1]
	mov	CReg,[STACK_PTR2]

	ret

;;;
;;; Vec4LengthBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4LengthBlockUseSize(float*        r,
;;;                                        const vec4*   u,
;;;                                        const int32_t iSize,
;;;                                        const int32_t iCount);
;;;

_Vec4LengthBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec4LengthBlockUseSizeLoop:

	movaps	xmm1,[zeroVec]
	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr(u)))

	add	AReg,ebx		; *u += iSize
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec4LengthBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufLengthBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufLengthBufAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const int32_t iCount);
;;;

_Vec4BufLengthBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4BufLengthBufLoop:

	movaps	xmm1,[zeroVec]
	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufLengthBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uLengthAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec4uLengthAsm(float* r,const vec4* v);
;;;

_Vec4uLengthAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm1,[zeroVec]
	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1
	
	sqrtss	xmm0,xmm0		; sqrtf(sum(sqr(v)))

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uLengthBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4uLengthBlockAsm(float* r,const vec4* u,const int32_t iCount);
;;; 

_Vec4uLengthBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR3]	; iCount

Vec4uLengthBlockLoop:

	movaps	xmm1,[zeroVec]
	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr))

	add	AReg,Vec4Size		; *u += iSize
	add	DReg,FloatSize		; *r += iSize

	dec	ecx
	jnz	Vec4uLengthBlockLoop

	mov	AReg,[STACK_PTR1]
	mov	CReg,[STACK_PTR2]

	ret

;;;
;;; Vec4uLengthBlockUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4uLengthBlockUseSize(float*        r,
;;;                                         const vec4*   u,
;;;                                         const int32_t iSize,
;;;                                         const int32_t iCount);
;;;

_Vec4uLengthBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec4uLengthBlockUseSizeLoop:

	movaps	xmm1,[zeroVec]
	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr(u)))

	add	AReg,ebx		; *u += iSize
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec4uLengthBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufLengthBufAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufLengthBufAsm(void*         r,
;;;                                      const int32_t iRSize,
;;;                                      const void*   u,
;;;                                      const int32_t iUSize,
;;;                                      const int32_t iCount);
;;;

_Vec4uBufLengthBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uBufLengthBufLoop:

	movaps	xmm1,[zeroVec]
	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	haddps	xmm0,xmm1
	haddps	xmm0,xmm1

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufLengthBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4LengthFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec4LengthFlatAsm(float* r,const vec4* v);
;;;

_Vec4LengthFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2		; sum(sqr(v))
	addss	xmm0,xmm3

	sqrtss	xmm0,xmm0		; sqrtf(sum(sqr(v)))
	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4LengthBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4LengthBlockFlatAsm(float* r,const vec4* u,const int32_t iCount);
;;; 

_Vec4LengthBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR3]	; iCount

Vec4LengthBlockLoopF:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr))

	add	AReg,Vec4Size		; *u += iSize
	add	DReg,FloatSize		; *r += iSize

	dec	ecx
	jnz	Vec4LengthBlockLoopF

	mov	AReg,[STACK_PTR1]
	mov	CReg,[STACK_PTR2]

	ret

;;;
;;; Vec4LengthBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4LengthBlockFlatUseSize(float*        r,
;;;                                            const vec4*   u,
;;;                                            const int32_t iSize,
;;;                                            const int32_t iCount);
;;;

_Vec4LengthBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec4LengthBlockUseSizeLoopF:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr(u)))

	add	AReg,ebx		; *u += iSize
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec4LengthBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufLengthBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufLengthFlatBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   u,
;;;                                         const int32_t iUSize,
;;;                                         const int32_t iCount);
;;;

_Vec4BufLengthBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4BufLengthBufLoopF:

	movaps	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4BufLengthBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uLengthFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec4uLengthFlatAsm(float* r,const vec4* v);
;;;

_Vec4uLengthFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; v
	mulps	xmm0,xmm0		; v * v

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2		; sum(sqr(v))
	addss	xmm0,xmm3

	sqrtss	xmm0,xmm0		; sqrtf(sum(sqr(v)))
	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Vec4uLengthBlockFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4uLengthBlockFlatAsm(float* r,const vec4* u,const int32_t iCount);
;;; 

_Vec4uLengthBlockFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ecx, [STACK_PTR3]	; iCount

Vec4uLengthBlockLoopF:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr))

	add	AReg,Vec4Size		; *u += iSize
	add	DReg,FloatSize		; *r += iSize

	dec	ecx
	jnz	Vec4uLengthBlockLoopF

	mov	AReg,[STACK_PTR1]
	mov	CReg,[STACK_PTR2]

	ret

;;;
;;; Vec4uLengthBlockFlatUseSizeAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] int32_t iSize
;;; [1] vec4*   u
;;; [1] float*  r
;;;
;;; extern "C" void Vec4uLengthBlockFlatUseSize(float*        r,
;;;                                             const vec4*   u,
;;;                                             const int32_t iSize,
;;;                                             const int32_t iCount);
;;;

_Vec4uLengthBlockFlatUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *u
	mov	ebx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec4uLengthBlockUseSizeLoopF:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0		; r=sqrt(sum(sqr(u)))

	add	AReg,ebx		; *u += iSize
	add	DReg,FloatSize

	dec	ecx
	jnz	Vec4uLengthBlockUseSizeLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufLengthBufFlatAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufLengthFlatBufAsm(void*         r,
;;;                                          const int32_t iRSize,
;;;                                          const void*   u,
;;;                                          const int32_t iUSize,
;;;                                          const int32_t iCount);
;;;

_Vec4uBufLengthBufFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	ebx, [STACK_PTR4]	; iUSize
	mov	ecx, [STACK_PTR5]	; iCount

Vec4uBufLengthBufLoopF:

	movups	xmm0,[AReg]		; u
	mulps	xmm0,xmm0		; u*u

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(2,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(3,0,0,0)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	sqrtss	xmm0,xmm0
	movss	[DReg],xmm0

	add	AReg,ebx		; *u += iUSize
	add	DReg,edi		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufLengthBufLoopF

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; Vec4LengthFPU_Asm
;;;
;;; Call Stack
;;;
;;; [2] vec4*  v
;;; [1] float* r
;;;
;;; extern "C" void Vec4LengthFPU_Asm(float* r,const vec4* v);
;;;

_Vec4LengthFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *v

	fld	dword [AReg]		; v.x
	fld	st0
	fmulp	st1,st0			; v.x*v.x

	fld	dword [AReg+4]		; v.y
	fld	st0
	fmulp	st1,st0			; v.y*v.y
	faddp	st1,st0			; v.x*v.x+v.y*v.y

	fld	dword [AReg+8]		; v.z
	fld	st0
	fmulp	st1,st0			; v.z*v.z
	faddp	st1,st0			; v.x*v.x+v.y*v.y+v.z*v.z

	fld	dword [AReg+12]		; v.w
	fld	st0
	fmulp	st1,st0			; v.w*v.w
	faddp	st1,st0			; v.x*v.x+v.y*v.y+v.z*v.z+v.w*v.w

	fsqrt				; sqrtf(sum(sqr(v)))

	fstp	dword [DReg]

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4CrossAsm
;;;
;;; Call Stack
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; vec4 = cross(const vec4* u,const vec4* v)
;;;
;;; return vec4(u.y * v.z - v.y * u.z, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x)
;;;
;;; extern "C" void Vec4CrossAsm(vec4* r,const vec4* u,const vec4* v)
;;; 

_Vec4CrossAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *u
	mov	BReg,[STACK_PTR3]		; *v
	mov	DReg,[STACK_PTR1]		; *r

	movaps	xmm0,[AReg]			; u
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]			; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)	; u_zxy
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)	; u_yzx
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; v_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; v_zxy

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movaps	[DReg],xmm1

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4CrossBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4CrossBlockAsm(vec4* ru,const vec4* v,const int32_iCount)
;;;

_Vec4CrossBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec4CrossBlockLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movaps	[AReg],xmm1

	add	AReg,Vec4Size
	add	BReg,Vec4Size

	dec	ecx
	jnz	Vec4CrossBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4CrossBlockUseSizeAsm
;;;
;;; Call Stack
;;; 
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4CrossBlockUseSizeAsm(void*         ru,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Vec4CrossBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec4CrossBlockUseSizeLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movaps	[AReg],xmm1

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4CrossBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4BufCrossBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4BufCrossBufAsm(void*         r,
;;;                                    const int32_t iRSize,
;;;                                    const void*   u,
;;;                                    const int32_t iUSize,
;;;                                    const void*   v,
;;;                                    const int32_t iVSize,
;;;                                    const int32_t iCount);
;;;

_Vec4BufCrossBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec4BufCrossBufLoop:

	movaps	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movaps	[DReg],xmm1

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4BufCrossBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Vec4uCrossAsm
;;;
;;; Call Stack
;;; [3] vec4* v
;;; [2] vec4* u
;;; [1] vec4* r
;;;
;;; vec4 = cross(const vec4* u,const vec4* v)
;;;
;;; return vec4(u.y * v.z - v.y * u.z, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x)
;;;
;;; extern "C" void Vec4uCrossAsm(vec4* r,const vec4* u,const vec4* v)
;;; 

_Vec4uCrossAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *u
	mov	BReg,[STACK_PTR3]		; *v
	mov	DReg,[STACK_PTR1]		; *r

	movups	xmm0,[AReg]			; u
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]			; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)	; u_zxy
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)	; u_yzx
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; v_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; v_zxy

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movups	[DReg],xmm1

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uCrossBlockAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t iCount
;;; [2] vec4*   v
;;; [1] vec4*   ru
;;;
;;; extern "C" void Vec4uCrossBlockAsm(vec4* ru,const vec4* v,const int32_iCount)
;;;

_Vec4uCrossBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	ecx, [STACK_PTR3]	; iCount

Vec4uCrossBlockLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movups	[AReg],xmm1

	add	AReg,Vec4Size
	add	BReg,Vec4Size

	dec	ecx
	jnz	Vec4uCrossBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Vec4uCrossBlockUseSizeAsm
;;;
;;; Call Stack
;;; 
;;; [4] int32_t iCount
;;; [3] int32_t iSize
;;; [2] void*   v
;;; [1] void*   ru
;;;
;;; extern "C" void Vec4uCrossBlockUseSizeAsm(void*         ru,
;;;                                           const void*   v,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Vec4uCrossBlockUseSizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR1]	; *ru
	mov	BReg,[STACK_PTR2]	; *v
	mov	edx, [STACK_PTR3]	; iSize
	mov	ecx, [STACK_PTR4]	; iCount

Vec4uCrossBlockUseSizeLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movups	[AReg],xmm1

	add	AReg,edx		; *ru += iSize
	add	BReg,edx		; *v  += iSize

	dec	ecx
	jnz	Vec4uCrossBlockUseSizeLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Vec4uBufCrossBufAsm
;;;
;;; Call Stack
;;;
;;; [7] int32_t iCount
;;; [6] int32_t iVSize
;;; [5] void*   v
;;; [4] int32_t iUSize
;;; [3] void*   u
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Vec4uBufCrossBufAsm(void*         r,
;;;                                     const int32_t iRSize,
;;;                                     const void*   u,
;;;                                     const int32_t iUSize,
;;;                                     const void*   v,
;;;                                     const int32_t iVSize,
;;;                                     const int32_t iCount);
;;;

_Vec4uBufCrossBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp
	mov	[STACK_SAVE7],BPtr

	mov	DReg,[STACK_PTR1]	; *r
	mov	edi, [STACK_PTR2]	; iRSize
	mov	AReg,[STACK_PTR3]	; *u
	mov	esi, [STACK_PTR4]	; iUSize
	mov	BReg,[STACK_PTR5]	; *v
	mov	ebp, [STACK_PTR6]	; iVSize
	mov	ecx, [STACK_PTR7]	; iCount

Vec4uBufCrossBufLoop:

	movups	xmm0,[AReg]		; u
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)

	mulps	xmm1,xmm3
	mulps	xmm0,xmm2
	subps	xmm1,xmm0

	movups	[DReg],xmm1

	add	AReg,esi		; *u += iUSize
	add	BReg,edi		; *v += iVSize
	add	DReg,ebp		; *r += iRSize

	dec	ecx
	jnz	Vec4uBufCrossBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]
	mov	BPtr,[STACK_SAVE7]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat2NegateAsm
;;;
;;; Call Stack
;;;
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; mat2 = -mat2
;;;
;;; extern "C" void Mat2NegateAsm(mat2& r,const mat2& m)
;;;

_Mat2NegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; m
	mulps	xmm0,[negVec]		; -m
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat2AddAsm
;;;
;;; Call Stack
;;;
;;; [3] mat2* n
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; mat2 = mat2 + mat2
;;;
;;; extern "C" void Mat2AddAsm(mat2& r,const mat2& m,const mat2& n)
;;; 

_Mat2AddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; m
	addps	xmm0,[BReg]		; m+n
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat2AddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat2* m
;;; [1] mat2* r
;;;
;;; extern "C" void Mat2AttFloatAsm(mat2* r,const mat2* m,const float s)
;;;

_Mat2AddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0
	addps	xmm0,[AReg]		; m+s
	movaps	[DReg],xmm0		; r

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat2SubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] mat2* n
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; mat2 = mat2 - mat2
;;;
;;; extern "C" void Mat2SubtractAsm(mat2& r,const mat2& m,const mat2& n)
;;; 

_Mat2SubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; m
	subps	xmm0,[BReg]		; m - n
	movaps	[DReg],xmm0

	mov	AReg,[STACK_PTR1]
	mov	BReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR3]

	ret

;;;
;;; Mat2SubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat2* m
;;; [1] mat2* r
;;; 
;;; extern "C" void Mat2SubtractFloatAsm(mat2* r,const mat2* m,const float s);
;;;

_Mat2SubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movaps	xmm0,[AReg]		; m
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	subps	xmm0,xmm1		; m-s
	movaps	[DReg],xmm0		; r

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat2MultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] mat2* n
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; mat2 = mat2 * mat2
;;;
;;; extern "C" void Mat2MultiplyAsm(mat2& r,const mat2& m,const mat2& n)
;;; 

_Mat2MultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n

	movaps	xmm0,[AReg]		; m
	movaps	xmm1,xmm0
	movaps	xmm2,[BReg]		; n
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(0,0,2,2)
	shufps	xmm1,xmm1,SHUFFLE(1,1,3,3)
	shufps	xmm2,xmm2,SHUFFLE(0,1,0,1)
	shufps	xmm3,xmm3,SHUFFLE(2,3,2,3)

	mulps	xmm0,xmm2
	mulps	xmm1,xmm3
	addps	xmm0,xmm1

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat2MultiplyVecAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2* v
;;; [2] mat2* m
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 = mat2 * vec2
;;;
;;; extern "C" void Mat2MultiplyVecAsm(vec2& r,const mat2& m,const vec2& v)
;;; 

_Mat2MultiplyVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; m
	movaps	xmm1,xmm0

	movhps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(0,2,0,0)	; m00, m10, xx, xx
	shufps	xmm1,xmm1,SHUFFLE(1,3,0,0)	; m01, m11, xx, xx
	shufps	xmm2,xmm2,SHUFFLE(2,2,0,0)	; v.x, v.x, xx, xx
	shufps	xmm3,xmm3,SHUFFLE(3,3,0,0)	; v.y, v.y, xx, xx

	mulps	xmm0,xmm2		; m00*v.x, m10*v.x
	mulps	xmm1,xmm3		; m01*v.y, m11*v.y
	addps	xmm0,xmm1		; m00*v.x+m01*v.y, m10*v.x+m11*v.y

	movlps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat2MultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float x
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; extern "C" void Mat2MultiplyFloatAsm(mat2& r,const mat2& m,const float x)
;;;

_Mat2MultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	; x
	shufps	xmm0,xmm0,0
	mulps	xmm0,[AReg]		; m*x

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat2IdentityAsm
;;;
;;; Call Stack
;;;
;;; [1] mat2* r
;;; [0] ret
;;;
;;; extern "C" void Mat2IdentityAsm(mat2& r)
;;;

_Mat2IdentityAsm:

	mov	[STACK_SAVE1],AReg

	mov	AReg,[STACK_PTR1]
	movaps	xmm0,[mat2Identity]
	movaps	[AReg],xmm0

	mov	AReg,[STACK_SAVE1]

	ret

;;;
;;; Mat2TransposeAsm
;;;
;;; Call Stack
;;;
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; extern "C" void Mat2TransposeAsm(mat2& r,const mat2& m)
;;;

_Mat2TransposeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; m
	shufps	xmm0,xmm0,SHUFFLE(0,2,1,3)
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat2MultiplyVecBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t nCount
;;; [3] vec2*   v
;;; [2] mat2*   m
;;; [1] vec2*   r
;;; [0] ret
;;;
;;; vec2 = mat2 * vec2
;;;
;;; extern "C" void Mat2MultiplyVecBlockAsm(vec2& r,const mat2& m,const vec2& v,int32_t nCount)
;;; 

_Mat2MultiplyVecBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ecx,[STACK_PTR4]	;  nCount

	movaps	xmm0,[AReg]		; m
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,2,0,0)	; m00, m10, xx, xx
	shufps	xmm1,xmm1,SHUFFLE(1,3,0,0)	; m01, m11, xx, xx

Mat2MultiplyVecBlockLoop:

	movhps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm2,xmm2,SHUFFLE(2,2,0,0)	; v.x, v.x, xx, xx
	shufps	xmm3,xmm3,SHUFFLE(3,3,0,0)	; v.y, v.y, xx, xx

	mulps	xmm2,xmm0		; m00*v.x, m10*v.x
	mulps	xmm3,xmm1		; m01*v.y, m11*v.y
	addps	xmm2,xmm3		; m00*v.x+m01*v.y, m10*v.x+m11*v.y

	movlps	[DReg],xmm2

	add	BReg,8
	add	DReg,8

	dec	ecx
	jnz	Mat2MultiplyVecBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat2uNegateAsm
;;;
;;; Call Stack
;;;
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; mat2 = -mat2
;;;
;;; extern "C" void Mat2uNegateAsm(mat2& r,const mat2& m)
;;;

_Mat2uNegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; m
	mulps	xmm0,[negVec]		; -m
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat2uAddAsm
;;;
;;; Call Stack
;;;
;;; [3] mat2* n
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; mat2 = mat2 + mat2
;;;
;;; extern "C" void Mat2uAddAsm(mat2& r,const mat2& m,const mat2& n)
;;; 

_Mat2uAddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; m
	movups	xmm1,[BReg]		; n
	addps	xmm0,xmm1		; m+n
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat2uAddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat2* m
;;; [1] mat2* r
;;;
;;; extern "C" void Mat2uAddFloatAsm(mat2* r,const mat2* m,const float s);
;;;

_Mat2uAddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movups	xmm0,[AReg]		; m
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	addps	xmm0,xmm1		; m+s
	movups	[DReg],xmm0		; r

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE1]

	ret

;;;
;;; Mat2uSubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] mat2* n
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; mat2 = mat2 - mat2
;;;
;;; extern "C" void Mat2uSubtractAsm(mat2& r,const mat2& m,const mat2& n)
;;; 

_Mat2uSubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; m
	movups	xmm1,[BReg]		; n
	subps	xmm0,xmm1		; m - n
	movups	[DReg],xmm0

	mov	AReg,[STACK_PTR1]
	mov	BReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR3]

	ret

;;;
;;; Mat2uSubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat2* m
;;; [1] mat2* r
;;;
;;; extern "C" void Mat2uSubtractFloatAsm(mat2* r,const mat2* m,const float s);
;;;

_Mat2uSubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movups	xmm0,[AReg]		; m
	movss	xmm1,[STACK_PTR3]	; s
	shufps	xmm1,xmm1,0
	subps	xmm0,xmm1		; m-s
	movups	[DReg],xmm0		; r

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]

	ret

;;;
;;; Mat2uMultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] mat2* n
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; mat2 = mat2 * mat2
;;;
;;; extern "C" void Mat2uMultiplyAsm(mat2& r,const mat2& m,const mat2& n)
;;; 

_Mat2uMultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n

	movups	xmm0,[AReg]		; m
	movaps	xmm1,xmm0
	movups	xmm2,[BReg]		; n
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(0,0,2,2)
	shufps	xmm1,xmm1,SHUFFLE(1,1,3,3)
	shufps	xmm2,xmm2,SHUFFLE(0,1,0,1)
	shufps	xmm3,xmm3,SHUFFLE(2,3,2,3)

	mulps	xmm0,xmm2
	mulps	xmm1,xmm3
	addps	xmm0,xmm1

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat2uMultiplyVecAsm
;;;
;;; Call Stack
;;;
;;; [3] vec2* v
;;; [2] mat2* m
;;; [1] vec2* r
;;; [0] ret
;;;
;;; vec2 = mat2 * vec2
;;;
;;; extern "C" void Mat2uMultiplyVecAsm(vec2& r,const mat2& m,const vec2& v)
;;; 

_Mat2uMultiplyVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; m
	movaps	xmm1,xmm0

	movhps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm0,xmm0,SHUFFLE(0,2,0,0)	; m00, m10, xx, xx
	shufps	xmm1,xmm1,SHUFFLE(1,3,0,0)	; m01, m11, xx, xx
	shufps	xmm2,xmm2,SHUFFLE(2,2,0,0)	; v.x, v.x, xx, xx
	shufps	xmm3,xmm3,SHUFFLE(3,3,0,0)	; v.y, v.y, xx, xx

	mulps	xmm0,xmm2		; m00*v.x, m10*v.x
	mulps	xmm1,xmm3		; m01*v.y, m11*v.y
	addps	xmm0,xmm1		; m00*v.x+m01*v.y, m10*v.x+m11*v.y

	movlps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat2uMultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float x
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; extern "C" void Mat2uMultiplyFloatAsm(mat2& r,const mat2& m,const float x)
;;;

_Mat2uMultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	; x
	shufps	xmm0,xmm0,0
	movups	xmm1,[AReg]		; m
	mulps	xmm0,xmm1		; m*x

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat2uIdentityAsm
;;;
;;; Call Stack
;;;
;;; [1] mat2* r
;;; [0] ret
;;;
;;; extern "C" void Mat2uIdentityAsm(mat2& r)
;;;

_Mat2uIdentityAsm:

	mov	[STACK_SAVE1],AReg

	mov	AReg,[STACK_PTR1]
	movaps	xmm0,[mat2Identity]
	movups	[AReg],xmm0

	mov	AReg,[STACK_SAVE1]

	ret

;;;
;;; Mat2uTransposeAsm
;;;
;;; Call Stack
;;;
;;; [2] mat2* m
;;; [1] mat2* r
;;; [0] ret
;;;
;;; extern "C" void Mat2uTransposeAsm(mat2& r,const mat2& m)
;;;

_Mat2uTransposeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; m
	shufps	xmm0,xmm0,SHUFFLE(0,2,1,3)
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat2uMultiplyVecBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t nCount
;;; [3] vec2*   v
;;; [2] mat2*   m
;;; [1] vec2*   r
;;; [0] ret
;;;
;;; vec2 = mat2 * vec2
;;;
;;; extern "C" void Mat2uMultiplyVecBlockAsm(vec2& r,const mat2& m,const vec2& v,int32_t nCount)
;;; 

_Mat2uMultiplyVecBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *v
	mov	DReg,[STACK_PTR1]	; *r

	mov	ecx,[STACK_PTR4]	;  nCount

	movups	xmm0,[AReg]		; m
	movaps	xmm1,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,2,0,0)	; m00, m10, xx, xx
	shufps	xmm1,xmm1,SHUFFLE(1,3,0,0)	; m01, m11, xx, xx

Mat2uMultiplyVecBlockLoop:

	movhps	xmm2,[BReg]		; v
	movaps	xmm3,xmm2

	shufps	xmm2,xmm2,SHUFFLE(2,2,0,0)	; v.x, v.x, xx, xx
	shufps	xmm3,xmm3,SHUFFLE(3,3,0,0)	; v.y, v.y, xx, xx

	mulps	xmm2,xmm0		; m00*v.x, m10*v.x
	mulps	xmm3,xmm1		; m01*v.y, m11*v.y
	addps	xmm2,xmm3		; m00*v.x+m01*v.y, m10*v.x+m11*v.y

	movlps	[DReg],xmm2

	add	BReg,8
	add	DReg,8

	dec	ecx
	jnz	Mat2uMultiplyVecBlockLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

%endif

;;;
;;; Mat2RotateLHAsm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat2* r
;;;
;;; extern "C" void Mat2RotateLHAsm(mat2* r,const float angle)
;;;

_Mat2RotateLHAsm:

	mov	[STACK_SAVE1],AReg
	mov	AReg,[STACK_PTR1]

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [AReg]		; cosx
	fstp	dword [AReg+12]

	fst	dword [AReg+4]		; sinx
	fchs
	fstp	dword [AReg+8]		; -sinx

	fnclex

	fwait

	mov	AReg,[STACK_SAVE1]

	ret

;;;
;;; Mat2RotateRHAsm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat2* r
;;;
;;; extern "C" void Mat2RotateRHAsm(mat2* r,const float angle)
;;;

_Mat2RotateRHAsm:

	mov	[STACK_SAVE1],AReg
	mov	AReg,[STACK_PTR1]

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [AReg]		; cosx
	fstp	dword [AReg+12]

	fst	dword [AReg+8]		; sinx
	fchs
	fstp	dword [AReg+4]		; -sinx

	fnclex

	fwait

	mov	AReg,[STACK_SAVE1]

	ret

;;;
;;; Mat2RotateAsm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat2* r
;;; [0] ret
;;;
;;; extern "C" void Mat2RotateAsm(mat2* r,const float angle)
;;; 

_Mat2RotateAsm:

	mov	[STACK_SAVE1],AReg
	mov	AReg,[STACK_PTR1]

	fld	dword [STACK_PTR2]
	fsincos

	fld	st0
	fstp	dword [AReg]		; cos
	fstp	dword [AReg+12]

	fld	st0
	fchs
	fstp	dword [AReg+4]		; sin
	fstp	dword [AReg+8]

	fnclex

	mov	AReg,[STACK_SAVE1]

	ret

;;;
;;; Mat2ScaleAsm
;;;
;;; Call Stack
;;;
;;; [3] float y-scale
;;; [2] float x-scale
;;; [1] mat2* r
;;; [0] ret
;;;
;;; extern "C" void Mat2ScaleAsm(mat2& r,const float x_scale,const float y_scale)
;;;

_Mat2ScaleAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; mat2* m

	mov	eax,[STACK_PTR2]
	mov	[DReg],eax

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax

	mov	eax,[STACK_PTR3]
	mov	[DReg+12],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3CopyAsm
;;;
;;; Call Stack
;;;
;;; [2] mat3* m
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3CopyAsm(mat3* r,const mat3* m);
;;;

_Mat3CopyAsm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],Srcp
	mov	[STACK_SAVE3],Dstp

	mov	CReg,12
	mov	Dstp,[STACK_PTR1]
	mov	Srcp,[STACK_PTR2]
	cld

	rep	movsd

	mov	CReg,[STACK_SAVE1]
	mov	Srcp,[STACK_SAVE2]
	mov	Dstp,[STACK_SAVE3]

	ret

;;;
;;; Mat3IdentityAsm
;;;
;;; Call Stack
;;;
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3IdentityAsm(mat3& r)
;;;

_Mat3IdentityAsm:

	mov	[STACK_SAVE1],Srcp
	mov	[STACK_SAVE2],Dstp
	mov	[STACK_SAVE3],CReg

	mov	Srcp,mat3Identity
	mov	Dstp,[STACK_PTR1]
	mov	ecx,12
	cld
	rep	movsd

	mov	Srcp,[STACK_SAVE1]
	mov	Dstp,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat3NegateAsm
;;;
;;; Call Stack
;;;
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3NegateAsm(mat3& r,const mat3& m)
;;;

_Mat3NegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		;  m00  m01  m02  m03
	movaps	xmm1,[AReg+16]		;  m10  m11  m12  m13
	movaps	xmm2,[AReg+32]		;  m20  m21  m22  m23
	movaps	xmm3,[negVec]		; -1.0 -1.0 -1.0 -1.0

	mulps	xmm0,xmm3
	mulps	xmm1,xmm3
	mulps	xmm2,xmm3

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2

	mov	eax, [zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3AddAsm
;;;
;;; Call Stack
;;;
;;; [3] mat3* n
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3AddAsm(mat3& r,const mat3& m,const mat3& n)
;;;

_Mat3AddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; m00 m01 m02 m03
	movaps	xmm1,[AReg+16]		; m10 m11 m12 m13
	movaps	xmm2,[AReg+32]		; m20 m21 m22 m23
	
	addps	xmm0,[BReg]		; m00+n00,m01+n01,m02+n02,m03+n03
	addps	xmm1,[BReg+16]		; m10+n10,m11+n11,m12+n12,m13+n13
	addps	xmm2,[BReg+32]		; m20+n20,m21+n21,m22+n22,m23+n23

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3AddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat3* m
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3AddFloatAsm(mat3* r,const mat3* m,const float s);
;;;

_Mat3AddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movaps	xmm1,[AReg]
	movaps	xmm2,[AReg+16]
	movaps	xmm3,[AReg+32]

	addps	xmm1,xmm0
	addps	xmm2,xmm0
	addps	xmm3,xmm0

	movaps	[DReg],xmm1
	movaps	[DReg+16],xmm2
	movaps	[DReg+32],xmm3

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3SubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] mat3* n
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3SubtractAsm(mat3& r,const mat3& m,const mat3& n);
;;;

_Mat3SubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n

	movaps	xmm0,[AReg]		; m00 m01 m02 m03
	movaps	xmm1,[AReg+16]		; m10 m11 m12 m13
	movaps	xmm2,[AReg+32]		; m20 m21 m22 m23

	subps	xmm0,[BReg]		; m00-n00 m01-n01 m02-n02 m03-n03
	subps	xmm1,[BReg+16]		; m10-n10 m11-n11 m12-n12 m03-n03
	subps	xmm2,[BReg+32]		; m20-n20 m21-n21 m22-n22 m23-n23

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3SubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat3* m
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3SubtractFloatAsm(mat3* r,const mat3* m,const float s);
;;;

_Mat3SubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movaps	xmm1,[AReg]
	movaps	xmm2,[AReg+16]
	movaps	xmm3,[AReg+32]

	subps	xmm1,xmm0
	subps	xmm2,xmm0
	subps	xmm3,xmm0

	movaps	[DReg],xmm1
	movaps	[DReg+16],xmm2
	movaps	[DReg+32],xmm3

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3MultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] mat3* n
;;; [2] mat3* m
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3MultiplyAsm(mat3& r,const mat3& m,const mat3& n)
;;;

_Mat3MultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *m
	mov	BReg,[STACK_PTR3]		; *n

	movaps	xmm3,[BReg]			; n00 n01 n02
	movaps	xmm4,[BReg+16]			; n10 n11 n12
	movaps	xmm5,[BReg+32]			; n20 n21 n22

	movaps	xmm0,[AReg]			; m00 m01 m02
	movaps	xmm1,xmm0			; m00 m01 m02
	movaps	xmm2,xmm0			; m00 m01 m02

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m00 m00 m00
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m01 m01 m01
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m02 m02 m02

	mulps	xmm0,xmm3			; m00*n00 m00*n01 m00*n02
	mulps	xmm1,xmm4			; m01*n10 m01*n11 m01*n12
	mulps	xmm2,xmm5			; m02*n20 m02*n21 m02*n22

	addps	xmm0,xmm1			; [0] m00*n00 + m01*n10 + m02*n20
						; [1] m01*n01 + m01*n11 + n02*n21
	addps	xmm0,xmm2			; [2] m00*n02 + m01*n12 + m02*n22

	movaps	[DReg],xmm0

	movaps	xmm0,[AReg+16]			; m10 m11 m12
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m10 m10 m10
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m11 m11 m11
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m12 m12 m12

	mulps	xmm0,xmm3			; m10*n00 m10*n01 m10*n02
	mulps	xmm1,xmm4			; m11*n10 m11*n11 m11*n12
	mulps	xmm2,xmm5			; m12*n20 m12*n21 m12*n22

	addps	xmm0,xmm1			; [0] m10*n00 + m11*n10 + m12*n20
						; [1] m10*n01 + m11*n11 + m12*n21
	addps	xmm0,xmm2			; [2] m10*n02 + m11*n12 + m12*n22

	movaps	[DReg+16],xmm0

	movaps	xmm0,[AReg+32]			; m20 m21 m22
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m20 m20 m20 m20
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m21 m21 m21 m21
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m22 m22 m22 m22

	mulps	xmm0,xmm3			; m20*n00 m20*n01 m20*n02
	mulps	xmm1,xmm4			; m21*n10 m21*n11 m21*n12
	mulps	xmm2,xmm5			; m22*n20 m22*n21 m22*n22

	addps	xmm0,xmm1			; [0] m20*n00 + m21*n10 + m22*n20
						; [1] m20*n01 + m21*n11 + m22*n21
	addps	xmm0,xmm2			; [2] m20*n02 + m21*n12 + m22*n22

	movaps	[DReg+32],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3MultiplyIdentityByBlocksAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] mat3*   m
;;; [1] mat3*   r
;;; [0] ret
;;;
;;; extern "C" void Mat3MultiplyIdentityByBlocksAsm(mat3& r,const mat3& m,int32_t nCount)
;;;

_Mat3MultiplyIdentityByBlocksAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	CReg,12
	mov	Srcp,mat3Identity
	mov	Dstp,DReg
	cld
	rep	movsd

	mov	AReg,[STACK_PTR2]
	mov	ecx, [STACK_PTR3]

Mat3MulIdentByBlkLoop:

	mov	BReg,[AReg]

	movaps	xmm0,[DReg]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m00 m00 m00 m00
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m01 m01 m01 m01
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m02 m02 m02 m02

	movaps	xmm3,[BReg]			; n00 n01 n02
	movaps	xmm4,[BReg+16]			; n10 n11 n12
	movaps	xmm5,[BReg+32]			; n20 n21 n22

	mulps	xmm0,xmm3			; m00*n00 m00*n01 m00*n02
	mulps	xmm1,xmm4			; m01*n10 m01*n11 m01*n12
	mulps	xmm2,xmm5			; m02*n20 m02*n21 m02*n22

	addps	xmm0,xmm1			; [0] m00*n00 + m02*n10 + m02*n20
						; [1] m00*n01 + m01*n11 + m02*n21
	addps	xmm0,xmm2			; [2] m00*n02 + m01*n12 + m02*n22
	movaps	[DReg],xmm0

	movaps	xmm0,[DReg+16]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)

	mulps	xmm0,xmm3
	mulps	xmm1,xmm4
	mulps	xmm2,xmm5

	addps	xmm0,xmm1
	addps	xmm0,xmm2

	movaps	[DReg+16],xmm0

	movaps	xmm0,[DReg+32]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)

	mulps	xmm0,xmm3
	mulps	xmm1,xmm4
	mulps	xmm2,xmm5

	addps	xmm0,xmm1
	addps	xmm0,xmm2

	movaps	[DReg+32],xmm0

	add	AReg,PtrSize

	dec	ecx
	jnz	Mat3MulIdentByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;;
;;; Mat3MultiplyVecAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] mat3* m
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3MultiplyVecAsm(vec3& r,const mat3& m,const vec3& v)
;;;

_Mat3MultiplyVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *m
	mov	BReg,[STACK_PTR3]		; *n
	mov	DReg,[STACK_PTR1]		; *r

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 m21
	movlps	xmm2,[zeroVec]			; 0.0 0.0 m20 m21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 0.0
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,0)	; m01 m11 m21 0.0

	movhps	xmm2,[AReg+8]			; xxx xxx m02 xxx
	movlps	xmm2,[AReg+24]			; m12 xxx m02 xxx
	movhps	xmm3,[AReg+40]			; xxx xxx m22 xxx
	movlps	xmm3,[zeroVec]			; 0.0 0.0 m22 xxx

	shufps	xmm2,xmm3,SHUFFLE(2,0,2,0)	; m02 m12 m22 0.0

	movss	xmm3,[BReg]			; v.x
	shufps	xmm3,xmm3,0

	movss	xmm4,[BReg+4]			; v.y
	shufps	xmm4,xmm4,0

	movss	xmm5,[BReg+8]			; v.z
	shufps	xmm5,xmm5,0

	mulps	xmm0,xmm3
	mulps	xmm1,xmm4
	mulps	xmm2,xmm5

	addps	xmm0,xmm1
	addps	xmm0,xmm2

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3MultiplyVecBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t nCount
;;; [3] vec3*   v
;;; [2] mat3*   m
;;; [1] vec3*   r
;;; [0] ret
;;;
;;; extern "C" void Mat3MultiplyVecBlockAsm(vec3& r,const mat3& m,const vec3& v,int32_t nCount)
;;;

_Mat3MultiplyVecBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]		; *m
	mov	BReg,[STACK_PTR3]		; *n
	mov	DReg,[STACK_PTR1]		; *r

	mov	ecx,[STACK_PTR4]		; nCount

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 m21
	movlps	xmm2,[zeroVec]			; 0.0 0.0 m20 m21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 0.0
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,0)	; m01 m11 m21 0.0

	movhps	xmm2,[AReg+8]			; xxx xxx m02 xxx
	movlps	xmm2,[AReg+24]			; m12 xxx m02 xxx
	movhps	xmm3,[AReg+40]			; xxx xxx m22 xxx
	movlps	xmm3,[zeroVec]			; 0.0 0.0 m22 xxx

	shufps	xmm2,xmm3,SHUFFLE(2,0,2,0)	; m02 m12 m22 0.0

Mat3MultiplyVecLoop:

	movss	xmm3,[BReg]			; v.x
	shufps	xmm3,xmm3,0

	movss	xmm4,[BReg+4]			; v.y
	shufps	xmm4,xmm4,0

	movss	xmm5,[BReg+8]			; v.z
	shufps	xmm5,xmm5,0

	mulps	xmm3,xmm0
	mulps	xmm4,xmm1
	mulps	xmm5,xmm2

	addps	xmm3,xmm4
	addps	xmm3,xmm5

	movaps	[DReg],xmm3

	add	BReg,Vec3Size
	add	DReg,Vec3Size

	dec	ecx
	jnz	Mat3MultiplyVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Mat3MulVecBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] mat3*   m
;;; [1] void*   r
;;;
;;; extern "C" void Mat3MulVecBlockBySizeAsm(void*         r,
;;;                                          const mat3*   m,
;;;                                          const void*   v,
;;;                                          const int32_t iSize,
;;;                                          const int32_t iCount);
;;;

_Mat3MulVecBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *m
	mov	BReg,[STACK_PTR3]		; *v
	mov	esi, [STACK_PTR4]		; iSize
	mov	ecx, [STACK_PTR5]		; iCount

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 m21
	movlps	xmm2,[zeroVec]			; 0.0 0.0 m20 m21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 0.0
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,0)	; m01 m11 m21 0.0

	movhps	xmm2,[AReg+8]			; xxx xxx m02 xxx
	movlps	xmm2,[AReg+24]			; m12 xxx m02 xxx
	movhps	xmm3,[AReg+40]			; xxx xxx m22 xxx
	movlps	xmm3,[zeroVec]			; 0.0 0.0 m22 xxx

	shufps	xmm2,xmm3,SHUFFLE(2,0,2,0)	; m02 m12 m22 0.0

Mat3MulVecBlockSzLoop:

	movss	xmm3,[BReg]			; v.x
	movss	xmm4,[BReg+4]			; v.y
	movss	xmm5,[BReg+8]			; v.z
	shufps	xmm3,xmm3,0
	shufps	xmm4,xmm4,0
	shufps	xmm5,xmm5,0

	mulps	xmm3,xmm0
	mulps	xmm4,xmm1
	mulps	xmm5,xmm2

	addps	xmm3,xmm4
	addps	xmm3,xmm5

	movaps	[DReg],xmm3

	add	BReg,esi			; *v += iSize
	add	DReg,esi			; *r += iSize

	dec	ecx
	jnz	Mat3MulVecBlockSzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Mat3MulVec3BufByBufAsm
;;;
;;; Call Stack
;;; [6] int32_t iCount
;;; [5] int32_t iVSize
;;; [4] void*   v
;;; [3] mat3*   m
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Mat3MulVec3BufByBufAsm(void*         r,
;;;                                        const int32_t iRSize,
;;;                                        const mat3*   m,
;;;                                        const void*   v,
;;;                                        const int32_t iVSize,
;;;                                        const int32_t iCount);
;;;

_Mat3MulVec3BufByBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]		; *r
	mov	edi, [STACK_PTR2]		; iRSize
	mov	AReg,[STACK_PTR3]		; *m
	mov	BReg,[STACK_PTR4]		; *v
	mov	esi, [STACK_PTR5]		; iVSize
	mov	ecx, [STACK_PTR6]		; iCount

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 xxx
	movlps	xmm2,[zeroVec]			; 0.0 0.0 m20 xxx

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 0.0
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,0)	; m01 m11 m21 0.0

	movhps	xmm2,[AReg+8]			; xxx xxx m02 xxx
	movlps	xmm2,[AReg+24]			; m12 xxx m02 xxx
	movhps	xmm3,[AReg+40]			; xxx xxx m22 xxx
	movlps	xmm3,[zeroVec]			; 0.0 0.0 m22 xxx

	shufps	xmm2,xmm3,SHUFFLE(2,0,2,0)	; m02 m12 m22 0.0

Mat3MulVec3BufByBufLoop:

	movss	xmm3,[BReg]			; v.x
	movss	xmm4,[BReg+4]			; v.y
	movss	xmm5,[BReg+8]			; v.z
	shufps	xmm3,xmm3,0
	shufps	xmm4,xmm4,0
	shufps	xmm5,xmm5,0

	mulps	xmm3,xmm0
	mulps	xmm4,xmm1
	mulps	xmm5,xmm2

	addps	xmm3,xmm4
	addps	xmm3,xmm5

	movaps	[DReg],xmm3

	add	BReg,esi			; *v += iVSize
	add	DReg,edi			; *r += iRSize

	dec	ecx
	jnz	Mat3MulVec3BufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;; 
;;; Mat3MultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float x
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3MultiplyFloatAsm(mat3& r,const mat3& m,const float x)
;;;

_Mat3MultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	;  x
	shufps	xmm0,xmm0,0

	movaps	xmm1,[AReg]		; m00 m01 m02 xxx
	movaps	xmm2,[AReg+16]		; m10 m11 m12 xxx
	movaps	xmm3,[AReg+32]		; m20 m21 m22 xxx

	mulps	xmm1,xmm0
	mulps	xmm2,xmm0
	mulps	xmm3,xmm0

	movaps	[DReg],xmm1
	movaps	[DReg+16],xmm2
	movaps	[DReg+32],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3InverseAsm
;;;
;;; Call Stack
;;;
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3InverseAsm(mat3& r,const mat3& m);
;;;
;;; IMPLEMENTORS NOTE:	This one will blow chunks if m = r
;;;

_Mat3InverseAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR1]

	mov	ebx,[zeroVec]
	mov	dword [AReg+12],ebx
	mov	dword [AReg+28],ebx
	mov	dword [AReg+44],ebx

	movaps	xmm4,[AReg]			; m00 m01 m02 xxx
	movaps	xmm0,[AReg+16]			; m10 m11 m12 0.0
	movaps	xmm1,[AReg+32]			; m20 m21 m22 0.0

	shufps	xmm0,xmm0,SHUFFLE(1,2,0,3)	; m11 m12 m10 0.0
	shufps	xmm1,xmm1,SHUFFLE(2,0,1,3)	; m22 m20 m21 0.0

	movhps	xmm2,[AReg+16]			; xxx xxx m10 m11
	movlps	xmm2,[AReg+32]			; m20 m21 m10 m11
	movhps	xmm3,[AReg+24]			; xxx xxx m12 0.0

	shufps	xmm2,xmm2,SHUFFLE(1,2,3,0)	; m21 m10 m11 m20
	shufps	xmm3,xmm1,SHUFFLE(2,3,0,1)	; m12 0.0 m22 m20
	shufps	xmm3,xmm3,SHUFFLE(0,2,3,1)	; m12 m22 m20 0.0

	mulps	xmm0,xmm1			; m11*m22 m12*m20 m10*m21 0.0
	mulps	xmm2,xmm3			; m21*m12 m10*m22 m11*m20 0.0
	subps	xmm0,xmm2			; m11*m22-m21*m12 m12*m20-m10*m22 m10*m21-m11*m20 0.0

	;; xmm0 = p0 p1 p2

	mulps	xmm4,xmm0			; m00*p0 m01*p1 m02*p2 0.0
	movaps	xmm1,xmm4
	movaps	xmm2,xmm4

	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm2
	addss	xmm1,xmm4

	ucomiss	xmm1,[zeroVec]
	jne	Mat3InverseDB0ErrorCont
	jmp	Mat3InverseDB0Error

Mat3InverseDB0ErrorCont:

	rcpss	xmm1,xmm1			; invDet
	shufps	xmm1,xmm1,0
	movaps	[DReg],xmm0			; p0 p1 p2

	mov	ebx,[DReg+4]			; p1
	mov	[DReg+16],ebx

	mov	ebx,[DReg+8]			; p2
	mov	[DReg+32],ebx

	mov	ebx,[zeroVec]
	mov	[DReg+4], ebx
	mov	[DReg+8], ebx
	mov	[DReg+12],ebx
	mov	[DReg+20],ebx
	mov	[DReg+24],ebx
	mov	[DReg+28],ebx
	mov	[DReg+36],ebx
	mov	[DReg+40],ebx

	movaps	xmm0,[DReg]			; p0 0.0 0.0 0.0
	mov	[DReg],ebx			; [DReg]: 0.0 0.0 0.0 0.0

	mov	ebx,[AReg+36]			; m21
	mov	[DReg+4],ebx
	mov	ebx,[AReg+4]			; m01
	mov	[DReg+8],ebx
	movaps	xmm2,[DReg]			; 0.0 m21 m01 0.0

	mov	ebx,[AReg+8]			; m02
	mov	[DReg+4],ebx
	mov	ebx,[AReg+24]			; m12
	mov	[DReg+8],ebx
	movaps	xmm3,[DReg]			; 0.0 m02 m12 0.0

	mov	ebx,[AReg+4]			; m01
	mov	[DReg+4],ebx
	mov	ebx,[AReg+20]			; m11
	mov	[DReg+8],ebx
	movaps	xmm4,[DReg]			; 0.0 m01 m11 0.0

	mov	ebx,[AReg+40]			; m22
	mov	[DReg+4],ebx
	mov	ebx,[AReg+8]			; m02
	mov	[DReg+8],ebx
	movaps	xmm5,[DReg]			; 0.0 m22 m02 0.0

	mulps	xmm2,xmm3			; 0.0 m21*m02 m01*m12 0.0
	mulps	xmm4,xmm5			; 0.0 m01*m22 m11*m02 0.0
	subps	xmm2,xmm4			; 0.0 m21*m02-m01*m22 m01*m12-m11*m02 0.0
	addps	xmm0,xmm2			; p0  m21*m02-m01*m22 m01*m12-m11*m02 0.0
	movaps	[DReg],xmm0

	movaps	xmm0,[DReg+16]			; p1 0.0 0.0 0.0
	mov	ebx,[zeroVec]
	mov	[DReg+16],ebx			; 0.0 0.0 0.0 0.0

	mov	ebx,[AReg]			; m00
	mov	[DReg+20],ebx
	mov	ebx,[AReg+16]			; m10
	mov	[DReg+24],ebx
	movaps	xmm2,[DReg+16]			; 0.0 m00 m10 0.0

	mov	ebx,[AReg+40]			; m22
	mov	[DReg+20],ebx
	mov	ebx,[AReg+8]			; m02
	mov	[DReg+24],ebx
	movaps	xmm3,[DReg+16]			; 0.0 m22 m02 0.0

	mov	ebx,[AReg+32]			; m20
	mov	[DReg+20],ebx
	mov	ebx,[AReg]			; m00
	mov	[DReg+24],ebx
	movaps	xmm4,[DReg+16]			; 0.0 m20 m00 0.0

	mov	ebx,[AReg+8]			; m02
	mov	[DReg+20],ebx
	mov	ebx,[AReg+24]			; m12
	mov	[DReg+24],ebx
	movaps	xmm5,[DReg+16]			; 0.0 m02 m12 0.0

	mulps	xmm2,xmm3			; 0.0 m00*m22 m10*m02 0.0
	mulps	xmm4,xmm5			; 0.0 m20*m02 m00*m12 0.0
	subps	xmm2,xmm4			; 0.0 m00*m22-m20*m02 m10*m02-m00*m12 0.0
	addps	xmm0,xmm2			; p1  m00*m22-m20*m02 m10*m02-m00*m12 0.0
	movaps	[DReg+16],xmm0

	movaps	xmm0,[DReg+32]			; p2 0.0 0.0 0.0
	mov	ebx,[zeroVec]
	mov	[DReg+32],ebx			; 0.0 0.0 0.0 0.0

	mov	ebx,[AReg+32]			; m20
	mov	[DReg+36],ebx
	mov	ebx,[AReg]			; m00
	mov	[DReg+40],ebx
	movaps	xmm2,[DReg+32]			; 0.0 m20 m00 0.0

	mov	ebx,[AReg+4]			; m01
	mov	[DReg+36],ebx
	mov	ebx,[AReg+20]			; m11
	mov	[DReg+40],ebx
	movaps	xmm3,[DReg+32]			; 0.0 m01 m11 0.0

	mov	ebx,[AReg]			; m00
	mov	[DReg+36],ebx
	mov	ebx,[AReg+4]			; m01
	mov	[DReg+40],ebx
	movaps	xmm4,[DReg+32]			; 0.0 m00 m01 0.0

	mov	ebx,[AReg+36]			; m21
	mov	[DReg+36],ebx
	mov	ebx,[AReg+16]			; m10
	mov	[DReg+40],ebx
	movaps	xmm5,[DReg+32]			; 0.0 m21 m10 0.0

	mulps	xmm2,xmm3			; 0.0 m20*m01 m00*m11 0.0
	mulps	xmm4,xmm5			; 0.0 m00*m21 m01*m10 0.0
	subps	xmm2,xmm4			; 0.0 m20*m01-m00*m21 m00*m11-m01*m10 0.0
	addps	xmm0,xmm2			; p2  m20*m01-m00*m21 m00*m11-m01*m10 0.0

	;; mat3 *= invDet

	mulps	xmm0,xmm1
	movaps	[DReg+32],xmm0

	movaps	xmm2,xmm1
	mulps	xmm1,[DReg]
	movaps	[DReg],xmm1
	mulps	xmm2,[DReg+16]
	movaps	[DReg+16],xmm2

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Mat3InverseDB0Error:

	mov	[STACK_SAVE4],CReg

	mov	ecx,12
	mov	ebx,[zeroVec]

Mat3InverseDB0ErrorLoop:

	mov	[DReg],ebx
	add	DReg,FloatSize
	dec	ecx
	jnz	Mat3InverseDB0ErrorLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	CReg,[STACK_SAVE4]

	ret

;;;
;;; Mat3TransposeAsm
;;;
;;; Call Stack
;;;
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3TransposeAsm(mat3& r,const mat3&m);
;;;

_Mat3TransposeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]		; *m
	mov	DReg,[STACK_PTR1]		; *r

	movlps	xmm0,[AReg]			; m00 m01 xxx xxx
	movhps	xmm0,[AReg+16]			; m00 m01 m10 m11
	movaps	xmm1,xmm0
	movlps	xmm2,[AReg+32]			; m20 m21 xxx xxx

	movlps	xmm3,[AReg+8]			; m02 xxx xxx xxx
	movhps	xmm3,[AReg+24]			; m02 xxx m12 xxx
	movlps	xmm4,[AReg+40]			; m22 xxx xxx xxx

	shufps	xmm0,xmm2,SHUFFLE(0,2,0,1)	; m00 m10 m20 m21
	shufps	xmm1,xmm2,SHUFFLE(1,3,1,0)	; m01 m11 m21 m20
	shufps	xmm3,xmm4,SHUFFLE(0,2,0,3)	; m02 m12 m22 xxx

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm3

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax

	ret

%endif	

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat3uNegateAsm
;;;
;;; Call Stack
;;;
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3uNegateAsm(mat3& r,const mat3& m)
;;;

_Mat3uNegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		;  m00  m01  m02  m03
	movups	xmm1,[AReg+16]		;  m10  m11  m12  m13
	movups	xmm2,[AReg+32]		;  m20  m21  m22  m23
	movups	xmm3,[negVec]		; -1.0 -1.0 -1.0 -1.0

	mulps	xmm0,xmm3
	mulps	xmm1,xmm3
	mulps	xmm2,xmm3

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3uAddAsm
;;;
;;; Call Stack
;;;
;;; [3] mat3* n
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3uAddAsm(mat3& r,const mat3& m,const mat3& n)
;;;

_Mat3uAddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; m00 m01 m02 m03
	movups	xmm1,[AReg+16]		; m10 m11 m12 m13
	movups	xmm2,[AReg+32]		; m20 m21 m22 m23

	movups	xmm3,[BReg]		; n00 n01 n02 n03
	movups	xmm4,[BReg+16]		; n10 n11 n12 n13
	movups	xmm5,[BReg+32]		; n20 n21 n22 n23

	addps	xmm0,xmm3		; m00+n00,m01+n01,m02+n02,m03+n03
	addps	xmm1,xmm4		; m10+n10,m11+n11,m12+n12,m13+n13
	addps	xmm2,xmm5		; m20+n20,m21+n21,m22+n22,m23+n23

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3uAddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat2* m
;;; [1] mat2* r
;;;
;;; extern "C" void Mat3uAddFloatAsm(mat3* r,const mat3* m,const float s);
;;;

_Mat3uAddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]
	shufps	xmm0,xmm0,0

	movups	xmm1,[AReg]
	movups	xmm2,[AReg+16]
	movups	xmm3,[AReg+32]

	addps	xmm1,xmm0
	addps	xmm2,xmm0
	addps	xmm3,xmm0

	movups	[DReg],xmm1
	movups	[DReg+16],xmm2
	movups	[DReg+32],xmm3

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3uSubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] mat3* n
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3uSubtractAsm(mat3& r,const mat3& m,const mat3& n);
;;;

_Mat3uSubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n

	movups	xmm0,[AReg]		; m00 m01 m02 m03
	movups	xmm1,[AReg+16]		; m10 m11 m12 m13
	movups	xmm2,[AReg+32]		; m20 m21 m22 m23

	movups	xmm3,[BReg]		; n00 n01 n02 n03
	movups	xmm4,[BReg+16]		; n10 n11 n12 n13
	movups	xmm5,[BReg+32]		; n20 n21 n22 n23

	subps	xmm0,xmm3		; m00-n00 m01-n01 m02-n02 m03-n03
	subps	xmm1,xmm4		; m10-n10 m11-n11 m12-n12 m03-n03
	subps	xmm2,xmm5		; m20-n20 m21-n21 m22-n22 m23-n23

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3uSubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat3* m
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3uSubtractFloatAsm(mat3* r,const mat3* m,const float s);
;;;

_Mat3uSubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movups	xmm1,[AReg]
	movups	xmm2,[AReg+16]
	movups	xmm3,[AReg+32]

	subps	xmm1,xmm0
	subps	xmm2,xmm0
	subps	xmm3,xmm0

	movups	[DReg],xmm1
	movups	[DReg+16],xmm2
	movups	[DReg+32],xmm3

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3uMultiplyAsm
;;;
;;; Call Stack
;;;
;;; [2] mat3* n
;;; [1] mat3* m
;;; [0] ret
;;;
;;; extern "C" void Mat3uMultiplyAsm(mat3& r,const mat3& m,const mat3& n)
;;;

_Mat3uMultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *m
	mov	BReg,[STACK_PTR3]		; *n

	movups	xmm3,[BReg]			; n00 n01 n02
	movups	xmm4,[BReg+16]			; n10 n11 n12
	movups	xmm5,[BReg+32]			; n20 n21 n22

	movups	xmm0,[AReg]			; m00 m01 m02
	movaps	xmm1,xmm0			; m00 m01 m02
	movaps	xmm2,xmm0			; m00 m01 m02

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m00 m00 m00
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m01 m01 m01
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m02 m02 m02

	mulps	xmm0,xmm3			; m00*n00 m00*n01 m00*n02
	mulps	xmm1,xmm4			; m01*n10 m01*n11 m01*n12
	mulps	xmm2,xmm5			; m02*n20 m02*n21 m02*n22

	addps	xmm0,xmm1			; [0] m00*n00 + m01*n10 + m02*n20
						; [1] m01*n01 + m01*n11 + n02*n21
	addps	xmm0,xmm2			; [2] m00*n02 + m01*n12 + m02*n22

	movups	[DReg],xmm0

	movups	xmm0,[AReg+16]			; m10 m11 m12
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m10 m10 m10
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m11 m11 m11
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m12 m12 m12

	mulps	xmm0,xmm3			; m10*n00 m10*n01 m10*n02
	mulps	xmm1,xmm4			; m11*n10 m11*n11 m11*n12
	mulps	xmm2,xmm5			; m12*n20 m12*n21 m12*n22

	addps	xmm0,xmm1			; [0] m10*n00 + m11*n10 + m12*n20
						; [1] m10*n01 + m11*n11 + m12*n21
	addps	xmm0,xmm2			; [2] m10*n02 + m11*n12 + m12*n22

	movups	[DReg+16],xmm0

	movups	xmm0,[AReg+32]			; m20 m21 m22
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m20 m20 m20 m20
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m21 m21 m21 m21
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m22 m22 m22 m22

	mulps	xmm0,xmm3			; m20*n00 m20*n01 m20*n02
	mulps	xmm1,xmm4			; m21*n10 m21*n11 m21*n12
	mulps	xmm2,xmm5			; m22*n20 m22*n21 m22*n22

	addps	xmm0,xmm1			; [0] m20*n00 + m21*n10 + m22*n20
						; [1] m20*n01 + m21*n11 + m22*n21
	addps	xmm0,xmm2			; [2] m20*n02 + m21*n12 + m22*n22

	movups	[DReg+32],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3uMultiplyIdentityByBlocksAsm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] mat3*   m
;;; [1] mat3*   r
;;; [0] ret
;;;
;;; extern "C" void Mat3uMultiplyIdentityByBlocksAsm(mat3& r,const mat3& m,int32_t nCount)
;;;

_Mat3uMultiplyIdentityByBlocksAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	CReg,12
	mov	Srcp,mat3Identity
	mov	Dstp,DReg
	cld
	rep	movsd

	mov	AReg,[STACK_PTR2]
	mov	ecx, [STACK_PTR3]

Mat3uMulIdentByBlkLoop:

	mov	BReg,[AReg]

	movups	xmm0,[DReg]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m00 m00 m00 m00
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m01 m01 m01 m01
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m02 m02 m02 m02

	movups	xmm3,[BReg]			; n00 n01 n02
	movups	xmm4,[BReg+16]			; n10 n11 n12
	movups	xmm5,[BReg+32]			; n20 n21 n22

	mulps	xmm0,xmm3			; m00*n00 m00*n01 m00*n02
	mulps	xmm1,xmm4			; m01*n10 m01*n11 m01*n12
	mulps	xmm2,xmm5			; m02*n20 m02*n21 m02*n22

	addps	xmm0,xmm1			; [0] m00*n00 + m02*n10 + m02*n20
						; [1] m00*n01 + m01*n11 + m02*n21
	addps	xmm0,xmm2			; [2] m00*n02 + m01*n12 + m02*n22
	movups	[DReg],xmm0

	movups	xmm0,[DReg+16]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)

	mulps	xmm0,xmm3
	mulps	xmm1,xmm4
	mulps	xmm2,xmm5

	addps	xmm0,xmm1
	addps	xmm0,xmm2

	movups	[DReg+16],xmm0

	movups	xmm0,[DReg+32]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)

	mulps	xmm0,xmm3
	mulps	xmm1,xmm4
	mulps	xmm2,xmm5

	addps	xmm0,xmm1
	addps	xmm0,xmm2

	movups	[DReg+32],xmm0

	add	AReg,PtrSize

	dec	ecx
	jnz	Mat3uMulIdentByBlkLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat3uMultiplyVecAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* v
;;; [2] mat3* m
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3uMultiplyVecAsm(vec3& r,const mat3& m,const vec3& v)
;;;

_Mat3uMultiplyVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *m
	mov	BReg,[STACK_PTR3]		; *n
	mov	DReg,[STACK_PTR1]		; *r

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 m21
	movlps	xmm2,[zeroVec]			; 0.0 0.0 m20 m21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 0.0
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,0)	; m01 m11 m21 0.0

	movhps	xmm2,[AReg+8]			; xxx xxx m02 xxx
	movlps	xmm2,[AReg+24]			; m12 xxx m02 xxx
	movhps	xmm3,[AReg+40]			; xxx xxx m22 xxx
	movlps	xmm3,[zeroVec]			; 0.0 0.0 m22 xxx

	shufps	xmm2,xmm3,SHUFFLE(2,0,2,0)	; m02 m12 m22 0.0

	movss	xmm3,[BReg]			; v.x
	shufps	xmm3,xmm3,0

	movss	xmm4,[BReg+4]			; v.y
	shufps	xmm4,xmm4,0

	movss	xmm5,[BReg+8]			; v.z
	shufps	xmm5,xmm5,0

	mulps	xmm0,xmm3
	mulps	xmm1,xmm4
	mulps	xmm2,xmm5

	addps	xmm0,xmm1
	addps	xmm0,xmm2

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3uMultiplyVecBlockAsm
;;;
;;; Call Stack
;;;
;;; [4] int32_t nCount
;;; [3] vec3*   v
;;; [2] mat3*   m
;;; [1] vec3*   r
;;; [0] ret
;;;
;;; extern "C" void Mat3uMultiplyVecBlockAsm(vec3& r,const mat3& m,const vec3& v,int32_t nCount)
;;;

_Mat3uMultiplyVecBlockAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]		; *m
	mov	BReg,[STACK_PTR3]		; *n
	mov	DReg,[STACK_PTR1]		; *r

	mov	ecx,[STACK_PTR4]		; nCount

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 m21
	movlps	xmm2,[zeroVec]			; 0.0 0.0 m20 m21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 0.0
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,0)	; m01 m11 m21 0.0

	movhps	xmm2,[AReg+8]			; xxx xxx m02 xxx
	movlps	xmm2,[AReg+24]			; m12 xxx m02 xxx
	movhps	xmm3,[AReg+40]			; xxx xxx m22 xxx
	movlps	xmm3,[zeroVec]			; 0.0 0.0 m22 xxx

	shufps	xmm2,xmm3,SHUFFLE(2,0,2,0)	; m02 m12 m22 0.0

Mat3uMultiplyVecLoop:

	movss	xmm3,[BReg]			; v.x
	shufps	xmm3,xmm3,0

	movss	xmm4,[BReg+4]			; v.y
	shufps	xmm4,xmm4,0

	movss	xmm5,[BReg+8]			; v.z
	shufps	xmm5,xmm5,0

	mulps	xmm3,xmm0
	mulps	xmm4,xmm1
	mulps	xmm5,xmm2

	addps	xmm3,xmm4
	addps	xmm3,xmm5

	movups	[DReg],xmm3

	add	BReg,Vec3Size
	add	DReg,Vec3Size

	dec	ecx
	jnz	Mat3uMultiplyVecLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Mat3uMulVecBlockBySizeAsm
;;;
;;; Call Stack
;;;
;;; [5] int32_t iCount
;;; [4] int32_t iSize
;;; [3] void*   v
;;; [2] mat3*   m
;;; [1] void*   r
;;;
;;; extern "C" void Mat3uMulVecBlockBySizeAsm(void*         r,
;;;                                           const mat3*   m,
;;;                                           const void*   v,
;;;                                           const int32_t iSize,
;;;                                           const int32_t iCount);
;;;

_Mat3uMulVecBlockBySizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *m
	mov	BReg,[STACK_PTR3]		; *v
	mov	esi, [STACK_PTR4]		; iSize
	mov	ecx, [STACK_PTR5]		; iCount

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 m21
	movlps	xmm2,[zeroVec]			; 0.0 0.0 m20 m21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 0.0
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,0)	; m01 m11 m21 0.0

	movhps	xmm2,[AReg+8]			; xxx xxx m02 xxx
	movlps	xmm2,[AReg+24]			; m12 xxx m02 xxx
	movhps	xmm3,[AReg+40]			; xxx xxx m22 xxx
	movlps	xmm3,[zeroVec]			; 0.0 0.0 m22 xxx

	shufps	xmm2,xmm3,SHUFFLE(2,0,2,0)	; m02 m12 m22 0.0

Mat3uMulVecBlockSzLoop:

	movss	xmm3,[BReg]			; v.x
	movss	xmm4,[BReg+4]			; v.y
	movss	xmm5,[BReg+8]			; v.z
	shufps	xmm3,xmm3,0
	shufps	xmm4,xmm4,0
	shufps	xmm5,xmm5,0

	mulps	xmm3,xmm0
	mulps	xmm4,xmm1
	mulps	xmm5,xmm2

	addps	xmm3,xmm4
	addps	xmm3,xmm5

	movups	[DReg],xmm3

	add	BReg,esi			; *v += iSize
	add	DReg,esi			; *r += iSize

	dec	ecx
	jnz	Mat3uMulVecBlockSzLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]

	ret

;;;
;;; Mat3uMulVec3BufByBufAsm
;;;
;;; Call Stack
;;; [6] int32_t iCount
;;; [5] int32_t iVSize
;;; [4] void*   v
;;; [3] mat3*   m
;;; [2] int32_t iRSize
;;; [1] void*   r
;;;
;;; extern "C" void Mat3uMulVec3BufByBufAsm(void*         r,
;;;                                         const int32_t iRSize,
;;;                                         const void*   v,
;;;                                         const mat3*   m,
;;;                                         const int32_t iRSize,
;;;                                         const void*   r);
;;;

_Mat3uMulVec3BufByBufAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]		; *r
	mov	edi, [STACK_PTR2]		; iRSize
	mov	AReg,[STACK_PTR3]		; *m
	mov	BReg,[STACK_PTR4]		; *v
	mov	esi, [STACK_PTR5]		; iVSize
	mov	ecx, [STACK_PTR6]		; iCount

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 xxx
	movlps	xmm2,[zeroVec]			; 0.0 0.0 m20 xxx

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 0.0
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,0)	; m01 m11 m21 0.0

	movhps	xmm2,[AReg+8]			; xxx xxx m02 xxx
	movlps	xmm2,[AReg+24]			; m12 xxx m02 xxx
	movhps	xmm3,[AReg+40]			; xxx xxx m22 xxx
	movlps	xmm3,[zeroVec]			; 0.0 0.0 m22 xxx

	shufps	xmm2,xmm3,SHUFFLE(2,0,2,0)	; m02 m12 m22 0.0

Mat3uMulVec3BufByBufLoop:

	movss	xmm3,[BReg]			; v.x
	movss	xmm4,[BReg+4]			; v.y
	movss	xmm5,[BReg+8]			; v.z
	shufps	xmm3,xmm3,0
	shufps	xmm4,xmm4,0
	shufps	xmm5,xmm5,0

	mulps	xmm3,xmm0
	mulps	xmm4,xmm1
	mulps	xmm5,xmm2

	addps	xmm3,xmm4
	addps	xmm3,xmm5

	movups	[DReg],xmm3

	add	BReg,esi			; *v += iVSize
	add	DReg,edi			; *r += iRSize

	dec	ecx
	jnz	Mat3uMulVec3BufByBufLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

;;; 
;;; Mat3uMultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float x
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3uMultiplyFloatAsm(mat3& r,const mat3& m,const float x)
;;;

_Mat3uMultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movss	xmm0,[STACK_PTR3]	;  x
	shufps	xmm0,xmm0,0

	movups	xmm1,[AReg]		; m00 m01 m02 xxx
	movups	xmm2,[AReg+16]		; m10 m11 m12 xxx
	movups	xmm3,[AReg+32]		; m20 m21 m22 xxx

	mulps	xmm1,xmm0
	mulps	xmm2,xmm0
	mulps	xmm3,xmm0

	movups	[DReg],xmm1
	movups	[DReg+16],xmm2
	movups	[DReg+32],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3uInverseAsm
;;;
;;; Call Stack
;;;
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3uInverseAsm(mat3& r,const mat3& m);
;;;
;;; IMPLEMENTORS NOTE:	This one will blow chunks if m = r
;;;

_Mat3uInverseAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]

	mov	ebx,  [zeroVec]
	mov	dword [AReg+12],ebx
	mov	dword [AReg+28],ebx
	mov	dword [AReg+44],ebx

	movups	xmm4,[AReg]			; m00 m01 m02 xxx
	movups	xmm0,[AReg+16]			; m10 m11 m12 0.0
	movups	xmm1,[AReg+32]			; m20 m21 m22 0.0

	shufps	xmm0,xmm0,SHUFFLE(1,2,0,3)	; m11 m12 m10 0.0
	shufps	xmm1,xmm1,SHUFFLE(2,0,1,3)	; m22 m20 m21 0.0

	movhps	xmm2,[AReg+16]			; xxx xxx m10 m11
	movlps	xmm2,[AReg+32]			; m20 m21 m10 m11
	movhps	xmm3,[AReg+24]			; xxx xxx m12 0.0

	shufps	xmm2,xmm2,SHUFFLE(1,2,3,0)	; m21 m10 m11 m20
	shufps	xmm3,xmm1,SHUFFLE(2,3,0,1)	; m12 0.0 m22 m20
	shufps	xmm3,xmm3,SHUFFLE(0,2,3,1)	; m12 m22 m20 0.0

	mulps	xmm0,xmm1			; m11*m22 m12*m20 m10*m21 0.0
	mulps	xmm2,xmm3			; m21*m12 m10*m22 m11*m20 0.0
	subps	xmm0,xmm2			; m11*m22-m21*m12 m12*m20-m10*m22 m10*m21-m11*m20 0.0

	;; xmm0 = p0 p1 p2

	mulps	xmm4,xmm0			; m00*p0 m01*p1 m02*p2 0.0
	movaps	xmm1,xmm4
	movaps	xmm2,xmm4

	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm2
	addss	xmm1,xmm4

	ucomiss	xmm1,[zeroVec]
	jne	Mat3uInverseDB0ErrorCont
	jmp	Mat3uInverseDB0Error

Mat3uInverseDB0ErrorCont:

	rcpss	xmm1,xmm1			; invDet
	shufps	xmm1,xmm1,0
	movups	[DReg],xmm0			; p0 p1 p2

	mov	ebx,[DReg+4]			; p1
	mov	[DReg+16],ebx

	mov	ebx,[DReg+8]			; p2
	mov	[DReg+32],ebx

	mov	ebx,[zeroVec]
	mov	[DReg+4], ebx
	mov	[DReg+8], ebx
	mov	[DReg+12],ebx
	mov	[DReg+20],ebx
	mov	[DReg+24],ebx
	mov	[DReg+28],ebx
	mov	[DReg+36],ebx
	mov	[DReg+40],ebx

	movups	xmm0,[DReg]			; p0 0.0 0.0 0.0
	mov	[DReg],ebx			; [DReg]: 0.0 0.0 0.0 0.0

	mov	ebx,[AReg+36]			; m21
	mov	[DReg+4],ebx
	mov	ebx,[AReg+4]			; m01
	mov	[DReg+8],ebx
	movups	xmm2,[DReg]			; 0.0 m21 m01 0.0

	mov	ebx,[AReg+8]			; m02
	mov	[DReg+4],ebx
	mov	ebx,[AReg+24]			; m12
	mov	[DReg+8],ebx
	movups	xmm3,[DReg]			; 0.0 m02 m12 0.0

	mov	ebx,[AReg+4]			; m01
	mov	[DReg+4],ebx
	mov	ebx,[AReg+20]			; m11
	mov	[DReg+8],ebx
	movups	xmm4,[DReg]			; 0.0 m01 m11 0.0

	mov	ebx,[AReg+40]			; m22
	mov	[DReg+4],ebx
	mov	ebx,[AReg+8]			; m02
	mov	[DReg+8],ebx
	movups	xmm5,[DReg]			; 0.0 m22 m02 0.0
	
	mulps	xmm2,xmm3			; 0.0 m21*m02 m01*m12 0.0
	mulps	xmm4,xmm5			; 0.0 m01*m22 m11*m02 0.0
	subps	xmm2,xmm4			; 0.0 m21*m02-m01*m22 m01*m12-m11*m02 0.0
	addps	xmm0,xmm2			; p0  m21*m02-m01*m22 m01*m12-m11*m02 0.0
	movups	[DReg],xmm0

	movups	xmm0,[DReg+16]			; p1 0.0 0.0 0.0
	mov	ebx,[zeroVec]
	mov	[DReg+16],ebx			; 0.0 0.0 0.0 0.0

	mov	ebx,[AReg]			; m00
	mov	[DReg+20],ebx
	mov	ebx,[AReg+16]			; m10
	mov	[DReg+24],ebx
	movups	xmm2,[DReg+16]			; 0.0 m00 m10 0.0

	mov	ebx,[AReg+40]			; m22
	mov	[DReg+20],ebx
	mov	ebx,[AReg+8]			; m02
	mov	[DReg+24],ebx
	movups	xmm3,[DReg+16]			; 0.0 m22 m02 0.0

	mov	ebx,[AReg+32]			; m20
	mov	[DReg+20],ebx
	mov	ebx,[AReg]			; m00
	mov	[DReg+24],ebx
	movups	xmm4,[DReg+16]			; 0.0 m20 m00 0.0

	mov	ebx,[AReg+8]			; m02
	mov	[DReg+20],ebx
	mov	ebx,[AReg+24]			; m12
	mov	[DReg+24],ebx
	movups	xmm5,[DReg+16]			; 0.0 m02 m12 0.0

	mulps	xmm2,xmm3			; 0.0 m00*m22 m10*m02 0.0
	mulps	xmm4,xmm5			; 0.0 m20*m02 m00*m12 0.0
	subps	xmm2,xmm4			; 0.0 m00*m22-m20*m02 m10*m02-m00*m12 0.0
	addps	xmm0,xmm2			; p1  m00*m22-m20*m02 m10*m02-m00*m12 0.0
	movups	[DReg+16],xmm0

	movups	xmm0,[DReg+32]			; p2 0.0 0.0 0.0
	mov	ebx,[zeroVec]
	mov	[DReg+32],ebx			; 0.0 0.0 0.0 0.0

	mov	ebx,[AReg+32]			; m20
	mov	[DReg+36],ebx
	mov	ebx,[AReg]			; m00
	mov	[DReg+40],ebx
	movups	xmm2,[DReg+32]			; 0.0 m20 m00 0.0

	mov	ebx,[AReg+4]			; m01
	mov	[DReg+36],ebx
	mov	ebx,[AReg+20]			; m11
	mov	[DReg+40],ebx
	movups	xmm3,[DReg+32]			; 0.0 m01 m11 0.0

	mov	ebx,[AReg]			; m00
	mov	[DReg+36],ebx
	mov	ebx,[AReg+4]			; m01
	mov	[DReg+40],ebx
	movups	xmm4,[DReg+32]			; 0.0 m00 m01 0.0

	mov	ebx,[AReg+36]			; m21
	mov	[DReg+36],ebx
	mov	ebx,[AReg+16]			; m10
	mov	[DReg+40],ebx
	movups	xmm5,[DReg+32]			; 0.0 m21 m10 0.0

	mulps	xmm2,xmm3			; 0.0 m20*m01 m00*m11 0.0
	mulps	xmm4,xmm5			; 0.0 m00*m21 m01*m10 0.0
	subps	xmm2,xmm4			; 0.0 m20*m01-m00*m21 m00*m11-m01*m10 0.0
	addps	xmm0,xmm2			; p2  m20*m01-m00*m21 m00*m11-m01*m10 0.0
	
	;; mat3 *= invDet

	mulps	xmm0,xmm1
	movups	[DReg+32],xmm0

	movaps	xmm2,xmm1

	movups	xmm3,[DReg]
	movups	xmm4,[DReg+16]

	mulps	xmm1,xmm3
	mulps	xmm2,xmm4

	movups	[DReg],xmm1
	movups	[DReg+16],xmm2

%if 0
	mulps	xmm1,[DReg]
	movups	[DReg],xmm1
	
	mulps	xmm2,[DReg+16]
	movups	[DReg+16],xmm2
%endif

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

Mat3uInverseDB0Error:

	mov	[STACK_SAVE4],CReg

	mov	ecx,12
	mov	ebx,[zeroVec]

Mat3uInverseDB0ErrorLoop:

	mov	[DReg],ebx
	add	DReg,FloatSize
	dec	ecx
	jnz	Mat3uInverseDB0ErrorLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Mat3uTransposeAsm
;;;
;;; Call Stack
;;;
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3uTransposeAsm(mat3& r,const mat3&m);
;;;

_Mat3uTransposeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]		; *m
	mov	DReg,[STACK_PTR1]		; *r

	movlps	xmm0,[AReg]			; m00 m01 xxx xxx
	movhps	xmm0,[AReg+16]			; m00 m01 m10 m11
	movaps	xmm1,xmm0
	movlps	xmm2,[AReg+32]			; m20 m21 xxx xxx

	movlps	xmm3,[AReg+8]			; m02 xxx xxx xxx
	movhps	xmm3,[AReg+24]			; m02 xxx m12 xxx
	movlps	xmm4,[AReg+40]			; m22 xxx xxx xxx

	shufps	xmm0,xmm2,SHUFFLE(0,2,0,1)	; m00 m10 m20 m21
	shufps	xmm1,xmm2,SHUFFLE(1,3,1,0)	; m01 m11 m21 m20
	shufps	xmm3,xmm4,SHUFFLE(0,2,0,3)	; m02 m12 m22 xxx

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm3

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; Mat3MultiplyFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] mat3* n
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3MultiplyFPU_Asm(mat3& r,const mat3& m,const mat3& n)
;;;

_Mat3MultiplyFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m
	mov	BReg,[STACK_PTR3]	; *n

	;; Calculate the save area position

	fld	dword [AReg]		; m00
	fld	st0
	fmul	dword [BReg]		; m00*n00
	fld	dword [AReg+4]		; m01
	fmul	dword [BReg+16]		; m01*n10
	fld	dword [AReg+8]		; m02
	fmul	dword [AReg+32]		; m01*n20

	faddp	st1,st0
	faddp	st1,st0			; m00*n00 + m01*n10 + m02*n20
	fstp	dword [DReg]		; r00

	fld	st0			; m00
	fmul	dword [BReg+4]		; m00*n10
	fld	dword [AReg+4]		; m01
	fmul	dword [BReg+20]		; m01*n11
	fld	dword [AReg+8]		; m02
	fmul	dword [BReg+36]		; m02*n12
	faddp	st1,st0
	faddp	st1,st0			; m00*n10 + m01*n11 + m02*n12
	fstp	dword [DReg+4]		; r01

	fmul	dword [BReg+8]		; m00*n02
	fld	dword [AReg+4]		; m01
	fmul	dword [BReg+24]		; m01*n12
	fld	dword [AReg+8]		; m02
	fmul	dword [BReg+40]		; m02*n22
	faddp	st1,st0
	faddp	st1,st0			; m00*n02 + m01*n12 + m02*n22
	fstp	dword [DReg+8]		; r02

	fldz
	fst	dword [DReg+12]		; rn03

	fld	dword [AReg+16]		; m10
	fld	st0
	fmul	dword [BReg]		; m10*n00
	fld	dword [AReg+20]		; m11
	fmul	dword [BReg+16]		; m11*n10
	fld	dword [AReg+24]		; m12
	fmul	dword [BReg+32]		; m12*n20
	faddp	st1,st0
	faddp	st1,st0			; m10*n00 + m11*n10 + m12*n20
	fstp	dword [DReg+16]		; r10

	fld	st0			; m10
	fmul	dword [BReg+4]		; m10*n01
	fld	dword [AReg+20]		; m11
	fmul	dword [BReg+20]		; m11*n11
	fld	dword [AReg+24]		; m12
	fmul	dword [BReg+36]		; m12*n21
	faddp	st1,st0
	faddp	st1,st0			; m10*n01 + m11*n11 + m12*n21
	fstp	dword [DReg+20]		; r11

	fmul	dword [BReg+8]		; m10*n02
	fld	dword [AReg+20]		; m11
	fmul	dword [BReg+24]		; m11*n12
	fld	dword [AReg+24]		; m12
	fmul	dword [BReg+40]		; m12*n22
	faddp	st1,st0
	faddp	st1,st0			; m10*n02 + m11*n12 + m12*n22
	fstp	dword [DReg+24]		; r12
	fst	dword [DReg+28]		; rn13

	fld	dword [AReg+32]		; m20
	fld	st0
	fmul	dword [BReg]		; m20*n00
	fld	dword [AReg+36]		; m21
	fmul	dword [BReg+16]		; m20*n10
	fld	dword [AReg+40]		; m22
	fmul	dword [BReg+32]		; m22*n20
	faddp	st1,st0
	faddp	st1,st0			; m20*n00 + m20*n10 + m22*n20
	fstp	dword [DReg+32]		; r20

	fld	st0			; m20
	fmul	dword [BReg+4]		; m20*n01
	fld	dword [AReg+36]		; m21
	fmul	dword [BReg+20]		; m20*n11
	fld	dword [AReg+40]		; m22
	fmul	dword [BReg+36]		; m22*n21
	faddp	st1,st0
	faddp	st1,st0			; m20*n01 + m20*n11 + m22*n21
	fstp	dword [DReg+36]		; r21

	fmul	dword [BReg+8]		; m20*n02
	fld	dword [AReg+36]		; m21
	fmul	dword [BReg+24]		; m21*n12
	fld	dword [AReg+40]		; m22
	fmul	dword [BReg+40]		; m22*n22
	faddp	st1,st0
	faddp	st1,st0			; m20*n02 + m21*n12 + m22*n22
	fstp	dword [DReg+40]		; r22
	fstp	dword [DReg+44]		; rn23

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat3MultiplyIdentityByBlockFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] int32_t nCount
;;; [2] mat3* m
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3MultiplyIdentityByBlockFPU_Asm(mat3& r,const mat3& m,const int32_t nCount)
;;;

_Mat3MultiplyIdentityByBlockFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg
	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	DReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; *m

	mov	Srcp,mat3Identity
	mov	Dstp,DReg
	cld
	mov	CReg,12
	rep	movsd

	mov	ecx,[STACK_PTR3]	; iCount

Mat3MulIdentBlkFpuLoop:

	mov	AReg,[BReg]

	fld	dword [DReg]		; m00
	fmul	dword [AReg]		; m00*n00
	fld	dword [DReg+4]		; m01
	fmul	dword [AReg+16]		; m01*n10
	fld	dword [DReg+8]		; m02
	fmul	dword [AReg+32]		; m02*n20
	faddp	st1,st0
	faddp	st1,st0			; m00*n00 + m01*n10 + m02*n20

	fld	dword [DReg]		; m00
	fmul	dword [AReg+4]		; m00*n01
	fld	dword [DReg+4]		; m01
	fmul	dword [AReg+20]		; m01*n11
	faddp	st1,st0
	fld	dword [DReg+8]		; m02
	fmul	dword [AReg+36]		; m02*m21
	faddp	st1,st0			; m00*n01 + m01*n11 + m02*m21

	fld	dword [DReg]		; m00
	fmul	dword [AReg+8]		; m00*n02
	fld	dword [DReg+4]		; m01
	fmul	dword [AReg+24]		; m01*n12
	faddp	st1,st0
	fld	dword [DReg+8]		; m02
	fmul	dword [AReg+40]		; m02*n22
	faddp	st1,st0			; m00*n02 + m01*n12 + m02*n22

	fstp	dword [DReg+8]		; r02
	fstp	dword [DReg+4]		; r01
	fstp	dword [DReg]		; r00

	fldz
	fstp	dword [DReg+12]		; rn03

	fld	dword [DReg+16]		; m10
	fmul	dword [AReg]		; m10*n00
	fld	dword [DReg+20]		; m11
	fmul	dword [AReg+16]		; m11*n10
	fld	dword [DReg+24]		; m12
	fmul	dword [AReg+32]		; m12*n20
	faddp	st1,st0
	faddp	st1,st0			; m10*n00 + m11*n10 + m12*n20

	fld	dword [DReg+16]		; m10
	fmul	dword [AReg+4]		; m10*n01
	fld	dword [DReg+20]		; m11
	fmul	dword [AReg+20]		; m11*n11
	faddp	st1,st0
	fld	dword [DReg+24]		; m12
	fmul	dword [AReg+36]		; m12*m21
	faddp	st1,st0			; m10*n01 + m11*n11 + m12*m21

	fld	dword [DReg+16]		; m10
	fmul	dword [AReg+8]		; m10*n02
	fld	dword [DReg+20]		; m11
	fmul	dword [AReg+24]		; m11*n12
	faddp	st1,st0
	fld	dword [DReg+24]		; m12
	fmul	dword [AReg+40]		; m12*n22
	faddp	st1,st0			; m10*n02 + m11*n12 + m12*n22

	fstp	dword [DReg+24]		; r12
	fstp	dword [DReg+20]		; r11
	fstp	dword [DReg+16]		; r10

	fldz
	fstp	dword [DReg+28]		; rn13

	fld	dword [DReg+32]		; m20
	fmul	dword [AReg]		; m20*n00
	fld	dword [DReg+36]		; m21
	fmul	dword [AReg+16]		; m21*n10
	fld	dword [DReg+40]		; m22
	fmul	dword [AReg+32]		; m22*n20
	faddp	st1,st0
	faddp	st1,st0			; m20*n00 + m21*n10 + m22*n20

	fld	dword [DReg+32]		; m20
	fmul	dword [AReg+4]		; m20*n01
	fld	dword [DReg+36]		; m21
	fmul	dword [AReg+20]		; m21*n11
	faddp	st1,st0
	fld	dword [DReg+40]		; m22
	fmul	dword [AReg+36]		; m22*m21
	faddp	st1,st0			; m20*n01 + m21*n11 + m22*m21

	fld	dword [DReg+32]		; m20
	fmul	dword [AReg+8]		; m20*n02
	fld	dword [DReg+36]		; m21
	fmul	dword [AReg+24]		; m21*n12
	faddp	st1,st0
	fld	dword [DReg+40]		; m22
	fmul	dword [AReg+40]		; m22*n22
	faddp	st1,st0			; m20*n02 + m21*n12 + m22*n22

	fstp	dword [DReg+40]		; r22
	fstp	dword [DReg+36]		; r21
	fstp	dword [DReg+32]		; r20

	fldz
	fstp	dword [DReg+44]		; rn23

	add	BReg,PtrSize

	dec	ecx
	jnz	Mat3MulIdentBlkFpuLoop

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

;;; 
;;; Mat3RotateRHX_Asm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateRHX_Asm(mat3& r,const float angle)
;;;

_Mat3RotateRHX_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	fld1

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [DReg+20]
	fstp	dword [DReg+40]

	fst	dword [DReg+36]
	fchs
	fstp	dword [DReg+24]

	fstp	dword [DReg]

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+44],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;; 
;;; Mat3RotateLHX_Asm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateLHX_Asm(mat3& r,const float angle)
;;;

_Mat3RotateLHX_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	fld1

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [DReg+20]
	fstp	dword [DReg+40]

	fst	dword [DReg+24]
	fchs
	fstp	dword [DReg+36]

	fstp	dword [DReg]

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+44],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateRHY_Asm
;;;
;;; Call Stack
;;;
;;; [2] const float angle
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateRHY_Asm(mat3* m,const float angle)
;;;

_Mat3RotateRHY_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *m

	fld	dword [STACK_PTR2]	; angle
	fsincos

	fst	dword [AReg]		; cosY
	fstp	dword [AReg+40]

	fst	dword [AReg+8]		; sinY
	fchs				; -sinY
	fstp	dword [AReg+32]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+4],edx
	mov	[AReg+12],edx
	mov	[AReg+16],edx
	mov	[AReg+24],edx
	mov	[AReg+28],edx
	mov	[AReg+36],edx
	mov	[AReg+44],edx

	mov	edx,[oneVec]
	mov	[AReg+20],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateLHY_Asm
;;;
;;; Call Stack
;;;
;;; [2] const float angle
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateLHY_Asm(mat3& r,const float angle)
;;;

_Mat3RotateLHY_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	fld1

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [DReg]
	fstp	dword [DReg+40]

	fst	dword [DReg+32]
	fchs
	fstp	dword [DReg+8]

	fstp	dword [DReg+20]

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+36],eax
	mov	[DReg+44],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateRHZ_Asm
;;;
;;; Call Stack
;;; [2] const float angle
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateRHZ_Asm(mat3& r,const float angle)
;;;

_Mat3RotateRHZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	fld1

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [DReg]
	fstp	dword [DReg+20]

	fst	dword [DReg+16]
	fchs
	fstp	dword [DReg+4]

	fstp	dword [DReg+40]

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateLHZ_Asm
;;;
;;; Call Stack
;;; [2] const float angle
;;; [1] mat3* r
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateLHZ_Asm(mat3& r,const float angle)
;;;

_Mat3RotateLHZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	fld1

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [DReg]
	fstp	dword [DReg+20]

	fst	dword [DReg+4]
	fchs
	fstp	dword [DReg+16]

	fstp	dword [DReg+40]

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateRHXY_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float y_angle
;;; [2] const float x_angle
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3RotateRHXY_Asm(mat3* r,const float x,const float y);
;;;

_Mat3RotateRHXY_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x
	fsincos				; [0] cosx [1] sinx
	fld	dword [STACK_PTR3]	; y
	fsincos				; [0] cosy [1] siny [2] cosx [3] sinx

	fst	dword [AReg]		; [0] cosy [1] siny [2] cosx [3] sinx

	fld	st3			; [0] sinx [1] cosy [2] siny [3] cosx [4] sinx
	fchs				; [0] -sinx [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st1			; [0] -sinx*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+24]		; [0] cosy [1] siny [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosy*cosx [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+40]		; [0] siny [1] cosx [2] sinx

	fst	dword [AReg+8]		; [0] siny [1] cosx [2] sinx

	fld	st2			; [0] sinx [1] siny [2] cosx [3] sinx
	fmul	st0,st1			; [0] sinx*siny [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+16]		; [0] siny [1] cosx [2] sinx

	fchs				; [0] -siny [1] cosx [2] sinx
	fmul	st0,st1			; [0] -siny*cosx [1] cosx [2] sinx
	fstp	dword [AReg+32]		; [0] cosx [1] sinx

	fstp	dword [AReg+20]		; [0] sinx
	fstp	dword [AReg+36]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+4],edx
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateLHXY_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float y_angle
;;; [2] const float x_angle
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3RotateLHXY_Asm(mat3* r,const float x,const float y);
;;;

_Mat3RotateLHXY_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x
	fsincos				; [0] cosx [1] sinx
	fld	dword [STACK_PTR3]	; y
	fsincos				; [0] cosy [1] siny [2] cosx [3] sinx

	fst	dword [AReg]		; [0] cosy [1] siny [2] cosx [3] sinx
	fld	st0			; [0] cosy [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st4			; [0] sinx*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+24]		; [0] cosy [1] siny [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosx*cosy [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+40]		; [0] siny [1] cosx [2] sinx

	fld	st0
	fchs				; [0] -siny [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+8]		; [0] siny [1] cosx [2] sinx

	fld	st0			; [0] siny [1] siny [2] cosx [3] sinx
	fmul	st0,st3			; [0] sinx*siny [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+16]		; [0] siny [1] cosx [2] sinx

	fmul	st0,st1			; [0] cosx*siny [1] cosx [2] sinx
	fstp	dword [AReg+32]		; [0] cosx [1] sinx

	fstp	dword [AReg+20]		; [0] sinx
	fchs				; [0] -sinx
	fstp	dword [AReg+36]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+4],edx
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateRHXZ_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float z_angle
;;; [2] const float x_angle
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3RotateRHXZ_Asm(mat3* m,const float x,const float z);
;;;

_Mat3RotateRHXZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x_angle
	fsincos				; [0] cosx [1] sinx
	fld	dword [STACK_PTR3]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosx [3] sinx

	fst	dword [AReg]		; [0] cosz [1] sinz [2] cosx [3] sinx

	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosx [4] sinx
	fmul	st0,st4			; [0] sinx*cosz [1] cosz [2] sinz [3] cosx [4] sinx
	fstp	dword [AReg+36]		; [0] cosz [1] sinz [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosx*cosz [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+20]		; [0] sinz [1] cosx [2] sinx

	fld	st0			; [0] sinz [1] sinz [2] cosx [3] sinx
	fmul	st0,st3			; [0] sinx*sinz [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+32]		; [0] sinz [1] cosx [2] sinx

	fld	st0			; [0] sinz [1] sinz [2] cosx [3] sinx
	fmul	st0,st2			; [0] cosx*sinz [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+16]		; [0] sinz [1] cosx [2] sinx
	fchs				; [0] -sinz [1] cosx [2] sinx
	fstp	dword [AReg+4]		; [0] cosx [1] sinx

	fstp	dword [AReg+40]		; [0] sinx
	fchs				; [0] -sinx
	fstp	dword [AReg+24]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+8],edx
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateLHXZ_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float z_angle
;;; [2] const float x_angle
;;; [1] mat3* m
;;;
;;; extern "C" void Mat3RotateLHXZ_Asm(mat3* m,const float x,const float z);
;;;

_Mat3RotateLHXZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x_angle
	fsincos				; [0] cosx [1] sinx
	fld	dword [STACK_PTR3]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosx [3] sinx

	fld	st3			; [0] sinx [1] cosz [2] sinz [3] cosx [4] sinx
	fchs				; [0] -sinx [1] cosz [2] sinz [3] cosx [4] sinx
	fmul	st0,st1			; [0] -sinx*cosz [1] cosz [2] sinz [3] cosx [4] sinx
	fstp	dword [AReg+36]		; [0] cosz [1] sinz [2] cosx [3] sinx

	fst	dword [AReg]		; [0] cosz [1] sinz [2] cosx [3] sinx
	fmul	st0,st2			; [0] cosx*cosz [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+20]		; [0] sinz [1] cosx [2] sinx

	fst	dword [AReg+4]		; [0] sinz [1] cosx [2] sinx

	fld	st0			; [0] sinz [1] sinz [2] cosx [3] sinx
	fchs				; [0] -sinz [1] sinz [2] cosx [3] sinx
	fmul	st0,st2			; [0] -sinz*cosx [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+16]		; [0] sinz [1] cosx [2] sinx

	fmul	st2			; [0] sinx*sinz [1] cosx [2] sinx
	fstp	dword [AReg+32]		; [0] cosx [1] sinx

	fstp	dword [AReg+40]		; [0] sinx
	fstp	dword [AReg+24]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+8],edx
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateRHYZ_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float z_angle
;;; [2] const float y_angle
;;; [1] mat3* m
;;;
;;; extern "C" void Mat3RotateRHYZ_Asm(mat3* r,const float y,const float z)
;;;

_Mat3RotateRHYZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; y_angle
	fsincos				; [0] cosy [1] siny
	fld	dword [STACK_PTR3]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosy [3] siny

	fst	dword [AReg+20]		; [0] cosz [1] sinz [2] cosy [3] siny

	fld	st3			; [0] siny [1] cosz [2] sinz [3] cosy [4] siny
	fchs				; [0] -siny [1] cosz [2] sinz [3] cosy [4] siny
	fmul	st0,st1			; [0] -siny*cosz [1] cosz [2] sinz [3] cosy [4] siny
	fstp	dword [AReg+32]		; [0] cosz [1] sinz [2] cosy [3] siny

	fmul	st0,st2			; [0] cosy*cosz [1] sinz [2] cosy [3] siny
	fstp	dword [AReg]		; [0] sinz [1] cosy [2] siny

	fld	st0			; [0] sinz [1] sinz [2] cosy [3] siny
	fchs				; [0] -sinz [1] sinz [2] cosy [3] siny
	fmul	st0,st2			; [0] -sinz*cosy [1] sinz [2] cosy [3] siny
	fstp	dword [AReg+4]		; [0] sinz [1] cosy [2] siny

	fst	dword [AReg+16]		; [0] sinz [1] cosy [2] siny
	fmul	st0,st2			; [0] siny*sinz [1] cosy [2] siny
	fstp	dword [AReg+36]		; [0] cosy [1] siny
	fstp	dword [AReg+40]		; [0] siny
	fstp	dword [AReg+8]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+24],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateLHYZ_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float z_angle
;;; [2] const float y_angle
;;; [1] mat3* m
;;;
;;; extern "C" void Mat3RotateLHYZ_Asm(mat3* m,const float y,const float z);
;;;

_Mat3RotateLHYZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]
	fsincos				; [0] cosy [1] siny
	fld	dword [STACK_PTR3]
	fsincos				; [0] cosz [1] sinz [2] cosy [3] siny

	fst	dword [AReg+20]		; [0] cosz [1] sinz [2] cosy [3] siny
	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosy [4] siny
	fmul	st0,st3			; [0] cosy*cosz [1] cosz [2] sinz [3] cosy [4] siny
	fstp	dword [AReg]		; [0] cosz [1] sinz [2] cosy [3] siny

	fmul	st0,st3			; [0] siny*cosz [1] sinz [2] cosy [3] siny
	fstp	dword [AReg+32]		; [0] sinz [1] cosy [2] siny

	fld	st0
	fchs				; [0] -sinz [1] sinz [2] cosy [3] siny
	fstp	dword [AReg+16]		; [0] sinz [1] cosy [2] siny

	fld	st0			; [0] sinz [1] sinz [2] cosy [3] siny
	fmul	st0,st2			; [0] cosy*sinz [1] sinz [2] cosy [3] siny
	fstp	dword [AReg+4]		; [0] sinz [1] cosy [2] siny

	fmul	st0,st2			; [0] siny*sinz [1] cosy [2] siny
	fstp	dword [AReg+36]		; [0] cosy [1] siny
	
	fstp	dword [AReg+40]		; [0] siny
	fchs				; [0] -siny
	fstp	dword [AReg+8]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+24],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3RotateRHXYZ_Asm
;;;
;;; Call Stack
;;;
;;; [4] const float z_angle
;;; [3] const float y_angle
;;; [2] const float x_angle
;;; [1] mat3* m
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateRHXYZ_Asm(mat3& r,const float x,const float y,const float z)
;;;

_Mat3RotateRHXYZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x_angle
	fsincos				; [0] cosx [1] sinx

	fld	dword [STACK_PTR3]	; y_angle
	fsincos				; [0] cosy [1] siny [2] cosx [3] sinx

	fld	dword [STACK_PTR4]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st2			; [0] cosy [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st1			; [0] cosy*cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st5			; [0] sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st4			; [0] sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st1			; [0] cosz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st5			; [0] cosx [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st3			; [0] cosx*sinx [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] cosx*sinx+cosz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+16]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st1			; [0] sinz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fchs				; [0] -sinz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st6			; [0] -sinz*sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st4			; [0] -sinz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st5			; [0] cosx [1] -sinz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st2			; [0] cosx*cosz [1] -sinz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] cosx*cosz+(-sinz*sinx*siny) [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+20]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st3			; [0] siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fchs				; [0] -siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st5			; [0] -siny*cosx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st1			; [0] -siny*cosx*cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st2			; [0] sinz [1] -siny*cosx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st7			; [0] sinz*sinx [1] -siny*cosx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] sinz*sinx+(-siny*cosx*cosz) [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+32]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fmul	st0,st5			; [0] cosz*sinx [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fld	st4			; [0] cosx [1] cosz*sinx [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st4			; [0] cosx*siny [1] cosz*sinx [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st2			; [0] cosx*siny*sinz [1] cosz*sinx [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	faddp	st1,st0			; [0] cosx*siny*sinz+cosz*sinx [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fstp	dword [AReg+36]		; [0] sinz [1] cosy [2] siny [3] cosx [4] sinx

	fchs				; [0] -sinz [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st1			; [0] -sinz*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+4]		; [0] cosy [1] siny [2] cosx [3] sinx

	fld	st3			; [0] sinx [1] cosy [2] siny [3] cosx [4] sinx
	fchs				; [0] -sinx [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st1			; [0] -sinx*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+24]		; [0] cosy [1] siny [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosy*cosx [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+40]		; [0] siny [1] cosx [2] sinx

	fstp	dword [AReg+8]		; [0] cosx [1] sinx

	ffree	st1
	ffree	st0
	fincstp
	fincstp

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	fwait

	ret

;;;
;;; Mat3RotateLHXYZ_Asm
;;;
;;; Call Stack
;;;
;;; [4] const float z_angle
;;; [3] const float y_angle
;;; [2] const float x_angle
;;; [1] mat3* m
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateLHXYZ_Asm(mat3& r,const float x,const float y,const float z)
;;;

_Mat3RotateLHXYZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x_angle
	fsincos				; [0] cosx [1] sinx

	fld	dword [STACK_PTR3]	; y_angle
	fsincos				; [0] cosy [1] siny [2] cosx [3] sinx

	fld	dword [STACK_PTR4]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st3			; [0] cosy*cosz [0] cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st6			; [0] cosz*sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st4			; [0] cosz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st2			; [0] sinz [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fchs				; [0] -sinz [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st6			; [0] -sinz*cosx [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] -sinz*cosx+cosz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+16]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st5			; [0] cosz*cosx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st6			; [0] sinx [1] cosz*cosx [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st5			; [0] sinx*siny [1] cosz*cosx [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st7			; [0] sinx*siny*sinz [1] cosz*cosx [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] sinx*siny*sinz+cosz*cosx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+20]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st5			; [0] sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fchs				; [0] -sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st1			; [0] -sinx*cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st5			; [0] cosx [1] -sinx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st5			; [0] cosx*siny [1] -sinx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st3			; [0] cosx*siny*sinz [1] -sinx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] cosx*siny*sinz+(-sinx*cosz) [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+36]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fmul	st0,st4			; [0] cosx*cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fmul	st0,st3			; [0] cosx*siny*cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fld	st5			; [0] sinx [1] cosx*siny*cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st2			; [0] sinx*sinz [1] cosx*siny*cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	faddp	st1,st0			; [0] sinx*sinz+cosx*siny*cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fstp	dword [AReg+32]		; [0] sinz [1] cosy [2] siny [3] cosx [4] sinx

	fmul	st0,st1			; [0] cosy*sinz [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+4]		; [0] cosy [1] siny [2] cosx [3] sinx

	fld	st0			; [0] cosy [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st4			; [0] sinx*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+24]		; [0] cosy [1] siny [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosx*cosy [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+40]		; [0] siny [1] cosx [2] sinx

	fchs				; [0] -siny [1] cosx [2] sinx
	fstp	dword [AReg+8]		; [0] cosx [1] sinx

	ffree	st1
	ffree	st0
	fincstp
	fincstp

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%if 0
	;; XXX:	THIS REALLY SHOULD BE REMOVED, BUT ITS SO NICE AND QUICK

;;;
;;; Mat3RotateTempSaveRHXYZ_Asm
;;;
;;; Call Stack
;;;
;;; [5] Aligned16 char TempSave[348]
;;; [4] const float z_angle
;;; [3] const float y_angle
;;; [2] const float x_angle
;;; [1] mat3* m
;;; [0] ret
;;;
;;; extern "C" void Mat3RotateTempSaveRHXYZ_Asm(mat3& r,const float x,const float y,const float z,char TempSave[348])
;;;

_Mat3RotateTempSaveRHXYZ_Asm:
	;; Build the following vector pattern
	;; 
	;;  v0: m00:000   1.0 004   sinX  008 -cosX 012  0.0
	;;  v1: m01:016  cosY 020   sinY  024   1.0 028  0.0
	;;  v2: m02:032  cosZ 036   sinZ  040  sinZ 044  0.0
	;;  v3: m03:048  sinX 052    1.0  056   0.0 060  0.0
	;;  v4: m10:064  cosY 068  -sinY  072   0.0 076  0.0
	;;  v5: m11:080  sinZ 084   cosZ  088   0.0 092  0.0
	;;  v6: m12:096   1.0 100  -sinX  104  cosX 108  0.0
	;;  v7: m13:112  cosY 116   sinY  120   1.0 124  0.0
	;;  v8: m20:128  sinZ 132   cosZ  136  cosZ 140  0.0
	;;  v9: m21:144   1.0 148  -sinX  152   0.0 156  0.0
	;; v10: m22:160 -sinY 164   cosY  168   0.0 172  0.0
	;; v11: m23:176  sinZ 180   cosZ  184   0.0 188  0.0
	;; v12: m30:192  cosX 196    0.0  200  sinX 204  0.0
	;; v13: m31:208  sinY 212    0.0  216   1.0 220  0.0
	;; v14: m32:224  cosX 228    0.0  232   0.0 236  0.0
	;; v15: m33:240  cosY 244    0.0  248   0.0 252  0.0

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR5]

	;; Calculate the x-rotation values

	fld	dword [STACK_PTR2]	; x rotation value
	fsincos
	fst	dword [AReg+104]	;  cosX
	fchs
	fstp	dword [AReg+8]		; -cosX
	fst	dword [AReg+4]		;  sinX
	fstp	dword [AReg+100]	; -sinX
	
	;; Add the ones to the matrix

	mov	edx,[oneVec]
	mov	[AReg],edx
	mov	[AReg+24],edx
	mov	[AReg+52],edx
	mov	[AReg+96],edx
	mov	[AReg+120],edx
	mov	[AReg+144],edx
	mov	[AReg+216],edx

	fld	dword [STACK_PTR3]	; y rotation value
	fsincos
	fstp	dword [AReg+16]		;  cosY
	fst	dword [AReg+20]		;  sinY
	fchs
	fstp	dword [AReg+68]		; -sinY

	;; Add the zeroes to the matrix

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+56],edx
	mov	[AReg+60],edx
	mov	[AReg+72],edx
	mov	[AReg+76],edx
	mov	[AReg+88],edx
	mov	[AReg+92],edx
	mov	[AReg+108],edx
	mov	[AReg+124],edx
	mov	[AReg+140],edx
	mov	[AReg+152],edx
	mov	[AReg+156],edx
	mov	[AReg+168],edx
	mov	[AReg+172],edx
	mov	[AReg+184],edx
	mov	[AReg+188],edx
	mov	[AReg+196],edx
	mov	[AReg+204],edx
	mov	[AReg+212],edx
	mov	[AReg+220],edx
	mov	[AReg+228],edx
	mov	[AReg+232],edx
	mov	[AReg+236],edx
	mov	[AReg+244],edx
	mov	[AReg+248],edx
	mov	[AReg+252],edx

	fld	dword [STACK_PTR4]	; z rotation value
	fsincos
	fstp	dword [AReg+32]		; cosZ
	fstp	dword [AReg+36]		; sinZ

	fwait

	mov	edx,[AReg+104]		; Copy additional cosX values
	mov	[AReg+192],edx
	mov	[AReg+224],edx

	mov	edx,[AReg+4]		; Copy additional sinX values
	mov	[AReg+48],edx
	mov	[AReg+200],edx

	mov	edx,[AReg+100]		; Copy additional -sinX values
	mov	[AReg+148],edx

	mov	edx,[AReg+16]		; Copy additional cosY values
	mov	[AReg+64],edx
	mov	[AReg+112],edx
	mov	[AReg+164],edx
	mov	[AReg+240],edx

	mov	edx,[AReg+20]		; Copy additional sinY values
	mov	[AReg+116],edx
	mov	[AReg+208],edx

	mov	edx,[AReg+68]		; Copy additional -sinY values
	mov	[AReg+160],edx

	mov	edx,[AReg+32]		; Copy additional cosZ values
	mov	[AReg+84],edx
	mov	[AReg+132],edx
	mov	[AReg+136],edx
	mov	[AReg+180],edx

	mov	edx,[AReg+36]		; Copy additional sinZ values
	mov	[AReg+40],edx
	mov	[AReg+80],edx
	mov	[AReg+128],edx
	mov	[AReg+176],edx

	;; Build the 1st row of the matrix
	
	mov	DReg,[STACK_PTR1]

	movaps	xmm0,[AReg]
	movaps	xmm1,[AReg+16]
	movaps	xmm2,[AReg+32]
	movaps	xmm3,[AReg+48]
	movaps	xmm4,[AReg+64]
	movaps	xmm5,[AReg+80]

	mulps	xmm0,xmm1
	mulps	xmm0,xmm2

	mulps	xmm3,xmm4
	mulps	xmm3,xmm5

	haddps	xmm0,xmm3
	movaps	[DReg],xmm0

	;; Build the second row of the matrix

	movaps	xmm0,[AReg+96]
	movaps	xmm1,[AReg+112]
	movaps	xmm2,[AReg+128]
	movaps	xmm3,[AReg+144]
	movaps	xmm4,[AReg+160]
	movaps	xmm5,[AReg+176]

	mulps	xmm0,xmm1
	mulps	xmm0,xmm2

	mulps	xmm3,xmm4
	mulps	xmm3,xmm5

	haddps	xmm0,xmm3
	movaps	[DReg+16],xmm0

	;; Build the 3rd row of the matrix

	movaps	xmm0,[AReg+192]
	movaps	xmm1,[AReg+208]
	movaps	xmm2,[AReg+224]
	movaps	xmm3,[AReg+240]

	mulps	xmm0,xmm1
	mulps	xmm2,xmm3

	haddps	xmm0,xmm2
	movaps	[DReg+32],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret
%endif

;;;
;;; Mat3ScaleAsm
;;;
;;; Call Stack
;;;
;;; [4] const float x_scale
;;; [3] const float y_scale
;;; [2] const float z_scale
;;; [1] mat3*       m
;;; [0] ret
;;;
;;; extern "C" void Mat3ScaleAsm(mat3& r,const float x_scale,const float y_scale,const float z_scale)
;;;

_Mat3ScaleAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg

	mov	AReg,[STACK_PTR1]	; *r

	mov	ebx,[STACK_PTR2]	; m00
	mov	[AReg],ebx

	mov	ebx,[STACK_PTR3]	; m11
	mov	[AReg+20],ebx

	mov	ebx,[STACK_PTR4]	; m22
	mov	[AReg+40],ebx

	mov	ebx,[zeroVec]
	mov	[AReg+4], ebx		; m01
	mov	[AReg+8], ebx		; m02
	mov	[AReg+12],ebx		; m03
	mov	[AReg+16],ebx		; m10
	mov	[AReg+24],ebx		; m12
	mov	[AReg+28],ebx		; m13
	mov	[AReg+32],ebx		; m20
	mov	[AReg+36],ebx		; m21
	mov	[AReg+44],ebx		; m23

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]

	ret

;;;
;;; Mat3ScaleByVec3Asm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] mat3* r
;;;
;;; extern "C" void Mat3ScaleByVec3Asm(mat3* r,const vec3* v);
;;;

_Mat3ScaleByVec3Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; *v

	mov	edx,[zeroVec]
	mov	[AReg+4], edx		; m01
	mov	[AReg+8], edx		; m02
	mov	[AReg+12],edx		; m03
	mov	[AReg+16],edx		; m10
	mov	[AReg+24],edx		; m12
	mov	[AReg+28],edx		; m13
	mov	[AReg+32],edx		; m20
	mov	[AReg+36],edx		; m21
	mov	[AReg+44],edx		; m23

	mov	edx,[BReg]		; m00
	mov	[AReg],edx

	mov	edx,[BReg+4]		; m11
	mov	[AReg+20],edx

	mov	edx,[BReg+8]		; m22
	mov	[AReg+40],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%if 0
;;;
;;; Mat4RHTranslateAsm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4TranslateRHAsm(mat4& m,const vec3& v)
;;;

	;; XXX:	This needs to be completed (translate embedded matrix)

_Mat4TranslateRH_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR2]

	mov	eax,[zeroVec]
	mov	[DReg+12],eax		; v.x x.y v.z 0.0

	mov	AReg,[STACK_PTR1]

	movaps	xmm0,[AReg]		; m00 m01 m02 m03
	movaps	xmm1,[AReg+16]		; m10 m11 m12 m13
	movaps	xmm2,[AReg+32]		; m20 m21 m22 m23
	movaps	xmm3,[AReg+48]		; m30 m31 m32 m33

	movaps	xmm4,[DReg]		; v.x v.y v.z 0.0
	movaps	xmm5,[zeroVec]		; 0.0 0.0 0.0 0.0

	mulps	xmm0,xmm4		; m00*v.x m01*v.y m02*v.z 0.0
	mulps	xmm1,xmm4		; m10*v.x m11*v.y m12*v.z 0.0
	mulps	xmm2,xmm4		; m20*v.x m21*v.y m22*v.z 0.0
	mulps	xmm3,xmm4		; m30*v.x m31*v.y m32*v.z 0.0

	haddps	xmm0,xmm5		; sum(m0? * v)
	haddps	xmm0,xmm5

	haddps	xmm1,xmm5		; sum(m1? * v)
	haddps	xmm1,xmm5

	haddps	xmm2,xmm5		; sum(m2? * v)
	haddps	xmm2,xmm5

	haddps	xmm3,xmm5		; sum(m2? * v)
	haddps	xmm3,xmm5

	addss	xmm0,[AReg+12]		; m03 += sum(v0? * v)
	addss	xmm1,[AReg+28]		; m13 += sum(v1? * v)
	addss	xmm2,[AReg+44]		; m23 += sum(v2? * v)
	addss	xmm3,[AReg+60]		; m33 += sum(v3? * v)

	movss	[AReg+12],xmm0		; Right Hand:	Save the last column
	movss	[AReg+28],xmm1
	movss	[AReg+44],xmm2
	movss	[AReg+60],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RHTranslateRH_FPU_Asm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4TranslateRH_FPU_Asm(mat4& m,const vec3& v)
;;;

_Mat4TranslateRH_FPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR2]

	mov	eax,[zeroVec]
	mov	[DReg+12],eax

	mov	AReg,[STACK_PTR1]

	movaps	xmm0,[AReg]
	movaps	xmm1,[AReg+16]
	movaps	xmm2,[AReg+32]
	movaps	xmm3,[AReg+48]

	movaps	xmm4,[DReg]
	movaps	xmm5,[zeroVec]
	movaps	xmm6,xmm0		; temporary storage area

	mulps	xmm0,xmm4
	mulps	xmm1,xmm4
	mulps	xmm2,xmm4
	mulps	xmm3,xmm4

	;; 	haddps	xmm3,xmm5
	;; 	haddps	xmm3,xmm5

	movaps	[AReg],xmm3

	fld	dword [AReg]
	fadd	dword [AReg+4]
	fadd	dword [AReg+8]
	fwait

	;; 	haddps	xmm2,xmm5
	;; 	haddps	xmm2,xmm5

	movaps	[AReg],xmm2

	fld	dword [AReg]
	fadd	dword [AReg+4]
	fadd	dword [AReg+8]
	fwait

	;; 	haddps	xmm1,xmm5
	;; 	haddps	xmm1,xmm5

	movaps	[AReg],xmm1

	fld	dword [AReg]
	fadd	dword [AReg+4]
	fadd	dword [AReg+8]
	fwait

	;; 	haddps	xmm0,xmm5
	;; 	haddps	xmm0,xmm5

	movaps	[AReg],xmm0

	fld	dword [AReg]
	fadd	dword [AReg+4]
	fadd	dword [AReg+8]
	fwait

	movaps	[AReg],xmm6		; restore the vector

	fadd	dword [AReg+12]		; e03 += sum(m0? * v)
	fstp	dword [AReg+12]

	fadd	dword [AReg+28]		; e13 += sum(v1? * v)
	fstp	dword [AReg+28]

	fadd	dword [AReg+44]		; e23 += sum(v2? * v)
	fstp	dword [AReg+44]

	fadd	dword [AReg+60]		; e33 += sum(v3? * v)
	fstp	dword [AReg+60]

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret
%endif

;;;
;;; Mat4CopyAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4CopyAsm(mat4* r,const mat4* m);
;;;

_Mat4CopyAsm:

	mov	[STACK_SAVE1],Srcp
	mov	[STACK_SAVE2],Dstp
	mov	[STACK_SAVE3],CReg

	mov	CReg,16
	mov	Dstp,[STACK_PTR1]
	mov	Srcp,[STACK_PTR2]
	cld

	rep	movsd

	mov	Srcp,[STACK_SAVE1]
	mov	Dstp,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat4NegateAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4NegateAsm(mat4* r,mat4* m)
;;;

_Mat4NegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]

	movaps	xmm0,[DReg]
	movaps	xmm1,[DReg+16]
	movaps	xmm2,[DReg+32]
	movaps	xmm3,[DReg+48]
	movaps	xmm4,[negVec]

	mulps	xmm0,xmm4
	mulps	xmm1,xmm4
	mulps	xmm2,xmm4
	mulps	xmm3,xmm4

	movaps	[AReg],xmm0
	movaps	[AReg+16],xmm1
	movaps	[AReg+32],xmm2
	movaps	[AReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4NegateMatrixAsm
;;;
;;; Call Stack
;;;
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4NegateMatrixAsm(mat4& r)
;;;

_Mat4NegateMatrixAsm:

	mov	[STACK_SAVE1],AReg

	mov	AReg,[STACK_PTR1]

	movaps	xmm0,[AReg]
	movaps	xmm1,[AReg+16]
	movaps	xmm2,[AReg+32]
	movaps	xmm3,[AReg+48]
	movaps	xmm4,[negVec]

	mulps	xmm0,xmm4
	mulps	xmm1,xmm4
	mulps	xmm2,xmm4
	mulps	xmm3,xmm4

	movaps	[AReg],xmm0
	movaps	[AReg+16],xmm1
	movaps	[AReg+32],xmm2
	movaps	[AReg+48],xmm3

	mov	AReg,[STACK_SAVE1]

	ret

;;;
;;; Mat4AddAsm
;;;
;;; Call Stack
;;; 
;;; [3] mat4* n
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4Add(mat4* r,const mat4* m,const mat4* n);
;;;

_Mat4AddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	movaps	xmm0,[AReg]
	movaps	xmm1,[AReg+16]
	movaps	xmm2,[AReg+32]
	movaps	xmm3,[AReg+48]

	addps	xmm0,[BReg]
	addps	xmm1,[BReg+16]
	addps	xmm2,[BReg+32]
	addps	xmm3,[BReg+48]

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2
	movaps	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4AddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4AddFloatAsm(mat4* r,const mat4* m,const float s);
;;;

_Mat4AddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movaps	xmm1,[AReg]		; m
	movaps	xmm2,[AReg+16]
	movaps	xmm3,[AReg+32]
	movaps	xmm4,[AReg+48]

	addps	xmm1,xmm0		; m+s
	addps	xmm2,xmm0
	addps	xmm3,xmm0
	addps	xmm4,xmm0

	movaps	[DReg],xmm1		; r
	movaps	[DReg+16],xmm2
	movaps	[DReg+32],xmm3
	movaps	[DReg+48],xmm4

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4AddMatrixAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* n
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4AddMatrixAsm(mat4& m,const mat4& n)
;;;

_Mat4AddMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR1]

	movaps	xmm0,[DReg]
	movaps	xmm1,[DReg+16]
	movaps	xmm2,[DReg+32]
	movaps	xmm3,[DReg+48]

	addps	xmm0,[AReg]
	addps	xmm1,[AReg+16]
	addps	xmm2,[AReg+32]
	addps	xmm3,[AReg+48]

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2
	movaps	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4SubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] mat4* n
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4SubtractAsm(mat4* r,mat4* m,const mat4* n)
;;;

_Mat4SubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	movaps	xmm0,[AReg]
	movaps	xmm1,[AReg+16]
	movaps	xmm2,[AReg+32]
	movaps	xmm3,[AReg+48]

	subps	xmm0,[BReg]
	subps	xmm1,[BReg+16]
	subps	xmm2,[BReg+32]
	subps	xmm3,[BReg+48]

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2
	movaps	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4SubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4SubtractFloatAsm(mat4* r,const mat4* m,const float s);
;;;

_Mat4SubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movaps	xmm1,[AReg]		; m
	movaps	xmm2,[AReg+16]
	movaps	xmm3,[AReg+32]
	movaps	xmm4,[AReg+48]

	subps	xmm1,xmm0		; m-x
	subps	xmm2,xmm0
	subps	xmm3,xmm0
	subps	xmm4,xmm0

	movaps	[DReg],xmm1		; r
	movaps	[DReg+16],xmm2
	movaps	[DReg+32],xmm3
	movaps	[DReg+48],xmm4

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4SubtractMatrixAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* n
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4SubtractMatrixAsm(mat4& m,const mat4& n)
;;; 

_Mat4SubtractMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]

	movaps	xmm0,[DReg]
	movaps	xmm1,[DReg+16]
	movaps	xmm2,[DReg+32]
	movaps	xmm3,[DReg+48]

	subps	xmm0,[AReg]
	subps	xmm1,[AReg+16]
	subps	xmm2,[AReg+32]
	subps	xmm3,[AReg+48]

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2
	movaps	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4MultiplyMatrixAsm
;;;
;;; Call Stack
;;; 
;;; [2] mat4* n
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4MultiplyMatrixAsm(mat4* m,const mat4* n)
;;;

_Mat4MultiplyMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]

	movaps	xmm4,[DReg]			; n00 n01 n02 n03
	movaps	xmm5,[DReg+16]			; n10 n11 n12 n13
	movaps	xmm6,[DReg+32]			; n20 n21 n22 n23
	movaps	xmm7,[DReg+48]			; n30 n31 n32 n33

	movaps	xmm0,[AReg]			; m00 m01 m02 m03
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m00 m00 m00 m00
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m01 m01 m01 m01
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m02 m02 m02 m02
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m03 m03 m03 m03

	mulps	xmm0,xmm4			; m00*n00 m00*n01 m00*n02 m00*n03
	mulps	xmm1,xmm5			; m01*n10 m01*n11 m01*n12 m01*n13
	mulps	xmm2,xmm6			; m02*n20 m02*n21 m02*n22 m02*n23
	mulps	xmm3,xmm7			; m03*n30 m03*n31 m03*n32 m03*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m00*n00+m01*n10+m02*n20+m03*n30
						; m00*n01+m01*n11+m03*n21+m03*n31
						; m00*n02+m01*n12+m02*n22+m03*n32
						; m00*n03+m01*n13+m02*n23+m03*n33

	movaps	[AReg],xmm0

	movaps	xmm0,[AReg+16]			; m10 m11 m12 m13
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m10 m10 m10 m10
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m11 m11 m11 m11
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m12 m12 m12 m12
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m13 m13 m13 m13

	mulps	xmm0,xmm4			; m10*n00 m10*n01 m10*n02 m10*n03
	mulps	xmm1,xmm5			; m11*n10 m11*n11 m11*n12 m11*n13
	mulps	xmm2,xmm6			; m12*n20 m12*n21 m12*n22 m12*n23
	mulps	xmm3,xmm7			; m13*n30 m13*m31 m13*n32 m13*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m10*n00+m11*n10+m12*n20+n13*n30
						; m10*n01+m11*n11+m12*n21+m13*n31
						; m10*n02+m11*n12+m12*n22+m13*n32
						; m10*n03+m11*n13+m12*n23+m13*n33

	movaps	[AReg+16],xmm0

	movaps	xmm0,[AReg+32]			; m20 m21 m22 m23
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m20 m20 m20 m20
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m21 m21 m21 m21
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m22 m22 m22 m22
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m23 m23 m23 m23

	mulps	xmm0,xmm4			; m20*n00 m20*n01 m20*n02 m20*n03
	mulps	xmm1,xmm5			; m21*n10 m21*n11 m21*n12 m21*n13
	mulps	xmm2,xmm6			; m22*n20 m22*n21 m22*n22 m22*n23
	mulps	xmm3,xmm7			; m23*n30 m23*n31 m23*n32 m23*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m20*n00+m21*n10+m22*n20+m23*n30
						; m20*n01+m21*n11+m22*n21+m23*n31
						; m20*n02+m21*n12+m22*n22+m23*n32
						; m20*n03+m21*n13+m22*n23+m23*n33

	movaps	[AReg+32],xmm0			; m30 m31 m32 m33

	movaps	xmm0,[AReg+48]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m30 m30 m30 m30
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m31 m31 m31 m31
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m32 m32 m32 m32
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m33 m33 m33 m33

	mulps	xmm0,xmm4			; m30*n00 m30*n01 m30*n02 m30*n03
	mulps	xmm1,xmm5			; m31*n10 m31*n11 m31*n12 m31*n13
	mulps	xmm2,xmm6			; m32*n20 m32*n21 m32*n22 m32*n23
	mulps	xmm3,xmm7			; m33*n30 m33*n31 m33*n32 m33*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m30*n00+m31*n10+m32*n20+m33*n30
						; m30*n01+m31*n11+m32*n21+m33*n31
						; m30*n02+m31*n12+m32*n22+m33*n32
						; m30*n03+m31*n13+m32*n23+m33*n33

	movaps	[AReg+48],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4MultiplyAsm
;;;
;;; Call Stack
;;; 
;;; [3] mat4* n
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4MultiplyAsm(mat4* r,mat4* m,const mat4* n)
;;;

_Mat4MultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	movaps	xmm4,[BReg]			; n00 n01 n02 n03
	movaps	xmm5,[BReg+16]			; n10 n11 n12 n13
	movaps	xmm6,[BReg+32]			; n20 n21 n22 n23
	movaps	xmm7,[BReg+48]			; n30 n31 n32 n33

	movaps	xmm0,[AReg]			; m00 m01 m02 m03
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m00 m00 m00 m00
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m01 m01 m01 m01
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m02 m02 m02 m02
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m03 m03 m03 m03

	mulps	xmm0,xmm4			; m00*n00 m00*n01 m00*n02 m00*n03
	mulps	xmm1,xmm5			; m01*n10 m01*n11 m01*n12 m01*n13
	mulps	xmm2,xmm6			; m02*n20 m02*n21 m02*n22 m02*n23
	mulps	xmm3,xmm7			; m03*n30 m03*n31 m03*n32 m03*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m00*n00+m01*n10+m02*n20+m03*n30
						; m00*n01+m01*n11+m03*n21+m03*n31
						; m00*n02+m01*n12+m02*n22+m03*n32
						; m00*n03+m01*n13+m02*n23+m03*n33

	movaps	[DReg],xmm0

	movaps	xmm0,[AReg+16]			; m10 m11 m12 m13
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m10 m10 m10 m10
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m11 m11 m11 m11
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m12 m12 m12 m12
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m13 m13 m13 m13

	mulps	xmm0,xmm4			; m10*n00 m10*n01 m10*n02 m10*n03
	mulps	xmm1,xmm5			; m11*n10 m11*n11 m11*n12 m11*n13
	mulps	xmm2,xmm6			; m12*n20 m12*n21 m12*n22 m12*n23
	mulps	xmm3,xmm7			; m13*n30 m13*m31 m13*n32 m13*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m10*n00+m11*n10+m12*n20+n13*n30
						; m10*n01+m11*n11+m12*n21+m13*n31
						; m10*n02+m11*n12+m12*n22+m13*n32
						; m10*n03+m11*n13+m12*n23+m13*n33

	movaps	[DReg+16],xmm0

	movaps	xmm0,[AReg+32]			; m20 m21 m22 m23
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m20 m20 m20 m20
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m21 m21 m21 m21
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m22 m22 m22 m22
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m23 m23 m23 m23

	mulps	xmm0,xmm4			; m20*n00 m20*n01 m20*n02 m20*n03
	mulps	xmm1,xmm5			; m21*n10 m21*n11 m21*n12 m21*n13
	mulps	xmm2,xmm6			; m22*n20 m22*n21 m22*n22 m22*n23
	mulps	xmm3,xmm7			; m23*n30 m23*n31 m23*n32 m23*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m20*n00+m21*n10+m22*n20+m23*n30
						; m20*n01+m21*n11+m22*n21+m23*n31
						; m20*n02+m21*n12+m22*n22+m23*n32
						; m20*n03+m21*n13+m22*n23+m23*n33

	movaps	[DReg+32],xmm0			; m30 m31 m32 m33

	movaps	xmm0,[AReg+48]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m30 m30 m30 m30
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m31 m31 m31 m31
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m32 m32 m32 m32
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m33 m33 m33 m33

	mulps	xmm0,xmm4			; m30*n00 m30*n01 m30*n02 m30*n03
	mulps	xmm1,xmm5			; m31*n10 m31*n11 m31*n12 m31*n13
	mulps	xmm2,xmm6			; m32*n20 m32*n21 m32*n22 m32*n23
	mulps	xmm3,xmm7			; m33*n30 m33*n31 m33*n32 m33*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m30*n00+m31*n10+m32*n20+m33*n30
						; m30*n01+m31*n11+m32*n21+m33*n31
						; m30*n02+m31*n12+m32*n22+m33*n32
						; m30*n03+m31*n13+m32*n23+m33*n33

	movaps	[DReg+48],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4MultiplyVecAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] mat4* m
;;; [1] vec4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4MultiplyVecAsm(vec4& r,const mat4& m,const vec4& v)
;;;

_Mat4MultiplyVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	movaps	xmm0,[AReg]			; m00 m01 m02 m03
	movaps	xmm1,[AReg+16]			; m10 m11 m12 m13
	movaps	xmm2,[AReg+32]			; m20 m21 m22 m23
	movaps	xmm3,[AReg+48]			; m30 m31 m32 m33

	movaps	xmm4,[BReg]			;  vx  vy  vz  vw

	mulps	xmm0,xmm4			; vx*m00 vy*m01 vz*m02 vw*m03
	mulps	xmm1,xmm4			; vx*m10 vy*m11 vz*m12 vw*m13
	mulps	xmm2,xmm4			; vx*m20 vy*m21 vz*m22 vw*m23
	mulps	xmm3,xmm4			; vx*m30 vy*m31 vy*m32 vw*m33

	movaps	 xmm4,xmm0
	unpcklpd xmm4,xmm1			; vx*m00 vy*m01 vx*m10 vy*m11
	movaps	 xmm5,xmm2
	unpcklpd xmm5,xmm3			; vx*m20 vy*m21 vx*m30 vy*m31
	movaps	 xmm6,xmm4
	shufps	 xmm4,xmm5,SHUFFLE(0,2,0,2)	; vx*m00 vx*m10 vx*m20 vx*m30
	shufps	 xmm6,xmm5,SHUFFLE(1,3,1,3)	; vy*m01 vy*m11 vy*m21 vy*m31

	unpckhpd xmm0,xmm1			; vz*m02 vw*m03 vz*m12 vz*m13
	unpckhpd xmm2,xmm3			; vz*m22 vw*m23 vz*m32 vw*m33
	movaps	 xmm3,xmm0
	shufps	 xmm0,xmm2,SHUFFLE(0,2,0,2)	; vz*m02 vz*m12 vz*m22 vz*m32
	shufps	 xmm3,xmm2,SHUFFLE(1,3,1,3)	; vw*m03 vw*m13 vw*m23 vw*m33

	addps	xmm0,xmm3
	addps	xmm0,xmm4
	addps	xmm0,xmm6

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat4uNegateAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4uNegateAsm(mat4* r,mat4* m)
;;;

_Mat4uNegateAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]

	movups	xmm0,[DReg]
	movups	xmm1,[DReg+16]
	movups	xmm2,[DReg+32]
	movups	xmm3,[DReg+48]
	movaps	xmm4,[negVec]

	mulps	xmm0,xmm4
	mulps	xmm1,xmm4
	mulps	xmm2,xmm4
	mulps	xmm3,xmm4

	movups	[AReg],xmm0
	movups	[AReg+16],xmm1
	movups	[AReg+32],xmm2
	movups	[AReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uNegateMatrixAsm
;;;
;;; Call Stack
;;;
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4uNegateMatrixAsm(mat4& r)
;;;

_Mat4uNegateMatrixAsm:

	mov	[STACK_SAVE1],AReg

	mov	AReg,[STACK_PTR1]

	movups	xmm0,[AReg]
	movups	xmm1,[AReg+16]
	movups	xmm2,[AReg+32]
	movups	xmm3,[AReg+48]
	movaps	xmm4,[negVec]

	mulps	xmm0,xmm4
	mulps	xmm1,xmm4
	mulps	xmm2,xmm4
	mulps	xmm3,xmm4

	movups	[AReg],xmm0
	movups	[AReg+16],xmm1
	movups	[AReg+32],xmm2
	movups	[AReg+48],xmm3

	mov	AReg,[STACK_SAVE1]

	ret

;;;
;;; Mat4uAddAsm
;;;
;;; Call Stack
;;; 
;;; [3] mat4* n
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4uAdd(mat4* r,const mat4* m,const mat4* n);
;;;

_Mat4uAddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	movups	xmm0,[AReg]
	movups	xmm1,[AReg+16]
	movups	xmm2,[AReg+32]
	movups	xmm3,[AReg+48]

	movups	xmm4,[BReg]
	movups	xmm5,[BReg+16]
	movups	xmm6,[BReg+32]
	movups	xmm7,[BReg+48]

	addps	xmm0,xmm4
	addps	xmm1,xmm5
	addps	xmm2,xmm6
	addps	xmm3,xmm7

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2
	movups	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4uAddFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4uAddFloatAsm(mat4* r,const mat4* m,const float s);
;;;

_Mat4uAddFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movups	xmm1,[AReg]		; m
	movups	xmm2,[AReg+16]
	movups	xmm3,[AReg+32]
	movups	xmm4,[AReg+48]

	addps	xmm1,xmm0		; m+s
	addps	xmm2,xmm0
	addps	xmm3,xmm0
	addps	xmm4,xmm0

	movups	[DReg],xmm1		; r
	movups	[DReg+16],xmm2
	movups	[DReg+32],xmm3
	movups	[DReg+48],xmm4

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uAddMatrixAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* n
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4uAddMatrixAsm(const mat4& m,const mat4& n)
;;;

_Mat4uAddMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR1]

	movups	xmm0,[DReg]
	movups	xmm1,[DReg+16]
	movups	xmm2,[DReg+32]
	movups	xmm3,[DReg+48]

	movups	xmm4,[AReg]
	movups	xmm5,[AReg+16]
	movups	xmm6,[AReg+32]
	movups	xmm7,[AReg+48]

	addps	xmm0,xmm4
	addps	xmm1,xmm5
	addps	xmm2,xmm6
	addps	xmm3,xmm7

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2
	movups	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uSubtractAsm
;;;
;;; Call Stack
;;;
;;; [3] mat4* n
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4uSubtractAsm(mat4* r,mat4* m,const mat4* n)
;;;

_Mat4uSubtractAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	movups	xmm0,[AReg]
	movups	xmm1,[AReg+16]
	movups	xmm2,[AReg+32]
	movups	xmm3,[AReg+48]

	movups	xmm4,[BReg]
	movups	xmm5,[BReg+16]
	movups	xmm6,[BReg+32]
	movups	xmm7,[BReg+48]

	subps	xmm0,xmm4
	subps	xmm1,xmm5
	subps	xmm2,xmm6
	subps	xmm3,xmm7

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2
	movups	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4uSubtractFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float s
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4uSubtractFloatAsm(mat4* r,const mat4* m,const float s);
;;;

_Mat4uSubtractFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	movss	xmm0,[STACK_PTR3]	; s
	shufps	xmm0,xmm0,0

	movups	xmm1,[AReg]		; m
	movups	xmm2,[AReg+16]
	movups	xmm3,[AReg+32]
	movups	xmm4,[AReg+48]

	subps	xmm1,xmm0		; m-s
	subps	xmm2,xmm0
	subps	xmm3,xmm0
	subps	xmm4,xmm0

	movups	[DReg],xmm1		; r
	movups	[DReg+16],xmm2
	movups	[DReg+32],xmm3
	movups	[DReg+48],xmm4

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uSubtractMatrixAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* n
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4uSubtractMatrixAsm(mat4& m,const mat4& n)
;;;

_Mat4uSubtractMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]

	movups	xmm0,[DReg]
	movups	xmm1,[DReg+16]
	movups	xmm2,[DReg+32]
	movups	xmm3,[DReg+48]

	movups	xmm4,[AReg]
	movups	xmm5,[AReg+16]
	movups	xmm6,[AReg+32]
	movups	xmm7,[AReg+48]

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2
	movups	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uMultiplyMatrixAsm
;;;
;;; Call Stack
;;; 
;;; [2] mat4* n
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4uMultiplyMatrixAsm(mat4* m,const mat4* n)
;;;

_Mat4uMultiplyMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]
	mov	DReg,[STACK_PTR2]

	movups	xmm4,[DReg]			; n00 n01 n02 n03
	movups	xmm5,[DReg+16]			; n10 n11 n12 n13
	movups	xmm6,[DReg+32]			; n20 n21 n22 n23
	movups	xmm7,[DReg+48]			; n30 n31 n32 n33

	movups	xmm0,[AReg]			; m00 m01 m02 m03
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m00 m00 m00 m00
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m01 m01 m01 m01
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m02 m02 m02 m02
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m03 m03 m03 m03

	mulps	xmm0,xmm4			; m00*n00 m00*n01 m00*n02 m00*n03
	mulps	xmm1,xmm5			; m01*n10 m01*n11 m01*n12 m01*n13
	mulps	xmm2,xmm6			; m02*n20 m02*n21 m02*n22 m02*n23
	mulps	xmm3,xmm7			; m03*n30 m03*n31 m03*n32 m03*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m00*n00+m01*n10+m02*n20+m03*n30
						; m00*n01+m01*n11+m03*n21+m03*n31
						; m00*n02+m01*n12+m02*n22+m03*n32
						; m00*n03+m01*n13+m02*n23+m03*n33

	movups	[AReg],xmm0

	movups	xmm0,[AReg+16]			; m10 m11 m12 m13
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m10 m10 m10 m10
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m11 m11 m11 m11
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m12 m12 m12 m12
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m13 m13 m13 m13

	mulps	xmm0,xmm4			; m10*n00 m10*n01 m10*n02 m10*n03
	mulps	xmm1,xmm5			; m11*n10 m11*n11 m11*n12 m11*n13
	mulps	xmm2,xmm6			; m12*n20 m12*n21 m12*n22 m12*n23
	mulps	xmm3,xmm7			; m13*n30 m13*m31 m13*n32 m13*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m10*n00+m11*n10+m12*n20+n13*n30
						; m10*n01+m11*n11+m12*n21+m13*n31
						; m10*n02+m11*n12+m12*n22+m13*n32
						; m10*n03+m11*n13+m12*n23+m13*n33

	movups	[AReg+16],xmm0

	movups	xmm0,[AReg+32]			; m20 m21 m22 m23
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m20 m20 m20 m20
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m21 m21 m21 m21
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m22 m22 m22 m22
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m23 m23 m23 m23

	mulps	xmm0,xmm4			; m20*n00 m20*n01 m20*n02 m20*n03
	mulps	xmm1,xmm5			; m21*n10 m21*n11 m21*n12 m21*n13
	mulps	xmm2,xmm6			; m22*n20 m22*n21 m22*n22 m22*n23
	mulps	xmm3,xmm7			; m23*n30 m23*n31 m23*n32 m23*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m20*n00+m21*n10+m22*n20+m23*n30
						; m20*n01+m21*n11+m22*n21+m23*n31
						; m20*n02+m21*n12+m22*n22+m23*n32
						; m20*n03+m21*n13+m22*n23+m23*n33

	movups	[AReg+32],xmm0			; m30 m31 m32 m33

	movups	xmm0,[AReg+48]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m30 m30 m30 m30
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m31 m31 m31 m31
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m32 m32 m32 m32
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m33 m33 m33 m33

	mulps	xmm0,xmm4			; m30*n00 m30*n01 m30*n02 m30*n03
	mulps	xmm1,xmm5			; m31*n10 m31*n11 m31*n12 m31*n13
	mulps	xmm2,xmm6			; m32*n20 m32*n21 m32*n22 m32*n23
	mulps	xmm3,xmm7			; m33*n30 m33*n31 m33*n32 m33*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m30*n00+m31*n10+m32*n20+m33*n30
						; m30*n01+m31*n11+m32*n21+m33*n31
						; m30*n02+m31*n12+m32*n22+m33*n32
						; m30*n03+m31*n13+m32*n23+m33*n33

	movups	[AReg+48],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uMultiplyAsm
;;;
;;; Call Stack
;;; 
;;; [3] mat4* n
;;; [2] mat4* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4uMultiplyAsm(mat4* r,mat4* m,const mat4* n)
;;;

_Mat4uMultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	movups	xmm4,[BReg]			; n00 n01 n02 n03
	movups	xmm5,[BReg+16]			; n10 n11 n12 n13
	movups	xmm6,[BReg+32]			; n20 n21 n22 n23
	movups	xmm7,[BReg+48]			; n30 n31 n32 n33

	movups	xmm0,[AReg]			; m00 m01 m02 m03
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m00 m00 m00 m00
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m01 m01 m01 m01
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m02 m02 m02 m02
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m03 m03 m03 m03

	mulps	xmm0,xmm4			; m00*n00 m00*n01 m00*n02 m00*n03
	mulps	xmm1,xmm5			; m01*n10 m01*n11 m01*n12 m01*n13
	mulps	xmm2,xmm6			; m02*n20 m02*n21 m02*n22 m02*n23
	mulps	xmm3,xmm7			; m03*n30 m03*n31 m03*n32 m03*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m00*n00+m01*n10+m02*n20+m03*n30
						; m00*n01+m01*n11+m03*n21+m03*n31
						; m00*n02+m01*n12+m02*n22+m03*n32
						; m00*n03+m01*n13+m02*n23+m03*n33

	movups	[DReg],xmm0

	movups	xmm0,[AReg+16]			; m10 m11 m12 m13
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m10 m10 m10 m10
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m11 m11 m11 m11
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m12 m12 m12 m12
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m13 m13 m13 m13

	mulps	xmm0,xmm4			; m10*n00 m10*n01 m10*n02 m10*n03
	mulps	xmm1,xmm5			; m11*n10 m11*n11 m11*n12 m11*n13
	mulps	xmm2,xmm6			; m12*n20 m12*n21 m12*n22 m12*n23
	mulps	xmm3,xmm7			; m13*n30 m13*m31 m13*n32 m13*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m10*n00+m11*n10+m12*n20+n13*n30
						; m10*n01+m11*n11+m12*n21+m13*n31
						; m10*n02+m11*n12+m12*n22+m13*n32
						; m10*n03+m11*n13+m12*n23+m13*n33

	movups	[DReg+16],xmm0

	movups	xmm0,[AReg+32]			; m20 m21 m22 m23
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m20 m20 m20 m20
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m21 m21 m21 m21
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m22 m22 m22 m22
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m23 m23 m23 m23

	mulps	xmm0,xmm4			; m20*n00 m20*n01 m20*n02 m20*n03
	mulps	xmm1,xmm5			; m21*n10 m21*n11 m21*n12 m21*n13
	mulps	xmm2,xmm6			; m22*n20 m22*n21 m22*n22 m22*n23
	mulps	xmm3,xmm7			; m23*n30 m23*n31 m23*n32 m23*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m20*n00+m21*n10+m22*n20+m23*n30
						; m20*n01+m21*n11+m22*n21+m23*n31
						; m20*n02+m21*n12+m22*n22+m23*n32
						; m20*n03+m21*n13+m22*n23+m23*n33

	movups	[DReg+32],xmm0			; m30 m31 m32 m33

	movups	xmm0,[AReg+48]
	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,0,0,0)	; m30 m30 m30 m30
	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)	; m31 m31 m31 m31
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)	; m32 m32 m32 m32
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)	; m33 m33 m33 m33

	mulps	xmm0,xmm4			; m30*n00 m30*n01 m30*n02 m30*n03
	mulps	xmm1,xmm5			; m31*n10 m31*n11 m31*n12 m31*n13
	mulps	xmm2,xmm6			; m32*n20 m32*n21 m32*n22 m32*n23
	mulps	xmm3,xmm7			; m33*n30 m33*n31 m33*n32 m33*n33

	addps	xmm0,xmm1
	addps	xmm0,xmm2
	addps	xmm0,xmm3			; m30*n00+m31*n10+m32*n20+m33*n30
						; m30*n01+m31*n11+m32*n21+m33*n31
						; m30*n02+m31*n12+m32*n22+m33*n32
						; m30*n03+m31*n13+m32*n23+m33*n33

	movups	[DReg+48],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4uMultiplyVecAsm
;;;
;;; Call Stack
;;;
;;; [3] vec4* v
;;; [2] mat4* m
;;; [1] vec3* r
;;; [0] ret
;;;
;;; extern "C" void Mat4uMultiplyVecAsm(vec4& r,const mat4& m,const vec4& v)
;;;

_Mat4uMultiplyVecAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]
	mov	BReg,[STACK_PTR3]

	movups	xmm0,[AReg]			; m00 m01 m02 m03
	movups	xmm1,[AReg+16]			; m10 m11 m12 m13
	movups	xmm2,[AReg+32]			; m20 m21 m22 m23
	movups	xmm3,[AReg+48]			; m30 m31 m32 m33

	movups	xmm4,[BReg]			;  vx  vy  vz  vw

	mulps	xmm0,xmm4			; vx*m00 vy*m01 vz*m02 vw*m03
	mulps	xmm1,xmm4			; vx*m10 vy*m11 vz*m12 vw*m13
	mulps	xmm2,xmm4			; vx*m20 vy*m21 vz*m22 vw*m23
	mulps	xmm3,xmm4			; vx*m30 vy*m31 vy*m32 vw*m33

	movaps	 xmm4,xmm0
	unpcklpd xmm4,xmm1			; vx*m00 vy*m01 vx*m10 vy*m11
	movaps	 xmm5,xmm2
	unpcklpd xmm5,xmm3			; vx*m20 vy*m21 vx*m30 vy*m31
	movaps	 xmm6,xmm4
	shufps	 xmm4,xmm5,SHUFFLE(0,2,0,2)	; vx*m00 vx*m10 vx*m20 vx*m30
	shufps	 xmm6,xmm5,SHUFFLE(1,3,1,3)	; vy*m01 vy*m11 vy*m21 vy*m31

	unpckhpd xmm0,xmm1			; vz*m02 vw*m03 vz*m12 vz*m13
	unpckhpd xmm2,xmm3			; vz*m22 vw*m23 vz*m32 vw*m33
	movaps	 xmm3,xmm0
	shufps	 xmm0,xmm2,SHUFFLE(0,2,0,2)	; vz*m02 vz*m12 vz*m22 vz*m32
	shufps	 xmm3,xmm2,SHUFFLE(1,3,1,3)	; vw*m03 vw*m13 vw*m23 vw*m33

	addps	xmm0,xmm3
	addps	xmm0,xmm4
	addps	xmm0,xmm6

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat4LookAtAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* at
;;; [2] vec3* from
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4LookAtAsm(mat4& r,const vec3* from,const vec3* at)
;;;

_Mat4LookAtAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *from
	mov	BReg,[STACK_PTR3]		; *at
	mov	edx,[zeroVec]

	mov	[AReg+12],edx			; zero out u/v.w
	mov	[BReg+12],edx

	mov	DReg,[STACK_PTR1]		; *r

	movaps	xmm6,[zeroVec]
	movaps	xmm7,[AReg]			; from

	movaps	xmm0,[BReg]			; at
	subps	xmm0,xmm7			; at - from

	movaps	xmm1,xmm0
	mulps	xmm1,xmm1			; sqr(at-from)

	haddps	xmm1,xmm6
	haddps	xmm1,xmm6

	sqrtss	xmm1,xmm1

	ucomiss xmm1,xmm6
	jne	Mat4LookAtCont1
	jmp	Mat4LookAtDB0

Mat4LookAtCont1:

	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1			; z = normalize(at-from)

	movaps	xmm1,xmm0
	mulss	xmm1,[negVec]			; -z.x z.y  z.z 0.0
	shufps	xmm1,xmm1,SHUFFLE(2,3,0,3)	;  z.z 0.0 -z.x 0.0

	movaps	xmm2,xmm1
	mulps	xmm2,xmm2

	haddps	xmm2,xmm6
	haddps	xmm2,xmm6

	sqrtss	xmm2,xmm2

	ucomiss	xmm2,xmm6
	jne	Mat4LookAtCont2
	jmp	Mat4LookAtDB0

Mat4LookAtCont2:

	shufps	xmm2,xmm2,0
	divps	xmm1,xmm2			; y = normalize(vec3(z.z,0,-z.x))

	movaps	xmm2,xmm0			; z
	movaps	xmm3,xmm0			; z
	movaps	xmm4,xmm1			; x
	movaps	xmm5,xmm1			; x

	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; z_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; z_zxy
	shufps	xmm4,xmm4,SHUFFLE(2,0,1,3)	; x_zxy
	shufps	xmm5,xmm5,SHUFFLE(1,2,0,3)	; x_yzx

	mulps	xmm2,xmm4			; u_yzx * v_zxy
	mulps	xmm3,xmm5			; u_zxy * v_yzx
	subps	xmm2,xmm3			; cross(z,x)

	movaps	xmm3,xmm2
	mulps	xmm3,xmm3

	haddps	xmm3,xmm6
	haddps	xmm3,xmm6

	sqrtss	xmm3,xmm3

	ucomiss	xmm3,xmm6
	jne	Mat4LookAtCont3
	jmp	Mat4LookAtDB0

Mat4LookAtCont3:

	shufps	xmm3,xmm3,0
	divps	xmm2,xmm3			; normalize(cross(z,x))

	movaps	[DReg+32],xmm0			; save z
	movaps	[DReg+16],xmm2			; save y
	movaps	[DReg],xmm1			; save x

	mulps	xmm7,[negVec]			; -from
	mulps	xmm0,xmm7			; translate(-from)
	mulps	xmm1,xmm7
	mulps	xmm2,xmm7

	movaps	xmm4,xmm1
	unpcklpd xmm4,xmm2
	movaps	xmm5,xmm4
	shufps	xmm4,xmm0,SHUFFLE(0,2,0,3)	; x,x,x,0.0
	shufps	xmm5,xmm0,SHUFFLE(1,3,1,3)	; y,y,y,0.0
	
	movaps	xmm6,xmm1
	unpckhpd xmm6,xmm2
	shufps	xmm6,xmm0,SHUFFLE(0,2,2,3)		; z,z,z,0.0

	addps	xmm4,xmm5
	addps	xmm4,xmm6

	movss	[DReg+12],xmm4
	shufps	xmm4,xmm4,SHUFFLE(1,2,1,2)
	movss	[DReg+28],xmm4
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	movss	[DReg+44],xmm4

	mov	eax,[zeroVec]
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Mat4LookAtDB0:
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp
	mov	[STACK_SAVE6],CReg

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]
	mov	CReg,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat4uLookAtAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* at
;;; [2] vec3* from
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4uLookAtAsm(mat4& r,const vec3* from,const vec3* at)
;;;

_Mat4uLookAtAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *from
	mov	BReg,[STACK_PTR3]		; *at
	mov	edx,[zeroVec]

	mov	[AReg+12],edx			; zero out u/v.w
	mov	[BReg+12],edx

	mov	DReg,[STACK_PTR1]		; *r

	movaps	xmm6,[zeroVec]
	movups	xmm7,[AReg]			; from

	movups	xmm0,[BReg]			; at
	subps	xmm0,xmm7			; at - from
	movaps	xmm1,xmm0

	mulps	xmm1,xmm1			; sqr(at-from)

	haddps	xmm1,xmm6
	haddps	xmm1,xmm6

	sqrtss	xmm1,xmm1

	ucomiss xmm1,xmm6
	jne	Mat4uLookAtCont1
	jmp	Mat4uLookAtDB0

Mat4uLookAtCont1:

	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1			; z = normalize(at-from)

	movaps	xmm1,xmm0
	mulss	xmm1,[negVec]			; -z.x z.y  z.z 0.0
	shufps	xmm1,xmm1,SHUFFLE(2,3,0,3)	;  z.z 0.0 -z.x 0.0

	movaps	xmm2,xmm1
	mulps	xmm2,xmm2

	haddps	xmm2,xmm6
	haddps	xmm2,xmm6

	sqrtss	xmm2,xmm2

	ucomiss	xmm2,xmm6
	jne	Mat4uLookAtCont2
	jmp	Mat4uLookAtDB0

Mat4uLookAtCont2:

	shufps	xmm2,xmm2,0
	divps	xmm1,xmm2			; y = normalize(vec3(z.z,0,-z.x))

	movaps	xmm2,xmm0			; z
	movaps	xmm3,xmm0			; z
	movaps	xmm4,xmm1			; x
	movaps	xmm5,xmm1			; x

	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; z_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; z_zxy
	shufps	xmm4,xmm4,SHUFFLE(2,0,1,3)	; x_zxy
	shufps	xmm5,xmm5,SHUFFLE(1,2,0,3)	; x_yzx

	mulps	xmm2,xmm4			; u_yzx * v_zxy
	mulps	xmm3,xmm5			; u_zxy * v_yzx
	subps	xmm2,xmm3			; cross(z,x)

	movaps	xmm3,xmm2
	mulps	xmm3,xmm3

	haddps	xmm3,xmm6
	haddps	xmm3,xmm6

	sqrtss	xmm3,xmm3

	ucomiss	xmm3,xmm6
	jne	Mat4uLookAtCont3
	jmp	Mat4uLookAtDB0

Mat4uLookAtCont3:

	shufps	xmm3,xmm3,0
	divps	xmm2,xmm3			; normalize(cross(z,x))

	movups	[DReg+32],xmm0			; save z
	movups	[DReg+16],xmm2			; save y
	movups	[DReg],xmm1			; save x

	mulps	xmm7,[negVec]			; -from
	mulps	xmm0,xmm7			; translate(-from)
	mulps	xmm1,xmm7
	mulps	xmm2,xmm7

	movaps	xmm4,xmm1
	unpcklpd xmm4,xmm2
	movaps	xmm5,xmm4
	shufps	xmm4,xmm0,SHUFFLE(0,2,0,3)	; x,x,x,0.0
	shufps	xmm5,xmm0,SHUFFLE(1,3,1,3)	; y,y,y,0.0
	
	movaps	xmm6,xmm1
	unpckhpd xmm6,xmm2
	shufps	xmm6,xmm0,SHUFFLE(0,2,2,3)		; z,z,z,0.0

	addps	xmm4,xmm5
	addps	xmm4,xmm6

	movss	[DReg+12],xmm4
	shufps	xmm4,xmm4,SHUFFLE(1,2,1,2)
	movss	[DReg+28],xmm4
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	movss	[DReg+44],xmm4

	mov	eax,[zeroVec]
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Mat4uLookAtDB0:
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp
	mov	[STACK_SAVE6],CReg

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]
	mov	CReg,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat4saLookAtAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* at
;;; [2] vec3* from
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4saLookAtAsm(mat4& r,const vec3* from,const vec3* at)
;;;

_Mat4saLookAtAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *from
	mov	BReg,[STACK_PTR3]		; *at
	mov	edx,[zeroVec]

	mov	[AReg+12],edx			; zero out u/v.w
	mov	[BReg+12],edx

	mov	DReg,[STACK_PTR1]		; *r

	movaps	xmm6,[zeroVec]
	movaps	xmm7,[AReg]			; from

	movaps	xmm0,[BReg]			; at
	subps	xmm0,xmm7			; at - from
	movaps	xmm1,xmm0

	mulps	xmm1,xmm1			; sqr(at-from)

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,1,1,1)
	shufps	xmm3,xmm3,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	sqrtss	xmm1,xmm1

	ucomiss xmm1,xmm6
	jne	Mat4LookAtsaCont1
	jmp	Mat4LookAtsaDB0

Mat4LookAtsaCont1:

	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1			; z = normalize(at-from)

	movaps	xmm1,xmm0
	mulss	xmm1,[negVec]			; -z.x z.y  z.z 0.0
	shufps	xmm1,xmm1,SHUFFLE(2,3,0,3)	;  z.z 0.0 -z.x 0.0

	movaps	xmm2,xmm1
	mulps	xmm2,xmm2

	movaps	xmm3,xmm2
	movaps	xmm4,xmm2

	shufps	xmm2,xmm2,SHUFFLE(0,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)

	addss	xmm2,xmm3
	addss	xmm2,xmm4

	sqrtss	xmm2,xmm2
	ucomiss	xmm2,xmm6
	jne	Mat4LookAtsaCont2
	jmp	Mat4LookAtsaDB0

Mat4LookAtsaCont2:

	shufps	xmm2,xmm2,0
	divps	xmm1,xmm2			; y = normalize(vec3(z.z,0,-z.x))

	movaps	xmm2,xmm0			; z
	movaps	xmm3,xmm0			; z
	movaps	xmm4,xmm1			; x
	movaps	xmm5,xmm1			; x

	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; z_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; z_zxy
	shufps	xmm4,xmm4,SHUFFLE(2,0,1,3)	; x_zxy
	shufps	xmm5,xmm5,SHUFFLE(1,2,0,3)	; x_yzx

	mulps	xmm2,xmm4			; u_yzx * v_zxy
	mulps	xmm3,xmm5			; u_zxy * v_yzx
	subps	xmm2,xmm3			; cross(z,x)

	movaps	xmm3,xmm2
	mulps	xmm3,xmm3
	movaps	xmm4,xmm3
	movaps	xmm5,xmm3

	shufps	xmm3,xmm3,SHUFFLE(0,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)

	addss	xmm3,xmm4
	addss	xmm3,xmm5
	sqrtss	xmm3,xmm3

	ucomiss	xmm3,xmm6
	jne	Mat4LookAtsaCont3
	jmp	Mat4LookAtsaDB0

Mat4LookAtsaCont3:

	shufps	xmm3,xmm3,0
	divps	xmm2,xmm3			; normalize(cross(z,x))

	movaps	[DReg+32],xmm0			; save z
	movaps	[DReg+16],xmm2			; save y
	movaps	[DReg],xmm1			; save x

	mulps	xmm7,[negVec]			; -from
	mulps	xmm0,xmm7			; translate(-from)
	mulps	xmm1,xmm7
	mulps	xmm2,xmm7

	movaps	xmm4,xmm1
	unpcklpd xmm4,xmm2
	movaps	xmm5,xmm4
	shufps	xmm4,xmm0,SHUFFLE(0,2,0,3)	; x,x,x,0.0
	shufps	xmm5,xmm0,SHUFFLE(1,3,1,3)	; y,y,y,0.0
	
	movaps	xmm6,xmm1
	unpckhpd xmm6,xmm2
	shufps	xmm6,xmm0,SHUFFLE(0,2,2,3)		; z,z,z,0.0

	addps	xmm4,xmm5
	addps	xmm4,xmm6

	movss	[DReg+12],xmm4
	shufps	xmm4,xmm4,SHUFFLE(1,2,1,2)
	movss	[DReg+28],xmm4
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	movss	[DReg+44],xmm4

	mov	eax,[zeroVec]
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Mat4LookAtsaDB0:
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp
	mov	[STACK_SAVE6],CReg

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]
	mov	CReg,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat4suLookAtAsm
;;;
;;; Call Stack
;;;
;;; [3] vec3* at
;;; [2] vec3* from
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4suLookAtAsm(mat4& r,const vec3* from,const vec3* at)
;;;

_Mat4suLookAtAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *from
	mov	BReg,[STACK_PTR3]		; *at
	mov	edx,[zeroVec]

	mov	[AReg+12],edx			; zero out u/v.w
	mov	[BReg+12],edx

	mov	DReg,[STACK_PTR1]		; *r

	movaps	xmm6,[zeroVec]
	movups	xmm7,[AReg]			; from

	movups	xmm0,[BReg]			; at
	subps	xmm0,xmm7			; at - from
	movaps	xmm1,xmm0

	mulps	xmm1,xmm1			; sqr(at-from)

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,1,1,1)
	shufps	xmm3,xmm3,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm2
	addss	xmm1,xmm3
	sqrtss	xmm1,xmm1

	ucomiss xmm1,xmm6
	jne	Mat4uLookAtsuCont1
	jmp	Mat4uLookAtsuDB0

Mat4uLookAtsuCont1:

	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1			; z = normalize(at-from)

	movaps	xmm1,xmm0
	mulss	xmm1,[negVec]			; -z.x z.y  z.z 0.0
	shufps	xmm1,xmm1,SHUFFLE(2,3,0,3)	;  z.z 0.0 -z.x 0.0

	movaps	xmm2,xmm1
	mulps	xmm2,xmm2

	movaps	xmm3,xmm2
	movaps	xmm4,xmm2

	shufps	xmm2,xmm2,SHUFFLE(0,0,0,0)
	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)

	addss	xmm2,xmm3
	addss	xmm2,xmm4

	sqrtss	xmm2,xmm2
	ucomiss	xmm2,xmm6
	jne	Mat4uLookAtsuCont2
	jmp	Mat4uLookAtsuDB0

Mat4uLookAtsuCont2:

	shufps	xmm2,xmm2,0
	divps	xmm1,xmm2			; y = normalize(vec3(z.z,0,-z.x))

	movaps	xmm2,xmm0			; z
	movaps	xmm3,xmm0			; z
	movaps	xmm4,xmm1			; x
	movaps	xmm5,xmm1			; x

	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; z_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; z_zxy
	shufps	xmm4,xmm4,SHUFFLE(2,0,1,3)	; x_zxy
	shufps	xmm5,xmm5,SHUFFLE(1,2,0,3)	; x_yzx

	mulps	xmm2,xmm4			; u_yzx * v_zxy
	mulps	xmm3,xmm5			; u_zxy * v_yzx
	subps	xmm2,xmm3			; cross(z,x)

	movaps	xmm3,xmm2
	mulps	xmm3,xmm3
	movaps	xmm4,xmm3
	movaps	xmm5,xmm3

	shufps	xmm3,xmm3,SHUFFLE(0,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)

	addss	xmm3,xmm4
	addss	xmm3,xmm5
	sqrtss	xmm3,xmm3

	ucomiss	xmm3,xmm6
	jne	Mat4uLookAtsuCont3
	jmp	Mat4uLookAtsuDB0

Mat4uLookAtsuCont3:

	shufps	xmm3,xmm3,0
	divps	xmm2,xmm3			; normalize(cross(z,x))

	movups	[DReg+32],xmm0			; save z
	movups	[DReg+16],xmm2			; save y
	movups	[DReg],xmm1			; save x

	mulps	xmm7,[negVec]			; -from
	mulps	xmm0,xmm7			; translate(-from)
	mulps	xmm1,xmm7
	mulps	xmm2,xmm7

	movaps	xmm4,xmm1
	unpcklpd xmm4,xmm2
	movaps	xmm5,xmm4
	shufps	xmm4,xmm0,SHUFFLE(0,2,0,3)	; x,x,x,0.0
	shufps	xmm5,xmm0,SHUFFLE(1,3,1,3)	; y,y,y,0.0
	
	movaps	xmm6,xmm1
	unpckhpd xmm6,xmm2
	shufps	xmm6,xmm0,SHUFFLE(0,2,2,3)		; z,z,z,0.0

	addps	xmm4,xmm5
	addps	xmm4,xmm6

	movss	[DReg+12],xmm4
	shufps	xmm4,xmm4,SHUFFLE(1,2,1,2)
	movss	[DReg+28],xmm4
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	movss	[DReg+44],xmm4

	mov	eax,[zeroVec]
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Mat4uLookAtsuDB0:
	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp
	mov	[STACK_SAVE6],CReg

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]
	mov	CReg,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; Mat4MultiplyFPU_Asm
;;;
;;; Call Stack
;;; 
;;; [2] mat4* n
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4MultiplyFPU_Asm(mat4* m,const mat4* n)
;;;

_Mat4MultiplyFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]

	movhps	xmm0,[AReg]			; xxx xxx n00 n01
	movlps	xmm0,[AReg+16]			; n10 n11 n00 n01
	movaps	xmm1,xmm0
	movhps	xmm2,[BReg+32]			; xxx xxx n20 n21
	movlps	xmm2,[BReg+48]			; n30 n31 n20 n21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; n00 n10 n20 n30
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,1)	; n01 n11 n21 n31

	movhps	xmm2,[AReg+8]			; xxx xxx n02 n03
	movlps	xmm2,[AReg+24]			; n12 n13 n02 n03
	movaps	xmm3,xmm2
	movhps	xmm4,[AReg+40]			; xxx xxx n22 n23
	movlps	xmm4,[AReg+56]			; n32 n33 n22 n23

	shufps	xmm2,xmm4,SHUFFLE(2,0,2,0)	; n02 n12 n22 n32
	shufps	xmm3,xmm4,SHUFFLE(3,1,3,1)	; n03 n13 n23 n33

	;; Calculate k00 k01 k02 k03

	movaps	xmm4,[DReg]			; m00 m01 m02 m03
	movaps	xmm5,xmm4
	movaps	xmm6,xmm4

	mulps	xmm4,xmm0
	mulps	xmm5,xmm1
	mulps	xmm6,xmm2
	mulps	xmm7,xmm3

	movaps	[DReg],xmm7

	fld	dword [DReg]
	fadd	dword [DReg+4]
	fadd	dword [DReg+8]
	fadd	dword [DReg+12]
	fwait

	movaps	[DReg],xmm6

	fld	dword [DReg]
	fadd	dword [DReg+4]
	fadd	dword [DReg+8]
	fadd	dword [DReg+12]
	fwait

	movaps	[DReg],xmm5

	fld	dword [DReg]
	fadd	dword [DReg+4]
	fadd	dword [DReg+8]
	fadd	dword [DReg+12]
	fwait

	movaps	[DReg],xmm4

	fld	dword [DReg]
	fadd	dword [DReg+4]
	fadd	dword [DReg+8]
	fadd	dword [DReg+12]

	fstp	dword [DReg]
	fstp	dword [DReg+4]
	fstp	dword [DReg+8]
	fstp	dword [DReg+12]

	;; Calculate k10 k11 k12 k13

	movaps	xmm4,[DReg+16]
	movaps	xmm5,xmm4
	movaps	xmm6,xmm4
	movaps	xmm7,xmm4

	mulps	xmm4,xmm0
	mulps	xmm5,xmm1
	mulps	xmm6,xmm2
	mulps	xmm7,xmm3

	movaps	[DReg+16],xmm7

	fld	dword [DReg+16]
	fadd	dword [DReg+20]
	fadd	dword [DReg+24]
	fadd	dword [DReg+28]
	fwait

	movaps	[DReg+16],xmm6

	fld	dword [DReg+16]
	fadd	dword [DReg+20]
	fadd	dword [DReg+24]
	fadd	dword [DReg+28]
	fwait

	movaps	[DReg+16],xmm5

	fld	dword [DReg+16]
	fadd	dword [DReg+20]
	fadd	dword [DReg+24]
	fadd	dword [DReg+28]
	fwait

	movaps	[DReg+16],xmm4

	fld	dword [DReg+16]
	fadd	dword [DReg+20]
	fadd	dword [DReg+24]
	fadd	dword [DReg+28]
	fwait

	fstp	dword [DReg+16]
	fstp	dword [DReg+20]
	fstp	dword [DReg+24]
	fstp	dword [DReg+28]

	;; Calculate k20 k21 k22 k23

	movaps	xmm4,[DReg+32]
	movaps	xmm5,xmm4
	movaps	xmm6,xmm4
	movaps	xmm7,xmm4

	mulps	xmm4,xmm0
	mulps	xmm5,xmm1
	mulps	xmm6,xmm2
	mulps	xmm7,xmm3

	movaps	[DReg+32],xmm7

	fld	dword [DReg+32]
	fadd	dword [DReg+36]
	fadd	dword [DReg+40]
	fadd	dword [DReg+44]
	fwait

	movaps	[DReg+32],xmm6

	fld	dword [DReg+32]
	fadd	dword [DReg+36]
	fadd	dword [DReg+40]
	fadd	dword [DReg+44]
	fwait

	movaps	[DReg+32],xmm5

	fld	dword [DReg+32]
	fadd	dword [DReg+36]
	fadd	dword [DReg+40]
	fadd	dword [DReg+44]
	fwait

	movaps	[DReg+32],xmm4

	fld	dword [DReg+32]
	fadd	dword [DReg+36]
	fadd	dword [DReg+40]
	fadd	dword [DReg+44]
	fwait

	fstp	dword [DReg+32]
	fstp	dword [DReg+36]
	fstp	dword [DReg+40]
	fstp	dword [DReg+44]

	;; Calculate k30 k31 k32 k33

	movaps	xmm4,[DReg+48]
	movaps	xmm5,[zeroVec]

	mulps	xmm0,xmm4
	mulps	xmm1,xmm4
	mulps	xmm2,xmm4
	mulps	xmm3,xmm4

	movaps	[DReg+48],xmm3

	fld	dword [DReg+48]
	fadd	dword [DReg+52]
	fadd	dword [DReg+56]
	fadd	dword [DReg+60]
	fwait

	movaps	[DReg+48],xmm2

	fld	dword [DReg+48]
	fadd	dword [DReg+52]
	fadd	dword [DReg+56]
	fadd	dword [DReg+60]
	fwait

	movaps	[DReg+48],xmm1

	fld	dword [DReg+48]
	fadd	dword [DReg+52]
	fadd	dword [DReg+56]
	fadd	dword [DReg+60]
	fwait

	movaps	[DReg+48],xmm0

	fld	dword [DReg+48]
	fadd	dword [DReg+52]
	fadd	dword [DReg+56]
	fadd	dword [DReg+60]
	fwait

	fstp	dword [DReg+48]
	fstp	dword [DReg+52]
	fstp	dword [DReg+56]
	fstp	dword [DReg+60]

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4LookAtFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] vec3* at
;;; [2] vec3* from
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4LookAtFPU_Asm(mat4& r,const vec3& from,const mat3& at)
;;;

_Mat4LookAtFPU_Asm:


	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *from
	mov	BReg,[STACK_PTR3]		; *at
	mov	DReg,[STACK_PTR1]		; *r

	fld	dword [BReg]			; at->x
	fld	dword [AReg]			; [0] from.x [1] at.x
	fsubp	st1,st0				; [0] at.x - from.x
	
	fld	dword [BReg+4]			; [0] at.y [1] at.x - from.x
	fld	dword [AReg+4]			; [0] from.y [1] at.y [2] at.x - from.x
	fsubp	st1,st0				; [0] at.y - from.y [1] at.x - from.x
	
	fld	dword [BReg+8]			; [0] at.z [1] at.y - from.y [2] at.x - from.x
	fld	dword [AReg+8]			; [0] from.z [1] at.z [2] at.y - from.y [3] at.x - from.x
	fsubp	st1,st0				; [0] at.z - from.z [1] at.y - from.y [2] at.x - from.x

	fld	st0
	fmul	st0,st0				; [0] del(z)*del(z) [1] del(z) [2] del(y) [3] del(x)
	fld	st2				; [0] del(y) [1] sqr(del(z)) [2] del(z) [3] del(y) [4] del(x)
	fmul	st0,st0				; [0] sqr(del(y)) [1] sqr(del(z)) [2] del(z) [3] del(y) [4] del(x)
	fld	st4				; [0] del(x) [1] sqr(del(y)) [2] sqr(del(z)) [3] del(z) [4] del(y) [5] del(x)
	fmul	st0,st0				; [0] sqr(del(x)) [1] sqr(del(y)) [2] sqr(del(z)) [3] del(z) [4] del(y) [5] del(x)

	faddp	st1,st0				; [0] sqr(del(x))+sqr(del(y)) [1] sqr(del(z)) [2] del(z) [3] del(y) [4] del(x)
	faddp	st1,st0				; [0] sqr(del(x))+sqr(del(y))+sqr(del(z)) [1] del(z) [2] del(y) [3] del(x)

	fldz
	fcomip	st0,st1

	jne	Mat4LookatCont0

	ffree	st0
	ffree	st1
	ffree	st2
	ffree	st3
	
	jmp	Mat4LookatDB0

Mat4LookatCont0:

	fsqrt					; [0] norm(at-from) [1] del(z) [2] del(y) [3] del(x)

	fdiv	st1,st0
	fdiv	st2,st0
	fdivp	st3,st0				; [0] norm((at-from)->z) [1] norm((at-from)->y) [2] norm((at-from)->x)

	;; Save the norm(vec3(at-from)) as the z-vector
	;; 

	fstp	dword [DReg+40]			; [0] norm((at-from)->y) [1] norm((at-from)->x)
	fstp	dword [DReg+36]			; [0] norm((at-from)->x)
	fst	dword [DReg+32]			; [0] norm((at-from)->x)

	fchs					; [0] x.z = -z.x
	fldz					; [0] x.y [1] x.z
	fld	dword [DReg+40]			; [0] x.x [1] x.y [2] x.z

	fld	st0				; [0] x.x [1] x.x [2] x.y [3] x.z
	fmul	st0,st0				; [0] x.x*x.x [1] x.x [2] x.y [3] x.z
	fld	st2				; [0] x.y [1] x.x*x.x [2] x.x [3] x.y [4] x.z
	fmul	st0,st0				; [0] x.y*x.y [1] x.x*x.x [2] x.x [3] x.y [4] x.z
	fld	st4				; [0] x.z [1] x.y*x.y [2] x.x*x.x [3] x.x [4] x.y [5] x.z
	fmul	st0,st0				; [0] x.z*x.z [1] x.y*x.y [2] x.x*x.x [3] x.x [4] x.y [5] x.z
	faddp	st1,st0				; [0] x.z*x.z+x.y*x.y [1] x.x*x.x [2] x.x [3] x.y [4] x.z
	faddp	st1,st0				; [0] x.z*x.z+x.y*x.y+x.x*x.x [1] x.x [2] x.y [3] x.z

	fldz
	fcomip	st0,st1

	jne	Mat4LookatCont1

	ffree	st0
	ffree	st1
	ffree	st2
	ffree	st3
	jmp	Mat4LookatDB0

Mat4LookatCont1:

	fsqrt					; [0] sqrt(sqr(x)) [1] x.x [2] x.y [3] x.z
	fdiv	st1,st0
	fdivp	st3,st0				; [0] norm(x.x) [1] 0.0f [2] norm(x.z)

	;; Save the norm(x)
	;; 

	fstp	dword [DReg]
	fstp	dword [DReg+4]
	fstp	dword [DReg+8]

	;; Cross(z,x)
	;;

	fld	dword [DReg+36]			; [0] z.y
	fmul	dword [DReg+8]			; [0] z.y*x.z
	fld	dword [DReg+40]			; [0] z.z [1] z.y*x.z
	fmul	dword [DReg+4]			; [0] z.z*x.y [1] z.y*x.z
	fsubp	st1,st0				; [0] z.y*x.z - z.z*x.y = y.x

	fld	dword [DReg+40]			; [0] z.z [1] y.x
	fmul	dword [DReg]			; [0] z.z*x.x [1] y.x
	fld	dword [DReg+32]			; [0] z.x [1] z.z*x.x [2] y.x
	fmul	dword [DReg+8]			; [0] z.x*x.z [1] z.z*x.x [2] y.x
	fsubp	st1,st0				; [0] z.z*x.x - z.x*x.z = y.y [1] y.x

	fld	dword [DReg+32]			; [0] z.x [1] y.y [2] y.x
	fmul	dword [DReg+4]			; [0] z.x*x.y [1] y.y [2] y.x
	fld	dword [DReg+36]			; [0] z.y [1] z.x*x.y [1] y.y [2] y.x
	fmul	dword [DReg]			; [0] z.y*x.x [1] z.x*x.y [2] y.y [3] y.x
	fsubp	st1,st0				; [0] x.z*x.y - z.y*x.x = y.z [1] y.y [2] y.x

	fld	st0				; [0] y.z [1] y.z [2] y.y [3] y.x
	fmul	st0,st0				; [0] sqr(y.z) [1] y.z [2] y.y [3] y.x
	fld	st2				; [0] y.y [1] sqr(y.z) [2] y.z [3] y.y [4] y.x
	fmul	st0,st0				; [0] sqr(y.y) [1] sqr(y.z) [2] y.z [3] y.y [4] y.x
	fld	st4				; [0] y.x [1] sqr(y.y) [2] sqr(y.z) [3] y.z [4] y.y [5] y.x
	fmul	st0,st0				; [0] sqr(y.x) [1] sqr(y.y) [2] sqr(y.z) [3] y.z [4] y.y [5] y.x

	faddp	st1,st0				; [0] sqr(y.x)+sqr(y.y) [1] sqr(y.z) [2] y.z [3] y.y [4] y.x
	faddp	st1,st0				; [0] sqr(y.x)+sqr(y.y)+sqr(y.z) [1] y.z [2] y.y [3] y.x

	fldz
	fcomip	st0,st1

	jne	Mat4LookatCont2

	ffree	st0
	ffree	st1
	ffree	st2
	ffree	st3
	
	jmp	Mat4LookatDB0

Mat4LookatCont2:

	;; Normalize(Cross(z,x))
	;;

	fdiv	st2,st0
	fdiv	st3,st0
	fdivp	st1,st0				; [0] y.z [1] y.y [2] y.x

	fstp	dword [DReg+24]
	fstp	dword [DReg+20]
	fstp	dword [DReg+16]

	fld	dword [AReg]			; [0] from.x
	fchs
	fld	dword [AReg+4]			; [0] from.y [1] from.x
	fchs
	fld	dword [AReg+8]			; [0] from.z [1] from.y [2] from.x
	fchs

	fld	dword [DReg]			; [0] m00 [1] from.z [2] from.y [3] from.x
	fmul	st0,st3				; [0] m00*from.x [1] from.z [2] from.y [3] from.x
	fld	dword [DReg+4]			; [0] m01 [1] m00*from.x [2] from.z [3] from.y [4] from.x
	fmul	st0,st3				; [0] m01*from.y [1] m00*from.x [2] from.z [3] from.y [4] from.x
	fld	dword [DReg+8]			; [0] m02 [1] m01*from.y [2] m00*from.x [3] from.z [4] from.y [5] from.x
	fmul	st0,st3				; [0] m02*from.z [1] m01*from.y [2] m00*from.x [3] from.z [4] from.y [5] from.x
	faddp	st1,st0				; [0] from.z*m02+from.y*m01 [1] from.x*m00 [2] from.z [3] from.y [4] from.x
	faddp	st1,st0				; [0] from.z*m02+from.y*m01+from.x*m00 [1] from.z [2] from.y [3] from.x
	fstp	dword [DReg+12]			; [0] from.z [1] from.y [2] from.x
	
	fld	dword [DReg+16]			; [0] m10 [1] from.z [2] from.y [3] from.x
	fmul	st0,st3				; [0] m10*from.x [1] from.z [2] from.y [3] from.x
	fld	dword [DReg+20]			; [0] m11 [1] m10*from.x [2] from.z [3] from.y [4] from.x
	fmul	st0,st3				; [0] m11*from.y [1] m10*from.x [2] from.z [3] from.y [4] from.x
	fld	dword [DReg+24]			; [0] m12 [1] m11*from.y [2] m10*from.x [3] from.z [4] from.y [5] from.x
	fmul	st0,st3				; [0] m12*from.z [1] m11*from.y [2] m10*from.x [3] from.z [4] from.y [5] from.x
	faddp	st1,st0				; [0] from.z*m12+from.y*m11 [1] from.x*m10 [2] from.z [3] from.y [4] from.x
	faddp	st1,st0				; [0] from.z*m12+from.y*m11+from.x*m10 [1] from.z [2] from.y [3] from.x
	fstp	dword [DReg+28]			; [0] from.z [1] from.y [2] from.x

	fld	dword [DReg+32]			; [0] m20 [1] from.z [2] from.y [3] from.x
	fmulp	st3,st0				; [0] from.z [1] from.y [2] from.x*m20
	fld	dword [DReg+36]			; [0] m21 [1] from.z [2] from.y [2] from.x*m20
	fmulp	st2,st0				; [0] from.z [1] from.y*m21 [2] from.x*m20
	fld	dword [DReg+40]			; [0] m22 [1] from.z [2] from.y*m21 [3] from.x*m20
	fmulp	st1,st0				; [0] m22+from.z [1] from.y*m21 [2] from.x*m20
	faddp	st1,st0				; [0] from.z*m22+from.y*m21 [1] from.x*m20
	faddp	st1,st0				; [0] from.z*m22+from.y*m21+from.x*m20
	fstp	dword [DReg+44]

	fwait

	mov	eax,[zeroVec]
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Mat4LookatDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	mov	[DReg+16],eax
	mov	[DReg+20],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax

	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+40],eax
	mov	[DReg+44],eax

	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret
	
%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat4MultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float x
;;; [2] mat4* m
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4MultiplyFloatAsm(mat4& r,const mat4& m,const float x)
;;;

_Mat4MultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movaps	xmm0,[AReg]		; m00 m01 m02 m03
	movaps	xmm1,[AReg+16]		; m10 m11 m12 m13
	movaps	xmm2,[AReg+32]		; m20 m21 m22 m23
	movaps	xmm3,[AReg+48]		; m30 m31 m32 m33

	movss	xmm4,[STACK_PTR3]	; x
	shufps	xmm4,xmm4,0

	mulps	xmm0,xmm4
	mulps	xmm1,xmm4
	mulps	xmm2,xmm4
	mulps	xmm3,xmm4

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2
	movaps	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4TransposeAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* m
;;; [1] mat3* r
;;;
;;; extern "C" void Mat4TransposeAsm(mat4& r,const mat4& m)
;;;

_Mat4TransposeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]		; *m
	mov	DReg,[STACK_PTR1]		; *r

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 m21
	movlps	xmm2,[AReg+48]			; m30 m31 m20 m21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 m30
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,1)	; m01 m11 m21 m31

	movhps	xmm2,[AReg+8]			; xxx xxx m02 m03
	movlps	xmm2,[AReg+24]			; m12 m13 m02 m03
	movaps	xmm3,xmm2
	movhps	xmm4,[AReg+40]			; xxx xxx m22 m23
	movlps	xmm4,[AReg+56]			; m32 m33 m22 m23

	shufps	xmm2,xmm4,SHUFFLE(2,0,2,0)	; m02 m12 m22 m32
	shufps	xmm3,xmm4,SHUFFLE(3,1,3,1)	; m03 m13 m23 m33

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2
	movaps	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4ShadowMatrixAsm
;;;
;;; Call Stack
;;;
;;; [4] vec3* lightPos
;;; [3] float planeOffset
;;; [2] vec3* planeNormal
;;; [1] mat4* r
;;;
;;; mat4 = m4_shadowMatrix(const vec3& planeNormal,
;;;                        const float planeOffset,
;;;                        const vec3& lightPos)
;;;
;;; extern "C" void Mat4ShadowMatrixAsm(mat4&       r,
;;;                                     const vec3& planeNormal,
;;;                                     const float planeOffset
;;;                                     const vec3& lightPos)
;;; 

_Mat4ShadowMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE3],DReg

	mov	BReg,[STACK_PTR4]	; lightPos
	mov	AReg,[STACK_PTR2]	; planeNormal
	mov	DReg,[STACK_PTR1]	; matrix

	fld	dword [BReg]
	fmul	dword [AReg]
	fld	dword [BReg+4]
	fmul	dword [AReg+4]
	fld	dword [BReg+8]
	fmul	dword [AReg+8]
	faddp	st1,st0
	faddp	st1,st0
	fadd	dword [STACK_PTR3]	; dot(lightPos,planeNormal)+planeOffset
	fstp	dword [DReg+48]

	mov	ecx,[AReg]
	mov	[DReg],ecx
	mov	ecx,[AReg+4]
	mov	[DReg+4],ecx
	mov	ecx,[AReg+8]
	mov	[DReg+8],ecx
	mov	ecx,[STACK_PTR3]	; planeOffset
	mov	[DReg+12],ecx

	mov	ecx,[zeroVec]
	mov	[DReg+52],ecx
	mov	[DReg+56],ecx
	mov	[DReg+60],ecx

	fwait

	movaps	xmm0,[DReg+48]		; dist  0.0  0.0  0.0
	movaps	xmm1,[DReg]		; pn.x pn.y pn.z planeOffset
	movss	xmm2,[BReg]		; lp.x
	shufps	xmm2,xmm2,0		; lp.x lp.x lp.x lp.x

	mulps	xmm2,xmm1
	subps	xmm0,xmm2		; dist - lightPos.x * planeNormal.x,
					;  0.0 - lightPos.x * planeNormal.y,
					;  0.0 - lightPos.x * planeNormal.z,
					;  0.0 - lightPos.x * planeOffset

	mov	ecx,[DReg+48]
	mov	[DReg+52],ecx
	mov	ecx,[DReg+60]
	mov	[DReg+48],ecx

	movaps	xmm2,[DReg+48]		;  0.0  dist   0.0   0.0
	movss	xmm3,[BReg+4]		; lp.y
	shufps	xmm3,xmm3,0		; lp.y  lp.y  lp.y  lp.y
	mulps	xmm3,xmm1
	subps	xmm2,xmm3		;  0.0 - lightPos.y * planeNormal.x,
					; dist - lightPos.y * planeNormal.y,
					;  0.0 - lightPos.y * planeNormal.z,
					;  0.0 - lightPos.y * planeOffset

	mov	ecx,[DReg+52]
	mov	[DReg+56],ecx
	mov	ecx,[DReg+60]
	mov	[DReg+52],ecx

	movaps	xmm3,[DReg+48]		;   0.0  0.0 dist  0.0
	movss	xmm4,[BReg+8]		;  lp.z
	shufps	xmm4,xmm4,0		;  lp.z lp.z lp.z lp.z
	mulps	xmm4,xmm1
	subps	xmm3,xmm4		;  0.0 - lightPos.z * planeNormal.x,
					;  0.0 - lightPos.z * planeNormal.y,
					; dist - lightPos.z * planeNormal.z,
					;  0.0 - lightPos.z * planeOffset

	mov	ecx,[DReg+56]
	mov	[DReg+60],ecx
	mov	ecx,[DReg+48]
	mov	[DReg+56],ecx

	movaps	xmm4,[DReg+48]		;  0.0  0.0  0.0  dist
	subps	xmm4,xmm1		;  0.0 - planeNormal.x,
					;  0.0 - planeNormal.y,
					;  0.0 - planeNormal.z,
					; dist - planeOffset

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm2
	movaps	[DReg+32],xmm3
	movaps	[DReg+48],xmm4

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Mat4MirrorMatrixAsm
;;;
;;; Call Stack
;;;
;;; [3] float planeOffset
;;; [2] vec3* planeNormal
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4MirrorMatrixAsm(mat4& r,const vec3& planeNormal,const float planeOffset)
;;; 

_Mat4MirrorMatrixAsm:
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *planeNormal
	mov	DReg,[STACK_PTR1]	; *r

	mov	ecx,[AReg]
	mov	[DReg],ecx
	mov	ecx,[AReg+4]
	mov	[DReg+4],ecx
	mov	ecx,[AReg+8]
	mov	[DReg+8],ecx
	mov	ecx,[STACK_PTR3]
	mov	[DReg+12],ecx

	movaps	xmm5,[twoVec]		;  2.0   2.0   2.0   2.0
	movaps	xmm6,[DReg]		; pn.x  pn.y  pn.z  offs

	movaps	xmm0,[mirrorVec0]	;  1.0   0.0   0.0   0.0
	movss	xmm1,[AReg]
	shufps	xmm1,xmm1,0		; pn.x  pn.x  pn.x  pn.x
	mulps	xmm1,xmm5
	mulps	xmm1,xmm6
	subps	xmm0,xmm1

	movaps	xmm1,[mirrorVec1]
	movss	xmm2,[AReg+4]
	shufps	xmm2,xmm2,0
	mulps	xmm2,xmm5
	mulps	xmm2,xmm6
	subps	xmm1,xmm2

	movaps	xmm2,[mirrorVec2]
	movss	xmm3,[AReg+8]
	shufps	xmm3,xmm3,0
	mulps	xmm3,xmm5
	mulps	xmm3,xmm6
	subps	xmm2,xmm3

	movaps	xmm3,[mirrorVec3]

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2
	movaps	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4GLtoD3DProjMatAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* m
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4GlToD3DProjMatAsm(mat4& r,const mat4& m)
;;;

_Mat4GlToD3DProjMatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]

	movaps	xmm0,[AReg]
	movaps	xmm1,[AReg+16]
	movaps	xmm2,[AReg+32]
	movaps	xmm3,[AReg+48]

	addps	xmm2,xmm3
	mulps	xmm2,[halfVec]

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm2
	movaps	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4LookAtLHAsm
;;;
;;; Call Stack
;;;
;;; [4] vec3* pUpVector
;;; [3] vec3* pCenterVector
;;; [2] vec3* pEyePointVector
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4LookAtLHAsm(mat4*       r,
;;;                                 const vec3* pEye,
;;;                                 const vec3* pLookAt,
;;;                                 const vec3* pUp);
;;;

_Mat4LookAtLHAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *eye
	mov	BReg,[STACK_PTR3]		; *center
	mov	CReg,[STACK_PTR4]		; *up

	movss	xmm6,[zeroVec]

	;; z = normalize(center-eye)
	;;

	movaps	xmm2,[BReg]			; center
	movaps	xmm7,[AReg]			; eye
	subps	xmm2,xmm7			; center-eye
	movaps	xmm3,xmm2
	mulps	xmm3,xmm3			; sqr(center-eye)
	movaps	xmm4,xmm3
	movaps	xmm5,xmm3
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)

	addss	xmm3,xmm4
	addss	xmm3,xmm5			; sum(sqr(center-eye))
	ucomiss	xmm3,xmm6
	jne	Mat4LHLookAtCont0
	jmp	Mat4LHDB0

Mat4LHLookAtCont0:

	sqrtss	xmm3,xmm3
	shufps	xmm3,xmm3,SHUFFLE(0,0,0,0)
	divps	xmm2,xmm3			; xmm2 = z

	;; x = normalize(cross(up,z))
	;;

	movaps	xmm0,[CReg]			; up
	movaps	xmm1,xmm0
	movaps	xmm3,xmm2
	movaps	xmm4,xmm2

	shufps	xmm0,xmm0,SHUFFLE(1,2,0,3)	; up_yzx
	shufps	xmm1,xmm1,SHUFFLE(2,0,1,3)	; up_zxy
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; z_zxy
	shufps	xmm4,xmm4,SHUFFLE(1,2,0,3)	; z_yzx

	mulps	xmm0,xmm3			; up_yzx * z_zxy
	mulps	xmm1,xmm4			; up_zxy * z_yzx
	subps	xmm0,xmm1			; cross(up,z)

	movaps	xmm1,xmm0
	mulps	xmm1,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1

	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm3
	addss	xmm1,xmm4

	ucomiss	xmm1,xmm6
	jne	Mat4LHLookAtCont1
	jmp	Mat4LHDB0

Mat4LHLookAtCont1:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	divps	xmm0,xmm1			; xmm0 = x

	;; y = normalize(cross(z,x))
	;;

	movaps	xmm1,xmm2
	movaps	xmm3,xmm2
	movaps	xmm4,xmm0
	movaps	xmm5,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)	; z_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; z_zxy
	shufps	xmm4,xmm4,SHUFFLE(2,0,1,3)	; x_zxy
	shufps	xmm5,xmm5,SHUFFLE(1,2,0,3)	; x_yzx

	mulps	xmm1,xmm4			; z_yzx*x_zxy
	mulps	xmm3,xmm5			; z_zxy*x_yzx
	subps	xmm1,xmm3			; cross(z,x)

	movaps	xmm3,xmm1
	mulps	xmm3,xmm3			; sqr(cross(z,x))
	movaps	xmm4,xmm3
	movaps	xmm5,xmm3

	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)
	addss	xmm3,xmm4
	addss	xmm3,xmm5

	ucomiss	xmm3,xmm6
	jne	Mat4LHLookAtCont2
	jmp	Mat4LHDB0

Mat4LHLookAtCont2:

	sqrtss	xmm3,xmm3
	shufps	xmm3,xmm3,SHUFFLE(0,0,0,0)
	divps	xmm1,xmm3			; y = normalize(cross(z,x))

	movaps	xmm3,xmm0
	movaps	xmm4,xmm1
	unpcklpd xmm0,xmm1
	movaps	xmm1,xmm0
	shufps	xmm0,xmm2,SHUFFLE(0,2,0,3)	; x,x,x,0.0
	shufps	xmm1,xmm2,SHUFFLE(1,3,1,3)	; y,y,y,0.0

	unpckhpd xmm3,xmm4
	shufps	xmm3,xmm2,SHUFFLE(0,2,2,3)

	movaps	xmm5,xmm7
	movaps	xmm6,xmm7
	shufps	xmm5,xmm5,SHUFFLE(0,0,0,0)
	shufps	xmm6,xmm6,SHUFFLE(1,1,1,1)
	shufps	xmm7,xmm7,SHUFFLE(2,2,2,2)

	mulps	xmm5,xmm0
	mulps	xmm6,xmm1
	mulps	xmm7,xmm3

	addps	xmm5,xmm6
	addps	xmm5,xmm7

	mulps	xmm5,[negVec]

	movaps	[DReg],xmm0
	movaps	[DReg+16],xmm1
	movaps	[DReg+32],xmm3
	movaps	[DReg+48],xmm5

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

Mat4LHDB0:

	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	Srcp,mat4Identity
	mov	Dstp,[STACK_PTR1]
	mov	CReg,16

	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; Mat4uMultiplyFloatAsm
;;;
;;; Call Stack
;;;
;;; [3] float x
;;; [2] mat4* m
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4uMultiplyFloatAsm(mat4& r,const mat4& m,const float x)
;;;

_Mat4uMultiplyFloatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]	; *m
	mov	DReg,[STACK_PTR1]	; *r

	movups	xmm0,[AReg]		; m00 m01 m02 m03
	movups	xmm1,[AReg+16]		; m10 m11 m12 m13
	movups	xmm2,[AReg+32]		; m20 m21 m22 m23
	movups	xmm3,[AReg+48]		; m30 m31 m32 m33

	movss	xmm4,[STACK_PTR3]	; x
	shufps	xmm4,xmm4,0

	mulps	xmm0,xmm4
	mulps	xmm1,xmm4
	mulps	xmm2,xmm4
	mulps	xmm3,xmm4

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2
	movups	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uTransposeAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* m
;;; [1] mat3* r
;;;
;;; extern "C" void Mat4uTransposeAsm(mat4& r,const mat4& m)
;;;

_Mat4uTransposeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR2]		; *m
	mov	DReg,[STACK_PTR1]		; *r

	movhps	xmm0,[AReg]			; xxx xxx m00 m01
	movlps	xmm0,[AReg+16]			; m10 m11 m00 m01
	movaps	xmm1,xmm0
	movhps	xmm2,[AReg+32]			; xxx xxx m20 m21
	movlps	xmm2,[AReg+48]			; m30 m31 m20 m21

	shufps	xmm0,xmm2,SHUFFLE(2,0,2,0)	; m00 m10 m20 m30
	shufps	xmm1,xmm2,SHUFFLE(3,1,3,1)	; m01 m11 m21 m31

	movhps	xmm2,[AReg+8]			; xxx xxx m02 m03
	movlps	xmm2,[AReg+24]			; m12 m13 m02 m03
	movaps	xmm3,xmm2
	movhps	xmm4,[AReg+40]			; xxx xxx m22 m23
	movlps	xmm4,[AReg+56]			; m32 m33 m22 m23

	shufps	xmm2,xmm4,SHUFFLE(2,0,2,0)	; m02 m12 m22 m32
	shufps	xmm3,xmm4,SHUFFLE(3,1,3,1)	; m03 m13 m23 m33

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2
	movups	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uShadowMatrixAsm
;;;
;;; Call Stack
;;;
;;; [4] vec3* lightPos
;;; [3] float planeOffset
;;; [2] vec3* planeNormal
;;; [1] mat4* r
;;;
;;; mat4 = m4_shadowMatrix(const vec3& planeNormal,
;;;                        const float planeOffset,
;;;                        const vec3& lightPos)
;;;
;;; extern "C" void Mat4uShadowMatrixAsm(mat4&       r,
;;;                                      const vec3& planeNormal,
;;;                                      const float planeOffset
;;;                                      const vec3& lightPos)
;;; 

_Mat4uShadowMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE3],DReg

	mov	BReg,[STACK_PTR4]	; lightPos
	mov	AReg,[STACK_PTR2]	; planeNormal
	mov	DReg,[STACK_PTR1]	; matrix

	fld	dword [BReg]
	fmul	dword [AReg]
	fld	dword [BReg+4]
	fmul	dword [AReg+4]
	fld	dword [BReg+8]
	fmul	dword [AReg+8]
	faddp	st1,st0
	faddp	st1,st0
	fadd	dword [STACK_PTR3]	; dot(lightPos,planeNormal)+planeOffset
	fstp	dword [DReg+48]

	mov	ecx,[AReg]
	mov	[DReg],ecx
	mov	ecx,[AReg+4]
	mov	[DReg+4],ecx
	mov	ecx,[AReg+8]
	mov	[DReg+8],ecx
	mov	ecx,[STACK_PTR3]	; planeOffset
	mov	[DReg+12],ecx

	mov	ecx,[zeroVec]
	mov	[DReg+52],ecx
	mov	[DReg+56],ecx
	mov	[DReg+60],ecx

	fwait

	movups	xmm0,[DReg+48]		; dist  0.0  0.0  0.0
	movups	xmm1,[DReg]		; pn.x pn.y pn.z planeOffset
	movss	xmm2,[BReg]		; lp.x
	shufps	xmm2,xmm2,0		; lp.x lp.x lp.x lp.x

	mulps	xmm2,xmm1
	subps	xmm0,xmm2		; dist - lightPos.x * planeNormal.x,
					;  0.0 - lightPos.x * planeNormal.y,
					;  0.0 - lightPos.x * planeNormal.z,
					;  0.0 - lightPos.x * planeOffset

	mov	ecx,[DReg+48]
	mov	[DReg+52],ecx
	mov	ecx,[DReg+60]
	mov	[DReg+48],ecx

	movups	xmm2,[DReg+48]		;  0.0  dist   0.0   0.0
	movss	xmm3,[BReg+4]		; lp.y
	shufps	xmm3,xmm3,0		; lp.y  lp.y  lp.y  lp.y
	mulps	xmm3,xmm1
	subps	xmm2,xmm3		;  0.0 - lightPos.y * planeNormal.x,
					; dist - lightPos.y * planeNormal.y,
					;  0.0 - lightPos.y * planeNormal.z,
					;  0.0 - lightPos.y * planeOffset

	mov	ecx,[DReg+52]
	mov	[DReg+56],ecx
	mov	ecx,[DReg+60]
	mov	[DReg+52],ecx

	movups	xmm3,[DReg+48]		;   0.0  0.0 dist  0.0
	movss	xmm4,[BReg+8]		;  lp.z
	shufps	xmm4,xmm4,0		;  lp.z lp.z lp.z lp.z
	mulps	xmm4,xmm1
	subps	xmm3,xmm4		;  0.0 - lightPos.z * planeNormal.x,
					;  0.0 - lightPos.z * planeNormal.y,
					; dist - lightPos.z * planeNormal.z,
					;  0.0 - lightPos.z * planeOffset

	mov	ecx,[DReg+56]
	mov	[DReg+60],ecx
	mov	ecx,[DReg+48]
	mov	[DReg+56],ecx

	movups	xmm4,[DReg+48]		;  0.0  0.0  0.0  dist
	subps	xmm4,xmm1		;  0.0 - planeNormal.x,
					;  0.0 - planeNormal.y,
					;  0.0 - planeNormal.z,
					; dist - planeOffset

	movups	[DReg],xmm0
	movups	[DReg+16],xmm2
	movups	[DReg+32],xmm3
	movups	[DReg+48],xmm4

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;;
;;; Mat4uMirrorMatrixAsm
;;;
;;; Call Stack
;;;
;;; [3] float planeOffset
;;; [2] vec3* planeNormal
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4uMirrorMatrixAsm(mat4& r,const vec3& planeNormal,const float planeOffset)
;;; 

_Mat4uMirrorMatrixAsm:
	
	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]	; *planeNormal
	mov	DReg,[STACK_PTR1]	; *r

	mov	ecx,[AReg]
	mov	[DReg],ecx
	mov	ecx,[AReg+4]
	mov	[DReg+4],ecx
	mov	ecx,[AReg+8]
	mov	[DReg+8],ecx
	mov	ecx,[STACK_PTR3]
	mov	[DReg+12],ecx

	movaps	xmm5,[twoVec]		;  2.0   2.0   2.0   2.0
	movups	xmm6,[DReg]		; pn.x  pn.y  pn.z  offs

	movaps	xmm0,[mirrorVec0]	;  1.0   0.0   0.0   0.0
	movss	xmm1,[AReg]
	shufps	xmm1,xmm1,0		; pn.x  pn.x  pn.x  pn.x
	mulps	xmm1,xmm5
	mulps	xmm1,xmm6
	subps	xmm0,xmm1

	movaps	xmm1,[mirrorVec1]
	movss	xmm2,[AReg+4]
	shufps	xmm2,xmm2,0
	mulps	xmm2,xmm5
	mulps	xmm2,xmm6
	subps	xmm1,xmm2

	movaps	xmm2,[mirrorVec2]
	movss	xmm3,[AReg+8]
	shufps	xmm3,xmm3,0
	mulps	xmm3,xmm5
	mulps	xmm3,xmm6
	subps	xmm2,xmm3

	movaps	xmm3,[mirrorVec3]

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2
	movups	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4uGLtoD3DProjMatAsm
;;;
;;; Call Stack
;;;
;;; [2] mat4* m
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4uGlToD3DProjMatAsm(mat4& r,const mat4& m)
;;;

_Mat4uGlToD3DProjMatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]

	movups	xmm0,[AReg]
	movups	xmm1,[AReg+16]
	movups	xmm2,[AReg+32]
	movups	xmm3,[AReg+48]

	addps	xmm2,xmm3
	mulps	xmm2,[halfVec]

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm2
	movups	[DReg+48],xmm3

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4uLookAtLHAsm
;;;
;;; Call Stack
;;;
;;; [4] vec3* pUpVector
;;; [3] vec3* pCenterVector
;;; [2] vec3* pEyePointVector
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4uLookAtLHAsm(mat4*       r,
;;;                                  const vec3* pEye,
;;;                                  const vec3* pLookAt,
;;;                                  const vec3* pUp);
;;;

_Mat4uLookAtLHAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *eye
	mov	BReg,[STACK_PTR3]		; *center
	mov	CReg,[STACK_PTR4]		; *up

	movss	xmm6,[zeroVec]

	;; z = normalize(center-eye)
	;;

	movups	xmm2,[BReg]			; center
	movups	xmm7,[AReg]			; eye
	subps	xmm2,xmm7			; center-eye
	movaps	xmm3,xmm2
	mulps	xmm3,xmm3			; sqr(center-eye)
	movaps	xmm4,xmm3
	movaps	xmm5,xmm3
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)

	addss	xmm3,xmm4
	addss	xmm3,xmm5			; sum(sqr(center-eye))
	ucomiss	xmm3,xmm6
	jne	Mat4uLHLookAtCont0
	jmp	Mat4uLHDB0

Mat4uLHLookAtCont0:

	sqrtss	xmm3,xmm3
	shufps	xmm3,xmm3,SHUFFLE(0,0,0,0)
	divps	xmm2,xmm3			; xmm2 = z

	;; x = normalize(cross(up,z))
	;;

	movups	xmm0,[CReg]			; up
	movaps	xmm1,xmm0
	movaps	xmm3,xmm2
	movaps	xmm4,xmm2

	shufps	xmm0,xmm0,SHUFFLE(1,2,0,3)	; up_yzx
	shufps	xmm1,xmm1,SHUFFLE(2,0,1,3)	; up_zxy
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; z_zxy
	shufps	xmm4,xmm4,SHUFFLE(1,2,0,3)	; z_yzx

	mulps	xmm0,xmm3			; up_yzx * z_zxy
	mulps	xmm1,xmm4			; up_zxy * z_yzx
	subps	xmm0,xmm1			; cross(up,z)

	movaps	xmm1,xmm0
	mulps	xmm1,xmm1
	movaps	xmm3,xmm1
	movaps	xmm4,xmm1

	shufps	xmm3,xmm3,SHUFFLE(1,1,1,1)
	shufps	xmm4,xmm4,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm3
	addss	xmm1,xmm4

	ucomiss	xmm1,xmm6
	jne	Mat4uLHLookAtCont1
	jmp	Mat4uLHDB0

Mat4uLHLookAtCont1:

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	divps	xmm0,xmm1			; xmm0 = x

	;; y = normalize(cross(z,x))
	;;

	movaps	xmm1,xmm2
	movaps	xmm3,xmm2
	movaps	xmm4,xmm0
	movaps	xmm5,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)	; z_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; z_zxy
	shufps	xmm4,xmm4,SHUFFLE(2,0,1,3)	; x_zxy
	shufps	xmm5,xmm5,SHUFFLE(1,2,0,3)	; x_yzx

	mulps	xmm1,xmm4			; z_yzx*x_zxy
	mulps	xmm3,xmm5			; z_zxy*x_yzx
	subps	xmm1,xmm3			; cross(z,x)

	movaps	xmm3,xmm1
	mulps	xmm3,xmm3			; sqr(cross(z,x))
	movaps	xmm4,xmm3
	movaps	xmm5,xmm3

	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)
	addss	xmm3,xmm4
	addss	xmm3,xmm5

	ucomiss	xmm3,xmm6
	jne	Mat4uLHLookAtCont2
	jmp	Mat4uLHDB0

Mat4uLHLookAtCont2:

	sqrtss	xmm3,xmm3
	shufps	xmm3,xmm3,SHUFFLE(0,0,0,0)
	divps	xmm1,xmm3			; y = normalize(cross(z,x))

	movaps	xmm3,xmm0
	movaps	xmm4,xmm1
	unpcklpd xmm0,xmm1
	movaps	xmm1,xmm0
	shufps	xmm0,xmm2,SHUFFLE(0,2,0,3)	; x,x,x,0.0
	shufps	xmm1,xmm2,SHUFFLE(1,3,1,3)	; y,y,y,0.0

	unpckhpd xmm3,xmm4
	shufps	xmm3,xmm2,SHUFFLE(0,2,2,3)

	movaps	xmm5,xmm7
	movaps	xmm6,xmm7
	shufps	xmm5,xmm5,SHUFFLE(0,0,0,0)
	shufps	xmm6,xmm6,SHUFFLE(1,1,1,1)
	shufps	xmm7,xmm7,SHUFFLE(2,2,2,2)

	mulps	xmm5,xmm0
	mulps	xmm6,xmm1
	mulps	xmm7,xmm3

	addps	xmm5,xmm6
	addps	xmm5,xmm7

	mulps	xmm5,[negVec]

	movups	[DReg],xmm0
	movups	[DReg+16],xmm1
	movups	[DReg+32],xmm3
	movups	[DReg+48],xmm5

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

Mat4uLHDB0:

	mov	[STACK_SAVE5],Srcp
	mov	[STACK_SAVE6],Dstp

	mov	Srcp,mat4Identity
	mov	Dstp,[STACK_PTR1]
	mov	CReg,16

	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]
	mov	Srcp,[STACK_SAVE5]
	mov	Dstp,[STACK_SAVE6]

	ret

	
_Mat4LookAtLH_OldAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]		; *eye
	mov	BReg,[STACK_PTR3]		; *center
	mov	CReg,[STACK_PTR4]		; *up
	mov	DReg,[STACK_PTR1]		; *r

	movss	xmm6,[zeroVec]

	;; z = Normalize(center - eye)

	movaps	xmm0,[BReg]			; center
	subps	xmm0,[AReg]			; center - eye
	movaps	xmm1,xmm0
	mulps	xmm1,xmm0			; sqr(center - eye)

	;;
	;; YYY:	Should be haddps xmm1,[zeroVec],haddps xmm1,[zeroVec]
	;; 
	;; movaps	[DReg],xmm1
	;; addss	xmm1,[DReg+4]
	;; addss	xmm1,[DReg+8]

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	shufps	xmm1,xmm1,SHUFFLE(0,0,0,0)
	shufps	xmm2,xmm2,SHUFFLE(1,1,1,1)
	shufps	xmm3,xmm3,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm2
	addss	xmm1,xmm3

	;; sqrtss	xmm1,xmm2			; XXX: Zero check here rqd

	sqrtss	xmm1,xmm1

	ucomiss	xmm1,xmm6
	je	LHLookAtSkip1
	divps	xmm0,xmm1			; xmm0:	z

LHLookAtSkip1:

	movaps	xmm2,xmm0			; xmm2:	z
	movaps	xmm4,xmm2

	;; x = y (X) z

	movaps	xmm1,[CReg]			; y = up
	movaps	xmm3,xmm1			; y

	shufps	xmm1,xmm1,SHUFFLE(2,3,1,0)	; y.y y.z y.x
	shufps	xmm2,xmm2,SHUFFLE(1,3,2,0)	; z.z z.x z.y
	shufps	xmm3,xmm3,SHUFFLE(1,3,2,0)	; y.z y.x y.y
	shufps	xmm4,xmm4,SHUFFLE(2,1,3,0)	; z.y z.z z.x

	mulps	xmm1,xmm2 
	mulps	xmm3,xmm4
	subps	xmm1,xmm3			; x

	;; y = z (X) x

	movaps	xmm2,xmm0			; xmm2:	z
	movaps	xmm3,xmm1			; xmm1:	x
	movaps	xmm4,xmm0
	movaps	xmm5,xmm3

	shufps	xmm2,xmm2,SHUFFLE(2,1,3,0)	; z.y z.z z.x
	shufps	xmm3,xmm3,SHUFFLE(1,3,2,0)	; x.z x.x x.y
	shufps	xmm4,xmm4,SHUFFLE(1,3,2,0)	; z.z z.x z.y
	shufps	xmm5,xmm5,SHUFFLE(2,1,3,0)	; x.y x.z x.x

	mulps	xmm2,xmm3
	mulps	xmm4,xmm5
	subps	xmm2,xmm4			; y

	;; Normalize(x)

	movaps	xmm3,xmm1
	mulps	xmm3,xmm1

	movaps	xmm4,xmm3
	movaps	xmm5,xmm3
	shufps	xmm3,xmm3,SHUFFLE(0,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)
	addss	xmm3,xmm4
	addss	xmm3,xmm5
	sqrtss	xmm3,xmm3
	ucomiss	xmm3,xmm6
	je	LHLookAtSkip2
	shufps	xmm3,xmm3,0			; XXX:	Check for 0 here
	divps	xmm1,xmm3			; x

LHLookAtSkip2:

	;; Normalize(y)

	movaps	xmm3,xmm2
	mulps	xmm3,xmm2
	movaps	xmm4,xmm3
	movaps	xmm5,xmm3
	shufps	xmm3,xmm3,SHUFFLE(0,0,0,0)
	shufps	xmm4,xmm4,SHUFFLE(1,1,1,1)
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)
	addss	xmm3,xmm4
	addss	xmm3,xmm5
	sqrtss	xmm3,xmm3
	ucomiss	xmm3,xmm6
	je	LHLookAtSkip3
	shufps	xmm3,xmm3,0			; XXX:	comiss here
	divps	xmm2,xmm3			; y

LHLookAtSkip3:

	movaps	[DReg],xmm1			; x
	movaps	[DReg+16],xmm2			; y

	;; A little swizzle

	movlps	xmm1,[DReg+16]			; x.x x.y y.x y.y
	movaps	xmm3,xmm1
	shufps	xmm1,xmm0,SHUFFLE(3,1,3,0)	; x.x y.x z.x
	shufps	xmm3,xmm0,SHUFFLE(2,0,2,0)	; x.y y.y z.y
	movhps	xmm2,[DReg+8]			; x.z xxx y.z xxx
	shufps	xmm2,xmm0,SHUFFLE(3,1,1,0)	; x.z y.z z.z

	movaps	[DReg],xmm1			; .x
	movaps	[DReg+16],xmm3			; .y
	movaps	[DReg+32],xmm2			; .z

	movaps	xmm0,[zeroVec]			;   0.0   0.0   0.0
	movaps	xmm4,[BReg]			; eye.x eye.y eye.z
	movaps	xmm5,xmm4
	movaps	xmm6,xmm4

	shufps	xmm4,xmm4,SHUFFLE(3,3,3,3)	; eye.x eye.x eye.x
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)	; eye.y eye.y eye.y
	shufps	xmm6,xmm6,SHUFFLE(1,1,1,1)	; eye.z eye.z eye.z

	mulps	xmm1,xmm4			; x.x*eye.x y.x*eye.x z.x*eye.x
	mulps	xmm3,xmm5			; x.y*eye.y y.y*eye.y z.y*eye.y
	mulps	xmm2,xmm6			; x.z*eye.z y.z*eye.z z.z*eye.z

	subps	xmm0,xmm1
	subps	xmm0,xmm3
	subps	xmm0,xmm2

	movaps	[DReg+48],xmm0

	;; Finish the matrix

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

%endif

;;;
;;; Mat4IdentityAsm(mat4& r)
;;;
;;; Call Stack
;;;
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4Identity(mat4& r)
;;;

_Mat4IdentityAsm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],Srcp
	mov	[STACK_SAVE3],Dstp

	mov	ecx,16

	mov	Srcp,mat4Identity
	mov	Dstp,[STACK_PTR1]
	cld
	rep	movsd

	mov	CReg,[STACK_SAVE1]
	mov	Srcp,[STACK_SAVE2]
	mov	Dstp,[STACK_SAVE3]

	ret
	
;;;
;;; Mat4ScaleAsm
;;;
;;; Call Stack
;;;
;;; [4] float z
;;; [3] float y
;;; [2] float x
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4ScaleAsm(mat4& r,const float x_scale,const float y_scale,const float z_scale)
;;;

_Mat4ScaleAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg
	mov	DReg,[STACK_PTR1]	; *r

	;; Fill in the matrix 0 values

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+44],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	;; Fill in the matrix 1 values

	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	eax,[STACK_PTR2]	; x_scale
	mov	[DReg],eax

	mov	eax,[STACK_PTR3]	; y_scale
	mov	[DReg+20],eax

	mov	eax,[STACK_PTR4]	; z_scale
	mov	[DReg+40],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateRHX_Asm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4RotateRHX_Asm(mat4& r,const float angle)
;;;

_Mat4RotateRHX_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]
	fsincos
	fst	dword [DReg+20]
	fstp	dword [DReg+40]
	fst	dword [DReg+36]
	fchs
	fstp	dword [DReg+24]

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+44],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg],eax
	mov	[DReg+60],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateLHX_Asm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4RotateLHX_Asm(mat4& r,const float angle)
;;;

_Mat4RotateLHX_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [DReg+20]		; cosX
	fstp	dword [DReg+40]
	fst	dword [DReg+24]		; sinX
	fchs
	fstp	dword [DReg+36]		; -sinX

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+44],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg],eax
	mov	[DReg+60],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateRHY_Asm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4RotateRHY_Asm(mat4& r,const float angle)
;;;
;;; IMPLEMENTORS NOTE:	Shifted from LH to RH Coordinate calculation
;;;			from the original implementation ... Note in
;;;			non-assembly method
;;;
;;; IMPLEMENTORS NOTE:	All coordinate system transformations appear
;;;			to be backwards. eg. RH is LH and LH is RH
;;;			Visual verification is required using non-assembly
;;;			methods prior to release.
;;;

_Mat4RotateRHY_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]
	fsincos
	fst	dword [DReg]		; cosY
	fstp	dword [DReg+40]
	fst	dword [DReg+8]		; sinY
	fchs
	fstp	dword [DReg+32]		; -sinY

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+36],eax
	mov	[DReg+44],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg+20],eax
	mov	[DReg+60],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateLHY_Asm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4RotateLHY_Asm(mat4& r,const float angle)
;;; 
;;;

_Mat4RotateLHY_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]
	fsincos
	fst	dword [DReg]		; cosX
	fstp	dword [DReg+40]
	fst	dword [DReg+32]		; sinX
	fchs
	fstp	dword [DReg+8]

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+36],eax
	mov	[DReg+44],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg+20],eax
	mov	[DReg+60],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateRHZ_Asm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4RotateRHZ_Asm(mat4& r,const float angle)
;;;

_Mat4RotateRHZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [DReg]		; cosZ
	fstp	dword [DReg+20]
	fst	dword [DReg+16]		; sinZ
	fchs
	fstp	dword [DReg+4]		; -sinZ

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+44],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg+40],eax
	mov	[DReg+60],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateLHZ_Asm
;;;
;;; Call Stack
;;;
;;; [2] float angle
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4RotateLHZ_Asm(mat4& r,const float angle)
;;;

_Mat4RotateLHZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]
	fsincos

	fst	dword [DReg]		; cosZ
	fstp	dword [DReg+20]
	fst	dword [DReg+4]		; sinZ
	fchs
	fstp	dword [DReg+16]		; -sinZ

	fnclex

	mov	eax,[zeroVec]
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+44],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg+40],eax
	mov	[DReg+60],eax

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret
	
;;;
;;; Mat4RotateRHXY_Asm
;;;
;;; Call Stack
;;;
;;; [3] float y_angle
;;; [2] float x_angle
;;; [1] mat4* m
;;; ret
;;;
;;; extern "C" void Mat4RotateRHXY_Asm(mat4& r,const float x_scale,const float y_scale)
;;;

_Mat4RotateRHXY_Asm:


	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x
	fsincos				; [0] cosx [1] sinx
	fld	dword [STACK_PTR3]	; y
	fsincos				; [0] cosy [1] siny [2] cosx [3] sinx

	fst	dword [AReg]		; [0] cosy [1] siny [2] cosx [3] sinx

	fld	st3			; [0] sinx [1] cosy [2] siny [3] cosx [4] sinx
	fchs				; [0] -sinx [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st1			; [0] -sinx*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+24]		; [0] cosy [1] siny [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosy*cosx [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+40]		; [0] siny [1] cosx [2] sinx

	fst	dword [AReg+8]		; [0] siny [1] cosx [2] sinx

	fld	st2			; [0] sinx [1] siny [2] cosx [3] sinx
	fmul	st0,st1			; [0] sinx*siny [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+16]		; [0] siny [1] cosx [2] sinx

	fchs				; [0] -siny [1] cosx [2] sinx
	fmul	st0,st1			; [0] -siny*cosx [1] cosx [2] sinx
	fstp	dword [AReg+32]		; [0] cosx [1] sinx

	fstp	dword [AReg+20]		; [0] sinx
	fstp	dword [AReg+36]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+4],edx
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+48],edx
	mov	[AReg+52],edx
	mov	[AReg+56],edx
	mov	edx,[oneVec]
	mov	[AReg+60],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateLHXY_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float y_angle
;;; [2] const float x_angle
;;; [1] mat3* r
;;;
;;; extern "C" void Mat4RotateLHXY_Asm(mat4* r,const float x,const float y);
;;;

_Mat4RotateLHXY_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x
	fsincos				; [0] cosx [1] sinx
	fld	dword [STACK_PTR3]	; y
	fsincos				; [0] cosy [1] siny [2] cosx [3] sinx

	fst	dword [AReg]		; [0] cosy [1] siny [2] cosx [3] sinx
	fld	st0			; [0] cosy [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st4			; [0] sinx*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+24]		; [0] cosy [1] siny [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosx*cosy [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+40]		; [0] siny [1] cosx [2] sinx

	fld	st0
	fchs				; [0] -siny [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+8]		; [0] siny [1] cosx [2] sinx

	fld	st0			; [0] siny [1] siny [2] cosx [3] sinx
	fmul	st0,st3			; [0] sinx*siny [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+16]		; [0] siny [1] cosx [2] sinx

	fmul	st0,st1			; [0] cosx*siny [1] cosx [2] sinx
	fstp	dword [AReg+32]		; [0] cosx [1] sinx

	fstp	dword [AReg+20]		; [0] sinx
	fchs				; [0] -sinx
	fstp	dword [AReg+36]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+4],edx
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+48],edx
	mov	[AReg+52],edx
	mov	[AReg+56],edx
	mov	edx,[oneVec]
	mov	[AReg+60],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateRHXZ_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float z_angle
;;; [2] const float x_angle
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4RotateRHXZ_Asm(mat4* m,const float x,const float z);
;;;

_Mat4RotateRHXZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x_angle
	fsincos				; [0] cosx [1] sinx
	fld	dword [STACK_PTR3]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosx [3] sinx

	fst	dword [AReg]		; [0] cosz [1] sinz [2] cosx [3] sinx

	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosx [4] sinx
	fmul	st0,st4			; [0] sinx*cosz [1] cosz [2] sinz [3] cosx [4] sinx
	fstp	dword [AReg+36]		; [0] cosz [1] sinz [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosx*cosz [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+20]		; [0] sinz [1] cosx [2] sinx

	fld	st0			; [0] sinz [1] sinz [2] cosx [3] sinx
	fmul	st0,st3			; [0] sinx*sinz [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+32]		; [0] sinz [1] cosx [2] sinx

	fld	st0			; [0] sinz [1] sinz [2] cosx [3] sinx
	fmul	st0,st2			; [0] cosx*sinz [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+16]		; [0] sinz [1] cosx [2] sinx
	fchs				; [0] -sinz [1] cosx [2] sinx
	fstp	dword [AReg+4]		; [0] cosx [1] sinx

	fstp	dword [AReg+40]		; [0] sinx
	fchs				; [0] -sinx
	fstp	dword [AReg+24]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+8],edx
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+48],edx
	mov	[AReg+52],edx
	mov	[AReg+56],edx
	mov	edx,[oneVec]
	mov	[AReg+60],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateLHXZ_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float z_angle
;;; [2] const float x_angle
;;; [1] mat4* m
;;;
;;; extern "C" void Mat4RotateLHXZ_Asm(mat4* m,const float x,const float z);
;;;

_Mat4RotateLHXZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x_angle
	fsincos				; [0] cosx [1] sinx
	fld	dword [STACK_PTR3]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosx [3] sinx

	fld	st3			; [0] sinx [1] cosz [2] sinz [3] cosx [4] sinx
	fchs				; [0] -sinx [1] cosz [2] sinz [3] cosx [4] sinx
	fmul	st0,st1			; [0] -sinx*cosz [1] cosz [2] sinz [3] cosx [4] sinx
	fstp	dword [AReg+36]		; [0] cosz [1] sinz [2] cosx [3] sinx

	fst	dword [AReg]		; [0] cosz [1] sinz [2] cosx [3] sinx
	fmul	st0,st2			; [0] cosx*cosz [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+20]		; [0] sinz [1] cosx [2] sinx

	fst	dword [AReg+4]		; [0] sinz [1] cosx [2] sinx

	fld	st0			; [0] sinz [1] sinz [2] cosx [3] sinx
	fchs				; [0] -sinz [1] sinz [2] cosx [3] sinx
	fmul	st0,st2			; [0] -sinz*cosx [1] sinz [2] cosx [3] sinx
	fstp	dword [AReg+16]		; [0] sinz [1] cosx [2] sinx

	fmul	st2			; [0] sinx*sinz [1] cosx [2] sinx
	fstp	dword [AReg+32]		; [0] cosx [1] sinx

	fstp	dword [AReg+40]		; [0] sinx
	fstp	dword [AReg+24]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+8],edx
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+48],edx
	mov	[AReg+52],edx
	mov	[AReg+56],edx
	mov	edx,[oneVec]
	mov	[AReg+60],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateRHYZ_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float z_angle
;;; [2] const float y_angle
;;; [1] mat4* m
;;;
;;; extern "C" void Mat4RotateRHYZ_Asm(mat4* r,const float y,const float z)
;;;

_Mat4RotateRHYZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; y_angle
	fsincos				; [0] cosy [1] siny
	fld	dword [STACK_PTR3]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosy [3] siny

	fst	dword [AReg+20]		; [0] cosz [1] sinz [2] cosy [3] siny

	fld	st3			; [0] siny [1] cosz [2] sinz [3] cosy [4] siny
	fchs				; [0] -siny [1] cosz [2] sinz [3] cosy [4] siny
	fmul	st0,st1			; [0] -siny*cosz [1] cosz [2] sinz [3] cosy [4] siny
	fstp	dword [AReg+32]		; [0] cosz [1] sinz [2] cosy [3] siny

	fmul	st0,st2			; [0] cosy*cosz [1] sinz [2] cosy [3] siny
	fstp	dword [AReg]		; [0] sinz [1] cosy [2] siny

	fld	st0			; [0] sinz [1] sinz [2] cosy [3] siny
	fchs				; [0] -sinz [1] sinz [2] cosy [3] siny
	fmul	st0,st2			; [0] -sinz*cosy [1] sinz [2] cosy [3] siny
	fstp	dword [AReg+4]		; [0] sinz [1] cosy [2] siny

	fst	dword [AReg+16]		; [0] sinz [1] cosy [2] siny
	fmul	st0,st2			; [0] siny*sinz [1] cosy [2] siny
	fstp	dword [AReg+36]		; [0] cosy [1] siny
	fstp	dword [AReg+40]		; [0] siny
	fstp	dword [AReg+8]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+24],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+48],edx
	mov	[AReg+52],edx
	mov	[AReg+56],edx
	mov	edx,[oneVec]
	mov	[AReg+60],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateLHYZ_Asm
;;;
;;; Call Stack
;;;
;;; [3] const float z_angle
;;; [2] const float y_angle
;;; [1] mat4* m
;;;
;;; extern "C" void Mat4RotateLHYZ_Asm(mat4* m,const float y,const float z);
;;;

_Mat4RotateLHYZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]
	fsincos				; [0] cosy [1] siny
	fld	dword [STACK_PTR3]
	fsincos				; [0] cosz [1] sinz [2] cosy [3] siny

	fst	dword [AReg+20]		; [0] cosz [1] sinz [2] cosy [3] siny
	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosy [4] siny
	fmul	st0,st3			; [0] cosy*cosz [1] cosz [2] sinz [3] cosy [4] siny
	fstp	dword [AReg]		; [0] cosz [1] sinz [2] cosy [3] siny

	fmul	st0,st3			; [0] siny*cosz [1] sinz [2] cosy [3] siny
	fstp	dword [AReg+32]		; [0] sinz [1] cosy [2] siny

	fld	st0
	fchs				; [0] -sinz [1] sinz [2] cosy [3] siny
	fstp	dword [AReg+16]		; [0] sinz [1] cosy [2] siny

	fld	st0			; [0] sinz [1] sinz [2] cosy [3] siny
	fmul	st0,st2			; [0] cosy*sinz [1] sinz [2] cosy [3] siny
	fstp	dword [AReg+4]		; [0] sinz [1] cosy [2] siny

	fmul	st0,st2			; [0] siny*sinz [1] cosy [2] siny
	fstp	dword [AReg+36]		; [0] cosy [1] siny
	
	fstp	dword [AReg+40]		; [0] siny
	fchs				; [0] -siny
	fstp	dword [AReg+8]

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+24],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+48],edx
	mov	[AReg+52],edx
	mov	[AReg+56],edx
	mov	edx,[oneVec]
	mov	[AReg+60],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4RotateRHXYZ_Asm
;;;
;;; Call Stack
;;;
;;; [4] const float z_angle
;;; [3] const float y_angle
;;; [2] const float x_angle
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4RotateRHXYZ_Asm(mat4& r,const float x,const float y,const float z)
;;;

_Mat4RotateRHXYZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x_angle
	fsincos				; [0] cosx [1] sinx

	fld	dword [STACK_PTR3]	; y_angle
	fsincos				; [0] cosy [1] siny [2] cosx [3] sinx

	fld	dword [STACK_PTR4]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st2			; [0] cosy [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st1			; [0] cosy*cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st5			; [0] sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st4			; [0] sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st1			; [0] cosz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st5			; [0] cosx [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st3			; [0] cosx*sinx [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] cosx*sinx+cosz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+16]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st1			; [0] sinz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fchs				; [0] -sinz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st6			; [0] -sinz*sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st4			; [0] -sinz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st5			; [0] cosx [1] -sinz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st2			; [0] cosx*cosz [1] -sinz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] cosx*cosz+(-sinz*sinx*siny) [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+20]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st3			; [0] siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fchs				; [0] -siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st5			; [0] -siny*cosx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st1			; [0] -siny*cosx*cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st2			; [0] sinz [1] -siny*cosx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st7			; [0] sinz*sinx [1] -siny*cosx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] sinz*sinx+(-siny*cosx*cosz) [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+32]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fmul	st0,st5			; [0] cosz*sinx [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fld	st4			; [0] cosx [1] cosz*sinx [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st4			; [0] cosx*siny [1] cosz*sinx [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st2			; [0] cosx*siny*sinz [1] cosz*sinx [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	faddp	st1,st0			; [0] cosx*siny*sinz+cosz*sinx [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fstp	dword [AReg+36]		; [0] sinz [1] cosy [2] siny [3] cosx [4] sinx

	fchs				; [0] -sinz [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st1			; [0] -sinz*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+4]		; [0] cosy [1] siny [2] cosx [3] sinx

	fld	st3			; [0] sinx [1] cosy [2] siny [3] cosx [4] sinx
	fchs				; [0] -sinx [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st1			; [0] -sinx*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+24]		; [0] cosy [1] siny [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosy*cosx [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+40]		; [0] siny [1] cosx [2] sinx

	fstp	dword [AReg+8]		; [0] cosx [1] sinx

	ffree	st1
	ffree	st0
	fincstp
	fincstp

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+48],edx
	mov	[AReg+52],edx
	mov	[AReg+56],edx
	mov	edx,[oneVec]
	mov	[AReg+60],edx

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	fwait

	ret

;;;
;;; Mat4RotateLHXYZ_Asm
;;;
;;; Call Stack
;;;
;;; [4] const float z_angle
;;; [3] const float y_angle
;;; [2] const float x_angle
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4RotateLHXYZ_Asm(mat4& r,const float x,const float y,const float z)
;;;

_Mat4RotateLHXYZ_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	AReg,[STACK_PTR1]	; *r

	fld	dword [STACK_PTR2]	; x_angle
	fsincos				; [0] cosx [1] sinx

	fld	dword [STACK_PTR3]	; y_angle
	fsincos				; [0] cosy [1] siny [2] cosx [3] sinx

	fld	dword [STACK_PTR4]	; z_angle
	fsincos				; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st3			; [0] cosy*cosz [0] cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st6			; [0] cosz*sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st4			; [0] cosz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st2			; [0] sinz [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fchs				; [0] -sinz [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st6			; [0] -sinz*cosx [1] cosz*sinx*siny [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] -sinz*cosx+cosz*sinx*siny [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+16]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st0			; [0] cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st5			; [0] cosz*cosx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st6			; [0] sinx [1] cosz*cosx [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st5			; [0] sinx*siny [1] cosz*cosx [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st7			; [0] sinx*siny*sinz [1] cosz*cosx [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] sinx*siny*sinz+cosz*cosx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+20]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fld	st5			; [0] sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fchs				; [0] -sinx [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st1			; [0] -sinx*cosz [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fld	st5			; [0] cosx [1] -sinx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st5			; [0] cosx*siny [1] -sinx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	fmul	st0,st3			; [0] cosx*siny*sinz [1] -sinx*cosz [2] cosz [3] sinz [4] cosy [5] siny [6] cosx [7] sinx
	faddp	st1,st0			; [0] cosx*siny*sinz+(-sinx*cosz) [1] cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fstp	dword [AReg+36]		; [0] cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx

	fmul	st0,st4			; [0] cosx*cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fmul	st0,st3			; [0] cosx*siny*cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fld	st5			; [0] sinx [1] cosx*siny*cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	fmul	st0,st2			; [0] sinx*sinz [1] cosx*siny*cosz [2] sinz [3] cosy [4] siny [5] cosx [6] sinx
	faddp	st1,st0			; [0] sinx*sinz+cosx*siny*cosz [1] sinz [2] cosy [3] siny [4] cosx [5] sinx
	fstp	dword [AReg+32]		; [0] sinz [1] cosy [2] siny [3] cosx [4] sinx

	fmul	st0,st1			; [0] cosy*sinz [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+4]		; [0] cosy [1] siny [2] cosx [3] sinx

	fld	st0			; [0] cosy [1] cosy [2] siny [3] cosx [4] sinx
	fmul	st0,st4			; [0] sinx*cosy [1] cosy [2] siny [3] cosx [4] sinx
	fstp	dword [AReg+24]		; [0] cosy [1] siny [2] cosx [3] sinx

	fmul	st0,st2			; [0] cosx*cosy [1] siny [2] cosx [3] sinx
	fstp	dword [AReg+40]		; [0] siny [1] cosx [2] sinx

	fchs				; [0] -siny [1] cosx [2] sinx
	fstp	dword [AReg+8]		; [0] cosx [1] sinx

	ffree	st1
	ffree	st0
	fincstp
	fincstp

	fnclex

	mov	edx,[zeroVec]
	mov	[AReg+12],edx
	mov	[AReg+28],edx
	mov	[AReg+44],edx
	mov	[AReg+48],edx
	mov	[AReg+52],edx
	mov	[AReg+56],edx
	mov	edx,[oneVec]
	mov	[AReg+60],edx

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4TranslateRH_FloatAsm
;;;
;;; Call Stack
;;;
;;; [4] float z
;;; [3] float y
;;; [2] float x
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4TranslateRH_Asm(mat4& r,const float x,const float y,const float z)
;;;

_Mat4TranslateRH_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg],eax
	mov	[DReg+20],eax
	mov	[DReg+40],eax
	mov	[DReg+60],eax

	mov	eax,[STACK_PTR2]
	mov	[DReg+12],eax		; x

	mov	eax,[STACK_PTR3]	; y
	mov	[DReg+28],eax

	mov	eax,[STACK_PTR4]	; z
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4TranslateLH_Asm
;;;
;;; Call Stack
;;;
;;; [4] float z
;;; [3] float y
;;; [2] float x
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4TranslateLH_Asm(mat4& r,const float x,const float y,const float z)
;;;

_Mat4TranslateLH_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+44],eax

	mov	eax,[oneVec]
	mov	[DReg],eax
	mov	[DReg+20],eax
	mov	[DReg+40],eax
	mov	[DReg+60],eax

	mov	eax,[STACK_PTR2]
	mov	[DReg+48],eax		; x

	mov	eax,[STACK_PTR3]	; y
	mov	[DReg+52],eax

	mov	eax,[STACK_PTR4]	; z
	mov	[DReg+56],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; Mat4TranslateRH_Vec3Asm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4TranslateRH_Vec3Asm(mat4& r,const vec3& v)
;;;

_Mat4TranslateRH_Vec3Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; *v

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg],eax
	mov	[DReg+20],eax
	mov	[DReg+40],eax
	mov	[DReg+60],eax

	mov	eax,[BReg]		; v.x
	mov	[DReg+12],eax
	mov	eax,[BReg+4]		; v.y
	mov	[DReg+28],eax
	mov	eax,[BReg+8]		; v.z
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4TranslateLH_Vec3Asm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v;
;;; [1] mat4* r;
;;;
;;; extern "C" void Mat4TranslateLH_Vec3Asm(mat4* r,const vec3* v);
;;;

_Mat4TranslateLH_Vec3Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; *v

	mov	edx,[zeroVec]
	mov	[AReg+4],edx
	mov	[AReg+8],edx
	mov	[AReg+12],edx
	mov	[AReg+16],edx
	mov	[AReg+24],edx
	mov	[AReg+28],edx
	mov	[AReg+32],edx
	mov	[AReg+36],edx
	mov	[AReg+44],edx

	mov	edx,[oneVec]
	mov	[AReg],edx
	mov	[AReg+20],edx
	mov	[AReg+40],edx
	mov	[AReg+60],edx

	mov	edx,[BReg]
	mov	[AReg+48],edx
	mov	edx,[BReg+4]
	mov	[AReg+52],edx
	mov	edx,[BReg+8]
	mov	[AReg+56],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret
	
;;;
;;; Mat4TranslateRH_Vec4Asm
;;;
;;; Call Stack
;;;
;;; [2] vec3* v
;;; [1] mat4* r
;;; [0] ret
;;;
;;; extern "C" void Mat4TranslateVec4Asm(mat4& r,const vec4& v)
;;;

_Mat4TranslateRH_Vec4Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; *v

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg],eax
	mov	[DReg+20],eax
	mov	[DReg+40],eax
	mov	[DReg+60],eax

	mov	eax,[BReg]		; v.x
	mov	[DReg+12],eax
	mov	eax,[BReg+4]		; v.y
	mov	[DReg+28],eax
	mov	eax,[BReg+8]		; v.z
	mov	[DReg+44],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4TranslateLH_Vec4Asm
;;;
;;; Call Stack
;;;
;;; [2] vec4* v
;;; [1] mat4* m
;;;
;;; extern "C" void Mat4TranslateLH_Vec4Asm(mat4* r,const vec4* v)
;;;

_Mat4TranslateLH_Vec4Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; *v

	mov	edx,[zeroVec]
	mov	[AReg+4],edx
	mov	[AReg+8],edx
	mov	[AReg+12],edx
	mov	[AReg+16],edx
	mov	[AReg+24],edx
	mov	[AReg+28],edx
	mov	[AReg+32],edx
	mov	[AReg+36],edx
	mov	[AReg+44],edx

	mov	edx,[oneVec]
	mov	[AReg],edx
	mov	[AReg+20],edx
	mov	[AReg+40],edx
	mov	[AReg+60],edx

	mov	edx,[BReg]
	mov	[AReg+48],edx
	mov	edx,[BReg+4]
	mov	[AReg+52],edx
	mov	edx,[BReg+8]
	mov	[AReg+56],edx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4OrthoMatrixAsm
;;;
;;; Call Stack
;;;
;;; [8] int32_t d3dFlag
;;; [7] float zFar
;;; [6] float zNear
;;; [5] float bottom
;;; [4] float top
;;; [3] float right
;;; [2] float left
;;; [1] mat4* m
;;; [0] ret
;;;
;;; extern "C" void Mat4OrthoMatrixAsm(mat4&         r,
;;;                                    const float   left,    1.0
;;;                                    const float   right,   5.0
;;;                                    const float   top      1.0
;;;                                    const float   bottom   5.0
;;;                                    const float   zNear  -20.0
;;;                                    const float   zFar   100.0
;;;                                    const int32_t d3dFlag)
;;;

_Mat4OrthoMatrixAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	fld	dword [floatTwo]	; [0] 2.0
	fld	dword [STACK_PTR2]	; [0] left [1] 2.0
	fld	dword [STACK_PTR3]	; [0] right [1] left [2] 2.0
	fld	st0			; [0] right [1] right [2] left [3] 2.0
	fsub	st0,st2			; [0] right-left [1] right [2] left [3] 2.0
	fld	st0			; [0] right-left [1] right-left [2] right [3] left [4] 2.0
	fldz				; [0] 0.0 [1] right-left [2] right-left [3] right [4] left [5] 2.0
	fcomip	st0,st1			; right-left == 0.0?
	jne	Mat4OrthoContinue1	; [0] right-left [1] right [2] left [3] 2.0
	jmp	Mat4OrthoDump4DB0
Mat4OrthoContinue1:
	fdivr	st0,st4			; [0] 2.0/right-left [1] right-left [2] right [3] left [4] 2.0
	fstp	dword [DReg]		; [0] right-left [1] right [2] left [3] 2.0
	fxch	st0,st2			; [0] left [1] right [2] right-left [3] 2.0
	faddp	st1,st0			; [0] left+right [1] right-left [2] 2.0
	fchs				; [0] -(right+left) [1] right-left [2] 2.0
	fdivrp	st1,st0			; [0] -(right+left)/right-left [1] 2.0
	fstp	dword [DReg+12]		; [0] 2.0

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax

	fld	dword [STACK_PTR5]	; [0] bottom [1] 2.0
	fld	dword [STACK_PTR4]	; [0] top [1] bottom [2] 2.0
	fld	st0			; [0] top [1] top [2] bottom [3] 2.0
	fsub	st0,st2			; [0] top-bottom [1] top [2] bottom [3] 2.0
	fld	st0			; [0] top-bottom [1] top-bottom [2] top [3] bottom [4] 2.0
	fldz				; [0] 0.0 [1] top-bottom [2] top-bottom [3] top [4] bottom [5] 2.0
	fcomip	st0,st1			; top-bottom == 0.0?
	jne	Mat4OrthoContinue2
	jmp	Mat4OrthoDump4DB0
Mat4OrthoContinue2:
	fdivr	st0,st4			; [0] 2.0/top-bottom [1] top-bottom [2] top [3] bottom [4] 2.0
	fstp	dword [DReg+20]		; [0] top-bottom [1] top [2] bottom [3] 2.0
	fxch	st0,st2			; [0] bottom [1] top [2] top-bottom [3] 2.0
	faddp	st1,st0			; [0] bottom+top [1] top-bottom [2] 2.0
	fchs				; [0] -(top+bottom) [1] top-bottom [2] 2.0
	fdivrp	st1,st0			; [0] -(top+bottom)/top-bottom [1] 2.0
	fstp	dword [DReg+28]		; [0] 2.0

	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	fchs				; [0] -2.0
	fld	dword [STACK_PTR6]	; [0] zNear [1] -2.0
	fld	dword [STACK_PTR7]	; [0] zFar [1] zNear [2] -2.0
	fld	st0			; [0] zFar [1] zFar [2] zNear [3] -2.0
	fsub	st0,st2			; [0] zFar-zNear [1] zFar [2] zNear [3] -2.0
	fld	st0			; [0] zFar-zNear [1] zFar-zNear [2] zFar [3] zNear [4] -2.0
	fldz				; [0] 0.0 [1] zFar-zNear [2] zFar-zNear [3] zFar [4] zNear [5] -2.0
	fcomip	st0,st1			; zFar-zNear == 0.0?
	jne	Mat4OrthoContinue3
	jmp	Mat4OrthoDump4DB0
Mat4OrthoContinue3:
	fdivr	st0,st4			; [0] -2.0/zFar-zNear [1] zFar-zNear [2] zFar [3] zNear [4] -2.0
	fstp	dword [DReg+40]		; [0] zFar-zNear [1] zFar [2] zNear [3] -2.0
	fxch	st2,st0			; [0] zNear [1] zFar [2] zFar-zNear [3] -2.0
	faddp	st1,st0			; [0] zNear+zFar [1] zFar-zNear [2] -2.0
	fchs				; [0] -(zFar+zNear) [1] zFar-zNear [2] -2.0
	fdivrp	st1,st0			; [0] -(zFar+zNear)/zFar-zNear [1] -2.0
	fstp	dword [DReg+44]		; [0] -2.0

	mov	eax,[oneVec]
	mov	[DReg+60],eax

	ffree	st0
	fincstp

	mov	eax,[STACK_PTR8]
	cmp	eax,0
	je	mat4ortho_done

	fld	dword [floatHalf]
	fld	dword [DReg+40]
	fadd	dword [DReg+56]
	fmul	st0,st1
	fstp	dword [DReg+40]

	fld	dword [DReg+44]
	fld1
	faddp	st1,st0
	fmulp	st1,st0
	fstp	dword [DReg+44]

mat4ortho_done:

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Mat4OrthoDump4DB0:		; [0] right-left [1] right [2] left [3] 2.0
	ffree	st0
	ffree	st1
	ffree	st2
	ffree	st3
	fincstp
	fincstp
	fincstp
	fincstp

	fnclex

	mov	[STACK_SAVE3],Srcp
	mov	[STACK_SAVE4],Dstp
	mov	[STACK_SAVE5],CReg

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]
	mov	CReg,[STACK_SAVE5]

	fwait

	ret
	

;;;
;;; Mat4OrthoStructAsm
;;;
;;; Call Stack
;;;
;;; [2] orthoStruct* s
;;; [1] mat4*        r
;;; [0] ret
;;;
;;; extern "C" void Mat4OrthoStructAsm(mat4& r,const orthoMatrix& s)
;;;

_Mat4OrthoStructAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	BReg,[STACK_PTR2]
	mov	DReg,[STACK_PTR1]

	fld	dword [floatTwo]	; [0] 2.0
	fld	dword [BReg]		; [0] left [1] 2.0
	fld	dword [BReg+4]		; [0] right [1] left [2] 2.0
	fld	st0			; [0] right [1] right [2] left [3] 2.0
	fsub	st0,st2			; [0] right-left [1] right [2] left [3] 2.0
	fld	st0			; [0] right-left [1] right-left [2] right [3] left [4] 2.0
	fldz				; [0] 0.0 [1] right-left [2] right-left [3] right [4] left [5] 2.0
	fcomip	st0,st1			; right-left == 0.0
	jne	Mat4OrthosCont1
	jmp	Mat4OrthosDump4DB0
Mat4OrthosCont1:
	fdivr	st0,st4			; [0] 2.0/right-left [1] right-left [2] right [3] left [4] 2.0
	fstp	dword [DReg]		; [0] right-left [1] right [2] left [3] 2.0
	fxch	st0,st2			; [0] left [1] right [2] right-left [3] 2.0
	faddp	st1,st0			; [0] left+right [1] right-left [2] 2.0
	fchs				; [0] -(right+left) [1] right-left [2] 2.0
	fdivrp	st1,st0			; [0] -(right+left)/right-left [1] 2.0
	fstp	dword [DReg+12]		; [0] 2.0

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax

	fld	dword [BReg+12]		; [0] bottom [1] 2.0
	fld	dword [BReg+8]		; [0] top [1] bottom [2] 2.0
	fld	st0			; [0] top [1] top [2] bottom [3] 2.0
	fsub	st0,st2			; [0] top-bottom [1] top [2] bottom [3] 2.0
	fld	st0			; [0] top-bottom [1] top-bottom [2] top [3] bottom [4] 2.0
	fldz				; [0] 0.0 [1] top-bottom [2] top-bottom [3] top [4] bottom [5] 2.0
	fcomip	st0,st1			; top-bottom == 0.0
	jne	Mat4OrthosCont2
	jmp	Mat4OrthosDump4DB0
Mat4OrthosCont2:
	fdivr	st0,st4			; [0] 2.0/top-bottom [1] top-bottom [2] top [3] bottom [4] 2.0
	fstp	dword [DReg+20]		; [0] top-bottom [1] top [2] bottom [3] 2.0
	fxch	st0,st2			; [0] bottom [1] top [2] top-bottom [3] 2.0
	faddp	st1,st0			; [0] bottom+top [1] top-bottom [2] 2.0
	fchs				; [0] -(top+bottom) [1] top-bottom [2] 2.0
	fdivrp	st1,st0			; [0] -(top+bottom)/top-bottom [1] 2.0
	fstp	dword [DReg+28]		; [0] 2.0

	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	fchs				; [0] -2.0
	fld	dword [BReg+16]		; [0] zNear [1] -2.0
	fld	dword [BReg+20]		; [0] zFar [1] zNear [2] -2.0
	fld	st0			; [0] zFar [1] zFar [2] zNear [3] -2.0
	fsub	st0,st2			; [0] zFar-zNear [1] zFar [2] zNear [3] -2.0
	fld	st0			; [0] zFar-zNear [1] zFar-zNear [2] zFar [3] zNear [4] -2.0
	fldz
	fcomip	st0,st1			; zFar-zNear == 0.0
	jne	Mat4OrthosCont3
	jmp	Mat4OrthosDump4DB0
Mat4OrthosCont3:
	fdivr	st0,st4			; [0] -2.0/zFar-zNear [1] zFar-zNear [2] zFar [3] zNear [4] -2.0
	fstp	dword [DReg+40]		; [0] zFar-zNear [1] zFar [2] zNear [3] -2.0
	fxch	st2,st0			; [0] zNear [1] zFar [2] zFar-zNear [3] -2.0
	faddp	st1,st0			; [0] zNear+zFar [1] zFar-zNear [2] -2.0
	fchs				; [0] -(zFar+zNear) [1] zFar-zNear [2] -2.0
	fdivrp	st1,st0			; [0] -(zFar+zNear)/zFar-zNear [1] -2.0
	fstp	dword [DReg+44]		; [0] -2.0

	mov	eax,[oneVec]
	mov	[DReg+60],eax

	ffree	st0

	fwait

	mov	eax,[BReg+24]		; XXX:	 Change structure to uint32_t
	cmp	eax,0
	je	mat4orthostruct_done

	fld	dword [floatHalf]
	fld	dword [DReg+40]
	fadd	dword [DReg+56]
	fmul	st0,st1
	fstp	dword [DReg+40]

	fld	dword [DReg+44]
	fld1
	faddp	st1,st0
	fmulp	st1,st0
	fstp	dword [DReg+44]

	fwait

mat4orthostruct_done:

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Mat4OrthosDump4DB0:

	ffree	st3
	ffree	st2
	ffree	st1
	ffree	st0

	mov	[STACK_SAVE3],Srcp
	mov	[STACK_SAVE4],Dstp
	mov	[STACK_SAVE5],CReg

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]
	mov	CReg,[STACK_SAVE5]

	ret

;;;
;;; Mat4PerspectiveAsm
;;;
;;; Call Stack
;;;
;;; [7] uint32_t d3dflag
;;; [6] float    zFar
;;; [5] float    zNear
;;; [4] float    height
;;; [3] float    width
;;; [2] float    fov
;;; [1] mat4*    r
;;; [0] ret
;;;
;;; mat4 = m4_perspective(const float    fov,
;;;                       const float    width
;;;                       const float    height
;;;                       const float    zNear
;;;                       const float    zFar
;;;                       const uint32_t d3dflag);
;;;
;;; extern "C" void Mat4PerspectiveAsm(mat4&          r,
;;;                                    const float    fov,
;;;                                    const float    width,
;;;                                    const float    height,
;;;                                    const float    zNear
;;;                                    const float    zFar,
;;;                                    const uint32_t d3dflag);
;;; 

_Mat4PerspectiveAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; Return matrix

	fld	dword [STACK_PTR2]	; [0] fov 
	fmul	dword [floatHalf]	; [0] 0.5*fov
	fptan				; [0] 1.0f [1] tanf(0.5*fov)
	fld	st1			; [0] tanf(0.5*fov) [1] 1.0 [2] tanf(0.5*fov)
	fldz				; [0] 0.0 [1] tanf(0.5*fov) [2] 1.0 [3] tanf(0.5*fov)
	fcomip	st0,st1			; 0.0 == tanf(0.5*fov)
	jne	Mat4PersCont1
	jmp	Mat4PersDump3DB0
Mat4PersCont1:
	fdivp	st1,st0			; [0] 1.0f/tanf(0.5*fov) [1] tanf(0.5*fov);
	fstp	dword [DReg]		; [0] tanf(0.5/fov)

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	fmul	dword [STACK_PTR4]	; [0] height * tanf(0.5*fov)
	fld	dword [STACK_PTR3]	; [0] width [1] height*tanf(0.5*fov)
	fldz				; [0] 0.0 [1] width [2] height*tanf(0.5*fov)
	fcomip	st0,st1			; width == 0.0
	jne	Mat4PersCont2
	jmp	Mat4PersDump1DB0
Mat4PersCont2:
	fdivp	st1,st0			; [0] height * tanf(0.5/fov) / width
	fldz				; [0] 0.0 [1] height*tanf(0.5*fov) / width
	fcomip	st0,st1			; 0.0 == height*tanf(0.5fov)/width?
	jne	Mat4PersCont3
	jmp	Mat4PersDump1DB0
Mat4PersCont3:	
	fld1				; [0] 1.0 [1] height * tanf(0.5/fov) / width
	fdivrp	st1,st0			; [0] 1.0/(height*tanf(0.5/fov)/width)
	fstp	dword [DReg+20]

	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax

	fld	dword [STACK_PTR5]	; [0] z_near
	fld	dword [STACK_PTR6]	; [0] z_far [1] z_near
	fld	st0			; [0] z_far [1] z_far [2] z_near
	fsub	st0,st2			; [0] z_far-z_near [1] z_far [2] z_near
	fld	st0			; [0] z_far-z_near [1] z_far-z_near [2] z_far [3] z_near
	fld	st2			; [0] z_far [1] z_far-z_near [2] z_far-z_near [3] z_far [4] z_near
	fadd	st4			; [0] z_far+z_near [1] z_far-z_near [2] z_far-z_near [3] z_far [4] z_near
	fldz
	fcomip	st0,st2			; 0.0 == z_far-z_near?
	jne	Mat4PersCont4
	jmp	Mat4PersDump5DB0
Mat4PersCont4:
	fdivrp	st1,st0			; [0] (z_far+z_near)/(z_far-z_near) [1] z_far-z_near [2] z_far [3] z_near
	fstp	dword [DReg+40]		; [0] z_far-z_near [1] z_far [2] z_near

	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+60],eax

	fxch	st0,st2			; [0] z_near [1] z_far [2] z_far-z_near
	fmul	dword [floatTwo]
	fmulp	st1,st0			; [0] 2.0*z_near*z_far [1] z_far-z_near
	fchs				; [0] -(2.0*z_near*z_far) [1] z_far-z_near
	fdivrp	st1,st0			; [0] -(2.0*z_near*z_far)/(z_far-z_near)
	fstp	dword [DReg+44]

	mov	eax,[oneVec]
	mov	[DReg+56],eax

	mov	ecx,[STACK_PTR7]	; d3dflag
	cmp	ecx,0
	je	mat4pers_done

	fld	dword [floatHalf]	; [0] 0.5
	fld	dword [DReg+40]		; [0] m22 [1] 0.5
	fadd	dword [DReg+56]		; [0] m22+m32 [1] 0.5
	fmul	st0,st1			; [0] 0.5*(m22+m32) [1] 0.5
	fstp	dword [DReg+40]

	fmul	dword [DReg+44]		; 0.5 * (m23 + m33)
	fstp	dword [DReg+44]

mat4pers_done:

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

Mat4PersDump5DB0:
	ffree	st4
	ffree	st3
	fincstp
	fincstp

Mat4PersDump3DB0:
	ffree	st2
	ffree	st1
	fincstp
	fincstp

Mat4PersDump1DB0:
	ffree	st0
	fincstp

	fnclex

	mov	[STACK_SAVE3],Srcp
	mov	[STACK_SAVE4],Dstp
	mov	[STACK_SAVE5],CReg

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]
	mov	CReg,[STACK_SAVE5]

	ret

;;;
;;; Mat4PerspectiveXAsm
;;;
;;; Call Stack
;;;
;;; [2] perspectiveMatrix* p
;;; [1] mat4*              m
;;; [0] ret
;;;
;;; mat4 = m4_perspectiveX(const struct perspectiveMatrix& s)
;;;
;;; extern "C" void Mat4PerspectiveXAsm(mat4& r,const struct perspectiveMatrix& s)
;;; 

_Mat4PerspectiveXAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; Return matrix
	mov	AReg,[STACK_PTR2]	; perspectiveMatrix

	fld	dword [AReg]		; [0] fov 
	fmul	dword [floatHalf]	; [0] 0.5/fov
	fptan				; [0] tanf(0.5/fov)
	fld	st1			; [0] tanf(0.5*fov) [1] 1.0 [2] tanf(0.5*fov)
	fldz				; [0] 0.0 [1] tanf(0.5*fov) [2] 1.0 [3] tanf(0.5*fov)
	fcomip	st0,st1			; 0.0 == tanf(0.5*fov)
	jne	Mat4PersxCont1
	jmp	Mat4PersxDump3DB0
Mat4PersxCont1:
	fdivp	st1,st0			; [0] 1.0/tanf(0.5/fov) [1] tanf(0.5/fov)
	fstp	dword [DReg]		; [0] tanf(0.5/fov)

	mov	ecx,[zeroVec]
	mov	[DReg+4],ecx
	mov	[DReg+8],ecx
	mov	[DReg+12],ecx

	fmul	dword [AReg+8]		; [0] height * tanf(0.5/fov)
	fld	dword [AReg+4]		; [0] width [1] height*tanf(0.5*fov)
	fldz				; [0] 0.0 [1] width [2] height*tanf(0.5*fov)
	fcomip	st0,st1			; width == 0.0
	jne	Mat4PersxCont2
	jmp	Mat4PersxDump1DB0
Mat4PersxCont2:
	fdivp	st1,st0			; [0] height * tanf(0.5/fov) / width
	fldz				; [0] 0.0 [1] height*tanf(0.5*fov) / width
	fcomip	st0,st1			; 0.0 == height*tanf(0.5fov)/width?
	jne	Mat4PersxCont3
	jmp	Mat4PersxDump1DB0
Mat4PersxCont3:
	fld1				; [0] 1.0 [1] height * tanf(0.5/fov) / width
	fdivrp	st1,st0			; [0] 1.0/(height*tanf(0.5/fov)/width)
	fstp	dword [DReg+20]

	mov	[DReg+16],ecx
	mov	[DReg+24],ecx
	mov	[DReg+28],ecx

	fld	dword [AReg+12]		; [0] z_near
	fld	dword [AReg+16]		; [0] z_far [1] z_near
	fld	st0			; [0] z_far [1] z_far [2] z_near
	fsub	st0,st2			; [0] z_far-z_near [1] z_far [2] z_near
	fld	st0			; [0] z_far-z_near [1] z_far-z_near [2] z_far [3] z_near
	fld	st2			; [0] z_far [1] z_far-z_near [2] z_far-z_near [3] z_far [4] z_near
	fadd	st4			; [0] z_far+z_near [1] z_far-z_near [2] z_far-z_near [3] z_far [4] z_near
	fldz
	fcomip	st0,st2			; 0.0 == z_far-z_near?
	jne	Mat4PersxCont4
	jmp	Mat4PersxDump5DB0
Mat4PersxCont4:
	fdivrp	st1,st0			; [0] (z_far+z_near)/(z_far-z_near) [1] z_far-z_near [2] z_far [3] z_near
	fstp	dword [DReg+40]		; [0] z_far-z_near [1] z_far [2] z_near

	mov	[DReg+32],ecx
	mov	[DReg+36],ecx
	mov	[DReg+48],ecx
	mov	[DReg+52],ecx
	mov	[DReg+60],ecx

	fxch	st0,st2			; [0] z_near [1] z_far [2] z_far - z_near
	fmul	dword [floatTwo]
	fmulp	st1,st0			; [0] 2.0*z_near*z_far [1] z_far-z_near
	fchs				; [0] -(2.0*z_near*z_far) [1] z_far-z_near
	fdivrp	st1,st0			; [0] -(2.0*z_near*z_far)/(z_far-z_near)
	fstp	dword [DReg+44]

	mov	ecx,[oneVec]
	mov	[DReg+56],ecx

	fwait

	mov	ecx,[AReg+20]		; d3dflag
	cmp	ecx,0
	jz	mat4perspect_done

	fld	dword [floatHalf]	; [0] 0.5
	fld	dword [DReg+40]		; [0] m22 [1] 0.5
	fadd	dword [DReg+56]		; [0] m22+m32 [1] 0.5
	fmul	st0,st1			; [0] 0.5*(m22+m32) [1] 0.5
	fstp	dword [DReg+40]

	fmul	dword [DReg+44]		; 0.5 * (m23 + m33)
	fstp	dword [DReg+44]

	fwait

mat4perspect_done:

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

Mat4PersxDump5DB0:
	ffree	st4
	ffree	st3

Mat4PersxDump3DB0:
	ffree	st2
	ffree	st1

Mat4PersxDump1DB0:
	ffree	st0

	mov	[STACK_SAVE4],Srcp
	mov	[STACK_SAVE5],Dstp

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	Srcp,[STACK_SAVE4]
	mov	Dstp,[STACK_SAVE5]

	ret

;;;
;;; Mat4CubemapMatrixAsm
;;;
;;; Call Stack
;;;
;;; [2] uint32_t face
;;; [1] mat4*    r
;;; [0] ret
;;;
;;; mat4 = m4_cubemapMatrix(unsigned int face)
;;;
;;; extern "C" void Mat4CubemapMatrixAsm(mat4& r,const unsigned int face)
;;; 

_Mat4CubemapMatrixAsm:

	mov	[STACK_SAVE1],CReg
	mov	[STACK_SAVE2],DReg
	mov	[STACK_SAVE3],Srcp
	mov	[STACK_SAVE4],Dstp

	mov	edx,[STACK_PTR2]

	mov	CReg,16
	mov	Dstp,[STACK_PTR1]		; Setup dest ptr
	cld
	
	cmp	edx,0
	jne	cube_try1

	mov	Srcp,face0
	rep	movsd

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]
	
	ret

cube_try1:
	cmp	edx,1
	jne	cube_try2
	
	mov	Srcp,face1
	rep	movsd

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]
	
	ret

cube_try2:
	cmp	edx,2
	jne	cube_try3

	mov	Srcp,face2
	rep	movsd

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]
	
	ret

cube_try3:
	cmp	edx,3
	jne	cube_try4

	mov	Srcp,face3
	rep	movsd

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]

	ret

cube_try4:
	cmp	edx,4
	jne	cube_default

	mov	Srcp,face4
	rep	movsd

	mov	CReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]
	
	ret

cube_default:
	mov	Srcp,face5
	rep	movsd

	mov	DReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]

	ret

;;; 
;;; Mat4CubemapProjectionMatAsm
;;;
;;; Call Stack
;;;
;;; [4] uint32_t d3dflag
;;; [3] float    zFar
;;; [2] float    zNear
;;; [1] mat4*    r
;;; [0] ret
;;;
;;; extern "C" void Mat4CubemapProjectionMatAsm(mat4& r,const float zNear,const float zFar,const uint32_t d3dflag)
;;; 

	
_Mat4CubemapProjectionMatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]

	fld	dword [STACK_PTR2]	; [0] zNear
	fld	dword [STACK_PTR3]	; [0] zFar [1] zNear
	fld	st0			; [0] zFar [1] zFar [2] zNear
	fsub	st0,st2			; [0] zFar-zNear [1] zFar [2] zNear
	fldz
	fcomip	st0,st1			; zFar-zNear == 0.0
	jne	Mat4CubeProjCont
	jmp	Mat4CubeProjDB0
Mat4CubeProjCont:
	fld	st0			; [0] zFar-zNear [1] zFar-zNear [2] zFar [3] zNear
	fld	st2			; [0] zFar [1] zFar-zNear [2] zFar-zNear [3] zFar [4] zNear
	fadd	st0,st4			; [0] zFar+zNear [1] zFar-zNear [2] zFar-zNear [3]zFar [4] zNear
	fdivrp	st1,st0			; [0] (zFar+zNear)/(zFar-zNear) [1] zFar-zNear [2] zFar [3] zNear
	fstp	dword [DReg+40]		; [0] zFar-zNear [1] zFar [2] zNear

	fxch	st1			; [0] zFar [1] zFar-zNear [2] zNear
	fmul	st2			; [0] zFar*zNear [1] zFar-zNear [2] zNear
	fmul	dword [twoVec]		; [0] 2*zFar*zNear [1] zFar-zNear [2] zNear
	fchs				; [0] -2*zFar*zNear [1] zFar-zNear [2] zNear
	fdivrp	st1,st0			; [0] (-2*zFar*zNear)/(zFar-zNear) [1] zNear
	fstp	dword [DReg+44]		; [0] zNear
	ffree	st0
	fincstp

	mov	eax,[zeroVec]
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax
	mov	[DReg+16],eax
	mov	[DReg+24],eax
	mov	[DReg+28],eax
	mov	[DReg+32],eax
	mov	[DReg+36],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+60],eax

	mov	eax,[oneVec]
	mov	[DReg],eax
	mov	[DReg+20],eax
	mov	[DReg+56],eax

	mov	eax,[STACK_PTR4]
	cmp	eax,0
	jz	mat4mirror_notd3d

	fld1
	fadd	dword [DReg+40]		; m22 + m32
	fmul	dword [floatHalf]
	fstp	dword [DReg+40]		; m22 = 0.5 * (m22 + m32)

	fld	dword [DReg+44]		; m23 + m33
	fmul	dword [floatHalf]
	fstp	dword [DReg+44]		; m23 = 0.5 * (m23 + m33)

	jmp	mat4mirror_done

mat4mirror_notd3d:

	mov	eax,[negVec]
	mov	[DReg+20],eax		; m11 = -1.0f

mat4mirror_done:

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret	

Mat4CubeProjDB0:

	mov	[STACK_SAVE3],Srcp
	mov	[STACK_SAVE4],Dstp
	mov	[STACK_SAVE5],CReg

	mov	Srcp,mat4Identity
	mov	Dstp,DReg
	mov	CReg,16
	cld
	rep	movsd

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]
	mov	Srcp,[STACK_SAVE3]
	mov	Dstp,[STACK_SAVE4]
	mov	CReg,[STACK_SAVE5]

	ret

;;;
;;; XXX: THIS REQUIRES REPAIR
;;; 

_Mat4LookAtHorizAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	AReg,[STACK_PTR2]		; *from
	mov	BReg,[STACK_PTR3]		; *at
	mov	edx,[zeroVec]

	mov	[AReg+12],edx			; zero out u/v.w
	mov	[BReg+12],edx

	mov	DReg,[STACK_PTR1]		; *r

	movaps	xmm5,[zeroVec]
	movaps	xmm0,[BReg]			; at
	subps	xmm0,[AReg]			; at - from
	movaps	xmm1,xmm0

	mulps	xmm1,xmm1			; sqr(at-from)
	haddps	xmm1,xmm5			; sum(sqr(at-from))
	haddps	xmm1,xmm5
	sqrtss	xmm1,xmm1			; sqrt(sqr(at-from))
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1			; z = normalize(at-from)

	movaps	xmm1,xmm0
	mulss	xmm1,[negVec]			; -z.x z.y  z.z 0.0
	shufps	xmm1,xmm1,SHUFFLE(2,3,0,3)	;  z.z 0.0 -z.x 0.0

	movaps	xmm2,xmm1
	mulps	xmm2,xmm2
	haddps	xmm2,xmm5
	haddps	xmm2,xmm5
	sqrtss	xmm2,xmm2
	shufps	xmm2,xmm2,0
	divps	xmm1,xmm2			; y = normalize(vec3(z.z,0,-z.x))

	movaps	[DReg],xmm0
	movaps	[DReg+32],xmm1

	movaps	xmm2,xmm0
	movaps	xmm3,xmm1
	shufps	xmm0,xmm0,SHUFFLE(2,0,1,3)	; u_zxy
	shufps	xmm2,xmm2,SHUFFLE(1,2,0,3)	; u_yzx
	shufps	xmm1,xmm1,SHUFFLE(1,2,0,3)	; v_yzx
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,3)	; v_zxy

	mulps	xmm2,xmm3			; u_yzx * v_zxy
	mulps	xmm0,xmm1			; u_zxy * v_yzx
	subps	xmm2,xmm0			; cross(z,x)

	movaps	xmm0,xmm2
	mulps	xmm2,xmm2
	haddps	xmm2,xmm5
	haddps	xmm2,xmm5
	sqrtss	xmm2,xmm2
	shufps	xmm2,xmm2,0
	divps	xmm0,xmm2			; normalize(cross(z,x))

	movaps	[DReg+16],xmm0

	mov	eax,[zeroVec]
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

_Mat4LookAtLH_HorizAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	AReg,[STACK_PTR2]		; *eye
	mov	BReg,[STACK_PTR3]		; *center
	mov	CReg,[STACK_PTR4]		; *up
	mov	DReg,[STACK_PTR1]		; *r

	;; z = Normalize(center - eye)

	movss	xmm6,[zeroVec]

	movaps	xmm0,[BReg]			; center
	subps	xmm0,[AReg]			; center - eye
	movaps	xmm1,xmm0
	mulps	xmm1,xmm0			; sqr(center - eye)
	haddps	xmm1,xmm5
	haddps	xmm1,xmm5
	sqrtss	xmm1,xmm1

	ucomiss	xmm1,xmm6
	je	LHLookAthSkip1
	divps	xmm0,xmm1			; xmm0:	z

LHLookAthSkip1:

	movaps	xmm2,xmm0			; xmm2:	z
	movaps	xmm4,xmm2

	;; x = y (X) z

	movaps	xmm1,[CReg]			; y = up
	movaps	xmm3,xmm1			; y

	shufps	xmm1,xmm1,SHUFFLE(2,3,1,0)	; y.y y.z y.x
	shufps	xmm2,xmm2,SHUFFLE(1,3,2,0)	; z.z z.x z.y
	shufps	xmm3,xmm3,SHUFFLE(1,3,2,0)	; y.z y.x y.y
	shufps	xmm4,xmm4,SHUFFLE(2,1,3,0)	; z.y z.z z.x

	mulps	xmm1,xmm2 
	mulps	xmm3,xmm4
	subps	xmm1,xmm3			; x

	;; y = z (X) x

	movaps	xmm2,xmm0			; xmm2:	z
	movaps	xmm3,xmm1			; xmm1:	x
	movaps	xmm4,xmm0
	movaps	xmm5,xmm3

	shufps	xmm2,xmm2,SHUFFLE(2,1,3,0)	; z.y z.z z.x
	shufps	xmm3,xmm3,SHUFFLE(1,3,2,0)	; x.z x.x x.y
	shufps	xmm4,xmm4,SHUFFLE(1,3,2,0)	; z.z z.x z.y
	shufps	xmm5,xmm5,SHUFFLE(2,1,3,0)	; x.y x.z x.x

	mulps	xmm2,xmm3
	mulps	xmm4,xmm5
	subps	xmm2,xmm4			; y

	;; Normalize(x)

	movaps	xmm3,xmm1
	mulps	xmm3,xmm1
	haddps	xmm3,xmm5
	haddps	xmm3,xmm5
	sqrtss	xmm3,xmm3
	ucomiss	xmm3,xmm6
	je	LHLookAthSkip2
	shufps	xmm3,xmm3,0			; XXX:	Check for 0 here
	divps	xmm1,xmm3			; x

LHLookAthSkip2:

	;; Normalize(y)

	movaps	xmm3,xmm2
	mulps	xmm3,xmm2
	haddps	xmm3,xmm5
	haddps	xmm3,xmm5
	sqrtss	xmm3,xmm3
	ucomiss	xmm3,xmm6
	je	LHLookAthSkip3
	shufps	xmm3,xmm3,0			; XXX:	comiss here
	divps	xmm2,xmm3			; y

LHLookAthSkip3:

	movaps	[DReg],xmm1			; x
	movaps	[DReg+16],xmm2			; y

	;; A little swizzle

	movlps	xmm1,[DReg+16]			; x.x x.y y.x y.y
	movaps	xmm3,xmm1
	shufps	xmm1,xmm0,SHUFFLE(3,1,3,0)	; x.x y.x z.x
	shufps	xmm3,xmm0,SHUFFLE(2,0,2,0)	; x.y y.y z.y
	movhps	xmm2,[DReg+8]			; x.z xxx y.z xxx
	shufps	xmm2,xmm0,SHUFFLE(3,1,1,0)	; x.z y.z z.z

	movaps	[DReg],xmm1			; .x
	movaps	[DReg+16],xmm3			; .y
	movaps	[DReg+32],xmm2			; .z

	movaps	xmm0,[zeroVec]			;   0.0   0.0   0.0
	movaps	xmm4,[BReg]			; eye.x eye.y eye.z
	movaps	xmm5,xmm4
	movaps	xmm6,xmm4

	shufps	xmm4,xmm4,SHUFFLE(3,3,3,3)	; eye.x eye.x eye.x
	shufps	xmm5,xmm5,SHUFFLE(2,2,2,2)	; eye.y eye.y eye.y
	shufps	xmm6,xmm6,SHUFFLE(1,1,1,1)	; eye.z eye.z eye.z

	mulps	xmm1,xmm4			; x.x*eye.x y.x*eye.x z.x*eye.x
	mulps	xmm3,xmm5			; x.y*eye.y y.y*eye.y z.y*eye.y
	mulps	xmm2,xmm6			; x.z*eye.z y.z*eye.z z.z*eye.z

	subps	xmm0,xmm1
	subps	xmm0,xmm3
	subps	xmm0,xmm2

	movaps	[DReg+48],xmm0

	;; Finish the matrix

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

;;; 
;;; Mat3RotationFromMat4Asm
;;;
;;; Call Stack
;;;
;;; [2] mat3* r
;;; [1] mat4* m
;;;
;;; extern "C" void Mat3RotationFromMat4Asm(mat3* r,const mat4* m)
;;;

_Mat3RotationFromMat4Asm:

	mov	[STACK_SAVE1],Srcp
	mov	[STACK_SAVE2],Dstp
	mov	[STACK_SAVE3],CReg

	mov	Dstp,[STACK_PTR1]	; *r
	mov	Srcp,[STACK_PTR2]	; *m
	mov	CReg,12
	cld

	rep	movsd

	mov	ecx, [zeroVec]
	mov	Dstp,[STACK_PTR1]
	mov	[Dstp+12],ecx
	mov	[Dstp+28],ecx
	mov	[Dstp+44],ecx

	mov	Srcp,[STACK_SAVE1]
	mov	Dstp,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]

	ret

;;;
;;; Mat4FromMat3Asm
;;;
;;; Call Stack
;;;
;;; [2] mat3* m
;;; [1] mat4* r
;;;
;;; extern "C" void Mat4FromMat3Asm(mat4* r,const mat3* m)
;;; 

_Mat4FromMat3Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],CReg
	mov	[STACK_SAVE4],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *a

	mov	ecx,12

Mat4FromMat3Loop0:

	mov	ebx,[AReg]
	mov	[DReg],ebx

	add	AReg,4
	add	DReg,4

	dec	ecx
	jnz	Mat4FromMat3Loop0

	mov	DReg,[STACK_PTR1]

	mov	eax,[zeroVec]
	mov	[DReg+12],eax
	mov	[DReg+28],eax
	mov	[DReg+44],eax
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax

	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	CReg,[STACK_SAVE3]
	mov	DReg,[STACK_SAVE4]

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; QuaternionAddAsm(quaternion* r,const quaternion* q,const quaternion* v)
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* q
;;; [1] quaternion* r
;;;
;;; extern "C" void QuaternionAddAsm(quaternion* r,const quaternion* q,const quaternion* v)
;;;

_QuaternionAddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *q
	mov	BReg,[STACK_PTR3]		; *v

	movaps	xmm7,[zeroVec]
	movaps	xmm6,[negateW]
	movaps	xmm0,[AReg]			; q_xyzw
	movaps	xmm1,[BReg]			; v_xyzw

	;; qt = q_xyz*v.w & -(q.z*v.z)
	;;

	movaps	xmm2,xmm1			; v_xyzw
	movaps	xmm3,xmm0			; q_xyzw
	shufps	xmm2,xmm2,SHUFFLE(3,3,3,2)	; v.w v.w v.w v.z
	shufps	xmm3,xmm3,SHUFFLE(0,1,2,2)	; q.x q.y q.z q.z
	mulps	xmm2,xmm3
	mulps	xmm2,xmm6			; qt = q_xyz*v.w & q.z*v.z

	;; vt = v_xyz*q.w
	;;

	movaps	xmm3,xmm0			; q_xyzw
	unpckhps xmm3,xmm7			; q.z 0.0 q.w 0.0
	shufps	xmm3,xmm3,SHUFFLE(2,2,2,1)	; q.w q.w q.w 0.0
	mulps	xmm3,xmm1			; vt = v_xyz*q.w

	addps	xmm2,xmm3			; qt+vt & q.z*v.z

	;; Calculate first parameter
	;;

	movaps	xmm3,xmm0			; q_xyzw
	movaps	xmm4,xmm1			; v_xyzw
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,0)	; q.z q.x q.y q.x
	shufps	xmm4,xmm4,SHUFFLE(1,2,0,0)	; v.y v.z v.x v.x
	mulps	xmm3,xmm4
	mulps	xmm3,xmm6

	addps	xmm2,xmm3

	;; Calculate second parameter
	;;

	movaps	xmm3,xmm0			; q_xyzw
	shufps	xmm3,xmm3,SHUFFLE(1,2,0,1)	; q.y q.z q.x q.y
	shufps	xmm1,xmm1,SHUFFLE(2,0,1,1)	; v.z v.x v.y v.y
	mulps	xmm3,xmm1

	subps	xmm2,xmm3

	;; Calulate the final paramerer
	;;

	unpckhps xmm0,xmm7			; q.z q.w 0.0 0.0
	shufps	xmm0,xmm0,SHUFFLE(1,1,1,2)	; 0.0 0.0 0.0 q.w
	mulps	xmm0,xmm0

	addps	xmm0,xmm2			; Final calculation

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; QuaternionMultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* u
;;; [1] quaternion* r
;;;
;;; extern "C" void QuaternionMultiplyAsm(quaternion*r,const quaternion* u,const quaternion* v)
;;;

_QuaternionMultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *q
	mov	BReg,[STACK_PTR3]		; *v

	movaps	xmm7,[negateW]
	movaps	xmm0,[AReg]			; q_xyzw
	movaps	xmm1,[BReg]			; v_xyzw

	;; Calculate the second parameter
	;;

	movaps	xmm2,xmm0			; q_xyzw
	movaps	xmm3,xmm1			; v_xyzw
	shufps	xmm2,xmm2,SHUFFLE(0,1,2,0)	; q_xyzx
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,0)	; v_wwwx
	mulps	xmm2,xmm3
	mulps	xmm2,xmm7

	;; Calculate the third parameter
	;;

	movaps	xmm3,xmm0			; q_xyzw
	movaps	xmm4,xmm1			; v_xyzw
	shufps	xmm3,xmm3,SHUFFLE(1,2,0,1)	; q_yzxy
	shufps	xmm4,xmm4,SHUFFLE(2,0,1,1)	; v_zxyy
	mulps	xmm3,xmm4
	mulps	xmm3,xmm7

	addps	xmm2,xmm3

	;; Calculate the forth parameter
	;;

	movaps	xmm3,xmm0			; q_xyzw
	movaps	xmm4,xmm1			; v_xyzw
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,2)	; q_zxyz
	shufps	xmm4,xmm4,SHUFFLE(1,2,0,2)	; v_yzxz
	mulps	xmm3,xmm4

	;; Calculate the first parameter
	;;

	shufps	xmm0,xmm0,SHUFFLE(3,3,3,3)	; q_wwww
	mulps	xmm0,xmm1			; v_xyzw * q_wwww
	addps	xmm0,xmm2
	subps	xmm0,xmm3			; final calculation

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; QuaternionInverseAsm
;;;
;;; Call Stack
;;; 
;;; [2] quaternion* q
;;; [1] quaternion* r
;;;
;;; extern "C" void QuaternionInverseAsm(quaternion* r,const quaternion* q)
;;;

_QuaternionInverseAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movaps	xmm0,[AReg]		; q
	mulps	xmm0,[quatInverse]
	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; QuaternionToMat3Asm
;;;
;;; Call Stack
;;;
;;; [2] quaternion* q
;;; [1] mat3*       m
;;;
;;; extern "C" void QuaternionToMat3Asm(mat3* r,const quaternion* q)
;;;

_QuaternionToMat3Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movaps	xmm0,[AReg]		; q

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	movaps	xmm4,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,2)	; y x x 0
	shufps	xmm2,xmm2,SHUFFLE(1,1,2,2)	; y y z 0
	shufps	xmm3,xmm3,SHUFFLE(2,2,1,2)	; z z y 0
	shufps	xmm4,xmm4,SHUFFLE(2,3,3,3)	; z w w 0

	mulps	xmm1,xmm2
	mulps	xmm3,xmm4

	mulps	xmm3,[qFlip2]			; (1,-1,1,0)
	addps	xmm1,xmm3
	mulps	xmm1,[twoVec]			; (2,2,2,2)
	mulps	xmm1,[qFlip1]			; (-1,1,1,0)
	addps	xmm1,[qPos1]			; (1,0,0,0)

	movaps	[DReg],xmm1

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	movaps	xmm4,xmm0

	shufps	xmm1,xmm1,SHUFFLE(0,0,1,1)	; x x y 0
	shufps	xmm2,xmm2,SHUFFLE(1,0,2,1)	; y x z 0
	shufps	xmm3,xmm3,SHUFFLE(2,2,0,0)	; z z x 0
	shufps	xmm4,xmm4,SHUFFLE(3,2,3,3)	; w z w 0

	mulps	xmm1,xmm2
	mulps	xmm3,xmm4
	mulps	xmm3,[qFlip3]			; (1,1,-1,0)
	addps	xmm1,xmm3
	mulps	xmm1,[twoVec]
	mulps	xmm1,[qFlip2]			; (1,-1,1,0)
	addps	xmm1,[qPos2]			; (0,1,0,0)

	movaps	[DReg+16],xmm1

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,1,0,0)	; x y x 0
	shufps	xmm1,xmm1,SHUFFLE(2,2,0,0)	; z z x 0
	shufps	xmm2,xmm2,SHUFFLE(1,0,1,1)	; y x y 0
	shufps	xmm3,xmm3,SHUFFLE(3,3,1,0)	; w w y 0

	mulps	xmm0,xmm1
	mulps	xmm2,xmm3
	mulps	xmm2,[qFlip1]			; (-1,1,1,0)
	addps	xmm0,xmm2
	mulps	xmm0,[twoVec]
	mulps	xmm0,[qFlip3]			; (1,1,-1,0)
	addps	xmm0,[qPos3]			; (0,0,1,0)

	movaps	[DReg+32],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; uQuaternionAddAsm(quaternion* r,const quaternion* q,const quaternion* v)
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* q
;;; [1] quaternion* r
;;;
;;; extern "C" void uQuaternionAddAsm(quaternion* r,const quaternion* q,const quaternion* v)
;;;

_uQuaternionAddAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *q
	mov	BReg,[STACK_PTR3]		; *v

	movaps	xmm7,[zeroVec]
	movaps	xmm6,[negateW]
	movups	xmm0,[AReg]			; q_xyzw
	movups	xmm1,[BReg]			; v_xyzw

	;; qt = q_xyz*v.w & -(q.z*v.z)
	;;

	movaps	xmm2,xmm1			; v_xyzw
	movaps	xmm3,xmm0			; q_xyzw
	shufps	xmm2,xmm2,SHUFFLE(3,3,3,2)	; v.w v.w v.w v.z
	shufps	xmm3,xmm3,SHUFFLE(0,1,2,2)	; q.x q.y q.z q.z
	mulps	xmm2,xmm3
	mulps	xmm2,xmm6			; qt = q_xyz*v.w & q.z*v.z

	;; vt = v_xyz*q.w
	;;

	movaps	xmm3,xmm0			; q_xyzw
	unpckhps xmm3,xmm7			; q.z q.w 0.0 0.0
	shufps	xmm3,xmm3,SHUFFLE(2,2,2,1)	; q.w q.w q.w 0.0
	mulps	xmm3,xmm1			; vt = v_xyz*q.w

	addps	xmm2,xmm3			; qt+vt & q.z*v.z

	;; Calculate first parameter
	;;

	movaps	xmm3,xmm0			; q_xyzw
	movaps	xmm4,xmm1			; v_xyzw
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,0)	; q.z q.x q.y q.x
	shufps	xmm4,xmm4,SHUFFLE(1,2,0,0)	; v.y v.z v.x v.x
	mulps	xmm3,xmm4
	mulps	xmm3,xmm6

	addps	xmm2,xmm3

	;; Calculate second parameter
	;;

	movaps	xmm3,xmm0			; q_xyzw
	shufps	xmm3,xmm3,SHUFFLE(1,2,0,1)	; q.y q.z q.x q.y
	shufps	xmm1,xmm1,SHUFFLE(2,0,1,1)	; v.z v.x v.y v.y
	mulps	xmm3,xmm1

	subps	xmm2,xmm3

	;; Calulate the final paramerer
	;;

	unpckhps xmm0,xmm7			; q.z q.w 0.0 0.0
	shufps	xmm0,xmm0,SHUFFLE(1,1,1,2)	; 0.0 0.0 0.0 q.w
	mulps	xmm0,xmm0

	addps	xmm0,xmm2			; Final calculation

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; uQuaternionMultiplyAsm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* u
;;; [1] quaternion* r
;;;
;;; extern "C" void uQuaternionMultiplyAsm(quaternion*r,const quaternion* u,const quaternion* v)
;;;

_uQuaternionMultiplyAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]		; *r
	mov	AReg,[STACK_PTR2]		; *q
	mov	BReg,[STACK_PTR3]		; *v

	movaps	xmm7,[negateW]
	movups	xmm0,[AReg]			; q_xyzw
	movups	xmm1,[BReg]			; v_xyzw

	;; Calculate the second parameter
	;;

	movaps	xmm2,xmm0			; q_xyzw
	movaps	xmm3,xmm1			; v_xyzw
	shufps	xmm2,xmm2,SHUFFLE(0,1,2,0)	; q_xyzx
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,0)	; v_wwwx
	mulps	xmm2,xmm3
	mulps	xmm2,xmm7

	;; Calculate the third parameter
	;;

	movaps	xmm3,xmm0			; q_xyzw
	movaps	xmm4,xmm1			; v_xyzw
	shufps	xmm3,xmm3,SHUFFLE(1,2,0,1)	; q_yzxy
	shufps	xmm4,xmm4,SHUFFLE(2,0,1,1)	; v_zxyy
	mulps	xmm3,xmm4
	mulps	xmm3,xmm7

	addps	xmm2,xmm3

	;; Calculate the forth parameter
	;;

	movaps	xmm3,xmm0			; q_xyzw
	movaps	xmm4,xmm1			; v_xyzw
	shufps	xmm3,xmm3,SHUFFLE(2,0,1,2)	; q_zxyz
	shufps	xmm4,xmm4,SHUFFLE(1,2,0,2)	; v_yzxz
	mulps	xmm3,xmm4

	;; Calculate the first parameter
	;;

	shufps	xmm0,xmm0,SHUFFLE(3,3,3,3)	; q_wwww
	mulps	xmm0,xmm1			; v_xyzw * q_wwww
	addps	xmm0,xmm2
	subps	xmm0,xmm3			; final calculation

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; uQuaternionInverseAsm
;;;
;;; Call Stack
;;; 
;;; [2] quaternion* q
;;; [1] quaternion* r
;;;
;;; extern "C" void uQuaternionInverseAsm(quaternion* r,const quaternion* q)
;;;

_uQuaternionInverseAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movups	xmm0,[AReg]		; q
	mulps	xmm0,[quatInverse]
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

;;;
;;; uQuaternionToMat3Asm
;;;
;;; Call Stack
;;;
;;; [2] quaternion* q
;;; [1] mat3*       m
;;;
;;; extern "C" void uQuaternionToMat3Asm(mat3* r,const quaternion* q)
;;;

_uQuaternionToMat3Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movups	xmm0,[AReg]		; q

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	movaps	xmm4,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,2)	; y x x 0
	shufps	xmm2,xmm2,SHUFFLE(1,1,2,2)	; y y z 0
	shufps	xmm3,xmm3,SHUFFLE(2,2,1,2)	; z z y 0
	shufps	xmm4,xmm4,SHUFFLE(2,3,3,3)	; z w w 0

	mulps	xmm1,xmm2
	mulps	xmm3,xmm4

	mulps	xmm3,[qFlip2]			; (1,-1,1,0)
	addps	xmm1,xmm3
	mulps	xmm1,[twoVec]			; (2,2,2,2)
	mulps	xmm1,[qFlip1]			; (-1,1,1,0)
	addps	xmm1,[qPos1]			; (1,0,0,0)

	movups	[DReg],xmm1

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	movaps	xmm4,xmm0

	shufps	xmm1,xmm1,SHUFFLE(0,0,1,1)	; x x y 0
	shufps	xmm2,xmm2,SHUFFLE(1,0,2,1)	; y x z 0
	shufps	xmm3,xmm3,SHUFFLE(2,2,0,0)	; z z x 0
	shufps	xmm4,xmm4,SHUFFLE(3,2,3,3)	; w z w 0

	mulps	xmm1,xmm2
	mulps	xmm3,xmm4
	mulps	xmm3,[qFlip3]			; (1,1,-1,0)
	addps	xmm1,xmm3
	mulps	xmm1,[twoVec]
	mulps	xmm1,[qFlip2]			; (1,-1,1,0)
	addps	xmm1,[qPos2]			; (0,1,0,0)

	movups	[DReg+16],xmm1

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,1,0,0)	; x y x 0
	shufps	xmm1,xmm1,SHUFFLE(2,2,0,0)	; z z x 0
	shufps	xmm2,xmm2,SHUFFLE(1,0,1,1)	; y x y 0
	shufps	xmm3,xmm3,SHUFFLE(3,3,1,0)	; w w y 0

	mulps	xmm0,xmm1
	mulps	xmm2,xmm3
	mulps	xmm2,[qFlip1]			; (-1,1,1,0)
	addps	xmm0,xmm2
	mulps	xmm0,[twoVec]
	mulps	xmm0,[qFlip3]			; (1,1,-1,0)
	addps	xmm0,[qPos3]			; (0,0,1,0)

	movups	[DReg+32],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; QuaternionNormalizeAsm
;;;
;;; Call Stack
;;;
;;; [2] quaternion* q
;;; [1] quaternion* r
;;;
;;; extern "C" void QuaternionNormalizeAsm(quaternion* r,const quaternion* q)
;;;

_QuaternionNormalizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movaps	xmm2,[zeroVec]
	movaps	xmm0,[AReg]		; q
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; q*q

	haddps	xmm1,xmm2
	haddps	xmm1,xmm2

	ucomiss	xmm1,[zeroVec]
	je	QuatNormDB0

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; q/length

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

QuatNormDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	ret

;;;
;;; QuaternionDotAsm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* q
;;; [1] float*      r
;;;
;;; extern "C" void QuaternionDotAsm(float* r,const quaterion* q,const quaternion* v)
;;;

_QuaternionDotAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q
	mov	BReg,[STACK_PTR3]	; *v

	movaps	xmm2,[zeroVec]
	movaps	xmm0,[AReg]
	mulps	xmm0,[BReg]		; q*v

	haddps	xmm0,xmm2
	haddps	xmm0,xmm2

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; uQuaternionNormalizeAsm
;;;
;;; Call Stack
;;;
;;; [2] quaternion* q
;;; [1] quaternion* r
;;;
;;; extern "C" void uQuaternionNormalizeAsm(quaternion* r,const quaternion* q)
;;;

_uQuaternionNormalizeAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movaps	xmm2,[zeroVec]
	movups	xmm0,[AReg]		; q
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; q*q

	haddps	xmm1,xmm2
	haddps	xmm1,xmm2

	ucomiss	xmm1,[zeroVec]
	je	uQuatNormDB0

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; q/length
	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

uQuatNormDB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	ret

;;;
;;; uQuaternionDotFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* q
;;; [1] float*      r
;;;
;;; extern "C" void uQuaternionDotAsm(float* r,const quaterion* q,const quaternion* v)
;;;

_uQuaternionDotAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q
	mov	BReg,[STACK_PTR3]	; *v

	movaps	xmm2,[zeroVec]
	movups	xmm0,[AReg]		; q
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; q*v

	haddps	xmm0,xmm2
	haddps	xmm0,xmm2

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; QuaternionNormalizeFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] quaternion* q
;;; [1] quaternion* r
;;;
;;; extern "C" void QuaternionNormalizeFlatAsm(quaternion* r,const quaternion* q)
;;;

_QuaternionNormalizeFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movaps	xmm0,[AReg]		; q
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; q*q

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	shufps	xmm2,xmm2,SHUFFLE(1,1,1,1)
	shufps	xmm3,xmm3,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm2
	addss	xmm1,xmm3		; length

	ucomiss	xmm1,[zeroVec]
	je	QuatNormDB0F

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; q/length

	movaps	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

QuatNormDB0F:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	ret

;;;
;;; QuaternionDotFPU_Asm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* u
;;; [1] float*      r
;;;
;;; extern "C" void QuaternionDotFPU_Asm(float* r,const quaternion* q,const quaternion* v)
;;;

_QuaternionDotFPU_Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q
	mov	BReg,[STACK_PTR3]	; *v

	fld	dword [AReg]		; q.x
	fld	dword [BReg]		; v.x
	fmulp	st1,st0

	fld	dword [AReg+4]
	fld	dword [BReg+4]
	fmulp	st1,st0
	faddp	st1,st0

	fld	dword [AReg+8]
	fld	dword [BReg+8]
	fmulp	st1,st0
	faddp	st1,st0

	fld	dword [AReg+12]
	fld	dword [BReg+12]
	fmulp	st1,st0
	faddp	st1,st0

	fstp	dword [DReg]

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; uQuaternionNormalizeFlatAsm
;;;
;;; Call Stack
;;;
;;; [2] quaternion* q
;;; [1] quaternion* r
;;;
;;; extern "C" void uQuaternionNormalizeFlatAsm(quaternion* r,const quaternion* q)
;;;

_uQuaternionNormalizeFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movups	xmm0,[AReg]		; q
	movaps	xmm1,xmm0
	mulps	xmm1,xmm1		; q*q

	movaps	xmm2,xmm1
	movaps	xmm3,xmm1
	shufps	xmm2,xmm2,SHUFFLE(1,1,1,1)
	shufps	xmm3,xmm3,SHUFFLE(2,2,2,2)

	addss	xmm1,xmm2
	addss	xmm1,xmm3		; length

	ucomiss	xmm1,[zeroVec]
	je	uQuatNormDB0F

	sqrtss	xmm1,xmm1
	shufps	xmm1,xmm1,0
	divps	xmm0,xmm1		; q/length

	movups	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

uQuatNormDB0F:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	ret

;;;
;;; uQuaternionDotFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* q
;;; [1] float*      r
;;;
;;; extern "C" void uQuaternionDotFlatAsm(float* r,const quaterion* q,const quaternion* v)
;;;

_uQuaternionDotFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q
	mov	BReg,[STACK_PTR3]	; *v

	movups	xmm0,[AReg]		; q
	movups	xmm1,[BReg]		; v
	mulps	xmm0,xmm1		; q*v

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

%if (__BUILD_ALL == 1)

;;;
;;; QuaternionDotFlatAsm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* v
;;; [2] quaternion* q
;;; [1] float*      r
;;;
;;; extern "C" void QuaternionDotFlatAsm(float* r,const quaterion* q,const quaternion* v)
;;;

_QuaternionDotFlatAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q
	mov	BReg,[STACK_PTR3]	; *v

	movaps	xmm0,[AReg]
	mulps	xmm0,[BReg]		; q*v

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,1,1,1)
	shufps	xmm2,xmm2,SHUFFLE(2,2,2,2)
	shufps	xmm3,xmm3,SHUFFLE(3,3,3,3)

	addss	xmm0,xmm1
	addss	xmm0,xmm2
	addss	xmm0,xmm3

	movss	[DReg],xmm0

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

%endif

;;;
;;; QuaternionFromAxisAsm
;;;
;;; Call Stack
;;;
;;; [3] float angle
;;; [2] vec3* v
;;; [1] quaternion* r
;;;
;;; extern "C" void QuaternionFromAxisAsm(quaternion* r,const vec3* v,const float angle)
;;;

_QuaternionFromAxisAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]
	mov	AReg,[STACK_PTR2]

	;; Calculate the length of the vector
	;; 

	fld	dword [AReg]
	fmul	st0,st0
	fld	dword [AReg+4]
	fmul	st0,st0
	faddp	st1,st0
	fld	dword [AReg+8]
	fmul	st0,st0
	faddp	st1,st0			; [0] length

	fldz
	fcomip	st0,st1
	jne	QuatFromAxisCont

	ffree	st0
	fincstp
	jmp	QuatFromAxisDB0

QuatFromAxisCont:

	fsqrt
	fld	dword [STACK_PTR3]	; [0] angle [1] length
	fld	dword [floatTwo]	; [0] 2.0 [1] angle [2] length
	fdivp	st1,st0			; [0] angle/2 [1] length
	fsincos				; [0] cos [1] sin [2] length
	fstp	dword [DReg+12]		; [0] sin(angle/2) [1] length
	fdivrp	st1,st0			; [0] scale = sin(angle/2) / length
	fld	dword [AReg+4]		; [0] y [1] scale
	fmul	st0,st1			; [0] scale*y [1] scale
	fld	dword [AReg]		; [0] x [1] scale*y [2] scale
	fmul	st0,st2			; [0] scale*x [1] scale*y [2] scale
	fld	dword [AReg+8]		; [0] z [1] scale*x [2] scale*y [3] scale
	fmulp	st3,st0			; [0] scale*x [1] scale*y [2] scale*z

	fstp	dword [DReg]
	fstp	dword [DReg+4]
	fstp	dword [DReg+8]

	fnclex
	fwait

	ret
	
QuatFromAxisDB0:

	fnclex
	fwait

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	ret

%if (__BUILD_ADVANCED_ALIGNED_LIB == 1 || __BUILD_ALIGNED_LIB == 1 || __BUILD_ALL == 1)
	
;;;
;;; QuaternionToMat4Asm
;;;
;;; Call Stack
;;;
;;; [2] quaternion* q
;;; [1] mat4*       m
;;;
;;; extern "C" void QuaternionToMat4Asm(mat4* m,const quaternion* q)
;;;

_QuaternionToMat4Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movaps	xmm0,[AReg]		; q

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	movaps	xmm4,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,2)	; y x x 0
	shufps	xmm2,xmm2,SHUFFLE(1,1,2,2)	; y y z 0
	shufps	xmm3,xmm3,SHUFFLE(2,2,1,2)	; z z y 0
	shufps	xmm4,xmm4,SHUFFLE(2,3,3,3)	; z w w 0

	mulps	xmm1,xmm2
	mulps	xmm3,xmm4

	mulps	xmm3,[qFlip2]			; (1,-1,1,0)
	addps	xmm1,xmm3
	mulps	xmm1,[twoVec]			; (2,2,2,2)
	mulps	xmm1,[qFlip1]			; (-1,1,1,0)
	addps	xmm1,[qPos1]			; (1,0,0,0)

	movaps	[DReg],xmm1

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	movaps	xmm4,xmm0

	shufps	xmm1,xmm1,SHUFFLE(0,0,1,1)	; x x y 0
	shufps	xmm2,xmm2,SHUFFLE(1,0,2,1)	; y x z 0
	shufps	xmm3,xmm3,SHUFFLE(2,2,0,0)	; z z x 0
	shufps	xmm4,xmm4,SHUFFLE(3,2,3,3)	; w z w 0

	mulps	xmm1,xmm2
	mulps	xmm3,xmm4
	mulps	xmm3,[qFlip3]			; (1,1,-1,0)
	addps	xmm1,xmm3
	mulps	xmm1,[twoVec]
	mulps	xmm1,[qFlip2]			; (1,-1,1,0)
	addps	xmm1,[qPos2]			; (0,1,0,0)

	movaps	[DReg+16],xmm1

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,1,0,0)	; x y x 0
	shufps	xmm1,xmm1,SHUFFLE(2,2,0,0)	; z z x 0
	shufps	xmm2,xmm2,SHUFFLE(1,0,1,1)	; y x y 0
	shufps	xmm3,xmm3,SHUFFLE(3,3,1,0)	; w w y 0

	mulps	xmm0,xmm1
	mulps	xmm2,xmm3
	mulps	xmm2,[qFlip1]			; (-1,1,1,0)
	addps	xmm0,xmm2
	mulps	xmm0,[twoVec]
	mulps	xmm0,[qFlip3]			; (1,1,-1,0)
	addps	xmm0,[qPos3]			; (0,0,1,0)

	movaps	[DReg+32],xmm0

	mov	eax,[zeroVec]
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

%if (__BUILD_ADVANCED_UNALIGNED_LIB == 1 || __BUILD_UNALIGNED_LIB == 1 || __BUILD_ALL == 1)

;;;
;;; uQuaternionToMat4Asm
;;;
;;; Call Stack
;;;
;;; [2] quaternion* q
;;; [1] mat4*       m
;;;
;;; extern "C" void uQuaternionToMat4Asm(mat4* m,const quaternion* q)
;;;

_uQuaternionToMat4Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q

	movups	xmm0,[AReg]		; q

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	movaps	xmm4,xmm0

	shufps	xmm1,xmm1,SHUFFLE(1,0,0,2)	; y x x 0
	shufps	xmm2,xmm2,SHUFFLE(1,1,2,2)	; y y z 0
	shufps	xmm3,xmm3,SHUFFLE(2,2,1,2)	; z z y 0
	shufps	xmm4,xmm4,SHUFFLE(2,3,3,3)	; z w w 0

	mulps	xmm1,xmm2
	mulps	xmm3,xmm4

	mulps	xmm3,[qFlip2]			; (1,-1,1,0)
	addps	xmm1,xmm3
	mulps	xmm1,[twoVec]			; (2,2,2,2)
	mulps	xmm1,[qFlip1]			; (-1,1,1,0)
	addps	xmm1,[qPos1]			; (1,0,0,0)

	movups	[DReg],xmm1

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0
	movaps	xmm4,xmm0

	shufps	xmm1,xmm1,SHUFFLE(0,0,1,1)	; x x y 0
	shufps	xmm2,xmm2,SHUFFLE(1,0,2,1)	; y x z 0
	shufps	xmm3,xmm3,SHUFFLE(2,2,0,0)	; z z x 0
	shufps	xmm4,xmm4,SHUFFLE(3,2,3,3)	; w z w 0

	mulps	xmm1,xmm2
	mulps	xmm3,xmm4
	mulps	xmm3,[qFlip3]			; (1,1,-1,0)
	addps	xmm1,xmm3
	mulps	xmm1,[twoVec]
	mulps	xmm1,[qFlip2]			; (1,-1,1,0)
	addps	xmm1,[qPos2]			; (0,1,0,0)

	movups	[DReg+16],xmm1

	movaps	xmm1,xmm0
	movaps	xmm2,xmm0
	movaps	xmm3,xmm0

	shufps	xmm0,xmm0,SHUFFLE(0,1,0,0)	; x y x 0
	shufps	xmm1,xmm1,SHUFFLE(2,2,0,0)	; z z x 0
	shufps	xmm2,xmm2,SHUFFLE(1,0,1,1)	; y x y 0
	shufps	xmm3,xmm3,SHUFFLE(3,3,1,0)	; w w y 0

	mulps	xmm0,xmm1
	mulps	xmm2,xmm3
	mulps	xmm2,[qFlip1]			; (-1,1,1,0)
	addps	xmm0,xmm2
	mulps	xmm0,[twoVec]
	mulps	xmm0,[qFlip3]			; (1,1,-1,0)
	addps	xmm0,[qPos3]			; (0,0,1,0)

	movups	[DReg+32],xmm0

	mov	eax,[zeroVec]
	mov	[DReg+48],eax
	mov	[DReg+52],eax
	mov	[DReg+56],eax
	mov	eax,[oneVec]
	mov	[DReg+60],eax

	mov	AReg,[STACK_SAVE1]
	mov	DReg,[STACK_SAVE2]

	ret

%endif

;;;
;;; QuaternionFromMat3Asm
;;;
;;; Call Stack
;;;
;;; [2] const mat3* m
;;; [1] quaternion* q
;;;
;;; extern "C" void QuaternionFromMat3Asm(quaternion* r,const mat3* m);
;;;

_QuaternionFromMat3Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	fld	dword [AReg]		; [0] m00
	fld	dword [AReg+20]		; [1] m11
	fld	dword [AReg+40]		; [2] m22
	faddp	st1,st0
	faddp	st1,st0			; [0] trace=m00+m11+m22

	fldz
	fcomip	st0,st1

	jbe	QuatFromMat3GT0		; 0.0 <= trace
	jmp	QuatFromMat3Le0

QuatFromMat3GT0:

	fld1				; [0] 1.0 [1] trace
	faddp	st1,st0			; [0] 1+trace
	fsqrt				; [0] scale=sqrt(1+trace)
	fld	dword [floatHalf]	; [0] 0.5 [1] scale
	fld	st0			; [0] 0.5 [1] 0.5 [2] scale
	fmul	st0,st2			; [0] q.w=0.5*scale [1] 0.5 [2] scale
	fstp	dword [DReg+12]		; [0] 0.5 [1] scale

	fldz
	fcomip	st0,st1			; 0.0 == scale ?
	jnz	QuatFromMat3GT0Cont

	jmp	QuatFromMat3DB0

QuatFromMat3GT0Cont:

	fdivrp	st1,st0			; [0] scale = 0.5 / scale
	fld	dword [AReg+36]		; [0] m21 [1] scale
	fld	dword [AReg+24]		; [0] m12 [1] m21 [2] scale
	fsubp	st1,st0			; [0] m21-m12 [1] scale
	fmul	st0,st1			; [0] q.x=scale*(m21-m12) [1] scale
	fstp	dword [DReg]		; [0] scale

	fld	dword [AReg+8]		; [0] m02 [1] scale
	fld	dword [AReg+32]		; [0] m20 [1] m02 [2] scale
	fsubp	st1,st0			; [0] m02-m20 [1] scale
	fmul	st0,st1			; [0] q.y=scale*(m02-m20) [1] scale
	fstp	dword [DReg+4]		; [0] scale

	fld	dword [AReg+16]		; [0] m10 [1] scale
	fld	dword [AReg+4]		; [0] m01 [1] m10 [2] scale
	fsubp	st1,st0			; [0] m10-m01 [1] scale
	fmulp	st1,st0			; [0] q.z=scale*(m10-m01)
	fstp	dword [DReg+8]

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatFromMat3Le0:

	ffree	st0			; clear trace
	fincstp

	;; i = 0 (sort to greatest of m00,m11 or m22)

	;; if ( m11 > m00 ) i=1

	mov	CReg,0			; if ( m11 > m00)
	fld	dword [AReg]		; [0] m00
	fld	dword [AReg+20]		; [0] m11 [1] m00
	fcomip	st0,st1			; [0] m00
	jbe	QuatFromMat3ChkMth1

	ffree	st0
	fincstp

	fld	dword [AReg+20]		; [0] m11
	mov	CReg,1

QuatFromMat3ChkMth1:

	;; if ( m22 > m?? ) i = 2

	fld	dword [AReg+40]		; [0] m22 [1] > of m00/m11
	fcomip	st0,st1			; [0] leftover
	
	jbe	QuatFromMat3SelectMethod
	mov	CReg,2

QuatFromMat3SelectMethod:

	ffree	st0
	fincstp

	cmp	CReg,2
	jne	QuatFromMat3ChkMethod1
	jmp	QuatFromMat3Method2

QuatFromMat3ChkMethod1:

	cmp	CReg,1
	jne	QuatFromMat3Method0
	jmp	QuatFromMat3Method1

QuatFromMat3Method0:

	fld	dword [AReg]		; [0] m00
	fld	dword [AReg+20]		; [0] m11 [1] m00
	fsubp	st1,st0			; [0] m00-m11
	fld	dword [AReg+40]		; [0] m22 [1] m00-m11
	fsubp	st1,st0			; [0] m00-m11-m22
	fld1
	faddp	st1,st0			; [0] m00-m11-m22+1
	fsqrt				; [0] scale=sqrt(m00-m11-m22+1)
	fldz
	fcomip	st0,st1
	jnz	QuatFromMat3Method1Cont
	jmp QuatFromMat3DB0

QuatFromMat3Method1Cont:

	fld	dword [floatHalf]	; [0] 0.5 [1] scale
	fld	st0			; [0] 0.5 [1] 0.5 [2] scale
	fmul	st0,st2			; [0] q.x=0.5*scale [1] 0.5 [2] scale
	fstp	dword [DReg]		; [0] 0.5 [1] scale

	fdivrp	st1,st0			; [0] scale = 0.5 / scale
	fld	dword [AReg+16]		; [0] m10 [1] scale
	fld	dword [AReg+4]		; [0] m01 [1] m10 [2] scale
	faddp	st1,st0			; [0] m10+m01 [1] scale
	fmul	st0,st1			; [0] q.y=scale*(m10+m01) [1] scale
	fstp	dword [DReg+4]		; [0] scale

	fld	dword [AReg+32]		; [0] m20 [1] scale
	fld	dword [AReg+8]		; [0] m02 [1] m20 [2] scale
	faddp	st1,st0			; [0] m20+m02 [1] scale
	fmul	st0,st1			; [0] q.z=scale*(m20+m02) [1] scale
	fstp	dword [DReg+8]		; [0] scale

	fld	dword [AReg+36]		; [0] m21 [1] scale
	fld	dword [AReg+24]		; [0] m12 [1] m21 [2] scale
	fsubp	st1,st0			; [0] m21-m12 [1] scale
	fmulp	st1,st0			; [0] q.w=scale*(m21-m12)
	fstp	dword [DReg+12]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatFromMat3Method1:

	fld	dword [AReg+20]		; [0] m11
	fld	dword [AReg]		; [0] m00 [1] m11
	fsubp	st1,st0			; [0] m11-m00
	fld	dword [AReg+40]		; [0] m22 [1] m11-m00
	fsubp	st1,st0			; [0] m11-m00-m22
	fld1
	faddp	st1,st0			; [0] m11-m00-m22+1
	fsqrt				; [0] scale=sqrt(m11-m00-m22+1)
	fldz
	fcomip	st0,st1
	jnz	QuatFromMat3Mth1Cont
	jmp	QuatFromMat3DB0

QuatFromMat3Mth1Cont:

	fld	dword [floatHalf]	; [0] 0.5 [1] scale
	fld	st0			; [0] 0.5 [1] 0.5 [2] scale
	fmul	st0,st2			; [0] q.y=0.5*scale [1] 0.5 [2] scale
	fstp	dword [DReg+4]		; [0] 0.5 [1] scale

	fdivrp	st1,st0			; [0] scale=0.5/scale
	fld	dword [AReg+4]		; [0] m01 [1] scale
	fld	dword [AReg+16]		; [0] m10 [1] m01 [2] scale
	faddp	st1,st0			; [0] m01+m10 [1] scale
	fmul	st0,st1			; [0] q.x=scale*(m01+m10) [1] scale
	fstp	dword [DReg]		; [0] scale

	fld	dword [AReg+36]		; [0] m21 [1] scale
	fld	dword [AReg+24]		; [0] m12 [1] m21 [2] scale
	faddp	st1,st0			; [0] m21+m12 [1] scale
	fmul	st0,st1			; [0] q.z=scale*(m21+m12) [1] scale
	fstp	dword [DReg+8]		; [0] scale

	fld	dword [AReg+8]		; [0] m02 [1] scale
	fld	dword [AReg+32]		; [0] m20 [1] m02 [2] scale
	fsubp	st1,st0			; [0] m02-m20 [1] scale
	fmulp	st1,st0			; [0] q.w=scale*(m02-m20)
	fstp	dword [DReg+12]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatFromMat3Method2:

	fld	dword [AReg+40]		; [0] m22
	fld	dword [AReg]		; [1] m00
	fsubp	st1,st0			; [0] m22-m00
	fld	dword [AReg+20]		; [0] m11 [1] m22-m00
	fsubp	st1,st0			; [0] m22-m00-m11
	fld1
	faddp	st1,st0			; [0] m22-m00-m11+1
	fsqrt				; [0] scale=sqrt(m22-m00-m11+1)
	fldz
	fcomip	st0,st1
	jnz	QuatFromMat3Mth2Cont
	jmp	QuatFromMat3DB0

QuatFromMat3Mth2Cont:

	fld	dword [floatHalf]	; [0] 0.5 [1] scale
	fld	st0			; [0] 0.5 [1] 0.5 [2] scale
	fmul	st0,st2			; [0] q.z=0.5*scale [1] scale
	fstp	dword [DReg+8]		; [0] 0.5 [1] scale
	fdivrp	st1,st0			; [0] scale = 0.5 / scale

	fld	dword [AReg+8]		; [0] m02 [1] scale
	fld	dword [AReg+32]		; [0] m20 [1] m02 [2] scale
	faddp	st1,st0			; [0] m02+m20 [1] scale
	fmul	st0,st1			; [0] q.x=scale*(m02+m20) [1] scale
	fstp	dword [DReg]		; [0] scale

	fld	dword [AReg+24]		; [0] m12 [1] scale
	fld	dword [AReg+36]		; [0] m21 [1] m12 [2] scale
	faddp	st1,st0			; [0] m12+m21 [1] scale
	fmul	st0,st1			; [0] q.y=scale*(m12+m21) [1] scale
	fstp	dword [DReg+4]		; [0] scale

	fld	dword [AReg+16]		; [0] m10 [1] scale
	fld	dword [AReg+4]		; [0] m01 [1] m10 [2] scale
	fsubp	st1,st0			; [0] m10-m01 [1] scale
	fmulp	st1,st0			; [0] q.w=scale*(m10-m01)
	fstp	dword [DReg+12]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatFromMat3DB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; QuaternionFromMat4Asm
;;;
;;; Call Stack
;;;
;;; [2] const mat4* m
;;; [1] quaternion* r
;;;
;;; extern "C" void QuaternionFromMat4Asm(quaternion* r,mat4* m)
;;; 

_QuaternionFromMat4Asm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],CReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *m

	fld	dword [AReg]		; [0] m00
	fld	dword [AReg+20]		; [1] m11
	fld	dword [AReg+40]		; [2] m22
	faddp	st1,st0
	faddp	st1,st0			; [0] trace=m00+m11+m22

	fldz
	fcomip	st0,st1

	jbe	QuatFromMat4GT0		; 0.0 <= trace
	jmp	QuatFromMat4Le0

QuatFromMat4GT0:

	fld1				; [0] 1.0 [1] trace
	faddp	st1,st0			; [0] 1+trace
	fsqrt				; [0] scale=sqrt(1+trace)
	fld	dword [floatHalf]	; [0] 0.5 [1] scale
	fld	st0			; [0] 0.5 [1] 0.5 [2] scale
	fmul	st0,st2			; [0] q.w=0.5*scale [1] 0.5 [2] scale
	fstp	dword [DReg+12]		; [0] 0.5 [1] scale

	fldz
	fcomip	st0,st1			; 0.0 == scale ?
	jnz	QuatFromMat4GT0Cont

	jmp	QuatFromMat4DB0

QuatFromMat4GT0Cont:

	fdivrp	st1,st0			; [0] scale = 0.5 / scale
	fld	dword [AReg+36]		; [0] m21 [1] scale
	fld	dword [AReg+24]		; [0] m12 [1] m21 [2] scale
	fsubp	st1,st0			; [0] m21-m12 [1] scale
	fmul	st0,st1			; [0] q.x=scale*(m21-m12) [1] scale
	fstp	dword [DReg]		; [0] scale

	fld	dword [AReg+8]		; [0] m02 [1] scale
	fld	dword [AReg+32]		; [0] m20 [1] m02 [2] scale
	fsubp	st1,st0			; [0] m02-m20 [1] scale
	fmul	st0,st1			; [0] q.y=scale*(m02-m20) [1] scale
	fstp	dword [DReg+4]		; [0] scale

	fld	dword [AReg+16]		; [0] m10 [1] scale
	fld	dword [AReg+4]		; [0] m01 [1] m10 [2] scale
	fsubp	st1,st0			; [0] m10-m01 [1] scale
	fmulp	st1,st0			; [0] q.z=scale*(m10-m01)
	fstp	dword [DReg+8]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatFromMat4Le0:

	ffree	st0			; clear trace
	fincstp

	;; i = 0 (sort to greatest of m00,m11 or m22)

	;; if ( m11 > m00 ) i=1

	mov	CReg,0			; if ( m11 > m00)
	fld	dword [AReg]		; [0] m00
	fld	dword [AReg+20]		; [0] m11 [1] m00
	fcomip	st0,st1			; [0] m00
	jbe	QuatFromMat4ChkMth1

	ffree	st0
	fincstp

	fld	dword [AReg+20]		; [0] m11
	mov	CReg,1

QuatFromMat4ChkMth1:

	;; if ( m22 > m?? ) i = 2

	fld	dword [AReg+40]		; [0] m22 [1] > of m00/m11
	fcomip	st0,st1			; [0] leftover
	
	jbe	QuatFromMat4SelectMethod
	mov	CReg,2

QuatFromMat4SelectMethod:

	ffree	st0
	fincstp

	cmp	CReg,2
	jne	QuatFromMat4ChkMethod1
	jmp	QuatFromMat4Method2

QuatFromMat4ChkMethod1:

	cmp	CReg,1
	jne	QuatFromMat4Method0
	jmp	QuatFromMat4Method1

QuatFromMat4Method0:

	fld	dword [AReg]		; [0] m00
	fld	dword [AReg+20]		; [0] m11 [1] m00
	fsubp	st1,st0			; [0] m00-m11
	fld	dword [AReg+40]		; [0] m22 [1] m00-m11
	fsubp	st1,st0			; [0] m00-m11-m22
	fld1
	faddp	st1,st0			; [0] m00-m11-m22+1
	fsqrt				; [0] scale=sqrt(m00-m11-m22+1)
	fldz
	fcomip	st0,st1
	jnz	QuatFromMat4Method1Cont
	jmp	QuatFromMat4DB0

QuatFromMat4Method1Cont:

	fld	dword [floatHalf]	; [0] 0.5 [1] scale
	fld	st0			; [0] 0.5 [1] 0.5 [2] scale
	fmul	st0,st2			; [0] q.x=0.5*scale [1] 0.5 [2] scale
	fstp	dword [DReg]		; [0] 0.5 [1] scale

	fdivrp	st1,st0			; [0] scale = 0.5 / scale
	fld	dword [AReg+16]		; [0] m10 [1] scale
	fld	dword [AReg+4]		; [0] m01 [1] m10 [2] scale
	faddp	st1,st0			; [0] m10+m01 [1] scale
	fmul	st0,st1			; [0] q.y=scale*(m10+m01) [1] scale
	fstp	dword [DReg+4]		; [0] scale

	fld	dword [AReg+32]		; [0] m20 [1] scale
	fld	dword [AReg+8]		; [0] m02 [1] m20 [2] scale
	faddp	st1,st0			; [0] m20+m02 [1] scale
	fmul	st0,st1			; [0] q.z=scale*(m20+m02) [1] scale
	fstp	dword [DReg+8]		; [0] scale

	fld	dword [AReg+36]		; [0] m21 [1] scale
	fld	dword [AReg+24]		; [0] m12 [1] m21 [2] scale
	fsubp	st1,st0			; [0] m21-m12 [1] scale
	fmulp	st1,st0			; [0] q.w=scale*(m21-m12)
	fstp	dword [DReg+12]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatFromMat4Method1:

	fld	dword [AReg+20]		; [0] m11
	fld	dword [AReg]		; [0] m00 [1] m11
	fsubp	st1,st0			; [0] m11-m00
	fld	dword [AReg+40]		; [0] m22 [1] m11-m00
	fsubp	st1,st0			; [0] m11-m00-m22
	fld1
	faddp	st1,st0			; [0] m11-m00-m22+1
	fsqrt				; [0] scale=sqrt(m11-m00-m22+1)
	fldz
	fcomip	st0,st1
	jnz	QuatFromMat4Mth1Cont
	jmp	QuatFromMat4DB0

QuatFromMat4Mth1Cont:

	fld	dword [floatHalf]	; [0] 0.5 [1] scale
	fld	st0			; [0] 0.5 [1] 0.5 [2] scale
	fmul	st0,st2			; [0] q.y=0.5*scale [1] 0.5 [2] scale
	fstp	dword [DReg+4]		; [0] 0.5 [1] scale

	fdivrp	st1,st0			; [0] scale=0.5/scale
	fld	dword [AReg+4]		; [0] m01 [1] scale
	fld	dword [AReg+16]		; [0] m10 [1] m01 [2] scale
	faddp	st1,st0			; [0] m01+m10 [1] scale
	fmul	st0,st1			; [0] q.x=scale*(m01+m10) [1] scale
	fstp	dword [DReg]		; [0] scale

	fld	dword [AReg+36]		; [0] m21 [1] scale
	fld	dword [AReg+24]		; [0] m12 [1] m21 [2] scale
	faddp	st1,st0			; [0] m21+m12 [1] scale
	fmul	st0,st1			; [0] q.z=scale*(m21+m12) [1] scale
	fstp	dword [DReg+8]		; [0] scale

	fld	dword [AReg+8]		; [0] m02 [1] scale
	fld	dword [AReg+32]		; [0] m20 [1] m02 [2] scale
	fsubp	st1,st0			; [0] m02-m20 [1] scale
	fmulp	st1,st0			; [0] q.w=scale*(m02-m20)
	fstp	dword [DReg+12]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatFromMat4Method2:

	fld	dword [AReg+40]		; [0] m22
	fld	dword [AReg]		; [1] m00
	fsubp	st1,st0			; [0] m22-m00
	fld	dword [AReg+20]		; [0] m11 [1] m22-m00
	fsubp	st1,st0			; [0] m22-m00-m11
	fld1
	faddp	st1,st0			; [0] m22-m00-m11+1
	fsqrt				; [0] scale=sqrt(m22-m00-m11+1)
	fldz
	fcomip	st0,st1
	jnz	QuatFromMat4Mth2Cont
	jmp	QuatFromMat4DB0

QuatFromMat4Mth2Cont:

	fld	dword [floatHalf]	; [0] 0.5 [1] scale
	fld	st0			; [0] 0.5 [1] 0.5 [2] scale
	fmul	st0,st2			; [0] q.z=0.5*scale [1] scale
	fstp	dword [DReg+8]		; [0] 0.5 [1] scale
	fdivrp	st1,st0			; [0] scale = 0.5 / scale

	fld	dword [AReg+8]		; [0] m02 [1] scale
	fld	dword [AReg+32]		; [0] m20 [1] m02 [2] scale
	faddp	st1,st0			; [0] m02+m20 [1] scale
	fmul	st0,st1			; [0] q.x=scale*(m02+m20) [1] scale
	fstp	dword [DReg]		; [0] scale

	fld	dword [AReg+24]		; [0] m12 [1] scale
	fld	dword [AReg+36]		; [0] m21 [1] m12 [2] scale
	faddp	st1,st0			; [0] m12+m21 [1] scale
	fmul	st0,st1			; [0] q.y=scale*(m12+m21) [1] scale
	fstp	dword [DReg+4]		; [0] scale

	fld	dword [AReg+16]		; [0] m10 [1] scale
	fld	dword [AReg+4]		; [0] m01 [1] m10 [2] scale
	fsubp	st1,st0			; [0] m10-m01 [1] scale
	fmulp	st1,st0			; [0] q.w=scale*(m10-m01)
	fstp	dword [DReg+12]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatFromMat4DB0:

	mov	eax,[zeroVec]
	mov	[DReg],eax
	mov	[DReg+4],eax
	mov	[DReg+8],eax
	mov	[DReg+12],eax

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	CReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; QuaternionSlerpAsm
;;;
;;; Call Stack
;;;
;;; [4] quaternion* v
;;; [3] quaternion* q
;;; [2] float       s
;;; [1] quaternion* r
;;;
;;; extern "C" void QuaternionSlerpAsm(quaternion*       r,
;;;                                    const float       s,
;;;                                    const quaternion* q,
;;;                                    const quaternion* v)
;;;

_QuaternionSlerpAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR3]	; *q
	mov	BReg,[STACK_PTR4]	; *v

	;; cos = dot(q,v)
	;;

	fld	dword [AReg]		; q.x
	fld	dword [BReg]		; v.x
	fmulp	st1,st0

	fld	dword [AReg+4]
	fld	dword [BReg+4]
	fmulp	st1,st0
	faddp	st1,st0

	fld	dword [AReg+8]
	fld	dword [BReg+8]
	fmulp	st1,st0
	faddp	st1,st0

	fld	dword [AReg+12]
	fld	dword [BReg+12]
	fmulp	st1,st0
	faddp	st1,st0

	;; Clamp the cos value to -1 to 1
	;;

	fld	dword [negVec]
	fcomip	st0,st1
	jbe	QuatSlerpCheckGT1

	ffree	st0
	fincstp
	fld	dword [negVec]

	jmp	QuatSlerpCont

QuatSlerpCheckGT1:

	fld1
	fcomip	st0,st1

	jae	QuatSlerpCont

	ffree	st0
	fincstp

	fld1

QuatSlerpCont:

	;; sin = sqrt(1-sqr(cos))
	;;

	fld1				; [0] 1.0f [1] cos
	fld	st1			; [0] cos [1] 1.0 [2] cos
	fmul	st0,st0			; [0] sqr(cos) [1] 1.0 [2] cos
	fsubp	st1,st0			; [0] 1-sqr(cos) [1] cos
	fsqrt				; [0] sin = sqrt(1-sqr(cos)) [1]cos

	fld	st0			; [0] sin [1] sin [2] cos
	fld	st2			; [0] cos [1] sin [2] sin [3] cos
	fpatan				; [0] angle [1] sin [2] cos

	fld	st0			; [0] angle [1] angle [2] sin [3] cos
	fabs				; [0] fabs(angle) [1] angle [2] sin [3] cos

	fld	dword [nearZero]	; 1e-6
	fcomip	st0,st1
	jbe	QuatSlerpCont1

	ffree	st3
	ffree	st2
	ffree	st1
	ffree	st0

	fincstp
	fincstp
	fincstp
	fincstp

	fwait

	mov	ebx,[AReg]
	mov	[DReg],ebx
	mov	ebx,[AReg+4]
	mov	[DReg+4],ebx
	mov	ebx,[AReg+8]
	mov	[DReg+8],ebx
	mov	ebx,[AReg+12]
	mov	[DReg+12],ebx

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

QuatSlerpCont1:

	;; [0] fabs(angle) [1] angle [2] sin [3] cos

	ffree	st0
	fincstp				; [0] angle [1] sin [2] cos

	;; [0] angle [1] sin [2] cos

	fxch	st0,st2			; [0] cos [1] sin [2] angle
	ffree	st0
	fincstp				; [0] sin [1] angle

	fld1
	fdivrp	st1,st0			; [0] invs [1] angle

	fld1				; [0] 1.0f [1] invs [2] angle
	fld	dword [STACK_PTR2]	; [0] s [1] 1.0f [2] invs [3] angle
	fsubp	st1,st0			; [0] 1-s [1] invs [2] angle
	fmul	st0,st2			; [0] angle*(1-s) [1] invs [2] angle
	fsin				; [0] sin(angle*(1-s)) [1] invs [2] angle
	fmul	st0,st1			; [0] invs*sin(angle*(1-s)) [1] invs [2] angle

	fxch	st2,st0			; [0] angle [1] invs [2] c1
	fld	dword [STACK_PTR2]	; [0] s [1] angle [2] invs [3] c1
	fmulp	st1,st0			; [0] s*angle [1] invs [2] c1
	fsin				; [0] sin(s*angle) [1] invs [2] c1
	fmulp	st1,st0			; [0] c2 = invs*sin(s*angle) [1] c1

	fld	dword [AReg]		; [0] q.x [1] c2 [2] c1
	fmul	st0,st2			; [0] c1*q.x [1] c2 [2] c1
	fld	dword [BReg]		; [0] v.x [1] c1*q.x [2] c2 [3] c1
	fmul	st0,st2			; [0] c2*v.x [1] c1*q.x [2] c2 [3] c1
	faddp	st1,st0			; [0] c2*v.x + c1*q.x [1] c2 [2] c1
	fstp	dword [DReg]		; [0] c2 [1] c1

	fld	dword [AReg+4]		; [0] q.y [1] c2 [2] c1
	fmul	st0,st2			; [0] c1*q.y [1] c2 [2] c1
	fld	dword [BReg+4]		; [0] v.y [1] c1*q.y [2] c2 [3] c1
	fmul	st0,st2			; [0] c2*v.y [1] c1*q.y [2] c2 [3] c1
	faddp	st1,st0			; [0] c2*v.y + c1*q.y [1] c2 [2] c1
	fstp	dword [DReg+4]		; [0] c2 [1] c1

	fld	dword [AReg+8]		; [0] q.z [1] c2 [2] c1
	fmul	st0,st2			; [0] c1*q.z [1] c2 [2] c1
	fld	dword [BReg+8]		; [0] v.z [1] c1*q.z [2] c2 [3] c1
	fmul	st0,st2			; [0] c2*v.z [1] c1*q.z [2] c2 [3] c1
	faddp	st1,st0			; [0] c2*v.z + c1*q.z [1] c2 [2] c1
	fstp	dword [DReg+8]		; [0] c2 [1] c1

	fld	dword [AReg+12]		; [0] q.w [1] c2 [2] c1
	fmulp	st2,st0			; [0] c2 [1] c1*q.w
	fld	dword [BReg+12]		; [0] v.w [1] c2 [2] c1*q.w
	fmulp	st1,st0			; [0] c2*v.w [1] c1*q.w
	faddp	st1,st0			; [0] c2*v.w + c1*q.w
	fstp	dword [DReg+12]

	fnclex

	fwait

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; QuaternionSinAsm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* p
;;; [2] quaternion* q
;;; [1] float*      pSin
;;;
;;; extern "C" void QuaternionSinAsm(float* r,quaternion* q,quaternio* p)
;;;

_QuaternionSinAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	BReg,[STACK_PTR2]	; *q
	mov	AReg,[STACK_PTR2]	; *p

	;; cos = dot(q,p)

	fld1				; [0] 1.0

	fld	dword [AReg]
	fld	dword [BReg]
	fmulp	st1,st0

	fld	dword [AReg+4]
	fld	dword [BReg+4]
	fmulp	st1,st0
	faddp	st1,st0

	fld	dword [AReg+8]
	fld	dword [BReg+8]
	fmulp	st1,st0
	faddp	st1,st0

	fld	dword [AReg+12]
	fld	dword [BReg+12]
	fmulp	st1,st0
	faddp	st1,st0			; [0] cos [1] 1.0

	fld	dword [negVec]
	fcomip	st0,st1
	jbe	QuatSinCheckGT1

	ffree	st0
	fincstp
	fld	dword [negVec]
	jmp	QuatSinCont

QuatSinCheckGT1:

	fld1
	fcomip	st0,st1

	jae	QuatSinCont

	ffree	st0
	fincstp

	fld1

QuatSinCont:

	;; sqr(sin) + sqr(cos) = 1
	;; sin = sqrt(1-sqr(cos))

	fld	st0
	fmulp	st1,st0			; [0] sqr(cos) [1] 1.0

	fsubp	st1,st0			; [0] 1-sqr(cos)
	fsqrt				; [0] sin = sqrt(1-sqr(cos))

	fstp	dword [DReg]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

;;;
;;; QuaternionCosAsm
;;;
;;; Call Stack
;;;
;;; [3] quaternion* p
;;; [2] quaternion* q
;;; [1] float*      r
;;;
;;; extern "C" void QuaternionCosAsm(float* r,const quaterion* q,const quaterinon* p)
;;;

_QuaternionCosAsm:

	mov	[STACK_SAVE1],AReg
	mov	[STACK_SAVE2],BReg
	mov	[STACK_SAVE3],DReg

	mov	DReg,[STACK_PTR1]	; *r
	mov	AReg,[STACK_PTR2]	; *q
	mov	BReg,[STACK_PTR3]	; *p

	;; cos = dot(q,p)

	fld	dword [AReg]
	fld	dword [BReg]
	fmulp	st1,st0

	fld	dword [AReg+4]
	fld	dword [BReg+4]
	fmulp	st1,st0
	faddp	st1,st0

	fld	dword [AReg+8]
	fld	dword [BReg+8]
	fmulp	st1,st0
	faddp	st1,st0

	fld	dword [AReg+12]
	fld	dword [BReg+12]
	fmulp	st1,st0
	faddp	st1,st0

	;; Clamp the value from -1 to 1
	;;

	fld	dword [negVec]
	fcomip	st0,st1
	jbe	QuatCosCheckGT1

	ffree	st0
	fincstp
	fld	dword [negVec]

	jmp	QuatCosCont

QuatCosCheckGT1:

	fld1
	fcomip	st0,st1

	jae	QuatCosCont

	ffree	st0
	fincstp

	fld1

QuatCosCont:

	fstp	dword [DReg]

	fnclex
	fwait

	mov	AReg,[STACK_SAVE1]
	mov	BReg,[STACK_SAVE2]
	mov	DReg,[STACK_SAVE3]

	ret

	