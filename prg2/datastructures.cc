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

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
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

//----------------------------------------------------------------------------------------------------------------------------------------
//phase 2
std::vector<WayID> Datastructures::all_ways()
{
    vector<WayID> WayIDs;
    for(auto i: wayIDUnordMap_){
        WayIDs.push_back(i.first);
    }
    return WayIDs;
}

//calculate WayID's length
//also cover the situation when length is 0
Distance Datastructures::calWayDist(const WayID id)
{
    vector<Coord> coords=wayIDUnordMap_.find(id)->second;
    Distance dist=0;
    for (unsigned int i=0; i<coords.size();i++){
        //calculating distance
        if(i==0){
            dist=0;
        }
        else{
            dist+=sqrt(pow((coords.at(i).x-coords.at(i-1).x),2)+pow((coords.at(i).y-coords.at(i-1).y),2));
        }
    }
    //qDebug()<<QString::fromStdString(id)<<" Distance is: "<<dist<<Qt::endl;
    return dist;
}


//update the wayIDUnordMap_, coordUnordMap_
bool Datastructures::add_way(WayID id, std::vector<Coord> coords)
{   
    if(wayIDUnordMap_.find(id) == wayIDUnordMap_.end()){
        //1. add to wayIDUnordMap_
        wayIDUnordMap_.insert({id,coords});

        //2. add to coordUnordMap_
        if(!coords.empty()){
            Distance d=calWayDist(id);
            Coord coord1 = coords.front();
            Coord coord2 = coords.back();
            BesideInfo info1; info1.d=d;
            BesideInfo info2; info2.d=d;
            //1-part
            if(coordUnordMap_.find(coord1)!=coordUnordMap_.end()){
                //adding Adj
                /////coordUnordMap_.find(coord1)->second->wayID_Dist.push_back( {id,d} );////
                if(coordUnordMap_.find(coord2)!=coordUnordMap_.end()){//2found, 1found
                    /////coordUnordMap_.find(coord2)->second->wayID_Dist.push_back( {id,d} );//******************//
                    //secondptr=&coordUnordMap_.find(new_coord2)->second;//give 2found value// if use this way, need to set secondptr back
                    info1.ptr=coordUnordMap_.find(coord2)->second;//2found
                    info2.ptr=coordUnordMap_.find(coord1)->second;//1found
                    coordUnordMap_.find(coord1)->second->besideInfo.insert( {id,info1} );//1found
                    coordUnordMap_.find(coord2)->second->besideInfo.insert( {id,info2} );//2found
                }
                else{//2-not found, 1found
                    CoordData* secondptr=new CoordData();
                    secondptr->coord=coord2;
                    /////secondptr->wayID_Dist.push_back({id,d});//******************//
                    info1.ptr=secondptr;//2-not found
                    info2.ptr=coordUnordMap_.find(coord1)->second;//1found
                    secondptr->besideInfo.insert({id,info2});//2-not found
                    coordUnordMap_.find(coord1)->second->besideInfo.insert( {id,info1} );//1found
                    coordUnordMap_.insert({coord2, secondptr});//2-not found
                }

            }
            else{
                CoordData* firstptr= new CoordData();
                firstptr->coord=coord1;
                /////firstptr->wayID_Dist.push_back({id,d});////
                if(coordUnordMap_.find(coord2)!=coordUnordMap_.end()){//2found, 1not found
                    /////coordUnordMap_.find(coord2)->second->wayID_Dist.push_back( {id,d} );//******************//
                    //secondptr=&coordUnordMap_.find(new_coord2)->second;//give 2found value// if use this way, need to set secondptr back
                    info1.ptr=coordUnordMap_.find(coord2)->second;//2found
                    info2.ptr=firstptr;//1-not found
                    firstptr->besideInfo.insert({id,info1});//1-not found
                    coordUnordMap_.find(coord2)->second->besideInfo.insert( {id,info2} );//2found
                    coordUnordMap_.insert({coord1, firstptr});//1-not found
                }
                else{//2-not found, 1 not found
                    CoordData* secondptr= new CoordData();
                    secondptr->coord=coord2;
                    //////secondptr->wayID_Dist.push_back({id,d});//******************//
                    info1.ptr=secondptr;//1-not found
                    info2.ptr=firstptr;//2-not found
                    firstptr->besideInfo.insert({id,info1});//1-not found
                    secondptr->besideInfo.insert({id,info2});//2-not found
                    coordUnordMap_.insert({coord2, secondptr});//2-not found
                    coordUnordMap_.insert({coord1, firstptr});//1-not found
                }
                //////firstptr->besideInfo.insert( {id,info2} );
                //first->coord=new_coord1;
                //newcoordData.IsCrossroad=true;
                ///////coordUnordMap_.insert({coord1,*firstptr});
            }
/**
//            //2-part
//            if(coordUnordMap_.find(new_coord2)!=coordUnordMap_.end()){
//                //adding Adj
//                coordUnordMap_.find(new_coord2)->second.wayID_Dist.push_back( {id,d} );////
//                //updateBesideInfo(new_coord2,second,info);
//                if(coordUnordMap_.find(new_coord1)!=coordUnordMap_.end()){//1found
//                    //firstptr=&coordUnordMap_.find(new_coord1)->second;//give 1found value// if use this way, need to set firstptr back
//                    info.ptr=&coordUnordMap_.find(new_coord1)->second;//update info
//                }
//                else{//1-not found
//                    info.ptr=firstptr;
//                }
//                coordUnordMap_.find(new_coord2)->second.besideInfo.insert( {id,info} );//update2 by giving 1info

//            }
//            else{
//                secondptr->wayID_Dist.push_back({id,d});////
//                //updateBesideInfo(new_coord2,second,info);
//                if(coordUnordMap_.find(new_coord1)!=coordUnordMap_.end()){//1found
//                    //firstptr=&coordUnordMap_.find(new_coord1)->second;//give 1found value// if use this way, need to set firstptr back
//                    info.ptr=&coordUnordMap_.find(new_coord1)->second;//update info
//                }
//                else{//1-not found
//                    info.ptr=firstptr;
//                }
//                secondptr->besideInfo.insert( {id,info} );
//                //first->coord=new_coord1;
//                //newcoordData.IsCrossroad=true;
//                coordUnordMap_.insert({new_coord2,*secondptr});
//            }


//            //2-part
//            if(coordUnordMap_.find(new_coord2) != coordUnordMap_.end()){
//                //adding Adj
//                coordUnordMap_.find(new_coord2)->second.wayID_Dist.push_back( {id,d} );////
//            }
//            else{//if not found
//                CoordData newcoordData;
//                newcoordData.wayID_Dist.push_back({id,d});////
//                newcoordData.coord = new_coord2;
//                //newcoordData.IsCrossroad=true;
//                coordUnordMap_.insert( {new_coord2,newcoordData} );
//            }
*/
        }
        return true;
    }

    return false;
}

