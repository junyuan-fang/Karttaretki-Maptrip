// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <QDebug>

#include <QString>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

//********
//return size
//O(1)
int Datastructures::place_count()
{
    return placeUnOrMap_.size();
}

//********
//O(n)
void Datastructures::clear_all()
{
    placeUnOrMap_.clear();//O(n)

    areaUnOrMap_.clear();//O(n)
}

//********
//create vector(assigning). copy places from unordered_map to vector
//return places as a vector
//O(n)
std::vector<PlaceID> Datastructures::all_places()
{
    vector<PlaceID> ID(placeUnOrMap_.size());//O(n)+O(n)
    vector<PlaceID>::iterator iter_vec=ID.begin();
    for(placeIter iter_map=placeUnOrMap_.begin();iter_map!=placeUnOrMap_.end();iter_map++){//O(n)
        *iter_vec=iter_map->first;//O(1)
        iter_vec++;
    }
    return ID;
}

//********
//search, if there is same address in the data structure return false.
//Otherwise, add a new address and return true.
//worst O(n), average thete(1)
bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
//    if(creation_finnished_){
//        return false;
//    }
    if(placeUnOrMap_.find(id)==placeUnOrMap_.end()){
        Place newPlace;
        newPlace.place_ID_=id;
        newPlace.name_=name;
        newPlace.type_=type;
        newPlace.xy_=xy;
        placeUnOrMap_.insert({id,newPlace});//worst O(n), average thete(1)
        return true;
    }
    return false;
}

//********
//Average case: theta(1),Worst case: O(n)
//return {Name,PlaceType}
//return {NO_NAME,NO_TYPE} if we do not find it
std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    placeIter place_iter=placeUnOrMap_.find(id);//Average case: O(1),Worst case: O(n)
    if(place_iter!=placeUnOrMap_.end()){
        return{place_iter->second.name_,place_iter->second.type_} ;
    }
    return {NO_NAME, PlaceType::NO_TYPE};
}
//********
//Average case: O(1),Worst case: O(n)
//return COORD
//return NO_COORD if we do not find it
Coord Datastructures::get_place_coord(PlaceID id)
{
    placeIter iter;//unordered_map<PlaceID,Place>::iterator
    iter=placeUnOrMap_.find(id);//Average case: O(1),Worst case: O(n)
    if(iter!=placeUnOrMap_.end()){
        return iter->second.xy_;
    }
    return NO_COORD;
}

//********
//search, if there is same area in the data structure return false.
//Otherwise, add a new area and return true.
//O(n)
bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
//    if(creation_finnished_){
//        return false;
//    }
    if(areaUnOrMap_.find(id)==areaUnOrMap_.end()){//Average case: O(1),Worst case: O(n)
        Area newArea;
        newArea.area_ID_=id;
        newArea.name_=name;
        newArea.coords_.assign(coords.begin(),coords.end());//O(n)
        newArea.parent_=nullptr;
        newArea.subArea_={};
        areaUnOrMap_.insert({id,newArea});
        return true;
    }
    return false;
}

//********
//in average theta(1),Worst case: O(n)
Name Datastructures::get_area_name(AreaID id)
{
    areaIter iter= areaUnOrMap_.find(id);
    if(iter!=areaUnOrMap_.end()){
        return iter->second.name_;
    }
    return NO_NAME;
}

//********
//in average theta(1),Worst case: O(n)
std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    areaIter iter= areaUnOrMap_.find(id);
    if(iter!=areaUnOrMap_.end()){
        return iter->second.coords_;
    }
    return {NO_COORD};
}

//********
//O(1)
void Datastructures::creation_finished()
{
    creation_finnished_=true;
}

