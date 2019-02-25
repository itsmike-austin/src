#ifndef __VECSTD_H
#define __VECSTD_H

#include <math.h>

#if !defined(__REGRESSION_TEST)

#define GetFpuStatus                    GetFpuStatusStd
#define ClearFpuStatus                  ClearFpuStatusStd

#define FloatLerp                       FloatLerpStd
#define FloatLerpPtr                    FloatLerpPtrStd
#define FloatSqr                        FloatSqrStd
#define FloatSqrPtr                     FloatSqrPtrStd

#if defined(__linux__)
  #define fCos                          cosf
  #define fSin                          sinf
  #define fTan                          tanf
  #define fACos                         acosf
  #define fASin                         asinf
  #define fATan                         atanf
  #define Cos                           cosl
  #define Sin                           sinl
  #define Tan                           tanl
  #define ACos                          acosl
  #define ASin                          asinl
  #define ATan                          atanl
#else
  #define fCos                          cos
  #define fSin                          sin
  #define fTan                          tan
  #define fACos                         acos
  #define fASin                         asin
  #define fATan                         atan
  #define Cos                           cos
  #define Sin                           sin
  #define Tan                           tan
  #define ACos                          acos
  #define ASin                          asin
  #define ATan                          atan
#endif

#define Vec2Copy                        Vec2CopyStd
#define Vec2CopyBlock                   Vec2CopyBlockStd
#define BuildVec2PackedArray            BuildVec2PackedArrayStd

#define Vec2AddFloat                    Vec2AddFloatStd
#define Vec2SubtractFloat               Vec2SubtractFloatStd
#define Vec2MultiplyFloat               Vec2MultiplyFloatStd
#define Vec2FloatMultiply               Vec2FloatMultiplyStd
#define Vec2DivideFloat                 Vec2DivideFloatStd

#define Vec2AddFloatFPU                 Vec2AddFloatStd
#define Vec2SubtractFloatFPU            Vec2SubtractFloatStd
#define Vec2MultiplyFloatFPU            Vec2MultiplyFloatStd
#define Vec2FloatMultiplyFPU            Vec2FloatMultiplyStd
#define Vec2DivideFloatFPU              Vec2DivideFloatStd

#define Vec2AddFloatToBlock             Vec2AddFloatToBlockStd
#define Vec2AddFloatToBlockSize         Vec2AddFloatToBlockSizeStd
#define Vec2BufAddFloatToBlock          Vec2BufAddFloatToBlockStd
#define Vec2BufAddFloatToBuf            Vec2BufAddFloatToBufStd

#define Vec2uAddFloatToBlockAsm         Vec2AddFloatToBlockStd

#define Vec2AddFloatToBlockFPU          Vec2AddFloatToBlockStd
#define Vec2AddFloatToBlockSizeFPU      Vec2AddFloatToBlockSizeStd
#define Vec2BufAddFloatToBlockFPU       Vec2BufAddFloatToBlockStd
#define Vec2BufAddFloatToBufFPU         Vec2BufAddFloatToBufStd

#define Vec2SubtractFloatFromBlock      Vec2SubtractFloatFromBlockStd
#define Vec2SubFloatFromBlockSize       Vec2SubFloatFromBlockSizeStd
#define Vec2BufSubFloatFromBlkSize      Vec2BufSubFloatFromBlkSizeStd
#define Vec2BufSubFloatFromBuf          Vec2BufSubFloatFromBufStd

#define Vec2uSubtractFloatFromBlock     Vec2SubtractFloatFromBlockStd

#define Vec2SubtractFloatFromBlockFPU   Vec2SubtractFloatFromBlockStd
#define Vec2SubFloatFromBlockSizeFPU    Vec2SubFloatFromBlockSizeStd
#define Vec2BufSubFloatFromBlkSizeFPU   Vec2BufSubFloatFromBlkSizeStd
#define Vec2BufSubFloatFromBufFPU       Vec2BufSubFloatFromBufStd

#define Vec2MultiplyBlockByFloat        Vec2MultiplyBlockByFloatStd
#define Vec2MultiplyBlkByFloatSize      Vec2MultiplyBlkByFloatSizeStd
#define Vec2BufMulBlockByFloatSize      Vec2BufMulBlockByFloatSizeStd
#define Vec2BufMulBlockByFloatBuf       Vec2BufMulBlockByFloatBufStd

#define Vec2uMultiplyBlockByFloat       Vec2MultiplyBlockByFloatStd

#define Vec2MultiplyBlockByFloatFPU     Vec2MultiplyBlockByFloatStd
#define Vec2MultiplyBlkByFloatSizeFPU   Vec2MultiplyBlkByFloatSizeStd
#define Vec2BufMulBlockByFloatSizeFPU   Vec2BufMulBlockByFloatSizeStd
#define Vec2BufMulBlockByFloatBufFPU    Vec2BufMulBlockByFloatBufStd

#define Vec2DivideBlockByFloat          Vec2DivideBlockByFloatStd
#define Vec2DivideBlockByFloatSize      Vec2DivideBlockByFloatSizeStd
#define Vec2BufDivBlockByFloatSize      Vec2BufDivBlockByFloatSizeStd
#define Vec2BufDivBufByFloat            Vec2BufDivBufByFloatStd

#define Vec2uDivideBlockByFloat         Vec2DivideBlockByFloatStd

#define Vec2DivideBlockByFloatFPU       Vec2DivideBlockByFloatStd
#define Vec2DivideBlockByFloatSizeFPU   Vec2DivideBlockByFloatSizeStd
#define Vec2BufDivBlockByFloatSizeFPU   Vec2BufDivBlockByFloatSizeStd
#define Vec2BufDivBufByFloatFPU         Vec2BufDivBufByFloatStd

#define Vec2Negate                      Vec2NegateStd
#define Vec2Add                         Vec2AddStd
#define Vec2Subtract                    Vec2SubtractStd
#define Vec2Multiply                    Vec2MultiplyStd
#define Vec2Divide                      Vec2DivideStd

#define Vec2Equals                      Vec2EqualsStd
#define Vec2NotEquals                   Vec2NotEqualsStd

#define Vec2uEquals                     Vec2EqualsStd
#define Vec2uNotEquals                  Vec2NotEqualsStd

#define Vec2NegateBlock                 Vec2NegateBlockStd
#define Vec2uNegateBlock                Vec2NegateBlockStd

#define Vec2NegateBlockBySize           Vec2NegateBlockBySizeStd
#define Vec2BufNegateBlockBySize        Vec2BufNegateBlockBySizeStd
#define Vec2BufNegateBufBySize          Vec2BufNegateBufBySizeStd

#define Vec2AddVec2ToBlock              Vec2AddVec2ToBlockStd
#define Vec2AddBlockToBlock             Vec2AddBlockToBlockStd

#define Vec2uAddVec2ToBlock             Vec2AddVec2ToBlockStd
#define Vec2uAddBlockToBlock            Vec2AddBlockToBlockStd

#define Vec2BufAddVec2ToBlockBySize     Vec2BufAddVec2ToBlockBySizeStd
#define Vec2BufAddBlockBySize           Vec2BufAddBlockBySizeStd
#define Vec2BufAddBufBySize             Vec2BufAddBufBySizeStd

#define Vec2SubtractVec2FromBlock       Vec2SubtractVec2FromBlockStd
#define Vec2SubtractBlockFromBlock      Vec2SubtractBlockFromBlockStd

#define Vec2uSubtractVec2FromBlock      Vec2SubtractVec2FromBlockStd
#define Vec2uSubtractBlockFromBlock     Vec2SubtractBlockFromBlockStd

#define Vec2BufSubVec2FromBlkBySize     Vec2BufSubVec2FromBlkBySizeStd
#define Vec2BufSubBlockBySize           Vec2BufSubBlockBySizeStd
#define Vec2BufSubBufBySize             Vec2BufSubBufBySizeStd

#define Vec2MultiplyBlockByVec2         Vec2MultiplyBlockByVec2Std
#define Vec2MultiplyBlockByBlock        Vec2MultiplyBlockByBlockStd

#define Vec2uMultiplyBlockByVec2        Vec2MultiplyBlockByVec2Std
#define Vec2uMultiplyBlockByBlock       Vec2MultiplyBlockByBlockStd

#define Vec2BufMulVec2ByBlockSize       Vec2BufMulVec2ByBlockSizeStd
#define Vec2BufMulBlockBySize           Vec2BufMulBlockBySizeStd
#define Vec2BufMulBufBySize             Vec2BufMulBufBySizeStd

#define Vec2DivideBlockByVec2           Vec2DivideBlockByVec2Std
#define Vec2DivideBlockByBlock          Vec2DivideBlockByBlockStd

#define Vec2uDivideBlockByVec2          Vec2DivideBlockByVec2Std
#define Vec2uDivideBlockByBlock         Vec2DivideBlockByBlockStd

#define Vec2BufDivVec2ByBlockSize       Vec2BufDivVec2ByBlockSizeStd
#define Vec2BufDivBlockBySize           Vec2BufDivBlockBySizeStd
#define Vec2BufDivBufBySize             Vec2BufDivBufBySizeStd

#define Vec2Lerp                        Vec2LerpStd
#define Vec2Sqr                         Vec2SqrStd
#define Vec2Sqrt                        Vec2SqrtStd
#define Vec2Normalize                   Vec2NormalizeStd
#define Vec2Dot                         Vec2DotStd
#define Vec2Length                      Vec2LengthStd
#define Vec2LengthBlock                 Vec2LengthBlockStd

#define Vec2BufLerpBuf                  Vec2BufLerpBufStd
#define Vec2BufSqrBuf                   Vec2BufSqrBufStd
#define Vec2BufSqrtBuf                  Vec2BufSqrtBufStd
#define Vec2BufNormalizeBuf             Vec2BufNormalizeBufStd
#define Vec2BufDotBuf                   Vec2BufDotBufStd
#define Vec2BufLengthBuf                Vec2BufLengthBufStd

#define Vec2LerpBlock                   Vec2LerpBlockStd
#define Vec2SqrBlock                    Vec2SqrBlockStd
#define Vec2SqrtBlock                   Vec2SqrtBlockStd
#define Vec2NormalizeBlock              Vec2NormalizeBlockStd
#define Vec2DotBlock                    Vec2DotBlockStd

