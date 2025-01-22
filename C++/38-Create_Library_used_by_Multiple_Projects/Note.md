## 38. Create Library used by Multiple Projects

**Knowledge Points**: `why need this`, `settings about creating library and multuple projects`

1. **why need this**: 

    if you are working on anything sizeable, this is important not only beacause it can create `module` or `library` and **reuse** them, but also **mix languages**

2. **multiple projects**: 

    1. **the whole solution**: 

        `solution name`: `Game`

        `project1 name`: `Game`, `project2 name`: `Engine`

    2. **configuration types**:

        `project Game`: `Application (.exe)`

        `project Engine`: `Static library (.lib)`

    3. **set Additional Include Directories**: 

        set `Additional Include Directories` in the `Game project properties`: `$(SolutionDir)\Engine\src` (otherwise you will need to use `#include "../../Engine/src/Engine.h"`, which will be changed from time to time, but now we can simple write `#include "Engine.h"`)

    4. **link**: 

        1. **Build**: 

            ``Build` `project Engine` and get `Engine.lib`

        2. **Add Reference**: 

            `Add Reference` to `project Engine` for `project Game`, so we don't need to manually set the `Linker` settings and we also don't need to worry about something like changes of `project name` (e.g., `Engine` to `Core`), and there is another more important advantages that if there are some changes of `Engine`, and we are compiling `Game`, we are actually compiling `Game` and `Engine`

            (you can test this by that first `Clean Solution` and then just `Build` `Game` and you will see it will build `Engine` first)

    5. **run the program and check the result**: 

        you can copy the `Game.exe` file and paste to somewhere like the `Desktop` and just double click it, it will run successfully because we just use `static linking` here

