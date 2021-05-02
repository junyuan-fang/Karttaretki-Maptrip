// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <memory>

using  namespace std;

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate:Only used size() to return int. and its comlexity is O(1)
    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: because unordered_map's clear() is O(n)
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate:for-loop dominate the time
    std::vector<PlaceID> all_places();

    // Estimate of performance: in average theta(1),worst O(n)
    // Short rationale for estimate:complexity depends on unordered_map's find() and size(), and both are theta(1)
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: in average theta(1),Worst case: O(n)
    // Short rationale for estimate:complexity depends on unordered_map's find()
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: in average theta(1),Worst case: O(n)
    // Short rationale for estimate:complexity depends on unordered_map's find()
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: same as sort()'s complexity and unordered_map's find() in average is theta(1)
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate:same as sort()'s complexity and unordered_map's find() in average is theta(1)
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n*m)/ O(n)
    // Short rationale for estimate:m is string's length, because strings area shart so we assume m=constant
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: one for-loop
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance:in average theta(1),Worst case: O(n)
    // Short rationale for estimate:complexity depends on unordered_map's find(). Because we find it from datastructure then we change it
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: in average theta(1),Worst case: O(n)
    // Short rationale for estimate:complexity depends on unordered_map's find(). Because we find it from datastructure then we change it
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: in average theta(1),Worst case: O(n)
    // Short rationale for estimate:complexity depends on unordered_map's find() and insert()
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: in average theta(1),Worst case: O(n)
    // Short rationale for estimate:no for loop, and unordered_map's find() dominate the time
    Name get_area_name(AreaID id);

    // Estimate of performance: in average theta(1),Worst case: O(n)
    // Short rationale for estimate:no for loop, and unordered_map's find() dominate the
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:one for-loop for using push_back(), and pushback() is armortized theta(1)
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(n)
    // Short rationale for estimate:one for-loop for using push_back(), and pushback() is armortized theta(1)
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate:while-loop increase the time complexity
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance: O(1)
    // Short rationale for estimate:there we only change the "flag"'s value so is constant
    void creation_finished();

    // Estimate of performance: O(n)
    // Short rationale for estimate:Depth First Traversal is O(n + m), where n is the number of nodes, and m is the number of edges.
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: there was one for loop, and a sort() function in the for-loop. Should be O(n*mlog(m)), but m <=3 and it's small we assume it is a constant
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: in average theta(1), O(n)
    // Short rationale for estimate:because we only used unordered_map's erase()
    bool remove_place(PlaceID id);

    // Estimate of performance: O(n), but perftest's result is theta(1)
    // Short rationale for estimate: there are one while-loop inside anoter while-loop. it depends what kind of data we have. In worst case first one's and second one's while-loop size will be n-1, if data's size is n.
    // but our "return" will interupt it, so it will never be (n-1)^2 (except they do not have the common area)
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

private:
    //Place
    struct Place{
        PlaceID place_ID_;
        Name name_;
        PlaceType type_;
        Coord xy_;
    };
    unordered_map<PlaceID,Place> placeUnOrMap_;
    typedef unordered_map<PlaceID,Place>::iterator placeIter ;

    //Area
    struct Area{
        AreaID area_ID_;
        Name name_;
        vector<Coord> coords_;
        Area * parent_=nullptr;//Area* parent
        vector<Area*> subArea_;
    };
    unordered_map<AreaID,Area> areaUnOrMap_;
    typedef unordered_map<AreaID,Area>::iterator areaIter ;

    // Helping "all_subareas_in_area". Pre-order-tree-walk through subarea and add them to "vector<AreaID>:
    // Depth First Traversal is O(n + m), where n is the number of nodes, and m is the number of edges.
    void PRE_WALK_SUB(Area* recentArea, vector<AreaID>& ID);

    void PRE_WALK_COMMON(bool& flag,Area* recentArea, const AreaID id1, const AreaID id2, AreaID& might_common_areaID, AreaID &common_areaID);

    //Helping "places_closest_to"and "sort3element" compare a's and b's distance from coord xy
    //return true id a's distance from xy is shorter than b
    //Coord's "<" was reloaded(from "datastructure.hh" in rows 64-71)
    //O(1)
    bool aShorterB(const Place &a,const Place & b,const Coord& xy);

    //Helping "places_closest_to", sorting 3(or less than 3) elements in the "vector<PlaceID>"
    //Coord's "<" was reloaded(from "datastructure.hh" in rows 64-71)
    //O(nlog(n)). But actually it is theta(1) because n is constant 0-3. So this one will not effect "places_closest_to"'s complexity
    void sort3element(vector<Place*>& placeVec,const Coord& xy);
    //lock
    bool creation_finnished_=false;


};


#endif // DATASTRUCTURES_HH