#define Vec2uLerpBlock                  Vec2LerpBlockStd
#define Vec2uSqrBlock                   Vec2SqrBlockStd
#define Vec2uSqrtBlock                  Vec2SqrtBlockStd
#define Vec2uNormalizeBlock             Vec2NormalizeBlockStd
#define Vec2uDotBlock                   Vec2DotBlockStd

#define Vec3Copy                        Vec3CopyStd
#define Vec3CopyBlock                   Vec3CopyBlockStd
#define BuildVec3PackedArray            BuildVec3PackedArrayStd

#define Vec3AddFloat                    Vec3AddFloatStd
#define Vec3AddFloatToBlock             Vec3AddFloatToBlockStd
#define Vec3AddFloatToBlockBySize       Vec3AddFloatToBlockBySizeStd
#define Vec3BufAddFloatToBlock          Vec3BufAddFloatToBlockStd
#define Vec3BufAddFloatToBuf            Vec3BufAddFloatToBufStd

#define Vec3uAddFloat                   Vec3AddFloatStd
#define Vec3uAddFloatToBlock            Vec3AddFloatToBlockStd
#define Vec3uAddFloatToBlockBySize      Vec3AddFloatToBlockBySizeStd
#define Vec3uBufAddFloatToBlock         Vec3BufAddFloatToBlockStd
#define Vec3uBufAddFloatToBuf           Vec3BufAddFloatToBufStd

#define Vec3SubtractFloat               Vec3SubtractFloatStd
#define Vec3SubtractFloatFromBlock      Vec3SubtractFloatFromBlockStd
#define Vec3SubFloatFromBlockBySize     Vec3SubFloatFromBlockBySizeStd
#define Vec3BufSubFloatFromBlock        Vec3BufSubFloatFromBlockStd
#define Vec3BufSubFloatFromBuf          Vec3BufSubFloatFromBufStd

#define Vec3uSubtractFloat              Vec3SubtractFloatStd
#define Vec3uSubtractFloatFromBlock     Vec3SubtractFloatFromBlockStd
#define Vec3uSubFloatFromBlockBySize    Vec3SubFloatFromBlockBySizeStd
#define Vec3uBufSubFloatFromBlock       Vec3BufSubFloatFromBlockStd
#define Vec3uBufSubFloatFromBuf         Vec3BufSubFloatFromBufStd

#define Vec3MultiplyFloat               Vec3MultiplyFloatStd
#define Vec3MultiplyFloatToBlock        Vec3MultiplyFloatToBlockStd
#define Vec3MulFloatToBlockBySize       Vec3MulFloatToBlockBySizeStd
#define Vec3BufMulFloatToBlock          Vec3BufMulFloatToBlockStd
#define Vec3BufMulFloatToBuf            Vec3BufMulFloatToBufStd

#define Vec3uMultiplyFloat              Vec3MultiplyFloatStd
#define Vec3uMultiplyFloatToBlock       Vec3MultiplyFloatToBlockStd
#define Vec3uMulFloatToBlockBySize      Vec3MulFloatToBlockBySizeStd
#define Vec3uBufMulFloatToBlock         Vec3BufMulFloatToBlockStd
#define Vec3uBufMulFloatToBuf           Vec3BufMulFloatToBufStd

#define Vec3DivideFloat                 Vec3DivideFloatStd
#define Vec3DivideBlockByFloat          Vec3DivideBlockByFloatStd
#define Vec3DivBlockByFloatBySize       Vec3DivBlockByFloatBySizeStd
#define Vec3BufDivBlockByFloat          Vec3BufDivBlockByFloatStd
#define Vec3BufDivBufByFloat            Vec3BufDivBufByFloatStd

#define Vec3uDivideFloat                Vec3DivideFloatStd
#define Vec3uDivideBlockByFloat         Vec3DivideBlockByFloatStd
#define Vec3uDivBlockByFloatBySize      Vec3DivBlockByFloatBySizeStd
#define Vec3uBufDivBlockByFloat         Vec3BufDivBlockByFloatStd
#define Vec3uBufDivBufByFloat           Vec3BufDivBufByFloatStd

#define Vec3Equals                      Vec3EqualsStd
#define Vec3NotEquals                   Vec3NotEqualsStd

#define Vec3uEquals                     Vec3EqualsStd
#define Vec3uNotEquals                  Vec3NotEqualsStd

#define Vec3Negate                      Vec3NegateStd
#define Vec3NegateBlock                 Vec3NegateBlockStd
#define Vec3NegateBlockBySize           Vec3NegateBlockBySizeStd
#define Vec3BufNegateBlock              Vec3BufNegateBlockStd
#define Vec3BufNegateBuf                Vec3BufNegateBufStd

#define Vec3uNegate                     Vec3NegateStd
#define Vec3uNegateBlock                Vec3NegateBlockStd
#define Vec3uNegateBlockBySize          Vec3NegateBlockBySizeStd
#define Vec3uBufNegateBlock             Vec3BufNegateBlockStd
#define Vec3uBufNegateBuf               Vec3BufNegateBufStd

#define Vec3Add                         Vec3AddStd
#define Vec3AddVecToBlock               Vec3AddVecToBlockStd
#define Vec3AddVecToBlockBySize         Vec3AddVecToBlockBySizeStd
#define Vec3BufAddVecToBlock            Vec3BufAddVecToBlockStd
#define Vec3BufAddVecToBuf              Vec3BufAddVecToBufStd
#define Vec3AddBlockToBlock             Vec3AddBlockToBlockStd
#define Vec3AddBlockToBlockBySize       Vec3AddBlockToBlockBySizeStd
#define Vec3BufAddBlockToBuf            Vec3BufAddBlockToBufStd
#define Vec3BufAddBufToBuf              Vec3BufAddBufToBufStd

#define Vec3uAdd                        Vec3AddStd
#define Vec3uAddVecToBlock              Vec3AddVecToBlockStd
#define Vec3uAddVecToBlockBySize        Vec3AddVecToBlockBySizeStd
#define Vec3uBufAddVecToBlock           Vec3BufAddVecToBlockStd
#define Vec3uBufAddVecToBuf             Vec3BufAddVecToBufStd
#define Vec3uAddBlockToBlock            Vec3AddBlockToBlockStd
#define Vec3uAddBlockToBlockBySize      Vec3AddBlockToBlockBySizeStd
#define Vec3uBufAddBlockToBuf           Vec3BufAddBlockToBufStd
#define Vec3uBufAddBufToBuf             Vec3BufAddBufToBufStd

#define Vec3Subtract                    Vec3SubtractStd
#define Vec3SubVecFromBlock             Vec3SubVecFromBlockStd
#define Vec3SubVecFromBlockBySize       Vec3SubVecFromBlockBySizeStd
#define Vec3BufSubVecFromBlock          Vec3BufSubVecFromBlockStd
#define Vec3BufSubVecFromBuf            Vec3BufSubVecFromBufStd
#define Vec3SubBlockFromBlock           Vec3SubBlockFromBlockStd
#define Vec3SubBlockFromBlockBySize     Vec3SubBlockFromBlockBySizeStd
#define Vec3BufSubBlockFromBuf          Vec3BufSubBlockFromBufStd
#define Vec3BufSubBufFromBuf            Vec3BufSubBufFromBufStd

#define Vec3uSubtract                   Vec3SubtractStd
#define Vec3uSubVecFromBlock            Vec3SubVecFromBlockStd
#define Vec3uSubVecFromBlockBySize      Vec3SubVecFromBlockBySizeStd
#define Vec3uBufSubVecFromBlock         Vec3BufSubVecFromBlockStd
#define Vec3uBufSubVecFromBuf           Vec3BufSubVecFromBufStd
#define Vec3uSubBlockFromBlock          Vec3SubBlockFromBlockStd
#define Vec3uSubBlockFromBlockBySize    Vec3SubBlockFromBlockBySizeStd
#define Vec3uBufSubBlockFromBuf         Vec3BufSubBlockFromBufStd
#define Vec3uBufSubBufFromBuf           Vec3BufSubBufFromBufStd

#define Vec3Multiply                    Vec3MultiplyStd
#define Vec3MulBlockByVec               Vec3MulBlockByVecStd
#define Vec3MulBlockByVecUseSize        Vec3MulBlockByVecUseSizeStd
#define Vec3BufMulBufByVec              Vec3BufMulBufByVecStd
#define Vec3BufMulBufByVecUseSize       Vec3BufMulBufByVecUseSizeStd
#define Vec3MulBlockByBlock             Vec3MulBlockByBlockStd
#define Vec3MulBlockByBlockUseSize      Vec3MulBlockByBlockUseSizeStd
#define Vec3BufMulBufByBlock            Vec3BufMulBufByBlockStd
#define Vec3BufMulBufByBuf              Vec3BufMulBufByBufStd

#define Vec3uMultiply                   Vec3MultiplyStd
#define Vec3uMulBlockByVec              Vec3MulBlockByVecStd
#define Vec3uMulBlockByVecUseSize       Vec3MulBlockByVecUseSizeStd
#define Vec3uBufMulBufByVec             Vec3BufMulBufByVecStd
#define Vec3uBufMulBufByVecUseSize      Vec3BufMulBufByVecUseSizeStd
#define Vec3uMulBlockByBlock            Vec3MulBlockByBlockStd
#define Vec3uMulBlockByBlockUseSize     Vec3MulBlockByBlockUseSizeStd
#define Vec3uBufMulBufByBlock           Vec3BufMulBufByBlockStd
#define Vec3uBufMulBufByBuf             Vec3BufMulBufByBufStd

#define Vec3Divide                      Vec3DivideStd
#define Vec3DivBlockByVec               Vec3DivBlockByVecStd
#define Vec3DivBlockByVecUseSize        Vec3DivBlockByVecUseSizeStd
#define Vec3BufDivBufByVec              Vec3BufDivBufByVecStd
#define Vec3BufDivBufByVecUseSize       Vec3BufDivBufByVecUseSizeStd
#define Vec3DivBlockByBlock             Vec3DivBlockByBlockStd
#define Vec3DivBlockByBlockUseSize      Vec3DivBlockByBlockUseSizeStd
#define Vec3BufDivBufByBlock            Vec3BufDivBufByBlockStd
#define Vec3BufDivBufByBuf              Vec3BufDivBufByBufStd

