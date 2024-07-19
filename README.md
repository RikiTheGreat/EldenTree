# EldenTree
## _EldenTree event handler_

![image info](logo.jpeg "EldenTree logo")


EldenTree is an event handler library written in  ✨C++✨   in order to please the gods.

## Features

- Compatible with all  C++ standards (11 ... 26)
- Cross Platform
- built-in concurrency support
- Qt like api style (almost!)
- Optimized and fast 

<br/>

> _When the gods are angry because of a junior Js developer
> you need a fast C++ event handler which you don't have to put
> sleep at the end of your main unlike other handlers!_


## Example

```c++
#include <iostream>
#include "et/eldentree.hpp"


void godHandler(et::god::GodEvent const& event)
{
    std::cout << "Zeous: " << event.info << '\n';
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

    et::EldenTree tree;
    tree.addGod(Zeous, godHandler);
    tree.addEvent(Zeous, et::god::GodEvent{"zeous said: hi"});
    tree.addEvent(Zeous, "zeous said: bye");

    tree.addGod(Medusa, [](et::god::GodEvent const& event) {
        std::cout << "Medusa: " << event.info << '\n';
    });
    
    tree.addEvent(Medusa, et::god::GodEvent{"medosa said fis fis"});
    tree.addEvent(Medusa, et::god::GodEvent{"medosa said haha"});


    tree.connect(Zeous, Medusa); // unlike Qt EldenTree is bidirectional

    tree.addEvent(Medusa, "hello zeous from medusa");
    tree.addEvent(Zeous, et::god::GodEvent{"hello medusa from zeus"});

    std::cout << "something from main " << '\n';

    return tree.exec();
}
```

## Getting Started

To get started, see [Requirements](#requirements) and [Installation](#installation). see [Documents](#documents) 
for a more comprehensive feature overview.


## Requirements
EldenTree relays on some third-party libraries, such as [Google Benchmark][Benchmark]
and [Google Test][Test]. Use [Vcpkg][vcpkg] to installing them automatically via [Cmake][cmake]!


## Installation
see all presets and select one! For example:

``
    cmake --list-presets
``
<br/>
``
cmake --preset Linux-Release-Ninja
``
</br>
``
cd Linux-Release-Ninja && ninja
``

## Documents
Enable DO_DOC option in CMakeLists.txt . After that You'll see a doc folder in you build directory.
go inside it and then run ``doxygen Doxyfile.doc``.


[Benchmark]: https://github.com/google/benchmark
[Test]: https://github.com/google/googletest
[vcpkg]: https://vcpkg.io/en/index.html
[cmake]: https://cmake.org/