//********
//Average cost: O(n log(n))
std::vector<PlaceID> Datastructures::places_alphabetically()
{
//    vector<PlaceID> ID= all_places();  //O(n)
//    sort(ID.begin(), ID.end(), [this](PlaceID a, PlaceID b)   //this
//        {return placeUnOrMap_.find(a)->second.name_
//                <
//                placeUnOrMap_.find(b)->second.name_;});//sort O(nlog(n))
    vector<Place*> placeVecPtr;
    for(placeIter iter_map=placeUnOrMap_.begin();iter_map!=placeUnOrMap_.end();iter_map++){//O(n)
        placeVecPtr.push_back(&iter_map->second);
    }

    sort(placeVecPtr.begin(), placeVecPtr.end(), [](Place* a, Place* b)   //this
        {return a->name_
                <
                b->name_;});//sort O(nlog(n))
    vector<PlaceID> ID;
    for(Place* a:placeVecPtr){//O(n)
        ID.push_back(a->place_ID_);
    }
    return ID;
}


//********
//Average cost: O(n log(n))
//Coord's "<" was reloaded(from "datastructure.hh" in rows 64-71)
//perftest places_coord_order;random_add 20 500 10;30;100;300;1000;3000;10000;30000;100000;300000
std::vector<PlaceID> Datastructures::places_coord_order()
{
    vector<Place*> placeVecPtr;
    for(placeIter iter_map=placeUnOrMap_.begin();iter_map!=placeUnOrMap_.end();iter_map++){//O(n)
        placeVecPtr.push_back(&iter_map->second);
    }
    sort(placeVecPtr.begin(),placeVecPtr.end(),[](Place* a, Place* b)//O(nlog(n))
    {   Coord a_coord=a->xy_; //theta(1)
        Coord b_coord=b->xy_;
        double a_coord_abs= sqrt(pow(a_coord.x,2)+pow(a_coord.y,2));
        double b_coord_abs= sqrt(pow(b_coord.x,2)+pow(b_coord.y,2));
        if(a_coord_abs<b_coord_abs){
            return true;
        }
        else if(a_coord_abs>b_coord_abs){
            return false;
        }
        return a_coord<b_coord;});//sort O(nlog(n))
    vector<PlaceID> ID;
    for(Place* a:placeVecPtr){//O(n)
        ID.push_back(a->place_ID_);
    }
    return ID;
}

//********
// O(n*m)
std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    vector<PlaceID> ID;
    for(placeIter iter=placeUnOrMap_.begin(); iter!=placeUnOrMap_.end(); iter++){//O(n)
        Name nameFrom= iter->second.name_;
        if(nameFrom==name){//O(m)， but our string is short so O(1)
            ID.push_back(iter->first);
        }
    }
    return ID;
}

//********
// O(n)
std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    vector<PlaceID> ID;
    for(placeIter iter=placeUnOrMap_.begin(); iter!=placeUnOrMap_.end();iter++){//O(n)
        PlaceType typeFrom=iter->second.type_;
        if(type==typeFrom){//O(n)， but our string is short so O(1)
            ID.push_back(iter->first);
        }
    }
    return ID;
}

//********
//O(n), in average theta(1)
bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    placeIter iter= placeUnOrMap_.find(id);//O(n), theta(1)
    if(iter!=placeUnOrMap_.end()){
        iter->second.name_=newname;
        return true;
    }
    return false;
}

//********
//O(n), in average theta(1)
bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    placeIter iter= placeUnOrMap_.find(id);//O(n), theta(1)
    if(iter!=placeUnOrMap_.end()){
        iter->second.xy_=newcoord;
        return true;
    }
    return false;
}

//********
//O(n)
std::vector<AreaID> Datastructures::all_areas()
{
    vector<AreaID> ID(areaUnOrMap_.size());
    vector<AreaID>::iterator ID_iter=ID.begin();
    for(areaIter iter=areaUnOrMap_.begin(); iter!=areaUnOrMap_.end(); iter++){//O(n)
        *ID_iter=iter->first;
        ID_iter++;
    }
    return ID;
}