#define Vec3uDivide                     Vec3DivideStd
#define Vec3uDivBlockByVec              Vec3DivBlockByVecStd
#define Vec3uDivBlockByVecUseSize       Vec3DivBlockByVecUseSizeStd
#define Vec3uBufDivBufByVec             Vec3BufDivBufByVecStd
#define Vec3uBufDivBufByVecUseSize      Vec3BufDivBufByVecUseSizeStd
#define Vec3uDivBlockByBlock            Vec3DivBlockByBlockStd
#define Vec3uDivBlockByBlockUseSize     Vec3DivBlockByBlockUseSizeStd
#define Vec3uBufDivBufByBlock           Vec3BufDivBufByBlockStd
#define Vec3uBufDivBufByBuf             Vec3BufDivBufByBufStd

#define Vec3Lerp                        Vec3LerpStd
#define Vec3LerpBlock                   Vec3LerpBlockStd
#define Vec3LerpBlockUseSize            Vec3LerpBlockUseSizeStd
#define Vec3BufLerpBlock                Vec3BufLerpBlockStd
#define Vec3BufLerpBuf                  Vec3BufLerpBufStd

#define Vec3uLerp                       Vec3LerpStd
#define Vec3uLerpBlock                  Vec3LerpBlockStd
#define Vec3uLerpBlockUseSize           Vec3LerpBlockUseSizeStd
#define Vec3uBufLerpBlock               Vec3BufLerpBlockStd
#define Vec3uBufLerpBuf                 Vec3BufLerpBufStd

#define Vec3DotFlat                     Vec3DotStd
#define Vec3uDotFlat                    Vec3DotStd

#define Vec3Dot                         Vec3DotStd
#define Vec3DotBlock                    Vec3DotBlockStd
#define Vec3DotBlockUseSize             Vec3DotBlockUseSizeStd
#define Vec3BufDotBuf                   Vec3BufDotBufStd

#define Vec3DotFPU                      Vec3DotStd

#define Vec3uDot                        Vec3DotStd
#define Vec3uDotBlock                   Vec3DotBlockStd
#define Vec3uDotBlockUseSize            Vec3DotBlockUseSizeStd
#define Vec3uBufDotBuf                  Vec3BufDotBufStd

#define Vec3Sqr                         Vec3SqrStd
#define Vec3SqrBlock                    Vec3SqrBlockStd
#define Vec3SqrBlockUseSize             Vec3SqrBlockUseSizeStd
#define Vec3BufSqrBuf                   Vec3BufSqrBufStd

#define Vec3uSqr                        Vec3SqrStd
#define Vec3uSqrBlock                   Vec3SqrBlockStd
#define Vec3uSqrBlockUseSize            Vec3SqrBlockUseSizeStd
#define Vec3uBufSqrBuf                  Vec3BufSqrBufStd

#define Vec3Sqrt                        Vec3SqrtStd
#define Vec3SqrtBlock                   Vec3SqrtBlockStd
#define Vec3SqrtBlockUseSize            Vec3SqrtBlockUseSizeStd
#define Vec3BufSqrtBuf                  Vec3BufSqrtBufStd

#define Vec3uSqrt                       Vec3SqrtStd
#define Vec3uSqrtBlock                  Vec3SqrtBlockStd
#define Vec3uSqrtBlockUseSize           Vec3SqrtBlockUseSizeStd
#define Vec3uBufSqrtBuf                 Vec3BufSqrtBufStd

#define Vec3NormalizeFlat               Vec3NormalizeFlatStd
#define Vec3NormalizeBlockFlat          Vec3NormalizeBlockStd
#define Vec3NormalizeBlockFlatUseSize   Vec3NormalizeBlockUseStd
#define Vec3BufNormalizeBufFlatAsm      Vec3BufNormalizeBufStd

#define Vec3Normalize                   Vec3NormalizeStd
#define Vec3NormalizeBlock              Vec3NormalizeBlockStd
#define Vec3NormalizeBlockUseSize       Vec3NormalizeBlockUseSizeStd
#define Vec3BufNormalizeBuf             Vec3BufNormalizeBufStd

#define Vec3NormalizeFPU                Vec3NormalizeStd

#define Vec3uNormalizeFlat              Vec3NormalizeFlatStd
#define Vec3uNormalizeBlockFlat         Vec3NormalizeBlockStd
#define Vec3uNormalizeBlockFlatUseSize  Vec3NormalizeBlockUseStd
#define Vec3uBufNormalizeBufFlatAsm     Vec3BufNormalizeBufStd

#define Vec3uNormalize                  Vec3NormalizeStd
#define Vec3uNormalizeBlock             Vec3NormalizeBlockStd
#define Vec3uNormalizeBlockUseSize      Vec3NormalizeBlockUseSizeStd
#define Vec3uBufNormalizeBuf            Vec3BufNormalizeBufStd

#define Vec3LengthFlat                  Vec3LengthStd
#define Vec3LengthBlockFlat             Vec3LengthBlockStd
#define Vec3LengthBlockFlatUseSize      Vec3LengthBlockUseSizeStd
#define Vec3BufLengthBufFlat            Vec3BufLengthBufStd

#define Vec3Length                      Vec3LengthStd
#define Vec3LengthBlock                 Vec3LengthBlockStd
#define Vec3LengthBlockUseSize          Vec3LengthBlockUseSizeStd
#define Vec3BufLengthBuf                Vec3BufLengthBufStd

#define Vec3LengthFPU                   Vec3LengthStd

#define Vec3uLengthFlat                 Vec3LengthStd
#define Vec3uLengthBlockFlat            Vec3LengthBlockStd
#define Vec3uLengthBlockFlatUseSize     Vec3LengthBlockUseSizeStd
#define Vec3uBufLengthBufFlat           Vec3BufLengthBufStd

#define Vec3uLength                     Vec3LengthStd
#define Vec3uLengthBlock                Vec3LengthBlockStd
#define Vec3uLengthBlockUseSize         Vec3LengthBlockUseSizeStd
#define Vec3uBufLengthBuf               Vec3BufLengthBufStd

#define Vec3Cross                       Vec3CrossStd
#define Vec3CrossBlock                  Vec3CrossBlockStd
#define Vec3CrossBlockUseSize           Vec3CrossBlockUseSizeStd
#define Vec3BufCrossBuf                 Vec3BufCrossBufStd

#define Vec3uCross                      Vec3CrossStd
#define Vec3uCrossBlock                 Vec3CrossBlockStd
#define Vec3uCrossBlockUseSize          Vec3CrossBlockUseSizeStd
#define Vec3uBufCrossBuf                Vec3BufCrossBufStd

#define Vec3Reflect                     Vec3ReflectStd
#define Vec3uReflect                    Vec3ReflectStd

#define Vec4Copy                        Vec4CopyStd
#define Vec4CopyBlock                   Vec4CopyBlockStd
#define BuildVec4PackedArray            BuildVec4PackedArrayStd

#define Vec4AddFloat                    Vec4AddFloatStd
#define Vec4AddFloatToBlock             Vec4AddFloatToBlockStd
#define Vec4AddFloatToBlockBySize       Vec4AddFloatToBlockBySizeStd
#define Vec4BufAddFloatToBlock          Vec4BufAddFloatToBlockStd
#define Vec4BufAddFloatToBuf            Vec4BufAddFloatToBufStd

#define Vec4uAddFloat                   Vec4AddFloatStd
#define Vec4uAddFloatToBlock            Vec4AddFloatToBlockStd
#define Vec4uAddFloatToBlockBySize      Vec4AddFloatToBlockBySizeStd
#define Vec4uBufAddFloatToBlock         Vec4BufAddFloatToBlockStd
#define Vec4uBufAddFloatToBuf           Vec4BufAddFloatToBufStd

#define Vec4SubtractFloat               Vec4SubtractFloatStd
#define Vec4SubtractFloatFromBlock      Vec4SubtractFloatFromBlockStd
#define Vec4SubFloatFromBlockBySize     Vec4SubFloatFromBlockBySizeStd
#define Vec4BufSubFloatFromBlock        Vec4BufSubFloatFromBlockStd
#define Vec4BufSubFloatFromBuf          Vec4BufSubFloatFromBufStd

#define Vec4uSubtractFloat              Vec4SubtractFloatStd
#define Vec4uSubtractFloatFromBlock     Vec4SubtractFloatFromBlockStd
#define Vec4uSubFloatFromBlockBySize    Vec4SubFloatFromBlockBySizeStd
#define Vec4uBufSubFloatFromBlock       Vec4BufSubFloatFromBlockStd
#define Vec4uBufSubFloatFromBuf         Vec4BufSubFloatFromBufStd

#define Vec4MultiplyFloat               Vec4MultiplyFloatStd
#define Vec4MultiplyFloatToBlock        Vec4MultiplyFloatToBlockStd
#define Vec4MulFloatToBlockBySize       Vec4MulFloatToBlockBySizeStd
#define Vec4BufMulFloatToBlock          Vec4BufMulFloatToBlockStd
#define Vec4BufMulFloatToBuf            Vec4BufMulFloatToBufStd

#define Vec4uMultiplyFloat              Vec4MultiplyFloatStd
#define Vec4uMultiplyFloatToBlock       Vec4MultiplyFloatToBlockStd
#define Vec4uMulFloatToBlockBySize      Vec4MulFloatToBlockBySizeStd
#define Vec4uBufMulFloatToBlock         Vec4BufMulFloatToBlockStd
#define Vec4uBufMulFloatToBuf           Vec4BufMulFloatToBufStd

#define Vec4DivideFloat                 Vec4DivideFloatStd
#define Vec4DivideBlockByFloat          Vec4DivideBlockByFloatStd
#define Vec4DivBlockByFloatBySize       Vec4DivBlockByFloatBySizeStd
#define Vec4BufDivBlockByFloat          Vec4BufDivBlockByFloatStd
#define Vec4BufDivBufByFloat            Vec4BufDivBufByFloatStd

#define Vec4uDivideFloat                Vec4DivideFloatStd
#define Vec4uDivideBlockByFloat         Vec4DivideBlockByFloatStd
#define Vec4uDivBlockByFloatBySize      Vec4DivBlockByFloatBySizeStd
#define Vec4uBufDivBlockByFloat         Vec4BufDivBlockByFloatStd
#define Vec4uBufDivBufByFloat           Vec4BufDivBufByFloatStd

#define Vec4Equals                      Vec4EqualsStd
#define Vec4NotEquals                   Vec4NotEqualsStd

