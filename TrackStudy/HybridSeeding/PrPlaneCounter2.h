#ifndef PRPLANECOUNTER2_H 
#define PRPLANECOUNTER2_H 1

// Include files

/** @class PrPlaneCounter2 PrPlaneCounter2.h
 *  Small Class to count how many different planes are in a List and how many planes with a single hit 
 *
 *  @author renato quagliani
 *  @date   2015-07-13
 */
class PrPlaneCounter2 {
public: 
  /// Standard constructor
  PrPlaneCounter2( ):
    m_nbFiredLayers(0),
    m_nbFiredLayers_singleHit(0),
    m_planeList({{0,0,0,0,0,0,0,0,0,0,0,0}}),
    m_nbT1X(0),
    m_nbT1X_singleHit(0),
    m_nbT2X(0),
    m_nbT2X_singleHit(0),
    m_nbT3X(0),
    m_nbT3X_singleHit(0),
    m_nbT1UV(0),
    m_nbT1UV_singleHit(0),
    m_nbT2UV(0),
    m_nbT2UV_singleHit(0),
    m_nbT3UV(0),
    m_nbT3UV_singleHit(0)
  { };
  
  void set( PrHits::iterator itBeg, PrHits::iterator itEnd, const bool fill = true){
    if(fill)
    {
      m_nbFiredLayers = 0;
      m_nbFiredLayers_singleHit = 0;
      m_planeList = {{0,0,0,0,0,0,0,0,0,0,0,0}};
      m_nbT1UV_singleHit = 0;
      m_nbT1X=0;
      m_nbT1X_singleHit=0;
      m_nbT2X=0;
      m_nbT2X_singleHit=0;
      m_nbT2X=0;
      m_nbT2X_singleHit=0;
      m_nbT3X=0;
      m_nbT3X_singleHit=0;
      m_nbT1UV=0;
      m_nbT1UV_singleHit=0;
      m_nbT2UV=0;
      m_nbT2UV_singleHit=0;
      m_nbT2UV=0;
      m_nbT2UV_singleHit=0;
      m_nbT3UV=0;
      m_nbT3UV_singleHit=0;
    }
    PrHit *hit = nullptr;
    for ( PrHits::const_iterator itH = itBeg; itEnd != itH; ++itH) {
      hit = (*itH);
      if(hit->isUsed()) continue;
      unsigned int plane = hit->planeCode();
      //if no hits in the plane, increase the counters anyway even if the plane
      if( 0 == m_planeList[ plane ] ++ ){
        m_nbFiredLayers_singleHit ++;
        m_nbFiredLayers ++;
        if( isT1(hit) && hit->isX()) { m_nbT1X++; m_nbT1X_singleHit++; }
        if( isT1(hit) && !hit->isX()){ m_nbT1UV++ ; m_nbT1UV_singleHit++;}
        if( isT2(hit) && hit->isX()) { m_nbT2X++; m_nbT2X_singleHit++; }
        if( isT2(hit) && !hit->isX()){ m_nbT2UV++ ;m_nbT2UV_singleHit++;}
        if( isT3(hit) &&  hit->isX()) { m_nbT3X++; m_nbT3X_singleHit++; }
        if( isT3(hit) && !hit->isX()){ m_nbT3UV++; m_nbT3UV_singleHit++;}
        
        if(isT1(hit)){ m_nbT1++; m_nbT1_singleHit++; }
        if(isT2(hit)){ m_nbT2++; m_nbT2_singleHit++; }
        if(isT3(hit)){ m_nbT3++; m_nbT2_singleHit++; }
      }else{
        if (2== m_planeList[plane]){
          m_nbFiredLayers_singleHit --;
          if( isT1(hit) && hit->isX()) { m_nbT1X_singleHit--;}
          if( isT1(hit) && !hit->isX()){ m_nbT1UV_singleHit--;}
          if( isT2(hit) && hit->isX()) { m_nbT2X_singleHit--; }
          if( isT2(hit) && !hit->isX()){ m_nbT2UV_singleHit--;}
          if( isT3(hit) && hit->isX()) {  m_nbT3X_singleHit--; }
          if( isT3(hit) && !hit->isX()){ m_nbT3UV_singleHit--;}
          if(isT1(hit)){ m_nbT1_singleHit--; }
          if(isT2(hit)){ m_nbT2_singleHit--; }
          if(isT3(hit)){ m_nbT2_singleHit--; }
        }
      }
    }//end loop hits
  }
  
