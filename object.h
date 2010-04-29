#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>

const int DEFAULT_TIME_TO_REPRODUCE = 10;
const int DEFAULT_TIME_TO_DIE = 5;

enum ObjectType {
    PREY,
    HUNTER,
    OBSTACLE
};

class Prey;
class Hunter;

class Object {
public:
    /*!
      * Perform some action (die / reproduce itself / move / eat somebody)
      */
    virtual void Act() = 0;
    /*!
      * Interaction of 2 objects. Multiple dispatch idiom (pattern visitor).
      * Return true if this Object is happpy after interacting with obj
      * (e.g. hunter eats prey).
      */
    virtual bool Interact(Object* obj) = 0;
    /*!
      * Utility function needed for multiple dispatch.
      * Return true if p is happy.
      */
    virtual bool Dispatch(Prey& p) = 0;
    /*!
      * Utility function needed for multiple dispatch.
      * Return true if h is happy.
      */
    virtual bool Dispatch(Hunter& h) = 0;
    /*!
     * Print special symbol wich helps to visualize this object
     */
    virtual void PrintSelf() const = 0;
    std::pair<int, int> GetCoords() const { return std::make_pair(x_, y_); }
protected:
    Object(int x = 0, int y = 0) : x_(x), y_(y) {}
    Object(const Object&);  // shouldn't be used
    Object& operator=(const Object&);   // shouldn't be used
    virtual ~Object() {}


    int x_;
    int y_;
private:
    friend class Ocean;
};

class Prey : public Object {
public:

    virtual void Act();
    virtual bool Interact(Object* obj) { return obj->Dispatch(*this); }
    virtual bool Dispatch(Prey& p);
    virtual bool Dispatch(Hunter& h);
    virtual void PrintSelf() const { std::cout << "P"; }
protected:
    Prey(int x = 0, int y = 0,
         int time_to_reproduce = DEFAULT_TIME_TO_REPRODUCE)
        : Object(x, y),
        time_to_reproduce_(time_to_reproduce),
        time_to_reproduce_left_(time_to_reproduce) {}

private:
    friend class Object;
    friend class Ocean;
    int time_to_reproduce_left_;
    const int time_to_reproduce_;
};

class Hunter : public Object {
public:
    virtual void Act();
    virtual bool Interact(Object* obj) { return obj->Dispatch(*this); }
    virtual bool Dispatch(Prey& p);
    virtual bool Dispatch(Hunter& h);
    virtual void PrintSelf() const { std::cout << "H"; }
protected:
    Hunter(int x = 0, int y = 0,
           int time_to_reproduce = DEFAULT_TIME_TO_REPRODUCE,
           int time_to_die = DEFAULT_TIME_TO_DIE)
        : Object(x, y),
        time_to_reproduce_(time_to_reproduce),
        time_to_reproduce_left_(time_to_reproduce),
        time_to_die_(time_to_die),
        time_to_die_left_(time_to_die) {}
private:
    int time_to_reproduce_left_;
    const int time_to_reproduce_;
   
    friend class Ocean;
    int time_to_die_left_;
    const int time_to_die_;
};

class Obstacle : public Object {
public:
    virtual void Act() {}
    virtual bool Interact(Object* /* obj */) { return false; }
    virtual bool Dispatch(Prey& /* p */);
    virtual bool Dispatch(Hunter& /* h */);
    virtual void PrintSelf() const { std::cout << "*"; }
protected:
    Obstacle(int x = 0, int y = 0) : Object(x, y) {}

    friend class Ocean;
};

#endif // OBJECT_H_