//perftest ways_from 20 5000 10;30;100;300;1000;3000;10000;30000;100000;300000;1000000
std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord xy)
{
    //qDebug()<<"-1" <<xy.x<<","<<xy.y<<Qt::endl;
    if(coordUnordMap_.find(xy)!=coordUnordMap_.end()){
        //qDebug()<<"0"<<Qt::endl;
        CoordData coordData=*coordUnordMap_.find(xy)->second;

        // Have to be crossroad
        //qDebug()<<"5"<<Qt::endl;
        vector<pair<WayID,Coord>> queue;
        for(auto x:coordData.besideInfo){
            Coord first = coordData.coord;//coord recent
            Coord second = x.second.ptr->coord;//coord to
            if(first==xy){
                queue.push_back({x.first,second});
            }
            else {
                queue.push_back({x.first,first});
            }
        }
/**
//        for(pair<WayID,Distance> x : coordData.wayID_Dist){//maybe this coord can go to many places
//            Coord second=wayIDUnordMap_.find(x.first)->second.back();
//            Coord first=wayIDUnordMap_.find(x.first)->second.front();
//            if(first==xy){
//                queue.push_back({x.first,second});
//            }
//            else {
//                queue.push_back({x.first,first});
//            }

//        }
*/
        return queue;
    }
    return {};

}
//perftest way_coords 20 5000 10;30;100;300;1000;3000;10000;30000;100000;300000;1000000
std::vector<Coord> Datastructures::get_way_coords(WayID id)
{
    if(wayIDUnordMap_.find(id)!=wayIDUnordMap_.end()){
        return wayIDUnordMap_.find(id)->second;
    }
    return {NO_COORD};
}

void Datastructures::clear_ways()
{
    wayIDUnordMap_.clear();
    for(auto x: coordUnordMap_){
       delete x.second;
    }
    coordUnordMap_.clear();
}


/**
 * @brief return a coord(to). Because theree are only wayId stored in our CoordData
 * @param recentCoordFrom
 * @param wayID
 * @pre recentCoordFrom exist and wayId can be find from the recentCoordFrom
 * @return coordTo a ptr
 */
