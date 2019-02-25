/* ============= *
 * VectorAsm     *
 * ==============*======================================================== *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ======================================================================= */

#ifndef __VECASM_H
#define __VECASM_H

#if defined(__cplusplus)
#define __C "C"
#else
#define __C
#endif

/* ------------- *
 * linux macros  *
 * --------------*-------------------------------------------------------- *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__linux__)
#define GetFpuStatusAsm                    _GetFpuStatusAsm
#define ClearFpuStatusAsm                  _ClearFpuStatusAsm

#define FloatLerpAsm                       _FloatLerpAsm
#define FloatLerpPtrAsm                    _FloatLerpPtrAsm
#define FloatSqrAsm                        _FloatSqrAsm
#define FloatSqrPtrAsm                     _FloatSqrPtrAsm

#define fCosAsm                            _fCosAsm
#define CosAsm                             _CosAsm
#define AfCosAsm                           _AfCosAsm
#define ACosAsm                            _ACosAsm
#define fSinAsm                            _fSinAsm
#define SinAsm                             _SinAsm
#define AfSinAsm                           _AfSinAsm
#define ASinAsm                            _ASinAsm
#define fTanAsm                            _fTanAsm
#define TanAsm                             _TanAsm
#define AfTanAsm                           _AfTanAsm
#define ATanAsm                            _ATanAsm

#define Vec2CopyAsm                        _Vec2CopyAsm
#define Vec2CopyBlockAsm                   _Vec2CopyBlockAsm
#define BuildVec2PackedArrayAsm            _BuildVec2PackedArrayAsm

#define Vec2AddFloatAsm                    _Vec2AddFloatAsm
#define Vec2SubtractFloatAsm               _Vec2SubtractFloatAsm
#define Vec2MultiplyFloatAsm               _Vec2MultiplyFloatAsm
#define Vec2FloatMultiplyAsm               _Vec2FloatMultiplyAsm
#define Vec2DivideFloatAsm                 _Vec2DivideFloatAsm

#define Vec2AddFloatFPU_Asm                _Vec2AddFloatFPU_Asm
#define Vec2SubtractFloatFPU_Asm           _Vec2SubtractFloatFPU_Asm
#define Vec2MultiplyFloatFPU_Asm           _Vec2MultiplyFloatFPU_Asm
#define Vec2FloatMultiplyFPU_Asm           _Vec2FloatMultiplyFPU_Asm
#define Vec2DivideFloatFPU_Asm             _Vec2DivideFloatFPU_Asm

#define Vec2AddFloatToBlockAsm             _Vec2AddFloatToBlockAsm
#define Vec2uAddFloatToBlockAsm            _Vec2uAddFloatToBlockAsm

#define Vec2AddFloatToBlockSizeAsm         _Vec2AddFloatToBlockSizeAsm
#define Vec2BufAddFloatToBlockAsm          _Vec2BufAddFloatToBlockAsm
#define Vec2BufAddFloatToBufAsm            _Vec2BufAddFloatToBufAsm

#define Vec2AddFloatToBlockFPU_Asm         _Vec2AddFloatToBlockFPU_Asm
#define Vec2AddFloatToBlockSizeFPU_Asm     _Vec2AddFloatToBlockSizeFPU_Asm
#define Vec2BufAddFloatToBlockFPU_Asm      _Vec2BufAddFloatToBlockFPU_Asm
#define Vec2BufAddFloatToBufFPU_Asm        _Vec2BufAddFloatToBufFPU_Asm

#define Vec2SubtractFloatFromBlockAsm      _Vec2SubtractFloatFromBlockAsm
#define Vec2uSubtractFloatFromBlockAsm     _Vec2uSubtractFloatFromBlockAsm

#define Vec2SubFloatFromBlockSizeAsm       _Vec2SubFloatFromBlockSizeAsm
#define Vec2BufSubFloatFromBlkSizeAsm      _Vec2BufSubFloatFromBlkSizeAsm
#define Vec2BufSubFloatFromBufAsm          _Vec2BufSubFloatFromBufAsm

#define Vec2SubtractFloatFromBlockFPU_Asm  _Vec2SubtractFloatFromBlockFPU_Asm
#define Vec2SubFloatFromBlockSizeFPU_Asm   _Vec2SubFloatFromBlockSizeFPU_Asm
#define Vec2BufSubFloatFromBlkSizeFPU_Asm  _Vec2BufSubFloatFromBlkSizeFPU_Asm
#define Vec2BufSubFloatFromBufFPU_Asm      _Vec2BufSubFloatFromBufFPU_Asm

#define Vec2MultiplyBlockByFloatAsm        _Vec2MultiplyBlockByFloatAsm
#define Vec2uMultiplyBlockByFloatAsm       _Vec2uMultiplyBlockByFloatAsm

#define Vec2MultiplyBlkByFloatSizeAsm      _Vec2MultiplyBlkByFloatSizeAsm
#define Vec2BufMulBlockByFloatSizeAsm      _Vec2BufMulBlockByFloatSizeAsm
#define Vec2BufMulBlockByFloatBufAsm       _Vec2BufMulBlockByFloatBufAsm

#define Vec2MultiplyBlockByFloatFPU_Asm    _Vec2MultiplyBlockByFloatFPU_Asm
#define Vec2MultiplyBlkByFloatSizeFPU_Asm  _Vec2MultiplyBlkByFloatSizeFPU_Asm
#define Vec2BufMulBlockByFloatSizeFPU_Asm  _Vec2BufMulBlockByFloatSizeFPU_Asm
#define Vec2BufMulBlockByFloatBufFPU_Asm   _Vec2BufMulBlockByFloatBufFPU_Asm

#define Vec2DivideBlockByFloatAsm          _Vec2DivideBlockByFloatAsm
#define Vec2uDivideBlockByFloatAsm         _Vec2uDivideBlockByFloatAsm

#define Vec2DivideBlockByFloatSizeAsm      _Vec2DivideBlockByFloatSizeAsm
#define Vec2BufDivBlockByFloatSizeAsm      _Vec2BufDivBlockByFloatSizeAsm
#define Vec2BufDivBufByFloatAsm            _Vec2BufDivBufByFloatAsm

#define Vec2DivideBlockByFloatFPU_Asm      _Vec2DivideBlockByFloatFPU_Asm
#define Vec2DivideBlockByFloatSizeFPU_Asm  _Vec2DivideBlockByFloatSizeFPU_Asm
#define Vec2BufDivBlockByFloatSizeFPU_Asm  _Vec2BufDivBlockByFloatSizeFPU_Asm
#define Vec2BufDivBufByFloatFPU_Asm        _Vec2BufDivBufByFloatFPU_Asm

#define Vec2NegateAsm                      _Vec2NegateAsm
#define Vec2AddAsm                         _Vec2AddAsm
#define Vec2SubtractAsm                    _Vec2SubtractAsm
#define Vec2MultiplyAsm                    _Vec2MultiplyAsm
#define Vec2DivideAsm                      _Vec2DivideAsm

#define Vec2EqualsAsm                      _Vec2EqualsAsm
#define Vec2NotEqualsAsm                   _Vec2NotEqualsAsm

#define Vec2uEqualsAsm                     _Vec2uEqualsAsm
#define Vec2uNotEqualsAsm                  _Vec2uNotEqualsAsm

#define Vec2NegateBlockAsm                 _Vec2NegateBlockAsm
#define Vec2uNegateBlockAsm                _Vec2uNegateBlockAsm

#define Vec2NegateBlockBySizeAsm           _Vec2NegateBlockBySizeAsm
#define Vec2BufNegateBlockBySizeAsm        _Vec2BufNegateBlockBySizeAsm
#define Vec2BufNegateBufBySizeAsm          _Vec2BufNegateBufBySizeAsm

#define Vec2AddVec2ToBlockAsm              _Vec2AddVec2ToBlockAsm
#define Vec2AddBlockToBlockAsm             _Vec2AddBlockToBlockAsm

#define Vec2uAddVec2ToBlockAsm             _Vec2uAddVec2ToBlockAsm
#define Vec2uAddBlockToBlockAsm            _Vec2uAddBlockToBlockAsm

#define Vec2BufAddVec2ToBlockBySizeAsm     _Vec2BufAddVec2ToBlockBySizeAsm
#define Vec2BufAddBlockBySizeAsm           _Vec2BufAddBlockBySizeAsm
#define Vec2BufAddBufBySizeAsm             _Vec2BufAddBufBySizeAsm

#define Vec2SubtractVec2FromBlockAsm       _Vec2SubtractVec2FromBlockAsm
#define Vec2SubtractBlockFromBlockAsm      _Vec2SubtractBlockFromBlockAsm

#define Vec2uSubtractVec2FromBlockAsm      _Vec2uSubtractVec2FromBlockAsm
#define Vec2uSubtractBlockFromBlockAsm     _Vec2uSubtractBlockFromBlockAsm

#define Vec2BufSubVec2FromBlkBySizeAsm     _Vec2BufSubVec2FromBlkBySizeAsm
#define Vec2BufSubBlockBySizeAsm           _Vec2BufSubBlockBySizeAsm
#define Vec2BufSubBufBySizeAsm             _Vec2BufSubBufBySizeAsm

#define Vec2MultiplyBlockByVec2Asm         _Vec2MultiplyBlockByVec2Asm
#define Vec2MultiplyBlockByBlockAsm        _Vec2MultiplyBlockByBlockAsm

#define Vec2uMultiplyBlockByVec2Asm        _Vec2uMultiplyBlockByVec2Asm
#define Vec2uMultiplyBlockByBlockAsm       _Vec2uMultiplyBlockByBlockAsm

#define Vec2BufMulVec2ByBlockSizeAsm       _Vec2BufMulVec2ByBlockSizeAsm
#define Vec2BufMulBlockBySizeAsm           _Vec2BufMulBlockBySizeAsm
#define Vec2BufMulBufBySizeAsm             _Vec2BufMulBufBySizeAsm

#define Vec2DivideBlockByVec2Asm           _Vec2DivideBlockByVec2Asm
#define Vec2DivideBlockByBlockAsm          _Vec2DivideBlockByBlockAsm

#define Vec2uDivideBlockByVec2Asm          _Vec2uDivideBlockByVec2Asm
#define Vec2uDivideBlockByBlockAsm         _Vec2uDivideBlockByBlockAsm

#define Vec2BufDivVec2ByBlockSizeAsm       _Vec2BufDivVec2ByBlockSizeAsm
#define Vec2BufDivBlockBySizeAsm           _Vec2BufDivBlockBySizeAsm
#define Vec2BufDivBufBySizeAsm             _Vec2BufDivBufBySizeAsm

#define Vec2LerpBlockAsm                   _Vec2LerpBlockAsm
#define Vec2SqrBlockAsm                    _Vec2SqrBlockAsm
#define Vec2SqrtBlockAsm                   _Vec2SqrtBlockAsm
#define Vec2NormalizeBlockAsm              _Vec2NormalizeBlockAsm
#define Vec2DotBlockAsm                    _Vec2DotBlockAsm

#define Vec2uLerpBlockAsm                  _Vec2uLerpBlockAsm
#define Vec2uSqrBlockAsm                   _Vec2uSqrBlockAsm
#define Vec2uSqrtBlockAsm                  _Vec2uSqrtBlockAsm
#define Vec2uNormalizeBlockAsm             _Vec2uNormalizeBlockAsm
#define Vec2uDotBlockAsm                   _Vec2uDotBlockAsm

#define Vec2LerpAsm                        _Vec2LerpAsm
#define Vec2SqrAsm                         _Vec2SqrAsm
#define Vec2SqrtAsm                        _Vec2SqrtAsm
#define Vec2NormalizeAsm                   _Vec2NormalizeAsm
#define Vec2DotAsm                         _Vec2DotAsm
#define Vec2LengthAsm                      _Vec2LengthAsm
#define Vec2LengthBlockAsm                 _Vec2LengthBlockAsm

#define Vec2BufLerpBufAsm                  _Vec2BufLerpBufAsm
#define Vec2BufSqrBufAsm                   _Vec2BufSqrBufAsm
#define Vec2BufSqrtBufAsm                  _Vec2BufSqrtBufAsm
#define Vec2BufNormalizeBufAsm             _Vec2BufNormalizeBufAsm
#define Vec2BufDotBufAsm                   _Vec2BufDotBufAsm
#define Vec2BufLengthBufAsm                _Vec2BufLengthBufAsm

#define Vec3CopyAsm                        _Vec3CopyAsm
#define Vec3CopyBlockAsm                   _Vec3CopyBlockAsm
#define BuildVec3PackedArrayAsm            _BuildVec3PackedArrayAsm

#define Vec3AddFloatAsm                    _Vec3AddFloatAsm
#define Vec3AddFloatToBlockAsm             _Vec3AddFloatToBlockAsm
#define Vec3AddFloatToBlockBySizeAsm       _Vec3AddFloatToBlockBySizeAsm
#define Vec3BufAddFloatToBlockAsm          _Vec3BufAddFloatToBlockAsm
#define Vec3BufAddFloatToBufAsm            _Vec3BufAddFloatToBufAsm

#define Vec3uAddFloatAsm                   _Vec3uAddFloatAsm
#define Vec3uAddFloatToBlockAsm            _Vec3uAddFloatToBlockAsm
#define Vec3uAddFloatToBlockBySizeAsm      _Vec3uAddFloatToBlockBySizeAsm
#define Vec3uBufAddFloatToBlockAsm         _Vec3uBufAddFloatToBlockAsm
#define Vec3uBufAddFloatToBufAsm           _Vec3uBufAddFloatToBufAsm

#define Vec3SubtractFloatAsm               _Vec3SubtractFloatAsm
#define Vec3SubtractFloatFromBlockAsm      _Vec3SubtractFloatFromBlockAsm
#define Vec3SubFloatFromBlockBySizeAsm     _Vec3SubFloatFromBlockBySizeAsm
#define Vec3BufSubFloatFromBlockAsm        _Vec3BufSubFloatFromBlockAsm
#define Vec3BufSubFloatFromBufAsm          _Vec3BufSubFloatFromBufAsm

#define Vec3uSubtractFloatAsm              _Vec3uSubtractFloatAsm
#define Vec3uSubtractFloatFromBlockAsm     _Vec3uSubtractFloatFromBlockAsm
#define Vec3uSubFloatFromBlockBySizeAsm    _Vec3uSubFloatFromBlockBySizeAsm
#define Vec3uBufSubFloatFromBlockAsm       _Vec3uBufSubFloatFromBlockAsm
#define Vec3uBufSubFloatFromBufAsm         _Vec3uBufSubFloatFromBufAsm

#define Vec3MultiplyFloatAsm               _Vec3MultiplyFloatAsm
#define Vec3MultiplyFloatToBlockAsm        _Vec3MultiplyFloatToBlockAsm
#define Vec3MulFloatToBlockBySizeAsm       _Vec3MulFloatToBlockBySizeAsm
#define Vec3BufMulFloatToBlockAsm          _Vec3BufMulFloatToBlockAsm
#define Vec3BufMulFloatToBufAsm            _Vec3BufMulFloatToBufAsm

#define Vec3uMultiplyFloatAsm              _Vec3uMultiplyFloatAsm
#define Vec3uMultiplyFloatToBlockAsm       _Vec3uMultiplyFloatToBlockAsm
#define Vec3uMulFloatToBlockBySizeAsm      _Vec3uMulFloatToBlockBySizeAsm
#define Vec3uBufMulFloatToBlockAsm         _Vec3uBufMulFloatToBlockAsm
#define Vec3uBufMulFloatToBufAsm           _Vec3uBufMulFloatToBufAsm

#define Vec3DivideFloatAsm                 _Vec3DivideFloatAsm
#define Vec3DivideBlockByFloatAsm          _Vec3DivideBlockByFloatAsm
#define Vec3DivBlockByFloatBySizeAsm       _Vec3DivBlockByFloatBySizeAsm
#define Vec3BufDivBlockByFloatAsm          _Vec3BufDivBlockByFloatAsm
#define Vec3BufDivBufByFloatAsm            _Vec3BufDivBufByFloatAsm

#define Vec3uDivideFloatAsm                _Vec3uDivideFloatAsm
#define Vec3uDivideBlockByFloatAsm         _Vec3uDivideBlockByFloatAsm
#define Vec3uDivBlockByFloatBySizeAsm      _Vec3uDivBlockByFloatBySizeAsm
#define Vec3uBufDivBlockByFloatAsm         _Vec3uBufDivBlockByFloatAsm
#define Vec3uBufDivBufByFloatAsm           _Vec3uBufDivBufByFloatAsm

#define Vec3EqualsAsm                      _Vec3EqualsAsm
#define Vec3NotEqualsAsm                   _Vec3NotEqualsAsm

#define Vec3uEqualsAsm                     _Vec3uEqualsAsm
#define Vec3uNotEqualsAsm                  _Vec3uNotEqualsAsm

#define Vec3NegateAsm                      _Vec3NegateAsm
#define Vec3NegateBlockAsm                 _Vec3NegateBlockAsm
#define Vec3NegateBlockBySizeAsm           _Vec3NegateBlockBySizeAsm
#define Vec3BufNegateBlockAsm              _Vec3BufNegateBlockAsm
#define Vec3BufNegateBufAsm                _Vec3BufNegateBufAsm

#define Vec3uNegateAsm                     _Vec3uNegateAsm
#define Vec3uNegateBlockAsm                _Vec3uNegateBlockAsm
#define Vec3uNegateBlockBySizeAsm          _Vec3uNegateBlockBySizeAsm
#define Vec3uBufNegateBlockAsm             _Vec3uBufNegateBlockAsm
#define Vec3uBufNegateBufAsm               _Vec3uBufNegateBufAsm

#define Vec3AddAsm                         _Vec3AddAsm
#define Vec3AddVecToBlockAsm               _Vec3AddVecToBlockAsm
#define Vec3AddVecToBlockBySizeAsm         _Vec3AddVecToBlockBySizeAsm
#define Vec3BufAddVecToBlockAsm            _Vec3BufAddVecToBlockAsm
#define Vec3BufAddVecToBufAsm              _Vec3BufAddVecToBufAsm
#define Vec3AddBlockToBlockAsm             _Vec3AddBlockToBlockAsm
#define Vec3AddBlockToBlockBySizeAsm       _Vec3AddBlockToBlockBySizeAsm
#define Vec3BufAddBlockToBufAsm            _Vec3BufAddBlockToBufAsm
#define Vec3BufAddBufToBufAsm              _Vec3BufAddBufToBufAsm

#define Vec3uAddAsm                        _Vec3uAddAsm
#define Vec3uAddVecToBlockAsm              _Vec3uAddVecToBlockAsm
#define Vec3uAddVecToBlockBySizeAsm        _Vec3uAddVecToBlockBySizeAsm
#define Vec3uBufAddVecToBlockAsm           _Vec3uBufAddVecToBlockAsm
#define Vec3uBufAddVecToBufAsm             _Vec3uBufAddVecToBufAsm
#define Vec3uAddBlockToBlockAsm            _Vec3uAddBlockToBlockAsm
#define Vec3uAddBlockToBlockBySizeAsm      _Vec3uAddBlockToBlockBySizeAsm
#define Vec3uBufAddBlockToBufAsm           _Vec3uBufAddBlockToBufAsm
#define Vec3uBufAddBufToBufAsm             _Vec3uBufAddBufToBufAsm

#define Vec3SubtractAsm                    _Vec3SubtractAsm
#define Vec3SubVecFromBlockAsm             _Vec3SubVecFromBlockAsm
#define Vec3SubVecFromBlockBySizeAsm       _Vec3SubVecFromBlockBySizeAsm
#define Vec3BufSubVecFromBlockAsm          _Vec3BufSubVecFromBlockAsm
#define Vec3BufSubVecFromBufAsm            _Vec3BufSubVecFromBufAsm
#define Vec3SubBlockFromBlockAsm           _Vec3SubBlockFromBlockAsm
#define Vec3SubBlockFromBlockBySizeAsm     _Vec3SubBlockFromBlockBySizeAsm
#define Vec3BufSubBlockFromBufAsm          _Vec3BufSubBlockFromBufAsm
#define Vec3BufSubBufFromBufAsm            _Vec3BufSubBufFromBufAsm

#define Vec3uSubtractAsm                   _Vec3uSubtractAsm
#define Vec3uSubVecFromBlockAsm            _Vec3uSubVecFromBlockAsm
#define Vec3uSubVecFromBlockBySizeAsm      _Vec3uSubVecFromBlockBySizeAsm
#define Vec3uBufSubVecFromBlockAsm         _Vec3uBufSubVecFromBlockAsm
#define Vec3uBufSubVecFromBufAsm           _Vec3uBufSubVecFromBufAsm
#define Vec3uSubBlockFromBlockAsm          _Vec3uSubBlockFromBlockAsm
#define Vec3uSubBlockFromBlockBySizeAsm    _Vec3uSubBlockFromBlockBySizeAsm
#define Vec3uBufSubBlockFromBufAsm         _Vec3uBufSubBlockFromBufAsm
#define Vec3uBufSubBufFromBufAsm           _Vec3uBufSubBufFromBufAsm

#define Vec3MultiplyAsm                    _Vec3MultiplyAsm
#define Vec3MulBlockByVecAsm               _Vec3MulBlockByVecAsm
#define Vec3MulBlockByVecUseSizeAsm        _Vec3MulBlockByVecUseSizeAsm
#define Vec3BufMulBufByVecAsm              _Vec3BufMulBufByVecAsm
#define Vec3BufMulBufByVecUseSizeAsm       _Vec3BufMulBufByVecUseSizeAsm
#define Vec3MulBlockByBlockAsm             _Vec3MulBlockByBlockAsm
#define Vec3MulBlockByBlockUseSizeAsm      _Vec3MulBlockByBlockUseSizeAsm
#define Vec3BufMulBufByBlockAsm            _Vec3BufMulBufByBlockAsm
#define Vec3BufMulBufByBufAsm	           _Vec3BufMulBufByBufAsm	

#define Vec3uMultiplyAsm                   _Vec3uMultiplyAsm
#define Vec3uMulBlockByVecAsm              _Vec3uMulBlockByVecAsm
#define Vec3uMulBlockByVecUseSizeAsm       _Vec3uMulBlockByVecUseSizeAsm
#define Vec3uBufMulBufByVecAsm             _Vec3uBufMulBufByVecAsm
#define Vec3uBufMulBufByVecUseSizeAsm      _Vec3uBufMulBufByVecUseSizeAsm
#define Vec3uMulBlockByBlockAsm            _Vec3uMulBlockByBlockAsm
#define Vec3uMulBlockByBlockUseSizeAsm     _Vec3uMulBlockByBlockUseSizeAsm
#define Vec3uBufMulBufByBlockAsm           _Vec3uBufMulBufByBlockAsm
#define Vec3uBufMulBufByBufAsm             _Vec3uBufMulBufByBufAsm

#define Vec3DivideAsm                      _Vec3DivideAsm
#define Vec3DivBlockByVecAsm               _Vec3DivBlockByVecAsm
#define Vec3DivBlockByVecUseSizeAsm        _Vec3DivBlockByVecUseSizeAsm
#define Vec3BufDivBufByVecAsm              _Vec3BufDivBufByVecAsm
#define Vec3BufDivBufByVecUseSizeAsm       _Vec3BufDivBufByVecUseSizeAsm
#define Vec3DivBlockByBlockAsm             _Vec3DivBlockByBlockAsm
#define Vec3DivBlockByBlockUseSizeAsm      _Vec3DivBlockByBlockUseSizeAsm
#define Vec3BufDivBufByBlockAsm            _Vec3BufDivBufByBlockAsm
#define Vec3BufDivBufByBufAsm              _Vec3BufDivBufByBufAsm

#define Vec3uDivideAsm                     _Vec3uDivideAsm
#define Vec3uDivBlockByVecAsm              _Vec3uDivBlockByVecAsm
#define Vec3uDivBlockByVecUseSizeAsm       _Vec3uDivBlockByVecUseSizeAsm
#define Vec3uBufDivBufByVecAsm             _Vec3uBufDivBufByVecAsm
#define Vec3uBufDivBufByVecUseSizeAsm      _Vec3uBufDivBufByVecUseSizeAsm
#define Vec3uDivBlockByBlockAsm            _Vec3uDivBlockByBlockAsm
#define Vec3uDivBlockByBlockUseSizeAsm     _Vec3uDivBlockByBlockUseSizeAsm
#define Vec3uBufDivBufByBlockAsm           _Vec3uBufDivBufByBlockAsm
#define Vec3uBufDivBufByBufAsm             _Vec3uBufDivBufByBufAsm

#define Vec3LerpAsm                        _Vec3LerpAsm
#define Vec3LerpBlockAsm                   _Vec3LerpBlockAsm
#define Vec3LerpBlockUseSizeAsm            _Vec3LerpBlockUseSizeAsm
#define Vec3BufLerpBlockAsm                _Vec3BufLerpBlockAsm
#define Vec3BufLerpBufAsm                  _Vec3BufLerpBufAsm

#define Vec3uLerpAsm                       _Vec3uLerpAsm
#define Vec3uLerpBlockAsm                  _Vec3uLerpBlockAsm
#define Vec3uLerpBlockUseSizeAsm           _Vec3uLerpBlockUseSizeAsm
#define Vec3uBufLerpBlockAsm               _Vec3uBufLerpBlockAsm
#define Vec3uBufLerpBufAsm                 _Vec3uBufLerpBufAsm

#define Vec3DotFlatAsm                     _Vec3DotFlatAsm
#define Vec3uDotFlatAsm                    _Vec3uDotFlatAsm

#define Vec3DotAsm                         _Vec3DotAsm
#define Vec3DotBlockAsm                    _Vec3DotBlockAsm
#define Vec3DotBlockUseSizeAsm             _Vec3DotBlockUseSizeAsm
#define Vec3BufDotBufAsm                   _Vec3BufDotBufAsm

#define Vec3DotFPU_Asm                     _Vec3DotFPU_Asm

#define Vec3uDotAsm                        _Vec3uDotAsm
#define Vec3uDotBlockAsm                   _Vec3uDotBlockAsm
#define Vec3uDotBlockUseSizeAsm            _Vec3uDotBlockUseSizeAsm
#define Vec3uBufDotBufAsm                  _Vec3uBufDotBufAsm

#define Vec3SqrAsm                         _Vec3SqrAsm
#define Vec3SqrBlockAsm                    _Vec3SqrBlockAsm
#define Vec3SqrBlockUseSizeAsm             _Vec3SqrBlockUseSizeAsm
#define Vec3BufSqrBufAsm                   _Vec3BufSqrBufAsm

#define Vec3uSqrAsm                        _Vec3uSqrAsm
#define Vec3uSqrBlockAsm                   _Vec3uSqrBlockAsm
#define Vec3uSqrBlockUseSizeAsm            _Vec3uSqrBlockUseSizeAsm
#define Vec3uBufSqrBufAsm                  _Vec3uBufSqrBufAsm

#define Vec3SqrtAsm                        _Vec3SqrtAsm
#define Vec3SqrtBlockAsm                   _Vec3SqrtBlockAsm
#define Vec3SqrtBlockUseSizeAsm            _Vec3SqrtBlockUseSizeAsm
#define Vec3BufSqrtBufAsm                  _Vec3BufSqrtBufAsm

#define Vec3uSqrtAsm                       _Vec3uSqrtAsm
#define Vec3uSqrtBlockAsm                  _Vec3uSqrtBlockAsm
#define Vec3uSqrtBlockUseSizeAsm           _Vec3uSqrtBlockUseSizeAsm
#define Vec3uBufSqrtBufAsm                 _Vec3uBufSqrtBufAsm

#define Vec3NormalizeFlatAsm               _Vec3NormalizeFlatAsm
#define Vec3NormalizeBlockFlatAsm          _Vec3NormalizeBlockFlatAsm
#define Vec3NormalizeBlockFlatUseSizeAsm   _Vec3NormalizeBlockFlatUseSizeAsm
#define Vec3BufNormalizeBufFlatAsm         _Vec3BufNormalizeBufFlatAsm

#define Vec3NormalizeAsm                   _Vec3NormalizeAsm
#define Vec3NormalizeBlockAsm              _Vec3NormalizeBlockAsm
#define Vec3NormalizeBlockUseSizeAsm       _Vec3NormalizeBlockUseSizeAsm
#define Vec3BufNormalizeBufAsm             _Vec3BufNormalizeBufAsm

#define Vec3NormalizeFPU_Asm               _Vec3NormalizeFPU_Asm

#define Vec3uNormalizeFlatAsm              _Vec3uNormalizeFlatAsm
#define Vec3uNormalizeBlockFlatAsm         _Vec3uNormalizeBlockFlatAsm
#define Vec3uNormalizeBlockFlatUseSizeAsm  _Vec3uNormalizeBlockFlatUseSizeAsm
#define Vec3uBufNormalizeBufFlatAsm        _Vec3uBufNormalizeBufFlatAsm

#define Vec3uNormalizeAsm                  _Vec3uNormalizeAsm
#define Vec3uNormalizeBlockAsm             _Vec3uNormalizeBlockAsm
#define Vec3uNormalizeBlockUseSizeAsm      _Vec3uNormalizeBlockUseSizeAsm
#define Vec3uBufNormalizeBufAsm            _Vec3uBufNormalizeBufAsm

#define Vec3LengthFlatAsm                  _Vec3LengthFlatAsm
#define Vec3LengthBlockFlatAsm             _Vec3LengthBlockFlatAsm
#define Vec3LengthBlockFlatUseSizeAsm      _Vec3LengthBlockFlatUseSizeAsm
#define Vec3BufLengthBufFlatAsm            _Vec3BufLengthBufFlatAsm

#define Vec3LengthAsm                      _Vec3LengthAsm
#define Vec3LengthBlockAsm                 _Vec3LengthBlockAsm
#define Vec3LengthBlockUseSizeAsm          _Vec3LengthBlockUseSizeAsm
#define Vec3BufLengthBufAsm                _Vec3BufLengthBufAsm

#define Vec3LengthFPU_Asm                  _Vec3LengthFPU_Asm

#define Vec3uLengthFlatAsm                 _Vec3uLengthFlatAsm
#define Vec3uLengthBlockFlatAsm            _Vec3uLengthBlockFlatAsm
#define Vec3uLengthBlockFlatUseSizeAsm     _Vec3uLengthBlockFlatUseSizeAsm
#define Vec3uBufLengthBufFlatAsm           _Vec3uBufLengthBufFlatAsm

#define Vec3uLengthAsm                     _Vec3uLengthAsm
#define Vec3uLengthBlockAsm                _Vec3uLengthBlockAsm
#define Vec3uLengthBlockUseSizeAsm         _Vec3uLengthBlockUseSizeAsm
#define Vec3uBufLengthBufAsm               _Vec3uBufLengthBufAsm

#define Vec3CrossAsm                       _Vec3CrossAsm
#define Vec3CrossBlockAsm                  _Vec3CrossBlockAsm
#define Vec3CrossBlockUseSizeAsm           _Vec3CrossBlockUseSizeAsm
#define Vec3BufCrossBufAsm                 _Vec3BufCrossBufAsm

#define Vec3uCrossAsm                      _Vec3uCrossAsm
#define Vec3uCrossBlockAsm                 _Vec3uCrossBlockAsm
#define Vec3uCrossBlockUseSizeAsm          _Vec3uCrossBlockUseSizeAsm
#define Vec3uBufCrossBufAsm                _Vec3uBufCrossBufAsm

#define Vec3ReflectAsm                     _Vec3ReflectAsm
#define Vec3uReflectAsm                    _Vec3uReflectAsm

#define Vec4CopyAsm                        _Vec4CopyAsm
#define Vec4CopyBlockAsm                   _Vec4CopyBlockAsm
#define BuildVec4PackedArrayAsm            _BuildVec4PackedArrayAsm

#define Vec4AddFloatAsm                    _Vec4AddFloatAsm
#define Vec4AddFloatToBlockAsm             _Vec4AddFloatToBlockAsm
#define Vec4AddFloatToBlockBySizeAsm       _Vec4AddFloatToBlockBySizeAsm
#define Vec4BufAddFloatToBlockAsm          _Vec4BufAddFloatToBlockAsm
#define Vec4BufAddFloatToBufAsm            _Vec4BufAddFloatToBufAsm

#define Vec4uAddFloatAsm                   _Vec4uAddFloatAsm
#define Vec4uAddFloatToBlockAsm            _Vec4uAddFloatToBlockAsm
#define Vec4uAddFloatToBlockBySizeAsm      _Vec4uAddFloatToBlockBySizeAsm
#define Vec4uBufAddFloatToBlockAsm         _Vec4uBufAddFloatToBlockAsm
#define Vec4uBufAddFloatToBufAsm           _Vec4uBufAddFloatToBufAsm

#define Vec4SubtractFloatAsm               _Vec4SubtractFloatAsm
#define Vec4SubtractFloatFromBlockAsm      _Vec4SubtractFloatFromBlockAsm
#define Vec4SubFloatFromBlockBySizeAsm     _Vec4SubFloatFromBlockBySizeAsm
#define Vec4BufSubFloatFromBlockAsm        _Vec4BufSubFloatFromBlockAsm
#define Vec4BufSubFloatFromBufAsm          _Vec4BufSubFloatFromBufAsm

#define Vec4uSubtractFloatAsm              _Vec4uSubtractFloatAsm
#define Vec4uSubtractFloatFromBlockAsm     _Vec4uSubtractFloatFromBlockAsm
#define Vec4uSubFloatFromBlockBySizeAsm    _Vec4uSubFloatFromBlockBySizeAsm
#define Vec4uBufSubFloatFromBlockAsm       _Vec4uBufSubFloatFromBlockAsm
#define Vec4uBufSubFloatFromBufAsm         _Vec4uBufSubFloatFromBufAsm

#define Vec4MultiplyFloatAsm               _Vec4MultiplyFloatAsm
#define Vec4MultiplyFloatToBlockAsm        _Vec4MultiplyFloatToBlockAsm
#define Vec4MulFloatToBlockBySizeAsm       _Vec4MulFloatToBlockBySizeAsm
#define Vec4BufMulFloatToBlockAsm          _Vec4BufMulFloatToBlockAsm
#define Vec4BufMulFloatToBufAsm            _Vec4BufMulFloatToBufAsm

#define Vec4uMultiplyFloatAsm              _Vec4uMultiplyFloatAsm
#define Vec4uMultiplyFloatToBlockAsm       _Vec4uMultiplyFloatToBlockAsm
#define Vec4uMulFloatToBlockBySizeAsm      _Vec4uMulFloatToBlockBySizeAsm
#define Vec4uBufMulFloatToBlockAsm         _Vec4uBufMulFloatToBlockAsm
#define Vec4uBufMulFloatToBufAsm           _Vec4uBufMulFloatToBufAsm

#define Vec4DivideFloatAsm                 _Vec4DivideFloatAsm
#define Vec4DivideBlockByFloatAsm          _Vec4DivideBlockByFloatAsm
#define Vec4DivBlockByFloatBySizeAsm       _Vec4DivBlockByFloatBySizeAsm
#define Vec4BufDivBlockByFloatAsm          _Vec4BufDivBlockByFloatAsm
#define Vec4BufDivBufByFloatAsm            _Vec4BufDivBufByFloatAsm

#define Vec4uDivideFloatAsm                _Vec4uDivideFloatAsm
#define Vec4uDivideBlockByFloatAsm         _Vec4uDivideBlockByFloatAsm
#define Vec4uDivBlockByFloatBySizeAsm      _Vec4uDivBlockByFloatBySizeAsm
#define Vec4uBufDivBlockByFloatAsm         _Vec4uBufDivBlockByFloatAsm
#define Vec4uBufDivBufByFloatAsm           _Vec4uBufDivBufByFloatAsm

#define Vec4EqualsAsm                      _Vec4EqualsAsm
#define Vec4NotEqualsAsm                   _Vec4NotEqualsAsm

#define Vec4NegateAsm                      _Vec4NegateAsm
#define Vec4NegateBlockAsm                 _Vec4NegateBlockAsm
#define Vec4NegateBlockBySizeAsm           _Vec4NegateBlockBySizeAsm
#define Vec4BufNegateBlockAsm              _Vec4BufNegateBlockAsm
#define Vec4BufNegateBufAsm                _Vec4BufNegateBufAsm

#define Vec4uNegateAsm                     _Vec4uNegateAsm
#define Vec4uNegateBlockAsm                _Vec4uNegateBlockAsm
#define Vec4uNegateBlockBySizeAsm          _Vec4uNegateBlockBySizeAsm
#define Vec4uBufNegateBlockAsm             _Vec4uBufNegateBlockAsm
#define Vec4uBufNegateBufAsm               _Vec4uBufNegateBufAsm

#define Vec4AddAsm                         _Vec4AddAsm
#define Vec4AddVecToBlockAsm               _Vec4AddVecToBlockAsm
#define Vec4AddVecToBlockBySizeAsm         _Vec4AddVecToBlockBySizeAsm
#define Vec4BufAddVecToBlockAsm            _Vec4BufAddVecToBlockAsm
#define Vec4BufAddVecToBufAsm              _Vec4BufAddVecToBufAsm
#define Vec4AddBlockToBlockAsm             _Vec4AddBlockToBlockAsm
#define Vec4AddBlockToBlockBySizeAsm       _Vec4AddBlockToBlockBySizeAsm
#define Vec4BufAddBlockToBufAsm            _Vec4BufAddBlockToBufAsm
#define Vec4BufAddBufToBufAsm              _Vec4BufAddBufToBufAsm

#define Vec4uAddAsm                        _Vec4uAddAsm
#define Vec4uAddVecToBlockAsm              _Vec4uAddVecToBlockAsm
#define Vec4uAddVecToBlockBySizeAsm        _Vec4uAddVecToBlockBySizeAsm
#define Vec4uBufAddVecToBlockAsm           _Vec4uBufAddVecToBlockAsm
#define Vec4uBufAddVecToBufAsm             _Vec4uBufAddVecToBufAsm
#define Vec4uAddBlockToBlockAsm            _Vec4uAddBlockToBlockAsm
#define Vec4uAddBlockToBlockBySizeAsm      _Vec4uAddBlockToBlockBySizeAsm
#define Vec4uBufAddBlockToBufAsm           _Vec4uBufAddBlockToBufAsm
#define Vec4uBufAddBufToBufAsm             _Vec4uBufAddBufToBufAsm

#define Vec4SubtractAsm                    _Vec4SubtractAsm
#define Vec4SubVecFromBlockAsm             _Vec4SubVecFromBlockAsm
#define Vec4SubVecFromBlockBySizeAsm       _Vec4SubVecFromBlockBySizeAsm
#define Vec4BufSubVecFromBlockAsm          _Vec4BufSubVecFromBlockAsm
#define Vec4BufSubVecFromBufAsm            _Vec4BufSubVecFromBufAsm
#define Vec4SubBlockFromBlockAsm           _Vec4SubBlockFromBlockAsm
#define Vec4SubBlockFromBlockBySizeAsm     _Vec4SubBlockFromBlockBySizeAsm
#define Vec4BufSubBlockFromBufAsm          _Vec4BufSubBlockFromBufAsm
#define Vec4BufSubBufFromBufAsm            _Vec4BufSubBufFromBufAsm

#define Vec4uSubtractAsm                   _Vec4uSubtractAsm
#define Vec4uSubVecFromBlockAsm            _Vec4uSubVecFromBlockAsm
#define Vec4uSubVecFromBlockBySizeAsm      _Vec4uSubVecFromBlockBySizeAsm
#define Vec4uBufSubVecFromBlockAsm         _Vec4uBufSubVecFromBlockAsm
#define Vec4uBufSubVecFromBufAsm           _Vec4uBufSubVecFromBufAsm
#define Vec4uSubBlockFromBlockAsm          _Vec4uSubBlockFromBlockAsm
#define Vec4uSubBlockFromBlockBySizeAsm    _Vec4uSubBlockFromBlockBySizeAsm
#define Vec4uBufSubBlockFromBufAsm         _Vec4uBufSubBlockFromBufAsm
#define Vec4uBufSubBufFromBufAsm           _Vec4uBufSubBufFromBufAsm

#define Vec4MultiplyAsm                    _Vec4MultiplyAsm
#define Vec4MulBlockByVecAsm               _Vec4MulBlockByVecAsm
#define Vec4MulBlockByVecUseSizeAsm        _Vec4MulBlockByVecUseSizeAsm
#define Vec4BufMulBufByVecAsm              _Vec4BufMulBufByVecAsm
#define Vec4BufMulBufByVecUseSizeAsm       _Vec4BufMulBufByVecUseSizeAsm
#define Vec4MulBlockByBlockAsm             _Vec4MulBlockByBlockAsm
#define Vec4MulBlockByBlockUseSizeAsm      _Vec4MulBlockByBlockUseSizeAsm
#define Vec4BufMulBufByBlockAsm            _Vec4BufMulBufByBlockAsm
#define Vec4BufMulBufByBufAsm              _Vec4BufMulBufByBufAsm

#define Vec4uMultiplyAsm                   _Vec4uMultiplyAsm
#define Vec4uMulBlockByVecAsm              _Vec4uMulBlockByVecAsm
#define Vec4uMulBlockByVecUseSizeAsm       _Vec4uMulBlockByVecUseSizeAsm
#define Vec4uBufMulBufByVecAsm             _Vec4uBufMulBufByVecAsm
#define Vec4uBufMulBufByVecUseSizeAsm      _Vec4uBufMulBufByVecUseSizeAsm
#define Vec4uMulBlockByBlockAsm            _Vec4uMulBlockByBlockAsm
#define Vec4uMulBlockByBlockUseSizeAsm     _Vec4uMulBlockByBlockUseSizeAsm
#define Vec4uBufMulBufByBlockAsm           _Vec4uBufMulBufByBlockAsm
#define Vec4uBufMulBufByBufAsm             _Vec4uBufMulBufByBufAsm

#define Vec4DivideAsm                      _Vec4DivideAsm
#define Vec4DivBlockByVecAsm               _Vec4DivBlockByVecAsm
#define Vec4DivBlockByVecUseSizeAsm        _Vec4DivBlockByVecUseSizeAsm
#define Vec4BufDivBufByVecAsm              _Vec4BufDivBufByVecAsm
#define Vec4BufDivBufByVecUseSizeAsm       _Vec4BufDivBufByVecUseSizeAsm
#define Vec4DivBlockByBlockAsm             _Vec4DivBlockByBlockAsm
#define Vec4DivBlockByBlockUseSizeAsm      _Vec4DivBlockByBlockUseSizeAsm
#define Vec4BufDivBufByBlockAsm            _Vec4BufDivBufByBlockAsm
#define Vec4BufDivBufByBufAsm              _Vec4BufDivBufByBufAsm

#define Vec4uDivideAsm                     _Vec4uDivideAsm
#define Vec4uDivBlockByVecAsm              _Vec4uDivBlockByVecAsm
#define Vec4uDivBlockByVecUseSizeAsm       _Vec4uDivBlockByVecUseSizeAsm
#define Vec4uBufDivBufByVecAsm             _Vec4uBufDivBufByVecAsm
#define Vec4uBufDivBufByVecUseSizeAsm      _Vec4uBufDivBufByVecUseSizeAsm
#define Vec4uDivBlockByBlockAsm            _Vec4uDivBlockByBlockAsm
#define Vec4uDivBlockByBlockUseSizeAsm     _Vec4uDivBlockByBlockUseSizeAsm
#define Vec4uBufDivBufByBlockAsm           _Vec4uBufDivBufByBlockAsm
#define Vec4uBufDivBufByBufAsm             _Vec4uBufDivBufByBufAsm

#define Vec4LerpAsm                        _Vec4LerpAsm
#define Vec4LerpBlockAsm                   _Vec4LerpBlockAsm
#define Vec4LerpBlockUseSizeAsm            _Vec4LerpBlockUseSizeAsm
#define Vec4BufLerpBlockAsm                _Vec4BufLerpBlockAsm
#define Vec4BufLerpBufAsm                  _Vec4BufLerpBufAsm

#define Vec4uLerpAsm                       _Vec4uLerpAsm
#define Vec4uLerpBlockAsm                  _Vec4uLerpBlockAsm
#define Vec4uLerpBlockUseSizeAsm           _Vec4uLerpBlockUseSizeAsm
#define Vec4uBufLerpBlockAsm               _Vec4uBufLerpBlockAsm
#define Vec4uBufLerpBufAsm                 _Vec4uBufLerpBufAsm

#define Vec4DotFlatAsm                     _Vec4DotFlatAsm
#define Vec4DotBlockFlatAsm                _Vec4DotBlockFlatAsm
#define Vec4DotBlockFlatUseSizeAsm         _Vec4DotBlockFlatUseSizeAsm
#define Vec4BufDotBufFlatAsm               _Vec4BufDotBufFlatAsm

#define Vec4DotAsm                         _Vec4DotAsm
#define Vec4DotBlockAsm                    _Vec4DotBlockAsm
#define Vec4DotBlockUseSizeAsm             _Vec4DotBlockUseSizeAsm
#define Vec4BufDotBufAsm                   _Vec4BufDotBufAsm

#define Vec4DotFPU_Asm                     _Vec4DotFPU_Asm

#define Vec4uDotFlatAsm                    _Vec4uDotFlatAsm
#define Vec4uDotBlockFlatAsm               _Vec4uDotBlockFlatAsm
#define Vec4uDotBlockFlatUseSizeAsm        _Vec4uDotBlockFlatUseSizeAsm
#define Vec4uBufDotBufFlatAsm              _Vec4uBufDotBufFlatAsm

#define Vec4uDotAsm                        _Vec4uDotAsm
#define Vec4uDotBlockAsm                   _Vec4uDotBlockAsm
#define Vec4uDotBlockUseSizeAsm            _Vec4uDotBlockUseSizeAsm
#define Vec4uBufDotBufAsm                  _Vec4uBufDotBufAsm

#define Vec4SqrAsm                         _Vec4SqrAsm
#define Vec4SqrBlockAsm                    _Vec4SqrBlockAsm
#define Vec4SqrBlockUseSizeAsm             _Vec4SqrBlockUseSizeAsm
#define Vec4BufSqrBufAsm                   _Vec4BufSqrBufAsm

#define Vec4uSqrtAsm                       _Vec4uSqrtAsm
#define Vec4uSqrtBlockAsm                  _Vec4uSqrtBlockAsm
#define Vec4uSqrtBlockUseSizeAsm           _Vec4uSqrtBlockUseSizeAsm
#define Vec4uBufSqrtBufAsm                 _Vec4uBufSqrtBufAsm

#define Vec4SqrtAsm                        _Vec4SqrtAsm
#define Vec4SqrtBlockAsm                   _Vec4SqrtBlockAsm
#define Vec4SqrtBlockUseSizeAsm            _Vec4SqrtBlockUseSizeAsm
#define Vec4BufSqrtBufAsm                  _Vec4BufSqrtBufAsm

#define Vec4uSqrAsm                        _Vec4uSqrAsm
#define Vec4uSqrBlockAsm                   _Vec4uSqrBlockAsm
#define Vec4uSqrBlockUseSizeAsm            _Vec4uSqrBlockUseSizeAsm
#define Vec4uBufSqrBufAsm                  _Vec4uBufSqrBufAsm

#define Vec4NormalizeFlatAsm               _Vec4NormalizeFlatAsm
#define Vec4NormalizeBlockFlatAsm          _Vec4NormalizeBlockFlatAsm
#define Vec4NormalizeBlockFlatUseSizeAsm   _Vec4NormalizeBlockFlatUseSizeAsm
#define Vec4BufNormalizeBufFlatAsm         _Vec4BufNormalizeBufFlatAsm

#define Vec4NormalizeAsm                   _Vec4NormalizeAsm
#define Vec4NormalizeBlockAsm              _Vec4NormalizeBlockAsm
#define Vec4NormalizeBlockUseSizeAsm       _Vec4NormalizeBlockUseSizeAsm
#define Vec4BufNormalizeBufAsm             _Vec4BufNormalizeBufAsm

#define Vec4NormalizeFPU_Asm               _Vec4NormalizeFPU_Asm

#define Vec4uNormalizeFlatAsm              _Vec4uNormalizeFlatAsm
#define Vec4uNormalizeBlockFlatAsm         _Vec4uNormalizeBlockFlatAsm
#define Vec4uNormalizeBlockFlatUseSizeAsm  _Vec4uNormalizeBlockFlatUseSizeAsm
#define Vec4uBufNormalizeBufFlatAsm        _Vec4uBufNormalizeBufFlatAsm

#define Vec4uNormalizeAsm                  _Vec4uNormalizeAsm
#define Vec4uNormalizeBlockAsm             _Vec4uNormalizeBlockAsm
#define Vec4uNormalizeBlockUseSizeAsm      _Vec4uNormalizeBlockUseSizeAsm
#define Vec4uBufNormalizeBufAsm            _Vec4uBufNormalizeBufAsm

#define Vec4LengthFlatAsm                  _Vec4LengthFlatAsm
#define Vec4LengthBlockFlatAsm             _Vec4LengthBlockFlatAsm
#define Vec4LengthBlockFlatUseSizeAsm      _Vec4LengthBlockFlatUseSizeAsm
#define Vec4BufLengthBufFlatAsm            _Vec4BufLengthBufFlatAsm

#define Vec4LengthAsm                      _Vec4LengthAsm
#define Vec4LengthBlockAsm                 _Vec4LengthBlockAsm
#define Vec4LengthBlockUseSizeAsm          _Vec4LengthBlockUseSizeAsm
#define Vec4BufLengthBufAsm                _Vec4BufLengthBufAsm

#define Vec4LengthFPU_Asm                  _Vec4LengthFPU_Asm

#define Vec4uLengthFlatAsm                 _Vec4uLengthFlatAsm
#define Vec4uLengthBlockFlatAsm            _Vec4uLengthBlockFlatAsm
#define Vec4uLengthBlockFlatUseSizeAsm     _Vec4uLengthBlockFlatUseSizeAsm
#define Vec4uBufLengthBufFlatAsm           _Vec4uBufLengthBufFlatAsm

#define Vec4uLengthAsm                     _Vec4uLengthAsm
#define Vec4uLengthBlockAsm                _Vec4uLengthBlockAsm
#define Vec4uLengthBlockUseSizeAsm         _Vec4uLengthBlockUseSizeAsm
#define Vec4uBufLengthBufAsm               _Vec4uBufLengthBufAsm

#define Vec4CrossAsm                       _Vec4CrossAsm
#define Vec4CrossBlockAsm                  _Vec4CrossBlockAsm
#define Vec4CrossBlockUseSizeAsm           _Vec4CrossBlockUseSizeAsm
#define Vec4BufCrossBufAsm                 _Vec4BufCrossBufAsm

#define Vec4uCrossAsm                      _Vec4uCrossAsm
#define Vec4uCrossBlockAsm                 _Vec4uCrossBlockAsm
#define Vec4uCrossBlockUseSizeAsm          _Vec4uCrossBlockUseSizeAsm
#define Vec4uBufCrossBufAsm                _Vec4uBufCrossBufAsm

#define Mat2NegateAsm                      _Mat2NegateAsm
#define Mat2AddAsm                         _Mat2AddAsm
#define Mat2AddFloatAsm                    _Mat2AddFloatAsm
#define Mat2SubtractAsm                    _Mat2SubtractAsm
#define Mat2SubtractFloatAsm               _Mat2SubtractFloatAsm
#define Mat2MultiplyAsm                    _Mat2MultiplyAsm
#define Mat2MultiplyVecAsm                 _Mat2MultiplyVecAsm
#define Mat2MultiplyFloatAsm               _Mat2MultiplyFloatAsm
#define Mat2IdentityAsm                    _Mat2IdentityAsm
#define Mat2TransposeAsm                   _Mat2TransposeAsm
#define Mat2MultiplyVecBlockAsm            _Mat2MultiplyVecBlockAsm

#define Mat2uNegateAsm                     _Mat2uNegateAsm
#define Mat2uAddAsm                        _Mat2uAddAsm
#define Mat2uSubtractAsm                   _Mat2uSubtractAsm
#define Mat2uMultiplyAsm                   _Mat2uMultiplyAsm
#define Mat2uMultiplyVecAsm                _Mat2uMultiplyVecAsm
#define Mat2uMultiplyFloatAsm              _Mat2uMultiplyFloatAsm
#define Mat2uIdentityAsm                   _Mat2uIdentityAsm
#define Mat2uTransposeAsm                  _Mat2uTransposeAsm
#define Mat2uMultiplyVecBlockAsm           _Mat2uMultiplyVecBlockAsm

#define Mat2RotateLHAsm                    _Mat2RotateLHAsm
#define Mat2RotateRHAsm                    _Mat2RotateRHAsm
#define Mat2RotateAsm                      _Mat2RotateAsm
#define Mat2ScaleAsm                       _Mat2ScaleAsm

#define Mat3CopyAsm                        _Mat3CopyAsm
#define Mat3IdentityAsm                    _Mat3IdentityAsm

#define Mat3NegateAsm                      _Mat3NegateAsm
#define Mat3AddAsm                         _Mat3AddAsm
#define Mat3AddFloatAsm                    _Mat3AddFloatAsm
#define Mat3SubtractAsm                    _Mat3SubtractAsm
#define Mat3SubtractFloatAsm               _Mat3SubtractFloatAsm

#define Mat3MultiplyAsm                    _Mat3MultiplyAsm
#define Mat3MultiplyIdentityByBlocksAsm    _Mat3MultiplyIdentityByBlocksAsm

#define Mat3MultiplyVecAsm                 _Mat3MultiplyVecAsm
#define Mat3MultiplyVecBlockAsm            _Mat3MultiplyVecBlockAsm
#define Mat3MulVecBlockBySizeAsm           _Mat3MulVecBlockBySizeAsm
#define Mat3MulVec3BufByBufAsm             _Mat3MulVec3BufByBufAsm
#define Mat3MultiplyFloatAsm               _Mat3MultiplyFloatAsm
#define Mat3InverseAsm                     _Mat3InverseAsm
#define Mat3TransposeAsm                   _Mat3TransposeAsm

#define Mat3MultiplyFPU_Asm                _Mat3MultiplyFPU_Asm
#define Mat3MultiplyIdentityByBlockFPU_Asm _Mat3MultiplyIdentityByBlockFPU_Asm

#define Mat3uNegateAsm                     _Mat3uNegateAsm
#define Mat3uAddAsm                        _Mat3uAddAsm
#define Mat3uSubtractAsm                   _Mat3uSubtractAsm

#define Mat3uMultiplyAsm                   _Mat3uMultiplyAsm
#define Mat3uMultiplyIdentityByBlocksAsm   _Mat3uMultiplyIdentityByBlocksAsm

#define Mat3uMultiplyVecAsm                _Mat3uMultiplyVecAsm
#define Mat3uMultiplyVecBlockAsm           _Mat3uMultiplyVecBlockAsm
#define Mat3uMulVecBlockBySizeAsm          _Mat3uMulVecBlockBySizeAsm
#define Mat3uMulVec3BufByBufAsm            _Mat3uMulVec3BufByBufAsm
#define Mat3uMultiplyFloatAsm              _Mat3uMultiplyFloatAsm
#define Mat3uInverseAsm                    _Mat3uInverseAsm
#define Mat3uTransposeAsm                  _Mat3uTransposeAsm

#define Mat3RotateRHX_Asm                  _Mat3RotateRHX_Asm
#define Mat3RotateLHX_Asm                  _Mat3RotateLHX_Asm
#define Mat3RotateRHY_Asm                  _Mat3RotateRHY_Asm
#define Mat3RotateLHY_Asm                  _Mat3RotateLHY_Asm
#define Mat3RotateRHZ_Asm                  _Mat3RotateRHZ_Asm
#define Mat3RotateLHZ_Asm                  _Mat3RotateLHZ_Asm

#define Mat3RotateRHXY_Asm                 _Mat3RotateRHXY_Asm
#define Mat3RotateLHXY_Asm                 _Mat3RotateLHXY_Asm
#define Mat3RotateRHXZ_Asm                 _Mat3RotateRHXZ_Asm
#define Mat3RotateLHXZ_Asm                 _Mat3RotateLHXZ_Asm
#define Mat3RotateRHYZ_Asm                 _Mat3RotateRHYZ_Asm
#define Mat3RotateLHYZ_Asm                 _Mat3RotateLHYZ_Asm

#define Mat3RotateRHXYZ_Asm                _Mat3RotateRHXYZ_Asm
#define Mat3RotateLHXYZ_Asm                _Mat3RotateLHXYZ_Asm

#define Mat3ScaleAsm                       _Mat3ScaleAsm
#define Mat3ScaleByVec3Asm                 _Mat3ScaleByVec3Asm

#define Mat4CopyAsm                        _Mat4CopyAsm

#define Mat4NegateAsm                      _Mat4NegateAsm
#define Mat4NegateMatrixAsm                _Mat4NegateMatrixAsm
#define Mat4AddAsm                         _Mat4AddAsm
#define Mat4AddFloatAsm                    _Mat4AddFloatAsm
#define Mat4AddMatrixAsm                   _Mat4AddMatrixAsm
#define Mat4SubtractAsm                    _Mat4SubtractAsm
#define Mat4SubtractFloatAsm               _Mat4SubtractFloatAsm
#define Mat4SubtractMatrixAsm              _Mat4SubtractMatrixAsm
#define Mat4MultiplyMatrixAsm              _Mat4MultiplyMatrixAsm
#define Mat4MultiplyAsm                    _Mat4MultiplyAsm
#define Mat4MultiplyVecAsm                 _Mat4MultiplyVecAsm
#define Mat4LookAtAsm                      _Mat4LookAtAsm

#define Mat4MultiplyFloatAsm               _Mat4MultiplyFloatAsm
#define Mat4TransposeAsm                   _Mat4TransposeAsm
#define Mat4ShadowMatrixAsm                _Mat4ShadowMatrixAsm
#define Mat4MirrorMatrixAsm                _Mat4MirrorMatrixAsm
#define Mat4LookAtAsm                      _Mat4LookAtAsm
#define Mat4GlToD3DProjMatAsm              _Mat4GlToD3DProjMatAsm
#define Mat4LookAtLHAsm                    _Mat4LookAtLHAsm

#define Mat4uNegateAsm                     _Mat4uNegateAsm
#define Mat4uNegateMatrixAsm               _Mat4uNegateMatrixAsm
#define Mat4uAddAsm                        _Mat4uAddAsm
#define Mat4uAddFloatAsm                   _Mat4uAddFloatAsm
#define Mat4uAddMatrixAsm                  _Mat4uAddMatrixAsm
#define Mat4uSubtractAsm                   _Mat4uSubtractAsm
#define Mat4uSubtractFloatAsm              _Mat4uSubtractFloatAsm
#define Mat4uSubtractMatrixAsm             _Mat4uSubtractMatrixAsm
#define Mat4uMultiplyMatrixAsm             _Mat4uMultiplyMatrixAsm
#define Mat4uMultiplyAsm                   _Mat4uMultiplyAsm
#define Mat4uMultiplyVecAsm                _Mat4uMultiplyVecAsm
#define Mat4uLookAtAsm                     _Mat4uLookAtAsm

#define Mat4uMultiplyFloatAsm              _Mat4uMultiplyFloatAsm
#define Mat4uTransposeAsm                  _Mat4uTransposeAsm
#define Mat4uShadowMatrixAsm               _Mat4uShadowMatrixAsm
#define Mat4uMirrorMatrixAsm               _Mat4uMirrorMatrixAsm
#define Mat4uLookAtAsm                     _Mat4uLookAtAsm
#define Mat4uGlToD3DProjMatAsm             _Mat4uGlToD3DProjMatAsm
#define Mat4uLookAtLHAsm                   _Mat4uLookAtLHAsm

#define Mat4saLookAtAsm                    _Mat4saLookAtAsm
#defime Mat4suLookAtAsm                    _Mat4suLookAtAsm

#define Mat4IdentityAsm                    _Mat4IdentityAsm
#define Mat4ScaleAsm                       _Mat4ScaleAsm

#define Mat4RotateRHX_Asm                  _Mat4RotateRHX_Asm
#define Mat4RotateLHX_Asm                  _Mat4RotateLHX_Asm
#define Mat4RotateRHY_Asm                  _Mat4RotateRHY_Asm
#define Mat4RotateLHY_Asm                  _Mat4RotateLHY_Asm
#define Mat4RotateRHZ_Asm                  _Mat4RotateRHZ_Asm
#define Mat4RotateLHZ_Asm                  _Mat4RotateLHZ_Asm

#define Mat4RotateRHXY_Asm                 _Mat4RotateRHXY_Asm
#define Mat4RotateLHXY_Asm                 _Mat4RotateLHXY_Asm
#define Mat4RotateRHXZ_Asm                 _Mat4RotateRHXZ_Asm
#define Mat4RotateLHXZ_Asm                 _Mat4RotateLHXZ_Asm
#define Mat4RotateRHYZ_Asm                 _Mat4RotateRHYZ_Asm
#define Mat4RotateLHYZ_Asm                 _Mat4RotateLHYZ_Asm

#define Mat4RotateRHXYZ_Asm                _Mat4RotateRHXYZ_Asm
#define Mat4RotateLHXYZ_Asm                _Mat4RotateLHXYZ_Asm

#define Mat4TranslateRH_Asm                _Mat4TranslateRH_Asm
#define Mat4TranslateLH_Asm                _Mat4TranslateLH_Asm
#define Mat4TranslateRH_Vec3Asm            _Mat4TranslateRH_Vec3Asm
#define Mat4TranslateLH_Vec3Asm            _Mat4TranslateLH_Vec3Asm
#define Mat4TranslateRH_Vec4Asm            _Mat4TranslateRH_Vec4Asm
#define Mat4TranslateLH_Vec4Asm            _Mat4TranslateLH_Vec4Asm
#define Mat4OrthoMatrixAsm                 _Mat4OrthoMatrixAsm
#define Mat4OrthoStructAsm                 _Mat4OrthoStructAsm
#define Mat4PerspectiveAsm                 _Mat4PerspectiveAsm
#define Mat4PerspectiveXAsm                _Mat4PerspectiveXAsm
#define Mat4CubemapMatrixAsm               _Mat4CubemapMatrixAsm
#define Mat4CubemapProjectionMatAsm        _Mat4CubemapProjectionMatAsm
#define Mat4LookAtHorizAsm                 _Mat4LookAtHorizAsm

#define Mat3RotationFromMat4Asm            _Mat3RotationFromMat4Asm
#define Mat4FromMat3Asm                    _Mat4FromMat3Asm

#define QuaternionAddAsm                   _QuaternionAddAsm
#define QuaternionMultiplyAsm              _QuaternionMultiplyAsm
#define QuaternionInverseAsm               _QuaternionInverseAsm
#define QuaternionToMat3Asm                _QuaternionToMat3Asm
#define QuaternionToMat4Asm                _QuaternionToMat4Asm

#define QuaternionNormalizeFlatAsm         _QuaternionNormalizeFlatAsm
#define QuaternionDotFlatAsm               _QuaternionDotFlatAsm

#define QuaternionNormalizeAsm             _QuaternionNormalizeAsm
#define QuaternionDotAsm                   _QuaternionDotAsm

#define QuaternionDotFPU_Asm               _QuaternionDotFPU_Asm

#define uQuaternionAddAsm                  _uQuaternionAddAsm
#define uQuaternionMultiplyAsm             _uQuaternionMultiplyAsm
#define uQuaternionInverseAsm              _uQuaternionInverseAsm
#define uQuaternionToMat3Asm               _uQuaternionToMat3Asm
#define uQuaternionToMat4Asm               _uQuaternionToMat4Asm

#define uQuaternionNormalizeFlatAsm        _uQuaternionNormalizeFlatAsm
#define uQuaternionDotFlatAsm              _uQuaternionDotFlatAsm

#define uQuaternionNormalizeAsm            _uQuaternionNormalizeAsm
#define uQuaternionDotAsm                  _uQuaternionDotAsm

#define QuaternionFromAxisAsm              _QuaternionFromAxisAsm
#define QuaternionFromMat3Asm              _QuaternionFromMat3Asm
#define QuaternionFromMat4Asm              _QuaternionFromMat4Asm
#define QuaternionFromMat3Asm              _QuaternionFromMat3Asm
#define QuaternionFromMat4Asm              _QuaternionFromMat4Asm
#define QuaternionSlerpAsm                 _QuaternionSlerpAsm
#define QuaternionCosAsm                   _QuaternionCosAsm
#define QuaternionSinAsm                   _QuaternionSinAsm

#endif

/* ------------------------ *
 * Advanced Aligned Library *
 * -------------------------*--------------------------------------------- *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if defined(__BUILD_ADVANCED_ALIGNED_LIB) || defined(__ADVANCED_ALIGNED_LIB)


#if !defined(__REGRESSION_TEST)
  #define GetFpuStatus                    GetFpuStatusAsm
  #define ClearFpuStatus                  ClearFpuStatusAsm
  #define FloatLerp                       FloatLerpAsm
  #define FloatLerpPtr                    FloatLerpPtrAsm
  #define FloatSqr                        FloatSqrAsm
  #define FloatSqrPtr                     FloatSqrPtrAsm
  #define fCos                            fCosAsm
  #define fSin                            fSinAsm
  #define fTan                            fTanAsm
  #define fACos                           AfCosAsm
  #define fASin                           AfSinAsm
  #define fATan                           AfTanAsm
  #define Cos                             CosAsm
  #define Sin                             SinAsm
  #define Tan                             TanAsm
  #define ACos                            ACosAsm
  #define ASin                            ASinAsm
  #define ATan                            ATanAsm
#endif

extern __C void  GetFpuStatusAsm(unsigned short* uStatus);
extern __C void  ClearFpuStatusAsm(unsigned short* uStatus);
extern __C float FloatLerpAsm   (const float x,const float v,const float u);
extern __C void  FloatLerpPtrAsm(float* ret,const float* u,const float* v,const float* x);
extern __C float FloatSqrAsm    (float x);
extern __C float FloatSqrPtrAsm (float* x);

extern __C float fCosAsm(const float angle);
extern __C float fSinAsm(const float angle);
extern __C float fTanAsm(const float angle);
extern __C float AfCosAsm(const float cosa);
extern __C float AfSinAsm(const float sina);
extern __C float AfTanAsm(const float tana);

extern __C double CosAsm(const double angle);
extern __C double SinAsm(const double angle);
extern __C double TanAsm(const double angle);
extern __C double ACosAsm(const double cosa);
extern __C double ASinAsm(const double sina);
extern __C double ATanAsm(const double tana);

#if !defined(__REGRESSION_TEST)
  #define Vec2Copy                        Vec2CopyAsm
  #define Vec2CopyBlock                   Vec2CopyBlockAsm
  #define BuildVec2PackedArray            BuildVec2PackedArrayAsm
#endif

extern __C void Vec2CopyAsm            (vec2* r,const vec2* v);
extern __C void Vec2CopyBlockAsm       (vec2* r,vec2* v,int32_t iCount);
extern __C void BuildVec2PackedArrayAsm(vec2* r,const vec2** ppList,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddFloat                    Vec2AddFloatAsm
  #define Vec2SubtractFloat               Vec2SubtractFloatAsm
  #define Vec2MultiplyFloat               Vec2MultiplyFloatAsm
  #define Vec2FloatMultiply               Vec2FloatMultiplyAsm
  #define Vec2DivideFloat                 Vec2DivideFloatAsm
  #define Vec2AddFloatToBlock             Vec2AddFloatToBlockAsm
  #define Vec2AddFloatToBlockSize         Vec2AddFloatToBlockSizeAsm
  #define Vec2BufAddFloatToBlock          Vec2BufAddFloatToBlockAsm
  #define Vec2BufAddFloatToBuf            Vec2BufAddFloatToBufAsm
#endif

extern __C void Vec2AddFloatAsm     (vec2* r,const vec2* u,const float s);
extern __C void Vec2SubtractFloatAsm(vec2* r,const vec2* u,const float s);
extern __C void Vec2MultiplyFloatAsm(vec2* r,const vec2* u,const float s);
extern __C void Vec2FloatMultiplyAsm(vec2* r,const float s,const vec2* v);
extern __C void Vec2DivideFloatAsm  (vec2* r,const vec2* u,const float s);
extern __C void Vec2AddFloatToBlockAsm    (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2AddFloatToBlockSizeAsm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBlockAsm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBufAsm   (void*  r,const int32_t iRSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2SubtractFloatFromBlock      Vec2SubtractFloatFromBlockAsm
  #define Vec2SubFloatFromBlockSize       Vec2SubFloatFromBlockSizeAsm
  #define Vec2BufSubFloatFromBlkSize      Vec2BufSubFloatFromBlkSizeAsm
  #define Vec2BufSubFloatFromBuf          Vec2BufSubFloatFromBufAsm
#endif

extern __C void Vec2SubtractFloatFromBlockAsm(vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2SubFloatFromBlockSizeAsm (vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBlkSizeAsm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBufAsm    (void*  r,const int32_t iDstSize,const void* pSource,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2MultiplyBlockByFloat        Vec2MultiplyBlockByFloatAsm
  #define Vec2MultiplyBlkByFloatSize      Vec2MultiplyBlkByFloatSizeAsm
  #define Vec2BufMulBlockByFloatSize      Vec2BufMulBlockByFloatSizeAsm
  #define Vec2BufMulBlockByFloatBuf       Vec2BufMulBlockByFloatBufAsm // XXX: Rename required
#endif

extern __C void Vec2MultiplyBlockByFloatAsm (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2MultiplyBlkByFloatSizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatSizeAsm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatBufAsm (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2DivideBlockByFloat          Vec2DivideBlockByFloatAsm
  #define Vec2DivideBlockByFloatSize      Vec2DivideBlockByFloatSizeAsm
  #define Vec2BufDivBlockByFloatSize      Vec2BufDivBlockByFloatSizeAsm
  #define Vec2BufDivBufByFloat            Vec2BufDivBufByFloatAsm
#endif

extern __C void Vec2DivideBlockByFloatAsm    (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2DivideBlockByFloatSizeAsm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockByFloatSizeAsm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufByFloatAsm      (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2Negate                      Vec2NegateAsm
  #define Vec2Add                         Vec2AddAsm
  #define Vec2Subtract                    Vec2SubtractAsm
  #define Vec2Multiply                    Vec2MultiplyAsm
  #define Vec2Divide                      Vec2DivideAsm
#endif

extern __C void Vec2NegateAsm  (vec2* r,const vec2* u);
extern __C void Vec2AddAsm     (vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2SubtractAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2MultiplyAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2DivideAsm  (vec2* r,const vec2* u,const vec2* v);

#if !defined(__REGRESSION_TEST)
  #define Vec2Equals                      Vec2EqualsAsm
  #define Vec2NotEquals                   Vec2NotEqualsAsm
#endif

extern __C void Vec2EqualsAsm   (int32_t* iFlag,const vec2* u,const vec2* v);
extern __C void Vec2NotEqualsAsm(int32_t* iFlag,const vec2* u,const vec2* v);

#if !defined(__REGRESSION_TEST)
  #define Vec2NegateBlock                 Vec2NegateBlockAsm
  #define Vec2NegateBlockBySize           Vec2NegateBlockBySizeAsm
  #define Vec2BufNegateBlockBySize        Vec2BufNegateBlockBySizeAsm
  #define Vec2BufNegateBufBySize          Vec2BufNegateBufBySizeAsm
#endif

extern __C void Vec2NegateBlockAsm         (vec2* pSource_Dest,int32_t iCount);
extern __C void Vec2NegateBlockBySizeAsm   (vec2* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBlockBySizeAsm(vec2*  r,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBufBySizeAsm  (vec2*  r,const int32_t iDstSize,const vec2* v,const int32_t iSrcSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddVec2ToBlock              Vec2AddVec2ToBlockAsm
  #define Vec2AddBlockToBlock             Vec2AddBlockToBlockAsm
  #define Vec2BufAddVec2ToBlockBySize     Vec2BufAddVec2ToBlockBySizeAsm
  #define Vec2BufAddBlockBySize           Vec2BufAddBlockBySizeAsm
  #define Vec2BufAddBufBySize             Vec2BufAddBufBySizeAsm
#endif

extern __C void Vec2AddVec2ToBlockAsm         (vec2* rv,const vec2* v,const int32_t iCount);
extern __C void Vec2AddBlockToBlockAsm        (vec2* rv,const vec2* v,int32_t iCount);
extern __C void Vec2BufAddVec2ToBlockBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2SubtractVec2FromBlock       Vec2SubtractVec2FromBlockAsm
  #define Vec2SubtractBlockFromBlock      Vec2SubtractBlockFromBlockAsm
  #define Vec2BufSubVec2FromBlkBySize     Vec2BufSubVec2FromBlkBySizeAsm
  #define Vec2BufSubBlockBySize           Vec2BufSubBlockBySizeAsm
  #define Vec2BufSubBufBySize             Vec2BufSubBufBySizeAsm
#endif

extern __C void Vec2SubtractVec2FromBlockAsm  (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2SubtractBlockFromBlockAsm (vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufSubVec2FromBlkBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2MultiplyBlockByVec2         Vec2MultiplyBlockByVec2Asm
  #define Vec2MultiplyBlockByBlock        Vec2MultiplyBlockByBlockAsm
  #define Vec2BufMulVec2ByBlockSize       Vec2BufMulVec2ByBlockSizeAsm
  #define Vec2BufMulBlockBySize           Vec2BufMulBlockBySizeAsm
  #define Vec2BufMulBufBySize             Vec2BufMulBufBySizeAsm
#endif

extern __C void Vec2MultiplyBlockByVec2Asm  (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2MultiplyBlockByBlockAsm (vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufMulVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2DivideBlockByVec2           Vec2DivideBlockByVec2Asm
  #define Vec2DivideBlockByBlock          Vec2DivideBlockByBlockAsm
  #define Vec2BufDivVec2ByBlockSize       Vec2BufDivVec2ByBlockSizeAsm
  #define Vec2BufDivBlockBySize           Vec2BufDivBlockBySizeAsm
  #define Vec2BufDivBufBySize             Vec2BufDivBufBySizeAsm
#endif

extern __C void Vec2DivideBlockByVec2Asm    (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2DivideBlockByBlockAsm   (vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufDivVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

// XXX: Missing buffer definitions for these methods
//

#if !defined(__REGRESSION_TEST)
  #define Vec2LerpBlock                   Vec2LerpBlockAsm
  #define Vec2SqrBlock                    Vec2SqrBlockAsm
  #define Vec2SqrtBlock                   Vec2SqrtBlockAsm
  #define Vec2NormalizeBlock              Vec2NormalizeBlockAsm
  #define Vec2DotBlock                    Vec2DotBlockAsm
#endif

extern __C void Vec2LerpBlockAsm     (vec2*  r,const vec2* u,const vec2* v,const float step,const int32_t iCount);
extern __C void Vec2SqrBlockAsm      (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2SqrtBlockAsm     (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2NormalizeBlockAsm(vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2DotBlockAsm      (float* r,const vec2* u,const vec2* v,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2Lerp                        Vec2LerpAsm
  #define Vec2Sqr                         Vec2SqrAsm
  #define Vec2Sqrt                        Vec2SqrtAsm
  #define Vec2Normalize                   Vec2NormalizeAsm
  #define Vec2Dot                         Vec2DotAsm
  #define Vec2Length                      Vec2LengthAsm
  #define Vec2LengthBlock                 Vec2LengthBlockAsm
#endif

extern __C void Vec2LerpAsm       (vec2*  r,const vec2* u,const vec2* v,const float step);
extern __C void Vec2SqrAsm        (vec2*  r,const vec2* u);
extern __C void Vec2SqrtAsm       (vec2*  r,const vec2* u);
extern __C void Vec2NormalizeAsm  (vec2*  r,const vec2* v);
extern __C void Vec2DotAsm        (float* f,const vec2* u,const vec2* v);
extern __C void Vec2LengthAsm     (float* r,const vec2* v);
extern __C void Vec2LengthBlockAsm(float* r,const vec2* v,const int32_t nCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2BufLerpBuf                  Vec2BufLerpBufAsm
  #define Vec2BufSqrBuf                   Vec2BufSqrBufAsm
  #define Vec2BufSqrtBuf                  Vec2BufSqrtBufAsm
  #define Vec2BufNormalizeBuf             Vec2BufNormalizeBufAsm
  #define Vec2BufDotBuf                   Vec2BufDotBufAsm
  #define Vec2BufLengthBuf                Vec2BufLengthBufAsm
#endif

extern __C void Vec2BufLerpBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);
extern __C void Vec2BufSqrBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufSqrtBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufNormalizeBufAsm(void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufDotBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Vec2BufLengthBufAsm   (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Copy                        Vec3CopyAsm
  #define Vec3CopyBlock                   Vec3CopyBlockAsm
  #define BuildVec3PackedArray            BuildVec3PackedArrayAsm
#endif

extern __C void Vec3CopyAsm            (vec3* r,const vec3*  u);
extern __C void Vec3CopyBlockAsm       (vec3* r,const vec3*  u,const int32_t iCount);
extern __C void BuildVec3PackedArrayAsm(vec3* r,const vec3** pu,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3AddFloat                    Vec3AddFloatAsm
  #define Vec3AddFloatToBlock             Vec3AddFloatToBlockAsm
  #define Vec3AddFloatToBlockBySize       Vec3AddFloatToBlockBySizeAsm
  #define Vec3BufAddFloatToBlock          Vec3BufAddFloatToBlockAsm
  #define Vec3BufAddFloatToBuf            Vec3BufAddFloatToBufAsm
#endif

extern __C void Vec3AddFloatAsm             (vec3*  r,const vec3* v,const float s);
extern __C void Vec3AddFloatToBlockAsm      (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3AddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3SubtractFloat               Vec3SubtractFloatAsm
  #define Vec3SubtractFloatFromBlock      Vec3SubtractFloatFromBlockAsm
  #define Vec3SubFloatFromBlockBySize     Vec3SubFloatFromBlockBySizeAsm
  #define Vec3BufSubFloatFromBlock        Vec3BufSubFloatFromBlockAsm
  #define Vec3BufSubFloatFromBuf          Vec3BufSubFloatFromBufAsm
#endif

extern __C void Vec3SubtractFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3SubtractFloatFromBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3SubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3MultiplyFloat               Vec3MultiplyFloatAsm
  #define Vec3MultiplyFloatToBlock        Vec3MultiplyFloatToBlockAsm
  #define Vec3MulFloatToBlockBySize       Vec3MulFloatToBlockBySizeAsm
  #define Vec3BufMulFloatToBlock          Vec3BufMulFloatToBlockAsm
  #define Vec3BufMulFloatToBuf            Vec3BufMulFloatToBufAsm
#endif

extern __C void Vec3MultiplyFloatAsm        (vec3*  r,const vec3* u,const float s);
extern __C void Vec3MultiplyFloatToBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3MulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3DivideFloat                 Vec3DivideFloatAsm
  #define Vec3DivideBlockByFloat          Vec3DivideBlockByFloatAsm
  #define Vec3DivBlockByFloatBySize       Vec3DivBlockByFloatBySizeAsm
  #define Vec3BufDivBlockByFloat          Vec3BufDivBlockByFloatAsm
  #define Vec3BufDivBufByFloat            Vec3BufDivBufByFloatAsm
#endif

extern __C void Vec3DivideFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3DivideBlockByFloatAsm   (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3DivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Equals                      Vec3EqualsAsm
  #define Vec3NotEquals                   Vec3NotEqualsAsm
#endif

extern __C void Vec3EqualsAsm   (int32_t* iFlag,const vec3* u,const vec3* v);
extern __C void Vec3NotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Vec3Negate                      Vec3NegateAsm
  #define Vec3NegateBlock                 Vec3NegateBlockAsm
  #define Vec3NegateBlockBySize           Vec3NegateBlockBySizeAsm
  #define Vec3BufNegateBlock              Vec3BufNegateBlockAsm
  #define Vec3BufNegateBuf                Vec3BufNegateBufAsm
#endif

extern __C void Vec3NegateAsm           (vec3*  r,const vec3* v);
extern __C void Vec3NegateBlockAsm      (vec3* rv,int32_t iCount);
extern __C void Vec3NegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Add                         Vec3AddAsm
  #define Vec3AddVecToBlock               Vec3AddVecToBlockAsm
  #define Vec3AddVecToBlockBySize         Vec3AddVecToBlockBySizeAsm
  #define Vec3BufAddVecToBlock            Vec3BufAddVecToBlockAsm
  #define Vec3BufAddVecToBuf              Vec3BufAddVecToBufAsm
  #define Vec3AddBlockToBlock             Vec3AddBlockToBlockAsm
  #define Vec3AddBlockToBlockBySize       Vec3AddBlockToBlockBySizeAsm
  #define Vec3BufAddBlockToBuf            Vec3BufAddBlockToBufAsm
  #define Vec3BufAddBufToBuf              Vec3BufAddBufToBufAsm
#endif

extern __C void Vec3AddAsm                  (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3AddVecToBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3AddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec3AddBlockToBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3AddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Subtract                    Vec3SubtractAsm
  #define Vec3SubVecFromBlock             Vec3SubVecFromBlockAsm
  #define Vec3SubVecFromBlockBySize       Vec3SubVecFromBlockBySizeAsm
  #define Vec3BufSubVecFromBlock          Vec3BufSubVecFromBlockAsm
  #define Vec3BufSubVecFromBuf            Vec3BufSubVecFromBufAsm
  #define Vec3SubBlockFromBlock           Vec3SubBlockFromBlockAsm
  #define Vec3SubBlockFromBlockBySize     Vec3SubBlockFromBlockBySizeAsm
  #define Vec3BufSubBlockFromBuf          Vec3BufSubBlockFromBufAsm
  #define Vec3BufSubBufFromBuf            Vec3BufSubBufFromBufAsm
#endif

extern __C void Vec3SubtractAsm               (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3SubVecFromBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3SubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3SubBlockFromBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3SubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Multiply                    Vec3MultiplyAsm
  #define Vec3MulBlockByVec               Vec3MulBlockByVecAsm
  #define Vec3MulBlockByVecUseSize        Vec3MulBlockByVecUseSizeAsm
  #define Vec3BufMulBufByVec              Vec3BufMulBufByVecAsm
  #define Vec3BufMulBufByVecUseSize       Vec3BufMulBufByVecUseSizeAsm
  #define Vec3MulBlockByBlock             Vec3MulBlockByBlockAsm
  #define Vec3MulBlockByBlockUseSize      Vec3MulBlockByBlockUseSizeAsm
  #define Vec3BufMulBufByBlock            Vec3BufMulBufByBlockAsm
  #define Vec3BufMulBufByBuf	          Vec3BufMulBufByBufAsm
#endif

extern __C void Vec3MultiplyAsm              (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3MulBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3BufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3MulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3MulBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3MulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Divide                      Vec3DivideAsm
  #define Vec3DivBlockByVec               Vec3DivBlockByVecAsm
  #define Vec3DivBlockByVecUseSize        Vec3DivBlockByVecUseSizeAsm
  #define Vec3BufDivBufByVec              Vec3BufDivBufByVecAsm
  #define Vec3BufDivBufByVecUseSize       Vec3BufDivBufByVecUseSizeAsm
  #define Vec3DivBlockByBlock             Vec3DivBlockByBlockAsm
  #define Vec3DivBlockByBlockUseSize      Vec3DivBlockByBlockUseSizeAsm
  #define Vec3BufDivBufByBlock            Vec3BufDivBufByBlockAsm
  #define Vec3BufDivBufByBuf              Vec3BufDivBufByBufAsm
#endif

extern __C void Vec3DivideAsm                (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3DivBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByVecUseSizeAsm  (void* ru,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByVecAsm        (void*  r,const void* u,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Lerp                        Vec3LerpAsm
  #define Vec3LerpBlock                   Vec3LerpBlockAsm
  #define Vec3LerpBlockUseSize            Vec3LerpBlockUseSizeAsm
  #define Vec3BufLerpBlock                Vec3BufLerpBlockAsm
  #define Vec3BufLerpBuf                  Vec3BufLerpBufAsm
#endif

extern __C void Vec3LerpAsm            (vec3*  r,const vec3* u,const vec3* v,const float s);
extern __C void Vec3LerpBlockAsm       (vec3* ru,vec3* v,const float s,const int32_t iCount);
extern __C void Vec3LerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec3BufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Dot                         Vec3DotAsm
  #define Vec3DotBlock                    Vec3DotBlockAsm
  #define Vec3DotBlockUseSize             Vec3DotBlockUseSizeAsm
  #define Vec3BufDotBuf                   Vec3BufDotBufAsm
#endif

extern __C void Vec3DotAsm            (float* r,const vec3* u,const vec3* v);
extern __C void Vec3DotBlockAsm       (float* r,const vec3* u,const vec3* v,const int32_t iCount);
extern __C void Vec3DotBlockUseSizeAsm(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDotBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Sqr                         Vec3SqrAsm
  #define Vec3SqrBlock                    Vec3SqrBlockAsm
  #define Vec3SqrBlockUseSize             Vec3SqrBlockUseSizeAsm
  #define Vec3BufSqrBuf                   Vec3BufSqrBufAsm
#endif

extern __C void Vec3SqrAsm            (vec3*  r,const vec3* v);
extern __C void Vec3SqrBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3SqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Sqrt                        Vec3SqrtAsm
  #define Vec3SqrtBlock                   Vec3SqrtBlockAsm
  #define Vec3SqrtBlockUseSize            Vec3SqrtBlockUseSizeAsm
  #define Vec3BufSqrtBuf                  Vec3BufSqrtBufAsm
#endif

extern __C void Vec3SqrtAsm            (vec3*  r,const vec3* v);
extern __C void Vec3SqrtBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3SqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Normalize                   Vec3NormalizeAsm
  #define Vec3NormalizeBlock              Vec3NormalizeBlockAsm
  #define Vec3NormalizeBlockUseSize       Vec3NormalizeBlockUseSizeAsm
  #define Vec3BufNormalizeBuf             Vec3BufNormalizeBufAsm
#endif

extern __C void Vec3NormalizeAsm                (vec3*  r,const vec3* v);
extern __C void Vec3NormalizeBlockAsm           (vec3* ru,const int32_t iCount);
extern __C void Vec3NormalizeBlockUseSizeAsm    (vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNormalizeBufAsm          (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Length                      Vec3LengthAsm
  #define Vec3LengthBlock                 Vec3LengthBlockAsm
  #define Vec3LengthBlockUseSize          Vec3LengthBlockUseSizeAsm
  #define Vec3BufLengthBuf                Vec3BufLengthBufAsm
#endif

extern __C void Vec3LengthAsm            (float* r,const vec3* v);
extern __C void Vec3LengthBlockAsm       (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3LengthBlockUseSizeAsm(float* r,const vec3* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLengthBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Cross                       Vec3CrossAsm
  #define Vec3CrossBlock                  Vec3CrossBlockAsm
  #define Vec3CrossBlockUseSize           Vec3CrossBlockUseSizeAsm
  #define Vec3BufCrossBuf                 Vec3BufCrossBufAsm
#endif

extern __C void Vec3CrossAsm             (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3CrossBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3CrossBlockUseSizeAsm (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufCrossBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Reflect                     Vec3ReflectAsm
#endif

extern __C void Vec3ReflectAsm (vec3* r,const vec3* u,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Vec4Copy                        Vec4CopyAsm
  #define Vec4CopyBlock                   Vec4CopyBlockAsm
  #define BuildVec4PackedArray            BuildVec4PackedArrayAsm
#endif

extern __C void Vec4CopyAsm            (vec4* r,const vec4*  u);
extern __C void Vec4CopyBlockAsm       (vec4* r,const vec4*  u,const int32_t iCount);
extern __C void BuildVec4PackedArrayAsm(vec4* r,const vec4** pu,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4AddFloat                    Vec4AddFloatAsm
  #define Vec4AddFloatToBlock             Vec4AddFloatToBlockAsm
  #define Vec4AddFloatToBlockBySize       Vec4AddFloatToBlockBySizeAsm
  #define Vec4BufAddFloatToBlock          Vec4BufAddFloatToBlockAsm
  #define Vec4BufAddFloatToBuf            Vec4BufAddFloatToBufAsm
#endif

extern __C void Vec4AddFloatAsm             (vec4*  r,const vec4* v,const float s);
extern __C void Vec4AddFloatToBlockAsm      (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4AddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4SubtractFloat               Vec4SubtractFloatAsm
  #define Vec4SubtractFloatFromBlock      Vec4SubtractFloatFromBlockAsm
  #define Vec4SubFloatFromBlockBySize     Vec4SubFloatFromBlockBySizeAsm
  #define Vec4BufSubFloatFromBlock        Vec4BufSubFloatFromBlockAsm
  #define Vec4BufSubFloatFromBuf          Vec4BufSubFloatFromBufAsm
#endif

extern __C void Vec4SubtractFloatAsm          (vec4* r,const vec4* u,const float s);
extern __C void Vec4SubtractFloatFromBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4SubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4MultiplyFloat               Vec4MultiplyFloatAsm
  #define Vec4MultiplyFloatToBlock        Vec4MultiplyFloatToBlockAsm
  #define Vec4MulFloatToBlockBySize       Vec4MulFloatToBlockBySizeAsm
  #define Vec4BufMulFloatToBlock          Vec4BufMulFloatToBlockAsm
  #define Vec4BufMulFloatToBuf            Vec4BufMulFloatToBufAsm
#endif

extern __C void Vec4MultiplyFloatAsm        (vec4*  r,const vec4* u,const float s);
extern __C void Vec4MultiplyFloatToBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4MulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4DivideFloat                 Vec4DivideFloatAsm
  #define Vec4DivideBlockByFloat          Vec4DivideBlockByFloatAsm
  #define Vec4DivBlockByFloatBySize       Vec4DivBlockByFloatBySizeAsm
  #define Vec4BufDivBlockByFloat          Vec4BufDivBlockByFloatAsm
  #define Vec4BufDivBufByFloat            Vec4BufDivBufByFloatAsm
#endif

extern __C void Vec4DivideFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4DivideBlockByFloatAsm   (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4DivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Equals                      Vec4EqualsAsm
  #define Vec4NotEquals                   Vec4NotEqualsAsm
#endif

extern __C void Vec4EqualsAsm   (int32_t* iFlag,const vec4* u,const vec4* v);
extern __C void Vec4NotEqualsAsm(int32_t* iFlag,const vec4* u,const vec4* v);

#if !defined(__REGRESSION_TEST)
  #define Vec4Negate                      Vec4NegateAsm
  #define Vec4NegateBlock                 Vec4NegateBlockAsm
  #define Vec4NegateBlockBySize           Vec4NegateBlockBySizeAsm
  #define Vec4BufNegateBlock              Vec4BufNegateBlockAsm
  #define Vec4BufNegateBuf                Vec4BufNegateBufAsm
#endif

extern __C void Vec4NegateAsm           (vec4*  r,const vec4* v);
extern __C void Vec4NegateBlockAsm      (vec4* rv,int32_t iCount);
extern __C void Vec4NegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Add                         Vec4AddAsm
  #define Vec4AddVecToBlock               Vec4AddVecToBlockAsm
  #define Vec4AddVecToBlockBySize         Vec4AddVecToBlockBySizeAsm
  #define Vec4BufAddVecToBlock            Vec4BufAddVecToBlockAsm
  #define Vec4BufAddVecToBuf              Vec4BufAddVecToBufAsm
  #define Vec4AddBlockToBlock             Vec4AddBlockToBlockAsm
  #define Vec4AddBlockToBlockBySize       Vec4AddBlockToBlockBySizeAsm
  #define Vec4BufAddBlockToBuf            Vec4BufAddBlockToBufAsm
  #define Vec4BufAddBufToBuf              Vec4BufAddBufToBufAsm
#endif

extern __C void Vec4AddAsm                  (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4AddVecToBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4AddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec4AddBlockToBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4AddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Subtract                    Vec4SubtractAsm
  #define Vec4SubVecFromBlock             Vec4SubVecFromBlockAsm
  #define Vec4SubVecFromBlockBySize       Vec4SubVecFromBlockBySizeAsm
  #define Vec4BufSubVecFromBlock          Vec4BufSubVecFromBlockAsm
  #define Vec4BufSubVecFromBuf            Vec4BufSubVecFromBufAsm
  #define Vec4SubBlockFromBlock           Vec4SubBlockFromBlockAsm
  #define Vec4SubBlockFromBlockBySize     Vec4SubBlockFromBlockBySizeAsm
  #define Vec4BufSubBlockFromBuf          Vec4BufSubBlockFromBufAsm
  #define Vec4BufSubBufFromBuf            Vec4BufSubBufFromBufAsm
#endif

extern __C void Vec4SubtractAsm               (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4SubVecFromBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4SubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4SubBlockFromBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4SubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Multiply                    Vec4MultiplyAsm
  #define Vec4MulBlockByVec               Vec4MulBlockByVecAsm
  #define Vec4MulBlockByVecUseSize        Vec4MulBlockByVecUseSizeAsm
  #define Vec4BufMulBufByVec              Vec4BufMulBufByVecAsm
  #define Vec4BufMulBufByVecUseSize       Vec4BufMulBufByVecUseSizeAsm
  #define Vec4MulBlockByBlock             Vec4MulBlockByBlockAsm
  #define Vec4MulBlockByBlockUseSize      Vec4MulBlockByBlockUseSizeAsm
  #define Vec4BufMulBufByBlock            Vec4BufMulBufByBlockAsm
  #define Vec4BufMulBufByBuf              Vec4BufMulBufByBufAsm
#endif

extern __C void Vec4MultiplyAsm              (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4MulBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4MulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4MulBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4MulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Divide                      Vec4DivideAsm
  #define Vec4DivBlockByVec               Vec4DivBlockByVecAsm
  #define Vec4DivBlockByVecUseSize        Vec4DivBlockByVecUseSizeAsm
  #define Vec4BufDivBufByVec              Vec4BufDivBufByVecAsm
  #define Vec4BufDivBufByVecUseSize       Vec4BufDivBufByVecUseSizeAsm
  #define Vec4DivBlockByBlock             Vec4DivBlockByBlockAsm
  #define Vec4DivBlockByBlockUseSize      Vec4DivBlockByBlockUseSizeAsm
  #define Vec4BufDivBufByBlock            Vec4BufDivBufByBlockAsm
  #define Vec4BufDivBufByBuf              Vec4BufDivBufByBufAsm
#endif

extern __C void Vec4DivideAsm                (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4DivBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByVecUseSizeAsm  (void* ru,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByVecAsm        (void*  r,const void* u,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Lerp                        Vec4LerpAsm
  #define Vec4LerpBlock                   Vec4LerpBlockAsm
  #define Vec4LerpBlockUseSize            Vec4LerpBlockUseSizeAsm
  #define Vec4BufLerpBlock                Vec4BufLerpBlockAsm
  #define Vec4BufLerpBuf                  Vec4BufLerpBufAsm
#endif

extern __C void Vec4LerpAsm            (vec4*  r,const vec4* u,const vec4* v,const float s);
extern __C void Vec4LerpBlockAsm       (vec4* ru,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4LerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4BufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Dot                         Vec4DotAsm
  #define Vec4DotBlock                    Vec4DotBlockAsm
  #define Vec4DotBlockUseSize             Vec4DotBlockUseSizeAsm
  #define Vec4BufDotBuf                   Vec4BufDotBufAsm
#endif

extern __C void Vec4DotAsm                 (float* r,const vec4* u,const vec4* v);
extern __C void Vec4DotBlockAsm            (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4DotBlockUseSizeAsm     (float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDotBufAsm           (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Sqr                         Vec4SqrAsm
  #define Vec4SqrBlock                    Vec4SqrBlockAsm
  #define Vec4SqrBlockUseSize             Vec4SqrBlockUseSizeAsm
  #define Vec4BufSqrBuf                   Vec4BufSqrBufAsm
#endif

extern __C void Vec4SqrAsm            (vec4*  r,const vec4* v);
extern __C void Vec4SqrBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4SqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Sqrt                        Vec4SqrtAsm
  #define Vec4SqrtBlock                   Vec4SqrtBlockAsm
  #define Vec4SqrtBlockUseSize            Vec4SqrtBlockUseSizeAsm
  #define Vec4BufSqrtBuf                  Vec4BufSqrtBufAsm
#endif

extern __C void Vec4SqrtAsm            (vec4*  r,const vec4* v);
extern __C void Vec4SqrtBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4SqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Normalize                   Vec4NormalizeAsm
  #define Vec4NormalizeBlock              Vec4NormalizeBlockAsm
  #define Vec4NormalizeBlockUseSize       Vec4NormalizeBlockUseSizeAsm
  #define Vec4BufNormalizeBuf             Vec4BufNormalizeBufAsm
#endif

extern __C void Vec4NormalizeAsm                 (vec4*  r,const vec4* v);
extern __C void Vec4NormalizeBlockAsm            (vec4* ru,const int32_t iCount);
extern __C void Vec4NormalizeBlockUseSizeAsm     (vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNormalizeBufAsm           (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Length                      Vec4LengthAsm
  #define Vec4LengthBlock                 Vec4LengthBlockAsm
  #define Vec4LengthBlockUseSize          Vec4LengthBlockUseSizeAsm
  #define Vec4BufLengthBuf                Vec4BufLengthBufAsm
#endif

extern __C void Vec4LengthAsm              (float* r,const vec4* v);
extern __C void Vec4LengthBlockAsm         (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4LengthBlockUseSize     (float* r,const vec4* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLengthBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Cross                       Vec4CrossAsm
  #define Vec4CrossBlock                  Vec4CrossBlockAsm
  #define Vec4CrossBlockUseSize           Vec4CrossBlockUseSizeAsm
  #define Vec4BufCrossBuf                 Vec4BufCrossBufAsm
#endif

extern __C void Vec4CrossAsm            (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4CrossBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4CrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Mat2Negate                      Mat2NegateAsm
  #define Mat2Add                         Mat2AddAsm
  #define Mat2AddFloat                    Mat2AddFloatAsm
  #define Mat2Subtract                    Mat2SubtractAsm
  #define Mat2SubtractFloat               Mat2SubtractFloatAsm
  #define Mat2Multiply                    Mat2MultiplyAsm
  #define Mat2MultiplyVec                 Mat2MultiplyVecAsm
  #define Mat2MultiplyFloat               Mat2MultiplyFloatAsm
  #define Mat2Identity                    Mat2IdentityAsm
  #define Mat2Transpose                   Mat2TransposeAsm
  #define Mat2MultiplyVecBlock            Mat2MultiplyVecBlockAsm
#endif

extern __C void Mat2NegateAsm          (mat2* r,const mat2* m);
extern __C void Mat2AddAsm             (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2AddFloatAsm        (mat2* r,const mat2* m,const float s);
extern __C void Mat2SubtractAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2SubtractFloatAsm   (mat2* r,const mat2* m,const float s);
extern __C void Mat2MultiplyAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2MultiplyVecAsm     (vec2* r,const mat2* m,const vec2* v);
extern __C void Mat2MultiplyFloatAsm   (mat2* r,const mat2* m,const float x);
extern __C void Mat2IdentityAsm        (mat2* r);
extern __C void Mat2TransposeAsm       (mat2* r,const mat2* m);
extern __C void Mat2MultiplyVecBlockAsm(vec2* r,const mat2* m,const vec2* v,int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Mat2RotateLH                    Mat2RotateLHAsm
  #define Mat2RotateRH                    Mat2RotateRHAsm
  #define Mat2Rotate                      Mat2RotateAsm
  #define Mat2Scale                       Mat2ScaleAsm
#endif

extern __C void Mat2RotateLHAsm(mat2* r,const float angle);
extern __C void Mat2RotateRHAsm(mat2* r,const float angle);
extern __C void Mat2RotateAsm  (mat2* r,const float angle);
extern __C void Mat2ScaleAsm   (mat2* r,const float x_scale,const float y_scale);

#if !defined(__REGRESSION_TEST)
  #define Mat3Copy                        Mat3CopyAsm
  #define Mat3Identity                    Mat3IdentityAsm
#endif

extern __C void Mat3CopyAsm    (mat3* r,const mat3* m);
extern __C void Mat3IdentityAsm(mat3* r);

#if !defined(__REGRESSION_TEST)
  #define Mat3Negate                      Mat3NegateAsm
  #define Mat3Add                         Mat3AddAsm
  #define Mat3AddFloat                    Mat3AddFloatAsm
  #define Mat3Subtract                    Mat3SubtractAsm
  #define Mat3SubtractFloat               Mat3SubtractFloatAsm
  #define Mat3Multiply                    Mat3MultiplyAsm
  #define Mat3MultiplyIdentityByBlocks    Mat3MultiplyIdentityByBlocksAsm
  #define Mat3MultiplyVec                 Mat3MultiplyVecAsm
  #define Mat3MultiplyVecBlock            Mat3MultiplyVecBlockAsm
  #define Mat3MulVecBlockBySize           Mat3MulVecBlockBySizeAsm
  #define Mat3MulVec3BufByBuf             Mat3MulVec3BufByBufAsm
  #define Mat3MultiplyFloat               Mat3MultiplyFloatAsm
  #define Mat3Inverse                     Mat3InverseAsm
  #define Mat3Transpose                   Mat3TransposeAsm
#endif

extern __C void Mat3NegateAsm                  (mat3* r,const mat3* m);
extern __C void Mat3AddAsm                     (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3AddFloatAsm                (mat3* r,const mat3* m,const float s);
extern __C void Mat3SubtractAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3SubtractFloatAsm           (mat3* r,const mat3* m,const float s);
extern __C void Mat3MultiplyAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3MultiplyIdentityByBlocksAsm(mat3* r,const mat3* m,int32_t iCount);
extern __C void Mat3MultiplyVecAsm             (vec3* r,const mat3* m,const vec3* v);
extern __C void Mat3MultiplyVecBlockAsm        (vec3* r,const mat3* m,const vec3* v,int32_t iCount);
extern __C void Mat3MulVecBlockBySizeAsm       (void* r,const mat3* m,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Mat3MulVec3BufByBufAsm         (void* r,const int32_t iRSize,const mat3* m,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Mat3MultiplyFloatAsm           (mat3* r,const mat3* m,const float x);
extern __C void Mat3InverseAsm                 (mat3* r,const mat3* m);
extern __C void Mat3TransposeAsm               (mat3* r,const mat3* m);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHX                   Mat3RotateRHX_Asm
  #define Mat3RotateLHX                   Mat3RotateLHX_Asm
  #define Mat3RotateRHY                   Mat3RotateRHY_Asm
  #define Mat3RotateLHY                   Mat3RotateLHY_Asm
  #define Mat3RotateRHZ                   Mat3RotateRHZ_Asm
  #define Mat3RotateLHZ                   Mat3RotateLHZ_Asm
#endif

extern __C void Mat3RotateRHX_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateLHX_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateRHY_Asm  (mat3* m,const float angle);
extern __C void Mat3RotateLHY_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateRHZ_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateLHZ_Asm  (mat3* r,const float angle);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHXY                  Mat3RotateRHXY_Asm
  #define Mat3RotateLHXY                  Mat3RotateLHXY_Asm
  #define Mat3RotateRHXZ                  Mat3RotateRHXZ_Asm
  #define Mat3RotateLHXZ                  Mat3RotateLHXZ_Asm
  #define Mat3RotateRHYZ                  Mat3RotateRHYZ_Asm
  #define Mat3RotateLHYZ                  Mat3RotateLHYZ_Asm
#endif

extern __C void Mat3RotateRHXY_Asm (mat3* r,const float x,const float y);
extern __C void Mat3RotateLHXY_Asm (mat3* r,const float x,const float y);
extern __C void Mat3RotateRHXZ_Asm (mat3* m,const float x,const float z);
extern __C void Mat3RotateLHXZ_Asm (mat3* m,const float x,const float z);
extern __C void Mat3RotateRHYZ_Asm (mat3* r,const float y,const float z);
extern __C void Mat3RotateLHYZ_Asm (mat3* m,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHXYZ                 Mat3RotateRHXYZ_Asm
  #define Mat3RotateLHXYZ                 Mat3RotateLHXYZ_Asm
#endif

extern __C void Mat3RotateRHXYZ_Asm(mat3* r,const float x,const float y,const float z);
extern __C void Mat3RotateLHXYZ_Asm(mat3* r,const float x,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat3Scale                       Mat3ScaleAsm
  #define Mat3ScaleByVec3                 Mat3ScaleByVec3Asm
#endif

extern __C void Mat3ScaleAsm      (mat3* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat3ScaleByVec3Asm(mat3* r,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Mat4Copy                        Mat4CopyAsm
#endif

extern __C void Mat4CopyAsm(mat4* r,const mat4* m);

#if !defined(__REGRESSION_TEST)
  #define Mat4Negate                      Mat4NegateAsm
  #define Mat4NegateMatrix                Mat4NegateMatrixAsm
  #define Mat4Add                         Mat4AddAsm
  #define Mat4AddFloat                    Mat4AddFloatAsm
  #define Mat4AddMatrix                   Mat4AddMatrixAsm
  #define Mat4Subtract                    Mat4SubtractAsm
  #define Mat4SubtractFloat               Mat4SubtractFloatAsm
  #define Mat4SubtractMatrix              Mat4SubtractMatrixAsm
  #define Mat4MultiplyMatrix              Mat4MultiplyMatrixAsm
  #define Mat4Multiply                    Mat4MultiplyAsm
  #define Mat4MultiplyVec                 Mat4MultiplyVecAsm
  #define Mat4LookAt                      Mat4LookAtAsm
#endif

extern __C void Mat4NegateAsm        (mat4* r,const mat4* m);
extern __C void Mat4NegateMatrixAsm  (mat4* r);
extern __C void Mat4AddAsm           (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4AddFloatAsm      (mat4* r,const mat4* m,const float s);
extern __C void Mat4AddMatrixAsm     (mat4* m,const mat4* n);
extern __C void Mat4SubtractAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4SubtractFloatAsm (mat4* r,const mat4* m,const float s);
extern __C void Mat4SubtractMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4MultiplyMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4MultiplyAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4MultiplyVecAsm   (vec4* r,const mat4* m,const vec4* v);
extern __C void Mat4LookAtAsm        (mat4* r,const vec3* from,const vec3* at);

#if !defined(__REGRESSION_TEST)
  #define Mat4MultiplyFloat               Mat4MultiplyFloatAsm
  #define Mat4Transpose                   Mat4TransposeAsm
  #define Mat4ShadowMatrix                Mat4ShadowMatrixAsm
  #define Mat4MirrorMatrix                Mat4MirrorMatrixAsm
  #define Mat4GlToD3DProjMat              Mat4GlToD3DProjMatAsm
  #define Mat4LookAtLH                    Mat4LookAtLHAsm
#endif

extern __C void Mat4MultiplyFloatAsm (mat4* r,const mat4* m,const float x);
extern __C void Mat4TransposeAsm     (mat4* r,const mat4* m);
extern __C void Mat4ShadowMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset,const vec3* lightPos);
extern __C void Mat4MirrorMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset);
extern __C void Mat4GlToD3DProjMatAsm(mat4* r,const mat4* m);
extern __C void Mat4LookAtLHAsm      (mat4* r,const vec3* pEye,const vec3* pLookAt,const vec3* pUp);

#if !defined(__REGRESSION_TEST)
  #define Mat4Identity                    Mat4IdentityAsm
  #define Mat4Scale                       Mat4ScaleAsm
#endif

extern __C void Mat4IdentityAsm(mat4* r);
extern __C void Mat4ScaleAsm   (mat4* r,const float x_scale,const float y_scale,const float z_scale);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHX                   Mat4RotateRHX_Asm
  #define Mat4RotateLHX                   Mat4RotateLHX_Asm
  #define Mat4RotateRHY                   Mat4RotateRHY_Asm
  #define Mat4RotateLHY                   Mat4RotateLHY_Asm
  #define Mat4RotateRHZ                   Mat4RotateRHZ_Asm
  #define Mat4RotateLHZ                   Mat4RotateLHZ_Asm
#endif

extern __C void Mat4RotateRHX_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHX_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateRHY_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHY_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateRHZ_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHZ_Asm  (mat4* r,const float angle);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHXY                  Mat4RotateRHXY_Asm
  #define Mat4RotateLHXY                  Mat4RotateLHXY_Asm
  #define Mat4RotateRHXZ                  Mat4RotateRHXZ_Asm
  #define Mat4RotateLHXZ                  Mat4RotateLHXZ_Asm
  #define Mat4RotateRHYZ                  Mat4RotateRHYZ_Asm
  #define Mat4RotateLHYZ                  Mat4RotateLHYZ_Asm
#endif

extern __C void Mat4RotateRHXY_Asm (mat4* r,const float x_scale,const float y_scale);
extern __C void Mat4RotateLHXY_Asm (mat4* r,const float x,const float y);
extern __C void Mat4RotateRHXZ_Asm (mat4* m,const float x,const float z);
extern __C void Mat4RotateLHXZ_Asm (mat4* m,const float x,const float z);
extern __C void Mat4RotateRHYZ_Asm (mat4* r,const float y,const float z);
extern __C void Mat4RotateLHYZ_Asm (mat4* m,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHXYZ                 Mat4RotateRHXYZ_Asm
  #define Mat4RotateLHXYZ                 Mat4RotateLHXYZ_Asm
#endif

extern __C void Mat4RotateRHXYZ_Asm(mat4* r,const float x,const float y,const float z);
extern __C void Mat4RotateLHXYZ_Asm(mat4* r,const float x,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat4TranslateRH                 Mat4TranslateRH_Asm
  #define Mat4TranslateLH                 Mat4TranslateLH_Asm
  #define Mat4TranslateRH_Vec3            Mat4TranslateRH_Vec3Asm
  #define Mat4TranslateLH_Vec3            Mat4TranslateLH_Vec3Asm
  #define Mat4TranslateRH_Vec4            Mat4TranslateRH_Vec4Asm
  #define Mat4TranslateLH_Vec4            Mat4TranslateLH_Vec4Asm
#endif

extern __C void Mat4TranslateRH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateLH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateRH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateLH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateRH_Vec4Asm (mat4* r,const vec4* v);
extern __C void Mat4TranslateLH_Vec4Asm (mat4* r,const vec4* v);

#if !defined(__REGRESSION_TEST)
  #define Mat4OrthoMatrix                 Mat4OrthoMatrixAsm
  #define Mat4OrthoStruct                 Mat4OrthoStructAsm
  #define Mat4Perspective                 Mat4PerspectiveAsm
  #define Mat4PerspectiveX                Mat4PerspectiveXAsm
  #define Mat4CubemapMatrix               Mat4CubemapMatrixAsm
  #define Mat4CubemapProjectionMat        Mat4CubemapProjectionMatAsm
  //#define Mat4LookAtHoriz                 Mat4LookAtHorizAsm
#endif

extern __C void Mat4OrthoMatrixAsm(mat4*         r,
                                   const float   left,
                                   const float   right,
                                   const float   top,
                                   const float   bottom,
                                   const float   zNear,
                                   const float   zFar,
                                   const int32_t d3dFlag);
extern __C void Mat4OrthoStructAsm(mat4* r,const orthoMatrix* s);

extern __C void Mat4PerspectiveAsm (mat4*          r,
                                    const float    fov,
                                    const float    width,
                                    const float    height,
                                    const float    zNear,
                                    const float    zFar,
                                    const uint32_t d3dflag);
extern __C void Mat4PerspectiveXAsm(mat4* r,const struct perspectiveMatrix* s);

extern __C void Mat4CubemapMatrixAsm(mat4* r,const unsigned int face);
extern __C void Mat4CubemapProjectionMatAsm(mat4* r,const float zNear,const float zFar,const uint32_t d3dflag);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotationFromMat4            Mat3RotationFromMat4Asm
  #define Mat4FromMat3                    Mat4FromMat3Asm
#endif

extern __C void Mat3RotationFromMat4Asm    (mat3* r,const mat4* m);
extern __C void Mat4FromMat3Asm            (mat4* r,const mat3* m);

#if !defined(__REGRESSION_TEST)
  #define QuaternionAdd                   QuaternionAddAsm
  #define QuaternionMultiply              QuaternionMultiplyAsm
  #define QuaternionInverse               QuaternionInverseAsm
  #define QuaternionToMat3                QuaternionToMat3Asm
  #define QuaternionToMat4                QuaternionToMat4Asm
#endif

extern __C void QuaternionAddAsm     (quaternion* r,const quaternion* q,const quaternion* v);
extern __C void QuaternionMultiplyAsm(quaternion*r,const quaternion* u,const quaternion* v);
extern __C void QuaternionInverseAsm (quaternion* r,const quaternion* q);
extern __C void QuaternionToMat3Asm  (mat3* r,const quaternion* q);
extern __C void QuaternionToMat4Asm  (mat4* m,const quaternion* q);

#if !defined(__REGRESSION_TEST)
  #define QuaternionNormalize             QuaternionNormalizeAsm
  #define QuaternionDot                   QuaternionDotAsm
#endif

extern __C void QuaternionNormalizeAsm (quaternion* r,const quaternion* q);
extern __C void QuaternionDotAsm       (float* r,const quaternion* q,const quaternion* v);

#if !defined(__REGRESSION_TEST)
  #define QuaternionFromAxis              QuaternionFromAxisAsm
  #define QuaternionFromMat3              QuaternionFromMat3Asm
  #define QuaternionFromMat4              QuaternionFromMat4Asm
  #define QuaternionFromMat3              QuaternionFromMat3Asm
  #define QuaternionFromMat4              QuaternionFromMat4Asm
  #define QuaternionSlerp                 QuaternionSlerpAsm
  #define QuaternionCos                   QuaternionCosAsm
  #define QuaternionSin                   QuaternionSinAsm
#endif

extern __C void QuaternionFromAxisAsm(quaternion* r,const vec3* v,const float angle);
extern __C void QuaternionFromMat3Asm(quaternion* r,const mat3* m);
extern __C void QuaternionFromMat4Asm(quaternion* r,const mat4* m);
extern __C void QuaternionSlerpAsm   (quaternion* r,const float s,const quaternion* q,const quaternion* v);
extern __C void QuaternionCosAsm     (float* r,const quaternion* q,const quaternion* p);
extern __C void QuaternionSinAsm     (float* r,const quaternion* q,const quaternion* p);

#elif defined(__BUILD_ADVANCED_UNALIGNED_LIB) || defined(__ADVANCED_UNALIGNED_LIB)

/* -------------------------- *
 * Advanced Unaligned Library *
 * ---------------------------*------------------------------------------- *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if !defined(__REGRESSION_TEST)
  #define GetFpuStatus                    GetFpuStatusAsm
  #define ClearFpuStatus                  ClearFpuStatusAsm
  #define FloatLerp                       FloatLerpAsm
  #define FloatLerpPtr                    FloatLerpPtrAsm
  #define FloatSqr                        FloatSqrAsm
  #define FloatSqrPtr                     FloatSqrPtrAsm
  #define fCos                            fCosAsm
  #define fSin                            fSinAsm
  #define fTan                            fTanAsm
  #define fACos                           AfCosAsm
  #define fASin                           AfSinAsm
  #define fATan                           AfTanAsm
  #define Cos                             CosAsm
  #define Sin                             SinAsm
  #define Tan                             TanAsm
  #define ACos                            ACosAsm
  #define ASin                            ASinAsm
  #define ATan                            ATanAsm
#endif

extern __C void  GetFpuStatusAsm  (unsigned short* uStatus);
extern __C void  ClearFpuStatusAsm(unsigned short* uStatus);
extern __C float FloatLerpAsm     (const float x,const float v,const float u);
extern __C void  FloatLerpPtrAsm  (float* ret,const float* u,const float* v,const float* x);
extern __C float FloatSqrAsm      (float x);
extern __C float FloatSqrPtrAsm   (float* x);

extern __C float fCosAsm(const float angle);
extern __C float fSinAsm(const float angle);
extern __C float fTanAsm(const float angle);
extern __C float AfCosAsm(const float cosa);
extern __C float AfSinAsm(const float sina);
extern __C float AfTanAsm(const float tana);

extern __C double CosAsm(const double angle);
extern __C double SinAsm(const double angle);
extern __C double TanAsm(const double angle);
extern __C double ACosAsm(const double cosa);
extern __C double ASinAsm(const double sina);
extern __C double ATanAsm(const double tana);

#if !defined(__REGRESSION_TEST)
  #define Vec2Copy                        Vec2CopyAsm
  #define Vec2CopyBlock                   Vec2CopyBlockAsm
  #define BuildVec2PackedArray            BuildVec2PackedArrayAsm
#endif

extern __C void Vec2CopyAsm            (vec2* r,const vec2* v);
extern __C void Vec2CopyBlockAsm       (vec2* r,vec2* v,int32_t iCount);
extern __C void BuildVec2PackedArrayAsm(vec2* r,const vec2** ppList,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddFloat                    Vec2AddFloatAsm
  #define Vec2SubtractFloat               Vec2SubtractFloatAsm
  #define Vec2MultiplyFloat               Vec2MultiplyFloatAsm
  #define Vec2FloatMultiply               Vec2FloatMultiplyAsm
  #define Vec2DivideFloat                 Vec2DivideFloatAsm
  #define Vec2AddFloatToBlock             Vec2uAddFloatToBlockAsm
  #define Vec2AddFloatToBlockSize         Vec2AddFloatToBlockSizeAsm
  #define Vec2BufAddFloatToBlock          Vec2BufAddFloatToBlockAsm
  #define Vec2BufAddFloatToBuf            Vec2BufAddFloatToBufAsm
#endif

extern __C void Vec2AddFloatAsm           (vec2* r,const vec2* u,const float s);
extern __C void Vec2SubtractFloatAsm      (vec2* r,const vec2* u,const float s);
extern __C void Vec2MultiplyFloatAsm      (vec2* r,const vec2* u,const float s);
extern __C void Vec2FloatMultiplyAsm      (vec2* r,const float s,const vec2* v);
extern __C void Vec2DivideFloatAsm        (vec2* r,const vec2* u,const float s);
extern __C void Vec2uAddFloatToBlockAsm   (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2AddFloatToBlockSizeAsm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBlockAsm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBufAsm   (void*  r,const int32_t iRSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2SubtractFloatFromBlock      Vec2uSubtractFloatFromBlockAsm
  #define Vec2SubFloatFromBlockSize       Vec2SubFloatFromBlockSizeAsm
  #define Vec2BufSubFloatFromBlkSize      Vec2BufSubFloatFromBlkSizeAsm
  #define Vec2BufSubFloatFromBuf          Vec2BufSubFloatFromBufAsm
#endif

extern __C void Vec2uSubtractFloatFromBlockAsm(vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2SubFloatFromBlockSizeAsm  (vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBlkSizeAsm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBufAsm     (void*  r,const int32_t iDstSize,const void* pSource,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2MultiplyBlockByFloat        Vec2uMultiplyBlockByFloatAsm
  #define Vec2MultiplyBlkByFloatSize      Vec2MultiplyBlkByFloatSizeAsm
  #define Vec2BufMulBlockByFloatSize      Vec2BufMulBlockByFloatSizeAsm
  #define Vec2BufMulBlockByFloatBuf       Vec2BufMulBlockByFloatBufAsm
#endif

extern __C void Vec2uMultiplyBlockByFloatAsm (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2MultiplyBlkByFloatSizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatSizeAsm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatBufAsm (void*  r,const int32_t iDstSizeconst,void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2DivideBlockByFloat          Vec2uDivideBlockByFloatAsm
  #define Vec2DivideBlockByFloatSize      Vec2DivideBlockByFloatSizeAsm
  #define Vec2BufDivBlockByFloatSize      Vec2BufDivBlockByFloatSizeAsm
  #define Vec2BufDivBufByFloat            Vec2BufDivBufByFloatAsm
#endif

extern __C void Vec2uDivideBlockByFloatAsm   (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2DivideBlockByFloatSizeAsm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockByFloatSizeAsm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufByFloatAsm      (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2Negate                      Vec2NegateAsm
  #define Vec2Add                         Vec2AddAsm
  #define Vec2Subtract                    Vec2SubtractAsm
  #define Vec2Multiply                    Vec2MultiplyAsm
  #define Vec2Divide                      Vec2DivideAsm
#endif

extern __C void Vec2NegateAsm  (vec2* r,const vec2* u);
extern __C void Vec2AddAsm     (vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2SubtractAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2MultiplyAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2DivideAsm  (vec2* r,const vec2* u,const vec2* v);

#if !defined(__REGRESSION_TEST)
  #define Vec2Equals                      Vec2uEqualsAsm
  #define Vec2NotEquals                   Vec2uNotEqualsAsm
#endif

extern __C void Vec2uEqualsAsm   (int32_t* iFlag,const vec2* u,const vec2* v);
extern __C void Vec2uNotEqualsAsm(int32_t* iFlag,const vec2* u,const vec2* v);

#if !defined(__REGRESSION_TEST)
  #define Vec2NegateBlock                 Vec2uNegateBlockAsm
  #define Vec2NegateBlockBySize           Vec2NegateBlockBySizeAsm
  #define Vec2BufNegateBlockBySize        Vec2BufNegateBlockBySizeAsm
  #define Vec2BufNegateBufBySize          Vec2BufNegateBufBySizeAsm
#endif

extern __C void Vec2uNegateBlockAsm        (vec2* rv,const int32_t iCount);
extern __C void Vec2NegateBlockBySizeAsm   (vec2* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBlockBySizeAsm(vec2*  r,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBufBySizeAsm  (vec2*  r,const int32_t iDstSize,const vec2* v,const int32_t iSrcSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddVec2ToBlock              Vec2uAddVec2ToBlockAsm
  #define Vec2AddBlockToBlock             Vec2uAddBlockToBlockAsm
  #define Vec2BufAddVec2ToBlockBySize     Vec2BufAddVec2ToBlockBySizeAsm
  #define Vec2BufAddBlockBySize           Vec2BufAddBlockBySizeAsm
  #define Vec2BufAddBufBySize             Vec2BufAddBufBySizeAsm
#endif

extern __C void Vec2uAddVec2ToBlockAsm (vec2* rv,const vec2* v,const int32_t iCount);
extern __C void Vec2uAddBlockToBlockAsm(vec2* rv,const vec2* v,int32_t nCount);
extern __C void Vec2BufAddVec2ToBlockBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2SubtractVec2FromBlock       Vec2uSubtractVec2FromBlockAsm
  #define Vec2SubtractBlockFromBlock      Vec2uSubtractBlockFromBlockAsm
  #define Vec2BufSubVec2FromBlkBySize     Vec2BufSubVec2FromBlkBySizeAsm
  #define Vec2BufSubBlockBySize           Vec2BufSubBlockBySizeAsm
  #define Vec2BufSubBufBySize             Vec2BufSubBufBySizeAsm
#endif

extern __C void Vec2uSubtractVec2FromBlockAsm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2uSubtractBlockFromBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufSubVec2FromBlkBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2MultiplyBlockByVec2         Vec2uMultiplyBlockByVec2Asm
  #define Vec2MultiplyBlockByBlock        Vec2uMultiplyBlockByBlockAsm
  #define Vec2BufMulVec2ByBlockSize       Vec2BufMulVec2ByBlockSizeAsm
  #define Vec2BufMulBlockBySize           Vec2BufMulBlockBySizeAsm
  #define Vec2BufMulBufBySize             Vec2BufMulBufBySizeAsm
#endif

extern __C void Vec2uMultiplyBlockByVec2Asm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2uMultiplyBlockByBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufMulVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2DivideBlockByVec2           Vec2uDivideBlockByVec2Asm
  #define Vec2DivideBlockByBlock          Vec2uDivideBlockByBlockAsm
  #define Vec2BufDivVec2ByBlockSize       Vec2BufDivVec2ByBlockSizeAsm
  #define Vec2BufDivBlockBySize           Vec2BufDivBlockBySizeAsm
  #define Vec2BufDivBufBySize             Vec2BufDivBufBySizeAsm
#endif

extern __C void Vec2uDivideBlockByVec2Asm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2uDivideBlockByBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufDivVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2LerpBlock                   Vec2uLerpBlockAsm
  #define Vec2SqrBlock                    Vec2uSqrBlockAsm
  #define Vec2SqrtBlock                   Vec2uSqrtBlockAsm
  #define Vec2NormalizeBlock              Vec2uNormalizeBlockAsm
  #define Vec2DotBlock                    Vec2uDotBlockAsm
#endif

extern __C void Vec2uLerpBlockAsm     (vec2*  r,const vec2* u,const vec2* v,const float step,const int32_t iCount);
extern __C void Vec2uSqrBlockAsm      (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2uSqrtBlockAsm     (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2uNormalizeBlockAsm(vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2uDotBlockAsm      (float* r,const vec2* u,const vec2* v,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2Lerp                        Vec2LerpAsm
  #define Vec2Sqr                         Vec2SqrAsm
  #define Vec2Sqrt                        Vec2SqrtAsm
  #define Vec2Normalize                   Vec2NormalizeAsm
  #define Vec2Dot                         Vec2DotAsm
  #define Vec2Length                      Vec2LengthAsm
  #define Vec2LengthBlock                 Vec2LengthBlockAsm
#endif

extern __C void Vec2LerpAsm       (vec2*  r,const vec2* u,const vec2* v,const float step);
extern __C void Vec2SqrAsm        (vec2*  r,const vec2* u);
extern __C void Vec2SqrtAsm       (vec2*  r,const vec2* u);
extern __C void Vec2NormalizeAsm  (vec2*  r,const vec2* v);
extern __C void Vec2DotAsm        (float* f,const vec2* u,const vec2* v);
extern __C void Vec2LengthAsm     (float* r,const vec2* v);
extern __C void Vec2LengthBlockAsm(float* r,const vec2* v,const int32_t nCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2BufLerpBuf                  Vec2BufLerpBufAsm
  #define Vec2BufSqrBuf                   Vec2BufSqrBufAsm
  #define Vec2BufSqrtBuf                  Vec2BufSqrtBufAsm
  #define Vec2BufNormalizeBuf             Vec2BufNormalizeBufAsm
  #define Vec2BufDotBuf                   Vec2BufDotBufAsm
  #define Vec2BufLengthBuf                Vec2BufLengthBufAsm
#endif

extern __C void Vec2BufLerpBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);
extern __C void Vec2BufSqrBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufSqrtBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufNormalizeBufAsm(void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufDotBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Vec2BufLengthBufAsm   (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Copy                        Vec3CopyAsm
  #define Vec3CopyBlock                   Vec3CopyBlockAsm
  #define BuildVec3PackedArray            BuildVec3PackedArrayAsm
#endif

extern __C void Vec3CopyAsm            (vec3* r,const vec3*  u);
extern __C void Vec3CopyBlockAsm       (vec3* r,const vec3*  u,const int32_t iCount);
extern __C void BuildVec3PackedArrayAsm(vec3* r,const vec3** pu,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3AddFloat                    Vec3uAddFloatAsm
  #define Vec3AddFloatToBlock             Vec3uAddFloatToBlockAsm
  #define Vec3AddFloatToBlockBySize       Vec3uAddFloatToBlockBySizeAsm
  #define Vec3BufAddFloatToBlock          Vec3uBufAddFloatToBlockAsm
  #define Vec3BufAddFloatToBuf            Vec3uBufAddFloatToBufAsm
#endif

extern __C void Vec3uAddFloatAsm             (vec3*  r,const vec3* v,const float s);
extern __C void Vec3uAddFloatToBlockAsm      (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uAddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3SubtractFloat               Vec3uSubtractFloatAsm
  #define Vec3SubtractFloatFromBlock      Vec3uSubtractFloatFromBlockAsm
  #define Vec3SubFloatFromBlockBySize     Vec3uSubFloatFromBlockBySizeAsm
  #define Vec3BufSubFloatFromBlock        Vec3uBufSubFloatFromBlockAsm
  #define Vec3BufSubFloatFromBuf          Vec3uBufSubFloatFromBufAsm
#endif

extern __C void Vec3uSubtractFloatAsm          (vec3* r,const vec3* u,const float s);
extern __C void Vec3uSubtractFloatFromBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uSubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3MultiplyFloat               Vec3uMultiplyFloatAsm
  #define Vec3MultiplyFloatToBlock        Vec3uMultiplyFloatToBlockAsm
  #define Vec3MulFloatToBlockBySize       Vec3uMulFloatToBlockBySizeAsm
  #define Vec3BufMulFloatToBlock          Vec3uBufMulFloatToBlockAsm
  #define Vec3BufMulFloatToBuf            Vec3uBufMulFloatToBufAsm
#endif

extern __C void Vec3uMultiplyFloatAsm        (vec3*  r,const vec3* u,const float s);
extern __C void Vec3uMultiplyFloatToBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uMulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3DivideFloat                 Vec3uDivideFloatAsm
  #define Vec3DivideBlockByFloat          Vec3uDivideBlockByFloatAsm
  #define Vec3DivBlockByFloatBySize       Vec3uDivBlockByFloatBySizeAsm
  #define Vec3BufDivBlockByFloat          Vec3uBufDivBlockByFloatAsm
  #define Vec3BufDivBufByFloat            Vec3uBufDivBufByFloatAsm
#endif

extern __C void Vec3uDivideFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3uDivideBlockByFloatAsm   (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uDivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Equals                      Vec3uEqualsAsm
  #define Vec3NotEquals                   Vec3uNotEqualsAsm
#endif

extern __C void Vec3uEqualsAsm   (int32_t* iFlag,const vec3* u,const vec3* v);
extern __C void Vec3uNotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Vec3Negate                      Vec3uNegateAsm
  #define Vec3NegateBlock                 Vec3uNegateBlockAsm
  #define Vec3NegateBlockBySize           Vec3uNegateBlockBySizeAsm
  #define Vec3BufNegateBlock              Vec3uBufNegateBlockAsm
  #define Vec3BufNegateBuf                Vec3uBufNegateBufAsm
#endif

extern __C void Vec3uNegateAsm           (vec3*  r,const vec3* v);
extern __C void Vec3uNegateBlockAsm      (vec3* rv,int32_t iCount);
extern __C void Vec3uNegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Add                         Vec3uAddAsm
  #define Vec3AddVecToBlock               Vec3uAddVecToBlockAsm
  #define Vec3AddVecToBlockBySize         Vec3uAddVecToBlockBySizeAsm
  #define Vec3BufAddVecToBlock            Vec3uBufAddVecToBlockAsm
  #define Vec3BufAddVecToBuf              Vec3uBufAddVecToBufAsm
  #define Vec3AddBlockToBlock             Vec3uAddBlockToBlockAsm
  #define Vec3AddBlockToBlockBySize       Vec3uAddBlockToBlockBySizeAsm
  #define Vec3BufAddBlockToBuf            Vec3uBufAddBlockToBufAsm
  #define Vec3BufAddBufToBuf              Vec3uBufAddBufToBufAsm
#endif

extern __C void Vec3uAddAsm                  (vec3* r,const vec3* u,const vec3* v);
extern __C void Vec3uAddVecToBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uAddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec3uAddBlockToBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uAddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Subtract                    Vec3uSubtractAsm
  #define Vec3SubVecFromBlock             Vec3uSubVecFromBlockAsm
  #define Vec3SubVecFromBlockBySize       Vec3uSubVecFromBlockBySizeAsm
  #define Vec3BufSubVecFromBlock          Vec3uBufSubVecFromBlockAsm
  #define Vec3BufSubVecFromBuf            Vec3uBufSubVecFromBufAsm
  #define Vec3SubBlockFromBlock           Vec3uSubBlockFromBlockAsm
  #define Vec3SubBlockFromBlockBySize     Vec3uSubBlockFromBlockBySizeAsm
  #define Vec3BufSubBlockFromBuf          Vec3uBufSubBlockFromBufAsm
  #define Vec3BufSubBufFromBuf            Vec3uBufSubBufFromBufAsm
#endif

extern __C void Vec3uSubtractAsm               (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uSubVecFromBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubBlockFromBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Multiply                    Vec3uMultiplyAsm
  #define Vec3MulBlockByVec               Vec3uMulBlockByVecAsm
  #define Vec3MulBlockByVecUseSize        Vec3uMulBlockByVecUseSizeAsm
  #define Vec3BufMulBufByVec              Vec3uBufMulBufByVecAsm
  #define Vec3BufMulBufByVecUseSize       Vec3uBufMulBufByVecUseSizeAsm
  #define Vec3MulBlockByBlock             Vec3uMulBlockByBlockAsm
  #define Vec3MulBlockByBlockUseSize      Vec3uMulBlockByBlockUseSizeAsm
  #define Vec3BufMulBufByBlock            Vec3uBufMulBufByBlockAsm
  #define Vec3BufMulBufByBuf              Vec3uBufMulBufByBufAsm
#endif

extern __C void Vec3uMultiplyAsm              (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uMulBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3uMulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uMulBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uMulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Divide                      Vec3uDivideAsm
  #define Vec3DivBlockByVec               Vec3uDivBlockByVecAsm
  #define Vec3DivBlockByVecUseSize        Vec3uDivBlockByVecUseSizeAsm
  #define Vec3BufDivBufByVec              Vec3uBufDivBufByVecAsm
  #define Vec3BufDivBufByVecUseSize       Vec3uBufDivBufByVecUseSizeAsm
  #define Vec3DivBlockByBlock             Vec3uDivBlockByBlockAsm
  #define Vec3DivBlockByBlockUseSize      Vec3uDivBlockByBlockUseSizeAsm
  #define Vec3BufDivBufByBlock            Vec3uBufDivBufByBlockAsm
  #define Vec3BufDivBufByBuf              Vec3uBufDivBufByBufAsm
#endif

extern __C void Vec3uDivideAsm                (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uDivBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByVecUseSizeAsm  (void* ru,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByVecAsm        (void*  r,const void* u,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Lerp                        Vec3uLerpAsm
  #define Vec3LerpBlock                   Vec3uLerpBlockAsm
  #define Vec3LerpBlockUseSize            Vec3uLerpBlockUseSizeAsm
  #define Vec3BufLerpBlock                Vec3uBufLerpBlockAsm
  #define Vec3BufLerpBuf                  Vec3uBufLerpBufAsm
#endif

extern __C void Vec3uLerpAsm            (vec3*  r,const vec3* u,const vec3* v,const float s);
extern __C void Vec3uLerpBlockAsm       (vec3* ru,vec3* v,const float s,const int32_t iCount);
extern __C void Vec3uLerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec3uBufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Dot                         Vec3uDotAsm
  #define Vec3DotBlock                    Vec3uDotBlockAsm
  #define Vec3DotBlockUseSize             Vec3uDotBlockUseSizeAsm
  #define Vec3BufDotBuf                   Vec3uBufDotBufAsm
#endif

extern __C void Vec3uDotAsm            (float* r,const vec3* u,const vec3* v);
extern __C void Vec3uDotBlockAsm       (float* r,const vec3* u,const vec3* v,const int32_t iCount);
extern __C void Vec3uDotBlockUseSizeAsm(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDotBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
 #define Vec3Sqr                         Vec3uSqrAsm
 #define Vec3SqrBlock                    Vec3uSqrBlockAsm
 #define Vec3SqrBlockUseSize             Vec3uSqrBlockUseSizeAsm
 #define Vec3BufSqrBuf                   Vec3uBufSqrBufAsm
#endif

extern __C void Vec3uSqrAsm            (vec3* r,const vec3* v);
extern __C void Vec3uSqrBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3uSqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Sqrt                        Vec3uSqrtAsm
  #define Vec3SqrtBlock                   Vec3uSqrtBlockAsm
  #define Vec3SqrtBlockUseSize            Vec3uSqrtBlockUseSizeAsm
  #define Vec3BufSqrtBuf                  Vec3uBufSqrtBufAsm
#endif

extern __C void Vec3uSqrtAsm            (vec3* r,const vec3* v);
extern __C void Vec3uSqrtBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3uSqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Normalize                   Vec3uNormalizeAsm
  #define Vec3NormalizeBlock              Vec3uNormalizeBlockAsm
  #define Vec3NormalizeBlockUseSize       Vec3uNormalizeBlockUseSizeAsm
  #define Vec3BufNormalizeBuf             Vec3uBufNormalizeBufAsm
#endif

extern __C void Vec3uNormalizeAsm            (vec3*  r,const vec3* u);
extern __C void Vec3uNormalizeBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3uNormalizeBlockUseSizeAsm(vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNormalizeBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Length                      Vec3uLengthAsm
  #define Vec3LengthBlock                 Vec3uLengthBlockAsm
  #define Vec3LengthBlockUseSize          Vec3uLengthBlockUseSizeAsm
  #define Vec3BufLengthBuf                Vec3uBufLengthBufAsm
#endif

extern __C void Vec3uLengthAsm             (float* r,const vec3* v);
extern __C void Vec3uLengthBlockAsm        (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3uLengthBlockUseSize    (float* r,const vec3* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufLengthBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Cross                       Vec3uCrossAsm
  #define Vec3CrossBlock                  Vec3uCrossBlockAsm
  #define Vec3CrossBlockUseSize           Vec3uCrossBlockUseSizeAsm
  #define Vec3BufCrossBuf                 Vec3uBufCrossBufAsm
#endif

extern __C void Vec3uCrossAsm            (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uCrossBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uCrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Reflect                     Vec3uReflectAsm
#endif

extern __C void Vec3uReflectAsm(vec3* r,const vec3* u,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Vec4Copy                        Vec4CopyAsm
  #define Vec4CopyBlock                   Vec4CopyBlockAsm
  #define BuildVec4PackedArray            BuildVec4PackedArrayAsm
#endif

extern __C void Vec4CopyAsm            (vec4* r,const vec4*  u);
extern __C void Vec4CopyBlockAsm       (vec4* r,const vec4*  u,const int32_t iCount);
extern __C void BuildVec4PackedArrayAsm(vec4* r,const vec4** pu,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4AddFloat                    Vec4uAddFloatAsm
  #define Vec4AddFloatToBlock             Vec4uAddFloatToBlockAsm
  #define Vec4AddFloatToBlockBySize       Vec4uAddFloatToBlockBySizeAsm
  #define Vec4BufAddFloatToBlock          Vec4uBufAddFloatToBlockAsm
  #define Vec4BufAddFloatToBuf            Vec4uBufAddFloatToBufAsm
#endif

extern __C void Vec4uAddFloatAsm             (vec4* r,const vec4* v,const float s);
extern __C void Vec4uAddFloatToBlockAsm      (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uAddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4SubtractFloat               Vec4uSubtractFloatAsm
  #define Vec4SubtractFloatFromBlock      Vec4uSubtractFloatFromBlockAsm
  #define Vec4SubFloatFromBlockBySize     Vec4uSubFloatFromBlockBySizeAsm
  #define Vec4BufSubFloatFromBlock        Vec4uBufSubFloatFromBlockAsm
  #define Vec4BufSubFloatFromBuf          Vec4uBufSubFloatFromBufAsm
#endif

extern __C void Vec4uSubtractFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uSubtractFloatFromBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uSubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubFloatFromBlockAsm   (void* r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubFloatFromBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4MultiplyFloat               Vec4uMultiplyFloatAsm
  #define Vec4MultiplyFloatToBlock        Vec4uMultiplyFloatToBlockAsm
  #define Vec4MulFloatToBlockBySize       Vec4uMulFloatToBlockBySizeAsm
  #define Vec4BufMulFloatToBlock          Vec4uBufMulFloatToBlockAsm
  #define Vec4BufMulFloatToBuf            Vec4uBufMulFloatToBufAsm
#endif

extern __C void Vec4uMultiplyFloatAsm        (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uMultiplyFloatToBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uMulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4DivideFloat                 Vec4uDivideFloatAsm
  #define Vec4DivideBlockByFloat          Vec4uDivideBlockByFloatAsm
  #define Vec4DivBlockByFloatBySize       Vec4uDivBlockByFloatBySizeAsm
  #define Vec4BufDivBlockByFloat          Vec4uBufDivBlockByFloatAsm
  #define Vec4BufDivBufByFloat            Vec4uBufDivBufByFloatAsm
#endif

extern __C void Vec4uDivideFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uDivideBlockByFloatAsm   (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uDivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBlockByFloatAsm   (void*  r,const void*   u,const float   s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Equals                      Vec4EqualsAsm
  #define Vec4NotEquals                   Vec4NotEqualsAsm
#endif

extern __C void Vec4EqualsAsm   (int32_t* iFlag,const vec4* u,const vec4* v);
extern __C void Vec4NotEqualsAsm(int32_t* iFlag,const vec4* u,const vec4* v);

#if !defined(__REGRESSION_TEST)
  #define Vec4Negate                      Vec4uNegateAsm
  #define Vec4NegateBlock                 Vec4uNegateBlockAsm
  #define Vec4NegateBlockBySize           Vec4uNegateBlockBySizeAsm
  #define Vec4BufNegateBlock              Vec4uBufNegateBlockAsm
  #define Vec4BufNegateBuf                Vec4uBufNegateBufAsm
#endif

extern __C void Vec4uNegateAsm           (vec4*  r,const vec4* v);
extern __C void Vec4uNegateBlockAsm      (vec4* rv,int32_t iCount);
extern __C void Vec4uNegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Add                         Vec4uAddAsm
  #define Vec4AddVecToBlock               Vec4uAddVecToBlockAsm
  #define Vec4AddVecToBlockBySize         Vec4uAddVecToBlockBySizeAsm
  #define Vec4BufAddVecToBlock            Vec4uBufAddVecToBlockAsm
  #define Vec4BufAddVecToBuf              Vec4uBufAddVecToBufAsm
  #define Vec4AddBlockToBlock             Vec4uAddBlockToBlockAsm
  #define Vec4AddBlockToBlockBySize       Vec4uAddBlockToBlockBySizeAsm
  #define Vec4BufAddBlockToBuf            Vec4uBufAddBlockToBufAsm
  #define Vec4BufAddBufToBuf              Vec4uBufAddBufToBufAsm
#endif

extern __C void Vec4uAddAsm                  (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uAddVecToBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uAddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec4uAddBlockToBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uAddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Subtract                    Vec4uSubtractAsm
  #define Vec4SubVecFromBlock             Vec4uSubVecFromBlockAsm
  #define Vec4SubVecFromBlockBySize       Vec4uSubVecFromBlockBySizeAsm
  #define Vec4BufSubVecFromBlock          Vec4uBufSubVecFromBlockAsm
  #define Vec4BufSubVecFromBuf            Vec4uBufSubVecFromBufAsm
  #define Vec4SubBlockFromBlock           Vec4uSubBlockFromBlockAsm
  #define Vec4SubBlockFromBlockBySize     Vec4uSubBlockFromBlockBySizeAsm
  #define Vec4BufSubBlockFromBuf          Vec4uBufSubBlockFromBufAsm
  #define Vec4BufSubBufFromBuf            Vec4uBufSubBufFromBufAsm
#endif

extern __C void Vec4uSubtractAsm               (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uSubVecFromBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uSubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubVecFromBufAsm       (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4uSubBlockFromBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uSubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Multiply                    Vec4uMultiplyAsm
  #define Vec4MulBlockByVec               Vec4uMulBlockByVecAsm
  #define Vec4MulBlockByVecUseSize        Vec4uMulBlockByVecUseSizeAsm
  #define Vec4BufMulBufByVec              Vec4uBufMulBufByVecAsm
  #define Vec4BufMulBufByVecUseSize       Vec4uBufMulBufByVecUseSizeAsm
  #define Vec4MulBlockByBlock             Vec4uMulBlockByBlockAsm
  #define Vec4MulBlockByBlockUseSize      Vec4uMulBlockByBlockUseSizeAsm
  #define Vec4BufMulBufByBlock            Vec4uBufMulBufByBlockAsm
  #define Vec4BufMulBufByBuf              Vec4uBufMulBufByBufAsm
#endif

extern __C void Vec4uMultiplyAsm              (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uMulBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4uMulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4uMulBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uMulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Divide                      Vec4uDivideAsm
  #define Vec4DivBlockByVec               Vec4uDivBlockByVecAsm
  #define Vec4DivBlockByVecUseSize        Vec4uDivBlockByVecUseSizeAsm
  #define Vec4BufDivBufByVec              Vec4uBufDivBufByVecAsm
  #define Vec4BufDivBufByVecUseSize       Vec4uBufDivBufByVecUseSizeAsm
  #define Vec4DivBlockByBlock             Vec4uDivBlockByBlockAsm
  #define Vec4DivBlockByBlockUseSize      Vec4uDivBlockByBlockUseSizeAsm
  #define Vec4BufDivBufByBlock            Vec4uBufDivBufByBlockAsm
  #define Vec4BufDivBufByBuf              Vec4uBufDivBufByBufAsm
#endif

extern __C void Vec4uDivideAsm                (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uDivBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uDivBlockByVecUseSizeAsm  (void* ru,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByVecAsm        (void*  r,const void* u,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4uDivBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uDivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Lerp                        Vec4uLerpAsm
  #define Vec4LerpBlock                   Vec4uLerpBlockAsm
  #define Vec4LerpBlockUseSize            Vec4uLerpBlockUseSizeAsm
  #define Vec4BufLerpBlock                Vec4uBufLerpBlockAsm
  #define Vec4BufLerpBuf                  Vec4uBufLerpBufAsm
#endif

extern __C void Vec4uLerpAsm            (vec4*  r,const vec4* u,const vec4* v,const float s);
extern __C void Vec4uLerpBlockAsm       (vec4* ru,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4uLerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4uBufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Dot                         Vec4uDotAsm
  #define Vec4DotBlock                    Vec4uDotBlockAsm
  #define Vec4DotBlockUseSize             Vec4uDotBlockUseSizeAsm
  #define Vec4BufDotBuf                   Vec4uBufDotBufAsm
#endif

extern __C void Vec4uDotAsm                (float* r,const vec4* u,const vec4* v);
extern __C void Vec4uDotBlockAsm           (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4uDotBlockUseSizeAsm    (float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDotBufAsm          (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Sqr                         Vec4uSqrAsm
  #define Vec4SqrBlock                    Vec4uSqrBlockAsm
  #define Vec4SqrBlockUseSize             Vec4uSqrBlockUseSizeAsm
  #define Vec4BufSqrBuf                   Vec4uBufSqrBufAsm
#endif

extern __C void Vec4uSqrAsm            (vec4*  r,const vec4* v);
extern __C void Vec4uSqrBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4uSqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Sqrt                        Vec4uSqrtAsm
  #define Vec4SqrtBlock                   Vec4uSqrtBlockAsm
  #define Vec4SqrtBlockUseSize            Vec4uSqrtBlockUseSizeAsm
  #define Vec4BufSqrtBuf                  Vec4uBufSqrtBufAsm
#endif

extern __C void Vec4uSqrtAsm            (vec4*  r,const vec4* v);
extern __C void Vec4uSqrtBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4uSqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Normalize                   Vec4uNormalizeAsm
  #define Vec4NormalizeBlock              Vec4uNormalizeBlockAsm
  #define Vec4NormalizeBlockUseSize       Vec4uNormalizeBlockUseSizeAsm
  #define Vec4BufNormalizeBuf             Vec4uBufNormalizeBufAsm
#endif

extern __C void Vec4uNormalizeAsm                (vec4*  r,const vec4* v);
extern __C void Vec4uNormalizeBlockAsm           (vec4* ru,const int32_t iCount);
extern __C void Vec4uNormalizeBlockUseSizeAsm    (vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNormalizeBufAsm          (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Length                      Vec4uLengthAsm
  #define Vec4LengthBlock                 Vec4uLengthBlockAsm
  #define Vec4LengthBlockUseSize          Vec4uLengthBlockUseSizeAsm
  #define Vec4BufLengthBuf                Vec4uBufLengthBufAsm
#endif

extern __C void Vec4uLengthAsm            (float* r,const vec4* v);
extern __C void Vec4uLengthBlockAsm       (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4uLengthBlockUseSizeAsm(float* r,const vec4* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufLengthBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Cross                       Vec4uCrossAsm
  #define Vec4CrossBlock                  Vec4uCrossBlockAsm
  #define Vec4CrossBlockUseSize           Vec4uCrossBlockUseSizeAsm
  #define Vec4BufCrossBuf                 Vec4uBufCrossBufAsm
#endif

extern __C void Vec4uCrossAsm            (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uCrossBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uCrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Mat2Negate                      Mat2uNegateAsm
  #define Mat2Add                         Mat2uAddAsm
  #define Mat2AddFloat                    Mat2uAddFloatAsm
  #define Mat2Subtract                    Mat2uSubtractAsm
  #define Mat2SubtractFloat               Mat2uSubtractFloatAsm
  #define Mat2Multiply                    Mat2uMultiplyAsm
  #define Mat2MultiplyVec                 Mat2uMultiplyVecAsm
  #define Mat2MultiplyFloat               Mat2uMultiplyFloatAsm
  #define Mat2Identity                    Mat2uIdentityAsm
  #define Mat2Transpose                   Mat2uTransposeAsm
  #define Mat2MultiplyVecBlock            Mat2uMultiplyVecBlockAsm
#endif

extern __C void Mat2uNegateAsm          (mat2* r,const mat2* m);
extern __C void Mat2uAddAsm             (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uAddFloatAsm        (mat2* r,const mat2* m,const float s);
extern __C void Mat2uSubtractAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uSubtractFloatAsm   (mat2* r,const mat2* m,const float s);
extern __C void Mat2uMultiplyAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uMultiplyVecAsm     (vec2* r,const mat2* m,const vec2* v);
extern __C void Mat2uMultiplyFloatAsm   (mat2* r,const mat2* m,const float x);
extern __C void Mat2uIdentityAsm        (mat2* r);
extern __C void Mat2uTransposeAsm       (mat2* r,const mat2* m);
extern __C void Mat2uMultiplyVecBlockAsm(vec2* r,const mat2* m,const vec2* v,int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Mat2RotateLH                    Mat2RotateLHAsm
  #define Mat2RotateRH                    Mat2RotateRHAsm
  #define Mat2Rotate                      Mat2RotateAsm
  #define Mat2Scale                       Mat2ScaleAsm
#endif

extern __C void Mat2RotateLHAsm(mat2* r,const float angle);
extern __C void Mat2RotateRHAsm(mat2* r,const float angle);
extern __C void Mat2RotateAsm  (mat2* r,const float angle);
extern __C void Mat2ScaleAsm   (mat2* r,const float x_scale,const float y_scale);

#if !defined(__REGRESSION_TEST)
  #define Mat3Copy                        Mat3CopyAsm
  #define Mat3Identity                    Mat3IdentityAsm
#endif

extern __C void Mat3CopyAsm    (mat3* r,const mat3* m);
extern __C void Mat3IdentityAsm(mat3* r);

#if !defined(__REGRESSION_TEST)
  #define Mat3Negate                      Mat3uNegateAsm
  #define Mat3Add                         Mat3uAddAsm
  #define Mat3AddFloat                    Mat3uAddFloatAsm
  #define Mat3Subtract                    Mat3uSubtractAsm
  #define Mat3SubtractFloat               Mat3uSubtractFloatAsm
  #define Mat3Multiply                    Mat3uMultiplyAsm
  #define Mat3MultiplyIdentityByBlocks    Mat3uMultiplyIdentityByBlocksAsm
  #define Mat3MultiplyVec                 Mat3uMultiplyVecAsm
  #define Mat3MultiplyVecBlock            Mat3uMultiplyVecBlockAsm
  #define Mat3MulVecBlockBySize           Mat3uMulVecBlockBySizeAsm
  #define Mat3MulVec3BufByBuf             Mat3uMulVec3BufByBufAsm
  #define Mat3MultiplyFloat               Mat3uMultiplyFloatAsm
  #define Mat3Inverse                     Mat3uInverseAsm
  #define Mat3Transpose                   Mat3uTransposeAsm
#endif

extern __C void Mat3uNegateAsm                  (mat3* r,const mat3* m);
extern __C void Mat3uAddAsm                     (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uAddFloatAsm                (mat3* r,const mat3* m,const float s);
extern __C void Mat3uSubtractAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uSubtractFloatAsm           (mat3* r,const mat3* m,const float s);
extern __C void Mat3uMultiplyAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uMultiplyIdentityByBlocksAsm(mat3* r,const mat3* m,int32_t nCount);
extern __C void Mat3uMultiplyVecAsm             (vec3* r,const mat3* m,const vec3* v);
extern __C void Mat3uMultiplyVecBlockAsm        (vec3* r,const mat3* m,const vec3* v,int32_t iCount);
extern __C void Mat3uMulVecBlockBySizeAsm       (void* r,const mat3* m,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Mat3uMulVec3BufByBufAsm         (void* r,const int32_t iRSize,const mat3* m,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Mat3uMultiplyFloatAsm           (mat3* r,const mat3* m,const float x);
extern __C void Mat3uInverseAsm                 (mat3* r,const mat3* m);
extern __C void Mat3uTransposeAsm               (mat3* r,const mat3* m);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHX                   Mat3RotateRHX_Asm
  #define Mat3RotateLHX                   Mat3RotateLHX_Asm
  #define Mat3RotateRHY                   Mat3RotateRHY_Asm
  #define Mat3RotateLHY                   Mat3RotateLHY_Asm
  #define Mat3RotateRHZ                   Mat3RotateRHZ_Asm
  #define Mat3RotateLHZ                   Mat3RotateLHZ_Asm
#endif

extern __C void Mat3RotateRHX_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateLHX_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateRHY_Asm  (mat3* m,const float angle);
extern __C void Mat3RotateLHY_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateRHZ_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateLHZ_Asm  (mat3* r,const float angle);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHXY                  Mat3RotateRHXY_Asm
  #define Mat3RotateLHXY                  Mat3RotateLHXY_Asm
  #define Mat3RotateRHXZ                  Mat3RotateRHXZ_Asm
  #define Mat3RotateLHXZ                  Mat3RotateLHXZ_Asm
  #define Mat3RotateRHYZ                  Mat3RotateRHYZ_Asm
  #define Mat3RotateLHYZ                  Mat3RotateLHYZ_Asm
#endif

extern __C void Mat3RotateRHXY_Asm (mat3* r,const float x,const float y);
extern __C void Mat3RotateLHXY_Asm (mat3* r,const float x,const float y);
extern __C void Mat3RotateRHXZ_Asm (mat3* m,const float x,const float z);
extern __C void Mat3RotateLHXZ_Asm (mat3* m,const float x,const float z);
extern __C void Mat3RotateRHYZ_Asm (mat3* r,const float y,const float z);
extern __C void Mat3RotateLHYZ_Asm (mat3* m,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHXYZ                 Mat3RotateRHXYZ_Asm
  #define Mat3RotateLHXYZ                 Mat3RotateLHXYZ_Asm
#endif

extern __C void Mat3RotateRHXYZ_Asm(mat3* r,const float x,const float y,const float z);
extern __C void Mat3RotateLHXYZ_Asm(mat3* r,const float x,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat3Scale                       Mat3ScaleAsm
  #define Mat3ScaleByVec3                 Mat3ScaleByVec3Asm
#endif

extern __C void Mat3ScaleAsm      (mat3* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat3ScaleByVec3Asm(mat3* r,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Mat4Copy                        Mat4CopyAsm
#endif

extern __C void Mat4CopyAsm(mat4* r,const mat4* m);

#if !defined(__REGRESSION_TEST)
  #define Mat4Negate                      Mat4uNegateAsm
  #define Mat4NegateMatrix                Mat4uNegateMatrixAsm
  #define Mat4Add                         Mat4uAddAsm
  #define Mat4AddFloat                    Mat4uAddFloatAsm
  #define Mat4AddMatrix                   Mat4uAddMatrixAsm
  #define Mat4Subtract                    Mat4uSubtractAsm
  #define Mat4SubtractFloat               Mat4uSubtractFloatAsm
  #define Mat4SubtractMatrix              Mat4uSubtractMatrixAsm
  #define Mat4MultiplyMatrix              Mat4uMultiplyMatrixAsm
  #define Mat4Multiply                    Mat4uMultiplyAsm
  #define Mat4MultiplyVec                 Mat4uMultiplyVecAsm
  #define Mat4LookAt                      Mat4uLookAtAsm
#endif

extern __C void Mat4uNegateAsm        (mat4* r,const mat4* m);
extern __C void Mat4uNegateMatrixAsm  (mat4* r);
extern __C void Mat4uAddAsm           (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uAddFloatAsm      (mat4* r,const mat4* m,const float s);
extern __C void Mat4uAddMatrixAsm     (mat4* m,const mat4* n);
extern __C void Mat4uSubtractAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uSubtractFloatAsm (mat4* r,const mat4* m,const float s);
extern __C void Mat4uSubtractMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4uMultiplyMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4uMultiplyAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uMultiplyVecAsm   (vec4* r,const mat4* m,const vec4* v);
extern __C void Mat4uLookAtAsm        (mat4* r,const vec3* from,const vec3* at);

#if !defined(__REGRESSION_TEST)
  #define Mat4MultiplyFloat               Mat4uMultiplyFloatAsm
  #define Mat4Transpose                   Mat4uTransposeAsm
  #define Mat4ShadowMatrix                Mat4uShadowMatrixAsm
  #define Mat4MirrorMatrix                Mat4uMirrorMatrixAsm
  #define Mat4GlToD3DProjMat              Mat4uGlToD3DProjMatAsm
  #define Mat4LookAtLH                    Mat4uLookAtLHAsm
#endif

extern __C void Mat4uMultiplyFloatAsm (mat4* r,const mat4* m,const float x);
extern __C void Mat4uTransposeAsm     (mat4* r,const mat4* m);
extern __C void Mat4uShadowMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset,const vec3* lightPos);
extern __C void Mat4uMirrorMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset);
extern __C void Mat4uGlToD3DProjMatAsm(mat4* r,const mat4* m);
extern __C void Mat4uLookAtLHAsm      (mat4* r,const vec3* pEye,const vec3* pLookAt,const vec3* pUp);

#if !defined(__REGRESSION_TEST)
  #define Mat4Identity                    Mat4IdentityAsm
  #define Mat4Scale                       Mat4ScaleAsm
#endif

extern __C void Mat4IdentityAsm(mat4* r);
extern __C void Mat4ScaleAsm   (mat4* r,const float x_scale,const float y_scale,const float z_scale);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHX                   Mat4RotateRHX_Asm
  #define Mat4RotateLHX                   Mat4RotateLHX_Asm
  #define Mat4RotateRHY                   Mat4RotateRHY_Asm
  #define Mat4RotateLHY                   Mat4RotateLHY_Asm
  #define Mat4RotateRHZ                   Mat4RotateRHZ_Asm
  #define Mat4RotateLHZ                   Mat4RotateLHZ_Asm
#endif

extern __C void Mat4RotateRHX_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHX_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateRHY_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHY_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateRHZ_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHZ_Asm  (mat4* r,const float angle);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHXY                  Mat4RotateRHXY_Asm
  #define Mat4RotateLHXY                  Mat4RotateLHXY_Asm
  #define Mat4RotateRHXZ                  Mat4RotateRHXZ_Asm
  #define Mat4RotateLHXZ                  Mat4RotateLHXZ_Asm
  #define Mat4RotateRHYZ                  Mat4RotateRHYZ_Asm
  #define Mat4RotateLHYZ                  Mat4RotateLHYZ_Asm
#endif

extern __C void Mat4RotateRHXY_Asm (mat4* r,const float x_scale,const float y_scale);
extern __C void Mat4RotateLHXY_Asm (mat4* r,const float x,const float y);
extern __C void Mat4RotateRHXZ_Asm (mat4* m,const float x,const float z);
extern __C void Mat4RotateLHXZ_Asm (mat4* m,const float x,const float z);
extern __C void Mat4RotateRHYZ_Asm (mat4* r,const float y,const float z);
extern __C void Mat4RotateLHYZ_Asm (mat4* m,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHXYZ                 Mat4RotateRHXYZ_Asm
  #define Mat4RotateLHXYZ                 Mat4RotateLHXYZ_Asm
#endif

extern __C void Mat4RotateRHXYZ_Asm(mat4* r,const float x,const float y,const float z);
extern __C void Mat4RotateLHXYZ_Asm(mat4* r,const float x,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat4TranslateRH                 Mat4TranslateRH_Asm
  #define Mat4TranslateLH                 Mat4TranslateLH_Asm
  #define Mat4TranslateRH_Vec3            Mat4TranslateRH_Vec3Asm
  #define Mat4TranslateLH_Vec3            Mat4TranslateLH_Vec3Asm
  #define Mat4TranslateRH_Vec4            Mat4TranslateRH_Vec4Asm
  #define Mat4TranslateLH_Vec4            Mat4TranslateLH_Vec4Asm
#endif

extern __C void Mat4TranslateRH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateLH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateRH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateLH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateRH_Vec4Asm (mat4* r,const vec4* v);
extern __C void Mat4TranslateLH_Vec4Asm (mat4* r,const vec4* v);

#if !defined(__REGRESSION_TEST)
  #define Mat4OrthoMatrix                 Mat4OrthoMatrixAsm
  #define Mat4OrthoStruct                 Mat4OrthoStructAsm
  #define Mat4Perspective                 Mat4PerspectiveAsm
  #define Mat4PerspectiveX                Mat4PerspectiveXAsm
  #define Mat4CubemapMatrix               Mat4CubemapMatrixAsm
  #define Mat4CubemapProjectionMat        Mat4CubemapProjectionMatAsm
  //#define Mat4LookAtHoriz                 Mat4LookAtHorizAsm
#endif

extern __C void Mat4OrthoMatrixAsm(mat4*         r,
                                   const float   left,
                                   const float   right,
                                   const float   top,
                                   const float   bottom,
                                   const float   zNear,
                                   const float   zFar,
                                   const int32_t d3dFlag);
extern __C void Mat4OrthoStructAsm(mat4* r,const orthoMatrix* s);

extern __C void Mat4PerspectiveAsm (mat4*          r,
                                    const float    fov,
                                    const float    width,
                                    const float    height,
                                    const float    zNear,
                                    const float    zFar,
                                    const uint32_t d3dflag);
extern __C void Mat4PerspectiveXAsm(mat4* r,const struct perspectiveMatrix* s);
extern __C void Mat4CubemapMatrixAsm(mat4* r,const unsigned int face);
extern __C void Mat4CubemapProjectionMatAsm(mat4* r,const float zNear,const float zFar,const uint32_t d3dflag);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotationFromMat4            Mat3RotationFromMat4Asm
  #define Mat4FromMat3                    Mat4FromMat3Asm
#endif

extern __C void Mat3RotationFromMat4Asm    (mat3* r,const mat4* m);
extern __C void Mat4FromMat3Asm            (mat4* r,const mat3* m);

#if !defined(__REGRESSION_TEST)
  #define QuaternionAdd                   uQuaternionAddAsm
  #define QuaternionMultiply              uQuaternionMultiplyAsm
  #define QuaternionInverse               uQuaternionInverseAsm
  #define QuaternionToMat3                uQuaternionToMat3Asm
  #define QuaternionToMat4                uQuaternionToMat4Asm
#endif

extern __C void uQuaternionAddAsm     (quaternion* r,const quaternion* q,const quaternion* v);
extern __C void uQuaternionMultiplyAsm(quaternion*r,const quaternion* u,const quaternion* v);
extern __C void uQuaternionInverseAsm (quaternion* r,const quaternion* q);
extern __C void uQuaternionToMat3Asm  (mat3* r,const quaternion* qp);
extern __C void uQuaternionToMat4Asm  (mat4* m,const quaternion* q);

#if !defined(__REGRESSION_TEST)
  #define QuaternionNormalize             uQuaternionNormalizeAsm
  #define QuaternionDot                   uQuaternionDotAsm
#endif

extern __C void uQuaternionNormalizeAsm(quaternion* r,const quaternion* q);
extern __C void uQuaternionDotAsm      (float* r,const quaternion* q,const quaternion* v);

#if !defined(__REGRESSION_TEST)
  #define QuaternionFromAxis              QuaternionFromAxisAsm
  #define QuaternionFromMat3              QuaternionFromMat3Asm
  #define QuaternionFromMat4              QuaternionFromMat4Asm
  #define QuaternionFromMat3              QuaternionFromMat3Asm
  #define QuaternionSlerp                 QuaternionSlerpAsm
  #define QuaternionCos                   QuaternionCosAsm
  #define QuaternionSin                   QuaternionSinAsm
#endif

extern __C void QuaternionFromAxisAsm(quaternion* r,const vec3* v,const float angle);
extern __C void QuaternionFromMat3Asm(quaternion* r,const mat3* m);
extern __C void QuaternionFromMat4Asm(quaternion* r,const mat4* m);
extern __C void QuaternionSlerpAsm   (quaternion* r,const float s,const quaternion* q,const quaternion* v);
extern __C void QuaternionCosAsm     (float* r,const quaternion* q,const quaternion* p);
extern __C void QuaternionSinAsm     (float* r,const quaternion* q,const quaternion* p);

#elif defined(__BUILD_ALIGNED_LIB) || defined(__ALIGNED_LIB)

/* --------------- *
 * Aligned Library *
 * ----------------*------------------------------------------------------ *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if !defined(__REGRESSION_TEST)
  #define GetFpuStatus                    GetFpuStatusAsm
  #define ClearFpuStatus                  ClearFpuStatusAsm
  #define FloatLerp                       FloatLerpAsm
  #define FloatLerpPtr                    FloatLerpPtrAsm
  #define FloatSqr                        FloatSqrAsm
  #define FloatSqrPtr                     FloatSqrPtrAsm
  #define fCos                            fCosAsm
  #define fSin                            fSinAsm
  #define fTan                            fTanAsm
  #define fACos                           AfCosAsm
  #define fASin                           AfSinAsm
  #define fATan                           AfTanAsm
  #define Cos                             CosAsm
  #define Sin                             SinAsm
  #define Tan                             TanAsm
  #define ACos                            ACosAsm
  #define ASin                            ASinAsm
  #define ATan                            ATanAsm
#endif

extern __C void  GetFpuStatusAsm  (unsigned short* uStatus);
extern __C void  ClearFpuStatusAsm(unsigned short* uStatus);
extern __C float FloatLerpAsm     (const float x,const float v,const float u);
extern __C void  FloatLerpPtrAsm  (float* ret,const float* u,const float* v,const float* x);
extern __C float FloatSqrAsm      (float x);
extern __C float FloatSqrPtrAsm   (float* x);

extern __C float fCosAsm(const float angle);
extern __C float fSinAsm(const float angle);
extern __C float fTanAsm(const float angle);
extern __C float AfCosAsm(const float cosa);
extern __C float AfSinAsm(const float sina);
extern __C float AfTanAsm(const float tana);

extern __C double CosAsm(const double angle);
extern __C double SinAsm(const double angle);
extern __C double TanAsm(const double angle);
extern __C double ACosAsm(const double cosa);
extern __C double ASinAsm(const double sina);
extern __C double ATanAsm(const double tana);

#if !defined(__REGRESSION_TEST)
  #define Vec2Copy                        Vec2CopyAsm
  #define Vec2CopyBlock                   Vec2CopyBlockAsm
  #define BuildVec2PackedArray            BuildVec2PackedArrayAsm
#endif

extern __C void Vec2CopyAsm            (vec2* r,const vec2* v);
extern __C void Vec2CopyBlockAsm       (vec2* r,vec2* v,int32_t iCount);
extern __C void BuildVec2PackedArrayAsm(vec2* r,const vec2** ppList,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddFloat                    Vec2AddFloatFPU_Asm
  #define Vec2SubtractFloat               Vec2SubtractFloatFPU_Asm
  #define Vec2MultiplyFloat               Vec2MultiplyFloatFPU_Asm
  #define Vec2FloatMultiply               Vec2FloatMultiplyFPU_Asm
  #define Vec2DivideFloat                 Vec2DivideFloatFPU_Asm
#endif

extern __C void Vec2AddFloatFPU_Asm     (vec2* r,const vec2* u,const float s);
extern __C void Vec2SubtractFloatFPU_Asm(vec2* r,const vec2* u,const float s);
extern __C void Vec2MultiplyFloatFPU_Asm(vec2* r,const vec2* u,const float s);
extern __C void Vec2FloatMultiplyFPU_Asm(vec2* r,const float s,const vec2* v);
extern __C void Vec2DivideFloatFPU_Asm  (vec2* r,const vec2* u,const float s);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddFloatToBlock             Vec2AddFloatToBlockFPU_Asm
  #define Vec2AddFloatToBlockSize         Vec2AddFloatToBlockSizeFPU_Asm
  #define Vec2BufAddFloatToBlock          Vec2BufAddFloatToBlockFPU_Asm
  #define Vec2BufAddFloatToBuf            Vec2BufAddFloatToBufFPU_Asm
#endif

extern __C void Vec2AddFloatToBlockFPU_Asm    (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2AddFloatToBlockSizeFPU_Asm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBlockFPU_Asm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBufFPU_Asm   (void*  r,const int32_t iRSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2SubtractFloatFromBlock      Vec2SubtractFloatFromBlockFPU_Asm
  #define Vec2SubFloatFromBlockSize       Vec2SubFloatFromBlockSizeFPU_Asm
  #define Vec2BufSubFloatFromBlkSize      Vec2BufSubFloatFromBlkSizeFPU_Asm
  #define Vec2BufSubFloatFromBuf          Vec2BufSubFloatFromBufFPU_Asm
#endif

extern __C void Vec2SubtractFloatFromBlockFPU_Asm(vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2SubFloatFromBlockSizeFPU_Asm (vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBlkSizeFPU_Asm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBufFPU_Asm    (void*  r,const int32_t iDstSize,const void* u,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2MultiplyBlockByFloat        Vec2MultiplyBlockByFloatFPU_Asm
  #define Vec2MultiplyBlkByFloatSize      Vec2MultiplyBlkByFloatSizeFPU_Asm
  #define Vec2BufMulBlockByFloatSize      Vec2BufMulBlockByFloatSizeFPU_Asm
  #define Vec2BufMulBlockByFloatBuf       Vec2BufMulBlockByFloatBufFPU_Asm
#endif

extern __C void Vec2MultiplyBlockByFloatFPU_Asm  (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2MultiplyBlkByFloatSizeFPU_Asm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatSizeFPU_Asm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatBufFPU_Asm (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2DivideBlockByFloat          Vec2DivideBlockByFloatFPU_Asm
  #define Vec2DivideBlockByFloatSize      Vec2DivideBlockByFloatSizeFPU_Asm
  #define Vec2BufDivBlockByFloatSize      Vec2BufDivBlockByFloatSizeFPU_Asm
  #define Vec2BufDivBufByFloat            Vec2BufDivBufByFloatFPU_Asm
#endif

extern __C void Vec2DivideBlockByFloatFPU_Asm    (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2DivideBlockByFloatSizeFPU_Asm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockByFloatSizeFPU_Asm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufByFloatFPU_Asm      (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2Negate                      Vec2NegateAsm
  #define Vec2Add                         Vec2AddAsm
  #define Vec2Subtract                    Vec2SubtractAsm
  #define Vec2Multiply                    Vec2MultiplyAsm
  #define Vec2Divide                      Vec2DivideAsm
#endif
extern __C void Vec2NegateAsm  (vec2* r,const vec2* u);
extern __C void Vec2AddAsm     (vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2SubtractAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2MultiplyAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2DivideAsm  (vec2* r,const vec2* u,const vec2* v);

#if !defined(__REGRESSION_TEST)
  #define Vec2Equals                      Vec2EqualsAsm
  #define Vec2NotEquals                   Vec2NotEqualsAsm
#endif

extern __C void Vec2EqualsAsm   (int32_t* iFlag,const vec2* u,const vec2* v);
extern __C void Vec2NotEqualsAsm(int32_t* iFlag,const vec2* u,const vec2* v);

#if !defined(__REGRESSION_TEST)
  #define Vec2NegateBlock                 Vec2NegateBlockAsm
  #define Vec2NegateBlockBySize           Vec2NegateBlockBySizeAsm
  #define Vec2BufNegateBlockBySize        Vec2BufNegateBlockBySizeAsm
  #define Vec2BufNegateBufBySize          Vec2BufNegateBufBySizeAsm
#endif

extern __C void Vec2NegateBlockAsm (vec2* rv,const int32_t iCount);
extern __C void Vec2NegateBlockBySizeAsm   (vec2* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBlockBySizeAsm(vec2*  r,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBufBySizeAsm  (vec2*  r,const int32_t iDstSize,const vec2* v,const int32_t iSrcSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddVec2ToBlock              Vec2AddVec2ToBlockAsm
  #define Vec2AddBlockToBlock             Vec2AddBlockToBlockAsm
  #define Vec2BufAddVec2ToBlockBySize     Vec2BufAddVec2ToBlockBySizeAsm
  #define Vec2BufAddBlockBySize           Vec2BufAddBlockBySizeAsm
  #define Vec2BufAddBufBySize             Vec2BufAddBufBySizeAsm
#endif

extern __C void Vec2AddVec2ToBlockAsm         (vec2* rv,const vec2* v,const int32_t iCount);
extern __C void Vec2AddBlockToBlockAsm        (vec2* rv,const vec2* v,int32_t iCount);
extern __C void Vec2BufAddVec2ToBlockBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2SubtractVec2FromBlock       Vec2SubtractVec2FromBlockAsm
  #define Vec2SubtractBlockFromBlock      Vec2SubtractBlockFromBlockAsm
  #define Vec2BufSubVec2FromBlkBySize     Vec2BufSubVec2FromBlkBySizeAsm
  #define Vec2BufSubBlockBySize           Vec2BufSubBlockBySizeAsm
  #define Vec2BufSubBufBySize             Vec2BufSubBufBySizeAsm
#endif

extern __C void Vec2SubtractVec2FromBlockAsm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2SubtractBlockFromBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufSubVec2FromBlkBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2MultiplyBlockByVec2         Vec2MultiplyBlockByVec2Asm
  #define Vec2MultiplyBlockByBlock        Vec2MultiplyBlockByBlockAsm
  #define Vec2BufMulVec2ByBlockSize       Vec2BufMulVec2ByBlockSizeAsm
  #define Vec2BufMulBlockBySize           Vec2BufMulBlockBySizeAsm
  #define Vec2BufMulBufBySize             Vec2BufMulBufBySizeAsm
#endif

extern __C void Vec2MultiplyBlockByVec2Asm  (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2MultiplyBlockByBlockAsm (vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufMulVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2DivideBlockByVec2           Vec2DivideBlockByVec2Asm
  #define Vec2DivideBlockByBlock          Vec2DivideBlockByBlockAsm
  #define Vec2BufDivVec2ByBlockSize       Vec2BufDivVec2ByBlockSizeAsm
  #define Vec2BufDivBlockBySize           Vec2BufDivBlockBySizeAsm
  #define Vec2BufDivBufBySize             Vec2BufDivBufBySizeAsm
#endif

extern __C void Vec2DivideBlockByVec2Asm    (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2DivideBlockByBlockAsm   (vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufDivVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2LerpBlock                   Vec2LerpBlockAsm
  #define Vec2SqrBlock                    Vec2SqrBlockAsm
  #define Vec2SqrtBlock                   Vec2SqrtBlockAsm
  #define Vec2NormalizeBlock              Vec2NormalizeBlockAsm
  #define Vec2DotBlock                    Vec2DotBlockAsm
#endif

extern __C void Vec2LerpBlockAsm     (vec2*  r,const vec2* u,const vec2* v,const float step,const int32_t iCount);
extern __C void Vec2SqrBlockAsm      (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2SqrtBlockAsm     (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2NormalizeBlockAsm(vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2DotBlockAsm      (float* r,const vec2* u,const vec2* v,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2Lerp                        Vec2LerpAsm
  #define Vec2Sqr                         Vec2SqrAsm
  #define Vec2Sqrt                        Vec2SqrtAsm
  #define Vec2Normalize                   Vec2NormalizeAsm
  #define Vec2Dot                         Vec2DotAsm
  #define Vec2Length                      Vec2LengthAsm
  #define Vec2LengthBlock                 Vec2LengthBlockAsm
#endif

extern __C void Vec2LerpAsm       (vec2*  r,const vec2* u,const vec2* v,const float step);
extern __C void Vec2SqrAsm        (vec2*  r,const vec2* u);
extern __C void Vec2SqrtAsm       (vec2*  r,const vec2* u);
extern __C void Vec2NormalizeAsm  (vec2*  r,const vec2* v);
extern __C void Vec2DotAsm        (float* f,const vec2* u,const vec2* v);
extern __C void Vec2LengthAsm     (float* r,const vec2* v);
extern __C void Vec2LengthBlockAsm(float* r,const vec2* v,const int32_t nCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2BufLerpBuf                  Vec2BufLerpBufAsm
  #define Vec2BufSqrBuf                   Vec2BufSqrBufAsm
  #define Vec2BufSqrtBuf                  Vec2BufSqrtBufAsm
  #define Vec2BufNormalizeBuf             Vec2BufNormalizeBufAsm
  #define Vec2BufDotBuf                   Vec2BufDotBufAsm
  #define Vec2BufLengthBuf                Vec2BufLengthBufAsm
#endif

extern __C void Vec2BufLerpBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);
extern __C void Vec2BufSqrBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufSqrtBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufNormalizeBufAsm(void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufDotBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Vec2BufLengthBufAsm   (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Copy                        Vec3CopyAsm
  #define Vec3CopyBlock                   Vec3CopyBlockAsm
  #define BuildVec3PackedArray            BuildVec3PackedArrayAsm
#endif

extern __C void Vec3CopyAsm            (vec3* r,const vec3*  u);
extern __C void Vec3CopyBlockAsm       (vec3* r,const vec3*  u,const int32_t iCount);
extern __C void BuildVec3PackedArrayAsm(vec3* r,const vec3** pu,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3AddFloat                    Vec3AddFloatAsm
  #define Vec3AddFloatToBlock             Vec3AddFloatToBlockAsm
  #define Vec3AddFloatToBlockBySize       Vec3AddFloatToBlockBySizeAsm
  #define Vec3BufAddFloatToBlock          Vec3BufAddFloatToBlockAsm
  #define Vec3BufAddFloatToBuf            Vec3BufAddFloatToBufAsm
#endif

extern __C void Vec3AddFloatAsm             (vec3*  r,const vec3* v,const float s);
extern __C void Vec3AddFloatToBlockAsm      (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3AddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3SubtractFloat               Vec3SubtractFloatAsm
  #define Vec3SubtractFloatFromBlock      Vec3SubtractFloatFromBlockAsm
  #define Vec3SubFloatFromBlockBySize     Vec3SubFloatFromBlockBySizeAsm
  #define Vec3BufSubFloatFromBlock        Vec3BufSubFloatFromBlockAsm
  #define Vec3BufSubFloatFromBuf          Vec3BufSubFloatFromBufAsm
#endif

extern __C void Vec3SubtractFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3SubtractFloatFromBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3SubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3MultiplyFloat               Vec3MultiplyFloatAsm
  #define Vec3MultiplyFloatToBlock        Vec3MultiplyFloatToBlockAsm
  #define Vec3MulFloatToBlockBySize       Vec3MulFloatToBlockBySizeAsm
  #define Vec3BufMulFloatToBlock          Vec3BufMulFloatToBlockAsm
  #define Vec3BufMulFloatToBuf            Vec3BufMulFloatToBufAsm
#endif

extern __C void Vec3MultiplyFloatAsm        (vec3*  r,const vec3* u,const float s);
extern __C void Vec3MultiplyFloatToBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3MulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3DivideFloat                 Vec3DivideFloatAsm
  #define Vec3DivideBlockByFloat          Vec3DivideBlockByFloatAsm
  #define Vec3DivBlockByFloatBySize       Vec3DivBlockByFloatBySizeAsm
  #define Vec3BufDivBlockByFloat          Vec3BufDivBlockByFloatAsm
  #define Vec3BufDivBufByFloat            Vec3BufDivBufByFloatAsm
#endif

extern __C void Vec3DivideFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3DivideBlockByFloatAsm   (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3DivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Equals                      Vec3EqualsAsm
  #define Vec3NotEquals                   Vec3NotEqualsAsm
#endif

extern __C void Vec3EqualsAsm   (int32_t* iFlag,const vec3* u,const vec3* v);
extern __C void Vec3NotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Vec3Negate                      Vec3NegateAsm
  #define Vec3NegateBlock                 Vec3NegateBlockAsm
  #define Vec3NegateBlockBySize           Vec3NegateBlockBySizeAsm
  #define Vec3BufNegateBlock              Vec3BufNegateBlockAsm
  #define Vec3BufNegateBuf                Vec3BufNegateBufAsm
#endif

extern __C void Vec3NegateAsm           (vec3*  r,const vec3* v);
extern __C void Vec3NegateBlockAsm      (vec3* rv,int32_t iCount);
extern __C void Vec3NegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Add                         Vec3AddAsm
  #define Vec3AddVecToBlock               Vec3AddVecToBlockAsm
  #define Vec3AddVecToBlockBySize         Vec3AddVecToBlockBySizeAsm
  #define Vec3BufAddVecToBlock            Vec3BufAddVecToBlockAsm
  #define Vec3BufAddVecToBuf              Vec3BufAddVecToBufAsm
  #define Vec3AddBlockToBlock             Vec3AddBlockToBlockAsm
  #define Vec3AddBlockToBlockBySize       Vec3AddBlockToBlockBySizeAsm
  #define Vec3BufAddBlockToBuf            Vec3BufAddBlockToBufAsm
  #define Vec3BufAddBufToBuf              Vec3BufAddBufToBufAsm
#endif

extern __C void Vec3AddAsm                  (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3AddVecToBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3AddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec3AddBlockToBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3AddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Subtract                    Vec3SubtractAsm
  #define Vec3SubVecFromBlock             Vec3SubVecFromBlockAsm
  #define Vec3SubVecFromBlockBySize       Vec3SubVecFromBlockBySizeAsm
  #define Vec3BufSubVecFromBlock          Vec3BufSubVecFromBlockAsm
  #define Vec3BufSubVecFromBuf            Vec3BufSubVecFromBufAsm
  #define Vec3SubBlockFromBlock           Vec3SubBlockFromBlockAsm
  #define Vec3SubBlockFromBlockBySize     Vec3SubBlockFromBlockBySizeAsm
  #define Vec3BufSubBlockFromBuf          Vec3BufSubBlockFromBufAsm
  #define Vec3BufSubBufFromBuf            Vec3BufSubBufFromBufAsm
#endif

extern __C void Vec3SubtractAsm               (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3SubVecFromBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3SubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3SubBlockFromBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3SubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Multiply                    Vec3MultiplyAsm
  #define Vec3MulBlockByVec               Vec3MulBlockByVecAsm
  #define Vec3MulBlockByVecUseSize        Vec3MulBlockByVecUseSizeAsm
  #define Vec3BufMulBufByVec              Vec3BufMulBufByVecAsm
  #define Vec3BufMulBufByVecUseSize       Vec3BufMulBufByVecUseSizeAsm
  #define Vec3MulBlockByBlock             Vec3MulBlockByBlockAsm
  #define Vec3MulBlockByBlockUseSize      Vec3MulBlockByBlockUseSizeAsm
  #define Vec3BufMulBufByBlock            Vec3BufMulBufByBlockAsm
  #define Vec3BufMulBufByBuf	        Vec3BufMulBufByBufAsm	
#endif

extern __C void Vec3MultiplyAsm              (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3MulBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3BufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3MulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3MulBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3MulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Divide                      Vec3DivideAsm
  #define Vec3DivBlockByVec               Vec3DivBlockByVecAsm
  #define Vec3DivBlockByVecUseSize        Vec3DivBlockByVecUseSizeAsm
  #define Vec3BufDivBufByVec              Vec3BufDivBufByVecAsm
  #define Vec3BufDivBufByVecUseSize       Vec3BufDivBufByVecUseSizeAsm
  #define Vec3DivBlockByBlock             Vec3DivBlockByBlockAsm
  #define Vec3DivBlockByBlockUseSize      Vec3DivBlockByBlockUseSizeAsm
  #define Vec3BufDivBufByBlock            Vec3BufDivBufByBlockAsm
  #define Vec3BufDivBufByBuf              Vec3BufDivBufByBufAsm
#endif

extern __C void Vec3DivideAsm                (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3DivBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByVecUseSizeAsm  (void* ru,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByVecAsm        (void*  r,const void* u,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Lerp                        Vec3LerpAsm
  #define Vec3LerpBlock                   Vec3LerpBlockAsm
  #define Vec3LerpBlockUseSize            Vec3LerpBlockUseSizeAsm
  #define Vec3BufLerpBlock                Vec3BufLerpBlockAsm
  #define Vec3BufLerpBuf                  Vec3BufLerpBufAsm
#endif

extern __C void Vec3LerpAsm            (vec3*  r,const vec3* u,const vec3* v,const float s);
extern __C void Vec3LerpBlockAsm       (vec3* ru,vec3* v,const float s,const int32_t iCount);
extern __C void Vec3LerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec3BufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Dot                         Vec3DotFlatAsm
  #define Vec3DotBlock                    Vec3DotBlockAsm
  #define Vec3DotBlockUseSize             Vec3DotBlockUseSizeAsm
  #define Vec3BufDotBuf                   Vec3BufDotBufAsm
#endif

extern __C void Vec3DotFlatAsm (float* r,const vec3* u,const vec3* v);
extern __C void Vec3DotBlockAsm       (float* r,const vec3* u,const vec3* v,const int32_t iCount);
extern __C void Vec3DotBlockUseSizeAsm(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDotBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Sqr                         Vec3SqrAsm
  #define Vec3SqrBlock                    Vec3SqrBlockAsm
  #define Vec3SqrBlockUseSize             Vec3SqrBlockUseSizeAsm
  #define Vec3BufSqrBuf                   Vec3BufSqrBufAsm
#endif

extern __C void Vec3SqrAsm            (vec3*  r,const vec3* v);
extern __C void Vec3SqrBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3SqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Sqrt                        Vec3SqrtAsm
  #define Vec3SqrtBlock                   Vec3SqrtBlockAsm
  #define Vec3SqrtBlockUseSize            Vec3SqrtBlockUseSizeAsm
  #define Vec3BufSqrtBuf                  Vec3BufSqrtBufAsm
#endif

extern __C void Vec3SqrtAsm            (vec3*  r,const vec3* v);
extern __C void Vec3SqrtBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3SqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Normalize                   Vec3NormalizeFlatAsm
  #define Vec3NormalizeBlock              Vec3NormalizeBlockFlatAsm
  #define Vec3NormalizeBlockUseSize       Vec3NormalizeBlockFlatUseSizeAsm
  #define Vec3BufNormalizeBuf             Vec3BufNormalizeBufFlatAsm
#endif

extern __C void Vec3NormalizeFlatAsm            (vec3*  r,const vec3* v);
extern __C void Vec3NormalizeBlockFlatAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3NormalizeBlockFlatUseSizeAsm(vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNormalizeBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Length                      Vec3LengthFlatAsm
  #define Vec3LengthBlock                 Vec3LengthBlockFlatAsm
  #define Vec3LengthBlockUseSize          Vec3LengthBlockFlatUseSizeAsm
  #define Vec3BufLengthBuf                Vec3BufLengthBufFlatAsm
#endif

extern __C void Vec3LengthFlatAsm         (float* r,const vec3* v);
extern __C void Vec3LengthBlockFlatAsm    (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3LengthBlockFlatUseSize(float* r,const vec3* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLengthBufFlatAsm   (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Cross                       Vec3CrossAsm
  #define Vec3CrossBlock                  Vec3CrossBlockAsm
  #define Vec3CrossBlockUseSize           Vec3CrossBlockUseSizeAsm
  #define Vec3BufCrossBuf                 Vec3BufCrossBufAsm
#endif

extern __C void Vec3CrossAsm            (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3CrossBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3CrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Reflect                     Vec3ReflectAsm
#endif

extern __C void Vec3ReflectAsm (vec3* r,const vec3* u,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Vec4Copy                        Vec4CopyAsm
  #define Vec4CopyBlock                   Vec4CopyBlockAsm
  #define BuildVec4PackedArray            BuildVec4PackedArrayAsm
#endif

extern __C void Vec4CopyAsm            (vec4* r,const vec4*  u);
extern __C void Vec4CopyBlockAsm       (vec4* r,const vec4*  u,const int32_t iCount);
extern __C void BuildVec4PackedArrayAsm(vec4* r,const vec4** pu,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4AddFloat                    Vec4AddFloatAsm
  #define Vec4AddFloatToBlock             Vec4AddFloatToBlockAsm
  #define Vec4AddFloatToBlockBySize       Vec4AddFloatToBlockBySizeAsm
  #define Vec4BufAddFloatToBlock          Vec4BufAddFloatToBlockAsm
  #define Vec4BufAddFloatToBuf            Vec4BufAddFloatToBufAsm
#endif

extern __C void Vec4AddFloatAsm             (vec4*  r,const vec4* v,const float s);
extern __C void Vec4AddFloatToBlockAsm      (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4AddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4SubtractFloat               Vec4SubtractFloatAsm
  #define Vec4SubtractFloatFromBlock      Vec4SubtractFloatFromBlockAsm
  #define Vec4SubFloatFromBlockBySize     Vec4SubFloatFromBlockBySizeAsm
  #define Vec4BufSubFloatFromBlock        Vec4BufSubFloatFromBlockAsm
  #define Vec4BufSubFloatFromBuf          Vec4BufSubFloatFromBufAsm
#endif

extern __C void Vec4SubtractFloatAsm          (vec4* r,const vec4* u,const float s);
extern __C void Vec4SubtractFloatFromBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4SubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4MultiplyFloat               Vec4MultiplyFloatAsm
  #define Vec4MultiplyFloatToBlock        Vec4MultiplyFloatToBlockAsm
  #define Vec4MulFloatToBlockBySize       Vec4MulFloatToBlockBySizeAsm
  #define Vec4BufMulFloatToBlock          Vec4BufMulFloatToBlockAsm
  #define Vec4BufMulFloatToBuf            Vec4BufMulFloatToBufAsm
#endif

extern __C void Vec4MultiplyFloatAsm        (vec4*  r,const vec4* u,const float s);
extern __C void Vec4MultiplyFloatToBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4MulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4DivideFloat                 Vec4DivideFloatAsm
  #define Vec4DivideBlockByFloat          Vec4DivideBlockByFloatAsm
  #define Vec4DivBlockByFloatBySize       Vec4DivBlockByFloatBySizeAsm
  #define Vec4BufDivBlockByFloat          Vec4BufDivBlockByFloatAsm
  #define Vec4BufDivBufByFloat            Vec4BufDivBufByFloatAsm
#endif

extern __C void Vec4DivideFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4DivideBlockByFloatAsm   (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4DivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Equals                      Vec4EqualsAsm
  #define Vec4NotEquals                   Vec4NotEqualsAsm
#endif

extern __C void Vec4EqualsAsm   (int32_t* iFlag,const vec4* u,const vec4* v);
extern __C void Vec4NotEqualsAsm(int32_t* iFlag,const vec4* u,const vec4* v);

#if !defined(__REGRESSION_TEST)
  #define Vec4Negate                      Vec4NegateAsm
  #define Vec4NegateBlock                 Vec4NegateBlockAsm
  #define Vec4NegateBlockBySize           Vec4NegateBlockBySizeAsm
  #define Vec4BufNegateBlock              Vec4BufNegateBlockAsm
  #define Vec4BufNegateBuf                Vec4BufNegateBufAsm
#endif

extern __C void Vec4NegateAsm           (vec4*  r,const vec4* v);
extern __C void Vec4NegateBlockAsm      (vec4* rv,const int32_t iCount);
extern __C void Vec4NegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Add                         Vec4AddAsm
  #define Vec4AddVecToBlock               Vec4AddVecToBlockAsm
  #define Vec4AddVecToBlockBySize         Vec4AddVecToBlockBySizeAsm
  #define Vec4BufAddVecToBlock            Vec4BufAddVecToBlockAsm
  #define Vec4BufAddVecToBuf              Vec4BufAddVecToBufAsm
  #define Vec4AddBlockToBlock             Vec4AddBlockToBlockAsm
  #define Vec4AddBlockToBlockBySize       Vec4AddBlockToBlockBySizeAsm
  #define Vec4BufAddBlockToBuf            Vec4BufAddBlockToBufAsm
  #define Vec4BufAddBufToBuf              Vec4BufAddBufToBufAsm
#endif

extern __C void Vec4AddAsm                  (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4AddVecToBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4AddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec4AddBlockToBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4AddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Subtract                    Vec4SubtractAsm
  #define Vec4SubVecFromBlock             Vec4SubVecFromBlockAsm
  #define Vec4SubVecFromBlockBySize       Vec4SubVecFromBlockBySizeAsm
  #define Vec4BufSubVecFromBlock          Vec4BufSubVecFromBlockAsm
  #define Vec4BufSubVecFromBuf            Vec4BufSubVecFromBufAsm
  #define Vec4SubBlockFromBlock           Vec4SubBlockFromBlockAsm
  #define Vec4SubBlockFromBlockBySize     Vec4SubBlockFromBlockBySizeAsm
  #define Vec4BufSubBlockFromBuf          Vec4BufSubBlockFromBufAsm
  #define Vec4BufSubBufFromBuf            Vec4BufSubBufFromBufAsm
#endif

extern __C void Vec4SubtractAsm               (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4SubVecFromBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4SubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4SubBlockFromBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4SubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Multiply                    Vec4MultiplyAsm
  #define Vec4MulBlockByVec               Vec4MulBlockByVecAsm
  #define Vec4MulBlockByVecUseSize        Vec4MulBlockByVecUseSizeAsm
  #define Vec4BufMulBufByVec              Vec4BufMulBufByVecAsm
  #define Vec4BufMulBufByVecUseSize       Vec4BufMulBufByVecUseSizeAsm
  #define Vec4MulBlockByBlock             Vec4MulBlockByBlockAsm
  #define Vec4MulBlockByBlockUseSize      Vec4MulBlockByBlockUseSizeAsm
  #define Vec4BufMulBufByBlock            Vec4BufMulBufByBlockAsm
  #define Vec4BufMulBufByBuf              Vec4BufMulBufByBufAsm
#endif

extern __C void Vec4MultiplyAsm              (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4MulBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4MulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4MulBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4MulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Divide                      Vec4DivideAsm
  #define Vec4DivBlockByVec               Vec4DivBlockByVecAsm
  #define Vec4DivBlockByVecUseSize        Vec4DivBlockByVecUseSizeAsm
  #define Vec4BufDivBufByVec              Vec4BufDivBufByVecAsm
  #define Vec4BufDivBufByVecUseSize       Vec4BufDivBufByVecUseSizeAsm
  #define Vec4DivBlockByBlock             Vec4DivBlockByBlockAsm
  #define Vec4DivBlockByBlockUseSize      Vec4DivBlockByBlockUseSizeAsm
  #define Vec4BufDivBufByBlock            Vec4BufDivBufByBlockAsm
  #define Vec4BufDivBufByBuf              Vec4BufDivBufByBufAsm
#endif

extern __C void Vec4DivideAsm                (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4DivBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByVecUseSizeAsm  (void* ru,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByVecAsm        (void*  r,const void* u,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Lerp                        Vec4LerpAsm
  #define Vec4LerpBlock                   Vec4LerpBlockAsm
  #define Vec4LerpBlockUseSize            Vec4LerpBlockUseSizeAsm
  #define Vec4BufLerpBlock                Vec4BufLerpBlockAsm
  #define Vec4BufLerpBuf                  Vec4BufLerpBufAsm
#endif

extern __C void Vec4LerpAsm            (vec4*  r,const vec4* u,const vec4* v,const float s);
extern __C void Vec4LerpBlockAsm       (vec4* ru,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4LerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4BufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Dot                         Vec4DotFlatAsm
  #define Vec4DotBlock                    Vec4DotBlockFlatAsm
  #define Vec4DotBlockUseSize             Vec4DotBlockFlatUseSizeAsm
  #define Vec4BufDotBuf                   Vec4BufDotBufFlatAsm
#endif

extern __C void Vec4DotFlatAsm             (float* r,const vec4* u,const vec4* v);
extern __C void Vec4DotBlockFlatAsm        (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4DotBlockFlatUseSizeAsm (float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDotBufFlatAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Sqr                         Vec4SqrAsm
  #define Vec4SqrBlock                    Vec4SqrBlockAsm
  #define Vec4SqrBlockUseSize             Vec4SqrBlockUseSizeAsm
  #define Vec4BufSqrBuf                   Vec4BufSqrBufAsm
#endif

extern __C void Vec4SqrAsm            (vec4*  r,const vec4* v);
extern __C void Vec4SqrBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4SqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Sqrt                        Vec4SqrtAsm
  #define Vec4SqrtBlock                   Vec4SqrtBlockAsm
  #define Vec4SqrtBlockUseSize            Vec4SqrtBlockUseSizeAsm
  #define Vec4BufSqrtBuf                  Vec4BufSqrtBufAsm
#endif

extern __C void Vec4SqrtAsm            (vec4*  r,const vec4* v);
extern __C void Vec4SqrtBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4SqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Normalize                   Vec4NormalizeFlatAsm
  #define Vec4NormalizeBlock              Vec4NormalizeBlockFlatAsm
  #define Vec4NormalizeBlockUseSize       Vec4NormalizeBlockFlatUseSizeAsm
  #define Vec4BufNormalizeBuf             Vec4BufNormalizeBufFlatAsm
#endif

extern __C void Vec4NormalizeFlatAsm            (vec4*  r,const vec4* v);
extern __C void Vec4NormalizeBlockFlatAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4NormalizeBlockFlatUseSizeAsm(vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNormalizeBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Length                      Vec4LengthFlatAsm
  #define Vec4LengthBlock                 Vec4LengthBlockFlatAsm
  #define Vec4LengthBlockUseSize          Vec4LengthBlockFlatUseSizeAsm
  #define Vec4BufLengthBuf                Vec4BufLengthBufFlatAsm
#endif

extern __C void Vec4LengthFlatAsm            (float* r,const vec4* v);
extern __C void Vec4LengthBlockFlatAsm       (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4LengthBlockFlatUseSizeAsm(float* r,const vec4* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLengthBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Cross                       Vec4CrossAsm
  #define Vec4CrossBlock                  Vec4CrossBlockAsm
  #define Vec4CrossBlockUseSize           Vec4CrossBlockUseSizeAsm
  #define Vec4BufCrossBuf                 Vec4BufCrossBufAsm
#endif

extern __C void Vec4CrossAsm            (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4CrossBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4CrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Mat2Negate                      Mat2NegateAsm
  #define Mat2Add                         Mat2AddAsm
  #define Mat2AddFloat                    Mat2AddFloatAsm
  #define Mat2Subtract                    Mat2SubtractAsm
  #define Mat2SubtractFloat               Mat2SubtractFloatAsm
  #define Mat2Multiply                    Mat2MultiplyAsm
  #define Mat2MultiplyVec                 Mat2MultiplyVecAsm
  #define Mat2MultiplyFloat               Mat2MultiplyFloatAsm
  #define Mat2Identity                    Mat2IdentityAsm
  #define Mat2Transpose                   Mat2TransposeAsm
  #define Mat2MultiplyVecBlock            Mat2MultiplyVecBlockAsm
#endif

extern __C void Mat2NegateAsm          (mat2* r,const mat2* m);
extern __C void Mat2AddAsm             (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2AddFloatAsm        (mat2* r,const mat2* m,const float s);
extern __C void Mat2SubtractAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2SubtractFloatAsm   (mat2* r,const mat2* m,const float s);
extern __C void Mat2MultiplyAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2MultiplyVecAsm     (vec2* r,const mat2* m,const vec2* v);
extern __C void Mat2MultiplyFloatAsm   (mat2* r,const mat2* m,const float x);
extern __C void Mat2IdentityAsm        (mat2* r);
extern __C void Mat2TransposeAsm       (mat2* r,const mat2* m);
extern __C void Mat2MultiplyVecBlockAsm(vec2* r,const mat2* m,const vec2* v,int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Mat2RotateLH                    Mat2RotateLHAsm
  #define Mat2RotateRH                    Mat2RotateRHAsm
  #define Mat2Rotate                      Mat2RotateAsm
  #define Mat2Scale                       Mat2ScaleAsm
#endif

extern __C void Mat2RotateLHAsm(mat2* r,const float angle);
extern __C void Mat2RotateRHAsm(mat2* r,const float angle);
extern __C void Mat2RotateAsm  (mat2* r,const float angle);
extern __C void Mat2ScaleAsm   (mat2* r,const float x_scale,const float y_scale);

#if !defined(__REGRESSION_TEST)
  #define Mat3Copy                        Mat3CopyAsm
  #define Mat3Identity                    Mat3IdentityAsm
#endif

extern __C void Mat3CopyAsm    (mat3* r,const mat3* m);
extern __C void Mat3IdentityAsm(mat3* r);

#if !defined(__REGRESSION_TEST)
  #define Mat3Negate                      Mat3NegateAsm
  #define Mat3Add                         Mat3AddAsm
  #define Mat3AddFloat                    Mat3AddFloatAsm
  #define Mat3Subtract                    Mat3SubtractAsm
  #define Mat3SubtractFloat               Mat3SubtractFloatAsm
  #define Mat3Multiply                    Mat3MultiplyAsm
  #define Mat3MultiplyIdentityByBlocks    Mat3MultiplyIdentityByBlocksAsm
  #define Mat3MultiplyVec                 Mat3MultiplyVecAsm
  #define Mat3MultiplyVecBlock            Mat3MultiplyVecBlockAsm
  #define Mat3MulVecBlockBySize           Mat3MulVecBlockBySizeAsm
  #define Mat3MulVec3BufByBuf             Mat3MulVec3BufByBufAsm
  #define Mat3MultiplyFloat               Mat3MultiplyFloatAsm
  #define Mat3Inverse                     Mat3InverseAsm
  #define Mat3Transpose                   Mat3TransposeAsm
#endif

extern __C void Mat3NegateAsm                  (mat3* r,const mat3* m);
extern __C void Mat3AddAsm                     (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3AddFloatAsm                (mat3* r,const mat3* m,const float s);
extern __C void Mat3SubtractAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3SubtractFloatAsm           (mat3* r,const mat3* m,const float s);
extern __C void Mat3MultiplyAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3MultiplyIdentityByBlocksAsm(mat3* r,const mat3* m,int32_t iCount);
extern __C void Mat3MultiplyVecAsm             (vec3* r,const mat3* m,const vec3* v);
extern __C void Mat3MultiplyVecBlocksAsm       (vec3* r,const mat3* m,const vec3* v,int32_t iCount);
extern __C void Mat3MulVecBlockBySizeAsm       (void* r,const mat3* m,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Mat3MulVec3BufByBufAsm         (void* r,const int32_t iRSize,const mat3* m,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Mat3MultiplyFloatAsm           (mat3* r,const mat3* m,const float x);
extern __C void Mat3InverseAsm                 (mat3* r,const mat3* m);
extern __C void Mat3TransposeAsm               (mat3* r,const mat3* m);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHX                   Mat3RotateRHX_Asm
  #define Mat3RotateLHX                   Mat3RotateLHX_Asm
  #define Mat3RotateRHY                   Mat3RotateRHY_Asm
  #define Mat3RotateLHY                   Mat3RotateLHY_Asm
  #define Mat3RotateRHZ                   Mat3RotateRHZ_Asm
  #define Mat3RotateLHZ                   Mat3RotateLHZ_Asm
#endif

extern __C void Mat3RotateRHX_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateLHX_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateRHY_Asm  (mat3* m,const float angle);
extern __C void Mat3RotateLHY_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateRHZ_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateLHZ_Asm  (mat3* r,const float angle);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHXY                  Mat3RotateRHXY_Asm
  #define Mat3RotateLHXY                  Mat3RotateLHXY_Asm
  #define Mat3RotateRHXZ                  Mat3RotateRHXZ_Asm
  #define Mat3RotateLHXZ                  Mat3RotateLHXZ_Asm
  #define Mat3RotateRHYZ                  Mat3RotateRHYZ_Asm
  #define Mat3RotateLHYZ                  Mat3RotateLHYZ_Asm
#endif

extern __C void Mat3RotateRHXY_Asm (mat3* r,const float x,const float y);
extern __C void Mat3RotateLHXY_Asm (mat3* r,const float x,const float y);
extern __C void Mat3RotateRHXZ_Asm (mat3* m,const float x,const float z);
extern __C void Mat3RotateLHXZ_Asm (mat3* m,const float x,const float z);
extern __C void Mat3RotateRHYZ_Asm (mat3* r,const float y,const float z);
extern __C void Mat3RotateLHYZ_Asm (mat3* m,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHXYZ                 Mat3RotateRHXYZ_Asm
  #define Mat3RotateLHXYZ                 Mat3RotateLHXYZ_Asm
#endif

extern __C void Mat3RotateRHXYZ_Asm(mat3* r,const float x,const float y,const float z);
extern __C void Mat3RotateLHXYZ_Asm(mat3* r,const float x,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat3Scale                       Mat3ScaleAsm
  #define Mat3ScaleByVec3                 Mat3ScaleByVec3Asm
#endif

extern __C void Mat3ScaleAsm      (mat3* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat3ScaleByVec3Asm(mat3* r,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Mat4Copy                        Mat4CopyAsm
#endif

extern __C void Mat4CopyAsm(mat4* r,const mat4* m);

#if !defined(__REGRESSION_TEST)
  #define Mat4Negate                      Mat4NegateAsm
  #define Mat4NegateMatrix                Mat4NegateMatrixAsm
  #define Mat4Add                         Mat4AddAsm
  #define Mat4AddFloat                    Mat4AddFloatAsm
  #define Mat4AddMatrix                   Mat4AddMatrixAsm
  #define Mat4Subtract                    Mat4SubtractAsm
  #define Mat4SubtractFloat               Mat4SubtractFloatAsm
  #define Mat4SubtractMatrix              Mat4SubtractMatrixAsm
  #define Mat4MultiplyMatrix              Mat4MultiplyMatrixAsm
  #define Mat4Multiply                    Mat4MultiplyAsm
  #define Mat4MultiplyVec                 Mat4MultiplyVecAsm
  #define Mat4LookAt                      Mat4saLookAtAsm
#endif

extern __C void Mat4NegateAsm        (mat4* r,const mat4* m);
extern __C void Mat4NegateMatrixAsm  (mat4* r);
extern __C void Mat4AddAsm           (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4AddFloatAsm      (mat4* r,const mat4* m,const float s);
extern __C void Mat4AddMatrixAsm     (mat4* m,const mat4* n);
extern __C void Mat4SubtractAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4SubtractFloatAsm (mat4* r,const mat4* m,const float s);
extern __C void Mat4SubtractMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4MultiplyMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4MultiplyAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4MultiplyVecAsm   (vec4* r,const mat4* m,const vec4* v);
extern __C void Mat4saLookAtAsm      (mat4* r,const vec3* from,const vec3* at);

#if !defined(__REGRESSION_TEST)
  #define Mat4MultiplyFloat               Mat4MultiplyFloatAsm
  #define Mat4Transpose                   Mat4TransposeAsm
  #define Mat4ShadowMatrix                Mat4ShadowMatrixAsm
  #define Mat4MirrorMatrix                Mat4MirrorMatrixAsm
  #define Mat4GlToD3DProjMat              Mat4GlToD3DProjMatAsm
  #define Mat4LookAtLH                    Mat4LookAtLHAsm
#endif

extern __C void Mat4MultiplyFloatAsm (mat4* r,const mat4* m,const float x);
extern __C void Mat4TransposeAsm     (mat4* r,const mat4* m);
extern __C void Mat4ShadowMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset,const vec3* lightPos);
extern __C void Mat4MirrorMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset);
extern __C void Mat4LookAtAsm        (mat4* r,const vec3* from,const vec3* at);
extern __C void Mat4GlToD3DProjMatAsm(mat4* r,const mat4* m);
extern __C void Mat4LookAtLHAsm      (mat4* r,const vec3* pEye,const vec3* pLookAt,const vec3* pUp);

#if !defined(__REGRESSION_TEST)
  #define Mat4Identity                    Mat4IdentityAsm
  #define Mat4Scale                       Mat4ScaleAsm
#endif

extern __C void Mat4IdentityAsm(mat4* r);
extern __C void Mat4ScaleAsm   (mat4* r,const float x_scale,const float y_scale,const float z_scale);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHX                   Mat4RotateRHX_Asm
  #define Mat4RotateLHX                   Mat4RotateLHX_Asm
  #define Mat4RotateRHY                   Mat4RotateRHY_Asm
  #define Mat4RotateLHY                   Mat4RotateLHY_Asm
  #define Mat4RotateRHZ                   Mat4RotateRHZ_Asm
  #define Mat4RotateLHZ                   Mat4RotateLHZ_Asm
#endif

extern __C void Mat4RotateRHX_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHX_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateRHY_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHY_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateRHZ_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHZ_Asm  (mat4* r,const float angle);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHXY                  Mat4RotateRHXY_Asm
  #define Mat4RotateLHXY                  Mat4RotateLHXY_Asm
  #define Mat4RotateRHXZ                  Mat4RotateRHXZ_Asm
  #define Mat4RotateLHXZ                  Mat4RotateLHXZ_Asm
  #define Mat4RotateRHYZ                  Mat4RotateRHYZ_Asm
  #define Mat4RotateLHYZ                  Mat4RotateLHYZ_Asm
#endif

extern __C void Mat4RotateRHXY_Asm (mat4* r,const float x_scale,const float y_scale);
extern __C void Mat4RotateLHXY_Asm (mat4* r,const float x,const float y);
extern __C void Mat4RotateRHXZ_Asm (mat4* m,const float x,const float z);
extern __C void Mat4RotateLHXZ_Asm (mat4* m,const float x,const float z);
extern __C void Mat4RotateRHYZ_Asm (mat4* r,const float y,const float z);
extern __C void Mat4RotateLHYZ_Asm (mat4* m,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHXYZ                 Mat4RotateRHXYZ_Asm
  #define Mat4RotateLHXYZ                 Mat4RotateLHXYZ_Asm
#endif

extern __C void Mat4RotateRHXYZ_Asm(mat4* r,const float x,const float y,const float z);
extern __C void Mat4RotateLHXYZ_Asm(mat4* r,const float x,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat4TranslateRH                 Mat4TranslateRH_Asm
  #define Mat4TranslateLH                 Mat4TranslateLH_Asm
  #define Mat4TranslateRH_Vec3            Mat4TranslateRH_Vec3Asm
  #define Mat4TranslateLH_Vec3            Mat4TranslateLH_Vec3Asm
  #define Mat4TranslateRH_Vec4            Mat4TranslateRH_Vec4Asm
  #define Mat4TranslateLH_Vec4            Mat4TranslateLH_Vec4Asm
#endif

extern __C void Mat4TranslateRH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateLH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateRH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateLH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateRH_Vec4Asm (mat4* r,const vec4* v);
extern __C void Mat4TranslateLH_Vec4Asm (mat4* r,const vec4* v);

#if !defined(__REGRESSION_TEST)
  #define Mat4OrthoMatrix                 Mat4OrthoMatrixAsm
  #define Mat4OrthoStruct                 Mat4OrthoStructAsm
  #define Mat4Perspective                 Mat4PerspectiveAsm
  #define Mat4PerspectiveX                Mat4PerspectiveXAsm
  #define Mat4CubemapMatrix               Mat4CubemapMatrixAsm
  #define Mat4CubemapProjectionMat        Mat4CubemapProjectionMatAsm
  //#define Mat4LookAtHoriz                 Mat4LookAtHorizAsm
#endif

extern __C void Mat4OrthoMatrixAsm(mat4*         r,
                                   const float   left,
                                   const float   right,
                                   const float   top,
                                   const float   bottom,
                                   const float   zNear,
                                   const float   zFar,
                                   const int32_t d3dFlag);
extern __C void Mat4OrthoStructAsm(mat4* r,const orthoMatrix* s);

extern __C void Mat4PerspectiveAsm (mat4*          r,
                                    const float    fov,
                                    const float    width,
                                    const float    height,
                                    const float    zNear,
                                    const float    zFar,
                                    const uint32_t d3dflag);
extern __C void Mat4PerspectiveXAsm(mat4* r,const struct perspectiveMatrix* s);

extern __C void Mat4CubemapMatrixAsm(mat4* r,const unsigned int face);
extern __C void Mat4CubemapProjectionMatAsm(mat4* r,const float zNear,const float zFar,const uint32_t d3dflag);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotationFromMat4            Mat3RotationFromMat4Asm
  #define Mat4FromMat3                    Mat4FromMat3Asm
#endif

extern __C void Mat3RotationFromMat4Asm    (mat3* r,const mat4* m);
extern __C void Mat4FromMat3Asm            (mat4* r,const mat3* m);

#if !defined(__REGRESSION_TEST)
  #define QuaternionAdd                   QuaternionAddAsm
  #define QuaternionMultiply              QuaternionMultiplyAsm
  #define QuaternionInverse               QuaternionInverseAsm
  #define QuaternionToMat3                QuaternionToMat3Asm
  #define QuaternionToMat4                QuaternionToMat4Asm
#endif

extern __C void QuaternionAddAsm     (quaternion* r,const quaternion* q,const quaternion* v);
extern __C void QuaternionMultiplyAsm(quaternion*r,const quaternion* u,const quaternion* v);
extern __C void QuaternionInverseAsm (quaternion* r,const quaternion* q);
extern __C void QuaternionToMat3Asm  (mat3* r,const quaternion* q);
extern __C void QuaternionToMat4Asm  (mat4* m,const quaternion* q);

#if !defined(__REGRESSION_TEST)
  #define QuaternionNormalize             QuaternionNormalizeFlatAsm
  #define QuaternionDot                   QuaternionDotFPU_Asm
#endif

extern __C void QuaternionNormalizeFlatAsm (quaternion* r,const quaternion* q);
extern __C void QuaternionDotFPU_Asm       (float* r,const quaternion* q,const quaternion* v);

#if !defined(__REGRESSION_TEST)
  #define QuaternionFromAxis              QuaternionFromAxisAsm
  #define QuaternionFromMat3              QuaternionFromMat3Asm
  #define QuaternionFromMat4              QuaternionFromMat4Asm
  #define QuaternionFromMat3              QuaternionFromMat3Asm
  #define QuaternionFromMat4              QuaternionFromMat4Asm
  #define QuaternionSlerp                 QuaternionSlerpAsm
  #define QuaternionCos                   QuaternionCosAsm
  #define QuaternionSin                   QuaternionSinAsm
#endif

extern __C void QuaternionFromAxisAsm(quaternion* r,const vec3* v,const float angle);
extern __C void QuaternionFromMat3Asm(quaternion* r,const mat3* m);
extern __C void QuaternionFromMat4Asm(quaternion* r,const mat4* m);
extern __C void QuaternionSlerpAsm   (quaternion* r,const float s,const quaternion* q,const quaternion* v);
extern __C void QuaternionCosAsm     (float* r,const quaternion* q,const quaternion* p);
extern __C void QuaternionSinAsm     (float* r,const quaternion* q,const quaternion* p);

#elif defined(__BUILD_UNALIGNED_LIB) || defined(__UNALIGNED_LIB)

/* ----------------- *
 * Unaligned Library *
 * ------------------*---------------------------------------------------- *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#if !defined(__REGRESSION_TEST)
  #define GetFpuStatus                    GetFpuStatusAsm
  #define ClearFpuStatus                  ClearFpuStatusAsm
  #define FloatLerp                       FloatLerpAsm
  #define FloatLerpPtr                    FloatLerpPtrAsm
  #define FloatSqr                        FloatSqrAsm
  #define FloatSqrPtr                     FloatSqrPtrAsm
  #define fCos                            fCosAsm
  #define fSin                            fSinAsm
  #define fTan                            fTanAsm
  #define fACos                           AfCosAsm
  #define fASin                           AfSinAsm
  #define fATan                           AfTanAsm
  #define Cos                             CosAsm
  #define Sin                             SinAsm
  #define Tan                             TanAsm
  #define ACos                            ACosAsm
  #define ASin                            ASinAsm
  #define ATan                            ATanAsm
#endif

extern __C void  GetFpuStatusAsm  (unsigned short* uStatus);
extern __C void  ClearFpuStatusAsm(unsigned short* uStatus);
extern __C float FloatLerpAsm     (const float x,const float v,const float u);
extern __C void  FloatLerpPtrAsm  (float* ret,const float* u,const float* v,const float* x);
extern __C float FloatSqrAsm      (float x);
extern __C float FloatSqrPtrAsm   (float* x);

extern __C float fCosAsm(const float angle);
extern __C float fSinAsm(const float angle);
extern __C float fTanAsm(const float angle);
extern __C float AfCosAsm(const float cosa);
extern __C float AfSinAsm(const float sina);
extern __C float AfTanAsm(const float tana);

extern __C double CosAsm(const double angle);
extern __C double SinAsm(const double angle);
extern __C double TanAsm(const double angle);
extern __C double ACosAsm(const double cosa);
extern __C double ASinAsm(const double sina);
extern __C double ATanAsm(const double tana);

#if !defined(__REGRESSION_TEST)
  #define Vec2Copy                        Vec2CopyAsm
  #define Vec2CopyBlock                   Vec2CopyBlockAsm
  #define BuildVec2PackedArray            BuildVec2PackedArrayAsm
#endif

extern __C void Vec2CopyAsm            (vec2* r,const vec2* v);
extern __C void Vec2CopyBlockAsm       (vec2* r,vec2* v,int32_t iCount);
extern __C void BuildVec2PackedArrayAsm(vec2* r,const vec2** ppList,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddFloat                    Vec2AddFloatFPU_Asm
  #define Vec2SubtractFloat               Vec2SubtractFloatFPU_Asm
  #define Vec2MultiplyFloat               Vec2MultiplyFloatFPU_Asm
  #define Vec2FloatMultiply               Vec2FloatMultiplyFPU_Asm
  #define Vec2DivideFloat                 Vec2DivideFloatFPU_Asm
#endif

extern __C void Vec2AddFloatFPU_Asm     (vec2* r,const vec2* u,const float s);
extern __C void Vec2SubtractFloatFPU_Asm(vec2* r,const vec2* u,const float s);
extern __C void Vec2MultiplyFloatFPU_Asm(vec2* r,const vec2* u,const float s);
extern __C void Vec2FloatMultiplyFPU_Asm(vec2* r,const float s,const vec2* v);
extern __C void Vec2DivideFloatFPU_Asm  (vec2* r,const vec2* u,const float s);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddFloatToBlock             Vec2uAddFloatToBlockAsm
  #define Vec2AddFloatToBlockSize         Vec2AddFloatToBlockSizeFPU_Asm
  #define Vec2BufAddFloatToBlock          Vec2BufAddFloatToBlockFPU_Asm
  #define Vec2BufAddFloatToBuf            Vec2BufAddFloatToBufFPU_Asm
#endif

extern __C void Vec2uAddFloatToBlockAsm(vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2AddFloatToBlockSizeFPU_Asm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBlockFPU_Asm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBufFPU_Asm   (void*  r,const int32_t iRSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2SubtractFloatFromBlock      Vec2uSubtractFloatFromBlockAsm
  #define Vec2SubFloatFromBlockSize       Vec2SubFloatFromBlockSizeFPU_Asm
  #define Vec2BufSubFloatFromBlkSize      Vec2BufSubFloatFromBlkSizeFPU_Asm
  #define Vec2BufSubFloatFromBuf          Vec2BufSubFloatFromBufFPU_Asm
#endif

extern __C void Vec2uSubtractFloatFromBlockAsm(vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2SubFloatFromBlockSizeFPU_Asm  (vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBlkSizeFPU_Asm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBufFPU_Asm     (void*  r,const int32_t iDstSize,const void* u,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2MultiplyBlockByFloat        Vec2uMultiplyBlockByFloatAsm
  #define Vec2MultiplyBlkByFloatSize      Vec2MultiplyBlkByFloatSizeFPU_Asm
  #define Vec2BufMulBlockByFloatSize      Vec2BufMulBlockByFloatSizeFPU_Asm
  #define Vec2BufMulBlockByFloatBuf       Vec2BufMulBlockByFloatBufFPU_Asm
#endif

extern __C void Vec2uMultiplyBlockByFloatAsm     (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2MultiplyBlkByFloatSizeFPU_Asm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatSizeFPU_Asm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatBufFPU_Asm (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2DivideBlockByFloat          Vec2uDivideBlockByFloatAsm
  #define Vec2DivideBlockByFloatSize      Vec2DivideBlockByFloatSizeFPU_Asm
  #define Vec2BufDivBlockByFloatSize      Vec2BufDivBlockByFloatSizeFPU_Asm
  #define Vec2BufDivBufByFloat            Vec2BufDivBufByFloatFPU_Asm
#endif

extern __C void Vec2uDivideBlockByFloatAsm       (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2DivideBlockByFloatSizeFPU_Asm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockByFloatSizeFPU_Asm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufByFloatFPU_Asm      (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2Negate                      Vec2NegateAsm
  #define Vec2Add                         Vec2AddAsm
  #define Vec2Subtract                    Vec2SubtractAsm
  #define Vec2Multiply                    Vec2MultiplyAsm
  #define Vec2Divide                      Vec2DivideAsm
#endif

extern __C void Vec2NegateAsm  (vec2* r,const vec2* u);
extern __C void Vec2AddAsm     (vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2SubtractAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2MultiplyAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2DivideAsm  (vec2* r,const vec2* u,const vec2* v);

#if !defined(__REGRESSION_TEST)
  #define Vec2Equals                      Vec2uEqualsAsm
  #define Vec2NotEquals                   Vec2uNotEqualsAsm
#endif

extern __C void Vec2uEqualsAsm   (int32_t* iFlag,const vec2* u,const vec2* v);
extern __C void Vec2uNotEqualsAsm(int32_t* iFlag,const vec2* u,const vec2* v);

#if !defined(__REGRESSION_TEST)
  #define Vec2NegateBlock                 Vec2uNegateBlockAsm
  #define Vec2NegateBlockBySize           Vec2NegateBlockBySizeAsm
  #define Vec2BufNegateBlockBySize        Vec2BufNegateBlockBySizeAsm
  #define Vec2BufNegateBufBySize          Vec2BufNegateBufBySizeAsm
#endif

extern __C void Vec2uNegateBlockAsm        (vec2* rv,const int32_t iCount);
extern __C void Vec2NegateBlockBySizeAsm   (vec2* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBlockBySizeAsm(vec2*  r,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBufBySizeAsm  (vec2*  r,const int32_t iDstSize,const vec2* v,const int32_t iSrcSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2AddVec2ToBlock              Vec2uAddVec2ToBlockAsm
  #define Vec2AddBlockToBlock             Vec2uAddBlockToBlockAsm
  #define Vec2BufAddVec2ToBlockBySize     Vec2BufAddVec2ToBlockBySizeAsm
  #define Vec2BufAddBlockBySize           Vec2BufAddBlockBySizeAsm
  #define Vec2BufAddBufBySize             Vec2BufAddBufBySizeAsm
#endif

extern __C void Vec2uAddVec2ToBlockAsm        (vec2* rv,const vec2* v,const int32_t iCount);
extern __C void Vec2uAddBlockToBlockAsm       (vec2* rv,const vec2* v,int32_t nCount);
extern __C void Vec2BufAddVec2ToBlockBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2SubtractVec2FromBlock       Vec2uSubtractVec2FromBlockAsm
  #define Vec2SubtractBlockFromBlock      Vec2uSubtractBlockFromBlockAsm
  #define Vec2BufSubVec2FromBlkBySize     Vec2BufSubVec2FromBlkBySizeAsm
  #define Vec2BufSubBlockBySize           Vec2BufSubBlockBySizeAsm
  #define Vec2BufSubBufBySize             Vec2BufSubBufBySizeAsm
#endif

extern __C void Vec2uSubtractVec2FromBlockAsm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2uSubtractBlockFromBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufSubVec2FromBlkBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2MultiplyBlockByVec2         Vec2uMultiplyBlockByVec2Asm
  #define Vec2MultiplyBlockByBlock        Vec2uMultiplyBlockByBlockAsm
  #define Vec2BufMulVec2ByBlockSize       Vec2BufMulVec2ByBlockSizeAsm
  #define Vec2BufMulBlockBySize           Vec2BufMulBlockBySizeAsm
  #define Vec2BufMulBufBySize             Vec2BufMulBufBySizeAsm
#endif

extern __C void Vec2uMultiplyBlockByVec2Asm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2uMultiplyBlockByBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufMulVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2DivideBlockByVec2           Vec2uDivideBlockByVec2Asm
  #define Vec2DivideBlockByBlock          Vec2uDivideBlockByBlockAsm
  #define Vec2BufDivVec2ByBlockSize       Vec2BufDivVec2ByBlockSizeAsm
  #define Vec2BufDivBlockBySize           Vec2BufDivBlockBySizeAsm
  #define Vec2BufDivBufBySize             Vec2BufDivBufBySizeAsm
#endif

extern __C void Vec2uDivideBlockByVec2Asm   (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2uDivideBlockByBlockAsm  (vec2* pDest,const vec2* pSource,const int32_t nCount);
extern __C void Vec2BufDivVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2Lerp                        Vec2LerpAsm
  #define Vec2Sqr                         Vec2SqrAsm
  #define Vec2Sqrt                        Vec2SqrtAsm
  #define Vec2Normalize                   Vec2NormalizeAsm
  #define Vec2Dot                         Vec2DotAsm
  #define Vec2Length                      Vec2LengthAsm
  #define Vec2LengthBlock                 Vec2LengthBlockAsm
#endif

extern __C void Vec2LerpAsm       (vec2*  r,const vec2* u,const vec2* v,const float step);
extern __C void Vec2SqrAsm        (vec2*  r,const vec2* u);
extern __C void Vec2SqrtAsm       (vec2*  r,const vec2* u);
extern __C void Vec2NormalizeAsm  (vec2*  r,const vec2* v);
extern __C void Vec2DotAsm        (float* f,const vec2* u,const vec2* v);
extern __C void Vec2LengthAsm     (float* r,const vec2* v);
extern __C void Vec2LengthBlockAsm(float* r,const vec2* v,const int32_t nCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2LerpBlock                   Vec2uLerpBlockAsm
  #define Vec2SqrBlock                    Vec2uSqrBlockAsm
  #define Vec2SqrtBlock                   Vec2uSqrtBlockAsm
  #define Vec2NormalizeBlock              Vec2uNormalizeBlockAsm
  #define Vec2DotBlock                    Vec2uDotBlockAsm
#endif

extern __C void Vec2uLerpBlockAsm     (vec2*  r,const vec2* u,const vec2* v,const float step,const int32_t iCount);
extern __C void Vec2uSqrBlockAsm      (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2uSqrtBlockAsm     (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2uNormalizeBlockAsm(vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2uDotBlockAsm      (float* r,const vec2* u,const vec2* v,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec2BufLerpBuf                  Vec2BufLerpBufAsm
  #define Vec2BufSqrBuf                   Vec2BufSqrBufAsm
  #define Vec2BufSqrtBuf                  Vec2BufSqrtBufAsm
  #define Vec2BufNormalizeBuf             Vec2BufNormalizeBufAsm
  #define Vec2BufDotBuf                   Vec2BufDotBufAsm
  #define Vec2BufLengthBuf                Vec2BufLengthBufAsm
#endif

extern __C void Vec2BufLerpBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);
extern __C void Vec2BufSqrBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufSqrtBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufNormalizeBufAsm(void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufDotBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Vec2BufLengthBufAsm   (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Copy                        Vec3CopyAsm
  #define Vec3CopyBlock                   Vec3CopyBlockAsm
  #define BuildVec3PackedArray            BuildVec3PackedArrayAsm
#endif

extern __C void Vec3CopyAsm            (vec3* r,const vec3*  u);
extern __C void Vec3CopyBlockAsm       (vec3* r,const vec3*  u,const int32_t iCount);
extern __C void BuildVec3PackedArrayAsm(vec3* r,const vec3** pu,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3AddFloat                    Vec3uAddFloatAsm
  #define Vec3AddFloatToBlock             Vec3uAddFloatToBlockAsm
  #define Vec3AddFloatToBlockBySize       Vec3uAddFloatToBlockBySizeAsm
  #define Vec3BufAddFloatToBlock          Vec3uBufAddFloatToBlockAsm
  #define Vec3BufAddFloatToBuf            Vec3uBufAddFloatToBufAsm
#endif

extern __C void Vec3uAddFloatAsm             (vec3*  r,const vec3* v,const float s);
extern __C void Vec3uAddFloatToBlockAsm      (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uAddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3SubtractFloat               Vec3uSubtractFloatAsm
  #define Vec3SubtractFloatFromBlock      Vec3uSubtractFloatFromBlockAsm
  #define Vec3SubFloatFromBlockBySize     Vec3uSubFloatFromBlockBySizeAsm
  #define Vec3BufSubFloatFromBlock        Vec3uBufSubFloatFromBlockAsm
  #define Vec3BufSubFloatFromBuf          Vec3uBufSubFloatFromBufAsm
#endif

extern __C void Vec3uSubtractFloatAsm          (vec3* r,const vec3* u,const float s);
extern __C void Vec3uSubtractFloatFromBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uSubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3MultiplyFloat               Vec3uMultiplyFloatAsm
  #define Vec3MultiplyFloatToBlock        Vec3uMultiplyFloatToBlockAsm
  #define Vec3MulFloatToBlockBySize       Vec3uMulFloatToBlockBySizeAsm
  #define Vec3BufMulFloatToBlock          Vec3uBufMulFloatToBlockAsm
  #define Vec3BufMulFloatToBuf            Vec3uBufMulFloatToBufAsm
#endif

extern __C void Vec3uMultiplyFloatAsm        (vec3*  r,const vec3* u,const float s);
extern __C void Vec3uMultiplyFloatToBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uMulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3DivideFloat                 Vec3uDivideFloatAsm
  #define Vec3DivideBlockByFloat          Vec3uDivideBlockByFloatAsm
  #define Vec3DivBlockByFloatBySize       Vec3uDivBlockByFloatBySizeAsm
  #define Vec3BufDivBlockByFloat          Vec3uBufDivBlockByFloatAsm
  #define Vec3BufDivBufByFloat            Vec3uBufDivBufByFloatAsm
#endif

extern __C void Vec3uDivideFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3uDivideBlockByFloatAsm   (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uDivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Equals                      Vec3uEqualsAsm
  #define Vec3NotEquals                   Vec3uNotEqualsAsm
#endif

extern __C void Vec3uEqualsAsm   (int32_t* iFlag,const vec3* u,const vec3* v);
extern __C void Vec3uNotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Vec3Negate                      Vec3uNegateAsm
  #define Vec3NegateBlock                 Vec3uNegateBlockAsm
  #define Vec3NegateBlockBySize           Vec3uNegateBlockBySizeAsm
  #define Vec3BufNegateBlock              Vec3uBufNegateBlockAsm
  #define Vec3BufNegateBuf                Vec3uBufNegateBufAsm
#endif

extern __C void Vec3uNegateAsm           (vec3*  r,const vec3* v);
extern __C void Vec3uNegateBlockAsm      (vec3* rv,int32_t iCount);
extern __C void Vec3uNegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Add                         Vec3uAddAsm
  #define Vec3AddVecToBlock               Vec3uAddVecToBlockAsm
  #define Vec3AddVecToBlockBySize         Vec3uAddVecToBlockBySizeAsm
  #define Vec3BufAddVecToBlock            Vec3uBufAddVecToBlockAsm
  #define Vec3BufAddVecToBuf              Vec3uBufAddVecToBufAsm
  #define Vec3AddBlockToBlock             Vec3uAddBlockToBlockAsm
  #define Vec3AddBlockToBlockBySize       Vec3uAddBlockToBlockBySizeAsm
  #define Vec3BufAddBlockToBuf            Vec3uBufAddBlockToBufAsm
  #define Vec3BufAddBufToBuf              Vec3uBufAddBufToBufAsm
#endif

extern __C void Vec3uAddAsm                  (vec3* r,const vec3* u,const vec3* v);
extern __C void Vec3uAddVecToBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uAddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec3uAddBlockToBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uAddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Subtract                    Vec3uSubtractAsm
  #define Vec3SubVecFromBlock             Vec3uSubVecFromBlockAsm
  #define Vec3SubVecFromBlockBySize       Vec3uSubVecFromBlockBySizeAsm
  #define Vec3BufSubVecFromBlock          Vec3uBufSubVecFromBlockAsm
  #define Vec3BufSubVecFromBuf            Vec3uBufSubVecFromBufAsm
  #define Vec3SubBlockFromBlock           Vec3uSubBlockFromBlockAsm
  #define Vec3SubBlockFromBlockBySize     Vec3uSubBlockFromBlockBySizeAsm
  #define Vec3BufSubBlockFromBuf          Vec3uBufSubBlockFromBufAsm
  #define Vec3BufSubBufFromBuf            Vec3uBufSubBufFromBufAsm
#endif

extern __C void Vec3uSubtractAsm               (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uSubVecFromBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubBlockFromBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Multiply                    Vec3uMultiplyAsm
  #define Vec3MulBlockByVec               Vec3uMulBlockByVecAsm
  #define Vec3MulBlockByVecUseSize        Vec3uMulBlockByVecUseSizeAsm
  #define Vec3BufMulBufByVec              Vec3uBufMulBufByVecAsm
  #define Vec3BufMulBufByVecUseSize       Vec3uBufMulBufByVecUseSizeAsm
  #define Vec3MulBlockByBlock             Vec3uMulBlockByBlockAsm
  #define Vec3MulBlockByBlockUseSize      Vec3uMulBlockByBlockUseSizeAsm
  #define Vec3BufMulBufByBlock            Vec3uBufMulBufByBlockAsm
  #define Vec3BufMulBufByBuf              Vec3uBufMulBufByBufAsm
#endif

extern __C void Vec3uMultiplyAsm              (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uMulBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3uMulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uMulBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uMulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Divide                      Vec3uDivideAsm
  #define Vec3DivBlockByVec               Vec3uDivBlockByVecAsm
  #define Vec3DivBlockByVecUseSize        Vec3uDivBlockByVecUseSizeAsm
  #define Vec3BufDivBufByVec              Vec3uBufDivBufByVecAsm
  #define Vec3BufDivBufByVecUseSize       Vec3uBufDivBufByVecUseSizeAsm
  #define Vec3DivBlockByBlock             Vec3uDivBlockByBlockAsm
  #define Vec3DivBlockByBlockUseSize      Vec3uDivBlockByBlockUseSizeAsm
  #define Vec3BufDivBufByBlock            Vec3uBufDivBufByBlockAsm
  #define Vec3BufDivBufByBuf              Vec3uBufDivBufByBufAsm
#endif

extern __C void Vec3uDivideAsm                (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uDivBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByVecUseSizeAsm  (void* ru,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByVecAsm        (void*  r,const void* u,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Lerp                        Vec3uLerpAsm
  #define Vec3LerpBlock                   Vec3uLerpBlockAsm
  #define Vec3LerpBlockUseSize            Vec3uLerpBlockUseSizeAsm
  #define Vec3BufLerpBlock                Vec3uBufLerpBlockAsm
  #define Vec3BufLerpBuf                  Vec3uBufLerpBufAsm
#endif

extern __C void Vec3uLerpAsm            (vec3*  r,const vec3* u,const vec3* v,const float s);
extern __C void Vec3uLerpBlockAsm       (vec3* ru,vec3* v,const float s,const int32_t iCount);
extern __C void Vec3uLerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec3uBufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Dot                         Vec3uDotFlatAsm
  #define Vec3DotBlock                    Vec3uDotBlockAsm
  #define Vec3DotBlockUseSize             Vec3uDotBlockUseSizeAsm
  #define Vec3BufDotBuf                   Vec3uBufDotBufAsm
#endif

extern __C void Vec3uDotFlatAsm(float* r,const vec3* u,const vec3* v);
extern __C void Vec3uDotBlockAsm       (float* r,const vec3* u,const vec3* v,const int32_t iCount);
extern __C void Vec3uDotBlockUseSizeAsm(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDotBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Sqr                         Vec3uSqrAsm
  #define Vec3SqrBlock                    Vec3uSqrBlockAsm
  #define Vec3SqrBlockUseSize             Vec3uSqrBlockUseSizeAsm
  #define Vec3BufSqrBuf                   Vec3uBufSqrBufAsm
#endif

extern __C void Vec3uSqrAsm            (vec3* r,const vec3* v);
extern __C void Vec3uSqrBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3uSqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Sqrt                        Vec3uSqrtAsm
  #define Vec3SqrtBlock                   Vec3uSqrtBlockAsm
  #define Vec3SqrtBlockUseSize            Vec3uSqrtBlockUseSizeAsm
  #define Vec3BufSqrtBuf                  Vec3uBufSqrtBufAsm
#endif

extern __C void Vec3uSqrtAsm            (vec3* r,const vec3* v);
extern __C void Vec3uSqrtBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3uSqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Normalize                   Vec3uNormalizeFlatAsm
  #define Vec3NormalizeBlock              Vec3uNormalizeBlockFlatAsm
  #define Vec3NormalizeBlockUseSize       Vec3uNormalizeBlockFlatUseSizeAsm
  #define Vec3BufNormalizeBuf             Vec3uBufNormalizeBufFlatAsm
#endif

extern __C void Vec3uNormalizeFlatAsm            (vec3*  r,const vec3* v);
extern __C void Vec3uNormalizeBlockFlatAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3uNormalizeBlockFlatUseSizeAsm(vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNormalizeBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Length                      Vec3uLengthFlatAsm
  #define Vec3LengthBlock                 Vec3uLengthBlockFlatAsm
  #define Vec3LengthBlockUseSize          Vec3uLengthBlockFlatUseSizeAsm
  #define Vec3BufLengthBuf                Vec3uBufLengthBufFlatAsm
#endif

extern __C void Vec3uLengthFlatAsm            (float* r,const vec3* v);
extern __C void Vec3uLengthBlockFlatAsm       (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3uLengthBlockFlatUseSizeAsm(float* r,const vec3* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufLengthBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Cross                       Vec3uCrossAsm
  #define Vec3CrossBlock                  Vec3uCrossBlockAsm
  #define Vec3CrossBlockUseSize           Vec3uCrossBlockUseSizeAsm
  #define Vec3BufCrossBuf                 Vec3uBufCrossBufAsm
#endif

extern __C void Vec3uCrossAsm            (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uCrossBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uCrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec3Reflect                     Vec3uReflectAsm
#endif

extern __C void Vec3uReflectAsm(vec3* r,const vec3* u,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Vec4Copy                        Vec4CopyAsm
  #define Vec4CopyBlock                   Vec4CopyBlockAsm
  #define BuildVec4PackedArray            BuildVec4PackedArrayAsm
#endif

extern __C void Vec4CopyAsm            (vec4* r,const vec4*  u);
extern __C void Vec4CopyBlockAsm       (vec4* r,const vec4*  u,const int32_t iCount);
extern __C void BuildVec4PackedArrayAsm(vec4* r,const vec4** pu,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4AddFloat                    Vec4uAddFloatAsm
  #define Vec4AddFloatToBlock             Vec4uAddFloatToBlockAsm
  #define Vec4AddFloatToBlockBySize       Vec4uAddFloatToBlockBySizeAsm
  #define Vec4BufAddFloatToBlock          Vec4uBufAddFloatToBlockAsm
  #define Vec4BufAddFloatToBuf            Vec4uBufAddFloatToBufAsm
#endif

extern __C void Vec4uAddFloatAsm             (vec4* r,const vec4* v,const float s);
extern __C void Vec4uAddFloatToBlockAsm      (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uAddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4SubtractFloat               Vec4uSubtractFloatAsm
  #define Vec4SubtractFloatFromBlock      Vec4uSubtractFloatFromBlockAsm
  #define Vec4SubFloatFromBlockBySize     Vec4uSubFloatFromBlockBySizeAsm
  #define Vec4BufSubFloatFromBlock        Vec4uBufSubFloatFromBlockAsm
  #define Vec4BufSubFloatFromBuf          Vec4uBufSubFloatFromBufAsm
#endif

extern __C void Vec4uSubtractFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uSubtractFloatFromBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uSubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubFloatFromBlockAsm   (void* r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubFloatFromBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4MultiplyFloat               Vec4uMultiplyFloatAsm
  #define Vec4MultiplyFloatToBlock        Vec4uMultiplyFloatToBlockAsm
  #define Vec4MulFloatToBlockBySize       Vec4uMulFloatToBlockBySizeAsm
  #define Vec4BufMulFloatToBlock          Vec4uBufMulFloatToBlockAsm
  #define Vec4BufMulFloatToBuf            Vec4uBufMulFloatToBufAsm
#endif

extern __C void Vec4uMultiplyFloatAsm        (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uMultiplyFloatToBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uMulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4DivideFloat                 Vec4uDivideFloatAsm
  #define Vec4DivideBlockByFloat          Vec4uDivideBlockByFloatAsm
  #define Vec4DivBlockByFloatBySize       Vec4uDivBlockByFloatBySizeAsm
  #define Vec4BufDivBlockByFloat          Vec4uBufDivBlockByFloatAsm
  #define Vec4BufDivBufByFloat            Vec4uBufDivBufByFloatAsm
#endif

extern __C void Vec4uDivideFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uDivideBlockByFloatAsm   (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uDivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBlockByFloatAsm   (void*  r,const void*   u,const float   s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Equals                      Vec4EqualsAsm
  #define Vec4NotEquals                   Vec4NotEqualsAsm
#endif

extern __C void Vec4EqualsAsm   (int32_t* iFlag,const vec4* u,const vec4* v);
extern __C void Vec4NotEqualsAsm(int32_t* iFlag,const vec4* u,const vec4* v);

#if !defined(__REGRESSION_TEST)
  #define Vec4Negate                      Vec4uNegateAsm
  #define Vec4NegateBlock                 Vec4uNegateBlockAsm
  #define Vec4NegateBlockBySize           Vec4uNegateBlockBySizeAsm
  #define Vec4BufNegateBlock              Vec4uBufNegateBlockAsm
  #define Vec4BufNegateBuf                Vec4uBufNegateBufAsm
#endif

extern __C void Vec4uNegateAsm           (vec4*  r,const vec4* v);
extern __C void Vec4uNegateBlockAsm      (vec4* rv,int32_t iCount);
extern __C void Vec4uNegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Add                         Vec4uAddAsm
  #define Vec4AddVecToBlock               Vec4uAddVecToBlockAsm
  #define Vec4AddVecToBlockBySize         Vec4uAddVecToBlockBySizeAsm
  #define Vec4BufAddVecToBlock            Vec4uBufAddVecToBlockAsm
  #define Vec4BufAddVecToBuf              Vec4uBufAddVecToBufAsm
  #define Vec4AddBlockToBlock             Vec4uAddBlockToBlockAsm
  #define Vec4AddBlockToBlockBySize       Vec4uAddBlockToBlockBySizeAsm
  #define Vec4BufAddBlockToBuf            Vec4uBufAddBlockToBufAsm
  #define Vec4BufAddBufToBuf              Vec4uBufAddBufToBufAsm
#endif

extern __C void Vec4uAddAsm                  (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uAddVecToBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uAddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec4uAddBlockToBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uAddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Subtract                    Vec4uSubtractAsm
  #define Vec4SubVecFromBlock             Vec4uSubVecFromBlockAsm
  #define Vec4SubVecFromBlockBySize       Vec4uSubVecFromBlockBySizeAsm
  #define Vec4BufSubVecFromBlock          Vec4uBufSubVecFromBlockAsm
  #define Vec4BufSubVecFromBuf            Vec4uBufSubVecFromBufAsm
  #define Vec4SubBlockFromBlock           Vec4uSubBlockFromBlockAsm
  #define Vec4SubBlockFromBlockBySize     Vec4uSubBlockFromBlockBySizeAsm
  #define Vec4BufSubBlockFromBuf          Vec4uBufSubBlockFromBufAsm
  #define Vec4BufSubBufFromBuf            Vec4uBufSubBufFromBufAsm
#endif

extern __C void Vec4uSubtractAsm               (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uSubVecFromBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uSubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4uSubBlockFromBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uSubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Multiply                    Vec4uMultiplyAsm
  #define Vec4MulBlockByVec               Vec4uMulBlockByVecAsm
  #define Vec4MulBlockByVecUseSize        Vec4uMulBlockByVecUseSizeAsm
  #define Vec4BufMulBufByVec              Vec4uBufMulBufByVecAsm
  #define Vec4BufMulBufByVecUseSize       Vec4uBufMulBufByVecUseSizeAsm
  #define Vec4MulBlockByBlock             Vec4uMulBlockByBlockAsm
  #define Vec4MulBlockByBlockUseSize      Vec4uMulBlockByBlockUseSizeAsm
  #define Vec4BufMulBufByBlock            Vec4uBufMulBufByBlockAsm
  #define Vec4BufMulBufByBuf              Vec4uBufMulBufByBufAsm
#endif

extern __C void Vec4uMultiplyAsm              (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uMulBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4uMulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4uMulBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uMulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Divide                      Vec4uDivideAsm
  #define Vec4DivBlockByVec               Vec4uDivBlockByVecAsm
  #define Vec4DivBlockByVecUseSize        Vec4uDivBlockByVecUseSizeAsm
  #define Vec4BufDivBufByVec              Vec4uBufDivBufByVecAsm
  #define Vec4BufDivBufByVecUseSize       Vec4uBufDivBufByVecUseSizeAsm
  #define Vec4DivBlockByBlock             Vec4uDivBlockByBlockAsm
  #define Vec4DivBlockByBlockUseSize      Vec4uDivBlockByBlockUseSizeAsm
  #define Vec4BufDivBufByBlock            Vec4uBufDivBufByBlockAsm
  #define Vec4BufDivBufByBuf              Vec4uBufDivBufByBufAsm
#endif

extern __C void Vec4uDivideAsm                (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uDivBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uDivBlockByVecUseSizeAsm  (void* ru,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByVecAsm        (void*  r,const void* u,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4uDivBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uDivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Lerp                        Vec4uLerpAsm
  #define Vec4LerpBlock                   Vec4uLerpBlockAsm
  #define Vec4LerpBlockUseSize            Vec4uLerpBlockUseSizeAsm
  #define Vec4BufLerpBlock                Vec4uBufLerpBlockAsm
  #define Vec4BufLerpBuf                  Vec4uBufLerpBufAsm
#endif

extern __C void Vec4uLerpAsm            (vec4*  r,const vec4* u,const vec4* v,const float s);
extern __C void Vec4uLerpBlockAsm       (vec4* ru,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4uLerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4uBufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Dot                         Vec4uDotFlatAsm
  #define Vec4DotBlock                    Vec4uDotBlockFlatAsm
  #define Vec4DotBlockUseSize             Vec4uDotBlockFlatUseSizeAsm
  #define Vec4BufDotBuf                   Vec4uBufDotBufFlatAsm
#endif

extern __C void Vec4uDotFlatAsm            (float* r,const vec4* u,const vec4* v);
extern __C void Vec4uDotBlockFlatAsm       (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4uDotBlockFlatUseSizeAsm(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDotBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Sqr                         Vec4uSqrAsm
  #define Vec4SqrBlock                    Vec4uSqrBlockAsm
  #define Vec4SqrBlockUseSize             Vec4uSqrBlockUseSizeAsm
  #define Vec4BufSqrBuf                   Vec4uBufSqrBufAsm
#endif

extern __C void Vec4uSqrAsm            (vec4*  r,const vec4* v);
extern __C void Vec4uSqrBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4uSqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Sqrt                        Vec4uSqrtAsm
  #define Vec4SqrtBlock                   Vec4uSqrtBlockAsm
  #define Vec4SqrtBlockUseSize            Vec4uSqrtBlockUseSizeAsm
  #define Vec4BufSqrtBuf                  Vec4uBufSqrtBufAsm
#endif

extern __C void Vec4uSqrtAsm            (vec4*  r,const vec4* v);
extern __C void Vec4uSqrtBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4uSqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Normalize                   Vec4uNormalizeFlatAsm
  #define Vec4NormalizeBlock              Vec4uNormalizeBlockFlatAsm
  #define Vec4NormalizeBlockUseSize       Vec4uNormalizeBlockFlatUseSizeAsm
  #define Vec4BufNormalizeBuf             Vec4uBufNormalizeBufFlatAsm
#endif

extern __C void Vec4uNormalizeFlatAsm            (vec4*  r,const vec4* v);
extern __C void Vec4uNormalizeBlockFlatAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4uNormalizeBlockFlatUseSizeAsm(vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNormalizeBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Length                      Vec4uLengthFlatAsm
  #define Vec4LengthBlock                 Vec4uLengthBlockFlatAsm
  #define Vec4LengthBlockUseSize          Vec4uLengthBlockFlatUseSizeAsm
  #define Vec4BufLengthBuf                Vec4uBufLengthBufFlatAsm
#endif

extern __C void Vec4uLengthFlatAsm            (float* r,const vec4* v);
extern __C void Vec4uLengthBlockFlatAsm       (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4uLengthBlockFlatUseSizeAsm(float* r,const vec4* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufLengthBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Vec4Cross                       Vec4uCrossAsm
  #define Vec4CrossBlock                  Vec4uCrossBlockAsm
  #define Vec4CrossBlockUseSize           Vec4uCrossBlockUseSizeAsm
  #define Vec4BufCrossBuf                 Vec4uBufCrossBufAsm
#endif

extern __C void Vec4uCrossAsm            (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uCrossBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uCrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Mat2Negate                      Mat2uNegateAsm
  #define Mat2Add                         Mat2uAddAsm
  #define Mat2AddFloat                    Mat2uAddFloatAsm
  #define Mat2Subtract                    Mat2uSubtractAsm
  #define Mat2SubtractFloat               Mat2uSubtractFloatAsm
  #define Mat2Multiply                    Mat2uMultiplyAsm
  #define Mat2MultiplyVec                 Mat2uMultiplyVecAsm
  #define Mat2MultiplyFloat               Mat2uMultiplyFloatAsm
  #define Mat2Identity                    Mat2uIdentityAsm
  #define Mat2Transpose                   Mat2uTransposeAsm
  #define Mat2MultiplyVecBlock            Mat2uMultiplyVecBlockAsm
#endif

extern __C void Mat2uNegateAsm          (mat2* r,const mat2* m);
extern __C void Mat2uAddAsm             (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uAddFloatAsm        (mat2* r,const mat2* m,const float s);
extern __C void Mat2uSubtractAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uSubtractFloatAsm   (mat2* r,const mat2* m,const float s);
extern __C void Mat2uMultiplyAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uMultiplyVecAsm     (vec2* r,const mat2* m,const vec2* v);
extern __C void Mat2uMultiplyFloatAsm   (mat2* r,const mat2* m,const float x);
extern __C void Mat2uIdentityAsm        (mat2* r);
extern __C void Mat2uTransposeAsm       (mat2* r,const mat2* m);
extern __C void Mat2uMultiplyVecBlockAsm(vec2* r,const mat2* m,const vec2* v,int32_t iCount);

#if !defined(__REGRESSION_TEST)
  #define Mat2RotateLH                    Mat2RotateLHAsm
  #define Mat2RotateRH                    Mat2RotateRHAsm
  #define Mat2Rotate                      Mat2RotateAsm
  #define Mat2Scale                       Mat2ScaleAsm
#endif

extern __C void Mat2RotateLHAsm(mat2* r,const float angle);
extern __C void Mat2RotateRHAsm(mat2* r,const float angle);
extern __C void Mat2RotateAsm  (mat2* r,const float angle);
extern __C void Mat2ScaleAsm   (mat2* r,const float x_scale,const float y_scale);

#if !defined(__REGRESSION_TEST)
  #define Mat3Copy                        Mat3CopyAsm
  #define Mat3Identity                    Mat3IdentityAsm
#endif

extern __C void Mat3CopyAsm    (mat3* r,const mat3* m);
extern __C void Mat3IdentityAsm(mat3* r);

#if !defined(__REGRESSION_TEST)
  #define Mat3Negate                      Mat3uNegateAsm
  #define Mat3Add                         Mat3uAddAsm
  #define Mat3AddFloat                    Mat3uAddFloatAsm
  #define Mat3Subtract                    Mat3uSubtractAsm
  #define Mat3SubtractFloat               Mat3uSubtractFloatAsm
  #define Mat3Multiply                    Mat3uMultiplyAsm
  #define Mat3MultiplyIdentityByBlocks    Mat3uMultiplyIdentityByBlocksAsm
  #define Mat3MultiplyVec                 Mat3uMultiplyVecAsm
  #define Mat3MultiplyVecBlock            Mat3uMultiplyVecBlockAsm
  #define Mat3MulVecBlockBySize           Mat3uMulVecBlockBySizeAsm
  #define Mat3MulVec3BufByBuf             Mat3uMulVec3BufByBufAsm
  #define Mat3MultiplyFloat               Mat3uMultiplyFloatAsm
  #define Mat3Inverse                     Mat3uInverseAsm
  #define Mat3Transpose                   Mat3uTransposeAsm
#endif

extern __C void Mat3uNegateAsm                  (mat3* r,const mat3* m);
extern __C void Mat3uAddAsm                     (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uAddFloatAsm                (mat3* r,const mat3* m,const float n);
extern __C void Mat3uSubtractAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uSubtractFloatAsm           (mat3* r,const mat3* m,const float n);
extern __C void Mat3uMultiplyAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uMultiplyIdentityByBlocksAsm(mat3* r,const mat3* m,int32_t nCount);
extern __C void Mat3uMultiplyVecAsm             (vec3* r,const mat3* m,const vec3* v);
extern __C void Mat3uMultiplyVecBlocksAsm       (vec3* r,const mat3* m,const vec3* v,int32_t iCount);
extern __C void Mat3uMulVecBlockBySizeAsm       (void* r,const mat3* m,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Mat3uMulVec3BufByBufAsm         (void* r,const int32_t iRSize,const mat3* m,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Mat3uMultiplyFloatAsm           (mat3* r,const mat3* m,const float x);
extern __C void Mat3uInverseAsm                 (mat3* r,const mat3* m);
extern __C void Mat3uTransposeAsm               (mat3* r,const mat3* m);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHX                   Mat3RotateRHX_Asm
  #define Mat3RotateLHX                   Mat3RotateLHX_Asm
  #define Mat3RotateRHY                   Mat3RotateRHY_Asm
  #define Mat3RotateLHY                   Mat3RotateLHY_Asm
  #define Mat3RotateRHZ                   Mat3RotateRHZ_Asm
  #define Mat3RotateLHZ                   Mat3RotateLHZ_Asm
#endif

extern __C void Mat3RotateRHX_Asm(mat3* r,const float angle);
extern __C void Mat3RotateLHX_Asm(mat3* r,const float angle);
extern __C void Mat3RotateRHY_Asm(mat3* m,const float angle);
extern __C void Mat3RotateLHY_Asm(mat3* r,const float angle);
extern __C void Mat3RotateRHZ_Asm(mat3* r,const float angle);
extern __C void Mat3RotateLHZ_Asm(mat3* r,const float angle);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHXY                  Mat3RotateRHXY_Asm
  #define Mat3RotateLHXY                  Mat3RotateLHXY_Asm
  #define Mat3RotateRHXZ                  Mat3RotateRHXZ_Asm
  #define Mat3RotateLHXZ                  Mat3RotateLHXZ_Asm
  #define Mat3RotateRHYZ                  Mat3RotateRHYZ_Asm
  #define Mat3RotateLHYZ                  Mat3RotateLHYZ_Asm
#endif

extern __C void Mat3RotateRHXY_Asm(mat3* r,const float x,const float y);
extern __C void Mat3RotateLHXY_Asm(mat3* r,const float x,const float y);
extern __C void Mat3RotateRHXZ_Asm(mat3* m,const float x,const float z);
extern __C void Mat3RotateLHXZ_Asm(mat3* m,const float x,const float z);
extern __C void Mat3RotateRHYZ_Asm(mat3* r,const float y,const float z);
extern __C void Mat3RotateLHYZ_Asm(mat3* m,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotateRHXYZ                 Mat3RotateRHXYZ_Asm
  #define Mat3RotateLHXYZ                 Mat3RotateLHXYZ_Asm
#endif

extern __C void Mat3RotateRHXYZ_Asm(mat3* r,const float x,const float y,const float z);
extern __C void Mat3RotateLHXYZ_Asm(mat3* r,const float x,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat3Scale                       Mat3ScaleAsm
  #define Mat3ScaleByVec3                 Mat3ScaleByVec3Asm
#endif

extern __C void Mat3ScaleAsm      (mat3* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat3ScaleByVec3Asm(mat3* r,const vec3* v);

#if !defined(__REGRESSION_TEST)
  #define Mat4Copy                        Mat4CopyAsm
#endif

extern __C void Mat4CopyAsm(mat4* r,const mat4* m);

#if !defined(__REGRESSION_TEST)
  #define Mat4Negate                      Mat4uNegateAsm
  #define Mat4NegateMatrix                Mat4uNegateMatrixAsm
  #define Mat4Add                         Mat4uAddAsm
  #define Mat4AddFloat                    Mat4uAddFloatAsm
  #define Mat4AddMatrix                   Mat4uAddMatrixAsm
  #define Mat4Subtract                    Mat4uSubtractAsm
  #define Mat4SubtractFloat               Mat4uSubtractFloatAsm
  #define Mat4SubtractMatrix              Mat4uSubtractMatrixAsm
  #define Mat4MultiplyMatrix              Mat4uMultiplyMatrixAsm
  #define Mat4Multiply                    Mat4uMultiplyAsm
  #define Mat4MultiplyVec                 Mat4uMultiplyVecAsm
  #define Mat4LookAt                      Mat4suLookAtAsm
#endif

extern __C void Mat4uNegateAsm        (mat4* r,const mat4* m);
extern __C void Mat4uNegateMatrixAsm  (mat4* r);
extern __C void Mat4uAddAsm           (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uAddFloatAsm      (mat4* r,const mat4* m,const float s);
extern __C void Mat4uAddMatrixAsm     (mat4* m,const mat4* n);
extern __C void Mat4uSubtractAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uSubtractFloatAsm (mat4* r,const mat4* m,const float s);
extern __C void Mat4uSubtractMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4uMultiplyMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4uMultiplyAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uMultiplyVecAsm   (vec4* r,const mat4* m,const vec4* v);
extern __C void Mat4suLookAtAsm       (mat4* r,const vec3* from,const vec3* at);

#if !defined(__REGRESSION_TEST)
  #define Mat4MultiplyFloat               Mat4uMultiplyFloatAsm
  #define Mat4Transpose                   Mat4uTransposeAsm
  #define Mat4ShadowMatrix                Mat4uShadowMatrixAsm
  #define Mat4MirrorMatrix                Mat4uMirrorMatrixAsm
  #define Mat4GlToD3DProjMat              Mat4uGlToD3DProjMatAsm
  #define Mat4LookAtLH                    Mat4uLookAtLHAsm
#endif

extern __C void Mat4uMultiplyFloatAsm (mat4* r,const mat4* m,const float x);
extern __C void Mat4uTransposeAsm     (mat4* r,const mat4* m);
extern __C void Mat4uShadowMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset,const vec3* lightPos);
extern __C void Mat4uMirrorMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset);
extern __C void Mat4uGlToD3DProjMatAsm(mat4* r,const mat4* m);
extern __C void Mat4uLookAtLHAsm      (mat4* r,const vec3* pEye,const vec3* pLookAt,const vec3* pUp);

#if !defined(__REGRESSION_TEST)
  #define Mat4Identity                    Mat4IdentityAsm
  #define Mat4Scale                       Mat4ScaleAsm
#endif

extern __C void Mat4IdentityAsm(mat4* r);
extern __C void Mat4ScaleAsm   (mat4* r,const float x_scale,const float y_scale,const float z_scale);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHX                   Mat4RotateRHX_Asm
  #define Mat4RotateLHX                   Mat4RotateLHX_Asm
  #define Mat4RotateRHY                   Mat4RotateRHY_Asm
  #define Mat4RotateLHY                   Mat4RotateLHY_Asm
  #define Mat4RotateRHZ                   Mat4RotateRHZ_Asm
  #define Mat4RotateLHZ                   Mat4RotateLHZ_Asm
#endif

extern __C void Mat4RotateRHX_Asm(mat4* r,const float angle);
extern __C void Mat4RotateLHX_Asm(mat4* r,const float angle);
extern __C void Mat4RotateRHY_Asm(mat4* r,const float angle);
extern __C void Mat4RotateLHY_Asm(mat4* r,const float angle);
extern __C void Mat4RotateRHZ_Asm(mat4* r,const float angle);
extern __C void Mat4RotateLHZ_Asm(mat4* r,const float angle);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHXY                  Mat4RotateRHXY_Asm
  #define Mat4RotateLHXY                  Mat4RotateLHXY_Asm
  #define Mat4RotateRHXZ                  Mat4RotateRHXZ_Asm
  #define Mat4RotateLHXZ                  Mat4RotateLHXZ_Asm
  #define Mat4RotateRHYZ                  Mat4RotateRHYZ_Asm
  #define Mat4RotateLHYZ                  Mat4RotateLHYZ_Asm
#endif

extern __C void Mat4RotateRHXY_Asm(mat4* r,const float x_scale,const float y_scale);
extern __C void Mat4RotateLHXY_Asm(mat4* r,const float x,const float y);
extern __C void Mat4RotateRHXZ_Asm(mat4* m,const float x,const float z);
extern __C void Mat4RotateLHXZ_Asm(mat4* m,const float x,const float z);
extern __C void Mat4RotateRHYZ_Asm(mat4* r,const float y,const float z);
extern __C void Mat4RotateLHYZ_Asm(mat4* m,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat4RotateRHXYZ                 Mat4RotateRHXYZ_Asm
  #define Mat4RotateLHXYZ                 Mat4RotateLHXYZ_Asm
#endif

extern __C void Mat4RotateRHXYZ_Asm(mat4* r,const float x,const float y,const float z);
extern __C void Mat4RotateLHXYZ_Asm(mat4* r,const float x,const float y,const float z);

#if !defined(__REGRESSION_TEST)
  #define Mat4TranslateRH                 Mat4TranslateRH_Asm
  #define Mat4TranslateLH                 Mat4TranslateLH_Asm
  #define Mat4TranslateRH_Vec3            Mat4TranslateRH_Vec3Asm
  #define Mat4TranslateLH_Vec3            Mat4TranslateLH_Vec3Asm
  #define Mat4TranslateRH_Vec4            Mat4TranslateRH_Vec4Asm
  #define Mat4TranslateLH_Vec4            Mat4TranslateLH_Vec4Asm
#endif

extern __C void Mat4TranslateRH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateLH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateRH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateLH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateRH_Vec4Asm (mat4* r,const vec4* v);
extern __C void Mat4TranslateLH_Vec4Asm (mat4* r,const vec4* v);

#if !defined(__REGRESSION_TEST)
  #define Mat4OrthoMatrix                 Mat4OrthoMatrixAsm
  #define Mat4OrthoStruct                 Mat4OrthoStructAsm
  #define Mat4Perspective                 Mat4PerspectiveAsm
  #define Mat4PerspectiveX                Mat4PerspectiveXAsm
  #define Mat4CubemapMatrix               Mat4CubemapMatrixAsm
  #define Mat4CubemapProjectionMat        Mat4CubemapProjectionMatAsm
  //define Mat4LookAtHoriz                 Mat4LookAtHorizAsm
#endif

extern __C void Mat4OrthoMatrixAsm(mat4*         r,
                                   const float   left,
                                   const float   right,
                                   const float   top,
                                   const float   bottom,
                                   const float   zNear,
                                   const float   zFar,
                                   const int32_t d3dFlag);
extern __C void Mat4OrthoStructAsm(mat4* r,const orthoMatrix* s);

extern __C void Mat4PerspectiveAsm (mat4*          r,
                                    const float    fov,
                                    const float    width,
                                    const float    height,
                                    const float    zNear,
                                    const float    zFar,
                                    const uint32_t d3dflag);
extern __C void Mat4PerspectiveXAsm(mat4* r,const struct perspectiveMatrix* s);

extern __C void Mat4CubemapMatrixAsm(mat4* r,const unsigned int face);
extern __C void Mat4CubemapProjectionMatAsm(mat4* r,const float zNear,const float zFar,const uint32_t d3dflag);

#if !defined(__REGRESSION_TEST)
  #define Mat3RotationFromMat4            Mat3RotationFromMat4Asm
  #define Mat4FromMat3                    Mat4FromMat3Asm
#endif

extern __C void Mat3RotationFromMat4Asm    (mat3* r,const mat4* m);
extern __C void Mat4FromMat3Asm            (mat4* r,const mat3* m);

#if !defined(__REGRESSION_TEST)
  #define QuaternionAdd                   uQuaternionAddAsm
  #define QuaternionMultiply              uQuaternionMultiplyAsm
  #define QuaternionInverse               uQuaternionInverseAsm
  #define QuaternionToMat3                uQuaternionToMat3Asm
  #define QuaternionToMat4                uQuaternionToMat4Asm
#endif

extern __C void uQuaternionAddAsm     (quaternion* r,const quaternion* q,const quaternion* v);
extern __C void uQuaternionMultiplyAsm(quaternion*r,const quaternion* u,const quaternion* v);
extern __C void uQuaternionInverseAsm (quaternion* r,const quaternion* q);
extern __C void uQuaternionToMat3Asm  (mat3* r,const quaternion* q);
extern __C void uQuaternionToMat4Asm  (mat4* m,const quaternion* q);

#if !defined(__REGRESSION_TEST)
  #define QuaternionNormalize             uQuaternionNormalizeFlatAsm
  #define QuaternionDot                   uQuaternionDotFlatAsm
#endif

extern __C void uQuaternionNormalizeFlatAsm(quaternion* r,const quaternion* q);
extern __C void uQuaternionDotFlatAsm      (float* r,const quaternion* q,const quaternion* v);

#if !defined(__REGRESSION_TEST)
  #define QuaternionFromAxis              QuaternionFromAxisAsm
  #define QuaternionFromMat3              QuaternionFromMat3Asm
  #define QuaternionFromMat4              QuaternionFromMat4Asm
  #define QuaternionFromMat3              QuaternionFromMat3Asm
  #define QuaternionFromMat4              QuaternionFromMat4Asm
  #define QuaternionSlerp                 QuaternionSlerpAsm
  #define QuaternionCos                   QuaternionCosAsm
  #define QuaternionSin                   QuaternionSinAsm
#endif

extern __C void QuaternionFromAxisAsm(quaternion* r,const vec3* v,const float angle);
extern __C void QuaternionFromMat3Asm(quaternion* r,const mat3* m);
extern __C void QuaternionFromMat4Asm(quaternion* r,const mat4* m);
extern __C void QuaternionSlerpAsm   (quaternion* r,const float s,const quaternion* q,const quaternion* v);
extern __C void QuaternionCosAsm     (float* r,const quaternion* q,const quaternion* p);
extern __C void QuaternionSinAsm     (float* r,const quaternion* q,const quaternion* p);

#else

/* ------------------- *
 * Full Method Library *
 * --------------------*-------------------------------------------------- *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 * ----------------------------------------------------------------------- */

#define GetFpuStatus                    GetFpuStatusAsm
#define ClearFpuStatus                  ClearFpuStatusAsm
#define FloatLerp                       FloatLerpAsm
#define FloatLerpPtr                    FloatLerpPtrAsm
#define FloatSqr                        FloatSqrAsm
#define FloatSqrPtr                     FloatSqrPtrAsm
#define fCos                            fCosAsm
#define fSin                            fSinAsm
#define fTan                            fTanAsm
#define fACos                           AfCosAsm
#define fASin                           AfSinAsm
#define fATan                           AfTanAsm
#define Cos                             CosAsm
#define Sin                             SinAsm
#define Tan                             TanAsm
#define ACos                            ACosAsm
#define ASin                            ASinAsm
#define ATan                            ATanAsm

extern __C void  GetFpuStatusAsm  (unsigned short* uStatus);
extern __C void  ClearFpuStatusAsm(unsigned short* uStatus);
extern __C float FloatLerpAsm     (const float x,const float v,const float u);
extern __C void  FloatLerpPtrAsm  (float* ret,const float* u,const float* v,const float* x);
extern __C float FloatSqrAsm      (float x);
extern __C float FloatSqrPtrAsm   (float* x);

extern __C float fCosAsm(const float angle);
extern __C float fSinAsm(const float angle);
extern __C float fTanAsm(const float angle);
extern __C float AfCosAsm(const float cosa);
extern __C float AfSinAsm(const float sina);
extern __C float AfTanAsm(const float tana);

extern __C double CosAsm(const double angle);
extern __C double SinAsm(const double angle);
extern __C double TanAsm(const double angle);
extern __C double ACosAsm(const double cosa);
extern __C double ASinAsm(const double sina);
extern __C double ATanAsm(const double tana);

#define Vec2Copy                        Vec2CopyAsm
#define Vec2CopyBlock                   Vec2CopyBlockAsm
#define BuildVec2PackedArray            BuildVec2PackedArrayAsm

extern __C void Vec2CopyAsm            (vec2* r,const vec2* v);
extern __C void Vec2CopyBlockAsm       (vec2* r,vec2* v,int32_t iCount);
extern __C void BuildVec2PackedArrayAsm(vec2* r,const vec2** ppList,const int32_t iCount);

#define Vec2AddFloat                    Vec2AddFloatAsm
#define Vec2SubtractFloat               Vec2SubtractFloatAsm
#define Vec2MultiplyFloat               Vec2MultiplyFloatAsm
#define Vec2FloatMultiply               Vec2FloatMultiplyAsm
#define Vec2DivideFloat                 Vec2DivideFloatAsm

extern __C void Vec2AddFloatAsm     (vec2* r,const vec2* u,const float s);
extern __C void Vec2SubtractFloatAsm(vec2* r,const vec2* u,const float s);
extern __C void Vec2MultiplyFloatAsm(vec2* r,const vec2* u,const float s);
extern __C void Vec2FloatMultiplyAsm(vec2* r,const float s,const vec2* v);
extern __C void Vec2DivideFloatAsm  (vec2* r,const vec2* u,const float s);

#define Vec2AddFloatFPU                 Vec2AddFloatFPU_Asm
#define Vec2SubtractFloatFPU            Vec2SubtractFloatFPU_Asm
#define Vec2MultiplyFloatFPU            Vec2MultiplyFloatFPU_Asm
#define Vec2FloatMultiplyFPU            Vec2FloatMultiplyFPU_Asm
#define Vec2DivideFloatFPU              Vec2DivideFloatFPU_Asm

extern __C void Vec2AddFloatFPU_Asm     (vec2* r,const vec2* u,const float s);
extern __C void Vec2SubtractFloatFPU_Asm(vec2* r,const vec2* u,const float s);
extern __C void Vec2MultiplyFloatFPU_Asm(vec2* r,const vec2* u,const float s);
extern __C void Vec2FloatMultiplyFPU_Asm(vec2* r,const float s,const vec2* v);
extern __C void Vec2DivideFloatFPU_Asm  (vec2* r,const vec2* u,const float s);

#define Vec2AddFloatToBlock             Vec2AddFloatToBlockAsm
#define Vec2uAddFloatToBlock            Vec2uAddFloatToBlockAsm

extern __C void Vec2AddFloatToBlockAsm (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2uAddFloatToBlockAsm(vec2* rv,const float s,const int32_t iCount);

#define Vec2AddFloatToBlockSize         Vec2AddFloatToBlockSizeAsm
#define Vec2BufAddFloatToBlock          Vec2BufAddFloatToBlockAsm
#define Vec2BufAddFloatToBuf            Vec2BufAddFloatToBufAsm

extern __C void Vec2AddFloatToBlockSizeAsm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBlockAsm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBufAsm   (void*  r,const int32_t iRSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#define Vec2AddFloatToBlockFPU          Vec2AddFloatToBlockFPU_Asm
#define Vec2AddFloatToBlockSizeFPU      Vec2AddFloatToBlockSizeFPU_Asm
#define Vec2BufAddFloatToBlockFPU       Vec2BufAddFloatToBlockFPU_Asm
#define Vec2BufAddFloatToBufFPU         Vec2BufAddFloatToBufFPU_Asm

extern __C void Vec2AddFloatToBlockFPU_Asm    (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2AddFloatToBlockSizeFPU_Asm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBlockFPU_Asm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddFloatToBufFPU_Asm   (void*  r,const int32_t iRSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#define Vec2SubtractFloatFromBlock      Vec2SubtractFloatFromBlockAsm
#define Vec2uSubtractFloatFromBlock     Vec2uSubtractFloatFromBlockAsm

extern __C void Vec2SubtractFloatFromBlockAsm (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2uSubtractFloatFromBlockAsm(vec2* rv,const float s,const int32_t iCount);

#define Vec2SubFloatFromBlockSize       Vec2SubFloatFromBlockSizeAsm
#define Vec2BufSubFloatFromBlkSize      Vec2BufSubFloatFromBlkSizeAsm
#define Vec2BufSubFloatFromBuf          Vec2BufSubFloatFromBufAsm

extern __C void Vec2SubFloatFromBlockSizeAsm (vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBlkSizeAsm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBufAsm    (void*  r,const int32_t iDstSize,const void* pSource,const int32_t iSrcSize,const float s,const int32_t iCount);

#define Vec2SubtractFloatFromBlockFPU   Vec2SubtractFloatFromBlockFPU_Asm
#define Vec2SubFloatFromBlockSizeFPU    Vec2SubFloatFromBlockSizeFPU_Asm
#define Vec2BufSubFloatFromBlkSizeFPU   Vec2BufSubFloatFromBlkSizeFPU_Asm
#define Vec2BufSubFloatFromBufFPU       Vec2BufSubFloatFromBufFPU_Asm

extern __C void Vec2uSubtractFloatFromBlockFPU_Asm(vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2SubFloatFromBlockSizeFPU_Asm  (vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBlkSizeFPU_Asm (void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubFloatFromBufFPU_Asm     (void*  r,const int32_t iDstSize,const void* u,const int32_t iSrcSize,const float s,const int32_t iCount);

#define Vec2MultiplyBlockByFloat        Vec2MultiplyBlockByFloatAsm
#define Vec2uMultiplyBlockByFloat       Vec2uMultiplyBlockByFloatAsm

extern __C void Vec2MultiplyBlockByFloatAsm (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2uMultiplyBlockByFloatAsm(vec2* rv,const float s,const int32_t iCount);

#define Vec2MultiplyBlkByFloatSize      Vec2MultiplyBlkByFloatSizeAsm
#define Vec2BufMulBlockByFloatSize      Vec2BufMulBlockByFloatSizeAsm
#define Vec2BufMulBlockByFloatBuf       Vec2BufMulBlockByFloatBufAsm

extern __C void Vec2MultiplyBlkByFloatSizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatSizeAsm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatBufAsm (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#define Vec2MultiplyBlockByFloatFPU     Vec2MultiplyBlockByFloatFPU_Asm
#define Vec2MultiplyBlkByFloatSizeFPU   Vec2MultiplyBlkByFloatSizeFPU_Asm
#define Vec2BufMulBlockByFloatSizeFPU   Vec2BufMulBlockByFloatSizeFPU_Asm
#define Vec2BufMulBlockByFloatBufFPU    Vec2BufMulBlockByFloatBufFPU_Asm

extern __C void Vec2MultiplyBlockByFloatFPU_Asm  (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2MultiplyBlkByFloatSizeFPU_Asm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatSizeFPU_Asm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockByFloatBufFPU_Asm (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#define Vec2DivideBlockByFloat          Vec2DivideBlockByFloatAsm
#define Vec2uDivideBlockByFloat         Vec2uDivideBlockByFloatAsm

extern __C void Vec2DivideBlockByFloatAsm (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2uDivideBlockByFloatAsm(vec2* rv,const float s,const int32_t iCount);

#define Vec2DivideBlockByFloatSize      Vec2DivideBlockByFloatSizeAsm
#define Vec2BufDivBlockByFloatSize      Vec2BufDivBlockByFloatSizeAsm
#define Vec2BufDivBufByFloat            Vec2BufDivBufByFloatAsm

extern __C void Vec2DivideBlockByFloatSizeAsm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockByFloatSizeAsm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufByFloatAsm      (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#define Vec2DivideBlockByFloatFPU       Vec2DivideBlockByFloatFPU_Asm
#define Vec2DivideBlockByFloatSizeFPU   Vec2DivideBlockByFloatSizeFPU_Asm
#define Vec2BufDivBlockByFloatSizeFPU   Vec2BufDivBlockByFloatSizeFPU_Asm
#define Vec2BufDivBufByFloatFPU         Vec2BufDivBufByFloatFPU_Asm

extern __C void Vec2DivideBlockByFloatFPU_Asm    (vec2* rv,const float s,const int32_t iCount);
extern __C void Vec2DivideBlockByFloatSizeFPU_Asm(vec2* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockByFloatSizeFPU_Asm(void*  r,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufByFloatFPU_Asm      (void*  r,const int32_t iDstSize,const void* v,const int32_t iSrcSize,const float s,const int32_t iCount);

#define Vec2Negate                      Vec2NegateAsm
#define Vec2Add                         Vec2AddAsm
#define Vec2Subtract                    Vec2SubtractAsm
#define Vec2Multiply                    Vec2MultiplyAsm
#define Vec2Divide                      Vec2DivideAsm

extern __C void Vec2NegateAsm  (vec2* r,const vec2* u);
extern __C void Vec2AddAsm     (vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2SubtractAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2MultiplyAsm(vec2* r,const vec2* u,const vec2* v);
extern __C void Vec2DivideAsm  (vec2* r,const vec2* u,const vec2* v);

#define Vec2Equals                      Vec2EqualsAsm
#define Vec2NotEquals                   Vec2NotEqualsAsm

extern __C void Vec2EqualsAsm   (int32_t* iFlag,const vec2* u,const vec2* v);
extern __C void Vec2NotEqualsAsm(int32_t* iFlag,const vec2* u,const vec2* v);

#define Vec2uEquals                     Vec2uEqualsAsm
#define Vec2uNotEquals                  Vec2uNotEqualsAsm

extern __C void Vec2uEqualsAsm   (int32_t* iFlag,const vec2* u,const vec2* v);
extern __C void Vec2uNotEqualsAsm(int32_t* iFlag,const vec2* u,const vec2* v);

#define Vec2NegateBlock                 Vec2NegateBlockAsm
#define Vec2uNegateBlock                Vec2uNegateBlockAsm

extern __C void Vec2NegateBlockAsm (vec2* rv,const int32_t iCount);
extern __C void Vec2uNegateBlockAsm(vec2* rv,const int32_t iCount);

#define Vec2NegateBlockBySize           Vec2NegateBlockBySizeAsm
#define Vec2BufNegateBlockBySize        Vec2BufNegateBlockBySizeAsm
#define Vec2BufNegateBufBySize          Vec2BufNegateBufBySizeAsm

extern __C void Vec2NegateBlockBySizeAsm   (vec2* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBlockBySizeAsm(vec2*  r,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufNegateBufBySizeAsm  (vec2*  r,const int32_t iDstSize,const vec2* v,const int32_t iSrcSize,const int32_t iCount);

#define Vec2AddVec2ToBlock              Vec2AddVec2ToBlockAsm
#define Vec2uAddVec2ToBlock             Vec2uAddVec2ToBlockAsm

extern __C void Vec2AddVec2ToBlockAsm (vec2* rv,const vec2* v,const int32_t iCount);
extern __C void Vec2uAddVec2ToBlockAsm(vec2* rv,const vec2* v,const int32_t iCount);

#define Vec2AddBlockToBlock             Vec2AddBlockToBlockAsm
#define Vec2uAddBlockToBlock            Vec2uAddBlockToBlockAsm

extern __C void Vec2AddBlockToBlockAsm (vec2* rv,const vec2* v,int32_t iCount);
extern __C void Vec2uAddBlockToBlockAsm(vec2* rv,const vec2* v,int32_t nCount);

#define Vec2BufAddVec2ToBlockBySize     Vec2BufAddVec2ToBlockBySizeAsm
#define Vec2BufAddBlockBySize           Vec2BufAddBlockBySizeAsm
#define Vec2BufAddBufBySize             Vec2BufAddBufBySizeAsm

extern __C void Vec2BufAddVec2ToBlockBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufAddBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#define Vec2SubtractVec2FromBlock       Vec2SubtractVec2FromBlockAsm
#define Vec2SubtractBlockFromBlock      Vec2SubtractBlockFromBlockAsm

extern __C void Vec2SubtractVec2FromBlockAsm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2SubtractBlockFromBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);

#define Vec2uSubtractVec2FromBlock      Vec2uSubtractVec2FromBlockAsm
#define Vec2uSubtractBlockFromBlock     Vec2uSubtractBlockFromBlockAsm

extern __C void Vec2uSubtractVec2FromBlockAsm (vec2* pDest,const vec2* pVector,int32_t nCount);
extern __C void Vec2uSubtractBlockFromBlockAsm(vec2* pDest,const vec2* pSource,int32_t nCount);

#define Vec2BufSubVec2FromBlkBySize     Vec2BufSubVec2FromBlkBySizeAsm
#define Vec2BufSubBlockBySize           Vec2BufSubBlockBySizeAsm
#define Vec2BufSubBufBySize             Vec2BufSubBufBySizeAsm

extern __C void Vec2BufSubVec2FromBlkBySizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBlockBySizeAsm      (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufSubBufBySizeAsm        (vec2* r,const int32_t iSaveSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#define Vec2MultiplyBlockByVec2         Vec2MultiplyBlockByVec2Asm
#define Vec2MultiplyBlockByBlock        Vec2MultiplyBlockByBlockAsm

extern __C void Vec2MultiplyBlockByVec2Asm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2MultiplyBlockByBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);

#define Vec2uMultiplyBlockByVec2        Vec2uMultiplyBlockByVec2Asm
#define Vec2uMultiplyBlockByBlock       Vec2uMultiplyBlockByBlockAsm

extern __C void Vec2uMultiplyBlockByVec2Asm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2uMultiplyBlockByBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);

#define Vec2BufMulVec2ByBlockSize       Vec2BufMulVec2ByBlockSizeAsm
#define Vec2BufMulBlockBySize           Vec2BufMulBlockBySizeAsm
#define Vec2BufMulBufBySize             Vec2BufMulBufBySizeAsm

extern __C void Vec2BufMulVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufMulBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#define Vec2DivideBlockByVec2           Vec2DivideBlockByVec2Asm
#define Vec2DivideBlockByBlock          Vec2DivideBlockByBlockAsm

extern __C void Vec2DivideBlockByVec2Asm (vec2* pDest,const vec2* pVector,const int32_t nCount);
extern __C void Vec2DivideBlockByBlockAsm(vec2* pDest,const vec2* pSource,const int32_t nCount);

#define Vec2uDivideBlockByVec2          Vec2uDivideBlockByVec2Asm
#define Vec2uDivideBlockByBlock         Vec2uDivideBlockByBlockAsm

extern __C void Vec2uDivideBlockByVec2Asm (vec2* pDest,vec2* pVector,int32_t nCount);
extern __C void Vec2uDivideBlockByBlockAsm(vec2* pDest,vec2* pSource,int32_t nCount);

#define Vec2BufDivVec2ByBlockSize       Vec2BufDivVec2ByBlockSizeAsm
#define Vec2BufDivBlockBySize           Vec2BufDivBlockBySizeAsm
#define Vec2BufDivBufBySize             Vec2BufDivBufBySizeAsm

extern __C void Vec2BufDivVec2ByBlockSizeAsm(vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBlockBySizeAsm    (vec2* r,const vec2* u,const vec2* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec2BufDivBufBySizeAsm      (vec2* r,const int32_t iDstSize,const vec2* u,const int32_t iSrcSize0,const vec2* v,const int32_t iSrcSize1,const int32_t iCount);

#define Vec2LerpBlock                   Vec2LerpBlockAsm
#define Vec2SqrBlock                    Vec2SqrBlockAsm
#define Vec2SqrtBlock                   Vec2SqrtBlockAsm
#define Vec2NormalizeBlock              Vec2NormalizeBlockAsm
#define Vec2DotBlock                    Vec2DotBlockAsm

extern __C void Vec2LerpBlockAsm     (vec2*  r,const vec2* u,const vec2* v,const float step,const int32_t iCount);
extern __C void Vec2SqrBlockAsm      (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2SqrtBlockAsm     (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2NormalizeBlockAsm(vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2DotBlockAsm      (float* r,const vec2* u,const vec2* v,const int32_t iCount);

#define Vec2uLerpBlock                  Vec2uLerpBlockAsm
#define Vec2uSqrBlock                   Vec2uSqrBlockAsm
#define Vec2uSqrtBlock                  Vec2uSqrtBlockAsm
#define Vec2uNormalizeBlock             Vec2uNormalizeBlockAsm
#define Vec2uDotBlock                   Vec2uDotBlockAsm

extern __C void Vec2uLerpBlockAsm     (vec2*  r,const vec2* u,const vec2* v,const float step,const int32_t iCount);
extern __C void Vec2uSqrBlockAsm      (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2uSqrtBlockAsm     (vec2*  r,const vec2* u,const int32_t iCount);
extern __C void Vec2uNormalizeBlockAsm(vec2*  r,const vec2* u,const vec2* v,const int32_t iCount);
extern __C void Vec2uDotBlockAsm      (float* r,const vec2* u,const vec2* v,const int32_t iCount);

#define Vec2Lerp                        Vec2LerpAsm
#define Vec2Sqr                         Vec2SqrAsm
#define Vec2Sqrt                        Vec2SqrtAsm
#define Vec2Normalize                   Vec2NormalizeAsm
#define Vec2Dot                         Vec2DotAsm
#define Vec2Length                      Vec2LengthAsm
#define Vec2LengthBlock                 Vec2LengthBlockAsm

extern __C void Vec2LerpAsm       (vec2*  r,const vec2* u,const vec2* v,const float step);
extern __C void Vec2SqrAsm        (vec2*  r,const vec2* u);
extern __C void Vec2SqrtAsm       (vec2*  r,const vec2* u);
extern __C void Vec2NormalizeAsm  (vec2*  r,const vec2* v);
extern __C void Vec2DotAsm        (float* f,const vec2* u,const vec2* v);
extern __C void Vec2LengthAsm     (float* r,const vec2* v);
extern __C void Vec2LengthBlockAsm(float* r,const vec2* v,const int32_t nCount);

#define Vec2BufLerpBuf                  Vec2BufLerpBufAsm
#define Vec2BufSqrBuf                   Vec2BufSqrBufAsm
#define Vec2BufSqrtBuf                  Vec2BufSqrtBufAsm
#define Vec2BufNormalizeBuf             Vec2BufNormalizeBufAsm
#define Vec2BufDotBuf                   Vec2BufDotBufAsm
#define Vec2BufLengthBuf                Vec2BufLengthBufAsm

extern __C void Vec2BufLerpBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);
extern __C void Vec2BufSqrBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufSqrtBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufNormalizeBufAsm(void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);
extern __C void Vec2BufDotBufAsm      (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Vec2BufLengthBufAsm   (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3Copy                        Vec3CopyAsm
#define Vec3CopyBlock                   Vec3CopyBlockAsm
#define BuildVec3PackedArray            BuildVec3PackedArrayAsm

extern __C void Vec3CopyAsm            (vec3* r,const vec3*  u);
extern __C void Vec3CopyBlockAsm       (vec3* r,const vec3*  u,const int32_t iCount);
extern __C void BuildVec3PackedArrayAsm(vec3* r,const vec3** pu,const int32_t iCount);

#define Vec3AddFloat                    Vec3AddFloatAsm
#define Vec3AddFloatToBlock             Vec3AddFloatToBlockAsm
#define Vec3AddFloatToBlockBySize       Vec3AddFloatToBlockBySizeAsm
#define Vec3BufAddFloatToBlock          Vec3BufAddFloatToBlockAsm
#define Vec3BufAddFloatToBuf            Vec3BufAddFloatToBufAsm

extern __C void Vec3AddFloatAsm             (vec3*  r,const vec3* v,const float s);
extern __C void Vec3AddFloatToBlockAsm      (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3AddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec3uAddFloat                   Vec3uAddFloatAsm
#define Vec3uAddFloatToBlock            Vec3uAddFloatToBlockAsm
#define Vec3uAddFloatToBlockBySize      Vec3uAddFloatToBlockBySizeAsm
#define Vec3uBufAddFloatToBlock         Vec3uBufAddFloatToBlockAsm
#define Vec3uBufAddFloatToBuf           Vec3uBufAddFloatToBufAsm

extern __C void Vec3uAddFloatAsm             (vec3*  r,const vec3* v,const float s);
extern __C void Vec3uAddFloatToBlockAsm      (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uAddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec3SubtractFloat               Vec3SubtractFloatAsm
#define Vec3SubtractFloatFromBlock      Vec3SubtractFloatFromBlockAsm
#define Vec3SubFloatFromBlockBySize     Vec3SubFloatFromBlockBySizeAsm
#define Vec3BufSubFloatFromBlock        Vec3BufSubFloatFromBlockAsm
#define Vec3BufSubFloatFromBuf          Vec3BufSubFloatFromBufAsm

extern __C void Vec3SubtractFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3SubtractFloatFromBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3SubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec3uSubtractFloat              Vec3uSubtractFloatAsm
#define Vec3uSubtractFloatFromBlock     Vec3uSubtractFloatFromBlockAsm
#define Vec3uSubFloatFromBlockBySize    Vec3uSubFloatFromBlockBySizeAsm
#define Vec3uBufSubFloatFromBlock       Vec3uBufSubFloatFromBlockAsm
#define Vec3uBufSubFloatFromBuf         Vec3uBufSubFloatFromBufAsm

extern __C void Vec3uSubtractFloatAsm          (vec3* r,const vec3* u,const float s);
extern __C void Vec3uSubtractFloatFromBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uSubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec3MultiplyFloat               Vec3MultiplyFloatAsm
#define Vec3MultiplyFloatToBlock        Vec3MultiplyFloatToBlockAsm
#define Vec3MulFloatToBlockBySize       Vec3MulFloatToBlockBySizeAsm
#define Vec3BufMulFloatToBlock          Vec3BufMulFloatToBlockAsm
#define Vec3BufMulFloatToBuf            Vec3BufMulFloatToBufAsm

extern __C void Vec3MultiplyFloatAsm        (vec3*  r,const vec3* u,const float s);
extern __C void Vec3MultiplyFloatToBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3MulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec3uMultiplyFloat              Vec3uMultiplyFloatAsm
#define Vec3uMultiplyFloatToBlock       Vec3uMultiplyFloatToBlockAsm
#define Vec3uMulFloatToBlockBySize      Vec3uMulFloatToBlockBySizeAsm
#define Vec3uBufMulFloatToBlock         Vec3uBufMulFloatToBlockAsm
#define Vec3uBufMulFloatToBuf           Vec3uBufMulFloatToBufAsm

extern __C void Vec3uMultiplyFloatAsm        (vec3*  r,const vec3* u,const float s);
extern __C void Vec3uMultiplyFloatToBlockAsm (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uMulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec3DivideFloat                 Vec3DivideFloatAsm
#define Vec3DivideBlockByFloat          Vec3DivideBlockByFloatAsm
#define Vec3DivBlockByFloatBySize       Vec3DivBlockByFloatBySizeAsm
#define Vec3BufDivBlockByFloat          Vec3BufDivBlockByFloatAsm
#define Vec3BufDivBufByFloat            Vec3BufDivBufByFloatAsm

extern __C void Vec3DivideFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3DivideBlockByFloatAsm   (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3DivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec3uDivideFloat                Vec3uDivideFloatAsm
#define Vec3uDivideBlockByFloat         Vec3uDivideBlockByFloatAsm
#define Vec3uDivBlockByFloatBySize      Vec3uDivBlockByFloatBySizeAsm
#define Vec3uBufDivBlockByFloat         Vec3uBufDivBlockByFloatAsm
#define Vec3uBufDivBufByFloat           Vec3uBufDivBufByFloatAsm

extern __C void Vec3uDivideFloatAsm          (vec3*  r,const vec3* u,const float s);
extern __C void Vec3uDivideBlockByFloatAsm   (vec3* rv,const float s,const int32_t iCount);
extern __C void Vec3uDivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec3Equals                      Vec3EqualsAsm
#define Vec3NotEquals                   Vec3NotEqualsAsm

extern __C void Vec3EqualsAsm   (int32_t* iFlag,const vec3* u,const vec3* v);
extern __C void Vec3NotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);

#define Vec3uEquals                     Vec3uEqualsAsm
#define Vec3uNotEquals                  Vec3uNotEqualsAsm

extern __C void Vec3uEqualsAsm   (int32_t* iFlag,const vec3* u,const vec3* v);
extern __C void Vec3uNotEqualsAsm(int32_t* iFlag,const vec3* u,const vec3* v);

#define Vec3Negate                      Vec3NegateAsm
#define Vec3NegateBlock                 Vec3NegateBlockAsm
#define Vec3NegateBlockBySize           Vec3NegateBlockBySizeAsm
#define Vec3BufNegateBlock              Vec3BufNegateBlockAsm
#define Vec3BufNegateBuf                Vec3BufNegateBufAsm

extern __C void Vec3NegateAsm           (vec3*  r,const vec3* v);
extern __C void Vec3NegateBlockAsm      (vec3* rv,int32_t iCount);
extern __C void Vec3NegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3uNegate                     Vec3uNegateAsm
#define Vec3uNegateBlock                Vec3uNegateBlockAsm
#define Vec3uNegateBlockBySize          Vec3uNegateBlockBySizeAsm
#define Vec3uBufNegateBlock             Vec3uBufNegateBlockAsm
#define Vec3uBufNegateBuf               Vec3uBufNegateBufAsm

extern __C void Vec3uNegateAsm           (vec3*  r,const vec3* v);
extern __C void Vec3uNegateBlockAsm      (vec3* rv,int32_t iCount);
extern __C void Vec3uNegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3Add                         Vec3AddAsm
#define Vec3AddVecToBlock               Vec3AddVecToBlockAsm
#define Vec3AddVecToBlockBySize         Vec3AddVecToBlockBySizeAsm
#define Vec3BufAddVecToBlock            Vec3BufAddVecToBlockAsm
#define Vec3BufAddVecToBuf              Vec3BufAddVecToBufAsm
#define Vec3AddBlockToBlock             Vec3AddBlockToBlockAsm
#define Vec3AddBlockToBlockBySize       Vec3AddBlockToBlockBySizeAsm
#define Vec3BufAddBlockToBuf            Vec3BufAddBlockToBufAsm
#define Vec3BufAddBufToBuf              Vec3BufAddBufToBufAsm

extern __C void Vec3AddAsm                  (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3AddVecToBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3AddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec3AddBlockToBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3AddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3uAdd                        Vec3uAddAsm
#define Vec3uAddVecToBlock              Vec3uAddVecToBlockAsm
#define Vec3uAddVecToBlockBySize        Vec3uAddVecToBlockBySizeAsm
#define Vec3uBufAddVecToBlock           Vec3uBufAddVecToBlockAsm
#define Vec3uBufAddVecToBuf             Vec3uBufAddVecToBufAsm
#define Vec3uAddBlockToBlock            Vec3uAddBlockToBlockAsm
#define Vec3uAddBlockToBlockBySize      Vec3uAddBlockToBlockBySizeAsm
#define Vec3uBufAddBlockToBuf           Vec3uBufAddBlockToBufAsm
#define Vec3uBufAddBufToBuf             Vec3uBufAddBufToBufAsm

extern __C void Vec3uAddAsm                  (vec3* r,const vec3* u,const vec3* v);
extern __C void Vec3uAddVecToBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uAddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec3uAddBlockToBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uAddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3Subtract                    Vec3SubtractAsm
#define Vec3SubVecFromBlock             Vec3SubVecFromBlockAsm
#define Vec3SubVecFromBlockBySize       Vec3SubVecFromBlockBySizeAsm
#define Vec3BufSubVecFromBlock          Vec3BufSubVecFromBlockAsm
#define Vec3BufSubVecFromBuf            Vec3BufSubVecFromBufAsm
#define Vec3SubBlockFromBlock           Vec3SubBlockFromBlockAsm
#define Vec3SubBlockFromBlockBySize     Vec3SubBlockFromBlockBySizeAsm
#define Vec3BufSubBlockFromBuf          Vec3BufSubBlockFromBufAsm
#define Vec3BufSubBufFromBuf            Vec3BufSubBufFromBufAsm

extern __C void Vec3SubtractAsm               (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3SubVecFromBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3SubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3SubBlockFromBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3SubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3uSubtract                   Vec3uSubtractAsm
#define Vec3uSubVecFromBlock            Vec3uSubVecFromBlockAsm
#define Vec3uSubVecFromBlockBySize      Vec3uSubVecFromBlockBySizeAsm
#define Vec3uBufSubVecFromBlock         Vec3uBufSubVecFromBlockAsm
#define Vec3uBufSubVecFromBuf           Vec3uBufSubVecFromBufAsm
#define Vec3uSubBlockFromBlock          Vec3uSubBlockFromBlockAsm
#define Vec3uSubBlockFromBlockBySize    Vec3uSubBlockFromBlockBySizeAsm
#define Vec3uBufSubBlockFromBuf         Vec3uBufSubBlockFromBufAsm
#define Vec3uBufSubBufFromBuf           Vec3uBufSubBufFromBufAsm

extern __C void Vec3uSubtractAsm               (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uSubVecFromBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubBlockFromBlockAsm      (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uSubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3Multiply                    Vec3MultiplyAsm
#define Vec3MulBlockByVec               Vec3MulBlockByVecAsm
#define Vec3MulBlockByVecUseSize        Vec3MulBlockByVecUseSizeAsm
#define Vec3BufMulBufByVec              Vec3BufMulBufByVecAsm
#define Vec3BufMulBufByVecUseSize       Vec3BufMulBufByVecUseSizeAsm
#define Vec3MulBlockByBlock             Vec3MulBlockByBlockAsm
#define Vec3MulBlockByBlockUseSize      Vec3MulBlockByBlockUseSizeAsm
#define Vec3BufMulBufByBlock            Vec3BufMulBufByBlockAsm
#define Vec3BufMulBufByBuf	           Vec3BufMulBufByBufAsm	

extern __C void Vec3MultiplyAsm              (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3MulBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3BufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3MulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3MulBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3MulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3uMultiply                   Vec3uMultiplyAsm
#define Vec3uMulBlockByVec              Vec3uMulBlockByVecAsm
#define Vec3uMulBlockByVecUseSize       Vec3uMulBlockByVecUseSizeAsm
#define Vec3uBufMulBufByVec             Vec3uBufMulBufByVecAsm
#define Vec3uBufMulBufByVecUseSize      Vec3uBufMulBufByVecUseSizeAsm
#define Vec3uMulBlockByBlock            Vec3uMulBlockByBlockAsm
#define Vec3uMulBlockByBlockUseSize     Vec3uMulBlockByBlockUseSizeAsm
#define Vec3uBufMulBufByBlock           Vec3uBufMulBufByBlockAsm
#define Vec3uBufMulBufByBuf             Vec3uBufMulBufByBufAsm

extern __C void Vec3uMultiplyAsm              (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uMulBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t nCount);
extern __C void Vec3uMulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uMulBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uMulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iVSize,const int32_t iCount);

#define Vec3Divide                      Vec3DivideAsm
#define Vec3DivBlockByVec               Vec3DivBlockByVecAsm
#define Vec3DivBlockByVecUseSize        Vec3DivBlockByVecUseSizeAsm
#define Vec3BufDivBufByVec              Vec3BufDivBufByVecAsm
#define Vec3BufDivBufByVecUseSize       Vec3BufDivBufByVecUseSizeAsm
#define Vec3DivBlockByBlock             Vec3DivBlockByBlockAsm
#define Vec3DivBlockByBlockUseSize      Vec3DivBlockByBlockUseSizeAsm
#define Vec3BufDivBufByBlock            Vec3BufDivBufByBlockAsm
#define Vec3BufDivBufByBuf              Vec3BufDivBufByBufAsm

extern __C void Vec3DivideAsm                (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3DivBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByVecUseSizeAsm  (void* ru,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByVecAsm        (void*  r,const void* u,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3DivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3uDivide                     Vec3uDivideAsm
#define Vec3uDivBlockByVec              Vec3uDivBlockByVecAsm
#define Vec3uDivBlockByVecUseSize       Vec3uDivBlockByVecUseSizeAsm
#define Vec3uBufDivBufByVec             Vec3uBufDivBufByVecAsm
#define Vec3uBufDivBufByVecUseSize      Vec3uBufDivBufByVecUseSizeAsm
#define Vec3uDivBlockByBlock            Vec3uDivBlockByBlockAsm
#define Vec3uDivBlockByBlockUseSize     Vec3uDivBlockByBlockUseSizeAsm
#define Vec3uBufDivBufByBlock           Vec3uBufDivBufByBlockAsm
#define Vec3uBufDivBufByBuf             Vec3uBufDivBufByBufAsm

extern __C void Vec3uDivideAsm                (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uDivBlockByVecAsm         (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByVecUseSizeAsm  (void* ru,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByVecAsm        (void*  r,const void* u,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uDivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3Lerp                        Vec3LerpAsm
#define Vec3LerpBlock                   Vec3LerpBlockAsm
#define Vec3LerpBlockUseSize            Vec3LerpBlockUseSizeAsm
#define Vec3BufLerpBlock                Vec3BufLerpBlockAsm
#define Vec3BufLerpBuf                  Vec3BufLerpBufAsm

extern __C void Vec3LerpAsm            (vec3*  r,const vec3* u,const vec3* v,const float s);
extern __C void Vec3LerpBlockAsm       (vec3* ru,vec3* v,const float s,const int32_t iCount);
extern __C void Vec3LerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec3BufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#define Vec3uLerp                       Vec3uLerpAsm
#define Vec3uLerpBlock                  Vec3uLerpBlockAsm
#define Vec3uLerpBlockUseSize           Vec3uLerpBlockUseSizeAsm
#define Vec3uBufLerpBlock               Vec3uBufLerpBlockAsm
#define Vec3uBufLerpBuf                 Vec3uBufLerpBufAsm

extern __C void Vec3uLerpAsm         (vec3*  r,const vec3* u,const vec3* v,const float s);
extern __C void Vec3uLerpBlockAsm    (vec3* ru,vec3* v,const float s,const int32_t iCount);
extern __C void Vec3uLerpBlockUseSize(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufLerpBlockAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec3uBufLerpBufAsm   (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#define Vec3DotFlat                     Vec3DotFlatAsm
#define Vec3uDotFlat                    Vec3uDotFlatAsm

extern __C void Vec3DotFlatAsm (float* r,const vec3* u,const vec3* v);
extern __C void Vec3uDotFlatAsm(float* r,const vec3* u,const vec3* v);

#define Vec3Dot                         Vec3DotAsm
#define Vec3DotBlock                    Vec3DotBlockAsm
#define Vec3DotBlockUseSize             Vec3DotBlockUseSizeAsm
#define Vec3BufDotBuf                   Vec3BufDotBufAsm

extern __C void Vec3DotAsm            (float* r,const vec3* u,const vec3* v);
extern __C void Vec3DotBlockAsm       (float* r,const vec3* u,const vec3* v,const int32_t iCount);
extern __C void Vec3DotBlockUseSizeAsm(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufDotBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3DotFPU                      Vec3DotFPU_Asm

extern __C void Vec3DotFPU_Asm(float* r,const vec3* u,const vec3* v);

#define Vec3uDot                        Vec3uDotAsm
#define Vec3uDotBlock                   Vec3uDotBlockAsm
#define Vec3uDotBlockUseSize            Vec3uDotBlockUseSizeAsm
#define Vec3uBufDotBuf                  Vec3uBufDotBufAsm

extern __C void Vec3uDotAsm            (float* r,const vec3* u,const vec3* v);
extern __C void Vec3uDotBlockAsm       (float* r,const vec3* u,const vec3* v,const int32_t iCount);
extern __C void Vec3uDotBlockUseSizeAsm(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufDotBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3Sqr                         Vec3SqrAsm
#define Vec3SqrBlock                    Vec3SqrBlockAsm
#define Vec3SqrBlockUseSize             Vec3SqrBlockUseSizeAsm
#define Vec3BufSqrBuf                   Vec3BufSqrBufAsm

extern __C void Vec3SqrAsm            (vec3*  r,const vec3* v);
extern __C void Vec3SqrBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3SqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3Sqrt                        Vec3SqrtAsm
#define Vec3SqrtBlock                   Vec3SqrtBlockAsm
#define Vec3SqrtBlockUseSize            Vec3SqrtBlockUseSizeAsm
#define Vec3BufSqrtBuf                  Vec3BufSqrtBufAsm

extern __C void Vec3SqrtAsm            (vec3*  r,const vec3* v);
extern __C void Vec3SqrtBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3SqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3uSqr                        Vec3uSqrAsm
#define Vec3uSqrBlock                   Vec3uSqrBlockAsm
#define Vec3uSqrBlockUseSize            Vec3uSqrBlockUseSizeAsm
#define Vec3uBufSqrBuf                  Vec3uBufSqrBufAsm

extern __C void Vec3uSqrAsm            (vec3* r,const vec3* v);
extern __C void Vec3uSqrBlockAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3uSqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3NormalizeFlat               Vec3NormalizeFlatAsm
#define Vec3NormalizeBlockFlat          Vec3NormalizeBlockFlatAsm
#define Vec3NormalizeBlockFlatUseSize   Vec3NormalizeBlockFlatUseSizeAsm
#define Vec3BufNormalizeBufFlat         Vec3BufNormalizeBufFlatAsm

extern __C void Vec3NormalizeFlatAsm            (vec3*  r,const vec3* v);
extern __C void Vec3NormalizeBlockFlatAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3NormalizeBlockFlatUseSizeAsm(vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNormalizeBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3Normalize                   Vec3NormalizeAsm
#define Vec3NormalizeBlock              Vec3NormalizeBlockAsm
#define Vec3NormalizeBlockUseSize       Vec3NormalizeBlockUseSizeAsm
#define Vec3BufNormalizeBuf             Vec3BufNormalizeBufAsm

extern __C void Vec3NormalizeAsm                (vec3*  r,const vec3* v);
extern __C void Vec3NormalizeBlockAsm           (vec3* ru,const int32_t iCount);
extern __C void Vec3NormalizeBlockUseSizeAsm    (vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufNormalizeBufAsm          (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3NormalizeFPU                Vec3NormalizeFPU_Asm

extern __C void Vec3NormalizeFPU_Asm            (vec3* r,const vec3* v);

#define Vec3uNormalizeFlat              Vec3uNormalizeFlatAsm
#define Vec3uNormalizeBlockFlat         Vec3uNormalizeBlockFlatAsm
#define Vec3uNormalizeBlockFlatUseSize  Vec3uNormalizeBlockFlatUseSizeAsm
#define Vec3uBufNormalizeBufFlat        Vec3uBufNormalizeBufFlatAsm

extern __C void Vec3uNormalizeFlatAsm            (vec3*  r,const vec3* v);
extern __C void Vec3uNormalizeBlockFlatAsm       (vec3* ru,const int32_t iCount);
extern __C void Vec3uNormalizeBlockFlatUseSizeAsm(vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNormalizeBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3uNormalize                  Vec3uNormalizeAsm
#define Vec3uNormalizeBlock             Vec3uNormalizeBlockAsm
#define Vec3uNormalizeBlockUseSize      Vec3uNormalizeBlockUseSizeAsm
#define Vec3uBufNormalizeBuf            Vec3uBufNormalizeBufAsm

extern __C void Vec3uNormalizeAsm                (vec3*  r,const vec3* v);
extern __C void Vec3uNormalizeBlockAsm           (vec3* ru,const int32_t iCount);
extern __C void Vec3uNormalizeBlockUseSizeAsm    (vec3* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufNormalizeBufAsm          (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3LengthFlat                  Vec3LengthFlatAsm
#define Vec3LengthBlockFlat             Vec3LengthBlockFlatAsm
#define Vec3LengthBlockFlatUseSize      Vec3LengthBlockFlatUseSizeAsm
#define Vec3BufLengthBufFlat            Vec3BufLengthBufFlatAsm

extern __C void Vec3LengthFlatAsm         (float* r,const vec3* v);
extern __C void Vec3LengthBlockFlatAsm    (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3LengthBlockFlatUseSize(float* r,const vec3* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLengthBufFlatAsm   (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3Length                      Vec3LengthAsm
#define Vec3LengthBlock                 Vec3LengthBlockAsm
#define Vec3LengthBlockUseSize          Vec3LengthBlockUseSizeAsm
#define Vec3BufLengthBuf                Vec3BufLengthBufAsm

extern __C void Vec3LengthAsm            (float* r,const vec3* v);
extern __C void Vec3LengthBlockAsm       (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3LengthBlockUseSizeAsm(float* r,const vec3* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufLengthBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3LengthFPU                   Vec3LengthFPU_Asm

extern __C void Vec3LengthFPU_Asm         (float* r,const vec3* v);

#define Vec3uLengthFlat                 Vec3uLengthFlatAsm
#define Vec3uLengthBlockFlat            Vec3uLengthBlockFlatAsm
#define Vec3uLengthBlockFlatUseSize     Vec3uLengthBlockFlatUseSizeAsm
#define Vec3uBufLengthBufFlat           Vec3uBufLengthBufFlatAsm

extern __C void Vec3uLengthFlatAsm            (float* r,const vec3& v);
extern __C void Vec3uLengthBlockFlatAsm       (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3uLengthBlockFlatUseSizeAsm(float* r,const vec3* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufLengthBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3uLength                     Vec3uLengthAsm
#define Vec3uLengthBlock                Vec3uLengthBlockAsm
#define Vec3uLengthBlockUseSize         Vec3uLengthBlockUseSizeAsm
#define Vec3uBufLengthBuf               Vec3uBufLengthBufAsm

extern __C void Vec3uLengthAsm            (float* r,const vec3* v);
extern __C void Vec3uLengthBlockAsm       (float* r,const vec3* u,const int32_t iCount);
extern __C void Vec3uLengthBlockUseSizeAsm(float* r,const vec3* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufLengthBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec3Cross                       Vec3CrossAsm
#define Vec3CrossBlock                  Vec3CrossBlockAsm
#define Vec3CrossBlockUseSize           Vec3CrossBlockUseSizeAsm
#define Vec3BufCrossBuf                 Vec3BufCrossBufAsm

extern __C void Vec3CrossAsm             (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3CrossBlockAsm        (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3CrossBlockUseSizeAsm (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3BufCrossBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3uCross                      Vec3uCrossAsm
#define Vec3uCrossBlock                 Vec3uCrossBlockAsm
#define Vec3uCrossBlockUseSize          Vec3uCrossBlockUseSizeAsm
#define Vec3uBufCrossBuf                Vec3uBufCrossBufAsm

extern __C void Vec3uCrossAsm            (vec3*  r,const vec3* u,const vec3* v);
extern __C void Vec3uCrossBlockAsm       (vec3* ru,const vec3* v,const int32_t iCount);
extern __C void Vec3uCrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec3uBufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec3Reflect                     Vec3ReflectAsm
#define Vec3uReflect                    Vec3uReflectAsm

extern __C void Vec3ReflectAsm (vec3* r,const vec3* u,const vec3* v);
extern __C void Vec3uReflectAsm(vec3* r,const vec3* u,const vec3* v);

#define Vec4Copy                        Vec4CopyAsm
#define Vec4CopyBlock                   Vec4CopyBlockAsm
#define BuildVec4PackedArray            BuildVec4PackedArrayAsm

extern __C void Vec4CopyAsm            (vec4* r,const vec4*  u);
extern __C void Vec4CopyBlockAsm       (vec4* r,const vec4*  u,const int32_t iCount);
extern __C void BuildVec4PackedArrayAsm(vec4* r,const vec4** pu,const int32_t iCount);

#define Vec4AddFloat                    Vec4AddFloatAsm
#define Vec4AddFloatToBlock             Vec4AddFloatToBlockAsm
#define Vec4AddFloatToBlockBySize       Vec4AddFloatToBlockBySizeAsm
#define Vec4BufAddFloatToBlock          Vec4BufAddFloatToBlockAsm
#define Vec4BufAddFloatToBuf            Vec4BufAddFloatToBufAsm

extern __C void Vec4AddFloatAsm             (vec4*  r,const vec4* v,const float s);
extern __C void Vec4AddFloatToBlockAsm      (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4AddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec4uAddFloat                   Vec4uAddFloatAsm
#define Vec4uAddFloatToBlock            Vec4uAddFloatToBlockAsm
#define Vec4uAddFloatToBlockBySize      Vec4uAddFloatToBlockBySizeAsm
#define Vec4uBufAddFloatToBlock         Vec4uBufAddFloatToBlockAsm
#define Vec4uBufAddFloatToBuf           Vec4uBufAddFloatToBufAsm

extern __C void Vec4uAddFloatAsm             (vec4* r,const vec4* v,const float s);
extern __C void Vec4uAddFloatToBlockAsm      (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uAddFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec4SubtractFloat               Vec4SubtractFloatAsm
#define Vec4SubtractFloatFromBlock      Vec4SubtractFloatFromBlockAsm
#define Vec4SubFloatFromBlockBySize     Vec4SubFloatFromBlockBySizeAsm
#define Vec4BufSubFloatFromBlock        Vec4BufSubFloatFromBlockAsm
#define Vec4BufSubFloatFromBuf          Vec4BufSubFloatFromBufAsm

extern __C void Vec4SubtractFloatAsm          (vec4* r,const vec4* u,const float s);
extern __C void Vec4SubtractFloatFromBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4SubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubFloatFromBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubFloatFromBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec4uSubtractFloat              Vec4uSubtractFloatAsm
#define Vec4uSubtractFloatFromBlock     Vec4uSubtractFloatFromBlockAsm
#define Vec4uSubFloatFromBlockBySize    Vec4uSubFloatFromBlockBySizeAsm
#define Vec4uBufSubFloatFromBlock       Vec4uBufSubFloatFromBlockAsm
#define Vec4uBufSubFloatFromBuf         Vec4uBufSubFloatFromBufAsm

extern __C void Vec4uSubtractFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uSubtractFloatFromBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uSubFloatFromBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubFloatFromBlockAsm   (void* r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubFloatFromBufAsm     (void* r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec4MultiplyFloat               Vec4MultiplyFloatAsm
#define Vec4MultiplyFloatToBlock        Vec4MultiplyFloatToBlockAsm
#define Vec4MulFloatToBlockBySize       Vec4MulFloatToBlockBySizeAsm
#define Vec4BufMulFloatToBlock          Vec4BufMulFloatToBlockAsm
#define Vec4BufMulFloatToBuf            Vec4BufMulFloatToBufAsm

extern __C void Vec4MultiplyFloatAsm        (vec4*  r,const vec4* u,const float s);
extern __C void Vec4MultiplyFloatToBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4MulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec4uMultiplyFloat              Vec4uMultiplyFloatAsm
#define Vec4uMultiplyFloatToBlock       Vec4uMultiplyFloatToBlockAsm
#define Vec4uMulFloatToBlockBySize      Vec4uMulFloatToBlockBySizeAsm
#define Vec4uBufMulFloatToBlock         Vec4uBufMulFloatToBlockAsm
#define Vec4uBufMulFloatToBuf           Vec4uBufMulFloatToBufAsm

extern __C void Vec4uMultiplyFloatAsm        (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uMultiplyFloatToBlockAsm (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uMulFloatToBlockBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulFloatToBlockAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulFloatToBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec4DivideFloat                 Vec4DivideFloatAsm
#define Vec4DivideBlockByFloat          Vec4DivideBlockByFloatAsm
#define Vec4DivBlockByFloatBySize       Vec4DivBlockByFloatBySizeAsm
#define Vec4BufDivBlockByFloat          Vec4BufDivBlockByFloatAsm
#define Vec4BufDivBufByFloat            Vec4BufDivBufByFloatAsm

extern __C void Vec4DivideFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4DivideBlockByFloatAsm   (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4DivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBlockByFloatAsm   (void*  r,const void* u,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec4uDivideFloat                Vec4uDivideFloatAsm
#define Vec4uDivideBlockByFloat         Vec4uDivideBlockByFloatAsm
#define Vec4uDivBlockByFloatBySize      Vec4uDivBlockByFloatBySizeAsm
#define Vec4uBufDivBlockByFloat         Vec4uBufDivBlockByFloatAsm
#define Vec4uBufDivBufByFloat           Vec4uBufDivBufByFloatAsm

extern __C void Vec4uDivideFloatAsm          (vec4*  r,const vec4* u,const float s);
extern __C void Vec4uDivideBlockByFloatAsm   (vec4* rv,const float s,const int32_t iCount);
extern __C void Vec4uDivBlockByFloatBySizeAsm(void* rv,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBlockByFloatAsm   (void*  r,const void*   u,const float   s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByFloatAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const float s,const int32_t iCount);

#define Vec4Equals                      Vec4EqualsAsm
#define Vec4NotEquals                   Vec4NotEqualsAsm

extern __C void Vec4EqualsAsm   (int32_t* iFlag,const vec4* u,const vec4* v);
extern __C void Vec4NotEqualsAsm(int32_t* iFlag,const vec4* u,const vec4* v);

#define Vec4Negate                      Vec4NegateAsm
#define Vec4NegateBlock                 Vec4NegateBlockAsm
#define Vec4NegateBlockBySize           Vec4NegateBlockBySizeAsm
#define Vec4BufNegateBlock              Vec4BufNegateBlockAsm
#define Vec4BufNegateBuf                Vec4BufNegateBufAsm

extern __C void Vec4NegateAsm           (vec4*  r,const vec4* v);
extern __C void Vec4NegateBlockAsm      (vec4* rv,int32_t iCount);
extern __C void Vec4NegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4uNegate                     Vec4uNegateAsm
#define Vec4uNegateBlock                Vec4uNegateBlockAsm
#define Vec4uNegateBlockBySize          Vec4uNegateBlockBySizeAsm
#define Vec4uBufNegateBlock             Vec4uBufNegateBlockAsm
#define Vec4uBufNegateBuf               Vec4uBufNegateBufAsm

extern __C void Vec4uNegateAsm           (vec4*  r,const vec4* v);
extern __C void Vec4uNegateBlockAsm      (vec4* rv,int32_t iCount);
extern __C void Vec4uNegateBlockBySizeAsm(void* rv,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNegateBlockAsm   (void*  r,const void* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNegateBufAsm     (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4Add                         Vec4AddAsm
#define Vec4AddVecToBlock               Vec4AddVecToBlockAsm
#define Vec4AddVecToBlockBySize         Vec4AddVecToBlockBySizeAsm
#define Vec4BufAddVecToBlock            Vec4BufAddVecToBlockAsm
#define Vec4BufAddVecToBuf              Vec4BufAddVecToBufAsm
#define Vec4AddBlockToBlock             Vec4AddBlockToBlockAsm
#define Vec4AddBlockToBlockBySize       Vec4AddBlockToBlockBySizeAsm
#define Vec4BufAddBlockToBuf            Vec4BufAddBlockToBufAsm
#define Vec4BufAddBufToBuf              Vec4BufAddBufToBufAsm

extern __C void Vec4AddAsm                  (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4AddVecToBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4AddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec4AddBlockToBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4AddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4uAdd                        Vec4uAddAsm
#define Vec4uAddVecToBlock              Vec4uAddVecToBlockAsm
#define Vec4uAddVecToBlockBySize        Vec4uAddVecToBlockBySizeAsm
#define Vec4uBufAddVecToBlock           Vec4uBufAddVecToBlockAsm
#define Vec4uBufAddVecToBuf             Vec4uBufAddVecToBufAsm
#define Vec4uAddBlockToBlock            Vec4uAddBlockToBlockAsm
#define Vec4uAddBlockToBlockBySize      Vec4uAddBlockToBlockBySizeAsm
#define Vec4uBufAddBlockToBuf           Vec4uBufAddBlockToBufAsm
#define Vec4uBufAddBufToBuf             Vec4uBufAddBufToBufAsm

extern __C void Vec4uAddAsm                  (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uAddVecToBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uAddVecToBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddVecToBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddVecToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec4uAddBlockToBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uAddBlockToBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddBlockToBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufAddBufToBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4Subtract                    Vec4SubtractAsm
#define Vec4SubVecFromBlock             Vec4SubVecFromBlockAsm
#define Vec4SubVecFromBlockBySize       Vec4SubVecFromBlockBySizeAsm
#define Vec4BufSubVecFromBlock          Vec4BufSubVecFromBlockAsm
#define Vec4BufSubVecFromBuf            Vec4BufSubVecFromBufAsm
#define Vec4SubBlockFromBlock           Vec4SubBlockFromBlockAsm
#define Vec4SubBlockFromBlockBySize     Vec4SubBlockFromBlockBySizeAsm
#define Vec4BufSubBlockFromBuf          Vec4BufSubBlockFromBufAsm
#define Vec4BufSubBufFromBuf            Vec4BufSubBufFromBufAsm

extern __C void Vec4SubtractAsm               (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4SubVecFromBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4SubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4SubBlockFromBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4SubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4uSubtract                   Vec4uSubtractAsm
#define Vec4uSubVecFromBlock            Vec4uSubVecFromBlockAsm
#define Vec4uSubVecFromBlockBySize      Vec4uSubVecFromBlockBySizeAsm
#define Vec4uBufSubVecFromBlock         Vec4uBufSubVecFromBlockAsm
#define Vec4uBufSubVecFromBuf           Vec4uBufSubVecFromBufAsm
#define Vec4uSubBlockFromBlock          Vec4uSubBlockFromBlockAsm
#define Vec4uSubBlockFromBlockBySize    Vec4uSubBlockFromBlockBySizeAsm
#define Vec4uBufSubBlockFromBuf         Vec4uBufSubBlockFromBufAsm
#define Vec4uBufSubBufFromBuf           Vec4uBufSubBufFromBufAsm

extern __C void Vec4uSubtractAsm               (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uSubVecFromBlockAsm        (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uSubVecFromBlockBySizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubVecFromBlockAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubVecFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iCount);
extern __C void Vec4uSubBlockFromBlockAsm      (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uSubBlockFromBlockBySizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubBlockFromBufAsm     (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSubBufFromBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4Multiply                    Vec4MultiplyAsm
#define Vec4MulBlockByVec               Vec4MulBlockByVecAsm
#define Vec4MulBlockByVecUseSize        Vec4MulBlockByVecUseSizeAsm
#define Vec4BufMulBufByVec              Vec4BufMulBufByVecAsm
#define Vec4BufMulBufByVecUseSize       Vec4BufMulBufByVecUseSizeAsm
#define Vec4MulBlockByBlock             Vec4MulBlockByBlockAsm
#define Vec4MulBlockByBlockUseSize      Vec4MulBlockByBlockUseSizeAsm
#define Vec4BufMulBufByBlock            Vec4BufMulBufByBlockAsm
#define Vec4BufMulBufByBuf              Vec4BufMulBufByBufAsm

extern __C void Vec4MultiplyAsm              (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4MulBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4MulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4MulBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4MulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4uMultiply                   Vec4uMultiplyAsm
#define Vec4uMulBlockByVec              Vec4uMulBlockByVecAsm
#define Vec4uMulBlockByVecUseSize       Vec4uMulBlockByVecUseSizeAsm
#define Vec4uBufMulBufByVec             Vec4uBufMulBufByVecAsm
#define Vec4uBufMulBufByVecUseSize      Vec4uBufMulBufByVecUseSizeAsm
#define Vec4uMulBlockByBlock            Vec4uMulBlockByBlockAsm
#define Vec4uMulBlockByBlockUseSize     Vec4uMulBlockByBlockUseSizeAsm
#define Vec4uBufMulBufByBlock           Vec4uBufMulBufByBlockAsm
#define Vec4uBufMulBufByBuf             Vec4uBufMulBufByBufAsm

extern __C void Vec4uMultiplyAsm              (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uMulBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t nCount);
extern __C void Vec4uMulBlockByVecUseSizeAsm  (void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByVecAsm        (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec4uMulBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uMulBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufMulBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iVSize,const int32_t iCount);

#define Vec4Divide                      Vec4DivideAsm
#define Vec4DivBlockByVec               Vec4DivBlockByVecAsm
#define Vec4DivBlockByVecUseSize        Vec4DivBlockByVecUseSizeAsm
#define Vec4BufDivBufByVec              Vec4BufDivBufByVecAsm
#define Vec4BufDivBufByVecUseSize       Vec4BufDivBufByVecUseSizeAsm
#define Vec4DivBlockByBlock             Vec4DivBlockByBlockAsm
#define Vec4DivBlockByBlockUseSize      Vec4DivBlockByBlockUseSizeAsm
#define Vec4BufDivBufByBlock            Vec4BufDivBufByBlockAsm
#define Vec4BufDivBufByBuf              Vec4BufDivBufByBufAsm

extern __C void Vec4DivideAsm                (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4DivBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByVecUseSizeAsm  (void* ru,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByVecAsm        (void*  r,const void* u,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4DivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4uDivide                     Vec4uDivideAsm
#define Vec4uDivBlockByVec              Vec4uDivBlockByVecAsm
#define Vec4uDivBlockByVecUseSize       Vec4uDivBlockByVecUseSizeAsm
#define Vec4uBufDivBufByVec             Vec4uBufDivBufByVecAsm
#define Vec4uBufDivBufByVecUseSize      Vec4uBufDivBufByVecUseSizeAsm
#define Vec4uDivBlockByBlock            Vec4uDivBlockByBlockAsm
#define Vec4uDivBlockByBlockUseSize     Vec4uDivBlockByBlockUseSizeAsm
#define Vec4uBufDivBufByBlock           Vec4uBufDivBufByBlockAsm
#define Vec4uBufDivBufByBuf             Vec4uBufDivBufByBufAsm

extern __C void Vec4uDivideAsm                (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uDivBlockByVecAsm         (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uDivBlockByVecUseSizeAsm  (void* ru,const vec3* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByVecAsm        (void*  r,const void* u,const vec4* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByVecUseSizeAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const int32_t iCount);
extern __C void Vec4uDivBlockByBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uDivBlockByBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByBlockAsm      (void*  r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDivBufByBufAsm        (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4Lerp                        Vec4LerpAsm
#define Vec4LerpBlock                   Vec4LerpBlockAsm
#define Vec4LerpBlockUseSize            Vec4LerpBlockUseSizeAsm
#define Vec4BufLerpBlock                Vec4BufLerpBlockAsm
#define Vec4BufLerpBuf                  Vec4BufLerpBufAsm

extern __C void Vec4LerpAsm            (vec4*  r,const vec4* u,const vec4* v,const float s);
extern __C void Vec4LerpBlockAsm       (vec4* ru,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4LerpBlockUseSizeAsm(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLerpBlockAsm    (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4BufLerpBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#define Vec4uLerp                       Vec4uLerpAsm
#define Vec4uLerpBlock                  Vec4uLerpBlockAsm
#define Vec4uLerpBlockUseSize           Vec4uLerpBlockUseSizeAsm
#define Vec4uBufLerpBlock               Vec4uBufLerpBlockAsm
#define Vec4uBufLerpBuf                 Vec4uBufLerpBufAsm

extern __C void Vec4uLerpAsm         (vec4*  r,const vec4* u,const vec4* v,const float s);
extern __C void Vec4uLerpBlockAsm    (vec4* ru,const vec4* v,const float s,const int32_t iCount);
extern __C void Vec4uLerpBlockUseSize(void* ru,const void* v,const float s,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufLerpBlockAsm (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const vec3* v,const float s,const int32_t iCount);
extern __C void Vec4uBufLerpBufAsm   (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const float s,const int32_t iCount);

#define Vec4DotFlat                     Vec4DotFlatAsm
#define Vec4DotBlockFlat                Vec4DotBlockFlatAsm
#define Vec4DotBlockFlatUseSize         Vec4DotBlockFlatUseSizeAsm
#define Vec4BufDotBufFlat               Vec4BufDotBufFlatAsm

extern __C void Vec4DotFlatAsm             (float* r,const vec4* u,const vec4* v);
extern __C void Vec4DotBlockFlatAsm        (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4DotBlockFlatUseSizeAsm (float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDotBufFlatAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4Dot                         Vec4DotAsm
#define Vec4DotBlock                    Vec4DotBlockAsm
#define Vec4DotBlockUseSize             Vec4DotBlockUseSizeAsm
#define Vec4BufDotBuf                   Vec4BufDotBufAsm

extern __C void Vec4DotAsm                 (float* r,const vec4* u,const vec4* v);
extern __C void Vec4DotBlockAsm            (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4DotBlockUseSizeAsm     (float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufDotBufAsm           (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4DotFPU                      Vec4DotFPU_Asm

extern __C void Vec4uDotFPU_Asm            (float* r,const vec4* u,const vec4* v);

#define Vec4uDotFlat                    Vec4uDotFlatAsm
#define Vec4uDotBlockFlat               Vec4uDotBlockFlatAsm
#define Vec4uDotBlockFlatUseSize        Vec4uDotBlockFlatUseSizeAsm
#define Vec4uBufDotBufFlat              Vec4uBufDotBufFlatAsm

extern __C void Vec4uDotFlatAsm            (float* r,const vec4* u,const vec4* v);
extern __C void Vec4uDotBlockFlatAsm       (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4uDotBlockFlatUseSizeAsm(float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDotBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4uDot                        Vec4uDotAsm
#define Vec4uDotBlock                   Vec4uDotBlockAsm
#define Vec4uDotBlockUseSize            Vec4uDotBlockUseSizeAsm
#define Vec4uBufDotBuf                  Vec4uBufDotBufAsm

extern __C void Vec4uDotAsm                (float* r,const vec4* u,const vec4* v);
extern __C void Vec4uDotBlockAsm           (float* r,const vec4* u,const vec4* v,const int32_t iCount);
extern __C void Vec4uDotBlockUseSizeAsm    (float* r,const void* u,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufDotBufAsm          (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4Sqr                         Vec4SqrAsm
#define Vec4SqrBlock                    Vec4SqrBlockAsm
#define Vec4SqrBlockUseSize             Vec4SqrBlockUseSizeAsm
#define Vec4BufSqrBuf                   Vec4BufSqrBufAsm

extern __C void Vec4SqrAsm            (vec4*  r,const vec4* v);
extern __C void Vec4SqrBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4SqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4Sqrt                        Vec4SqrtAsm
#define Vec4SqrtBlock                   Vec4SqrtBlockAsm
#define Vec4SqrtBlockUseSize            Vec4SqrtBlockUseSizeAsm
#define Vec4BufSqrtBuf                  Vec4BufSqrtBufAsm

extern __C void Vec4SqrtAsm            (vec4*  r,const vec4* v);
extern __C void Vec4SqrtBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4SqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4uSqr                        Vec4uSqrAsm
#define Vec4uSqrBlock                   Vec4uSqrBlockAsm
#define Vec4uSqrBlockUseSize            Vec4uSqrBlockUseSizeAsm
#define Vec4uBufSqrBuf                  Vec4uBufSqrBufAsm

extern __C void Vec4uSqrAsm            (vec4*  r,const vec4* v);
extern __C void Vec4uSqrBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4uSqrBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSqrBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4uSqrt                       Vec4uSqrtAsm
#define Vec4uSqrtBlock                  Vec4uSqrtBlockAsm
#define Vec4uSqrtBlockUseSize           Vec4uSqrtBlockUseSizeAsm
#define Vec4uBufSqrtBuf                 Vec4uBufSqrtBufAsm

extern __C void Vec4uSqrtAsm            (vec4*  r,const vec4* v);
extern __C void Vec4uSqrtBlockAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4uSqrtBlockUseSizeAsm(void* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufSqrtBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4NormalizeFlat               Vec4NormalizeFlatAsm
#define Vec4NormalizeBlockFlat          Vec4NormalizeBlockFlatAsm
#define Vec4NormalizeBlockFlatUseSize   Vec4NormalizeBlockFlatUseSizeAsm
#define Vec4BufNormalizeBufFlat         Vec4BufNormalizeBufFlatAsm

extern __C void Vec4NormalizeFlatAsm             (vec4*  r,const vec3* v);
extern __C void Vec4NormalizeBlockFlatAsm        (vec4* ru,const int32_t iCount);
extern __C void Vec4NormalizeBlockFlatUseSizeAsm (vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNormalizeBufFlatAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4Normalize                   Vec4NormalizeAsm
#define Vec4NormalizeBlock              Vec4NormalizeBlockAsm
#define Vec4NormalizeBlockUseSize       Vec4NormalizeBlockUseSizeAsm
#define Vec4BufNormalizeBuf             Vec4BufNormalizeBufAsm

extern __C void Vec4NormalizeAsm                 (vec4*  r,const vec4* v);
extern __C void Vec4NormalizeBlockAsm            (vec4* ru,const int32_t iCount);
extern __C void Vec4NormalizeBlockUseSizeAsm     (vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufNormalizeBufAsm           (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4NormalizeFPU                Vec4NormalizeFPU_Asm

extern __C void Vec4uNormalizeFPU_Asm            (vec4*  r,const vec3* v);

#define Vec4uNormalizeFlat              Vec4uNormalizeFlatAsm
#define Vec4uNormalizeBlockFlat         Vec4uNormalizeBlockFlatAsm
#define Vec4uNormalizeBlockFlatUseSize  Vec4uNormalizeBlockFlatUseSizeAsm
#define Vec4uBufNormalizeBufFlat        Vec4uBufNormalizeBufFlatAsm

extern __C void Vec4uNormalizeFlatAsm            (vec4*  r,const vec3* v);
extern __C void Vec4uNormalizeBlockFlatAsm       (vec4* ru,const int32_t iCount);
extern __C void Vec4uNormalizeBlockFlatUseSizeAsm(vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNormalizeBufFlatAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4uNormalize                  Vec4uNormalizeAsm
#define Vec4uNormalizeBlock             Vec4uNormalizeBlockAsm
#define Vec4uNormalizeBlockUseSize      Vec4uNormalizeBlockUseSizeAsm
#define Vec4uBufNormalizeBuf            Vec4uBufNormalizeBufAsm

extern __C void Vec4uNormalizeAsm                (vec4*  r,const vec3* v);
extern __C void Vec4uNormalizeBlockAsm           (vec4* ru,const int32_t iCount);
extern __C void Vec4uNormalizeBlockUseSizeAsm    (vec4* ru,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufNormalizeBufAsm          (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4LengthFlat                  Vec4LengthFlatAsm
#define Vec4LengthBlockFlat             Vec4LengthBlockFlatAsm
#define Vec4LengthBlockFlatUseSize      Vec4LengthBlockFlatUseSizeAsm
#define Vec4BufLengthBufFlat            Vec4BufLengthBufFlatAsm

extern __C void Vec4LengthFlatAsm            (float* r,const vec4* v);
extern __C void Vec4LengthBlockFlatAsm       (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4LengthBlockFlatUseSizeAsm(float* r,const vec4* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLengthFlatBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4Length                      Vec4LengthAsm
#define Vec4LengthBlock                 Vec4LengthBlockAsm
#define Vec4LengthBlockUseSize          Vec4LengthBlockUseSizeAsm
#define Vec4BufLengthBuf                Vec4BufLengthBufAsm

extern __C void Vec4LengthAsm             (float* r,const vec4* v);
extern __C void Vec4LengthBlockAsm        (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4LengthBlockUseSizeAsm (float* r,const vec4* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufLengthBufAsm       (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4LengthFPU                   Vec4LengthFPU_Asm

extern __C void Vec4LengthFPU_Asm          (float* r,const vec4* v);

#define Vec4uLengthFlat                 Vec4uLengthFlatAsm
#define Vec4uLengthBlockFlat            Vec4uLengthBlockFlatAsm
#define Vec4uLengthBlockFlatUseSize     Vec4uLengthBlockFlatUseSizeAsm
#define Vec4uBufLengthBufFlat           Vec4uBufLengthBufFlatAsm

extern __C void Vec4uLengthFlatAsm            (float* r,const vec4* v);
extern __C void Vec4uLengthBlockFlatAsm       (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4uLengthBlockFlatUseSizeAsm(float* r,const vec4* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufLengthFlatBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4uLength                     Vec4uLengthAsm
#define Vec4uLengthBlock                Vec4uLengthBlockAsm
#define Vec4uLengthBlockUseSize         Vec4uLengthBlockUseSizeAsm
#define Vec4uBufLengthBuf               Vec4uBufLengthBufAsm

extern __C void Vec4uLengthAsm            (float* r,const vec4* v);
extern __C void Vec4uLengthBlockAsm       (float* r,const vec4* u,const int32_t iCount);
extern __C void Vec4uLengthBlockUseSizeAsm(float* r,const vec4* u,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufLengthBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const int32_t iCount);

#define Vec4Cross                       Vec4CrossAsm
#define Vec4CrossBlock                  Vec4CrossBlockAsm
#define Vec4CrossBlockUseSize           Vec4CrossBlockUseSizeAsm
#define Vec4BufCrossBuf                 Vec4BufCrossBufAsm

extern __C void Vec4CrossAsm            (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4CrossBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4CrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4BufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Vec4uCross                      Vec4uCrossAsm
#define Vec4uCrossBlock                 Vec4uCrossBlockAsm
#define Vec4uCrossBlockUseSize          Vec4uCrossBlockUseSizeAsm
#define Vec4uBufCrossBuf                Vec4uBufCrossBufAsm

extern __C void Vec4uCrossAsm            (vec4*  r,const vec4* u,const vec4* v);
extern __C void Vec4uCrossBlockAsm       (vec4* ru,const vec4* v,const int32_t iCount);
extern __C void Vec4uCrossBlockUseSizeAsm(void* ru,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Vec4uBufCrossBufAsm      (void*  r,const int32_t iRSize,const void* u,const int32_t iUSize,const void* v,const int32_t iVSize,const int32_t iCount);

#define Mat2Negate                      Mat2NegateAsm
#define Mat2Add                         Mat2AddAsm
#define Mat2AddFloat                    Mat2AddFloatAsm
#define Mat2Subtract                    Mat2SubtractAsm
#define Mat2SubtractFloat               Mat2SubtractFloatAsm
#define Mat2Multiply                    Mat2MultiplyAsm
#define Mat2MultiplyVec                 Mat2MultiplyVecAsm
#define Mat2MultiplyFloat               Mat2MultiplyFloatAsm
#define Mat2Identity                    Mat2IdentityAsm
#define Mat2Transpose                   Mat2TransposeAsm
#define Mat2MultiplyVecBlock            Mat2MultiplyVecBlockAsm

extern __C void Mat2NegateAsm          (mat2* r,const mat2* m);
extern __C void Mat2AddAsm             (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2AddFloatAsm        (mat2* r,const mat2* m,const float s);
extern __C void Mat2SubtractAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2SubtractFloatAsm   (mat2* r,const mat2* m,const float s);
extern __C void Mat2MultiplyAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2MultiplyVecAsm     (vec2* r,const mat2* m,const vec2* v);
extern __C void Mat2MultiplyFloatAsm   (mat2* r,const mat2* m,const float x);
extern __C void Mat2IdentityAsm        (mat2* r);
extern __C void Mat2TransposeAsm       (mat2* r,const mat2* m);
extern __C void Mat2MultiplyVecBlockAsm(vec2* r,const mat2* m,const vec2* v,int32_t iCount);

#define Mat2uNegate                     Mat2uNegateAsm
#define Mat2uAdd                        Mat2uAddAsm
#define Mat2uAddFloat                   Mat2uAddFloatAsm
#define Mat2uSubtract                   Mat2uSubtractAsm
#define Mat2uSubtractFloat              Mat2uSubtractFloatAsm
#define Mat2uMultiply                   Mat2uMultiplyAsm
#define Mat2uMultiplyVec                Mat2uMultiplyVecAsm
#define Mat2uMultiplyFloat              Mat2uMultiplyFloatAsm
#define Mat2uIdentity                   Mat2uIdentityAsm
#define Mat2uTranspose                  Mat2uTransposeAsm
#define Mat2uMultiplyVecBlock           Mat2uMultiplyVecBlockAsm

extern __C void Mat2uNegateAsm          (mat2* r,const mat2* m);
extern __C void Mat2uAddAsm             (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uAddFloatAsm        (mat2* r,const mat2* m,const float s);
extern __C void Mat2uSubtractAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uSubtractFloatAsm   (mat2* r,const mat2* m,const float s);
extern __C void Mat2uMultiplyAsm        (mat2* r,const mat2* m,const mat2* n);
extern __C void Mat2uMultiplyVecAsm     (vec2* r,const mat2* m,const vec2* v);
extern __C void Mat2uMultiplyFloatAsm   (mat2* r,const mat2* m,const float x);
extern __C void Mat2uIdentityAsm        (mat2* r);
extern __C void Mat2uTransposeAsm       (mat2* r,const mat2* m);
extern __C void Mat2uMultiplyVecBlockAsm(vec2* r,const mat2* m,const vec2* v,int32_t iCount);

#define Mat2RotateLH                    Mat2RotateLHAsm
#define Mat2RotateRH                    Mat2RotateRHAsm
#define Mat2Rotate                      Mat2RotateAsm
#define Mat2Scale                       Mat2ScaleAsm

extern __C void Mat2RotateLHAsm(mat2* r,const float angle);
extern __C void Mat2RotateRHAsm(mat2* r,const float angle);
extern __C void Mat2RotateAsm  (mat2* r,const float angle);
extern __C void Mat2ScaleAsm   (mat2* r,const float x_scale,const float y_scale);

#define Mat3Copy                        Mat3CopyAsm
#define Mat3Identity                    Mat3IdentityAsm

extern __C void Mat3CopyAsm    (mat3* r,const mat3* m);
extern __C void Mat3IdentityAsm(mat3* r);

#define Mat3Negate                      Mat3NegateAsm
#define Mat3Add                         Mat3AddAsm
#define Mat3AddFloat                    Mat3AddFloatAsm
#define Mat3Subtract                    Mat3SubtractAsm
#define Mat3SubtractFloat               Mat3SubtractFloatAsm

extern __C void Mat3NegateAsm       (mat3* r,const mat3* m);
extern __C void Mat3AddAsm          (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3AddFloatAsm     (mat3* r,const mat3* m,const float s);
extern __C void Mat3SubtractAsm     (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3SubtractFloatAsm(mat3* r,const mat3* m,const float s);

#define Mat3Multiply                    Mat3MultiplyAsm
#define Mat3MultiplyIdentityByBlocks    Mat3MultiplyIdentityByBlocksAsm

extern __C void Mat3MultiplyAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3MultiplyIdentityByBlocksAsm(mat3* r,const mat3* m,int32_t iCount);

#define Mat3MultiplyVec                 Mat3MultiplyVecAsm
#define Mat3MultiplyVecBlock            Mat3MultiplyVecBlockAsm
#define Mat3MulVecBlockBySize           Mat3MulVecBlockBySizeAsm
#define Mat3MulVec3BufByBuf             Mat3MulVec3BufByBufAsm
#define Mat3MultiplyFloat               Mat3MultiplyFloatAsm
#define Mat3Inverse                     Mat3InverseAsm
#define Mat3Transpose                   Mat3TransposeAsm

extern __C void Mat3MultiplyVecAsm             (vec3* r,const mat3* m,const vec3* v);
extern __C void Mat3MultiplyVecBlockAsm        (vec3* r,const mat3* m,const vec3* v,int32_t iCount);
extern __C void Mat3MulVecBlockBySizeAsm       (void* r,const mat3* m,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Mat3MulVec3BufByBufAsm         (void* r,const int32_t iRSize,const mat3* m,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Mat3MultiplyFloatAsm           (mat3* r,const mat3* m,const float x);
extern __C void Mat3InverseAsm                 (mat3* r,const mat3* m);
extern __C void Mat3TransposeAsm               (mat3* r,const mat3* m);

#define Mat3MultiplyFPU                 Mat3MultiplyFPU_Asm
#define Mat3MultiplyIdentityByBlockFPU  Mat3MultiplyIdentityByBlockFPU_Asm

extern __C void Mat3MultiplyFPU_Asm               (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3MultiplyIdentityByBlockFPU_Asm(mat3* r,const mat3* m,const int32_t iCount);

#define Mat3uNegate                     Mat3uNegateAsm
#define Mat3uAdd                        Mat3uAddAsm
#define Mat3uAddFloat                   Mat3uAddFloatAsm
#define Mat3uSubtract                   Mat3uSubtractAsm
#define Mat3uSubtractFloat              Mat3uSubtractFloatAsm

extern __C void Mat3uNegateAsm                  (mat3* r,const mat3* m);
extern __C void Mat3uAddAsm                     (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uAddFloatAsm                (mat3* r,const mat3* m,const float s);
extern __C void Mat3uSubtractAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uSubtractFloatAsm           (mat3* r,const mat3* m,const float s);

#define Mat3uMultiply                   Mat3uMultiplyAsm
#define Mat3uMultiplyIdentityByBlocks   Mat3uMultiplyIdentityByBlocksAsm

extern __C void Mat3uMultiplyAsm                (mat3* r,const mat3* m,const mat3* n);
extern __C void Mat3uMultiplyIdentityByBlocksAsm(mat3* r,const mat3* m,int32_t nCount);

#define Mat3uMultiplyVec                Mat3uMultiplyVecAsm
#define Mat3uMultiplyVecBlock           Mat3uMultiplyVecBlockAsm
#define Mat3uMulVecBlockBySize          Mat3uMulVecBlockBySizeAsm
#define Mat3uMulVec3BufByBuf            Mat3uMulVec3BufByBufAsm
#define Mat3uMultiplyFloat              Mat3uMultiplyFloatAsm
#define Mat3uInverse                    Mat3uInverseAsm
#define Mat3uTranspose                  Mat3uTransposeAsm

extern __C void Mat3uMultiplyVecAsm             (vec3* r,const mat3* m,const vec3* v);
extern __C void Mat3uMultiplyVecBlockAsm        (vec3* r,const mat3* m,const vec3* v,int32_t iCount);
extern __C void Mat3uMulVecBlockBySizeAsm       (void* r,const mat3* m,const void* v,const int32_t iSize,const int32_t iCount);
extern __C void Mat3uMulVec3BufByBufAsm         (void* r,const int32_t iRSize,const mat3* m,const void* v,const int32_t iVSize,const int32_t iCount);
extern __C void Mat3uMultiplyFloatAsm           (mat3* r,const mat3* m,const float x);
extern __C void Mat3uInverseAsm                 (mat3* r,const mat3* m);
extern __C void Mat3uTransposeAsm               (mat3* r,const mat3* m);

#define Mat3RotateRHX                   Mat3RotateRHX_Asm
#define Mat3RotateLHX                   Mat3RotateLHX_Asm
#define Mat3RotateRHY                   Mat3RotateRHY_Asm
#define Mat3RotateLHY                   Mat3RotateLHY_Asm
#define Mat3RotateRHZ                   Mat3RotateRHZ_Asm
#define Mat3RotateLHZ                   Mat3RotateLHZ_Asm

extern __C void Mat3RotateRHX_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateLHX_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateRHY_Asm  (mat3* m,const float angle);
extern __C void Mat3RotateLHY_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateRHZ_Asm  (mat3* r,const float angle);
extern __C void Mat3RotateLHZ_Asm  (mat3* r,const float angle);

#define Mat3RotateRHXY                  Mat3RotateRHXY_Asm
#define Mat3RotateLHXY                  Mat3RotateLHXY_Asm
#define Mat3RotateRHXZ                  Mat3RotateRHXZ_Asm
#define Mat3RotateLHXZ                  Mat3RotateLHXZ_Asm
#define Mat3RotateRHYZ                  Mat3RotateRHYZ_Asm
#define Mat3RotateLHYZ                  Mat3RotateLHYZ_Asm

extern __C void Mat3RotateRHXY_Asm (mat3* r,const float x,const float y);
extern __C void Mat3RotateLHXY_Asm (mat3* r,const float x,const float y);
extern __C void Mat3RotateRHXZ_Asm (mat3* m,const float x,const float z);
extern __C void Mat3RotateLHXZ_Asm (mat3* m,const float x,const float z);
extern __C void Mat3RotateRHYZ_Asm (mat3* r,const float y,const float z);
extern __C void Mat3RotateLHYZ_Asm (mat3* m,const float y,const float z);

#define Mat3RotateRHXYZ                 Mat3RotateRHXYZ_Asm
#define Mat3RotateLHXYZ                 Mat3RotateLHXYZ_Asm

extern __C void Mat3RotateRHXYZ_Asm(mat3* r,const float x,const float y,const float z);
extern __C void Mat3RotateLHXYZ_Asm(mat3* r,const float x,const float y,const float z);

#define Mat3Scale                       Mat3ScaleAsm
#define Mat3ScaleByVec3                 Mat3ScaleByVec3Asm

extern __C void Mat3ScaleAsm      (mat3* r,const float x_scale,const float y_scale,const float z_scale);
extern __C void Mat3ScaleByVec3Asm(mat3* r,const vec3* v);

#define Mat4Copy                        Mat4CopyAsm

extern __C void Mat4CopyAsm(mat4* r,const mat4* m);

#define Mat4Negate                      Mat4NegateAsm
#define Mat4NegateMatrix                Mat4NegateMatrixAsm
#define Mat4Add                         Mat4AddAsm
#define Mat4AddFloat                    Mat4AddFloatAsm
#define Mat4AddMatrix                   Mat4AddMatrixAsm
#define Mat4Subtract                    Mat4SubtractAsm
#define Mat4SubtractFloat               Mat4SubtractFloatAsm
#define Mat4SubtractMatrix              Mat4SubtractMatrixAsm
#define Mat4MultiplyMatrix              Mat4MultiplyMatrixAsm
#define Mat4Multiply                    Mat4MultiplyAsm
#define Mat4MultiplyVec                 Mat4MultiplyVecAsm

extern __C void Mat4NegateAsm        (mat4* r,const mat4* m);
extern __C void Mat4NegateMatrixAsm  (mat4* r);
extern __C void Mat4AddAsm           (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4AddFloatAsm      (mat4* r,const mat4* m,const float s);
extern __C void Mat4AddMatrixAsm     (mat4* m,const mat4* n);
extern __C void Mat4SubtractAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4SubtractFloatAsm (mat4* r,const mat4* m,const float s);
extern __C void Mat4SubtractMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4MultiplyMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4MultiplyAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4MultiplyVecAsm   (vec4* r,const mat4* m,const vec4* v);

#define Mat4MultiplyFloat               Mat4MultiplyFloatAsm
#define Mat4Transpose                   Mat4TransposeAsm
#define Mat4ShadowMatrix                Mat4ShadowMatrixAsm
#define Mat4MirrorMatrix                Mat4MirrorMatrixAsm
#define Mat4LookAt                      Mat4LookAtAsm
#define Mat4GlToD3DProjMat              Mat4GlToD3DProjMatAsm
#define Mat4LookAtLH                    Mat4LookAtLHAsm

extern __C void Mat4MultiplyFloatAsm (mat4* r,const mat4* m,const float x);
extern __C void Mat4TransposeAsm     (mat4* r,const mat4* m);
extern __C void Mat4ShadowMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset,const vec3* lightPos);
extern __C void Mat4MirrorMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset);
extern __C void Mat4LookAtAsm        (mat4* r,const vec3* from,const vec3* at);
extern __C void Mat4GlToD3DProjMatAsm(mat4* r,const mat4* m);
extern __C void Mat4LookAtLHAsm      (mat4* r,const vec3* pEye,const vec3* pLookAt,const vec3* pUp);

#define Mat4uMultiply                   Mat4uMultiplyAsm
#define Mat4uMultiplyVec                Mat4uMultiplyVecAsm
#define Mat4uLookAt                     Mat4uLookAtAsm

extern __C void Mat4uMultiplyAsm    (mat4* m,const mat4* n);
extern __C void Mat4uMultiplyVecAsm (vec4* r,const mat4* m,const vec4* v);
extern __C void Mat4uLookAtAsm      (mat4* r,const vec3* from,const vec3* at);

#define Mat4saLookAt                    Mat4saLookAtAsm
#define Mat4suLookAt                    Mat4suLookAtAsm

extern __C void Mat4saLookAtAsm     (mat4* r,const vec3* from,const vec3* at);
extern __C void Mat4suLookAtAsm     (mat4* r,const vec3* from,const vec3* at);

#define Mat4uNegate                     Mat4uNegateAsm
#define Mat4uNegateMatrix               Mat4uNegateMatrixAsm
#define Mat4uAdd                        Mat4uAddAsm
#define Mat4uAddFloat                   Mat4uAddFloatAsm
#define Mat4uAddMatrix                  Mat4uAddMatrixAsm
#define Mat4uSubtract                   Mat4uSubtractAsm
#define Mat4uSubtractFloat              Mat4uSubtractFloatAsm
#define Mat4uSubtractMatrix             Mat4uSubtractMatrixAsm
#define Mat4uMultiplyMatrix             Mat4uMultiplyMatrixAsm

extern __C void Mat4uNegateAsm        (mat4* r,const mat4* m);
extern __C void Mat4uNegateMatrixAsm  (mat4* r);
extern __C void Mat4uAddAsm           (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uAddFloatAsm      (mat4* r,const mat4* m,const float s);
extern __C void Mat4uAddMatrixAsm     (mat4* m,const mat4* n);
extern __C void Mat4uSubtractAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uSubtractFloatAsm (mat4* r,const mat4* m,const float s);
extern __C void Mat4uSubtractMatrixAsm(mat4* m,const mat4* n);
extern __C void Mat4uMultiplyMatrixAsm(mat4* m,const mat4* n);

#define Mat4uMultiply                   Mat4uMultiplyAsm
#define Mat4uMultiplyVec                Mat4uMultiplyVecAsm

extern __C void Mat4uMultiplyAsm      (mat4* r,const mat4* m,const mat4* n);
extern __C void Mat4uMultiplyVecAsm   (vec4* r,const mat4* m,const vec4* v);

#define Mat4uMultiplyFloat              Mat4uMultiplyFloatAsm
#define Mat4uTranspose                  Mat4uTransposeAsm
#define Mat4uShadowMatrix               Mat4uShadowMatrixAsm
#define Mat4uMirrorMatrix               Mat4uMirrorMatrixAsm
#define Mat4uLookAt                     Mat4uLookAtAsm
#define Mat4uGlToD3DProjMat             Mat4uGlToD3DProjMatAsm
#define Mat4uLookAtLH                   Mat4uLookAtLHAsm

extern __C void Mat4uMultiplyFloatAsm (mat4* r,const mat4* m,const float x);
extern __C void Mat4uTransposeAsm     (mat4* r,const mat4* m);
extern __C void Mat4uShadowMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset,const vec3* lightPos);
extern __C void Mat4uMirrorMatrixAsm  (mat4* r,const vec3* planeNormal,const float planeOffset);
extern __C void Mat4uLookAtAsm        (mat4* r,const vec3* from,const vec3* at);
extern __C void Mat4uGlToD3DProjMatAsm(mat4* r,const mat4* m);
extern __C void Mat4uLookAtLHAsm      (mat4* r,const vec3* pEye,const vec3* pLookAt,const vec3* pUp);

#define Mat4Identity                    Mat4IdentityAsm
#define Mat4Scale                       Mat4ScaleAsm

extern __C void Mat4IdentityAsm(mat4* r);
extern __C void Mat4ScaleAsm   (mat4* r,const float x_scale,const float y_scale,const float z_scale);

#define Mat4RotateRHX                   Mat4RotateRHX_Asm
#define Mat4RotateLHX                   Mat4RotateLHX_Asm
#define Mat4RotateRHY                   Mat4RotateRHY_Asm
#define Mat4RotateLHY                   Mat4RotateLHY_Asm
#define Mat4RotateRHZ                   Mat4RotateRHZ_Asm
#define Mat4RotateLHZ                   Mat4RotateLHZ_Asm

extern __C void Mat4RotateRHX_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHX_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateRHY_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHY_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateRHZ_Asm  (mat4* r,const float angle);
extern __C void Mat4RotateLHZ_Asm  (mat4* r,const float angle);

#define Mat4RotateRHXY                  Mat4RotateRHXY_Asm
#define Mat4RotateLHXY                  Mat4RotateLHXY_Asm
#define Mat4RotateRHXZ                  Mat4RotateRHXZ_Asm
#define Mat4RotateLHXZ                  Mat4RotateLHXZ_Asm
#define Mat4RotateRHYZ                  Mat4RotateRHYZ_Asm
#define Mat4RotateLHYZ                  Mat4RotateLHYZ_Asm

extern __C void Mat4RotateRHXY_Asm (mat4* r,const float x_scale,const float y_scale);
extern __C void Mat4RotateLHXY_Asm (mat4* r,const float x,const float y);
extern __C void Mat4RotateRHXZ_Asm (mat4* m,const float x,const float z);
extern __C void Mat4RotateLHXZ_Asm (mat4* m,const float x,const float z);
extern __C void Mat4RotateRHYZ_Asm (mat4* r,const float y,const float z);
extern __C void Mat4RotateLHYZ_Asm (mat4* m,const float y,const float z);

#define Mat4RotateRHXYZ                 Mat4RotateRHXYZ_Asm
#define Mat4RotateLHXYZ                 Mat4RotateLHXYZ_Asm

extern __C void Mat4RotateRHXYZ_Asm(mat4* r,const float x,const float y,const float z);
extern __C void Mat4RotateLHXYZ_Asm(mat4* r,const float x,const float y,const float z);

#define Mat4TranslateRH                 Mat4TranslateRH_Asm
#define Mat4TranslateLH                 Mat4TranslateLH_Asm
#define Mat4TranslateRH_Vec3            Mat4TranslateRH_Vec3Asm
#define Mat4TranslateLH_Vec3            Mat4TranslateLH_Vec3Asm
#define Mat4TranslateRH_Vec4            Mat4TranslateRH_Vec4Asm
#define Mat4TranslateLH_Vec4            Mat4TranslateLH_Vec4Asm

extern __C void Mat4TranslateRH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateLH_Asm     (mat4* r,const float x,const float y,const float z);
extern __C void Mat4TranslateRH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateLH_Vec3Asm (mat4* r,const vec3* v);
extern __C void Mat4TranslateRH_Vec4Asm (mat4* r,const vec4* v);
extern __C void Mat4TranslateLH_Vec4Asm (mat4* r,const vec4* v);

#define Mat4OrthoMatrix                 Mat4OrthoMatrixAsm
#define Mat4OrthoStruct                 Mat4OrthoStructAsm
#define Mat4Perspective                 Mat4PerspectiveAsm
#define Mat4PerspectiveX                Mat4PerspectiveXAsm
#define Mat4CubemapMatrix               Mat4CubemapMatrixAsm
#define Mat4CubemapProjectionMat        Mat4CubemapProjectionMatAsm
// #define Mat4LookAtHoriz                 Mat4LookAtHorizAsm

extern __C void Mat4OrthoMatrixAsm(mat4*         r,
                                   const float   left,
                                   const float   right,
                                   const float   top,
                                   const float   bottom,
                                   const float   zNear,
                                   const float   zFar,
                                   const int32_t d3dFlag);
extern __C void Mat4OrthoStructAsm(mat4* r,const orthoMatrix* s);

extern __C void Mat4PerspectiveAsm (mat4*          r,
                                    const float    fov,
                                    const float    width,
                                    const float    height,
                                    const float    zNear,
                                    const float    zFar,
                                    const uint32_t d3dflag);
extern __C void Mat4PerspectiveXAsm(mat4* r,const struct perspectiveMatrix* s);

extern __C void Mat4CubemapMatrixAsm(mat4* r,const unsigned int face);
extern __C void Mat4CubemapProjectionMatAsm(mat4* r,const float zNear,const float zFar,const uint32_t d3dflag);

#define Mat3RotationFromMat4            Mat3RotationFromMat4Asm
#define Mat4FromMat3                    Mat4FromMat3Asm

extern __C void Mat3RotationFromMat4Asm    (mat3* r,const mat4* m);
extern __C void Mat4FromMat3Asm            (mat4* r,const mat3* m);

#define QuaternionAdd                   QuaternionAddAsm
#define QuaternionMultiply              QuaternionMultiplyAsm
#define QuaternionInverse               QuaternionInverseAsm
#define QuaternionToMat3                QuaternionToMat3Asm
#define QuaternionToMat4                QuaternionToMat4Asm

extern __C void QuaternionAddAsm     (quaternion* r,const quaternion* q,const quaternion* v);
extern __C void QuaternionMultiplyAsm(quaternion*r,const quaternion* u,const quaternion* v);
extern __C void QuaternionInverseAsm (quaternion* r,const quaternion* q);
extern __C void QuaternionToMat3Asm  (mat3* r,const quaternion* q);
extern __C void QuaternionToMat4Asm  (mat4* m,const quaternion* q);

#define QuaternionNormalizeFlat         QuaternionNormalizeFlatAsm
#define QuaternionDotFlat               QuaternionDotFlatAsm

extern __C void QuaternionNormalizeFlatAsm(quaternion* r,const quaternion* q);
extern __C void QuaternionDotFlatAsm      (float* r,const quaternion* q,const quaternion* v);

#define QuaternionNormalize             QuaternionNormalizeAsm
#define QuaternionDot                   QuaternionDotAsm
#define QuaternionDotFPU                QuaternionDotFPU_Asm

extern __C void QuaternionNormalizeAsm(quaternion* r,const quaternion* q);
extern __C void QuaternionDotAsm      (float* r,const quaternion* q,const quaternion* v);
extern __C void QuaternionDotFPU_Asm  (float* r,const quaternion* q,const quaternion* v);

#define uQuaternionAdd                  uQuaternionAddAsm
#define uQuaternionMultiply             uQuaternionMultiplyAsm
#define uQuaternionInverse              uQuaternionInverseAsm
#define uQuaternionToMat3               uQuaternionToMat3Asm
#define uQuaternionToMat4               uQuaternionToMat4Asm

extern __C void uQuaternionAddAsm     (quaternion* r,const quaternion* q,const quaternion* v);
extern __C void uQuaternionMultiplyAsm(quaternion*r,const quaternion* u,const quaternion* v);
extern __C void uQuaternionInverseAsm (quaternion* r,const quaternion* q);
extern __C void uQuaternionToMat3Asm  (mat3* r,const quaternion* q);
extern __C void uQuaternionToMat4Asm  (mat4* r,const quaternion* q);

#define uQuaternionNormalizeFlat        uQuaternionNormalizeFlatAsm
#define uQuaternionDotFlat              uQuaternionDotFlatAsm

extern __C void uQuaternionNormalizeFlatAsm(quaternion* r,const quaternion* q);
extern __C void uQuaternionDotFlatAsm      (float* r,const quaternion* q,const quaternion* v);

#define uQuaternionNormalize            uQuaternionNormalizeAsm
#define uQuaternionDot                  uQuaternionDotAsm

extern __C void uQuaternionNormalizeAsm    (quaternion* r,const quaternion* q);
extern __C void uQuaternionDotFlatAsm      (float* r,const quaternion* q,const quaternion* v);

#define QuaternionFromAxis              QuaternionFromAxisAsm
#define QuaternionFromMat3              QuaternionFromMat3Asm
#define QuaternionFromMat4              QuaternionFromMat4Asm
#define QuaternionSlerp                 QuaternionSlerpAsm
#define QuaternionCos                   QuaternionCosAsm
#define QuaternionSin                   QuaternionSinAsm

// #define Mat4LookAtHoriz                 Mat4LookAtHorizAsm

extern __C void QuaternionFromAxisAsm(quaternion* r,const vec3* v,const float angle);
extern __C void QuaternionFromMat3Asm(quaternion* r,const mat3* m);
extern __C void QuaternionFromMat4Asm(quaternion* r,const mat4* m);
extern __C void QuaternionSlerpAsm   (quaternion* r,const float s,const quaternion* q,const quaternion* v);
extern __C void QuaternionCosAsm     (float* r,const quaternion* q,const quaternion* p);
extern __C void QuaternionSinAsm     (float* r,const quaternion* q,const quaternion* p);
#endif

#endif
