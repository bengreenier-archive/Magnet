#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

class KeyBindings
{
    public:
        KeyBindings();
        ~KeyBindings();
        static KeyBindings* GetBindings();
        static void AddBinding(sf::Key::Code);//should take function ptr also.
        static void RemoveBinding(sf::Key::Code);//also takes function ptr
        static void CheckKeys();
    protected:
    private:
        static KeyBindings* BindingHolderPtr;
 //       static std::vector < std::map <sf::Key::Code,/*Function Pointer*/> > function_map;

};

#endif // KEYBINDINGS_H

/*
The concept here is that to see what a key will do we build GetBindings into our Events loop.
What GetBindings will do is check if keypress && key= function_map[i].first and if so, call the function.
This way we can rebind keys, etc.
Should be helpful, though hard.
*/