Datastructures::CoordData* Datastructures::coordTo(const Datastructures::CoordData recentCoordFrom, WayID wayID)
{
    vector<Coord> coordList=wayIDUnordMap_.find(wayID)->second;
    Coord first=coordList.front();
    Coord second=coordList.back();
    CoordData* recentCoordTo;
    if(first==recentCoordFrom.coord){
        recentCoordTo=coordUnordMap_.find(second)->second;
    }
    else {
        recentCoordTo=coordUnordMap_.find(first)->second;
    }

    return recentCoordTo;
}


void Datastructures::clearCoorDataMarks()
{
    for(auto iter=coordUnordMap_.begin();iter!=coordUnordMap_.end();iter++){
        iter->second->colour=Colour::WHITE;
        iter->second->from=nullptr;
        iter->second->fromWay=NO_WAY;
        iter->second->d=-1;
    }
}

//precondition: CoordData need to save node's all data from the former node
//precondition*:coordDataTo.from can not be nullptr!
// course side ask the tuple of coord(current), WayID(which is going to), dist(from the origin node)
//idea of printPath: because at push_back we can use the pointer of "former". So we travel the index of (1-n).
//                   and always push back (1.former - n.former)'s data to vec. (1.former - n.former)=(0-(n-1))'s data.
//                    So the last one we need to add by our hand out of the printPath function.
void Datastructures::printPath(vector<std::tuple<Coord, WayID, Distance> > &path, const Datastructures::CoordData coordDataFrom, const Datastructures::CoordData coordDataTo)
{
    if(coordDataFrom.coord==coordDataTo.from->coord){//when back to the coord where begin
        path.push_back({coordDataTo.from->coord,coordDataTo.fromWay,0});
    }
//    else if(coordDataTo.from==nullptr){//never hapend
//        path.push_back({NO_COORD,NO_WAY,NO_DISTANCE});
//    }

    else{
        printPath(path,coordDataFrom,*coordDataTo.from);
        path.push_back({coordDataTo.from->coord,coordDataTo.fromWay,coordDataTo.from->d});
    }
}