//********
//mark id's parent and parentid's children
//O(n), theta(1)
bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
//    if(creation_finnished_){
//        return false;
//    }
    areaIter id_iter=areaUnOrMap_.find(id);
    areaIter parent_iter=areaUnOrMap_.find(parentid);
    if(id_iter==areaUnOrMap_.end()||parent_iter==areaUnOrMap_.end()){
        return false;
    }
    if(id_iter!=areaUnOrMap_.end() && id_iter->second.parent_==nullptr){//O(n), theta(1)
        //mark id's parent
        Area &parentArea= parent_iter->second;//quote
        id_iter->second.parent_= &parentArea;//address-of
        //mark parentid's children in vec
        Area &subArea=id_iter->second;
        parent_iter->second.subArea_.push_back(&subArea);//O(1) amortized run time
        return true;
    }
    return false;
}

//********
//return all areas, which subarea belongs directly or not
//pram subarea
//O(n)
std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    areaIter iter = areaUnOrMap_.find(id);
    if(iter != areaUnOrMap_.end()){
        Area* pointed=&iter->second;
        vector<AreaID> ID;
        while(pointed->parent_!=nullptr){//O(n)
            ID.push_back(pointed->parent_->area_ID_);//O(1) amortized run time
            pointed=pointed->parent_;
        }
        return ID;
    }
    return {NO_AREA};
}


//compare distance a and b from coord xy
//return true id a's distance from xy is shorter than b
//Coord's "<" was reloaded(from "datastructure.hh" in rows 64-71)
//O(1)
bool Datastructures::aShorterB(const Place &a, const Place &b, const Coord &xy)
{
    Coord xyA=a.xy_;//theta(1)
    Coord xyB=b.xy_;
    double distanceA=sqrt(pow(xyA.x-xy.x,2)+pow(xyA.y-xy.y,2));
    double distanceB=sqrt(pow(xyB.x-xy.x,2)+pow(xyB.y-xy.y,2));
    if(distanceA<distanceB){
        return true;
    }
    else if(distanceA>distanceB){
        return false;
    }
    return xyA<xyB;
}

//helping "places_closest_to"
//Coord's "<" was reloaded(from "datastructure.hh" in rows 64-71)
//O(nlog(n))
void Datastructures::sort3element(vector<Place*>& placeVec,const Coord& xy)
{
    sort(placeVec.begin(),placeVec.end(),
         [this,&xy](const Place* a,const Place* b)
    {   /*Coord xyA=placeUnOrMap_.find(a)->second.xy_;//theta(1)
        Coord xyB=placeUnOrMap_.find(b)->second.xy_;
        double distanceA=sqrt(pow(xyA.x-xy.x,2)+pow(xyA.y-xy.y,2));
        double distanceB=sqrt(pow(xyB.x-xy.x,2)+pow(xyB.y-xy.y,2));
        if(distanceA<distanceB){
            return true;
        }
        else if(distanceA>distanceB){
            return false;
        }
        return xyA<xyB;*/
        return aShorterB(*a,*b,xy);
    }   );
}

//********
//returns Coord xy's closest 3 places(max 3). And places are in order
//O(n)
//perftest places_closest_to;random_add 20 500 10;30;100;300;1000;3000;10000;30000;100000;300000
std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    vector<Place*> ID;
    for(placeIter iter=placeUnOrMap_.begin();iter!=placeUnOrMap_.end();iter++){
        PlaceType recentType=iter->second.type_;
        if (recentType==type||type==PlaceType::NO_TYPE){
            if(ID.size()<3 ){
                //add ID to vec
                ID.push_back(&iter->second);
                sort3element(ID,xy);
            }
            //compare iter.first with the largest +adjust(swap)
            else if(aShorterB(*ID.back(),iter->second,xy)==false){
                ID.back()=&iter->second;
            }
            //sort
            sort3element(ID,xy);//should be O(nlogn), but n is constant 3 so O(1)
        }
    }
    vector<PlaceID> id;
    for(Place* x:ID){
        id.push_back(x->place_ID_);
    }
    return id;
}

