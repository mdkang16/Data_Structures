/* Your code here! */
#include "maze.h"
using namespace std;

//no-parameter constructor
SquareMaze::SquareMaze(){
   h = w = 0;                 //set width and height to 0;
}
void SquareMaze::makeMaze(int width, int height){
   w = width;
   h = height;
   int down_ad, right_ad;
   DisjointSets dsets;
   dsets.addelements(w*h);            //add disjoint sets elements
   vector<int> cell;
   for(int i = 0; i < w*h; i++){      //initialize each square cell
      cell.push_back(i);
   }
   for(int i = 0; i < w*h; i++){      //randomize
      int temp = rand() % (w*h);
      int celltemp = cell[i];
      cell[i] = cell[temp];
      cell[temp] = celltemp;
   }
   for(int i = 0; i < w*h; i ++){     //if walls=11, both walls exist
      walls[i] = 11;
   }
   srand(time(NULL));
   for(int i = 0; i < w*h; i++){      //check adjacent cells
      down_ad = cell[i] + w;
      right_ad = cell[i] + 1;
      if( right_ad%w == 0){           //cell is on the last col
         right_ad = -1;
      }
      if(right_ad> -1){               //else, if not in the same set, union them
         if(dsets.find(cell[i]) != dsets.find(right_ad)){
            dsets.setunion(cell[i], right_ad);
            walls[cell[i]] = walls[cell[i]] - 10;   //walls=1 means no right wall
         }
      }

      if(down_ad > w*h-1){            //cell is out of bound
         down_ad = -1;
      }
      if(down_ad> -1){                //else, if not in the same set, union them
         if(dsets.find(cell[i]) != dsets.find(down_ad)){
            dsets.setunion(cell[i], down_ad);
            walls[cell[i]] = walls[cell[i]] - 1;      //walls=10 means no down wall
         }
      }
   }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
   int currcell= walls.at(y*w+x);
   if(dir == 0){                              //move right
      if(x == w - 1 || currcell >= 10){      //if last column or right wall exists
         return false;
      }
   }
   else if(dir == 1){                           //move down
      if(y == h-1 || currcell%10 == 1){        //last row or down wall exists
         return false;
      }
   }
   else if(dir == 2){                                     //move left
      if(x == 0 || walls.at(y*w + x - 1) >= 10){          //first column or left wall exists
         return false;
      }
   }
   else if(dir==3){                                        //move up
      if(y == 0 || walls.at((y-1)*w+x) % 10 == 1){        //first row or up wall exists
         return false;
      }
   }
   return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
   if(exists==true){
      if(dir == 0){                                //setup right wall
         walls[y*w+x] = (walls[y*w+x]%10)+10;
      }
      else if(dir == 1){                           //setup down wall
         walls[y*w+x] = (walls[y*w+x]/10)*10+1;
      }
   }
   else if(exists==false){
      if(dir == 0){                          //no right wall. remove right wall
         walls[y*w+x] = walls[y*w+x]%10;
      }
      else if(dir==1){                       //no down wall. remove down wall
         walls[y*w+x] = (walls[y*w+x]/10)*10;
      }
   }
}

vector<int> SquareMaze::solveMaze(){
   std::queue<int> q;
   q.push(0);
   vector<int> path;
   vector<int> val;
   int currval;
   int length = 0;
   int current = 0;
   int *visited  = new int[w*h];
   int *distance = new int[w*h];
   int *parent = new int[w*h];
   distance[0] = 0;
   parent[0] = -1;
   for(int i =0; i <w*h; i++){   //initialize visited as 0
      visited[i]=0;
   }
   while(!q.empty()){
      currval = q.front();
      q.pop();
      if(canTravel(currval%w, currval/w, 0)==true){   //travel right
        if(visited[currval+1]==0){                    //if not visited
          q.push(currval+1);                          //push in value
          parent[currval+1] = currval;                //update parent
          visited[currval] = 1;                       //is visited
        }
      }

      if(canTravel(currval%w, currval/w, 1)==true){     // travel down
        if(visited[currval+w]==0){
          q.push(currval+w);
          parent[currval+w] = currval;
          visited[currval] = 1;
        }
      }

      if(canTravel(currval%w, currval/w, 2)==true){     //travel left
        if(visited[currval-1] == 0){
          q.push(currval-1);
          parent[currval-1] = currval;
          visited[currval] = 1;
        }
      }

      if(canTravel(currval%w, currval/w, 3)==true){     //travel up
        if(visited[currval-w] == 0){
          q.push(currval-w);
          parent[currval-w] = currval;
          visited[currval] = 1;
        }
      }
      if(currval != 0){                           //update distance
        distance[currval] = distance[parent[currval]]+1;
      }
    }

   for(int i = 0; i < w; i ++){             //find the longest path
      if(distance[w*(h-1)+i] > length){
         length = distance[w*(h-1)+i];
         current = i;
      }
   }

   int fin = current+w*(h-1);               //find the final destination
   endpt = fin;
   while(length > 0){
      if(parent[fin] == fin-1){           //move left to right
         val.push_back(0);
      }
      if(parent[fin] == fin-w){           //move down
         val.push_back(1);
      }
      if(parent[fin] == fin+1){          //move right to left
         val.push_back(2);
      }
      if(parent[fin] == fin+w){          //move up
         val.push_back(3);
      }
      length--;
      fin = parent[fin];
   }
   for(unsigned int i = val.size()-1; i!=0; i--){
      path.push_back(val[i]);         //push the path in order
   }
   path.push_back(val[0]);
   return path;

   delete visited;                    //free
   visited=NULL;
   delete parent;
   parent=NULL;
   delete distance;
   distance=NULL;
}

