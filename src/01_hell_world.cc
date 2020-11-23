#include <string>
#include <iostream>
#include <chrono>

#include <caf/event_based_actor.hpp>
#include <caf/actor_ostream.hpp>
#include <caf/exec_main.hpp>

caf::behavior mirror(caf::event_based_actor* self)
{
    return {
        [=] (const std::string& what) -> std::string {
            caf::aout(self) << what << std::endl;
            return std::string(what.rbegin(), what.rend());
        }
    };
}

void hello_world(caf::event_based_actor* self, const caf::actor& buddy)
{
    self->request(buddy, std::chrono::seconds(10), "hell world")
        .then(
            [=] (const std::string& what) {
                caf::aout(self) << what << std::endl;
            }
        );
}


void caf_main(caf::actor_system& system)
{
    auto mirror_actor = system.spawn(mirror);
    system.spawn(hello_world, mirror_actor);
}



int main(int argc, char** argv)
{
    return caf::exec_main(caf_main, argc, argv);
}