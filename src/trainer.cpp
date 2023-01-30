#include <flashback/trainer.hpp>

using namespace flashback;

trainer::trainer(): _practice_queue{}, _stream{std::cin, std::cout}
{
}

void trainer::init()
{
    _stream << color::pink;
    _stream.header("Trainer");
}
