#pragma once

#ifndef RUNNERMODEL_H
#define RUNNERMOFEL_H
#include <memory>

enum StateInput
{
    Standard,
    Jumping,
};

class Runner;

class State
{
public:
    virtual void update(Runner &runner) = 0;
    virtual bool isFinished() const = 0;
};

class StandardState final : public State
{
public:
    virtual void update(Runner &runner) final;
    virtual bool isFinished() const final { return false; }

private:
};

class JumpingState final : public State
{
public:
    virtual void update(Runner &runner) final;
    virtual bool isFinished() const final { return finished; }

private:
    bool finished;
    float heavy;
    float speed;
};

class StateAdpater
{
public:

public:
    void update(Runner &runner);
    bool changeState(Runner &runner, int state);
    State *getCurrentState() { return currentState; }

private:
    StandardState standardState;
    JumpingState jumpingState;
    State *currentState;
};

class Runner
{
public:
    void changeState(int state);
    void update();
    float getX() const { return x; }
    float getY() const { return y; }
    StateAdpater *getStateAdpter() { return &state; }

private:
    StateAdpater state;
    float x;
    float y;
};

class World
{
public:
    World(float width, float height);
private:
    Runner runner;
    float width;
    float height;
};

#endif // RUNNERMODEL_H

