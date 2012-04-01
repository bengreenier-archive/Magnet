#include "Graphics.h"
#include "../Pipeline.h"

angle_t Angle::RadToDegree(const angle_t& rot){
    return (rot * (180.0f/PI));
}

angle_t Angle::DegreeToRad(const angle_t& rot){
    return (rot * (PI/180.0f));
}

Angle::Angle( angle_t rotation, std::string _type ){
    m_rot   = rotation;

    for(width_t i = 0; i < _type.size(); i++){
        _type[i] = tolower(_type[i]);
    }

    if(_type == "radian"  ||
       _type == "radians" ||
       _type == "rad"     ||
       _type == "rads"      )
    {
        type    = RADIAN;
    }else{
        type    = DEGREE;
    }
}

Angle::Angle( const Angle& cpy ){
    type    = cpy.type;
    m_rot   = cpy.m_rot;
}

Angle& Angle::toRadians(){
    if(type == DEGREE){
        m_rot   = DegreeToRad(m_rot);
        type = RADIAN;
    }
    return *this;
}

Angle& Angle::toDegrees(){
    if(type == RADIAN){
        m_rot   = RadToDegree(m_rot);
        type = DEGREE;
    }

    return *this;
}

angle_t Angle::degrees() const{
    if(type == DEGREE){
        return m_rot;
    }else{
        return RadToDegree(m_rot);
    }
}

angle_t Angle::radians() const{
    if(type == RADIAN){
        return m_rot;
    }else{
        return DegreeToRad(m_rot);
    }
}
