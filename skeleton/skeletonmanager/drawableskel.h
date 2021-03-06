#ifndef DRAWABLESKEL_H
#define DRAWABLESKEL_H


#include "iostream"
#include "fstream"
#include "common/trischar.h"
#include "viewer/interfaces/drawable_object.h"
#include "viewer/interfaces/drawable_mesh.h"
#include "viewer/objects/objects.h"
#include "viewer/mainwindow.h"
#include "skel.h"

#include <QColor>
#include "skeleton/compacttrisonboarders.h"
#include "skeleton/skeletoncreator.h"
#include "trimesh/trimesh.h"
#include "trimesh/load_save_trimesh.h"
#include <algorithm>


class DrawableSkel : public DrawableMesh,
                     public Trimesh<double>
{
    public:

        const int TID_ELIM = -5;


        DrawableSkel();
        DrawableSkel(const char* file_name);
        DrawableSkel(const char* file_name, int compressions, double trashold);
        DrawableSkel(const char* file_name, int compressions, double trashold, int test_Value);
        DrawableSkel(const Skel *skel);

        ~DrawableSkel();
        // Implementation of the
        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const ;
        double sceneRadius() const ;

        bool isVisible() const;
        void init();
        void compressSkeletonUntilConverge();
        void compressSkeletonUntilConverge(int numTris2BeDeleted);



   protected:

        //std::list<Pointd> vtx_list;
        std::list<std::pair<Pointd, Pointd>> edge_list;
        const Skel* skeleton;
        MainWindow* mainWindow;
        DrawableTrimesh* trimesh;
        DrawableSkel* dsk;
        double triTrashold;


        void setEdgeList(std::list<std::pair<Pointd, Pointd>> edges);
        static bool isTrisOnBorder(Pointd a, Pointd b, Pointd c, double trasholdAngle);
        static bool isTrisOnBorder2(Pointd a, Pointd b, Pointd c, double trasholdAngle);
        static bool isTrisOnBorder3(Pointd a, Pointd b, Pointd c, double trasholdAngle);
        bool mergeTwoVertexes(int tid);
        bool mergeTwoVertexes(int tid, Pointd a, Pointd b);
        bool shiftTriangleList();
        bool shiftTriangleList(int tid);
        bool deleteTriangle(int tid);
        int minDistanceBetweenThreePoints(Pointd a, Pointd b, Pointd c);
        bool hasTidThisTwoVertexes(int tid, Pointd a, Pointd b);
        bool deleteVTX(int vid, int vid0);
        bool updateDeletedTriNeighbours(int tid, int NeighTid);

   private:
       std::ofstream logPietro;
       std::string pathToDesktop = "/home/pietro/Desktop/log.txt";


};

#endif // DRAWABLESKEL_H