//********
//theta(1),O(n)
bool Datastructures::remove_place(PlaceID id)
{
    return placeUnOrMap_.erase(id);
}

// Helping "all_subareas_in_area"
void Datastructures::PRE_WALK_SUB(Area* recentArea, vector<AreaID>& ID){
    if (recentArea->subArea_.empty()==false){
        //handling
        for(Area* subArea : recentArea->subArea_){
            ID.push_back(subArea->area_ID_);
        }
        for(Area* subArea : recentArea->subArea_){
            PRE_WALK_SUB( subArea,  ID);
        }
    }
}


//********
//Depth First Traversal is O(n + m), where n is the number of nodes, and m is the number of edges.
//pre-order-tree-walk
//O(n)
std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    areaIter iter =areaUnOrMap_.find(id);//O(n),Theta(1)
    if(iter!=areaUnOrMap_.end()){
        vector<AreaID> ID;
        Area* recentArea=&iter->second;
        PRE_WALK_SUB( recentArea, ID);//PREORDER-TREE-WALK
        return ID;
    }
    return {NO_AREA};
}

void Datastructures::PRE_WALK_COMMON(bool& flag,Datastructures::Area* recentArea, const AreaID id1, const AreaID id2, AreaID &might_common_areaID, AreaID &common_areaID)
{
    if(recentArea->area_ID_==id2){
        common_areaID=might_common_areaID;
        return;
    }
    if(recentArea->subArea_.size()==0){
        return;
    }
    if(recentArea->area_ID_==id1){
        flag=true;
    }
    if(recentArea->parent_==nullptr){

    }
    else if (recentArea->area_ID_==recentArea->parent_->subArea_.back()->area_ID_ &&recentArea->subArea_.size()>1 && !flag){
        might_common_areaID=recentArea->area_ID_;
    }
//    QString a= QString::fromStdString(recentArea->name_);
//    qDebug()<<a<<Qt::endl;

    for(Area* x:recentArea->subArea_){
        PRE_WALK_COMMON(flag ,x, id1, id2, might_common_areaID, common_areaID);
    }
}

//returns 2 id's common area
//returns NO_AREA when id1, id2 not find or no common area
//perftest places_closest_to;random_add 20 500 10;30;100;300;1000;3000;10000;30000;100000;300000
AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
//    areaIter id1Iter=areaUnOrMap_.find(id1);
//    areaIter id2Iter=areaUnOrMap_.find(id2);
//    Area* id1Ptr=&id1Iter->second;
//    if(id1Iter!=areaUnOrMap_.end()||id2Iter!=areaUnOrMap_.end()){
//        while(id1Ptr->parent_!=nullptr){
//            Area* id2Ptr=&id2Iter->second;
//            while(id2Ptr->parent_!=nullptr){
//                if(id2Ptr->parent_->area_ID_==id1Ptr->parent_->area_ID_){
//                    return id2Ptr->parent_->area_ID_;
//                }
//                id2Ptr=id2Ptr->parent_;
//            }
//            id1Ptr=id1Ptr->parent_;
//        }
//    }
//    return NO_AREA;
    areaIter id1Iter=areaUnOrMap_.find(id1);
    areaIter id2Iter=areaUnOrMap_.find(id2);
    if(id1Iter==areaUnOrMap_.end()||id2Iter==areaUnOrMap_.end()){
        return NO_AREA;
    }
    Area* id1Top=&id1Iter->second;
    while(id1Top->parent_!=nullptr){
        id1Top=id1Top->parent_;
    }
    //find id2 by id1Top and return the area
    AreaID might_common_areaID= id1Top->area_ID_;
    AreaID common_areaID=NO_AREA;
    bool flag=false;
    PRE_WALK_COMMON(flag,id1Top, id1, id2,might_common_areaID, common_areaID);
//    qDebug()<<"done"<<Qt::endl;
    return common_areaID;
}