//perftest route_any 20 5000 10;30;100;300;1000;3000;10000;30000;100000;300000;1000000
std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_any(Coord fromxy, Coord toxy)
{

    if( coordUnordMap_.find(fromxy)==coordUnordMap_.end()
     || coordUnordMap_.find(toxy)==coordUnordMap_.end()){//If either of the coordinates is not a crossroad
        return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    }
    CoordData* coordDataFrom=coordUnordMap_.find(fromxy)->second;
    CoordData* coordDataTo=coordUnordMap_.find(toxy)->second;
    clearCoorDataMarks();
    vector<std::tuple<Coord, WayID, Distance> > path;

    list<CoordData*> queue;//ptr
    coordDataFrom->d=0;
    coordDataFrom->colour=Colour::GRAY;
    queue.push_back(coordDataFrom);
    bool found=false;
    //bool first=true;//test
    while(!queue.empty() and !found){
        CoordData* recentCoordFrom=queue.front();
        queue.pop_front();

        for(besideInfoiter iter=recentCoordFrom->besideInfo.begin();iter!=recentCoordFrom->besideInfo.end();iter++){//first:wayId, second:besideInfo(struct)
            //auto besideInfo:recentCoordFrom->besideInfo
            if(iter->second.d==0){
                continue;
            }
            //find the right node
            CoordData* recentCoordTo=iter->second.ptr;

            //qDebug()<< recentCoordTo->coord.x<<","<<recentCoordTo->coord.y<<Qt::endl;
            if(recentCoordTo->colour==Colour::WHITE){
                recentCoordTo->colour=Colour::GRAY;
                recentCoordTo->from=recentCoordFrom;
                recentCoordTo->d=recentCoordFrom->d+iter->second.d;//calWayDist(way.first);
                recentCoordTo->fromWay=iter->first;
                //if find
                if(recentCoordTo->coord==toxy){
                    found=true;
                    break;
                }
                queue.push_back(recentCoordTo);
            }
        }
/**
//        for(pair<WayID,Distance> way:recentCoordFrom.wayID_Dist){
//            // test
//            if(way==recentCoordFrom.wayID_Dist.front()){
//                qDebug()<<"-------------------"<<Qt::endl;
//                qDebug()<<"from coord: "<<recentCoordFrom.coord.x<<","<<recentCoordFrom.coord.y<<Qt::endl;

//                qDebug()<<"start"<<Qt::endl;
//            }
//            qDebug()<<QString::fromStdString(way.first)<<Qt::endl;
//            if(way==recentCoordFrom.wayID_Dist.back()){
//                qDebug()<<"end"<<Qt::endl;
//                qDebug()<<"-------------------"<<Qt::endl;
//            }
//            //
//            if(way.second==0){
//                continue;
//            }
//            //find the right node
//            CoordData* recentCoordTo=coordTo(recentCoordFrom,way.first);

//            //qDebug()<< recentCoordTo->coord.x<<","<<recentCoordTo->coord.y<<Qt::endl;
//            if(recentCoordTo->colour==Colour::WHITE){
//                recentCoordTo->colour=Colour::GRAY;
//                recentCoordTo->from=&recentCoordFrom;
//                recentCoordTo->d=recentCoordFrom.d+way.second;//calWayDist(way.first);
//                recentCoordTo->fromWay=way.first;
//                //if find
//                queue.push_back(recentCoordTo);
//            }
//            if(recentCoordTo->colour==Colour::BLACK){
//                qDebug()<<recentCoordFrom.coord.x<<","<<recentCoordFrom.coord.y<<"colour is black"<<Qt::endl;
//            }
//        }
 */
        recentCoordFrom->colour=Colour::BLACK;
    }
    //printpath
    if(coordDataTo->from!=nullptr){
        printPath(path,*coordDataFrom,*coordDataTo);// in order 1-(n-1)
        path.push_back({coordDataTo->coord,NO_WAY,coordDataTo->d});//n
        return path;
    }


    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

bool Datastructures::remove_way(WayID id)
{
    if(wayIDUnordMap_.find(id)!=wayIDUnordMap_.end()){
        //wayIDUnordMap_
        vector<Coord> vec=wayIDUnordMap_.find(id)->second;
        wayIDUnordMap_.erase(wayIDUnordMap_.find(id));
        //coordUnordMap_

        Coord first=vec.front();
        Coord second=vec.back();
        if(first==second){
            CoordData* firstptr=coordUnordMap_.find(first)->second;
            firstptr->besideInfo.erase(firstptr->besideInfo.find(id));
            if(firstptr->besideInfo.size()==0){
                coordUnordMap_.erase(coordUnordMap_.find(first));
                delete firstptr;
            }
        }
        else{//front and back are different
            CoordData* firstptr=coordUnordMap_.find(first)->second;
            CoordData* secondtptr=coordUnordMap_.find(second)->second;
            firstptr->besideInfo.erase(firstptr->besideInfo.find(id));
            secondtptr->besideInfo.erase(secondtptr->besideInfo.find(id));
            if(firstptr->besideInfo.size()==0){
                coordUnordMap_.erase(coordUnordMap_.find(first));
                delete firstptr;
            }
            if(secondtptr->besideInfo.size()==0){
                coordUnordMap_.erase(coordUnordMap_.find(second));
                delete secondtptr;
            }
        }
        return true;
    }
    return false;
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_least_crossroads(Coord fromxy, Coord toxy)
{
    vector<std::tuple<Coord, WayID, Distance> > returnable={{NO_COORD, NO_WAY, NO_DISTANCE}};
    returnable=route_any(fromxy,toxy);
    return returnable;
    // Replace this comment with your implementation
    //return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}


void Datastructures::printPath(vector<std::tuple<Coord, WayID> > &path, const CoordData coordDataFrom, const CoordData coordDataTo)
{
    //qDebug()<<coordDataTo.from->coord.x<<","<<coordDataTo.from->coord.y<<"is"<<QString::fromStdString(coordDataTo.fromWay)<<Qt::endl;
    if(coordDataTo.from->coord==coordDataFrom.coord){
        path.push_back({coordDataTo.from->coord,coordDataTo.fromWay});
    }
    else {
        printPath(path,coordDataFrom,*coordDataTo.from);
        path.push_back({coordDataTo.from->coord,coordDataTo.fromWay});
    }
}
//perftest route_with_cycle 20 5000 10;30;100;300;1000;3000;10000;30000;100000;300000;1000000
std::vector<std::tuple<Coord, WayID> > Datastructures::route_with_cycle(Coord fromxy)
{
    if(coordUnordMap_.find(fromxy)!=coordUnordMap_.end()){
        clearCoorDataMarks();
        CoordData* fromptr=coordUnordMap_.find(fromxy)->second;
        vector<std::tuple<Coord, WayID> > path;

        CoordData* recentFrom;
        CoordData* recentCoordTo;
        WayID wayTo;

        vector<CoordData*> queue;//ptr
        queue.push_back(fromptr);
        bool found = false;
        int i =0;
        while ( !queue.empty() and !found){
            i++;
            recentFrom= queue.back();
            queue.pop_back();
            if(recentFrom->colour==Colour::WHITE){
                recentFrom->colour=Colour::GRAY;
                queue.push_back(recentFrom);
                for(besideInfoiter iter=recentFrom->besideInfo.begin();iter!=recentFrom->besideInfo.end();iter++){
                    if(iter->second.d==0){
                        continue;
                    }
                    //find the right node
                    recentCoordTo=iter->second.ptr;
                    wayTo=iter->first;
                    if(recentCoordTo->colour==Colour::WHITE){
                        //recentCoordTo->d=recentCoordFrom->d+iter->second.d;
                        recentCoordTo->from=recentFrom;
                        recentCoordTo->fromWay=wayTo;
                        queue.push_back(recentCoordTo);
                    }
                    else if(recentCoordTo->colour==Colour::GRAY and recentCoordTo->coord!=recentFrom->from->coord){
                        found=true;
                        break;
                        //circle found
                    }
                }
            }
            else{
                recentFrom->colour=Colour::BLACK;
            }
        }
        if(found==true){
            printPath(path,*fromptr,*recentFrom);
            path.push_back({recentFrom->coord,wayTo});
            path.push_back({recentCoordTo->coord,NO_WAY});
            return path;
        }
    }
    // Replace this comment with your implementation
    return {};
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_shortest_distance(Coord fromxy, Coord toxy)
{
    if( coordUnordMap_.find(fromxy)==coordUnordMap_.end()
        || coordUnordMap_.find(toxy)==coordUnordMap_.end()){//If either of the coordinates is not a crossroad
           return {{NO_COORD, NO_WAY, NO_DISTANCE}};
       }


       CoordData* coordDataFrom=coordUnordMap_.find(fromxy)->second;
       CoordData* coordDataTo=coordUnordMap_.find(toxy)->second;
       clearCoorDataMarks();
       vector<std::tuple<Coord, WayID, Distance> > path;

       //        auto myComp = [](const CoordData* &a, const CoordData* &b)
       //                      {return a->d > b->d;};//just like reload <, so smaller one goes out from the p_queue first

       //        priority_queue<pair<CoordData*, vector<CoordData*>, decltype(myComp)> queue(myComp);
        priority_queue<CoordData*, vector<CoordData*>, PQueComCoorD_Ptr> queue;

       coordDataFrom->d=0;
       coordDataFrom->colour=Colour::GRAY;
       queue.push(coordDataFrom);
       while(!queue.empty()){
           CoordData* recentCoordFrom=queue.top();
           queue.pop();

           for(besideInfoiter iter=recentCoordFrom->besideInfo.begin();iter!=recentCoordFrom->besideInfo.end();iter++){//first:wayId, second:besideInfo(struct)
               //auto besideInfo:recentCoordFrom->besideInfo
               if(iter->second.d==0){
                   continue;
               }
               //find the right node
               CoordData* recentCoordTo=iter->second.ptr;

               //qDebug()<< recentCoordTo->coord.x<<","<<recentCoordTo->coord.y<<Qt::endl;
               if(recentCoordTo->colour==Colour::WHITE){
                   recentCoordTo->colour=Colour::GRAY;
                   recentCoordTo->from=recentCoordFrom;
                   recentCoordTo->d=recentCoordFrom->d+iter->second.d;//calWayDist(way.first);
                   recentCoordTo->fromWay=iter->first;
                   queue.push(recentCoordTo);
               }
               //RELAX
               if(recentCoordTo->d>recentCoordFrom->d+iter->second.d){
                   recentCoordTo->from=recentCoordFrom;
                   recentCoordTo->d=recentCoordFrom->d+iter->second.d;//calWayDist(way.first);
                   recentCoordTo->fromWay=iter->first;
               }


           }
           recentCoordFrom->colour=Colour::BLACK;
       }
       //printpath
       if(coordDataTo->from!=nullptr){
           printPath(path,*coordDataFrom,*coordDataTo);// in order 1-(n-1)
           path.push_back({coordDataTo->coord,NO_WAY,coordDataTo->d});//n
           return path;
        }

    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

Distance Datastructures::trim_ways()
{
    // Replace this comment with your implementation
    return NO_DISTANCE;
}
