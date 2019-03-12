#ifndef __NODE_MAP_H
#define __NODE_MAP_H

#include <CVector.h>

typedef struct {
  int   iWidth;
  int   iHeight;
  int   iNodeCount;
  int** ppNodeMap;
}NodeMap;

int LhRectNodeMap(NodeMap** ppNodeMap,int iWidthSegments,int iHeightSegments);
int RhRectNodeMap(NodeMap** ppNodeMap,int iWidthSegments,int iHeightSegments);

#endif
