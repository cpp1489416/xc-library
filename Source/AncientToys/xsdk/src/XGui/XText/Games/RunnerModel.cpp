#include <RunnerModel.h>

World::World(float width, float height)
{
    this->width = width;
    this->height = height;
    StateAdpater *state = runner.getStateAdpter();
    state->changeState(runner, StateInput::Standard);
}
