#ifndef OCEAN_HPP_
#define OCEAN_HPP_

#include "object.h"

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
class Ocean : public Singleton<Ocean> {
public:
    /*!
      * Return pointer to the object located by coordinates (i, j) if any
      * or NULL pointer otherwise
      */
    Object* GetObject(int i, int j);
    Object* GetObject(std::pair<int, int> coords) {
        return GetObject(coords.first, coords.second);
    }

    Object* operator()(int i, int j) { return GetObject(i, j); }
    /*!
      * Create new object of type t under the coordinates (i, j). Return
      * false if operation fails.
      */
    bool CreateNewObject(ObjectType t, int i, int j);
    bool CreateNewObject(ObjectType t, std::pair<int, int> coords) {
        return CreateNewObject(t, coords.first, coords.second);
    }

    /*!
      * Delete object under the coordinates (i, j) (if any). Return
      * false if operation fails.
      */
    bool DeleteObject(int i, int j);
    bool DeleteObject(std::pair<int, int> coords) {
        return DeleteObject(coords.first, coords.second);
    }

    /*!
      * Move object to the coordinates (i, j). Return false if operation fails.
      */
    bool MoveObject(Object* obj, int i, int j);
    bool MoveObject(Object* obj, std::pair<int, int> coords) {
        return MoveObject(obj, coords.first, coords.second);
    }

private:
    Ocean() {}
    friend class Singleton<Ocean>;
};

#endif // OCEAN_HPP_