  int addHit( const PrHit* hit){
    if(hit->isUsed()) return m_nbFiredLayers;
    unsigned int plane = hit->planeCode();
    if( 0 == m_planeList[plane]++){
       m_nbFiredLayers_singleHit ++;
       m_nbFiredLayers ++;
       if( isT1(hit) && hit->isX()) { m_nbT1X++; m_nbT1X_singleHit++;}
       if( isT1(hit) && !hit->isX()){ m_nbT1UV++ ;m_nbT1UV_singleHit++;}
       if( isT2(hit) && hit->isX()) { m_nbT2X++; m_nbT2X_singleHit++;}
       if( isT2(hit) && !hit->isX()){ m_nbT2UV++ ;m_nbT2UV_singleHit++;}
       if( isT3(hit) && hit->isX()) { m_nbT3X++; m_nbT3X_singleHit++;}
       if( isT3(hit) && !hit->isX()){ m_nbT3UV++ ;m_nbT3UV_singleHit++;}
       if(isT1(hit)){ m_nbT1++; m_nbT1_singleHit++; }
       if(isT2(hit)){ m_nbT2++; m_nbT2_singleHit++; }
       if(isT3(hit)){ m_nbT3++; m_nbT2_singleHit++; }
    }else{
      if( 2 == m_planeList[plane]){ //if you are adding a hit where already present one singlecounting decreased
        m_nbFiredLayers_singleHit --;
        if( isT1(hit) && hit->isX()) { m_nbT1X_singleHit--;}
        if( isT1(hit) && !hit->isX()){ m_nbT1UV_singleHit--;}
        if( isT2(hit) && hit->isX()) { m_nbT2X_singleHit--; }
        if( isT2(hit) && !hit->isX()){ m_nbT2UV_singleHit--;}
        if( isT3(hit) && hit->isX()) {  m_nbT3X_singleHit--; }
        if( isT3(hit) && !hit->isX()){ m_nbT3UV_singleHit--;}
        if(isT1(hit)){ m_nbT1_singleHit--; }
        if(isT2(hit)){ m_nbT2_singleHit--; }
        if(isT3(hit)){ m_nbT2_singleHit--; }
      }
    } 
    return m_nbFiredLayers;
  }
  
  int removeHit( const PrHit* hit){
    if(hit->isUsed() ) return m_nbFiredLayers;
    unsigned int plane = hit->planeCode();
    unsigned int NumberInLayerAfterRemove = m_planeList[plane] -1;
    m_planeList[plane]--;
    if( 0 == NumberInLayerAfterRemove){ //you remain with 0 hits in that plane decrease everything
      m_nbFiredLayers_singleHit --;
      m_nbFiredLayers --;
      if( isT1(hit) && hit->isX()) { m_nbT1X--; m_nbT1X_singleHit--; }
      if( isT1(hit) && !hit->isX()){ m_nbT1UV-- ;m_nbT1UV_singleHit--;}
      if( isT2(hit) && hit->isX()) { m_nbT2X--; m_nbT2X_singleHit--; }
      if( isT2(hit) && !hit->isX()){ m_nbT2UV-- ;m_nbT2UV_singleHit--;}
      if( isT3(hit) && hit->isX()) { m_nbT3X--; m_nbT3X_singleHit--; }
      if( isT3(hit) && !hit->isX()){ m_nbT3UV-- ;m_nbT3UV_singleHit--;}
      if(isT1(hit)){ m_nbT1--; m_nbT1_singleHit--; }
      if(isT2(hit)){ m_nbT2--; m_nbT2_singleHit--; }
      if(isT3(hit)){ m_nbT3--; m_nbT2_singleHit--; }
    }
    if( 1 == NumberInLayerAfterRemove) //you remain with just one hit in that layer after removing it
    {
      m_nbFiredLayers_singleHit++;
      if( isT1(hit) && !hit->isX()){ m_nbT1UV_singleHit++;}
      if( isT2(hit) && hit->isX()) { m_nbT2X_singleHit++; }
      if( isT2(hit) && !hit->isX()){ m_nbT2UV_singleHit++;}
      if( isT3(hit) && hit->isX()) { m_nbT3X_singleHit++; }
      if( isT3(hit) && !hit->isX()){ m_nbT3UV_singleHit++;}
      if(isT1(hit)){ m_nbT1_singleHit++; }
      if(isT2(hit)){ m_nbT2_singleHit++; }
      if(isT3(hit)){ m_nbT2_singleHit++; }
    }
    return m_nbFiredLayers;
  }
  unsigned int nbDifferentUVT1() const
  {
    return m_nbT1UV;
  }
  unsigned int nbDifferentUVT2() const
  {
    return m_nbT2UV;
  }
  unsigned int nbDifferentUVT3() const 
  {
    return m_nbT3UV;
  }
  
