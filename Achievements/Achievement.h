#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>

class Achievement
{
    public:
        //* typedef */
        //typedef bool (*AchievementFunction)(std::string name);
        typedef void (*CompletionFunction)(std::string name);

        /** Default constructor */
        Achievement(std::string name, std::string desc,CompletionFunction complete = NULL);//!< Creates an achieive and a static function that will be called upon to check if achieved
        /** Default destructor */
        virtual ~Achievement();

        std::string GetName();
        std::string GetDesc();

       // bool CheckFunction();//checks the condition fn for if true

        void SetName(std::string name);
        void SetDesc(std::string desc);
        //void SetFunction(AchievementFunction fn);
        void SetCompleteFunction(CompletionFunction fn);

        void Completed();//called on completion of acheiv
    protected:
    private:
        std::string m_name;
        std::string m_desc;
        //AchievementFunction m_fn_cond;
        CompletionFunction m_fn_comp;
};

#endif // ACHIEVEMENT_H