#define Vec4Negate                      Vec4NegateStd
#define Vec4NegateBlock                 Vec4NegateBlockStd
#define Vec4NegateBlockBySize           Vec4NegateBlockBySizeStd
#define Vec4BufNegateBlock              Vec4BufNegateBlockStd
#define Vec4BufNegateBuf                Vec4BufNegateBufStd

#define Vec4uNegate                     Vec4NegateStd
#define Vec4uNegateBlock                Vec4NegateBlockStd
#define Vec4uNegateBlockBySize          Vec4NegateBlockBySizeStd
#define Vec4uBufNegateBlock             Vec4BufNegateBlockStd
#define Vec4uBufNegateBuf               Vec4BufNegateBufStd

#define Vec4Add                         Vec4AddStd
#define Vec4AddVecToBlock               Vec4AddVecToBlockStd
#define Vec4AddVecToBlockBySize         Vec4AddVecToBlockBySizeStd
#define Vec4BufAddVecToBlock            Vec4BufAddVecToBlockStd
#define Vec4BufAddVecToBuf              Vec4BufAddVecToBufStd
#define Vec4AddBlockToBlock             Vec4AddBlockToBlockStd
#define Vec4AddBlockToBlockBySize       Vec4AddBlockToBlockBySizeStd
#define Vec4BufAddBlockToBuf            Vec4BufAddBlockToBufStd
#define Vec4BufAddBufToBuf              Vec4BufAddBufToBufStd

#define Vec4uAdd                        Vec4AddStd
#define Vec4uAddVecToBlock              Vec4AddVecToBlockStd
#define Vec4uAddVecToBlockBySize        Vec4AddVecToBlockBySizeStd
#define Vec4uBufAddVecToBlock           Vec4BufAddVecToBlockStd
#define Vec4uBufAddVecToBuf             Vec4BufAddVecToBufStd
#define Vec4uAddBlockToBlock            Vec4AddBlockToBlockStd
#define Vec4uAddBlockToBlockBySize      Vec4AddBlockToBlockBySizeStd
#define Vec4uBufAddBlockToBuf           Vec4BufAddBlockToBufStd
#define Vec4uBufAddBufToBuf             Vec4BufAddBufToBufStd

#define Vec4Subtract                    Vec4SubtractStd
#define Vec4SubVecFromBlock             Vec4SubVecFromBlockStd
#define Vec4SubVecFromBlockBySize       Vec4SubVecFromBlockBySizeStd
#define Vec4BufSubVecFromBlock          Vec4BufSubVecFromBlockStd
#define Vec4BufSubVecFromBuf            Vec4BufSubVecFromBufStd
#define Vec4SubBlockFromBlock           Vec4SubBlockFromBlockStd
#define Vec4SubBlockFromBlockBySize     Vec4SubBlockFromBlockBySizeStd
#define Vec4BufSubBlockFromBuf          Vec4BufSubBlockFromBufStd
#define Vec4BufSubBufFromBuf            Vec4BufSubBufFromBufStd

#define Vec4uSubtract                   Vec4SubtractStd
#define Vec4uSubVecFromBlock            Vec4SubVecFromBlockStd
#define Vec4uSubVecFromBlockBySize      Vec4SubVecFromBlockBySizeStd
#define Vec4uBufSubVecFromBlock         Vec4BufSubVecFromBlockStd
#define Vec4uBufSubVecFromBuf           Vec4BufSubVecFromBufStd
#define Vec4uSubBlockFromBlock          Vec4SubBlockFromBlockStd
#define Vec4uSubBlockFromBlockBySize    Vec4SubBlockFromBlockBySizeStd
#define Vec4uBufSubBlockFromBuf         Vec4BufSubBlockFromBufStd
#define Vec4uBufSubBufFromBuf           Vec4BufSubBufFromBufStd

#define Vec4Multiply                    Vec4MultiplyStd
#define Vec4MulBlockByVec               Vec4MulBlockByVecStd
#define Vec4MulBlockByVecUseSize        Vec4MulBlockByVecUseSizeStd
#define Vec4BufMulBufByVec              Vec4BufMulBufByVecStd
#define Vec4BufMulBufByVecUseSize       Vec4BufMulBufByVecUseSizeStd
#define Vec4MulBlockByBlock             Vec4MulBlockByBlockStd
#define Vec4MulBlockByBlockUseSize      Vec4MulBlockByBlockUseSizeStd
#define Vec4BufMulBufByBlock            Vec4BufMulBufByBlockStd
#define Vec4BufMulBufByBuf              Vec4BufMulBufByBufStd

#define Vec4uMultiply                   Vec4MultiplyStd
#define Vec4uMulBlockByVec              Vec4MulBlockByVecStd
#define Vec4uMulBlockByVecUseSize       Vec4MulBlockByVecUseSizeStd
#define Vec4uBufMulBufByVec             Vec4BufMulBufByVecStd
#define Vec4uBufMulBufByVecUseSize      Vec4BufMulBufByVecUseSizeStd
#define Vec4uMulBlockByBlock            Vec4MulBlockByBlockStd
#define Vec4uMulBlockByBlockUseSize     Vec4MulBlockByBlockUseSizeStd
#define Vec4uBufMulBufByBlock           Vec4BufMulBufByBlockStd
#define Vec4uBufMulBufByBuf             Vec4BufMulBufByBufStd

#define Vec4Divide                      Vec4DivideStd
#define Vec4DivBlockByVec               Vec4DivBlockByVecStd
#define Vec4DivBlockByVecUseSize        Vec4DivBlockByVecUseSizeStd
#define Vec4BufDivBufByVec              Vec4BufDivBufByVecStd
#define Vec4BufDivBufByVecUseSize       Vec4BufDivBufByVecUseSizeStd
#define Vec4DivBlockByBlock             Vec4DivBlockByBlockStd
#define Vec4DivBlockByBlockUseSize      Vec4DivBlockByBlockUseSizeStd
#define Vec4BufDivBufByBlock            Vec4BufDivBufByBlockStd
#define Vec4BufDivBufByBuf              Vec4BufDivBufByBufStd

#define Vec4uDivide                     Vec4DivideStd
#define Vec4uDivBlockByVec              Vec4DivBlockByVecStd
#define Vec4uDivBlockByVecUseSize       Vec4DivBlockByVecUseSizeStd
#define Vec4uBufDivBufByVec             Vec4BufDivBufByVecStd
#define Vec4uBufDivBufByVecUseSize      Vec4BufDivBufByVecUseSizeStd
#define Vec4uDivBlockByBlock            Vec4DivBlockByBlockStd
#define Vec4uDivBlockByBlockUseSize     Vec4DivBlockByBlockUseSizeStd
#define Vec4uBufDivBufByBlock           Vec4BufDivBufByBlockStd
#define Vec4uBufDivBufByBuf             Vec4BufDivBufByBufStd

#define Vec4Lerp                        Vec4LerpStd
#define Vec4LerpBlock                   Vec4LerpBlockStd
#define Vec4LerpBlockUseSize            Vec4LerpBlockUseSizeStd
#define Vec4BufLerpBlock                Vec4BufLerpBlockStd
#define Vec4BufLerpBuf                  Vec4BufLerpBufStd

#define Vec4uLerp                       Vec4LerpStd
#define Vec4uLerpBlock                  Vec4LerpBlockStd
#define Vec4uLerpBlockUseSize           Vec4LerpBlockUseSizeStd
#define Vec4uBufLerpBlock               Vec4BufLerpBlockStd
#define Vec4uBufLerpBuf                 Vec4BufLerpBufStd

#define Vec4DotFlat                     Vec4DotStd
#define Vec4DotBlockFlat                Vec4DotBlockStd
#define Vec4DotBlockFlatUseSize         Vec4DotBlockUseSizeStd
#define Vec4BufDotBufFlat               Vec4BufDotBufStd

#define Vec4Dot                         Vec4DotStd
#define Vec4DotBlock                    Vec4DotBlockStd
#define Vec4DotBlockUseSize             Vec4DotBlockUseSizeStd
#define Vec4BufDotBuf                   Vec4BufDotBufStd

#define Vec4DotFPU                      Vec4DotStd

#define Vec4uDotFlat                    Vec4DotStd
#define Vec4uDotBlockFlat               Vec4DotBlockStd
#define Vec4uDotBlockFlatUseSize        Vec4DotBlockUseSizeStd
#define Vec4uBufDotBufFlat              Vec4BufDotBufStd

#define Vec4uDot                        Vec4DotStd
#define Vec4uDotBlock                   Vec4DotBlockStd
#define Vec4uDotBlockUseSize            Vec4DotBlockUseSizeStd
#define Vec4uBufDotBuf                  Vec4BufDotBufStd

#define Vec4Sqr                         Vec4SqrStd
#define Vec4SqrBlock                    Vec4SqrBlockStd
#define Vec4SqrBlockUseSize             Vec4SqrBlockUseSizeStd
#define Vec4BufSqrBuf                   Vec4BufSqrBufStd

#define Vec4uSqr                        Vec4SqrStd
#define Vec4uSqrBlock                   Vec4SqrBlockStd
#define Vec4uSqrBlockUseSize            Vec4SqrBlockUseSizeStd
#define Vec4uBufSqrBuf                  Vec4BufSqrBufStd

#define Vec4Sqrt                        Vec4SqrtStd
#define Vec4SqrtBlock                   Vec4SqrtBlockStd
#define Vec4SqrtBlockUseSize            Vec4SqrtBlockUseSizeStd
#define Vec4BufSqrtBuf                  Vec4BufSqrtBufStd

#define Vec4uSqrt                       Vec4SqrtStd
#define Vec4uSqrtBlock                  Vec4SqrtBlockStd
#define Vec4uSqrtBlockUseSize           Vec4SqrtBlockUseSizeStd
#define Vec4uBufSqrtBuf                 Vec4BufSqrtBufStd

#define Vec4NormalizeFlat               Vec4NormalizeFlatStd
#define Vec4NormalizeBlockFlat          Vec4NormalizeBlockStd
#define Vec4NormalizeBlockFlatUseSize   Vec4NormalizeBlockUseSizeStd
#define Vec4BufNormalizeBufFlat         Vec4BufNormalizeBufStd