  unsigned int nbDifferent() const{ return m_nbFiredLayers;}
  unsigned int nbSingle() const{ return m_nbFiredLayers_singleHit;}
  
  unsigned int nbDifferentX() const { return m_nbT1X + m_nbT2X + m_nbT3X; }
  unsigned int nbSingleX() const{ return m_nbT1X_singleHit + m_nbT2X_singleHit + m_nbT3X_singleHit;}
  unsigned int nbDifferentUV() const{ return m_nbT1UV + m_nbT2UV + m_nbT3UV;}
  unsigned int nbSingleUV() const{return m_nbT1UV_singleHit + m_nbT2UV_singleHit + m_nbT3UV_singleHit;}
  
  bool isOKUV() const{
    return (m_nbT1UV>=1 && m_nbT2UV>=1 && m_nbT3UV>=1);
    return false;
  }
  
  bool isOK() const{ 
    return ( m_nbT1X>=1 &&
             m_nbT1UV>=1 && 
             m_nbT2X>=1 && 
             m_nbT2UV>=1 && 
             m_nbT3UV >=1 && 
             m_nbT3X>=1);
    return false;
  }
  unsigned int nbInPlane( const int plane) const{return m_planeList[plane];}
  
  
  
    
  
  
  
  
  

  //Checkers for the Hits
  bool isT1(const PrHit *hit)const{
    if(hit->planeCode() >=0 && hit->planeCode() <=4)
      return true;
    return false;
  }
  bool isT2(const PrHit *hit)const{
    if(hit->planeCode() >=5 && hit->planeCode() <=8)
      return true;
    return false;
  }
  bool isT3(const PrHit *hit)const{
    if(hit->planeCode() >=8 && hit->planeCode() <=11)      
      return true;
    return false;
  }
  
  
  virtual ~PrPlaneCounter2( ) {} ///< Destructor
  

  
protected:
  
private:
  unsigned int m_nbFiredLayers; 
  unsigned int m_nbFiredLayers_singleHit;
  std::array<unsigned int,12> m_planeList;
  unsigned int m_nbT1X;
  unsigned int m_nbT1X_singleHit;
  
  unsigned int m_nbT2X;
  unsigned int m_nbT2X_singleHit;
  
  unsigned int m_nbT3X;
  unsigned int m_nbT3X_singleHit;

  unsigned int m_nbT1UV;
  unsigned int m_nbT1UV_singleHit;
  
  unsigned int m_nbT2UV;
  unsigned int m_nbT2UV_singleHit;
  
  unsigned int m_nbT3UV;
  unsigned int m_nbT3UV_singleHit;

  unsigned int m_nbT1;
  unsigned int m_nbT1_singleHit;

  unsigned int m_nbT2;
  unsigned int m_nbT2_singleHit;
  
  unsigned int m_nbT3;
  unsigned int m_nbT3_singleHit;
};
#endif // PRPLANECOUNTER2_H