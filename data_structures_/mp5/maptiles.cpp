/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     int rows=theSource.getRows();                  /*set the rows and columns*/
     int cols=theSource.getColumns();
     MosaicCanvas* canvasptr=new MosaicCanvas(rows, cols);    /*create a canvas*/
     vector <Point<3> > pixel;                            /*create a Point vector*/
     map <Point<3>, int> index;                           /*create map vector*/

     for(size_t i=0; i<theTiles.size(); i++){         /*calculate the average color*/
       HSLAPixel temp=theTiles[i].getAverageColor();  /*and push back the h,s, and l values*/
       Point<3> temp_point=convertToLAB(temp);
       pixel.push_back(temp_point);
     }

     for(size_t i=0; i<pixel.size(); i++){            /*initialize the index*/
       index[pixel[i]]=i;
     }

     KDTree <3> thetree(pixel);                       /*set the tree vector*/
     for(int i=0; i<rows; i++){                  /*for each rows and columns*/
       for(int j=0; j<cols; j++){                /*call the helper function*/
        TileImage *theimage=get_match_at_idx(thetree, index, theTiles, theSource, i, j);
        canvasptr->setTile(i, j, theimage);      /*set tile for the row and column with the image*/
       }
     }
    return canvasptr;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