#define Vec4Normalize                   Vec4NormalizeStd
#define Vec4NormalizeBlock              Vec4NormalizeBlockStd
#define Vec4NormalizeBlockUseSize       Vec4NormalizeBlockUseSizeStd
#define Vec4BufNormalizeBuf             Vec4BufNormalizeBufStd

#define Vec4NormalizeFPU                Vec4NormalizeStd

#define Vec4uNormalizeFlat              Vec4NormalizeFlatStd
#define Vec4uNormalizeBlockFlat         Vec4NormalizeBlockStd
#define Vec4uNormalizeBlockFlatUseSize  Vec4NormalizeBlockUseSizeStd
#define Vec4uBufNormalizeBufFlat        Vec4BufNormalizeBufStd

#define Vec4uNormalize                  Vec4NormalizeStd
#define Vec4uNormalizeBlock             Vec4NormalizeBlockStd
#define Vec4uNormalizeBlockUseSize      Vec4NormalizeBlockUseSizeStd
#define Vec4uBufNormalizeBuf            Vec4BufNormalizeBufStd

#define Vec4LengthFlat                  Vec4LengthStd
#define Vec4LengthBlockFlat             Vec4LengthBlockStd
#define Vec4LengthBlockFlatUseSize      Vec4LengthBlockUseSizeStd
#define Vec4BufLengthBufFlat            Vec4BufLengthBufStd

#define Vec4Length                      Vec4LengthStd
#define Vec4LengthBlock                 Vec4LengthBlockStd
#define Vec4LengthBlockUseSize          Vec4LengthBlockUseSizeStd
#define Vec4BufLengthBuf                Vec4BufLengthBufStd

#define Vec4LengthFPU                   Vec4LengthStd

#define Vec4uLengthFlat                 Vec4LengthStd
#define Vec4uLengthBlockFlat            Vec4LengthBlockStd
#define Vec4uLengthBlockFlatUseSize     Vec4LengthBlockUseSizeStd
#define Vec4uBufLengthBufFlat           Vec4BufLengthBufStd

#define Vec4uLength                     Vec4LengthStd
#define Vec4uLengthBlock                Vec4LengthBlockStd
#define Vec4uLengthBlockUseSize         Vec4LengthBlockUseSizeStd
#define Vec4uBufLengthBuf               Vec4BufLengthBufStd

#define Vec4Cross                       Vec4CrossStd
#define Vec4CrossBlock                  Vec4CrossBlockStd
#define Vec4CrossBlockUseSize           Vec4CrossBlockUseSizeStd
#define Vec4BufCrossBuf                 Vec4BufCrossBufStd

#define Vec4uCross                      Vec4CrossStd
#define Vec4uCrossBlock                 Vec4CrossBlockStd
#define Vec4uCrossBlockUseSize          Vec4CrossBlockUseSizeStd
#define Vec4uBufCrossBuf                Vec4BufCrossBufStd

#define Mat2Negate                      Mat2NegateStd
#define Mat2Add                         Mat2AddStd
#define Mat2AddFloat                    Mat2AddFloatStd
#define Mat2Subtract                    Mat2SubtractStd
#define Mat2SubtractFloat               Mat2SubtractFloatStd
#define Mat2Multiply                    Mat2MultiplyStd
#define Mat2MultiplyVec                 Mat2MultiplyVecStd
#define Mat2MultiplyFloat               Mat2MultiplyFloatStd
#define Mat2Identity                    Mat2IdentityStd
#define Mat2Transpose                   Mat2TransposeStd
#define Mat2MultiplyVecBlock            Mat2MultiplyVecBlockStd

#define Mat2uNegate                     Mat2NegateStd
#define Mat2uAdd                        Mat2AddStd
#define Mat2uAddFloat                   Mat2AddFloatStd
#define Mat2uSubtract                   Mat2SubtractStd
#define Mat2uSubtractFloat              Mat2SubtractFloatStd
#define Mat2uMultiply                   Mat2MultiplyStd
#define Mat2uMultiplyVec                Mat2MultiplyVecStd
#define Mat2uMultiplyFloat              Mat2MultiplyFloatStd
#define Mat2uIdentity                   Mat2IdentityStd
#define Mat2uTranspose                  Mat2TransposeStd
#define Mat2uMultiplyVecBlock           Mat2MultiplyVecBlockStd

#define Mat2RotateLH                    Mat2RotateLHStd
#define Mat2RotateRH                    Mat2RotateRHStd
#define Mat2Rotate                      Mat2RotateStd
#define Mat2Scale                       Mat2ScaleStd

#define Mat3Copy                        Mat3CopyStd
#define Mat3Identity                    Mat3IdentityStd

#define Mat3Negate                      Mat3NegateStd
#define Mat3Add                         Mat3AddStd
#define Mat3AddFloat                    Mat3AddFloatStd
#define Mat3Subtract                    Mat3SubtractStd
#define Mat3SubtractFloat               Mat3SubtractFloatStd

#define Mat3Multiply                    Mat3MultiplyStd
#define Mat3MultiplyIdentityByBlocks    Mat3MultiplyIdentityByBlocksStd

#define Mat3MultiplyVec                 Mat3MultiplyVecStd
#define Mat3MultiplyVecBlock            Mat3MultiplyVecBlockStd
#define Mat3MulVecBlockBySize           Mat3MulVecBlockBySizeStd
#define Mat3MulVec3BufByBuf             Mat3MulVec3BufByBufStd
#define Mat3MultiplyFloat               Mat3MultiplyFloatStd
#define Mat3Inverse                     Mat3InverseStd
#define Mat3Transpose                   Mat3TransposeStd

#define Mat3MultiplyFPU                 Mat3MultiplyStd
#define Mat3MultiplyIdentityByBlockFPU  Mat3MultiplyIdentityByBlocksStd

#define Mat3uNegate                     Mat3NegateStd
#define Mat3uAdd                        Mat3AddStd
#define Mat3uSubtract                   Mat3SubtractStd

#define Mat3uMultiply                   Mat3MultiplyStd
#define Mat3uMultiplyIdentityByBlocks   Mat3MultiplyIdentityByBlocksStd

#define Mat3uMultiplyVec                Mat3MultiplyVecStd
#define Mat3uMultiplyVecBlock           Mat3MultiplyVecBlockStd
#define Mat3uMulVecBlockBySize          Mat3MulVecBlockBySizeStd
#define Mat3uMulVec3BufByBuf            Mat3MulVec3BufByBufStd
#define Mat3uMultiplyFloat              Mat3MultiplyFloatStd
#define Mat3uInverse                    Mat3InverseStd
#define Mat3uTranspose                  Mat3TransposeStd

#define Mat3RotateRHX                   Mat3RotateRHX_Std
#define Mat3RotateLHX                   Mat3RotateLHX_Std
#define Mat3RotateRHY                   Mat3RotateRHY_Std
#define Mat3RotateLHY                   Mat3RotateLHY_Std
#define Mat3RotateRHZ                   Mat3RotateRHZ_Std
#define Mat3RotateLHZ                   Mat3RotateLHZ_Std

#define Mat3RotateRHXY                  Mat3RotateRHXY_Std
#define Mat3RotateLHXY                  Mat3RotateLHXY_Std
#define Mat3RotateRHXZ                  Mat3RotateRHXZ_Std
#define Mat3RotateLHXZ                  Mat3RotateLHXZ_Std
#define Mat3RotateRHYZ                  Mat3RotateRHYZ_Std
#define Mat3RotateLHYZ                  Mat3RotateLHYZ_Std

#define Mat3RotateRHXYZ                 Mat3RotateRHXYZ_Std
#define Mat3RotateLHXYZ                 Mat3RotateLHXYZ_Std

#define Mat3Scale                       Mat3ScaleStd
#define Mat3ScaleByVec3                 Mat3ScaleByVec3Std

#if 0
//#define Mat3RotateTempSaveRHXYZ         Mat3RotateTempSaveRHXYZ_Std

#define Mat4TranslateRH                 Mat4TranslateRH_Std
#define Mat4TranslateRH_FPU             Mat4TranslateRH_Std
#endif


#define Mat4Copy                        Mat4CopyStd

#define Mat4Negate                      Mat4NegateStd
#define Mat4NegateMatrix                Mat4NegateMatrixStd
#define Mat4Add                         Mat4AddStd
#define Mat4AddFloat                    Mat4AddFloatStd
#define Mat4AddMatrix                   Mat4AddMatrixStd
#define Mat4Subtract                    Mat4SubtractStd
#define Mat4SubtractFloat               Mat4SubtractFloatStd
#define Mat4SubtractMatrix              Mat4SubtractMatrixStd
#define Mat4MultiplyMatrix              Mat4MultiplyStd
#define Mat4Multiply                    Mat4MultiplyStd
#define Mat4MultiplyVec                 Mat4MultiplyVecStd

#define Mat4MultiplyFloat               Mat4MultiplyFloatStd
#define Mat4Transpose                   Mat4TransposeStd
#define Mat4ShadowMatrix                Mat4ShadowMatrixStd
#define Mat4MirrorMatrix                Mat4MirrorMatrixStd
#define Mat4LookAt                      Mat4LookAtStd
#define Mat4GlToD3DProjMat              Mat4GlToD3DProjMatStd
#define Mat4LookAtLH                    Mat4LookAtLHStd

#define Mat4uNegate                     Mat4NegateStd
#define Mat4uNegateMatrix               Mat4NegateMatrixStd
#define Mat4uAdd                        Mat4AddStd
#define Mat4uAddFloat                   Mat4AddFloatStd
#define Mat4uAddMatrix                  Mat4AddMatrixStd
#define Mat4uSubtract                   Mat4SubtractStd
#define Mat4uSubtractFloat              Mat4SubtractFloatStd
#define Mat4uSubtractMatrix             Mat4SubtractMatrixStd
#define Mat4uMultiplyMatrix             Mat4MultiplyStd
#define Mat4uMultiply                   Mat4MultiplyStd
#define Mat4uMultiplyVec                Mat4MultiplyVecStd

#define Mat4LookAt                      Mat4LookAtStd
#define Mat4uLookAt                     Mat4LookAtStd
#define Mat4saLookAt                    Mat4LookAtStd
#define Mat4suLookAt                    Mat4LookAtStd

