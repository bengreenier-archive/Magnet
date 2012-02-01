#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>

class Achievement
{
    public:
        /** Default constructor */
        Achievement(std::string name, std::string desc);
        /** Default destructor */
        virtual ~Achievement();

        std::string GetName();
        std::string GetDesc();

        void SetName(std::string name);
        void SetDesc(std::string desc);
    protected:
    private:
        std::string m_name;
        std::string m_desc;
};

#endif // ACHIEVEMENT_H
