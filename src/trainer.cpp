#include <flashback/trainer.hpp>

using namespace flashback;

trainer::trainer(): _practice_queue{}, _stream{std::cerr, std::cin}
{
}

void trainer::init()
{
    _stream.write("\nTrainer\n", console::color::pink);
}