#define Mat4uMultiplyFloat              Mat4MultiplyFloatStd
#define Mat4uTranspose                  Mat4TransposeStd
#define Mat4uShadowMatrix               Mat4ShadowMatrixStd
#define Mat4uMirrorMatrix               Mat4MirrorMatrixStd
#define Mat4uLookAt                     Mat4LookAtStd
#define Mat4uGlToD3DProjMat             Mat4GlToD3DProjMatStd
#define Mat4uLookAtLH                   Mat4LookAtLHStd

#define Mat4Identity                    Mat4IdentityStd
#define Mat4Scale                       Mat4ScaleStd

#define Mat4RotateRHX                   Mat4RotateRHX_Std
#define Mat4RotateLHX                   Mat4RotateLHX_Std
#define Mat4RotateRHY                   Mat4RotateRHY_Std
#define Mat4RotateLHY                   Mat4RotateLHY_Std
#define Mat4RotateRHZ                   Mat4RotateRHZ_Std
#define Mat4RotateLHZ                   Mat4RotateLHZ_Std

#define Mat4RotateRHXY                  Mat4RotateRHXY_Std
#define Mat4RotateLHXY                  Mat4RotateLHXY_Std
#define Mat4RotateRHXZ                  Mat4RotateRHXZ_Std
#define Mat4RotateLHXZ                  Mat4RotateLHXZ_Std
#define Mat4RotateRHYZ                  Mat4RotateRHYZ_Std
#define Mat4RotateLHYZ                  Mat4RotateLHYZ_Std

#define Mat4RotateRHXYZ                 Mat4RotateRHXYZ_Std
#define Mat4RotateLHXYZ                 Mat4RotateLHXYZ_Std

#define Mat4TranslateRH                 Mat4TranslateRH_Std
#define Mat4TranslateLH                 Mat4TranslateLH_Std
#define Mat4TranslateRH_Vec3            Mat4TranslateRH_Vec3Std
#define Mat4TranslateLH_Vec3            Mat4TranslateLH_Vec3Std
#define Mat4TranslateRH_Vec4            Mat4TranslateRH_Vec4Std
#define Mat4TranslateLH_Vec4            Mat4TranslateLH_Vec4Std
#define Mat4OrthoMatrix                 Mat4OrthoMatrixStd
#define Mat4OrthoStruct                 Mat4OrthoStructStd
#define Mat4Perspective                 Mat4PerspectiveStd
#define Mat4PerspectiveX                Mat4PerspectiveXStd
#define Mat4CubemapMatrix               Mat4CubemapMatrixStd
#define Mat4CubemapProjectionMat        Mat4CubemapProjectionMatStd
#define Mat4LookAtHorizAsm              Mat4LookAtHorizStd

#define Mat3RotationFromMat4            Mat3RotationFromMat4Std
#define Mat4FromMat3                    Mat4FromMat3Std

#if 0
#define MatMultiply3x3                  MatMultiply3x3Std
#define MatMultiply4x4                  MatMultiply4x4Std
#define MatMultiply4x4Matrix            MatMultiply4x4MatrixStd
#define MatMultiplyVec4x4               MatMultiplyVec4x4Std
#endif

// XXX: Add these to the library

#define QuaternionAdd                   QuaternionAddStd
#define QuaternionMultiply              QuaternionMultiplyStd
#define QuaternionInverse               QuaternionInverseStd
#define QuaternionToMat3                QuaternionToMat3Std

#define QuaternionNormalizeFlat         QuaternionNormalizeStd
#define QuaternionDotFlat               QuaternionDotStd

#define QuaternionNormalize             QuaternionNormalizeStd
#define QuaternionDot                   QuaternionDotStd

#define QuaternionDotFPU                QuaternionDotStd

#define uQuaternionAdd                  QuaternionAddStd
#define uQuaternionMultiply             QuaternionMultiplyStd
#define uQuaternionInverse              QuaternionInverseStd
#define uQuaternionToMat3               QuaternionToMat3Std

#define uQuaternionNormalizeFlat        QuaternionNormalizeStd
#define uQuaternionDotFlat              QuaternionDotStd

#define uQuaternionNormalize            QuaternionNormalizeStd
#define uQuaternionDot                  QuaternionDotStd

#define QuaternionFromAxis              QuaternionFromAxisStd
#define QuaternionFromMat3              QuaternionFromMat3Std
#define QuaternionFromMat4              QuaternionFromMat4Std
#define QuaternionToMat4                QuaternionToMat4Std
#define QuaternionSlerp                 QuaternionSlerpStd
#define QuaternionCos                   QuaterionCosStd
#define QuaternionSin                   QuaternionSinStd

#endif

#if defined(__cplusplus)
#define __C "C"
#else
#define __C
#endif

// Single-Precision methods
//

extern __C void  GetFpuStatusStd(unsigned short* uStatus);
extern __C void  ClearFpuStatusStd(unsigned short* uStatus);

extern __C float FloatLerpStd   (const float u,const float v,const float x);
extern __C void  FloatLerpPtrStd(float* r,const float* pu,const float* pv,const float* px);
extern __C float FloatSqrStd    (const float x);
extern __C float FloatSqrPtrStd (const float* px);

// 2-Dimensional Vector Copy Methods
//

extern __C void  Vec2CopyStd            (vec2* r,const vec2* v);
extern __C void  Vec2CopyBlockStd       (vec2* r,const vec2*  v,   const int32_t nCount);
extern __C void  BuildVec2PackedArrayStd(vec2* r,const vec2** base,const int32_t nCount);

// Basic 2-Dimensional Vector - Single-Precision Scalar Methods
//

extern __C void  Vec2AddFloatStd         (vec2* r,const vec2* u,const float s);
extern __C void  Vec2SubtractFloatStd    (vec2* r,const vec2* u,const float s);
extern __C void  Vec2MultiplyFloatStd    (vec2* r,const vec2* u,const float s);
extern __C void  Vec2FloatMultiplyStd    (vec2* r,const float s,const vec2* v);
extern __C void  Vec2DivideFloatStd      (vec2* r,const vec2* u,const float s);

// Basic 2-Dimensional Vector Array - Single-Precision Scalar Methods
//

