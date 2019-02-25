#include <NodeMap.h>

struct MeshPat;
typedef struct MeshPat MeshPattern;

struct MeshPat {
  int          iValue;
  MeshPattern* next;
};

MeshPattern pLhPattern0[] = {
  { 0, pLhPattern0+1 },
  { 1, pLhPattern0+2 },
  { 3, pLhPattern0+3 },
  { 2, pLhPattern0+1 },
};

MeshPattern pLhPattern1[] = {
  { 2, pLhPattern1+1 },
  { 1, pLhPattern1+2 },
  { 2, pLhPattern1+3 },
  { 2, pLhPattern1+4 },
  { 3, pLhPattern1+5 },
  { 1, pLhPattern1+6 },
  { 1, pLhPattern1+7 },
  { 3, pLhPattern1+8 },
  { 2, pLhPattern1+3 }
};

MeshPattern pLhPattern2[] = {
  { 2, pLhPattern2+1 },
  { 1, pLhPattern2+2 },
  { 3, pLhPattern2+3 },
  { 2, pLhPattern2+1 },
};

MeshPattern pLhPattern3[] = {
  { 2, pLhPattern3+1 },
  { 1, pLhPattern3+2 },
  { 2, pLhPattern3+3 },
  { 3, pLhPattern3+4 },
  { 1, pLhPattern3+2 }
};

MeshPattern* pLhPattern[] = {
  { pLhPattern0 },
  { pLhPattern1 },
  { pLhPattern2 },
  { pLhPattern3 },
};

typedef enum { Start, Low, High } StartPos;

struct PhasePat;
typedef struct PhasePat PhasePattern;

struct PhasePat {
  StartPos      ePhase;
  PhasePattern* next;
};

PhasePattern pPhasePattern[] = {
  { Start, pPhasePattern+1 },
  { Start, pPhasePattern+2 },
  { High,  pPhasePattern+3 },
  { Low,   pPhasePattern+4 },
  { Low,   pPhasePattern+5 },
  { Low,   pPhasePattern+6 },
  { High,  pPhasePattern+7 },
  { High,  pPhasePattern+8 },
  { High,  pPhasePattern+3 }
};

PhasePattern pPhaseEnd[] = {
  { Low,  pPhaseEnd+1 },
  { High, pPhaseEnd+2 },
  { High, pPhaseEnd   }
};

// Add the adjustments

PhasePattern* pPhaseList[] = {
  { pPhasePattern },
  { pPhaseEnd },
};


