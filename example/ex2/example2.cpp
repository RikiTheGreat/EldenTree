#include <iostream>
#include "et/eldentree.hpp"


void godHandler(et::god::GodEvent const& event)
{
    std::cout << event.info << '\n';
}

auto main() -> int
{
    et::god::God const Zeous{
        .name = "Zeous",
        .id = 1
    };

    et::god::God const Medusa{
        .name = "Medusa",
        .id = 2

    };

    et::god::God const Queen{
        .name = "THE GLOAM-EYED QUEEN",
        .id = 3

    };

    et::god::God const Dragon{
        .name = "UNNAMED ANCIENT DRAGON GOD",
        .id = 4

    };

    et::god::God const Sky{
        .name = "SKY WARRIOR",
        .id = 5

    };

    et::EldenTree tree{et::land::iland32(2)};
    tree.addGod(Zeous, [](et::god::GodEvent const& event)
    {
        std::cout << "Zeous:" << event.info << '\n';
    });
    tree.addGod(Medusa, [](et::god::GodEvent const& event)
    {
        std::cout << "Medusa:" << event.info << '\n';
    });

    tree.addGod(Dragon, [](et::god::GodEvent const& event)
    {
        std::cout << "Dragon:" << event.info << '\n';
    });
    tree.addGod(Queen, [](et::god::GodEvent const& event)
    {
        std::cout << "Queen:" << event.info << '\n';
    });

    tree.addGod(Sky, [](et::god::GodEvent const& event)
{
    std::cout << "Sky:" << event.info << '\n';
});

    connect(tree, Zeous, Queen, Dragon, Sky);

    tree.addEvent(Queen, "hello from Queen");
    tree.addEvent(Dragon, "hello from Dragon");
    et::god::GodEvent sky_event;
    sky_event.info = "hello from sky";
    tree.addEvent(Sky, sky_event);

    std::cout << "something from main " << '\n';

    return tree.exec();
}
