#include <iostream>
#include "et/eldentree.hpp"


void godHandler(et::god::GodEvent const& event)
{
    std::cout << "Zeous: " << event.info << '\n';
}

auto main() -> int
{
    et::god::God const zeous{
        .name = "Zeous",
        .id = 1
    };

    et::god::God const Medusa{
        .name = "Medusa",
        .id = 2

    };

    et::EldenTree tree;
    tree.addGod(zeous, godHandler);
    tree.addEvent(zeous, et::god::GodEvent{"zeous said: hi"});
    tree.addEvent(zeous, et::god::GodEvent{"zeous said: bye"});

    tree.addGod(Medusa, [](et::god::GodEvent const& event) {
        std::cout << "Medusa: " << event.info << std::endl;
    });
    tree.addEvent(Medusa, et::god::GodEvent{"medosa said fis fis"});
    tree.addEvent(Medusa, et::god::GodEvent{"medosa said haha"});


    tree.connect(zeous, Medusa); // unlike Qt eldentree is bidirectional

    tree.addEvent(Medusa, et::god::GodEvent{"hello zeous from medusa"});
    tree.addEvent(zeous, et::god::GodEvent{"hello medusa from zeus"});

    return tree.exec();
}