PNG *SquareMaze::drawMaze() const{
   PNG *unsolved = new PNG(w*10+1, h*10+1);

   for(int i = 10; i < w*10+1; i++){     //blacken (10,0) to (w*10+1, 0)
      unsolved->getPixel(i, 0).h = 0;
      unsolved->getPixel(i, 0).s = 0;
      unsolved->getPixel(i, 0).l = 0;
      unsolved->getPixel(i, 0).a = 1;
   }

   for(int i = 0; i < h*10+1; i++){     //blacken leftmost
      unsolved->getPixel(0, i).h = 0;
      unsolved->getPixel(0, i).s = 0;
      unsolved->getPixel(0, i).l = 0;
      unsolved->getPixel(0, i).a = 1;
   }

   for (auto it = walls.begin(); it!=walls.end(); it++){
     int x = it->first % w;         //get the coordinates x and y
     int y = it->first / w;
     if(it->second >= 10){
       for(int k=0; k<=10; k++){      //right wall exists, blacken
         unsolved->getPixel((x+1) * 10, (y*10) +k).h = 0;
         unsolved->getPixel((x+1) * 10, (y*10) +k).s = 0;
         unsolved->getPixel((x+1) * 10, (y*10) +k).l = 0;
         unsolved->getPixel((x+1) * 10, (y*10) +k).a = 1;
       }
     }

     if(it->second %10==1){           //bottom wall exists, blacken
       for(int k=0; k<=10; k++){
         unsolved->getPixel(x*10+k, (y+1) * 10).h = 0;
         unsolved->getPixel(x*10+k, (y+1) * 10).s = 0;
         unsolved->getPixel(x*10+k, (y+1) * 10).l = 0;
         unsolved->getPixel(x*10+k, (y+1) * 10).a = 1;
       }
     }
   }
   return unsolved;
}

PNG *SquareMaze::drawMazeWithSolution(){
   PNG *solved = drawMaze();
   vector<int> answer = solveMaze();
   int i = 5;                                 //set the starting pixel
   int j = 5;

   for(unsigned int k = 0; k < answer.size(); k ++){
      if(answer[k] == 0){                   //color pixels red
         for( int z = 0; z <= 10; z ++){
            solved->getPixel(i+z, j).h = 0;
            solved->getPixel(i+z, j).s = 1;
            solved->getPixel(i+z, j).l = 0.5;
            solved->getPixel(i+z, j).a = 1;
         }
         i+=10;
      }

      else if(answer[k] == 1){
         for(int z = 0; z <= 10; z++){
            solved->getPixel(i, j+z).h = 0;
            solved->getPixel(i, j+z).s = 1;
            solved->getPixel(i, j+z).l = 0.5;
            solved->getPixel(i, j+z).a = 1;
         }
         j+=10;
      }

      else if(answer[k] == 2){
         for(int z = 0; z <= 10; z++){
            solved->getPixel(i-z, j).h = 0;
            solved->getPixel(i-z, j).s = 1;
            solved->getPixel(i-z, j).l = 0.5;
            solved->getPixel(i-z, j).a = 1;
         }
         i-=10;
      }

      else if(answer[k] == 3){
         for(int z = 0; z <= 10; z++){
            solved->getPixel(i, j-z).h = 0;
            solved->getPixel(i, j-z).s = 1;
            solved->getPixel(i, j-z).l = 0.5;
            solved->getPixel(i, j-z).a = 1;
         }
         j-=10;
      }
   }
   int x = i/10;
   int y = h-1;
   for(int k = 1; k < 10; k++){                   //make exit, whiten
      solved->getPixel(x*10+ k, (y+1)*10).h = 0;
      solved->getPixel(x*10+ k, (y+1)*10).s = 0;
      solved->getPixel(x*10+ k, (y+1)*10).l = 1;
      solved->getPixel(x*10+ k, (y+1)*10).a = 1;
   }
   return solved;
}

void SquareMaze::makenewmaze(int width, int height){
   w = width;
   h = height;
   DisjointSets dsets;
   dsets.addelements(w*h);
   vector<int> cell;
   for(int i = 0; i < w*h; i++){
      cell.push_back(i);
   }
   for(int i = 0; i < w*h; i++){
      int r = rand() % (w*h);
      int celltemp = cell[i];
      cell[i] = cell[r];
      cell[r] = celltemp;
   }
   for(int i=0; i<30; i++){       //set where walls will exist
     for(int j=0; j<w-i; j++){
       walls[w*i+j]=11;
     }
   }
   srand(time(NULL));
   for(int i = 0; i < w*h; i++){
      int down_ad = cell[i] + w;
      int right_ad = cell[i] + 1;

      if( right_ad%w == 0){
         right_ad = -1;
      }
      if(down_ad > w*h-1){
         down_ad = -1;
      }

      if(right_ad> -1){
         if(dsets.find(cell[i]) != dsets.find(right_ad)){
            dsets.setunion(cell[i], right_ad);
            walls[cell[i]] = walls[cell[i]] - 10;
         }
      }

      if(down_ad> -1){
         if(dsets.find(cell[i]) != dsets.find(down_ad)){
            dsets.setunion(cell[i], down_ad);
            walls[cell[i]] = walls[cell[i]] - 1;
         }
      }
   }
}