extern __C void Vec2AddFloatToBlockStd        (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2AddFloatToBlockSizeStd    (vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBlockStd     (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBufStd       (void*  r,const int32_t iRSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

extern __C void Vec2SubtractFloatFromBlockStd    (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2SubFloatFromBlockSizeStd     (void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBlkSizeStd    (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBufStd        (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

extern __C void Vec2MultiplyBlockByFloatStd      (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2MultiplyBlkByFloatSizeStd    (void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatSizeStd    (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatBufStd     (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

extern __C void Vec2DivideBlockByFloatStd        (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2DivideBlockByFloatSizeStd    (void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockByFloatSizeStd    (void* r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufByFloatStd          (void* r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

// Basic 2-Dimensional Vector Methods
//

extern __C void  Vec2NegateStd  (vec2* r,const vec2* u);
extern __C void  Vec2AddStd     (vec2* r,const vec2* u,const vec2* v);
extern __C void  Vec2SubtractStd(vec2* r,const vec2* u,const vec2* v);
extern __C void  Vec2MultiplyStd(vec2* r,const vec2* u,const vec2* v);
extern __C void  Vec2DivideStd  (vec2* r,const vec2* u,const vec2* v);

extern __C void  Vec2EqualsStd   (int32_t* iFlag,const vec2* u,const vec2* v);
extern __C void  Vec2NotEqualsStd(int32_t* iFlag,const vec2* u,const vec2* v);

// Basic 2-Dimensional Vector - 2-Dimensional Vector Array Methods
//

extern __C void Vec2NegateBlockStd         (vec2* rv,const int32_t nCount);
extern __C void Vec2NegateBlockBySizeStd   (void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBlockBySizeStd(void*  r,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBufBySizeStd  (void*  r,const int32_t iDstSize,const vec2* v,const int32_t iSrcSize,const int32_t iCount);

extern __C void Vec2AddVec2ToBlockStd         (vec2* ru,const vec2* v,const int32_t iCount);
extern __C void Vec2AddBlockToBlockStd        (vec2* ru,const vec2* v,const int32_t iCount);
extern __C void Vec2BufAddVec2ToBlockBySizeStd(void*  r,const void* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBlockBySizeStd      (void*  r,const vec2* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBufBySizeStd        (void*  r,const int32_t iSaveSize,const void* u,const int32_t iSrcSize0,const void* v,const int32_t iSrcSize1,const int32_t iCount);

extern __C void Vec2SubtractVec2FromBlockStd  (vec2* pDest,vec2* pVector,int32_t nCount);
extern __C void Vec2SubtractBlockFromBlockStd (vec2* pDest,vec2* pSource,int32_t nCount);
extern __C void Vec2BufSubVec2FromBlkBySizeStd(void* r,const void* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBlockBySizeStd      (void* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBufBySizeStd        (void* r,const int32_t iSaveSize,const void* u,const int32_t iSrcSize0,const void* v,const int32_t iSrcSize1,const int32_t iCount);

// Basic 2-Dimensional Vector Array - 2-Dimensional Vector Array Methods
//

extern __C void Vec2MultiplyBlockByVec2Std  (vec2* pDest,vec2* pVector,int32_t nCount);
extern __C void Vec2MultiplyBlockByBlockStd (vec2* pDest,vec2* pSource,int32_t nCount);
extern __C void Vec2BufMulVec2ByBlockSizeStd(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockBySizeStd    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBufBySizeStd      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

// Basic 2-Dimensional Vector Array - 2-Dimensional Vector Array Methods
//

extern __C void Vec2DivideBlockByVec2Std    (vec2* pDest,vec2* pVector,int32_t nCount);
extern __C void Vec2DivideBlockByBlockStd   (vec2* pDest,vec2* pSource,int32_t nCount);
extern __C void Vec2BufDivVec2ByBlockSizeStd(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockBySizeStd    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufBySizeStd      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iUSize,const vec2* v,const int32_t iVSize1,const int32_t iCount);

// Fundamental 2-Dimensional Vector Methods
//

extern __C void  Vec2LerpStd     (vec2*  r,const vec2* u,const vec2* v,const float step);
extern __C void  Vec2SqrStd      (vec2*  r,const vec2* u);
extern __C void  Vec2SqrtStd     (vec2*  r,const vec2* u);
extern __C void  Vec2NormalizeStd(vec2*  r,const vec2* v);
extern __C void  Vec2DotStd      (float* r,const vec2* u,const vec2* v);
extern __C void  Vec2LengthStd   (float* r,const vec2* v);

// Fundamental 2-Dimensional Vector Array Methods
//

extern __C void  Vec2LerpBlockStd     (vec2*  r,const vec2* u,const vec2* v,const float step,const int32_t iCount);
extern __C void  Vec2SqrBlockStd      (vec2*  r,const vec2* v,const int32_t iCount);
extern __C void  Vec2SqrtBlockStd     (vec2*  r,const vec2* v,const int32_t iCount);
extern __C void  Vec2NormalizeBlockStd(vec2*  r,const vec2* v,const int32_t iCount);
extern __C void  Vec2DotBlockStd      (float* r,const vec2* u,const vec2* v,const int32_t iCount);
extern __C void  Vec2LengthBlockStd   (float* r,const vec2* v,const int32_t iCount);

extern __C void Vec2BufLerpBufStd     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);
extern __C void Vec2BufSqrBufStd      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufSqrtBufStd     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufNormalizeBufStd(void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufDotBufStd      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Vec2BufLengthBufStd   (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

// Fundamental 3-Dimensional Vector Scalar Methods 
//

extern __C void Vec3CopyStd(vec3* pDest,const vec3* pSource);
extern __C void Vec3CopyBlockStd(vec3* pDest,const vec3* pSource,const int32_t iCount);
extern __C void BuildVec3PackedArrayStd(vec3* r,const vec3** pSrc,const int32_t iCount);

extern __C void Vec3AddFloatStd             (vec3*  r,const vec3* u,const float s);
extern __C void Vec3AddFloatToBlockStd      (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3AddFloatToBlockBySizeStd(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddFloatToBlockStd   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddFloatToBufStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

extern __C void Vec3SubtractFloatStd          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3SubtractFloatFromBlockStd (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3SubFloatFromBlockBySizeStd(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubFloatFromBlockStd   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubFloatFromBufStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

extern __C void Vec3MultiplyFloatStd        (vec3*  r,const vec3* u,const float s);
extern __C void Vec3MultiplyFloatToBlockStd (vec3* ru,const float s,const int32_t iCount);
extern __C void Vec3MulFloatToBlockBySizeStd(void* ru,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulFloatToBlockStd   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulFloatToBufStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

extern __C void Vec3DivideFloatStd          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3DivideBlockByFloatStd   (vec3* ru,const float s,const int32_t iCount);
extern __C void Vec3DivBlockByFloatBySizeStd(void* ru,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBlockByFloatStd   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByFloatStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

// Fundamental 3-Dimensional Vector-Scalar Array Methods

extern __C void Vec3EqualsStd   (int32_t* iFlag,const vec3* u,const vec3* v);
extern __C void Vec3NotEqualsStd(int32_t* iFlag,const vec3* u,const vec3* v);

extern __C void Vec3NegateStd           (vec3*  r,const vec3* v);
extern __C void Vec3NegateBlockStd      (vec3* ru,const int32_t iCount);
extern __C void Vec3NegateBlockBySizeStd(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNegateBlockStd   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNegateBufStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec3AddStd                  (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3AddVecToBlockStd        (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3AddVecToBlockBySizeStd  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddVecToBlockStd     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddVecToBufStd       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3AddBlockToBlockStd      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3AddBlockToBlockBySizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddBlockToBufStd     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddBufToBufStd       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec3SubtractStd               (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3SubVecFromBlockStd        (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3SubVecFromBlockBySizeStd  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubVecFromBlockStd     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubVecFromBufStd       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3SubBlockFromBlockStd      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3SubBlockFromBlockBySizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubBlockFromBufStd     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubBufFromBufStd       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec3MultiplyStd              (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3MulBlockByVecStd         (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3MulBlockByVecUseSizeStd  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByVecStd        (void*  r,const void* u,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByVecUseSizeStd (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3MulBlockByBlockStd       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3MulBlockByBlockUseSizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByBlockStd      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByBufStd        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec3DivideStd                (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3DivBlockByVecStd         (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3DivBlockByVecUseSizeStd  (void* ru,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByVecStd        (void*  r,const void* u,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByVecUseSizeStd (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByBlockStd       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByBlockUseSizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByBlockStd      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByBufStd        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec3LerpStd         (vec3*  r,const vec3* u,const vec3* v,const float s);
extern __C void Vec3LerpBlockStd    (vec3* ru,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec3LerpBlockUseSizeStd(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLerpBlockStd (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec3BufLerpBufStd   (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

extern __C void Vec3DotStd            (float* r,const vec3* u,const vec3* v);
extern __C void Vec3DotBlockStd       (float* r,const vec3* u,const vec3* v,const int32_t iCount);
extern __C void Vec3DotBlockUseSizeStd(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDotBufStd      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec3SqrStd            (vec3*  r,const vec3* v);
extern __C void Vec3SqrBlockStd       (vec3* ru,const int32_t iCount);
extern __C void Vec3SqrBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSqrBufStd      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec3SqrtStd            (vec3*  r,const vec3* v);
extern __C void Vec3SqrtBlockStd       (vec3* ru,const int32_t iCount);
extern __C void Vec3SqrtBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSqrtBufStd      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec3NormalizeStd            (vec3*  r,const vec3* u);
extern __C void Vec3NormalizeBlockStd       (vec3* ru,const int32_t iCount);
extern __C void Vec3NormalizeBlockUseSizeStd(vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNormalizeBufStd      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec3LengthStd            (float* r,const vec3* v);
extern __C void Vec3LengthBlockStd       (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3LengthBlockUseSizeStd(float* r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLengthBufStd      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec3CrossStd            (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3CrossBlockStd       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3CrossBlockUseSizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufCrossBufStd      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec3ReflectStd(vec3* r,const vec3* u,const vec3* v);

// Fundamental 4-Dimensional Vector Scalar Methods 
//

extern __C void Vec4CopyStd(vec4* pDest,const vec4* pSource);
extern __C void Vec4CopyBlockStd(vec4* pDest,const vec4* pSource,const int32_t iCount);
extern __C void BuildVec4PackedArrayStd(vec4* r,const vec4** pSrc,const int32_t iCount);

extern __C void Vec4AddFloatStd             (vec4*  r,const vec4* u,const float s);
extern __C void Vec4AddFloatToBlockStd      (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4AddFloatToBlockBySizeStd(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddFloatToBlockStd   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddFloatToBufStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

extern __C void Vec4SubtractFloatStd          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4SubtractFloatFromBlockStd (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4SubFloatFromBlockBySizeStd(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubFloatFromBlockStd   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubFloatFromBufStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

extern __C void Vec4MultiplyFloatStd        (vec4*  r,const vec4* u,const float s);
extern __C void Vec4MultiplyFloatToBlockStd (vec4* ru,const float s,const int32_t iCount);
extern __C void Vec4MulFloatToBlockBySizeStd(void* ru,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulFloatToBlockStd   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulFloatToBufStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

extern __C void Vec4DivideFloatStd          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4DivideBlockByFloatStd   (vec4* ru,const float s,const int32_t iCount);
extern __C void Vec4DivBlockByFloatBySizeStd(void* ru,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBlockByFloatStd   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByFloatStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

// Fundamental 3-Dimensional Vector-Scalar Array Methods

extern __C void Vec4EqualsStd   (int32_t* iFlag,const vec4* u,const vec4* v);
extern __C void Vec4NotEqualsStd(int32_t* iFlag,const vec4* u,const vec4* v);

extern __C void Vec4NegateStd           (vec4*  r,const vec4* v);
extern __C void Vec4NegateBlockStd      (vec4* ru,const int32_t iCount);
extern __C void Vec4NegateBlockBySizeStd(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNegateBlockStd   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNegateBufStd     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec4AddStd                  (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4AddVecToBlockStd        (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4AddVecToBlockBySizeStd  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddVecToBlockStd     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddVecToBufStd       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4AddBlockToBlockStd      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4AddBlockToBlockBySizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddBlockToBufStd     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddBufToBufStd       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec4SubtractStd               (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4SubVecFromBlockStd        (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4SubVecFromBlockBySizeStd  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubVecFromBlockStd     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubVecFromBufStd       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4SubBlockFromBlockStd      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4SubBlockFromBlockBySizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubBlockFromBufStd     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubBufFromBufStd       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec4MultiplyStd              (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4MulBlockByVecStd         (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4MulBlockByVecUseSizeStd  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByVecStd        (void*  r,const void* u,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByVecUseSizeStd (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4MulBlockByBlockStd       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4MulBlockByBlockUseSizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByBlockStd      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByBufStd        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec4DivideStd                (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4DivBlockByVecStd         (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4DivBlockByVecUseSizeStd  (void* ru,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByVecStd        (void*  r,const void* u,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByVecUseSizeStd (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByBlockStd       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByBlockUseSizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByBlockStd      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByBufStd        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec4LerpStd            (vec4*  r,const vec4* u,const vec4* v,const float s);
extern __C void Vec4LerpBlockStd       (vec4* ru,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4LerpBlockUseSizeStd(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLerpBlockStd    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4BufLerpBufStd      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

extern __C void Vec4DotStd            (float* r,const vec4* u,const vec4* v);
extern __C void Vec4DotBlockStd       (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4DotBlockUseSizeStd(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDotBufStd      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Vec4SqrStd            (vec4*  r,const vec4* v);
extern __C void Vec4SqrBlockStd       (vec4* ru,const int32_t iCount);
extern __C void Vec4SqrBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSqrBufStd      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec4SqrtStd            (vec4*  r,const vec4* v);
extern __C void Vec4SqrtBlockStd       (vec4* ru,const int32_t iCount);
extern __C void Vec4SqrtBlockUseSizeStd(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSqrtBufStd      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec4NormalizeStd            (vec4*  r,const vec4* u);
extern __C void Vec4NormalizeBlockStd       (vec4* ru,const int32_t iCount);
extern __C void Vec4NormalizeBlockUseSizeStd(vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNormalizeBufStd      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec4LengthStd         (float* r,const vec4* v);
extern __C void Vec4LengthBlockStd    (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4LengthBlockUseSizeStd(float* r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLengthBufStd   (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

extern __C void Vec4CrossStd            (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4CrossBlockStd       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4CrossBlockUseSizeStd(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufCrossBufStd      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Mat2IdentityStd              (mat2*  r);
extern __C void Mat2NegateStd                (mat2*  r,const mat2* m);
extern __C void Mat2AddStd                   (mat2*  r,const mat2* m,const mat2* n);
extern __C void Mat2AddFloatStd              (mat2*  r,const mat2* m,const float s);
extern __C void Mat2SubtractStd              (mat2*  r,const mat2* m,const mat2* n);
extern __C void Mat2SubtractFloatStd         (mat2*  r,const mat2* m,const float s);
extern __C void Mat2MultiplyStd              (mat2*  r,const mat2* m,const mat2* n);
extern __C void Mat2MultiplyVecStd           (vec2*  r,const mat2* m,const vec2* v);
extern __C void Mat2MultiplyFloatStd         (mat2*  r,const mat2* m,const float s);
extern __C void Mat2TransposeStd             (mat2*  r,const mat2* m);

extern __C void Mat2RotateLHStd              (mat2*  r,const float angle);
extern __C void Mat2RotateRHStd              (mat2*  r,const float angle);
extern __C void Mat2RotateStd                (mat2*  r,const float angle);

extern __C void Mat2ScaleStd                 (mat2*  r,const float x_scale,const float y_scale);
extern __C void Mat2MultiplyVecBlockStd      (vec2*  r,const mat2* m,const vec2* v,const int32_t nCount);

extern __C void Mat3CopyStd(mat3* r,const mat3* m);
extern __C void Mat3IdentityStd(mat3* r);
extern __C void Mat3NegateStd(mat3* r,const mat3* m);
extern __C void Mat3AddStd(mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3AddFloatStd(mat3* r,const mat3* m,const float s);
extern __C void Mat3SubtractStd(mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3SubtractFloatStd(mat3* r,const mat3* m,const float s);
extern __C void Mat3MultiplyStd(mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3Multiply3x3Std(mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3MultiplyIdentityByBlocksStd(mat3* r,const mat3** m,int32_t nCount);
extern __C void Mat3MultiplyVecStd(vec3* r,const mat3* m,const vec3* v);
extern __C void Mat3MultiplyVecBlockStd(vec3* r,const mat3* m,const vec3* v,int32_t nCount);
extern __C void Mat3MulVecBlockBySizeStd(void* r,const mat3* m,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Mat3MulVec3BufByBufStd(void* r,const int32_t iRSize,const mat3* m,const void* v,const int32_t iVSize,const int32_t iCount);

extern __C void Mat3MultiplyFloatStd(mat3* r,const mat3* m,const float x);
extern __C void Mat3InverseStd(mat3* r,const mat3* m); // XXX: See notes
extern __C void Mat3TransposeStd(mat3* r,const mat3*m);
extern __C void Mat3RotateRHX_Std(mat3* r,const float angle);
extern __C void Mat3RotateLHX_Std(mat3* r,const float angle);
extern __C void Mat3RotateRHY_Std(mat3* r,const float angle);
extern __C void Mat3RotateLHY_Std(mat3* r,const float angle);
extern __C void Mat3RotateRHZ_Std(mat3* r,const float angle);
extern __C void Mat3RotateLHZ_Std(mat3* r,const float angle);
extern __C void Mat3RotateRHXY_Std(mat3* r,const float x_angle,const float y_angle);
extern __C void Mat3RotateLHXY_Std(mat3* r,const float x_angle,const float y_angle);
extern __C void Mat3RotateRHXZ_Std(mat3* r,const float x_angle,const float z_angle);
extern __C void Mat3RotateLHXZ_Std(mat3* r,const float x_angle,const float z_angle);
extern __C void Mat3RotateRHYZ_Std(mat3* r,const float y_angle,const float z_angle);
extern __C void Mat3RotateLHYZ_Std(mat3* r,const float y_angle,const float z_angle);

extern __C void Mat3RotateRHXYZ_Std(mat3* r,const float x,const float y,const float z);
extern __C void Mat3RotateLHXYZ_Std(mat3* r,const float x,const float y,const float z);
extern __C void Mat3ScaleStd(mat3* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat3ScaleByVec3Std(mat3* r,const vec3* v);
extern __C void Mat4CopyStd(mat4* r,const mat4* m);
extern __C void Mat4IdentityStd(mat4* r);
extern __C void Mat4NegateMatrixStd(mat4* r);
extern __C void Mat4NegateStd(mat4* r,mat4* m);
extern __C void Mat4AddMatrixStd(mat4* m,const mat4* n);
extern __C void Mat4AddStd(mat4* r,mat4* m,const mat4* n);
extern __C void Mat4AddFloatStd(mat4* r,const mat4* m,const float s);
extern __C void Mat4SubtractMatrixStd(mat4* m,const mat4* n);
extern __C void Mat4SubtractStd(mat4* r,mat4* m,const mat4* n);
extern __C void Mat4SubtractFloatStd(mat4* r,const mat4* m,const float s);
extern __C void Mat4MultiplyStd(mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4MulStd(mat4* r,const mat4* m,const mat4* n);
extern __C void MatMultiplyVec4x4Std(vec4* r,const mat4* m,const vec4* v);
extern __C void Mat4MultiplyVecStd(vec4* r,const mat4* m,const vec4* v);
extern __C void Mat4MultiplyFloatStd(mat4* r,const mat4* m,const float x);
extern __C void Mat4TransposeStd(mat4* r,const mat4* m);
extern __C void Mat4ScaleStd(mat4* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat4RotateRHX_Std(mat4* r,const float angle);
extern __C void Mat4RotateLHX_Std(mat4* r,const float angle);
extern __C void Mat4RotateRHY_Std(mat4* r,const float angle);
extern __C void Mat4RotateLHY_Std(mat4* r,const float angle);
extern __C void Mat4RotateRHZ_Std(mat4* r,const float angle);
extern __C void Mat4RotateLHZ_Std(mat4* r,const float angle);
extern __C void Mat4RotateRHXY_Std(mat4* r,const float x_angle,const float y_angle);
extern __C void Mat4RotateLHXY_Std(mat4* r,const float x_angle,const float y_angle);
extern __C void Mat4RotateRHXZ_Std(mat4* r,const float x_angle,const float z_angle);
extern __C void Mat4RotateLHXZ_Std(mat4* r,const float x_angle,const float z_angle);
extern __C void Mat4RotateRHYZ_Std(mat4* r,const float y_angle,const float z_angle);
extern __C void Mat4RotateLHYZ_Std(mat4* r,const float y_angle,const float z_angle);
extern __C void Mat4RotateRHXYZ_Std(mat4* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat4RotateLHXYZ_Std(mat4* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat4TranslateRH_Std(mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateLH_Std(mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateRH_Vec3Std(mat4* r,const vec3* v);
extern __C void Mat4TranslateLH_Vec3Std(mat4* r,const vec3* v);
extern __C void Mat4TranslateRH_Vec4Std(mat4* r,const vec4* v);
extern __C void Mat4TranslateLH_Vec4Std(mat4* r,const vec4* v);
extern __C void Mat4OrthoMatrixStd(mat4* r,
				   const float left,
				   const float right,
				   const float top,
				   const float bottom,
				   const float z_near,
				   const float z_far,
				   const int32_t d3dFlag);
extern __C void Mat4OrthoStructStd(mat4* r,const struct orthoMatrix* s);
extern __C void Mat4PerspectiveStd(mat4*          r,
                                   const float    fov,
                                   const float    width,
                                   const float    height,
                                   const float    zNear,
                                   const float    zFar,
                                   const uint32_t d3dflag);
extern __C void Mat4PerspectiveXStd(mat4* r,const struct perspectiveMatrix* s);
extern __C void Mat4ShadowMatrixStd(mat4*       r,
                                    const vec3* planeNormal,
                                    const float planeOffset,
                                    const vec3* lightPos);
extern __C void Mat4MirrorMatrixStd        (mat4* r,const vec3* planeNormal,const float planeOffset);
extern __C void Mat4CubemapMatrixStd       (mat4* r,const unsigned int face);
extern __C void Mat4CubemapProjectionMatStd(mat4* r,const float zNear,const float zFar,const uint32_t d3dflag);
extern __C void Mat4LookAtStd              (mat4* r,const vec3* from,const vec3* at);
extern __C void Mat4GlToD3DProjMatStd      (mat4* r,const mat4* m);
extern __C void Mat4LookAtLHStd            (mat4* r,vec3* pEye,vec3* pLookAt,vec3* pUp);

#if 0
extern __C void MatMultiply3x3Std          (mat3* m,const mat3* n);
extern __C void MatMultiply4x4Std          (mat4* r,mat4* m,const mat4* n);
extern __C void MatMultiply4x4MatrixStd    (mat4* m,const mat4* n);
extern __C void MatMultiplyVec4x4Std       (vec4* r,const mat4* m,const vec4* v);
#endif

extern __C void Mat3RotationFromMat4Std  (mat3* r,const mat4* m);
extern __C void Mat4FromMat3Std            (mat4* r,const mat3* m);

extern __C void QuaternionAddStd           (quaternion* r,const quaternion* q,const quaternion* v);
extern __C void QuaternionMultiplyStd      (quaternion* r,const quaternion* q,const quaternion* v);
extern __C void QuaternionInverseStd       (quaternion* q,const quaternion* u);
extern __C void QuaternionToMat3Std        (mat3* m,const quaternion* q);

extern __C void QuaternionNormalizeStd     (quaternion* r,const quaternion* q);
extern __C void QuaternionDotStd           (float* r,const quaternion* q,const quaternion* v);

extern __C void QuaternionFromAxisStd      (quaternion* q,const vec3* axis,const float angle);
extern __C void QuaternionFromMat3Std      (quaternion* q,const mat3* m);
extern __C void QuaternionFromMat4Std      (quaternion* q,const mat4* m);
extern __C void QuaternionToMat4Std        (mat4* m,const quaternion* q);
#if 0
extern __C void QuaternionDotStd           (quaternion* r,const quaternion* q,const quaternion* v);
#endif
extern __C void QuaternionSlerpStd         (quaternion* r,const float s,const quaternion* q,const quaternion* v);

extern __C void QuaterionCosStd            (float* r,const quaternion* q,const quaternion* p);
extern __C void QuaternionSinStd           (float* r,const quaternion* q,const quaternion* p);

#endif
