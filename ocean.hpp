#ifndef OCEAN_HPP_
#define OCEAN_HPP_

#include "object.h"
#include <vector>
#include <utility>
#include <map>
template <typename T>
class Singleton {
public:
    static T& Instance() {
        static T instance = T();
        return instance;
    }
protected:
    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton&);  // shouldn't be used
    Singleton& operator=(const Singleton&);   // shouldn't be used
};


/*!
 * Factory pattern (?).
 */
 using std::vector;
 using std::pair;
 using std::map;
class Ocean : public Singleton<Ocean> {
public:
    /*!
      * Return pointer to the object located by coordinates (i, j) if any
      * or NULL pointer otherwise
      */
    Object* GetObject(int i, int j){
      return inhabitants[i][j];
    }

    Object* GetObject(std::pair<int, int> coords) {
        return GetObject(coords.first, coords.second);
    }

    void SetSize(int width, int height){
      if(width > 0 && height > 0){
        inhabitants = vector<vector<Object *> >(width, vector<Object *>(height, (Object*)NULL ));
        this-> width = width;
        this-> height = height;
        Draw();
        std::cout << "setsize draw\n";
      }
    }

    void TicTac(){
    map<Object *, bool> acted_objects;
      for(int i = 0; i < width; ++i)
        for(int j = 0; j < height; ++j)
          if(inhabitants[i][j] != NULL && !acted_objects[inhabitants[i][j]]){
            acted_objects[inhabitants[i][j]] = true;
            inhabitants[i][j]->Act();
          }
    }

    Object* operator()(int i, int j) { return GetObject(i, j); }
    /*!
      * Create new object of type t under the coordinates (i, j). Return
      * false if operation fails.
      */
    bool CreateNewObject(ObjectType t, int i, int j){
      if(inhabitants[i][j] != NULL)
        return false;
      switch (t){
        case  HUNTER : {
          inhabitants[i][j] = new Hunter(i,j);
          break;
        }
        case PREY : {
          inhabitants[i][j] = new Prey(i,j);
          break;
        }
        case OBSTACLE : {
          inhabitants[i][j] = new Obstacle(i,j);
          break;
        }
        default : {
          return false;
        }
      }
      Draw();
      std::cout << "create draw\n";
      return true;
    }

    bool CreateNewObject(ObjectType t, std::pair<int, int> coords) {
        return CreateNewObject(t, coords.first, coords.second);
    }

    /*!
      * Delete object under the coordinates (i, j) (if any). Return
      * false if operation fails.
      */
    bool DeleteObject(int i, int j){
      if(inhabitants[i][j] == NULL)
        return false;
      delete inhabitants[i][j];
      inhabitants[i][j] = NULL;
      Draw();
      std::cout << "delete draw\n";
      return true;
    }

    bool DeleteObject(std::pair<int, int> coords) {
        return DeleteObject(coords.first, coords.second);
    }

    /*!
      * Move object to the coordinates (i, j). Return false if operation fails.
      */

    bool MoveObject(Object* obj, int i, int j){
      if(inhabitants[i][j] != NULL || i < 0 || i >= width || j < 0 || j >= height )
        return false;
      pair<int,int> coords = obj->GetCoords();
      if (i == coords.first && j == coords.second)
        return true;
      std::swap(inhabitants[coords.first][coords.second], inhabitants[i][j]);
      Draw();
      std::cout << "move draw\n";
      return true;
    }

    bool MoveObject(Object* obj, std::pair<int, int> coords) {
        return MoveObject(obj, coords.first, coords.second);
    }

    void Draw(){
      //static bool printed = false;
      for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
          //if(printed)
            //std::cout << "\b";
          if(inhabitants[j][i] != NULL)
            inhabitants[j][i]->PrintSelf();
          else
            std::cout << ' ';
        }
        //if(printed)
          //std::cout << "\b";
        std::cout << '|' <<std::endl;
      }
      for(int i = 0; i < width; ++i)
        std::cout << '-';
      std::cout << std::endl;
      //printed = true;
    }
private:
    vector<vector<Object *> > inhabitants;
    int width;
    int height;
    Ocean() {}
    friend class Singleton<Ocean>;
};

#endif // OCEAN_HPP_
