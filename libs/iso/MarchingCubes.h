/*
Copyright (c) 2007, Michael Kazhdan
All rights reserved.

Contains modifications by Simon Fuhrmann, 2013.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer. Redistributions in binary form must reproduce
the above copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the distribution.

Neither the name of the Johns Hopkins University nor the names of its contributors
may be used to endorse or promote products derived from this software without specific
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.
*/

#ifndef MARCHING_CUBES_INCLUDED
#define MARCHING_CUBES_INCLUDED

#include <vector>
#include <string.h>

class Square
{
public:
    const static int CORNERS=4,EDGES=4;
    static int  CornerIndex			(const int& x,const int& y);
    static void FactorCornerIndex	(const int& idx,int& x,int& y);
    static void FactorEdgeIndex		(const int& idx,int& orientation,int& i);

    static void EdgeCorners(const int& idx,int& c1,int &c2);
    static void OrientedEdgeCorners(const int& idx,int& c1,int &c2);
};

class Cube
{
public:
    const static int CORNERS=8,EDGES=12,FACES=6;

    static int  CornerIndex			(const int& x,const int& y,const int& z);
    static void FactorCornerIndex	(const int& idx,int& x,int& y,int& z);
    static int  EdgeIndex			(const int& orientation,const int& i,const int& j);
    static void FactorEdgeIndex		(const int& idx,int& orientation,int& i,int &j);
    static int  FaceIndex			(const int& dir,const int& offSet);
    static int  FaceIndex			(const int& x,const int& y,const int& z);
    static void FactorFaceIndex		(const int& idx,int& dir,int& offSet);

    static int  FaceReflectEdgeIndex	(const int& idx,const int& faceIndex);
    static int	EdgeReflectEdgeIndex	(const int& edgeIndex);

    static int  FaceAdjacentToEdges	(const int& eIndex1,const int& eIndex2);
    static void FacesAdjacentToEdge	(const int& eIndex,int& f1Index,int& f2Index);

    static void EdgeCorners(const int& idx,int& c1,int &c2);
    static void FaceCorners(const int& idx,int& c1,int &c2,int& c3,int& c4);

    static int SquareToCubeCorner(const int& fIndex,const int& cIndex);
    static int SquareToCubeEdge(const int& fIndex,const int& eIndex);
};

class MarchingSquares
{
public:
    struct FaceEdges
    {
        int count;
        std::pair<int,int> edge[2];
    };

private:
    static FaceEdges __caseTable[1<<(Square::CORNERS)];

public:
    static void SetCaseTable(void);
    static const FaceEdges& caseTable(const int& idx);
};

class MarchingCubes
{
    static void GetEdgeLoops(std::vector<std::pair<int,int> >& edges,std::vector<std::vector<int> >& loops);
    static std::vector< std::vector<int> > __caseTable[1<<Cube::CORNERS];

public:
    static void SetCaseTable(void);
    template<class Real>
    static int GetIndex(const Real values[Cube::CORNERS],const Real& iso);
    static const std::vector< std::vector<int> >& caseTable(const int& idx);
    static int HasRoots(const int& mcIndex);
    static int HasEdgeRoots(const int& mcIndex,const int& edgeIndex);
};

#include "MarchingCubes.inl"

#endif //MARCHING_CUBES_INCLUDED
