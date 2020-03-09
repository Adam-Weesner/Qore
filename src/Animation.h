// Qore Engine written by Adam Weesner @ 2020
#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
    public:
        Animation();
        Animation(unsigned int newIndex, unsigned int newNumFrames, unsigned int newAnimationSpeed);
        unsigned int index;
        unsigned int numFrames;
        unsigned int animationSpeed;
};

#endif