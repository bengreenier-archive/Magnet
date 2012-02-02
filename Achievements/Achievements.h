#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include "Achievement.h"

#include <vector>
#include <iostream>

//Achievements::Register   , call register on the achievements object for whatever you want to have achievements 4

namespace achievementglobals{static const bool debug=true; };


namespace Achievements{
    class Registry{
        public:

            void Register(Achievement* in,EventListener* evt){

                m_cheives.push_back(in);
                EventHandler::AddListener(evt);//waiting at this stage for adam to add data capabilities to listeners
            }

            void Finish(Achievement* in)
            {
                in->Completed();
                Remove(in);
                m_done.push_back(in);
            }

            void Remove(std::string name){
                cheives_iterator_t it;

                for(it  =   m_cheives.begin();
                    it  !=  m_cheives.end();
                    it++)
                {
                    if ((*it)->GetName() == name)
                        m_cheives.erase(it);
                }

            }

            void Remove(Achievement* in){
                cheives_iterator_t it;

                for(it  =   m_cheives.begin();
                    it  !=  m_cheives.end();
                    it++)
                {
                    if ((*it) == in)
                        m_cheives.erase(it);
                }

            }

            void IterateAll(){
                cheives_iterator_t it;

                for(it  =   m_cheives.begin();
                    it  !=  m_cheives.end();
                    it++)
                {
                    if (achievementglobals::debug)
                        std::cout<<"[Acheivements][IterateAll] "<<(*it)->GetName()<<"\n";
                }
            }
        protected:
        private:
            std::vector<Achievement*>           m_cheives;
            std::vector<Achievement*>           m_done;
            typedef std::vector<Achievement*>::iterator cheives_iterator_t;

    };
}
#endif // ACHEIVEMENTS_H
